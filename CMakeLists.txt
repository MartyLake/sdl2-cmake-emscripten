cmake_minimum_required(VERSION 3.5)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/ThirdParty/tcbrindle/sdl2-cmake-scripts-88fd08a/")
set (CMAKE_CXX_STANDARD 14)


message("CMAKE_SYSTEM_NAME [${CMAKE_SYSTEM_NAME}]")
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")
  set(PROJECT_NAME "gameSdl2.html")
else()
  set(PROJECT_NAME "gameSdl2")
endif()

project (${PROJECT_NAME})

file(GLOB PROJECT_SOURCES
    "src/*.h"
    "src/*.cpp"
)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
configure_file("${CMAKE_SOURCE_DIR}/rsc/test.bmp"
  "${CMAKE_BINARY_DIR}/rsc/test.bmp"
  COPYONLY
)
configure_file("${CMAKE_SOURCE_DIR}/rsc/up.bmp"
  "${CMAKE_BINARY_DIR}/rsc/up.bmp"
  COPYONLY
)
configure_file("${CMAKE_SOURCE_DIR}/rsc/down.bmp"
  "${CMAKE_BINARY_DIR}/rsc/down.bmp"
  COPYONLY
)
configure_file("${CMAKE_SOURCE_DIR}/rsc/left.bmp"
  "${CMAKE_BINARY_DIR}/rsc/left.bmp"
  COPYONLY
)
configure_file("${CMAKE_SOURCE_DIR}/rsc/right.bmp"
  "${CMAKE_BINARY_DIR}/rsc/right.bmp"
  COPYONLY
)
configure_file("${CMAKE_SOURCE_DIR}/rsc/press.bmp"
  "${CMAKE_BINARY_DIR}/rsc/press.bmp"
  COPYONLY
)
configure_file("${CMAKE_SOURCE_DIR}/rsc/BebasNeue Bold.ttf"
  "${CMAKE_BINARY_DIR}/rsc/BebasNeue Bold.ttf"
  COPYONLY
)

if ( CMAKE_COMPILER_IS_GNUCC )
  target_compile_options(${PROJECT_NAME} PRIVATE "-Wall")
endif ( CMAKE_COMPILER_IS_GNUCC )
if ( MSVC )
  target_compile_options(${PROJECT_NAME} PRIVATE "/W4")
endif ( MSVC )

message("CMAKE_SYSTEM_NAME [${CMAKE_SYSTEM_NAME}]")
  
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  target_link_libraries(${PROJECT_NAME} "-s WASM=1") #web assembly FTW
  target_link_libraries(${PROJECT_NAME} "-s USE_SDL=2")
  target_link_libraries(${PROJECT_NAME} "-s USE_SDL_IMAGE=2")
  target_link_libraries(${PROJECT_NAME} "-s USE_SDL_IMAGE_FORMATS='[\"png\"]'")
  target_link_libraries(${PROJECT_NAME} "--preload-file rsc")
  target_link_libraries(${PROJECT_NAME} "-o gameSdl2.html")
  target_link_libraries(${PROJECT_NAME} "-s DEMANGLE_SUPPORT=1")
  target_compile_options(${PROJECT_NAME} PUBLIC "-O2") #creates the runtime resources
  target_link_libraries(${PROJECT_NAME} "-O2") #creates the runtime resources
else()
  message("${CMAKE_SOURCE_DIR}")
  set(SDL2_PATH "${CMAKE_SOURCE_DIR}/../sdl2lib/VC/")
  if(NOT IS_DIRECTORY "${SDL2_PATH}")
    message(WARNING "SDL2_PATH: " "${SDL2_PATH}" " is not a valid directory")
  else()
    message(STATUS "SDL2_PATH: " "${SDL2_PATH}" " found")
  endif()
  find_package(SDL2 REQUIRED)
  set(SDL2_IMAGE_PATH "${CMAKE_SOURCE_DIR}/../sdl2lib-image/VC/")
  if(NOT IS_DIRECTORY "${SDL2_IMAGE_PATH}")
    message(WARNING "SDL2_IMAGE_PATH: " "${SDL2_IMAGE_PATH}" " is not a valid directory")
  else()
    message(STATUS "SDL2_IMAGE_PATH: " "${SDL2_IMAGE_PATH}" " found")
  endif()
  find_package(SDL2_image REQUIRED)
  set(SDL2_TTF_PATH "${CMAKE_SOURCE_DIR}/../sdl2lib-ttf/VC/")
  if(NOT IS_DIRECTORY "${SDL2_TTF_PATH}")
    message(WARNING "SDL2_TTF_PATH: " "${SDL2_TTF_PATH}" " is not a valid directory")
  else()
    message(STATUS "SDL2_TTF_PATH: " "${SDL2_TTF_PATH}" " found")
  endif()
  find_package(SDL2_ttf REQUIRED)
  target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} 
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES})
endif()

