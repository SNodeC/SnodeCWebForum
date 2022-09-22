//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_SUBTOPICDAOIMPL_H
#define GETANDPOSTSERVERTEMPLATE_SUBTOPICDAOIMPL_H


#include "../DaoInterfaces/TopicDao.h"
#include "../../domain/Topic.h"

class TopicDaoImpl : TopicDao {
    bool create(std::string title) override;

    std::list<Topic> getRecentSubtopics(int amount, std::time_t start, std::time_t end) override;
};


#endif //GETANDPOSTSERVERTEMPLATE_SUBTOPICDAOIMPL_H
