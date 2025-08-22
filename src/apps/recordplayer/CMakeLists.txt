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
# Set lib base name and out put path
#-----------------------------------------------------------------------------------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${QEXT_BUILD_DIR}/${QEXT_INSTALL_BINDIR})
set(LIBRARY_OUTPUT_PATH ${QEXT_BUILD_DIR}/${QEXT_INSTALL_LIBDIR})
set(RP_PROGRAM_NAME RecordPlayer)
set(RP_VERSION_MAJOR 0)
set(RP_VERSION_MINOR 1)
set(RP_VERSION_PATCH 1)
set(RP_VERSION_TWEAK 1)
set(RP_VERSION_STAGE alpha)
set(RP_VERSION ${RP_VERSION_MAJOR}.${RP_VERSION_MINOR}.${RP_VERSION_PATCH})
set(RP_VERSION_STRING "${RP_VERSION_MAJOR}.${RP_VERSION_MINOR}.${RP_VERSION_PATCH}")
set(RP_COPYRIGHT "Copyright (c) 2025 ChengXueWen")
set(RP_ORGANIZATION_DOMAIN_NAME "ChengXueWen & 1398831004@qq.com")
set(RP_ORGANIZATION_NAME "QExt")


#-----------------------------------------------------------------------------------------------------------------------
# Set build datetime and package name
#-----------------------------------------------------------------------------------------------------------------------
string(TIMESTAMP RP_COMPILE_DATE %Y%m%d)
string(TIMESTAMP RP_COMPILE_TIME %H%M%S)
string(TIMESTAMP RP_COMPILE_FORMAT_DATE %Y-%m-%d)
set(RP_COMPILE_DATETIME ${RP_COMPILE_DATE}_${RP_COMPILE_TIME})
set(RP_PACKAGE_NAME ${RP_PROGRAM_NAME}-${RP_VERSION_NAME}-${RP_VERSION_STAGE}-${RP_ARCH_NAME})
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(RP_PACKAGE_NAME "${RP_PACKAGE_NAME}-debug")
endif()


#-----------------------------------------------------------------------------------------------------------------------
# Create translations ts file
#-----------------------------------------------------------------------------------------------------------------------
# qt5_create_translation(QM_FILES
#     ${PROJECT_SOURCE_DIR}/src
#     ${RP_OUTPUT_TRANSLATIONS_DIR}/RecordPlayer_en.ts
#     OPTIONS -source-language en_US -no-obsolete)


#-----------------------------------------------------------------------------------------------------------------------
# Set app link libraries
#-----------------------------------------------------------------------------------------------------------------------
if(UNIX)
    list(APPEND RP_LINK_EXTERNAL_LIBS ${CMAKE_DL_LIBS})
endif()

if(WIN32)
    list(APPEND RP_LINK_EXTERNAL_LIBS shlwapi.lib dbghelp)
endif()

if(CMAKE_THREAD_LIBS_INIT)
    list(APPEND RP_LINK_EXTERNAL_LIBS ${CMAKE_THREAD_LIBS_INIT})
endif()

foreach(component ${RP_DEPENDS_QT_COMPONENTS})
    list(APPEND RP_LINK_QT_LIBS Qt${RP_QT_VERSION_MAJOR}::${component})
endforeach()

list(APPEND RP_LINK_INTERNAL_LIBS
    QExt::Plot
    QExt::DAView
    QExt::Widgets
    QExt::Breakpad
    QExt::Keyboard)
qext_find_package(WrapSingleApp PROVIDED_TARGETS QExt3rdparty::WrapSingleApp)
qext_find_package(WrapQtADS PROVIDED_TARGETS QExt3rdparty::WrapQtADS)
list(APPEND RP_LINK_EXTERNAL_LIBS
    QExt3rdparty::WrapSingleApp
    QExt3rdparty::WrapQtADS)


#-----------------------------------------------------------------------------------------------------------------------
# Configure a header file to pass some of the CMake settings to the source code
#-----------------------------------------------------------------------------------------------------------------------
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/source/rpConfig.h.in" "${CMAKE_CURRENT_BINARY_DIR}/rpConfig.h")


