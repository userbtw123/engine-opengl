cmake_minimum_required(VERSION 3.20)

project(engine2 LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/EHs- /EHc- /D_HAS_EXCEPTIONS=0)
else()
  add_compile_options(-fno-exceptions -fno-rtti)
endif()

include(FetchContent)

FetchContent_Declare(
    glfw 
    GIT_REPOSITORY https://github.com/glfw/glfw.git 
    GIT_TAG 3.4
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	1.0.3
)

FetchContent_Declare(
	imgui
	GIT_REPOSITORY	https://github.com/ocornut/imgui.git
	GIT_TAG 	v1.92.5
)

FetchContent_MakeAvailable(glfw glm imgui)

add_library(glad STATIC "thirdparty/glad/src/glad.c")

FetchContent_GetProperties(imgui SOURCE_DIR IMGUI_SOURCE_DIR)

set(IMGUI_BACKEND_SOURCES
    "${IMGUI_SOURCE_DIR}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
)

set(IMGUI_SOURCES
    "${IMGUI_SOURCE_DIR}/imgui.cpp"
    "${IMGUI_SOURCE_DIR}/imgui_draw.cpp"
    "${IMGUI_SOURCE_DIR}/imgui_tables.cpp"
    "${IMGUI_SOURCE_DIR}/imgui_widgets.cpp"
    "${IMGUI_SOURCE_DIR}/imgui_demo.cpp"
    "${IMGUI_SOURCE_DIR}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
)

set(CORE_SOURCES
  src/core/window.cpp
)

set(RENDERER_SOURCES
)

add_executable(${PROJECT_NAME}
    "src/main.cpp"
    ${CORE_SOURCES}
    ${IMGUI_BACKEND_SOURCES}
    ${IMGUI_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "thirdparty/glad/include" 
    "include" 
    ${IMGUI_SOURCE_DIR} 
    "${IMGUI_SOURCE_DIR}/backends"
)

find_package(OpenGL REQUIRED)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE 
    glad
    OpenGL::OpenGL 
    glfw 
    glm::glm
)
