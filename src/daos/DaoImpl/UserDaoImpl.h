//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_USERSDAOIMPL_H
#define GETANDPOSTSERVERTEMPLATE_USERSDAOIMPL_H


#include "../DaoInterfaces/UserDao.h"
#include "DaoImpl.h"
#include "../../utils/Utils.h"

class UserDaoImpl : public UserDao, protected DaoImpl {

public:

    explicit UserDaoImpl(database::mariadb::MariaDBClient &client) : DaoImpl{client} {}

    void getById(unsigned long id, std::function<void(User &&)> callback) override;

    void isUserNameTaken(const std::string username, std::function<void(bool)> callback) override;

    void createUser(const std::string& username, const std::string& password, const std::string& salt,
                    const std::string& avatarURL, std::function<void(bool)> callback) override;

    void checkUserPassword(unsigned long id, const std::string& password, std::function<void(bool)> callback) override;

    void getSalt(unsigned long id, std::function<void(std::string&&)> callback) override;
};

#endif //GETANDPOSTSERVERTEMPLATE_USERSDAOIMPL_H
