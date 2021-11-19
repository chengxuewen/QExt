#ifndef _QEXTDATETIMETUMBLER_H
#define _QEXTDATETIMETUMBLER_H

/***************************************************************************************************
 *@Brief:日期时间滑动选择器
 *  1.可设置年月日时分秒
 *  2.可鼠标或者手指滑动选择年月日时分秒
 *  3.支持自定义数值范围
 *  4.支持鼠标滚轮选择
 *  5.年月日自动联动计算
 *@Author:chengxuewen，QQ：1398831004，Email：1398831004@qq.com，基于刘典武（QQ:517216493）代码。
 *@Date:2017-08-11
 *@History:
 *  Modification data:2021-10-15
 *  Author:chengxuewen
 *  Brief:1.整理优化;
***************************************************************************************************/

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QDateTime>

class QEXTTumbler;
class QEXTDateTimeTumblerPrivate;
class QEXT_WIDGETS_API QEXTDateTimeTumbler : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int year READ year WRITE setYear)
    Q_PROPERTY(int month READ month WRITE setMonth)
    Q_PROPERTY(int day READ day WRITE setDay)

    Q_PROPERTY(int hour READ hour WRITE setHour)
    Q_PROPERTY(int min READ min WRITE setMin)
    Q_PROPERTY(int sec READ sec WRITE setSec)

public:
    explicit QEXTDateTimeTumbler(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTDateTimeTumbler();

    //获取年份
    int year() const;
    //获取月份
    int month() const;
    //获取日期
    int day() const;

    //获取时钟
    int hour() const;
    //获取分钟
    int min() const;
    //获取秒钟
    int sec() const;

public Q_SLOTS:
    //设置年份
    void setYear(int year);

    //设置月份
    void setMonth(int month);

    //设置日期
    void setDay(int day);

    //设置时钟
    void setHour(int hour);

    //设置分钟
    void setMin(int min);

    //设置秒钟
    void setSec(int sec);

    //设置年月日
    void setDateTime(int year, int month, int day, int hour, int min, int sec);

protected Q_SLOTS:
    void currentValueChanged(const QString &);

protected:
    void initForm();
    QScopedPointer<QEXTDateTimeTumblerPrivate> d_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTDateTimeTumbler)
    Q_DECLARE_PRIVATE(QEXTDateTimeTumbler)
};

#endif // _QEXTDATETIMETUMBLER_H
