#include <qextVLCYUVVideoFrame.h>
#include <qextQmlVLCVideoOutput.h>
#include <qextQmlVLCVideoStream.h>

QEXTQmlVLCVideoStream::QEXTQmlVLCVideoStream(QObject *parent)
    : QEXTVLCVideoStream(QEXTVLC::YUVFormat, parent)
{

}

QEXTQmlVLCVideoStream::~QEXTQmlVLCVideoStream() {}

void QEXTQmlVLCVideoStream::frameUpdated()
{
    // convert to shared pointer to const frame to avoid crash
    QSharedPointer<const QEXTVLCYUVVideoFrame> frame = this->renderFrame().dynamicCast<const QEXTVLCYUVVideoFrame>();
    if (frame.isNull())
    {
        return; // LCOV_EXCL_LINE
    }
    for (int i = 0; i < m_attachedOutputs.size(); ++i)
    {
        m_attachedOutputs.at(i)->presentFrame(frame);
    }
}

void QEXTQmlVLCVideoStream::registerVideoOutput(QEXTQmlVLCVideoOutput *output)
{
    Q_ASSERT(m_attachedOutputs.count(output) <= 1);

    if (m_attachedOutputs.contains(output))
    {
        return;
    }

    m_attachedOutputs.append(output);
}

void QEXTQmlVLCVideoStream::deregisterVideoOutput(QEXTQmlVLCVideoOutput *output)
{
    Q_ASSERT(m_attachedOutputs.count(output) <= 1);

    m_attachedOutputs.removeOne(output);
}
