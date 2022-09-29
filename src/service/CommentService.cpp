//
// Created by Cleo on 28.09.2022.
//

#include "CommentService.h"

#include <memory>

using std::shared_ptr;
using std::make_shared;

typedef service::CommentService cls;

namespace service {

#pragma region Constants

    const size_t CONTENT_MIN_LEN = 1;

    const char* CS_CONTENT_ERR_MSG = "The post content cannot be empty";
    const char* CS_INTERNAL_ERR_MSG = "There seems to be a problem with the server. Try again later";

#pragma endregion

#pragma region Constructors

    CommentService::CommentService(CommentDao& commentDao, UserDao& userDao): _commentDao{commentDao}, _userDao{userDao} {}

#pragma endregion

#pragma region Static Methods

    bool cls::checkContentFormat(const string& content) {
        return content.size() >= CONTENT_MIN_LEN;
    }

    vector<string> cls::getCommentCreateErrorMessages(int errorCode) {
        static const string invalidContent{CS_CONTENT_ERR_MSG};
        static const string internalError{CS_INTERNAL_ERR_MSG};

        vector<string> result;

        if (errorCode & INVALID_CONTENT) {
            result.push_back(invalidContent);
        }

        if (errorCode & INTERNAL_ERROR) {
            result.push_back(internalError);
        }

        return std::move(result);
    }

#pragma endregion

#pragma  region Instance Methods

    void cls::createComment(const string& content, const string& username, unsigned long postId,
                                       function<void(int)> callback) /* NOLINT */ {
        int result = SUCCESS;
        if (!checkContentFormat(content)) { // invalid content
            result |= INVALID_CONTENT;
        }

        if (result != SUCCESS) { // anything invalid
            callback(result);
            return;
        }

        shared_ptr<string> contentPtr = make_shared<string>(content);

        function<void(unsigned long)> userIdCallback = [this, contentPtr, postId, callback](unsigned long userId){
            function<void(bool)> createCallback = [callback](bool success) {
                callback(success ? SUCCESS : INTERNAL_ERROR);
            };
            _commentDao.create(*contentPtr,userId, postId, createCallback);
        };
        _userDao.getIdByUsername(username, userIdCallback);
    }

#pragma endregion

} // service