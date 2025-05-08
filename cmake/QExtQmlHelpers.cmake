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


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
macro(qext_internal_get_internal_add_qml_module_keywords option_args single_args multi_args
        internal_option_args internal_single_args internal_multi_args)
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
        __QT_INTERNAL_STATIC_MODULE
        __QT_INTERNAL_SYSTEM_MODULE)
    set(${single_args}
        URI
        VERSION
        PLUGIN_TARGET
        TYPEINFO
        CLASS_NAME
        TYPE_COMPILER_NAMESPACE)
    set(${multi_args}
        QML_FILES
        RESOURCES
        IMPORTS
        IMPORT_PATH
        PLUGIN_SOURCES
        OPTIONAL_IMPORTS
        DEFAULT_IMPORTS
        DEPENDENCIES
        PAST_MAJOR_VERSIONS)
    # Args used by qt_internal_add_qml_module directly, which should not be passed to any other
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
# This function is essentially a wrapper around qt6_add_qml_module().
# It creates the targets explicitly and sets up internal properties before passing those targets to qt6_add_qml_module()
# for further updates.
# All keywords supported by qt_internal_add_module() can be used, as can most keywords for qt6_add_qml_module() except
# RESOURCE_PREFIX and OUTPUT_TARGETS.
#
# OUTPUT_DIRECTORY and INSTALL_DIRECTORY will be given more appropriate defaults
# if not provided by the caller. The defaults are usually what you want to use.
#
# - SOURCES is only passed through to qt_internal_add_plugin() or
#   qt_internal_add_module() but not to qt6_add_qml_module()
#
# See qt_internal_add_plugin() and qt6_add_qml_module() for the full set of supported keywords.
#-----------------------------------------------------------------------------------------------------------------------
function(qt_internal_add_qml_module target)
    qext_internal_get_internal_add_module_keywords(
        module_option_args
        module_single_args
        module_multi_args)

    qext_internal_get_internal_add_qml_module_keywords(
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
        INSTALL_QMLTYPES)       # Now the default

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

    qext_parse_all_arguments(arg "qt_internal_add_qml_module"
        "${option_args}"
        "${single_args}"
        "${multi_args}"
        ${ARGN})

    set(QEXT_QML_OUTPUT_DIRECTORY "${QEXT_BUILD_DIR}/${QEXT_INSTALL_QMLDIR}")
    # message(QEXT_QML_OUTPUT_DIRECTORY=${QEXT_QML_OUTPUT_DIRECTORY})
    string(REPLACE "." "/" target_path ${arg_URI})
    if(NOT arg_OUTPUT_DIRECTORY)
        set(arg_OUTPUT_DIRECTORY "${QEXT_QML_OUTPUT_DIRECTORY}/${target_path}")
    endif()
    # message(arg_OUTPUT_DIRECTORY=${arg_OUTPUT_DIRECTORY})
    if(NOT arg_INSTALL_DIRECTORY)
        set(arg_INSTALL_DIRECTORY "${QEXT_INSTALL_QMLDIR}/${target_path}")
    endif()
    # message(arg_INSTALL_DIRECTORY=${arg_INSTALL_DIRECTORY})
    if(arg_NO_PLUGIN)
        unset(arg_PLUGIN_TARGET)
    elseif(NOT arg_PLUGIN_TARGET)
        set(arg_PLUGIN_TARGET ${target}plugin)
    endif()
     message(arg_PLUGIN_TARGET=${arg_PLUGIN_TARGET})

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
            # message(------module_args=${module_args})
            qext_add_library(${target} ${module_args})
        elseif(arg_SOURCES)
            # If a module target was pre-created, we still need to pass the additional sources.
            target_sources(${target} PRIVATE ${arg_SOURCES})
        endif()
    else()
        # Since we are not creating a separate backing target, we have to pass
        # through the default args to the plugin target creation instead
        qext_internal_get_internal_add_qml_module_keywords(plugin_option_args plugin_single_args plugin_multi_args)
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
            ALL_ARGS
            ${option_args}
            ${single_args}
            ${multi_args}
            ARGS
            ${ARGN})
    endif()

    set(add_qml_module_args "")
    if(NOT arg_NO_PLUGIN AND NOT arg_NO_CREATE_PLUGIN_TARGET)
        # If the qt_internal_add_qml_module call didn't specify a CLASS_NAME, we need to pre-compute
        # it here and pass it along to qt_internal_add_plugin -> qt_add_plugin so that
        # qt_add_qml_plugin does not complain about differing class names (the default pre-computed
        # class name of a regular plugin and qml plugin are different).
        if(NOT arg_CLASS_NAME)
            qext_internal_compute_qml_plugin_class_name_from_uri("${arg_URI}" arg_CLASS_NAME)
        endif()

        # Create plugin target now so we can set internal things
        list(APPEND plugin_args
            PLUGIN_TYPE qml_plugin
            DEFAULT_IF FALSE
            SOURCES ${arg_PLUGIN_SOURCES}
            PUBLIC_LIBRARIES ${target}
            LIBRARIES ${target}Private
            OUTPUT_DIRECTORY ${arg_OUTPUT_DIRECTORY}
            INSTALL_DIRECTORY ${arg_INSTALL_DIRERY}
            CLASS_NAME ${arg_CLASS_NAME})

        # message(arg_PLUGIN_TARGET=${arg_PLUGIN_TARGET})
        # message(plugin_args=${plugin_args})
        qext_add_plugin(${arg_PLUGIN_TARGET} ${plugin_args})

        # Use the plugin target name as the main part of the plugin basename.
        string(TOLOWER "${arg_PLUGIN_TARGET}" plugin_basename)

        # If the target name already ends with a "plugin" suffix, remove it and re-add it to the end
        # of the base name after the infix.
        if(plugin_basename MATCHES "(.+)plugin$")
            set(plugin_basename "${CMAKE_MATCH_1}")
        endif()

        # Add a the infix if Qt was configured with one.
        if(QT_LIBINFIX)
            string(APPEND plugin_basename "${QT_LIBINFIX}")
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
                # suffixes, so the dependency logic in qt_internal_add_plugin()
                # doesn't find these. For non-static builds, the private
                # dependency doesn't get exposed to find_package(), so we don't
                # have to make the dependency known for that case.
                set_property(TARGET ${arg_PLUGIN_TARGET} APPEND PROPERTY
                    _qt_target_deps "${INSTALL_CMAKE_NAMESPACE}${target}\;${PROJECT_VERSION}")
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
        message(FATAL_ERROR "Do not set FOLLOW_FOREIGN_VERSIONING for module ${target}. "
            "It is already set by default for internal modules.")
    endif()

    get_target_property(qext_namespace ${QEXT_CMAKE_EXPORT_NAMESPACE}::Core _qext_namespace)
    if(qext_namespace)
        list(APPEND add_qml_module_args NAMESPACE ${qext_namespace})
    endif()

    if (arg_ENABLE_TYPE_COMPILER AND NOT arg_TYPE_COMPILER_NAMESPACE)
        # if qmltc namespace is not specified explicitly, use QExt's namespace
        list(APPEND add_qml_module_args TYPE_COMPILER_NAMESPACE ${qext_namespace})
    endif()
    # Update the backing and plugin targets with qml-specific things.
#     message(add_qml_module_args=${add_qml_module_args})
    qt6_add_qml_module(${target}
        ${add_qml_module_args}
        __QT_INTERNAL_INSTALL_METATYPES_JSON
        OUTPUT_DIRECTORY ${arg_OUTPUT_DIRECTORY}
        RESOURCE_PREFIX "/QExt.org/imports"
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
            get_target_property(is_plugin_init ${output_target} _is_qt_plugin_init_target)
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
            qt_internal_record_rcc_object_files(${target} "${backing_lib_export_targets}"
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
            qext_internal_get_relative_resource_path_for_file(file_resource_path ${resource_file})
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
        if(QT_WILL_INSTALL)
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
        if(QT_WILL_INSTALL)
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


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qt_add_qml_module)
    message(qt_add_qml_module-----------)
    qt6_add_qml_module(${ARGV})
    cmake_parse_arguments(PARSE_ARGV 1 arg "" "OUTPUT_TARGETS" "")
    if(arg_OUTPUT_TARGETS)
        set(${arg_OUTPUT_TARGETS} ${${arg_OUTPUT_TARGETS}} PARENT_SCOPE)
    endif()
endfunction()

#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qt6_add_qml_module target)
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

        # Used only by qext_internal_qml_type_registration()
        # TODO: Remove this once qt6_extract_metatypes does not install by default.
        __QT_INTERNAL_INSTALL_METATYPES_JSON

        # Used to mark modules as having static side effects (i.e. if they install an image provider)
        __QT_INTERNAL_STATIC_MODULE
        # Used to mark modules as being a system module that provides all builtins
        __QT_INTERNAL_SYSTEM_MODULE)

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
        PLUGIN_SOURCES
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
    # qt_internal_add_qml_module() or left as a responsibility of the caller).
    if(DEFINED arg_RESOURCE_EXPORT)
        message(AUTHOR_WARNING
            "RESOURCE_EXPORT will be ignored. This function does not handle installation, which is what "
            "RESOURCE_EXPORT was previously used for. Please update your project to install the target directly.")
    endif()

    if(DEFINED arg_INSTALL_DIRECTORY)
        message(AUTHOR_WARNING
            "INSTALL_DIRECTORY will be ignored. This function does not handle installation, please update "
            "your project to install the target directly.")
    endif()

    if(DEFINED arg_INSTALL_LOCATION)
        message(AUTHOR_WARNING
            "INSTALL_LOCATION will be ignored. This function does not handle installation, please update "
            "your project to install the target directly.")
    endif()

    if(arg_SKIP_TYPE_REGISTRATION)
        message(AUTHOR_WARNING "SKIP_TYPE_REGISTRATION is no longer used and will be ignored.")
    endif()

    # Mandatory arguments
    if (NOT arg_URI)
        message(FATAL_ERROR "Called without a module URI. Please specify one using the URI argument.")
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
            message(FATAL_ERROR "Cannot use STATIC or SHARED keyword when passed an existing target (${target})")
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
        if(NOT source_dir STREQUAL CMAKE_CURRENT_SOURCE_DIR AND CMAKE_VERSION VERSION_LESS "3.18")
            message(WARNING
                "qt6_add_qml_module() is being called in a different "
                "directory scope to the one in which the target \"${target}\" "
                "was created. CMake 3.18 or later is required to generate a "
                "project robustly for this scenario, but you are using "
                "CMake ${CMAKE_VERSION}. Ideally, qt6_add_qml_module() should "
                "only be called from the same scope as the one the target was "
                "created in to avoid dependency and visibility problems.")
        endif()

        get_target_property(backing_target_type ${target} TYPE)
        get_target_property(is_android_executable "${target}" _qt_is_android_executable)
        if (backing_target_type STREQUAL "EXECUTABLE" OR is_android_executable)
            if(DEFINED arg_PLUGIN_TARGET)
                message(FATAL_ERROR "A QML module with an executable as its backing target cannot have a plugin.")
            endif()
            if(arg_NO_CREATE_PLUGIN_TARGET)
                message(WARNING
                    "A QML module with an executable as its backing target "
                    "cannot have a plugin. The NO_CREATE_PLUGIN_TARGET option "
                    "has no effect and should be removed.")
            endif()
            set(lib_type "")
            set(is_executable TRUE)
            set(arg_NO_PLUGIN TRUE)
        elseif(arg_NO_RESOURCE_TARGET_PATH)
            message(FATAL_ERROR "NO_RESOURCE_TARGET_PATH cannot be used for a backing target that is not an executable")
        elseif(backing_target_type STREQUAL "STATIC_LIBRARY")
            set(lib_type STATIC)
        elseif(backing_target_type MATCHES "(SHARED|MODULE)_LIBRARY")
            set(lib_type SHARED)
        else()
            message(FATAL_ERROR "Unsupported backing target type: ${backing_target_type}")
        endif()
    else()
        if(arg_STATIC AND arg_SHARED)
            message(FATAL_ERROR "Both STATIC and SHARED specified, at most one can be given")
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
        elseif(QT6_IS_SHARED_LIBS_BUILD)
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
    # message(arg_OUTPUT_DIRECTORY=${arg_OUTPUT_DIRECTORY})
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

    # Sanity check that we are not trying to have two different QML modules use the same output directory.
    get_property(dirs GLOBAL PROPERTY _qt_all_qml_output_dirs)
    if(dirs)
        list(FIND dirs "${arg_OUTPUT_DIRECTORY}" index)
        if(NOT index EQUAL -1)
            get_property(qml_targets GLOBAL PROPERTY _qt_all_qml_targets)
            list(GET qml_targets ${index} other_target)
            message(FATAL_ERROR
                "Output directory for target \"${target}\" is already used by "
                "another QML module (target \"${other_target}\"). "
                "Output directory is:\n  ${arg_OUTPUT_DIRECTORY}\n")
        endif()
    endif()
    set_property(GLOBAL APPEND PROPERTY _qt_all_qml_output_dirs ${arg_OUTPUT_DIRECTORY})
    set_property(GLOBAL APPEND PROPERTY _qt_all_qml_targets     ${target})

    if(NOT arg_CLASS_NAME AND TARGET "${arg_PLUGIN_TARGET}")
        get_target_property(class_name ${arg_PLUGIN_TARGET} QT_PLUGIN_CLASS_NAME)
        if(class_name)
            set(arg_CLASS_NAME)
        endif()
    endif()
    if(NOT arg_CLASS_NAME)
        qext_internal_compute_qml_plugin_class_name_from_uri("${arg_URI}" arg_CLASS_NAME)
    endif()

    if(TARGET ${target})
        if(arg_PLUGIN_TARGET STREQUAL target)
            # Insert the plugin's URI into its meta data to enable usage
            # of static plugins in QtDeclarative (like in mkspecs/features/qml_plugin.prf).
            set_property(TARGET ${target} APPEND PROPERTY AUTOMOC_MOC_OPTIONS "-Muri=${arg_URI}")
        endif()
    else()
        if(arg_PLUGIN_TARGET STREQUAL target)
            set(conditional_args ${no_gen_source})
            if(arg_NAMESPACE)
                list(APPEND conditional_args NAMESPACE ${arg_NAMESPACE})
            endif()
            qt6_add_qml_plugin(${target}
                ${lib_type}
                OUTPUT_DIRECTORY ${arg_OUTPUT_DIRECTORY}
                URI ${arg_URI}
                CLASS_NAME ${arg_CLASS_NAME}
                ${conditional_args})
        else()
            qt6_add_library(${target} ${lib_type})
        endif()
    endif()

    if(NOT target STREQUAL Qml)
        target_link_libraries(${target} PRIVATE ${QEXT_QT_EXPORT_NAMESPACE}::Qml)
    endif()

    if(NOT arg_TYPEINFO)
        set(arg_TYPEINFO ${target}.qmltypes)
    endif()

    if(NOT arg_NO_PLUGIN_OPTIONAL)
        set(arg_NO_PLUGIN_OPTIONAL ON)
    endif()

    foreach(import_set IN ITEMS IMPORTS OPTIONAL_IMPORTS DEFAULT_IMPORTS)
        foreach(import IN LISTS arg_${import_set})
            string(FIND ${import} "/" slash_position REVERSE)
            if (slash_position EQUAL -1)
                set_property(TARGET ${target} APPEND PROPERTY
                    QT_QML_MODULE_${import_set} "${import}")
            else()
                string(SUBSTRING ${import} 0 ${slash_position} import_module)
                math(EXPR slash_position "${slash_position} + 1")
                string(SUBSTRING ${import} ${slash_position} -1 import_version)
                if (import_version MATCHES "^([0-9]+(\\.[0-9]+)?|auto)$")
                    set_property(TARGET ${target} APPEND PROPERTY
                        QT_QML_MODULE_${import_set} "${import_module} ${import_version}")
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
            set_property(TARGET ${target} APPEND PROPERTY QT_QML_MODULE_DEPENDENCIES "${dependency}")
        else()
            string(SUBSTRING ${dependency} 0 ${slash_position} dep_module)
            math(EXPR slash_position "${slash_position} + 1")
            string(SUBSTRING ${dependency} ${slash_position} -1 dep_version)
            if (dep_version MATCHES "^([0-9]+(\\.[0-9]+)?|auto)$")
                set_property(TARGET ${target} APPEND PROPERTY QT_QML_MODULE_DEPENDENCIES "${dep_module} ${dep_version}")
            else()
                message(FATAL_ERROR
                    "Invalid module dependency version number. "
                    "Expected 'VersionMajor', 'VersionMajor.VersionMinor' or 'auto'.")
            endif()
        endif()
    endforeach()

    _qt_internal_canonicalize_resource_path("${arg_RESOURCE_PREFIX}" arg_RESOURCE_PREFIX)
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
        _qt_qml_module_follow_foreign_versioning "${arg_FOLLOW_FOREIGN_VERSIONING}"
        QEXT_QML_MODULE_URI "${arg_URI}"
        QEXT_QML_MODULE_TARGET_PATH "${arg_TARGET_PATH}"
        QEXT_QML_MODULE_VERSION "${arg_VERSION}"
        QEXT_QML_MODULE_CLASS_NAME "${arg_CLASS_NAME}"

        QEXT_QML_MODULE_PLUGIN_TARGET "${arg_PLUGIN_TARGET}"
        QEXT_QML_MODULE_INSTALLED_PLUGIN_TARGET "${arg_INSTALLED_PLUGIN_TARGET}"

        # Also Save the PLUGIN_TARGET values in a separate property to circumvent
        # https://gitlab.kitware.com/cmake/cmake/-/issues/21484 when exporting the properties
        _qt_qml_module_plugin_target "${arg_PLUGIN_TARGET}"
        _qt_qml_module_installed_plugin_target "${arg_INSTALLED_PLUGIN_TARGET}"

        QEXT_QML_MODULE_DESIGNER_SUPPORTED "${arg_DESIGNER_SUPPORTED}"
        QEXT_QML_MODULE_IS_STATIC "${arg___QT_INTERNAL_STATIC_MODULE}"
        QEXT_QML_MODULE_IS_SYSTEM "${arg___QT_INTERNAL_SYSTEM_MODULE}"
        QEXT_QML_MODULE_OUTPUT_DIRECTORY "${arg_OUTPUT_DIRECTORY}"
        QEXT_QML_MODULE_RESOURCE_PREFIX "${qext_qml_module_resource_prefix}"
        QEXT_QML_MODULE_PAST_MAJOR_VERSIONS "${arg_PAST_MAJOR_VERSIONS}"
        QEXT_QML_MODULE_TYPEINFO "${arg_TYPEINFO}"

        # TODO: Check how this is used by qt6_android_generate_deployment_settings()
        QEXT_QML_IMPORT_PATH "${arg_IMPORT_PATH}")
    # message(arg_TYPEINFO=${arg_TYPEINFO})
    target_compile_definitions(${target} PRIVATE
        QEXT_QML_MODULE_URI="${arg_URI}"
        QEXT_QML_MODULE_VERSION="${arg_VERSION}")

    # Executables don't have a plugin target, so no need to export the properties.
    if(NOT backing_target_type STREQUAL "EXECUTABLE" AND NOT is_android_executable)
        set_property(TARGET ${target} APPEND PROPERTY
            EXPORT_PROPERTIES _qt_qml_module_plugin_target _qt_qml_module_installed_plugin_target)
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
        if(arg___QT_INTERNAL_INSTALL_METATYPES_JSON)
            list(APPEND type_registration_extra_args __QT_INTERNAL_INSTALL_METATYPES_JSON)
        endif()
        if(arg_NAMESPACE)
            list(APPEND type_registration_extra_args NAMESPACE ${arg_NAMESPACE})
        endif()
        #TODO: manunal register qml types
        qext_internal_qml_type_registration(${target} ${type_registration_extra_args})
    endif()

    set(output_targets)
    if(NOT arg_NO_GENERATE_QMLDIR)
        qext_internal_target_generate_qmldir(${target})

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
            PROPERTIES QT_RESOURCE_ALIAS "qmldir")

        foreach(prefix IN LISTS prefixes)
            set(resource_targets)
            qt6_add_resources(${target} ${qmldir_resource_name}
                FILES ${arg_OUTPUT_DIRECTORY}/qmldir
                PREFIX "${prefix}"
                OUTPUT_TARGETS resource_targets)
            list(APPEND output_targets ${resource_targets})
            # If we are adding the same file twice, we need a different resource
            # name for the second one. It has the same QT_RESOURCE_ALIAS but a
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
        qt6_add_qml_plugin(${arg_PLUGIN_TARGET}
            ${plugin_args}
            OUTPUT_DIRECTORY ${arg_OUTPUT_DIRECTORY}
            BACKING_TARGET ${target}
            CLASS_NAME ${arg_CLASS_NAME})
    endif()

    if(TARGET "${arg_PLUGIN_TARGET}" AND NOT arg_PLUGIN_TARGET STREQUAL target)
        # message(------target=${target})
        target_link_libraries(${arg_PLUGIN_TARGET} PRIVATE ${target})
    endif()

    # message(arg_SOURCES=${arg_SOURCES})
    target_sources(${target} PRIVATE ${arg_SOURCES})

    # QML tooling might need to map build dir paths to source dir paths. Create
    # a mapping file before qt6_target_qml_sources() to be able to use it
    if(arg_ENABLE_TYPE_COMPILER)
        # But: for now, only enable this when dealing with qmltc
        _qt_internal_qml_map_build_files(${target} "${arg_QML_FILES}" dir_map_qrc)
        set_property(TARGET ${target} APPEND PROPERTY _qt_generated_qrc_files "${dir_map_qrc}")
    endif()

    set(cache_target)
    qt6_target_qml_sources(${target}
        __QT_INTERNAL_FORCE_DEFER_QMLDIR
        QML_FILES ${arg_QML_FILES}
        RESOURCES ${arg_RESOURCES}
        OUTPUT_TARGETS cache_target
        PREFIX "${qext_qml_module_resource_prefix}")
    list(APPEND output_targets ${cache_target})

    # Build an init object library for static plugins and propagate it along with the plugin
    # target.
    # TODO: Figure out if we can move this code block into qt_add_qml_plugin. Need to consider
    #       various corner cases.
    #       QTBUG-96937
    #TODO:init
    # if(TARGET "${arg_PLUGIN_TARGET}")
    #     get_target_property(plugin_lib_type ${arg_PLUGIN_TARGET} TYPE)
    #     if(plugin_lib_type STREQUAL "STATIC_LIBRARY")
    #         __qext_internal_add_static_plugin_init_object_library("${arg_PLUGIN_TARGET}" plugin_init_target)
    #         list(APPEND output_targets ${plugin_init_target})
    #         __qt_internal_propagate_object_library("${arg_PLUGIN_TARGET}" "${plugin_init_target}")
    #     endif()
    # endif()
    # return() #TODO

    if(NOT arg_NO_GENERATE_QMLDIR)
        if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.19.0")
            # Defer the write to allow more qml files to be added later by calls to
            # qt6_target_qml_sources(). We wrap the deferred call with EVAL CODE
            # so that ${target} is evaluated now rather than the end of the scope.
            # We also delay target finalization until after our deferred write
            # because the qmldir file must be written before any finalizer
            # might call qt_import_qml_plugins().
            cmake_language(EVAL CODE
                "cmake_language(DEFER ID_VAR write_id CALL _qt_internal_write_deferred_qmldir_file ${target})")
            _qt_internal_delay_finalization_until_after(${write_id})
        else()
            # Can't defer the write, have to do it now
            _qt_internal_write_deferred_qmldir_file(${target})
        endif()
    endif()

    if (arg_ENABLE_TYPE_COMPILER)
        _qt_internal_target_enable_qmltc(${target}
            QML_FILES ${arg_QML_FILES}
            IMPORT_PATHS ${arg_IMPORT_PATH}
            NAMESPACE ${arg_TYPE_COMPILER_NAMESPACE})
    endif()

    if(arg_OUTPUT_TARGETS)
        set(${arg_OUTPUT_TARGETS} ${output_targets} PARENT_SCOPE)
    endif()

endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
# If a task needs to run before any targets are finalized in the current directory
# scope, call this function and pass the ID of that task as the argument.
function(_qt_internal_delay_finalization_until_after defer_id)
    set_property(DIRECTORY APPEND PROPERTY qt_internal_finalizers_wait_for_ids "${defer_id}")
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(_qt_internal_write_deferred_qmldir_file target)
    get_target_property(__qt_qmldir_content ${target} _qt_internal_qmldir_content)
    get_target_property(out_dir ${target} QT_QML_MODULE_OUTPUT_DIRECTORY)
    set(qmldir_file "${out_dir}/qmldir")
    configure_file(${__qt_qml_macros_module_base_dir}/QExtQmldirTemplate.cmake.in ${qmldir_file} @ONLY)
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qt6_add_qml_plugin target)
    # return() # TODO
    set(args_option
        STATIC
        SHARED
        NO_GENERATE_PLUGIN_SOURCE)

    set(args_single
        OUTPUT_DIRECTORY
        URI
        BACKING_TARGET
        CLASS_NAME
        NAMESPACE
        # The following is only needed on Android, and even then, only if the
        # default conversion from the URI is not applicable. It is an internal
        # option, it may be removed.
        TARGET_PATH)

    set(args_multi "")

    cmake_parse_arguments(PARSE_ARGV 1 arg
        "${args_option}"
        "${args_single}"
        "${args_multi}")

    if(arg_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unexpected arguments: ${arg_UNPARSED_ARGUMENTS}")
    endif()

    if(NOT arg_URI)
        if(NOT arg_BACKING_TARGET)
            message(FATAL_ERROR "No URI or BACKING_TARGET provided")
        endif()
        if(NOT TARGET ${arg_BACKING_TARGET})
            if(arg_BACKING_TARGET STREQUAL target)
                message(FATAL_ERROR
                    "Plugin ${target} is its own backing target, URI must be provided")
            else()
                message(FATAL_ERROR
                    "No URI provided and unable to obtain it from the BACKING_TARGET "
                    "(${arg_BACKING_TARGET}) because no such target exists")
            endif()
        endif()
        get_target_property(arg_URI ${arg_BACKING_TARGET} QEXT_QML_MODULE_URI)
        if(NOT arg_URI)
            message(FATAL_ERROR
                "No URI provided and the BACKING_TARGET (${arg_BACKING_TARGET}) "
                "does not have one set either")
        endif()
    endif()

    # TODO: Probably should remove TARGET_PATH as a supported keyword now
    if(NOT arg_TARGET_PATH AND TARGET "${arg_BACKING_TARGET}")
        get_target_property(arg_TARGET_PATH ${arg_BACKING_TARGET} QEXT_QML_MODULE_TARGET_PATH)
    endif()
    if(NOT arg_TARGET_PATH)
        string(REPLACE "." "/" arg_TARGET_PATH "${arg_URI}")
    endif()

    qext_internal_get_escaped_uri("${arg_URI}" escaped_uri)

    if(NOT arg_CLASS_NAME)
        if(NOT "${arg_BACKING_TARGET}" STREQUAL "")
            get_target_property(arg_CLASS_NAME ${target} QEXT_QML_MODULE_CLASS_NAME)
        endif()
        if(NOT arg_CLASS_NAME)
            qext_internal_compute_qml_plugin_class_name_from_uri("${arg_URI}" arg_CLASS_NAME)
        endif()
    endif()

    if(TARGET ${target})
        # Plugin target already exists. Perform a few sanity checks, but we
        # otherwise trust that the target is appropriate for use as a plugin.
        get_target_property(target_type ${target} TYPE)
        if(target_type STREQUAL "EXECUTABLE")
            message(FATAL_ERROR "Plugins cannot be executables (target: ${target})")
        endif()
        foreach(arg IN ITEMS STATIC SHARED)
            if(arg_${arg})
                message(FATAL_ERROR
                    "Cannot specify ${arg} keyword, target ${target} already exists")
            endif()
        endforeach()

        get_target_property(existing_class_name ${target} QT_PLUGIN_CLASS_NAME)
        if(existing_class_name)
            if(NOT existing_class_name STREQUAL arg_CLASS_NAME)
                message(FATAL_ERROR
                    "An existing plugin target was given, but it has a different class name "
                    "(${existing_class_name}) to that being used here (${arg_CLASS_NAME})")
            endif()
        elseif(arg_CLASS_NAME)
            set_property(TARGET ${target} PROPERTY QT_PLUGIN_CLASS_NAME "${arg_CLASS_NAME}")
        else()
            message(FATAL_ERROR
                "An existing '${target}' plugin target was given, but it has no class name set "
                "and no new class name was provided.")
        endif()
    else()
        if(arg_STATIC AND arg_SHARED)
            message(FATAL_ERROR
                "Cannot specify both STATIC and SHARED for target ${target}")
        endif()
        set(lib_type "")
        if(arg_STATIC)
            set(lib_type STATIC)
        elseif(arg_SHARED)
            set(lib_type SHARED)
        endif()

        if(TARGET "${arg_BACKING_TARGET}")
            # Ensure that the plugin type we create will be compatible with the
            # type of backing target we were given
            get_target_property(backing_type ${arg_BACKING_TARGET} TYPE)
            if(backing_type STREQUAL "STATIC_LIBRARY")
                if(lib_type STREQUAL "")
                    set(lib_type STATIC)
                elseif(lib_type STREQUAL "SHARED")
                    message(FATAL_ERROR
                        "Mixing a static backing library with a non-static plugin "
                        "is not supported")
                endif()
            elseif(backing_type STREQUAL "SHARED_LIBRARY")
                if(lib_type STREQUAL "")
                    set(lib_type SHARED)
                elseif(lib_type STREQUAL "STATIC")
                    message(FATAL_ERROR
                        "Mixing a non-static backing library with a static plugin "
                        "is not supported")
                endif()
            elseif(backing_type STREQUAL "EXECUTABLE")
                message(FATAL_ERROR
                    "A separate plugin should not be needed when the backing target "
                    "is an executable. Pre-create the plugin target before calling "
                    "this command if you really must have a separate plugin.")
            else()
                # Object libraries, utility/custom targets
                message(FATAL_ERROR "Unsupported backing target type: ${backing_type}")
            endif()
        endif()

        # qext_add_plugin(${target} ${lib_type}
        #     PLUGIN_TYPE qml_plugin
        #     CLASS_NAME ${arg_CLASS_NAME})
        qt6_add_plugin(${target} ${lib_type}
            PLUGIN_TYPE qml_plugin
            CLASS_NAME ${arg_CLASS_NAME})
    endif()

    # Ignore any CMAKE_INSTALL_RPATH and set a better default RPATH on platforms
    # that support it, if allowed. Projects will often set CMAKE_INSTALL_RPATH
    # for executables or backing libraries, but forget about plugins. Because
    # the path for QML plugins depends on their URI, it is unlikely that
    # CMAKE_INSTALL_RPATH would ever be intended for use with QML plugins.
    if(NOT WIN32 AND NOT QT_NO_QML_PLUGIN_RPATH)
        # Construct a relative path from a default install location (assumed to
        # be qml/target-path) to ${CMAKE_INSTALL_LIBDIR}. This would be
        # applicable for Apple too (although unusual) if this is a bare install
        # (i.e. not part of an app bundle).
        string(REPLACE "/" ";" path "qml/${arg_TARGET_PATH}")
        list(LENGTH path path_count)
        string(REPEAT "../" ${path_count} rel_path)
        string(APPEND rel_path "${CMAKE_INSTALL_LIBDIR}")
#        message(rel_path=${rel_path})
        if(APPLE)
            set(install_rpath
                # If embedded in an app bundle, search in a bundle-local path
                # first. This path should always be the same for every app
                # bundle because plugin binaries should live in the PlugIns
                # directory, not a subdirectory of it or anywhere else.
                # Similarly, frameworks and bare shared libraries should always
                # be in the bundle's Frameworks directory.
                "@loader_path/../Frameworks"

                # This will be needed if the plugin is not installed as part of
                # an app bundle, such as when used by a command-line tool.
                "@loader_path/${rel_path}")
        else()
            set(install_rpath "$ORIGIN/${rel_path}")
        endif()
        set_target_properties(${target} PROPERTIES
            BUILD_WITH_INSTALL_RPATH ON
            INSTALL_RPATH "${install_rpath}")
    endif()

    get_target_property(moc_opts ${target} AUTOMOC_MOC_OPTIONS)
    set(already_set FALSE)
    if(moc_opts)
        foreach(opt IN LISTS moc_opts)
            if("${opt}" MATCHES "^-Muri=")
                set(already_set TRUE)
                break()
            endif()
        endforeach()
    endif()
    if(NOT already_set)
        # Insert the plugin's URI into its meta data to enable usage
        # of static plugins in QtDeclarative (like in mkspecs/features/qml_plugin.prf).
        set_property(TARGET ${target} APPEND PROPERTY
            AUTOMOC_MOC_OPTIONS "-Muri=${arg_URI}")
    endif()

    if(ANDROID)
        qext_internal_get_qml_plugin_output_name(plugin_output_name ${target}
            BACKING_TARGET "${arg_BACKING_TARGET}"
            TARGET_PATH "${arg_TARGET_PATH}"
            URI "${arg_URI}")
        set_target_properties(${target}
            PROPERTIES
            LIBRARY_OUTPUT_NAME "${plugin_output_name}")
        qt6_android_apply_arch_suffix(${target})
    endif()

    if(NOT arg_OUTPUT_DIRECTORY AND arg_BACKING_TARGET AND TARGET ${arg_BACKING_TARGET})
        get_target_property(arg_OUTPUT_DIRECTORY ${arg_BACKING_TARGET} QEXT_QML_MODULE_OUTPUT_DIRECTORY)
    endif()
    if(arg_OUTPUT_DIRECTORY)
        # Plugin target must be in the output directory. The backing target,
        # if it is different to the plugin target, can be anywhere.
        set_target_properties(${target} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${arg_OUTPUT_DIRECTORY}
            LIBRARY_OUTPUT_DIRECTORY ${arg_OUTPUT_DIRECTORY}
            ARCHIVE_OUTPUT_DIRECTORY ${arg_OUTPUT_DIRECTORY})
    endif()

    if(NOT arg_NO_GENERATE_PLUGIN_SOURCE)
        set(generated_cpp_file_name_base "${target}_${arg_CLASS_NAME}")
        set(register_types_function_name "qml_register_types_${escaped_uri}")

        # These are all substituted in the template file used further below
        set(qt_qml_plugin_class_name "${arg_CLASS_NAME}")
        set(qt_qml_plugin_moc_include_name "${generated_cpp_file_name_base}.moc")
        set(qt_qml_plugin_intro "")
        set(qt_qml_plugin_outro "")
        if (arg_NAMESPACE)
            string(APPEND qt_qml_plugin_intro "namespace ${arg_NAMESPACE} {\n\n")
            string(APPEND qt_qml_plugin_outro "} // namespace ${arg_NAMESPACE}")
        endif()

        string(APPEND qt_qml_plugin_intro "extern void ${register_types_function_name}();\nQ_GHS_KEEP_REFERENCE(${register_types_function_name})")

        # Indenting here is deliberately different so as to make the generated
        # file have sensible indenting
        set(qt_qml_plugin_constructor_content
            "volatile auto registration = &${register_types_function_name};
            Q_UNUSED(registration)")

        set(generated_cpp_file
            "${CMAKE_CURRENT_BINARY_DIR}/${generated_cpp_file_name_base}.cpp")
        # TODO:manual plugin cpp
        #    message(__qt_qml_macros_module_base_dir=${__qt_qml_macros_module_base_dir})
        # configure_file(
        #     #            "${__qt_qml_macros_module_base_dir}/Qt6QmlPluginTemplate.cpp.in"
        #     "${PROJECT_SOURCE_DIR}/cmake/QExtQmlPluginTemplate.cpp.in"
        #     "${generated_cpp_file}"
        #     @ONLY)
        # target_sources(${target} PRIVATE "${generated_cpp_file}")

        # The generated cpp file expects to include its moc-ed output file.
        set_target_properties(${target} PROPERTIES AUTOMOC TRUE)
    endif()

    target_link_libraries(${target} PRIVATE ${QEXT_QT_EXPORT_NAMESPACE}::Qml)

    # Link plugin against its backing lib if it has one.
    if(NOT arg_BACKING_TARGET STREQUAL "" AND NOT arg_BACKING_TARGET STREQUAL target)
        target_link_libraries(${target} PRIVATE ${arg_BACKING_TARGET})
    endif()

    if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.19.0")
        # Defer the collection of plugin dependencies until after any extra target_link_libraries
        # calls that a user project might do.
        # We wrap the deferred call with EVAL CODE
        # so that ${target} is evaluated now rather than the end of the scope.
        cmake_language(EVAL CODE
            "cmake_language(DEFER CALL _qt_internal_add_static_qml_plugin_dependencies \"${target}\" \"${arg_BACKING_TARGET}\")")
    else()
        # Can't defer, have to do it now.
        _qt_internal_add_static_qml_plugin_dependencies("${target}" "${arg_BACKING_TARGET}")
    endif()
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
# Make the prefix conform to the following:
#   - Starts with a "/"
#   - Does not end with a "/" unless the prefix is exactly "/"
function(_qt_internal_canonicalize_resource_path path out_var)
    if(NOT path)
        set(path "/")
    endif()
    if(NOT path MATCHES "^/")
        string(PREPEND path "/")
    endif()
    if(path MATCHES [[(.+)/$]])
        set(path "${CMAKE_MATCH_1}")
    endif()
    set(${out_var} "${path}" PARENT_SCOPE)
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
# target: Expected to be the backing target for a qml module. Certain target
#   properties normally set by qt6_add_qml_module() will be retrieved from this
#   target. (REQUIRED)
#
# MANUAL_MOC_JSON_FILES: Specifies a list of json files, generated by a manual
#   moc call, to extract metatypes. (OPTIONAL)
#
# NAMESPACE: Specifies a namespace the type registration function shall be
#   generated into. (OPTIONAL)
#
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_qml_type_registration target)
    set(args_option __QT_INTERNAL_INSTALL_METATYPES_JSON)
    set(args_single NAMESPACE)
    set(args_multi  MANUAL_MOC_JSON_FILES)

    cmake_parse_arguments(PARSE_ARGV 1 arg
        "${args_option}" "${args_single}" "${args_multi}")
    if(arg_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unknown/unexpected arguments: ${arg_UNPARSED_ARGUMENTS}")
    endif()

    get_target_property(import_name ${target} QEXT_QML_MODULE_URI)
    if (NOT import_name)
        message(FATAL_ERROR "Target ${target} is not a QML module")
    endif()
    # message(import_name=${import_name})
    get_target_property(qmltypes_output_name ${target} QEXT_QML_MODULE_TYPEINFO)
    if (NOT qmltypes_output_name)
        get_target_property(compile_definitions_list ${target} COMPILE_DEFINITIONS)
        list(FIND compile_definitions_list QT_PLUGIN is_a_plugin)
        if (is_a_plugin GREATER_EQUAL 0)
            set(qmltypes_output_name "plugins.qmltypes")
        else()
            set(qmltypes_output_name ${target}.qmltypes)
        endif()
    endif()

    set(meta_types_json_args "")
    if(arg_MANUAL_MOC_JSON_FILES)
        list(APPEND meta_types_json_args "MANUAL_MOC_JSON_FILES" ${arg_MANUAL_MOC_JSON_FILES})
    endif()

    # Don't install the metatypes json files by default for user project created qml modules.
    # Only install them for Qt provided qml modules.
    if(NOT arg___QT_INTERNAL_INSTALL_METATYPES_JSON)
        list(APPEND meta_types_json_args __QT_INTERNAL_NO_INSTALL)
    endif()
    # qt6_extract_metatypes(${target} ${meta_types_json_args}) #TODO:del?

    get_target_property(import_url ${target} QEXT_QML_MODULE_URI)
    get_target_property(import_version ${target} QEXT_QML_MODULE_VERSION)
    get_target_property(output_dir ${target} QEXT_QML_MODULE_OUTPUT_DIRECTORY)
    get_target_property(target_source_dir ${target} SOURCE_DIR)
    get_target_property(target_binary_dir ${target} BINARY_DIR)
    get_target_property(target_metatypes_file ${target} INTERFACE_QT_META_TYPES_BUILD_FILE)
    if (NOT target_metatypes_file)
        # message(FATAL_ERROR "Target ${target} does not have a meta types file")
    endif()

    # Extract major and minor version (could also have patch part, but we don't
    # need that here)
    if (import_version MATCHES "^([0-9]+)\\.([0-9]+)")
        set(major_version ${CMAKE_MATCH_1})
        set(minor_version ${CMAKE_MATCH_2})
    else()
        message(FATAL_ERROR
            "Invalid module version number '${import_version}'. "
            "Expected VersionMajor.VersionMinor.")
    endif()

    # check if plugins.qmltypes is already defined
    get_target_property(target_plugin_qmltypes ${target} QEXT_QML_MODULE_PLUGIN_TYPES_FILE)
    if (target_plugin_qmltypes)
        message(FATAL_ERROR "Target ${target} already has a qmltypes file set.")
    endif()

    set(cmd_args)
    set(plugin_types_file "${output_dir}/${qmltypes_output_name}")
    set(generated_marker_file "${target_binary_dir}/.generated/${qmltypes_output_name}")
    get_filename_component(generated_marker_dir "${generated_marker_file}" DIRECTORY)
    set_target_properties(${target} PROPERTIES QEXT_QML_MODULE_PLUGIN_TYPES_FILE ${plugin_types_file})
#     message(output_dir=${output_dir})
#     message(plugin_types_file=${plugin_types_file})
#     message(arg_PLUGIN_TARGET=${arg_PLUGIN_TARGET})
#     message(QEXT_QML_OUTPUT_DIRECTORY=${QEXT_QML_OUTPUT_DIRECTORY})
    if(TARGET ${arg_PLUGIN_TARGET} AND EXISTS "${QEXT_QT_QMLPLUGINDUMP_EXECUTABLE}")
        add_custom_command(
            TARGET ${arg_PLUGIN_TARGET}
            COMMAND
            ${QEXT_QT_QMLPLUGINDUMP_EXECUTABLE} -v -relocatable ${import_name} ${import_version} ${QEXT_QML_OUTPUT_DIRECTORY}
            -output ${plugin_types_file}
            COMMENT "Running qmlplugindump for ${import_name} qml module"
            POST_BUILD)
    endif()
    return()

    if (arg_NAMESPACE)
        list(APPEND cmd_args --namespace=${arg_NAMESPACE})
    endif()

    list(APPEND cmd_args
        --generate-qmltypes=${plugin_types_file}
        --import-name=${import_name}
        --major-version=${major_version}
        --minor-version=${minor_version})


    # Add --follow-foreign-versioning if requested
    get_target_property(follow_foreign_versioning ${target} _qt_qml_module_follow_foreign_versioning)

    if (follow_foreign_versioning)
        list(APPEND cmd_args --follow-foreign-versioning)
    endif()

    # Add past minor versions
    get_target_property(past_major_versions ${target} QEXT_QML_MODULE_PAST_MAJOR_VERSIONS)

    if (past_major_versions OR past_major_versions STREQUAL "0")
        foreach (past_major_version ${past_major_versions})
            list(APPEND cmd_args --past-major-version ${past_major_version})
        endforeach()
    endif()

    # Run a script to recursively evaluate all the metatypes.json files in order
    # to collect all foreign types.
    string(TOLOWER "${target}_qmltyperegistrations.cpp" type_registration_cpp_file_name)
    set(foreign_types_file "${target_binary_dir}/qmltypes/${target}_foreign_types.txt")
    set(type_registration_cpp_file "${target_binary_dir}/${type_registration_cpp_file_name}")

    # Enable evaluation of metatypes.json source interfaces
    set_target_properties(${target} PROPERTIES QT_CONSUMES_METATYPES TRUE)
    set(genex_list "$<REMOVE_DUPLICATES:$<FILTER:$<TARGET_PROPERTY:${target},SOURCES>,INCLUDE,metatypes.json$>>")
    set(genex_main "$<JOIN:${genex_list},$<COMMA>>")
    file(GENERATE OUTPUT "${foreign_types_file}" CONTENT "$<IF:$<BOOL:${genex_list}>,--foreign-types=${genex_main},\n>")

    list(APPEND cmd_args "@${foreign_types_file}")

    if (TARGET ${target}Private)
        list(APPEND cmd_args --private-includes)
    else()
        string(REGEX MATCH "Private$" privateSuffix ${target})
        if (privateSuffix)
            list(APPEND cmd_args --private-includes)
        endif()
    endif()

    get_target_property(target_metatypes_json_file ${target} INTERFACE_QT_META_TYPES_BUILD_FILE)
    if (NOT target_metatypes_json_file)
        # message(FATAL_ERROR "Need target metatypes.json file")
    endif()

    cmake_policy(PUSH)

    _qt_internal_check_depfile_support(has_depfile_support)
    set(registration_cpp_file_dep_args)
    if(has_depfile_support)
        if(POLICY CMP0116)
            # Without explicitly setting this policy to NEW, we get a warning
            # even though we ensure there's actually no problem here.
            # See https://gitlab.kitware.com/cmake/cmake/-/issues/21959
            cmake_policy(SET CMP0116 NEW)
            set(relative_to_dir ${CMAKE_CURRENT_BINARY_DIR})
        else()
            set(relative_to_dir ${CMAKE_BINARY_DIR})
        endif()
        set(dependency_file_cpp "${target_binary_dir}/qmltypes/${type_registration_cpp_file_name}.d")
        set(registration_cpp_file_dep_args DEPFILE ${dependency_file_cpp})
        file(RELATIVE_PATH cpp_file_name "${relative_to_dir}" "${type_registration_cpp_file}")
        file(GENERATE OUTPUT "${dependency_file_cpp}"
            CONTENT "${cpp_file_name}: $<IF:$<BOOL:${genex_list}>,\\\n$<JOIN:${genex_list}, \\\n>, \\\n>")
    endif()


    _qt_internal_get_tool_wrapper_script_path(tool_wrapper)
    message(tool_wrapper=${tool_wrapper})
    # add_custom_command(
    #     OUTPUT
    #     ${type_registration_cpp_file}
    #     ${plugin_types_file}
    #     DEPENDS
    #     ${foreign_types_file}
    #     ${target_metatypes_json_file}
    #     ${QEXT_QT_EXPORT_NAMESPACE}::qmltyperegistrar
    #     "$<$<BOOL:${genex_list}>:${genex_list}>"
    #     COMMAND
    #     ${tool_wrapper}
    #     $<TARGET_FILE:${QEXT_QT_EXPORT_NAMESPACE}::qmltyperegistrar>
    #     ${cmd_args}
    #     -o ${type_registration_cpp_file}
    #     ${target_metatypes_json_file}
    #     COMMAND
    #     ${CMAKE_COMMAND} -E make_directory "${generated_marker_dir}"
    #     COMMAND
    #     ${CMAKE_COMMAND} -E touch "${generated_marker_file}"
    #     ${registration_cpp_file_dep_args}
    #     COMMENT "Automatic QML type registration for target ${target}"
    #     VERBATIM
    # )

    cmake_policy(POP)
    # message(plugin_types_file=${plugin_types_file})
    # The ${target}_qmllint targets need to depend on the generation of all
    # *.qmltypes files in the build. We have no way of reliably working out
    # which QML modules a given target depends on at configure time, so we
    # have to be conservative and make ${target}_qmllint targets depend on all
    # *.qmltypes files. We need to provide a target for those dependencies
    # here. Note that we can't use ${target} itself for those dependencies
    # because the user might want to run qmllint without having to build the
    # QML module.
    add_custom_target(${target}_qmltyperegistration
        DEPENDS
        ${type_registration_cpp_file}
        ${plugin_types_file})
    if(NOT TARGET all_qmltyperegistrations)
        add_custom_target(all_qmltyperegistrations)
    endif()
    add_dependencies(all_qmltyperegistrations ${target}_qmltyperegistration)

    # Both ${target} (via target_sources) and ${target}_qmltyperegistration (via add_custom_target
    # DEPENDS option) depend on ${type_registration_cpp_file}.
    # The new Xcode build system requires a common target to drive the generation of files,
    # otherwise project configuration fails.
    # Make ${target} the common target, by adding it as a dependency for
    # ${target}_qmltyperegistration.
    # The consequence is that the ${target}_qmllint target will now first build ${target} when using
    # the Xcode generator (mostly only relevant for projects using Qt for iOS).
    # See QTBUG-95763.
    if(CMAKE_GENERATOR STREQUAL "Xcode")
        add_dependencies(${target}_qmltyperegistration ${target})
    endif()

    target_sources(${target} PRIVATE ${type_registration_cpp_file})

    # FIXME: The generated .cpp file has usually lost the path information for
    #        the headers it #include's. Since these generated .cpp files are in
    #        the build directory away from those headers, the header search path
    #        has to be augmented to ensure they can be found. We don't know what
    #        paths are needed, but add the source directory to at least handle
    #        the common case of headers in the same directory as the target.
    #        See QTBUG-93443.
    target_include_directories(${target} PRIVATE ${target_source_dir})

    # Circumvent "too many sections" error when doing a 32 bit debug build on Windows with
    # MinGW.
    set(additional_source_files_properties "")
    if(MINGW)
        set(additional_source_files_properties "COMPILE_OPTIONS" "-Wa,-mbig-obj")
    elseif(MSVC)
        set(additional_source_files_properties "COMPILE_OPTIONS" "/bigobj")
    endif()
    set_source_files_properties(${type_registration_cpp_file} PROPERTIES
        SKIP_AUTOGEN ON
        ${additional_source_files_properties})
    if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.18")
        set_source_files_properties(
            ${type_registration_cpp_file}
            TARGET_DIRECTORY ${target}
            PROPERTIES
            SKIP_AUTOGEN TRUE
            GENERATED TRUE
            ${additional_source_files_properties})
    endif()

    # target_include_directories(${target} PRIVATE
    #     $<TARGET_PROPERTY:${QEXT_QT_EXPORT_NAMESPACE}::QmlPrivate,INTERFACE_INCLUDE_DIRECTORIES>
    # )
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
# TODO:del?
#-----------------------------------------------------------------------------------------------------------------------
function(qt6_extract_metatypes target)
    return() #TODO
    get_target_property(existing_meta_types_file ${target} INTERFACE_QT_META_TYPES_BUILD_FILE)
    if (existing_meta_types_file)
        return()
    endif()

    set(args_option
        # TODO: Remove this once all leaf module usages of it are removed. It's now a no-op.
        # It's original purpose was to skip installation of the metatypes file.
        __QT_INTERNAL_NO_INSTALL

        # TODO: Move this into a separate internal function, so it doesn't pollute the public one.
        # When given, metatypes files will be installed into the default Qt
        # metatypes folder. Only to be used by the Qt build.
        __QT_INTERNAL_INSTALL)
    set(args_single
        # TODO: Move this into a separate internal function, so it doesn't pollute the public one.
        # Location where to install the metatypes file. Only used if
        # __QT_INTERNAL_INSTALL is given. It defaults to the
        # ${QEXT_INSTALL_PREFIX}/${INSTALL_LIBDIR}/metatypes directory.
        # Executable metatypes files are never installed.
        __QT_INTERNAL_INSTALL_DIR

        OUTPUT_FILES)
    set(args_multi
        MANUAL_MOC_JSON_FILES)

    cmake_parse_arguments(arg
        "${args_option}"
        "${args_single}"
        "${args_multi}" ${ARGN})

    get_target_property(target_type ${target} TYPE)
    if (target_type STREQUAL "INTERFACE_LIBRARY")
        message(FATAL_ERROR "Meta types generation does not work on interface libraries")
        return()
    endif()

    if (CMAKE_VERSION VERSION_LESS "3.16.0")
        message(FATAL_ERROR "Meta types generation requires CMake >= 3.16")
        return()
    endif()

    get_target_property(target_binary_dir ${target} BINARY_DIR)
    set(type_list_file "${target_binary_dir}/meta_types/${target}_json_file_list.txt")
    set(type_list_file_manual "${target_binary_dir}/meta_types/${target}_json_file_list_manual.txt")

    get_target_property(uses_automoc ${target} AUTOMOC)
    set(automoc_args)
    set(automoc_dependencies)
    # Handle automoc generated data
    if (uses_automoc)
        message(uses_automoc-target=${target})
        # Tell automoc to output json files)
        set_property(TARGET "${target}" APPEND PROPERTY AUTOMOC_MOC_OPTIONS "--output-json")

        get_property(is_multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
        if(NOT is_multi_config)
            set(cmake_autogen_cache_file
                "${target_binary_dir}/CMakeFiles/${target}_autogen.dir/ParseCache.txt")
            set(multi_config_args
                --cmake-autogen-include-dir-path "${target_binary_dir}/${target}_autogen/include")
        else()
            set(cmake_autogen_cache_file
                "${target_binary_dir}/CMakeFiles/${target}_autogen.dir/ParseCache_$<CONFIG>.txt")
            set(multi_config_args
                --cmake-autogen-include-dir-path "${target_binary_dir}/${target}_autogen/include_$<CONFIG>"
                "--cmake-multi-config")
        endif()

        set(cmake_autogen_info_file
            "${target_binary_dir}/CMakeFiles/${target}_autogen.dir/AutogenInfo.json")

        set (use_dep_files FALSE)
        if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.17") # Requires automoc changes present only in 3.17
            if(CMAKE_GENERATOR STREQUAL "Ninja" OR CMAKE_GENERATOR STREQUAL "Ninja Multi-Config")
                set(use_dep_files TRUE)
            endif()
        endif()

        set(cmake_automoc_parser_timestamp "${type_list_file}.timestamp")

        if (NOT use_dep_files)
            # When a project is configured with a Visual Studio generator, CMake's
            # cmQtAutoGenInitializer::InitAutogenTarget() can take one of two code paths on how to
            # handle AUTOMOC rules.
            # It either creates a ${target}_autogen custom target or uses PRE_BUILD build events.
            #
            # The latter in considered an optimization and is used by CMake when possible.
            # Unfortunately that breaks our add_dependency call because we expect on _autogen target
            # to always exist.
            #
            # Ensure the PRE_BUILD path is not taken by generating a dummy header file and adding it
            # as a source file to the target. This causes the file to be added to
            # cmQtAutoGenInitializer::AutogenTarget.DependFiles, which disables the PRE_BUILD path.
            if(CMAKE_GENERATOR MATCHES "Visual Studio")
                # The file name should be target specific, but still short, so we don't hit path
                # length issues.
                string(MAKE_C_IDENTIFIER "ddf_${target}" dummy_dependency_file)
                set(dummy_out_file "${CMAKE_CURRENT_BINARY_DIR}/${dummy_dependency_file}.h")

                # The content shouldn't be empty so we don't trigger AUTOMOC warnings about it.
                file(GENERATE OUTPUT "${dummy_out_file}" CONTENT "//")
                set_source_files_properties("${dummy_out_file}" PROPERTIES
                    GENERATED TRUE
                    SKIP_AUTOGEN OFF)
                target_sources("${target}" PRIVATE "${dummy_out_file}")
            endif()

            add_custom_target(${target}_automoc_json_extraction
                DEPENDS ${QEXT_QT_EXPORT_NAMESPACE}::cmake_automoc_parser
                BYPRODUCTS
                ${type_list_file}
                "${cmake_automoc_parser_timestamp}"
                COMMAND
                ${QEXT_QT_EXPORT_NAMESPACE}::cmake_automoc_parser
                --cmake-autogen-cache-file "${cmake_autogen_cache_file}"
                --cmake-autogen-info-file "${cmake_autogen_info_file}"
                --output-file-path "${type_list_file}"
                --timestamp-file-path "${cmake_automoc_parser_timestamp}"
                ${multi_config_args}
                COMMENT "Running AUTOMOC file extraction for target ${target}"
                COMMAND_EXPAND_LISTS)
            add_dependencies(${target}_automoc_json_extraction ${target}_autogen)
        else()
            set(cmake_autogen_timestamp_file
                "${target_binary_dir}/${target}_autogen/timestamp")

            add_custom_command(OUTPUT ${type_list_file}
                DEPENDS ${QEXT_QT_EXPORT_NAMESPACE}::cmake_automoc_parser
                ${cmake_autogen_timestamp_file}
                BYPRODUCTS "${cmake_automoc_parser_timestamp}"
                COMMAND
                ${QEXT_QT_EXPORT_NAMESPACE}::cmake_automoc_parser
                --cmake-autogen-cache-file "${cmake_autogen_cache_file}"
                --cmake-autogen-info-file "${cmake_autogen_info_file}"
                --output-file-path "${type_list_file}"
                --timestamp-file-path "${cmake_automoc_parser_timestamp}"
                ${multi_config_args}
                COMMENT "Running AUTOMOC file extraction for target ${target}"
                COMMAND_EXPAND_LISTS
                VERBATIM)

        endif()
        set(automoc_args "@${type_list_file}")
        set(automoc_dependencies "${type_list_file}")
    endif()

    set(manual_args)
    set(manual_dependencies)
    if(arg_MANUAL_MOC_JSON_FILES)
        list(REMOVE_DUPLICATES arg_MANUAL_MOC_JSON_FILES)
        file(GENERATE
            OUTPUT ${type_list_file_manual}
            CONTENT "$<JOIN:$<GENEX_EVAL:${arg_MANUAL_MOC_JSON_FILES}>,\n>")
        list(APPEND manual_dependencies ${arg_MANUAL_MOC_JSON_FILES} ${type_list_file_manual})
        set(manual_args "@${type_list_file_manual}")
    endif()

    if (NOT manual_args AND NOT automoc_args)
        message(FATAL_ERROR "Metatype generation requires either the use of AUTOMOC or a manual list of generated json files")
    endif()

    if (CMAKE_BUILD_TYPE AND NOT is_multi_config)
        string(TOLOWER ${target}_${CMAKE_BUILD_TYPE} target_lowercase)
    else()
        string(TOLOWER ${target} target_lowercase)
    endif()

    set(metatypes_file_name "qt6${target_lowercase}_metatypes.json")
    set(metatypes_file "${target_binary_dir}/meta_types/${metatypes_file_name}")
    set(metatypes_file_gen "${target_binary_dir}/meta_types/${metatypes_file_name}.gen")

    set(metatypes_dep_file_name "qt6${target_lowercase}_metatypes_dep.txt")
    set(metatypes_dep_file "${target_binary_dir}/meta_types/${metatypes_dep_file_name}")

    # Due to generated source file dependency rules being tied to the directory
    # scope in which they are created it is not possible for other targets which
    # are defined in a separate scope to see these rules. This leads to failures
    # in locating the generated source files.
    # To work around this we write a dummy file to disk to make sure targets
    # which link against the current target do not produce the error. This dummy
    # file is then replaced with the contents of the generated file during
    # build.
    if (NOT EXISTS ${metatypes_file})
        file(MAKE_DIRECTORY "${target_binary_dir}/meta_types")
        file(TOUCH ${metatypes_file})
    endif()

    add_custom_command(
        OUTPUT
        ${metatypes_file_gen}
        ${metatypes_file}
        DEPENDS ${QEXT_QT_MOC_EXECUTABLE} ${automoc_dependencies} ${manual_dependencies}
        #        DEPENDS ${QEXT_QT_EXPORT_NAMESPACE}::moc ${automoc_dependencies} ${manual_dependencies}
        COMMAND ${QEXT_QT_MOC_EXECUTABLE}
        -o ${metatypes_file_gen}
        --collect-json ${automoc_args} ${manual_args}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${metatypes_file_gen}
        ${metatypes_file}
        COMMENT "Running moc --collect-json for target ${target}"
        VERBATIM)

    # We can't rely on policy CMP0118 since user project controls it
    set(scope_args)
    if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.18")
        set(scope_args TARGET_DIRECTORY ${target})
    endif()
    set_source_files_properties(${metatypes_file_gen} ${metatypes_file}  ${scope_args}
        PROPERTIES GENERATED TRUE)

    # We still need to add this file as a source of the target, otherwise the file
    # rule above is not triggered. INTERFACE_SOURCES do not properly register
    # as dependencies to build the current target.
    # TODO: Can we pass ${metatypes_file} instead of ${metatypes_file_gen} as a source?
    # TODO: Do we still need the _gen variant at all?
    target_sources(${target} PRIVATE ${metatypes_file_gen})
    set_source_files_properties(${metatypes_file} ${scope_args} PROPERTIES HEADER_FILE_ONLY TRUE)

    set_target_properties(${target} PROPERTIES
        INTERFACE_QT_MODULE_HAS_META_TYPES YES
        INTERFACE_QT_META_TYPES_BUILD_FILE "${metatypes_file}")

    # Set up consumption of files via INTERFACE_SOURCES.
    set(consumes_metatypes "$<BOOL:$<TARGET_PROPERTY:QT_CONSUMES_METATYPES>>")
    set(metatypes_file_genex_build "$<BUILD_INTERFACE:$<${consumes_metatypes}:${metatypes_file}>>")
    target_sources(${target} INTERFACE ${metatypes_file_genex_build})

    if(arg_OUTPUT_FILES)
        set(${arg_OUTPUT_FILES} "${metatypes_file}" PARENT_SCOPE)
    endif()

    # Check whether the generated json file needs to be installed.
    # Executable metatypes.json files should not be installed. Qt non-prefix builds should also
    # not install the files.
    set(should_install FALSE)

    if(NOT target_type STREQUAL "EXECUTABLE" AND arg___QT_INTERNAL_INSTALL)
        set(should_install TRUE)
    endif()

    # Automatically fill default install args when not specified.
    if(NOT arg___QT_INTERNAL_INSTALL_DIR)
        # INSTALL_LIBDIR is not set when QtBuildInternals is not loaded (when not doing a Qt build).
        # Default to a hardcoded location for user projects.
        if(INSTALL_LIBDIR)
            set(install_dir "${INSTALL_LIBDIR}/metatypes")
        else()
            set(install_dir "lib/metatypes")
        endif()
    else()
        set(install_dir "${arg___QT_INTERNAL_INSTALL_DIR}")
    endif()

    if(should_install)
        set(metatypes_file_install_path "${install_dir}/${metatypes_file_name}")
        set(metatypes_file_install_path_genex "$<INSTALL_PREFIX>/${metatypes_file_install_path}")
        set(metatypes_file_genex_install
            "$<INSTALL_INTERFACE:$<${consumes_metatypes}:${metatypes_file_install_path_genex}>>")
        target_sources(${target} INTERFACE ${metatypes_file_genex_install})
        install(FILES "${metatypes_file}" DESTINATION "${install_dir}")
    endif()
endfunction()



#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
# The function checks if add_custom_command has the support of the DEPFILE argument.
function(_qt_internal_check_depfile_support out_var)
    if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.20 AND CMAKE_GENERATOR MATCHES "Makefiles")
        set(mk_MATCHES ON)
    endif()
    if (CMAKE_GENERATOR MATCHES "Visual Studio ([0-9]+)" AND CMAKE_MATCH_1 GREATER_EQUAL 12)
        set(VS_MATCHES ON)
    endif()
    if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.21 AND CMAKE_GENERATOR MATCHES "Xcode" OR VS_MATCHES)
        set(VS_Xcode_MATCHES ON)
    endif()
    if(CMAKE_GENERATOR MATCHES "Ninja" OR mk_MATCHES OR VS_Xcode_MATCHES)
        set(${out_var} TRUE)
    else()
        set(${out_var} FALSE)
    endif()
    set(${out_var} "${${out_var}}" PARENT_SCOPE)
endfunction()



#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
# Gets the path to tool wrapper shell script.
function(_qt_internal_get_tool_wrapper_script_path out_variable)
    # Ensure the script wrapper exists.
    _qt_internal_generate_tool_command_wrapper()

    set(${out_variable} "${QT_TOOL_COMMAND_WRAPPER_PATH}" PARENT_SCOPE)
endfunction()



#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(_qt_internal_generate_tool_command_wrapper)
    get_property(is_called GLOBAL PROPERTY _qt_internal_generate_tool_command_wrapper_called)
    if(NOT CMAKE_HOST_WIN32 OR is_called)
        return()
    endif()

    set(prefixes "")

    # In a prefix build, the just-built tools should pick up libraries from the current repo build dir.
    if(QT_BUILD_DIR)
        list(APPEND prefixes "${QT_BUILD_DIR}")
    endif()

    # Pick up libraries from the main location where Qt was installed during a Qt build.
    if(QT_BUILD_INTERNALS_RELOCATABLE_INSTALL_PREFIX)
        list(APPEND prefixes "${QT_BUILD_INTERNALS_RELOCATABLE_INSTALL_PREFIX}")
    endif()

    # Needed for ExternalProjects examples, where the Qt build dir is passed via this variable
    # to the example project.
    if(QT_ADDITIONAL_PACKAGES_PREFIX_PATH)
        __qt_internal_prefix_paths_to_roots(additional_roots "${QT_ADDITIONAL_PACKAGES_PREFIX_PATH}")
        list(APPEND prefixes ${QT_ADDITIONAL_PACKAGES_PREFIX_PATH})
    endif()

    # Fallback to wherever Qt6 package is.
    if(QT6_INSTALL_PREFIX)
        list(APPEND prefixes "${QT6_INSTALL_PREFIX}")
    endif()

    # When building qtbase, QT6_INSTALL_BINS is not set yet.
    if(INSTALL_BINDIR)
        set(bin_suffix "${INSTALL_BINDIR}")
    else()
        set(bin_suffix "${QT6_INSTALL_BINS}")
    endif()

    set(path_dirs "")
    foreach(prefix IN LISTS prefixes)
        set(bin_dir "${prefix}/${bin_suffix}")
        if(EXISTS "${bin_dir}")
            file(TO_NATIVE_PATH "${bin_dir}" path_dir)
            list(APPEND path_dirs "${path_dir}")
        endif()
    endforeach()

    set(tool_command_wrapper_dir "${CMAKE_BINARY_DIR}/.qt/bin")
    file(MAKE_DIRECTORY "${tool_command_wrapper_dir}")
    set(tool_command_wrapper_path "${tool_command_wrapper_dir}/qt_setup_tool_path.bat")

    file(WRITE "${tool_command_wrapper_path}" "@echo off
        set PATH=${path_dirs};%PATH%
        %*")

    set(QT_TOOL_COMMAND_WRAPPER_PATH "${tool_command_wrapper_path}"
        CACHE INTERNAL "Path to the wrapper of the tool commands")

    set_property(GLOBAL PROPERTY _qt_internal_generate_tool_command_wrapper_called TRUE)
endfunction()



#-----------------------------------------------------------------------------------------------------------------------
# We cannot defer writing out the qmldir file to generation time because the
# qmlimportscanner runs at configure time as part of target finalizers.
# Therefore, the best we can do is defer writing the qmldir file if we are
# using a recent enough CMake version, otherwise we write it out progressively
# on each call that adds qml sources. The immediate progressive writes will
# trigger some unnecessary rebuilds after reconfiguring due to the qmldir
# file's timestamp being updated even though its contents might not change,
# but that's the cost of not having deferred write capability.
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_target_generate_qmldir target)
    macro(qext_internal_qmldir_item prefix property)
        get_target_property(_value ${target} ${property})
        if(_value)
            string(APPEND content "${prefix} ${_value}\n")
        endif()
    endmacro()

    macro(qext_internal_qmldir_item_list prefix property)
        get_target_property(_values ${target} ${property})
        if(_values)
            foreach(_value IN LISTS _values)
                string(APPEND content "${prefix} ${_value}\n")
            endforeach()
        endif()
    endmacro()

    get_target_property(uri ${target} QEXT_QML_MODULE_URI)
    if(NOT uri)
        message(FATAL_ERROR "Target ${target} has no URI set, cannot create qmldir")
    endif()
    set(content "module ${uri}\n")

    qext_internal_qmldir_item(linktarget QEXT_QML_MODULE_INSTALLED_PLUGIN_TARGET)

    get_target_property(plugin_target ${target} QEXT_QML_MODULE_PLUGIN_TARGET)
    if(plugin_target)
        get_target_property(no_plugin_optional ${target} QEXT_QML_MODULE_NO_PLUGIN_OPTIONAL)
        if(NOT no_plugin_optional MATCHES "NOTFOUND" AND NOT no_plugin_optional)
            string(APPEND content "optional ")
        endif()

        get_target_property(target_path ${target} QEXT_QML_MODULE_TARGET_PATH)
        qext_internal_get_qml_plugin_output_name(plugin_output_name ${plugin_target}
            TARGET_PATH "${target_path}"
            URI "${uri}")
        string(APPEND content "plugin ${plugin_output_name}\n")

        qext_internal_qmldir_item(classname QEXT_QML_MODULE_CLASS_NAME)
    endif()

    get_target_property(designer_supported ${target} QEXT_QML_MODULE_DESIGNER_SUPPORTED)
    if(designer_supported)
        string(APPEND content "designersupported\n")
    endif()

    get_target_property(static_module ${target} QEXT_QML_MODULE_IS_STATIC)
    if (static_module)
        string(APPEND content "static\n")
    endif()

    get_target_property(system_module ${target} QEXT_QML_MODULE_IS_SYSTEM)
    if (system_module)
        string(APPEND content "system\n")
    endif()

    qext_internal_qmldir_item(typeinfo QEXT_QML_MODULE_TYPEINFO)

    qext_internal_qmldir_item_list(import QT_QML_MODULE_IMPORTS)
    qext_internal_qmldir_item_list("optional import" QT_QML_MODULE_OPTIONAL_IMPORTS)
    qext_internal_qmldir_item_list("default import" QT_QML_MODULE_DEFAULT_IMPORTS)

    # qext_internal_qmldir_item_list(depends QT_QML_MODULE_DEPENDENCIES)

    get_target_property(prefix ${target} QEXT_QML_MODULE_RESOURCE_PREFIX)
    if(prefix)
        # Ensure we use a path that ends with a "/", but handle the special case
        # of "/" without anything after it
        if(NOT prefix STREQUAL "/" AND NOT prefix MATCHES "/$")
            string(APPEND prefix "/")
        endif()
        string(APPEND content "prefer :${prefix}\n")
    endif()

    # Record the contents but defer the actual write. We will write the file
    # later, either at the end of qt6_add_qml_module() or the end of the
    # directory scope (depending on the CMake version being used).
    set_property(TARGET ${target} PROPERTY _qext_internal_qmldir_content "${content}")
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
# The function returns the output name of a qml plugin that will be used as library output
# name and in a qmldir file as the 'plugin <plugin_output_name>' record.
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_get_qml_plugin_output_name out_var plugin_target)
    cmake_parse_arguments(arg
        ""
        "BACKING_TARGET;TARGET_PATH;URI"
        ""
        ${ARGN})
    set(plugin_name)
    if(TARGET ${plugin_target})
        get_target_property(plugin_name ${plugin_target} OUTPUT_NAME)
    endif()
    if(NOT plugin_name)
        set(plugin_name "${plugin_target}")
    endif()

    if(ANDROID)
        # In Android all plugins are stored in directly the /libs directory. This means that plugin
        # names must be unique in scope of apk. To make this work we prepend uri-based prefix to
        # each qml plugin in case if users don't use the manually written qmldir files.
        get_target_property(no_generate_qmldir ${target} QEXT_QML_MODULE_NO_GENERATE_QMLDIR)
        if(TARGET "${arg_BACKING_TARGET}")
            get_target_property(no_generate_qmldir ${arg_BACKING_TARGET}
                QEXT_QML_MODULE_NO_GENERATE_QMLDIR)

            # Adjust Qml plugin names on Android similar to qml_plugin.prf which calls
            # $$qt5LibraryTarget($$TARGET, "qml/$$TARGETPATH/").
            # Example plugin names:
            # qtdeclarative
            #   TARGET_PATH: QtQml/Models
            #   file name:   libqml_QtQml_Models_modelsplugin_x86_64.so
            # qtquickcontrols2
            #   TARGET_PATH: QtQuick/Controls.2/Material
            #   file name:
            #     libqml_QtQuick_Controls.2_Material_qtquickcontrols2materialstyleplugin_x86_64.so
            if(NOT arg_TARGET_PATH)
                get_target_property(arg_TARGET_PATH ${arg_BACKING_TARGET} QEXT_QML_MODULE_TARGET_PATH)
            endif()
        endif()
        if(arg_TARGET_PATH)
            string(REPLACE "/" "_" android_plugin_name_infix_name "${arg_TARGET_PATH}")
        else()
            string(REPLACE "." "_" android_plugin_name_infix_name "${arg_URI}")
        endif()

        # If plugin supposed to use manually written qmldir file we don't prepend the uri-based
        # prefix to the plugin output name. User should keep the file name of a QML plugin in
        # qmldir the same as the name of plugin on a file system. Exception is the
        # ABI-/platform-specific suffix that has the separate processing and should not be
        # a part of plugin name in qmldir.
        if(NOT no_generate_qmldir)
            set(plugin_name "qml_${android_plugin_name_infix_name}_${plugin_name}")
        endif()
    endif()

    set(${out_var} "${plugin_name}" PARENT_SCOPE)
