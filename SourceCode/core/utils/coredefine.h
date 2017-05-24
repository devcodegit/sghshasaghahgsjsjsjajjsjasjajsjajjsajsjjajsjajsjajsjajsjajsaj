#ifndef COREDEFINE_H
#define COREDEFINE_H

namespace Core { namespace ErrorCode {

    class CoreErrorCode
    {
    public:
        static const int ERROR_NONE = 0;
        static const int ERROR_UNKNOW = -600;
        static const int ERROR_NETWORK_NOT_AVAILABE = -601;
        static const int ERROR_REQUEST_TIME_OUT = -602;
        static const int ERROR_PARSE_JSON = -603;
        static const int ERROR_MANUAL_CANCEL = -604;
        static const int ERROR_INVALID_SUBMIT_DATA = -605;
        static const int ERROR_INVALID_RESPONSE_DATA = -606;
        static const int ERROR_UNKNOW_FROM_SERVER = -607;
        static const int ERROR_READ_WRITE_FILE = -608;
        static const int ERROR_REQUEST_FAIL_MANY_TIME = -609;
        static const int ERROR_UNZIP_FILE = -610;
        static const int ERROR_CONFIG_HTTP = -611;
        static const int ERROR_DECOMPRESS_GZIP = -612;

        static const int ERROR_SESSION_EXPIRE = 102;
        static const int ERROR_ITEM_NOT_FOUND = 1001;
        static const int ERROR_PERMISSION_DENY = 500;
    };
}
}

#endif // COREDEFINE_H
