#ifndef _QEXTSTYLETHEME_H
#define _QEXTSTYLETHEME_H

#include <QApplication>
#include <QObject>
#include <QWidget>

class QEXTStyleTheme
{
public:
    virtual ~QEXTStyleTheme() {}

    virtual QString styleName() const = 0;
    virtual QString themeName(int type) const = 0;

    virtual int currentTheme() const = 0;
    virtual void setCurrentTheme(int type) = 0;

    virtual QString styleSheet() const = 0;
    virtual QString additionalStyle() const = 0;
    virtual void setAdditionalStyle(const QString &style) = 0;
    virtual void addAdditionalStyle(const QString &style) = 0;
};

#endif // _QEXTSTYLETHEME_H
