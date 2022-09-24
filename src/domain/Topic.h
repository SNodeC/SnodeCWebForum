//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_SUBTOPIC_H
#define GETANDPOSTSERVERTEMPLATE_SUBTOPIC_H


#include <string>
#include <memory>
#include "User.h"

struct Topic {

    unsigned long id;
    User creator;
    std::string title;
    std::string description;
    std::string creationDate;

};


#endif //GETANDPOSTSERVERTEMPLATE_SUBTOPIC_H
