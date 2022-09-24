//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_SUBTOPICDAO_H
#define GETANDPOSTSERVERTEMPLATE_SUBTOPICDAO_H


#include "../../domain/Topic.h"
#include <ctime>
#include <functional>

class TopicDao {

public:

    virtual void create(std::string title, int userID, std::function<void(bool)> &callback) = 0;

    virtual void getCreator(unsigned long id, std::function<void(User)> &callback) = 0;

    virtual void getRecentTopics(int amount, int start,
                                 std::function<void(std::vector<Topic>)> &callback) = 0;


};


#endif //GETANDPOSTSERVERTEMPLATE_SUBTOPICDAO_H
