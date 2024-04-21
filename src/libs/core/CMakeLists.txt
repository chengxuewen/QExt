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

if(UNIX)
    list(APPEND QEXT_LIB_LINK_LIBRARIES ${CMAKE_DL_LIBS})
endif()

if(APPLE)
    list(APPEND QEXT_LIB_LINK_LIBRARIES "-framework Cocoa" "iconv")
endif()

if(WIN32)
    # shlwapi.lib           ->  shell,string
    # ws2_32.lib            ->  network
    # Synchronization.lib   ->  sync
    if(${CMAKE_SYSTEM_VERSION} EQUAL 6.1) # Windows 7
    elseif(${CMAKE_SYSTEM_VERSION} GREATER_EQUAL 6.2) # Windows 8
        list(APPEND QEXT_LIB_LINK_LIBRARIES Synchronization.lib)
    endif()
    list(APPEND QEXT_LIB_LINK_LIBRARIES shlwapi.lib ws2_32.lib)
    if(NOT MINGW)
        list(APPEND QEXT_LIB_LINK_LIBRARIES dbghelp)
    endif()
endif()

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore)
elseif (QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt${QEXT_QT_VERSION_MAJOR}::Core)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
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
    source/tools/qextBackTrace.cpp
    source/tools/qextBackTrace.h
    source/tools/qextDiskInfo.cpp
    source/tools/qextDiskInfo.h
    source/tools/qextException.cpp
    source/tools/qextException.h
    source/tools/qextLinearBuffer.cpp
    source/tools/qextLinearBuffer.h
    source/tools/qextNumeric.cpp
    source/tools/qextNumeric.h
    source/tools/qextTag.cpp
    source/tools/qextTag.h
    source/tools/qextSpinlock.h
    source/tools/qextOnceFlag.h
    source/tools/qextTypeInfo.h
    source/tools/qextTypeTrait.h
    source/tools/qextUniquePointer.h
    source/tools/qextWinSystemLibrary_p.h
    source/tools/qextWinSystemLibrary.cpp
    source/utils/qextCodecUtils.cpp
    source/utils/qextCodecUtils.h
    source/utils/qextDateTimeUtils.cpp
    source/utils/qextHostInfoUtils_p.h
    source/utils/qextDateTimeUtils.h
    source/utils/qextHostInfoUtils.cpp
    source/utils/qextHostInfoUtils.h
    source/utils/qextNetworkUtils.cpp
    source/utils/qextNetworkUtils.h
    source/utils/qextUtils.cpp
    source/utils/qextUtils.h
    PRECOMPILED_HEADER
    source/qextPch.h
    PUBLIC_LIBRARIES
    ${QEXT_LIB_LINK_LIBRARIES})


if(QEXT_FEATURE_ENABLE_JSON)
    qext_internal_extend_target(Core
        SOURCES
        source/tools/qextJson.cpp
        source/tools/qextJson.h
        source/tools/qextJson_p.h)
    if(QEXT_FEATURE_USE_CJSON_BACKEND)
        qext_find_package(WrapCJSON PROVIDED_TARGETS QExt3rdparty::WrapCJSON)
        qext_internal_extend_target(Core
            LIBRARIES
            QExt3rdparty::WrapCJSON)
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
