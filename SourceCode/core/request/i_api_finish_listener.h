#ifndef I_API_FINISH_LISTENER_H
#define I_API_FINISH_LISTENER_H

namespace Core { namespace Request {

    class IApiFinishListener
    {
    public:
        virtual ~IApiFinishListener() {}

        virtual void OnApiFinish(int aRequestId) = 0;
    };

}
}


#endif // I_API_FINISH_LISTENER_H
