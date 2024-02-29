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
function(qext_internal_clear_repo_known_libraries)
    set(QEXT_REPO_KNOWN_LIBRARIES "" CACHE INTERNAL "Known current repo QExt libraries" FORCE)
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_add_repo_known_library)
    if(NOT (${ARGN} IN_LIST QEXT_REPO_KNOWN_LIBRARIES))
        set(QEXT_REPO_KNOWN_LIBRARIES ${QEXT_REPO_KNOWN_LIBRARIES} ${ARGN}
            CACHE INTERNAL "Known current repo QExt libraries" FORCE)
    endif()
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_get_repo_known_libraries out_var)
    set("${out_var}" "${QEXT_REPO_KNOWN_LIBRARIES}" PARENT_SCOPE)
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
macro(qext_internal_set_qext_known_plugins)
    set(QEXT_KNOWN_PLUGINS ${ARGN} CACHE INTERNAL "Known QExt plugins" FORCE)
endmacro()


#-----------------------------------------------------------------------------------------------------------------------
# Gets the list of all known QExt modules both found and that were built as part of the current project.
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_get_all_known_modules out_var)
    qext_internal_get_repo_known_libraries(repo_known_modules)
    set(known_modules ${QEXT_ALL_MODULES_FOUND_VIA_FIND_PACKAGE} ${repo_known_modules})
    list(REMOVE_DUPLICATES known_modules)
    set("${out_var}" "${known_modules}" PARENT_SCOPE)
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
macro(qext_internal_append_known_libraries_with_tools library)
    if(NOT ${library} IN_LIST QEXT_KNOWN_LIBRARIES_WITH_TOOLS)
        set(QEXT_KNOWN_LIBRARIES_WITH_TOOLS "${QEXT_KNOWN_LIBRARIES_WITH_TOOLS};${library}"
            CACHE INTERNAL "Known QExt libraries with tools" FORCE)
        set(QEXT_KNOWN_LIBRARIES_${library}_TOOLS ""
            CACHE INTERNAL "Known QExt libraries ${library} tools" FORCE)
    endif()
endmacro()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
macro(qext_internal_append_known_library_tool library tool)
    if(NOT ${tool} IN_LIST QEXT_KNOWN_LIBRARIES_${library}_TOOLS)
        list(APPEND QEXT_KNOWN_LIBRARIES_${library}_TOOLS "${tool}")
        set(QEXT_KNOWN_LIBRARIES_${library}_TOOLS "${QEXT_KNOWN_LIBRARIES_${library}_TOOLS}"
            CACHE INTERNAL "Known QExt library ${library} tools" FORCE)
    endif()
