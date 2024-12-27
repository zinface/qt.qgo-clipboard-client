#include "global.h"
#include "config.h"
#include <utils/configutil.h>
#include <utils/pathutil.h>

#define KEY_SERVER_ADDRESS "Server/Address"

Global::Global()
{
    QString clipConfig = PathUtil::clipboardServerConfig();

    address = ConfigUtil::instance().readConfigValue(clipConfig, KEY_SERVER_ADDRESS);

    if (address.isEmpty()) {
        address = REMOTE_HOST;
    }
}

Global &Global::instance()
{
    static Global global;
    return global;
}

QString Global::getAddress() const
{
    return address;
}

void Global::setAddress(const QString &newAddress)
{
    address = newAddress;

    QString clipConfig = PathUtil::clipboardServerConfig();
    ConfigUtil::instance().writeConfigValue(clipConfig, KEY_SERVER_ADDRESS, address);
}
