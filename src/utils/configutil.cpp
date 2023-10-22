#include "configutil.h"

#include <QSettings>

//ConfigUtil::ConfigUtil()
//{

//}

ConfigUtil &ConfigUtil::instance()
{
    static ConfigUtil configutil;
    return configutil;
}

QString ConfigUtil::readConfigValue(const QString &iniPath, const QString &key)
{
    QSettings configSetting(iniPath, QSettings::IniFormat);

    if (key.split("/").count() != 2) {
        return "";
    }

    return configSetting.value(key).toString();
}

bool ConfigUtil::writeConfigValue(const QString &iniPath, const QString &key, const QString &value)
{
    QSettings configSetting(iniPath, QSettings::IniFormat);

    if (key.split("/").count() != 2) {
        return false;
    }

    configSetting.setValue(key, value);
    return true;
}
