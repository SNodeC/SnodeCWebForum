//
// Created by Cleo on 28.09.2022.
//

#include "PostService.h"

namespace service {
    PostService::PostService(PostDao& postDao, UserDao& userDao): _postDao{postDao}, _userDao{userDao} {}

    void
    PostService::createPost(const string& title, const string& content, const string& username, unsigned long topicId,
                            function<void(int)> callback) {

    }
} // service