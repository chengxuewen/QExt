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

#include <private/qextQmlWorld_p.h>
#include <qextQml.h>

QExtQmlWorldPrivate::QExtQmlWorldPrivate(QExtQmlWorld *q)
    : q_ptr(q)
{

}

QExtQmlWorldPrivate::~QExtQmlWorldPrivate()
{

}



QExtQmlWorld::QExtQmlWorld(QQuickItem *parent)
    : QQuickItem(parent)
    , dd_ptr(new QExtQmlWorldPrivate(this))
{
    static bool inited = false;
    if(inited)
    {
        qErrnoWarning("Error:There is only one world :)");
    }
    else
    {
        inited = true;
        this->setVisible(false);
        this->setEnabled(false);
        connect(this, SIGNAL(parentChanged(QQuickItem *)), this, SLOT(onParentChanged(QQuickItem *)));
    }
}

QExtQmlWorld::~QExtQmlWorld()
{

}


int QExtQmlWorld::mouseAreaCursorShape() const
{
    return QExtQml::instance()->mouseAreaCursorShape();
}

void QExtQmlWorld::setMouseAreaCursorShape(int shape)
{
    QExtQml::instance()->setMouseAreaCursorShape((Qt::CursorShape)shape);
    emit this->mouseAreaCursorShapeChanged(shape);
}

void QExtQmlWorld::onParentChanged(QQuickItem *parent)
{
    Q_UNUSED(parent);
    QExtQml::instance()->initQuickRoot(dynamic_cast<QQuickWindow *>(this->parent()));
    QExtQml::instance()->initWorld(this);
    disconnect(this, SIGNAL(parentChanged(QQuickItem *)), this, SLOT(onParentChanged(QQuickItem *)));
}
