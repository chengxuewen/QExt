#ifndef _QEXTQMLTHEMEPALETTE_H
#define _QEXTQMLTHEMEPALETTE_H

#include <qextQmlPalette.h>
#include <qextQmlSingleton.h>

class QExtQmlThemePalette : public QExtQmlPalette, public QExtQmlSingleton<QExtQmlThemePalette>
{
    Q_OBJECT
    QEXT_DECLARE_QML_SINGLETON(QExtQmlThemePalette)
public:
    Q_INVOKABLE QString version() const override;
};

#endif // _QEXTQMLTHEMEPALETTE_H
