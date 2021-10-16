#ifndef _QEXTTHEMEBUILTINICONENGINE_H
#define _QEXTTHEMEBUILTINICONENGINE_H

#include <qextThemeGlobal.h>

#include <QIconEngine>
#include <QtGui/private/qiconloader_p.h>

class QEXT_THEME_API QEXTThemeBuiltinIconEngine : public QIconEngine
{
public:
    QEXTThemeBuiltinIconEngine(const QString &iconName);
    ~QEXTThemeBuiltinIconEngine();

    void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) QEXT_DECL_OVERRIDE;
    QSize actualSize(const QSize &size, QIcon::Mode mode, QIcon::State state) QEXT_DECL_OVERRIDE;
    QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state) QEXT_DECL_OVERRIDE;

    QString key() const QEXT_DECL_OVERRIDE;
    QIconEngine *clone() const QEXT_DECL_OVERRIDE;
    bool read(QDataStream &in) QEXT_DECL_OVERRIDE;
    bool write(QDataStream &out) const QEXT_DECL_OVERRIDE;

    QString iconName() const QEXT_DECL_OVERRIDE;

    static QThemeIconInfo loadIcon(const QString &iconName, uint key);

protected:
    QEXTThemeBuiltinIconEngine(const QEXTThemeBuiltinIconEngine &other);
    bool hasIcon() const;
    void ensureLoaded();

    void virtual_hook(int id, void *data) QEXT_DECL_OVERRIDE;

private:
    friend class QIconLoader;
    QThemeIconInfo m_info;
    QString m_iconName;
    uint m_key;
};

#endif // _QEXTTHEMEBUILTINICONENGINE_H
