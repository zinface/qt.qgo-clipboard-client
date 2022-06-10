#ifndef __API__H__
#define __API__H__

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "httprequest.h"
#include "config.h"

class ClipboardApi : public QObject {
    Q_OBJECT

public:
    void set(QString mime, QString baseData);
    QJsonObject get();
    QJsonObject check();
};



#endif  //!__API__H__