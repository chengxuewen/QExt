#include <qextThemeBuiltinIconEngine.h>
#include <qextThemeHelper.h>

#include <QPainter>
#include <QPixmap>
#include <QPixmapCache>
#include <QImageReader>
#include <QDir>
#include <qmath.h>
#include <private/qiconloader_p.h>
#include <private/qguiapplication_p.h>
#include <QDebug>

#define BUILTIN_ICON_PATH ":/icons/deepin/builtin"

class QEXTThemeImageEntry : public QIconLoaderEngineEntry
{
public:
    enum Type
    {
        TextType, // 完全跟随画笔前景色变化
        ActionType, // 只在非normal状态下跟随画笔前景色
        IconType // 任务状态都不跟随画笔颜色
    };

    QEXTThemeImageEntry(Type t)
        : m_type(t)
    {
    }

    QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state) QEXT_DECL_OVERRIDE
    {
        Q_UNUSED(state)

        if (Q_UNLIKELY(!m_reader.device()))
        {
            m_reader.setFileName(filename);
        }

        if (dir.type == QIconDirInfo::Scalable)
        {
            m_reader.setScaledSize(size);
        }

        QPixmap pixmap = QPixmap::fromImageReader(&m_reader);

        if (m_type == IconType && qobject_cast<QGuiApplication *>(QCoreApplication::instance()))
        {
            const QPixmap generated = QGuiApplicationPrivate::instance()->applyQIconStyleHelper(mode, pixmap);
            if (!generated.isNull())
            {
                pixmap = generated;
            }
        }

        return pixmap;
    }

    Type m_type;
    QImageReader m_reader;
};

class QEXTThemeDirImageEntry : public QEXTThemeImageEntry
{
public:
    QEXTThemeDirImageEntry(Type t)
        : QEXTThemeImageEntry(t)
    {
    }

    static QString iconFile(const QString &key, const QDir &dir, const QString &suffix)
    {
        if (dir.exists(key + "." + suffix))
        {
            return dir.filePath(key + "." + suffix);
        }

        int index = key.indexOf('_');

        if (index > 0)
        {
            const QString &mode = key.left(index);

            if (dir.exists(mode + "." + suffix))
            {
                return dir.filePath(mode + "." + suffix);
            }

            const QString &state = key.mid(index);

            if (dir.exists("normal" + state + "." + suffix))
            {
                return dir.filePath("normal" + state + "." + suffix);
            }
        }

        return dir.filePath("normal." + suffix);
    }

    QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state) override
    {
        if (m_iconFileMap.isEmpty())
        {
            const QString &suffix = QFileInfo(filename).suffix();
            QDir dir(filename);

            m_iconFileMap[QIcon::Disabled << 8 | QIcon::On] = this->iconFile("disabled_on", dir, suffix);
            m_iconFileMap[QIcon::Disabled << 8 | QIcon::Off] = this->iconFile("disabled_off", dir, suffix);
            m_iconFileMap[QIcon::Active << 8 | QIcon::On] = this->iconFile("active_on", dir, suffix);
            m_iconFileMap[QIcon::Active << 8 | QIcon::Off] = this->iconFile("active_off", dir, suffix);
            m_iconFileMap[QIcon::Selected << 8 | QIcon::On] = this->iconFile("selected_on", dir, suffix);
            m_iconFileMap[QIcon::Selected << 8 | QIcon::Off] = this->iconFile("selected_off", dir, suffix);
            m_iconFileMap[QIcon::Normal << 8 | QIcon::On] = this->iconFile("normal_on", dir, suffix);
            m_iconFileMap[QIcon::Normal << 8 | QIcon::Off] = this->iconFile("normal_off", dir, suffix);
        }

        m_reader.setFileName(m_iconFileMap.value(mode << 8 | state));

        return QEXTThemeImageEntry::pixmap(size, mode, state);
    }

    QMap<qint16, QString> m_iconFileMap;
};

QEXTThemeBuiltinIconEngine::QEXTThemeBuiltinIconEngine(const QString &iconName)
    : m_iconName(iconName)
    , m_key(UINT_MAX)
{

}

