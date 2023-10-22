#ifndef CONFIGUTIL_H
#define CONFIGUTIL_H

#include <QString>

class ConfigUtil
{
//private:
//    ConfigUtil();

public:
    static ConfigUtil &instance();

    QString readConfigValue(const QString &iniPath, const QString &key);
    bool writeConfigValue(const QString &iniPath, const QString &key, const QString &value);
};

#endif // CONFIGUTIL_H
