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

#ifndef _QEXTQMLPADDING_H
#define _QEXTQMLPADDING_H

#include <qextQmlGlobal.h>
#include <qextQmlRegistration.h>

#include <QObject>

class QExtQmlPaddingPrivate;
class QEXT_QML_API QExtQmlPadding : public QObject
{
    Q_OBJECT
    QEXT_QML_ELEMENT()
    Q_PROPERTY(double padding WRITE setPadding)
    Q_PROPERTY(double topPadding READ topPadding WRITE setTopPadding NOTIFY topPaddingChanged)
    Q_PROPERTY(double leftPadding READ leftPadding WRITE setLeftPadding NOTIFY leftPaddingChanged)
    Q_PROPERTY(double rightPadding READ rightPadding WRITE setRightPadding NOTIFY rightPaddingChanged)
    Q_PROPERTY(double bottomPadding READ bottomPadding WRITE setBottomPadding NOTIFY bottomPaddingChanged)
public:
    explicit QExtQmlPadding(QObject *parent = QEXT_NULLPTR);
    QExtQmlPadding(double padding, QObject *parent = QEXT_NULLPTR);
    ~QExtQmlPadding() QEXT_OVERRIDE;

    double topPadding() const;
    double leftPadding() const;
    double rightPadding() const;
    double bottomPadding() const;

Q_SIGNALS:
    void topPaddingChanged(double padding);
    void leftPaddingChanged(double padding);
    void rightPaddingChanged(double padding);
    void bottomPaddingChanged(double padding);

public Q_SLOTS:
    Q_INVOKABLE void setPadding(double padding);
    Q_INVOKABLE void setTopPadding(double padding);
    Q_INVOKABLE void setLeftPadding(double padding);
    Q_INVOKABLE void setRightPadding(double padding);
    Q_INVOKABLE void setBottomPadding(double padding);

protected:
    QScopedPointer<QExtQmlPaddingPrivate> dd_ptr;

private:
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtQmlPadding)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlPadding)
};

#endif // _QEXTQMLPADDING_H
