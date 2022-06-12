#include "httprequest.h"

void HttpRequest::getRequest(const QNetworkRequest &request)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    manager->get(request);
    connect(manager, &QNetworkAccessManager::finished, 
        this, &HttpRequest::readyRead);
    connect(manager, &QNetworkAccessManager::finished, 
        manager, &QNetworkAccessManager::deleteLater);
}

QByteArray HttpRequest::getRequestSync(const QNetworkRequest &request)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(request);

    QEventLoop loop(this);
    connect(reply, static_cast<void(QNetworkReply::*)()>(&QNetworkReply::finished), 
        &loop, &QEventLoop::quit);
    loop.exec();

    reply->deleteLater();
    manager->deleteLater();
    return reply->readAll();
}

void HttpRequest::postRequest(const QNetworkRequest &request, QByteArray data)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    manager->post(request, data);
    connect(manager, &QNetworkAccessManager::finished, 
        this, &HttpRequest::readyRead);
    connect(manager, &QNetworkAccessManager::finished, 
        manager, &QNetworkAccessManager::deleteLater);
}

// public slots:
void HttpRequest::readyRead(QNetworkReply *reply)
{
    emit finished(reply->readAll());
}