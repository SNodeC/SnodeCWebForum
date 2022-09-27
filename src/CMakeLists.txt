cmake_minimum_required(VERSION 3.5)

project(SnodeCWebForum LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
        snodec COMPONENTS http-server-express db-mariadb core-socket-stream-legacy net-in-stream-legacy
)
find_package(OpenSSL REQUIRED)

add_executable(main main.cpp

        utils
        utils/Utils.cpp
        utils/Utils.h
        daos

        daos/DaoInterfaces/CommentDao.h
        daos/DaoInterfaces/PostDao.h
        daos/DaoInterfaces/UserDao.h
        daos/DaoInterfaces/TopicDao.h

        daos/DaoImpl/UserDaoImpl.h
        daos/DaoImpl/UserDaoImpl.cpp
        daos/DaoImpl/CommentDaoImpl.cpp
        daos/DaoImpl/CommentDaoImpl.h
        daos/DaoImpl/DaoImpl.h
        daos/DaoImpl/PostDaoImpl.cpp
        daos/DaoImpl/PostDaoImpl.h
        daos/DaoImpl/TopicDaoImpl.cpp
        daos/DaoImpl/TopicDaoImpl.h
        daos/DaoImpl/UserDaoImpl.cpp
        daos/DaoImpl/UserDaoImpl.h

        domain
        domain/User.h
        domain/Comment.h
        domain/Post.h
        domain/Topic.h

        service
        service/UserService.h
        service/HTMLResponseCreationService.h
        service/UserService.cpp
        service/HTMLResponseCreationService.cpp

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

target_link_libraries(main PRIVATE snodec::http-server-express snodec::db-mariadb snodec::core-socket-stream-legacy snodec::net-in-stream-legacy OpenSSL::SSL
        )