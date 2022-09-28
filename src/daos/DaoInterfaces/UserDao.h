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

typedef std::basic_string<unsigned char> ustring;

class UserDao {

public:
    virtual void getById(unsigned long id, std::function<void(User&&)> callback) = 0;

    virtual void isUserNameTaken(const std::string& username, std::function<void(bool)> callback) = 0;

    virtual void createUser(const std::string& username, const std::string& password, const ustring& salt,
                            const std::string& avatarURL, std::function<void(bool)> callback) = 0;

    virtual void checkUserPassword(unsigned long id, const std::string& password,
                                   std::function<void(bool)> callback) = 0;

    virtual void getSalt(unsigned long id, std::function<void(std::string&&)> callback) = 0;
};

#endif //GETANDPOSTSERVERTEMPLATE_USERSDAO_H
