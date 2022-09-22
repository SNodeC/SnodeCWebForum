//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_THREAD_H
#define GETANDPOSTSERVERTEMPLATE_THREAD_H


#include <string>
#include <memory>
#include "User.h"
#include "Topic.h"

struct Post {

    unsigned long id;

    std::string title;
    std::unique_ptr<User> creator;
    std::unique_ptr<Topic> topic;

};


#endif //GETANDPOSTSERVERTEMPLATE_THREAD_H
