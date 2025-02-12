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

# We can't create the same interface imported target multiple times, CMake will complain if we do
# that. This can happen if the find_package call is done in multiple different subdirectories.
if(TARGET QwtPlot3D3rdparty::WrapFreeGLUT)
    set(WrapFreeGLUT_FOUND ON)
    return()
endif()

find_package(freeglut CONFIG)
if(NOT freeglut_FOUND)
    set(WrapFreeGLUT_DIR_NAME "freeglut-3.6.0")
    set(WrapFreeGLUT_PKG_NAME "freeglut-3.6.0.tar.gz")
    set(WrapFreeGLUT_URL_PATH "${PROJECT_SOURCE_DIR}/3rdparty/${WrapFreeGLUT_PKG_NAME}")
    set(WrapFreeGLUT_ROOT_DIR "${PROJECT_BINARY_DIR}/3rdparty/${WrapFreeGLUT_DIR_NAME}")
    set(WrapFreeGLUT_BUILD_DIR "${WrapFreeGLUT_ROOT_DIR}/build" CACHE INTERNAL "" FORCE)
    set(WrapFreeGLUT_SOURCE_DIR "${WrapFreeGLUT_ROOT_DIR}/source" CACHE INTERNAL "" FORCE)
    set(WrapFreeGLUT_INSTALL_DIR "${WrapFreeGLUT_ROOT_DIR}/install" CACHE INTERNAL "" FORCE)
    if(NOT EXISTS ${WrapFreeGLUT_SOURCE_DIR})
        include(FetchContent)
        FetchContent_Declare(
            QwtPlot3D3rdparty-freeglut-3.6.0
            SOURCE_DIR ${WrapFreeGLUT_SOURCE_DIR}
            BINARY_DIR ${WrapFreeGLUT_BUILD_DIR}
            DOWNLOAD_EXTRACT_TIMESTAMP FALSE
            URL ${WrapFreeGLUT_URL_PATH})
        FetchContent_Populate(QwtPlot3D3rdparty-freeglut-3.6.0)
    endif()
    if(NOT EXISTS ${WrapFreeGLUT_INSTALL_DIR})
        if(NOT EXISTS ${WrapFreeGLUT_SOURCE_DIR})
            message(FATAL_ERROR "${WrapFreeGLUT_DIR_NAME} FetchContent failed.")
        endif()
        execute_process(
            COMMAND ${CMAKE_COMMAND}
            -G${CMAKE_GENERATOR}
            -DFREEGLUT_GLES=ON
            # -DFREEGLUT_WAYLAND=ON
            -DFREEGLUT_BUILD_SHARED_LIBS=OFF
            -DCMAKE_INSTALL_PREFIX=${WrapFreeGLUT_INSTALL_DIR}
            ${WrapFreeGLUT_SOURCE_DIR}
            WORKING_DIRECTORY "${WrapFreeGLUT_BUILD_DIR}"
            RESULT_VARIABLE CONFIGURE_RESULT)
        if(CONFIGURE_RESULT MATCHES 0)
            message(STATUS "${WrapFreeGLUT_DIR_NAME} configure success")
            execute_process(
                COMMAND ${CMAKE_COMMAND} --build ./ --parallel ${QEXT_NUMBER_OF_ASYNC_JOBS} --config Release
                WORKING_DIRECTORY "${WrapFreeGLUT_BUILD_DIR}"
                RESULT_VARIABLE BUILD_RESULT)
            if(BUILD_RESULT MATCHES 0)
                message(STATUS "${WrapFreeGLUT_DIR_NAME} build success")
                execute_process(
                    COMMAND ${CMAKE_COMMAND} --install ./
                    WORKING_DIRECTORY "${WrapFreeGLUT_BUILD_DIR}"
                    RESULT_VARIABLE INSTALL_RESULT)
                if(BUILD_RESULT MATCHES 0)
                    message(STATUS "${WrapFreeGLUT_DIR_NAME} install success")
                else()
                    message(FATAL_ERROR "${WrapFreeGLUT_DIR_NAME} install failed.")
                endif()
            else()
                message(FATAL_ERROR "${WrapFreeGLUT_DIR_NAME} build failed.")
            endif()
        else()
            message(FATAL_ERROR "${WrapFreeGLUT_DIR_NAME} configure failed.")
        endif()
    endif()
    find_package(freeglut PATHS ${WrapFreeGLUT_INSTALL_DIR} REQUIRED)
endif()
add_library(QwtPlot3D3rdparty::WrapFreeGLUT INTERFACE IMPORTED GLOBAL)
target_link_libraries(QwtPlot3D3rdparty::WrapFreeGLUT INTERFACE freeglut)
set(WrapFreeGLUT_FOUND ON)
