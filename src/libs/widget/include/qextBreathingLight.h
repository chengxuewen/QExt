/***************************************************************************************************
 *@Brief:呼吸点控件
 * 1:可设置呼吸间隔
 * 2:可设置颜色透明渐变步长
 * 3:可设置背景颜色
 *@Author:chengxuewen，QQ：1398831004，Email：1398831004@qq.com,基于刘典武工程师（QQ:517216493）代码。
 *@Version:V0.1
 *@Date:2019-08-06
 *@History:
***************************************************************************************************/
#ifndef _QEXTBREATHINGLIGHT_H
#define _QEXTBREATHINGLIGHT_H

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

class QEXTBreathingLightPrivate;
class QEXT_WIDGET_API QEXTBreathingLight : public QWidget, public QEXTObject
{
    Q_OBJECT
    Q_PROPERTY(int step READ step WRITE setStep)
    Q_PROPERTY(int interval READ interval WRITE setInterval)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)

public:
    explicit QEXTBreathingLight(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTBreathingLight();

    int step() const;
    int interval() const;
    QColor backgroundColor() const;

    QSize sizeHint() const QEXT_DECL_OVERRIDE;
    QSize minimumSizeHint() const QEXT_DECL_OVERRIDE;

public slots:
    void setStep(const int &step);
    void setInterval(const int &interval);
    void setBackgroundColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *) QEXT_DECL_OVERRIDE;

    void drawBackground(QPainter *painter);

private:
    QEXT_DECL_PRIVATE(QEXTBreathingLight)
    QEXT_DISABLE_COPY_MOVE(QEXTBreathingLight)
};

#endif // _QEXTBREATHINGLIGHT_H
