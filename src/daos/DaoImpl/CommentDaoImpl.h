//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_TOPICDAOIMPL_H
#define GETANDPOSTSERVERTEMPLATE_TOPICDAOIMPL_H


#include "../DaoInterfaces/CommentDao.h"
#include "../../utils/DateTime.h"

class CommentDaoImpl: public CommentDao{
    void create(std::string content, int posterID, int postID, std::function<void(bool)> &callback) override;

    void getRecentCommentsOfPost(unsigned long id, int amount, int start, std::function<void(std::vector<Comment>)> &callback) override;

    void getCreator(unsigned long id, std::function<void(User)> &callback) override;
};


#endif //GETANDPOSTSERVERTEMPLATE_TOPICDAOIMPL_H
