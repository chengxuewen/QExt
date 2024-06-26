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
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui Qt4::QtSvg)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Svg
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::GuiPrivate
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_LIB_LINK_LIBRARIES QExt::Core PinyinIME)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
qext_add_library(Keyboard
    PLUGIN_TYPES platforminputcontexts
    EXCEPTIONS
    SOURCES
    source/CandidatesListWidget.h
    source/CandidatesListWidget.cpp
    source/KeyboardContainer.cpp
    source/KeyboardContainer.h
    source/NormalKeyboard.h
    source/NormalKeyboard.ui
    source/NormalKeyboard.cpp
    source/NumKeyboard.h
    source/NumKeyboard.ui
    source/NumKeyboard.cpp
    source/QAbstractInputMethod.h
    source/QAbstractInputMethod.cpp
    source/QKeyboardLayout.h
    source/QKeyboardLayout.cpp
    source/QPinyinInputMethod.h
    source/QPinyinInputMethod.cpp
    source/SymbolKeyboard.h
    source/SymbolKeyboard.ui
    source/SymbolKeyboard.cpp
    source/qextKeyboardInputContext_p.h
    source/qextKeyboardInputContext.cpp
    source/pinyindecoderservice.cpp
    source/pinyindecoderservice_p.h
    source/qextKeyboardGlobal.h
    resource/qextKeyboard.qrc
    PRECOMPILED_HEADER
    source/qextKeyboardPch.h
    PUBLIC_LIBRARIES
    ${QEXT_LIB_LINK_LIBRARIES})


#-----------------------------------------------------------------------------------------------------------------------
# Add lib examples and tests
#-----------------------------------------------------------------------------------------------------------------------
#qext_add_subdirectory(examples QEXT_BUILD_EXAMPLES)
#qext_add_subdirectory(tests QEXT_BUILD_TESTS)
