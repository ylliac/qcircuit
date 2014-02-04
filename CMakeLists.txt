#
# Set environment variable
# Warning! Do not use backslash
#

# MINGW_HOME
# NSIS_HOME

########################################################################
# Configuration
########################################################################

#
# CMAKE >= 2.8.10
# Bugs detected in 2.8.7 
#
CMAKE_MINIMUM_REQUIRED (VERSION 2.8.10) 

#
# Project
#
PROJECT (dspatchdemo)

# Dist path
SET (EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/dist)
SET (LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/dist)
# Build path
SET (CMAKE_CURRENT_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/build")

MESSAGE ("CURRENT PATH : ${CMAKE_CURRENT_SOURCE_DIR}")
MESSAGE ("BUILD PATH : ${CMAKE_CURRENT_BINARY_DIR}")
MESSAGE ("DIST PATH : ${EXECUTABLE_OUTPUT_PATH}")

#PREPROC
ADD_DEFINITIONS ()

#
# Debug by default
#
IF (CMAKE_BUILD_TYPE MATCHES "Release")
    MESSAGE ("Build in Release")
    SET (DEBUG_SUFFIX "")
ELSE()
    MESSAGE ("Build in Debug")
    SET (CMAKE_BUILD_TYPE Debug)
    SET (DEBUG_SUFFIX "d")
ENDIF ()

# Set the flag -Wall to activate all warnings and -pg to activate profiling
IF (${CMAKE_BUILD_TYPE} STREQUAL Debug)
	SET(CMAKE_CXX_FLAGS "-Wall")
	SET(CMAKE_C_FLAGS "-Wall")
ELSE()
	SET(CMAKE_CXX_FLAGS "-Wall -O2")
	SET(CMAKE_C_FLAGS "-Wall -O2")
ENDIF()

# CMake variable to choose whether the profiling option of gcc is activated 
# (-pg). 
IF (CMAKE_BUILD_TYPE MATCHES "Release")
    MESSAGE ("Profiling deactivated.")
ELSE ()
    MESSAGE ("Profiling activated.")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
ENDIF()

#
# Find Qmake for Linux OS
#
IF (UNIX)
    SET (QT_QMAKE_EXECUTABLE /usr/lib64/qt4/bin/qmake)
ENDIF ()

#
# Variables
#
SET (EXECUTABLE_NAME demo)
SET (SOURCE_FOLDER ${CMAKE_SOURCE_DIR}/src)
SET (RESOURCES_FOLDER ${CMAKE_SOURCE_DIR}/resources)
SET (EXTERN_FOLDER ${CMAKE_SOURCE_DIR}/extern)
SET (DSPATCH_FOLDER ${EXTERN_FOLDER}/dspatch)

IF (WIN32)
    SET (MINGW_DLL_DIR $ENV{MINGW_HOME}/bin)
    STRING (REPLACE "\\" "/" MINGW_DLL_DIR "${MINGW_DLL_DIR}") 
ENDIF ()

MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list *.h)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

#
# Include directories
#
# General includes
INCLUDE_DIRECTORIES (${CMAKE_SOURCE_DIR}/${SOURCE_FOLDER})
INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR})
#DSPATCH
INCLUDE_DIRECTORIES (${DSPATCH_FOLDER}/include)

HEADER_DIRECTORIES(LIST)
FOREACH(file_path ${LIST})
    INCLUDE_DIRECTORIES (${file_path})
ENDFOREACH()

#
# Link directories
#
LINK_DIRECTORIES(${EXECUTABLE_OUTPUT_PATH})

