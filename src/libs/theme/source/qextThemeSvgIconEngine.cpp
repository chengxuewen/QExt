#include <qextThemeSvgIconEngine.h>

#include <QGuiApplication>
#include <QFileInfo>
#include <QPainter>
#include <QPixmap>
#include <QPixmapCache>
#include <QMimeDatabase>
#include <QMimeType>
#include <QAtomicInt>
#include <QDebug>
#include <QtSvg/QSvgRenderer>
#include <QtGui/private/qguiapplication_p.h>

class QEXTThemeSvgIconEnginePrivate : public QSharedData
{
public:
    QEXTThemeSvgIconEnginePrivate()
        : m_svgBuffers(0), m_addedPixmaps(0)
    {
        this->stepSerialNum();
    }

    ~QEXTThemeSvgIconEnginePrivate()
    {
        delete m_addedPixmaps;
        delete m_svgBuffers;
    }

    static int hashKey(QIcon::Mode mode, QIcon::State state)
    {
        return (((mode) << 4) | state);
    }

    QString pmcKey(const QSize &size, QIcon::Mode mode, QIcon::State state)
    {
        return QLatin1String("$qt_svgicon_")
               + QString::number(m_serialNum, 16).append(QLatin1Char('_'))
               + QString::number((((((qint64(size.width()) << 11) | size.height()) << 11) | mode) << 4) | state, 16);
    }

    void stepSerialNum()
    {
        m_serialNum = sm_lastSerialNum.fetchAndAddRelaxed(1);
    }

    void loadDataForModeAndState(QSvgRenderer *renderer, QIcon::Mode mode, QIcon::State state);

    QHash<int, QString> m_svgFiles;
    QHash<int, QByteArray> *m_svgBuffers;
    QHash<int, QPixmap> *m_addedPixmaps;
    int m_serialNum;
    static QAtomicInt sm_lastSerialNum;
};

QAtomicInt QEXTThemeSvgIconEnginePrivate::sm_lastSerialNum;

QEXTThemeSvgIconEngine::QEXTThemeSvgIconEngine()
    : d(new QEXTThemeSvgIconEnginePrivate)
{
}

QEXTThemeSvgIconEngine::QEXTThemeSvgIconEngine(const QEXTThemeSvgIconEngine &other)
    : QIconEngine(other), d(new QEXTThemeSvgIconEnginePrivate)
{
    d->m_svgFiles = other.d->m_svgFiles;
    if (other.d->m_svgBuffers)
    {
        d->m_svgBuffers = new QHash<int, QByteArray>(*other.d->m_svgBuffers);
    }
    if (other.d->m_addedPixmaps)
    {
        d->m_addedPixmaps = new QHash<int, QPixmap>(*other.d->m_addedPixmaps);
    }
}


QEXTThemeSvgIconEngine::~QEXTThemeSvgIconEngine()
{
}


QSize QEXTThemeSvgIconEngine::actualSize(const QSize &size, QIcon::Mode mode,
        QIcon::State state)
{
    if (d->m_addedPixmaps)
    {
        QPixmap pm = d->m_addedPixmaps->value(d->hashKey(mode, state));
        if (!pm.isNull() && pm.size() == size)
        {
            return size;
        }
    }

    QPixmap pm = pixmap(size, mode, state);
    if (pm.isNull())
    {
        return QSize();
    }
    return pm.size();
}

void QEXTThemeSvgIconEnginePrivate::loadDataForModeAndState(QSvgRenderer *renderer, QIcon::Mode mode, QIcon::State state)
{
    QByteArray buf;
    const QIcon::State oppositeState = state == QIcon::Off ? QIcon::On : QIcon::Off;
    if (m_svgBuffers)
    {
        buf = m_svgBuffers->value(this->hashKey(mode, state));
        if (buf.isEmpty())
        {
            buf = m_svgBuffers->value(this->hashKey(QIcon::Normal, state));
        }
        if (buf.isEmpty())
        {
            buf = m_svgBuffers->value(this->hashKey(QIcon::Normal, oppositeState));
        }
    }
    if (!buf.isEmpty())
    {
#ifndef QT_NO_COMPRESS
        buf = qUncompress(buf);
#endif
        renderer->load(buf);
    }
    else
    {
        QString svgFile = m_svgFiles.value(this->hashKey(mode, state));
        if (svgFile.isEmpty())
        {
            svgFile = m_svgFiles.value(this->hashKey(QIcon::Normal, state));
        }
        if (svgFile.isEmpty())
        {
            svgFile = m_svgFiles.value(this->hashKey(QIcon::Normal, oppositeState));
        }
        if (!svgFile.isEmpty())
        {
            renderer->load(svgFile);
        }
    }
}

