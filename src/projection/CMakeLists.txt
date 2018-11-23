add_executable(projection ${CMAKE_CURRENT_LIST_DIR}/projection.cpp ${PROJECT_SOURCE_DIR}/src/comm/Shader.cpp ${PROJECT_SOURCE_DIR}/src/comm/std_image.cpp)
target_link_libraries(projection LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
