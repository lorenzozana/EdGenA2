#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(EdGenA2)
set(useROOT true)        # use true or false
include(FindROOT.cmake)

include_directories(${PROJECT_SOURCE_DIR} ${ROOT_INCLUDE_DIR} )
set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}	
  )
file(GLOB sources 
  ${PROJECT_SOURCE_DIR}/EdGen.cxx
  ${PROJECT_SOURCE_DIR}/EdInput.cxx
  ${PROJECT_SOURCE_DIR}/EdModel.cxx
  ${PROJECT_SOURCE_DIR}/EdHisto.cxx
  ${PROJECT_SOURCE_DIR}/EdOutput.cxx
  ${PROJECT_SOURCE_DIR}/EdPhysics.cxx
  ${PROJECT_SOURCE_DIR}/EdGenPhaseSpace.cxx
  ${PROJECT_SOURCE_DIR}/EdProcess.cxx
  ${PROJECT_SOURCE_DIR}/EdCrossSection.cxx
  )
file(GLOB headers 
  ${PROJECT_SOURCE_DIR}/EdGen.h
  ${PROJECT_SOURCE_DIR}/EdInput.h
  ${PROJECT_SOURCE_DIR}/EdModel.h
  ${PROJECT_SOURCE_DIR}/EdHisto.h
  ${PROJECT_SOURCE_DIR}/EdOutput.h
  ${PROJECT_SOURCE_DIR}/EdPhysics.h	
  ${PROJECT_SOURCE_DIR}/EdGenPhaseSpace.h	
  ${PROJECT_SOURCE_DIR}/EdProcess.h
  ${PROJECT_SOURCE_DIR}/EdCrossSection.h
  )

link_directories( ${LINK_DIRECTORIES})


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(EdGenA2 ${sources} ${headers})

set(LINK_LIBRARIES
  ${ROOT_LIBRARIES} -lThread -lHtml -lGed -lEG -lGeom
  )
target_link_libraries(EdGenA2 ${LINK_LIBRARIES})


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output) 
#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS EdGenA2 DESTINATION bin)


