#################################################################################
#
# Library: QExt
#
# Copyright (c) ChengXueWen. Contact: 1398831004@qq.com
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#################################################################################


#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(QEXT_LIB_LINK_LIBRARIES)

if (QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore)
elseif (QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
            Qt${QEXT_QT_VERSION_MAJOR}::Core
    )
else ()
    message(FATAL_ERROR "Not find Qt package")
endif ()


#--------------------------------------------------------------------------------
# Add lib target
#--------------------------------------------------------------------------------
qext_add_library(Core
        EXCEPTIONS
        SOURCES
        source/global/qextCompiler.h
        source/global/qextGlobal.h
        source/global/qextPreprocessor.h
        source/global/qextProcessor.h
        source/global/qextSystem.h
        source/invoke/qextAdaptorTrait.h
        source/invoke/qextBindFunctor.h
        source/invoke/qextBindReturnFunctor.h
        source/invoke/qextBoundArgument.h
        source/invoke/qextComposeFunctor.h
        source/invoke/qextConnection.h
        source/invoke/qextConnection.cpp
        source/invoke/qextEmitter.h
        source/invoke/qextFunction.h
        source/invoke/qextFunction.cpp
        source/invoke/qextHideFunctor.h
        source/invoke/qextInPlace.h
        source/invoke/qextLimitReference.h
        source/invoke/qextMemberFunctor.h
        source/invoke/qextPointerFunctor.h
        source/invoke/qextReferenceWrapper.h
        source/invoke/qextReturnTypeDeduce.h
        source/invoke/qextRetypeFunctor.h
        source/invoke/qextRetypeReturnFunctor.h
        source/invoke/qextSignal.h
        source/invoke/qextSignal.cpp
        source/invoke/qextTrackObjectFunctor.h
        source/invoke/qextVisitor.h
        source/tools/qextId.h
        source/tools/qextId.cpp
        source/tools/qextTypeInfo.h
        source/tools/qextTypeTrait.h
        source/tools/qextUniquePointer.h
        PRECOMPILED_HEADER
        source/qextPch.h
        PUBLIC_LIBRARIES
        ${QEXT_LIB_LINK_LIBRARIES})


#--------------------------------------------------------------------------------
# Add lib tests and examples
#--------------------------------------------------------------------------------
if (QEXT_BUILD_TESTS)
    add_subdirectory(tests)
endif ()

if (QEXT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()