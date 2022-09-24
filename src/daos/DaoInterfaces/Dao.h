//
// Created by student on 9/21/22.
//

#ifndef GETANDPOSTSERVERTEMPLATE_DAO_H
#define GETANDPOSTSERVERTEMPLATE_DAO_H

#include <list>
#include <string>
#include <database/mariadb/MariaDBConnectionDetails.h>
#include <database/mariadb/MariaDBClient.h>
#include <database/mariadb/MariaDBConnection.h>
#include <database/mariadb/MariaDBClient.h>
#include <database/mariadb/MariaDBCommand.h>
#include <database/mariadb/MariaDBConnectionDetails.h>
#include <database/mariadb/commands/sync/MariaDBUseResultCommand.h>
#include <database/mariadb/MariaDBCommandSequence.h>
#include <filesystem>
#include <algorithm>


template<typename T>
class Dao {

protected:
    database::mariadb::MariaDBClient &DBClient;

    explicit Dao(database::mariadb::MariaDBClient &client) : DBClient{client} {}

/*

    database::mariadb::MariaDBClient DatabaseInit() {


        database::mariadb::MariaDBClient dbClient(DBConnectionDetails);


        return dbClient;

        std::function<void(const std::string &, unsigned int)> onError = [](const std::string &, unsigned int) {};

        dbClient.exec("INSERT into Users ( username, password) VALUES ('Fidi','Passwd');", []() {},
                      [](const std::string &, unsigned int) {});

        dbClient.commit([]() {}, [](const std::string &, unsigned int) {});

    }

*/

/*    T get(long id) {

        T t;

        return t;

    };

    std::vector<T> getAll() {

        std::vector<T> resultList;

        return resultList;
    };

    bool save(T t) {

        return true;

    };

    bool update(T t, std::vector<std::string> params) {

        return true;

    };

    bool del(T t) {

        return true;

    };*/

};


#endif //GETANDPOSTSERVERTEMPLATE_DAO_H
