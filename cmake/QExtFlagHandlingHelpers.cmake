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
function(qext_skip_warnings_are_errors_when_repo_unclean target)
    if(QEXT_REPO_NOT_WARNINGS_CLEAN)
        qext_skip_warnings_are_errors("${target}")
    endif()
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_skip_warnings_are_errors target)
    get_target_property(target_type "${target}" TYPE)
    if(target_type STREQUAL "INTERFACE_LIBRARY")
        return()
    endif()
    set_target_properties("${target}" PROPERTIES QEXT_SKIP_WARNINGS_ARE_ERRORS ON)
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_library_deprecation_level result)
    # QEXT_DISABLE_DEPPRECATED_BEFORE controls which version we use as a cut-off
    # compiling in to the library. E.g. if it is set to QEXT_VERSION then no
    # code which was deprecated before QEXT_VERSION will be compiled in.
    if(WIN32)
        # On Windows, due to the way DLLs work, we need to export all functions,
        # including the inlines
        list(APPEND deprecations "QEXT_DISABLE_DEPRECATED_BEFORE=0x040800")
    else()
        # On other platforms, QExt's own compilation goes needs to compile the QExt 5.0 API
        list(APPEND deprecations "QEXT_DISABLE_DEPRECATED_BEFORE=0x050000")
    endif()
    # QEXT_DEPRECATED_WARNINGS_SINCE controls the upper-bound of deprecation
    # warnings that are emitted. E.g. if it is set to 7.0 then all deprecations
    # during the 6.* lifetime will be warned about in QExt builds.
    list(APPEND deprecations "QEXT_DEPRECATED_WARNINGS_SINCE=0x070000")
    set("${result}" "${deprecations}" PARENT_SCOPE)
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_set_msvc_cplusplus_options target visibility)
    # For MSVC we need to explicitly pass -Zc:__cplusplus to get correct __cplusplus.
    # Check qext_config_compile_test for more info.
    if(MSVC AND MSVC_VERSION GREATER_EQUAL 1913)
        set(flags "-Zc:__cplusplus" "-permissive-")
        target_compile_options("${target}" ${visibility} "$<$<COMPILE_LANGUAGE:CXX>:${flags}>")
    endif()
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_set_language_standards_interface_compile_features target)
    # Regardless of which C++ standard is used to build QExt itself, require C++17 when building
    # QExt applications using CMake (because the QExt header files use C++17 features).
    set(cpp_feature "cxx_std_17")
    target_compile_features("${target}" INTERFACE ${cpp_feature})
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_enable_utf8_sources target)
    set(utf8_flags "")
    if(MSVC)
        list(APPEND utf8_flags "-utf-8")
    endif()

    if(utf8_flags)
        # Allow opting out by specifying the QEXT_NO_UTF8_SOURCE target property.
        set(opt_out_condition "$<NOT:$<BOOL:$<TARGET_PROPERTY:QEXT_NO_UTF8_SOURCE>>>")
        # Only set the compiler option for C and C++.
        set(language_condition "$<COMPILE_LANGUAGE:C,CXX>")
        # Compose the full condition.
        set(genex_condition "$<AND:${opt_out_condition},${language_condition}>")
        set(utf8_flags "$<${genex_condition}:${utf8_flags}>")
        target_compile_options("${target}" INTERFACE "${utf8_flags}")
    endif()
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_enable_unicode_defines)
    if(WIN32)
        set(no_unicode_condition "$<NOT:$<BOOL:$<TARGET_PROPERTY:QEXT_NO_UNICODE_DEFINES>>>")
        target_compile_definitions(platform INTERFACE "$<${no_unicode_condition}:UNICODE;_UNICODE>")
    endif()
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
# Sets the ignore warning flags for the given target
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_set_ignore_warning_flags target)
    set(flags "")
    # c4464 : A #include directive has a path that includes a parent directory specifier (a .. path segment).
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        set(flags "/wd4464")
    elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU|AppleClang|InteLLLVM")

    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        if(MSVC)
            set(flags "/wd4464")
        endif()
    endif()
    target_compile_options("${target}" PRIVATE ${flags})
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
# Sets the exceptions flags for the given target according to exceptions_on
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_set_exceptions_flags target exceptions_on)
    set(_defs "")
    set(_flag "")
    if(exceptions_on)
		if(MSVC)
			set(_flag "/EHsc")
			if((MSVC_VERSION GREATER_EQUAL 1929) AND NOT CLANG)
				set(_flag ${_flag} "/d2FH4")
			endif()
		elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU|AppleClang|InteLLLVM")
			set(_flag "-fexceptions" "-fcxx-exceptions")
		endif()
    else()
        set(_defs "QEXT_NO_EXCEPTIONS")
        if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
            set(_flag "/EHs-c-" "/wd4530" "/wd4577")
        elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU|AppleClang|InteLLLVM")
            set(_flag "-fno-exceptions")
        elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
            if(MSVC)
                set(_flag "/EHs-c-" "/wd4530" "/wd4577")
            else()
                set(_flag "-fno-exceptions")
            endif()
        endif()
    endif()

    target_compile_definitions("${target}" PRIVATE ${_defs})
    target_compile_options("${target}" PRIVATE ${_flag})
