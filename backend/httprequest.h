#ifndef __HTTPREQUEST__H__
#define __HTTPREQUEST__H__

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QHttpMultiPart>
#include <QByteArray>
#include <QTextCodec>

class HttpRequest :public QObject {
    Q_OBJECT

public:
    void getRequest(const QNetworkRequest &request);
    QByteArray getRequestSync(const QNetworkRequest &request);
    void postRequest(const QNetworkRequest &request, QByteArray data);

signals:
    void finished(QString);

public slots:
    void readyRead(QNetworkReply *reply);
};





#endif  //!__HTTPREQUEST__H__




