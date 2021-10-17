/***************************************************************************************************
 *@Brief:字模提取控件
 * 1:可设置字模文字
 * 2:可设置字体名称及字号
 * 3:可设置步长间隔
 * 4:可设置前景色
 *@Author:chengxuewen，QQ：1398831004，Email：1398831004@qq.com
 *@Version:V0.1
 *@Date:2019-08-02
 *@History:
***************************************************************************************************/
#ifndef _QEXTTEXTLCD_H
#define _QEXTTEXTLCD_H

#include <qextWidgetGlobal.h>

#include <qextObject.h>

#ifndef Q_WS_QWS
    #if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
        #include <QtDesigner/QDesignerExportWidget>
    #else
        #include <QtUiPlugin/QDesignerExportWidget>
    #endif
#endif

#include <QWidget>
#include <QObject>

class QEXTTextLcdPrivate;
class QEXT_WIDGET_API QEXTTextLcd : public QWidget, public QEXTObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(int textAlignment READ textAlignment WRITE setTextAlignment)

    Q_PROPERTY(int fontPixelSize READ fontPixelSize WRITE setFontPixelSize)
    Q_PROPERTY(int rowCount READ rowCount WRITE setRowCount)
    Q_PROPERTY(double spaceFactory READ spaceFactory WRITE setSpaceFactory)
    Q_PROPERTY(bool isHighLightBorderEnable READ isHighLightBorderEnable WRITE setHighLightBorderEnable)

    Q_PROPERTY(Animation animationType READ animationType WRITE setAnimationType)
    Q_PROPERTY(int animationInterval READ animationInterval WRITE setAnimationInterval)

    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)

public:
    enum Animation {
        Animation_Static = 0,
        Animation_LeftToRight,
        Animation_RightToLeft,
        Animation_TopToBottom,
        Animation_BottomToTop
    };
    Q_ENUMS(Animation)

public:
    explicit QEXTTextLcd(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTTextLcd();

    QString text() const;
    int textAlignment() const;

    int fontPixelSize() const;
    int rowCount() const;
    double spaceFactory() const;
    bool isHighLightBorderEnable() const;

    Animation animationType() const;
    int animationInterval() const;

    QColor textColor() const;
    QColor foregroundColor() const;
    QColor backgroundColor() const;

    QSize sizeHint() const QEXT_DECL_OVERRIDE;
    QSize minimumSizeHint() const QEXT_DECL_OVERRIDE;

public Q_SLOTS:
    void setText(const QString &strText);

    void setTextAlignment(const int &iAlign);

    void setFontPixelSize(const int &iSize);
    void setRowCount(const int &iCount);
    void setSpaceFactory(const double &dFac);
    void setHighLightBorderEnable(const bool &bEnable);

    void setAnimationType(const Animation &eType);
    void setAnimationInterval(const int &iInterval);

    void setTextColor(const QColor &color);
    void setForegroundColor(const QColor &color);
    void setBackgroundColor(const QColor &color);

protected Q_SLOTS:
    void updateOffsetValue();

protected:
    void paintEvent(QPaintEvent *) QEXT_DECL_OVERRIDE;

private:
    QEXT_DECL_PRIVATE(QEXTTextLcd)
    QEXT_DISABLE_COPY_MOVE(QEXTTextLcd)
};

#endif // _QEXTTEXTLCD_H
