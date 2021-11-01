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

#ifndef QTKMETATYPESERVICE_H
#define QTKMETATYPESERVICE_H

#include "qtkmetatypeinformation.h"
#include "../../qtkpluginframework_global.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKMetaTypeService class
 * The MetaType Service can be used to obtain meta type information for a
 * plugin. The MetaType Service will examine the specified plugin for meta type
 * documents to create the returned <code>ctkMetaTypeInformation</code> object.
 *
 * <p>
 * If the specified plugin does not contain any meta type documents, then a
 * <code>ctkMetaTypeInformation</code> object will be returned that wraps any
 * <code>ctkManagedService</code> or <code>ctkManagedServiceFactory</code>
 * services registered by the specified plugin that implement
 * <code>ctkMetaTypeProvider</code>. Thus the MetaType Service can be used to
 * retrieve meta type information for plugins which contain meta type
 * documents or which provide their own <code>ctkMetaTypeProvider</code> objects.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKMetaTypeService
{
public:
    virtual ~QTKMetaTypeService() {}

    /**
     * @brief getMetaTypeInformation
     * Return the MetaType information for the specified plugin.
     *
     * @param plugin The plugin for which meta type information is requested.
     * @return A ctkMetaTypeInformation object for the specified plugin.
     */
    virtual QTKMetaTypeInformationPtr getMetaTypeInformation(const QSharedPointer<QTKPlugin>& plugin) = 0;

    /**
     * @brief METATYPE_DOCUMENTS_LOCATION
     * Location of meta type documents. The MetaType Service will process each
     * entry in the meta type documents directory.
     */
    static const char *METATYPE_DOCUMENTS_LOCATION; // = "QTK-INF/metatype"
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

Q_DECLARE_INTERFACE(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKMetaTypeService,
                    "org.qtk.service.metatype.MetaTypeServce")

#endif // QTKMETATYPESERVICE_H
