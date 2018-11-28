add_executable(projection ${CMAKE_CURRENT_LIST_DIR}/projection.cpp ${PROJECT_SOURCE_DIR}/src/comm/Shader.cpp ${PROJECT_SOURCE_DIR}/src/comm/std_image.cpp)
target_link_libraries(projection LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(more3d ${CMAKE_CURRENT_LIST_DIR}/more3d.cpp ${PROJECT_SOURCE_DIR}/src/comm/Shader.cpp ${PROJECT_SOURCE_DIR}/src/comm/std_image.cpp)
target_link_libraries(more3d LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(proj_e1 ${CMAKE_CURRENT_LIST_DIR}/proj_e1.cpp ${PROJECT_SOURCE_DIR}/src/comm/Shader.cpp ${PROJECT_SOURCE_DIR}/src/comm/std_image.cpp)
target_link_libraries(proj_e1 LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(proj_e2 ${CMAKE_CURRENT_LIST_DIR}/proj_e2.cpp ${PROJECT_SOURCE_DIR}/src/comm/Shader.cpp ${PROJECT_SOURCE_DIR}/src/comm/std_image.cpp)
target_link_libraries(proj_e2 LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(proj_e3 ${CMAKE_CURRENT_LIST_DIR}/proj_e3.cpp ${PROJECT_SOURCE_DIR}/src/comm/Shader.cpp ${PROJECT_SOURCE_DIR}/src/comm/std_image.cpp)
target_link_libraries(proj_e3 LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
