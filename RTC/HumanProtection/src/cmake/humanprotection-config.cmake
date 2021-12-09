# HumanProtection CMake config file
#
# This file sets the following variables:
# HumanProtection_FOUND - Always TRUE.
# HumanProtection_INCLUDE_DIRS - Directories containing the HumanProtection include files.
# HumanProtection_IDL_DIRS - Directories containing the HumanProtection IDL files.
# HumanProtection_LIBRARIES - Libraries needed to use HumanProtection.
# HumanProtection_DEFINITIONS - Compiler flags for HumanProtection.
# HumanProtection_VERSION - The version of HumanProtection found.
# HumanProtection_VERSION_MAJOR - The major version of HumanProtection found.
# HumanProtection_VERSION_MINOR - The minor version of HumanProtection found.
# HumanProtection_VERSION_REVISION - The revision version of HumanProtection found.
# HumanProtection_VERSION_CANDIDATE - The candidate version of HumanProtection found.

message(STATUS "Found HumanProtection-1.0.0")
set(HumanProtection_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(HumanProtection_INCLUDE_DIRS
#    "/usr/local/include/humanprotection-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(HumanProtection_IDL_DIRS
#    "/usr/local/include/humanprotection-1/idl")
set(HumanProtection_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(HumanProtection_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(HumanProtection_LIBRARIES
        "/usr/local//libhumanprotection.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(HumanProtection_LIBRARIES
        "/usr/local//libhumanprotection.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(HumanProtection_DEFINITIONS ${<dependency>_DEFINITIONS})

set(HumanProtection_VERSION 1.0.0)
set(HumanProtection_VERSION_MAJOR 1)
set(HumanProtection_VERSION_MINOR 0)
set(HumanProtection_VERSION_REVISION 0)
set(HumanProtection_VERSION_CANDIDATE )

