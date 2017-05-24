#ifndef I_API_REQUEST_LISTENER_H
#define I_API_REQUEST_LISTENER_H

namespace Core { namespace Request {

    class IApiRequest;

    class IApiRequestListener
    {
    public:
        virtual ~IApiRequestListener() {}

        virtual void OnApiRequestComplete(IApiRequest* a_pRequest) = 0;
        virtual void OnApiRequestError(IApiRequest* a_pRequest) = 0;
    };

}
}

#endif // I_API_REQUEST_LISTENER_H
