//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_USERSDAOIMPL_H
#define GETANDPOSTSERVERTEMPLATE_USERSDAOIMPL_H


#include "../DaoInterfaces/UserDao.h"
#include "DaoImpl.h"

class UserDaoImpl: public UserDao, DaoImpl{
    void isUserNameTaken(std::string username,std::function<void(bool)> &callback) override;

    void createUser(std::string username, std::string password, std::string salt,std::function<void(bool)> &callback) override;

    void checkUserPassword(unsigned long id, std::string password, std::string salt,std::function<void(bool)> &callback) override;
};


#endif //GETANDPOSTSERVERTEMPLATE_USERSDAOIMPL_H
