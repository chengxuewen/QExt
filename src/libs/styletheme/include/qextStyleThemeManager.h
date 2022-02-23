#ifndef _QEXTSTYLETHEMEMANAGER_H
#define _QEXTSTYLETHEMEMANAGER_H

#include <qextStyleThemeGlobal.h>
#include <qextStyleTheme.h>

#include <QApplication>
#include <QObject>
#include <QWidget>

class QEXTStyleThemeManagerPrivate;
class QEXT_STYLETHEM_API QEXTStyleThemeManager : public QObject
{
public:
    enum StyleType
    {
        Style_Default = 0,
        Style_Material,
        Style_Universal,
    };
    Q_ENUM(StyleType)

    explicit QEXTStyleThemeManager(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTStyleThemeManager();

    QEXTStyleTheme *styleTheme(StyleType type) const;
    QSharedPointer<QEXTStyleTheme> currentStyleTheme() const;

    StyleType currentStyle() const;
    void setCurrentStyle(StyleType type);

    static QString styleTypeString(int type);

protected:
    QScopedPointer<QEXTStyleThemeManagerPrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTStyleThemeManager)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTStyleThemeManager)
};

#endif // _QEXTSTYLETHEMEMANAGER_H
