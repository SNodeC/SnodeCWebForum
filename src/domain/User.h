//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_USER_H
#define GETANDPOSTSERVERTEMPLATE_USER_H

#include <string>


struct User {

    unsigned long id;
    std::string userName;
    std::string passwordHash;
    std::string salt;
    std::string avatarURL;
    std::string sessionToken;
    std::string creationDate;

};


#endif //GETANDPOSTSERVERTEMPLATE_USER_H
