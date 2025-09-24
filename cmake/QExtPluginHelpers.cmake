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
macro(qext_internal_get_add_plugin_keywords option_args single_args multi_args)
    set(${option_args}
        STATIC
        SHARED
        __QEXT_INTERNAL_NO_PROPAGATE_PLUGIN_INITIALIZER)
    set(${single_args}
        # TODO: For backward compatibility / transitional use only, remove once all repos no longer
        # use it
        TYPE
        PLUGIN_TYPE   # Internal use only, may be changed or removed
        CLASS_NAME
        OUTPUT_NAME   # Internal use only, may be changed or removed
        OUTPUT_TARGETS)
    set(${multi_args})
endmacro()

#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
# Note that these are only the keywords that are unique to qext_internal_add_plugin().
# That function also supports the keywords defined by _qext_internal_get_add_plugin_keywords().
macro(qext_internal_get_internal_add_plugin_keywords option_args single_args multi_args)
    set(${option_args}
        EXCEPTIONS
        ALLOW_UNDEFINED_SYMBOLS
        SKIP_INSTALL)
    set(${single_args}
        OUTPUT_DIRECTORY
        INSTALL_DIRECTORY
        ARCHIVE_INSTALL_DIRECTORY
        ${QEXT_DEFAULT_TARGET_INFO_ARGS})
    set(${multi_args}
        ${QEXT_DEFAULT_PRIVATE_ARGS}
        ${QEXT_DEFAULT_PUBLIC_ARGS}
        DEFAULT_IF)
