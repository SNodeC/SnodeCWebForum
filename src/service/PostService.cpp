//
// Created by Cleo on 28.09.2022.
//

#include "PostService.h"

#include <memory>

using std::shared_ptr;
using std::make_shared;

typedef service::PostService cls;

namespace service {

#pragma region Constants

    const size_t TITLE_MIN_LEN = 3;
    const size_t CONTENT_MIN_LEN = 1;

    const char* TITLE_ERR_MSG = "The post title must be at least 3 characters long";
    const char* CONTENT_ERR_MSG = "The post content cannot be empty";
    const char* INTERNAL_ERR_MSG = "There seems to be a problem with the server. Try again later";

#pragma endregion

#pragma region Constructors

    PostService::PostService(PostDao& postDao, UserDao& userDao): _postDao{postDao}, _userDao{userDao} {}

#pragma endregion

#pragma region Static Methods

    bool cls::checkTitleFormat(const string& title) {
        return title.size() >= TITLE_MIN_LEN;
    }

    bool cls::checkContentFormat(const string& content) {
        return content.size() >= CONTENT_MIN_LEN;
    }

    vector<string> cls::getPostCreateErrorMessages(int errorCode) {
        static const string invalidTitle{TITLE_ERR_MSG};
        static const string invalidContent{CONTENT_ERR_MSG};
        static const string internalError{INTERNAL_ERR_MSG};

        vector<string> result;

        if (errorCode & INVALID_TITLE) {
            result.push_back(invalidTitle);
        }

        if (errorCode & INVALID_CONTENT) {
            result.push_back(invalidContent);
        }

        if (errorCode & INTERNAL_ERROR) {
            result.push_back(internalError);
        }

        return std::move(result);
    }

#pragma endregion

#pragma region Instance Methods

    void cls::createPost(const string& title, const string& content, const string& username,
                                 unsigned long topicId, function<void(int)> callback) /* NOLINT */ {
        int result = SUCCESS;
        if(!checkTitleFormat(title)) { // invalid title
            result |= INVALID_TITLE;
        }

        if (!checkContentFormat(content)) { // invalid content
            result |= INVALID_CONTENT;
        }

        if (result != SUCCESS) { // anything invalid
            callback(result);
            return;
        }

        shared_ptr<string> titlePtr = make_shared<string>(title);
        shared_ptr<string> contentPtr = make_shared<string>(content);

        function<void(unsigned long)> userIdCallback = [this, titlePtr, contentPtr, topicId, callback](unsigned long userId){
            function<void(bool)> createCallback = [callback](bool success) {
                callback(success ? SUCCESS : INTERNAL_ERROR);
            };
            _postDao.create(*titlePtr, *contentPtr, userId, topicId, createCallback);
        };
        _userDao.getIdByUsername(username, userIdCallback);
    }

    void cls::checkPostId(unsigned long postId, unsigned long topicId,
                                  function<void(bool)> callback) /* NOLINT */ {
        function<void(Post&&)> postCallback = [callback, postId, topicId](Post&& post) {
            callback(post.id == postId && post.topic.id == topicId);
        };
        _postDao.getById(postId, postCallback);
    }

#pragma endregion

} // service