//
// Created by Cleo on 28.09.2022.
//

#ifndef SNODECWEBFORUM_TOPICSERVICE_H
#define SNODECWEBFORUM_TOPICSERVICE_H

#include <functional>
#include <string>
#include <vector>

#include "../daos/DaoInterfaces/UserDao.h"
#include "../daos/DaoInterfaces/TopicDao.h"

using std::function;
using std::string;
using std::vector;

namespace service {

    class TopicService {
    private:
        static bool checkTitleFormat(const string& title);
        static bool checkDescriptionFormat(const string& description);

        TopicDao& _topicDao;
        UserDao& _userDao;

    public:
        enum TopicCreationResult {
            SUCCESS =             0b000,
            INVALID_TITLE =       0b001,
            INVALID_DESCRIPTION = 0b010,
            INTERNAL_ERROR =      0b100
        };

        static vector<string> getTopicCreateErrorMessages(int errorCode);

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
