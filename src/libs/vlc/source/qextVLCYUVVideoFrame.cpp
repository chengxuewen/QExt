#include <qextVLCYUVVideoFrame.h>

#include <stdint.h>

QEXTVLCYUVVideoFrame::QEXTVLCYUVVideoFrame(unsigned *width, unsigned *height,
                                           unsigned *pitches, unsigned *lines)
    : QEXTVLCAbstractVideoFrame(3)
{
    uint16_t evenWidth = *width + (*width & 1 ? 1 : 0);
    uint16_t evenHeight = *height + (*height & 1 ? 1 : 0);

    pitches[0] = evenWidth;
    if (pitches[0] % 4)
    {
        pitches[0] += 4 - pitches[0] % 4;
    }
    pitches[1] = evenWidth / 2;
    if (pitches[1] % 4)
    {
        pitches[1] += 4 - pitches[1] % 4;
    }
    pitches[2] = pitches[1];

    lines[0] = evenHeight;
    lines[1] = evenHeight / 2;
    lines[2] = lines[1];

    frameBuffer.resize(pitches[0] * lines[0] + pitches[1] * lines[1] + pitches[2] * lines[2]);

    this->width = evenWidth;
    this->height = evenHeight;

    setPitchesAndLines(pitches, lines);
}

QEXTVLCYUVVideoFrame::~QEXTVLCYUVVideoFrame() {}

QEXTVLCYUVVideoFrame::QEXTVLCYUVVideoFrame(const QSharedPointer<QEXTVLCYUVVideoFrame> &frame)
    : QEXTVLCAbstractVideoFrame(3)
{
    frameBuffer.resize(frame->frameBuffer.size());

    width = frame->width;
    height = frame->height;

    this->setPitchesAndLines(frame);
}
