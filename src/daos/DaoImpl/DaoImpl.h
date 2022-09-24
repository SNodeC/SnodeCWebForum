//
// Created by student on 9/24/22.
//

#ifndef SNODECWEBFORUM_DAOIMPL_H
#define SNODECWEBFORUM_DAOIMPL_H


#include <database/mariadb/MariaDBClient.h>

class DaoImpl {
protected:
    database::mariadb::MariaDBClient &DBClient;

    explicit DaoImpl(database::mariadb::MariaDBClient &client) : DBClient{client} {}


};


#endif //SNODECWEBFORUM_DAOIMPL_H
