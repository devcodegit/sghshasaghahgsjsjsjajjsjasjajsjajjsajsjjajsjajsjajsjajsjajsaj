#ifndef NETWORK_SESSION_MANAGER_H
#define NETWORK_SESSION_MANAGER_H

namespace Core { namespace Network {

    class NetworkSessionManager
    {
    public:
        enum NetworkType {
            TYPE_UNKNOW = 0,
            TYPE_WIFI = 1,
            TYPE_3G = 2,
            TYPE_2G = 3
        };

        enum TimeOutType {
            HTTP_TIMEOUT,
            CHAT_TIMEOUT,
            UPLOAD_TIMEOUT
        };

        static int GET_TIMEOUT(TimeOutType aTimeOutType);

        static bool NETWORK_AVAILABE();
    };

}}
#endif // NETWORK_SESSION_MANAGER_H
