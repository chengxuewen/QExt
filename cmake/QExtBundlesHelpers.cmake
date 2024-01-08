########################################################################################################################
#
# Library: QExt
#
# Copyright (C) 2024 ChengXueWen.
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
# qext_internal_get_add_bundle_keywords macro
#-----------------------------------------------------------------------------------------------------------------------
macro(qext_internal_get_add_bundle_keywords option_args single_args multi_args)
    set(${option_args}
        TEST_PLUGIN)
    set(${single_args}
        LIBRARY_INCLUDE_NAME
        LIBRARY_INTERFACE_NAME
        CONFIG_LIBRARY_NAME
        PRECOMPILED_HEADER
        CONFIGURE_FILE_PATH
        CPP_EXPORT_HEADER_BASE_NAME
        EXTERNAL_HEADERS_DIR
        CONFIGURE_RESET
        ${QEXT_DEFAULT_TARGET_INFO_ARGS})
    set(${multi_args}
        EXTRA_CMAKE_FILES
        EXTRA_CMAKE_INCLUDES
        NO_PCH_SOURCES
        EXTERNAL_HEADERS
        ${QEXT_DEFAULT_PUBLIC_ARGS}
        ${QEXT_DEFAULT_PRIVATE_ARGS})
endmacro()

macro(CtkMacroParseArguments prefix arg_names option_names)
    set(DEFAULT_ARGS)
    foreach(arg_name ${arg_names})
        set(${prefix}_${arg_name})
    endforeach()
    foreach(option ${option_names})
        set(${prefix}_${option} FALSE)
    endforeach()

    set(current_arg_name DEFAULT_ARGS)
    set(current_arg_list)
    foreach(arg ${ARGN})
        set(larg_names ${arg_names})
        list(FIND larg_names "${arg}" is_arg_name)
        IF (is_arg_name GREATER -1)
        set(${prefix}_${current_arg_name} ${current_arg_list})
        set(current_arg_name ${arg})
        set(current_arg_list)
        ELSE (is_arg_name GREATER -1)
        set(loption_names ${option_names})
        list(FIND loption_names "${arg}" is_option)
        IF (is_option GREATER -1)
        set(${prefix}_${arg} TRUE)
        ELSE (is_option GREATER -1)
        set(current_arg_list ${current_arg_list} ${arg})
        ENDIF (is_option GREATER -1)
        ENDIF (is_arg_name GREATER -1)
    endforeach()
    set(${prefix}_${current_arg_name} ${current_arg_list})
endmacro()

macro(ctkMacroListFilter)
    ctkMacroParseArguments(LIST_FILTER "OUTPUT_VARIABLE" "" ${ARGV})
    # Check arguments.
    list(LENGTH LIST_FILTER_DEFAULT_ARGS LIST_FILTER_default_length)
    if(${LIST_FILTER_default_length} EQUAL 0)
        message(FATAL_ERROR "LIST_FILTER: missing list variable.")
    endif()
    if(${LIST_FILTER_default_length} EQUAL 1)
        message(FATAL_ERROR "LIST_FILTER: missing regular expression variable.")
    endif()
    # Reset output variable
    if(NOT LIST_FILTER_OUTPUT_VARIABLE)
        set(LIST_FILTER_OUTPUT_VARIABLE "LIST_FILTER_internal_output")
    endif()
    set(${LIST_FILTER_OUTPUT_VARIABLE})
    # Extract input list from arguments
    list(GET LIST_FILTER_DEFAULT_ARGS 0 LIST_FILTER_input_list)
    list(REMOVE_AT LIST_FILTER_DEFAULT_ARGS 0)
    foreach(LIST_FILTER_item ${${LIST_FILTER_input_list}})
        foreach(LIST_FILTER_regexp_var ${LIST_FILTER_DEFAULT_ARGS})
            foreach(LIST_FILTER_regexp ${${LIST_FILTER_regexp_var}})
                if(${LIST_FILTER_item} MATCHES ${LIST_FILTER_regexp})
                    list(APPEND ${LIST_FILTER_OUTPUT_VARIABLE} ${LIST_FILTER_item})
                endif()
            endforeach()
        endforeach()
    endforeach()
    # If OUTPUT_VARIABLE is not specified, overwrite the input list.
    if(${LIST_FILTER_OUTPUT_VARIABLE} STREQUAL "LIST_FILTER_internal_output")
        set(${LIST_FILTER_input_list} ${${LIST_FILTER_OUTPUT_VARIABLE}})
    endif()
endmacro(ctkMacroListFilter)



#!
#! Extract all library names which are build within this project
#!
#! \ingroup CMakeUtilities
macro(ctkMacroGetAllProjectTargetLibraries all_target_libraries varname)
    # Allow external projects to override the set of internal targets
    if(COMMAND GetMyTargetLibraries)
        GetMyTargetLibraries("${all_target_libraries}" ${varname})
    else()
        set(re_ctklib "^(c|C)(t|T)(k|K)[a-zA-Z0-9]+$")
        set(re_ctkplugin "^org_commontk_[a-zA-Z0-9_]+$")
        set(_tmp_list)
        list(APPEND _tmp_list ${all_target_libraries})
        #message("calling ctkMacroListFilter with varname:${varname}")
        ctkMacroListFilter(_tmp_list re_ctklib re_ctkplugin OUTPUT_VARIABLE ${varname})
        #message(STATUS "getallctklibs from ${all_target_libraries}")
        #message(STATUS varname:${varname}:${${varname}})
    endif()
