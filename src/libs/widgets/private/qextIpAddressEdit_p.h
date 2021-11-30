#ifndef _QEXTIPADDRESS_P_H
#define _QEXTIPADDRESS_P_H

#include <qextWidgetGlobal.h>

#include <QColor>
#include <QLabel>
#include <QLineEdit>

class QEXTIpAddressEdit;
class QEXT_WIDGETS_API QEXTIpAddressEditPrivate
{
    Q_DECLARE_PUBLIC(QEXTIpAddressEdit)
    Q_DISABLE_COPY(QEXTIpAddressEditPrivate)
public:
    explicit QEXTIpAddressEditPrivate(QEXTIpAddressEdit *q);
    virtual ~QEXTIpAddressEditPrivate();

    void initForm(QEXTIpAddressEdit *qq);
    void updateQSS(QEXTIpAddressEdit *qq);

    QEXTIpAddressEdit * const q_ptr;

    QLabel *m_labDot1;
    QLabel *m_labDot2;
    QLabel *m_labDot3;

    QLineEdit *m_txtIP1;
    QLineEdit *m_txtIP2;
    QLineEdit *m_txtIP3;
    QLineEdit *m_txtIP4;

    QString m_ip;
    QColor m_backgroundColor;
    QColor m_textColor;
    QColor m_dotColor;
    QColor m_borderColor;
    int m_borderRadius;
};

#endif // _QEXTIPADDRESS_P_H
