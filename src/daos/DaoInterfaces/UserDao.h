//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_USERSDAO_H
#define GETANDPOSTSERVERTEMPLATE_USERSDAO_H

#include <string>
#include <functional>
#include <vector>
#include "../../domain/User.h"
#include "../../utils/Utils.h"

class UserDao {

public:

    virtual void getById(unsigned long id, std::function<void(User &&)> callback) = 0;

    virtual void isUserNameTaken(std::string username, std::function<void(bool)> callback) = 0;

    virtual void
    createUser(std::string username, std::string password, std::string salt, std::function<void(bool)> callback) = 0;

    virtual void
    checkUserPassword(unsigned long id, std::string password, std::function<void(bool)> callback) = 0;

    virtual void
    getSalt(unsigned long id, std::function<void(std::string)> callback) = 0;



};


#endif //GETANDPOSTSERVERTEMPLATE_USERSDAO_H
