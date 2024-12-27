#include "clipboardApi.h"
#include "global/global.h"

void ClipboardApi::set(QString mime, QString baseData)
{
//    QNetworkRequest request;
//    request.setUrl(QUrl(GL.getAddress() + "/clipboard"));
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

//    QJsonObject object;
//    object["mime"] = mime;
//    object["data"] = baseData;

//    QJsonDocument document(object);
//    QByteArray jsonData = document.toJson(QJsonDocument::JsonFormat::Compact);

//    // QTextStream(stdout) << "Set: " << QString(document.toJson(QJsonDocument::Compact)) << "\n";
    
//    httpUtil->postRequest(request, jsonData);

    Request request(GL.getAddress() +  "/clipboard");

    QVariantMap object;
    object["mime"] = mime;
    object["data"] = baseData;
    request.setData(object);

    HttpClient::instance().post(request);
}

Response ClipboardApi::get()
{
//    QNetworkRequest request;
//    request.setUrl(QUrl(GL.getAddress() + "/clipboard"));

//    QByteArray data = httpUtil->getRequestSync(request);

//    QJsonDocument document = QJsonDocument::fromJson(data);
    
//    // QTextStream(stdout) << "Get: " << QString(document.toJson(QJsonDocument::Compact)) << "\n";

//    return document.object();

    Request request(GL.getAddress() + "/clipboard");
    return HttpClient::instance().get(request);
}

Response ClipboardApi::info()
{
//    QNetworkRequest request;
//    request.setUrl(QUrl(GL.getAddress() + "/clipboard/info"));

//    QJsonDocument document = QJsonDocument::fromJson(httpUtil->getRequestSync(request));

//    // QTextStream(stdout) << "Info: " << QString(document.toJson(QJsonDocument::Compact)) << "\n";

//    return document.object();

    Request request(GL.getAddress() + "/clipboard/info");
    return HttpClient::instance().get(request);
}
