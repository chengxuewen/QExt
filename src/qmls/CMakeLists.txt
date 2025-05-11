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

qext_find_qt_tool(moc)
set(QEXT_QT_MOC_EXECUTABLE "${moc_EXECUTABLE}" CACHE INTERNAL "" FORCE)
# message(QEXT_QT_MOC_EXECUTABLE=${QEXT_QT_MOC_EXECUTABLE})
qext_find_qt_tool(rcc)
set(QEXT_QT_RCC_EXECUTABLE "${rcc_EXECUTABLE}" CACHE INTERNAL "" FORCE)
# message(QEXT_QT_RCC_EXECUTABLE=${QEXT_QT_RCC_EXECUTABLE})
qext_find_qt_tool(qmlplugindump)
set(QEXT_QT_QMLPLUGINDUMP_EXECUTABLE "${qmlplugindump_EXECUTABLE}" CACHE INTERNAL "" FORCE)
# set(QEXT_QT_QMLPLUGINDUMP_EXECUTABLE "${QEXT_BUILD_DIR}/${QEXT_DEFAULT_DLLDIR}/qmlplugindump.exe" CACHE INTERNAL "" FORCE)
# message(QEXT_QT_QMLPLUGINDUMP_EXECUTABLE=${QEXT_QT_QMLPLUGINDUMP_EXECUTABLE})

add_subdirectory(qml)
add_subdirectory(quick)
add_subdirectory(toou2d)

list(APPEND QEXT_QML_IMPORT_PATH ${QML_IMPORT_PATH} "${QEXT_BUILD_DIR}/${QEXT_INSTALL_QMLDIR}")
list(REMOVE_DUPLICATES QEXT_QML_IMPORT_PATH)
set(QML_IMPORT_PATH ${QEXT_QML_IMPORT_PATH} CACHE INTERNAL "Qt Creator extra qml import paths" FORCE)
