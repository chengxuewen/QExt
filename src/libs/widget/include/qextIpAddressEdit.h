#ifndef _QEXTIPADDRESS_H
#define _QEXTIPADDRESS_H

#include <qextWidgetGlobal.h>

/**
 * IP地址输入框控件 作者:feiyangqingyun(QQ:517216493) 2017-8-11
 * 1:可设置IP地址,自动填入框
 * 2:可清空IP地址
 * 3:支持按下小圆点自动切换
 * 4:支持退格键自动切换
 * 5:支持IP地址过滤
 * 6:可设置背景色/边框颜色/边框圆角角度
 */

#include <QWidget>

class QEXTIpAddressEditPrivate;
class QEXT_WIDGET_API QEXTIpAddressEdit : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString iP READ iP WRITE setIP NOTIFY ipChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor dotColor READ dotColor WRITE setDotColor)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
    Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius)

public:
    explicit QEXTIpAddressEdit(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTIpAddressEdit();

    QString iP() const;
    QColor backgroundColor() const;
    QColor textColor() const;
    QColor dotColor() const;
    QColor borderColor() const;
    int borderRadius() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    void setIP(const QString &ip);
    void clear();

    void setBackgroundColor(const QColor &color);
    void setTextColor(const QColor &color);
    void setDotColor(const QColor &color);
    void setBorderColor(const QColor &color);
    void setBorderRadius(int radius);

signals:
    void ipChanged(const QString &ip);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

    QScopedPointer<QEXTIpAddressEditPrivate> d_ptr;

private Q_SLOTS:
    void textChanged(const QString &text);

private:
    QEXT_DECL_PRIVATE(QEXTIpAddressEdit)
    QEXT_DECL_DISABLE_COPY(QEXTIpAddressEdit)
};

#endif // _QEXTIPADDRESS_H
