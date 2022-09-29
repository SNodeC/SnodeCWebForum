//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_USERSDAO_H
#define GETANDPOSTSERVERTEMPLATE_USERSDAO_H

#include <string>
#include <functional>
#include <vector>
#include "../../domain/User.h"

typedef std::basic_string<unsigned char> ustring;

class UserDao {

public:
    virtual void getById(unsigned long id, std::function<void(User&&)> callback) = 0;

    virtual void getByUsername(const std::string& username, std::function<void(User &&)> callback) = 0;

    virtual void isUserNameTaken(const std::string& username, std::function<void(bool)> callback) = 0;

    virtual void createUser(const std::string& username, const std::string& passwordHash, const ustring& salt,
                            const std::string& avatarURL, std::function<void(bool)> callback) = 0;

    virtual void getPasswordHashById(unsigned long id, std::function<void(std::string&&)> callback) = 0;

    virtual void getPasswordHashByUsername(const std::string& username, std::function<void(std::string&&)> callback) = 0;

    virtual void getIdByUsername(const std::string& username, std::function<void(unsigned long)> callback) = 0;

    virtual void getSaltById(unsigned long id, std::function<void(ustring&&)> callback) = 0;

    virtual void getSaltByUsername(const std::string& username, std::function<void(ustring&&)> callback) = 0;

    virtual void getSessionTokenById(unsigned long id, std::function<void(std::string&&)> callback) = 0;

    virtual void getSessionTokenByUsername(const std::string& username, std::function<void(std::string&&)> callback) = 0;

    virtual void setSessionTokenById(unsigned long id, const std::string& sessionToken, std::function<void(bool)> callback) = 0;

    virtual void setSessionTokenByUsername(const std::string& username, const std::string& sessionToken, std::function<void(bool)> callback) = 0;
};

#endif //GETANDPOSTSERVERTEMPLATE_USERSDAO_H
