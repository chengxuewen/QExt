#ifndef _QEXTSTYLETHEMEMATERIAL_H
#define _QEXTSTYLETHEMEMATERIAL_H

#include <qextStyleThemeGlobal.h>
#include <qextStyleTheme.h>

class QEXTStyleThemeMaterialPrivate;
class QEXTStyleThemeMaterial : public QObject, public QEXTStyleTheme
{
public:
    explicit QEXTStyleThemeMaterial(QObject *parent = nullptr);
    ~QEXTStyleThemeMaterial();

    QString styleName() const QEXT_DECL_OVERRIDE;
    QString themeName(int type) const QEXT_DECL_OVERRIDE;

    int currentTheme() const QEXT_DECL_OVERRIDE;
    void setCurrentTheme(int type) QEXT_DECL_OVERRIDE;

    QString styleSheet() const QEXT_DECL_OVERRIDE;
    QString additionalStyle() const QEXT_DECL_OVERRIDE;
    void setAdditionalStyle(const QString &style) QEXT_DECL_OVERRIDE;
    void addAdditionalStyle(const QString &style) QEXT_DECL_OVERRIDE;

protected:
    QScopedPointer<QEXTStyleThemeMaterialPrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTStyleThemeMaterial)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTStyleThemeMaterial)
};

#endif // _QEXTSTYLETHEMEMATERIAL_H
