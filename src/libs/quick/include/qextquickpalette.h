/****************************************************************************
**
** Library: QEXTQuick
**
** MIT License
**
** Copyright (c) 2019 toou http://www.toou.net
** Copyright (c) 2020 chengxuewen <1398831004@qq.com>
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
****************************************************************************/

#ifndef QEXTQUICKPALETTE_H
#define QEXTQUICKPALETTE_H

#include <qextquickglobal.h>

#include <qextObject.h>

#include <QObject>
#include <QColor>
#include <QPalette>
#include <QDebug>
#include <QQmlEngine>



class QEXTQuickPalettePrivate;
class QEXT_QUICK_API QEXTQuickPalette : public QObject, public QEXTObject
{
    Q_OBJECT
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
    enum BrandType {
        Brand_Primary = 0,
        Brand_Secondary,
        Brand_Accent,
        Brand_Dark,
        Brand_Positive,
        Brand_Negative,
        Brand_Info,
        Brand_Success,
        Brand_Warning,
        Brand_Danger
    };
    Q_ENUMS(BrandType)
    static const int BrandTypeNum; // = 10

    enum TextType {
        Text_Primary = 0,
        Text_Normal,
        Text_Secondary,
        Text_Placeholder
    };
    Q_ENUMS(TextType)
    static const int TextTypeNum; // = 4

    enum BorderType {
        Border_Level1 = 0,
        Border_Level2,
        Border_Level3,
        Border_Level4
    };
    Q_ENUMS(BorderType)
    static const int BorderTypeNum; // = 4

    enum ColorType {
        Color_Red = 0,
        Color_Pink,
        Color_Purple,
        Color_DeepPurple,
        Color_Indigo,
        Color_Blue,
        Color_LightBlue,
        Color_Cyan,
        Color_Teal,
        Color_Green,
        Color_LightGreen,
        Color_Lime,
        Color_Yellow,
        Color_Amber,
        Color_Orange,
        Color_DeepOrange,
        Color_Brown,
        Color_Grey,
        Color_BlueGrey,
    };
    Q_ENUMS(ColorType)
    static const int ColorTypeNum; // = 19

    enum DepthType {
        Depth_50 = 0,
        Depth_100,
        Depth_200,
        Depth_300,
        Depth_400,
        Depth_500,
        Depth_600,
        Depth_700,
        Depth_800,
        Depth_900,
        Depth_A100,
        Depth_A200,
        Depth_A400,
        Depth_A700
    };
    Q_ENUMS(DepthType)
    static const int DepthTypeNum; // = 14

    ~QEXTQuickPalette();
    static QObject *qmlSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine);
    static QEXTQuickPalette *instance();

    Q_INVOKABLE QString randomColor() const;

    Q_INVOKABLE QString brandColor(int brand) const;
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

    Q_INVOKABLE QString textColor(int textType) const;
    QString textPrimaryColor() const;
    QString textNormalColor() const;
    QString textSecondaryColor() const;
    QString textPlaceholderColor() const;

    Q_INVOKABLE QString borderColor(int borderLevel) const;
    QString borderLevel1Color() const;
    QString borderLevel2Color() const;
    QString borderLevel3Color() const;
    QString borderLevel4Color() const;

    Q_INVOKABLE QString materialColor(int color, int depth = Depth_500) const;

    Q_INVOKABLE static QString materialColorTypeName(int color);
    Q_INVOKABLE static QString materialDepthTypeName(int depth);

Q_SIGNALS:
    void brandColorChanged(int brand);
    void brandPrimaryColorChanged();
    void brandSecondaryColorChanged();
    void brandAccentColorChanged();
    void brandDarkColorChanged();
    void brandPositiveColorChanged();
    void brandNegativeColorChanged();
    void brandInfoColorChanged();
    void brandSuccessColorChanged();
    void brandWarningColorChanged();
    void brandDangerColorChanged();

    void textColorChanged(int textType);
    void textPrimaryColorChanged();
    void textNormalColorChanged();
    void textSecondaryColorChanged();
    void textPlaceholderColorChanged();

    void borderColorChanged(int borderLevel);
    void borderLevel1ColorChanged();
    void borderLevel2ColorChanged();
    void borderLevel3ColorChanged();
    void borderLevel4ColorChanged();

protected:
    explicit QEXTQuickPalette(QObject *parent = QEXT_DECL_NULLPTR);

private:
    QEXT_DECL_PRIVATE(QEXTQuickPalette)
    QEXT_DISABLE_COPY_MOVE(QEXTQuickPalette)
};



#endif // QEXTQUICKPALETTE_H
