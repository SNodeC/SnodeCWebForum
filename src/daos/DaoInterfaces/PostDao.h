//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_THREADDAO_H
#define GETANDPOSTSERVERTEMPLATE_THREADDAO_H


#include <ctime>
#include "Dao.h"
#include "../../domain/Post.h"

class PostDao : Dao<Post> {

    virtual bool create(std::string title) = 0;
    virtual Topic getSubtopic(unsigned long id) = 0;
    virtual std::list<Post> getRecentThreadsOfSubtopic(unsigned long id, int amount, std::time_t start, std::time_t end) = 0;

};


#endif //GETANDPOSTSERVERTEMPLATE_THREADDAO_H
