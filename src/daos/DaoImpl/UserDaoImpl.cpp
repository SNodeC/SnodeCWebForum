//
// Created by student on 9/21/22.
//

#include "UserDaoImpl.h"
#include <sstream>
#include <cstring>

void UserDaoImpl::isUserNameTaken(std::string username, const std::function<void(bool)> &callback) {


    std::ostringstream sql;
    sql <<
        "SELECT username "
        "FROM User "
        "WHERE username = " << username << ";";


    DBClient.query(sql.str(),
                   [&](const MYSQL_ROW &rows) {
                       callback(rows[0] != nullptr);
                   },
                   [&](const std::string &, int) {
                       callback(false);
                   });
}

void UserDaoImpl::createUser(std::string username, std::string password, std::string salt,
                             const std::function<void(bool)> &callback) {

    std::ostringstream sql;
    sql <<
        "INSERT INTO User (username, password, salt) "
        "VALUES (" << username << "," << password << "," << salt << ");";


    DBClient.exec(sql.str(),
                  [&]() { callback(true); },
                  [&](const std::string &, int) { callback(false); });


}

void UserDaoImpl::checkUserPassword(unsigned long id, std::string password, std::string salt,
                                    const std::function<void(bool)> &callback) {

    std::ostringstream sql;
    sql <<
        "SELECT password"
        "FROM USER"
        "WHERE id =" << id << ";";

    DBClient.query(sql.str(),
                   [&](const MYSQL_ROW &rows) {
                       if (rows[0] == nullptr) {
                           //TODO password magic
                           callback(std::strcmp(password.c_str(), rows[0]));
                       }
                   },
                   [&](const std::string &, int) {
                       callback(false);
                   });


}

void UserDaoImpl::getById(unsigned long id, const std::function<void(User &&)> &callback) {

    std::ostringstream sql;
    sql <<
        "SELECT id, username, password, salt, avatarURL, DATE_FORMAT(creationDate, '%d/%m/%Y') "
        "FROM User "
        "WHERE id = " << id << ";";


    DBClient.query(sql.str(),
                   [&](const MYSQL_ROW &rows) {

                       if (rows[0] == nullptr) {
                           callback(User{
                                   std::stoul(rows[0]),
                                   rows[1],
                                   rows[2],
                                   rows[3],
                                   rows[4],
                                   rows[5]});
                       }

                   },
                   [&](const std::string &, int) {
                       callback({});
                   });


}