endfunction()



#-----------------------------------------------------------------------------------------------------------------------
# qt6_add_resources(target resourcename ...
# or
# qt6_add_resources(outfiles inputfile ... )
#-----------------------------------------------------------------------------------------------------------------------
function(qt6_add_resources outfiles )
    if (TARGET ${outfiles})
        cmake_parse_arguments(arg "" "OUTPUT_TARGETS" "" ${ARGN})
        _qt_internal_process_resource(${ARGV})
        if (arg_OUTPUT_TARGETS)
            set(${arg_OUTPUT_TARGETS} ${${arg_OUTPUT_TARGETS}} PARENT_SCOPE)
        endif()
    else()
        set(options)
        set(oneValueArgs)
        set(multiValueArgs OPTIONS)

        cmake_parse_arguments(_RCC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

        set(rcc_files ${_RCC_UNPARSED_ARGUMENTS})
        set(rcc_options ${_RCC_OPTIONS})

        if("${rcc_options}" MATCHES "-binary")
            message(WARNING "Use qt6_add_binary_resources for binary option")
        endif()

        if(NOT QT_FEATURE_zstd)
            # list(APPEND rcc_options "--no-zstd")
        endif()

        foreach(it ${rcc_files})
            get_filename_component(outfilename ${it} NAME_WE)
            get_filename_component(infile ${it} ABSOLUTE)
            set(outfile ${CMAKE_CURRENT_BINARY_DIR}/qrc_${outfilename}.cpp)

            _qt6_parse_qrc_file(${infile} _out_depends _rc_depends)
            set_source_files_properties(${infile} PROPERTIES SKIP_AUTORCC ON)

            add_custom_command(OUTPUT ${outfile}
                COMMAND ${QEXT_QT_RCC_EXECUTABLE}
                ARGS ${rcc_options} --name ${outfilename} --output ${outfile} ${infile}
                MAIN_DEPENDENCY ${infile}
                DEPENDS ${_rc_depends} "${_out_depends}" ${QEXT_QT_RCC_EXECUTABLE}
                VERBATIM)
            set_source_files_properties(${outfile} PROPERTIES SKIP_AUTOMOC ON
                SKIP_AUTOUIC ON
                SKIP_UNITY_BUILD_INCLUSION ON
                SKIP_PRECOMPILE_HEADERS ON)
            list(APPEND ${outfiles} ${outfile})
        endforeach()
        set(${outfiles} ${${outfiles}} PARENT_SCOPE)
    endif()
endfunction()



#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------

#
# Process resources via file path instead of QRC files. Behind the
# scenes, it will generate a qrc file.
#
# The QRC Prefix is set via the PREFIX parameter.
#
# Alias settings for files need to be set via the QT_RESOURCE_ALIAS property
# via the set_source_files_properties() command.
#
# When using this command with static libraries, one or more special targets
# will be generated. Should you wish to perform additional processing on these
# targets pass a value to the OUTPUT_TARGETS parameter.
#
function(_qt_internal_process_resource target resourceName)

    cmake_parse_arguments(rcc "" "PREFIX;LANG;BASE;OUTPUT_TARGETS;DESTINATION" "FILES;OPTIONS" ${ARGN})

    if("${rcc_OPTIONS}" MATCHES "-binary")
        set(isBinary TRUE)
    endif()

    string(REPLACE "/" "_" resourceName ${resourceName})
    string(REPLACE "." "_" resourceName ${resourceName})

    set(resource_files "")
    # Strip the ending slashes from the file_path. If paths contain slashes in the end
    # set/get source properties works incorrect and may have the same QT_RESOURCE_ALIAS
    # for two different paths. See https://gitlab.kitware.com/cmake/cmake/-/issues/23212
    # for details.
    foreach(file_path IN LISTS rcc_FILES)
        if(file_path MATCHES "(.+)/$")
            set(file_path "${CMAKE_MATCH_1}")
        endif()
        list(APPEND resource_files ${file_path})
    endforeach()

    if(NOT "${rcc_BASE}" STREQUAL "")
        get_filename_component(abs_base "${rcc_BASE}" ABSOLUTE)
        foreach(file_path IN LISTS resource_files)
            get_source_file_property(alias "${file_path}" QT_RESOURCE_ALIAS)
            if(alias STREQUAL "NOTFOUND")
                get_filename_component(abs_file "${file_path}" ABSOLUTE)
                file(RELATIVE_PATH rel_file "${abs_base}" "${abs_file}")
                set_property(SOURCE "${file_path}" PROPERTY QT_RESOURCE_ALIAS "${rel_file}")
            endif()
        endforeach()
    endif()

    if(ANDROID)
        if(COMMAND _qt_internal_collect_qml_root_paths)
            _qt_internal_collect_qml_root_paths(${target} ${resource_files})
        endif()
    endif()

    if(NOT rcc_PREFIX)
        get_target_property(rcc_PREFIX ${target} QT_RESOURCE_PREFIX)
        if (NOT rcc_PREFIX)
            message(FATAL_ERROR "_qt_internal_process_resource() was called without a PREFIX and the target does not"
                " provide QT_RESOURCE_PREFIX. Please either add a PREFIX or make the target ${target} provide a default.")
        endif()
    endif()

    if (NOT resource_files)
        if (rcc_OUTPUT_TARGETS)
            set(${rcc_OUTPUT_TARGETS} "" PARENT_SCOPE)
        endif()
        return()
    endif()
    set(generatedResourceFile "${CMAKE_CURRENT_BINARY_DIR}/.rcc/${resourceName}.qrc")

    # Generate .qrc file:

    # <RCC><qresource ...>
    set(qrcContents "<RCC>\n  <qresource")
    if (rcc_PREFIX)
        string(APPEND qrcContents " prefix=\"${rcc_PREFIX}\"")
    endif()
    if (rcc_LANG)
        string(APPEND qrcContents " lang=\"${rcc_LANG}\"")
    endif()
    string(APPEND qrcContents ">\n")

    set(resource_dependencies)
    foreach(file IN LISTS resource_files)
        qext_internal_get_relative_resource_path_for_file(file_resource_path ${file})

        if (NOT IS_ABSOLUTE ${file})
            set(file "${CMAKE_CURRENT_SOURCE_DIR}/${file}")
        endif()

        ### FIXME: escape file paths to be XML conform
        # <file ...>...</file>
        string(APPEND qrcContents "    <file alias=\"${file_resource_path}\">")
        string(APPEND qrcContents "${file}</file>\n")
        list(APPEND files "${file}")

        set(scope_args)
        if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.18")
            set(scope_args TARGET_DIRECTORY ${target})
        endif()
        get_source_file_property(target_dependency ${file} ${scope_args} _qt_resource_target_dependency)

        # The target dependency code path does not take care of rebuilds when ${file}
        # is touched. Limit its usage to the Xcode generator to avoid the Xcode common
        # dependency issue.
        # TODO: Figure out how to avoid the issue on Xcode, while also enabling proper
        # dependency tracking when ${file} is touched.
        if(target_dependency AND CMAKE_GENERATOR STREQUAL "Xcode")
            if(NOT TARGET ${target_dependency})
                message(FATAL_ERROR "Target dependency on resource file ${file} is not a cmake target.")
            endif()
            list(APPEND resource_dependencies ${target_dependency})
        else()
            list(APPEND resource_dependencies ${file})
        endif()
        qext_internal_expose_source_file_to_ide(${target} "${file}")
    endforeach()

    # </qresource></RCC>
    string(APPEND qrcContents "  </qresource>\n</RCC>\n")

    set(template_file "${PROJECT_SOURCE_DIR}/cmake/QExtCoreConfigureFileTemplate.in")
    set(qext_core_configure_file_contents "${qrcContents}")
    configure_file("${template_file}" "${generatedResourceFile}")

    set(rccArgs --name "${resourceName}" "${generatedResourceFile}")

    if(rcc_OPTIONS)
        list(APPEND rccArgs ${rcc_OPTIONS})
    endif()

    # When cross-building, we use host tools to generate target code. If the host rcc was compiled
    # with zstd support, it expects the target QtCore to be able to decompress zstd compressed
    # content. This might be true with qmake where host tools are built as part of the
    # cross-compiled Qt, but with CMake we build tools separate from the cross-compiled Qt.
    # If the target does not support zstd (feature is disabled), tell rcc not to generate
    # zstd related code.
    if(NOT QT_FEATURE_zstd)
        # list(APPEND rccArgs "--no-zstd")
    endif()

    set_property(SOURCE "${generatedResourceFile}" PROPERTY SKIP_AUTOGEN ON)

    # Set output file name for rcc command
    if(isBinary)
        set(generatedOutfile "${CMAKE_CURRENT_BINARY_DIR}/${resourceName}.rcc")
        if(rcc_DESTINATION)
            # Add .rcc suffix if it's not specified by user
            get_filename_component(destinationRccExt "${rcc_DESTINATION}" LAST_EXT)
            if("${destinationRccExt}" STREQUAL ".rcc")
                set(generatedOutfile "${rcc_DESTINATION}")
            else()
                set(generatedOutfile "${rcc_DESTINATION}.rcc")
            endif()
        endif()
    else()
        set(generatedOutfile "${CMAKE_CURRENT_BINARY_DIR}/.rcc/qrc_${resourceName}.cpp")
    endif()

    list(PREPEND rccArgs --output "${generatedOutfile}")

    # Process .qrc file:
    add_custom_command(OUTPUT "${generatedOutfile}"
        COMMAND "${QEXT_QT_RCC_EXECUTABLE}" ${rccArgs}
        DEPENDS
        ${resource_dependencies}
        ${generatedResourceFile}
        "${QEXT_QT_RCC_EXECUTABLE}"
        COMMENT "Running rcc for resource ${resourceName}"
        VERBATIM)

    set(output_targets "")
    if(isBinary)
        # Add generated .rcc target to 'all' set
        add_custom_target(binary_resource_${resourceName} ALL DEPENDS "${generatedOutfile}")
    else()
        # We can't rely on policy CMP0118 since user project controls it.
        # We also want SKIP_AUTOGEN known in the target's scope, where we can.
        set(scope_args)
        if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.18")
            set(scope_args TARGET_DIRECTORY ${target})
        endif()
        set_source_files_properties(${generatedOutfile} ${scope_args} PROPERTIES
            SKIP_AUTOGEN TRUE
            GENERATED TRUE
            SKIP_UNITY_BUILD_INCLUSION TRUE
            SKIP_PRECOMPILE_HEADERS TRUE)
        get_target_property(target_source_dir ${target} SOURCE_DIR)
        if(NOT target_source_dir STREQUAL CMAKE_CURRENT_SOURCE_DIR)
            # We have to create a separate target in this scope that depends on
            # the generated file, otherwise the original target won't have the
            # required dependencies in place to ensure correct build order.
            add_custom_target(${target}_${resourceName} DEPENDS ${generatedOutfile})
            add_dependencies(${target} ${target}_${resourceName})
        endif()
        set_property(TARGET ${target} APPEND PROPERTY _qt_generated_qrc_files "${generatedResourceFile}")

        __qt_propagate_generated_resource(${target} ${resourceName} "${generatedOutfile}" output_targets)
    endif()
    if (rcc_OUTPUT_TARGETS)
        set(${rcc_OUTPUT_TARGETS} "${output_targets}" PARENT_SCOPE)
    endif()
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_get_relative_resource_path_for_file output_alias file)
    get_property(alias SOURCE ${file} PROPERTY QT_RESOURCE_ALIAS)
    if (NOT alias)
        set(alias "${file}")
    endif()
    set(${output_alias} ${alias} PARENT_SCOPE)
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
# Creates fake targets and adds resource files to IDE's tree
# FIXME: We shouldn't need to create a separate target for this, the files
#        should be added to the actual target instead.
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_expose_source_file_to_ide target file)
    set(ide_target ${target}Files)
    if(NOT TARGET ${ide_target})
        add_custom_target(${ide_target} SOURCES "${file}")

        # The new Xcode build system requires a common target to drive the generation of files, otherwise project
        # configuration fails.
        # By adding ${target} as a dependency of ${target}Files, it becomes the common target, so project
        # configuration succeeds.
        if(CMAKE_GENERATOR STREQUAL "Xcode")
            add_dependencies(${ide_target} ${target})
        endif()
    else()
        set_property(TARGET ${ide_target} APPEND PROPERTY SOURCES "${file}")
    endif()

    set(scope_args)
    if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.18")
        set(scope_args TARGET_DIRECTORY "${target}")
    endif()
    get_source_file_property(target_dependency "${file}" ${scope_args} _qt_resource_target_dependency)
    if(target_dependency)
        if(NOT TARGET "${target_dependency}")
            message(FATAL_ERROR "Target dependency on source file ${file} is not a cmake target.")
        endif()
        add_dependencies(${ide_target} ${target_dependency})
    endif()
