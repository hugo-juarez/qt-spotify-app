#ifndef SPOTIFYAUTH_H
#define SPOTIFYAUTH_H

#include <QObject>
#include <QOAuth2AuthorizationCodeFlow>
#include <QOAuthHttpServerReplyHandler>

class SpotifyAuth : public QObject
{
    Q_OBJECT
public:
    explicit SpotifyAuth(QObject *parent = nullptr);

    void startAuth();
    void resumeFromToken(const QString &storedToken);

signals:
    void refreshTokenRotated(QString t);

private:
    QOAuth2AuthorizationCodeFlow m_oauth;
    QOAuthHttpServerReplyHandler *m_handler;
};

#endif // SPOTIFYAUTH_H
