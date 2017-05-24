#include "json_utils.h"
#include "json_exception.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <QDebug>

using namespace Core::Json;

Document& JsonUtils::parseJson(Document& aJsonDocument, const QString& aJsonData)
{
    aJsonDocument.Parse(aJsonData.toStdString().c_str());
    if (!aJsonDocument.HasParseError())
    {
        return aJsonDocument;
    }
    throw JsonException();
}

Document& JsonUtils::tryParseJson(Document& aJsonDocument, const QString& aJsonData)
{
    aJsonDocument.Parse(aJsonData.toStdString().c_str());
    if (!aJsonDocument.HasParseError())
    {
        return aJsonDocument;
    }
    static Document NULL_DOCUMENT;
    return NULL_DOCUMENT;
}

Value& JsonUtils::getJsonObject(Document& a_JsonDocument)
{
    if (a_JsonDocument.IsObject())
    {
        return a_JsonDocument;
    }
    // else throw JsonException
    throw JsonException();
}

Value& JsonUtils::getJsonObject(Value& a_JsonObj, const QString& a_sName)
{
    // Input must be object
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_ValueObj = iIter->value;
            if (i_ValueObj.IsObject())
            {
                return i_ValueObj;
            }
        }
    }
    // else throw JsonException
    throw JsonException();
}

Value& JsonUtils::getJsonObject(Value& a_JsonArr, int a_iIndex)
{
    if (a_JsonArr.IsArray() && a_iIndex >= 0 && a_JsonArr.Size() > a_iIndex)
    {
        Value& i_ValueObj = a_JsonArr[a_iIndex];
        if (i_ValueObj.IsObject())
        {
            return i_ValueObj;
        }
    }
    // else throw JsonException
    throw JsonException();
}

Value& JsonUtils::tryGetJsonObject(Document& a_JsonDocument)
{
    if (!a_JsonDocument.HasParseError() && a_JsonDocument.IsObject())
    {
        return a_JsonDocument;
    }
    // else return empty Obj
    return NULL_VALUE();
}

Value& JsonUtils::tryGetJsonObject(Value& a_JsonObj, const QString& a_sName)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_ValueObj = iIter->value;
            if (i_ValueObj.IsObject())
            {
                return i_ValueObj;
            }
        }
    }
    // else return empty Object
    return NULL_VALUE();
}

Value& JsonUtils::tryGetJsonObject(Value& a_JsonArr, int a_iIndex)
{
    if (a_JsonArr.IsArray() && a_iIndex >= 0 && a_JsonArr.Size() > a_iIndex)
    {
        Value& i_ValueObj = a_JsonArr[a_iIndex];
        if (i_ValueObj.IsObject())
        {
            return i_ValueObj;
        }
    }
    // else return Undefined Object
    return NULL_VALUE();
}

Value& JsonUtils::getJsonArray(Document& a_JsonDoc)
{
    if (!a_JsonDoc.HasParseError() && a_JsonDoc.IsArray())
    {
        return a_JsonDoc;
    }
    // else throw JsonException
    throw JsonException();
}

Value& JsonUtils::getJsonArray(Value& a_JsonObj, const QString& a_sName)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_ValueArr = iIter->value;
            if (i_ValueArr.IsArray())
            {
                return i_ValueArr;
            }
        }
    }
    // else throw JsonException
    throw JsonException();
}

Value& JsonUtils::getJsonArray(Value& a_JsonArr, int a_iIndex)
{
    if (a_JsonArr.IsArray() && a_iIndex >= 0 && a_JsonArr.Size() > a_iIndex)
    {
        Value& i_ValueArr = a_JsonArr[a_iIndex];
        if (i_ValueArr.IsArray())
        {
            return i_ValueArr;
        }
    }
    // else throw JsonException
    throw JsonException();
}

