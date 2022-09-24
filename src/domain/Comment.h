//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_TOPIC_H
#define GETANDPOSTSERVERTEMPLATE_TOPIC_H

#include <string>
#include <memory>
#include "User.h"
#include "Post.h"

struct Comment {

    unsigned long id;
    Post post;
    User poster;
    std::string content;
    std::string creationDate;

};





#endif //GETANDPOSTSERVERTEMPLATE_TOPIC_H
