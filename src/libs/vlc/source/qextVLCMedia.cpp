#include <qextVLCError.h>
#include <qextVLCInstance.h>
#include <qextVLCMedia.h>
#include <qextVLCStats.h>

#include <QtCore/QDebug>
#include <QtCore/QDir>

#include <vlc/vlc.h>

QEXTVLCMedia::QEXTVLCMedia(const QString &location, bool localFile, QEXTVLCInstance *instance)
    : QObject(instance)
{
    this->initMedia(location, localFile, instance);
}

QEXTVLCMedia::QEXTVLCMedia(const QString &location, QEXTVLCInstance *instance)
    : QObject(instance)
{
    this->initMedia(location, false, instance);
}

QEXTVLCMedia::QEXTVLCMedia(libvlc_media_t *media)
{
    // Create a new libvlc media descriptor from existing one
    m_vlcMedia = libvlc_media_duplicate(media);
    QEXTVLCError::showErrMsg();
}

QEXTVLCMedia::~QEXTVLCMedia()
{
    removeCoreConnections();

    libvlc_media_release(m_vlcMedia);

    QEXTVLCError::showErrMsg();
}

libvlc_media_t *QEXTVLCMedia::core()
{
    return m_vlcMedia;
}

void QEXTVLCMedia::initMedia(const QString &location, bool localFile, QEXTVLCInstance *instance)
{
    m_currentLocation = location;
    QString l = location;
    if (localFile)
    {
        l = QDir::toNativeSeparators(l);
    }

    // Create a new libvlc media descriptor from location
    if (localFile)
    {
        m_vlcMedia = libvlc_media_new_path(instance->core(), l.toUtf8().data());
    }
    else
    {
        m_vlcMedia = libvlc_media_new_location(instance->core(), l.toUtf8().data());
    }

    m_vlcEvents = libvlc_media_event_manager(m_vlcMedia);

    this->createCoreConnections();

    QEXTVLCError::showErrMsg();
}

void QEXTVLCMedia::createCoreConnections()
{
    QList<libvlc_event_e> list;
    list << libvlc_MediaMetaChanged
         << libvlc_MediaSubItemAdded
         << libvlc_MediaDurationChanged
         << libvlc_MediaParsedChanged
         << libvlc_MediaFreed
         << libvlc_MediaStateChanged;

    foreach (const libvlc_event_e &event, list)
    {
        libvlc_event_attach(m_vlcEvents, event, libvlc_callback, this);
    }
}

void QEXTVLCMedia::removeCoreConnections()
{
    QList<libvlc_event_e> list;
    list << libvlc_MediaMetaChanged
         << libvlc_MediaSubItemAdded
         << libvlc_MediaDurationChanged
         << libvlc_MediaParsedChanged
         << libvlc_MediaFreed
         << libvlc_MediaStateChanged;

    foreach (const libvlc_event_e &event, list)
    {
        libvlc_event_detach(m_vlcEvents, event, libvlc_callback, this);
    }
}

bool QEXTVLCMedia::parsed() const
{
    int parsed = libvlc_media_is_parsed(m_vlcMedia);

    QEXTVLCError::showErrMsg();

    return parsed;
}

void QEXTVLCMedia::parse()
{
    libvlc_media_parse_async(m_vlcMedia);

    QEXTVLCError::showErrMsg();
}

QString QEXTVLCMedia::currentLocation() const
{
    return m_currentLocation;
}