endmacro()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
# This is the main entry point for defining QExt plugins.
# A CMake target is created with the given target.
# The target name should end with "Plugin" so static plugins are linked automatically.
# The PLUGIN_TYPE parameter is needed to place the plugin into the correct plugins/ sub-directory.
function(qext_add_plugin target)
    qext_internal_set_qext_known_plugins("${QEXT_KNOWN_PLUGINS}" "${target}")

    qext_internal_get_add_plugin_keywords(
        public_option_args
        public_single_args
        public_multi_args)
    qext_internal_get_internal_add_plugin_keywords(
        internal_option_args
        internal_single_args
        internal_multi_args)
    set(option_args ${public_option_args} ${internal_option_args})
    set(single_args ${public_single_args} ${internal_single_args})
    set(multi_args  ${public_multi_args}  ${internal_multi_args})

    qext_parse_all_arguments(arg "qext_add_plugin"
        "${option_args}"
        "${single_args}"
        "${multi_args}"
        "${ARGN}")

    # Put this behind a cache option for now. It's too noisy for general use until most repos are updated.
    option(QEXT_WARN_PLUGIN_PUBLIC_KEYWORDS "Warn if a plugin specifies a PUBLIC keyword" ON)
    if(QEXT_WARN_PLUGIN_PUBLIC_KEYWORDS)
        foreach(publicKeyword IN LISTS __default_public_args)
            if(NOT "${arg_${publicKeyword}}" STREQUAL "")
                string(REPLACE "PUBLIC_" "" privateKeyword "${publicKeyword}")
                message(AUTHOR_WARNING
                    "Plugins are not intended to be linked to. "
                    "They should not have any public properties, but ${target} "
                    "sets ${publicKeyword} to the following value:\n"
                    "    ${arg_${publicKeyword}}\n"
                    "Update your project to use ${privateKeyword} instead.\n")
            endif()
        endforeach()
    endif()

    qext_remove_args(plugin_args
        ARGS_TO_REMOVE
        ${internal_option_args}
        ${internal_single_args}
        ${internal_multi_args}
        ALL_ARGS
        ${option_args}
        ${single_args}
        ${multi_args}
        ARGS
        ${ARGN})

    # When creating a static plugin, retrieve the plugin initializer target name, but don't
    # automatically propagate the plugin initializer.
    list(APPEND plugin_args __QEXT_INTERNAL_NO_PROPAGATE_PLUGIN_INITIALIZER OUTPUT_TARGETS plugin_init_target)

    qext_internal_add_plugin(${target} ${plugin_args})
    qext_internal_mark_as_internal_library(${target})

    set(plugin_type "")
    # TODO: Transitional: Remove the TYPE option handling after all repos have been converted to use
    # PLUGIN_TYPE.
    if(arg_TYPE)
        set(plugin_type "${arg_TYPE}")
    elseif(arg_PLUGIN_TYPE)
        set(plugin_type "${arg_PLUGIN_TYPE}")
    endif()

    if((NOT plugin_type STREQUAL "qml_plugin") AND (NOT target MATCHES "(.*)Plugin$"))
        message(AUTHOR_WARNING "The internal plugin target name '${target}' should end with the 'Plugin' suffix.")
    endif()

    qext_get_sanitized_plugin_type("${plugin_type}" plugin_type_escaped)

    set(output_directory_default "${QEXT_BUILD_DIR}/${QEXT_INSTALL_PLUGINSDIR}/${plugin_type}")
    set(install_directory_default "${QEXT_INSTALL_PLUGINSDIR}/${plugin_type}")

    qext_internal_check_directory_or_type(OUTPUT_DIRECTORY "${arg_OUTPUT_DIRECTORY}" "${plugin_type}"
        "${output_directory_default}" output_directory)
    if (NOT arg_SKIP_INSTALL)
        qext_internal_check_directory_or_type(INSTALL_DIRECTORY "${arg_INSTALL_DIRECTORY}"
            "${plugin_type}"
            "${install_directory_default}" install_directory)
        set(archive_install_directory ${arg_ARCHIVE_INSTALL_DIRECTORY})
        if (NOT archive_install_directory AND install_directory)
            set(archive_install_directory "${install_directory}")
        endif()
    endif()

    qext_set_target_info_properties(${target} ${ARGN})

    set_target_properties(${target} PROPERTIES
        _qext_package_version "${PROJECT_VERSION}")
    set_property(TARGET ${target}
        APPEND PROPERTY
        EXPORT_PROPERTIES "_qext_package_version")

    # Override the OUTPUT_NAME that qext_add_plugin() set, we need to account for
    # QEXT_LIBINFIX, which is specific to building Qt.
    # Make sure the Qt6 plugin library names are like they were in Qt5 qmake land.
    # Whereas the Qt6 CMake target names are like the Qt5 CMake target names.
    get_target_property(output_name ${target} OUTPUT_NAME)
    set_property(TARGET "${target}" PROPERTY OUTPUT_NAME "${output_name}${QEXT_LIBINFIX}")

    # Add a custom target with the Qt5 qmake name for a more user friendly ninja experience.
    if(arg_OUTPUT_NAME AND NOT TARGET "${output_name}")
        # But don't create such a target if it would just differ in case from "${target}"
        # and we're not using Ninja. See https://gitlab.kitware.com/cmake/cmake/-/issues/21915
        string(TOUPPER "${output_name}" uc_output_name)
        string(TOUPPER "${target}" uc_target)
        if(NOT uc_output_name STREQUAL uc_target OR CMAKE_GENERATOR MATCHES "^Ninja")
            add_custom_target("${output_name}")
            add_dependencies("${output_name}" "${target}")
        endif()
    endif()

    qext_set_common_target_properties("${target}")
    qext_internal_add_target_aliases("${target}")
    qext_skip_warnings_are_errors_when_repo_unclean("${target}")
    qext_internal_apply_strict_cpp("${target}")

    set_target_properties("${target}" PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${output_directory}"
        RUNTIME_OUTPUT_DIRECTORY "${output_directory}"
        ARCHIVE_OUTPUT_DIRECTORY "${output_directory}"
        QEXT_PLUGIN_TYPE "${plugin_type_escaped}"
        # Save the non-sanitized plugin type values for qmake consumption via .pri files.
        QEXT_QMAKE_PLUGIN_TYPE "${plugin_type}")

    qext_handle_multi_config_output_dirs("${target}")

    qext_internal_library_deprecation_level(deprecation_define)

    qt_autogen_tools_initial_setup(${target})

    unset(plugin_install_package_suffix)

    # The generic plugins should be enabled by default.
    # But platform plugins should always be disabled by default, and only one is enabled
    # based on the platform (condition specified in arg_DEFAULT_IF).
    if(plugin_type_escaped STREQUAL "platforms")
        set(_default_plugin 0)
    else()
        set(_default_plugin 1)
    endif()

    if(DEFINED arg_DEFAULT_IF)
        if(${arg_DEFAULT_IF})
            set(_default_plugin 1)
        else()
            set(_default_plugin 0)
        endif()
    endif()

    # Save the Qt module in the plug-in's properties and vice versa
    if(NOT plugin_type_escaped STREQUAL "qml_plugin")
