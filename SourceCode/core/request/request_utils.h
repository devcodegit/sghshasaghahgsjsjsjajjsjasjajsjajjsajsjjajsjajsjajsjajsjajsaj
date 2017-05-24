#ifndef REQUEST_UTILS_H
#define REQUEST_UTILS_H

namespace Core { namespace Request {

    class RequestUtils
    {
    public:
        static int GET_REQUEST_ID();

    private:
        static int s_iRequestId;
    };

}
}

#endif // REQUEST_UTILS_H
