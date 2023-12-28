/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2017 feiyangqingyun. Contact: QQ:517216493
** Copyright (C) 2021~Present ChengXueWen. Contact: 1398831004@qq.com
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#ifndef _QEXTIPADDRESS_P_H
#define _QEXTIPADDRESS_P_H

#include <qextIpAddressEdit.h>

#include <QColor>
#include <QLabel>
#include <QLineEdit>

class QExtIpAddressEdit;
class QEXT_WIDGETS_API QExtIpAddressEditPrivate
{
public:
    explicit QExtIpAddressEditPrivate(QExtIpAddressEdit *q);
    virtual ~QExtIpAddressEditPrivate();

    void initForm(QExtIpAddressEdit *qq);
    void updateQSS(QExtIpAddressEdit *qq);

    QExtIpAddressEdit * const q_ptr;

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

private:
    QEXT_DISABLE_COPY_MOVE(QExtIpAddressEditPrivate)
    QEXT_DECL_PUBLIC(QExtIpAddressEdit)
};

#endif // _QEXTIPADDRESS_P_H