QEXTVLCStats *QEXTVLCMedia::getStats()
{
    libvlc_media_stats_t *coreStats = new libvlc_media_stats_t;

    QEXTVLCStats *stats = new QEXTVLCStats;
    stats->valid = libvlc_media_get_stats(m_vlcMedia, coreStats);

    stats->read_bytes = coreStats->i_read_bytes;
    stats->input_bitrate = coreStats->f_input_bitrate;
    stats->demux_read_bytes = coreStats->i_demux_read_bytes;
    stats->demux_bitrate = coreStats->f_demux_bitrate;
    stats->demux_corrupted = coreStats->i_demux_corrupted;
    stats->demux_discontinuity = coreStats->i_demux_discontinuity;
    stats->decoded_video = coreStats->i_decoded_video;
    stats->decoded_audio = coreStats->i_decoded_audio;
    stats->displayed_pictures = coreStats->i_displayed_pictures;
    stats->lost_pictures = coreStats->i_lost_pictures;
    stats->played_abuffers = coreStats->i_played_abuffers;
    stats->lost_abuffers = coreStats->i_lost_abuffers;
    stats->sent_packets = coreStats->i_sent_packets;
    stats->sent_bytes = coreStats->i_sent_bytes;
    stats->send_bitrate = coreStats->f_send_bitrate;

    return stats;
}

QEXTVLC::StateType QEXTVLCMedia::state() const
{
    libvlc_state_t state;
    state = libvlc_media_get_state(m_vlcMedia);

    QEXTVLCError::showErrMsg();

    return QEXTVLC::StateType(state);
}

qint64 QEXTVLCMedia::duration() const
{
    libvlc_time_t duration = libvlc_media_get_duration(m_vlcMedia);

    QEXTVLCError::showErrMsg();

    return duration;
}

QString QEXTVLCMedia::duplicate(const QString &name,
                                const QString &path,
                                const QEXTVLC::MuxType &mux)
{
    return record(name, path, mux, true);
}

QString QEXTVLCMedia::duplicate(const QString &name,
                                const QString &path,
                                const QEXTVLC::MuxType &mux,
                                const QEXTVLC::AudioCodecType &audioCodec,
                                const QEXTVLC::VideoCodecType &videoCodec)
{
    return record(name, path, mux, audioCodec, videoCodec, true);
}

QString QEXTVLCMedia::duplicate(const QString &name,
                                const QString &path,
                                const QEXTVLC::MuxType &mux,
                                const QEXTVLC::AudioCodecType &audioCodec,
                                const QEXTVLC::VideoCodecType &videoCodec,
                                int bitrate,
                                int fps,
                                int scale)
{
    return record(name, path, mux, audioCodec, videoCodec, bitrate, fps, scale, true);
}

QString QEXTVLCMedia::merge(const QString &name,
                            const QString &path,
                            const QEXTVLC::MuxType &mux)
{
    QString option1, option2, parameters;
    QString l = QDir::toNativeSeparators(path + "/" + name);

    parameters = "gather:std{access=file,mux=%1,dst='%2'}";
    parameters = parameters.arg(QEXTVLC::mux()[mux], l + "." + QEXTVLC::mux()[mux]);

    option1 = ":sout-keep";
    option2 = ":sout=#%1";
    option2 = option2.arg(parameters);

    setOption(option1);
    setOption(option2);

    QEXTVLCError::showErrMsg();

    return l + "." + QEXTVLC::mux()[mux];
}

QString QEXTVLCMedia::record(const QString &name,
                             const QString &path,
                             const QEXTVLC::MuxType &mux,
                             bool duplicate)
{
    QString option1, option2, parameters;
    QString l = QDir::toNativeSeparators(path + "/" + name);

    parameters = "std{access=file,mux=%1,dst='%2'}";
    parameters = parameters.arg(QEXTVLC::mux()[mux], l + "." + QEXTVLC::mux()[mux]);

    if (duplicate)
    {
        option2 = ":sout=#duplicate{dst=display,dst=\"%1\"}";
    }
    else
    {
        option2 = ":sout=#%1";
    }

    option1 = ":sout-all";
    option2 = option2.arg(parameters);

    setOption(option1);
    setOption(option2);

    QEXTVLCError::showErrMsg();

    return l + "." + QEXTVLC::mux()[mux];
}