#
# Remove all DLL and SO files
#
MESSAGE ("Removing all DLL and SO files")
FILE (REMOVE_RECURSE ${EXECUTABLE_OUTPUT_PATH}/*.dll)
FILE (REMOVE_RECURSE ${EXECUTABLE_OUTPUT_PATH}/*.so)

# Create a symbolic link from source to destination. If destination exists, it 
# will be deleted before creating the link
MACRO (CREATE_SYMLINK source destination)
    IF (EXISTS ${destination})
        FILE (REMOVE ${destination})
    ENDIF ()
    EXECUTE_PROCESS (COMMAND ln -s ${source} ${destination})
ENDMACRO ()

#
# Copy all DLL and SO files
#
IF (WIN32)
    MESSAGE ("Copying all DLL files")

    #############
    # FOR MINGW
    #############

	#MINGW
	FILE (COPY ${MINGW_DLL_DIR}/libgcc_s_dw2-1.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH})
	FILE (COPY ${MINGW_DLL_DIR}/mingwm10.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH})
	FILE (COPY ${MINGW_DLL_DIR}/libstdc++-6.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH})
	
	#DSPATCH
	FILE (COPY ${DSPATCH_FOLDER}/lib/win32/libDSPatch.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH})
ELSE ()
    MESSAGE ("Copying all SO files")	
	
	#DSPATCH
    FILE (COPY ${DSPATCH_FOLDER}/lib/linux/libDSPatch.so DESTINATION ${EXECUTABLE_OUTPUT_PATH})
	
ENDIF ()

#
# Qt 4
#
FIND_PACKAGE(Qt4 REQUIRED)
SET(QT_USE_QTXML TRUE)
SET(QT_USE_QTSQL TRUE)
SET(QT_USE_QTMULTIMEDIA TRUE)
SET(QT_USE_QTNETWORK TRUE)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

#
# Source files (.cpp)
#
FILE (GLOB_RECURSE PROJECT_SOURCES ${SOURCE_FOLDER}/*.cpp ${SOURCE_FOLDER}/*.c)

#
# Headers files (.h)
#
FILE (GLOB_RECURSE PROJECT_HEADERS ${SOURCE_FOLDER}/*.h)

#
# Ui files
#
FILE (GLOB_RECURSE PROJECT_FORMS ${SOURCE_FOLDER}/*.ui)

#
# Resources files
#
FILE (GLOB_RECURSE PROJECT_RESOURCES ${RESOURCES_FOLDER}/*.qrc)

#
# Libraries
#
IF (WIN32)
	SET (PROJECT_LIBS 
		${QT_LIBRARIES}
		${DSPATCH_FOLDER}/lib/win32/libDSPatch.dll.a
		)
ELSE ()	
    SET (PROJECT_LIBS 
        ${QT_LIBRARIES} 
		${DSPATCH_FOLDER}/lib/linux/libDSPatch.a
        )
ENDIF ()

########################################################################
# Generation
########################################################################

#
# moc_XXX.cxx generation
#
QT4_WRAP_CPP (PROJECT_GENERATED_HEADERS_MOC ${PROJECT_HEADERS})

#
# ui_XXX.h generation
#
QT4_WRAP_UI (PROJECT_GENERATED_FORMS_HEADER ${PROJECT_FORMS})

#
# qrc_XXX.cxx generation
#
QT4_ADD_RESOURCES (PROJECT_GENERATED_RESOURCES_RCC ${PROJECT_RESOURCES})

#
# Executable generation
#
SET (EXECUTABLE_OPTS )
IF (WIN32 AND CMAKE_BUILD_TYPE MATCHES "Release")
    SET(EXECUTABLE_OPTS ${EXECUTABLE_OPTS} WIN32)
ENDIF()

ADD_EXECUTABLE (
  ${EXECUTABLE_NAME}       				# Executable name
  ${EXECUTABLE_OPTS}                    # Options
  ${PROJECT_SOURCES}                    # .cpp --> .o
  ${PROJECT_GENERATED_HEADERS_MOC}      # moc XXX.h --> moc_XXX.cxx
  ${PROJECT_GENERATED_FORMS_HEADER}     # uic XXX.ui --> ui_XXX.h
  ${PROJECT_GENERATED_RESOURCES_RCC}    # resources
)

#
# Link libraries
#
TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} ${PROJECT_LIBS})
