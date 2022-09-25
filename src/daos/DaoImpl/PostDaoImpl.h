//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_THREADDAOIMPL_H
#define GETANDPOSTSERVERTEMPLATE_THREADDAOIMPL_H


#include "../DaoInterfaces/PostDao.h"
#include "../../domain/Topic.h"
#include "../../domain/Post.h"
#include "DaoImpl.h"

class PostDaoImpl : public PostDao, protected DaoImpl {
    void create(std::string title, int userID, std::function<void(bool)> callback) override;

    void getRecentPostsOfTopic(unsigned long id, int amount, int start,
                               std::function<void(std::vector<Post> &&)> callback) override;

    void getCreator(unsigned long id, std::function<void(User &&)> callback) override;

    void getTopic(unsigned long id, std::function<void(Topic &&)> callback) override;

    void getCommentCount(unsigned long id, std::function<void(int)> callback) override;

    void getById(unsigned long id, std::function<void(Post &&)> callback) override;

};


#endif //GETANDPOSTSERVERTEMPLATE_THREADDAOIMPL_H
