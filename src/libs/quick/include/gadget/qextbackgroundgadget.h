/****************************************************************************
**
** Library: QEXTQuick
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

#ifndef QEXTBACKGROUNDGADGET_H
#define QEXTBACKGROUNDGADGET_H

#include <qextquickglobal.h>

#include <qextObject.h>

#include <QColor>
#include <QObject>



class QEXTBackgroundGadgetPrivate;
class QEXT_QUICK_API QEXTBackgroundGadget : public QObject, public QEXTObject
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)

public:
    explicit QEXTBackgroundGadget(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTBackgroundGadget();

    QColor color() const;
    qreal scale() const;
    qreal opacity() const;
    qreal radius() const;
    qreal width() const;
    qreal height() const;
    bool isVisible() const;

Q_SIGNALS:
    void scaleChanged();
    void radiusChanged();
    void colorChanged();
    void visibleChanged();
    void widthChanged();
    void heightChanged();
    void opacityChanged();

public Q_SLOTS:
    void setColor(const QColor &color);
    void setWidth(const qreal &width);
    void setHeight(const qreal &height);
    void setOpacity(const qreal &opacity);
    void setScale(const qreal &scale);
    void setRadius(const qreal &radius);
    void setVisible(const bool &visible);

private:
    QEXT_DECL_PRIVATE(QEXTBackgroundGadget)
    QEXT_DISABLE_COPY_MOVE(QEXTBackgroundGadget)
};



#endif // QEXTBACKGROUNDGADGET_H
