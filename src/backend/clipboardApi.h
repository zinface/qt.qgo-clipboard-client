#ifndef __API__H__
#define __API__H__

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "utils/httprequest.h"

#include <httpclient.h>

class ClipboardApi : public QObject {
    Q_OBJECT

public:
    void set(QString mime, QString baseData);
    Response get();
    Response info();

private:
    HttpRequest *httpUtil = new HttpRequest;
};



#endif  //!__API__H__
