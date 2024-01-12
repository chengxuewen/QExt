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
	list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
	list(APPEND QEXT_LIB_LINK_LIBRARIES
		Qt${QEXT_QT_VERSION_MAJOR}::Core
		Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets)
else()
	message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_LIB_LINK_LIBRARIES QExt::Core)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
qext_add_library(Pattern
	EXCEPTIONS
	SOURCES
	source/qextPatternCommand.cpp
	source/qextPatternCommand.h
	source/qextPatternController.cpp
	source/qextPatternController.h
	source/qextPatternFacade.cpp
	source/qextPatternFacade.h
	source/qextPatternInterface.h
	source/qextPatternMediator.cpp
	source/qextPatternMediator.h
	source/qextPatternModel.cpp
	source/qextPatternModel.h
	source/qextPatternNotification.cpp
	source/qextPatternNotification.h
	source/qextPatternNotifier.cpp
	source/qextPatternNotifier.h
	source/qextPatternProxy.cpp
	source/qextPatternProxy.h
    source/qextPatternGlobal.h
	source/qextPatternUpdateData.cpp
	source/qextPatternUpdateData.h
	source/qextPatternView.cpp
	source/qextPatternView.h
	resource/qextPattern.qrc
	PRECOMPILED_HEADER
	source/qextPatternPch.h
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
