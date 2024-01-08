########################################################################################################################
#
# Library: QExt
#
# Copyright (C) 2022 ChengXueWen.
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


include_guard(GLOBAL)

#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
macro(qext_internal_get_add_qml_keywords option_args single_args multi_args internal_option_args internal_single_args internal_multi_args)
    set(${option_args}
        DESIGNER_SUPPORTED
        FOLLOW_FOREIGN_VERSIONING
        NO_PLUGIN
        NO_PLUGIN_OPTIONAL
        NO_CREATE_PLUGIN_TARGET
        NO_GENERATE_PLUGIN_SOURCE
        NO_GENERATE_QMLTYPES
        NO_GENERATE_QMLDIR
        NO_LINT
        NO_CACHEGEN
        ENABLE_TYPE_COMPILER
        __QEXT_INTERNAL_STATIC_MODULE
        __QEXT_INTERNAL_SYSTEM_MODULE)
    set(${single_args}
        URI
        VERSION
        PLUGIN_TARGET
        TYPEINFO
        CLASS_NAME
        CLASSNAME  # TODO: Remove once all other repos have been updated to use
        #       CLASS_NAME instead.
        TYPE_COMPILER_NAMESPACE)
    set(${multi_args}
        QML_FILES
        RESOURCES
        IMPORTS
        IMPORT_PATH
        OPTIONAL_IMPORTS
        DEFAULT_IMPORTS
        DEPENDENCIES
        PAST_MAJOR_VERSIONS)
    # Args used by qext_internal_add_qml directly, which should not be passed to any other
    # functions.
    #
    # INSTALL_SOURCE_QMLTYPES takes a path to an existing plugins.qmltypes file that should be
    # installed.
    #
    # INSTALL_SOURCE_QMLDIR takes a path to an existing qmldir file that should be installed.
    set(${internal_option_args})
    set(${internal_single_args}
        INSTALL_SOURCE_QMLTYPES
        INSTALL_SOURCE_QMLDIR)
    set(${internal_multi_args})