Value& JsonUtils::tryGetJsonArray(Document& a_JsonDoc)
{
    if (!a_JsonDoc.HasParseError() && a_JsonDoc.IsArray())
    {
        return a_JsonDoc;
    }
    // else return Empty Object
    return NULL_VALUE();
}

Value& JsonUtils::tryGetJsonArray(Value& a_JsonObj, const QString& a_sName)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_ValueArr = iIter->value;
            if (i_ValueArr.IsArray())
            {
                return i_ValueArr;
            }
        }
    }
    // else return Empty Object
    return NULL_VALUE();
}

Value& JsonUtils::tryGetJsonArray(Value& a_JsonArr, int a_iIndex)
{
    if (a_JsonArr.IsArray() && a_iIndex >= 0 && a_JsonArr.Size() > a_iIndex)
    {
        Value& i_ValueArr = a_JsonArr[a_iIndex];
        if (i_ValueArr.IsArray())
        {
            return i_ValueArr;
        }
    }
    // else return Empty Object
    return NULL_VALUE();
}

int32_t JsonUtils::getInt(Value& a_JsonObj, const QString& a_sName)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_Value = iIter->value;
            if (i_Value.IsInt())
            {
                return i_Value.GetInt();
            }
        }
    }
    // else throw JsonException
    throw JsonException();
}

int32_t JsonUtils::getInt(Value& a_JsonArr, int a_iIndex)
{
    if (a_JsonArr.IsArray() && a_iIndex >= 0 && a_JsonArr.Size() > a_iIndex)
    {
        Value& i_Value = a_JsonArr[a_iIndex];
        if (i_Value.IsInt())
        {
            return i_Value.GetInt();
        }
    }
    // else throw JsonException
    throw JsonException();
}

int32_t JsonUtils::getIntFromStr(Value& a_JsonObj, const QString& a_sName)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_Value = iIter->value;
            if (i_Value.IsString())
            {
                SizeType iStrLen = i_Value.GetStringLength();
                const char* i_ValueStream = i_Value.GetString();
                std::string i_ValueStdStr(i_ValueStream, iStrLen);
                QString i_ValueStr = QString::fromStdString(i_ValueStdStr);
                // convert to int32_t
                bool isSuccess = false;
                int32_t i_iResult = i_ValueStr.toInt(&isSuccess);
                if (isSuccess)
                {
                    return i_iResult;
                }
            }
        }
    }
    // else throw JsonException
    throw JsonException();
}

int32_t JsonUtils::getIntFromStr(Value& a_JsonArr, int a_iIndex)
{
    if (a_JsonArr.IsArray() && a_iIndex >= 0 && a_JsonArr.Size() > a_iIndex)
    {
        Value& i_Value = a_JsonArr[a_iIndex];
        if (i_Value.IsString())
        {
            SizeType iStrLen = i_Value.GetStringLength();
            const char* i_ValueStream = i_Value.GetString();
            std::string i_ValueStdStr(i_ValueStream, iStrLen);
            QString i_ValueStr = QString::fromStdString(i_ValueStdStr);
            // convert to int32_t
            bool isSuccess = false;
            int32_t i_iResult = i_ValueStr.toInt(&isSuccess);
            if (isSuccess)
            {
                return i_iResult;
            }
        }
    }
    // else throw JsonException
    throw JsonException();
}

int32_t JsonUtils::tryGetInt(Value& a_JsonObj, const QString& a_sName, int32_t a_iDefault)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_Value = iIter->value;
            if (i_Value.IsInt())
            {
                return i_Value.GetInt();
            }
        }
    }
    // else return Default
    return a_iDefault;
}

int32_t JsonUtils::tryGetInt(Value& a_JsonArr, int a_iIndex, int32_t a_iDefault)
{
    if (a_JsonArr.IsArray() && a_iIndex >= 0 && a_JsonArr.Size() > a_iIndex)
    {
        Value& i_Value = a_JsonArr[a_iIndex];
        if (i_Value.IsInt())
        {
            return i_Value.GetInt();
        }
    }
    // else return Default
    return a_iDefault;
}

