#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequestFactory>
#include <QRestAccessManager>

class ApiClient : public QObject
{
    Q_OBJECT
public:
    explicit ApiClient(QUrl url, QObject *parent = nullptr);

private:

    void get(const QString &path, std::function<void(QJsonObject)> callback);
    void post(const QString &path, QJsonDocument doc);

    QNetworkAccessManager m_netManager;
    QNetworkRequestFactory m_factory;
    QRestAccessManager m_restManager;
};

#endif // APICLIENT_H
