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
# qext_add_test finction
#-----------------------------------------------------------------------------------------------------------------------
function(qext_add_test NAME)
    set(multiValueArgs SOURCES INCLUDE_DIRECTORIES LIBRARIES OUTPUT_DIRECTORY DEFINES)
    cmake_parse_arguments(ARG "" "" "${multiValueArgs}" "${ARGN}")

    if ("x${ARG_OUTPUT_DIRECTORY}" STREQUAL "x")
        set(ARG_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
    endif ()

    if (ARG_SOURCES)
        set(private_includes
                ${CMAKE_CURRENT_SOURCE_DIR}
                ${CMAKE_CURRENT_BINARY_DIR}
                ${ARG_INCLUDE_DIRECTORIES})

        add_executable(${NAME} ${ARG_SOURCES})

        set_target_properties(${NAME} PROPERTIES
                ARCHIVE_OUTPUT_DIRECTORY ${ARG_OUTPUT_DIRECTORY}
                RUNTIME_OUTPUT_DIRECTORY ${ARG_OUTPUT_DIRECTORY}
                LIBRARY_OUTPUT_DIRECTORY ${ARG_OUTPUT_DIRECTORY})

        target_link_libraries(${NAME} PRIVATE ${ARG_LIBRARIES})

        target_include_directories(${NAME} PRIVATE
                ${CMAKE_CURRENT_BINARY_DIR}
                ${CMAKE_CURRENT_SOURCE_DIR}
                ${ARG_INCLUDE_DIRECTORIES})

        target_compile_definitions(${NAME} PRIVATE ${ARG_DEFINES})

        set_property(TARGET ${TEST_NAME} PROPERTY INTERFACE_C_EXTENSIONS OFF)
    endif ()
    add_test(NAME ${NAME} COMMAND ${NAME} WORKING_DIRECTORY ${ARG_OUTPUT_DIRECTORY})
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
# This function creates a CMake test target with the specified name for use with CTest.
#
# All tests are wrapped with cmake script that supports TESTARGS and TESTRUNNER environment
# variables handling. Endpoint wrapper may be used standalone as cmake script to run tests e.g.:
# TESTARGS="-o result.xml,junitxml" TESTRUNNER="testrunner --arg" ./tst_simpleTestWrapper.cmake
# On non-UNIX machine you may need to use 'cmake -P' explicitly to execute wrapper.
# You may avoid test wrapping by either passing NO_WRAPPER option or switching QEXT_NO_TEST_WRAPPERS
# to ON. This is helpful if you want to use internal CMake tools within tests, like memory or
# sanitizer checks. See https://cmake.org/cmake/help/v3.19/manual/ctest.1.html#ctest-memcheck-step
# Arguments:
#    BUILTIN_TESTDATA the option forces adding the provided TESTDATA to resources.
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_add_test name)
    # EXCEPTIONS is a noop as they are enabled by default.
    set(optional_args
            RUN_SERIAL
            EXCEPTIONS
            NO_EXCEPTIONS
            GUI
            CATCH
            LOWDPI
            NO_WRAPPER
            BUILTIN_TESTDATA)
    set(single_value_args
            OUTPUT_DIRECTORY
            WORKING_DIRECTORY
            TIMEOUT
            VERSION)
    set(multi_value_args
            TESTDATA
            QEXT_TEST_SERVER_LIST
            ${QEXT_DEFAULT_PRIVATE_ARGS}
            ${QEXT_DEFAULT_PUBLIC_ARGS})
    qext_parse_all_arguments(arg "qext_add_test"
            "${optional_args}"
            "${single_value_args}"
            "${multi_value_args}"
            ${ARGN})

    if (NOT arg_OUTPUT_DIRECTORY)
        set(arg_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
    endif ()

    # QExt modules get compiled without exceptions enabled by default.
    # However, testcases should be still built with exceptions.
    set(exceptions_text "EXCEPTIONS")
    if (${arg_NO_EXCEPTIONS})
        set(exceptions_text "")
    endif ()

    if (${arg_GUI})
        set(gui_text "GUI")
    endif ()

    if (arg_VERSION)
        set(version_arg VERSION "${arg_VERSION}")
    endif ()

    # Handle cases where we have a qml test without source files
    if (arg_SOURCES)
        set(private_includes
                "${CMAKE_CURRENT_SOURCE_DIR}"
                "${CMAKE_CURRENT_BINARY_DIR}"
                "$<BUILD_INTERFACE:${QEXT_BUILD_DIR}/include>"
                ${arg_INCLUDE_DIRECTORIES})

        qext_add_executable("${name}"
                ${exceptions_text}
                ${gui_text}
                ${version_arg}
                NO_INSTALL
                OUTPUT_DIRECTORY "${arg_OUTPUT_DIRECTORY}"
                SOURCES "${arg_SOURCES}"
                INCLUDE_DIRECTORIES
                ${private_includes}
                DEFINES
                ${arg_DEFINES}
                PUBLIC_LIBRARIES ${QEXT_CMAKE_EXPORT_NAMESPACE}::Core ${arg_PUBLIC_LIBRARIES}
                LIBRARIES ${arg_LIBRARIES}
                COMPILE_OPTIONS ${arg_COMPILE_OPTIONS}
                LINK_OPTIONS ${arg_LINK_OPTIONS})

        qext_internal_add_repo_local_defines(${name})

        # Disable the QEXT_NO_NARROWING_CONVERSIONS_IN_CONNECT define for tests
        qext_internal_undefine_global_definition(${name} QEXT_NO_NARROWING_CONVERSIONS_IN_CONNECT)

        # Tests should not be bundles on macOS even if arg_GUI is true, because some tests make
        # assumptions about the location of helper processes, and those paths would be different
        # if a test is built as a bundle.
        set_property(TARGET "${name}" PROPERTY MACOSX_BUNDLE FALSE)
        # The same goes for WIN32_EXECUTABLE, but because it will detach from the console window and not print anything.
        set_property(TARGET "${name}" PROPERTY WIN32_EXECUTABLE FALSE)

        # Tests on iOS must be app bundles.
        if (IOS)
            set_target_properties(${name} PROPERTIES MACOSX_BUNDLE TRUE)
        endif ()

        # Android requires QExt::Gui so add it by default for tests, todo
        #        qext_internal_extend_target("${name}" CONDITION ANDROID PUBLIC_LIBRARIES ${QEXT_CMAKE_EXPORT_NAMESPACE}::Gui)
    endif ()

    # Generate a label in the form tests/auto/foo/bar/tst_baz
    # and use it also for XML output
    set(label_base_directory "${PROJECT_SOURCE_DIR}")
    if (QEXT_SUPERBUILD)
        # Prepend repository name for QExt0 builds, so that tests can be run for
        # individual repositories.
        set(label_base_directory "${label_base_directory}/..")
    endif ()
    file(RELATIVE_PATH label "${label_base_directory}" "${CMAKE_CURRENT_SOURCE_DIR}/${name}")

    if (arg_LOWDPI)
        target_compile_definitions("${name}" PUBLIC TESTCASE_LOWDPI)
        if (MACOS)
            set_property(TARGET "${name}" PROPERTY MACOSX_BUNDLE_INFO_PLIST "${QEXT_MKSPECS_DIR}/macx-clang/Info.plist.disable_highdpi")
            set_property(TARGET "${name}" PROPERTY PROPERTY MACOSX_BUNDLE TRUE)
        endif ()
    endif ()

    if (ANDROID)
        qext_internal_android_test_arguments("${name}" test_executable extra_test_args)
        set(test_working_dir "${CMAKE_CURRENT_BINARY_DIR}")
    elseif (QNX)
        set(test_working_dir "")
        set(test_executable "${name}")
    elseif (WASM)
        # Test script expects html file
        set(test_executable "${name}.html")

        if (QExt6_INSTALL_PREFIX)
            set(QEXT_WASM_TESTRUNNER "${QEXT_INSTALL_PREFIX}/${QEXT_INSTALL_LIBEXECDIR}/qext-wasmtestrunner.py")
        elseif (QEXT_BUILD_DIR)
            set(QEXT_WASM_TESTRUNNER "${QEXT_BUILD_DIR}/${QEXT_INSTALL_LIBEXECDIR}/qext-wasmtestrunner.py")
        endif ()
        # This tells cmake to run the tests with this script, since wasm files can't be
        # executed directly
        set_property(TARGET "${name}" PROPERTY CROSSCOMPILING_EMULATOR "${QEXT_WASM_TESTRUNNER}")
    else ()
        if (arg_WORKING_DIRECTORY)
            set(test_working_dir "${arg_WORKING_DIRECTORY}")
        elseif (arg_OUTPUT_DIRECTORY)
            set(test_working_dir "${arg_OUTPUT_DIRECTORY}")
        else ()
            set(test_working_dir "${CMAKE_CURRENT_BINARY_DIR}")
        endif ()
        set(test_executable "${name}")
    endif ()

    qext_internal_collect_command_environment(test_env_path test_env_plugin_path)

    if (arg_NO_WRAPPER OR QEXT_NO_TEST_WRAPPERS)
        add_test(NAME "${name}" COMMAND ${test_executable} ${extra_test_args}
                WORKING_DIRECTORY "${test_working_dir}")
        set_property(TEST "${name}" APPEND PROPERTY
                ENVIRONMENT "PATH=${test_env_path}"
                "QEXT_TEST_RUNNING_IN_CTEST=1"
                "QEXT_PLUGIN_PATH=${test_env_plugin_path}")
    else ()
        set(test_wrapper_file "${CMAKE_CURRENT_BINARY_DIR}/${name}Wrapper$<CONFIG>.cmake")
        qext_internal_create_test_script(NAME "${name}"
                COMMAND "${test_executable}"
                ARGS "${extra_test_args}"
                WORKING_DIRECTORY "${test_working_dir}"
                OUTPUT_FILE "${test_wrapper_file}"
                ENVIRONMENT "QEXT_TEST_RUNNING_IN_CTEST" 1
                "PATH" "${test_env_path}"
                "QEXT_PLUGIN_PATH" "${test_env_plugin_path}")
    endif ()

    if (arg_QEXT_TEST_SERVER_LIST AND NOT ANDROID)
        qext_internal_setup_docker_test_fixture(${name} ${arg_QEXT_TEST_SERVER_LIST})
    endif ()

    set_tests_properties("${name}" PROPERTIES RUN_SERIAL "${arg_RUN_SERIAL}" LABELS "${label}")
    if (arg_TIMEOUT)
        set_tests_properties(${name} PROPERTIES TIMEOUT ${arg_TIMEOUT})
    endif ()

    # Add a ${target}/check makefile target, to more easily test one test.

    ###TODO:?
    #    set(test_config_options "")
    #    get_cmake_property(is_multi_config GENERATOR_IS_MULTI_CONFIG)
    #    if(is_multi_config)
    #        set(test_config_options -C $<CONFIG>)
    #    endif()
    #    add_custom_target("${name}_check"
    #        VERBATIM
    #        COMMENT "Running ${CMAKE_CTEST_COMMAND} -V -R \"^${name}$\" ${test_config_options}"
    #        COMMAND "${CMAKE_CTEST_COMMAND}" -V -R "^${name}$" ${test_config_options}
    #        )
    #    if(TARGET "${name}")
    #        add_dependencies("${name}_check" "${name}")
    #        if(ANDROID)
    #            add_dependencies("${name}_check" "${name}_make_apk")
    #        endif()
    #    endif()

    if (ANDROID OR IOS OR INTEGRITY OR arg_BUILTIN_TESTDATA)
        set(builtin_testdata TRUE)
    endif ()

    if (builtin_testdata)
        # Safe guard against qml only tests, no source files == no target
        if (TARGET "${name}")
            target_compile_definitions("${name}" PRIVATE BUILTIN_TESTDATA)

            foreach (testdata IN LISTS arg_TESTDATA)
                list(APPEND builtin_files ${testdata})
            endforeach ()

            set(blacklist_path "BLACKLIST")
            if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${blacklist_path}")
                list(APPEND builtin_files ${blacklist_path})
            endif ()

            list(REMOVE_DUPLICATES builtin_files)

            # Skip QExt quick compiler when embedding test resources
            foreach (file IN LISTS builtin_files)
                set_source_files_properties(${file} PROPERTIES QEXT_SKIP_QUICKCOMPILER TRUE)
            endforeach ()

            ###TODO:need impl
            #            if(builtin_files)
            #                qext_internal_add_resource(${name} "${name}_testdata_builtin"
            #                    PREFIX "/"
            #                    FILES ${builtin_files}
            #                    BASE ${CMAKE_CURRENT_SOURCE_DIR})
            #            endif()
        endif ()
    else ()
        # Install test data
        file(RELATIVE_PATH relative_path_to_test_project
                "${QEXT_TOP_LEVEL_SOURCE_DIR}"
                "${CMAKE_CURRENT_SOURCE_DIR}")
        qext_path_join(testdata_install_dir ${QEXT_INSTALL_DIR}
                "${relative_path_to_test_project}")
        if (testdata_install_dir)
            foreach (testdata IN LISTS arg_TESTDATA)
                set(testdata "${CMAKE_CURRENT_SOURCE_DIR}/${testdata}")
                if (IS_DIRECTORY "${testdata}")
                    qext_install(
                            DIRECTORY "${testdata}"
                            DESTINATION "${testdata_install_dir}")
                else ()
                    qext_install(
                            FILES "${testdata}"
                            DESTINATION "${testdata_install_dir}")
                endif ()
            endforeach ()
        endif ()
    endif ()

    qext_internal_add_test_finalizers("${name}")
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
# The function disables one or multiple internal global definitions that are defined by the
# qext_internal_add_global_definition function for a specific 'target'.
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_undefine_global_definition target)
    if (NOT TARGET ${target})
        message(FATAL_ERROR "${target} is not a target.")
    endif ()

    if ("${ARGN}" STREQUAL "")
        message(FATAL_ERROR "The function expects at least one definition as an argument.")
    endif ()

    foreach (definition IN LISTS ARGN)
        set(undef_property_name "QEXT_INTERNAL_UNDEF_${definition}")
        set_target_properties(${target} PROPERTIES "${undef_property_name}" TRUE)
    endforeach ()
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_add_test_finalizers target)
    # It might not be safe to run all the finalizers of _qext_internal_finalize_executable
    # within the context of a QExt build (not a user project) when targeting a host build.
    # For now, we limit it to iOS, where it was tested to work, an we know that host tools
    # should already be built and available.
    if (IOS)
        qext_add_list_file_finalizer(_qext_internal_finalize_executable "${target}")
    endif ()
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_collect_command_environment out_path out_plugin_path)
    # Get path to <qext_relocatable_install_prefix>/bin, as well as QEXT_INSTALL_PREFIX/bin, and
    # combine them with the PATH environment variable.
    # It's needed on Windows to find the shared libraries and plugins.
    # qext_relocatable_install_prefix is dynamically computed from the location of where the QExt CMake
    # package is found.
    # The regular QEXT_INSTALL_PREFIX can be different for example when building standalone tests.
    # Any given QEXT_INSTALL_PREFIX takes priority over qext_relocatable_install_prefix for the
    # PATH environment variable.
    set(install_prefixes "${QEXT_INSTALL_PREFIX}")
    if (QEXT_BUILD_INTERNALS_RELOCATABLE_INSTALL_PREFIX)
        list(APPEND install_prefixes "${QEXT_BUILD_INTERNALS_RELOCATABLE_INSTALL_PREFIX}")
    endif ()

    file(TO_NATIVE_PATH "${CMAKE_CURRENT_BINARY_DIR}" test_env_path)
    foreach (install_prefix ${install_prefixes})
        file(TO_NATIVE_PATH "${install_prefix}/${QEXT_INSTALL_BINDIR}" install_prefix)
        set(test_env_path "${test_env_path}${QEXT_PATH_SEPARATOR}${install_prefix}")
    endforeach ()
    set(test_env_path "${test_env_path}${QEXT_PATH_SEPARATOR}$ENV{PATH}")
    string(REPLACE ";" "\;" test_env_path "${test_env_path}")
    set(${out_path} "${test_env_path}" PARENT_SCOPE)

    # Add the install prefix to list of plugin paths when doing a prefix build
    if (NOT QEXT_INSTALL_DIR)
        foreach (install_prefix ${install_prefixes})
            file(TO_NATIVE_PATH "${install_prefix}/${QEXT_INSTALL_BINDIR}" install_prefix)
            list(APPEND plugin_paths "${install_prefix}")
        endforeach ()
    endif ()

    #TODO: Collect all paths from known repositories when performing a super
    # build.
    file(TO_NATIVE_PATH "${PROJECT_BINARY_DIR}/${QEXT_INSTALL_PLUGINSDIR}" install_pluginsdir)
    list(APPEND plugin_paths "${install_pluginsdir}")
    list(JOIN plugin_paths "${QEXT_PATH_SEPARATOR}" plugin_paths_joined)
    string(REPLACE ";" "\;" plugin_paths_joined "${plugin_paths_joined}")
    set(${out_plugin_path} "${plugin_paths_joined}" PARENT_SCOPE)
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
# This function adds test with specified NAME and wraps given test COMMAND with standalone cmake
# script.
#
# NAME must be compatible with add_test function, since it's propagated as is.
# COMMAND might be either target or path to executable. When test is called either by ctest or
# directly by 'cmake -P path/to/scriptWrapper.cmake', COMMAND will be executed in specified
# WORKING_DIRECTORY with arguments specified in ARGS.
#
# See also _qext_internal_create_command_script for details.
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_create_test_script)
    #This style of parsing keeps ';' in ENVIRONMENT variables
    cmake_parse_arguments(PARSE_ARGV 0 arg
            ""
            "NAME;COMMAND;OUTPUT_FILE;WORKING_DIRECTORY"
            "ARGS;ENVIRONMENT;PRE_RUN;POST_RUN")

    if (NOT arg_COMMAND)
        message(FATAL_ERROR "qext_internal_create_test_script: Test COMMAND is not specified")
    endif ()

    if (NOT arg_NAME)
        message(FATAL_ERROR "qext_internal_create_test_script: Test NAME is not specified")
    endif ()

    if (NOT arg_OUTPUT_FILE)
        message(FATAL_ERROR "qext_internal_create_test_script: Test Wrapper OUTPUT_FILE is not specified")
    endif ()

    if (arg_PRE_RUN)
        message(WARNING "qext_internal_create_test_script: PRE_RUN is not acceptable argument for this function. Will be ignored")
    endif ()

    if (arg_POST_RUN)
        message(WARNING "qext_internal_create_test_script: POST_RUN is not acceptable argument for this function. Will be ignored")
    endif ()

    if (arg_ARGS)
        set(command_args ${arg_ARGS})# Avoid "${arg_ARGS}" usage and let cmake expand string to
        # semicolon-separated list
        qext_internal_wrap_command_arguments(command_args)
    endif ()

    if (TARGET ${arg_COMMAND})
        set(executable_file "$<TARGET_FILE:${arg_COMMAND}>")
    else ()
        set(executable_file "${arg_COMMAND}")
    endif ()

    add_test(NAME "${arg_NAME}" COMMAND "${CMAKE_COMMAND}" "-P" "${arg_OUTPUT_FILE}"
            WORKING_DIRECTORY "${arg_WORKING_DIRECTORY}")

    # If crosscompiling is enabled, we should avoid run cmake in emulator environment.
    # Prepend emulator to test command in generated cmake script instead. Keep in mind that
    # CROSSCOMPILING_EMULATOR don't check if actual cross compilation is configured,
    # emulator is prepended independently.
    set(crosscompiling_emulator "")
    if (CMAKE_CROSSCOMPILING AND TARGET ${arg_NAME})
        get_target_property(crosscompiling_emulator ${arg_NAME} CROSSCOMPILING_EMULATOR)
        if (NOT crosscompiling_emulator)
            set(crosscompiling_emulator "")
        else ()
            qext_internal_wrap_command_arguments(crosscompiling_emulator)
        endif ()
    endif ()

    _qext_internal_create_command_script(COMMAND "${crosscompiling_emulator} \${env_test_runner} \"${executable_file}\" \${env_test_args} ${command_args}"
            OUTPUT_FILE "${arg_OUTPUT_FILE}"
            WORKING_DIRECTORY "${arg_WORKING_DIRECTORY}"
            ENVIRONMENT ${arg_ENVIRONMENT}
            PRE_RUN "separate_arguments(env_test_args NATIVE_COMMAND \"\$ENV{TESTARGS}\")"
            "separate_arguments(env_test_runner NATIVE_COMMAND \"\$ENV{TESTRUNNER}\")")
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
# This function wraps COMMAND with cmake script, that makes possible standalone run with external
# arguments.
#
# Generated wrapper will be written to OUTPUT_FILE.
# If WORKING_DIRECTORY is not set COMMAND will be executed in CMAKE_CURRENT_BINARY_DIR.
# Variables from ENVIRONMENT will be set before COMMAND execution.
# PRE_RUN and POST_RUN arguments may contain extra cmake code that supposed to be executed before
# and after COMMAND, respectively. Both arguments accept a list of cmake script language
# constructions. Each item of the list will be concantinated into single string with '\n' separator.
# COMMAND_ECHO option takes a value like it does for execute_process, and passes that value to
# execute_process.
#-----------------------------------------------------------------------------------------------------------------------
function(_qext_internal_create_command_script)
    #This style of parsing keeps ';' in ENVIRONMENT variables
    cmake_parse_arguments(PARSE_ARGV 0 arg
            ""
            "OUTPUT_FILE;WORKING_DIRECTORY;COMMAND_ECHO"
            "COMMAND;ENVIRONMENT;PRE_RUN;POST_RUN")

    if (NOT arg_COMMAND)
        message(FATAL_ERROR "qext_internal_create_command_script: COMMAND is not specified")
    endif ()

    if (NOT arg_OUTPUT_FILE)
        message(FATAL_ERROR "qext_internal_create_command_script: Wrapper OUTPUT_FILE is not specified")
    endif ()

    if (NOT arg_WORKING_DIRECTORY AND NOT QNX)
        set(arg_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
    endif ()

    set(environment_extras)
    set(skipNext false)
    if (arg_ENVIRONMENT)
        list(LENGTH arg_ENVIRONMENT length)
        math(EXPR length "${length} - 1")
        foreach (envIdx RANGE ${length})
            if (skipNext)
                set(skipNext FALSE)
                continue()
            endif ()

            set(envVariable "")
            set(envValue "")

            list(GET arg_ENVIRONMENT ${envIdx} envVariable)
            math(EXPR envIdx "${envIdx} + 1")
            if (envIdx LESS_EQUAL ${length})
                list(GET arg_ENVIRONMENT ${envIdx} envValue)
            endif ()

            if (NOT "${envVariable}" STREQUAL "")
                set(environment_extras "${environment_extras}\nset(ENV{${envVariable}} \"${envValue}\")")
            endif ()
            set(skipNext TRUE)
        endforeach ()
    endif ()

    #Escaping environment variables before expand them by file GENERATE
    string(REPLACE "\\" "\\\\" environment_extras "${environment_extras}")

    if (WIN32)
        # It's necessary to call actual test inside 'cmd.exe', because 'execute_process' uses
        # SW_HIDE to avoid showing a console window, it affects other GUI as well.
        # See https://gitlab.kitware.com/cmake/cmake/-/issues/17690 for details.
        set(extra_runner "cmd /c")
    endif ()

    if (arg_PRE_RUN)
        string(JOIN "\n" pre_run ${arg_PRE_RUN})
    endif ()

    if (arg_POST_RUN)
        string(JOIN "\n" post_run ${arg_POST_RUN})
    endif ()

    set(command_echo "")
    if (arg_COMMAND_ECHO)
        set(command_echo "COMMAND_ECHO ${arg_COMMAND_ECHO}")
    endif ()

    file(GENERATE OUTPUT "${arg_OUTPUT_FILE}" CONTENT
            "#!${CMAKE_COMMAND} -P
        # QExt generated command wrapper

        ${environment_extras}
            ${pre_run}
        execute_process(COMMAND ${extra_runner} ${arg_COMMAND}
                WORKING_DIRECTORY \"${arg_WORKING_DIRECTORY}\"
                ${command_echo}
                RESULT_VARIABLE result)
        ${post_run}
        if(NOT result EQUAL 0)
            string(JOIN \" \" full_command ${arg_COMMAND})
            message(FATAL_ERROR \"\${full_command} execution failed with exit code \${result}.\")
        endif()")
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_wrap_command_arguments argument_list)
    list(TRANSFORM ${argument_list} REPLACE "^(.+)$" "[=[\\1]=]")
    list(JOIN ${argument_list} " " ${argument_list})
    set(${argument_list} "${${argument_list}}" PARENT_SCOPE)
endfunction()
