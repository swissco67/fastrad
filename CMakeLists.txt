	#----------------------------------------------------------------------------	
	# Setup the project	
	cmake_minimum_required(VERSION 2.6 FATAL_ERROR)	
	project(Ht)	
	#----------------------------------------------------------------------------
# Find Geant4 package, activating all available Vis drivers by default
# You can set WITH_GEANT4_VIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()
	
	#----------------------------------------------------------------------------	
	# Find Geant4 package, no UI and Vis drivers activated	
	#	
	find_package(Geant4 REQUIRED)	
		
	#----------------------------------------------------------------------------	
	# Setup Geant4 include directories and compile definitions	
	#	
	include(${Geant4_USE_FILE})	
		
		
	#----------------------------------------------------------------------------	
	# Locate sources and headers for this project	
	#	
	include_directories(${PROJECT_SOURCE_DIR}/include   
	                    ${Geant4_INCLUDE_DIR})	
	file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)	
	file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)	
		
	#----------------------------------------------------------------------------	
	# Add the executables, and link it to the Geant4 libraries	
	#	
	add_executable(Ht Ht.cc ${sources} ${headers})	
	target_link_libraries(Ht ${Geant4_LIBRARIES} )	
