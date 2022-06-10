#include "clipboardApi.h"

void ClipboardApi::set(QString mime, QString baseData)
{
    QNetworkRequest request;
    request.setUrl(QUrl(REMOTE_HOST "/set"));

    QString data(QString("mime=%1&data=%2").arg(mime).arg(baseData.replace("+", "%2B")));

    HttpRequest *httpRequest = new HttpRequest;
    httpRequest->postRequest(request, data.toLocal8Bit());
}

QJsonObject ClipboardApi::get()
{
    QNetworkRequest request;
    request.setUrl(QUrl(REMOTE_HOST "/get"));

    HttpRequest *httpRequest = new HttpRequest;
    // connect(httpRequest, &HttpRequest::finished, [=](QString data){

    // });
    QJsonDocument document = QJsonDocument::fromJson(httpRequest->getRequestSync(request));

    return document.object();
}

QJsonObject ClipboardApi::check()
{
    QNetworkRequest request;
    request.setUrl(QUrl(REMOTE_HOST "/check"));

    HttpRequest *httpRequest = new HttpRequest;
    QJsonDocument document = QJsonDocument::fromJson(httpRequest->getRequestSync(request));
    return document.object();
}