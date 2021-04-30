/****************************************************************************
**
** Library: QEXTQuick
**
** MIT License
**
** Copyright (c) 2019 toou http://www.toou.net
** Copyright (c) 2020 chengxuewen <1398831004@qq.com>
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

#include <qextthemehandler.h>
#include <qextthemehandler_p.h>
#include <qextthemebinder.h>
#include <qextthemeconstant.h>

#include <QVariantMap>
#include <QDebug>
#include <QFile>
#include <QByteArray>


QEXTThemeHandlerPrivate::QEXTThemeHandlerPrivate(QEXTThemeHandler *qq)
    : QEXTObjectPrivate(qq)
{
    m_themeValid = false;
}

QEXTThemeHandlerPrivate::~QEXTThemeHandlerPrivate()
{

}



QEXTThemeHandler::QEXTThemeHandler(const QString &themeName, const QString &themePath)
    : QObject(), QEXTObject(*(new QEXTThemeHandlerPrivate(this)))
{
    QEXT_D(QEXTThemeHandler);
    d->m_themeName = themeName;
    d->m_themePath = themePath;
}

QEXTThemeHandler::~QEXTThemeHandler()
{

}

QString QEXTThemeHandler::themeName() const
{
    QEXT_DC(QEXTThemeHandler);
    return d->m_themeName;
}

QString QEXTThemeHandler::themePath() const
{
    QEXT_DC(QEXTThemeHandler);
    return d->m_themePath;
}

QString QEXTThemeHandler::lastError() const
{
    QEXT_DC(QEXTThemeHandler);
    return d->m_lastError;
}

bool QEXTThemeHandler::isThemeValid() const
{
    QEXT_DC(QEXTThemeHandler);
    return d->m_themeValid;
}

bool QEXTThemeHandler::isTHemeLoad() const
{
    QEXT_DC(QEXTThemeHandler);
    return !d->m_themeDataMap.isEmpty();
}

QVariant QEXTThemeHandler::propertyData(const QString &fieldKey, const QString &propertyKey)
{
    QEXT_D(QEXTThemeHandler);
    if (d->m_themeDataMap.contains(fieldKey)) {
        QVariantMap fieldMap = d->m_themeDataMap.value(fieldKey);
        if (fieldMap.contains(propertyKey)) {
            return fieldMap.value(propertyKey);
        }
    }
    return QVariant();
}

QMap<QString, QVariantMap> QEXTThemeHandler::themeDataMap() const
{
    QEXT_DC(QEXTThemeHandler);
    return d->m_themeDataMap;
}

QVariantMap QEXTThemeHandler::themeInfo() const
{
    QEXT_DC(QEXTThemeHandler);
    return d->m_themeDataMap.value(QEXTThemeConstant::THEME_INFO_KEY);
}

void QEXTThemeHandler::setLastError(const QString &text)
{
    QEXT_D(QEXTThemeHandler);
    if (text != d->m_lastError) {
        d->m_lastError = text;
    }
}

void QEXTThemeHandler::setThemeData(const QMap<QString, QVariantMap> &data)
{
    QEXT_D(QEXTThemeHandler);
    if (data != d->m_themeDataMap) {
        d->m_themeDataMap = data;
        d->m_themeValid = !data.isEmpty();
        emit this->themeDataChanged();
    }
}