int32_t JsonUtils::tryGetIntOrStr(Value &a_JsonObj, const QString &a_sName, int32_t a_iDefault)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_Value = iIter->value;
            if (i_Value.IsInt())
            {
                return i_Value.GetInt();
            }
            else if (i_Value.IsString())
            {
                SizeType iStrLen = i_Value.GetStringLength();
                const char* i_ValueStream = i_Value.GetString();
                std::string i_ValueStdStr(i_ValueStream, iStrLen);
                QString i_ValueStr = QString::fromStdString(i_ValueStdStr);

                bool ok = false;
                int ret = i_ValueStr.toInt(&ok);
                if (ok)
                {
                    return ret;
                }
            }
        }
    }
    // else return Default
    return a_iDefault;
}

int32_t JsonUtils::tryGetIntFromStr(Value& a_JsonObj, const QString& a_sName, int32_t a_iDefault)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_Value = iIter->value;
            if (i_Value.IsString())
            {
                SizeType iStrLen = i_Value.GetStringLength();
                const char* i_ValueStream = i_Value.GetString();
                std::string i_ValueStdStr(i_ValueStream, iStrLen);
                QString i_ValueStr = QString::fromStdString(i_ValueStdStr);
                // convert to int32_t
                bool isSuccess = false;
                int32_t i_iResult = i_ValueStr.toInt(&isSuccess);
                if (isSuccess)
                {
                    return i_iResult;
                }
            }
        }
    }
    return a_iDefault;
}

int32_t JsonUtils::tryGetIntFromStr(Value& a_JsonArr, int a_iIndex, int32_t a_iDefault)
{
    if (a_JsonArr.IsArray() && a_iIndex >= 0 && a_JsonArr.Size() > a_iIndex)
    {
        Value& i_Value = a_JsonArr[a_iIndex];
        if (i_Value.IsString())
        {
            SizeType iStrLen = i_Value.GetStringLength();
            const char* i_ValueStream = i_Value.GetString();
            std::string i_ValueStdStr(i_ValueStream, iStrLen);
            QString i_ValueStr = QString::fromStdString(i_ValueStdStr);
            // convert to int32_t
            bool isSuccess = false;
            int32_t i_iResult = i_ValueStr.toInt(&isSuccess);
            if (isSuccess)
            {
                return i_iResult;
            }
        }
    }
    // else return Default
    return a_iDefault;
}

int64_t JsonUtils::getLong(Value& a_JsonObj, const QString& a_sName)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_Value = iIter->value;
            if (i_Value.IsInt64())
            {
                return i_Value.GetInt64();
            }
        }
    }
    // else throw JsonException
    throw JsonException();
}

int64_t JsonUtils::getLong(Value& a_JsonArr, int a_iIndex)
{
    if (a_JsonArr.IsArray() && a_iIndex >= 0 && a_JsonArr.Size() > a_iIndex)
    {
        Value& i_Value = a_JsonArr[a_iIndex];
        if (i_Value.IsInt64())
        {
            return i_Value.GetInt64();
        }
    }
    // else throw JsonException
    throw JsonException();
}

int64_t JsonUtils::getLongFromStr(Value& a_JsonObj, const QString& a_sName)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_Value = iIter->value;
            if (i_Value.IsString())
            {
                SizeType iStrLen = i_Value.GetStringLength();
                const char* i_ValueStream = i_Value.GetString();
                std::string i_ValueStdStr(i_ValueStream, iStrLen);
                QString i_ValueStr = QString::fromStdString(i_ValueStdStr);
                // convert to int64_t
                bool isSuccess = false;
                int64_t i_iResult = i_ValueStr.toLongLong(&isSuccess);
                if (isSuccess)
                {
                    return i_iResult;
                }
            }
        }
    }
    // else throw JsonException
    throw JsonException();
}

