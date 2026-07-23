#include "apiclient.h"
#include <QRestReply>
#include <QJsonDocument>
#include <QJsonObject>

ApiClient::ApiClient(QUrl url, QObject *parent)
    : QObject{parent},
    m_netManager(this),
    m_restManager(&m_netManager, this)
{
    m_factory.setBaseUrl(url);

    QHttpHeaders headers;
    headers.append(
        QHttpHeaders::WellKnownHeader::ContentType, "application/json"
    );

    m_factory.setCommonHeaders(headers);
}

void ApiClient::get(const QString &path, std::function<void(QJsonObject)> callback) {
    // Function to make an asynchorouns GET request
    m_restManager.get(m_factory.createRequest(path), this, [callback = std::move(callback)] (QRestReply &reply){
        const int status = reply.httpStatus();
        if (!reply.isSuccess()) {
            qWarning() << "API Error" << status << reply.errorString();
            return;
        }

        std::optional doc = reply.readJson();
        if (!doc || !doc->isObject()) {
            qWarning() << "Bad JSON";
            return;
        }

        QJsonObject obj = doc->object();
        qDebug() << "Status: " << status << "\nData: " <<  obj;
        callback(obj);
    });
}

void ApiClient::post(const QString &path, QJsonDocument doc) {
    m_restManager.post(m_factory.createRequest(path), doc, this, [](QRestReply &reply){
        const int status = reply.httpStatus();
        if (!reply.isSuccess()) {
            qWarning() << "API Error" << status << reply.errorString();
            return;
        }

        std::optional doc = reply.readJson();
        if (!doc || !doc->isObject()) {
            qWarning() << "Bad JSON";
            return;
        }

        qDebug() << doc->object();
    });
}