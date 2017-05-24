#include "service_map_manager.h"

using namespace Core::Service;

QMutex ServiceMapManager::mutexIns;
ServiceMapManager *ServiceMapManager::Instance = NULL;
ServiceMapManager *ServiceMapManager::instance()
{
    if (!Instance)
    {
        mutexIns.lock();
        if (!Instance)
        {
            Instance = new ServiceMapManager();
        }
        mutexIns.unlock();
    }
    return Instance;
}

ServiceMapManager::ServiceMapManager()
{
    m_urlServiceLazada = QString("https://api.sellercenter.lazada.vn");
}

QString ServiceMapManager::urlServiceLazada() const
{
    return m_urlServiceLazada;
}
