#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QtWebSockets/QWebSocket>

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);

    void disconnect();

signals:
    void closed();

private slots:
    void onConnected();
    void onReceived(QString message);

private:
    QWebSocket m_webSocket;
};

#endif // BACKEND_H