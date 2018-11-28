cmake_minimum_required( VERSION 3.0 )
project(opengl)

find_package( OpenGL REQUIRED )
find_package( glfw3 REQUIRED )
find_package( glad REQUIRED )
find_package( boost REQUIRED )

include_directories("./includes/" ${GLFW3_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${BOOST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

# set target bin
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# other
include(${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/src/textures/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/src/trans/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/src/projection/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/src/camera/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/src/breakout/CMakeLists.txt)

add_executable(window src/window.cpp)
target_link_libraries(window LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(square src/square.cpp)
target_link_libraries(square LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(uniform src/shaders/uniform.cpp)
target_link_libraries(uniform LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})


# exercise
add_executable(e1 src/trangle/e1.cpp)
target_link_libraries(e1 LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(e2 src/trangle/e2.cpp)
target_link_libraries(e2 LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(e3 src/trangle/e3.cpp)
target_link_libraries(e3 LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
