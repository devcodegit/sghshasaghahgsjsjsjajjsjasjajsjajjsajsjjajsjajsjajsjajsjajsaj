#include "apirequest_worker.h"
#include "apirequest.h"
#include "../network/network_manager_factory.h"

#include <QVector>
#include <QThread>

using namespace Core::Request;

namespace {
    const int32_t MAX_CONCURRENT_REQUEST = 10;
}

ApiRequestWorker::ApiRequestWorker()
    : m_isStop(true)
    , m_isRunning(false)
    , m_workerThread(NULL)
    , m_networkManager(NULL)
{
    m_workerThread = new QThread();
    connect(this, SIGNAL(destroyed(QObject*)), m_workerThread, SLOT(quit()));
    connect(m_workerThread, SIGNAL(finished()), m_workerThread, SLOT(deleteLater()));

    moveToThread(m_workerThread);
    m_workerThread->start();
}

ApiRequestWorker::~ApiRequestWorker()
{

}

void ApiRequestWorker::run()
{
    if (!m_networkManager)
    {
        //Todo: get network
        m_networkManager = NetworkManagerFactory::instance()->getNetworkManager();
    }
    ApiRequest* iRequest = NULL;
    while(true)
    {
        QMutexLocker iLocker(&m_mutexLock);
        if (m_requestQueue.size() > 0 && m_currentRequestHash.size() <= MAX_CONCURRENT_REQUEST)
        {
            iRequest = m_requestQueue.takeFirst();
            if (!iRequest)
            {
                continue;
            }
            m_currentRequestHash.insert(iRequest->getRequestId(), iRequest);
        }
        else
        {
            break;
        }
        iLocker.unlock();

        iRequest->setFinishListener(this);
        iRequest->Start();
        iRequest->Handle(m_networkManager);
    }
}

void ApiRequestWorker::WakeAll()
{
    QMetaObject::invokeMethod(this, "run");
}

void ApiRequestWorker::AddRequest(ApiRequest *aRequest)
{
    if (!aRequest)
    {
        return;
    }

    QMutexLocker locker(&m_mutexLock);
    int iPos = m_requestQueue.size();
    for (int i = 0; i < iPos; ++i)
    {
        ApiRequest *pTmpRequest = m_requestQueue.at(i);
        if (pTmpRequest->getPriority() > aRequest->getPriority())
        {
            iPos = i;
            break;
        }
    }
    m_requestQueue.insert(iPos, aRequest);

    WakeAll();
}

void ApiRequestWorker::RemoveRequest(int aRequestId)
{
    ApiRequest *iRequest = NULL;
    QMutexLocker locker(&m_mutexLock);

    for (int i = 0; i < m_requestQueue.size(); ++i)
    {
        ApiRequest *pTmpRequest =  m_requestQueue.at(i);
        if (pTmpRequest && pTmpRequest->getRequestId() == aRequestId)
        {
            m_requestQueue.removeAt(i);
            iRequest = pTmpRequest;
            break;
        }
    }

    if (m_currentRequestHash.contains(aRequestId))
    {
        iRequest = m_currentRequestHash.take(aRequestId);
    }

    WakeAll();

    locker.unlock();

    if (iRequest)
    {
         iRequest->cancelRequest();
        //Todo: Cancel request from ApiRequest
    }
}

void ApiRequestWorker::ClearAllRequest()
{
    QVector<ApiRequest*> removeList;
    QMutexLocker locker(&m_mutexLock);

    for(QHash<int, ApiRequest*>::iterator iter = m_currentRequestHash.begin(); iter != m_currentRequestHash.end(); ++iter)
    {
        removeList.append(iter.value());
    }
    m_currentRequestHash.clear();

    for (int iter = 0; iter < m_requestQueue.size(); ++iter)
    {
        removeList.append(m_requestQueue.at(iter));
    }
    m_requestQueue.clear();

    WakeAll();
    locker.unlock();

    for (int i = 0; i < removeList.count(); ++i)
    {
        ApiRequest* iRemoveRequest = removeList.at(i);
//        iRemoveRequest->cancelRequest();
        //Todo: Cancel request from ApiRequest
    }
    removeList.clear();
}

void ApiRequestWorker::StartWorker()
{
    QMutexLocker iLocker(&m_mutexLock);
    m_isStop = false;
}

void ApiRequestWorker::StopWorker()
{
    QMutexLocker iLocker(&m_mutexLock);
    m_isStop = true;
    ClearAllRequest();
}

void ApiRequestWorker::OnApiFinish(int aRequestId)
{
    ApiRequest* iRequest = NULL;
    QMutexLocker locker(&m_mutexLock);

    if (m_currentRequestHash.contains(aRequestId))
    {
        iRequest = m_currentRequestHash.take(aRequestId);
    }

    WakeAll();
}
