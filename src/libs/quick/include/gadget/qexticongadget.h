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

#ifndef _QEXTICONGADGET_H
#define _QEXTICONGADGET_H

#include <qextquickglobal.h>

#include <qextObject.h>

#include <QColor>
#include <QObject>



class QEXTIconGadgetPrivate;
class QEXT_QUICK_API QEXTIconGadget : public QObject, public QEXTObject
{
    Q_OBJECT

    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(int position READ position WRITE setPosition NOTIFY positionChanged)

public:
    explicit QEXTIconGadget(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTIconGadget();

    qreal width() const;
    qreal height() const;
    QColor color() const;
    qreal scale() const;
    QString source() const;
    int type() const;
    int position() const;

Q_SIGNALS:
    void widthChanged();
    void heightChanged();
    void colorChanged();
    void scaleChanged();
    void sourceChanged();
    void typeChanged(const int &type);
    void positionChanged(const int &position);

private Q_SLOTS:
    void setWidth(const qreal &width);
    void setHeight(const qreal &height);
    void setColor(const QColor &color);
    void setScale(const qreal &scale);
    void setSource(const QString &source);
    void setType(const int &type);
    void setPosition(const int &position);

private:
    QEXT_DECL_PRIVATE(QEXTIconGadget)
    QEXT_DISABLE_COPY_MOVE(QEXTIconGadget)
};



#endif // _QEXTICONGADGET_H
