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

#ifndef QTKPLUGINLOCALIZATION_H
#define QTKPLUGINLOCALIZATION_H

#include "qtkpluginframework_global.h"

#include <QLocale>
#include <QSharedDataPointer>
#include <QSharedPointer>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPlugin;
struct QTKPluginLocalizationData;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginLocalization class
 * Translate text into different languages.
 *
 * Use this class to dynamically translate human-readable text
 * in your plugin. You can get an instance of this class
 * corresponding to a specific locale via the method
 * <code>QTKPlugin::getPluginLocalization()</code>.
 *
 * @see QTKPlugin::getPluginLocalization()
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginLocalization
{
public:
    /**
     * @brief QTKPluginLocalization
     * Creates a default QTKPluginLocalization instance, using
     * the default locale.
     *
     * Note that getLocalized() will always return a null QString
     * for a default constructed QTKPluginLocalization object.
     * Use <code>QTKPlugin::getPluginLocalization()</code> to create
     * a valid instance.
     */
    QTKPluginLocalization();
    QTKPluginLocalization(const QTKPluginLocalization &pluginLocal);
    ~QTKPluginLocalization();

    QTKPluginLocalization& operator=(const QTKPluginLocalization &other);

    /**
     * @brief getLocalized
     * Translate <code>str</code> to a specific locale, using the
     * specified <code>context</code>.
     *
     * @return The translation or a null QString, if no translation was found.
     */
    QString getLocalized(const QString &strContext, const QString &str) const;

    /**
     * @brief getLocale
     * Get the locale for which this <code>QTKPluginLocalization</code>
     * object was constructed.
     *
     * @return The locale for this object.
     */
    QLocale getLocale() const;

private:
    QTKPluginLocalization(const QString &strMsgFileName, const QLocale &locale,
                          const QSharedPointer<QTKPlugin> &plugin);

    friend class QTKPlugin;

    mutable QSharedDataPointer<QTKPluginLocalizationData> d;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINLOCALIZATION_H
