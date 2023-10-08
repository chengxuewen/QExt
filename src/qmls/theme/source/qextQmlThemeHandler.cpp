/****************************************************************************
**
** Library: QEXTQmlQuick
**
** MIT License
**
** Copyright (c) 2021 chengxuewen <1398831004@qq.com>
** Copyright (c) 2019 toou http://www.toou.net
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

#include <qextQmlThemeHandler.h>
#include <qextQmlThemeHandler_p.h>
#include <qextQmlThemeBinder.h>
#include <qextQmlThemeConstant.h>

#include <QVariantMap>
#include <QDebug>
#include <QFile>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTextStream>

QEXTQmlThemeHandlerPrivate::QEXTQmlThemeHandlerPrivate(QEXTQmlThemeHandler *q)
    : q_ptr(q)
{
    m_valid = false;
}

QEXTQmlThemeHandlerPrivate::~QEXTQmlThemeHandlerPrivate()
{

}



QEXTQmlThemeHandler::QEXTQmlThemeHandler(const QString &name, const QString &path)
    : QObject()
    , dd_ptr(new QEXTQmlThemeHandlerPrivate(this))
{
    Q_D(QEXTQmlThemeHandler);
    d->m_name = name;
    d->m_path = path;
}

QEXTQmlThemeHandler::~QEXTQmlThemeHandler()
{

}

QString QEXTQmlThemeHandler::themeName() const
{
    Q_D(const QEXTQmlThemeHandler);
    return d->m_name;
}

QString QEXTQmlThemeHandler::themePath() const
{
    Q_D(const QEXTQmlThemeHandler);
    return d->m_path;
}

QString QEXTQmlThemeHandler::lastErrorString() const
{
    Q_D(const QEXTQmlThemeHandler);
    return d->m_lastErrorString;
}

bool QEXTQmlThemeHandler::isValid() const
{
    Q_D(const QEXTQmlThemeHandler);
    return d->m_valid;
}

bool QEXTQmlThemeHandler::isLoad() const
{
    Q_D(const QEXTQmlThemeHandler);
    return !d->m_themeDataMap.isEmpty();
}

QVariant QEXTQmlThemeHandler::propertyData(const QString &fieldKey, const QString &propertyKey)
{
    Q_D(QEXTQmlThemeHandler);
    if (d->m_themeDataMap.contains(fieldKey)) {
        QVariantMap mapField = d->m_themeDataMap.value(fieldKey);
        if (mapField.contains(propertyKey)) {
            return mapField.value(propertyKey);
        }
    }
    return QVariant();
}

const QMap<QString, QVariantMap> QEXTQmlThemeHandler::themeData() const
{
    Q_D(const QEXTQmlThemeHandler);
    return d->m_themeDataMap;
}

const QVariantMap QEXTQmlThemeHandler::themeInfo() const
{
    Q_D(const QEXTQmlThemeHandler);
    return d->m_themeDataMap.value(QEXTQmlThemeConstant::THEME_INFO_KEY);
}

void QEXTQmlThemeHandler::setLastErrorString(const QString &string)
{
    Q_D(QEXTQmlThemeHandler);
    if (string != d->m_lastErrorString) {
        d->m_lastErrorString = string;
    }
}

void QEXTQmlThemeHandler::setThemeData(const QMap<QString, QVariantMap> &data)
{
    Q_D(QEXTQmlThemeHandler);
    if (data != d->m_themeDataMap) {
        d->m_themeDataMap = data;
        d->m_valid = !data.isEmpty();
        emit this->themeDataChanged();
    }
}
