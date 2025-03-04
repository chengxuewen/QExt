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
set(QEXT_TEST_LINK_LIBRARIES QExt::Core)
set(QEXT_TEST_INCLUDE_DIRECTORIES)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_TEST_LINK_LIBRARIES Qt4::QtCore Qt4::QtTest Qt4::QtGui)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_TEST_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Test
        Qt${QEXT_QT_VERSION_MAJOR}::Gui
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

find_package(Threads)
list(APPEND QEXT_TEST_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

#-----------------------------------------------------------------------------------------------------------------------
# add tests
#-----------------------------------------------------------------------------------------------------------------------
qext_internal_add_test(QExtTstCoreTypeTrait
    SOURCES
    tools/tst_qextTypeTrait.cpp
    LIBRARIES
    ${QEXT_TEST_LINK_LIBRARIES}
    OUTPUT_DIRECTORY
    ${QEXT_INSTALL_TESTSDIR})
qext_internal_add_test(QExtTstCoreTSValue
    SOURCES
    tools/tst_qextTSValue.cpp
    LIBRARIES
    ${QEXT_TEST_LINK_LIBRARIES}
    OUTPUT_DIRECTORY
    ${QEXT_INSTALL_TESTSDIR})
qext_internal_add_test(QExtTstCoreInvoke
    SOURCES
    tools/tst_qextInvoke.cpp
    LIBRARIES
    ${QEXT_TEST_LINK_LIBRARIES}
    OUTPUT_DIRECTORY
    ${QEXT_INSTALL_TESTSDIR})
qext_internal_add_test(QExtTstCoreMemory
    SOURCES
    tools/tst_qextMemory.cpp
    LIBRARIES
    ${QEXT_TEST_LINK_LIBRARIES}
    OUTPUT_DIRECTORY
    ${QEXT_INSTALL_TESTSDIR})
qext_internal_add_test(QExtTstCoreOptional
    SOURCES
    tools/tst_qextOptional.cpp
    LIBRARIES
    ${QEXT_TEST_LINK_LIBRARIES}
    OUTPUT_DIRECTORY
    ${QEXT_INSTALL_TESTSDIR})
qext_internal_add_test(QExtTstCoreVariant
    SOURCES
    tools/tst_qextVariant.cpp
    LIBRARIES
    ${QEXT_TEST_LINK_LIBRARIES}
    OUTPUT_DIRECTORY
    ${QEXT_INSTALL_TESTSDIR})
qext_internal_add_test(QExtTstCoreConcurrent
    SOURCES
    tools/tst_qextConcurrent.cpp
    LIBRARIES
    ${QEXT_TEST_LINK_LIBRARIES}
    OUTPUT_DIRECTORY
    ${QEXT_INSTALL_TESTSDIR})
qext_internal_add_test(QExtTstCoreNumeric
    SOURCES
    tools/tst_qextNumeric.cpp
    LIBRARIES
    ${QEXT_TEST_LINK_LIBRARIES}
    OUTPUT_DIRECTORY
    ${QEXT_INSTALL_TESTSDIR})
qext_internal_add_test(QExtTstCoreDatatime
    SOURCES
    utils/tst_qextDataTimeUtils.cpp
    LIBRARIES
    ${QEXT_TEST_LINK_LIBRARIES}
    OUTPUT_DIRECTORY
    ${QEXT_INSTALL_TESTSDIR})
qext_internal_add_test(QExtTstCoreNetwork
    SOURCES
    utils/tst_qextNetworkUtils.cpp
    LIBRARIES
    ${QEXT_TEST_LINK_LIBRARIES}
    OUTPUT_DIRECTORY
    ${QEXT_INSTALL_TESTSDIR})
qext_internal_add_test(QExtTstCoreCodec
    SOURCES
    utils/tst_qextCodecUtils.cpp
    LIBRARIES
    ${QEXT_TEST_LINK_LIBRARIES}
    OUTPUT_DIRECTORY
    ${QEXT_INSTALL_TESTSDIR})
qext_internal_add_test(QExtTstCoreCommonUtils
    SOURCES
    utils/tst_qextCommonUtils.cpp
    LIBRARIES
    ${QEXT_TEST_LINK_LIBRARIES}
    OUTPUT_DIRECTORY
    ${QEXT_INSTALL_TESTSDIR})

qext_internal_add_test(QExtTstCoreJson
    SOURCES
    tools/json/tst_qextJson.cpp
    LIBRARIES
    ${QEXT_TEST_LINK_LIBRARIES}
    OUTPUT_DIRECTORY
    ${QEXT_INSTALL_TESTSDIR})
add_custom_command(TARGET QExtTstCoreJson
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/tools/json/testdata ${QEXT_INSTALL_TESTSDIR}/json
    COMMENT "Copying json testdata directory to ${QEXT_INSTALL_TESTSDIR}"
    POST_BUILD)
