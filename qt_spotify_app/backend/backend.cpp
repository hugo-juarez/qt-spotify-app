#include "backend.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Backend::Backend(QObject *parent)
    : QObject{parent},
    m_playerTracker{new PlayerTracker(this)},
    m_songName{"Loading..."}
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

    if(!jsonObj.contains("type"))
        return;

    // Check if the mesage is a metadata to change cover album image
    if( jsonObj["type"] == "metadata") {
        QJsonObject data = jsonObj["data"].toObject();
        setAlbumCover(QUrl(data["album_cover_url"].toString()));
        setSongName(data["name"].toString());

        QJsonArray jsonArray = data["artist_names"].toArray();
        QStringList artist_list;
        for(const QJsonValue &value : std::as_const(jsonArray))
        {
            artist_list.append(value.toString());
        }

        setArtists(artist_list.join(", "));

        m_playerTracker->songChanged(data["duration"].toInt());
    }

    if( jsonObj["type"] == "playing" )
        m_playerTracker->setPlaying(true);


    if ( jsonObj["type"] == "paused" )
        m_playerTracker->setPlaying(false);
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

QString Backend::songName() const
{
    return m_songName;
}

void Backend::setSongName(const QString &newSongName)
{
    if (m_songName == newSongName)
        return;
    m_songName = newSongName;
    emit songNameChanged();
}

QString Backend::artists() const
{
    return m_artists;
}

void Backend::setArtists(const QString &newArtists)
{
    if (m_artists == newArtists)
        return;
    m_artists = newArtists;
    emit artistsChanged();
}