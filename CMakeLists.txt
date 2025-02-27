cmake_minimum_required(VERSION 3.14)

project(qt6_qsqlchiper_plugin VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories for the src and ui projects
add_subdirectory(qsqlcipher-qt6)
add_subdirectory(QSQLCIPHER)
