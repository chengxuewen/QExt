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

#include <qextQuickQwt.h>
#include <qextQuickQwtPlot.h>

#include <qextOnceFlag.h>

#include <QDebug>
#include <QMutex>
#include <QQmlContext>
#include <QMutexLocker>

class QExtQuickQwtWorld;
class QExtQuickQwtPrivate
{
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQuickQwtPrivate)
    QEXT_DECLARE_PUBLIC(QExtQuickQwt)
public:
    explicit QExtQuickQwtPrivate(QExtQuickQwt *q);
    virtual ~QExtQuickQwtPrivate();

    QExtQuickQwt * const q_ptr;
};

QExtQuickQwtPrivate::QExtQuickQwtPrivate(QExtQuickQwt *q)
    : q_ptr(q)
{
}

QExtQuickQwtPrivate::~QExtQuickQwtPrivate()
{
}

QExtQuickQwt::QExtQuickQwt()
    : dd_ptr(new QExtQuickQwtPrivate(this))
{
}

QExtQuickQwt::~QExtQuickQwt()
{
}

QString QExtQuickQwt::version() const
{
    return QString("%1.%2").arg(QEXT_VERSION_MAJOR).arg(QEXT_VERSION_MINOR);
}

void QExtQuickQwt::registerTypes(const char *url)
{
    qDebug() << QString("QExtQuickQwt::registerTypes(%1)").arg(QEXT_QML_MODULE_URI);
    if (url)
    {
        Q_ASSERT(url == QLatin1String(QEXT_QML_MODULE_URI));
    }
    static QExtOnceFlag onceFlag;
    if (onceFlag.enter())
    {
        Q_INIT_RESOURCE(qextQuickQwt);
        const int major = QEXT_VERSION_MAJOR;
        const int minor = QEXT_VERSION_MINOR;

        qmlRegisterSingletonType<QExtQuickQwt>(QEXT_QML_MODULE_URI, major, minor, "QExtQuickQwt",
                                               QExtQuickQwt::create);

        qmlRegisterType<QExtQuickQwtPlot>(QEXT_QML_MODULE_URI, major, minor, "QExtQuickQwtPlot");
        onceFlag.leave();
    }
}

void QExtQuickQwt::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(engine)
    Q_UNUSED(uri)
}
