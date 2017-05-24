#ifndef JSON_EXCEPTION_H
#define JSON_EXCEPTION_H

namespace Core { namespace Json {

    class JsonException
    {
    public:
        const char * what () const throw ();
    };

} // End Json
} // End Core

#endif // JSON_EXCEPTION_H