#        message(output_directory=${output_directory})
        # Ignore any CMAKE_INSTALL_RPATH and set a better default RPATH on platforms that support it, if allowed.
        # Projects will often set CMAKE_INSTALL_RPATH for executables or backing libraries, but forget about plugins.
        if(NOT WIN32 AND NOT QT_NO_PLUGIN_RPATH)
            # Construct a relative path from a default install location
            # (assumed to be ${QEXT_INSTALL_PLUGINSDIR}/${plugin_type}) to ${CMAKE_INSTALL_LIBDIR}.
            # This would be applicable for Apple too (although unusual) if this is a bare install
            # (i.e. not part of an app bundle).
            string(REPLACE "/" ";" path "${QEXT_INSTALL_PLUGINSDIR}/${plugin_type}")
            list(LENGTH path path_count)
            string(REPEAT "../" ${path_count} rel_path)
            string(APPEND rel_path "${CMAKE_INSTALL_LIBDIR}")
#            message(rel_path=${rel_path})
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

        qext_internal_get_library_for_plugin("${target}" "${plugin_type_escaped}" qext_library)

        set(qext_library_target "${QEXT_CMAKE_EXPORT_NAMESPACE}::${qext_library}")
        if(NOT TARGET "${qext_library_target}")
            message(FATAL_ERROR "Failed to associate Qt plugin with Qt module. ${qext_library_target} is not a known CMake target")
        endif()

        set_target_properties("${target}" PROPERTIES QEXT_MODULE "${qext_library}")
        set(plugin_install_package_suffix "${qext_library}")


        get_target_property(aliased_target ${qext_library_target} ALIASED_TARGET)
        if(aliased_target)
            set(qext_library_target ${aliased_target})
        endif()
        get_target_property(is_imported_qext_library ${qext_library_target} IMPORTED)

        # Associate plugin with its Qt module when both are both built in the same repository.
        # Check that by comparing the PROJECT_NAME of each.
        # This covers auto-linking of the majority of plugins to executables and in-tree tests.
        # Linking of plugins in standalone tests (when the Qt module will be an imported target)
        # is handled instead by the complicated genex logic in QtModulePlugins.cmake.in.
        set(is_plugin_and_module_in_same_project FALSE)
        if(NOT is_imported_qext_library)
            # This QEXT_PLUGINS assignment is only used by QtPostProcessHelpers to decide if a
            # QtModulePlugins.cmake file should be generated (which only happens in static builds).
            set_property(TARGET "${qext_library_target}" APPEND PROPERTY QEXT_PLUGINS "${target}")

            get_target_property(module_source_dir ${qext_library_target} SOURCE_DIR)
            get_directory_property(module_project_name
                DIRECTORY ${module_source_dir}
                DEFINITION PROJECT_NAME)
            if(module_project_name STREQUAL PROJECT_NAME)
                set(is_plugin_and_module_in_same_project TRUE)
            endif()

            # When linking static plugins with the special logic in qext_internal_add_executable,
            # make sure to skip non-default plugins.
            if(is_plugin_and_module_in_same_project AND _default_plugin)
                set_property(TARGET ${qext_library_target} APPEND PROPERTY
                    _qext_initial_repo_plugins
                    "${target}")
                set_property(TARGET ${qext_library_target} APPEND PROPERTY
                    _qext_initial_repo_plugin_class_names
                    "$<TARGET_PROPERTY:${target},QT_PLUGIN_CLASS_NAME>")
            endif()
        endif()

        # Associate plugin with its Qt module when the plugin is built in the current repository
        # but the module is built in a different repository (qtsvg's QSvgPlugin associated with
        # qtbase's QtGui).
        # The association is done in a separate property, to ensure that reconfiguring in-tree tests
        # in qtbase doesn't accidentally cause linking to a plugin from a previously built qtsvg.
        # Needed for in-tree tests like in qtsvg, qtimageformats.
        # This is done for each Qt module regardless if it's an imported target or not, to handle
        # both per-repo and top-level builds (in per-repo build of qtsvg QtGui is imported, in a
        # top-level build Gui is not imported, but in both cases qtsvg tests need to link to
        # QSvgPlugin).
        #
        # TODO: Top-level in-tree tests and qdeclarative per-repo in-tree tests that depend on
        #       static Qml plugins won't work due to the requirement of running qmlimportscanner
        #       at configure time, but qmlimportscanner is not built at that point. Moving the
        #       execution of qmlimportscanner to build time is non-trivial because qmlimportscanner
        #       not only generates a cpp file to compile but also outputs a list of static plugins
        #       that should be linked and there is no straightforward way to tell CMake to link
        #       against a list of libraries that was discovered at build time (apart from
        #       response files, which apparently might not work on all platforms).
        #       qmake doesn't have this problem because each project is configured separately so
        #       qmlimportscanner is always built by the time it needs to be run for a test.
        if(NOT is_plugin_and_module_in_same_project AND _default_plugin)
            string(MAKE_C_IDENTIFIER "${PROJECT_NAME}" current_project_name)
            set(prop_prefix "_qext_repo_${current_project_name}")
            set_property(TARGET ${qext_library_target} APPEND PROPERTY
                ${prop_prefix}_plugins "${target}")
            set_property(TARGET ${qext_library_target} APPEND PROPERTY
                ${prop_prefix}_plugin_class_names
                "$<TARGET_PROPERTY:${target},QT_PLUGIN_CLASS_NAME>")
        endif()
    endif()

    # Change the configuration file install location for qml plugins into the Qml package location.
    if(plugin_type_escaped STREQUAL "qml_plugin" AND TARGET "${QEXT_CMAKE_INSTALL_NAMESPACE}::Qml")
        set(plugin_install_package_suffix "Qml/QmlPlugins")
    endif()

    # Save the install package suffix as a property, so that the Dependencies file is placed
    # in the correct location.
    if(plugin_install_package_suffix)
        set_target_properties("${target}" PROPERTIES
            _qext_plugin_install_package_suffix "${plugin_install_package_suffix}")
    endif()

    if(TARGET qext_plugins)
        add_dependencies(qext_plugins "${target}")
    endif()
    if(plugin_type STREQUAL "platforms")
        if(TARGET qpa_plugins)
            add_dependencies(qpa_plugins "${target}")
        endif()

        if(_default_plugin AND TARGET qpa_default_plugins)
            add_dependencies(qpa_default_plugins "${target}")
        endif()
    endif()

    set_property(TARGET "${target}" PROPERTY QEXT_DEFAULT_PLUGIN "${_default_plugin}")
    set_property(TARGET "${target}" APPEND PROPERTY EXPORT_PROPERTIES "QT_PLUGIN_CLASS_NAME;QEXT_PLUGIN_TYPE;QEXT_MODULE;QEXT_DEFAULT_PLUGIN")

    set(private_includes
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_BINARY_DIR}"
        # For the syncqt headers
        "$<BUILD_INTERFACE:${QEXT_BUILD_DIR}/include>"
        ${arg_INCLUDE_DIRECTORIES})

    set(public_includes
        ${arg_PUBLIC_INCLUDE_DIRECTORIES})

    qext_internal_extend_target("${target}"
        SOURCES ${arg_SOURCES}
        INCLUDE_DIRECTORIES
        ${private_includes}
        PUBLIC_INCLUDE_DIRECTORIES
        ${public_includes}
        LIBRARIES ${arg_LIBRARIES}
        PUBLIC_LIBRARIES ${arg_PUBLIC_LIBRARIES}
        DEFINES
        ${arg_DEFINES}
        ${deprecation_define}
        PUBLIC_DEFINES
        ${arg_PUBLIC_DEFINES}
        FEATURE_DEPENDENCIES ${arg_FEATURE_DEPENDENCIES}
        DBUS_ADAPTOR_SOURCES "${arg_DBUS_ADAPTOR_SOURCES}"
        DBUS_ADAPTOR_FLAGS "${arg_DBUS_ADAPTOR_FLAGS}"
        DBUS_INTERFACE_SOURCES "${arg_DBUS_INTERFACE_SOURCES}"
        DBUS_INTERFACE_FLAGS "${arg_DBUS_INTERFACE_FLAGS}"
        COMPILE_OPTIONS ${arg_COMPILE_OPTIONS}
        PUBLIC_COMPILE_OPTIONS ${arg_PUBLIC_COMPILE_OPTIONS}
        LINK_OPTIONS ${arg_LINK_OPTIONS}
        PUBLIC_LINK_OPTIONS ${arg_PUBLIC_LINK_OPTIONS}
        MOC_OPTIONS ${arg_MOC_OPTIONS}
        ENABLE_AUTOGEN_TOOLS ${arg_ENABLE_AUTOGEN_TOOLS}
        DISABLE_AUTOGEN_TOOLS ${arg_DISABLE_AUTOGEN_TOOLS})
    return()

    qext_internal_add_repo_local_defines("${target}")

    qext_internal_set_ignore_warning_flags("${target}")
    qext_internal_set_exceptions_flags("${target}" ${arg_EXCEPTIONS})


    set(qext_libs_private "")
    qext_internal_get_all_known_modules(known_modules)
    foreach(it ${known_modules})
        list(FIND arg_LIBRARIES "QExt::${it}Private" pos)
        if(pos GREATER -1)
            list(APPEND qext_libs_private "QExt::${it}Private")
        endif()
    endforeach()

    qext_register_target_dependencies("${target}" "${arg_PUBLIC_LIBRARIES}" "${qext_libs_private}")
    if (NOT BUILD_SHARED_LIBS)

        # There's no point in generating pri files for qml plugins. We didn't do it in Qt5 times.
        # if(NOT plugin_type_escaped STREQUAL "qml_plugin")
        #     qext_generate_plugin_pri_file("${target}" pri_file)
        # endif()

        if(qext_library_target)
            qext_internal_link_internal_platform_for_object_library("${plugin_init_target}")
        endif()
    endif()

    if (NOT arg_SKIP_INSTALL)
        # Handle creation of cmake files for consumers of find_package().
        # If we are part of a Qt module, the plugin cmake files are installed as part of that
        # module.
        # For qml plugins, they are all installed into the QtQml package location for automatic
        # discovery.
        if(plugin_install_package_suffix)
            set(path_suffix "${QEXT_CMAKE_INSTALL_NAMESPACE}${plugin_install_package_suffix}")
        else()
            set(path_suffix "${QEXT_CMAKE_INSTALL_NAMESPACE}${target}")
        endif()

        qext_path_join(config_build_dir ${QEXT_CONFIG_BUILD_DIR} ${path_suffix})
        qext_path_join(config_install_dir ${QEXT_CONFIG_INSTALL_DIR} ${path_suffix})

        qext_internal_export_additional_targets_file(
            TARGETS ${target} ${plugin_init_target}
            EXPORT_NAME_PREFIX ${QEXT_CMAKE_INSTALL_NAMESPACE}${target}
            CONFIG_INSTALL_DIR "${config_install_dir}")

        qext_internal_get_min_new_policy_cmake_version(min_new_policy_version)
        qext_internal_get_max_new_policy_cmake_version(max_new_policy_version)
        configure_package_config_file(
            "${QEXT_CMAKE_DIR}/QExtPluginConfig.cmake.in"
            "${config_build_dir}/${QEXT_CMAKE_INSTALL_NAMESPACE}${target}Config.cmake"
            INSTALL_DESTINATION "${config_install_dir}")
        write_basic_package_version_file(
            "${config_build_dir}/${QEXT_CMAKE_INSTALL_NAMESPACE}${target}ConfigVersionImpl.cmake"
            VERSION ${PROJECT_VERSION}
            COMPATIBILITY AnyNewerVersion)
        qext_internal_write_qext_package_version_file(
            "${QEXT_CMAKE_INSTALL_NAMESPACE}${target}"
            "${config_build_dir}/${QEXT_CMAKE_INSTALL_NAMESPACE}${target}ConfigVersion.cmake")

        qext_install(FILES
            "${config_build_dir}/${QEXT_CMAKE_INSTALL_NAMESPACE}${target}Config.cmake"
            "${config_build_dir}/${QEXT_CMAKE_INSTALL_NAMESPACE}${target}ConfigVersion.cmake"
            "${config_build_dir}/${QEXT_CMAKE_INSTALL_NAMESPACE}${target}ConfigVersionImpl.cmake"
            DESTINATION "${config_install_dir}"
            COMPONENT ${QEXT_INSTALL_COMPONENT_NAME})
        if(pri_file)
            qext_install(FILES "${pri_file}" DESTINATION "${QEXT_INSTALL_MKSPECSDIR}/modules")
        endif()

        # Make the export name of plugins be consistent with modules, so that
        # qext_add_resource adds its additional targets to the same export set in a static Qt build.
        set(export_name "${QEXT_CMAKE_INSTALL_NAMESPACE}${target}Targets")
        qext_install(TARGETS
            "${target}"
            ${plugin_init_target}
            EXPORT ${export_name}
            RUNTIME DESTINATION "${install_directory}"
            LIBRARY DESTINATION "${install_directory}"
            OBJECTS DESTINATION "${install_directory}"
            ARCHIVE DESTINATION "${archive_install_directory}")
        qext_install(EXPORT ${export_name}
            NAMESPACE ${QEXT_CMAKE_EXPORT_NAMESPACE}::
            DESTINATION "${config_install_dir}")
        if(BUILD_SHARED_LIBS)
            qext_apply_rpaths(TARGET "${target}" INSTALL_PATH "${install_directory}" RELATIVE_RPATH)
            qext_internal_apply_staging_prefix_build_rpath_workaround()
        endif()
    endif()

    if (NOT arg_ALLOW_UNDEFINED_SYMBOLS)
        ### fixme: cmake is missing a built-in variable for this. We want to apply it only to
        # modules and plugins that belong to Qt.
        qext_internal_add_link_flags_no_undefined("${target}")
    endif()

    qext_internal_add_linker_version_script(${target})
    set(finalizer_extra_args "")
    if(NOT arg_SKIP_INSTALL)
        list(APPEND finalizer_extra_args INSTALL_PATH "${install_directory}")
    endif()
    qext_add_list_file_finalizer(qext_finalize_plugin ${target} ${finalizer_extra_args})

    if(NOT arg_SKIP_INSTALL)
        qext_enable_separate_debug_info(${target} "${install_directory}")
        qext_internal_install_pdb_files(${target} "${install_directory}")
    endif()
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_finalize_plugin target)
    cmake_parse_arguments(arg "" "INSTALL_PATH" "" ${ARGN})
    if(WIN32 AND BUILD_SHARED_LIBS)
        _qext_internal_generate_win32_rc_file("${target}")
    endif()

    # Generate .prl files for plugins of static Qt builds.
    if(NOT BUILD_SHARED_LIBS)
        if(arg_INSTALL_PATH)
            qext_generate_prl_file(${target} "${arg_INSTALL_PATH}")
        endif()
    endif()
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_get_sanitized_plugin_type plugin_type out_var)
    # Used to handle some edge cases such as platforms/darwin
    string(REGEX REPLACE "[-/]" "_" plugin_type "${plugin_type}")
    set("${out_var}" "${plugin_type}" PARENT_SCOPE)
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
# Utility function to find the module to which a plug-in belongs.
function(qext_internal_get_library_for_plugin target target_type out_var)
    qext_internal_get_all_known_modules(known_modules)

    qext_get_sanitized_plugin_type("${target_type}" target_type)
