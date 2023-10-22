#ifndef PATHUTIL_H
#define PATHUTIL_H

#include <QString>

class PathUtil
{
private:
    PathUtil();

public:
    static QString homeDir();
    static QString tmpDir();
    static QString appDataDir();

    static QString clipboardServerConfig();

    static bool mkDir(const QString &dirPath);
};

#endif // PATHUTIL_H
