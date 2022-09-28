//
// Created by Cleo on 28.09.2022.
//

#include "TopicService.h"

#include <memory>

using std::shared_ptr;
using std::make_shared;

namespace service {
    TopicService::TopicService(TopicDao& topicDao, UserDao& userDao): _topicDao{topicDao}, _userDao{userDao} {}

    void TopicService::createTopic(const string& title, const string& description, const string& username,
                                   function<void(int)> callback) {
        shared_ptr<string> titlePtr = make_shared<string>(title);
        shared_ptr<string> descriptionPtr = make_shared<string>(description);

        function<void(unsigned long)> userIdCallback = [this, titlePtr, descriptionPtr, callback](unsigned long userId){
            _topicDao.create(*titlePtr, *descriptionPtr, userId, callback);
        };
        _userDao.getIdByUsername(username, userIdCallback);
    }

    void TopicService::checkTopicId(unsigned long topicId, function<void(bool)> callback) {
        function<void(Topic&&)> topicCallback = [callback, topicId](Topic&& topic) {
            callback(topic.id == topicId);
        };
        _topicDao.getById(topicId, topicCallback);
    }
} // service