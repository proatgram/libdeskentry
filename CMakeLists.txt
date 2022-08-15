cmake_minimum_required(VERSION 3.2)

# set(CMAKE_TOOLCHAIN_FILE "/media/thetimbrick/4d2d47b0-3ef2-4c5a-8721-f1970dd6ff77/host/share/buildroot/toolchainfile.cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(EmbreadedWM VERSION 0.1
    DESCRIPTION "A library that parses Desktop Entry Files"
LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

file(GLOB_RECURSE libdeskentry_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE libdeskentry_HEADERS "${CMAKE_SOURCE_DIR}/include/*.h}" "${CMAKE_SOURCE_DIR}/include/*.hpp")

add_library(deskentry SHARED ${libdeskentry_SOURCES} ${libdeskentry_HEADERS})

target_include_directories(deskentry PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(libdeskentry-test ${CMAKE_SOURCE_DIR}/tests/main.cpp)

target_link_libraries(libdeskentry-test ${CMAKE_SOURCE_DIR}/build/libdeskentry.so)

target_include_directories(libdeskentry-test PUBLIC ${CMAKE_SOURCE_DIR}/include)
