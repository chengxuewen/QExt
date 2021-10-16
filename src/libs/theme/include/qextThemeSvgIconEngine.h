#ifndef _QEXTTHEMESVGICONENGINE_H
#define _QEXTTHEMESVGICONENGINE_H

#include <qextThemeGlobal.h>

#include <QIconEngine>
#include <QtGui/private/qiconloader_p.h>

class QEXTThemeSvgIconEnginePrivate;
class QEXT_THEME_API QEXTThemeSvgIconEngine : public QIconEngine
{
public:
    QEXTThemeSvgIconEngine();
    QEXTThemeSvgIconEngine(const QEXTThemeSvgIconEngine &other);
    ~QEXTThemeSvgIconEngine();

    void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state);
    QSize actualSize(const QSize &size, QIcon::Mode mode, QIcon::State state);
    QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state);

    void addPixmap(const QPixmap &pixmap, QIcon::Mode mode, QIcon::State state);
    void addFile(const QString &fileName, const QSize &size, QIcon::Mode mode, QIcon::State state);

    QString key() const;
    QIconEngine *clone() const;
    bool read(QDataStream &in);
    bool write(QDataStream &out) const;

private:
    QSharedDataPointer<QEXTThemeSvgIconEnginePrivate> d;
};


#endif // _QEXTTHEMESVGICONENGINE_H
