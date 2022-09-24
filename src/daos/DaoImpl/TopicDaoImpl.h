//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_SUBTOPICDAOIMPL_H
#define GETANDPOSTSERVERTEMPLATE_SUBTOPICDAOIMPL_H


#include "../DaoInterfaces/TopicDao.h"
#include "../../domain/Topic.h"
#include "DaoImpl.h"

class TopicDaoImpl : public TopicDao , DaoImpl {
    void create(std::string title,int userID,std::function<void(bool)> &callback) override;

    void getCreator(unsigned long id, std::function<void(User)> &callback) override;

    void getRecentTopics(int amount, int start, std::function<void(std::vector<Topic>)> & callback) override;

public:
    void getPostCount(int id, std::function<void(int)> &callback) override;
};


#endif //GETANDPOSTSERVERTEMPLATE_SUBTOPICDAOIMPL_H
