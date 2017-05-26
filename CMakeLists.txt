cmake_minimum_required(VERSION 3.5)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/ThirdParty/tcbrindle/sdl2-cmake-scripts-88fd08a/")
set (CMAKE_CXX_STANDARD 11)

project (gameSdl2)
add_executable(gameSdl2 src/main.cpp)
configure_file("${CMAKE_SOURCE_DIR}/rsc/test.bmp"
  "${CMAKE_BINARY_DIR}/rsc/test.bmp"
  COPYONLY
)

if ( CMAKE_COMPILER_IS_GNUCC )
    target_compile_options(gameSdl2 PRIVATE "-Wall")
endif ( CMAKE_COMPILER_IS_GNUCC )
if ( MSVC )
  target_compile_options(gameSdl2 PRIVATE "/W4")
endif ( MSVC )

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
target_include_directories(gameSdl2 SYSTEM PUBLIC
  ${SDL2_INCLUDE_DIR}
  ${SDL2_IMAGE_INCLUDE_DIR}
  ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(gameSdl2 
  ${SDL2_LIBRARY}
  ${SDL2_IMAGE_LIBRARIES}
  ${SDL2_TTF_LIBRARIES})

