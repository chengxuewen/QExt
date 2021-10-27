#ifndef _QEXTNUMBERLCD_P_H
#define _QEXTNUMBERLCD_P_H

#include <qextWidgetGlobal.h>
#include <qextNumberLed.h>

#include <QColor>

class QEXTNumberLed;
class QEXT_WIDGET_API QEXTNumberLedPrivate
{
public:
    explicit QEXTNumberLedPrivate(QEXTNumberLed *q);
    virtual ~QEXTNumberLedPrivate();

    QEXTNumberLed * const q_ptr;

    int m_number;                  //目标值
    int m_space;                   //间距

    QColor m_backgroundStartColor;  //背景渐变开始颜色
    QColor m_backgroundEndColor;    //背景渐变结束颜色

    QColor m_numberStartColor;      //数字渐变开始颜色
    QColor m_numberEndColor;        //数字渐变结束颜色

    QEXTNumberLed::Symbol m_symbol;

    bool m_dotVisiable;            //点显示
    bool m_colonVisiable;          //冒号显示

private:
    QEXT_DECL_PUBLIC(QEXTNumberLed)
    QEXT_DISABLE_COPY_MOVE(QEXTNumberLedPrivate)
};

#endif // _QEXTNUMBERLCD_P_H
