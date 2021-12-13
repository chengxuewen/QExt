#include <qextVLC.h>

QEXTVLC::QEXTVLC(QObject *parent)
    : QObject(parent)
{

}

QStringList QEXTVLC::logLevel()
{
    QStringList list;
    list << "debug"
         << "debug"
         << "notice"
         << "warning"
         << "error"
         << "disabled";

    return list;
}

QStringList QEXTVLC::audioCodec()
{
    QStringList list;
    list << "none"
         << "mpga"
         << "mp3"
         << "mp4a"
         << "vorb"
         << "flac";

    return list;
}

QStringList QEXTVLC::audioOutput()
{
    QStringList list;
    list << "default";

    return list;
}

QStringList QEXTVLC::audioOutputHuman()
{
    QStringList list;
    list << "default";

    return list;
}

QStringList QEXTVLC::deinterlacing()
{
    QStringList list;
    list << ""
         << "discard"
         << "blend"
         << "man"
         << "bob"
         << "linear"
         << "x"
         << "yadif"
         << "yadif2x"
         << "phosphor"
         << "ivtc";

    return list;
}

QStringList QEXTVLC::mux()
{
    QStringList list;
    list << "ts"
         << "ps"
         << "mp4"
         << "ogg"
         << "avi";

    return list;
}

QStringList QEXTVLC::ratio()
{
    QStringList list;
    list << ""
         << "ignore"
         << "16:9"
         << "16:10"
         << "185:100"
         << "221:100"
         << "235:100"
         << "239:100"
         << "4:3"
         << "5:4"
         << "5:3"
         << "1:1";

    return list;
}

QStringList QEXTVLC::ratioHuman()
{
    QStringList list;
    list << ""
         << ""
         << "16:9"
         << "16:10"
         << "1.85:1"
         << "2.21:1"
         << "2.35:1"
         << "2.39:1"
         << "4:3"
         << "5:4"
         << "5:3"
         << "1:1";

    return list;
}

QSizeF QEXTVLC::ratioSize(const QEXTVLC::RatioType &ratio)
{
    switch (ratio)
    {
        case QEXTVLC::Ratio_16_9:
            return QSizeF(16, 9);
            break;
        case QEXTVLC::Ratio_16_10:
            return QSizeF(16, 10);
            break;
        case QEXTVLC::Ratio_185_100:
            return QSizeF(185, 100);
            break;
        case QEXTVLC::Ratio_221_100:
            return QSizeF(221, 100);
            break;
        case QEXTVLC::Ratio_235_100:
            return QSizeF(235, 100);
            break;
        case QEXTVLC::Ratio_239_100:
            return QSizeF(239, 100);
            break;
        case QEXTVLC::Ratio_4_3:
            return QSizeF(4, 3);
            break;
        case QEXTVLC::Ratio_5_4:
            return QSizeF(5, 4);
            break;
        case QEXTVLC::Ratio_5_3:
            return QSizeF(5, 3);
            break;
        case QEXTVLC::Ratio_1_1:
            return QSizeF(1, 1);
            break;
        case QEXTVLC::Ratio_Original:
        case QEXTVLC::Ratio_Ignore:
        default:
            return QSizeF(0, 0);
            break;
    }

    return QSizeF(0, 0);
}

QList<float> QEXTVLC::scale()
{
    QList<float> list;
    list << (float)0
         << (float)1.05
         << (float)1.1
         << (float)1.2
         << (float)1.3
         << (float)1.4
         << (float)1.5
         << (float)1.6
         << (float)1.7
         << (float)1.8
         << (float)1.9
         << (float)2.0;

    return list;
}

QStringList QEXTVLC::videoCodec()
{
    QStringList list;
    list << "none"
         << "mpgv"
         << "mp4v"
         << "h264"
         << "theora";

    return list;
}

QStringList QEXTVLC::videoOutput()
{
    QStringList list;
    list << "default";

#if defined(Q_OS_LINUX)
    list << "x11"
         << "xvideo"
         << "glx";
#elif defined(Q_OS_WIN32)
    list << "directx"
         << "direct3d"
         << "opengl";
#endif

    return list;
}

QStringList QEXTVLC::videoOutputHuman()
{
    QStringList list;
    list << "default";

#if defined(Q_OS_LINUX)
    list << "X11"
         << "XVideo"
         << "OpenGL";
#elif defined(Q_OS_WIN32)
    list << "DirectX"
         << "Direct3D"
         << "OpenGL";
#endif

    return list;
}
