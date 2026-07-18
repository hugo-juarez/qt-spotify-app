#include "backend.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

Backend::Backend(QObject *parent)
    : QObject{parent}
{
    qDebug("Initialized Backend");
    QUrl url{"ws://localhost:3678/events"};
    connect(&m_webSocket, &QWebSocket::connected, this, &Backend::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &Backend::closed);
    qDebug("Created Librespot websocket");
    m_webSocket.open(url);
}

void Backend::disconnect()
{
    m_webSocket.close();
    qDebug("Disconnected websocket");
}

void Backend::onConnected()
{
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &Backend::onReceived);
    qDebug("Connected websocket");
}

void Backend::onReceived(QString message)
{
    qDebug() << "Message Received" << message;
    QJsonObject jsonObj = QJsonDocument::fromJson(message.toUtf8()).object();

    // Check if the mesage is a metadata to change cover album image
    if(jsonObj.contains("type") && jsonObj["type"] == "metadata") {
        QUrl url(jsonObj["data"].toObject()["album_cover_url"].toString());
        setAlbumCover(url);
    }

}

QUrl Backend::albumCover() const
{
    return m_albumCover;
}

void Backend::setAlbumCover(const QUrl &newAlbumCover)
{
    if (m_albumCover == newAlbumCover)
        return;
    m_albumCover = newAlbumCover;
    emit albumCoverChanged();
}
