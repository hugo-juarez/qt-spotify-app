#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "backend.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Backend backend;
    QQmlApplicationEngine engine;

    qmlRegisterSingletonInstance("qt_spotify_app", 1, 0, "Backend", &backend);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("qt_spotify_app", "Main");

    return QGuiApplication::exec();
}
