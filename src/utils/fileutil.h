#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QString>

class FileUtil
{
public:
    static bool createDirectory(const QString &dirPath);
};

#endif // FILEUTIL_H
