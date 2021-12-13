#include <qextVLCMetaManager.h>
#include <qextVLCMedia.h>

#include <vlc/vlc.h>
#include <vlc/deprecated.h>

QEXTVLCMetaManager::QEXTVLCMetaManager(QEXTVLCMedia *media)
    : m_media(media)
{
    libvlc_media_parse(media->core());
}

QEXTVLCMetaManager::~QEXTVLCMetaManager() {}

QString QEXTVLCMetaManager::title() const
{
    QString meta(libvlc_media_get_meta(m_media->core(), libvlc_meta_Title));
    return meta;
}

void QEXTVLCMetaManager::setTitle(const QString &title)
{
    libvlc_media_set_meta(m_media->core(), libvlc_meta_Title, title.toUtf8().data());
}

QString QEXTVLCMetaManager::artist() const
{
    QString meta(libvlc_media_get_meta(m_media->core(), libvlc_meta_Artist));
    return meta;
}

void QEXTVLCMetaManager::setArtist(const QString &artist)
{
    libvlc_media_set_meta(m_media->core(), libvlc_meta_Artist, artist.toUtf8().data());
}

QString QEXTVLCMetaManager::genre() const
{
    QString meta(libvlc_media_get_meta(m_media->core(), libvlc_meta_Genre));
    return meta;
}

void QEXTVLCMetaManager::setGenre(const QString &genre)
{
    libvlc_media_set_meta(m_media->core(), libvlc_meta_Genre, genre.toUtf8().data());
}

QString QEXTVLCMetaManager::copyright() const
{
    QString meta(libvlc_media_get_meta(m_media->core(), libvlc_meta_Copyright));
    return meta;
}

void QEXTVLCMetaManager::setCopyright(const QString &copyright)
{
    libvlc_media_set_meta(m_media->core(), libvlc_meta_Copyright, copyright.toUtf8().data());
}

QString QEXTVLCMetaManager::album() const
{
    QString meta(libvlc_media_get_meta(m_media->core(), libvlc_meta_Album));
    return meta;
}

void QEXTVLCMetaManager::setAlbum(const QString &album)
{
    libvlc_media_set_meta(m_media->core(), libvlc_meta_Album, album.toUtf8().data());
}

int QEXTVLCMetaManager::number() const
{
    QString meta(libvlc_media_get_meta(m_media->core(), libvlc_meta_TrackNumber));
    return meta.toInt();
}

void QEXTVLCMetaManager::setNumber(int number)
{
    libvlc_media_set_meta(m_media->core(), libvlc_meta_TrackNumber, QString().number(number).toUtf8().data());
}

QString QEXTVLCMetaManager::description() const
{
    QString meta(libvlc_media_get_meta(m_media->core(), libvlc_meta_Description));
    return meta;
}

void QEXTVLCMetaManager::setDescription(const QString &description)
{
    libvlc_media_set_meta(m_media->core(), libvlc_meta_Description, description.toUtf8().data());
}

QString QEXTVLCMetaManager::rating() const
{
    QString meta(libvlc_media_get_meta(m_media->core(), libvlc_meta_Rating));
    return meta;
}

int QEXTVLCMetaManager::year() const
{
    QString meta(libvlc_media_get_meta(m_media->core(), libvlc_meta_Date));
    return meta.toInt();
}

void QEXTVLCMetaManager::setYear(int year)
{
    libvlc_media_set_meta(m_media->core(), libvlc_meta_Date, QString().number(year).toUtf8().data());
}

QString QEXTVLCMetaManager::setting() const
{
    QString meta(libvlc_media_get_meta(m_media->core(), libvlc_meta_Setting));
    return meta;
}

QString QEXTVLCMetaManager::url() const
{
    QString meta(libvlc_media_get_meta(m_media->core(), libvlc_meta_URL));
    return meta;
}

QString QEXTVLCMetaManager::language() const
{
    QString meta(libvlc_media_get_meta(m_media->core(), libvlc_meta_Language));
    return meta;
}

void QEXTVLCMetaManager::setLanguage(const QString &language)
{
    libvlc_media_set_meta(m_media->core(), libvlc_meta_Language, language.toUtf8().data());
}

QString QEXTVLCMetaManager::publisher() const
{
    QString meta(libvlc_media_get_meta(m_media->core(), libvlc_meta_Publisher));
    return meta;
}

void QEXTVLCMetaManager::setPublisher(const QString &publisher)
{
    libvlc_media_set_meta(m_media->core(), libvlc_meta_Publisher, publisher.toUtf8().data());
}

QString QEXTVLCMetaManager::encoder() const
{
    QString meta(libvlc_media_get_meta(m_media->core(), libvlc_meta_EncodedBy));
    return meta;
}

void QEXTVLCMetaManager::setEncoder(const QString &encoder)
{
    libvlc_media_set_meta(m_media->core(), libvlc_meta_EncodedBy, encoder.toUtf8().data());
}

QString QEXTVLCMetaManager::artwork() const
{
    QString meta(libvlc_media_get_meta(m_media->core(), libvlc_meta_ArtworkURL));
    return meta;
}

QString QEXTVLCMetaManager::id() const
{
    QString meta(libvlc_media_get_meta(m_media->core(), libvlc_meta_TrackID));
    return meta;
}

bool QEXTVLCMetaManager::saveMeta() const
{
    return libvlc_media_save_meta(m_media->core());
}