int64_t JsonUtils::getLongFromStr(Value& a_JsonArr, int a_iIndex)
{
    if (a_JsonArr.IsArray() && a_iIndex >= 0 && a_JsonArr.Size() > a_iIndex)
    {
        Value& i_Value = a_JsonArr[a_iIndex];
        if (i_Value.IsString())
        {
            SizeType iStrLen = i_Value.GetStringLength();
            const char* i_ValueStream = i_Value.GetString();
            std::string i_ValueStdStr(i_ValueStream, iStrLen);
            QString i_ValueStr = QString::fromStdString(i_ValueStdStr);
            // convert to int64_t
            bool isSuccess = false;
            int64_t i_iResult = i_ValueStr.toLongLong(&isSuccess);
            if (isSuccess)
            {
                return i_iResult;
            }
        }
    }
    // else throw JsonException
    throw JsonException();
}

int64_t JsonUtils::tryGetLong(Value& a_JsonObj, const QString& a_sName, int64_t a_lDefault)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_Value = iIter->value;
            if (i_Value.IsInt64())
            {
                return i_Value.GetInt64();
            }
        }
    }
    // else return Default
    return a_lDefault;
}

int64_t JsonUtils::tryGetLong(Value& a_JsonArr, int a_iIndex, int64_t a_lDefault)
{
    if (a_JsonArr.IsArray() && a_iIndex >= 0 && a_JsonArr.Size() > a_iIndex)
    {
        Value& i_Value = a_JsonArr[a_iIndex];
        if (i_Value.IsInt64())
        {
            return i_Value.GetInt64();
        }
    }
    // else return Default
    return a_lDefault;
}

int64_t JsonUtils::tryGetLongFromStr(Value& a_JsonObj, const QString& a_sName, int64_t a_lDefault)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_Value = iIter->value;
            if (i_Value.IsString())
            {
                SizeType iStrLen = i_Value.GetStringLength();
                const char* i_ValueStream = i_Value.GetString();
                std::string i_ValueStdStr(i_ValueStream, iStrLen);
                QString i_ValueStr = QString::fromStdString(i_ValueStdStr);
                // convert to int64_t
                bool isSuccess = false;
                int64_t i_iResult = i_ValueStr.toLongLong(&isSuccess);
                if (isSuccess)
                {
                    return i_iResult;
                }
            }
        }
    }
    // else return Default
    return a_lDefault;
}

int64_t JsonUtils::tryGetLongFromStr(Value& a_JsonArr, int a_iIndex, int64_t a_lDefault)
{
    if (a_JsonArr.IsArray() && a_iIndex >= 0 && a_JsonArr.Size() > a_iIndex)
    {
        Value& i_Value = a_JsonArr[a_iIndex];
        if (i_Value.IsString())
        {
            SizeType iStrLen = i_Value.GetStringLength();
            const char* i_ValueStream = i_Value.GetString();
            std::string i_ValueStdStr(i_ValueStream, iStrLen);
            QString i_ValueStr = QString::fromStdString(i_ValueStdStr);
            // convert to int64_t
            bool isSuccess = false;
            int64_t i_iResult = i_ValueStr.toLongLong(&isSuccess);
            if (isSuccess)
            {
                return i_iResult;
            }
        }
    }
    // else return Default
    return a_lDefault;
}

double JsonUtils::getDouble(Value& a_JsonObj, const QString& a_sName)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_Value = iIter->value;
            if (i_Value.IsDouble())
            {
                return i_Value.GetDouble();
            }
        }
    }
    // else throw JsonException
    throw JsonException();
}

double JsonUtils::getDouble(Value& a_JsonArr, int a_iIndex)
{
    if (a_JsonArr.IsArray() && a_iIndex >= 0 && a_JsonArr.Size() > a_iIndex)
    {
        Value& i_Value = a_JsonArr[a_iIndex];
        if (i_Value.IsDouble())
        {
            return i_Value.GetDouble();
        }
    }
    // else throw JsonException
    throw JsonException();
}

