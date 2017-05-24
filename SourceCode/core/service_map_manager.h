#ifndef SERVICE_MAP_MANAGER_H
#define SERVICE_MAP_MANAGER_H

#include <QMutex>
#include <QString>

namespace Core { namespace Service {

    class ServiceMapManager
    {
        ServiceMapManager();
        static ServiceMapManager *Instance;
        static QMutex mutexIns;

    public:
        static ServiceMapManager *instance();

        QString urlServiceLazada() const;

    private:
        QString m_urlServiceLazada;
    };

}
}

#endif // SERVICE_MAP_MANAGER_H
