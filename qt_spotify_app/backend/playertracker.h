#ifndef PLAYERTRACKER_H
#define PLAYERTRACKER_H

#include <QObject>
#include <QQmlEngine>
#include <QTimer>
#include <QtQml/qqmlregistration.h>

class PlayerTracker : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("PlayerTracker is provided by Backed")

    Q_PROPERTY(int position READ position NOTIFY positionChanged FINAL)
    Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged FINAL)
    Q_PROPERTY(bool playing READ playing WRITE setPlaying NOTIFY playingChanged FINAL)
    Q_PROPERTY(qreal progress READ progress NOTIFY positionChanged FINAL)

public:
    explicit PlayerTracker(QObject *parent = nullptr);

    int position() const;
    int duration() const;
    bool playing() const;
    qreal progress() const;

    void setDuration(int newDuration);
    void setPlaying(bool newPlaying);

signals:
    void positionChanged();
    void durationChanged();
    void playingChanged();

public slots:
    void songChanged(int duration);
    void onPlayPause(bool isPlaying);
    void onSeek(int position);

private slots:
    void tick();

private:
    QTimer m_timer;
    int m_position;
    int m_duration;
    bool m_playing;
    qreal m_progress;
    static int kInterval;
};

#endif // PLAYERTRACKER_H