#-----------------------------------------------------------------------------------------------------------------------
# Set app file list
#-----------------------------------------------------------------------------------------------------------------------
set(RP_SOURCES
    ${CMAKE_CURRENT_BINARY_DIR}/rpConfig.h
    source/gui/dialog/rpChangesLogDialog.h
    source/gui/dialog/rpChangesLogDialog.ui
    source/gui/dialog/rpChangesLogDialog.cpp
    source/gui/dialog/rpLogDialog.h
    source/gui/dialog/rpLogDialog.cpp
    source/gui/dialog/rpLogDialog.ui
    source/gui/rpMainWindow.h
    source/gui/rpMainWindow.cpp
    source/gui/rpMainWindow.ui
    source/main/main.cpp
    source/main/rpApp.cpp
    source/main/rpApp.h
    source/main/rpSplashScreen.cpp
    source/main/rpSplashScreen.h
    source/utils/rpCommonUtils.h
    source/utils/rpCommonUtils.cpp
    source/utils/rpConstants.h
    source/utils/rpConstants.cpp
    source/utils/rpKeyboardManager.h
    source/utils/rpKeyboardManager.cpp
    source/utils/rpLanguageManager.h
    source/utils/rpLanguageManager.cpp
    source/utils/rpLogger.h
    source/utils/rpLogger.cpp
    source/utils/rpSettings.cpp
    source/utils/rpSettings.h
    source/rpPch.h
    source/rpGlobal.h
    source/rpGlobal.cpp)

set(RP_RESOURCES
    source/resources/RecordPlayer.qrc)
if(WIN32)
    list(APPEND RP_RESOURCES source/resources/RecordPlayerWin.rc)
endif(WIN32)

add_executable(${RP_PROGRAM_NAME}
    ${RP_SOURCES}
    ${RP_RESOURCES}
    ${RP_CONFIG_HPP_FILE_PATH}
    ${QM_FILES})
if (RP_BUILD_USE_PCH)
    qext_activate_precompiled_headers(${RP_PROGRAM_NAME} PRIVATE source/rpPch.h)
endif()
qext_hide_executable_console(${RP_PROGRAM_NAME})
target_link_libraries(${RP_PROGRAM_NAME} PUBLIC
    ${RP_LINK_EXTERNAL_LIBS}
    ${RP_LINK_INTERNAL_LIBS}
    ${RP_LINK_QT_LIBS})
