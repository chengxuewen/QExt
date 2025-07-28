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
set(QEXT_LIB_LINK_LIBRARIES)
set(QEXT_LIB_NAME Plot)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Gui)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

qext_find_package(WrapQwt PROVIDED_TARGETS QExt3rdparty::WrapQwt)
list(APPEND QEXT_LIB_LINK_LIBRARIES
    QExt::Core QExt::Widgets
    QExt3rdparty::WrapQwt)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
qext_add_library(${QEXT_LIB_NAME}
    EXCEPTIONS
    SOURCES
    source/qwt/qextQwtPlot.cpp
    source/qwt/qextQwtPlot.h
    source/qwt/qextQwtPlotCurve.cpp
    source/qwt/qextQwtPlotCurve.h
    source/qwt/qextQwtPlotCurve_p.h
    source/qwt/qextQwtPlotScalePicker.cpp
    source/qwt/qextQwtPlotScalePicker.h
    source/qwt/qextQwtPlotScaleZoomer.cpp
    source/qwt/qextQwtPlotScaleZoomer.h
    source/qwt/qextQwtPlotScrollBar.cpp
    source/qwt/qextQwtPlotScrollBar.h
    source/qwt/qextQwtPlotScrollZoomer.cpp
    source/qwt/qextQwtPlotScrollZoomer.h
    source/qwt/qextQwtPlotZoomer.cpp
    source/qwt/qextQwtPlotZoomer.h
    source/qwt/qextQwtSeriesData.cpp
    source/qwt/qextQwtSeriesData.h
    source/qwt/qextQwtSeriesData_p.h
    source/qextPlot.cpp
    source/qextPlot.h
    source/qextPlot_p.h
    source/qextPlotConstants.h
    source/qextPlotData.cpp
    source/qextPlotData.h
    source/qextPlotDataBuffer.cpp
    source/qextPlotDataBuffer.h
    source/qextPlotDataTransform.cpp
    source/qextPlotDataTransform.h
    source/qextPlotFactory.cpp
    source/qextPlotFactory.h
    source/qextPlotGlobal.h
    source/qextPlotGroup.cpp
    source/qextPlotGroup.h
    source/qextPlotManager.cpp
    source/qextPlotManager.h
    source/qextPlotModel.cpp
    source/qextPlotModel.h
    source/qextPlotUtils.cpp
    source/qextPlotUtils.h
    resources/qextPlot.qrc
    PRECOMPILED_HEADER
    source/qextPlotPch.h
    PUBLIC_LIBRARIES
    ${QEXT_LIB_LINK_LIBRARIES})


#-----------------------------------------------------------------------------------------------------------------------
# Add lib examples and tests
#-----------------------------------------------------------------------------------------------------------------------
qext_add_subdirectory(examples QEXT_BUILD_EXAMPLES)
qext_add_subdirectory(tests QEXT_BUILD_TESTS)
