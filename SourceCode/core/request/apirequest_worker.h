#ifndef APIREQUEST_WORKER_H
#define APIREQUEST_WORKER_H

#include <QObject>
#include <QWaitCondition>
#include <QNetworkAccessManager>

#include "i_api_finish_listener.h"

namespace Core { namespace Request {
    class ApiRequest;

    class ApiRequestWorker : public QObject, public IApiFinishListener
    {
        Q_OBJECT
    public:
        static ApiRequestWorker* instance()
        {
            static ApiRequestWorker mInstance;
            return &mInstance;
        }

        void AddRequest(ApiRequest* aRequest);
        void RemoveRequest(int aRequestId);
        void ClearAllRequest();

        void StartWorker();
        void StopWorker();

        // Override IApiFinishListener
        void OnApiFinish(int aRequestId) override;

    protected:
        ApiRequestWorker();
        ~ApiRequestWorker();

    private slots:
        void run();

    private:
        void WakeAll();

    private:
        QThread* m_workerThread;
        QNetworkAccessManager* m_networkManager;
        QVector<ApiRequest*> m_requestQueue;
        QHash<int, ApiRequest*> m_currentRequestHash;

        QWaitCondition m_Wait;
        QMutex m_mutexLock;

        bool m_isRunning;
        bool m_isStop;
    };

}}

#endif // APIREQUEST_WORKER_H
