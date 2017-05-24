#include "network_manager_factory.h"

#include <QNetworkProxy>
#include <QFile>
#include <QTextCodec>

using namespace Core::Network;

QMutex NetworkManagerFactory::mutexIns;
NetworkManagerFactory *NetworkManagerFactory::Instance = NULL;

NetworkManagerFactory *NetworkManagerFactory::instance()
{
    if (!Instance)
    {
        mutexIns.lock();
        if (!Instance)
        {
            Instance = new NetworkManagerFactory();
        }
        mutexIns.unlock();
    }
    return Instance;
}

NetworkManagerFactory::NetworkManagerFactory()
{

}

NetworkManagerFactory::~NetworkManagerFactory()
{
    for(int iter = 0; iter < m_networkManagerList.size(); iter++)
    {
        QNetworkAccessManager* i_pNetworkManager = m_networkManagerList.at(iter);
        i_pNetworkManager->deleteLater();
    }
    m_networkManagerList.clear();
}

QNetworkAccessManager *NetworkManagerFactory::getNetworkManager()
{
    QNetworkAccessManager* i_pNetworkManager = new QNetworkAccessManager();
    doConfig(i_pNetworkManager);
    m_networkManagerList.append(i_pNetworkManager);
    return i_pNetworkManager;
}

void NetworkManagerFactory::removeNetworkManager(QNetworkAccessManager *a_pNetworkManager)
{
    m_networkManagerList.removeAll(a_pNetworkManager);
}

void NetworkManagerFactory::doConfig(QNetworkAccessManager *a_pNetworkManager)
{
    // set config for a_pNetworkManager
    // Set Proxy
    QString proxy = /*ZTransport::instance()->getProxy()*/"";
    QString iHost = "";
    int iPort = 0;
    if (!proxy.isEmpty())
    {
//        QNetworkProxyFactory::setUseSystemConfiguration(false);
//        int idx = proxy.lastIndexOf(":");
//        if (idx != -1) { // Found port
//            QString iPortStr = proxy.mid(idx + 1);
//            bool isSuccess = false;
//            iPort = iPortStr.toShort(&isSuccess);
//            iHost = proxy.mid(0, idx);
//        } else {
//            // Not found port
//            iHost = proxy;
//        }

//        if (!iHost.isEmpty() && iPort > 0) {
//            QNetworkProxy iProxy;
//            iProxy.setHostName(iHost);
//            iProxy.setPort(iPort);

//            int iProxyType = ZTransport::instance()->getProxyType();
//            if (iProxyType == TYPE_PROXY_SOCKS) {
//                iProxy.setType(QNetworkProxy::Socks5Proxy);
//            } else {
//                iProxy.setType(QNetworkProxy::HttpProxy);
//            }

//            if (!ZTransport::instance()->getUserProxy().isEmpty())
//            {
//                iProxy.setUser(ZTransport::instance()->getUserProxy());
//                if (!ZTransport::instance()->getPassProxy().isEmpty())
//                {
//                    iProxy.setPassword(ZTransport::instance()->getPassProxy());
//                }
//            }
//            a_pNetworkManager->setProxy(iProxy);
//        }
    }
    else
    {
        QNetworkProxyFactory::setUseSystemConfiguration(true);
    }
}

void NetworkManagerFactory::Init(const QString &a_sCertificateFilePath)
{
    // Add more CA certificate to default config of QSslConfiguration
    // Certificate get from FireFox at
    // https://raw.githubusercontent.com/bagder/ca-bundle/master/ca-bundle.crt
    QFile iCertFile(a_sCertificateFilePath);
    if (iCertFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream iTextStream(&iCertFile);
        iTextStream.setCodec(QTextCodec::codecForName("UTF-8"));
        const QString iCertData = iTextStream.readAll();
        // Get List Cert from Default Config
        QSslConfiguration iDefaultConfig = QSslConfiguration::defaultConfiguration();
        QList<QSslCertificate> iDefaultCertList = iDefaultConfig.caCertificates();
        // Add Old default QSslCertificate list to the new one from file
        QList<QSslCertificate> iListCert = QSslCertificate::fromData(iCertData.toUtf8(), QSsl::Pem);
        for (int iter = 0; iter < iDefaultCertList.size(); ++iter)
        {
            QSslCertificate iCertificate = iDefaultCertList[iter];
            iListCert.append(iCertificate);
        }
        // Set new certificate list againt to GlobalConfig
        iDefaultConfig.setCaCertificates(iListCert);
        QSslConfiguration::setDefaultConfiguration(iDefaultConfig);
        // Close file
        iCertFile.close();
    }
}

void NetworkManagerFactory::onProxyChange()
{
    // Iterator through all NetworkAccessManager instance and update proxy
    for (int iter = 0; iter < m_networkManagerList.size(); ++iter)
    {
        QNetworkAccessManager* i_pNetworkManager = m_networkManagerList.at(iter);
        doConfig(i_pNetworkManager);
    }
}

void NetworkManagerFactory::onProxyReset()
{
    for (int iter = 0; iter < m_networkManagerList.size(); ++iter)
    {
        QNetworkAccessManager* i_pNetworkManager = m_networkManagerList.at(iter);
        QNetworkProxy iProxy;
        iProxy.setType(QNetworkProxy::NoProxy);
        i_pNetworkManager->setProxy(iProxy);
    }
}
