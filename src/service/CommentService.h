//
// Created by Cleo on 28.09.2022.
//

#ifndef SNODECWEBFORUM_COMMENTSERVICE_H
#define SNODECWEBFORUM_COMMENTSERVICE_H

#include <functional>
#include <string>
#include <vector>

#include "../daos/DaoInterfaces/UserDao.h"
#include "../daos/DaoInterfaces/CommentDao.h"

using std::function;
using std::string;
using std::vector;

namespace service {

    class CommentService {
    private:
        static bool checkContentFormat(const string& content);

        CommentDao& _commentDao;
        UserDao& _userDao;

    public:
        enum TopicCreationResult {
            SUCCESS =         0b00,
            INVALID_CONTENT = 0b01,
            INTERNAL_ERROR =  0b10
        };

        static vector<string> getCommentCreateErrorMessages(int errorCode);

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
