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

if(NOT DEFINED QMLTYPES_FILE)
    message(FATAL_ERROR "QMLTYPES_FILE not set")
endif()
if(NOT EXISTS "${QMLTYPES_FILE}")
    message(FATAL_ERROR "qmltypes '${QMLTYPES_FILE}' not exist")
endif()

if(NOT DEFINED IMPORT_VERSION)
    message(FATAL_ERROR "IMPORT_VERSION not set")
endif()
set(IMPORT_VERSION_OLD_TEXT -1.-1)
set(IMPORT_VERSION_NEW_TEXT ${IMPORT_VERSION})

if(NOT DEFINED MINOR_VERSION)
    message(FATAL_ERROR "MINOR_VERSION not set")
endif()
set(MINOR_VERSION_OLD_TEXT [-1])
set(MINOR_VERSION_NEW_TEXT [${MINOR_VERSION}])

file(READ "${QMLTYPES_FILE}" MODIFIED_CONTENT)
string(REPLACE "${IMPORT_VERSION_OLD_TEXT}" "${IMPORT_VERSION_NEW_TEXT}" MODIFIED_CONTENT "${MODIFIED_CONTENT}")
string(REPLACE "${MINOR_VERSION_OLD_TEXT}" "${MINOR_VERSION_NEW_TEXT}" MODIFIED_CONTENT "${MODIFIED_CONTENT}")
file(WRITE "${QMLTYPES_FILE}" "${MODIFIED_CONTENT}")
