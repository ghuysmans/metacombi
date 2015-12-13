cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/modules")

project(metacombi)
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)

find_package(SDL)
find_package(SDL_ttf)
find_package(SDL_gfx)
find_package(SDL_image)
if(SDL_FOUND AND SDLTTF_FOUND AND SDLGFX_FOUND AND SDLIMAGE_FOUND)
	link_libraries(${LIBS} ${SDL_LIBRARY} ${SDLTTF_LIBRARY} ${SDLGFX_LIBRARY} ${SDLIMAGE_LIBRARY})
	set(USE_SDL 1) #we have to use a separate variable to ensure all deps are met
endif(SDL_FOUND AND SDLTTF_FOUND AND SDLGFX_FOUND AND SDLIMAGE_FOUND)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

#config header
get_directory_property(COMPILE_DEFINITIONS COMPILE_DEFINITIONS)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
	"${CMAKE_CURRENT_BINARY_DIR}/config.h")

#Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
	#adapted from https://www.tty1.net/blog/2014/cmake-doxygen_en.html
	set(doxyfile_in "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in")
	set(doxyfile "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
	configure_file("${doxyfile_in}" "${doxyfile}")
	add_custom_target(doc
		COMMAND "${DOXYGEN_EXECUTABLE}" "${doxyfile}"
		WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
		COMMENT "Generating API documentation with Doxygen"
		VERBATIM)
endif(DOXYGEN_FOUND)

#unit tests
include(tests/tests.cmake)

file(GLOB Source src/*.cpp src/metaheuristics/*.cpp)
add_executable(metacombi ${Source} src/programs/metacombi.cpp)
add_executable(monitor ${Source} src/programs/monitor.cpp)
set_target_properties(metacombi PROPERTIES LINKER_LANGUAGE CXX)
