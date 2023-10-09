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
set(QEXT_LIB_LINK_LIBRARIES)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore Qt4::QtGui)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
            Qt${QEXT_QT_VERSION_MAJOR}::Core
            Qt${QEXT_QT_VERSION_MAJOR}::Gui
    )
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_LIB_LINK_LIBRARIES QExt::Core)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
qext_add_library(GooglePinYin
        EXCEPTIONS
        SOURCES
        source/googlepinyin/atomdictbase.h
        source/googlepinyin/dictbuilder.cpp
        source/googlepinyin/dictbuilder.h
        source/googlepinyin/dictdef.h
        source/googlepinyin/dictlist.cpp
        source/googlepinyin/dictlist.h
        source/googlepinyin/dicttrie.cpp
        source/googlepinyin/dicttrie.h
        source/googlepinyin/lpicache.cpp
        source/googlepinyin/lpicache.h
        source/googlepinyin/matrixsearch.cpp
        source/googlepinyin/matrixsearch.h
        source/googlepinyin/mystdlib.cpp
        source/googlepinyin/mystdlib.h
        source/googlepinyin/ngram.cpp
        source/googlepinyin/ngram.h
        source/googlepinyin/pinyinime.cpp
        source/googlepinyin/pinyinime.h
        source/googlepinyin/searchutility.cpp
        source/googlepinyin/searchutility.h
        source/googlepinyin/spellingtable.cpp
        source/googlepinyin/spellingtable.h
        source/googlepinyin/spellingtrie.cpp
        source/googlepinyin/spellingtrie.h
        source/googlepinyin/sync.cpp
        source/googlepinyin/sync.h
        source/googlepinyin/userdict.cpp
        source/googlepinyin/userdict.h
        source/googlepinyin/splparser.cpp
        source/googlepinyin/splparser.h
        source/googlepinyin/utf16char.cpp
        source/googlepinyin/utf16char.h
        source/googlepinyin/utf16reader.cpp
        source/googlepinyin/utf16reader.h
        source/qextGooglePinYin.cpp
        source/qextGooglePinYin.h
        source/qextGooglePinYinGlobal.h
        source/qextGooglePinYinPch.h
        resource/qextGooglePinYin.qrc
        PUBLIC_LIBRARIES
        ${QEXT_LIB_LINK_LIBRARIES})


#-----------------------------------------------------------------------------------------------------------------------
# Add lib tests and examples
#-----------------------------------------------------------------------------------------------------------------------
if(QEXT_BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(QEXT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
