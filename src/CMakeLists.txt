cmake_minimum_required(VERSION 3.5)

project(SnodeCWebForum LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
        snodec COMPONENTS http-server-express db-mariadb core-socket-stream-legacy net-in-stream-legacy
)

#[[
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
        ${CMAKE_SOURCE_DIR} "*.cpp")

file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS
        ${CMAKE_SOURCE_DIR} "*.h"
        ${CMAKE_SOURCE_DIR} "*.hpp")
]]



add_executable(main main.cpp daos domain utils service  #[[${HEADER_FILES} ${SOURCE_FILES}]]
        )

add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/../resources/assets
        ${PROJECT_BINARY_DIR}/assets
        COMMENT "Copying assets into binary directory"
        )

add_custom_target(copy_js ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/../resources/js
        ${PROJECT_BINARY_DIR}/js
        COMMENT "Copying js into binary directory"
        )

add_custom_target(copy_css ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/../resources/css
        ${PROJECT_BINARY_DIR}/css
        COMMENT "Copying css into binary directory"
        )

add_dependencies(main copy_assets)
add_dependencies(main copy_js)
add_dependencies(main copy_css)

target_link_libraries(main PRIVATE snodec::http-server-express snodec::db-mariadb snodec::core-socket-stream-legacy snodec::net-in-stream-legacy
        )