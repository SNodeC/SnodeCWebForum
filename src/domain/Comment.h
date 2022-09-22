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

    std::string topicText;
    std::unique_ptr<User> poster;
    std::unique_ptr<Post> post;

};


#endif //GETANDPOSTSERVERTEMPLATE_TOPIC_H
