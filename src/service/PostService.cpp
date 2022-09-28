//
// Created by Cleo on 28.09.2022.
//

#include "PostService.h"

#include <memory>

using std::shared_ptr;
using std::make_shared;

namespace service {
    PostService::PostService(PostDao& postDao, UserDao& userDao): _postDao{postDao}, _userDao{userDao} {}

    void
    PostService::createPost(const string& title, const string& content, const string& username, unsigned long topicId,
                            function<void(int)> callback) {
        shared_ptr<string> titlePtr = make_shared<string>(title);
        shared_ptr<string> contentPtr = make_shared<string>(content);

        function<void(unsigned long)> userIdCallback = [this, titlePtr, contentPtr, topicId, callback](unsigned long userId){
            _postDao.create(*titlePtr, *contentPtr, userId, topicId, callback);
        };
        _userDao.getIdByUsername(username, userIdCallback);
    }
} // service