QPixmap QEXTThemeSvgIconEngine::pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state)
{
    QPixmap pixmap;

    QString pmckey(d->pmcKey(size, mode, state));
    if (QPixmapCache::find(pmckey, pixmap))
    {
        return pixmap;
    }

    if (d->m_addedPixmaps)
    {
        pixmap = d->m_addedPixmaps->value(d->hashKey(mode, state));
        if (!pixmap.isNull() && pixmap.size() == size)
        {
            return pixmap;
        }
    }

    QSvgRenderer renderer;
    d->loadDataForModeAndState(&renderer, mode, state);
    if (!renderer.isValid())
    {
        return pixmap;
    }

    QSize actualSize = renderer.defaultSize();
    if (!actualSize.isNull())
    {
        actualSize.scale(size, Qt::KeepAspectRatio);
    }

    if (actualSize.isEmpty())
    {
        return QPixmap();
    }

    QImage img;
    QPainter imgPainter(&img);
    renderer.render(&imgPainter, QRect(0, 0, actualSize.width(), actualSize.height()));
    pixmap = QPixmap::fromImage(img);
    if (qobject_cast<QGuiApplication *>(QCoreApplication::instance()))
    {
        const QPixmap generated = QGuiApplicationPrivate::instance()->applyQIconStyleHelper(mode, pixmap);
        if (!generated.isNull())
        {
            pixmap = generated;
        }
    }

    if (!pixmap.isNull())
    {
        QPixmapCache::insert(pmckey, pixmap);
    }

    return pixmap;
}


void QEXTThemeSvgIconEngine::addPixmap(const QPixmap &pixmap, QIcon::Mode mode,
                                       QIcon::State state)
{
    if (!d->m_addedPixmaps)
    {
        d->m_addedPixmaps = new QHash<int, QPixmap>;
    }
    d->stepSerialNum();
    d->m_addedPixmaps->insert(d->hashKey(mode, state), pixmap);
}

enum FileType { OtherFile, SvgFile, CompressedSvgFile };

static FileType fileType(const QFileInfo &fi)
{
    const QString &abs = fi.absoluteFilePath();
    if (abs.endsWith(QLatin1String(".svg"), Qt::CaseInsensitive))
    {
        return SvgFile;
    }
    if (abs.endsWith(QLatin1String(".svgz"), Qt::CaseInsensitive)
            || abs.endsWith(QLatin1String(".svg.gz"), Qt::CaseInsensitive))
    {
        return CompressedSvgFile;
    }
#ifndef QT_NO_MIMETYPE
    const QString &mimeTypeName = QMimeDatabase().mimeTypeForFile(fi).name();
    if (mimeTypeName == QLatin1String("image/svg+xml"))
    {
        return SvgFile;
    }
    if (mimeTypeName == QLatin1String("image/svg+xml-compressed"))
    {
        return CompressedSvgFile;
    }
#endif // !QT_NO_MIMETYPE
    return OtherFile;
}

