message(${CMAKE_CURRENT_LIST_DIR})

add_executable(trans_move ${CMAKE_CURRENT_LIST_DIR}/trans_move.cpp ${PROJECT_SOURCE_DIR}/src/comm/Shader.cpp ${PROJECT_SOURCE_DIR}/src/comm/std_image.cpp)
target_link_libraries(trans_move LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(trans ${CMAKE_CURRENT_LIST_DIR}/trans.cpp ${PROJECT_SOURCE_DIR}/src/comm/Shader.cpp ${PROJECT_SOURCE_DIR}/src/comm/std_image.cpp)
target_link_libraries(trans LINK_PUBLIC ${OPENGL_LIBRARIES} glfw glad ${BOOST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
