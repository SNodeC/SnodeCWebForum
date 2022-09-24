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
    Topic topic;
    User creator;
    std::string title;
    std::string content;
    std::string creationDate;


};


#endif //GETANDPOSTSERVERTEMPLATE_THREAD_H
