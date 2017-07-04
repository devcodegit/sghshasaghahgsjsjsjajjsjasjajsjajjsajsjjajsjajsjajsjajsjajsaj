#include "lazada_data_item_get_document.h"
#include "../../core/jsonutil/json_utils.h"
#include "../../core/jsonutil/json_exception.h"
#include <QFile>
#include <QDateTime>
#include <QDebug>

using namespace Core::Json;
using namespace Core::DataItem;

LazadaDataItemGetDocument::LazadaDataItemGetDocument()
{

}

void LazadaDataItemGetDocument::parseItemData(Value &aJsonObject)
{
    if (!aJsonObject.IsNull())
    {
        try
        {
            Value &aJsonData = JsonUtils::getJsonObject(aJsonObject, "Document");
            if (!aJsonData.IsNull())
            {
                DocumentType = JsonUtils::tryGetString(aJsonData, "DocumentType", "");
                MimeType = JsonUtils::tryGetString(aJsonData, "MimeType", "");
                data = JsonUtils::tryGetString(aJsonData, "File", "");
                qDebug() << "LazadaDataItemGetDocument::parseItemData !!!!!!" << data.isEmpty();
                saveFile();
            }
        }
        catch (JsonException ex)
        {
            qDebug() << "LazadaDataItemGetDocument::parseItemData ERORR: " << ex.what();
        }
    }
}

AbstractDataItem *LazadaDataItemGetDocument::clone() const
{
    return new LazadaDataItemGetDocument(*this);
}

QString LazadaDataItemGetDocument::getData() const
{
    return data;
}

QString LazadaDataItemGetDocument::getDocumentType() const
{
    return DocumentType;
}

QString LazadaDataItemGetDocument::getMimeType() const
{
    return MimeType;
}

QString LazadaDataItemGetDocument::getPathFile() const
{
    return pathFile;
}

void LazadaDataItemGetDocument::saveFile()
{
    if (data.isEmpty()) return;
    QByteArray ba;
    ba.append(data);
    QByteArray newdata = QByteArray::fromBase64(ba);

    pathFile = "C:\\Users\\DatVT\\Desktop\\ " + DocumentType + "_" + QString::number(QDateTime::currentMSecsSinceEpoch()) + ".html";
    QFile file(pathFile);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(newdata);
        file.close();
        qDebug() << "Save file Success: " << pathFile;
    }
    else
    {
        qDebug() << "Save file FAIL!";
    }
}
