cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

SET(PROJECTNAME Celebrimbor)

SET(ROOT_DIR ..)

PROJECT(${PROJECTNAME})

# Add .lib files
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/${ROOT_DIR}/lib)

FILE(GLOB_RECURSE EXAMPLE_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

FILE(GLOB_RECURSE PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/${ROOT_DIR}/lib/*.cpp)

FILE(GLOB_RECURSE PROJECT_HEADERS ${CMAKE_SOURCE_DIR}/${ROOT_DIR}/include/*.h)

FILE(GLOB_RECURSE THIRD_PARTY_SOURCES ${CMAKE_SOURCE_DIR}/${ROOT_DIR}/third-party/lib/*.c)

FILE(GLOB_RECURSE THIRD_PARTY_HEADERS ${CMAKE_SOURCE_DIR}/${ROOT_DIR}/third-party/include/*.h)

ADD_EXECUTABLE(${PROJECTNAME} ${EXAMPLE_SOURCES} ${PROJECT_HEADERS} ${PROJECT_SOURCES} ${THIRD_PARTY_HEADERS} ${THIRD_PARTY_SOURCES})

# We need a CMAKE_DIR with some code to find external dependencies
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/${ROOT_DIR}/cmake/)

# OpenGL
SET(OpenGL_GL_PREFERENCE GLVND)
FIND_PACKAGE(OpenGL REQUIRED)

# GLM
FIND_PACKAGE(GLM REQUIRED)
MESSAGE(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

# GLFW3
FIND_PACKAGE(GLFW3 REQUIRED)
MESSAGE(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

# GLAD
ADD_LIBRARY(GLAD ${CMAKE_SOURCE_DIR}/${ROOT_DIR}/third-party/lib/glad/gl.c)

SET(LIBRARIES ${LIBRARIES} ${GLFW3_LIBRARY} GLAD ${OPENGL_LIBRARY} ${CMAKE_DL_LIBS})

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/${ROOT_DIR}/include
    ${CMAKE_SOURCE_DIR}/${ROOT_DIR}/third-party/include/glad/
    ${CMAKE_SOURCE_DIR}/${ROOT_DIR}/third-party/include/khr/
    ${CMAKE_SOURCE_DIR}/${ROOT_DIR}/third-party/include/glm/
    ${CMAKE_SOURCE_DIR}/${ROOT_DIR}/third-party/include/lin-math/
    ${CMAKE_SOURCE_DIR}/${ROOT_DIR}/third-party/include/stb_image/
    /usr/include/GLFW
)

TARGET_LINK_LIBRARIES(${PROJECTNAME} ${LIBRARIES})

TARGET_COMPILE_OPTIONS(${PROJECTNAME} PUBLIC -std=c++20 -Wall -g)