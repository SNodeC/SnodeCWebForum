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

    void getByUsername(const std::string& username, std::function<void(User &&)> callback) override;

    void isUserNameTaken(const std::string& username, std::function<void(bool)> callback) override;

    void createUser(const std::string& username, const std::string& passwordHash, const ustring& salt,
                    const std::string& avatarURL, std::function<void(bool)> callback) override;

    void getPasswordHashById(unsigned long id, std::function<void(std::string&&)> callback) override;

    void getPasswordHashByUsername(const std::string& username, std::function<void(std::string&&)> callback) override;

    void getIdByUsername(const std::string& username, std::function<void(unsigned long)> callback) override;

    void getSaltById(unsigned long id, std::function<void(ustring&&)> callback) override;

    void getSaltByUsername(const std::string& username, std::function<void(ustring&&)> callback) override;

    virtual void setSessionTokenById(unsigned long id, const std::string& sessionToken, std::function<void(bool)> callback) override;

    virtual void setSessionTokenByUsername(const std::string& username, const std::string& sessionToken, std::function<void(bool)> callback) override;
};

#endif //GETANDPOSTSERVERTEMPLATE_USERSDAOIMPL_H
