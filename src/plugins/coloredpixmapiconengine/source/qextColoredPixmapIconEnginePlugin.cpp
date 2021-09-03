#include <qextColoredPixmapIconEngine.h>

#include <QDebug>
#include <QFileInfo>
#include <QIconEnginePlugin>
#include <QLoggingCategory>
#include <QRegularExpression>

Q_LOGGING_CATEGORY(lcQEXTColoredPixmapIconEnginePlugin, "QEXTColoredPixmapIconEnginePlugin")

#define lcDebug qCDebug(lcQEXTColoredPixmapIconEnginePlugin)
#define lcWarning qCWarning(lcQEXTColoredPixmapIconEnginePlugin)


class QEXTColoredPixmapIconEnginePlugin : public QIconEnginePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QIconEngineFactoryInterface_iid FILE "QEXTColoredPixmapIcon.json")

public:
    QEXTColoredPixmapIconEnginePlugin(QObject *parent = Q_NULLPTR);
    QIconEngine *create(const QString &filename = QString()) QEXT_DECL_OVERRIDE;

private:
    QRegularExpression m_reColoredFiles;
};

QEXTColoredPixmapIconEnginePlugin::QEXTColoredPixmapIconEnginePlugin(QObject *parent) : QIconEnginePlugin(parent)
{
    const QString fileNamePattern = QString::fromLocal8Bit(qgetenv("QT_COLORED_ICONS_FILES_PATTERN"));
    m_reColoredFiles.setPattern(fileNamePattern);
    m_reColoredFiles.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
    lcDebug << "Use regexp pattern:" << fileNamePattern;
}

QIconEngine *QEXTColoredPixmapIconEnginePlugin::create(const QString &filePath)
{
    const QString baseFileName = QFileInfo(filePath).baseName();
    const bool colorizeFile = m_reColoredFiles.pattern().isEmpty() ? false : m_reColoredFiles.match(baseFileName).hasMatch();
    QPixmapIconEngine *engine = colorizeFile ? (new QEXTColoredPixmapIconEngine) : (new QPixmapIconEngine);

    lcDebug << qPrintable(QString("Use %1 icon engine for file:").arg(colorizeFile ? "colored" : "default"))
            << filePath;

    if (!filePath.isEmpty())
    {
        engine->addFile(filePath, QSize(), QIcon::Normal, QIcon::Off);
    }

    return engine;
}

QT_MOC_EXPORT_PLUGIN(QEXTColoredPixmapIconEnginePlugin, QEXTColoredPixmapIconEnginePlugin)

#include "qextColoredPixmapIconEnginePlugin.moc"
