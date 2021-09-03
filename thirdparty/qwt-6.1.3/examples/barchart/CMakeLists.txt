#----------------------------------------------------------------
# Packages
#----------------------------------------------------------------
# Find includes in corresponding build include_directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

#----------------------------------------------------------------
# Sources
#----------------------------------------------------------------
set(barchart_sources
    barchart.cpp
    barchart.h
    main.cpp
    )

#----------------------------------------------------------------
# Target
#----------------------------------------------------------------
add_executable(qwt_example_barchart ${barchart_sources})

target_link_libraries(qwt_example_barchart PRIVATE Qwt)


#----------------------------------------------------------------
# Deploy
#----------------------------------------------------------------
if (QWT_QT_VERSION_MAJOR EQUAL 4)
    add_custom_command(
        TARGET qwt_example_animation POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt4::QtCore> $<TARGET_FILE_DIR:qwt_example_animation>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt4::QtGui> $<TARGET_FILE_DIR:qwt_example_animation>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt4::QtOpenGL> $<TARGET_FILE_DIR:qwt_example_animation>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qwt> $<TARGET_FILE_DIR:qwt_example_animation>
        )
else(QWT_QT_VERSION_MAJOR GREATER 4)
    add_custom_command(
        TARGET qwt_example_animation POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt${QWT_QT_VERSION_MAJOR}::Core> $<TARGET_FILE_DIR:qwt_example_animation>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt${QWT_QT_VERSION_MAJOR}::Gui> $<TARGET_FILE_DIR:qwt_example_animation>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt${QWT_QT_VERSION_MAJOR}::OpenGL> $<TARGET_FILE_DIR:qwt_example_animation>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt${QWT_QT_VERSION_MAJOR}::PrintSupport> $<TARGET_FILE_DIR:qwt_example_animation>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt${QWT_QT_VERSION_MAJOR}::Svg> $<TARGET_FILE_DIR:qwt_example_animation>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt${QWT_QT_VERSION_MAJOR}::Widgets> $<TARGET_FILE_DIR:qwt_example_animation>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qwt> $<TARGET_FILE_DIR:qwt_example_animation>
        )
endif()



