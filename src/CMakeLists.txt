cmake_minimum_required(VERSION 2.8)

SET(SRC main.cpp
        app.h app.cpp
        crowd.h crowd.cpp)

ADD_EXECUTABLE(sfml-horde-example ${SRC})
TARGET_LINK_LIBRARIES(sfml-horde-example
                      ${Horde3D_LIBRARIES} ${SFML_LIBRARIES})