QString QEXTVLCMedia::record(const QString &name,
                             const QString &path,
                             const QEXTVLC::MuxType &mux,
                             const QEXTVLC::AudioCodecType &audioCodec,
                             const QEXTVLC::VideoCodecType &videoCodec,
                             bool duplicate)
{
    QString option1, option2, parameters;
    QString l = QDir::toNativeSeparators(path + "/" + name);

    parameters = "transcode{vcodec=%1,acodec=%2}:std{access=file,mux=%3,dst='%4'}";
    parameters = parameters.arg(QEXTVLC::videoCodec()[videoCodec], QEXTVLC::audioCodec()[audioCodec], QEXTVLC::mux()[mux], l + "." + QEXTVLC::mux()[mux]);

    if (duplicate)
    {
        option2 = ":sout=#duplicate{dst=display,dst=\"%1\"}";
    }
    else
    {
        option2 = ":sout=#%1";
    }

    option1 = ":sout-all";
    option2 = option2.arg(parameters);

    this->setOption(option1);
    this->setOption(option2);

    QEXTVLCError::showErrMsg();

    return l + "." + QEXTVLC::mux()[mux];
}

QString QEXTVLCMedia::record(const QString &name,
                             const QString &path,
                             const QEXTVLC::MuxType &mux,
                             const QEXTVLC::AudioCodecType &audioCodec,
                             const QEXTVLC::VideoCodecType &videoCodec,
                             int bitrate,
                             int fps,
                             int scale,
                             bool duplicate)
{
    QString option1, option2, parameters;
    QString l = QDir::toNativeSeparators(path + "/" + name);

    parameters = "transcode{vcodec=%1,vb=%2,fps=%3,scale=%4,acodec=%5}:std{access=file,mux=%6,dst='%7'}";
    parameters = parameters.arg(QEXTVLC::videoCodec()[videoCodec], QString::number(bitrate), QString::number(fps), QString::number(scale), QEXTVLC::audioCodec()[audioCodec], QEXTVLC::mux()[mux], l + "." + QEXTVLC::mux()[mux]);

    if (duplicate)
    {
        option2 = ":sout=#duplicate{dst=display,dst=\"%1\"}";
    }
    else
    {
        option2 = ":sout=#%1";
    }

    option1 = ":sout-all";
    option2 = option2.arg(parameters);

    this->setOption(option2);
    this->setOption(option1);

    QEXTVLCError::showErrMsg();

    return l + "." + QEXTVLC::mux()[mux];
}

void QEXTVLCMedia::setProgram(int program)
{
    QString option = "program=%1";
    this->setOption(option.arg(program));
}

void QEXTVLCMedia::setOption(const QString &option)
{
    libvlc_media_add_option(m_vlcMedia, option.toUtf8().data());

    QEXTVLCError::showErrMsg();
}

void QEXTVLCMedia::setOptions(const QStringList &options)
{
    foreach (const QString &option, options)
    {
        libvlc_media_add_option(m_vlcMedia, option.toUtf8().data());
    }

    QEXTVLCError::showErrMsg();
}

void QEXTVLCMedia::libvlc_callback(const libvlc_event_t *event, void *data)
{
    QEXTVLCMedia *core = static_cast<QEXTVLCMedia *>(data);

    switch (event->type)
    {
        case libvlc_MediaMetaChanged:
            emit core->metaChanged(QEXTVLC::MetaType(event->u.media_meta_changed.meta_type));
            break;
        case libvlc_MediaSubItemAdded:
            emit core->subitemAdded(event->u.media_subitem_added.new_child);
            break;
        case libvlc_MediaDurationChanged:
            emit core->durationChanged(event->u.media_duration_changed.new_duration);
            break;
        case libvlc_MediaParsedChanged:
            emit core->parsedChanged(event->u.media_parsed_changed.new_status);
            emit core->parsedChanged((bool)event->u.media_parsed_changed.new_status);
            break;
        case libvlc_MediaFreed:
            emit core->freed(event->u.media_freed.md);
            break;
        case libvlc_MediaStateChanged:
            emit core->stateChanged(QEXTVLC::StateType(event->u.media_state_changed.new_state));
            break;
        default:
            break;
    }
}
