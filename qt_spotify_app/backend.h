#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QQmlEngine>

class backend : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit backend(QObject *parent = nullptr);

signals:
};

#endif // BACKEND_H
