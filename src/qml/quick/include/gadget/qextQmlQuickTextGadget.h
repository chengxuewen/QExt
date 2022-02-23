/****************************************************************************
**
** Library: QEXTQmlQuick
**
** MIT License
**
** Copyright (c) 2019 toou http://www.toou.net
** Copyright (c) 2020 chengxuewen <1398831004@qq.com>
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
****************************************************************************/

#ifndef _QEXTQMLQUICKTEXTGADGET_H
#define _QEXTQMLQUICKTEXTGADGET_H

#include <qextQmlQuickGlobal.h>

#include <QColor>
#include <QFont>
#include <QObject>

class QEXTQmlQuickTextGadgetPrivate;
class QEXT_QUICK_API QEXTQmlQuickTextGadget : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTQmlQuickTextGadget)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTQmlQuickTextGadget)

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)

public:
    explicit QEXTQmlQuickTextGadget(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTQmlQuickTextGadget();

    QString text() const;
    QColor color() const;
    qreal scale() const;
    QFont font() const;
    int fontSize() const;

Q_SIGNALS:
    void textChanged();
    void colorChanged();
    void scaleChanged();
    void fontChanged();
    void fontSizeChanged(const int &size);

public Q_SLOTS:
    void setText(const QString &text);
    void setColor(const QColor &color);
    void setScale(const qreal &scale);
    void setFont(const QFont &font);
    void setFontSize(const int &size);

protected:
    QScopedPointer<QEXTQmlQuickTextGadgetPrivate> dd_ptr;
};

#endif // _QEXTQMLQUICKTEXTGADGET_H