endmacro()


#!
#! Extract all library names *NOT* being build within this project
#!
#! \ingroup CMakeUtilities
macro(ctkMacroGetAllNonProjectTargetLibraries all_target_libraries varname)
    ctkMacroGetAllProjectTargetLibraries("${all_target_libraries}" all_project_libraries)
    set(_tmp_list ${all_target_libraries})
    if(all_project_libraries)
        list(REMOVE_ITEM _tmp_list ${all_project_libraries})
    endif()
    set(${varname} ${_tmp_list})
    #message(varname:${varname}:${${varname}})
endmacro()

#! \ingroup CMakeUtilities
macro(ctkMacroShouldAddExternalProject libraries_variable_name resultvar)
    set(${resultvar} FALSE)
    if(DEFINED NON_CTK_DEPENDENCIES)
        list(FIND NON_CTK_DEPENDENCIES ${libraries_variable_name} index)

        if(${index} GREATER -1)
            set(${resultvar} TRUE)
        endif()
    endif()
endmacro()



#! \ingroup CMakeUtilities
function(ctkFunctionGetLibraryDirs var_library_dirs)

    if(NOT ARGN)
        message(FATAL_ERROR "No targets given")
    endif()

    set(_library_dirs ${${var_library_dirs}})
    foreach(_target ${ARGN})

        # Add the library directories from the external project
        # The variable ${_target}_DEPENDENCIES is set in the
        # macro ctkMacroValidateBuildOptions

        set(ext_deps )

        ctkMacroGetAllNonProjectTargetLibraries("${${_target}_DEPENDENCIES}" ext_deps)

        foreach(dep ${ext_deps})

            if(${dep}_LIBRARY_DIRS)
                string(REPLACE "^" ";" _ext_library_dirs "${${dep}_LIBRARY_DIRS}")
                list(APPEND _library_dirs ${_ext_library_dirs})
            endif()

        endforeach()

    endforeach()

    if(_library_dirs)
        list(REMOVE_DUPLICATES _library_dirs)
    endif()
    set(${var_library_dirs} ${_library_dirs} PARENT_SCOPE)

endfunction()


#!
#! Extract all library names which are build within this project
#!
#! \ingroup CMakeUtilities
macro(ctkMacroGetAllProjectTargetLibraries all_target_libraries varname)
    # Allow external projects to override the set of internal targets
    if(COMMAND GetMyTargetLibraries)
        GetMyTargetLibraries("${all_target_libraries}" ${varname})
    else()
        set(re_ctklib "^(c|C)(t|T)(k|K)[a-zA-Z0-9]+$")
        set(re_ctkplugin "^org_commontk_[a-zA-Z0-9_]+$")
        set(_tmp_list)
        list(APPEND _tmp_list ${all_target_libraries})
        #message("calling ctkMacroListFilter with varname:${varname}")
        ctkMacroListFilter(_tmp_list re_ctklib re_ctkplugin OUTPUT_VARIABLE ${varname})
        #message(STATUS "getallctklibs from ${all_target_libraries}")
        #message(STATUS varname:${varname}:${${varname}})
    endif()
endmacro()


#! \ingroup CMakeUtilities
function(ctkFunctionGetIncludeDirs var_include_dirs)
    if(NOT ARGN)
        message(FATAL_ERROR "No targets given")
    endif()

    set(_include_dirs ${${var_include_dirs}} ${CTK_CONFIG_H_INCLUDE_DIR})
    foreach(_target ${ARGN})

        # Add the include directories from the plugin dependencies
        # The variable ${_target}_DEPENDENCIES is set in the
        # macro ctkMacroValidateBuildOptions

        set(ctk_deps )
        set(ext_deps )

        ctkMacroGetAllProjectTargetLibraries("${${_target}_DEPENDENCIES}" ctk_deps)
        ctkMacroGetAllNonProjectTargetLibraries("${${_target}_DEPENDENCIES}" ext_deps)

        foreach(dep ${ctk_deps})

            if(${dep}_INCLUDE_SUFFIXES)
                foreach(_suffix ${${dep}_INCLUDE_SUFFIXES})
                    list(APPEND _include_dirs ${${dep}_SOURCE_DIR}/${_suffix})
                endforeach()
                list(APPEND _include_dirs ${${dep}_BINARY_DIR})
            else()
                list(APPEND _include_dirs
                    ${${dep}_SOURCE_DIR}
                    ${${dep}_BINARY_DIR})
            endif()

            # For external projects, CTKConfig.cmake contains variables
            # listening the include dirs for CTK libraries and plugins
            if(${dep}_INCLUDE_DIRS)
                list(APPEND _include_dirs ${${dep}_INCLUDE_DIRS})
            endif()
        endforeach()

        foreach(dep ${ext_deps})

            if(${dep}_INCLUDE_DIRS)
                string(REPLACE "^" ";" _ext_include_dirs "${${dep}_INCLUDE_DIRS}")
                list(APPEND _include_dirs ${_ext_include_dirs})
            endif()

            # This is for resolving include dependencies between
            # libraries / plugins from external projects using CTK
            if(${dep}_SOURCE_DIR AND ${dep}_INCLUDE_SUFFIXES)
                foreach(_suffix ${${dep}_INCLUDE_SUFFIXES})
                    list(APPEND _include_dirs ${${dep}_SOURCE_DIR}/${_suffix})
                endforeach()
                list(APPEND _include_dirs ${${dep}_BINARY_DIR})
            elseif(${dep}_SOURCE_DIR)
                list(APPEND _include_dirs ${${dep}_SOURCE_DIR})
            endif()

            if(${dep}_BINARY_DIR)
                list(APPEND _include_dirs ${${dep}_BINARY_DIR})
            endif()

        endforeach()

    endforeach()

    if(_include_dirs)
        list(REMOVE_DUPLICATES _include_dirs)
    endif()
    set(${var_include_dirs} ${_include_dirs} PARENT_SCOPE)

