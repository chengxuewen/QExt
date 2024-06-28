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

#include <private/qextQuickKeyboard_p.h>

#include <qextOnceFlag.h>

#include <QDebug>
#include <QMutex>
#include <QQmlContext>
#include <QMutexLocker>

QExtQuickKeyboardPrivate::QExtQuickKeyboardPrivate(QExtQuickKeyboard *q)
    : q_ptr(q)
{
}

QExtQuickKeyboardPrivate::~QExtQuickKeyboardPrivate()
{
}

QExtQuickKeyboard::QExtQuickKeyboard(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQuickKeyboardPrivate(this))
{
}

QExtQuickKeyboard::~QExtQuickKeyboard()
{
}

QObject *QExtQuickKeyboard::qmlSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return QExtQuickKeyboard::instance();
}

QExtQuickKeyboard *QExtQuickKeyboard::instance()
{
    static QExtQuickKeyboard *instance = QEXT_NULLPTR;
    static QExtOnceFlag onceFlag;
    if(onceFlag.enter())
    {
        instance = new QExtQuickKeyboard;
        onceFlag.leave();
    }
    return instance;
}

QString QExtQuickKeyboard::version() const
{
    return QString("%1.%2").arg(QEXT_VERSION_MAJOR).arg(QEXT_VERSION_MINOR);
}

void QExtQuickKeyboard::registerTypes(const char *url)
{
    Q_ASSERT(url == QLatin1String(QEXT_QML_MODULE_URI));
    Q_INIT_RESOURCE(qextQuickKeyboard);

    const int major = QEXT_VERSION_MAJOR;
    const int minor = QEXT_VERSION_MINOR;

    qmlRegisterSingletonType<QExtQuickKeyboard>(url, major, minor, "QExtQuickKeyboard", QExtQuickKeyboard::qmlSingletonTypeProvider);
}

void QExtQuickKeyboard::initQmlEngine(QQmlEngine *engine, const char *uri)
{
    Q_D(QExtQuickKeyboard);
    Q_UNUSED(uri)
    d->m_qmlEngine = engine;
}

void QExtQuickKeyboard::initQuickRoot(QQuickWindow *rootWindow)
{

}
