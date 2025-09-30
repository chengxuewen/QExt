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
#include <qextQmlRegistration.h>

#include <QObject>
#include <QQmlEngine>
#include <QQmlExtensionPlugin>

QEXT_QML_DECLARE_REGISTRATION(QExtQuick_Qwt)

class QExtQuickQwtPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    QExtQuickQwtPlugin(QObject *parent = nullptr) : QQmlExtensionPlugin(parent)
    {
        QEXT_QML_REFERENCE_REGISTRATION(QExtQuick_Qwt)
    }

    void registerTypes(const char *uri)
    {
        QExtQuickQwt::instance()->registerTypes(uri);
    }

    void initializeEngine(QQmlEngine *engine, const char *uri)
    {
        QExtQuickQwt::instance()->initializeEngine(engine, uri);
    }
};

#include <qextQuickQwtPlugin.moc>
