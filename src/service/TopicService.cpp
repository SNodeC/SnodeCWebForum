//
// Created by Cleo on 28.09.2022.
//

#include "TopicService.h"

namespace service {
    TopicService::TopicService(TopicDao& topicDao, UserDao& userDao): _topicDao{topicDao}, _userDao{userDao} {}

    void TopicService::createTopic(const string& title, const string& description, const string& username,
                                   function<void(int)> callback) {

    }
} // service