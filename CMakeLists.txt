# - CmakeLists.txt for building an application

#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(exampleN01)

#----------------------------------------------------------------------------
# check MPI package...
find_package(MPI REQUIRED)
# modify these var. if needed
set(CMAKE_CXX_COMPILER mpicxx)
#set(CMAKE_CXX_INCLUDE_PATH )

#------------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
option(WITH_GEANT4_UIVIS "Build PMT with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()
SET(Geant4_DIR /home/hzy/geant4/geant4-install/lib/Geant4-10.1.3)
#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})
#

#----------------------------------------------------------------------------
# Add G4mpi library
#
SET(Geant4_LIBRARIES ${Geant4_LIBRARIES} G4mpi)
ADD_LIBRARY(G4mpi SHARED IMPORTED)
SET_PROPERTY(TARGET G4mpi APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
SET_TARGET_PROPERTIES(G4mpi PROPERTIES
  IMPORTED_LOCATION_RELEASE "${Geant4_DIR}/../libG4mpi.so"
  IMPORTED_SONAME_RELEASE "libG4mpi.so"
)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${Geant4_INCLUDE_DIR})


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(exampleN01 exampleN01.cc ${sources} ${headers})
target_link_libraries(exampleN01 ${Geant4_LIBRARIES})
set_target_properties(exampleN01
                      PROPERTIES INSTALL_RPATH
                      ${Geant4_DIR}/..
                      BUILD_WITH_INSTALL_RPATH TRUE)

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build exampleN01. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(exampleN01_SCRIPTS
    run.mac
	vis.mac

  )

foreach(_script ${exampleN01_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS exampleN01 RUNTIME DESTINATION bin)