endmacro()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
# This function is essentially a wrapper around qext6_add_qml_module().
# It creates the targets explicitly and sets up internal properties before passing those targets to
# qext6_add_qml_module() for further updates.
# All keywords supported by qext_internal_add_module() can be used, as can most
# keywords for qext6_add_qml_module() except RESOURCE_PREFIX and
# OUTPUT_TARGETS.
#
# OUTPUT_DIRECTORY and INSTALL_DIRECTORY will be given more appropriate defaults
# if not provided by the caller. The defaults are usually what you want to use.
#
# - SOURCES is only passed through to qext_add_plugin() or
#   qext_internal_add_module() but not to qext6_add_qml_module().
#
# See qext_add_plugin() and qext6_add_qml_module() for the full set of
# supported keywords.
function(qext_add_qml target)
    qext_internal_get_add_library_keywords(
        module_option_args
        module_single_args
        module_multi_args)
    qext_internal_get_add_qml_keywords(
        qml_module_option_args
        qml_module_single_args
        qml_module_multi_args
        qml_module_internal_option_args
        qml_module_internal_single_args
        qml_module_internal_multi_args)
    # TODO: Remove these once all repos have been updated to not use them
    set(ignore_option_args
        SKIP_TYPE_REGISTRATION  # Now always done
        PLUGIN_OPTIONAL         # Now the default
        GENERATE_QMLTYPES       # Now the default
        INSTALL_QMLTYPES)        # Now the default

    set(option_args
        ${module_option_args}
        ${qml_module_option_args}
        ${ignore_option_args}
        ${qml_module_internal_option_args})
    set(single_args
        ${module_single_args}
        ${qml_module_single_args}
        ${qml_module_internal_single_args})
    set(multi_args
        ${module_multi_args}
        ${qml_module_multi_args}
        ${qml_module_internal_multi_args})

    qext_parse_all_arguments(arg "qext_internal_add_qml"
        "${option_args}"
        "${single_args}"
        "${multi_args}"
        ${ARGN})

    set(QEXT_QML_OUTPUT_DIRECTORY "${QEXT_BUILD_DIR}/${INSTALL_QMLDIR}")
    string(REPLACE "." "/" target_path ${arg_URI})
    if(NOT arg_OUTPUT_DIRECTORY)
        set(arg_OUTPUT_DIRECTORY "${QEXT_QML_OUTPUT_DIRECTORY}/${target_path}")
    endif()
    if(NOT arg_INSTALL_DIRECTORY)
        set(arg_INSTALL_DIRECTORY "${INSTALL_QMLDIR}/${target_path}")
    endif()
    if(arg_NO_PLUGIN)
        unset(arg_PLUGIN_TARGET)
    elseif(NOT arg_PLUGIN_TARGET)
        set(arg_PLUGIN_TARGET ${target}plugin)
    endif()

    # TODO: Support for old keyword, remove once all repos no longer use CLASSNAME
    if(arg_CLASSNAME)
        if(arg_CLASS_NAME AND NOT arg_CLASSNAME STREQUAL arg_CLASS_NAME)
            message(FATAL_ERROR
                "Both CLASSNAME and CLASS_NAME were given and were different. "
                "Update call site to only use CLASS_NAME.")
        endif()
        set(arg_CLASS_NAME "${arg_CLASSNAME}")
        unset(arg_CLASSNAME)
    endif()

    set(plugin_args "")
    if(arg_NO_PLUGIN OR NOT arg_PLUGIN_TARGET STREQUAL target)
        # Allow using an existing backing target.
        if(NOT TARGET ${target})
            # Create the backing target now to handle module-related things
            qext_remove_args(module_args
                ARGS_TO_REMOVE
                ${ignore_option_args}
                ${qml_module_option_args}
                ${qml_module_single_args}
                ${qml_module_multi_args}
                ${qml_module_internal_option_args}
                ${qml_module_internal_single_args}
                ${qml_module_internal_multi_args}
                OUTPUT_DIRECTORY
                INSTALL_DIRECTORY
                ALL_ARGS
                ${option_args}
                ${single_args}
                ${multi_args}
                ARGS
                ${ARGN})
            qext_add_library(${target} ${module_args})
        elseif(arg_SOURCES)
            # If a module target was pre-created, we still need to pass the additional sources.
            target_sources(${target} PRIVATE ${arg_SOURCES})
        endif()
    else()
        # Since we are not creating a separate backing target, we have to pass
        # through the default args to the plugin target creation instead
        qext_internal_get_internal_add_plugin_keywords(
            plugin_option_args plugin_single_args plugin_multi_args)
        set(args_to_remove ${option_args} ${single_args} ${multi_args})
        list(REMOVE_ITEM args_to_remove
            ${plugin_option_args}
            ${plugin_single_args}
            ${plugin_multi_args})
        qext_remove_args(plugin_args
            ARGS_TO_REMOVE
            ${args_to_remove}
            DEFAULT_IF
            OUTPUT_DIRECTORY
            INSTALL_DIRECTORY
            CLASS_NAME
            CLASSNAME
            ALL_ARGS
            ${option_args}
            ${single_args}
            ${multi_args}
            ARGS
            ${ARGN})
    endif()

    set(add_qml_module_args "")

    if(NOT arg_NO_PLUGIN AND NOT arg_NO_CREATE_PLUGIN_TARGET)
        # If the qext_internal_add_qml call didn't specify a CLASS_NAME, we need to pre-compute
        # it here and pass it along to qext_add_plugin -> qext_add_plugin so that
        # qext_add_qml_plugin does not complain about differing class names (the default pre-computed
        # class name of a regular plugin and qml plugin are different).
        if(NOT arg_CLASS_NAME)
            _qext_internal_compute_qml_plugin_class_name_from_uri("${arg_URI}" arg_CLASS_NAME)
        endif()

        # Create plugin target now so we can set internal things
        list(APPEND plugin_args
            PLUGIN_TYPE qml_plugin
            DEFAULT_IF FALSE
            OUTPUT_DIRECTORY ${arg_OUTPUT_DIRECTORY}
            INSTALL_DIRECTORY ${arg_INSTALL_DIRECTORY}
            CLASS_NAME ${arg_CLASS_NAME})

        qext_add_plugin(${arg_PLUGIN_TARGET} ${plugin_args})

        # Use the plugin target name as the main part of the plugin basename.
        set(plugin_basename "${arg_PLUGIN_TARGET}")

        # If the target name already ends with a "plugin" suffix, remove it and re-add it to the end
        # of the base name after the infix.
        if(plugin_basename MATCHES "(.+)plugin$")
            set(plugin_basename "${CMAKE_MATCH_1}")
        endif()

        # Add a the infix if Qt was configured with one.
        if(QEXT_LIBINFIX)
            string(APPEND plugin_basename "${QEXT_LIBINFIX}")
        endif()

        # Add the "plugin" suffix after the infix.
        string(APPEND plugin_basename "plugin")

        # Lowercase the whole thing and use it as the basename of the plugin library.
        string(TOLOWER "${plugin_basename}" plugin_basename)
        set_target_properties(${arg_PLUGIN_TARGET} PROPERTIES OUTPUT_NAME "${plugin_basename}")

        get_target_property(export_name ${arg_PLUGIN_TARGET} EXPORT_NAME)
        if(export_name)
            list(APPEND add_qml_module_args
                INSTALLED_PLUGIN_TARGET "${QEXT_CMAKE_EXPORT_NAMESPACE}::${export_name}")
        else()
            list(APPEND add_qml_module_args
                INSTALLED_PLUGIN_TARGET "${QEXT_CMAKE_EXPORT_NAMESPACE}::${arg_PLUGIN_TARGET}")
        endif()

        if(NOT arg_PLUGIN_TARGET STREQUAL target)
            get_target_property(lib_type ${arg_PLUGIN_TARGET} TYPE)
            if(lib_type STREQUAL "STATIC_LIBRARY")
                # This is needed so that the dependency on the backing target
                # is included in the plugin's find_package() support.
                # The naming of backing targets and plugins don't typically
                # follow the pattern of other plugins with regard to Private
                # suffixes, so the dependency logic in qext_add_plugin()
                # doesn't find these. For non-static builds, the private
                # dependency doesn't get exposed to find_package(), so we don't
                # have to make the dependency known for that case.
                set_property(TARGET ${arg_PLUGIN_TARGET} APPEND PROPERTY
                    _qext_target_deps "${INSTALL_CMAKE_NAMESPACE}${target}\;${PROJECT_VERSION}")
            endif()
        endif()
    endif()

    # TODO: Check if we need arg_SOURCES in this condition
    if (arg_SOURCES AND NOT arg_TYPEINFO)
        set(arg_TYPEINFO "plugins.qmltypes")
    endif()

    # Pass through options if given (these are present/absent, not true/false)
    foreach(opt IN LISTS qml_module_option_args)
        if(arg_${opt})
            list(APPEND add_qml_module_args ${opt})
        endif()
    endforeach()

    # Pass through single and multi-value args as provided.
    foreach(arg IN LISTS qml_module_single_args qml_module_multi_args)
        if(DEFINED arg_${arg})
            list(APPEND add_qml_module_args ${arg} ${arg_${arg}})
        endif()
    endforeach()

    if (arg_FOLLOW_FOREIGN_VERSIONING)
        message(FATAL_ERROR "Do not set FOLLOW_FOREIGN_VERSIONING for module ${target}. It is already set by default for internal modules.")
    endif()

    get_target_property(qext_namespace ${QEXT_CMAKE_EXPORT_NAMESPACE}::Core _qext_namespace)
    if(qext_namespace)
        list(APPEND add_qml_module_args NAMESPACE ${qext_namespace})
    endif()

    if (arg_ENABLE_TYPE_COMPILER AND NOT arg_TYPE_COMPILER_NAMESPACE)
        # if qmltc namespace is not specified explicitly, use Qt's namespace
        list(APPEND add_qml_module_args TYPE_COMPILER_NAMESPACE ${qext_namespace})
    endif()

    message(add_qml_module_args=${add_qml_module_args})
    # Update the backing and plugin targets with qml-specific things.
    qext_internal_add_qml(${target}
        ${add_qml_module_args}
        __QEXT_INTERNAL_INSTALL_METATYPES_JSON
        OUTPUT_DIRECTORY ${arg_OUTPUT_DIRECTORY}
        RESOURCE_PREFIX "/QExt-Project.org/imports"
        OUTPUT_TARGETS output_targets
        FOLLOW_FOREIGN_VERSIONING)

    if(output_targets)
        set(plugin_export_targets)
        set(backing_lib_export_targets)

        # Separate which output target should go to which export set.
        # The plugin initializer library should go to the plugin export set, the rest should go to
        # the backing lib export set.
        # In the case when the plugin target is the same as the backing lib target, all of the
        # output targets will go to the plugin export set.

        foreach(output_target IN LISTS output_targets)
            get_target_property(is_plugin_init ${output_target} _is_qext_plugin_init_target)
            if(is_plugin_init)
                list(APPEND plugin_export_targets ${output_target})

                # Plugin initializers associated with an internal module need the internal
                # platform flags.
                qext_internal_link_internal_platform_for_object_library("${output_target}")
            else()
                list(APPEND backing_lib_export_targets ${output_target})
            endif()
        endforeach()

        if(backing_lib_export_targets)
            qext_install(TARGETS ${backing_lib_export_targets}
                EXPORT "${INSTALL_CMAKE_NAMESPACE}${target}Targets"
                DESTINATION "${arg_INSTALL_DIRECTORY}")
            qext_internal_record_rcc_object_files(${target} "${backing_lib_export_targets}"
                INSTALL_DIRECTORY "${arg_INSTALL_DIRECTORY}")

            qext_internal_add_targets_to_additional_targets_export_file(
                TARGETS ${backing_lib_export_targets}
                EXPORT_NAME_PREFIX "${INSTALL_CMAKE_NAMESPACE}${target}")
        endif()

        if(arg_PLUGIN_TARGET AND plugin_export_targets)
            qext_install(TARGETS ${plugin_export_targets}
                EXPORT "${INSTALL_CMAKE_NAMESPACE}${arg_PLUGIN_TARGET}Targets"
                DESTINATION "${arg_INSTALL_DIRECTORY}")

            qext_internal_add_targets_to_additional_targets_export_file(
                TARGETS ${plugin_export_targets}
                EXPORT_NAME_PREFIX "${INSTALL_CMAKE_NAMESPACE}${arg_PLUGIN_TARGET}")
        endif()
    endif()

    if(DEFINED arg_QML_FILES OR DEFINED arg_RESOURCES)
        foreach(resource_file IN LISTS arg_QML_FILES arg_RESOURCES)
            __qext_get_relative_resource_path_for_file(file_resource_path ${resource_file})
            get_filename_component(resource_dir  ${file_resource_path} DIRECTORY)
            get_filename_component(resource_name ${file_resource_path} NAME)
            if(resource_dir)
                set(dest "${arg_INSTALL_DIRECTORY}/${resource_dir}")
            else()
                set(dest "${arg_INSTALL_DIRECTORY}")
            endif()
            qext_install(
                FILES ${resource_file}
                DESTINATION ${dest}
                RENAME ${resource_name})
        endforeach()
    endif()

    if(NOT arg_NO_GENERATE_QMLTYPES)
        qext_install(
            FILES ${arg_OUTPUT_DIRECTORY}/$<TARGET_PROPERTY:${target},QEXT_QML_MODULE_TYPEINFO>
            DESTINATION "${arg_INSTALL_DIRECTORY}")
    endif()

    if(NOT arg_NO_GENERATE_QMLDIR)
        qext_install(
            FILES ${arg_OUTPUT_DIRECTORY}/qmldir
            DESTINATION "${arg_INSTALL_DIRECTORY}")
    endif()

    if(arg_INSTALL_SOURCE_QMLTYPES)
        message(AUTHOR_WARNING
            "INSTALL_SOURCE_QMLTYPES option is deprecated and should not be used. "
            "Please port your module to use declarative type registration.")

        set(files ${arg_INSTALL_SOURCE_QMLTYPES})
        if(QEXT_WILL_INSTALL)
            install(
                FILES ${files}
                DESTINATION "${arg_INSTALL_DIRECTORY}")
        else()
            file(
                COPY ${files}
                DESTINATION "${arg_OUTPUT_DIRECTORY}")
        endif()
    endif()

    if(arg_INSTALL_SOURCE_QMLDIR)
        message(AUTHOR_WARNING
            "INSTALL_SOURCE_QMLDIR option is deprecated and should not be used. "
            "Please port your module to use declarative type registration.")

        set(files ${arg_INSTALL_SOURCE_QMLDIR})
        if(QEXT_WILL_INSTALL)
            install(
                FILES ${files}
                DESTINATION "${arg_INSTALL_DIRECTORY}")
        else()
            file(
                COPY ${files}
                DESTINATION "${arg_OUTPUT_DIRECTORY}")
        endif()
    endif()
