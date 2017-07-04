#ifndef LAZADA_DATA_ITEM_GET_DOCUMENT_H
#define LAZADA_DATA_ITEM_GET_DOCUMENT_H

#include "../../core/dataitem/abstract_data_item.h"

namespace Core { namespace DataItem {

    class LazadaDataItemGetDocument : public AbstractDataItem
    {
    public:
        LazadaDataItemGetDocument();

        virtual void parseItemData(Value& aJsonObject);
        virtual AbstractDataItem *clone() const;

        QString getData() const;
        QString getDocumentType() const;
        QString getMimeType() const;
        QString getPathFile() const;

    private:
        void saveFile();

    private:
        QString DocumentType;
        QString MimeType;
        QString data;
        QString pathFile;
    };

}}

#endif // LAZADA_DATA_ITEM_GET_DOCUMENT_H
