cmake_minimum_required(VERSION 2.8)



set (INTERN_LINK_LIBS ${INTERN_LINK_LIBS} gui io utils)
set (EXTERN_LINK_LIBS ${EXTERN_LINK_LIBS} Qt5::Widgets Qt5::SerialPort)

# target
add_executable(${PROJECT_NAME} main.cpp ${RESOURCES_DIR}/resources.qrc)
target_link_libraries(${PROJECT_NAME} ${INTERN_LINK_LIBS} ${EXTERN_LINK_LIBS})
