#include "clipboardApi.h"
#include "global/global.h"

ClipApiResponse::ClipApiResponse(Response resp) : Response(resp) {

}

QString ClipApiResponse::create_at()
{
    return toMap().value("create_at").toString();
}

ClipApiResponse ClipboardApi::set(QString mime, QString baseData)
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

    return HttpClient::instance().post(request);
}

ClipApiResponse ClipboardApi::get()
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

ClipApiResponse ClipboardApi::info()
{
//    QNetworkRequest request;
//    request.setUrl(QUrl(GL.getAddress() + "/clipboard/info"));

//    QJsonDocument document = QJsonDocument::fromJson(httpUtil->getRequestSync(request));

//    // QTextStream(stdout) << "Info: " << QString(document.toJson(QJsonDocument::Compact)) << "\n";

//    return document.object();

    Request request(GL.getAddress() + "/clipboard/info");
    return HttpClient::instance().get(request);
}
