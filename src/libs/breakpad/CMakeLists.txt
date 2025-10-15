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
set(QEXT_BREAKPAD_REPORTER_NAME "QExtBreakpadReporter" CACHE INTERNAL "" FORCE)
set(QEXT_LIB_LINK_LIBRARIES)
set(QEXT_LIB_NAME Breakpad)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Network
        Qt${QEXT_QT_VERSION_MAJOR}::Widgets)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_LIB_LINK_LIBRARIES QExt::Core)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
qext_add_library(${QEXT_LIB_NAME}
    EXCEPTIONS
    SOURCES
    source/qextBreakpadGlobal.h
    source/qextBreakpadHandler.cpp
    source/qextBreakpadHandler.h
    source/qextBreakpadHttpUploader.cpp
    source/qextBreakpadHttpUploader.h
    resources/qextBreakpad.qrc
    PRECOMPILED_HEADER
    source/qextBreakpadPch.h
    PUBLIC_LIBRARIES
    ${QEXT_LIB_LINK_LIBRARIES})

qext_find_package(WrapBreakpad PROVIDED_TARGETS QExt3rdparty::WrapBreakpad)
qext_internal_extend_target(${QEXT_LIB_NAME} LIBRARIES QExt3rdparty::WrapBreakpad)
if(QExtWrapBreakpad_USE_SOURCE)
    qext_internal_extend_target(${QEXT_LIB_NAME}
        INCLUDE_DIRECTORIES
        ${QExtWrapBreakpad_SOURCE_DIR}/src)
    qext_internal_extend_target(${QEXT_LIB_NAME}
        SOURCES
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/minidump_file_writer.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/common/convert_UTF.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/common/md5.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/common/string_conversion.cc
        CONDITION UNIX)
    qext_internal_extend_target(${QEXT_LIB_NAME}
        SOURCES
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/mac/crash_generation/crash_generation_client.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/mac/handler/breakpad_nlist_64.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/mac/handler/dynamic_images.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/mac/handler/exception_handler.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/mac/handler/minidump_generator.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/common/mac/MachIPC.mm
        ${QExtWrapBreakpad_SOURCE_DIR}/src/common/mac/bootstrap_compat.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/common/mac/file_id.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/common/mac/macho_id.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/common/mac/macho_utilities.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/common/mac/macho_walker.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/common/mac/string_utilities.cc
        CONDITION APPLE)
    qext_internal_extend_target(${QEXT_LIB_NAME}
        SOURCES
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/ios/handler/ios_exception_minidump_generator.mm
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/ios/Breakpad.mm
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/ios/BreakpadController.mm
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/ios/exception_handler_no_mach.cc
        CONDITION IOS)
    qext_internal_extend_target(${QEXT_LIB_NAME}
        SOURCES
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/linux/crash_generation/crash_generation_client.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/linux/dump_writer_common/thread_info.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/linux/dump_writer_common/ucontext_reader.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/linux/handler/exception_handler.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/linux/handler/minidump_descriptor.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/linux/log/log.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/linux/microdump_writer/microdump_writer.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/linux/minidump_writer/linux_core_dumper.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/linux/minidump_writer/linux_dumper.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/linux/minidump_writer/linux_ptrace_dumper.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/linux/minidump_writer/minidump_writer.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/common/linux/breakpad_getcontext.S
        ${QExtWrapBreakpad_SOURCE_DIR}/src/common/linux/elfutils.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/common/linux/file_id.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/common/linux/guid_creator.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/common/linux/linux_libc_support.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/common/linux/memory_mapped_file.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/common/linux/safe_readlink.cc
        CONDITION UNIX AND NOT APPLE)
    qext_internal_extend_target(${QEXT_LIB_NAME}
        SOURCES
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/windows/crash_generation/crash_generation_client.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/client/windows/handler/exception_handler.cc
        ${QExtWrapBreakpad_SOURCE_DIR}/src/common/windows/guid_string.cc
        DEFINES UNICODE
        CONDITION WIN32)
endif()


#-----------------------------------------------------------------------------------------------------------------------
# Add lib examples and tests
#-----------------------------------------------------------------------------------------------------------------------
qext_add_subdirectory(examples QEXT_BUILD_EXAMPLES)
qext_add_subdirectory(tests QEXT_BUILD_TESTS)
qext_add_subdirectory(tools)
