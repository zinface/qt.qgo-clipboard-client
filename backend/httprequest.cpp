#include "httprequest.h"

void HttpRequest::getRequest(const QNetworkRequest &request)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    manager->get(request);
    connect(manager, &QNetworkAccessManager::finished, 
        this, &HttpRequest::readyRead);
}

QByteArray HttpRequest::getRequestSync(const QNetworkRequest &request)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(request);

    QEventLoop loop(this);
    connect(reply, static_cast<void(QNetworkReply::*)()>(&QNetworkReply::finished), 
        &loop, &QEventLoop::quit);
    loop.exec();

    // QTextCodec *codec = QTextCodec::codecForName("utf8");
    // QString repStr = codec->toUnicode(reply->readAll())

    reply->deleteLater();
    return reply->readAll();
}

void HttpRequest::postRequest(const QNetworkRequest &request, QByteArray data)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    manager->post(request, data);
    connect(manager, &QNetworkAccessManager::finished, 
        this, &HttpRequest::readyRead);
}

// public slots:
void HttpRequest::readyRead(QNetworkReply *reply)
{
    emit finished(reply->readAll());
}