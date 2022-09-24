//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_THREADDAO_H
#define GETANDPOSTSERVERTEMPLATE_THREADDAO_H


#include <ctime>
#include <functional>
#include "../../domain/Post.h"

class PostDao {

public:

    virtual void create(std::string title,int userID,std::function<void(bool)> &callback) = 0;
    //virtual void getPost(unsigned long id, std::function<void(Post)> &callback) = 0;
    virtual void getCreator(unsigned long id, std::function<void(User)> &callback) = 0;
    virtual void getTopic(unsigned long id, std::function<void(Topic)> &callback) = 0;
    virtual void getRecentPostsOfTopic(unsigned long id, int amount, int start, std::function<void(std::vector<Post>)> &callback) = 0;



};


#endif //GETANDPOSTSERVERTEMPLATE_THREADDAO_H
