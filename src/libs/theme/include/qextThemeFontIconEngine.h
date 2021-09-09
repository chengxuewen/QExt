#ifndef QEXTTHEMEFONTICONENGINE_H
#define QEXTTHEMEFONTICONENGINE_H

#include <qextThemeGlobal.h>
#include <qextObject.h>

#include <qextThemePalette.h>

#include <QIconEngine>

class QEXTThemeFontIconEnginePrivate;
class QEXT_THEME_API QEXTThemeFontIconEngine : public QIconEngine, public QEXTObject
{
public:
    QEXTThemeFontIconEngine();
    QEXTThemeFontIconEngine(QEXTThemePalette::ColorGroup cg, QEXTThemePalette::ColorType ct);
    QEXTThemeFontIconEngine(const QEXTThemeFontIconEngine &other);
    ~QEXTThemeFontIconEngine();

    void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) QEXT_DECL_OVERRIDE;
    QSize actualSize(const QSize &size, QIcon::Mode mode, QIcon::State state) QEXT_DECL_OVERRIDE;
    QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state) QEXT_DECL_OVERRIDE;

    QString key() const QEXT_DECL_OVERRIDE;
    QIconEngine *clone() const QEXT_DECL_OVERRIDE;
    bool read(QDataStream &in) QEXT_DECL_OVERRIDE;
    bool write(QDataStream &out) const QEXT_DECL_OVERRIDE;

    QString iconName() const QEXT_DECL_OVERRIDE;

private:
    QEXTThemeFontIconEngine &operator=(const QEXTThemeFontIconEngine &other);
    QEXT_DECL_PRIVATE(QEXTThemeFontIconEngine)
};

#endif // QEXTTHEMEFONTICONENGINE_H
