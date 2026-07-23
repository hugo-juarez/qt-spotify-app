#include "spotifyauth.h"

SpotifyAuth::SpotifyAuth(QObject *parent)
    : QObject{parent} ,
    m_handler{nullptr}
{
    m_oauth.setAuthorizationUrl(QUrl("https://accounts.spotify.com/authorize"));
    m_oauth.setTokenUrl(QUrl("https://accounts.spotify.com/api/token"));
    m_oauth.setClientIdentifier(qgetenv("SPOTIFY_CLIENT_ID"));
    m_oauth.setRequestedScopeTokens({"playlist-read-private", "user-library-read"});

    m_oauth.setPkceMethod(QOAuth2AuthorizationCodeFlow::PkceMethod::S256);
    m_oauth.setAutoRefresh(true);
    m_oauth.setRefreshLeadTime(std::chrono::seconds{120});

    m_handler = new QOAuthHttpServerReplyHandler(QHostAddress::LocalHost, 8888, this);
    m_handler->setCallbackPath(QStringLiteral("/callback"));
    m_handler->close();
    m_oauth.setReplyHandler(m_handler);

    connect(&m_oauth, &QAbstractOAuth::authorizeWithBrowser,[](const QUrl &url) { qDebug() << "authorize URL:" << url.toString(); });

    connect(&m_oauth, &QAbstractOAuth2::refreshTokenChanged, this, [this](const QString &token){
        if (!token.isEmpty()) {
            qDebug() << "New Token: " << token;
            emit refreshTokenRotated(token);
        }
    });

    connect(&m_oauth, &QAbstractOAuth2::serverReportedErrorOccurred, this,
            [](const QString &e, const QString &desc, const QUrl &) {
                qWarning() << "Spotify auth error:" << e << desc;
            });

    connect(&m_oauth, &QAbstractOAuth::requestFailed, this, [this] {
        if (m_oauth.status() != QAbstractOAuth::Status::Granted)
            qWarning() << "Reauthorization Required";
    });
}

void SpotifyAuth::startAuth()
{
    if (!m_handler->listen(QHostAddress::LocalHost, 8888)) {
        qWarning() << "Could not bind callback port";
        return;
    }
    qDebug() << "redirect_uri:" << m_handler->callback();
    m_oauth.grant();
}

void SpotifyAuth::resumeFromToken(const QString &storedToken)
{
    m_oauth.setRefreshToken(storedToken);
    m_oauth.refreshToken();
}
