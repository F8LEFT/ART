# ART version
set(ART_VERSION_MAJOR 0)
set(ART_VERSION_MINOR 8)
set(ART_VERSION_PATCH 0)
set(ART_VERSION ${ART_VERSION_MAJOR}.${ART_VERSION_MINOR}.${ART_VERSION_PATCH})

################################################################################

project(AndroidReverseToolkit)
cmake_minimum_required(VERSION 3.5)

set(ECM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/KDE/share/ECM/cmake)

add_subdirectory(KDE)
find_package(ECM 5.28.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})
if(POLICY CMP0063)
    cmake_policy(SET CMP0063 NEW)
endif()

include(KDEInstallDirs)
include(KDECompilerSettings)
include(KDECMakeSettings)
include(ECMSetupVersion)
include(FeatureSummary)

#
# Dependencies
#
set(REQUIRED_QT_VERSION "5.7.0")
find_package(Qt5 ${REQUIRED_QT_VERSION} NO_MODULE REQUIRED COMPONENTS Core Gui Network)
find_package(Qt5 ${REQUIRED_QT_VERSION} NO_MODULE QUIET OPTIONAL_COMPONENTS Widgets XmlPatterns WebSockets)
set_package_properties(Qt5 PROPERTIES URL "http://qt-project.org/")
set_package_properties(Qt5Widgets PROPERTIES PURPOSE "MainWindow application.")
set_package_properties(Qt5XmlPatterns PROPERTIES PURPOSE "Compile-time validation of syntax definition files.")
set_package_properties(Qt5WebSockets PROPERTIES PURPOSE "Connect to network.")

set(KF5_DEP_VERSION "5.28.0") # we need KCrash::initialize
set_package_properties(KF5SyntaxHighlighting PROPERTIES PURPOSE "Syntax highlighting engine")

#
# Translations
#
if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/po")
    ecm_install_po_files_as_qm(po)
endif()

SET(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

IF (WIN32 OR WIN64)
    MESSAGE("Building windows version")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
    set(SYSNAME win)
ELSEIF (APPLE)
    MESSAGE("Building apple version")
    set(SYSNAME mac)
ELSEIF (UNIX)
    MESSAGE("Building UNIX version.")
    set(SYSNAME unix)
ELSE()
    message(FATAL_ERROR "not supported platform")
ENDIF ()

# just generate all file into one folder.
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif()


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Werror  -fexceptions")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -Wno-overloaded-virtual -Wno-unused-function -Wno-unused-parameter -Wno-unknown-pragmas")

SET(ART_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${ART_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_definitions(-DQT_NO_EMIT)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_SUPPRESS_REGENERATION 1)


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bin/cfgs
        DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bin/platforms/${SYSNAME}/adb
        DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/thirdparty)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bin/thirdparty
        DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


add_subdirectory(lib)

ecm_setup_version(${ART_VERSION_MAJOR}.${ART_VERSION_MINOR}.${ART_VERSION_PATCH}
        VARIABLE_PREFIX ART
        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/art_version.h"
        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/ARTConfigVersion.cmake"
        )

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

