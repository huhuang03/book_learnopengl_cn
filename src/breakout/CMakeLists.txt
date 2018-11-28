add_executable(game ${CMAKE_CURRENT_LIST_DIR}/Game.cpp ${PROJECT_SOURCE_DIR}/src/breakout/texture.cpp ${PROJECT_SOURCE_DIR}/src/breakout/shader.cpp ${PROJECT_SOURCE_DIR}/src/comm/std_image.cpp)
target_link_libraries(game LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
