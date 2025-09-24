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

#include <qextQmlFontAwesome.h>
#include <qextOnceFlag.h>
#include <qextQml.h>

QExtQmlFontAwesome::~QExtQmlFontAwesome()
{

}

QEXT_QML_SINGLETON_TYPE(QExtQmlFontAwesome) *QExtQmlFontAwesome::create(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return QExtQmlFontAwesome::instance();
}

QExtQmlFontAwesome *QExtQmlFontAwesome::instance()
{
    static QExtQmlFontAwesome *instance = QEXT_NULLPTR;
    static QExtOnceFlag onceFlag;
    if(onceFlag.enter())
    {
        instance = new QExtQmlFontAwesome;
        onceFlag.leave();
    }
    return instance;
}

QString QExtQmlFontAwesome::fontUrl(int value) const
{
    return QExtQml::instance()->fontIconUrl(this->fontName(), this->textFromValue(value));
}

QString QExtQmlFontAwesome::fontUrl(const QString &key) const
{
    return QExtQml::instance()->fontIconUrl(this->fontName(), this->textFromKey(key));
}

QExtQmlFontAwesome::QExtQmlFontAwesome(QObject *parent)
    : QExtFontAwesome(parent)
{

}