double JsonUtils::getDoubleFromStr(Value& a_JsonObj, const QString& a_sName)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_Value = iIter->value;
            if (i_Value.IsString())
            {
                SizeType iStrLen = i_Value.GetStringLength();
                const char* i_ValueStream = i_Value.GetString();
                std::string i_ValueStdStr(i_ValueStream, iStrLen);
                QString i_ValueStr = QString::fromStdString(i_ValueStdStr);
                // convert to double
                bool isSuccess = false;
                double i_iResult = i_ValueStr.toDouble(&isSuccess);
                if (isSuccess)
                {
                    return i_iResult;
                }
            }
        }
    }
    // else throw JsonException
    throw JsonException();
}

double JsonUtils::getDoubleFromStr(Value& a_JsonArr, int a_iIndex)
{
    if (a_JsonArr.IsArray() && a_iIndex >= 0 && a_JsonArr.Size() > a_iIndex)
    {
        Value& i_Value = a_JsonArr[a_iIndex];
        if (i_Value.IsString())
        {
            SizeType iStrLen = i_Value.GetStringLength();
            const char* i_ValueStream = i_Value.GetString();
            std::string i_ValueStdStr(i_ValueStream, iStrLen);
            QString i_ValueStr = QString::fromStdString(i_ValueStdStr);
            // convert to double
            bool isSuccess = false;
            double i_iResult = i_ValueStr.toDouble(&isSuccess);
            if (isSuccess)
            {
                return i_iResult;
            }
        }
    }
    // else throw JsonException
    throw JsonException();
}

double JsonUtils::tryGetDouble(Value& a_JsonObj, const QString& a_sName, double a_dDefault)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_Value = iIter->value;
            if (i_Value.IsDouble())
            {
                return i_Value.GetDouble();
            }
        }
    }
    // else return Default
    return a_dDefault;
}

double JsonUtils::tryGetDouble(Value& a_JsonArr, int a_iIndex, double a_dDefault)
{
    if (a_JsonArr.IsArray() && a_iIndex >= 0 && a_JsonArr.Size() > a_iIndex)
    {
        Value& i_Value = a_JsonArr[a_iIndex];
        if (i_Value.IsDouble())
        {
            return i_Value.GetDouble();
        }
    }
    // else return Default
    return a_dDefault;
}

double JsonUtils::tryGetDoubleOrStr(Value& a_JsonObj, const QString& a_sName, double a_dDefault)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_Value = iIter->value;
            if (i_Value.IsDouble())
            {
                return i_Value.GetDouble();
            }
            else if (i_Value.IsString())
            {
                SizeType iStrLen = i_Value.GetStringLength();
                const char* i_ValueStream = i_Value.GetString();
                std::string i_ValueStdStr(i_ValueStream, iStrLen);
                QString i_ValueStr = QString::fromStdString(i_ValueStdStr);

                bool ok = false;
                double ret = i_ValueStr.toDouble(&ok);
                if (ok)
                {
                    return ret;
                }
            }
        }
    }
    // else return Default
    return a_dDefault;
}

double JsonUtils::tryGetDoubleFromStr(Value& a_JsonObj, const QString& a_sName, double a_dDefault)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_Value = iIter->value;
            if (i_Value.IsString())
            {
                SizeType iStrLen = i_Value.GetStringLength();
                const char* i_ValueStream = i_Value.GetString();
                std::string i_ValueStdStr(i_ValueStream, iStrLen);
                QString i_ValueStr = QString::fromStdString(i_ValueStdStr);
                // convert to double
                bool isSuccess = false;
                double i_iResult = i_ValueStr.toDouble(&isSuccess);
                if (isSuccess)
                {
                    return i_iResult;
                }
            }
        }
    }
    // else return Default
    return a_dDefault;
}

