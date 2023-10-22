#include "pathutil.h"

#include <QDir>
#include <QStandardPaths>

PathUtil::PathUtil()
{

}

QString PathUtil::homeDir()
{
    return QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first();
}

QString PathUtil::tmpDir()
{
    return QStandardPaths::standardLocations(QStandardPaths::TempLocation).first();
}

QString PathUtil::appDataDir()
{
    QString path = homeDir() + "/.config/qgo-clipboard/";
    mkDir(path);
    return path;
}

QString PathUtil::clipboardServerConfig()
{
    QString path = appDataDir() + "server.ini";
    return path;
}

bool PathUtil::mkDir(const QString &dirPath)
{
    QDir dir(dirPath);
    if (!dir.exists())
    {
        dir.mkpath(dirPath);
    }
    return true;
}