endfunction()



#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(__qt_propagate_generated_resource target resource_name generated_source_code output_generated_target)
    get_target_property(type ${target} TYPE)
    if(type STREQUAL STATIC_LIBRARY)
        get_target_property(resource_count ${target} _qt_generated_resource_target_count)
        if(NOT resource_count)
            set(resource_count "0")
        endif()
        math(EXPR resource_count "${resource_count} + 1")
        set_target_properties(${target} PROPERTIES _qt_generated_resource_target_count ${resource_count})

        set(resource_target "${target}_resources_${resource_count}")
        add_library("${resource_target}" OBJECT "${generated_source_code}")
        target_compile_definitions("${resource_target}" PRIVATE
            "$<TARGET_PROPERTY:${QEXT_QT_EXPORT_NAMESPACE}::Core,INTERFACE_COMPILE_DEFINITIONS>")
        _qt_internal_set_up_static_runtime_library("${resource_target}")

        # Special handling is required for the Core library resources. The linking of the Core
        # library to the resources adds a circular dependency. This leads to the wrong
        # objects/library order in the linker command line, since the Core library target is
        # resolved first.
        if(NOT target STREQUAL "Core")
            target_link_libraries(${resource_target} INTERFACE ${QEXT_QT_EXPORT_NAMESPACE}::Core)
        endif()
        set_property(TARGET ${resource_target} APPEND PROPERTY _qt_resource_name ${resource_name})

        # Save the path to the generated source file, relative to the the current build dir.
        # The path will be used in static library prl file generation to ensure qmake links
        # against the installed resource object files.
        # Example saved path:
        #    .rcc/qrc_qprintdialog.cpp
        file(RELATIVE_PATH generated_cpp_file_relative_path
            "${CMAKE_CURRENT_BINARY_DIR}"
            "${generated_source_code}")
        set_property(TARGET ${resource_target} APPEND PROPERTY
            _qt_resource_generated_cpp_relative_path "${generated_cpp_file_relative_path}")

        if(target STREQUAL "Core")
            set(skip_direct_linking NO_LINK_OBJECT_LIBRARY_REQUIREMENTS_TO_TARGET)
        endif()
        __qt_internal_propagate_object_library(${target} ${resource_target}
            ${skip_direct_linking})

        set(${output_generated_target} "${resource_target}" PARENT_SCOPE)
    else()
        set(${output_generated_target} "" PARENT_SCOPE)
        target_sources(${target} PRIVATE ${generated_source_code})
    endif()
