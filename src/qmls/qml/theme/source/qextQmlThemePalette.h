#ifndef _QEXTQMLTHEMEPALETTE_H
#define _QEXTQMLTHEMEPALETTE_H

#include <qextQmlPalette.h>
#include <qextQmlSingleton.h>
#include <qextQmlThemeGlobal.h>

class QEXT_QMLTHEME_API QExtQmlThemePalette : public QExtQmlPalette, public QExtQmlSingleton<QExtQmlThemePalette>
{
    Q_OBJECT
    QEXT_DECLARE_QML_SINGLETON(QExtQmlThemePalette)
public:
    Q_INVOKABLE QString version() const override;
};

#endif // _QEXTQMLTHEMEPALETTE_H
