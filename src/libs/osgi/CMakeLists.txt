########################################################################################################################
#
# Library: QExt
#
# Copyright (C) 2021~Present ChengXueWen. Contact: 1398831004@qq.com.
#
# License: MIT License
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
# documentation files (the "Software"), to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and
# to permit persons to whom the Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or substantial portions
# of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE  AUTHORS
# OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
########################################################################################################################


#-----------------------------------------------------------------------------------------------------------------------
# Add lib link libraries
#-----------------------------------------------------------------------------------------------------------------------
set(QEXT_LIB_LINK_LIBRARIES)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui Qt4::QtNetwork)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
            Qt${QEXT_QT_VERSION_MAJOR}::Core
            Qt${QEXT_QT_VERSION_MAJOR}::Gui
            Qt${QEXT_QT_VERSION_MAJOR}::Network)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_LIB_LINK_LIBRARIES QExt::Core)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
qext_add_library(Osgi
        EXCEPTIONS
        SOURCES
        source/service/application/qextOsgiApplicationDescriptor.cpp
        source/service/application/qextOsgiApplicationDescriptor.h
        source/service/application/qextOsgiApplicationException.cpp
        source/service/application/qextOsgiApplicationException.h
        source/service/application/qextOsgiApplicationHandle.cpp
        source/service/application/qextOsgiApplicationHandle.h
        source/service/application/qextOsgiApplicationLauncher.h
        source/service/cm/qextOsgiConfiguration.cpp
        source/service/cm/qextOsgiConfiguration.h
        source/service/cm/qextOsgiConfigurationAdmin.cpp
        source/service/cm/qextOsgiConfigurationAdmin.h
        source/service/cm/qextOsgiConfigurationEvent.cpp
        source/service/cm/qextOsgiConfigurationEvent.h
        source/service/cm/qextOsgiConfigurationException.cpp
        source/service/cm/qextOsgiConfigurationException.h
        source/service/cm/qextOsgiConfigurationListener.h
        source/service/cm/qextOsgiConfigurationPlugin.cpp
        source/service/cm/qextOsgiConfigurationPlugin.h
        source/service/cm/qextOsgiManagedService.h
        source/service/cm/qextOsgiManagedServiceFactory.h
        source/service/datalocation/qextOsgiLocation.cpp
        source/service/datalocation/qextOsgiLocation.h
        source/service/debug/qextOsgiDebugOptions.cpp
        source/service/debug/qextOsgiDebugOptions.h
        source/service/debug/qextOsgiDebugOptionsListener.h
        source/service/event/qextOsgiEvent.cpp
        source/service/event/qextOsgiEvent.h
        source/service/event/qextOsgiEventAdmin.h
        source/service/event/qextOsgiEventConstants.cpp
        source/service/event/qextOsgiEventConstants.h
        source/service/event/qextOsgiEventHandler.h
        source/service/log/qextOsgiLogEntry.h
        source/service/log/qextOsgiLogListener.h
        source/service/log/qextOsgiLogReaderService.h
        source/service/log/qextOsgiLogService.cpp
        source/service/log/qextOsgiLogService.h
        source/service/log/qextOsgiLogStream.cpp
        source/service/log/qextOsgiLogStream.h
        source/service/metatype/qextOsgiAttributeDefinition.h
        source/service/metatype/qextOsgiMetaTypeInformation.h
        source/service/metatype/qextOsgiMetaTypeProvider.h
        source/service/metatype/qextOsgiMetaTypeService.h
        source/service/metatype/qextOsgiObjectClassDefinition.h
        source/qextOsgiApplicationRunnable.cpp
        source/qextOsgiApplicationRunnable.h
        source/qextOsgiBasicLocation_p.h
        source/qextOsgiBasicLocation.cpp
        source/qextOsgiDefaultApplicationLauncher_p.h
        source/qextOsgiDefaultApplicationLauncher.cpp
        source/qextOsgiDictionary.h
        source/qextOsgiGlobal.h
        source/qextOsgiLDAPExpr_p.h
        source/qextOsgiLDAPExpr.cpp
        source/qextOsgiLDAPSearchFilter.cpp
        source/qextOsgiLDAPSearchFilter.h
        source/qextOsgiLocationManager_p.h
        source/qextOsgiLocationManager.cpp
        source/qextOsgiPlugin_p.cpp
        source/qextOsgiPlugin_p.h
        source/qextOsgiPlugin.cpp
        source/qextOsgiPlugin.h
        source/qextOsgiPluginAbstractTracked_p.h
        source/qextOsgiPluginActivator.h
        source/qextOsgiPluginArchive_p.h
        source/qextOsgiPluginArchive.cpp
        source/qextOsgiPluginArchiveSQL_p.h
        source/qextOsgiPluginArchiveSQL.cpp
        source/qextOsgiPluginConstants.cpp
        source/qextOsgiPluginConstants.h
        source/qextOsgiPluginContext_p.h
        source/qextOsgiPluginContext.cpp
        source/qextOsgiPluginContext.h
        source/qextOsgiPluginDatabaseException.cpp
        source/qextOsgiPluginDatabaseException.h
        source/qextOsgiPluginEvent.cpp
        source/qextOsgiPluginEvent.h
        source/qextOsgiPluginException.cpp
        source/qextOsgiPluginException.h
        source/qextOsgiPluginFramework_p.cpp
        source/qextOsgiPluginFramework_p.h
        source/qextOsgiPluginFramework.cpp
        source/qextOsgiPluginFramework.h
        source/qextOsgiPluginFrameworkContext_p.h
        source/qextOsgiPluginFrameworkContext.cpp
        source/qextOsgiPluginFrameworkDebug_p.h
        source/qextOsgiPluginFrameworkDebug.cpp
        source/qextOsgiPluginFrameworkDebugOptions_p.h
        source/qextOsgiPluginFrameworkDebugOptions.cpp
        source/qextOsgiPluginFrameworkEvent.cpp
        source/qextOsgiPluginFrameworkEvent.h
        source/qextOsgiPluginFrameworkFactory.cpp
        source/qextOsgiPluginFrameworkFactory.h
        source/qextOsgiPluginFrameworkGlobal.h
        source/qextOsgiPluginFrameworkLauncher.cpp
        source/qextOsgiPluginFrameworkLauncher.h
        source/qextOsgiPluginFrameworkListeners_p.h
        source/qextOsgiPluginFrameworkListeners.cpp
        source/qextOsgiPluginFrameworkProperties_p.h
        source/qextOsgiPluginFrameworkProperties.cpp
        source/qextOsgiPluginFrameworkUtil_p.h
        source/qextOsgiPluginFrameworkUtil.cpp
        source/qextOsgiPluginLocalization.cpp
        source/qextOsgiPluginLocalization.h
        source/qextOsgiPluginManifest_p.h
        source/qextOsgiPluginManifest.cpp
        source/qextOsgiPlugins_p.h
        source/qextOsgiPlugins.cpp
        source/qextOsgiPluginStorage_p.h
        source/qextOsgiPluginStorageSQL_p.h
        source/qextOsgiPluginStorageSQL.cpp
        source/qextOsgiPluginTracker_p.h
        source/qextOsgiPluginTracker.h
        source/qextOsgiPluginTrackerCustomizer.h
        source/qextOsgiRequirePlugin_p.h
        source/qextOsgiRequirePlugin.cpp
        source/qextOsgiServiceEvent.cpp
        source/qextOsgiServiceEvent.h
        source/qextOsgiServiceException.cpp
        source/qextOsgiServiceException.h
        source/qextOsgiServiceFactory.h
        source/qextOsgiServiceProperties_p.h
        source/qextOsgiServiceProperties.cpp
        source/qextOsgiServiceReference_p.cpp
        source/qextOsgiServiceReference_p.h
        source/qextOsgiServiceReference.cpp
        source/qextOsgiServiceReference.h
        source/qextOsgiServiceRegistration_p.cpp
        source/qextOsgiServiceRegistration_p.h
        source/qextOsgiServiceRegistration.cpp
        source/qextOsgiServiceRegistration.h
        source/qextOsgiServices_p.h
        source/qextOsgiServices.cpp
        source/qextOsgiServiceSlotEntry_p.h
        source/qextOsgiServiceSlotEntry.cpp
        source/qextOsgiServiceTracker_p.h
        source/qextOsgiServiceTracker.h
        source/qextOsgiServiceTrackerCustomizer.h
        source/qextOsgiTrackedPlugin_p.h
        source/qextOsgiTrackedPluginListener_p.h
        source/qextOsgiTrackedService_p.h
        source/qextOsgiTrackedServiceListener_p.h
        source/qextOsgiVersion.cpp
        source/qextOsgiVersion.h
        source/qextOsgiVersionRange.cpp
        source/qextOsgiVersionRange_p.h
        PRECOMPILED_HEADER
        source/qextOsgiPch.h
        PUBLIC_LIBRARIES
        ${QEXT_LIB_LINK_LIBRARIES})


#-----------------------------------------------------------------------------------------------------------------------
# Add lib tests and examples
#-----------------------------------------------------------------------------------------------------------------------
if(QEXT_BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(QEXT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
