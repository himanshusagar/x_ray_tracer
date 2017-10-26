cmake_minimum_required(VERSION 3.7)
set(AssignmentNameHere Project)
project(${AssignmentNameHere})

set(CMAKE_CXX_STANDARD 11)
file(GLOB DEPS_SOURCES ext/glad/src/glad.c)
macro(pre_build TARGET_NAME)
    add_custom_target( ${TARGET_NAME}_PRE_BUILD ALL )
    message("STATUS" "current source dir in macro " ${CMAKE_CURRENT_SOURCE_DIR})
    add_custom_command(
            TARGET ${TARGET_NAME}_PRE_BUILD
            ${ARGN}
            PRE_BUILD
            COMMENT "${TARGET_NAME}_PRE_BUILD ..."
    )

    add_dependencies(${TARGET_NAME} ${TARGET_NAME}_PRE_BUILD)
endmacro()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin)
include_directories("ext/glm/"
        "ext/glfw/include"
        "ext/glad/include"
        "src/"
        )
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(ext/glfw)

set(PLATFORM_LINK )
if (UNIX)
    set(PLATFORM_LINK -ldl)
endif (UNIX)


file(GLOB SRC_CUSTOM

        "src/objects/triangle.cpp"
        "src/objects/sphere.cpp"
        "src/objects/sphere.h"

        "src/utils/matrix3D.cpp"
        "src/utils/matrix3D.h"

        "src/utils/utility.hpp"
        "src/utils/utility.cpp"

        "src/utils/vector3D.cpp"
        "src/utils/vector3D.h"

        "src/lights/pointlightsource.h"
        "src/lights/arealightsource.h"

        "src/materials/PhongMaterial.cpp"
        "src/materials/PhongMaterial.h"
        "src/materials/DielectricPhongMaterial.h"
        "src/materials/DielectricPhongMaterial.cpp"


        "src/materials/ReflectivePhongMaterial.cpp"
        "src/materials/ReflectivePhongMaterial.h"

        "src/materials/RefractivePhongMaterial.cpp"
        "src/materials/RefractivePhongMaterial.h"

        "src/materials/GlossyMaterial.cpp"
        "src/materials/GlossyMaterial.h"





        "src/objects/Cylinder.cpp"
        "src/objects/Cylinder.h"


        "src/setup/world.cpp"
        "src/setup/world.h"
        "src/camera/camera.h"
        "src/camera/camera.cpp"
        "src/setup/color.h"
        "src/setup/color.cpp"

        "src/setup/ray.h"
        "src/setup/ray.cpp"

        "src/setup/lightsource.h"
        "src/setup/material.h"
        "src/setup/material.cpp"
        "src/setup/object.h"

        "src/setup/random_gen.h"
        "src/setup/renderengine.cpp"
        "src/setup/renderengine.h"
        "src/setup/scene.cpp"
        "src/setup/scene.h"




        "src/setup/structs.h"

        "src/first/provider.cc"

        "src/setup/random_gen.h"
        "src/objects/triangle.h")



file(GLOB SRC_CPP "src/*.cpp")
file(GLOB SRC_HDR "src/*.h")

set(SOURCE_FILES ${SRC_CPP} ${SRC_HDR})

#TODO add your source files here
set(SOURCE_FILES main.cpp ${SRC_CPP} ${SRC_HDR} ${SRC_CUSTOM})

add_executable(${AssignmentNameHere} ${SOURCE_FILES} ${DEPS_SOURCES})
target_link_libraries(${AssignmentNameHere} glfw ${GLFW_LIBRARIES} ${PLATFORM_LINK})

pre_build(${AssignmentNameHere}
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/bin/Resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory   ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${CMAKE_CURRENT_SOURCE_DIR}/bin/Resources)