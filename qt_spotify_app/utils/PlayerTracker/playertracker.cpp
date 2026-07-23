#include "playertracker.h"

/*static*/ int PlayerTracker::kInterval = 100;

PlayerTracker::PlayerTracker(QObject *parent)
    : QObject{parent}
{
    m_timer.setInterval(100); //100ms interval
    connect(&m_timer, &QTimer::timeout, this, &PlayerTracker::tick);
}

int PlayerTracker::position() const
{
    return m_position;
}

int PlayerTracker::duration() const
{
    return m_duration;
}

void PlayerTracker::setDuration(int newDuration)
{
    if (m_duration == newDuration)
        return;
    m_duration = newDuration;
    emit durationChanged();
}

bool PlayerTracker::playing() const
{
    return m_playing;
}

void PlayerTracker::setPlaying(bool newPlaying)
{
    if (m_playing == newPlaying)
        return;
    m_playing = newPlaying;

    if(m_playing)
        m_timer.start();
    else
        m_timer.stop();

    emit playingChanged();
}

qreal PlayerTracker::progress() const
{
    return m_duration > 0 ? qreal(m_position) / m_duration : 0.0;
}

void PlayerTracker::songChanged(int duration, int position)
{
    m_position = position;
    setDuration(duration);
    emit positionChanged();
}

void PlayerTracker::onPlayPause(bool isPlaying)
{
    setPlaying(isPlaying);
}

void PlayerTracker::onSeek(int position) {
    m_position = position;
    emit positionChanged();
}

void PlayerTracker::tick()
{
    m_position += kInterval;
    if(m_position > 0 && m_position >= m_duration ) {
        m_position = m_duration;
        m_timer.stop();
    }

    emit positionChanged();
}
