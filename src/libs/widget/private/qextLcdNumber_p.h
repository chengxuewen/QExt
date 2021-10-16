#ifndef _QEXTLCDNUMBER_P_H
#define _QEXTLCDNUMBER_P_H

#include <qextWidgetGlobal.h>
#include <qextLcdNumber.h>

#include <qextObject_p.h>

#include <QColor>

class QEXTLcdNumber;
class QEXT_WIDGET_API QEXTLcdNumberPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTLcdNumberPrivate(QEXTLcdNumber *qq);
    ~QEXTLcdNumberPrivate();

    int m_number;                  //目标值
    int m_space;                   //间距

    QColor m_backgroundStartColor;  //背景渐变开始颜色
    QColor m_backgroundEndColor;    //背景渐变结束颜色

    QColor m_numberStartColor;      //数字渐变开始颜色
    QColor m_numberEndColor;        //数字渐变结束颜色

    QEXTLcdNumber::Symbol m_symbol;

    bool m_dotVisiable;            //点显示
    bool m_colonVisiable;          //冒号显示

private:
    QEXT_DECL_PUBLIC(QEXTLcdNumber)
    QEXT_DISABLE_COPY_MOVE(QEXTLcdNumberPrivate)
};

#endif // _QEXTLCDNUMBER_P_H
