/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2021 ChengXueWen.
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#ifndef _QEXTQMLPALETTE_H
#define _QEXTQMLPALETTE_H

#include <qextQmlGlobal.h>
#include <qextQmlRegistration.h>

#include <QDebug>
#include <QColor>
#include <QObject>
#include <QPalette>
#include <QQmlEngine>

class QExtQmlPalettePrivate;
class QEXT_QML_API QExtQmlPalette : public QObject
{
    Q_OBJECT
    QEXT_QML_ELEMENT()
    Q_PROPERTY(QString brandPrimaryColor READ brandPrimaryColor NOTIFY brandPrimaryColorChanged)
    Q_PROPERTY(QString brandSecondaryColor READ brandSecondaryColor NOTIFY brandSecondaryColorChanged)
    Q_PROPERTY(QString brandAccentColor READ brandAccentColor NOTIFY brandAccentColorChanged)
    Q_PROPERTY(QString brandDarkColor READ brandDarkColor NOTIFY brandDarkColorChanged)
    Q_PROPERTY(QString brandPositiveColor READ brandPositiveColor NOTIFY brandPositiveColorChanged)
    Q_PROPERTY(QString brandNegativeColor READ brandNegativeColor NOTIFY brandNegativeColorChanged)
    Q_PROPERTY(QString brandInfoColor READ brandInfoColor NOTIFY brandInfoColorChanged)
    Q_PROPERTY(QString brandSuccessColor READ brandSuccessColor NOTIFY brandSuccessColorChanged)
    Q_PROPERTY(QString brandWarningColor READ brandWarningColor NOTIFY brandWarningColorChanged)
    Q_PROPERTY(QString brandDangerColor READ brandDangerColor NOTIFY brandDangerColorChanged)

    Q_PROPERTY(QString textPrimaryColor READ textPrimaryColor NOTIFY textPrimaryColorChanged)
    Q_PROPERTY(QString textNormalColor READ textNormalColor NOTIFY textNormalColorChanged)
    Q_PROPERTY(QString textSecondaryColor READ textSecondaryColor NOTIFY textSecondaryColorChanged)
    Q_PROPERTY(QString textPlaceholderColor READ textPlaceholderColor NOTIFY textPlaceholderColorChanged)

    Q_PROPERTY(QString borderLevel1Color READ borderLevel1Color NOTIFY borderLevel1ColorChanged)
    Q_PROPERTY(QString borderLevel2Color READ borderLevel2Color NOTIFY borderLevel2ColorChanged)
    Q_PROPERTY(QString borderLevel3Color READ borderLevel3Color NOTIFY borderLevel3ColorChanged)
    Q_PROPERTY(QString borderLevel4Color READ borderLevel4Color NOTIFY borderLevel4ColorChanged)

public:
    enum BrandEnum
    {
        BrandPrimary = 0,
        BrandSecondary,
        BrandAccent,
        BrandDark,
        BrandPositive,
        BrandNegative,
        BrandInfo,
        BrandSuccess,
        BrandWarning,
        BrandDanger
    };
    Q_ENUM(BrandEnum)
    QEXT_STATIC_CONSTANT_NUMBER(BrandEnumCount, 10)

    enum TextEnum
    {
        TextPrimary = 0,
        TextNormal,
        TextSecondary,
        TextPlaceholder
    };
    Q_ENUM(TextEnum)
    QEXT_STATIC_CONSTANT_NUMBER(TextEnumCount, 4)

    enum BorderLevelEnum
    {
        BorderLevel1 = 0,
        BorderLevel2,
        BorderLevel3,
        BorderLevel4
    };
    Q_ENUM(BorderLevelEnum)
    QEXT_STATIC_CONSTANT_NUMBER(BorderLevelEnumCount, 4)

    enum ColorEnum
    {
        ColorRed = 0,
        ColorPink,
        ColorPurple,
        ColorDeepPurple,
        ColorIndigo,
        ColorBlue,
        ColorLightBlue,
        ColorCyan,
        ColorTeal,
        ColorGreen,
        ColorLightGreen,
        ColorLime,
        ColorYellow,
        ColorAmber,
        ColorOrange,
        ColorDeepOrange,
        ColorBrown,
        ColorGrey,
        ColorBlueGrey,
    };
    Q_ENUM(ColorEnum)
    QEXT_STATIC_CONSTANT_NUMBER(ColorEnumCount, 19)

    enum DepthEnum
    {
        Depth50 = 0,
        Depth100,
        Depth200,
        Depth300,
        Depth400,
        Depth500,
        Depth600,
        Depth700,
        Depth800,
        Depth900,
        DepthA100,
        DepthA200,
        DepthA400,
        DepthA700
    };
    Q_ENUM(DepthEnum)
    QEXT_STATIC_CONSTANT_NUMBER(DepthEnumCount, 14)

    explicit QExtQmlPalette(QObject *parent = QEXT_NULLPTR);
    ~QExtQmlPalette() override;

    Q_INVOKABLE QColor randomColor() const;

    Q_INVOKABLE QColor brandColor(int brand) const;
    QString brandPrimaryColor() const;
    QString brandSecondaryColor() const;
    QString brandAccentColor() const;
    QString brandDarkColor() const;
    QString brandPositiveColor() const;
    QString brandNegativeColor() const;
    QString brandInfoColor() const;
    QString brandSuccessColor() const;
    QString brandWarningColor() const;
    QString brandDangerColor() const;

    Q_INVOKABLE QColor textColor(int text) const;
    QString textPrimaryColor() const;
    QString textNormalColor() const;
    QString textSecondaryColor() const;
    QString textPlaceholderColor() const;

    Q_INVOKABLE QColor borderColor(int level) const;
    QString borderLevel1Color() const;
    QString borderLevel2Color() const;
    QString borderLevel3Color() const;
    QString borderLevel4Color() const;

    Q_INVOKABLE QColor materialColor(int color, int depth = Depth500) const;

    Q_INVOKABLE static QString materialColorTypeName(int color);
    Q_INVOKABLE static QString materialDepthTypeName(int depth);

Q_SIGNALS:
    void brandColorChanged(int brand, const QColor &color);
    void brandPrimaryColorChanged(const QColor &color);
    void brandSecondaryColorChanged(const QColor &color);
    void brandAccentColorChanged(const QColor &color);
    void brandDarkColorChanged(const QColor &color);
    void brandPositiveColorChanged(const QColor &color);
    void brandNegativeColorChanged(const QColor &color);
    void brandInfoColorChanged(const QColor &color);
    void brandSuccessColorChanged(const QColor &color);
    void brandWarningColorChanged(const QColor &color);
    void brandDangerColorChanged(const QColor &color);

    void textColorChanged(int type, const QColor &color);
    void textPrimaryColorChanged(const QColor &color);
    void textNormalColorChanged(const QColor &color);
    void textSecondaryColorChanged(const QColor &color);
    void textPlaceholderColorChanged(const QColor &color);

    void borderColorChanged(int level, const QColor &color);
    void borderLevel1ColorChanged(const QColor &color);
    void borderLevel2ColorChanged(const QColor &color);
    void borderLevel3ColorChanged(const QColor &color);
    void borderLevel4ColorChanged(const QColor &color);

public Q_SLOTS:
    void setBorderColor(int level, const QColor &color);
    void setBrandColor(int brand, const QColor &color);
    void setTextColor(int text, const QColor &color);

protected:
    QScopedPointer<QExtQmlPalettePrivate> dd_ptr;

private:
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtQmlPalette)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlPalette)
};

#endif // _QEXTQMLPALETTE_H
