/****************************************************************************
**
** Library: QEXTQmlQuick
**
** MIT License
**
** Copyright (c) 2019 toou http://www.toou.net
** Copyright (c) 2021 chengxuewen <1398831004@qq.com>
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

#include "qextQmlQuickFontAwesome.h"

#include <QDebug>
#include <QMutex>
#include <QMutexLocker>
#include <QFontDatabase>

static QEXTQmlQuickFontAwesome *sg_insrance = nullptr;

QEXTQmlQuickFontAwesome::~QEXTQmlQuickFontAwesome()
{

}

QObject *QEXTQmlQuickFontAwesome::qmlSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return QEXTQmlQuickFontAwesome::instance();
}

QEXTQmlQuickFontAwesome *QEXTQmlQuickFontAwesome::instance()
{
    static QMutex mutex;
    QMutexLocker mutexLocker(&mutex);
    if (nullptr == sg_insrance) {
        sg_insrance = new QEXTQmlQuickFontAwesome;
    }
    return sg_insrance;
}

int QEXTQmlQuickFontAwesome::maiorVersion()
{
    return 4;
}

int QEXTQmlQuickFontAwesome::minorVersion()
{
    return 7;
}

QString QEXTQmlQuickFontAwesome::version() const
{
    return QString("%1.%2").arg(this->maiorVersion()).arg(this->minorVersion());
}

QString QEXTQmlQuickFontAwesome::awesomeFromKey(const QString &key)
{
    if(!key.isEmpty()) {
        int index = this->staticMetaObject.indexOfEnumerator("FontAwesomeType");

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
        return QChar(this->staticMetaObject.enumerator(index).keysToValue(key.toStdString().c_str()));
#else
        return QString(this->staticMetaObject.enumerator(index).keysToValue(key.toStdString().c_str()));
#endif
    }
    return QString();
}

QString QEXTQmlQuickFontAwesome::awesomeFromValue(const int &type)
{
    return QChar(type);
}

QStringList QEXTQmlQuickFontAwesome::awesomelist()
{
    QMetaEnum enumType = QEXTQmlQuickFontAwesome::staticMetaObject.enumerator(QEXTQmlQuickFontAwesome::staticMetaObject.indexOfEnumerator("FontAwesomeType"));
    QStringList list;
    for(int i = 0; i < enumType.keyCount(); ++i){
        list.append(enumType.key(i)); //enumType.value(i)
    }
    return list;
}

QEXTQmlQuickFontAwesome::QEXTQmlQuickFontAwesome(QObject *parent)
    : QObject(parent)
{
    QFontDatabase::addApplicationFont(":/Font/fontawesome-webfont.ttf");
}
