#ifndef _QEXTTUMBLER_P_H
#define _QEXTTUMBLER_P_H

#include <qextWidgetGlobal.h>

#include <QStringList>
#include <QColor>

class QEXTTumbler;
class QEXT_WIDGETS_API QEXTTumblerPrivate
{
public:
    explicit QEXTTumblerPrivate(QEXTTumbler *q);
    virtual ~QEXTTumblerPrivate();

    QEXTTumbler * const q_ptr;

    QStringList m_valueList;          //值队列
    int m_currentIndex;               //当前索引
    QString m_currentValue;           //当前值
    bool m_isHorizontal;                //是否横向显示

    QColor m_foregroundColor;              //前景色
    QColor m_backgroundColor;              //背景色
    QColor m_lineColor;               //线条颜色
    QColor m_textColor;               //当前文本颜色

    int m_percent;                    //比例
    int m_offset;                     //偏离值
    bool m_pressed;                   //鼠标是否按下
    int m_pressedPos;                 //按下处坐标
    int m_currentPos;                 //当前值对应起始坐标

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTTumblerPrivate)
    Q_DECLARE_PUBLIC(QEXTTumbler)
};

#endif // _QEXTTUMBLER_P_H
