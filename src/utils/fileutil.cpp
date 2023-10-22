#include "fileutil.h"
#include <QDir>

bool FileUtil::createDirectory(const QString &dirPath)
{
    QDir dir(dirPath);
    if (!dir.exists())
    {
        return dir.mkpath(dirPath);
    }
    return true;
}
