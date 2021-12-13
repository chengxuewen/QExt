#include <qextQmlVLCSource.h>
#include <qextQmlVLCVideoStream.h>

QEXTQmlVLCSource::QEXTQmlVLCSource(QObject *parent)
    : QObject(parent)
    , m_videoStream(new QEXTQmlVLCVideoStream(parent)) {}

QEXTQmlVLCSource::~QEXTQmlVLCSource()
{
    delete m_videoStream;
}

void QEXTQmlVLCSource::setPlayer(QEXTVLCMediaPlayer *player)
{
    m_videoStream->init(player);
}

void QEXTQmlVLCSource::removePlayer()
{
    m_videoStream->deinit();
}

void QEXTQmlVLCSource::registerVideoOutput(QEXTQmlVLCVideoOutput *output)
{
    m_videoStream->registerVideoOutput(output);
}

void QEXTQmlVLCSource::deregisterVideoOutput(QEXTQmlVLCVideoOutput *output)
{
    m_videoStream->deregisterVideoOutput(output);
}