#    message(target_type=${target_type})
#    message(known_modules=${known_modules})
    foreach(module ${known_modules})
        if(TARGET ${module})
            get_target_property(module_type "${QEXT_CMAKE_EXPORT_NAMESPACE}::${module}" TYPE)
            # Assuming interface libraries can't have plugins. Otherwise we'll need to fix the property
            # name, because the current one would be invalid for interface libraries.
            if(module_type STREQUAL "INTERFACE_LIBRARY")
                continue()
            endif()

            get_target_property(plugin_types "${QEXT_CMAKE_EXPORT_NAMESPACE}::${module}" LIBRARY_PLUGIN_TYPES)
#            message(plugin_types=${plugin_types})
            if(plugin_types AND target_type IN_LIST plugin_types)
                set("${out_var}" "${module}" PARENT_SCOPE)
                return()
            endif()
        endif()
    endforeach()
    message(FATAL_ERROR "The plug-in '${target}' does not belong to any QExt library.")
endfunction()



#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_add_plugin target)
    qext_internal_get_add_plugin_keywords(opt_args single_args multi_args)

    cmake_parse_arguments(PARSE_ARGV 1 arg "${opt_args}" "${single_args}" "${multi_args}")

    if (arg_UNPARSED_ARGUMENTS)
        message(AUTHOR_WARNING "Unexpected arguments: ${arg_UNPARSED_ARGUMENTS}. "
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
        message(FATAL_ERROR "Both STATIC and SHARED options were given. Only one of the two should be used.")
    endif()

    # Explicit option takes priority over the computed default.
    # message(arg_STATIC=${arg_STATIC})
    # message(arg_SHARED=${arg_SHARED})
    if(arg_STATIC)
        set(create_static_plugin TRUE)
    elseif(arg_SHARED)
        set(create_static_plugin FALSE)
    else()
        # If no explicit STATIC/SHARED option is set, default to the flavor of the Qt build.
        if(QEXT_BUILD_SHARED_LIBS)
            set(create_static_plugin FALSE)
        else()
            set(create_static_plugin TRUE)
        endif()
    endif()
    # message(create_static_plugin=${create_static_plugin})

    # The default of _qext_internal_add_library creates SHARED in a shared Qt build, so we need to
    # be explicit about the MODULE.
    if(create_static_plugin)
        set(type_to_create STATIC)
    else()
        set(type_to_create MODULE)
    endif()

    # message(type_to_create=${type_to_create})
    qext_internal_add_library(${target} ${type_to_create})

    get_target_property(target_type "${target}" TYPE)
    if (target_type STREQUAL "STATIC_LIBRARY")
        target_compile_definitions(${target} PRIVATE QEXT_STATICPLUGIN)
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
        __qext_internal_add_static_plugin_init_object_library("${target}" plugin_init_target)

        if(arg_OUTPUT_TARGETS)
            set(${arg_OUTPUT_TARGETS} ${plugin_init_target} PARENT_SCOPE)
        endif()

        # We don't automatically propagate the plugin init library for Qt provided plugins, because there are 2 other
        # code paths that take care of that, one involving finalizers and the other regular usage requirements.
        if(NOT arg___QEXT_INTERNAL_NO_PROPAGATE_PLUGIN_INITIALIZER)
            __qext_internal_propagate_object_library("${target}" "${plugin_init_target}")
        endif()
    else()
        if(arg_OUTPUT_TARGETS)
            set(${arg_OUTPUT_TARGETS} "" PARENT_SCOPE)
        endif()
    endif()

    target_compile_definitions(${target} PRIVATE
        QEXT_PLUGIN
        QEXT_DEPRECATED_WARNINGS)

    if(target_type STREQUAL "MODULE_LIBRARY")
        if(NOT TARGET qext_internal_plugins)
            add_custom_target(qext_internal_plugins)
        endif()
        add_dependencies(qext_internal_plugins ${target})
    endif()
endfunction()



#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
# Create an object library that initializes a static qt plugin.
#
# The object library contains a single generated C++ file that calls Q_IMPORT_PLUGIN(plugin_class).
# The object library is exported as part of the Qt build and consumed by user applications
# that link to qt plugins.
#
# The created target name is assigned to 'out_var_plugin_init_target'.
function(__qext_internal_add_static_plugin_init_object_library
        plugin_target
        out_var_plugin_init_target)

    _qext_internal_get_plugin_import_macro(${plugin_target} import_macro)
    _qext_internal_get_plugin_include_prelude(include_prelude)
    set(import_content "${include_prelude}${import_macro}")

    string(MAKE_C_IDENTIFIER "${plugin_target}" plugin_target_identifier)
    set(generated_qext_plugin_file_name
        "${CMAKE_CURRENT_BINARY_DIR}/${plugin_target_identifier}_init.cpp")

    file(GENERATE
        OUTPUT "${generated_qext_plugin_file_name}"
        CONTENT "${import_content}"
    )

# CMake versions earlier than 3.18.0 can't find the generated file for some reason,
# failing at generation phase.
# Explicitly marking the file as GENERATED fixes the issue.
set_source_files_properties("${generated_qext_plugin_file_name}" PROPERTIES GENERATED TRUE)

_qext_internal_get_static_plugin_init_target_name("${plugin_target}" plugin_init_target)

qext_add_library("${plugin_init_target}" OBJECT "${generated_qext_plugin_file_name}")
target_link_libraries(${plugin_init_target}
    PRIVATE

    # Core provides the symbols needed by Q_IMPORT_PLUGIN.
    ${QEXT_QT_EXPORT_NAMESPACE}::Core
)

set_property(TARGET ${plugin_init_target} PROPERTY _is_qt_plugin_init_target TRUE)
set_property(TARGET ${plugin_init_target} APPEND PROPERTY
    EXPORT_PROPERTIES _is_qt_plugin_init_target
)

set(${out_var_plugin_init_target} "${plugin_init_target}" PARENT_SCOPE)
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
# Generates C++ import macro source code for given plugin
function(_qext_internal_get_plugin_import_macro plugin_target out_var)
    set(plugin_target_prefixed "${QEXT_QT_EXPORT_NAMESPACE}::${plugin_target}")

    # Query the class name of plugin targets prefixed with a Qt namespace and without, this is
    # needed to support plugin object initializers created by user projects.
    set(class_name"")
    set(class_name_prefixed "")

    if(TARGET ${plugin_target})
        get_target_property(class_name "${plugin_target}" QT_PLUGIN_CLASS_NAME)
    endif()

    if(TARGET ${plugin_target_prefixed})
        get_target_property(class_name_prefixed "${plugin_target_prefixed}" QT_PLUGIN_CLASS_NAME)
    endif()

    if(NOT class_name AND NOT class_name_prefixed)
        message(FATAL_ERROR "No QT_PLUGIN_CLASS_NAME value on target: '${plugin_target}'")
    endif()

    # Qt prefixed target takes priority.
    if(class_name_prefixed)
        set(class_name "${class_name_prefixed}")
    endif()

    set(${out_var} "Q_IMPORT_PLUGIN(${class_name})" PARENT_SCOPE)
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(_qext_internal_get_plugin_include_prelude out_var)
    # set(${out_var} "#include <QtPlugin>\n" PARENT_SCOPE)
endfunction()



#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------

# Get target name of object library which is used to initialize a qt plugin.
function(_qext_internal_get_static_plugin_init_target_name plugin_target out_var)
    # Keep the target name short, so we don't hit long path issues on Windows.
    set(plugin_init_target "${plugin_target}_init")

    set(${out_var} "${plugin_init_target}" PARENT_SCOPE)
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_finalize_target target)
    if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.19")
        cmake_language(DEFER GET_CALL_IDS ids_queued)
        get_directory_property(wait_for_ids qext_internal_finalizers_wait_for_ids)
        while(wait_for_ids)
            list(GET wait_for_ids 0 id_to_wait_for)
            if(id_to_wait_for IN_LIST ids_queued)
                # Something else needs to run before we finalize targets.
                # Try again later by re-deferring ourselves, which effectively
                # puts us at the end of the current list of deferred actions.
                cmake_language(EVAL CODE "cmake_language(DEFER CALL ${CMAKE_CURRENT_FUNCTION} ${ARGV})")
                set_directory_properties(PROPERTIES
                    qext_internal_finalizers_wait_for_ids "${wait_for_ids}"
                )
                return()
            endif()
            list(POP_FRONT wait_for_ids)
        endwhile()
        # No other deferred tasks to wait for
        set_directory_properties(PROPERTIES qext_internal_finalizers_wait_for_ids "")
    endif()

    if(NOT TARGET "${target}")
        message(FATAL_ERROR "No target '${target}' found in current scope.")
    endif()

    get_target_property(target_type ${target} TYPE)
    get_target_property(is_android_executable "${target}" _qt_is_android_executable)

    if(target_type STREQUAL "EXECUTABLE" OR is_android_executable)
        qext_internal_finalize_executable(${ARGV})
    endif()
endfunction()



#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_apply_strict_cpp target)
    # Disable C, Obj-C and C++ GNU extensions aka no "-std=gnu++11".
    # Similar to mkspecs/features/default_post.prf's CONFIG += strict_cpp.
    # Allow opt-out via variable.
    if(NOT QT_ENABLE_CXX_EXTENSIONS)
        get_target_property(target_type "${target}" TYPE)
        if(NOT target_type STREQUAL "INTERFACE_LIBRARY")
            set_target_properties("${target}" PROPERTIES
                CXX_EXTENSIONS OFF
                C_EXTENSIONS OFF
                OBJC_EXTENSIONS OFF
                OBJCXX_EXTENSIONS OFF)
        endif()
    endif()
endfunction()
