add_executable(camera ${CMAKE_CURRENT_LIST_DIR}/camera.cpp ${PROJECT_SOURCE_DIR}/src/comm/Shader.cpp ${PROJECT_SOURCE_DIR}/src/comm/std_image.cpp)
target_link_libraries(camera LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})


add_executable(came_move ${CMAKE_CURRENT_LIST_DIR}/came_move.cpp ${PROJECT_SOURCE_DIR}/src/comm/Shader.cpp ${PROJECT_SOURCE_DIR}/src/comm/std_image.cpp ${PROJECT_SOURCE_DIR}/src/comm/camera.cpp)
target_link_libraries(came_move LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(came_e1 ${CMAKE_CURRENT_LIST_DIR}/came_e1.cpp ${PROJECT_SOURCE_DIR}/src/comm/Shader.cpp ${PROJECT_SOURCE_DIR}/src/comm/std_image.cpp ${PROJECT_SOURCE_DIR}/src/comm/camera.cpp)
target_link_libraries(came_e1 LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(came_e2 ${CMAKE_CURRENT_LIST_DIR}/came_e2.cpp ${PROJECT_SOURCE_DIR}/src/comm/Shader.cpp ${PROJECT_SOURCE_DIR}/src/comm/std_image.cpp ${CMAKE_CURRENT_LIST_DIR}/camera_e2.cpp)
target_link_libraries(came_e2 LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
