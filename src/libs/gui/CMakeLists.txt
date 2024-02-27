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
set(QEXT_LIB_NAME Gui)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_LIB_LINK_LIBRARIES QExt::Core)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
qext_add_library(${QEXT_LIB_NAME}
    EXCEPTIONS
    SOURCES
    source/frameless/qextAbstractFramelessContext_p.h
    source/frameless/qextAbstractFramelessContext.cpp
    source/frameless/qextFramelessItemDelegate_p.h
    source/frameless/qextFramelessItemDelegate.cpp
    source/frameless/qextFramelessNativeEvent_p.h
    source/frameless/qextFramelessNativeEvent.cpp
    source/frameless/qextFramelessSharedEvent_p.h
    source/frameless/qextFramelessSharedEvent.cpp
    source/frameless/qextFramelessAgent.h
    source/frameless/qextFramelessAgent_p.h
    source/frameless/qextFramelessAgent.cpp
    source/frameless/qextFramelessUtils.h
    source/frameless/qextFramelessUtils_p.h
    source/pinyinime/atomdictbase.h
    source/pinyinime/dictbuilder.cpp
    source/pinyinime/dictbuilder.h
    source/pinyinime/dictdef.h
    source/pinyinime/dictlist.cpp
    source/pinyinime/dictlist.h
    source/pinyinime/dicttrie.cpp
    source/pinyinime/dicttrie.h
    source/pinyinime/lpicache.cpp
    source/pinyinime/lpicache.h
    source/pinyinime/matrixsearch.cpp
    source/pinyinime/matrixsearch.h
    source/pinyinime/mystdlib.cpp
    source/pinyinime/mystdlib.h
    source/pinyinime/ngram.cpp
    source/pinyinime/ngram.h
    source/pinyinime/pinyinime.cpp
    source/pinyinime/pinyinime.h
    source/pinyinime/searchutility.cpp
    source/pinyinime/searchutility.h
    source/pinyinime/spellingtable.cpp
    source/pinyinime/spellingtable.h
    source/pinyinime/spellingtrie.cpp
    source/pinyinime/spellingtrie.h
    source/pinyinime/sync.cpp
    source/pinyinime/sync.h
    source/pinyinime/userdict.cpp
    source/pinyinime/userdict.h
    source/pinyinime/splparser.cpp
    source/pinyinime/splparser.h
    source/pinyinime/utf16char.cpp
    source/pinyinime/utf16char.h
    source/pinyinime/utf16reader.cpp
    source/pinyinime/utf16reader.h
    source/qextIconAnimation.cpp
    source/qextIconAnimation_p.h
    source/qextIconAnimation.h
    source/qextGuiGlobal.h
    source/qextPainter.cpp
    source/qextPainter.h
    source/qextPinyin.cpp
    source/qextPinyin.h
    source/qextPinyin_p.h
    resource/qextGui.qrc
    PRECOMPILED_HEADER
    source/qextGuiPch.h
    PUBLIC_LIBRARIES
    ${QEXT_LIB_LINK_LIBRARIES})

if(LINUX)
    qext_internal_extend_target(${QEXT_LIB_NAME} SOURCES
        source/frameless/qwindowkit_linux.cpp)
elseif(WIN32)
    qext_internal_extend_target(${QEXT_LIB_NAME} SOURCES
        source/frameless/qextFrameless_win.h
        source/frameless/qextFrameless_win.cpp
        source/frameless/qextFramelessExtra_p.h)
endif()

if(QEXT_FEATURE_USE_FRAMELESS_QT_CONTEXT)
    qext_internal_extend_target(${QEXT_LIB_NAME} SOURCES
        source/frameless/qextFramelessContext_p.h
        source/frameless/qextFramelessContext.cpp)
else()
    if(WIN32)
        qext_internal_extend_target(${QEXT_LIB_NAME} SOURCES
            source/frameless/qextFramelessContext_win_p.h
            source/frameless/qextFramelessContext_win.cpp
            LIBRARIES uxtheme)
    elseif(APPLE)
        qext_internal_extend_target(${QEXT_LIB_NAME} SOURCES
            source/frameless/qextFramelessContext_cocoa_p.h
            source/frameless/qextFramelessContext_cocoa.mm
            LIBRARIES
            "-framework Foundation"
            "-framework Cocoa"
            "-framework AppKit")
    else()
        qext_internal_extend_target(${QEXT_LIB_NAME} SOURCES
            source/frameless/qextFramelessContext_p.h
            source/frameless/qextFramelessContext.cpp)
    endif()
endif()


if(QEXT_FEATURE_USE_FRAMELESS_STYLE_AGENT)
    qext_internal_extend_target(${QEXT_LIB_NAME} SOURCES
        source/frameless/qextFramelessStyleAgent.h
        source/frameless/qextFramelessStyleAgent_p.h
        source/frameless/qextFramelessStyleAgent.cpp)
    if(WIN32)
        qext_internal_extend_target(${QEXT_LIB_NAME} SOURCES
            source/frameless/qextFramelessStyleAgent_win.cpp)
    elseif(APPLE)
        qext_internal_extend_target(${QEXT_LIB_NAME} SOURCES
            source/frameless/qextFramelessStyleAgent_mac.mm)
    else()
        qext_internal_extend_target(${QEXT_LIB_NAME} SOURCES
            source/frameless/qextFramelessStyleAgent_linux.cpp)
    endif()
endif()


#-----------------------------------------------------------------------------------------------------------------------
# Add lib tests and examples
#-----------------------------------------------------------------------------------------------------------------------
if(QEXT_BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(QEXT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
