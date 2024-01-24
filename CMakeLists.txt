cmake_minimum_required(VERSION 3.20)

project(MotorDriverApp)

# Find requirements
if(NOT fastcdr_FOUND)
    find_package(fastcdr 2 REQUIRED)
endif()

if(NOT fastrtps_FOUND)
    find_package(fastrtps 2.12 REQUIRED)
endif()

pkg_check_modules(LIBMODBUS REQUIRED libmodbus)
include_directories(${LIBMODBUS_INCLUDE_DIRS})
link_directories(${LIBMODBUS_LIBRARY_DIRS})

include_directories(include)

# Set C++11
include(CheckCXXCompilerFlag)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG OR
        CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    check_cxx_compiler_flag(-std=c++11 SUPPORTS_CXX11)
    if(SUPPORTS_CXX11)
        add_compile_options(-std=c++11)
    else()
        message(FATAL_ERROR "Compiler doesn't support C++11")
    endif()
endif()



message(STATUS "Configuring MotorDriverApp  publisher/subscriber example...")
file(GLOB MOTORDRIVERAPP_SOURCES_CXX "src/generated/*.cxx")

add_executable(MotorDriverApp src/main.cpp src/QuerySubscriber.cpp  src/ResponsePublisher.cpp src/StatePublisher.cpp ${MOTORDRIVERAPP_SOURCES_CXX})
target_link_libraries(MotorDriverApp modbus fastrtps fastcdr)
 

