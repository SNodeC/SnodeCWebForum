cmake_minimum_required(VERSION 3.5)

project(SnodeCWebForum LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
        snodec COMPONENTS http-server-express db-mariadb core-socket-stream-legacy net-in-stream-legacy
)

add_executable(
        main

        main.cpp

        utils
        daos
        domain

        #daos/DaoInterfaces/Dao.h
        #daos/DaoInterfaces/UserDao.h
        #daos/DaoInterfaces/PostDao.h
        #daos/DaoInterfaces/CommentDao.h
        #daos/DaoInterfaces/TopicDao.h

        #daos/DaoImpl/PostDaoImpl.cpp
        #daos/DaoImpl/PostDaoImpl.h
        #daos/DaoImpl/CommentDaoImpl.cpp
        #daos/DaoImpl/CommentDaoImpl.h
        #daos/DaoImpl/TopicDaoImpl.cpp
        #daos/DaoImpl/TopicDaoImpl.h

        #domain/User.h
        #domain/Comment.h
        #domain/Topic.h
        #domain/Post.h
)

target_link_libraries(main PRIVATE snodec::http-server-express snodec::db-mariadb snodec::core-socket-stream-legacy snodec::net-in-stream-legacy
        )