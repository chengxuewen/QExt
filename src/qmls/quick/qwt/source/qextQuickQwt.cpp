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

#include <private/qextQuickQwt_p.h>
#include <qextQuickQwtGlobal.h>

#include <qextOnceFlag.h>

#include <QDebug>
#include <QMutex>
#include <QQmlContext>
#include <QMutexLocker>

inline void initMyResource()
{
    Q_INIT_RESOURCE(qextQuickQwt);
}

namespace MyNamespace
{
void myFunction()
{
    initMyResource();
}
}


QExtQuickQwtPrivate::QExtQuickQwtPrivate(QExtQuickQwt *q)
    : q_ptr(q)
{
    m_mouseAreaCurrsor = Qt::ArrowCursor;
}

QExtQuickQwtPrivate::~QExtQuickQwtPrivate()
{

}


QExtQuickQwt::QExtQuickQwt(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQuickQwtPrivate(this))
{

}

QExtQuickQwt::~QExtQuickQwt()
{

}

QObject *QExtQuickQwt::qmlSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return QExtQuickQwt::instance();
}

QExtQuickQwt *QExtQuickQwt::instance()
{
    static QExtQuickQwt *instance = QEXT_NULLPTR;
    static QExtOnceFlag onceFlag;
    if(onceFlag.enter())
    {
        instance = new QExtQuickQwt;
        onceFlag.leave();
    }
    return instance;
}

QString QExtQuickQwt::version() const
{
    return QString("%1.%2").arg(QEXT_VERSION_MAJOR).arg(QEXT_VERSION_MINOR);
}

void QExtQuickQwt::registerTypes(const char *url)
{
    Q_ASSERT(url == QLatin1String(QEXT_QML_MODULE_URI));
    Q_INIT_RESOURCE(qextQuickQwt);

    const int major = QEXT_VERSION_MAJOR;
    const int minor = QEXT_VERSION_MINOR;

    qmlRegisterSingletonType<QExtQuickQwt>(url, major, minor, "QExtQuickQwt", QExtQuickQwt::qmlSingletonTypeProvider);
}

void QExtQuickQwt::initQmlEngine(QQmlEngine *engine, const char *uri)
{
    Q_D(QExtQuickQwt);
    Q_UNUSED(uri)
    d->m_qmlEngine = engine;
}

void QExtQuickQwt::initQuickRoot(QQuickWindow *rootWindow)
{

}

int QExtQuickQwt::mouseAreaCursorShape() const
{
    Q_D(const QExtQuickQwt);
    return (int)d->m_mouseAreaCurrsor;
}

void QExtQuickQwt::setMouseAreaCursorShape(const Qt::CursorShape &cursor)
{
    Q_D(QExtQuickQwt);
    d->m_mouseAreaCurrsor = cursor;
}
