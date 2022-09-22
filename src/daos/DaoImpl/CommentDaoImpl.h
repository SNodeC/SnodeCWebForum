//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_TOPICDAOIMPL_H
#define GETANDPOSTSERVERTEMPLATE_TOPICDAOIMPL_H


#include "../DaoInterfaces/CommentDao.h"

class CommentDaoImpl: CommentDao{
    bool create(std::string content) override;

    std::list<Comment> getRecentTopicsOfThread(unsigned long id, int amount, std::time_t start, std::time_t end) override;
};


#endif //GETANDPOSTSERVERTEMPLATE_TOPICDAOIMPL_H
