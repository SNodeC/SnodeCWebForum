//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_THREADDAOIMPL_H
#define GETANDPOSTSERVERTEMPLATE_THREADDAOIMPL_H


#include "../DaoInterfaces/PostDao.h"
#include "../../domain/Topic.h"
#include "../../domain/Post.h"

class PostDaoImpl : PostDao {
    bool create(std::string title) override;

    Topic getSubtopic(unsigned long id) override;

    std::list<Post>
    getRecentThreadsOfSubtopic(unsigned long id, int amount, std::time_t start, std::time_t end) override;
};


#endif //GETANDPOSTSERVERTEMPLATE_THREADDAOIMPL_H
