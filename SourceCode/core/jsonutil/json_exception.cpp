#include "json_exception.h"

using namespace Core::Json;

const char *JsonException::what() const
{
    return "Json Exception";
}
