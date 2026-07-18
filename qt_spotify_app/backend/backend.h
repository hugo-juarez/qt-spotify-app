#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QtWebSockets/QWebSocket>

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl albumCover READ albumCover WRITE setAlbumCover NOTIFY albumCoverChanged FINAL)
public:
    explicit Backend(QObject *parent = nullptr);

    void disconnect();

    QUrl albumCover() const;
    void setAlbumCover(const QUrl &newAlbumCover);

signals:
    void closed();

    void albumCoverChanged();

private slots:
    void onConnected();
    void onReceived(QString message);

private:
    QWebSocket m_webSocket;
    QUrl m_albumCover;
};

#endif // BACKEND_H