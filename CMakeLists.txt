cmake_minimum_required(VERSION 3.1)
project(3DFinalProjecrt)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# libigl
option(LIBIGL_WITH_OPENGL            "Use OpenGL"         ON)
option(LIBIGL_WITH_OPENGL_GLFW       "Use GLFW"           ON)
option(LIBIGL_WITH_VIEWER            "Use OpenGL viewer"  ON)

find_package(LIBIGL REQUIRED QUIET)

# Add your project files
file(GLOB SRCFILES *.cpp)
add_executable(${PROJECT_NAME}_bin ${SRCFILES} src/main.cpp src/utils/Utils.cpp src/utils/Utils.h src/find_core/SimulatedAnnealingManager.cpp src/find_core/SimulatedAnnealingManager.h)
target_link_libraries(${PROJECT_NAME}_bin igl::core igl::opengl_glfw igl::opengl_glfw_imgui)
