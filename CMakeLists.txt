cmake_minimum_required(VERSION 3.5)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/ThirdParty/tcbrindle/sdl2-cmake-scripts-88fd08a/")
set (CMAKE_CXX_STANDARD 11)


message("CMAKE_SYSTEM_NAME [${CMAKE_SYSTEM_NAME}]")
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")
  set(PROJECT_NAME "gameSdl2.html")
else()
  set(PROJECT_NAME "gameSdl2")
endif()

project (${PROJECT_NAME})
add_executable(${PROJECT_NAME} src/main.cpp)
configure_file("${CMAKE_SOURCE_DIR}/rsc/test.bmp"
  "${CMAKE_BINARY_DIR}/rsc/test.bmp"
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
  find_package(SDL2 REQUIRED)
  find_package(SDL2_image REQUIRED)
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

