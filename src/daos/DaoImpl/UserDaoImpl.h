//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_USERSDAOIMPL_H
#define GETANDPOSTSERVERTEMPLATE_USERSDAOIMPL_H


#include "../DaoInterfaces/UserDao.h"
#include "DaoImpl.h"

class UserDaoImpl : public UserDao, protected DaoImpl {
public:
    void getById(unsigned long id,const std::function<void(User&)> &callback) override;

    void isUserNameTaken(std::string username,const std::function<void(bool)> &callback) override;

    void createUser(std::string username, std::string password, std::string salt,const
                    std::function<void(bool)> &callback) override;

    void checkUserPassword(unsigned long id, std::string password, std::string salt,const
                           std::function<void(bool)> &callback) override;
};


#endif //GETANDPOSTSERVERTEMPLATE_USERSDAOIMPL_H
