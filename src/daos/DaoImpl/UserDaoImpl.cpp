//
// Created by student on 9/21/22.
//

#include "UserDaoImpl.h"
#include "../../utils/Utils.h"

#include <sstream>
#include <cstring>
#include <memory>

void UserDaoImpl::getById(unsigned long id, std::function<void(User &&)> callback) {
    std::shared_ptr<size_t> counterPtr = std::make_shared<size_t>(0);

    std::ostringstream sql;
    sql <<
        "SELECT id, username, passwordHash, salt, avatarURL, DATE_FORMAT(creationDate, '%d/%m/%Y') "
        "FROM User "
        "WHERE id = " << id << ";";


    DBClient.query(sql.str(),
                   [callback, counterPtr](const MYSQL_ROW &rows) {

                       if (rows != nullptr && rows[0] != nullptr) {
                           callback(User{
                                   std::stoul(rows[0]),
                                   rows[1],
                                   rows[2],
                                   rows[3],
                                   rows[4],
                                   rows[5]}
                           );
                           ++(*counterPtr);
                       } else if (*counterPtr == 0) {
                           callback({});
                       }
                   },
                   [callback](const std::string &, int) {
                       callback({});
                   });


}

void UserDaoImpl::getByUsername(const std::string &username, std::function<void(User &&)> callback) {
    std::shared_ptr<size_t> counterPtr = std::make_shared<size_t>(0);

    std::ostringstream sql;
    sql <<
        "SELECT id, username, passwordHash, salt, avatarURL, DATE_FORMAT(creationDate, '%d/%m/%Y') "
        "FROM User "
        "WHERE username = '" << Utils::escapeForSQL(username) << "';";


    DBClient.query(sql.str(),
                   [callback, counterPtr](const MYSQL_ROW &rows) {

                       if (rows != nullptr && rows[0] != nullptr) {
                           callback(User{
                                   std::stoul(rows[0]),
                                   rows[1],
                                   rows[2],
                                   rows[3],
                                   rows[4],
                                   rows[5]});
                           ++(*counterPtr);
                       } else if (*counterPtr == 0) {
                           callback({});
                       }

                   },
                   [callback](const std::string &, int) {
                       callback({});
                   });


}

void UserDaoImpl::isUserNameTaken(const std::string &username, std::function<void(bool)> callback) {
    std::shared_ptr<size_t> counterPtr = std::make_shared<size_t>(0);

    std::ostringstream sql;
    sql <<
        "SELECT username "
        "FROM User "
        "WHERE username = '" << Utils::escapeForSQL(username) << "';";


    DBClient.query(sql.str(),
                   [callback, counterPtr](const MYSQL_ROW &rows) {

                       if (rows != nullptr && rows[0] != nullptr) {
                           callback(true);

                           ++(*counterPtr);

                       } else if (*counterPtr == 0) {
                           callback(false);
                       }
                   },
                   [callback](const std::string &, int) {
                       callback(false);
                   });
}

void UserDaoImpl::createUser(const std::string &username, const std::string &passwordHash, const ustring &salt,
                             const std::string &avatarURL, std::function<void(bool)> callback) {

    const char *salt_c_ptr = reinterpret_cast<const char *>(salt.c_str());
    std::string salt_str{salt_c_ptr};
    std::ostringstream sql;
    sql <<
        "INSERT INTO User (username, passwordHash, salt, avatarURL) "
        "VALUES ('" << Utils::escapeForSQL(username) << "','" << Utils::escapeForSQL(passwordHash) << "','"
        << Utils::escapeForSQL(salt_str) << "','" << Utils::escapeForSQL(avatarURL) << "');";


    DBClient.exec(sql.str(),
                  [callback]() { callback(true); },
                  [callback](const std::string &s, int) {
                      callback(false);
                  });


}

void UserDaoImpl::getPasswordHashById(unsigned long id, std::function<void(std::string &&)> callback) {
    std::shared_ptr<size_t> counterPtr = std::make_shared<size_t>(0);

    std::ostringstream sql;
    sql <<
        "SELECT passwordHash "
        "FROM User "
        "WHERE id = " << id << ";";

    DBClient.query(sql.str(),
                   [callback, counterPtr](const MYSQL_ROW &rows) {
                       if (rows != nullptr && rows[0] != nullptr) {
                           callback(rows[0]);
                           ++(*counterPtr);

                       } else if (*counterPtr == 0) {
                           callback({});
                       }
                   },
                   [callback](const std::string &, int) {
                       callback({});
                   });
}

void
UserDaoImpl::getPasswordHashByUsername(const std::string &username, std::function<void(std::string &&)> callback) {
    std::shared_ptr<size_t> counterPtr = std::make_shared<size_t>(0);

    std::ostringstream sql;
    sql <<
        "SELECT passwordHash "
        "FROM User "
        "WHERE username = " << Utils::escapeForSQL(username) << ";";

    DBClient.query(sql.str(),
                   [callback, counterPtr](const MYSQL_ROW &rows) {
                       if (rows != nullptr && rows[0] != nullptr) {
                           callback(rows[0]);
                           ++(*counterPtr);

                       } else if (*counterPtr == 0) {
                           callback({});
                       }
                   },
                   [callback](const std::string &, int) {
                       callback({});
                   });
}

