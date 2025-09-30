/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2024 ChengXueWen.
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

#ifndef _QEXTQMLBACKGROUNDINFO_H
#define _QEXTQMLBACKGROUNDINFO_H

#include <qextQmlGlobal.h>
#include <qextQmlRegistration.h>

#include <QColor>
#include <QObject>

class QExtQmlBackgroundInfoPrivate;
class QEXT_QML_API QExtQmlBackgroundInfo : public QObject
{
    Q_OBJECT
    QEXT_QML_ELEMENT()
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)

public:
    explicit QExtQmlBackgroundInfo(QObject *parent = QEXT_NULLPTR);
    ~QExtQmlBackgroundInfo();

    QColor color() const;
    qreal opacity() const;
    qreal radius() const;
    bool isVisible() const;

Q_SIGNALS:
    void radiusChanged();
    void colorChanged();
    void visibleChanged();
    void opacityChanged();

public Q_SLOTS:
    void setColor(const QColor &color);
    void setOpacity(const qreal &opacity);
    void setRadius(const qreal &radius);
    void setVisible(const bool &visible);

protected:
    QScopedPointer<QExtQmlBackgroundInfoPrivate> dd_ptr;

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlBackgroundInfo)
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtQmlBackgroundInfo)
};

#endif // _QEXTQMLBACKGROUNDINFO_H
