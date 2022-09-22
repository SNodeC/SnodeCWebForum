//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_SUBTOPICDAO_H
#define GETANDPOSTSERVERTEMPLATE_SUBTOPICDAO_H


#include "Dao.h"
#include "../../domain/Topic.h"
#include <ctime>

class TopicDao : Dao<Topic> {

    virtual bool create(std::string title) = 0;

    virtual std::list<Topic> getRecentSubtopics(int amount, std::time_t start, std::time_t end) = 0;


};


#endif //GETANDPOSTSERVERTEMPLATE_SUBTOPICDAO_H