target_include_directories(${RP_PROGRAM_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source/gui>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source/gui/dialog>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source/main>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source/utils>
    $<INSTALL_INTERFACE:include>)
# target_compile_definitions(${RP_PROGRAM_NAME} PUBLIC QT_FORCE_ASSERTS)
add_custom_target(Init${RP_PROGRAM_NAME}Resources ALL
    # COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/changes ${EXECUTABLE_OUTPUT_PATH}/changes
    COMMENT "Init ${RP_PROGRAM_NAME} Resources"
    POST_BUILD)

return()
#-----------------------------------------------------------------------------------------------------------------------
# Build install pack
#-----------------------------------------------------------------------------------------------------------------------
message(STATUS "Build install pack in ${CMAKE_SYSTEM_NAME}")
if(CMAKE_SYSTEM_NAME MATCHES Linux)
    message(STATUS "Set build linux install pack")
    set(QEXT_PACK_TARGET_DIRECTORY @HomeDir@)
elseif(CMAKE_SYSTEM_NAME MATCHES Darwin)
    message(STATUS "Set build darwin(mac) install pack")
    set(QEXT_PACK_TARGET_DIRECTORY @HomeDir@)
elseif(CMAKE_SYSTEM_NAME MATCHES Windows)
    message(STATUS "Set build windows install pack")
    set(QEXT_PACK_TARGET_DIRECTORY @ApplicationsDir@)

    foreach(component ${RP_DEPENDS_QT_COMPONENTS})
        if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
            list(APPEND RP_DEPENDS_EXTERNAL_QT_LIBS Qt${RP_QT_VERSION_MAJOR}${component}d.dll)
        else()
            list(APPEND RP_DEPENDS_EXTERNAL_QT_LIBS Qt${RP_QT_VERSION_MAJOR}${component}.dll)
        endif()
    endforeach()

    qext_copy_target_external_dependent_libraries(
        TARGET ${RP_PROGRAM_NAME}
        LIBS ${RP_DEPENDS_EXTERNAL_QT_LIBS}
        SOURCE ${RP_QT_BIN_DIR}
        DESTINATION ${RP_OUTPUT_BIN_DIR}
        # VERBOSE
        POST_BUILD)
    qext_copy_target_internal_dependent_libraries(
        TARGET ${RP_PROGRAM_NAME}
        LIBS ${RP_LINK_INTERNAL_LIBS}
        DESTINATION ${RP_OUTPUT_BIN_DIR}
        # VERBOSE
        POST_BUILD)

    qext_find_qt_tool(windeployqt)
    if(NOT windeployqt_EXECUTABLE)
        message(FATAL_ERROR "Not find Qt windeployqt.exe")
    else()
        message(STATUS "Qt${RP_QT_VERSION_MAJOR} windeployqt.exe found")
        file(GLOB RP_OUTPUT_BIN_DLL_FILES "${RP_OUTPUT_BIN_DIR}/*.dll")
        foreach(dll_file in ${RP_OUTPUT_BIN_DLL_FILES})
            string(REPLACE ".dll" ".pdb" pdb_file ${dll_file})
            if (EXISTS ${pdb_file})
                # message(pdb_file=${pdb_file})
                list(APPEND RP_OUTPUT_BIN_PDB_FILES ${pdb_file})
            endif()
        endforeach()
        if(CMAKE_BUILD_TYPE MATCHES "Debug")
            list(APPEND RP_OUTPUT_BIN_DLL_FILES "C:/Windows/System32/ucrtbased.dll")
        endif()
        # message(RP_OUTPUT_BIN_DLL_FILES=${RP_OUTPUT_BIN_DLL_FILES})
        set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${RP_OUTPUT_INSTALL_DIR})
        list(APPEND RP_DEPLOYQT_ARGS --verbose=1)
        list(APPEND RP_DEPLOYQT_ARGS --compiler-runtime)
        list(APPEND RP_DEPLOYQT_ARGS --force)
        list(APPEND RP_DEPLOYQT_ARGS --pdb)
        add_custom_command(
            TARGET ${RP_PROGRAM_NAME}
            # COMMAND ${CMAKE_COMMAND} -E remove_directory ${RP_OUTPUT_INSTALL_DIR}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${RP_OUTPUT_INSTALL_DIR}
            COMMAND ${CMAKE_COMMAND} -E make_directory "${RP_OUTPUT_INSTALL_DIR}/bin"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${RP_OUTPUT_INSTALL_DIR}/bin/translations"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${RP_OUTPUT_INSTALL_DIR}/share"
            COMMAND ${CMAKE_COMMAND} -E copy_directory "${RP_OUTPUT_PLUGINS_DIR}" "${RP_OUTPUT_INSTALL_DIR}/plugins"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${RP_OUTPUT_BIN_DLL_FILES} "${RP_OUTPUT_INSTALL_DIR}/bin"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${RP_OUTPUT_BIN_PDB_FILES} "${RP_OUTPUT_INSTALL_DIR}/bin"
            COMMAND ${CMAKE_COMMAND} -E copy_directory "${RP_OUTPUT_BIN_DIR}/changes"
            "${RP_OUTPUT_INSTALL_DIR}/bin/changes"
            COMMAND ${CMAKE_COMMAND} -E copy_directory "${RP_OUTPUT_TRANSLATIONS_DIR}"
            "${RP_OUTPUT_INSTALL_DIR}/bin/translations"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:${RP_PROGRAM_NAME}>"
            "${RP_OUTPUT_INSTALL_DIR}/bin/$<TARGET_FILE_NAME:${RP_PROGRAM_NAME}>"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_PDB_FILE:${RP_PROGRAM_NAME}>"
            "${RP_OUTPUT_INSTALL_DIR}/bin/$<TARGET_PDB_FILE_NAME:${RP_PROGRAM_NAME}>"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:${QEXT_BREAKPAD_REPORTER_NAME}>"
            "${RP_OUTPUT_INSTALL_DIR}/bin/$<TARGET_FILE_NAME:${QEXT_BREAKPAD_REPORTER_NAME}>"
            COMMAND "${windeployqt_EXECUTABLE}" ${RP_DEPLOYQT_ARGS}
            "${RP_OUTPUT_INSTALL_DIR}/bin/$<TARGET_FILE_NAME:${RP_PROGRAM_NAME}>"
            COMMENT "Run windeployqt to deploy ${RP_PROGRAM_NAME}"
            POST_BUILD)
    endif()
