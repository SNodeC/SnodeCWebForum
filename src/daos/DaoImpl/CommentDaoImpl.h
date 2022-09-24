//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_TOPICDAOIMPL_H
#define GETANDPOSTSERVERTEMPLATE_TOPICDAOIMPL_H


#include "../DaoInterfaces/CommentDao.h"
#include "DaoImpl.h"

class CommentDaoImpl: public CommentDao, protected DaoImpl{
public:
    void create(std::string content, int posterID, int postID, const std::function<void(bool)> &callback) override;

    void getRecentCommentsOfPost(unsigned long id, int amount, int start, const std::function<void(std::vector<Comment>&&)> &callback) override;

    void getCreator(unsigned long id, const std::function<void(User&)> &callback) override;
};


#endif //GETANDPOSTSERVERTEMPLATE_TOPICDAOIMPL_H