endmacro()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
macro(qext_build_repo_begin)
    qext_build_internals_set_up_private_api()

    # Prevent installation in non-prefix builds.
    # We need to associate targets with export names, and that is only possible to do with the
    # install(TARGETS) command. But in a non-prefix build, we don't want to install anything.
    # To make sure that developers don't accidentally run make install, add bail out code to
    # cmake_install.cmake.
    #    if(NOT QEXT_WILL_INSTALL)
    #        # In a top-level build, print a message only in qextbase, which is the first repository.
    #        if(NOT QEXT_SUPERBUILD OR (PROJECT_NAME STREQUAL "QEXTBase"))
    #            install(CODE [[message(FATAL_ERROR
    #                    "QExt was configured as non-prefix build. "
    #                    "Installation is not supported for this arrangement.")]])
    #        endif()
    #
    #        install(CODE [[return()]])
    #    endif()

    #    qext_enable_cmake_languages()

    qext_internal_generate_binary_strip_wrapper()

    #    # Add global docs targets that will work both for per-repo builds, and super builds.
    #    if(NOT TARGET docs)
    #        add_custom_target(docs)
    #        add_custom_target(prepare_docs)
    #        add_custom_target(generate_docs)
    #        add_custom_target(html_docs)
    #        add_custom_target(qch_docs)
    #        add_custom_target(install_html_docs)
    #        add_custom_target(install_qch_docs)
    #        add_custom_target(install_docs)
    #        add_dependencies(html_docs generate_docs)
    #        add_dependencies(docs html_docs qch_docs)
    #        add_dependencies(install_docs install_html_docs install_qch_docs)
    #    endif()

    # Add global qext_plugins, qpa_plugins and qpa_default_plugins convenience custom targets.
    # Internal executables will add a dependency on the qpa_default_plugins target,
    # so that building and running a test ensures it won't fail at runtime due to a missing qpa
    # plugin.
    #    if(NOT TARGET qext_plugins)
    #        add_custom_target(qext_plugins)
    #        add_custom_target(qext_pa_plugins)
    #        add_custom_target(qext_pa_default_plugins)
    #    endif()
    #
    #    string(TOLOWER ${PROJECT_NAME} project_name_lower)
    #
    #    set(qext_repo_targets_name ${project_name_lower})
    #    set(qext_docs_target_name docs_${project_name_lower})
    #    set(qext_docs_prepare_target_name prepare_docs_${project_name_lower})
    #    set(qext_docs_generate_target_name generate_docs_${project_name_lower})
    #    set(qext_docs_html_target_name html_docs_${project_name_lower})
    ##    set(qext_docs_qch_target_name qch_docs_${project_name_lower})
    #    set(qext_docs_install_html_target_name install_html_docs_${project_name_lower})
    #    set(qext_docs_install_qch_target_name install_qch_docs_${project_name_lower})
    #    set(qext_docs_install_target_name install_docs_${project_name_lower})
    #
    #    add_custom_target(${qext_docs_target_name})
    #    add_custom_target(${qext_docs_prepare_target_name})
    #    add_custom_target(${qext_docs_generate_target_name})
    ##    add_custom_target(${qext_docs_qch_target_name})
    #    add_custom_target(${qext_docs_html_target_name})
    #    add_custom_target(${qext_docs_install_html_target_name})
    #    add_custom_target(${qext_docs_install_qch_target_name})
    #    add_custom_target(${qext_docs_install_target_name})
    #
    #    add_dependencies(${qext_docs_generate_target_name} ${qext_docs_prepare_target_name})
    #    add_dependencies(${qext_docs_html_target_name} ${qext_docs_generate_target_name})
    #    add_dependencies(${qext_docs_target_name} ${qext_docs_html_target_name} ${qext_docs_qch_target_name})
    #    add_dependencies(${qext_docs_install_target_name} ${qext_docs_install_html_target_name} ${qext_docs_install_qch_target_name})
    #
    #    # Make top-level prepare_docs target depend on the repository-level prepare_docs_<repo> target.
    #    add_dependencies(prepare_docs ${qext_docs_prepare_target_name})
    #
    #    # Make top-level install_*_docs targets depend on the repository-level install_*_docs targets.
    #    add_dependencies(install_html_docs ${qext_docs_install_html_target_name})
    ##    add_dependencies(install_qch_docs ${qext_docs_install_qch_target_name})
    #
    #    # Add host_tools meta target, so that developrs can easily build only tools and their
    #    # dependencies when working in qextbase.
    #    if(NOT TARGET host_tools)
    #        add_custom_target(host_tools)
    #        add_custom_target(bootstrap_tools)
    #    endif()
    #
    #    # Add benchmark meta target. It's collection of all benchmarks added/registered by
    #    # 'qext_internal_add_benchmark' helper.
    #    if(NOT TARGET benchmark)
    #        add_custom_target(benchmark)
    #    endif()
endmacro()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
macro(qext_build_repo_end)
    if(NOT QEXT_BUILD_STANDALONE_TESTS)
        # Delayed actions on some of the QExt targets:
        include(QEXTPostProcess)

        # Install the repo-specific cmake find modules.
        qext_path_join(__qext_repo_install_dir ${QEXT_CONFIG_INSTALL_DIR} ${QEXT_CMAKE_INSTALL_NAMESPACE})
        qext_path_join(__qext_repo_build_dir ${QEXT_CONFIG_BUILD_DIR} ${QEXT_CMAKE_INSTALL_NAMESPACE})

        if(NOT PROJECT_NAME STREQUAL "QEXTBase")
            if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
                qext_copy_or_install(DIRECTORY cmake/
                    DESTINATION "${__qext_repo_install_dir}"
                    FILES_MATCHING PATTERN "Find*.cmake")
            if(QEXT_SUPERBUILD AND QEXT_WILL_INSTALL)
                file(COPY cmake/
                    DESTINATION "${__qext_repo_build_dir}"
                    FILES_MATCHING PATTERN "Find*.cmake")
        endif()
    endif()
endif()

if(NOT QEXT_SUPERBUILD)
    qext_print_feature_summary()
endif()
endif()

qext_build_internals_add_toplevel_targets()

if(NOT QEXT_SUPERBUILD)
    qext_print_build_instructions()
endif()
endmacro()
