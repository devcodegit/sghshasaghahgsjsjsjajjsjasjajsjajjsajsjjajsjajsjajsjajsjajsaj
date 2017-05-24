#ifndef GZIP_UTILS_H
#define GZIP_UTILS_H

#include <QByteArray>

namespace Core { namespace Utility {

    class GZipUtils
    {
    public:
        static bool gzipCompress(QByteArray input, QByteArray &output, int level = -1);
        static bool gzipDecompress(QByteArray input, QByteArray &output);
    };

}}

#endif // GZIP_UTILS_H
