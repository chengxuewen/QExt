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


qext_configure_feature("ENABLE_ASSERT" PUBLIC
    LABEL "Enable this to build enable assert"
    CONDITION ON)

qext_configure_feature("ENABLE_CHECK" PUBLIC
    LABEL "Enable this to build enable check"
    CONDITION ON)

qext_configure_feature("ENABLE_DEBUG" PUBLIC
    LABEL "Enable this to build enable debug"
    CONDITION ON)

qext_configure_feature("ENABLE_VARIADIC_TEMPLATES" PUBLIC
    LABEL "Enable this to use cxx_variadic_templates"
    CONDITION OFF)

qext_configure_feature("USE_3rdQJSON_BACKEND" PUBLIC
    LABEL "Enable this to build use 3rd cJSON backend"
    CONDITION ON)
qext_configure_feature("USE_CJSON_BACKEND" PUBLIC
    LABEL "Enable this to build use cJSON backend"
    AUTODETECT QEXT_USE_QT5
    CONDITION QEXT_USE_QT4)
qext_configure_feature("ENABLE_JSON" PUBLIC
    LABEL "Enable this to build enable json"
    AUTODETECT OFF
    CONDITION QEXT_FEATURE_USE_CJSON_BACKEND OR QEXT_FEATURE_USE_3rdQJSON_BACKEND OR QEXT_QT_HAS_QJSON)

qext_configure_definition("QEXT_VERSION_NAME" PUBLIC VALUE "\"${QEXT_VERSION_NAME}\"")
qext_configure_definition("QEXT_VERSION_MAJOR" PUBLIC VALUE ${QEXT_VERSION_MAJOR})
qext_configure_definition("QEXT_VERSION_MINOR" PUBLIC VALUE ${QEXT_VERSION_MINOR})
qext_configure_definition("QEXT_VERSION_PATCH" PUBLIC VALUE ${QEXT_VERSION_PATCH})
qext_configure_definition("QEXT_VERSION_TWEAK" PUBLIC VALUE ${QEXT_VERSION_TWEAK})

qext_configure_definition("QEXT_SYSTEM_NAME" PUBLIC VALUE ${QEXT_SYSTEM_NAME})
qext_configure_definition("QEXT_SYSTEM_VERSION" PUBLIC VALUE ${QEXT_SYSTEM_VERSION})
qext_configure_definition("QEXT_SYSTEM_PROCESSOR" PUBLIC VALUE ${QEXT_SYSTEM_PROCESSOR})

qext_configure_definition("QEXT_CXX_STANDARD" PUBLIC VALUE ${QEXT_CXX_STANDARD})
qext_configure_definition("QEXT_CXX_COMPILER_ID" PUBLIC VALUE "\"${QEXT_CXX_COMPILER_ID}\"")

# QExt lib type
if (BUILD_SHARED_LIBS)
    qext_configure_definition("QEXT_BUILD_SHARED" PUBLIC)
else ()
    qext_configure_definition("QEXT_BUILD_STATIC" PUBLIC)
endif ()

# QExt debug/optimization type
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    qext_configure_definition("QEXT_BUILD_DEBUG" PUBLIC)
endif ()
