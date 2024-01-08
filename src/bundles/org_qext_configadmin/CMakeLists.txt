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

project(org_qext_configadmin)

set(PLUGIN_export_directive "org_commontk_configadmin_EXPORT")

set(PLUGIN_SRCS
    source/qextOsgiCMEventDispatcher.cpp
    source/qextOsgiCMEventDispatcher_p.h
    source/qextOsgiCMLogTracker.cpp
    source/qextOsgiCMLogTracker_p.h
    source/qextOsgiCMPluginManager.cpp
    source/qextOsgiCMPluginManager_p.h
    source/qextOsgiCMSerializedTaskQueue.cpp
    source/qextOsgiCMSerializedTaskQueue_p.h
    source/qextOsgiConfigurationAdminActivator.cpp
    source/qextOsgiConfigurationAdminActivator_p.h
    source/qextOsgiConfigurationAdminFactory.cpp
    source/qextOsgiConfigurationAdminFactory_p.h
    source/qextOsgiConfigurationAdminImpl.cpp
    source/qextOsgiConfigurationAdminImpl_p.h
    source/qextOsgiConfigurationEventAdapter_p.h
    source/qextOsgiConfigurationEventAdapter.cpp
    source/qextOsgiConfigurationImpl.cpp
    source/qextOsgiConfigurationImpl_p.h
    source/qextOsgiConfigurationStore.cpp
    source/qextOsgiConfigurationStore_p.h
    source/qextOsgiManagedServiceTracker.cpp
    source/qextOsgiManagedServiceTracker_p.h
    source/qextOsgiManagedServiceFactoryTracker.cpp
    source/qextOsgiManagedServiceFactoryTracker_p.h)

# Files which should be processed by Qts moc
set(PLUGIN_MOC_SRCS
    source/qextOsgiCMSerializedTaskQueue_p.h
    source/qextOsgiConfigurationAdminActivator_p.h
    source/qextOsgiConfigurationAdminFactory_p.h
    source/qextOsgiConfigurationAdminImpl_p.h
    source/qextOsgiConfigurationEventAdapter_p.h)

# Qt Designer files which should be processed by Qts uic
set(PLUGIN_UI_FORMS)

# QRC Files which should be compiled into the plugin
set(PLUGIN_resources)

#Compute the plugin dependencies
# ctkFunctionGetTargetLibraries(PLUGIN_target_libraries)

ctkMacroBuildPlugin(
    NAME ${PROJECT_NAME}
    EXPORT_DIRECTIVE ${PLUGIN_export_directive}
    SRCS ${PLUGIN_SRCS}
    MOC_SRCS ${PLUGIN_MOC_SRCS}
    UI_FORMS ${PLUGIN_UI_FORMS}
    RESOURCES ${PLUGIN_resources}
    TARGET_LIBRARIES
    QExt::Osgi)
