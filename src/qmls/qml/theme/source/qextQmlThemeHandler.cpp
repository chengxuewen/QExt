/****************************************************************************
**
** Library: QExtQmlQuick
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

class QExtQmlThemeHandler;
class QEXT_QMLTHEME_API QExtQmlThemeHandlerPrivate
{
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlThemeHandlerPrivate)
    QEXT_DECLARE_PUBLIC(QExtQmlThemeHandler)
public:
    explicit QExtQmlThemeHandlerPrivate(QExtQmlThemeHandler *q);
    virtual ~QExtQmlThemeHandlerPrivate();

    QExtQmlThemeHandler * const q_ptr;

    bool mValid;
    QString mName;
    QString mPath;
    QString mLastError;
    QVariantMap mThemeInfoMap;
    QMap<QString, QVariantMap> mThemeDataMap;
};

QExtQmlThemeHandlerPrivate::QExtQmlThemeHandlerPrivate(QExtQmlThemeHandler *q)
    : q_ptr(q)
{
    mValid = false;
}

QExtQmlThemeHandlerPrivate::~QExtQmlThemeHandlerPrivate()
{
}


QExtQmlThemeHandler::QExtQmlThemeHandler(const QString &name, const QString &path)
    : QObject()
    , dd_ptr(new QExtQmlThemeHandlerPrivate(this))
{
    Q_D(QExtQmlThemeHandler);
    d->mName = name;
    d->mPath = path;
}

QExtQmlThemeHandler::~QExtQmlThemeHandler()
{
}

QString QExtQmlThemeHandler::themeName() const
{
    Q_D(const QExtQmlThemeHandler);
    return d->mName;
}

QString QExtQmlThemeHandler::themePath() const
{
    Q_D(const QExtQmlThemeHandler);
    return d->mPath;
}

QString QExtQmlThemeHandler::lastError() const
{
    Q_D(const QExtQmlThemeHandler);
    return d->mLastError;
}

bool QExtQmlThemeHandler::isValid() const
{
    Q_D(const QExtQmlThemeHandler);
    return d->mValid;
}

bool QExtQmlThemeHandler::isLoaded() const
{
    Q_D(const QExtQmlThemeHandler);
    return !d->mThemeDataMap.isEmpty();
}

QVariant QExtQmlThemeHandler::propertyData(const QString &fieldKey, const QString &propertyKey)
{
    Q_D(QExtQmlThemeHandler);
    if (d->mThemeDataMap.contains(fieldKey))
    {
        QVariantMap mapField = d->mThemeDataMap.value(fieldKey);
        if (mapField.contains(propertyKey))
        {
            return mapField.value(propertyKey);
        }
    }
    return QVariant();
}

const QMap<QString, QVariantMap> QExtQmlThemeHandler::themeData() const
{
    Q_D(const QExtQmlThemeHandler);
    return d->mThemeDataMap;
}

const QVariantMap QExtQmlThemeHandler::themeInfo() const
{
    Q_D(const QExtQmlThemeHandler);
    return d->mThemeDataMap.value(QExtQmlThemeConstant::kInfo);
}

void QExtQmlThemeHandler::setLastError(const QString &string)
{
    Q_D(QExtQmlThemeHandler);
    if (string != d->mLastError)
    {
        d->mLastError = string;
    }
}

void QExtQmlThemeHandler::setThemeData(const QMap<QString, QVariantMap> &data)
{
    Q_D(QExtQmlThemeHandler);
    if (data != d->mThemeDataMap)
    {
        d->mThemeDataMap = data;
        d->mValid = !data.isEmpty();
        emit this->themeDataChanged();
    }
}
