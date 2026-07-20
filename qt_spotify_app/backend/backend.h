#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QtWebSockets/QWebSocket>
#include "playertracker.h"

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl albumCover READ albumCover WRITE setAlbumCover NOTIFY albumCoverChanged FINAL)
    Q_PROPERTY(QString songName READ songName WRITE setSongName NOTIFY songNameChanged FINAL)
    Q_PROPERTY(QString artists READ artists WRITE setArtists NOTIFY artistsChanged FINAL)
    Q_PROPERTY(PlayerTracker *player READ player CONSTANT)

public:
    explicit Backend(QObject *parent = nullptr);

    void disconnect();

    QUrl albumCover() const;
    void setAlbumCover(const QUrl &newAlbumCover);

    QString songName() const;
    void setSongName(const QString &newSongName);

    QString artists() const;
    void setArtists(const QString &newArtists);

    PlayerTracker *player() const {return m_playerTracker;};

signals:
    void closed();

    void albumCoverChanged();

    void songNameChanged();

    void artistsChanged();

private slots:
    void onConnected();
    void onReceived(QString message);

private:
    PlayerTracker *m_playerTracker;
    QWebSocket m_webSocket;
    QUrl m_albumCover;
    QString m_songName;
    QString m_artists;
};

#endif // BACKEND_H