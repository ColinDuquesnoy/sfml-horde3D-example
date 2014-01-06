cmake_minimum_required(VERSION 2.8)
PROJECT(IrrlichtCMake)

SET(SRC main.cpp
        app.h app.cpp
        crowd.h crowd.cpp)

ADD_EXECUTABLE(sfml-horde-example ${SRC})
TARGET_LINK_LIBRARIES(sfml-horde-example
                      ${SFML_LIBRARIES} ${Horde3D_LIBRARIES} ${OPENGL_LIBRARIES})

