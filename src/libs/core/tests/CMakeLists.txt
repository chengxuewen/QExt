#################################################################################
#
# Library: QEXT
#
# Copyright (c) ChengXueWen. Contact: 1398831004@qq.com
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0.txt
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#################################################################################

#--------------------------------------------------------------------------------
# Set lib base name and out put path
#--------------------------------------------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${QEXT_TEST_OUTPUT_DIR})
set(LIBRARY_OUTPUT_PATH ${QEXT_TEST_OUTPUT_DIR})



#--------------------------------------------------------------------------------
# Add lib link libraries
#--------------------------------------------------------------------------------
set(_test_link_libraries)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND _test_link_libraries Qt4::QtCore Qt4::QtTest)
elseif(QEXT_QT_VERSION_MAJOR EQUAL 5)
    list(APPEND _test_link_libraries Qt5::Core Qt5::Test)
else()
    message(FATAL_ERROR "----QEXT---- Not find Qt package")
endif()

list(APPEND _test_link_libraries QEXTCore)



#--------------------------------------------------------------------------------
# Add tst_qextobject test
#--------------------------------------------------------------------------------
set(_test_name tst_qextobject)
add_executable(${_test_name}
    qextsimpleobject.h
    tst_qextobject.cpp
    qextsimpleobject.cpp
    )
add_test(NAME ${_test_name} COMMAND ${_test_name})
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})



#--------------------------------------------------------------------------------
# Add tst_qextfunctortrait test
#--------------------------------------------------------------------------------
set(_test_name tst_qextfunctortrait)
add_executable(${_test_name}
    tst_qextfunctortrait.cpp
    )
add_test(NAME ${_test_name} COMMAND ${_test_name})
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})


#--------------------------------------------------------------------------------
# Add tst_qextpointerfunctor test
#--------------------------------------------------------------------------------
set(_test_name tst_qextpointerfunctor)
add_executable(${_test_name}
    tst_qextpointerfunctor.cpp
    )
add_test(NAME ${_test_name} COMMAND ${_test_name})
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})



#--------------------------------------------------------------------------------
# Add tst_qextmemberfunctor test
#--------------------------------------------------------------------------------
set(_test_name tst_qextmemberfunctor)
add_executable(${_test_name}
    tst_qextmemberfunctor.cpp
    )
add_test(NAME ${_test_name} COMMAND ${_test_name})
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})



#--------------------------------------------------------------------------------
# Add tst_qexttrackable test
#--------------------------------------------------------------------------------
set(_test_name tst_qexttrackable)
add_executable(${_test_name}
    tst_qexttrackable.cpp
    )
add_test(NAME ${_test_name} COMMAND ${_test_name})
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})



#--------------------------------------------------------------------------------
# Add tst_qextslot test
#--------------------------------------------------------------------------------
set(_test_name tst_qextslot)
add_executable(${_test_name}
    tst_qextslot.cpp
    )
add_test(NAME ${_test_name} COMMAND ${_test_name})
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})



#--------------------------------------------------------------------------------
# Add tst_qextsignal test
#--------------------------------------------------------------------------------
set(_test_name tst_qextsignal)
add_executable(${_test_name}
    tst_qextsignal.cpp
    )
add_test(NAME ${_test_name} COMMAND ${_test_name})
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})



#--------------------------------------------------------------------------------
# Add tst_qexttypetrait test
#--------------------------------------------------------------------------------
set(_test_name tst_qexttypetrait)
add_executable(${_test_name}
    tst_qexttypetrait.cpp
    )
add_test(NAME ${_test_name} COMMAND ${_test_name})
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})



#--------------------------------------------------------------------------------
# Add tst_qextvisitor test
#--------------------------------------------------------------------------------
set(_test_name tst_qextvisitor)
add_executable(${_test_name}
    tst_qextvisitor.cpp
    )
add_test(NAME ${_test_name} COMMAND ${_test_name})
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})



#--------------------------------------------------------------------------------
# Add tst_qextresulttypededuce test
#--------------------------------------------------------------------------------
set(_test_name tst_qextresulttypededuce)
add_executable(${_test_name}
    tst_qextresulttypededuce.cpp
    )
add_test(NAME ${_test_name} COMMAND ${_test_name})
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})



#--------------------------------------------------------------------------------
# Add tst_qextbindfunctor test
#--------------------------------------------------------------------------------
set(_test_name tst_qextbindfunctor)
add_executable(${_test_name}
    tst_qextbindfunctor.cpp
    )
add_test(NAME ${_test_name} COMMAND ${_test_name})
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})



#--------------------------------------------------------------------------------
# Add tst_qextbindreturnfunctor test
#--------------------------------------------------------------------------------
set(_test_name tst_qextbindreturnfunctor)
add_executable(${_test_name}
    tst_qextbindreturnfunctor.cpp
    )
add_test(NAME ${_test_name} COMMAND ${_test_name})
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})



#--------------------------------------------------------------------------------
# Add tst_qexttrackobjectfunctor test
#--------------------------------------------------------------------------------
set(_test_name tst_qexttrackobjectfunctor)
add_executable(${_test_name}
    tst_qexttrackobjectfunctor.cpp
    )
add_test(NAME ${_test_name} COMMAND ${_test_name})
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})



#--------------------------------------------------------------------------------
# Add tst_qextcomposefunctor test
#--------------------------------------------------------------------------------
set(_test_name tst_qextcomposefunctor)
add_executable(${_test_name}
    tst_qextcomposefunctor.cpp
    )
add_test(NAME ${_test_name} COMMAND ${_test_name})
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})



#--------------------------------------------------------------------------------
# Add tst_qextlimitreference test
#--------------------------------------------------------------------------------
set(_test_name tst_qextlimitreference)
add_executable(${_test_name}
    tst_qextlimitreference.cpp
    )
add_test(NAME ${_test_name} COMMAND ${_test_name})
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})



#--------------------------------------------------------------------------------
# Add tst_qextretypefunctor test
#--------------------------------------------------------------------------------
set(_test_name tst_qextretypefunctor)
add_executable(${_test_name}
    tst_qextretypefunctor.cpp
    )
add_test(NAME ${_test_name} COMMAND ${_test_name})
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})



#--------------------------------------------------------------------------------
# Add tst_qexthidefunctor test
#--------------------------------------------------------------------------------
set(_test_name tst_qexthidefunctor)
add_executable(${_test_name}
    tst_qexthidefunctor.cpp
    )
add_test(NAME ${_test_name} COMMAND ${_test_name})
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})



#--------------------------------------------------------------------------------
# Add tst_qextlambda test
#--------------------------------------------------------------------------------
set(_test_name tst_qextlambda)
add_executable(${_test_name}
    tst_qextlambda.cpp
    )
add_test(NAME ${_test_name} COMMAND ${_test_name})
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})



#--------------------------------------------------------------------------------
# Add tst_qextretypereturnfunctor test
#--------------------------------------------------------------------------------
set(_test_name tst_qextretypereturnfunctor)
add_executable(${_test_name}
    tst_qextretypereturnfunctor.cpp
    )
add_test(NAME ${_test_name} COMMAND ${_test_name})
target_link_libraries(${_test_name} PRIVATE ${_test_link_libraries})
target_include_directories(${_test_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