double JsonUtils::tryGetDoubleFromStr(Value& a_JsonArr, int a_iIndex, double a_dDefault)
{
    if (a_JsonArr.IsArray() && a_iIndex >= 0 && a_JsonArr.Size() > a_iIndex)
    {
        Value& i_Value = a_JsonArr[a_iIndex];
        if (i_Value.IsString())
        {
            SizeType iStrLen = i_Value.GetStringLength();
            const char* i_ValueStream = i_Value.GetString();
            std::string i_ValueStdStr(i_ValueStream, iStrLen);
            QString i_ValueStr = QString::fromStdString(i_ValueStdStr);
            // convert to double
            bool isSuccess = false;
            double i_iResult = i_ValueStr.toDouble(&isSuccess);
            if (isSuccess)
            {
                return i_iResult;
            }
        }
    }
    // else return Default
    return a_dDefault;
}

QString JsonUtils::getString(Value& a_JsonObj, const QString& a_sName)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_Value = iIter->value;
            if (i_Value.IsString())
            {
                SizeType iStrLen = i_Value.GetStringLength();
                const char* i_ValueStream = i_Value.GetString();
                std::string i_ValueStdStr(i_ValueStream, iStrLen);
                QString i_ValueStr = QString::fromStdString(i_ValueStdStr);
                return i_ValueStr;
            }
        }
    }
    // else throw JsonException
    throw JsonException();
}

QString JsonUtils::getString(Value& a_JsonArr, int a_iIndex)
{
    if (a_JsonArr.IsArray() && a_iIndex >= 0 && a_JsonArr.Size() > a_iIndex)
    {
        Value& i_Value = a_JsonArr[a_iIndex];
        if (i_Value.IsString())
        {
            SizeType iStrLen = i_Value.GetStringLength();
            const char* i_ValueStream = i_Value.GetString();
            std::string i_ValueStdStr(i_ValueStream, iStrLen);
            QString i_ValueStr = QString::fromStdString(i_ValueStdStr);
            return i_ValueStr;
        }
    }
    // else throw JsonException
    throw JsonException();
}

QString JsonUtils::tryGetString(Value& a_JsonObj, const QString& a_sName, const QString& a_sDefault)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_Value = iIter->value;
            if (i_Value.IsString())
            {
                SizeType iStrLen = i_Value.GetStringLength();
                const char* i_ValueStream = i_Value.GetString();
                std::string i_ValueStdStr(i_ValueStream, iStrLen);
                QString i_ValueStr = QString::fromStdString(i_ValueStdStr);
                return i_ValueStr;
            }
        }
    }
    // else return Default
    return a_sDefault;
}

QString JsonUtils::tryGetString(Value& a_JsonArr, int a_iIndex, const QString& a_sDefault)
{
    if (a_JsonArr.IsArray() && a_iIndex >= 0 && a_JsonArr.Size() > a_iIndex)
    {
        Value& i_Value = a_JsonArr[a_iIndex];
        if (i_Value.IsString())
        {
            SizeType iStrLen = i_Value.GetStringLength();
            const char* i_ValueStream = i_Value.GetString();
            std::string i_ValueStdStr(i_ValueStream, iStrLen);
            QString i_ValueStr = QString::fromStdString(i_ValueStdStr);
            return i_ValueStr;
        }
    }
    // else return Default
    return a_sDefault;
}

bool JsonUtils::getBool(Value& a_JsonObj, const QString& a_sName)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_Value = iIter->value;
            if (i_Value.IsBool())
            {
                return i_Value.GetBool();
            }
            else if (i_Value.IsInt())
            {
                int32_t i_IntValue = i_Value.GetInt();
                if (i_IntValue == 0)
                {
                    return false;
                }
                else if(i_IntValue == 1)
                {
                    return true;
                }
            }
        }
    }
    // else throw JsonException
    throw JsonException();
}

