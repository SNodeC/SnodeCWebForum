//
// Created by Cleo on 28.09.2022.
//

#include "CommentService.h"

#include <memory>

using std::shared_ptr;
using std::make_shared;

namespace service {
    CommentService::CommentService(CommentDao& commentDao, UserDao& userDao): _commentDao{commentDao}, _userDao{userDao} {}

    void CommentService::createComment(const string& content, const string& username, unsigned long postId,
                                       function<void(int)> callback) {
        shared_ptr<string> contentPtr = make_shared<string>(content);

        function<void(unsigned long)> userIdCallback = [this, contentPtr, postId, callback](unsigned long userId){
            _commentDao.create(*contentPtr,userId, postId, callback);
        };
        _userDao.getIdByUsername(username, userIdCallback);
    }
} // service