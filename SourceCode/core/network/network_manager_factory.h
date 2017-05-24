#ifndef NETWORK_MANAGER_FACTORY_H
#define NETWORK_MANAGER_FACTORY_H

#include <QMutex>
#include <QNetworkAccessManager>

namespace Core { namespace Network {

class NetworkManagerFactory
{
    NetworkManagerFactory();
    ~NetworkManagerFactory();
    static NetworkManagerFactory *Instance;
    static QMutex mutexIns;

public:
    static NetworkManagerFactory *instance();

    QNetworkAccessManager* getNetworkManager();
    void removeNetworkManager(QNetworkAccessManager *a_pNetworkManager);

    void doConfig(QNetworkAccessManager* a_pNetworkManager);

    void Init(const QString& a_sCertificateFilePath);

    void onProxyChange();
    void onProxyReset();

private:
    QList<QNetworkAccessManager *> m_networkManagerList;
};

}}

#endif // NETWORK_MANAGER_FACTORY_H
