//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_USERSDAOIMPL_H
#define GETANDPOSTSERVERTEMPLATE_USERSDAOIMPL_H


#include "../DaoInterfaces/UserDao.h"

class UserDaoImpl: UserDao {
    bool isUserNameTaken(std::string username) override;

    bool createUser(std::string username, std::string password, std::string salt) override;

    bool checkUserPassword(unsigned long id, std::string password, std::string salt) override;
};


#endif //GETANDPOSTSERVERTEMPLATE_USERSDAOIMPL_H
