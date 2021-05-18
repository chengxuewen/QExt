/****************************************************************************
**
** Library: QEXTQuick
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

#include <qextquickthemehandler.h>
#include <qextquickthemehandler_p.h>
#include <qextquickthemebinder.h>
#include <qextquickthemeconstant.h>

#include <QVariantMap>
#include <QDebug>
#include <QFile>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTextStream>



QEXTQuickThemeHandlerPrivate::QEXTQuickThemeHandlerPrivate(QEXTQuickThemeHandler *qq)
    : QEXTObjectPrivate(qq)
{
    m_valid = false;
}

QEXTQuickThemeHandlerPrivate::~QEXTQuickThemeHandlerPrivate()
{

}



QEXTQuickThemeHandler::QEXTQuickThemeHandler(const QString &name, const QString &path)
    : QObject(), QEXTObject(*(new QEXTQuickThemeHandlerPrivate(this)))
{
    QEXT_D(QEXTQuickThemeHandler);
    d->m_name = name;
    d->m_path = path;
}

QEXTQuickThemeHandler::~QEXTQuickThemeHandler()
{

}

QString QEXTQuickThemeHandler::themeName() const
{
    QEXT_DC(QEXTQuickThemeHandler);
    return d->m_name;
}

QString QEXTQuickThemeHandler::themePath() const
{
    QEXT_DC(QEXTQuickThemeHandler);
    return d->m_path;
}

QString QEXTQuickThemeHandler::lastErrorString() const
{
    QEXT_DC(QEXTQuickThemeHandler);
    return d->m_lastErrorString;
}

bool QEXTQuickThemeHandler::isValid() const
{
    QEXT_DC(QEXTQuickThemeHandler);
    return d->m_valid;
}

bool QEXTQuickThemeHandler::isLoad() const
{
    QEXT_DC(QEXTQuickThemeHandler);
    return !d->m_themeDataMap.isEmpty();
}

QVariant QEXTQuickThemeHandler::propertyData(const QString &fieldKey, const QString &propertyKey)
{
    QEXT_D(QEXTQuickThemeHandler);
    if (d->m_themeDataMap.contains(fieldKey)) {
        QVariantMap mapField = d->m_themeDataMap.value(fieldKey);
        if (mapField.contains(propertyKey)) {
            return mapField.value(propertyKey);
        }
    }
    return QVariant();
}

const QMap<QString, QVariantMap> QEXTQuickThemeHandler::themeData() const
{
    QEXT_DC(QEXTQuickThemeHandler);
    return d->m_themeDataMap;
}

const QVariantMap QEXTQuickThemeHandler::themeInfo() const
{
    QEXT_DC(QEXTQuickThemeHandler);
    return d->m_themeDataMap.value(QEXTQuickThemeConstant::THEME_INFO_KEY);
}

void QEXTQuickThemeHandler::setLastErrorString(const QString &string)
{
    QEXT_D(QEXTQuickThemeHandler);
    if (string != d->m_lastErrorString) {
        d->m_lastErrorString = string;
    }
}

void QEXTQuickThemeHandler::setThemeData(const QMap<QString, QVariantMap> &data)
{
    QEXT_D(QEXTQuickThemeHandler);
    if (data != d->m_themeDataMap) {
        d->m_themeDataMap = data;
        d->m_valid = !data.isEmpty();
        emit this->themeDataChanged();
    }
}