void QEXTThemeSvgIconEngine::addFile(const QString &fileName, const QSize &,
                                     QIcon::Mode mode, QIcon::State state)
{
    if (!fileName.isEmpty())
    {
        const QFileInfo fi(fileName);
        const QString abs = fi.absoluteFilePath();
        const FileType type = fileType(fi);
#ifndef QT_NO_COMPRESS
        if (type == SvgFile || type == CompressedSvgFile)
        {
#else
        if (type == SvgFile)
        {
#endif
            QSvgRenderer renderer(abs);
            if (renderer.isValid())
            {
                d->stepSerialNum();
                d->m_svgFiles.insert(d->hashKey(mode, state), abs);
            }
        }
        else if (type == OtherFile)
        {
            QPixmap pm(abs);
            if (!pm.isNull())
            {
                addPixmap(pm, mode, state);
            }
        }
    }
}

void QEXTThemeSvgIconEngine::paint(QPainter *painter, const QRect &rect,
                                   QIcon::Mode mode, QIcon::State state)
{
    QSize pixmapSize = rect.size();
    if (painter->device())
    {
        pixmapSize *= painter->device()->devicePixelRatioF();
    }
    painter->drawPixmap(rect, this->pixmap(pixmapSize, mode, state));
}

QString QEXTThemeSvgIconEngine::key() const
{
    return QLatin1String("svg");
}

QIconEngine *QEXTThemeSvgIconEngine::clone() const
{
    return new QEXTThemeSvgIconEngine(*this);
}


bool QEXTThemeSvgIconEngine::read(QDataStream &in)
{
    d = new QEXTThemeSvgIconEnginePrivate;
    d->m_svgBuffers = new QHash<int, QByteArray>;

    if (in.version() >= QDataStream::Qt_4_4)
    {
        int isCompressed;
        QHash<int, QString> fileNames;  // For memoryoptimization later
        in >> fileNames >> isCompressed >> *d->m_svgBuffers;
#ifndef QT_NO_COMPRESS
        if (!isCompressed)
        {
            for (auto it = d->m_svgBuffers->begin(), end = d->m_svgBuffers->end(); it != end; ++it)
            {
                it.value() = qCompress(it.value());
            }
        }
#else
        if (isCompressed)
        {
            qWarning("QEXTThemeSvgIconEngine: Can not decompress SVG data");
            d->svgBuffers->clear();
        }
#endif
        int hasAddedPixmaps;
        in >> hasAddedPixmaps;
        if (hasAddedPixmaps)
        {
            d->m_addedPixmaps = new QHash<int, QPixmap>;
            in >> *d->m_addedPixmaps;
        }
    }
    else
    {
        QPixmap pixmap;
        QByteArray data;
        uint mode;
        uint state;
        int num_entries;

        in >> data;
        if (!data.isEmpty())
        {
#ifndef QT_NO_COMPRESS
            data = qUncompress(data);
#endif
            if (!data.isEmpty())
            {
                d->m_svgBuffers->insert(d->hashKey(QIcon::Normal, QIcon::Off), data);
            }
        }
        in >> num_entries;
        for (int i = 0; i < num_entries; ++i)
        {
            if (in.atEnd())
            {
                return false;
            }
            in >> pixmap;
            in >> mode;
            in >> state;
            // The pm list written by 4.3 is buggy and/or useless, so ignore.
            //addPixmap(pixmap, QIcon::Mode(mode), QIcon::State(state));
        }
    }

    return true;
}


bool QEXTThemeSvgIconEngine::write(QDataStream &out) const
{
    if (out.version() >= QDataStream::Qt_4_4)
    {
        int isCompressed = 0;
#ifndef QT_NO_COMPRESS
        isCompressed = 1;
#endif
        QHash<int, QByteArray> svgBuffers;
        if (d->m_svgBuffers)
        {
            svgBuffers = *d->m_svgBuffers;
        }
        for (auto it = d->m_svgFiles.cbegin(), end = d->m_svgFiles.cend(); it != end; ++it)
        {
            QByteArray buf;
            QFile f(it.value());
            if (f.open(QIODevice::ReadOnly))
            {
                buf = f.readAll();
            }
#ifndef QT_NO_COMPRESS
            buf = qCompress(buf);
#endif
            svgBuffers.insert(it.key(), buf);
        }
        out << d->m_svgFiles << isCompressed << svgBuffers;
        if (d->m_addedPixmaps)
        {
            out << (int)1 << *d->m_addedPixmaps;
        }
        else
        {
            out << (int)0;
        }
    }
    else
    {
        QByteArray buf;
        if (d->m_svgBuffers)
        {
            buf = d->m_svgBuffers->value(d->hashKey(QIcon::Normal, QIcon::Off));
        }
        if (buf.isEmpty())
        {
            QString svgFile = d->m_svgFiles.value(d->hashKey(QIcon::Normal, QIcon::Off));
            if (!svgFile.isEmpty())
            {
                QFile f(svgFile);
                if (f.open(QIODevice::ReadOnly))
                {
                    buf = f.readAll();
                }
            }
        }
#ifndef QT_NO_COMPRESS
        buf = qCompress(buf);
#endif
        out << buf;
        // 4.3 has buggy handling of added pixmaps, so don't write any
        out << (int)0;
    }
    return true;
}