endif()

# QTIFW
if(NOT "${QEXT_PACK_TARGET_DIRECTORY}" STREQUAL "" AND OFF)
    set(QEXT_QTIFWDIR_FIND_REQUIRED FALSE)
    qext_find_qt_tool(binarycreator)
    if(binarycreator_BIN_DIR)
        message(STATUS "Use QtIFW in ${binarycreator_BIN_DIR}")
        set(CPACK_IFW_ROOT ${binarycreator_BIN_DIR})
    endif()
    set(QEXT_PACK_SPECVIEW_PATH ${CMAKE_CURRENT_SOURCE_DIR}/install/RecordPlayer)
    set(QEXT_PACK_MAINTENANCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/install/Maintenance)
    if(CPACK_IFW_ROOT OR DEFINED ENV{QTIFWDIR})
        include(CPackComponent)
        include(InstallRequiredSystemLibraries)
        set(CPACK_PACKAGE_NAME ${RP_PROGRAM_NAME})
        set(CPACK_PACKAGE_FILE_NAME ${RP_PACKAGE_NAME})
        set(CPACK_PACKAGE_VENDOR ${RP_ORGANIZATION_NAME})
        set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Installation Tool")
        set(CPACK_PACKAGE_INSTALL_DIRECTORY "${RP_PROGRAM_NAME} ${RP_VERSION_NAME}")    # Installation directory on the target system.
        set(CPACK_PACKAGE_EXECUTABLES bin/${RP_PROGRAM_NAME})
        set(CPACK_PACKAGE_ICON "${QEXT_PACK_SPECVIEW_PATH}/RecordPlayer_Icon.ico")
        set(CPACK_PACKAGE_VERSION "${RP_VERSION_NAME}")
        set(CPACK_CREATE_DESKTOP_LINKS ${RP_PROGRAM_NAME})
        set(CPACK_SOURCE_GENERATOR ";")
        set(CPACK_COMPONENTS_ALL)
        set(CPACK_GENERATOR IFW)
        set(CPACK_IFW_VERBOSE ON)
        set(CPACK_IFW_TARGET_DIRECTORY ${QEXT_PACK_TARGET_DIRECTORY}/${CPACK_PACKAGE_INSTALL_DIRECTORY})
        set(CPACK_IFW_PACKAGE_START_MENU_DIRECTORY ${RP_ORGANIZATION_NAME})
        set(CPACK_IFW_PACKAGE_TITLE ${RP_DISPLAY_NAME}) # Publisher of the software (as shown in the Windows Control Panel). By default used CPACK_PACKAGE_VENDOR.
        set(CPACK_IFW_PACKAGE_PUBLISHER ${RP_ORGANIZATION_DOMAIN_NAME})
        set(CPACK_IFW_PACKAGE_WIZARD_STYLE "Mac") # “Modern”、“Mac”、“Aero”或“Classic”
        set(CPACK_IFW_PACKAGE_LOGO "${QEXT_PACK_SPECVIEW_PATH}/RecordPlayer_Logo.png")
        set(CPACK_IFW_PACKAGE_ICON "${QEXT_PACK_SPECVIEW_PATH}/RecordPlayer_Icon.ico")
        set(CPACK_IFW_PACKAGE_WINDOW_ICON "${QEXT_PACK_SPECVIEW_PATH}/RecordPlayer_Icon.png")
        include(CPack REQUIRED)
        include(CPackIFW REQUIRED)

        # Maintenance config
        set(QEXT_PACK_MAINTENANCE_NAME Maintenance)
        list(APPEND QEXT_PACK_MAINTENANCE_ICONS
            ${QEXT_PACK_MAINTENANCE_PATH}/Maintenance.bmp
            ${QEXT_PACK_MAINTENANCE_PATH}/Maintenance.ico
            ${QEXT_PACK_MAINTENANCE_PATH}/Maintenance.png)
        install(FILES ${QEXT_PACK_MAINTENANCE_ICONS}
            DESTINATION share/icons/
            COMPONENT ${QEXT_PACK_MAINTENANCE_NAME})
        cpack_add_component(${QEXT_PACK_MAINTENANCE_NAME} REQUIRED
            DISPLAY_NAME "Maintenance tool"
            DESCRIPTION "${RP_DESCRIPTION} Maintenance tool")
        configure_file("${QEXT_PACK_MAINTENANCE_PATH}/MaintenanceInstallScript.qs.in"
            "${CMAKE_CURRENT_BINARY_DIR}/MaintenanceInstallScript.qs")
        cpack_ifw_configure_component(${QEXT_PACK_MAINTENANCE_NAME}
            VERSION ${RP_VERSION_NAME}
            RELEASE_DATE ${RP_COMPILE_FORMAT_DATE}
            SCRIPT ${CMAKE_CURRENT_BINARY_DIR}/MaintenanceInstallScript.qs)

        # RecordPlayer config
        set(QEXT_PACK_SPECVIEW_NAME RecordPlayer)
        set(RP_INSTALL_DIR_PERMISSIONS
            OWNER_READ OWNER_WRITE
            GROUP_READ GROUP_WRITE
            WORLD_READ WORLD_WRITE)
        set(RP_INSTALL_BIN_PERMISSIONS
            OWNER_READ OWNER_WRITE OWNER_EXECUTE
            GROUP_READ GROUP_WRITE GROUP_EXECUTE
            WORLD_READ WORLD_WRITE WORLD_EXECUTE)
        install(
            DIRECTORY ${RP_OUTPUT_INSTALL_DIR}/
            DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ GROUP_WRITE WORLD_READ WORLD_WRITE
            DESTINATION .
            COMPONENT ${QEXT_PACK_SPECVIEW_NAME}
            PATTERN "*.exe" PERMISSIONS ${RP_INSTALL_BIN_PERMISSIONS})
        list(APPEND QEXT_PACK_SPECVIEW_ICONS
            ${QEXT_PACK_SPECVIEW_PATH}/RecordPlayer_Icon.bmp
            ${QEXT_PACK_SPECVIEW_PATH}/RecordPlayer_Icon.ico
            ${QEXT_PACK_SPECVIEW_PATH}/RecordPlayer_Icon.png)
        install(FILES ${QEXT_PACK_SPECVIEW_ICONS}
            DESTINATION share/icons/
            COMPONENT ${QEXT_PACK_SPECVIEW_NAME})
        configure_file("${QEXT_PACK_SPECVIEW_PATH}/RecordPlayerInstallScript.qs.in"
            "${CMAKE_CURRENT_BINARY_DIR}/RecordPlayerInstallScript.qs")
        cpack_add_component(${QEXT_PACK_SPECVIEW_NAME} REQUIRED
            DISPLAY_NAME "RecordPlayer program"
            DESCRIPTION ${RP_DESCRIPTION})
        cpack_ifw_configure_component(${QEXT_PACK_SPECVIEW_NAME}
            VERSION ${RP_VERSION_NAME}
            RELEASE_DATE ${RP_COMPILE_FORMAT_DATE}
            SCRIPT ${CMAKE_CURRENT_BINARY_DIR}/RecordPlayerInstallScript.qs)

        add_custom_target(${RP_PROGRAM_NAME}CPack
            COMMAND cpack.exe -C CPackConfig.cmake
            WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
            COMMENT "CPack ${RP_PROGRAM_NAME} program...")
    endif()
endif()
