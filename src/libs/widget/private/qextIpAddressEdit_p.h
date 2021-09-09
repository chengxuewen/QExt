#ifndef QEXTIPADDRESS_P_H
#define QEXTIPADDRESS_P_H

#include <qextWidgetGlobal.h>

#include <qextObject_p.h>

#include <QColor>
#include <QLabel>
#include <QLineEdit>

class QEXTIpAddressEdit;
class QEXT_WIDGET_API QEXTIpAddressEditPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTIpAddressEditPrivate(QEXTIpAddressEdit *qq);
    ~QEXTIpAddressEditPrivate();

    void initForm(QEXTIpAddressEdit *qq);
    void updateQSS(QEXTIpAddressEdit *qq);

    QLabel *m_labDot1;    //第一个小圆点
    QLabel *m_labDot2;    //第二个小圆点
    QLabel *m_labDot3;    //第三个小圆点

    QLineEdit *m_txtIP1;  //IP地址网段输入框1
    QLineEdit *m_txtIP2;  //IP地址网段输入框2
    QLineEdit *m_txtIP3;  //IP地址网段输入框3
    QLineEdit *m_txtIP4;  //IP地址网段输入框4

    QString m_ip;
    QColor m_backgroundColor;
    QColor m_textColor;
    QColor m_dotColor;
    QColor m_borderColor;
    int m_borderRadius;

private:
    QEXT_DECL_PUBLIC(QEXTIpAddressEdit)
    QEXT_DISABLE_COPY_MOVE(QEXTIpAddressEditPrivate)
};

#endif // QEXTIPADDRESS_P_H
