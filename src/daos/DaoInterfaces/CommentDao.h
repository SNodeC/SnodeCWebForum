//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_TOPICDAO_H
#define GETANDPOSTSERVERTEMPLATE_TOPICDAO_H


#include <ctime>
#include "Dao.h"
#include "../../domain/Comment.h"
#include "../../utils/DateTime.h"

class CommentDao: public Dao<Comment> {

    virtual void create(std::string content, int posterID, int postID, std::function<void(bool)> &callback) = 0;
    virtual void getRecentCommentsOfPost(unsigned long id, int amount, int start, std::function<void(std::vector<Comment>)> &callback) = 0;
    virtual void getCreator(unsigned long id, std::function<void(User)> &callback) = 0;




};


#endif //GETANDPOSTSERVERTEMPLATE_TOPICDAO_H
