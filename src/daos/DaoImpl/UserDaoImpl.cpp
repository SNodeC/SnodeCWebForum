//
// Created by student on 9/21/22.
//

#include "UserDaoImpl.h"

#include <sstream>
#include <cstring>
#include <iostream>

void UserDaoImpl::getById(unsigned long id, std::function<void(User &&)> callback) {

    std::ostringstream sql;
    sql <<
        "SELECT id, username, password, salt, avatarURL, DATE_FORMAT(creationDate, '%d/%m/%Y') "
        "FROM User "
        "WHERE id = " << id << ";";


    DBClient.query(sql.str(),
                   [callback](const MYSQL_ROW &rows) {

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
                   [callback](const std::string &, int) {
                       callback({});
                   });


}


void UserDaoImpl::isUserNameTaken(const std::string& username, std::function<void(bool)> callback) {


    std::ostringstream sql;
    sql <<
        "SELECT username "
        "FROM User "
        "WHERE username = '" << username << "';";


    DBClient.query(sql.str(),
                   [callback](const MYSQL_ROW &rows) {
                       callback(rows[0] != nullptr);
                   },
                   [callback](const std::string &, int) {
                       callback(false);
                   });
}

void UserDaoImpl::createUser(const std::string& username, const std::string& password, const ustring& salt,
                             const std::string& avatarURL, std::function<void(bool)> callback) {

    std::ostringstream sql;
    sql <<
        "INSERT INTO User (username, password, salt) "
        "VALUES ('" << username << "','" << password << "','" << salt << "','" << avatarURL << "');";


    DBClient.exec(sql.str(),
                  [callback]() { callback(true); },
                  [callback](const std::string &s, int) { std::cout << s << std::endl;  callback(false); });


}

void UserDaoImpl::checkUserPassword(unsigned long id, const std::string& password,
                                    std::function<void(bool)> callback) {

    std::ostringstream sql;
    sql <<
        "SELECT password"
        "FROM USER"
        "WHERE id =" << id << ";";

    DBClient.query(sql.str(),
                   [callback](const MYSQL_ROW &rows) {
                       if (rows[0] == nullptr) {
                           callback(std::strcmp(password.c_str(), rows[0]));
                       }
                   },
                   [callback](const std::string &, int) {
                       callback(false);
                   });


}


void UserDaoImpl::getSalt(unsigned long id, std::function<void(std::string&&)> callback) {

    std::ostringstream sql;
    sql <<
        "SELECT salt "
        "FROM User "
        "WHERE id = " << id << ";";


    DBClient.query(sql.str(),
                   [callback](const MYSQL_ROW &rows) {
                       if (rows[0] == nullptr) {
                           callback(rows[0]);
                       }
                   },
                   [callback](const std::string &, int) {
                       callback({});
                   });

}

