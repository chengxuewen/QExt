/*=============================================================================

  Library: CTK

  Copyright (c) German Cancer Research Center,
    Division of Medical and Biological Informatics

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/

#include <qextOsgiPluginLocalization.h>
#include <qextOsgiPlugin.h>

#include <QTranslator>

//----------------------------------------------------------------------------
struct QExtOsgiPluginLocalizationData : public QSharedData
{
    QExtOsgiPluginLocalizationData(const QString& fileName, const QLocale& locale,
                                   const QSharedPointer<QExtOsgiPlugin>& plugin)
        : locale(locale), translation(plugin->getResource(fileName))
    {
        translator.load(reinterpret_cast<const uchar*>(translation.constData()), translation.size());
    }

    QExtOsgiPluginLocalizationData(const QExtOsgiPluginLocalizationData& other)
        : QSharedData(other),
        locale(other.locale), translation(other.translation)
    {
        translator.load(reinterpret_cast<const uchar*>(translation.constData()), translation.size());
    }

    ~QExtOsgiPluginLocalizationData()
    {

    }

    QTranslator translator;
    const QLocale locale;
    const QByteArray translation;
};

//----------------------------------------------------------------------------
QExtOsgiPluginLocalization::QExtOsgiPluginLocalization()
    : d(0)
{

}

//----------------------------------------------------------------------------
QExtOsgiPluginLocalization::QExtOsgiPluginLocalization(const QExtOsgiPluginLocalization &pl)
    : d(pl.d)
{

}

//----------------------------------------------------------------------------
QExtOsgiPluginLocalization::QExtOsgiPluginLocalization(const QString& msgFileName,
                                                       const QLocale& locale, const QSharedPointer<QExtOsgiPlugin>& plugin)
    : d(new QExtOsgiPluginLocalizationData(msgFileName, locale, plugin))
{

}

//----------------------------------------------------------------------------
QExtOsgiPluginLocalization::~QExtOsgiPluginLocalization()
{

}

//----------------------------------------------------------------------------
QExtOsgiPluginLocalization& QExtOsgiPluginLocalization::operator=(const QExtOsgiPluginLocalization& other)
{
    d = other.d;
    return *this;
}

//----------------------------------------------------------------------------
QString QExtOsgiPluginLocalization::getLocalized(const QString& context, const QString& str) const
{
    if (d)
    {
        return d->translator.translate(qPrintable(context), qPrintable(str));
    }
    return QString();
}

//----------------------------------------------------------------------------
QLocale QExtOsgiPluginLocalization::getLocale() const
{
    if (d) return d->locale;
    return QLocale();
}

