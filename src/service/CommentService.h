//
// Created by Cleo on 28.09.2022.
//

#ifndef SNODECWEBFORUM_COMMENTSERVICE_H
#define SNODECWEBFORUM_COMMENTSERVICE_H

#include <functional>
#include <string>

#include "../daos/DaoInterfaces/UserDao.h"
#include "../daos/DaoInterfaces/CommentDao.h"

using std::string;
using std::function;

namespace service {

    class CommentService {
    private:
        CommentDao& _commentDao;
        UserDao& _userDao;

    public:
        CommentService() = delete;
        CommentService(const CommentService&) = delete;
        CommentService(CommentService&&) = delete;
        CommentService& operator=(const CommentService&) = delete;
        CommentService& operator=(CommentService&&) = delete;

        CommentService(CommentDao& commentDao, UserDao& userDao);

        void createComment(const string& content, const string& username, unsigned long postId,
                           function<void(int)> callback);
    };

} // service

#endif //SNODECWEBFORUM_COMMENTSERVICE_H
