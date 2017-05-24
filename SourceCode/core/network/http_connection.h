#ifndef HTTP_CONNECTION_H
#define HTTP_CONNECTION_H

#include <QObject>
#include <QTimer>
#include <QNetworkReply>

namespace Core { namespace Network {

    class HttpConnection : public QObject
    {
        Q_OBJECT
    public:
        HttpConnection();
        ~HttpConnection();

        void openGetConnection(QNetworkAccessManager* m_pNetworkManager,
                               const QString& a_sUrl,
                               const QList<QNetworkCookie>& a_CookieList = QList<QNetworkCookie>(),
                               int a_MilisecTimeOut = -1);

        void openPostConnection(QNetworkAccessManager* m_pNetworkManager,
                                const QString& a_sUrl,
                                const QByteArray& a_PostData,
                                const QList<QNetworkCookie>& a_CookieList = QList<QNetworkCookie>(),
                                int a_MilisecTimeOut = -1);

        void Cancel();

        int getResponseCode();

        QByteArray getResponseData();

        QString getHeader(const QString& a_sHeaderName);

    private slots:
        void onRequestFinish();
        void onRequestTimeout();

    signals:
        void notifyRequestComplete();

    private:
        void stopTimeoutTimer();

    private:
        QNetworkReply* m_pRequestReply;
        QMutex m_Lock;

        QByteArray m_ResponseData;
        int m_ResponseCode;
        QTimer m_TimeOutTimer;
    };

}
}
#endif // HTTP_CONNECTION_H