QEXTThemeBuiltinIconEngine::QEXTThemeBuiltinIconEngine(const QEXTThemeBuiltinIconEngine &other)
    : QIconEngine(other)
    , m_iconName(other.m_iconName)
    , m_key(other.m_key)
{

}

QEXTThemeBuiltinIconEngine::~QEXTThemeBuiltinIconEngine()
{

}

QSize QEXTThemeBuiltinIconEngine::actualSize(const QSize &size, QIcon::Mode mode, QIcon::State state)
{
    Q_UNUSED(mode);
    Q_UNUSED(state);

    this->ensureLoaded();

//    QIconLoaderEngineEntry *entry = QIconLoaderEngine::entryForSize(m_info, size);
//    if (entry)
//    {
//        const QIconDirInfo &dir = entry->dir;
//        if (dir.type == QIconDirInfo::Scalable)
//        {
//            return size;
//        }
//        else
//        {
//            int result = qMin<int>(dir.size, qMin(size.width(), size.height()));
//            return QSize(result, result);
//        }
//    }
    return QSize(0, 0);
}

QPixmap QEXTThemeBuiltinIconEngine::pixmap(const QSize &size, QIcon::Mode mode,
        QIcon::State state)
{
    this->ensureLoaded();

//    QIconLoaderEngineEntry *entry = QIconLoaderEngine::entryForSize(m_info, size);
//    if (entry)
//    {
//        return entry->pixmap(size, mode, state);
//    }

    return QPixmap();
}

void QEXTThemeBuiltinIconEngine::paint(QPainter *painter, const QRect &rect,
                                       QIcon::Mode mode, QIcon::State state)
{
    this->ensureLoaded();

    QSize pixmapSize = rect.size();
    qreal scale = 1;
    if (painter->device())
    {
        scale = painter->device()->devicePixelRatioF();
    }

    pixmapSize *= scale;

//    QIconLoaderEngineEntry *entry = QIconLoaderEngine::entryForSize(m_info, pixmapSize);
//    if (!entry)
//    {
//        return;
//    }

//    QPixmap pixmap = entry->pixmap(pixmapSize, mode, state);
    QPixmap pixmap;
//    QEXTThemeImageEntry::Type type = static_cast<QEXTThemeImageEntry *>(entry)->m_type;

//    if (type == QEXTThemeImageEntry::TextType || (type == QEXTThemeImageEntry::ActionType && mode != QIcon::Normal))
//    {
//        QPainter pa(&pixmap);
//        pa.setCompositionMode(QPainter::CompositionMode_SourceIn);
//        pa.fillRect(pixmap.rect(), painter->pen().brush());
//    }

    pixmap.setDevicePixelRatio(scale);
    painter->drawPixmap(rect, pixmap);
}

QString QEXTThemeBuiltinIconEngine::key() const
{
    return QLatin1String("QEXTThemeBuiltinIconEngine");
}

QIconEngine *QEXTThemeBuiltinIconEngine::clone() const
{
    return new QEXTThemeBuiltinIconEngine(*this);
}


bool QEXTThemeBuiltinIconEngine::read(QDataStream &in)
{
    in >> m_iconName;
    return true;
}


bool QEXTThemeBuiltinIconEngine::write(QDataStream &out) const
{
    out << m_iconName;
    return true;
}

QString QEXTThemeBuiltinIconEngine::iconName() const
{
    return m_iconName;
}