void UserDaoImpl::getIdByUsername(const std::string &username, std::function<void(unsigned long)> callback) {
    std::shared_ptr<size_t> counterPtr = std::make_shared<size_t>(0);

    std::ostringstream sql;
    sql <<
        "SELECT id "
        "FROM User "
        "WHERE username = '" << Utils::escapeForSQL(username) << "';";

    DBClient.query(sql.str(),
                   [callback, counterPtr](const MYSQL_ROW &rows) {
                       if (rows != nullptr && rows[0] != nullptr) {
                           callback(std::stoul(rows[0]));
                           ++(*counterPtr);

                       } else if (*counterPtr == 0) {
                           callback(-1);
                       }
                   },
                   [callback](const std::string &, int) {
                       callback(-1);
                   });
}

void UserDaoImpl::getSaltById(unsigned long id, std::function<void(ustring &&)> callback) {
    std::shared_ptr<size_t> counterPtr = std::make_shared<size_t>(0);

    std::ostringstream sql;
    sql <<
        "SELECT salt "
        "FROM User "
        "WHERE id = " << id << ";";

    DBClient.query(sql.str(),
                   [callback, counterPtr](const MYSQL_ROW &rows) {
                       if (rows != nullptr && rows[0] != nullptr) {
                           callback(reinterpret_cast<const unsigned char *>(rows[0]));
                           ++(*counterPtr);
                       } else if (*counterPtr == 0) {
                           callback({});
                       }
                   },
                   [callback](const std::string &, int) {
                       callback({});
                   });

}

void UserDaoImpl::getSaltByUsername(const std::string &username, std::function<void(ustring &&)> callback) {
    std::shared_ptr<size_t> counterPtr = std::make_shared<size_t>(0);

    std::ostringstream sql;
    sql <<
        "SELECT salt "
        "FROM User "
        "WHERE username = '" << Utils::escapeForSQL(username) << "';";

    DBClient.query(sql.str(),
                   [callback, counterPtr](const MYSQL_ROW &rows) {
                       if (rows != nullptr && rows[0] != nullptr) {
                           callback(reinterpret_cast<const unsigned char *>(rows[0]));
                           ++(*counterPtr);

                       } else if (*counterPtr == 0) {
                           callback({});
                       }
                   },
                   [callback](const std::string &, int) {
                       callback({});
                   });

}

void UserDaoImpl::setSessionTokenById(unsigned long id, const std::string &sessionToken,
                                      std::function<void(bool)> callback) {

    std::ostringstream sql;
    sql <<
        "UPDATE User "
        "SET sessionToken='" << Utils::escapeForSQL(sessionToken) << "' "
                                                "WHERE id=" << id << ";";

    DBClient.exec(sql.str(),
                  [callback]() { callback(true); },
                  [callback](const std::string &s, int) {
                      callback(false);
                  });
}

void UserDaoImpl::setSessionTokenByUsername(const std::string &username, const std::string &sessionToken,
                                            std::function<void(bool)> callback) {
    std::ostringstream sql;
    sql <<
        "UPDATE User "
        "SET sessionToken='" << Utils::escapeForSQL(sessionToken) << "' "
        "WHERE username='" << Utils::escapeForSQL(username) << "';";

    DBClient.exec(sql.str(),
                  [callback]() { callback(true); },
                  [callback](const std::string &s, int) {
                      callback(false);
                  });
}

void UserDaoImpl::getSessionTokenById(unsigned long id, std::function<void(std::string &&)> callback) {

    std::shared_ptr<size_t> counterPtr = std::make_shared<size_t>(0);

    std::ostringstream sql;
    sql <<
        "SELECT sessionToken "
        "FROM User "
        "WHERE id = '" << id << "';";

    DBClient.query(
            sql.str(),
            [callback, counterPtr](const MYSQL_ROW &rows) {
                if (rows != nullptr && rows[0] != nullptr) {
                    callback(rows[0]);
                    ++(*counterPtr);
                } else if (*counterPtr == 0) {
                    callback({});
                }
            },
            [callback](const std::string &, int) {
                callback({});
            });
}

void
UserDaoImpl::getSessionTokenByUsername(const std::string &username, std::function<void(std::string &&)> callback) {
    std::shared_ptr<size_t> counterPtr = std::make_shared<size_t>(0);

    std::ostringstream sql;
    sql <<
        "SELECT sessionToken "
        "FROM User "
        "WHERE username = '" << Utils::escapeForSQL(username) << "';";

    DBClient.query(
            sql.str(),
            [callback, counterPtr](const MYSQL_ROW &rows) {
                if (rows != nullptr && rows[0] != nullptr) {
                    callback(rows[0]);
                    ++(*counterPtr);

                } else if (*counterPtr == 0) {
                    callback({});
                }
            },
            [callback](const std::string &, int) {
                callback({});
            });

}

