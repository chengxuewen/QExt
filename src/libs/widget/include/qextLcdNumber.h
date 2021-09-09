/***************************************************************************************************
 *@Brief:LCD数字控件
 * 1:可设置目标值和间隔
 * 2:可设置背景颜色和数字颜色
 * 3:可设置显示点、冒号
 *@Author:chengxuewen，QQ：1398831004，Email：1398831004@qq.com,基于刘典武工程师（QQ:517216493）代码。
 *@Version:V0.1
 *@Date:2019-08-02
 *@History:
***************************************************************************************************/
#ifndef QEXTLCDNUMBER_H
#define QEXTLCDNUMBER_H

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

class QEXTLcdNumberPrivate;
class QEXT_WIDGET_API QEXTLcdNumber : public QWidget, public QEXTObject
{
    Q_OBJECT
    Q_PROPERTY(int number READ number WRITE setNumber)
    Q_PROPERTY(int space READ space WRITE setSpace)

    Q_PROPERTY(QColor backgroundStartColor READ backgroundStartColor WRITE setBackgroundStartColor)
    Q_PROPERTY(QColor backgroundEndColor READ backgroundEndColor WRITE setBackgroundEndColor)

    Q_PROPERTY(QColor numberStartColor READ numberStartColor WRITE setNumberStartColor)
    Q_PROPERTY(QColor numberEndColor READ numberEndColor WRITE setNumberEndColor)

    Q_PROPERTY(Symbol symbolType READ symbolType WRITE setSymbolType)
public:
    enum Symbol {
        Symbol_None = 0,    //0-无符号
        Symbol_Dot,         //1-点
        Symbol_Colon,       //2-冒号
        Symbol_Line         //3-划线
    };
    Q_ENUMS(Symbol)

public:
    explicit QEXTLcdNumber(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTLcdNumber();

    int number() const;
    int space() const;

    QColor backgroundStartColor() const;
    QColor backgroundEndColor() const;

    QColor numberStartColor() const;
    QColor numberEndColor() const;

    Symbol symbolType() const;

    QSize sizeHint() const QEXT_DECL_OVERRIDE;
    QSize minimumSizeHint() const QEXT_DECL_OVERRIDE;

public Q_SLOTS:
    //设置值
    void setNumber(int number);
    //设置间距
    void setSpace(int space);

    //设置背景颜色
    void setBackgroundStartColor(const QColor &color);
    void setBackgroundEndColor(const QColor &color);

    //设置数字颜色
    void setNumberStartColor(const QColor &color);
    void setNumberEndColor(const QColor &color);

    void setSymbolType(const Symbol &type);

protected:
    void paintEvent(QPaintEvent *) QEXT_DECL_OVERRIDE;

    void drawBackground(QPainter *painter);
    void drawNumber(QPainter *painter);

private:
    QEXT_DECL_PRIVATE(QEXTLcdNumber)
    QEXT_DISABLE_COPY_MOVE(QEXTLcdNumber)
};

#endif // QEXTLCDNUMBER_H
