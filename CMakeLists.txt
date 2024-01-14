cmake_minimum_required(VERSION 3.5)
set(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)

project(r-type LANGUAGES CXX)

find_package(SFML 2.5 COMPONENTS system window graphics audio QUIET)

if(NOT SFML_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG        2.5.0
    )
    set(SFML_BUILD_STATIC_LIBS TRUE)
    FetchContent_MakeAvailable(SFML)
endif()

file(COPY ${CMAKE_SOURCE_DIR}/includes/assets DESTINATION ${EXECUTABLE_OUTPUT_PATH}/includes)

set(CLIENT_SRC_PATH "src/Client")
set(CLIENT_INCLUDE_PATH "includes/Client")

set(SERVER_SRC_PATH "src/Server")
set(SERVER_INCLUDE_PATH "includes/Server")

set(ECS_SRC_PATH "src//ECS")
set(ECS_INCLUDE_PATH "includes//ECS")

set(SRC_CLIENT
        ${CLIENT_SRC_PATH}/main.cpp
        ${CLIENT_SRC_PATH}/collision.cpp
        ${CLIENT_SRC_PATH}/event.cpp
        ${CLIENT_SRC_PATH}/createBulletFoe.cpp
        ${CLIENT_SRC_PATH}/redirectFile.cpp
        ${CLIENT_SRC_PATH}/createSong.cpp
        ${CLIENT_SRC_PATH}/nextRound.cpp
        ${CLIENT_SRC_PATH}/printHelp.cpp
        ${CLIENT_SRC_PATH}/shipExplode.cpp
        ${CLIENT_SRC_PATH}/showSprite.cpp
        ${CLIENT_SRC_PATH}/level.cpp
        ${CLIENT_SRC_PATH}/newStrat.cpp
        ${CLIENT_SRC_PATH}/spriteAnimation.cpp
        ${CLIENT_SRC_PATH}/Editor/levelEditor.cpp
)

set(HPP_CLIENT
        ${CLIENT_INCLUDE_PATH}/window.hpp
        ${CLIENT_INCLUDE_PATH}/functions.hpp
        ${CLIENT_INCLUDE_PATH}/SFML.hpp
)

set(SRC_SERVER
        ${SERVER_SRC_PATH}/main.cpp
)

#set(HPP_SERVER
#        ${SERVER_INCLUDE_PATH}/window.hpp
#)

set(SRC_ECS
        ${ECS_SRC_PATH}/addComponent.cpp
        ${ECS_SRC_PATH}/addSystem.cpp
        ${ECS_SRC_PATH}/killEntity.cpp
        ${ECS_SRC_PATH}/registerComponent.cpp
)

set(HPP_ECS
        ${ECS_INCLUDE_PATH}/step.hpp
)

add_executable(r-type_client ${SRC_CLIENT} ${HPP_CLIENT})
add_executable(r-type_server ${SRC_SERVER})
add_library(ecsProject SHARED ${SRC_ECS} ${HPP_ECS})

target_link_libraries(r-type_client
        ecsProject
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
)

target_include_directories(r-type_client PUBLIC
        ${CLIENT_INCLUDE_PATH}
        $(ECS_INCLUDE_PATH)
)

target_link_libraries(r-type_server
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
)

target_include_directories(r-type_server PUBLIC
        ${SERVER_INCLUDE_PATH}
)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(r-type_client PRIVATE -std=c++17 -W -Wall -Wextra)
    target_compile_options(r-type_server PRIVATE -std=c++17 -W -Wall -Wextra)
endif()

if(MSVC)
    target_compile_options(r-type_client PRIVATE /std:c++17 /D_WIN32_WINNT=0x0A00)
    target_compile_options(r-type_server PRIVATE /std:c++17)
endif()
