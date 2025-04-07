cmake_minimum_required(VERSION 3.10)

# Project name
project(DeformationTransferVisualizer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
set(SOURCES
    main.cpp
    ModelLoader.cpp
    Shader.cpp
)

# Add header files
set(HEADERS
    ModelLoader.h
    Shader.h
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLFW
find_package(glfw3 REQUIRED)

# Find GLEW
find_package(GLEW REQUIRED)

# Find OpenMesh
find_package(OpenMesh REQUIRED)

# Include directories
include_directories(
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${OPENMESH_INCLUDE_DIRS}
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    glfw
    GLEW::GLEW
    OpenMeshCore
    OpenMeshTools
)
