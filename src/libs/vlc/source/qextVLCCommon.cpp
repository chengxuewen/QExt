#include <qextVLCCommon.h>

QStringList QEXTVLCCommon::args()
{
    QStringList argsList;

    QString args = qgetenv("VLC_ARGS");
    if (!args.isEmpty())
    {
        argsList << args.split(" ", QString::SkipEmptyParts);
    }
    else
    {
        argsList << "--intf=dummy"
                  << "--no-media-library"
                  << "--no-stats"
                  << "--no-osd"
                  << "--no-loop"
                  << "--no-video-title-show"
#if defined(Q_OS_DARWIN)
                  << "--vout=macosx"
#endif
                  << "--drop-late-frames";
    }

    return argsList;
}

bool QEXTVLCCommon::setPluginPath(const QString &path)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    const bool empty = qEnvironmentVariableIsEmpty("VLC_PLUGIN_PATH");
#else
    const bool empty = qgetenv("VLC_PLUGIN_PATH").isEmpty();
#endif
    if (empty)
    {
        return qputenv("VLC_PLUGIN_PATH", path.toLocal8Bit());
    }
    return false;
}
