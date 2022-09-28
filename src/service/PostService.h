//
// Created by Cleo on 28.09.2022.
//

#ifndef SNODECWEBFORUM_POSTSERVICE_H
#define SNODECWEBFORUM_POSTSERVICE_H

#include <functional>
#include <string>

#include "../daos/DaoInterfaces/UserDao.h"
#include "../daos/DaoInterfaces/PostDao.h"

using std::string;
using std::function;

namespace service {

    class PostService {
    private:
        PostDao& _postDao;
        UserDao& _userDao;

    public:
        PostService() = delete;
        PostService(const PostService&) = delete;
        PostService(PostService&&) = delete;
        PostService& operator=(const PostService&) = delete;
        PostService& operator=(PostService&&) = delete;

        PostService(PostDao& postDao, UserDao& userDao);

        void createPost(const string& title, const string& content, const string& username, unsigned long topicId,
                        function<void(int)> callback);

        void checkPostId(unsigned long postId, unsigned long topicId, function<void(bool)> callback);
    };

} // service

#endif //SNODECWEBFORUM_POSTSERVICE_H
