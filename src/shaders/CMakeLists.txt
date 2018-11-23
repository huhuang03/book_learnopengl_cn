message("Hello in shader cmakelists")
message(${PROJECT_SOURCE_DIR})

message(${CMAKE_CURRENT_LIST_DIR})

add_executable(shader_moreVetexAttr ${CMAKE_CURRENT_LIST_DIR}/morevetexattr.cpp ${PROJECT_SOURCE_DIR}/src/comm/Shader.cpp)
target_link_libraries(shader_moreVetexAttr LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(shader_e1 ${CMAKE_CURRENT_LIST_DIR}/e1.cpp ${PROJECT_SOURCE_DIR}/src/comm/Shader.cpp)
target_link_libraries(shader_e1 LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})


add_executable(shader_e2 ${CMAKE_CURRENT_LIST_DIR}/e2.cpp ${PROJECT_SOURCE_DIR}/src/comm/Shader.cpp)
target_link_libraries(shader_e2 LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(shader_e3 ${CMAKE_CURRENT_LIST_DIR}/e3.cpp ${PROJECT_SOURCE_DIR}/src/comm/Shader.cpp)
target_link_libraries(shader_e3 LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
