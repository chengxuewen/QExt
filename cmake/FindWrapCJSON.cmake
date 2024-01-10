########################################################################################################################
#
# Library: QExt
#
# Copyright (C) 2023 ChengXueWen.
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
if(TARGET QExt3rdparty::WrapCJSON)
    set(WrapCJSON_FOUND ON)
    return()
endif()

find_package(cjson CONFIG)
add_library(QExt3rdparty::WrapCJSON INTERFACE IMPORTED)
if(NOT cjson_FOUND)
    set(CJSON_DIR_NAME "cJSON-1.7.16")
    set(CJSON_TAR_GZ_NAME "cJSON-1.7.16.tar.gz")
    set(CJSON_TAR_GZ_PATH "${PROJECT_SOURCE_DIR}/3rdparty/${CJSON_TAR_GZ_NAME}")
    set(CJSON_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${CJSON_DIR_NAME}")
    set(CJSON_BUILD_DIR "${CJSON_ROOT_DIR}/build")
    set(CJSON_SOURCE_DIR "${CJSON_ROOT_DIR}/source")
    set(CJSON_INSTALL_DIR "${CJSON_ROOT_DIR}/install")
    if(NOT EXISTS ${CJSON_SOURCE_DIR})
        include(FetchContent)
        FetchContent_Declare(
            QExt-cJSON
            SOURCE_DIR ${CJSON_SOURCE_DIR}
            BINARY_DIR ${CJSON_BUILD_DIR}
            URL ${CJSON_TAR_GZ_PATH})
        FetchContent_Populate(QExt-cJSON)
    endif()
    if(NOT EXISTS ${CJSON_INSTALL_DIR})
        if(NOT EXISTS ${CJSON_SOURCE_DIR})
            message(FATAL_ERROR "${CJSON_DIR_NAME} FetchContent failed.")
        endif()
        execute_process(
            COMMAND ${CMAKE_COMMAND}
            -G${CMAKE_GENERATOR}
            -DBUILD_SHARED_LIBS=OFF
            -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
            -DCMAKE_INSTALL_PREFIX=${CJSON_INSTALL_DIR} ${CJSON_SOURCE_DIR}
            WORKING_DIRECTORY "${CJSON_BUILD_DIR}"
            RESULT_VARIABLE CONFIGURE_RESULT)
        if(CONFIGURE_RESULT MATCHES 0)
            message(STATUS "${CJSON_DIR_NAME} configure success")
            execute_process(
                COMMAND ${CMAKE_COMMAND} --build ./ --parallel ${QEXT_NUMBER_OF_ASYNC_JOBS} --config Release
                WORKING_DIRECTORY "${CJSON_BUILD_DIR}"
                RESULT_VARIABLE BUILD_RESULT)
            if(BUILD_RESULT MATCHES 0)
                message(STATUS "${CJSON_DIR_NAME} build success")
                execute_process(
                    COMMAND ${CMAKE_COMMAND} --install ./
                    WORKING_DIRECTORY "${CJSON_BUILD_DIR}"
                    RESULT_VARIABLE INSTALL_RESULT)
                if(BUILD_RESULT MATCHES 0)
                    message(STATUS "${CJSON_DIR_NAME} install success")
                else()
                    message(FATAL_ERROR "${CJSON_DIR_NAME} install failed.")
                endif()
            else()
                message(FATAL_ERROR "${CJSON_DIR_NAME} build failed.")
            endif()
        else()
            message(FATAL_ERROR "${CJSON_DIR_NAME} configure failed.")
        endif()
    endif()
    find_package(cjson PATHS ${CJSON_INSTALL_DIR} REQUIRED)
endif()
target_link_libraries(QExt3rdparty::WrapCJSON INTERFACE cjson)
set(WrapCJSON_FOUND ON)
