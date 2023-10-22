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

private:
    QString address;
};

#define GL Global::instance()

#endif // GLOBAL_H
