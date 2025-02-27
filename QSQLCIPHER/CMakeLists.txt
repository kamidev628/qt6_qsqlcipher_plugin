cmake_minimum_required(VERSION 3.19)
project(QSQLCIPHER LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Sql)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/deploy/)
qt_standard_project_setup()

qt_add_executable(QSQLCIPHER
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

target_link_libraries(QSQLCIPHER
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Sql
)

include(GNUInstallDirs)

install(TARGETS QSQLCIPHER
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET QSQLCIPHER
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
