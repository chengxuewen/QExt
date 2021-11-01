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

#ifndef QTKMETATYPEPROVIDER_H
#define QTKMETATYPEPROVIDER_H

#include "qtkobjectclassdefinition.h"
#include "../../qtkpluginframework_global.h"

#include <QLocale>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKMetaTypeProvider class
 * Provides access to metatypes. This interface can be implemented on a Managed
 * Service or Managed Service Factory as well as registered as a service. When
 * registered as a service, it must be registered with a
 * {@link #METATYPE_FACTORY_PID} or {@link #METATYPE_PID} service property (or
 * both). Any PID mentioned in either of these factories must be a valid argument
 * to the {@link #getObjectClassDefinition(const QString&, const QLocale&)} method.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKMetaTypeProvider
{
public:
    /**
     * @brief getObjectClassDefinition
     * Returns an object class definition for the specified id localized to the
     * specified locale. If no locale is specified, the default locale is used,
     * according to the default constructor of QLocale.
     *
     * @param strId The ID of the requested object class. This can be a pid or
     *        factory pid returned by getPids or getFactoryPids.
     * @param strLocale The locale of the definition
     * @return A <code>ctkObjectClassDefinition</code> object.
     */
    virtual QTKObjectClassDefinitionPtr getObjectClassDefinition(const QString &strId,
                                                                 const QLocale &strLocale = QLocale()) = 0;
    virtual ~QTKMetaTypeProvider() {}

    /**
     * @brief getLocales
     * Return a list of available locales.
     *
     * @return A list of QLocale objects.
     */
    virtual QList<QLocale> getLocales() const = 0;

    /**
     * @brief METATYPE_FACTORY_PID
     * Service property to signal that this service has
     * {@link ctkObjectClassDefinition} objects for the given factory PIDs. The
     * type of this service property is <code>QString</code>.
     */
    static const char *METATYPE_FACTORY_PID; // = "metatype.factory.pid"

    /**
     * @brief METATYPE_PID
     * Service property to signal that this service has
     * {@link ctkObjectClassDefinition} objects for the given PIDs. The type of
     * this service property is <code>QString</code>.
     */
    static const char *METATYPE_PID; // = "metatype.pid"
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

Q_DECLARE_INTERFACE(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKMetaTypeProvider,
                    "org.qtk.service.metatype.MetaTypeProvider")

#endif // QTKMETATYPEPROVIDER_H
