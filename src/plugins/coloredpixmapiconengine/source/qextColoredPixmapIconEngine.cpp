#include <qextColoredPixmapIconEngine.h>

#include <QPainter>
#include <QLoggingCategory>
#include <QtGui/private/qguiapplication_p.h>

Q_LOGGING_CATEGORY(lcQExtColoredPixmapIconEngine, "QExtColoredPixmapIconEngine")

#define lcDebug qCDebug(lcQExtColoredPixmapIconEngine)


QPixmap QExtColoredPixmapIconEngine::pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state)
{
    QPixmap pix = QPixmapIconEngine::pixmap(size, mode, state);
    if (pix.isNull())
    {
        return pix;
    }

    const QString colorName = QString::fromLocal8Bit(qgetenv("QT_COLORED_ICONS_COLOR"));
    const QColor color(colorName);
    if (color.isValid())
    {
        //        lcDebug << "Colorize icon with color" << color.name();

        QPainter painter(&pix);
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        painter.fillRect(pix.rect(), color);
        painter.end();

        QPixmap styledPix;
        if (QGuiApplication *gApp = qobject_cast<QGuiApplication *>(qApp))
        {
            styledPix = static_cast<QGuiApplicationPrivate *>(QObjectPrivate::get(gApp))->applyQIconStyleHelper(mode, pix);
        }

        if (!styledPix.isNull())
        {
            pix = styledPix;
        }
    }

    return pix;
}
