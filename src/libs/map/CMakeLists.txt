########################################################################################################################
#
# Library: QExt
#
# Copyright (C) 2025~Present ChengXueWen. Contact: 1398831004@qq.com.
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
set(QEXT_LIB_NAME Map)
set(QEXT_LIB_LINK_LIBRARIES)

if(QEXT_QT_VERSION_MAJOR EQUAL 5)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::OpenGL)
elseif(QEXT_QT_VERSION_MAJOR GREATER_EQUAL 6)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::OpenGLWidgets)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_LIB_LINK_LIBRARIES QExt::Core QExt::CorePrivate)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
qext_add_library(${QEXT_LIB_NAME}
    EXCEPTIONS
    SOURCES
    source/style/qextMapFilterParameter.cpp
    source/style/qextMapFilterParameter.h
    source/style/qextMapImageParameter.cpp
    source/style/qextMapImageParameter.h
    source/style/qextMapImageStyleChange.cpp
    source/style/qextMapImageStyleChange_p.h
    source/style/qextMapLayerParameter.cpp
    source/style/qextMapLayerParameter.h
    source/style/qextMapLayerStyleChange.cpp
    source/style/qextMapLayerStyleChange_p.h
    source/style/qextMapSourceParameter.cpp
    source/style/qextMapSourceParameter.h
    source/style/qextMapSourceStyleChange.cpp
    source/style/qextMapSourceStyleChange_p.h
    source/style/qextMapStyleChange.cpp
    source/style/qextMapStyleChangeUtils.cpp
    source/style/qextMapStyleChangeUtils_p.h
    source/style/qextMapStyleChange_p.h
    source/style/qextMapStyleParameter.cpp
    source/style/qextMapStyleParameter.h
    source/qextMap.cpp
    source/qextMap.h
    source/qextMap_p.h
    source/qextMapConversion_p.h
    source/qextMapGLWidget.cpp
    source/qextMapGLWidget.h
    source/qextMapGLWidget_p.h
    source/qextMapGeoJson.cpp
    source/qextMapGeoJson_p.h
    source/qextMapGlobal.h
    source/qextMapObserver.cpp
    source/qextMapObserver_p.h
    source/qextMapRenderer.cpp
    source/qextMapRenderer_p.h
    source/qextMapSettings.cpp
    source/qextMapSettings.h
    source/qextMapSettings_p.h
    source/qextMapTypes.cpp
    source/qextMapTypes.h
    source/qextMapUtils.cpp
    source/qextMapUtils.h
    qextMap.qrc
    PRECOMPILED_HEADER
    source/qextMapPch.h
    PUBLIC_LIBRARIES
    ${QEXT_LIB_LINK_LIBRARIES})
if(QEXT_FEATURE_USE_SUBDIR_QMAPLIBRE)
    set(MLN_QT_STATIC ON CACHE INTERNAL "" FORCE)
    set(MLN_WITH_WERROR OFF CACHE INTERNAL "" FORCE)
    set(MLN_QT_WITH_LOCATION OFF CACHE INTERNAL "" FORCE)
    set(QExtWrapQMapLibre_DIR_NAME "maplibre-native-qt")
    set(QExtWrapQMapLibre_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QExtWrapQMapLibre_DIR_NAME}")
    set(QExtWrapQMapLibre_SOURCE_DIR "${PROJECT_SOURCE_DIR}/3rdparty/${QExtWrapQMapLibre_DIR_NAME}")
    if(NOT EXISTS "${QExtWrapQMapLibre_SOURCE_DIR}")
        qext_fetch_3rdparty(QExtWrapQMapLibre URL "${PROJECT_SOURCE_DIR}/3rdparty/${QExtWrapQMapLibre_DIR_NAME}.7z")
    endif()
    add_subdirectory(${QExtWrapQMapLibre_SOURCE_DIR} ${QExtWrapQMapLibre_ROOT_DIR}/subbuild)
    qext_internal_extend_target(${QEXT_LIB_NAME}
        INCLUDE_DIRECTORIES
        ${MLN_CORE_PATH}/src
        ${MLN_CORE_PATH}/platform/qt/src
        LIBRARIES
        mbgl-core
        mapbox-base
        MLNQtCore
        MLNQtWidgets
        $<BUILD_INTERFACE:mbgl-core>
        $<BUILD_INTERFACE:mbgl-compiler-options>
        $<BUILD_INTERFACE:MLNQtCompilerOptions>)
else()
    qext_find_package(WrapQMapLibre PROVIDED_TARGETS QExt3rdparty::WrapQMapLibre)
    qext_internal_extend_target(${QEXT_LIB_NAME}
        DEFINES
        __QT__
        LIBRARIES
        QExt3rdparty::WrapQMapLibre)
endif()
if(LINUX OR ANDROID)
    qext_find_package(WrapOpenSSL PROVIDED_TARGETS QExt3rdparty::WrapOpenSSL)
    qext_internal_extend_target(${QEXT_LIB_NAME} PUBLIC_LIBRARIES QExt3rdparty::WrapOpenSSL)
endif()


#-----------------------------------------------------------------------------------------------------------------------
# Add lib examples and tests
#-----------------------------------------------------------------------------------------------------------------------
qext_add_subdirectory(examples QEXT_BUILD_EXAMPLES)
qext_add_subdirectory(tests QEXT_BUILD_TESTS)
