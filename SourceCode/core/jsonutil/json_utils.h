#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include <QString>
#include <QMap>

#include "rapidjson/document.h"

using namespace rapidjson;

namespace Core { namespace Json {

    class JsonUtils
    {
    public:
        static Document& parseJson(Document& aJsonDocument, const QString& aJsonData);
        static Document& tryParseJson(Document& aJsonDocument, const QString& aJsonData);
        /**
         * @return throw JsonException if invalid
         */
        static Value& getJsonObject(Document& a_JsonDocument);
        /**
         * @return throw JsonException if invalid
         */
        static Value& getJsonObject(Value& a_JsonObj, const QString& a_sName);
        /**
         * @return throw JsonException if invalid
         */
        static Value& getJsonObject(Value& a_JsonArr, int a_iIndex);
        /**
         * @return Empty QJsonObject if invalid. Handler should be check .isEmpty() before any action
         */
        static Value& tryGetJsonObject(Document& a_JsonDocument);
        /**
         * @return Empty QJsonObject if invalid. Handler should be check .isEmpty() before any action
         */
        static Value& tryGetJsonObject(Value& a_JsonObj, const QString& a_sName);
        /**
         * @return Empty QJsonObject if invalid. Handler should be check .isEmpty() before any action
         */
        static Value& tryGetJsonObject(Value& a_JsonArr, int a_iIndex);


        /**
         * @return throw JsonException if invalid
         */
        static Value& getJsonArray(Document& a_JsonDoc);
        /**
         * @return throw JsonException if invalid
         */
        static Value& getJsonArray(Value& a_JsonObj, const QString& a_sName);
        /**
         * @return throw JsonException if invalid
         */
        static Value& getJsonArray(Value& a_JsonArr, int a_iIndex);
        /**
         * @return Empty QJsonArray if invalid. Handler should be check .isEmpty() before any action
         */
        static Value& tryGetJsonArray(Document& a_JsonDoc);
        /**
         * @return Empty QJsonArray if invalid. Handler should be check .isEmpty() before any action
         */
        static Value& tryGetJsonArray(Value& a_JsonObj, const QString& a_sName);
        /**
         * @return Empty QJsonArray if invalid. Handler should be check .isEmpty() before any action
         */
        static Value& tryGetJsonArray(Value& a_JsonArr, int a_iIndex);

        static int32_t getInt(Value& a_JsonObj, const QString& a_sName);
        static int32_t getInt(Value& a_JsonArr, int a_iIndex);
        static int32_t getIntFromStr(Value& a_JsonObj, const QString& a_sName);
        static int32_t getIntFromStr(Value& a_JsonArr, int a_iIndex);
        static int32_t tryGetInt(Value& a_JsonObj, const QString& a_sName, int32_t a_iDefault);
        static int32_t tryGetInt(Value& a_JsonArr, int a_iIndex, int32_t a_iDefault);
        static int32_t tryGetIntOrStr(Value& a_JsonObj, const QString& a_sName, int32_t a_iDefault);
        static int32_t tryGetIntFromStr(Value& a_JsonObj, const QString& a_sName, int32_t a_iDefault);
        static int32_t tryGetIntFromStr(Value& a_JsonArr, int a_iIndex, int32_t a_iDefault);

        static int64_t getLong(Value& a_JsonObj, const QString& a_sName);
        static int64_t getLong(Value& a_JsonArr, int a_iIndex);
        static int64_t getLongFromStr(Value& a_JsonObj, const QString& a_sName);
        static int64_t getLongFromStr(Value& a_JsonArr, int a_iIndex);
        static int64_t tryGetLong(Value& a_JsonObj, const QString& a_sName, int64_t a_lDefault);
        static int64_t tryGetLong(Value& a_JsonArr, int a_iIndex, int64_t a_lDefault);
        static int64_t tryGetLongFromStr(Value& a_JsonObj, const QString& a_sName, int64_t a_lDefault);
        static int64_t tryGetLongFromStr(Value& a_JsonArr, int a_iIndex, int64_t a_lDefault);

        static double getDouble(Value& a_JsonObj, const QString& a_sName);
        static double getDouble(Value& a_JsonArr, int a_iIndex);
        static double getDoubleFromStr(Value& a_JsonObj, const QString& a_sName);
        static double getDoubleFromStr(Value& a_JsonArr, int a_iIndex);
        static double tryGetDouble(Value& a_JsonObj, const QString& a_sName, double a_dDefault);
        static double tryGetDouble(Value& a_JsonArr, int a_iIndex, double a_dDefault);
        static double tryGetDoubleOrStr(Value& a_JsonObj, const QString& a_sName, double a_dDefault);
        static double tryGetDoubleFromStr(Value& a_JsonObj, const QString& a_sName, double a_dDefault);
        static double tryGetDoubleFromStr(Value& a_JsonArr, int a_iIndex, double a_dDefault);

        static QString getString(Value& a_JsonObj, const QString& a_sName);
        static QString getString(Value& a_JsonArr, int a_iIndex);
        static QString tryGetString(Value& a_JsonObj, const QString& a_sName, const QString& a_sDefault);
        static QString tryGetString(Value& a_JsonArr, int a_iIndex, const QString& a_sDefault);

        static bool getBool(Value& a_JsonObj, const QString& a_sName);
        static bool getBool(Value& a_JsonArr, int a_iIndex);
        static bool tryGetBool(Value& a_JsonObj, const QString& a_sName, bool a_isDefault);
        static bool tryGetBool(Value& a_JsonArr, int a_iIndex, bool a_isDefault);

        static QString toString(Value& aJsonObject);
        static QString toString(Document& aJsonDocument);

        static void addMember(Document& aJsonDocument, const QString& aKey, const QString& aValue);
        static void addMember(Document& aJsonDocument, const QString& aKey, bool aValue);
        static void addMember(Document& aJsonDocument, const QString& aKey, double aValue);
        static void addMember(Document& aJsonDocument, const QString& aKey, int32_t aValue);
        static void addMember(Document& aJsonDocument, const QString& aKey, int64_t aValue);
        static void addMember(Document& aJsonDocument, const QString& aKey, uint32_t aValue);
        static void addMember(Document& aJsonDocument, const QString& aKey, uint64_t aValue);

        static void addMember(Value &obj, const QString &key, const QString &value, Document::AllocatorType &allocator);
        static void addMember(Value &obj, const QString &key, bool value, Document::AllocatorType &allocator);
        static void addMember(Value &obj, const QString &key, Value &value, Document::AllocatorType &allocator);

        static QString BuildJsonString(const QMap<QString,QString> &aMap);
private:
        static Value& NULL_VALUE();
    };

} // End Json
} // End Core

#endif // JSON_UTILS_H
