#ifndef _QEXTSTYLETHEMEDEFAULT_H
#define _QEXTSTYLETHEMEDEFAULT_H

#include <qextStyleThemeGlobal.h>
#include <qextStyleTheme.h>

#include <QObject>

class QEXTStyleThemeDefaultPrivate;
class QEXT_STYLETHEM_API QEXTStyleThemeDefault : public QObject, public QEXTStyleTheme
{
    Q_OBJECT
public:
    enum RoleType
    {
        Role_StyleName = 0,
        Role_TextColor,
        Role_PanelColor,
        Role_BorderColor,
        Role_HighColor,
        Role_NormalStartColor,
        Role_NormalEndColor,
        Role_DarkStartColor,
        Role_DarkEndColor,
    };
    Q_ENUMS(RoleType)
    static const int RoleNum; //=9

    enum ThemeType
    {
        Theme_FlatWhite = 0,
        Theme_LightBlue,
        Theme_PSBlack,
    };
    Q_ENUMS(ThemeType)
    static const int ThemeNum; //=3

    explicit QEXTStyleThemeDefault(QObject *parent = 0);
    ~QEXTStyleThemeDefault();

    QString styleName() const QEXT_DECL_OVERRIDE;
    QString themeName(int type) const QEXT_DECL_OVERRIDE;

    int currentTheme() const QEXT_DECL_OVERRIDE;
    void setCurrentTheme(int type) QEXT_DECL_OVERRIDE;

    QString styleSheet() const QEXT_DECL_OVERRIDE;
    QString additionalStyle() const QEXT_DECL_OVERRIDE;
    void setAdditionalStyle(const QString &style) QEXT_DECL_OVERRIDE;
    void addAdditionalStyle(const QString &style) QEXT_DECL_OVERRIDE;

protected:
    QScopedPointer<QEXTStyleThemeDefaultPrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTStyleThemeDefault)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTStyleThemeDefault)
};

#endif // _QEXTSTYLETHEMEDEFAULT_H
