//
// Created by Cleo on 28.09.2022.
//

#include "CommentService.h"

namespace service {
    CommentService::CommentService(CommentDao& commentDao, UserDao& userDao): _commentDao{commentDao}, _userDao{userDao} {}

    void CommentService::createComment(const string& content, const string& username, unsigned long postId,
                                       function<void(int)> callback) {

    }
} // service