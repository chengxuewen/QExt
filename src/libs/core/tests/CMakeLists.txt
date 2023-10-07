#################################################################################
#
# Library: QEXT
#
# Copyright (c) ChengXueWen. Contact: 1398831004@qq.com
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0.txt
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#################################################################################

#--------------------------------------------------------------------------------
# Set lib base name and out put path
#--------------------------------------------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${QEXT_OUTPUT_TEST_DIR}/core)
set(LIBRARY_OUTPUT_PATH ${QEXT_OUTPUT_TEST_DIR}/core)


#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(QEXT_TEST_LINK_LIBRARIES)
set(QEXT_TEST_INCLUDE_DIRECTORIES)

if (QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_TEST_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui Qt4::QtTest)
elseif (QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_TEST_LINK_LIBRARIES
            Qt${QEXT_QT_VERSION_MAJOR}::Core
            Qt${QEXT_QT_VERSION_MAJOR}::Test
    )
else ()
    message(FATAL_ERROR "Not find Qt package")
endif ()


#--------------------------------------------------------------------------------
# add tests
#--------------------------------------------------------------------------------
qext_internal_add_test(qext_tst_coreTypeTrait
        SOURCES
        tools/tst_qextTypeTrait.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH})
qext_internal_add_test(tst_QExtCorePointerFunctor
        SOURCES
        invoke/tst_qextPointerFunctor.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH})
qext_internal_add_test(tst_QExtCoreMemberFunctor
        SOURCES
        invoke/tst_qextMemberFunctor.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH})
qext_internal_add_test(tst_QExtCoreFunction
        SOURCES
        invoke/tst_qextFunction.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH})
qext_internal_add_test(tst_QExtCoreVisitor
        SOURCES
        invoke/tst_qextVisitor.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH})
qext_internal_add_test(tst_QExtCoreTrackable
        SOURCES
        invoke/tst_qextTrackable.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH})
qext_internal_add_test(tst_QExtCoreBindFunctor
        SOURCES
        invoke/tst_qextBindFunctor.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH})
qext_internal_add_test(tst_QExtCoreBindReturnFunctor
        SOURCES
        invoke/tst_qextBindReturnFunctor.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH})
qext_internal_add_test(tst_QExtCoreConnection
        SOURCES
        invoke/tst_qextConnection.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH})
qext_internal_add_test(tst_QExtCoreFunctorTrait
        SOURCES
        invoke/tst_qextFunctorTrait.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH})
qext_internal_add_test(tst_QExtCoreHideFunctor
        SOURCES
        invoke/tst_qextHideFunctor.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH})
qext_internal_add_test(tst_QExtCoreLimitReference
        SOURCES
        invoke/tst_qextLimitReference.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH})
qext_internal_add_test(tst_QExtCoreReturnTypeDeduce
        SOURCES
        invoke/tst_qextReturnTypeDeduce.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH})
qext_internal_add_test(tst_QExtCoreRetypeReturnFunctor
        SOURCES
        invoke/tst_qextRetypeReturnFunctor.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH})
qext_internal_add_test(tst_QExtCoreTrackObjectFunctor
        SOURCES
        invoke/tst_qextTrackObjectFunctor.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH})
qext_internal_add_test(tst_QExtCoreRetypeFunctor
        SOURCES
        invoke/tst_qextRetypeFunctor.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH})
qext_internal_add_test(tst_QExtCoreSignal
        SOURCES
        invoke/tst_qextSignal.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH})
qext_internal_add_test(tst_QExtCoreSlot
        SOURCES
        invoke/tst_qextSlot.cpp
        LIBRARIES
        ${QEXT_TEST_LINK_LIBRARIES}
        OUTPUT_DIRECTORY
        ${EXECUTABLE_OUTPUT_PATH})
