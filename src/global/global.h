#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>

class Global
{
private:
    Global();

public:
    static Global &instance();

    QString getAddress() const;
    void setAddress(const QString &newAddress);

    bool notifySend() const;
    void setNotifySend(bool newNotifySend);
    bool notifyRecv() const;
    void setNotifyRecv(bool newNotifyRecv);

private:
    QString m_address;
    bool m_notifySend;
    bool m_notifyRecv;
};

#define GL Global::instance()

#endif // GLOBAL_H
