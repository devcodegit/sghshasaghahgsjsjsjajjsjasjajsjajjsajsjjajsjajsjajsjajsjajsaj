#include "network_session_manager.h"
#include <QVector>

using namespace Core::Network;

static int DEFAULT_TIMEOUT = 5000; // 5s
static QVector<int> HTTP_TIMEOUT_TABLE = {5000, 10000, 15000}; // WIFI, 3G, 2G

int NetworkSessionManager::GET_TIMEOUT(NetworkSessionManager::TimeOutType aTimeOutType)
{
    QVector<int> iTimeOutArr;

    switch (aTimeOutType) {
    case TimeOutType::HTTP_TIMEOUT:
        iTimeOutArr = HTTP_TIMEOUT_TABLE;
        break;
    default:
        break;
    }

    int iNetworkType = NetworkType::TYPE_UNKNOW;
    if (iTimeOutArr.size() > 0 && iTimeOutArr.size() > iNetworkType && iNetworkType >= 0)
    {
        return iTimeOutArr[iNetworkType];
    }
    else
    {
        return DEFAULT_TIMEOUT;
    }
}

bool NetworkSessionManager::NETWORK_AVAILABE()
{
    return true;
}
