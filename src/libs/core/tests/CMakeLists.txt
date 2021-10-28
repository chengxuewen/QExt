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
set(EXECUTABLE_OUTPUT_PATH ${QEXT_TEST_OUTPUT_DIR})
set(LIBRARY_OUTPUT_PATH ${QEXT_TEST_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(qext_test_link_libraries)
set(qext_test_include_directories)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND qext_test_link_libraries Qt4::QtCore Qt4::QtGui Qt4::QtTest)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND qext_test_link_libraries
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Test
        )
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND qext_test_link_libraries QEXTCore)


#--------------------------------------------------------------------------------
# define function
#--------------------------------------------------------------------------------
function(qextCoreAddTest TEST_NAME)
    set(multiValueArgs TEST_SOURCE)
    cmake_parse_arguments(MY "" "" "${multiValueArgs}" "${ARGN}")
    add_executable(${TEST_NAME} ${MY_TEST_SOURCE})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    target_link_libraries(${TEST_NAME} PRIVATE ${qext_test_link_libraries})
    target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${qext_test_include_directories})
    if(QEXT_BUILD_SHARED_LIBS AND WIN32)
        qextMacroCopyDependenceLib(${TEST_NAME} QEXTCore ${EXECUTABLE_OUTPUT_PATH})
    endif()
endfunction()



##--------------------------------------------------------------------------------
## Add test
##--------------------------------------------------------------------------------
qextCoreAddTest(qext_tst_corePointerFunctor TEST_SOURCE tst_qextPointerFunctor.cpp)
qextCoreAddTest(qext_tst_coreMemberFunctor TEST_SOURCE tst_qextMemberFunctor.cpp)
qextCoreAddTest(qext_tst_coreFunction TEST_SOURCE tst_qextFunction.cpp)
qextCoreAddTest(qext_tst_coreVisitor TEST_SOURCE tst_qextVisitor.cpp)
qextCoreAddTest(qext_tst_coreTypeTrait TEST_SOURCE tst_qextTypeTrait.cpp)
qextCoreAddTest(qext_tst_coreTrackable TEST_SOURCE tst_qextTrackable.cpp)
qextCoreAddTest(qext_tst_coreBindFunctor TEST_SOURCE tst_qextBindFunctor.cpp)
qextCoreAddTest(qext_tst_coreBindReturnFunctor TEST_SOURCE tst_qextBindReturnFunctor.cpp)
qextCoreAddTest(qext_tst_coreConnection TEST_SOURCE tst_qextConnection.cpp)
qextCoreAddTest(qext_tst_coreFunctorTrait TEST_SOURCE tst_qextFunctorTrait.cpp)
qextCoreAddTest(qext_tst_coreHideFunctor TEST_SOURCE tst_qextHideFunctor.cpp)
qextCoreAddTest(qext_tst_coreLambda TEST_SOURCE tst_qextLambda.cpp)
qextCoreAddTest(qext_tst_coreLimitReference TEST_SOURCE tst_qextLimitReference.cpp)
qextCoreAddTest(qext_tst_coreReturnTypeDeduce TEST_SOURCE tst_qextReturnTypeDeduce.cpp)
qextCoreAddTest(qext_tst_coreRetypeReturnFunctor TEST_SOURCE tst_qextRetypeReturnFunctor.cpp)
qextCoreAddTest(qext_tst_coreTrackObjectFunctor TEST_SOURCE tst_qextTrackObjectFunctor.cpp)
qextCoreAddTest(qext_tst_coreRetypeFunctor TEST_SOURCE tst_qextRetypeFunctor.cpp)
qextCoreAddTest(qext_tst_coreSignal TEST_SOURCE tst_qextSignal.cpp)
qextCoreAddTest(qext_tst_coreSlot TEST_SOURCE tst_qextSlot.cpp)

