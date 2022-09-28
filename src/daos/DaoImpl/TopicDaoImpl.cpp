//
// Created by student on 9/21/22.
//

#include <sstream>
#include "TopicDaoImpl.h"

void TopicDaoImpl::create(const std::string &title, const std::string &description, unsigned long userID,
                          std::function<void(bool)> callback) {

    std::ostringstream sql;
    sql <<
        "Insert INTO Topic (creatorID, title, description) "
        "VALUES (" << userID << ",'" << title << "','" << description << "');";


    DBClient.exec(sql.str(),
                  [callback]() { callback(true); },
                  [callback](const std::string &, int) { callback(false); });


}

void TopicDaoImpl::getCreator(unsigned long id, std::function<void(User &&)> callback) {
    std::shared_ptr<size_t> counterPtr = std::make_shared<size_t>(0);

    std::ostringstream sql;
    sql <<
        "SELECT u.id, u.username , u.passwordHash, u.salt, u.avatarURL, u.sessionToken , DATE_FORMAT(u.creationDate, '%d/%m/%Y') "
        "FROM User u left JOIN Topic T on u.id = T.creatorID "
        "WHERE t.id = " << id << ";";

    DBClient.query(sql.str(),
                   [callback, counterPtr](const MYSQL_ROW &rows) {
                       if (rows != nullptr && rows[0] != nullptr) {
                           callback(User{
                                   std::stoul(rows[0]),
                                   rows[1],
                                   rows[2],
                                   rows[3],
                                   rows[4],
                                   rows[5],
                                   rows[6]
                           });
                           ++(*counterPtr);

                       } else if (*counterPtr == 0) {
                           callback({});
                       }

                   },
                   [callback](const std::string &, int) {
                       callback({});
                   });


}

void TopicDaoImpl::getRecentTopics(int amount, int start,
                                   std::function<void(std::vector<Topic> &&)> callback) {

    std::ostringstream sql;
    sql <<
        "SELECT id, creatorID, title, description, DATE_FORMAT(creationDate, '%d/%m/%Y') "
        "FROM Topic "
        "ORDER BY creationDate DESC ";

    if (amount != -1) {
        sql <<
            "LIMIT " << amount << " "
                                  "OFFSET" << start;
    }

    sql << ";";
    std::shared_ptr<std::vector<Topic>> topicsPtr = std::make_unique<std::vector<Topic>>();

    DBClient.query(sql.str(),
                   [callback, topicsPtr](const MYSQL_ROW &rows) {
                       if (rows != nullptr && rows[0] != nullptr) {
                           topicsPtr->push_back(Topic{
                                   std::stoul(rows[0]),
                                   User{std::stoul(rows[1])},
                                   rows[2],
                                   rows[3],
                                   rows[4]
                           });
                       } else {
                           callback(std::move(*topicsPtr));
                       }
                   },
                   [callback](const std::string &, int) {
                       callback({});
                   });


}

void TopicDaoImpl::getPostCount(unsigned long id, std::function<void(int)> callback) {
    std::shared_ptr<size_t> counterPtr = std::make_shared<size_t>(0);

    std::ostringstream sql;
    sql <<
        "SELECT COUNT(*) "
        "FROM Post "
        "WHERE topicID = " << id << ";";


    DBClient.query(sql.str(),
                   [callback, counterPtr](const MYSQL_ROW &rows) {
                       if (rows != nullptr && rows[0] != nullptr) {
                           int i = std::stoi(rows[0]);

                           callback(i);
                           ++(*counterPtr);

                       } else if (*counterPtr == 0) {
                           callback(-1);
                       }
                   },
                   [callback](const std::string &, int) {
                       callback(-1);
                   });


}

void TopicDaoImpl::getById(unsigned long id, std::function<void(Topic &&)> callback) {
    std::shared_ptr<size_t> counterPtr = std::make_shared<size_t>(0);

    std::shared_ptr<size_t> creatorCountPtr = std::make_shared<size_t>(0);

    std::ostringstream sql;
    sql <<
        "SELECT id, creatorID, title, description, DATE_FORMAT(creationDate, '%d/%m/%Y') "
        "FROM Topic "
        "WHERE id = " << id << ";";

    DBClient.query(sql.str(),
                   [callback, counterPtr](const MYSQL_ROW &rows) {

                       if (rows != nullptr && rows[0] != nullptr) {
                           callback(Topic{
                                   std::stoul(rows[0]),
                                   User{std::stoul(rows[1])},
                                   rows[2],
                                   rows[3],
                                   rows[4]
                           });
                           ++(*counterPtr);
                       } else if (*counterPtr == 0) {
                           callback({});
                       }
                   },
                   [callback](const std::string &, int) {
                       callback({});
                   });
}

