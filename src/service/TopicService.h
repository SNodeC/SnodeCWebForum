//
// Created by Cleo on 28.09.2022.
//

#ifndef SNODECWEBFORUM_TOPICSERVICE_H
#define SNODECWEBFORUM_TOPICSERVICE_H

#include <functional>
#include <string>

#include "../daos/DaoInterfaces/UserDao.h"
#include "../daos/DaoInterfaces/TopicDao.h"

using std::string;
using std::function;

namespace service {

    class TopicService {
    private:
        TopicDao& _topicDao;
        UserDao& _userDao;

    public:
        TopicService() = delete;
        TopicService(const TopicService&) = delete;
        TopicService(TopicService&&) = delete;
        TopicService& operator=(const TopicService&) = delete;
        TopicService& operator=(TopicService&&) = delete;

        TopicService(TopicDao& topicDao, UserDao& userDao);

        void createTopic(const string& title, const string& description, const string& username, 
                         function<void(int)> callback);

        void checkTopicId(unsigned long topicId, function<void(bool)> callback);
    };

} // service

#endif //SNODECWEBFORUM_TOPICSERVICE_H
