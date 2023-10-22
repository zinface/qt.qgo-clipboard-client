#include "clipboardApi.h"

void ClipboardApi::set(QString mime, QString baseData)
{
    QNetworkRequest request;
    request.setUrl(QUrl(REMOTE_HOST "/clipboard"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject object;
    object["mime"] = mime;
    object["data"] = baseData;

    QJsonDocument document(object);
    QByteArray jsonData = document.toJson(QJsonDocument::JsonFormat::Compact);

    // QTextStream(stdout) << "Set: " << QString(document.toJson(QJsonDocument::Compact)) << "\n";
    
    httpUtil->postRequest(request, jsonData);
}

QJsonObject ClipboardApi::get()
{
    QNetworkRequest request;
    request.setUrl(QUrl(REMOTE_HOST "/clipboard"));

    QByteArray data = httpUtil->getRequestSync(request);

    QJsonDocument document = QJsonDocument::fromJson(data);
    
    // QTextStream(stdout) << "Get: " << QString(document.toJson(QJsonDocument::Compact)) << "\n";

    return document.object();
}

QJsonObject ClipboardApi::info()
{
    QNetworkRequest request;
    request.setUrl(QUrl(REMOTE_HOST "/clipboard/info"));

    QJsonDocument document = QJsonDocument::fromJson(httpUtil->getRequestSync(request));

    // QTextStream(stdout) << "Info: " << QString(document.toJson(QJsonDocument::Compact)) << "\n";

    return document.object();
}