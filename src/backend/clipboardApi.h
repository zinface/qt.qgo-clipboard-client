#ifndef __API__H__
#define __API__H__

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "utils/httprequest.h"

#include <httpclient.h>

class ClipApiResponse : public Response {
public:
    ClipApiResponse(Response resp);
    QString create_at();
};

class ClipboardApi : public QObject {
    Q_OBJECT

public:
    ClipApiResponse set(QString mime, QString baseData);
    ClipApiResponse get();
    ClipApiResponse info();

private:
    HttpRequest *httpUtil = new HttpRequest;
};



#endif  //!__API__H__