bool JsonUtils::getBool(Value& a_JsonArr, int a_iIndex)
{
    if (a_JsonArr.IsArray() && a_iIndex >= 0 && a_JsonArr.Size() > a_iIndex)
    {
        Value& i_Value = a_JsonArr[a_iIndex];
        if (i_Value.IsBool())
        {
            return i_Value.GetBool();
        }
        else if (i_Value.IsInt())
        {
            int32_t i_IntValue = i_Value.GetInt();
            if (i_IntValue == 0)
            {
                return false;
            }
            else if(i_IntValue == 1)
            {
                return true;
            }
        }
    }
    // else throw JsonException
    throw JsonException();
}

bool JsonUtils::tryGetBool(Value& a_JsonObj, const QString& a_sName, bool a_isDefault)
{
    if (a_JsonObj.IsObject())
    {
        // Used FindMember to prevent double seek when used .HasMember & ["key"]
        Value::MemberIterator iIter = a_JsonObj.FindMember(a_sName.toStdString().c_str());
        if (iIter != a_JsonObj.MemberEnd())
        {
            Value& i_Value = iIter->value;
            if (i_Value.IsBool())
            {
                return i_Value.GetBool();
            }
            else if (i_Value.IsInt())
            {
                int32_t i_IntValue = i_Value.GetInt();
                if (i_IntValue == 0)
                {
                    return false;
                }
                else if(i_IntValue == 1)
                {
                    return true;
                }
            }
        }
    }
    // else return Default
    return a_isDefault;
}

bool JsonUtils::tryGetBool(Value& a_JsonArr, int a_iIndex, bool a_isDefault)
{
    if (a_JsonArr.IsArray() && a_iIndex >= 0 && a_JsonArr.Size() > a_iIndex)
    {
        Value& i_Value = a_JsonArr[a_iIndex];
        if (i_Value.IsBool())
        {
            return i_Value.GetBool();
        }
        else if (i_Value.IsInt())
        {
            int32_t i_IntValue = i_Value.GetInt();
            if (i_IntValue == 0)
            {
                return false;
            }
            else if(i_IntValue == 1)
            {
                return true;
            }
        }
    }
    // else return Default
    return a_isDefault;
}

QString JsonUtils::toString(Value& aJsonObject)
{
    // Must be check input valid before put to QJsonDocument
    if (aJsonObject.IsObject() && !aJsonObject.Empty())
    {
        Document iDocument;
        iDocument.SetObject();
        for(Value::MemberIterator iIter = aJsonObject.MemberBegin(); iIter != aJsonObject.MemberEnd(); ++iIter)
        {
            iDocument.AddMember(iIter->name, iIter->value, iDocument.GetAllocator());
        }
        StringBuffer iBuffer;
        Writer<StringBuffer> iJsonWiter(iBuffer);
        iDocument.Accept(iJsonWiter);
        const char* iStringStream = iBuffer.GetString();
        int32_t iStringLen = iBuffer.GetSize();
        std::string iStdString(iStringStream, iStringLen);

        return QString::fromStdString(iStdString);
    }
    return "";
}

QString JsonUtils::toString(Document& aJsonDocument)
{
    // Must be check input valid before put to QJsonDocument
    if (!aJsonDocument.HasParseError() && aJsonDocument.IsObject())
    {
        StringBuffer iBuffer;
        Writer<StringBuffer> iJsonWiter(iBuffer);
        aJsonDocument.Accept(iJsonWiter);
        const char* iStringStream = iBuffer.GetString();
        int32_t iStringLen = iBuffer.GetSize();
        std::string iStdString(iStringStream, iStringLen);

        return QString::fromStdString(iStdString);
    }
    return "";
}

Value& JsonUtils::NULL_VALUE()
{
    static Value NULL_VALUE;
    return NULL_VALUE;
}

void JsonUtils::addMember(Document &aJsonDocument, const QString &aKey, const QString &aValue)
{
    Value iKey;
    iKey.SetString(aKey.toStdString().c_str(), aJsonDocument.GetAllocator());
    Value iValue;
    iValue.SetString(aValue.toStdString().c_str(), aJsonDocument.GetAllocator());
    aJsonDocument.AddMember(iKey, iValue, aJsonDocument.GetAllocator());
}

