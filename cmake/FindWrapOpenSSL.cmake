########################################################################################################################
#
# Library: QExt
#
# Copyright (C) 2025 ChengXueWen.
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

# We can't create the same interface imported target multiple times, CMake will complain if we do
# that. This can happen if the find_package call is done in multiple different subdirectories.
if(TARGET QExt3rdparty::WrapOpenSSL)
    set(QExtWrapOpenSSL_FOUND ON)
    return()
endif()

if(ANDROID)
    include(${ANDROID_SDK_ROOT}/android_openssl/CMakeLists.txt)
    add_library(QExt3rdparty::WrapOpenSSL INTERFACE IMPORTED)
    target_link_libraries(QExt3rdparty::WrapOpenSSL INTERFACE ${ANDROID_EXTRA_LIBS})
    set_target_properties(QExt3rdparty::WrapOpenSSL PROPERTIES QT_ANDROID_EXTRA_LIBS "${ANDROID_EXTRA_LIBS}")
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ANDROID_EXTRA_LIBS}
        "${QEXT_BUILD_DIR}/${QEXT_INSTALL_DLLDIR}/"
        WORKING_DIRECTORY "${QExtWrapOpenSSL_ROOT_DIR}"
        RESULT_VARIABLE COPY_RESULT)
    qext_install(FILES "${ANDROID_EXTRA_LIBS}" DESTINATION "${QEXT_INSTALL_DLLDIR}")
else()
    set(QExtWrapOpenSSL_DIR_NAME "openssl-3.0.16")
    set(QExtWrapOpenSSL_URL_NAME "${QExtWrapOpenSSL_DIR_NAME}.7z")
    set(QExtWrapOpenSSL_URL_PATH "${PROJECT_SOURCE_DIR}/3rdparty/${QExtWrapOpenSSL_URL_NAME}")
    set(QExtWrapOpenSSL_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${QExtWrapOpenSSL_DIR_NAME}")
    set(QExtWrapOpenSSL_SOURCE_DIR "${QExtWrapOpenSSL_ROOT_DIR}/source" CACHE INTERNAL "" FORCE)
    set(QExtWrapOpenSSL_BUILD_DIR "${QExtWrapOpenSSL_ROOT_DIR}/source" CACHE INTERNAL "" FORCE)
    set(QExtWrapOpenSSL_INSTALL_DIR "${QExtWrapOpenSSL_ROOT_DIR}/install" CACHE INTERNAL "" FORCE)
    qext_stamp_file_info(QExtWrapOpenSSL OUTPUT_DIR "${QExtWrapOpenSSL_ROOT_DIR}")
    qext_fetch_3rdparty(QExtWrapOpenSSL URL "${QExtWrapOpenSSL_URL_PATH}")
    if(NOT EXISTS ${QExtWrapOpenSSL_STAMP_FILE_PATH})
        if(NOT EXISTS ${QExtWrapOpenSSL_SOURCE_DIR})
            message(FATAL_ERROR "${QExtWrapOpenSSL_DIR_NAME} FetchContent failed.")
        endif()

        execute_process(
            COMMAND ${CMAKE_COMMAND} -E make_directory ${QExtWrapOpenSSL_BUILD_DIR}
            WORKING_DIRECTORY "${QExtWrapOpenSSL_ROOT_DIR}"
            RESULT_VARIABLE MKDIR_RESULT)
        if(NOT (MKDIR_RESULT MATCHES 0))
            message(FATAL_ERROR "${QExtWrapOpenSSL_DIR_NAME} lib build directory make failed.")
        endif()

        execute_process(
            COMMAND ./Configure
            --prefix=${QExtWrapOpenSSL_INSTALL_DIR}
            --openssldir=${QExtWrapOpenSSL_INSTALL_DIR}/ssl
            WORKING_DIRECTORY "${QExtWrapOpenSSL_BUILD_DIR}"
            RESULT_VARIABLE CONFIGURE_RESULT)
        if(CONFIGURE_RESULT MATCHES 0)
            message(STATUS "${QExtWrapOpenSSL_DIR_NAME} configure success")
            execute_process(
                COMMAND make -j${QEXT_NUMBER_OF_ASYNC_JOBS}
                WORKING_DIRECTORY "${QExtWrapOpenSSL_BUILD_DIR}"
                RESULT_VARIABLE BUILD_RESULT)
            if(BUILD_RESULT MATCHES 0)
                message(STATUS "${QExtWrapOpenSSL_DIR_NAME} build success")
                execute_process(
                    COMMAND make install
                    WORKING_DIRECTORY "${QExtWrapOpenSSL_BUILD_DIR}"
                    RESULT_VARIABLE INSTALL_RESULT)
                if(BUILD_RESULT MATCHES 0)
                    message(STATUS "${QExtWrapOpenSSL_DIR_NAME} install success")
                    qext_make_stamp_file("${QExtWrapOpenSSL_STAMP_FILE_PATH}")
                else()
                    message(FATAL_ERROR "${QExtWrapOpenSSL_DIR_NAME} install failed.")
                endif()
            else()
                message(FATAL_ERROR "${QExtWrapOpenSSL_DIR_NAME} build failed.")
            endif()
        else()
            message(FATAL_ERROR "${QExtWrapOpenSSL_DIR_NAME} configure failed.")
        endif()
    endif()
    # wrap lib
    add_library(QExt3rdparty::WrapOpenSSL INTERFACE IMPORTED)
    find_package(PkgConfig REQUIRED)
    set(PKG_CONFIG_PATH_BKG "${PKG_CONFIG_PATH}")
    set(ENV{PKG_CONFIG_PATH} "${QExtWrapOpenSSL_INSTALL_DIR}/lib64/pkgconfig")
    pkg_check_modules(OpenSSL REQUIRED openssl>=3.0)
    set(ENV{PKG_CONFIG_PATH} "${PKG_CONFIG_PATH_BKG}")
    target_link_libraries(QExt3rdparty::WrapOpenSSL INTERFACE ${OpenSSL_LIBRARIES})
    target_link_directories(QExt3rdparty::WrapOpenSSL INTERFACE ${OpenSSL_LIBRARY_DIRS})
    if(UNIX)
        file(GLOB QExtWrapOpenSSL_LIBRARIES "${QExtWrapOpenSSL_INSTALL_DIR}/lib64/*.so*")
    else()
        file(GLOB QExtWrapOpenSSL_LIBRARIES "${QExtWrapOpenSSL_INSTALL_DIR}/lib64/*.dll*")
    endif()
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QExtWrapOpenSSL_LIBRARIES}
        "${QEXT_BUILD_DIR}/${QEXT_INSTALL_DLLDIR}/"
        WORKING_DIRECTORY "${QExtWrapOpenSSL_ROOT_DIR}"
        RESULT_VARIABLE COPY_RESULT)
    qext_install(FILES "${QExtWrapOpenSSL_LIBRARIES}" DESTINATION "${QEXT_INSTALL_DLLDIR}")
endif()
set(QExtWrapOpenSSL_FOUND ON)