endfunction()


#-----------------------------------------------------------------------------------------------------------------------
####TODO::del
#-----------------------------------------------------------------------------------------------------------------------
function(qext_internal_add_linker_version_script target)
    qext_parse_all_arguments(arg "qext_internal_add_linker" "" "" "PRIVATE_HEADERS" ${ARGN})

    if(TEST_ld_version_script)
        set(contents "QEXT_${PROJECT_VERSION_MAJOR}_PRIVATE_API {\n    qext_private_api_tag*;\n")
        foreach(ph ${arg_PRIVATE_HEADERS})
            string(APPEND contents "    @FILE:${ph}@\n")
        endforeach()
        string(APPEND contents "};\n")
        set(current "QEXT_${PROJECT_VERSION_MAJOR}")
        if(QEXT_NAMESPACE STREQUAL "")
            set(tag_symbol "qext_version_tag")
        else()
            set(tag_symbol "qext_version_tag_${QEXT_NAMESPACE}")
        endif()
        string(APPEND contents "${current} { *; };\n")

        foreach(minor_version RANGE ${PROJECT_VERSION_MINOR})
            set(previous "${current}")
            set(current "QEXT_${PROJECT_VERSION_MAJOR}.${minor_version}")
            if(minor_version EQUAL ${PROJECT_VERSION_MINOR})
                string(APPEND contents "${current} { ${tag_symbol}; } ${previous};\n")
            else()
                string(APPEND contents "${current} {} ${previous};\n")
            endif()
        endforeach()

        set(infile "${CMAKE_CURRENT_BINARY_DIR}/${target}.version.in")
        set(outfile "${CMAKE_CURRENT_BINARY_DIR}/${target}.version")

        file(GENERATE OUTPUT "${infile}" CONTENT "${contents}")

        qext_ensure_perl()

        set(generator_command "${HOST_PERL}"
            "${QEXT_MKSPECS_DIR}/features/data/unix/findclasslist.pl"
            "<" "${infile}" ">" "${outfile}")
        set(generator_dependencies
            "${infile}"
            "${QEXT_MKSPECS_DIR}/features/data/unix/findclasslist.pl")

        add_custom_command(
            OUTPUT "${outfile}"
            COMMAND ${generator_command}
            DEPENDS ${generator_dependencies}
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
            COMMENT "Generating version linker script for target ${target}"
            VERBATIM)
        add_custom_target(${target}_version_script DEPENDS ${outfile})
        add_dependencies(${target} ${target}_version_script)
        target_link_options(${target} PRIVATE "-Wl,--version-script,${outfile}")
    endif()
endfunction()


function(qext_internal_add_link_flags_no_undefined target)
    if(NOT QEXT_BUILD_SHARED_LIBS)
        return()
    endif()
    if((GCC OR CLANG) AND NOT MSVC)
        if(CLANG AND QEXT_FEATURE_sanitizer)
            return()
        endif()
        set(previous_CMAKE_REQUIRED_LINK_OPTIONS ${CMAKE_REQUIRED_LINK_OPTIONS})

        set(CMAKE_REQUIRED_LINK_OPTIONS "-Wl,-undefined,error")
        check_cxx_source_compiles("int main() {}" HAVE_DASH_UNDEFINED_SYMBOLS)
        if(HAVE_DASH_UNDEFINED_SYMBOLS)
            set(no_undefined_flag "-Wl,-undefined,error")
        endif()

        set(CMAKE_REQUIRED_LINK_OPTIONS "-Wl,--no-undefined")
        check_cxx_source_compiles("int main() {}" HAVE_DASH_DASH_NO_UNDEFINED)
        if(HAVE_DASH_DASH_NO_UNDEFINED)
            set(no_undefined_flag "-Wl,--no-undefined")
        endif()

        set(CMAKE_REQUIRED_LINK_OPTIONS ${previous_CMAKE_REQUIRED_LINK_OPTIONS})

        if(NOT HAVE_DASH_UNDEFINED_SYMBOLS AND NOT HAVE_DASH_DASH_NO_UNDEFINED)
            message(FATAL_ERROR "platform linker doesn't support erroring upon encountering undefined symbols. Target:\"${target}\".")
        endif()
        target_link_options("${target}" PRIVATE "${no_undefined_flag}")
    endif()
endfunction()
