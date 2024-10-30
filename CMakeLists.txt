cmake_minimum_required(VERSION 3.26)
project(opengl_learn)
set(CMAKE_CXX_STANDARD 17)
if (${CMAKE_HOST_SYSTEM} MATCHES "Windows")
    set(VCPKG_INSTALLED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/vcpkg_installed/x64-windows")
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_INSTALLED_DIR}/share/vcpkg/scripts/buildsystems/vcpkg.cmake")
    set(CMAKE_PREFIX_PATH ${VCPKG_INSTALLED_DIR})
    include_directories(${VCPKG_INSTALLED_DIR}/include
            "${CMAKE_CURRENT_SOURCE_DIR}/include"
            "${CMAKE_CURRENT_SOURCE_DIR}/src")
    link_directories(${VCPKG_INSTALLED_DIR}/lib
            ${VCPKG_INSTALLED_DIR}/debug/lib
    )
    file(GLOB_RECURSE native_srcs src/*.cpp include/*.h )
    add_executable(${PROJECT_NAME} ${native_srcs})

    set(opengl_DIR ${VCPKG_INSTALLED_DIR}/share/opengl)
    find_package(OpenGL REQUIRED)

    set(glfw_DIR ${VCPKG_INSTALLED_DIR}/share/glfw)
    find_package(glfw3 CONFIG REQUIRED)

    set(glew_DIR ${VCPKG_INSTALLED_DIR}/share/glew)
    find_package(glew CONFIG REQUIRED)

    set(glslang_DIR ${VCPKG_INSTALLED_DIR}/share/glslang)
    find_package(glslang CONFIG REQUIRED)

    set(glm_DIR ${VCPKG_INSTALLED_DIR}/share/glm)
    find_package(glm CONFIG REQUIRED)

    set(soil_DIR ${VCPKG_INSTALLED_DIR}/share/soil)
    find_package(soil CONFIG REQUIRED)
    target_link_libraries(${PROJECT_NAME}
            OpenGL32
            glfw3dll
            glew32s
            glslang
            soil
    )
elseif (${CMAKE_HOST_SYSTEM} MATCHES "Linux")
    file(GLOB_RECURSE SOURCES src/*.* include/*.*)
    add_executable(OpenGL_Learn ${SOURCES})
    target_link_libraries(OpenGL_Learn
            OpenGL
            GLEW
            glfw
            SOIL)
endif ()
