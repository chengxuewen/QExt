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
set(QEXT_TEST_LINK_LIBRARIES)
set(QEXT_TEST_INCLUDE_DIRECTORIES)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_TEST_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui Qt4::QtTest)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_TEST_LINK_LIBRARIES
            Qt${QEXT_QT_VERSION_MAJOR}::Core
            Qt${QEXT_QT_VERSION_MAJOR}::Test
    )
else()
    message(FATAL_ERROR "Not find Qt package")
endif()


#-----------------------------------------------------------------------------------------------------------------------
# add tests
#-----------------------------------------------------------------------------------------------------------------------
qext_internal_add_test(tst_QExtCoreTypeTrait
        SOURCES
        tools/tst_qextTypeTrait.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${QEXT_OUTPUT_TEST_DIR})
qext_internal_add_test(tst_QExtCorePointerFunctor
        SOURCES
        invoke/tst_qextPointerFunctor.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${QEXT_OUTPUT_TEST_DIR})
qext_internal_add_test(tst_QExtCoreMemberFunctor
        SOURCES
        invoke/tst_qextMemberFunctor.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${QEXT_OUTPUT_TEST_DIR})
qext_internal_add_test(tst_QExtCoreFunction
        SOURCES
        invoke/tst_qextFunction.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${QEXT_OUTPUT_TEST_DIR})
qext_internal_add_test(tst_QExtCoreVisitor
        SOURCES
        invoke/tst_qextVisitor.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${QEXT_OUTPUT_TEST_DIR})
qext_internal_add_test(tst_QExtCoreTrackable
        SOURCES
        invoke/tst_qextTrackable.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${QEXT_OUTPUT_TEST_DIR})
qext_internal_add_test(tst_QExtCoreBindFunctor
        SOURCES
        invoke/tst_qextBindFunctor.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${QEXT_OUTPUT_TEST_DIR})
qext_internal_add_test(tst_QExtCoreBindReturnFunctor
        SOURCES
        invoke/tst_qextBindReturnFunctor.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${QEXT_OUTPUT_TEST_DIR})
qext_internal_add_test(tst_QExtCoreConnection
        SOURCES
        invoke/tst_qextConnection.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${QEXT_OUTPUT_TEST_DIR})
qext_internal_add_test(tst_QExtCoreFunctorTrait
        SOURCES
        invoke/tst_qextFunctorTrait.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${QEXT_OUTPUT_TEST_DIR})
qext_internal_add_test(tst_QExtCoreHideFunctor
        SOURCES
        invoke/tst_qextHideFunctor.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${QEXT_OUTPUT_TEST_DIR})
qext_internal_add_test(tst_QExtCoreLimitReference
        SOURCES
        invoke/tst_qextLimitReference.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${QEXT_OUTPUT_TEST_DIR})
qext_internal_add_test(tst_QExtCoreReturnTypeDeduce
        SOURCES
        invoke/tst_qextReturnTypeDeduce.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${QEXT_OUTPUT_TEST_DIR})
qext_internal_add_test(tst_QExtCoreRetypeReturnFunctor
        SOURCES
        invoke/tst_qextRetypeReturnFunctor.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${QEXT_OUTPUT_TEST_DIR})
qext_internal_add_test(tst_QExtCoreTrackObjectFunctor
        SOURCES
        invoke/tst_qextTrackObjectFunctor.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${QEXT_OUTPUT_TEST_DIR})
qext_internal_add_test(tst_QExtCoreRetypeFunctor
        SOURCES
        invoke/tst_qextRetypeFunctor.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${QEXT_OUTPUT_TEST_DIR})
qext_internal_add_test(tst_QExtCoreSignal
        SOURCES
        invoke/tst_qextSignal.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${QEXT_OUTPUT_TEST_DIR})
qext_internal_add_test(tst_QExtCoreSlot
        SOURCES
        invoke/tst_qextSlot.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${QEXT_OUTPUT_TEST_DIR})
