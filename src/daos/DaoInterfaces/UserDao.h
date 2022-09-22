//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_USERSDAO_H
#define GETANDPOSTSERVERTEMPLATE_USERSDAO_H

#include <string>
#include "Dao.h"
#include "../../domain/User.h"

class UserDao : Dao<User>{

public:

    virtual bool isUserNameTaken(std::string username) = 0;
    virtual bool createUser(std::string username, std::string password, std::string salt) = 0;
    virtual bool checkUserPassword(unsigned long id, std::string password, std::string salt) = 0;

};


#endif //GETANDPOSTSERVERTEMPLATE_USERSDAO_H
