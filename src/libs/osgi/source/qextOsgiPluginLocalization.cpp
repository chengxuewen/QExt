/****************************************************************************
** Library: QTK
**
** Copyright (c) German Cancer Research Center,
**     Division of Medical and Biological Informatics
** Copyright (c) chengxuewen <1398831004@qq.com>
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
** http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
****************************************************************************/

#include "qtkpluginlocalization.h"
#include "qtkplugin.h"

#include <QTranslator>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

struct QTKPluginLocalizationData : public QSharedData
{
    QTKPluginLocalizationData(const QString &strFileName, const QLocale &locale,
                              const QSharedPointer<QTKPlugin> &plugin)
        : m_locale(locale),
          m_translation(plugin->getResource(strFileName))
    {
        m_translator.load(reinterpret_cast<const uchar*>(m_translation.constData()), m_translation.size());
    }

    QTKPluginLocalizationData(const QTKPluginLocalizationData &other)
        : QSharedData(other),
          m_locale(other.m_locale),
          m_translation(other.m_translation)
    {
        m_translator.load(reinterpret_cast<const uchar*>(m_translation.constData()), m_translation.size());
    }

    ~QTKPluginLocalizationData()
    {

    }

    QTranslator m_translator;
    const QLocale m_locale;
    const QByteArray m_translation;
};

QTKPluginLocalization::QTKPluginLocalization()
    : d(0)
{

}

QTKPluginLocalization::QTKPluginLocalization(const QTKPluginLocalization &pluginLocal)
    : d(pluginLocal.d)
{

}

QTKPluginLocalization::QTKPluginLocalization(const QString &strMsgFileName,
                                             const QLocale &locale, const QSharedPointer<QTKPlugin> &plugin)
    : d(new QTKPluginLocalizationData(strMsgFileName, locale, plugin))
{

}

QTKPluginLocalization::~QTKPluginLocalization()
{

}

QTKPluginLocalization& QTKPluginLocalization::operator=(const QTKPluginLocalization &other)
{
    d = other.d;
    return *this;
}

QString QTKPluginLocalization::getLocalized(const QString &strContext, const QString &str) const
{
    if (d) {
        return d->m_translator.translate(qPrintable(strContext), qPrintable(str));
    }
    return QString();
}

QLocale QTKPluginLocalization::getLocale() const
{
    if (d) {
        return d->m_locale;
    }
    return QLocale();
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