void JsonUtils::addMember(Document &aJsonDocument, const QString &aKey, bool aValue)
{
    Value iKey;
    iKey.SetString(aKey.toStdString().c_str(), aJsonDocument.GetAllocator());
    Value iValue;
    iValue.SetBool(aValue);
    aJsonDocument.AddMember(iKey, iValue, aJsonDocument.GetAllocator());
}

void JsonUtils::addMember(Document &aJsonDocument, const QString &aKey, double aValue)
{
    Value iKey;
    iKey.SetString(aKey.toStdString().c_str(), aJsonDocument.GetAllocator());
    Value iValue;
    iValue.SetDouble(aValue);
    aJsonDocument.AddMember(iKey, iValue, aJsonDocument.GetAllocator());
}

void JsonUtils::addMember(Document &aJsonDocument, const QString &aKey, int32_t aValue)
{
    Value iKey;
    iKey.SetString(aKey.toStdString().c_str(), aJsonDocument.GetAllocator());
    Value iValue;
    iValue.SetInt(aValue);
    aJsonDocument.AddMember(iKey, iValue, aJsonDocument.GetAllocator());
}

void JsonUtils::addMember(Document &aJsonDocument, const QString &aKey, int64_t aValue)
{
    Value iKey;
    iKey.SetString(aKey.toStdString().c_str(), aJsonDocument.GetAllocator());
    Value iValue;
    iValue.SetInt64(aValue);
    aJsonDocument.AddMember(iKey, iValue, aJsonDocument.GetAllocator());
}

void JsonUtils::addMember(Document &aJsonDocument, const QString &aKey, uint32_t aValue)
{
    Value iKey;
    iKey.SetString(aKey.toStdString().c_str(), aJsonDocument.GetAllocator());
    Value iValue;
    iValue.SetUint(aValue);
    aJsonDocument.AddMember(iKey, iValue, aJsonDocument.GetAllocator());
}

void JsonUtils::addMember(Document &aJsonDocument, const QString &aKey, uint64_t aValue)
{
    Value iKey;
    iKey.SetString(aKey.toStdString().c_str(), aJsonDocument.GetAllocator());
    Value iValue;
    iValue.SetUint64(aValue);
    aJsonDocument.AddMember(iKey, iValue, aJsonDocument.GetAllocator());
}

void JsonUtils::addMember(Value &obj, const QString &key, const QString &value, Document::AllocatorType &allocator)
{
    Value keyObj;
    keyObj.SetString(key.toStdString().c_str(), allocator);
    Value valueObj;
    valueObj.SetString(value.toStdString().c_str(), allocator);

    obj.AddMember(keyObj, valueObj, allocator);
}

void JsonUtils::addMember(Value &obj, const QString &key, bool value, Document::AllocatorType &allocator)
{
    Value keyObj;
    keyObj.SetString(key.toStdString().c_str(), allocator);
    Value valueObj;
    valueObj.SetBool(value);

    obj.AddMember(keyObj, valueObj, allocator);
}

void JsonUtils::addMember(Value &obj, const QString &key, Value &value, Document::AllocatorType &allocator)
{
    Value keyObj;
    keyObj.SetString(key.toStdString().c_str(), allocator);

    obj.AddMember(keyObj, value, allocator);
}

QString JsonUtils::BuildJsonString(const QMap<QString, QString> &aMap) {
    Document iDocumentBuilder;
    iDocumentBuilder.SetObject();
    for(QMap<QString, QString>::const_iterator iItem = aMap.begin(); iItem != aMap.end(); iItem++) {
        addMember(iDocumentBuilder, iItem.key(), iItem.value());
    }
    QString iResult = JsonUtils::toString(iDocumentBuilder);
    iDocumentBuilder.Clear();
    return iResult;
}

