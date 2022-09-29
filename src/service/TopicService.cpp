//
// Created by Cleo on 28.09.2022.
//

#include "TopicService.h"

#include <memory>

using std::shared_ptr;
using std::make_shared;

typedef service::TopicService cls;

namespace service {

#pragma region Constants

    const size_t TITLE_MIN_LEN = 3;
    const size_t DESCRIPTION_MIN_LEN = 1;

    const char* TITLE_ERR_MSG = "The topic title must be at least 3 characters long";
    const char* DESCRIPTION_ERR_MSG = "The topic description cannot be empty";
    const char* INTERNAL_ERR_MSG = "There seems to be a problem with the server. Try again later";

#pragma endregion

#pragma region Constructors

    TopicService::TopicService(TopicDao& topicDao, UserDao& userDao): _topicDao{topicDao}, _userDao{userDao} {}

#pragma endregion

#pragma region Static Methods

    bool cls::checkTitleFormat(const string& title)
    {
        return title.size() >= TITLE_MIN_LEN;
    }

    bool cls::checkDescriptionFormat(const string& description)
    {
        return description.size() >= DESCRIPTION_MIN_LEN;
    }

    vector<string> cls::getTopicCreateErrorMessages(int errorCode) {
        static const string invalidTitle{TITLE_ERR_MSG};
        static const string invalidDescription{DESCRIPTION_ERR_MSG};
        static const string internalError{INTERNAL_ERR_MSG};

        vector<string> result;

        if (errorCode & INVALID_TITLE) {
            result.push_back(invalidTitle);
        }

        if (errorCode & INVALID_DESCRIPTION) {
            result.push_back(invalidDescription);
        }

        if (errorCode & INTERNAL_ERROR) {
            result.push_back(internalError);
        }

        return std::move(result);
    }

#pragma endregion

#pragma region Instance Methods

    void cls::createTopic(const string& title, const string& description, const string& username,
                          function<void(int)> callback) /* NOLINT */ {
        int result = SUCCESS;
        if(!checkTitleFormat(title)) { // invalid title
            result |= INVALID_TITLE;
        }

        if (!checkDescriptionFormat(description)) { // invalid description
            result |= INVALID_DESCRIPTION;
        }

        if (result != SUCCESS) { // anything invalid
            callback(result);
            return;
        }

        shared_ptr<string> titlePtr = make_shared<string>(title);
        shared_ptr<string> descriptionPtr = make_shared<string>(description);

        function<void(unsigned long)> userIdCallback = [this, titlePtr, descriptionPtr, callback](unsigned long userId){
            function<void(bool)> createCallback = [callback](bool success) {
                callback(success ? SUCCESS : INTERNAL_ERROR);
            };
            _topicDao.create(*titlePtr, *descriptionPtr, userId, createCallback);
        };
        _userDao.getIdByUsername(username, userIdCallback);
    }

    void cls::checkTopicId(unsigned long topicId, function<void(bool)> callback) /* NOLINT */  {
        function<void(Topic&&)> topicCallback = [callback, topicId](Topic&& topic) {
            callback(topic.id == topicId);
        };
        _topicDao.getById(topicId, topicCallback);
    }

#pragma endregion

} // service