endfunction()



#! \ingroup CMakeUtilities
function(ctkFunctionGeneratePluginManifest QRC_SRCS)
    CtkMacroParseArguments(MY
        "ACTIVATIONPOLICY;CATEGORY;CONTACT_ADDRESS;COPYRIGHT;DESCRIPTION;DOC_URL;ICON;LICENSE;NAME;REQUIRE_PLUGIN;SYMBOLIC_NAME;VENDOR;VERSION;CUSTOM_HEADERS"
        ""
        ${ARGN})

    # Sanity checks
    if(NOT DEFINED MY_SYMBOLIC_NAME)
        message(FATAL_ERROR "SYMBOLIC_NAME is mandatory")
    endif()

    set(_manifest_content "Plugin-SymbolicName: ${MY_SYMBOLIC_NAME}")

    if(DEFINED MY_ACTIVATIONPOLICY)
        string(TOLOWER "${MY_ACTIVATIONPOLICY}" _activation_policy)
        if(_activation_policy STREQUAL "eager")
            set(_manifest_content "${_manifest_content}\nPlugin-ActivationPolicy: eager")
        else()
            message(FATAL_ERROR "ACTIVATIONPOLICY is set to '${MY_ACTIVATIONPOLICY}', which is not supported")
        endif()
    endif()

    if(DEFINED MY_CATEGORY)
        set(_manifest_content "${_manifest_content}\nPlugin-Category: ${MY_CATEGORY}")
    endif()

    if(DEFINED MY_CONTACT_ADDRESS)
        set(_manifest_content "${_manifest_content}\nPlugin-ContactAddress: ${MY_CONTACT_ADDRESS}")
    endif()

    if(DEFINED MY_COPYRIGHT)
        set(_manifest_content "${_manifest_content}\nPlugin-Copyright: ${MY_COPYRIGHT}")
    endif()

    if(DEFINED MY_DESCRIPTION)
        set(_manifest_content "${_manifest_content}\nPlugin-Description: ${MY_DESCRIPTION}")
    endif()

    if(DEFINED MY_DOC_URL)
        set(_manifest_content "${_manifest_content}\nPlugin-DocURL: ${MY_DOC_URL}")
    endif()

    if(DEFINED MY_ICON)
        set(_manifest_content "${_manifest_content}\nPlugin-Icon: ${MY_ICON}")
    endif()

    if(DEFINED MY_LICENSE)
        set(_manifest_content "${_manifest_content}\nPlugin-License: ${MY_LICENSE}")
    endif()

    if(DEFINED MY_NAME)
        set(_manifest_content "${_manifest_content}\nPlugin-Name: ${MY_NAME}")
    endif()

    if(DEFINED MY_REQUIRE_PLUGIN)
        string(REPLACE ";" "," require_plugin "${MY_REQUIRE_PLUGIN}")
        set(_manifest_content "${_manifest_content}\nRequire-Plugin: ${require_plugin}")
    endif()

    if(DEFINED MY_VENDOR)
        set(_manifest_content "${_manifest_content}\nPlugin-Vendor: ${MY_VENDOR}")
    endif()

    if(DEFINED MY_VERSION)
        set(_manifest_content "${_manifest_content}\nPlugin-Version: ${MY_VERSION}")
    endif()

    if(DEFINED MY_CUSTOM_HEADERS)
        set(_manifest_content "${_manifest_content}\n")
        foreach(_custom_header ${MY_CUSTOM_HEADERS})
            set(_manifest_content "${_manifest_content}\n${_custom_header}: ${${_custom_header}}")
        endforeach()
    endif()

    set(_manifest_filename "MANIFEST.MF")
    set(_manifest_filepath "${CMAKE_CURRENT_BINARY_DIR}/${_manifest_filename}")
    string(REPLACE "." "_" _symbolic_name ${MY_SYMBOLIC_NAME})
    set(_manifest_qrc_filepath "${CMAKE_CURRENT_BINARY_DIR}/${_symbolic_name}_manifest.qrc")

    set(_manifest_qrc_content
        "<!DOCTYPE RCC><RCC version=\"1.0\">
        <qresource prefix=\"/${MY_SYMBOLIC_NAME}/META-INF\">
        <file>${_manifest_filename}</file>
        </qresource>
        </RCC>
        ")

    configure_file("${QEXT_CMAKE_DIR}/MANIFEST.MF.in" "${_manifest_filepath}" @ONLY)
    configure_file("${QEXT_CMAKE_DIR}/plugin_manifest.qrc.in" "${_manifest_qrc_filepath}" @ONLY)

    if (QEXT_QT_VERSION VERSION_GREATER "4")
        QT5_ADD_RESOURCES(_qrc_src ${_manifest_qrc_filepath})
    else()
        QT4_ADD_RESOURCES(_qrc_src ${_manifest_qrc_filepath})
    endif()

    set(${QRC_SRCS} ${${QRC_SRCS}} ${_qrc_src} PARENT_SCOPE)

endfunction()


#! \ingroup CMakeUtilities
macro(ctkMacroGeneratePluginResourceFile QRC_SRCS)
    CtkMacroParseArguments(MY
        "NAME;PREFIX;RESOURCES;BINARY_RESOURCES"
        ""
        ${ARGN})

    set(_qrc_filepath "${CMAKE_CURRENT_BINARY_DIR}/${MY_NAME}")

    set(_qrc_content
        "<!DOCTYPE RCC><RCC version=\"1.0\">
        <qresource prefix=\"/${MY_PREFIX}\">
        ")

    if(MY_RESOURCES)
        foreach(_resource_file ${MY_RESOURCES})
            configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${_resource_file}" "${CMAKE_CURRENT_BINARY_DIR}/${_resource_file}" COPYONLY)
            set(_qrc_content "${_qrc_content}<file>${_resource_file}</file>
                ")
        endforeach()
    endif()

    if(MY_BINARY_RESOURCES)
        foreach(_resource_file ${MY_BINARY_RESOURCES})
            set(_qrc_content "${_qrc_content}<file>${_resource_file}</file>
                ")
        endforeach()
    endif()

    set(_qrc_content "${_qrc_content}</qresource>
        </RCC>
        ")
    configure_file("${QEXT_CMAKE_DIR}/plugin_resources_cached.qrc.in" "${_qrc_filepath}" @ONLY)

    if (QEXT_QT_VERSION VERSION_GREATER "4")
        QT5_ADD_RESOURCES(${QRC_SRCS} ${_qrc_filepath})
    else()
        QT4_ADD_RESOURCES(${QRC_SRCS} ${_qrc_filepath})
    endif()

endmacro()



include(TestCXXAcceptsFlag)

#! \ingroup CMakeUtilities
function(ctkFunctionCheckCompilerFlags CXX_FLAG_TO_TEST RESULT_VAR)
    if(CXX_FLAG_TO_TEST STREQUAL "")
        message(FATAL_ERROR "CXX_FLAG_TO_TEST shouldn't be empty")
    endif()

    # Internally, the macro CMAKE_CXX_ACCEPTS_FLAG calls TRY_COMPILE. To avoid
    # the cost of compiling the test each time the project is configured, the variable set by
    # the macro is added to the cache so that following invocation of the macro with
    # the same variable name skip the compilation step.
    # For that same reason, ctkFunctionCheckCompilerFlags function appends a unique suffix to
    # the HAS_FLAG variable. This suffix is created using a 'clean version' of the flag to test.
    string(REGEX REPLACE "-\\s\\$\\+\\*\\{\\}\\(\\)\\#" "" suffix ${CXX_FLAG_TO_TEST})
        CHECK_CXX_ACCEPTS_FLAG(${CXX_FLAG_TO_TEST} HAS_FLAG_${suffix})

    if(HAS_FLAG_${suffix})
        set(${RESULT_VAR} "${${RESULT_VAR}} ${CXX_FLAG_TO_TEST}" PARENT_SCOPE)
    endif()

endfunction()



function(ctkFunctionGetCompilerVisibilityFlags RESULT_VAR)

    # We only support hidden visibility for gcc for now. Clang 3.0 still has troubles with
    # correctly marking template declarations and explicit template instantiations as exported.
    # See http://comments.gmane.org/gmane.comp.compilers.clang.scm/50028
    # and http://llvm.org/bugs/show_bug.cgi?id=10113
    set(use_visibility_flags 0)

    if(CMAKE_COMPILER_IS_GNUCXX)

        set(use_visibility_flags 1)
        ctkFunctionGetGccVersion(${CMAKE_CXX_COMPILER} GCC_VERSION)

        # MinGW does not export all symbols automatically, so no need to set flags.
        #
        # With gcc < 4.5, RTTI symbols from classes declared in third-party libraries
        # which are not "gcc visibility aware" are marked with hidden visibility in
        # DSOs which include the class declaration and which are compiled with
        # hidden visibility. This leads to dynamic_cast and exception handling problems.
        # While this problem could be worked around by sandwiching the include
        # directives for the third-party headers between "#pragma visibility push/pop"
        # statements, it is generally safer to just use default visibility with
        # gcc < 4.5.

        if(${GCC_VERSION} VERSION_LESS "4.5" OR MINGW)
            set(use_visibility_flags 0)
        endif()

    endif()

    if(use_visibility_flags)
        set(visibility_flags "")
        ctkFunctionCheckCompilerFlags("-fvisibility=hidden" visibility_flags)
        ctkFunctionCheckCompilerFlags("-fvisibility-inlines-hidden" visibility_flags)
        set(${RESULT_VAR} "${${RESULT_VAR}} ${visibility_flags}" PARENT_SCOPE)
    endif()

endfunction()




#
# Depends on:
#  CTK/CMake/ctkMacroParseArguments.cmake
#  CTK/CMake/ctkMacroGeneratePluginManifest.cmake
#
#! \brief Build a CTK plug-in.
#!
#! This macro takes the usual arguments for building
#! a shared library using Qt. Additionally, it generates
#! plugin meta-data by creating a MANIFEST.MF text file
#! which is embedded in the share library as a Qt resource.
#!
#! The following variables can be set in a file named
#! manifest_headers.cmake, which will then be read by
#! this macro:
#!
#! - Plugin-ActivationPolicy
#! - Plugin-Category
#! - Plugin-ContactAddress
#! - Plugin-Copyright
#! - Plugin-Description
#! - Plugin-DocURL
#! - Plugin-Icon
#! - Plugin-License
#! - Plugin-Name
#! - Require-Plugin
#! - Plugin-Vendor
#! - Plugin-Version
#!
#! \ingroup CMakeAPI
macro(ctkMacroBuildPlugin)
    CtkMacroParseArguments(MY
        "EXPORT_DIRECTIVE;SRCS;MOC_SRCS;MOC_OPTIONS;UI_FORMS;INCLUDE_DIRECTORIES;EXPORTED_INCLUDE_SUFFIXES;TARGET_LIBRARIES;RESOURCES;CACHED_RESOURCEFILES;TRANSLATIONS;OUTPUT_DIR"
        "TEST_PLUGIN;NO_INSTALL"
        ${ARGN})

    # Keep parameter 'INCLUDE_DIRECTORIES' for backward compatibility

    # Sanity checks
    if(NOT DEFINED MY_EXPORT_DIRECTIVE)
        message(FATAL_ERROR "EXPORT_DIRECTIVE is mandatory")
    endif()

    # Print a warning if the project name does not match the directory name
    get_filename_component(_dir_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    string(REPLACE "." "_" _dir_name_with_ ${_dir_name})
    if(NOT _dir_name_with_ STREQUAL ${PROJECT_NAME})
        message(WARNING "Discouraged mismatch of plug-in project name [${PROJECT_NAME}] and top-level directory name [${CMAKE_CURRENT_SOURCE_DIR}].")
    endif()

    # Define library name
    set(lib_name ${PROJECT_NAME})

    # Plug-in target names must contain at least one _
    if(NOT lib_name MATCHES _)
        message(FATAL_ERROR "The plug-in project name ${lib_name} must contain at least one '_' character")
    endif()

    # Plugin are expected to be shared library
    set(MY_LIBRARY_TYPE "SHARED")

    # Clear the variables for the manifest headers
    set(Plugin-ActivationPolicy )
    set(Plugin-Category )
    set(Plugin-ContactAddress )
    set(Plugin-Copyright )
    set(Plugin-Description )
    set(Plugin-DocURL )
    set(Plugin-Icon )
    set(Plugin-License )
    set(Plugin-Name )
    set(Require-Plugin )
    set(Plugin-SymbolicName )
    set(Plugin-Vendor )
    set(Plugin-Version )

    set(Custom-Headers )

    if(MY_TEST_PLUGIN)
        # Since the test plug-ins are not considered when calculating
        # target dependencies via DGraph, we add the dependencies
        # manually here
        #message("${lib_name}_DEPENDENCIES ${MY_TARGET_LIBRARIES}")
        list(APPEND ${lib_name}_DEPENDENCIES ${MY_TARGET_LIBRARIES})
    endif()

    # If a file named manifest_headers.cmake exists, read it
    set(manifest_headers_dep )
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/manifest_headers.cmake")
        include(${CMAKE_CURRENT_SOURCE_DIR}/manifest_headers.cmake)
        set(manifest_headers_dep "${CMAKE_CURRENT_SOURCE_DIR}/manifest_headers.cmake")
    endif()

    string(REPLACE "_" "." Plugin-SymbolicName ${lib_name})

    # --------------------------------------------------------------------------
    # Include dirs
    if(MY_EXPORTED_INCLUDE_SUFFIXES)
        set(${lib_name}_INCLUDE_SUFFIXES ${MY_EXPORTED_INCLUDE_SUFFIXES}
            CACHE INTERNAL "List of exported plugin include dirs")

        set(my_includes )
        foreach(_suffix ${MY_EXPORTED_INCLUDE_SUFFIXES})
            list(APPEND my_includes ${CMAKE_CURRENT_SOURCE_DIR}/${_suffix})
        endforeach()
    else()
        set(${lib_name}_INCLUDE_SUFFIXES ""
            CACHE INTERNAL "List of exported plugin include dirs")

        set(my_includes )
    endif()

    list(APPEND my_includes
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR})

    # Add the include directories from the plugin dependencies
    # and external dependencies
    ctkFunctionGetIncludeDirs(my_includes ${lib_name})

    if(CMAKE_VERSION VERSION_LESS 2.8.12)
        include_directories(${my_includes})
    endif()

    if(QEXT_QT_VERSION VERSION_LESS "5")
        # Add Qt include dirs and defines
        include(${QT_USE_FILE})
    else()
        find_package(Qt5 COMPONENTS LinguistTools REQUIRED)
    endif()

    # Add the library directories from the external project
    ctkFunctionGetLibraryDirs(my_library_dirs ${lib_name})

    link_directories(${my_library_dirs})

    set(MY_LIBRARY_EXPORT_DIRECTIVE ${MY_EXPORT_DIRECTIVE})
    set(MY_EXPORT_HEADER_PREFIX "${lib_name}_")
    set(MY_LIBNAME ${lib_name})

    # message(CTK_EXPORT_HEADER_TEMPLATE=${CTK_EXPORT_HEADER_TEMPLATE})
    # configure_file(
    #     ${CTK_EXPORT_HEADER_TEMPLATE}
    #     ${CMAKE_CURRENT_BINARY_DIR}/${MY_EXPORT_HEADER_PREFIX}Export.h)
    # set(dynamicHeaders
        # "${dynamicHeaders};${CMAKE_CURRENT_BINARY_DIR}/${MY_EXPORT_HEADER_PREFIX}Export.h")

    # Make sure variable are cleared
    set(MY_MOC_CPP)
    set(MY_UI_CPP)
    set(MY_QRC_SRCS)

    # Wrap
    if (QEXT_QT_VERSION VERSION_GREATER "4")
        set(target)
        if(Qt5Core_VERSION VERSION_GREATER "5.2.0")
            set(target TARGET ${lib_name})
        endif()
        if(MY_MOC_SRCS)
            # this is a workaround for Visual Studio. The relative include paths in the generated
            # moc files can get very long and can't be resolved by the MSVC compiler.
            foreach(moc_src ${MY_MOC_SRCS})
                QT5_WRAP_CPP(MY_MOC_CPP ${moc_src} OPTIONS -f${moc_src} -DHAVE_QT5 ${MY_MOC_OPTIONS} ${target})
            endforeach()
        endif()
        QT5_WRAP_UI(MY_UI_CPP ${MY_UI_FORMS})
        if(DEFINED MY_RESOURCES)
            QT5_ADD_RESOURCES(MY_QRC_SRCS ${MY_RESOURCES})
        endif()
    else()
        if(MY_MOC_SRCS)
            # this is a workaround for Visual Studio. The relative include paths in the generated
            # moc files can get very long and can't be resolved by the MSVC compiler.
            foreach(moc_src ${MY_MOC_SRCS})
                QT4_WRAP_CPP(MY_MOC_CPP ${moc_src} OPTIONS -f${moc_src} ${MY_MOC_OPTIONS} TARGET ${lib_name})
            endforeach()
        endif()
        QT4_WRAP_UI(MY_UI_CPP ${MY_UI_FORMS})
        if(DEFINED MY_RESOURCES)
            QT4_ADD_RESOURCES(MY_QRC_SRCS ${MY_RESOURCES})
        endif()
    endif()
    # Add the generated manifest qrc file
    set(manifest_qrc_src )
    ctkFunctionGeneratePluginManifest(manifest_qrc_src
        ACTIVATIONPOLICY ${Plugin-ActivationPolicy}
        CATEGORY ${Plugin-Category}
        CONTACT_ADDRESS ${Plugin-ContactAddress}
        COPYRIGHT ${Plugin-Copyright}
        DESCRIPTION ${Plugin-Description}
        DOC_URL ${Plugin-DocURL}
        ICON ${Plugin-Icon}
        LICENSE ${Plugin-License}
        NAME ${Plugin-Name}
        REQUIRE_PLUGIN ${Require-Plugin}
        SYMBOLIC_NAME ${Plugin-SymbolicName}
        VENDOR ${Plugin-Vendor}
        VERSION ${Plugin-Version}
        CUSTOM_HEADERS ${Custom-Headers})

    if(manifest_headers_dep)
        set_property(SOURCE ${manifest_qrc_src} APPEND
            PROPERTY OBJECT_DEPENDS ${manifest_headers_dep})
    endif()
    list(APPEND MY_QRC_SRCS ${manifest_qrc_src})

    # Create translation files (.ts and .qm)
    set(_plugin_qm_files )
    set(_plugin_cached_resources_in_binary_tree )
    set(_translations_dir "${CMAKE_CURRENT_BINARY_DIR}/CTK-INF/l10n")
    if(MY_TRANSLATIONS)
        set_source_files_properties(${MY_TRANSLATIONS}
            PROPERTIES OUTPUT_LOCATION ${_translations_dir})
        if(QEXT_QT_VERSION VERSION_GREATER "4")
            qt5_create_translation(_plugin_qm_files ${MY_SRCS} ${MY_UI_FORMS} ${MY_TRANSLATIONS})
        else()
            QT4_CREATE_TRANSLATION(_plugin_qm_files ${MY_SRCS} ${MY_UI_FORMS} ${MY_TRANSLATIONS})
        endif()
    endif()

    if(_plugin_qm_files)
        foreach(_qm_file ${_plugin_qm_files})
            file(RELATIVE_PATH _relative_qm_file ${CMAKE_CURRENT_BINARY_DIR} ${_qm_file})
            list(APPEND _plugin_cached_resources_in_binary_tree ${_relative_qm_file})
        endforeach()
    endif()

    set(_plugin_cached_resources_in_source_tree )
    if(MY_CACHED_RESOURCEFILES)
        foreach(_cached_resource ${MY_CACHED_RESOURCEFILES})
            if(IS_ABSOLUTE "${_cached_resource}")
                # create a path relative to the current binary dir
                file(RELATIVE_PATH _relative_cached_resource ${CMAKE_CURRENT_BINARY_DIR} ${_cached_resource})
                list(APPEND _plugin_cached_resources_in_binary_tree ${_relative_cached_resource})
            else()
                list(APPEND _plugin_cached_resources_in_source_tree ${_cached_resource})
            endif()
        endforeach()
    endif()

    # Add any other additional resource files
    if(_plugin_cached_resources_in_source_tree OR _plugin_cached_resources_in_binary_tree)
        string(REPLACE "." "_" _plugin_symbolicname ${Plugin-SymbolicName})
        ctkMacroGeneratePluginResourcefile(MY_QRC_SRCS
            NAME ${_plugin_symbolicname}_cached.qrc
            PREFIX ${Plugin-SymbolicName}
            RESOURCES ${_plugin_cached_resources_in_source_tree}
            BINARY_RESOURCES ${_plugin_cached_resources_in_binary_tree})
    endif()

    source_group("Resources" FILES
        ${MY_RESOURCES}
        ${MY_UI_FORMS}
        ${MY_TRANSLATIONS})

    source_group("Generated" FILES
        ${MY_QRC_SRCS}
        ${MY_MOC_CPP}
        ${MY_UI_CPP}
        ${_plugin_qm_files})

    add_library(${lib_name} ${MY_LIBRARY_TYPE}
        ${MY_SRCS}
        ${MY_MOC_CPP}
        ${MY_UI_CPP}
        ${MY_QRC_SRCS}
        ${_plugin_qm_files})

    if(NOT CMAKE_VERSION VERSION_LESS 2.8.12)
        target_include_directories(${lib_name}
            PUBLIC "$<BUILD_INTERFACE:${my_includes}>"
            "$<INSTALL_INTERFACE:${CTK_INSTALL_PLUGIN_INCLUDE_DIR}/${Plugin-SymbolicName}>")
        if(QEXT_QT_VERSION VERSION_LESS "5")
            # Add Qt include dirs to the target
            target_include_directories(${lib_name} PUBLIC ${QT_INCLUDE_DIR})
            foreach(module Qt3Support QTOPENGL QTASSISTANT QTDESIGNER QTMOTIF QTNSPLUGIN
                    QAXSERVER QAXCONTAINER QTDECLARATIVE QTSCRIPT QTSVG QTUITOOLS QTHELP
                    QTWEBKIT PHONON QTSCRIPTTOOLS QTMULTIMEDIA QTXMLPATTERNS QTGUI QTTEST
                    QtDBus QtXml QtSql QTNETWORK QTCORE)
                if (QT_USE_${module} OR QT_USE_${module}_DEPENDS)
                    if (QT_${module}_FOUND)
                        target_include_directories(${lib_name} PUBLIC ${QT_${module}_INCLUDE_DIR})
                    endif ()
                endif ()
            endforeach()
        endif()
    else()
        find_package(Qt5LinguistTools REQUIRED)
    endif()

    if(MY_TEST_PLUGIN AND QEXT_QT_VERSION VERSION_GREATER "4")
        find_package(Qt5Test REQUIRED)
        if(CMAKE_VERSION VERSION_LESS 2.8.12)
            target_link_libraries(${lib_name} Qt5::Test)
        else()
            target_link_libraries(${lib_name} PRIVATE Qt5::Test)
        endif()
    endif()

    # Set the output directory for the plugin
    if(MY_OUTPUT_DIR)
        set(output_dir_suffix "/${MY_OUTPUT_DIR}")
    else()
        set(output_dir_suffix "")
    endif()

    foreach(type RUNTIME LIBRARY ARCHIVE)
        if(NOT DEFINED CTK_PLUGIN_${type}_OUTPUT_DIRECTORY AND CMAKE_${type}_OUTPUT_DIRECTORY)
            # Put plug-ins by default into a "plugins" subdirectory
            set(CTK_PLUGIN_${type}_OUTPUT_DIRECTORY "${CMAKE_${type}_OUTPUT_DIRECTORY}/plugins")
        endif()

        if(IS_ABSOLUTE "${CTK_PLUGIN_${type}_OUTPUT_DIRECTORY}")
            set(plugin_${type}_output_dir "${CTK_PLUGIN_${type}_OUTPUT_DIRECTORY}${output_dir_suffix}")
        elseif(CMAKE_${type}_OUTPUT_DIRECTORY)
            set(plugin_${type}_output_dir "${CMAKE_${type}_OUTPUT_DIRECTORY}/${CTK_PLUGIN_${type}_OUTPUT_DIRECTORY}${output_dir_suffix}")
        else()
            set(plugin_${type}_output_dir "${CMAKE_CURRENT_BINARY_DIR}/${CTK_PLUGIN_${type}_OUTPUT_DIRECTORY}${output_dir_suffix}")
        endif()

        if(MY_TEST_PLUGIN)
            # Test plug-ins will always be put in a separate directory
            if(CMAKE_${type}_OUTPUT_DIRECTORY)
                set(plugin_${type}_output_dir "${CMAKE_${type}_OUTPUT_DIRECTORY}/test_plugins")
            else()
                set(plugin_${type}_output_dir "${PROJECT_BINARY_DIR}/test_plugins")
            endif()
        endif()
    endforeach()

    set(plugin_compile_flags "-DQT_PLUGIN")
    ctkFunctionGetCompilerVisibilityFlags(plugin_compile_flags)

    # Apply properties to the library target.
    set_target_properties(${lib_name} PROPERTIES
        COMPILE_FLAGS "${plugin_compile_flags}"
        RUNTIME_OUTPUT_DIRECTORY ${plugin_RUNTIME_output_dir}
        LIBRARY_OUTPUT_DIRECTORY ${plugin_LIBRARY_output_dir}
        ARCHIVE_OUTPUT_DIRECTORY ${plugin_ARCHIVE_output_dir}
        PREFIX "lib")

    if(NOT MY_TEST_PLUGIN AND NOT MY_NO_INSTALL)
        # Install rules
        install(TARGETS ${lib_name} EXPORT CTKExports
            RUNTIME DESTINATION ${CTK_INSTALL_PLUGIN_DIR} COMPONENT RuntimePlugins
            LIBRARY DESTINATION ${CTK_INSTALL_PLUGIN_DIR} COMPONENT RuntimePlugins
            ARCHIVE DESTINATION ${CTK_INSTALL_PLUGIN_DIR} COMPONENT Development)
    endif()

    set(my_libs
        ${MY_TARGET_LIBRARIES})

    if(MINGW)
        list(APPEND my_libs ssp) # add stack smash protection lib
    endif()

    if(CMAKE_VERSION VERSION_LESS 2.8.12)
        target_link_libraries(${lib_name} ${my_libs})
    else()
        target_link_libraries(${lib_name} PUBLIC ${my_libs})
    endif()

    if(NOT MY_TEST_PLUGIN)
        set(${CMAKE_PROJECT_NAME}_PLUGIN_LIBRARIES ${${CMAKE_PROJECT_NAME}_PLUGIN_LIBRARIES} ${lib_name}
            CACHE INTERNAL "CTK plugins" FORCE)
    endif()

    if(NOT MY_TEST_PLUGIN AND NOT MY_NO_INSTALL)
        # Install headers
        file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.tpp")
        install(FILES
            ${headers}
            ${dynamicHeaders}
            DESTINATION ${CTK_INSTALL_PLUGIN_INCLUDE_DIR}/${Plugin-SymbolicName} COMPONENT Development)
    endif()

endmacro()




#!
#! This macro could be invoked using two different signatures:
#!   ctkFunctionGetTargetLibraries(TARGET_LIBS)
#! or
#!   ctkFunctionGetTargetLibraries(TARGET_LIBS "/path/to/ctk_target_dir")
#!
#! Without specifying the second argument, the current folder will be used.
#!
#! \ingroup CMakeUtilities
function(ctkFunctionGetTargetLibraries varname)
    set(expanded_target_library_list)

    set(TARGET_DIRECTORY ${ARGV1})
    set(_target_name )
    if("${TARGET_DIRECTORY}" STREQUAL "")
        set(TARGET_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
        set(_target_name ${PROJECT_NAME})
    endif()

    set(filepath ${TARGET_DIRECTORY}/target_libraries.cmake)
    set(manifestpath ${TARGET_DIRECTORY}/manifest_headers.cmake)

    # Check if "target_libraries.cmake" or "manifest_headers.cmake" file exists
    if(NOT EXISTS ${filepath} AND NOT EXISTS ${manifestpath})
        message(FATAL_ERROR "${filepath} or ${manifestpath} doesn't exists !")
    endif()

    # Make sure the variable is cleared
    set(target_libraries )
    set(Require-Plugin )

    if(EXISTS ${filepath})
        # Let's make sure target_libraries contains only strings
        file(STRINGS "${filepath}" stringtocheck) # read content of 'filepath' into 'stringtocheck'
        string(REGEX MATCHALL "[^\\#]\\$\\{.*\\}" incorrect_elements ${stringtocheck})
        foreach(incorrect_element ${incorrect_elements})
            string(REGEX REPLACE "\\$|\\{|\\}" "" correct_element ${incorrect_element})
            message(FATAL_ERROR "In ${filepath}, ${incorrect_element} should be replaced by ${correct_element}")
        endforeach()

        include(${filepath})

        if(_target_name)
            list(APPEND target_libraries "${${_target_name}_OPTIONAL_DEPENDENCIES}")
        endif()

        # Loop over all target library, if it does *NOT* start with "CTK",
        # let's resolve the variable to access its content
        foreach(target_library ${target_libraries})
            if(${target_library} MATCHES "^CTK[a-zA-Z0-9]+$" OR
                    ${target_library} MATCHES "^org_commontk_[a-zA-Z0-9_]+$")
                list(APPEND expanded_target_library_list ${target_library})
            else()
                list(APPEND expanded_target_library_list "${${target_library}}")
            endif()
        endforeach()
    endif()

    if(EXISTS ${manifestpath})
        # Let's make sure Require-Plugins contains only strings
        file(STRINGS "${manifestpath}" stringtocheck) # read content of 'manifestpath' into 'stringtocheck'
        string(REGEX MATCHALL "[^\\#]\\$\\{.*\\}" incorrect_elements ${stringtocheck})
        foreach(incorrect_element ${incorrect_elements})
            string(REGEX REPLACE "\\$|\\{|\\}" "" correct_element ${incorrect_element})
            message(FATAL_ERROR "In ${manifestpath}, ${incorrect_element} should be replaced by ${correct_element}")
        endforeach()

        include(${manifestpath})

        # Loop over all plugin dependencies,
        foreach(plugin_symbolicname ${Require-Plugin})
            string(REPLACE "." "_" plugin_library ${plugin_symbolicname})
            list(APPEND expanded_target_library_list ${plugin_library})
        endforeach()
    endif()

    # Pass the list of target libraries to the caller
    set(${varname} ${expanded_target_library_list} PARENT_SCOPE)

endfunction()
