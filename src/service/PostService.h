//
// Created by Cleo on 28.09.2022.
//

#ifndef SNODECWEBFORUM_POSTSERVICE_H
#define SNODECWEBFORUM_POSTSERVICE_H

#include <functional>
#include <string>
#include <vector>

#include "../daos/DaoInterfaces/UserDao.h"
#include "../daos/DaoInterfaces/PostDao.h"

using std::function;
using std::string;
using std::vector;

namespace service {

    class PostService {
    private:
        static bool checkTitleFormat(const string& title);
        static bool checkContentFormat(const string& content);

        PostDao& _postDao;
        UserDao& _userDao;

    public:
        enum TopicCreationResult {
            SUCCESS =         0b000,
            INVALID_TITLE =   0b001,
            INVALID_CONTENT = 0b010,
            INTERNAL_ERROR =  0b100
        };

        static vector<string> getPostCreateErrorMessages(int errorCode);

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