QThemeIconInfo QEXTThemeBuiltinIconEngine::loadIcon(const QString &iconName, uint key)
{
    QThemeIconInfo info;
    info.iconName = iconName;

    QString theme_name = (key == QEXTThemeHelper::Color_Dark ? "dark" : "light");
    QStringList iconDirList
    {
        QString("%1/%2/texts").arg(BUILTIN_ICON_PATH, theme_name),
        QString("%1/%2/actions").arg(BUILTIN_ICON_PATH, theme_name),
        QString("%1/%2/icons").arg(BUILTIN_ICON_PATH, theme_name),
        QString("%1/texts").arg(BUILTIN_ICON_PATH),
        QString("%1/actions").arg(BUILTIN_ICON_PATH),
        QString("%1/icons").arg(BUILTIN_ICON_PATH)
    };

    QDir dir;
    dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    for (int i = 0; i < iconDirList.count(); ++i)
    {
        dir.setPath(iconDirList.at(i));

        if (!dir.exists())
        {
            continue;
        }

        QEXTThemeImageEntry::Type type = static_cast<QEXTThemeImageEntry::Type>(i % 3);

        for (const QFileInfo &icon_file_info : dir.entryInfoList())
        {
            const QString &file_name = icon_file_info.fileName();

            if (!file_name.startsWith(iconName))
            {
                continue;
            }

            // 先找到px所在位置
            int size_str_pos = iconName.length() + 1;
            int px_str_pos = file_name.indexOf("px.", size_str_pos + 1);

            if (px_str_pos < 0)
            {
                continue;
            }

            bool ok = false;
            int size = file_name.mid(size_str_pos, px_str_pos - size_str_pos).toInt(&ok);

            if (Q_UNLIKELY(!ok || size <= 0))
            {
                continue;
            }

            QEXTThemeImageEntry *entry = icon_file_info.isDir() ? new QEXTThemeDirImageEntry(type) : new QEXTThemeImageEntry(type);
            entry->filename = icon_file_info.absoluteFilePath();
            entry->dir.path = icon_file_info.absolutePath();
            entry->dir.size = size;
            entry->dir.type = icon_file_info.suffix().startsWith("svg") ? QIconDirInfo::Scalable : QIconDirInfo::Fixed;
            info.entries.append(entry);
        }

        // 已经找到图标时不再继续
        if (!info.entries.isEmpty())
        {
            break;
        }
    }

    return info;
}

bool QEXTThemeBuiltinIconEngine::hasIcon() const
{
    return !m_info.entries.isEmpty();
}

void QEXTThemeBuiltinIconEngine::virtual_hook(int id, void *data)
{
    this->ensureLoaded();

    switch (id)
    {
        case QIconEngine::AvailableSizesHook:
            {
                QIconEngine::AvailableSizesArgument &arg = *reinterpret_cast<QIconEngine::AvailableSizesArgument *>(data);
                const int N = m_info.entries.size();
                QList<QSize> sizes;
                sizes.reserve(N);

                // Gets all sizes from the DirectoryInfo entries
                for (int i = 0; i < N; ++i)
                {
                    const QIconLoaderEngineEntry *entry = m_info.entries.at(i);
                    int size = entry->dir.size;
                    sizes.append(QSize(size, size));
                }
                arg.sizes.swap(sizes); // commit
            }
            break;
        case QIconEngine::IconNameHook:
            {
                QString &name = *reinterpret_cast<QString *>(data);
                name = m_info.iconName;
            }
            break;
        case QIconEngine::IsNullHook:
            {
                *reinterpret_cast<bool *>(data) = m_info.entries.isEmpty();
            }
            break;
        case QIconEngine::ScaledPixmapHook:
            {
                QIconEngine::ScaledPixmapArgument &arg = *reinterpret_cast<QIconEngine::ScaledPixmapArgument *>(data);
                // QIcon::pixmap() multiplies size by the device pixel ratio.
                const int integerScale = qCeil(arg.scale);
//                QIconLoaderEngineEntry *entry = QIconLoaderEngine::entryForSize(m_info, arg.size / integerScale, integerScale);
//                arg.pixmap = entry ? entry->pixmap(arg.size, arg.mode, arg.state) : QPixmap();
            }
            break;
        default:
            QIconEngine::virtual_hook(id, data);
    }
}

void QEXTThemeBuiltinIconEngine::ensureLoaded()
{
    if (QEXTThemeHelper::instance()->themeType() == m_key)
    {
        return;
    }

    qDeleteAll(m_info.entries);
    m_info.entries.clear();
    m_info.iconName.clear();

    Q_ASSERT(m_info.entries.size() == 0);
    m_key = QEXTThemeHelper::instance()->themeType();
    m_info = loadIcon(m_iconName, m_key);
}
