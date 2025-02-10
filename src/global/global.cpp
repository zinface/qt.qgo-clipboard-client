#include "global.h"
#include "config.h"
#include <utils/configutil.h>
#include <utils/pathutil.h>

#define KEY_SERVER_ADDRESS "Server/Address"
#define KEY_CLIENT_NOTIFY_SEND "Client/NOTIFY_SEND"
#define KEY_CLIENT_NOTIFY_RECV "Client/NOTIFY_RECV"

Global::Global()
    : m_address("http://127.0.0.1:9090")
    , m_notifySend(true)
    , m_notifyRecv(true)
{
    QString clipConfig = PathUtil::clipboardServerConfig();

    { // initialize address
        m_address = ConfigUtil::instance().readConfigValue(clipConfig, KEY_SERVER_ADDRESS);
        if (m_address.isEmpty()) {
            m_address = REMOTE_HOST;
        }
    }

    { // initialize notify send/recv flag
        auto notify_send = ConfigUtil::instance().readConfigValue(clipConfig, KEY_CLIENT_NOTIFY_SEND);
        auto notify_recv = ConfigUtil::instance().readConfigValue(clipConfig, KEY_CLIENT_NOTIFY_RECV);

        setNotifySend(notify_send == "yes");
        setNotifyRecv(notify_recv == "yes");
    }
}

Global &Global::instance()
{
    static Global global;
    return global;
}

QString Global::getAddress() const
{
    return m_address;
}

void Global::setAddress(const QString &newAddress)
{
    m_address = newAddress;

    QString clipConfig = PathUtil::clipboardServerConfig();
    ConfigUtil::instance().writeConfigValue(clipConfig, KEY_SERVER_ADDRESS, m_address);
}

bool Global::notifySend() const
{
    return m_notifySend;
}

void Global::setNotifySend(bool newNotifySend)
{
    m_notifySend = newNotifySend;

    QString clipConfig = PathUtil::clipboardServerConfig();
    ConfigUtil::instance().writeConfigValue(clipConfig, KEY_CLIENT_NOTIFY_SEND, m_notifySend?"yes":"no");
}

bool Global::notifyRecv() const
{
    return m_notifyRecv;
}

void Global::setNotifyRecv(bool newNotifyRecv)
{
    m_notifyRecv = newNotifyRecv;

    QString clipConfig = PathUtil::clipboardServerConfig();
    ConfigUtil::instance().writeConfigValue(clipConfig, KEY_CLIENT_NOTIFY_RECV, m_notifyRecv?"yes":"no");
}
