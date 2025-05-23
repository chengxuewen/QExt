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
# Set example link libraries
#-----------------------------------------------------------------------------------------------------------------------
set(QEXT_EXAMPLE_LINK_LIBRARIES)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::UiTools
        Qt${QEXT_QT_VERSION_MAJOR}::Network
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_EXAMPLE_LINK_LIBRARIES QExt::Designer)


#-----------------------------------------------------------------------------------------------------------------------
# Add examples
#-----------------------------------------------------------------------------------------------------------------------
qext_add_executable(QExtExpDesignerCalculatorBuilder
    SOURCES
    calculatorbuilder/calculatorbuilder.qrc
    calculatorbuilder/calculatorform.cpp
    calculatorbuilder/calculatorform.h
    calculatorbuilder/calculatorform.ui
    calculatorbuilder/main.cpp
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/calculatorbuilder
    OUTPUT_DIRECTORY
    ${QEXT_INSTALL_EXAMPLESDIR}
    DEFINES
    EXECUTABLE_OUTPUT_PATH="${QEXT_INSTALL_EXAMPLESDIR}")
qext_add_executable(QExtExpDesignerCalculatorForm
    SOURCES
    calculatorform/calculatorform.cpp
    calculatorform/calculatorform.h
    calculatorform/calculatorform.h
    calculatorform/calculatorform.ui
    calculatorform/main.cpp
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/calculatorform
    OUTPUT_DIRECTORY
    ${QEXT_INSTALL_EXAMPLESDIR}
    DEFINES
    EXECUTABLE_OUTPUT_PATH="${QEXT_INSTALL_EXAMPLESDIR}")
qext_add_executable(QExtExpDesignerWorldTimeClockBuilder
    SOURCES
    worldtimeclockbuilder/form.ui
    worldtimeclockbuilder/main.cpp
    worldtimeclockbuilder/worldtimeclockbuilder.qrc
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/worldtimeclockbuilder
    OUTPUT_DIRECTORY
    ${QEXT_INSTALL_EXAMPLESDIR}
    DEFINES
    EXECUTABLE_OUTPUT_PATH="${QEXT_INSTALL_EXAMPLESDIR}")
qext_add_executable(QExtExpDesigner
    SOURCES
    designer/appfontdialog.cpp
    designer/appfontdialog.h
    designer/assistantclient.cpp
    designer/assistantclient.h
    designer/designer_enums.h
    designer/main.cpp
    designer/mainwindow.cpp
    designer/mainwindow.h
    designer/newform.cpp
    designer/newform.h
    designer/preferencesdialog.cpp
    designer/preferencesdialog.h
    designer/preferencesdialog.ui
    designer/designer.qrc
    designer/qdesigner.cpp
    designer/qdesigner.h
    designer/qdesigner_actions.cpp
    designer/qdesigner_actions.h
    designer/qdesigner_appearanceoptions.cpp
    designer/qdesigner_appearanceoptions.h
    designer/qdesigner_appearanceoptions.ui
    designer/qdesigner_formwindow.cpp
    designer/qdesigner_formwindow.h
    designer/qdesigner_pch.h
    designer/qdesigner_server.cpp
    designer/qdesigner_server.h
    designer/qdesigner_settings.cpp
    designer/qdesigner_settings.h
    designer/qdesigner_toolwindow.cpp
    designer/qdesigner_toolwindow.h
    designer/qdesigner_workbench.cpp
    designer/qdesigner_workbench.h
    designer/saveformastemplate.cpp
    designer/saveformastemplate.h
    designer/saveformastemplate.ui
    designer/versiondialog.cpp
    designer/versiondialog.h
    LIBRARIES
    ${QEXT_EXAMPLE_LINK_LIBRARIES}
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/designer
    OUTPUT_DIRECTORY
    ${QEXT_INSTALL_EXAMPLESDIR}
    DEFINES
    EXECUTABLE_OUTPUT_PATH="${QEXT_INSTALL_EXAMPLESDIR}")