endfunction()



include(CMakeParseArguments)

### Finds where to qmlplugindump binary is installed
### Requires that 'qmake' directory is in PATH
function(FindQmlPluginDump)
    execute_process(
        COMMAND qmake -query QEXT_INSTALL_BINS
        OUTPUT_VARIABLE QEXT_BIN_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(QMLPLUGINDUMP_BIN ${QEXT_BIN_DIR}/qmlplugindump PARENT_SCOPE)
endfunction()

### Sets QEXT_INSTALL_QML to the directory where QML Plugins should be installed
function(FindQtInstallQml)
    execute_process(
        COMMAND qmake -query QEXT_INSTALL_QML
        OUTPUT_VARIABLE PROC_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(QEXT_INSTALL_QML ${PROC_RESULT} PARENT_SCOPE)
endfunction()

function(add_qmlplugin TARGET)
    set(options NO_AUTORCC NO_AUTOMOC)
    set(oneValueArgs URI VERSION BINARY_DIR)
    set(multiValueArgs SOURCES QMLFILES)
    cmake_parse_arguments(QMLPLUGIN "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    ### At least TARGET, URI and VERSION must be specified
    if(NOT QMLPLUGIN_URI OR NOT QMLPLUGIN_VERSION)
        message(WARNING "TARGET, URI and VERSION must be set, no files generated")
        return()
    endif()

    ### Depending on project hierarchy, one might want to specify a custom binary dir
    if(NOT QMLPLUGIN_BINARY_DIR)
        set(QMLPLUGIN_BINARY_DIR ${CMAKE_BINARY_DIR})
    endif()

    ### Source files
    add_library(${TARGET} SHARED ${QMLPLUGIN_SOURCES})

    ### QML files, just to make them visible in the editor
    add_custom_target("${TARGET}-qmlfiles" SOURCES ${QMLPLUGIN_QMLFILES})

    ### No AutoMOC or AutoRCC
    if(QMLPLUGIN_NO_AUTORCC)
        set_target_properties(${TARGET} PROPERTIES AUTOMOC OFF)
    else()
        set_target_properties(${TARGET} PROPERTIES AUTOMOC ON)
    endif()
    if(QMLPLUGIN_NO_AUTOMOC)
        set_target_properties(${TARGET} PROPERTIES AUTOMOC OFF)
    else()
        set_target_properties(${TARGET} PROPERTIES AUTOMOC ON)
    endif()

    ### Find location of qmlplugindump (stored in QMLPLUGINDUMP_BIN)
    FindQmlPluginDump()
    ### Find where to install QML Plugins (stored in QEXT_INSTALL_QML)
    FindQtInstallQml()

    set(COPY_QMLDIR_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/qmldir $<TARGET_FILE_DIR:${TARGET}>/qmldir)
    set(COPY_QMLFILES_COMMAND ${CMAKE_COMMAND} -E copy ${QMLPLUGIN_QMLFILES} $<TARGET_FILE_DIR:${TARGET}>)
    set(GENERATE_QMLTYPES_COMMAND ${QMLPLUGINDUMP_BIN} -nonrelocatable ${QMLPLUGIN_URI} ${QMLPLUGIN_VERSION} ${QMLPLUGIN_BINARY_DIR} > ${CMAKE_CURRENT_BINARY_DIR}/plugin.qmltypes)

    ### Copy qmldir from project source to binary dir
    add_custom_command(
        TARGET ${TARGET}
        POST_BUILD
        COMMAND ${COPY_QMLDIR_COMMAND}
        COMMENT "Copying qmldir to binary directory")

    ### Copy QML-files from project source to binary dir
    if(QMLPLUGIN_QMLFILES)
        add_custom_command(
            TARGET ${TARGET}
            POST_BUILD
            COMMAND ${COPY_QMLFILES_COMMAND}
            COMMENT "Copying QML files to binary directory")
    endif()

    ### Create command to generate plugin.qmltypes after build
    add_custom_command(
        TARGET ${TARGET}
        POST_BUILD
        COMMAND ${GENERATE_QMLTYPES_COMMAND}
        COMMENT "Generating plugin.qmltypes")

    string(REPLACE "." "/" QMLPLUGIN_INSTALL_URI ${QMLPLUGIN_URI})

    ### Install library
    install(TARGETS ${TARGET} DESTINATION ${QEXT_INSTALL_QML}/${QMLPLUGIN_INSTALL_URI})

    ### Install aditional files
    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/qmldir
        ${CMAKE_CURRENT_BINARY_DIR}/plugin.qmltypes
        ${QMLPLUGIN_QMLFILES}
        DESTINATION ${QEXT_INSTALL_QML}/${QMLPLUGIN_INSTALL_URI})
endfunction()


function(qext_internal_add_qml target)
    set(args_option
        STATIC
        SHARED
        DESIGNER_SUPPORTED
        FOLLOW_FOREIGN_VERSIONING
        NO_PLUGIN
        NO_PLUGIN_OPTIONAL
        NO_CREATE_PLUGIN_TARGET
        NO_GENERATE_PLUGIN_SOURCE
        NO_GENERATE_QMLTYPES
        NO_GENERATE_QMLDIR
        NO_LINT
        NO_CACHEGEN
        NO_RESOURCE_TARGET_PATH
        NO_IMPORT_SCAN
        # TODO: Remove once all usages have also been removed
        SKIP_TYPE_REGISTRATION
        ENABLE_TYPE_COMPILER

        # Used only by _qext_internal_qml_type_registration()
        # TODO: Remove this once qext6_extract_metatypes does not install by default.
        __QEXT_INTERNAL_INSTALL_METATYPES_JSON

        # Used to mark modules as having static side effects (i.e. if they install an image provider)
        __QEXT_INTERNAL_STATIC_MODULE
        # Used to mark modules as being a system module that provides all builtins
        __QEXT_INTERNAL_SYSTEM_MODULE)

    set(args_single
        PLUGIN_TARGET
        INSTALLED_PLUGIN_TARGET  # Internal option only, it may be removed
        OUTPUT_TARGETS
        RESOURCE_PREFIX
        URI
        TARGET_PATH   # Internal option only, it may be removed
        VERSION
        OUTPUT_DIRECTORY
        CLASS_NAME
        CLASSNAME  # TODO: For backward compatibility, remove once all repos no longer use it
        TYPEINFO
        NAMESPACE
        # TODO: We don't handle installation, warn if callers used these with the old
        #       API and eventually remove them once we have updated all other repos
        RESOURCE_EXPORT
        INSTALL_DIRECTORY
        INSTALL_LOCATION
        TYPE_COMPILER_NAMESPACE)

    set(args_multi
        SOURCES
        QML_FILES
        RESOURCES
        IMPORTS
        IMPORT_PATH
        OPTIONAL_IMPORTS
        DEFAULT_IMPORTS
        DEPENDENCIES
        PAST_MAJOR_VERSIONS)

    cmake_parse_arguments(PARSE_ARGV 1 arg
        "${args_option}"
        "${args_single}"
        "${args_multi}")
    if(arg_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unknown/unexpected arguments: ${arg_UNPARSED_ARGUMENTS}")
    endif()

    # Warn about options we no longer need/use (these were used by the internal
    # targets and examples, but the logic has been shifted to
    # qext_internal_add_qml_module() or left as a responsibility of the caller).
    if(DEFINED arg_RESOURCE_EXPORT)
        message(AUTHOR_WARNING
            "RESOURCE_EXPORT will be ignored. This function does not handle "
            "installation, which is what RESOURCE_EXPORT was previously used "
            "for. Please update your project to install the target directly.")
    endif()

    if(DEFINED arg_INSTALL_DIRECTORY)
        message(AUTHOR_WARNING
            "INSTALL_DIRECTORY will be ignored. This function does not handle "
            "installation, please update your project to install the target "
            "directly.")
    endif()

    if(DEFINED arg_INSTALL_LOCATION)
        message(AUTHOR_WARNING
            "INSTALL_LOCATION will be ignored. This function does not handle "
            "installation, please update your project to install the target "
            "directly.")
    endif()

    if(arg_SKIP_TYPE_REGISTRATION)
        message(AUTHOR_WARNING
            "SKIP_TYPE_REGISTRATION is no longer used and will be ignored.")
    endif()

    # Mandatory arguments
    if (NOT arg_URI)
        message(FATAL_ERROR
            "Called without a module URI. Please specify one using the URI argument.")
    endif()

    if (NOT arg_VERSION)
        message(FATAL_ERROR "Called without a module version. Please specify one using the VERSION argument.")
    endif()

    if ("${arg_VERSION}" MATCHES "^([0-9]+\\.[0-9]+)\\.[0-9]+$")
        set(arg_VERSION "${CMAKE_MATCH_1}")
    endif()

    if (NOT "${arg_VERSION}" MATCHES "^[0-9]+\\.[0-9]+$")
        message(FATAL_ERROR
            "Called with an invalid version argument: '${arg_VERSION}'. "
            "Expected version in the form: VersionMajor.VersionMinor.")
    endif()

    # Other arguments and checking for invalid combinations
    if (NOT arg_TARGET_PATH)
        # NOTE: This will always be used for copying things to the build
        #       directory, but it will not be used for resource paths if
        #       NO_RESOURCE_TARGET_PATH was given.
        string(REPLACE "." "/" arg_TARGET_PATH ${arg_URI})
    endif()

    if(arg_NO_PLUGIN AND DEFINED arg_PLUGIN_TARGET)
        message(FATAL_ERROR
            "NO_PLUGIN was specified, but PLUGIN_TARGET was also given. "
            "At most one of these can be present.")
    endif()

    if (DEFINED arg_TYPE_COMPILER_NAMESPACE AND NOT arg_ENABLE_TYPE_COMPILER)
        message(WARNING
            "TYPE_COMPILER_NAMESPACE is set, but ENABLE_TYPE_COMPILER is not specified. "
            "The TYPE_COMPILER_NAMESPACE value will be ignored.")
    endif()

    set(is_executable FALSE)
    if(TARGET ${target})
        if(arg_STATIC OR arg_SHARED)
            message(FATAL_ERROR
                "Cannot use STATIC or SHARED keyword when passed an existing target (${target})")
        endif()

        # With CMake 3.17 and earlier, a source file's generated property isn't
        # visible outside of the directory scope in which it is set. That can
        # lead to build errors for things like type registration due to CMake
        # thinking nothing will create a missing file on the first run. With
        # CMake 3.18 or later, we can force that visibility. Policy CMP0118
        # added in CMake 3.20 should have made this unnecessary, but we can't
        # rely on that because the user project controls what it is set to at
        # the point where it matters, which is the end of the target's
        # directory scope (hence we can't even test for it here).
        get_target_property(source_dir ${target} SOURCE_DIR)
        if(NOT source_dir STREQUAL CMAKE_CURRENT_SOURCE_DIR AND
                CMAKE_VERSION VERSION_LESS "3.18")
            message(WARNING
                "qext6_add_qml_module() is being called in a different "
                "directory scope to the one in which the target \"${target}\" "
                "was created. CMake 3.18 or later is required to generate a "
                "project robustly for this scenario, but you are using "
                "CMake ${CMAKE_VERSION}. Ideally, qext6_add_qml_module() should "
                "only be called from the same scope as the one the target was "
                "created in to avoid dependency and visibility problems.")
        endif()

        get_target_property(backing_target_type ${target} TYPE)
        get_target_property(is_android_executable "${target}" _qext_is_android_executable)
        if (backing_target_type STREQUAL "EXECUTABLE" OR is_android_executable)
            if(DEFINED arg_PLUGIN_TARGET)
                message(FATAL_ERROR
                    "A QML module with an executable as its backing target "
                    "cannot have a plugin.")
            endif()
            if(arg_NO_CREATE_PLUGIN_TARGET)
                message(WARNING
                    "A QML module with an executable as its backing target "
                    "cannot have a plugin. The NO_CREATE_PLUGIN_TARGET option "
                    "has no effect and should be removed.")
            endif()
            set(arg_NO_PLUGIN TRUE)
            set(lib_type "")
            set(is_executable TRUE)
        elseif(arg_NO_RESOURCE_TARGET_PATH)
            message(FATAL_ERROR
                "NO_RESOURCE_TARGET_PATH cannot be used for a backing target "
                "that is not an executable")
        elseif(backing_target_type STREQUAL "STATIC_LIBRARY")
            set(lib_type STATIC)
        elseif(backing_target_type MATCHES "(SHARED|MODULE)_LIBRARY")
            set(lib_type SHARED)
        else()
            message(FATAL_ERROR "Unsupported backing target type: ${backing_target_type}")
        endif()
    else()
        if(arg_STATIC AND arg_SHARED)
            message(FATAL_ERROR
                "Both STATIC and SHARED specified, at most one can be given")
        endif()

        if(arg_NO_RESOURCE_TARGET_PATH)
            message(FATAL_ERROR
                "NO_RESOURCE_TARGET_PATH can only be provided when an existing "
                "executable target is passed in as the backing target")
        endif()

        # Explicit arguments take precedence, otherwise default to using the same
        # staticality as what Qt was built with. This follows the already
        # established default behavior for building ordinary Qt plugins.
        # We don't allow the standard CMake BUILD_SHARED_LIBS variable to control
        # the default because that can lead to different defaults depending on
        # whether you build with a separate backing target or not.
        if(arg_STATIC)
            set(lib_type STATIC)
        elseif(arg_SHARED)
            set(lib_type SHARED)
        elseif(QEXT6_IS_SHARED_LIBS_BUILD)
            set(lib_type SHARED)
        else()
            set(lib_type STATIC)
        endif()
    endif()

    if(arg_NO_PLUGIN)
        # Simplifies things a bit further below
        set(arg_PLUGIN_TARGET "")
    elseif(NOT DEFINED arg_PLUGIN_TARGET)
        if(arg_NO_CREATE_PLUGIN_TARGET)
            # We technically could allow this and rely on the project using the
            # default plugin target name, but not doing so gives us the
            # flexibility to potentially change that default later if needed.
            message(FATAL_ERROR
                "PLUGIN_TARGET must also be provided when NO_CREATE_PLUGIN_TARGET "
                "is used. If you want to disable creating a plugin altogether, "
                "use the NO_PLUGIN option instead.")
        endif()
        set(arg_PLUGIN_TARGET ${target}plugin)
    endif()
    if(arg_NO_CREATE_PLUGIN_TARGET AND arg_PLUGIN_TARGET STREQUAL target AND NOT TARGET ${target})
        message(FATAL_ERROR
            "PLUGIN_TARGET is the same as the backing target, which is allowed, "
            "but NO_CREATE_PLUGIN_TARGET was also given and the target does not "
            "exist. Either ensure the target is already created or do not "
            "specify NO_CREATE_PLUGIN_TARGET.")
    endif()
    if(NOT arg_INSTALLED_PLUGIN_TARGET)
        set(arg_INSTALLED_PLUGIN_TARGET ${arg_PLUGIN_TARGET})
    endif()

    set(no_gen_source)
    if(arg_NO_GENERATE_PLUGIN_SOURCE)
        set(no_gen_source NO_GENERATE_PLUGIN_SOURCE)
    endif()

    if(arg_OUTPUT_DIRECTORY)
        get_filename_component(arg_OUTPUT_DIRECTORY "${arg_OUTPUT_DIRECTORY}"
            ABSOLUTE BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
    else()
        if("${QEXT_QML_OUTPUT_DIRECTORY}" STREQUAL "")
            set(arg_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
            # For libraries, we assume/require that the source directory
            # structure is consistent with the target path. For executables,
            # the source directory will usually not reflect the target path
            # and the project will often expect to be able to use resource
            # paths that don't include the target path (they need the
            # NO_RESOURCE_TARGET_PATH option if they do that). Tooling always
            # needs the target path in the file system though, so the output
            # directory should always have it. Handle the special case for
            # executables to ensure this is what we get.
            if(is_executable)
                string(APPEND arg_OUTPUT_DIRECTORY "/${arg_TARGET_PATH}")
            endif()
        else()
            if(NOT IS_ABSOLUTE "${QEXT_QML_OUTPUT_DIRECTORY}")
                message(FATAL_ERROR
                    "QEXT_QML_OUTPUT_DIRECTORY must be an absolute path, but given: "
                    "${QEXT_QML_OUTPUT_DIRECTORY}")
            endif()
            # This inherently does what we want for libraries and executables
            set(arg_OUTPUT_DIRECTORY ${QEXT_QML_OUTPUT_DIRECTORY}/${arg_TARGET_PATH})
        endif()
    endif()

    # Sanity check that we are not trying to have two different QML modules use
    # the same output directory.
    get_property(dirs GLOBAL PROPERTY _qext_all_qml_output_dirs)
    if(dirs)
        list(FIND dirs "${arg_OUTPUT_DIRECTORY}" index)
        if(NOT index EQUAL -1)
            get_property(qml_targets GLOBAL PROPERTY _qext_all_qml_targets)
            list(GET qml_targets ${index} other_target)
            message(FATAL_ERROR
                "Output directory for target \"${target}\" is already used by "
                "another QML module (target \"${other_target}\"). "
                "Output directory is:\n  ${arg_OUTPUT_DIRECTORY}\n")
        endif()
    endif()
    set_property(GLOBAL APPEND PROPERTY _qext_all_qml_output_dirs ${arg_OUTPUT_DIRECTORY})
    set_property(GLOBAL APPEND PROPERTY _qext_all_qml_targets     ${target})

    # TODO: Support for old keyword, remove once all repos no longer use CLASSNAME
    if(arg_CLASSNAME)
        if(arg_CLASS_NAME AND NOT arg_CLASSNAME STREQUAL arg_CLASS_NAME)
            message(FATAL_ERROR
                "Both CLASSNAME and CLASS_NAME were given and were different. "
                "Update call site to only use CLASS_NAME.")
        endif()
        set(arg_CLASS_NAME "${arg_CLASSNAME}")
        unset(arg_CLASSNAME)
    endif()

    if(NOT arg_CLASS_NAME AND TARGET "${arg_PLUGIN_TARGET}")
        get_target_property(class_name ${arg_PLUGIN_TARGET} QEXT_PLUGIN_CLASS_NAME)
        if(class_name)
            set(arg_CLASS_NAME)
        endif()
    endif()
    if(NOT arg_CLASS_NAME)
        _qext_internal_compute_qml_plugin_class_name_from_uri("${arg_URI}" arg_CLASS_NAME)
    endif()

    if(TARGET ${target})
        if(arg_PLUGIN_TARGET STREQUAL target)
            # Insert the plugin's URI into its meta data to enable usage
            # of static plugins in QtDeclarative (like in mkspecs/features/qml_plugin.prf).
            set_property(TARGET ${target} APPEND PROPERTY
                AUTOMOC_MOC_OPTIONS "-Muri=${arg_URI}")
        endif()
    else()
        if(arg_PLUGIN_TARGET STREQUAL target)
            set(conditional_args ${no_gen_source})
            if(arg_NAMESPACE)
                list(APPEND conditional_args NAMESPACE ${arg_NAMESPACE})
            endif()
            qext6_add_qml_plugin(${target}
                ${lib_type}
                OUTPUT_DIRECTORY ${arg_OUTPUT_DIRECTORY}
                URI ${arg_URI}
                CLASS_NAME ${arg_CLASS_NAME}
                ${conditional_args})
        else()
            qext6_add_library(${target} ${lib_type})
        endif()
    endif()

    if(NOT target STREQUAL Qml)
        target_link_libraries(${target} PRIVATE ${QEXT_CMAKE_EXPORT_NAMESPACE}::Qml)
    endif()

    if(NOT arg_TYPEINFO)
        set(arg_TYPEINFO ${target}.qmltypes)
    endif()

    foreach(import_set IN ITEMS IMPORTS OPTIONAL_IMPORTS DEFAULT_IMPORTS)
        foreach(import IN LISTS arg_${import_set})
            string(FIND ${import} "/" slash_position REVERSE)
            if (slash_position EQUAL -1)
                set_property(TARGET ${target} APPEND PROPERTY
                    QEXT_QML_MODULE_${import_set} "${import}")
            else()
                string(SUBSTRING ${import} 0 ${slash_position} import_module)
                math(EXPR slash_position "${slash_position} + 1")
                string(SUBSTRING ${import} ${slash_position} -1 import_version)
                if (import_version MATCHES "^([0-9]+(\\.[0-9]+)?|auto)$")
                    set_property(TARGET ${target} APPEND PROPERTY
                        QEXT_QML_MODULE_${import_set} "${import_module} ${import_version}")
                else()
                    message(FATAL_ERROR
                        "Invalid module ${import} version number. "
                        "Expected 'VersionMajor', 'VersionMajor.VersionMinor' or 'auto'.")
                endif()
            endif()
        endforeach()
    endforeach()

    foreach(dependency IN LISTS arg_DEPENDENCIES)
        string(FIND ${dependency} "/" slash_position REVERSE)
        if (slash_position EQUAL -1)
            set_property(TARGET ${target} APPEND PROPERTY
                QEXT_QML_MODULE_DEPENDENCIES "${dependency}"
            )
    else()
        string(SUBSTRING ${dependency} 0 ${slash_position} dep_module)
        math(EXPR slash_position "${slash_position} + 1")
        string(SUBSTRING ${dependency} ${slash_position} -1 dep_version)
        if (dep_version MATCHES "^([0-9]+(\\.[0-9]+)?|auto)$")
            set_property(TARGET ${target} APPEND PROPERTY
                QEXT_QML_MODULE_DEPENDENCIES "${dep_module} ${dep_version}"
            )
    else()
        message(FATAL_ERROR
            "Invalid module dependency version number. "
            "Expected 'VersionMajor', 'VersionMajor.VersionMinor' or 'auto'."
        )
endif()
endif()
endforeach()

_qext_internal_canonicalize_resource_path("${arg_RESOURCE_PREFIX}" arg_RESOURCE_PREFIX)
if(arg_NO_RESOURCE_TARGET_PATH)
    set(qext_qml_module_resource_prefix "${arg_RESOURCE_PREFIX}")
else()
    if(arg_RESOURCE_PREFIX STREQUAL "/")   # Checked so we prevent double-slash
        set(qext_qml_module_resource_prefix "/${arg_TARGET_PATH}")
    else()
        set(qext_qml_module_resource_prefix "${arg_RESOURCE_PREFIX}/${arg_TARGET_PATH}")
    endif()
endif()

set_target_properties(${target} PROPERTIES
    QEXT_QML_MODULE_NO_LINT "${arg_NO_LINT}"
    QEXT_QML_MODULE_NO_CACHEGEN "${arg_NO_CACHEGEN}"
    QEXT_QML_MODULE_NO_GENERATE_QMLDIR "${arg_NO_GENERATE_QMLDIR}"
    QEXT_QML_MODULE_NO_PLUGIN "${arg_NO_PLUGIN}"
    QEXT_QML_MODULE_NO_PLUGIN_OPTIONAL "${arg_NO_PLUGIN_OPTIONAL}"
    QEXT_QML_MODULE_NO_IMPORT_SCAN "${arg_NO_IMPORT_SCAN}"
    _qext_qml_module_follow_foreign_versioning "${arg_FOLLOW_FOREIGN_VERSIONING}"
    QEXT_QML_MODULE_URI "${arg_URI}"
    QEXT_QML_MODULE_TARGET_PATH "${arg_TARGET_PATH}"
    QEXT_QML_MODULE_VERSION "${arg_VERSION}"
    QEXT_QML_MODULE_CLASS_NAME "${arg_CLASS_NAME}"

    QEXT_QML_MODULE_PLUGIN_TARGET "${arg_PLUGIN_TARGET}"
    QEXT_QML_MODULE_INSTALLED_PLUGIN_TARGET "${arg_INSTALLED_PLUGIN_TARGET}"

    # Also Save the PLUGIN_TARGET values in a separate property to circumvent
    # https://gitlab.kitware.com/cmake/cmake/-/issues/21484 when exporting the properties
    _qext_qml_module_plugin_target "${arg_PLUGIN_TARGET}"
    _qext_qml_module_installed_plugin_target "${arg_INSTALLED_PLUGIN_TARGET}"

    QEXT_QML_MODULE_DESIGNER_SUPPORTED "${arg_DESIGNER_SUPPORTED}"
    QEXT_QML_MODULE_IS_STATIC "${arg___QEXT_INTERNAL_STATIC_MODULE}"
    QEXT_QML_MODULE_IS_SYSTEM "${arg___QEXT_INTERNAL_SYSTEM_MODULE}"
    QEXT_QML_MODULE_OUTPUT_DIRECTORY "${arg_OUTPUT_DIRECTORY}"
    QEXT_QML_MODULE_RESOURCE_PREFIX "${qext_qml_module_resource_prefix}"
    QEXT_QML_MODULE_PAST_MAJOR_VERSIONS "${arg_PAST_MAJOR_VERSIONS}"
    QEXT_QML_MODULE_TYPEINFO "${arg_TYPEINFO}"

    # TODO: Check how this is used by qext6_android_generate_deployment_settings()
    QEXT_QML_IMPORT_PATH "${arg_IMPORT_PATH}")

# Executables don't have a plugin target, so no need to export the properties.
if(NOT backing_target_type STREQUAL "EXECUTABLE" AND NOT is_android_executable)
    set_property(TARGET ${target} APPEND PROPERTY
        EXPORT_PROPERTIES _qext_qml_module_plugin_target _qext_qml_module_installed_plugin_target)
endif()

set(ensure_set_properties
    QEXT_QML_MODULE_PLUGIN_TYPES_FILE
    QEXT_QML_MODULE_RESOURCES       # Original files as provided by the project (absolute)
    QEXT_QML_MODULE_RESOURCE_PATHS  # By qmlcachegen (resource paths)
    QEXT_QMLCACHEGEN_DIRECT_CALLS
    QEXT_QMLCACHEGEN_EXECUTABLE
    QEXT_QMLCACHEGEN_ARGUMENTS)
foreach(prop IN LISTS ensure_set_properties)
    get_target_property(val ${target} ${prop})
    if("${val}" MATCHES "-NOTFOUND$")
        set_target_properties(${target} PROPERTIES ${prop} "")
    endif()
endforeach()

if(NOT arg_NO_GENERATE_QMLTYPES)
    set(type_registration_extra_args "")
    if(arg___QEXT_INTERNAL_INSTALL_METATYPES_JSON)
        list(APPEND type_registration_extra_args __QEXT_INTERNAL_INSTALL_METATYPES_JSON)
    endif()
    if(arg_NAMESPACE)
        list(APPEND type_registration_extra_args NAMESPACE ${arg_NAMESPACE})
    endif()
    _qext_internal_qml_type_registration(${target} ${type_registration_extra_args})
endif()

set(output_targets)

if(NOT arg_NO_GENERATE_QMLDIR)
    _qext_internal_target_generate_qmldir(${target})

    # Embed qmldir in qrc. The following comments relate mostly to Qt5->6 transition.
    # The requirement to keep the same resource name might no longer apply, but it doesn't
    # currently appear to cause any hinderance to keep it.
    # The qmldir resource name needs to match the one generated by qmake's qml_module.prf, to
    # ensure that all Q_INIT_RESOURCE(resource_name) calls in Qt code don't lead to undefined
    # symbol errors when linking an application project.
    # The Q_INIT_RESOURCE() calls are not strictly necessary anymore because the CMake Qt
    # build passes around the compiled resources as object files.
    # These object files have global initiliazers that don't get discared when linked into
    # an application (as opposed to when the resource libraries were embedded into the static
    # libraries when Qt was built with qmake).
    # The reason to match the naming is to ensure that applications link successfully regardless
    # if Qt was built with CMake or qmake, while the build system transition phase is still
    # happening.
    string(REPLACE "/" "_" qmldir_resource_name "qmake_${arg_TARGET_PATH}")

    # The qmldir file ALWAYS has to be under the target path, even in the
    # resources. If it isn't, an explicit import can't find it. We need a
    # second copy NOT under the target path if NO_RESOURCE_TARGET_PATH is
    # given so that the implicit import will work.
    set(prefixes "${qext_qml_module_resource_prefix}")
    if(arg_NO_RESOURCE_TARGET_PATH)
        # The above prefixes item won't include the target path, so add a
        # second one that does.
        if(qext_qml_module_resource_prefix STREQUAL "/")
            list(APPEND prefixes "/${arg_TARGET_PATH}")
        else()
            list(APPEND prefixes "${qext_qml_module_resource_prefix}/${arg_TARGET_PATH}")
        endif()
    endif()
    set_source_files_properties(${arg_OUTPUT_DIRECTORY}/qmldir
        PROPERTIES QEXT_RESOURCE_ALIAS "qmldir")

    foreach(prefix IN LISTS prefixes)
        set(resource_targets)
        qext6_add_resources(${target} ${qmldir_resource_name}
            FILES ${arg_OUTPUT_DIRECTORY}/qmldir
            PREFIX "${prefix}"
            OUTPUT_TARGETS resource_targets)
        list(APPEND output_targets ${resource_targets})
        # If we are adding the same file twice, we need a different resource
        # name for the second one. It has the same QEXT_RESOURCE_ALIAS but a
        # different prefix, so we can't put it in the same resource.
        string(APPEND qmldir_resource_name "_copy")
    endforeach()
endif()

if(NOT arg_NO_PLUGIN AND NOT arg_NO_CREATE_PLUGIN_TARGET)
    # This also handles the case where ${arg_PLUGIN_TARGET} already exists,
    # including where it is the same as ${target}. If ${arg_PLUGIN_TARGET}
    # already exists, it will update the necessary things that are specific
    # to qml plugins.
    if(TARGET ${arg_PLUGIN_TARGET})
        set(plugin_args "")
    else()
        set(plugin_args ${lib_type})
    endif()
    list(APPEND plugin_args ${no_gen_source})
    if(arg_NAMESPACE)
        list(APPEND plugin_args NAMESPACE ${arg_NAMESPACE})
    endif()
    qext6_add_qml_plugin(${arg_PLUGIN_TARGET}
        ${plugin_args}
        OUTPUT_DIRECTORY ${arg_OUTPUT_DIRECTORY}
        BACKING_TARGET ${target}
        CLASS_NAME ${arg_CLASS_NAME})
endif()

if(TARGET "${arg_PLUGIN_TARGET}" AND NOT arg_PLUGIN_TARGET STREQUAL target)
    target_link_libraries(${arg_PLUGIN_TARGET} PRIVATE ${target})
endif()

target_sources(${target} PRIVATE ${arg_SOURCES})

# QML tooling might need to map build dir paths to source dir paths. Create
# a mapping file before qext6_target_qml_sources() to be able to use it
if(arg_ENABLE_TYPE_COMPILER)
    # But: for now, only enable this when dealing with qmltc
    _qext_internal_qml_map_build_files(${target} "${arg_QML_FILES}" dir_map_qrc)
    set_property(TARGET ${target} APPEND PROPERTY _qext_generated_qrc_files "${dir_map_qrc}")
endif()

set(cache_target)
qext6_target_qml_sources(${target}
    __QEXT_INTERNAL_FORCE_DEFER_QMLDIR
    QML_FILES ${arg_QML_FILES}
    RESOURCES ${arg_RESOURCES}
    OUTPUT_TARGETS cache_target
    PREFIX "${qext_qml_module_resource_prefix}")
list(APPEND output_targets ${cache_target})

# Build an init object library for static plugins and propagate it along with the plugin
# target.
# TODO: Figure out if we can move this code block into qext_add_qml_plugin. Need to consider
#       various corner cases.
#       QEXTBUG-96937
if(TARGET "${arg_PLUGIN_TARGET}")
    get_target_property(plugin_lib_type ${arg_PLUGIN_TARGET} TYPE)
    if(plugin_lib_type STREQUAL "STATIC_LIBRARY")
        __qext_internal_add_static_plugin_init_object_library(
            "${arg_PLUGIN_TARGET}" plugin_init_target)
        list(APPEND output_targets ${plugin_init_target})

        __qext_internal_propagate_object_library("${arg_PLUGIN_TARGET}" "${plugin_init_target}")
    endif()
endif()

if(NOT arg_NO_GENERATE_QMLDIR)
    if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.19.0")
        # Defer the write to allow more qml files to be added later by calls to
        # qext6_target_qml_sources(). We wrap the deferred call with EVAL CODE
        # so that ${target} is evaluated now rather than the end of the scope.
        # We also delay target finalization until after our deferred write
        # because the qmldir file must be written before any finalizer
        # might call qext_import_qml_plugins().
        cmake_language(EVAL CODE
            "cmake_language(DEFER ID_VAR write_id CALL _qext_internal_write_deferred_qmldir_file ${target})")
        _qext_internal_delay_finalization_until_after(${write_id})
    else()
        # Can't defer the write, have to do it now
        _qext_internal_write_deferred_qmldir_file(${target})
    endif()
endif()

if (arg_ENABLE_TYPE_COMPILER)
    _qext_internal_target_enable_qmltc(${target}
        QML_FILES ${arg_QML_FILES}
        IMPORT_PATHS ${arg_IMPORT_PATH}
        NAMESPACE ${arg_TYPE_COMPILER_NAMESPACE})
endif()

if(arg_OUTPUT_TARGETS)
    set(${arg_OUTPUT_TARGETS} ${output_targets} PARENT_SCOPE)
endif()

endfunction()
