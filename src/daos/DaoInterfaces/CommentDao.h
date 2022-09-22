//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_TOPICDAO_H
#define GETANDPOSTSERVERTEMPLATE_TOPICDAO_H


#include <ctime>
#include "Dao.h"
#include "../../domain/Comment.h"

class CommentDao: Dao<Comment> {

    virtual bool create(std::string content) = 0;
    virtual std::list<Comment> getRecentTopicsOfThread(unsigned long id, int amount, std::time_t start, std::time_t end) = 0;


};


#endif //GETANDPOSTSERVERTEMPLATE_TOPICDAO_H
