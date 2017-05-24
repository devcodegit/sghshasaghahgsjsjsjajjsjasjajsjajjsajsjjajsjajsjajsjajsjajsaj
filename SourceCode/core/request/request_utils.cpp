#include "request_utils.h"
using namespace Core::Request;

int RequestUtils::s_iRequestId = 0;

int RequestUtils::GET_REQUEST_ID()
{
    s_iRequestId++;
    return s_iRequestId;
}
