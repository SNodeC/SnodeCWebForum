//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_USERSDAO_H
#define GETANDPOSTSERVERTEMPLATE_USERSDAO_H

#include <string>
#include <functional>
#include <vector>
#include "../../domain/User.h"

class UserDao {

public:

    virtual void getById(unsigned long id,const std::function<void(User&&)> &callback) = 0;
    virtual void isUserNameTaken(std::string username,const std::function<void(bool)> &callback) = 0;
    virtual void createUser(std::string username, std::string password, std::string salt,const std::function<void(bool)> &callback) = 0;
    virtual void checkUserPassword(unsigned long id, std::string password, std::string salt,const std::function<void(bool)> &callback) = 0;

};


#endif //GETANDPOSTSERVERTEMPLATE_USERSDAO_H
