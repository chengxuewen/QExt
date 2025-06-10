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

add_subdirectory(core)
qext_add_subdirectory(gui QEXT_ENABLE_LIB_GUI)
qext_add_subdirectory(plot QEXT_ENABLE_LIB_PLOT)
qext_add_subdirectory(widgets QEXT_ENABLE_LIB_WIDGETS)
qext_add_subdirectory(serialport QEXT_ENABLE_LIB_SERIALPORT)
qext_add_subdirectory(daview QEXT_ENABLE_LIB_DAVIEW)
qext_add_subdirectory(patterns QEXT_ENABLE_LIB_PATTERNS)
qext_add_subdirectory(fonticon QEXT_ENABLE_LIB_FONTICON)
qext_add_subdirectory(keyboard QEXT_ENABLE_LIB_KEYBOARD)
qext_add_subdirectory(graphics QEXT_ENABLE_LIB_GRAPHICS)
qext_add_subdirectory(blueprint QEXT_ENABLE_LIB_BLUEPRINT)
qext_add_subdirectory(recordplay QEXT_ENABLE_LIB_RECORDPLAY)
qext_add_subdirectory(devicewatcher QEXT_ENABLE_LIB_DEVICEWATCHER)
