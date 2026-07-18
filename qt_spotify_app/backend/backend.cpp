#include "backend.h"
#include <QDebug>

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
}