endfunction()



#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(_qt_internal_set_up_static_runtime_library target)
    if(QT_FEATURE_static_runtime)
        if(MSVC)
            set_property(TARGET ${target} PROPERTY
                MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
        elseif(MINGW)
            target_link_options(${target} INTERFACE "LINKER:-Bstatic")
        endif()
    endif()
endfunction()



#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------

# Performs linking and propagation of the object library via the target's usage requirements.
# Arguments:
# NO_LINK_OBJECT_LIBRARY_REQUIREMENTS_TO_TARGET skip linking of ${object_library} to ${target}, only
#   propagate $<TARGET_OBJECTS:${object_library}> by linking it to ${target}. It's useful in case
#   if ${object_library} depends on the ${target}. E.g. resource libraries depend on the Core
#   library so linking them back to Core will cause a CMake error.
#
# EXTRA_CONDITIONS object library specific conditions to be checked before link the object library
#   to the end-point executable.
function(__qt_internal_propagate_object_library target object_library)
    set(options NO_LINK_OBJECT_LIBRARY_REQUIREMENTS_TO_TARGET)
    set(single_args "")
    set(multi_args EXTRA_CONDITIONS)
    cmake_parse_arguments(arg "${options}" "${single_args}" "${multi_args}" ${ARGN})

    get_target_property(is_imported ${object_library} IMPORTED)
    if(NOT is_imported)
        #            target_link_libraries(${object_library} PRIVATE ${QEXT_QT_EXPORT_NAMESPACE}::Platform)
        _qt_internal_copy_dependency_properties(${object_library} ${target} PRIVATE_ONLY)
    endif()

    # After internal discussion we decided to not rely on the linker order that CMake
    # offers, until CMake provides the guaranteed linking order that suites our needs in a
    # future CMake version.
    # All object libraries mark themselves with the _is_qt_propagated_object_library property.
    # Using a finalizer approach we walk through the target dependencies and look for libraries
    # using the _is_qt_propagated_object_library property. Then, objects of the collected libraries
    # are moved to the beginning of the linker line using target_sources.
    #
    # Note: target_link_libraries works well with linkers other than ld. If user didn't enforce
    # a finalizer we rely on linker to resolve circular dependencies between objects and static
    # libraries.
    set_property(TARGET ${object_library} PROPERTY _is_qt_propagated_object_library TRUE)
    if(NOT is_imported)
        set_property(TARGET ${object_library} APPEND PROPERTY
            EXPORT_PROPERTIES _is_qt_propagated_object_library)
    endif()

    # Keep the implicit linking if finalizers are not used.
    set(not_finalizer_mode_condition
        "$<NOT:$<BOOL:$<TARGET_PROPERTY:_qt_object_libraries_finalizer_mode>>>")

    # Collect object library specific conditions.
    if(arg_EXTRA_CONDITIONS)
        list(JOIN arg_EXTRA_CONDITIONS "," extra_conditions)
    else()
        set(extra_conditions "$<BOOL:TRUE>")
    endif()

    # Do not litter the static libraries
    set(not_static_condition
        "$<NOT:$<STREQUAL:$<TARGET_PROPERTY:TYPE>,STATIC_LIBRARY>>")

    # Check if link order matters for the Platform.
    #        set(platform_link_order_property
    #            "$<TARGET_PROPERTY:${QEXT_QT_EXPORT_NAMESPACE}::Platform,_qt_link_order_matters>"
    #            )
    set(platform_link_order_condition
        "$<BOOL:${platform_link_order_property}>")

    # Check if link options are propagated according to CMP0099
    # In user builds the _qt_cmp0099_policy_check is set to FALSE or $<TARGET_POLICY:CMP0099>
    # depending on the used CMake version.
    # See __qt_internal_check_cmp0099_available for details.
    #        set(cmp0099_policy_check_property
    #            "$<TARGET_PROPERTY:${QEXT_QT_EXPORT_NAMESPACE}::Platform,_qt_cmp0099_policy_check>"
    #            )
    set(link_objects_using_link_options_condition
        "$<BOOL:$<GENEX_EVAL:${cmp0099_policy_check_property}>>")

    # Use TARGET_NAME to have the correct namespaced name in the exports.
    set(objects "$<TARGET_OBJECTS:$<TARGET_NAME:${object_library}>>")

    # Collect link conditions for the target_sources call.
    string(JOIN "" target_sources_genex
        "$<"
        "$<AND:"
        "${not_finalizer_mode_condition},"
        "${not_static_condition},"
        "${platform_link_order_condition},"
        "$<NOT:${link_objects_using_link_options_condition}>,"
        "${extra_conditions}"
        ">"
        ":${objects}>")
    target_sources(${target} INTERFACE
        "${target_sources_genex}")

    # Collect link conditions for the target_link_options call.
    string(JOIN "" target_link_options_genex
        "$<"
        "$<AND:"
        "${not_static_condition},"
        "${platform_link_order_condition},"
        "${link_objects_using_link_options_condition},"
        "${extra_conditions}"
        ">"
        ":${objects}>")
    # target_link_options works well since CMake 3.17 which has policy CMP0099 set to NEW for the
    # minimum required CMake version greater than or equal to 3.17. The default is OLD. See
    # https://cmake.org/cmake/help/git-master/policy/CMP0099.html for details.
    # This provides yet another way of linking object libraries if user sets the policy to NEW
    # before calling find_package(Qt...).
    target_link_options(${target} INTERFACE
        "${target_link_options_genex}")

    # Collect link conditions for the target_link_libraries call.
    string(JOIN "" target_link_libraries_genex
        "$<"
        "$<AND:"
        "${not_finalizer_mode_condition},"
        "${not_static_condition},"
        "$<NOT:${platform_link_order_condition}>,"
        "${extra_conditions}"
        ">"
        ":${objects}>")
    target_link_libraries(${target} INTERFACE
        "${target_link_libraries_genex}")

    if(NOT arg_NO_LINK_OBJECT_LIBRARY_REQUIREMENTS_TO_TARGET)
        # It's necessary to link the object library target, since we want to pass the object library
        # dependencies to the 'target'. Interface linking doesn't add the objects of the library to
        # the end-point linker line but propagates all the dependencies of the object_library added
        # before or AFTER the line below.
        target_link_libraries(${target} INTERFACE ${object_library})
    endif()
endfunction()



#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------

# Copies properties of the dependency to the target.
# Arguments:
#   PROPERTIES list of properties to copy. If not specified the following properties are copied
#              by default: INCLUDE_DIRECTORIES SYSTEM_INCLUDE_DIRECTORIES COMPILE_DEFINITIONS
#              COMPILE_OPTIONS COMPILE_FEATURES
#   PRIVATE_ONLY copy only private properties (without INTERFACE analogues). Optional.
#   INTERFACE_ONLY copy only interface properties (without non-prefixed analogues). Optional.
#      Note: Not all properties have INTERFACE properties analogues.
#            See https://cmake.org/cmake/help/latest/prop_tgt/EXPORT_PROPERTIES.html for details.
#
# PRIVATE_ONLY and INTERFACE_ONLY in the same call are not allowed. Omit these options to copy
# both sets.
function(_qt_internal_copy_dependency_properties target dependency)
    cmake_parse_arguments(arg "INTERFACE_ONLY;PRIVATE_ONLY" "" "PROPERTIES" ${ARGN})
    if(arg_PRIVATE_ONLY AND arg_INTERFACE_ONLY)
        message("Both PRIVATE_ONLY and INTERFACE_ONLY options are set.\
            Please use _qt_internal_copy_dependency_properties without these options to copy a set of
            properties of both types.")
    endif()

    if(arg_PROPERTIES)
        set(common_props_to_set ${arg_PROPERTIES})
    else()
        set(common_props_to_set
            INCLUDE_DIRECTORIES SYSTEM_INCLUDE_DIRECTORIES
            COMPILE_DEFINITIONS COMPILE_OPTIONS
            COMPILE_FEATURES)
    endif()

    set(props_to_set "")
    if(NOT arg_INTERFACE_ONLY)
        set(props_to_set ${common_props_to_set})
    endif()
    if(NOT arg_PRIVATE_ONLY)
        list(TRANSFORM common_props_to_set PREPEND INTERFACE_OUTPUT_VARIABLE interface_properties)
        list(APPEND props_to_set ${interface_properties})
    endif()

    foreach(prop ${props_to_set})
        set_property(TARGET
            "${target}" APPEND PROPERTY
            ${prop} "$<TARGET_PROPERTY:${dependency},${prop}>")
    endforeach()
endfunction()



#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_get_escaped_uri uri out_var)
    string(REGEX REPLACE "[^A-Za-z0-9]" "_" escaped_uri "${uri}")
    set(${out_var} "${escaped_uri}" PARENT_SCOPE)
endfunction()



#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------

function(_qt_internal_add_static_qml_plugin_dependencies plugin_target backing_target)
    # Protect against multiple calls of qt_add_qml_plugin.
    get_target_property(plugin_deps_added "${plugin_target}" _qt_extra_static_qml_plugin_deps_added)
    if(plugin_deps_added)
        return()
    endif()
    set_target_properties("${plugin_target}" PROPERTIES _qt_extra_static_qml_plugin_deps_added TRUE)

    # Get the install plugin target name, which we will need for filtering later on.
    if(TARGET "${backing_target}")
        get_target_property(installed_plugin_target
            "${backing_target}" _qt_qml_module_installed_plugin_target)
    endif()

    if(NOT backing_target STREQUAL plugin_target AND TARGET "${backing_target}")
        set(has_backing_lib TRUE)
    else()
        set(has_backing_lib FALSE)
    endif()

    get_target_property(plugin_type ${plugin_target} TYPE)
    set(skip_prl_marker "$<BOOL:QT_IS_PLUGIN_GENEX>")

    # If ${plugin_target} is a static qml plugin, recursively get its private dependencies (and its
    # backing lib private deps), identify which of those are qml modules, extract any associated qml
    # plugin target from those qml modules and make them dependencies of ${plugin_target}.
    #
    # E.g. this ensures that if a user project links directly to the static qtquick2plugin plugin
    # target (note the plugin target, not the backing lib) it will automatically also link to
    # Quick's transitive plugin dependencies: qmlplugin, modelsplugin and workerscriptplugin, in
    # addition to the the Qml, QmlModels and QmlWorkerScript backing libraries.
    #
    # Note this logic is not specific to qtquick2plugin, it applies to all static qml plugins.
    #
    # This eliminates the needed boilerplate to link to the full transitive closure of qml plugins
    # in user projects that don't want to use qmlimportscanner / qt_import_qml_plugins.
    set(additional_plugin_deps "")

    if(plugin_type STREQUAL "STATIC_LIBRARY")
        set(all_private_deps "")

        # We walk both plugin_target and backing_lib private deps because they can have differing
        # dependencies and we want to consider all of them.
        __qt_internal_collect_all_target_dependencies(
            "${plugin_target}" plugin_private_deps)
        if(plugin_private_deps)
            list(APPEND all_private_deps ${plugin_private_deps})
        endif()

        if(has_backing_lib)
            __qt_internal_collect_all_target_dependencies(
                "${backing_target}" backing_lib_private_deps)
            if(backing_lib_private_deps)
                list(APPEND all_private_deps ${backing_lib_private_deps})
            endif()
        endif()

        foreach(dep IN LISTS all_private_deps)
            if(NOT TARGET "${dep}")
                continue()
            endif()
            get_target_property(dep_type ${dep} TYPE)
            if(dep_type STREQUAL "STATIC_LIBRARY")
                set(associated_qml_plugin "")

                # Check if the target has an associated imported qml plugin (like a Qt-provided
                # one).
                get_target_property(associated_qml_plugin_candidate ${dep}
                    _qt_qml_module_installed_plugin_target)

                if(associated_qml_plugin_candidate AND TARGET "${associated_qml_plugin_candidate}")
                    set(associated_qml_plugin "${associated_qml_plugin_candidate}")
                endif()

                # Check if the target has an associated qml plugin that's built as part of the
                # current project (non-installed one, so without a target namespace prefix).
                get_target_property(associated_qml_plugin_candidate ${dep}
                    _qt_qml_module_plugin_target)

                if(NOT associated_qml_plugin AND
                        associated_qml_plugin_candidate
                        AND TARGET "${associated_qml_plugin_candidate}")
                    set(associated_qml_plugin "${associated_qml_plugin_candidate}")
                endif()

                # We need to filter out adding the plugin_target as a dependency to itself,
                # when walking the backing lib of the plugin_target.
                if(associated_qml_plugin
                        AND NOT associated_qml_plugin STREQUAL plugin_target
                        AND NOT associated_qml_plugin STREQUAL installed_plugin_target)
                    # Abuse a genex marker, to skip the dependency to be added into prl files.
                    # TODO: Introduce a more generic marker name in qtbase specifically
                    # for skipping deps in prl file deps generation.
                    set(wrapped_associated_qml_plugin
                        "$<${skip_prl_marker}:$<TARGET_NAME:${associated_qml_plugin}>>")

                    if(NOT wrapped_associated_qml_plugin IN_LIST additional_plugin_deps)
                        list(APPEND additional_plugin_deps "${wrapped_associated_qml_plugin}")
                    endif()
                endif()
            endif()
        endforeach()
    endif()

    if(additional_plugin_deps)
        target_link_libraries(${plugin_target} PRIVATE ${additional_plugin_deps})
    endif()
endfunction()



#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------

# Given ${target}, collect all its private dependencies that are CMake targets.
#
# Discards non-CMake-target dependencies like linker flags or file paths.
# Does nothing when given an interface library.
#
# To be used to extract the full list of target dependencies of a library or executable.
function(__qt_internal_collect_all_target_dependencies target out_var)
    set(dep_targets "")

    get_target_property(target_type ${target} TYPE)

    if(NOT target_type STREQUAL "INTERFACE_LIBRARY")
        get_target_property(link_libs ${target} LINK_LIBRARIES)
        if(link_libs)
            foreach(lib ${link_libs})
                if(TARGET "${lib}")
                    list(APPEND dep_targets "${lib}")

                    #                    __qt_internal_walk_libs(
                    __qext_internal_walk_libs(
                        "${lib}"
                        lib_walked_targets
                        _discarded_out_var
                        "qt_private_link_library_targets"
                        "collect_targets")

                    if(lib_walked_targets)
                        list(APPEND dep_targets ${lib_walked_targets})
                    endif()
                endif()
            endforeach()
        endif()
    endif()

    list(REMOVE_DUPLICATES dep_targets)

    set(${out_var} "${dep_targets}" PARENT_SCOPE)
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qt6_target_qml_sources target)
    get_target_property(uri        ${target} QEXT_QML_MODULE_URI)
    get_target_property(output_dir ${target} QEXT_QML_MODULE_OUTPUT_DIRECTORY)
    if(NOT uri OR NOT output_dir)
        message(FATAL_ERROR "Target ${target} is not a QML module")
    endif()

    set(args_option
        NO_LINT
        NO_CACHEGEN
        NO_QMLDIR_TYPES
        __QT_INTERNAL_FORCE_DEFER_QMLDIR)  # Used only by qt6_add_qml_module())

    set(args_single
        PREFIX
        OUTPUT_TARGETS)

    set(args_multi
        QML_FILES
        RESOURCES)

    cmake_parse_arguments(PARSE_ARGV 1 arg
        "${args_option}" "${args_single}" "${args_multi}")
    if(arg_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unknown/unexpected arguments: ${arg_UNPARSED_ARGUMENTS}")
    endif()

    if (NOT arg_QML_FILES AND NOT arg_RESOURCES)
        if(arg_OUTPUT_TARGETS)
            set(${arg_OUTPUT_TARGETS} "" PARENT_SCOPE)
        endif()
        return()
    endif()

    if(NOT arg___QT_INTERNAL_FORCE_DEFER_QMLDIR AND ${CMAKE_VERSION} VERSION_LESS "3.19.0")
        message(FATAL_ERROR
            "You are using CMake ${CMAKE_VERSION}, but CMake 3.19 or later "
            "is required to add qml files with this function. Either pass "
            "the qml files to qt6_add_qml_module() instead or update to "
            "CMake 3.19 or later.")
    endif()

    get_target_property(no_lint                ${target} QEXT_QML_MODULE_NO_LINT)
    get_target_property(no_cachegen            ${target} QEXT_QML_MODULE_NO_CACHEGEN)
    get_target_property(no_qmldir              ${target} QEXT_QML_MODULE_NO_GENERATE_QMLDIR)
    get_target_property(resource_prefix        ${target} QEXT_QML_MODULE_RESOURCE_PREFIX)
    get_target_property(qml_module_version     ${target} QEXT_QML_MODULE_VERSION)
    get_target_property(past_major_versions    ${target} QEXT_QML_MODULE_PAST_MAJOR_VERSIONS)

    if(NOT output_dir)
        # Probably not a qml module. We still want to support tooling for this
        # scenario, it's just that we will be relying solely on the implicit
        # imports to find things.
        set(output_dir ${CMAKE_CURRENT_BINARY_DIR})
        set(no_qmldir TRUE)
    endif()

    if(NOT arg_PREFIX)
        if(resource_prefix)
            set(arg_PREFIX ${resource_prefix})
        else()
            message(FATAL_ERROR
                "PREFIX option not given and target ${target} does not have a "
                "QEXT_QML_MODULE_RESOURCE_PREFIX property set.")
        endif()
    endif()
    _qt_internal_canonicalize_resource_path("${arg_PREFIX}" arg_PREFIX)
    if(arg_PREFIX STREQUAL resource_prefix)
        set(prefix_override "")
    else()
        set(prefix_override "${arg_PREFIX}")
    endif()
    if(NOT arg_PREFIX STREQUAL "/")
        string(APPEND arg_PREFIX "/")
    endif()

    if (qml_module_version MATCHES "^([0-9]+)\\.")
        set(qml_module_files_versions "${CMAKE_MATCH_1}.0")
    else()
        message(FATAL_ERROR
            "No major version found in '${qml_module_version}'.")
    endif()
    if (past_major_versions OR past_major_versions STREQUAL "0")
        foreach (past_major_version ${past_major_versions})
            list(APPEND qml_module_files_versions "${past_major_version}.0")
        endforeach()
    endif()

    # Linting and cachegen can still occur for a target that isn't a qml module,
    # but for such targets, there is no qmldir file to update.
    if(arg_NO_LINT)
        set(no_lint TRUE)
    endif()
    if(arg_NO_CACHEGEN)
        set(no_cachegen TRUE)
    endif()
    if(no_qmldir MATCHES "NOTFOUND" OR arg_NO_QMLDIR_TYPES)
        set(no_qmldir TRUE)
    endif()

    if(NOT no_cachegen AND arg_QML_FILES)

        # Even if we don't generate a qmldir file, it still should be here, manually written.
        # We can pass it unconditionally. If it's not there, qmlcachegen or qmlsc might warn,
        # but that's not fatal.
        set(qmldir_file ${output_dir}/qmldir)

        _qt_internal_genex_getproperty(qmltypes_file ${target} QEXT_QML_MODULE_PLUGIN_TYPES_FILE)
        _qt_internal_genex_getproperty(qmlcachegen   ${target} QEXT_QMLCACHEGEN_EXECUTABLE)
        _qt_internal_genex_getproperty(direct_calls  ${target} QEXT_QMLCACHEGEN_DIRECT_CALLS)
        _qt_internal_genex_getjoinedproperty(arguments ${target}
            QEXT_QMLCACHEGEN_ARGUMENTS "$<SEMICOLON>" "$<SEMICOLON>")
        _qt_internal_genex_getjoinedproperty(import_paths ${target}
            QEXT_QML_IMPORT_PATH "-I$<SEMICOLON>" "$<SEMICOLON>")
        _qt_internal_genex_getjoinedproperty(qrc_resource_args ${target}
            _qt_generated_qrc_files "--resource$<SEMICOLON>" "$<SEMICOLON>")
        get_target_property(target_type ${target} TYPE)
        get_target_property(is_android_executable ${target} _qt_is_android_executable)
        if(target_type STREQUAL "EXECUTABLE" OR is_android_executable)
            # The application binary directory is part of the default import path.
            list(APPEND import_paths -I "$<TARGET_PROPERTY:${target},BINARY_DIR>")
        endif()
        _qt_internal_extend_qml_import_paths(import_paths)
        set(cachegen_args
            ${import_paths}
            -i "${qmldir_file}"
            "$<${have_direct_calls}:--direct-calls>"
            "$<${have_arguments}:${arguments}>"
            ${qrc_resource_args})

        # For direct evaluation in if() below
        get_target_property(cachegen_prop ${target} QEXT_QMLCACHEGEN_EXECUTABLE)
        if(cachegen_prop)
            if(cachegen_prop STREQUAL "qmlcachegen" OR cachegen_prop STREQUAL "qmlsc")
                # If it's qmlcachegen or qmlsc, don't go looking for other programs of that name
                set(qmlcachegen "$<TARGET_FILE:${QEXT_QT_EXPORT_NAMESPACE}::${cachegen_prop}>")
            else()
                find_program(${target}_QMLCACHEGEN ${cachegen_prop})
                if(${target}_QMLCACHEGEN)
                    set(qmlcachegen "${${target}_QMLCACHEGEN}")
                else()
                    message(FATAL_ERROR "Invalid qmlcachegen binary ${cachegen_prop} for ${target}")
                endif()
            endif()
        else()
            set(have_qmlsc "$<TARGET_EXISTS:${QEXT_QT_EXPORT_NAMESPACE}::qmlsc>")
            set(cachegen_name "$<IF:${have_qmlsc},qmlsc,qmlcachegen>")
            set(qmlcachegen "$<TARGET_FILE:${QEXT_QT_EXPORT_NAMESPACE}::${cachegen_name}>")
        endif()
    endif()

    set(non_qml_files)
    set(output_targets)
    set(copied_files)

    # We want to set source file properties in the target's own scope if we can.
    # That's the canonical place the properties will be read from.
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.18)
        set(scope_option TARGET_DIRECTORY ${target})
    else()
        set(scope_option "")
    endif()

    foreach(file_set IN ITEMS QML_FILES RESOURCES)
        foreach(file_src IN LISTS arg_${file_set})
            get_filename_component(file_absolute ${file_src} ABSOLUTE)

            # Store the original files so the project can query them later.
            set_property(TARGET ${target} APPEND PROPERTY
                QT_QML_MODULE_${file_set} ${file_absolute})
            if(prefix_override)
                set_source_files_properties(${file_absolute} ${scope_option}
                    PROPERTIES
                    QT_QML_MODULE_PREFIX_OVERRIDE "${prefix_override}")
            endif()

            # We need to copy the file to the build directory now so that when
            # qmlimportscanner is run in qt6_import_qml_plugins() as part of
            # target finalizers, the files will be there. We need to do this
            # in a way that CMake doesn't create a dependency on the source or it
            # will re-run CMake every time the file is modified. We also don't
            # want to update the file's timestamp if its contents won't change.
            # We still enforce the dependency on the source file by adding a
            # build-time rule. This avoids having to re-run CMake just to re-copy
            # the file.
            qext_internal_get_relative_resource_path_for_file(file_resource_path ${file_src})
            set(file_out ${output_dir}/${file_resource_path})

            # Don't generate or copy the file in an in-source build if the source
            # and destination paths are the same, it will cause a ninja dependency
            # cycle at build time.
            if(NOT file_out STREQUAL file_absolute)
                get_filename_component(file_out_dir ${file_out} DIRECTORY)
                file(MAKE_DIRECTORY ${file_out_dir})

                execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different ${file_absolute} ${file_out})

                add_custom_command(OUTPUT ${file_out}
                    COMMAND ${CMAKE_COMMAND} -E copy ${file_absolute} ${file_out}
                    DEPENDS ${file_absolute}
                    WORKING_DIRECTORY $<TARGET_PROPERTY:${target},SOURCE_DIR>
                    VERBATIM)
                list(APPEND copied_files ${file_out})
            endif()
        endforeach()
    endforeach()

    set(generated_sources_other_scope)
    foreach(qml_file_src IN LISTS arg_QML_FILES)
        # This is to facilitate updating code that used the earlier tech preview
        # API function qt6_target_qml_files()
        if(NOT qml_file_src MATCHES "\\.(js|mjs|qml)$")
            list(APPEND non_qml_files ${qml_file_src})
            continue()
        endif()

        # Mark QML files as source files, so that they do not appear in <Other Locations> in Creator
        # or other IDEs
        set_source_files_properties(${qml_file_src} HEADER_FILE_ONLY ON)
        target_sources(${target} PRIVATE ${qml_file_src})

        get_filename_component(file_absolute ${qml_file_src} ABSOLUTE)
        qext_internal_get_relative_resource_path_for_file(file_resource_path ${qml_file_src})

        # For the tooling steps below, run the tools on the copied qml file in
        # the build directory, not the source directory. This is required
        # because the tools may need to reference imported modules from
        # subdirectories, which would require those subdirectories to have
        # their generated qmldir files present. They also need to use the right
        # resource paths and the source locations might be structured quite
        # differently.

        # Add file to those processed by qmllint
        get_source_file_property(skip_qmllint ${qml_file_src} QT_QML_SKIP_QMLLINT)
        if(NOT no_lint AND NOT skip_qmllint)
            # The set of qml files to run qmllint on may be a subset of the
            # full set of files, so record these in a separate property.
            _qt_internal_target_enable_qmllint(${target})
            set_property(TARGET ${target} APPEND PROPERTY QT_QML_LINT_FILES ${file_absolute})
        endif()

        # Add qml file's type to qmldir
        get_source_file_property(skip_qmldir ${qml_file_src} QT_QML_SKIP_QMLDIR_ENTRY)
        if(NOT no_qmldir AND NOT skip_qmldir)
            get_source_file_property(qml_file_typename ${qml_file_src} QT_QML_SOURCE_TYPENAME)
            if (NOT qml_file_typename)
                get_filename_component(qml_file_ext ${qml_file_src} EXT)
                get_filename_component(qml_file_typename ${qml_file_src} NAME_WE)
            endif()

            # Do not add qmldir entries for lowercase names. Those are not components.
            if (qml_file_typename AND qml_file_typename MATCHES "^[A-Z]")
                if (qml_file_ext AND NOT qml_file_ext STREQUAL ".qml" AND NOT qml_file_ext STREQUAL ".ui.qml"
                        AND NOT qml_file_ext STREQUAL ".js" AND NOT qml_file_ext STREQUAL ".mjs")
                    message(AUTHOR_WARNING
                        "${qml_file_src} has a file extension different from .qml, .ui.qml, .js, "
                        "and .mjs. This leads to unexpected component names.")
                endif()

                # We previously accepted the singular form of this property name
                # during tech preview. Issue a warning for that, but still
                # honor it. The plural form will override it if both are set.
                get_property(have_singular_property SOURCE ${qml_file_src}
                    PROPERTY QT_QML_SOURCE_VERSION SET)
                if(have_singular_property)
                    message(AUTHOR_WARNING
                        "The QT_QML_SOURCE_VERSION source file property has been replaced "
                        "by QT_QML_SOURCE_VERSIONS (i.e. plural rather than singular). "
                        "The singular form will eventually be removed, please update "
                        "the project to use the plural form instead for the file at:\n"
                        "  ${qml_file_src}")
                endif()
                get_source_file_property(qml_file_versions ${qml_file_src} QT_QML_SOURCE_VERSIONS)
                if(NOT qml_file_versions AND have_singular_property)
                    get_source_file_property(qml_file_versions ${qml_file_src} QT_QML_SOURCE_VERSION)
                endif()

                get_source_file_property(qml_file_singleton ${qml_file_src} QT_QML_SINGLETON_TYPE)
                get_source_file_property(qml_file_internal  ${qml_file_src} QT_QML_INTERNAL_TYPE)

                if (NOT qml_file_versions)
                    set(qml_file_versions ${qml_module_files_versions})
                endif()

                set(qmldir_file_contents "")
                foreach(qml_file_version IN LISTS qml_file_versions)
                    if (qml_file_singleton)
                        string(APPEND qmldir_file_contents "singleton ")
                    endif()
                    string(APPEND qmldir_file_contents "${qml_file_typename} ${qml_file_version} ${file_resource_path}\n")
                endforeach()

                if (qml_file_internal)
                    string(APPEND qmldir_file_contents "internal ${qml_file_typename} ${file_resource_path}\n")
                endif()

                set_property(TARGET ${target} APPEND_STRING PROPERTY
                    _qext_internal_qmldir_content "${qmldir_file_contents}")
            endif()
        endif()

        # Run cachegen on the qml file, or if disabled, store the raw qml file in the resources
        get_source_file_property(skip_cachegen ${qml_file_src} QT_QML_SKIP_CACHEGEN)
        if(NOT no_cachegen AND NOT skip_cachegen)
            # We delay this to here to ensure that we only ever enable cachegen
            # after we know there will be at least one file to compile.
            get_target_property(is_cachegen_set_up ${target} _qt_cachegen_set_up)
            if(NOT is_cachegen_set_up)
                _qt_internal_target_enable_qmlcachegen(${target} resource_target ${qmlcachegen})
                list(APPEND output_targets ${resource_target})
            endif()

            # We ensured earlier that arg_PREFIX always ends with "/"
            file(TO_CMAKE_PATH "${arg_PREFIX}${file_resource_path}" file_resource_path)

            set_property(TARGET ${target} APPEND PROPERTY
                QEXT_QML_MODULE_RESOURCE_PATHS ${file_resource_path})

            file(RELATIVE_PATH file_relative ${CMAKE_CURRENT_SOURCE_DIR} ${file_absolute})
            string(REGEX REPLACE "\\.(js|mjs|qml)$" "_\\1" compiled_file ${file_relative})
            string(REGEX REPLACE "[$#?]+" "_" compiled_file ${compiled_file})

                # The file name needs to be unique to work around an Integrity compiler issue.
                # Search for INTEGRITY_SYMBOL_UNIQUENESS in this file for details.
                set(compiled_file
                    "${CMAKE_CURRENT_BINARY_DIR}/.rcc/qmlcache/${target}_${compiled_file}.cpp")
                get_filename_component(out_dir ${compiled_file} DIRECTORY)

                if(CMAKE_GENERATOR STREQUAL "Ninja Multi-Config" AND CMAKE_VERSION VERSION_GREATER_EQUAL "3.20")
                    set(qmlcachegen_cmd "$<COMMAND_CONFIG:${qmlcachegen}>")
                else()
                    set(qmlcachegen_cmd "${qmlcachegen}")
                endif()

                _qt_internal_get_tool_wrapper_script_path(tool_wrapper)
                add_custom_command(
                    OUTPUT ${compiled_file}
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${out_dir}
                    COMMAND
                    ${tool_wrapper}
                    ${qmlcachegen_cmd}
                    --bare
                    --resource-path "${file_resource_path}"
                    ${cachegen_args}
                    -o "${compiled_file}"
                    "${file_absolute}"
                    COMMAND_EXPAND_LISTS
                    DEPENDS
                    ${qmlcachegen_cmd}
                    "${file_absolute}"
                    $<TARGET_PROPERTY:${target},_qt_generated_qrc_files>
                    "$<$<BOOL:${qmltypes_file}>:${qmltypes_file}>"
                    "${qmldir_file}"
                    VERBATIM)

                target_sources(${target} PRIVATE ${compiled_file})
                set_source_files_properties(${compiled_file} PROPERTIES SKIP_AUTOGEN ON)
                # The current scope automatically sees the file as generated, but the
                # target scope may not if it is different. Force it where we can.
                # We will also have to add the generated file to a target in this
                # scope at the end to ensure correct dependencies.
                get_target_property(target_source_dir ${target} SOURCE_DIR)
                if(NOT target_source_dir STREQUAL CMAKE_CURRENT_SOURCE_DIR)
                    list(APPEND generated_sources_other_scope ${compiled_file})
                    if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.18")
                        set_source_files_properties(
                            ${compiled_file}
                            TARGET_DIRECTORY ${target}
                            PROPERTIES
                            SKIP_AUTOGEN TRUE
                            GENERATED TRUE)
                    endif()
                endif()
            endif()
        endforeach()

        if(ANDROID)
            _qt_internal_collect_qml_root_paths("${target}" ${arg_QML_FILES})
        endif()

        if(non_qml_files)
            list(JOIN non_qml_files "\n  " file_list)
            message(WARNING
                "Only .qml, .js or .mjs files should be added with QML_FILES. "
                "The following files should be added with RESOURCES instead:"
                "\n  ${file_list}")
        endif()

        if(copied_files OR generated_sources_other_scope)
            if(CMAKE_VERSION VERSION_LESS 3.19)
                # Called from qt6_add_qml_module() and we know there can only be
                # this one call. With those constraints, we can use a custom target
                # to implement the necessary dependencies to get files copied to the
                # build directory when their source files change.
                add_custom_target(${target}_tooling ALL
                    DEPENDS
                    ${copied_files}
                    ${generated_sources_other_scope})
                add_dependencies(${target} ${target}_tooling)
            else()
                # We could be called multiple times and a custom target can only
                # have file-level dependencies added at the time the target is
                # created. Use an interface library instead, since we can add
                # private sources to those and have the library act as a build
                # system target from CMake 3.19 onward, and we can add the sources
                # progressively over multiple calls.
                if(NOT TARGET ${target}_tooling)
                    add_library(${target}_tooling INTERFACE)
                    add_dependencies(${target} ${target}_tooling)
                endif()
                target_sources(${target}_tooling PRIVATE
                    ${copied_files}
                    ${generated_sources_other_scope})
            endif()
        endif()

        # Batch all the non-compiled qml sources into a single resource for this
        # call. Subsequent calls for the same target will be in their own separate
        # resource file.
        get_target_property(counter ${target} QT_QML_MODULE_RAW_QML_SETS)
        if(NOT counter)
            set(counter 0)
        endif()
        set(resource_name ${target}_raw_qml_${counter})
        set(resource_targets)
        qt6_add_resources(${target} ${resource_name}
            PREFIX ${arg_PREFIX}
            FILES ${arg_QML_FILES} ${arg_RESOURCES}
            OUTPUT_TARGETS resource_targets)
        math(EXPR counter "${counter} + 1")
        set_target_properties(${target} PROPERTIES QT_QML_MODULE_RAW_QML_SETS ${counter})
        list(APPEND output_targets ${resource_targets})

        if(arg_OUTPUT_TARGETS)
            set(${arg_OUTPUT_TARGETS} ${output_targets} PARENT_SCOPE)
        endif()
    endfunction()


    #-----------------------------------------------------------------------------------------------------------------------
    #-----------------------------------------------------------------------------------------------------------------------
    function(_qt_internal_write_deferred_qmldir_file target)
        get_target_property(__qext_qmldir_content ${target} _qext_internal_qmldir_content)
        get_target_property(out_dir ${target} QEXT_QML_MODULE_OUTPUT_DIRECTORY)
        set(qmldir_file "${out_dir}/qmldir")
        set(__qt_qml_macros_module_base_dir ${PROJECT_SOURCE_DIR}/cmake)
        configure_file(${__qt_qml_macros_module_base_dir}/QExtqmldirTemplate.cmake.in ${qmldir_file} @ONLY)
    endfunction()


    #-----------------------------------------------------------------------------------------------------------------------
    #-----------------------------------------------------------------------------------------------------------------------
    function(qt6_add_plugin target)
        qext_internal_get_add_plugin_keywords(opt_args single_args multi_args)

        cmake_parse_arguments(PARSE_ARGV 1 arg "${opt_args}" "${single_args}" "${multi_args}")

        if (arg_UNPARSED_ARGUMENTS)
            message(AUTHOR_WARNING "Unexpected arguments: ${arg_UNPARSED_ARGUMENTS}."
                "If these are source files, consider using target_sources() instead.")
        endif()

        # Handle the inconsistent TYPE/PLUGIN_TYPE keyword naming between commands
        if(arg_TYPE)
            if(arg_PLUGIN_TYPE AND NOT arg_TYPE STREQUAL arg_PLUGIN_TYPE)
                message(FATAL_ERROR
                    "Both TYPE and PLUGIN_TYPE were given and were different. "
                    "Only one of the two should be used.")
            endif()
            message(AUTHOR_WARNING
                "The TYPE keyword is deprecated and will be removed soon. Please use PLUGIN_TYPE instead.")
            set(arg_PLUGIN_TYPE "${arg_TYPE}")
            unset(arg_TYPE)
        endif()

        if(arg_STATIC AND arg_SHARED)
            message(FATAL_ERROR
                "Both STATIC and SHARED options were given. Only one of the two should be used.")
        endif()

        # Explicit option takes priority over the computed default.
        if(arg_STATIC)
            set(create_static_plugin TRUE)
        elseif(arg_SHARED)
            set(create_static_plugin FALSE)
        else()
            # If no explicit STATIC/SHARED option is set, default to the flavor of the Qt build.
            if(QT6_IS_SHARED_LIBS_BUILD)
                set(create_static_plugin FALSE)
            else()
                set(create_static_plugin TRUE)
            endif()
        endif()

        # The default of qext_internal_add_library creates SHARED in a shared Qt build, so we need to
        # be explicit about the MODULE.
        if(create_static_plugin)
            set(type_to_create STATIC)
        else()
            set(type_to_create MODULE)
        endif()

        qext_internal_add_library(${target} ${type_to_create})

        get_target_property(target_type "${target}" TYPE)
        if (target_type STREQUAL "STATIC_LIBRARY")
            target_compile_definitions(${target} PRIVATE QT_STATICPLUGIN)
        endif()

        set(output_name ${target})
        if (arg_OUTPUT_NAME)
            set(output_name ${arg_OUTPUT_NAME})
        endif()
        set_property(TARGET "${target}" PROPERTY OUTPUT_NAME "${output_name}")

        if (ANDROID)
            set_target_properties(${target}
                PROPERTIES
                LIBRARY_OUTPUT_NAME "plugins_${arg_PLUGIN_TYPE}_${output_name}")
        endif()

        # Derive the class name from the target name if it's not explicitly specified.
        set(plugin_class_name "")
        if (NOT "${arg_PLUGIN_TYPE}" STREQUAL "qml_plugin")
            if (NOT arg_CLASS_NAME)
                set(plugin_class_name "${target}")
            else()
                set(plugin_class_name "${arg_CLASS_NAME}")
            endif()
        else()
            # Make sure to set any passed-in class name for qml plugins as well, because it's used for
            # building the qml plugin foo_init object libraries.
            if(arg_CLASS_NAME)
                set(plugin_class_name "${arg_CLASS_NAME}")
            else()
                message(FATAL_ERROR "Qml plugin target has no CLASS_NAME specified: '${target}'")
            endif()
        endif()

        set_target_properties(${target} PROPERTIES QT_PLUGIN_CLASS_NAME "${plugin_class_name}")

        # Create a plugin initializer object library for static plugins.
        # It contains a Q_IMPORT_PLUGIN(QT_PLUGIN_CLASS_NAME) call.
        # Project targets will automatically link to the plugin initializer whenever they link to the plugin target.
        # The plugin init target name is stored in OUTPUT_TARGETS, so projects may install them.
        # Qml plugin inits are handled in Qt6QmlMacros.
        if(NOT "${arg_PLUGIN_TYPE}" STREQUAL "qml_plugin" AND target_type STREQUAL "STATIC_LIBRARY")
            __qt_internal_add_static_plugin_init_object_library("${target}" plugin_init_target)

            if(arg_OUTPUT_TARGETS)
                set(${arg_OUTPUT_TARGETS} ${plugin_init_target} PARENT_SCOPE)
            endif()

            # We don't automatically propagate the plugin init library for Qt provided plugins, because
            # there are 2 other code paths that take care of that, one involving finalizers and the
            # other regular usage requirements.
            if(NOT arg___QT_INTERNAL_NO_PROPAGATE_PLUGIN_INITIALIZER)
                __qt_internal_propagate_object_library("${target}" "${plugin_init_target}")
            endif()
        else()
            if(arg_OUTPUT_TARGETS)
                set(${arg_OUTPUT_TARGETS} "" PARENT_SCOPE)
            endif()
        endif()

        target_compile_definitions(${target} PRIVATE
            QT_PLUGIN
            QT_DEPRECATED_WARNINGS)

        if(target_type STREQUAL "MODULE_LIBRARY")
            if(NOT TARGET qt_internal_plugins)
                add_custom_target(qt_internal_plugins)
            endif()
            add_dependencies(qt_internal_plugins ${target})
        endif()
    endfunction()


    #-----------------------------------------------------------------------------------------------------------------------
    #-----------------------------------------------------------------------------------------------------------------------
    function(qext_internal_compute_qml_plugin_class_name_from_uri uri out_var)
        qext_internal_get_escaped_uri("${uri}" escaped_uri)
        set(${out_var} "${escaped_uri}Plugin" PARENT_SCOPE)
    endfunction()


    #-----------------------------------------------------------------------------------------------------------------------
    #-----------------------------------------------------------------------------------------------------------------------
    function(qext_internal_get_escaped_uri uri out_var)
        string(REGEX REPLACE "[^A-Za-z0-9]" "_" escaped_uri "${uri}")
        set(${out_var} "${escaped_uri}" PARENT_SCOPE)
    endfunction()
