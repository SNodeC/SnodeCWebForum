//
// Created by student on 9/21/22.
//

#include <sstream>
#include "TopicDaoImpl.h"

void TopicDaoImpl::create(std::string title, int userID, std::function<void(bool)> &callback) {


    std::ostringstream sql;
    sql <<
        "INSERT INTO Topic (creatorID, title) "
        "VALUES (" << userID << ",'" << title << "');";


    DBClient.exec(sql.str(),
                  [&]() { callback(true); },
                  [&](const std::string &, int) { callback(false); });


}

void TopicDaoImpl::getCreator(unsigned long id, std::function<void(User)> &callback) {

    std::ostringstream sql;
    sql <<
        "SELECT u.id, u.username , u.password, u.salt, DATE_FORMAT(u.creationDate, '%d/%m/%Y') "
        "FROM User u left JOIN Topic T on u.id = T.creatorID"
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

void TopicDaoImpl::getRecentTopics(int amount, int start,
                                   std::function<void(std::vector<Topic>)> &callback) {

    std::ostringstream sql;
    sql <<
        "SELECT id, creatorID, title, description, DATE_FORMAT(creationDate, '%d/%m/%Y') "
        "FROM Topic "
        "ORDER BY creationDate DESC ";

    if (amount != -1) {
        sql <<
            "LIMIT " << amount <<
            "OFFSET " << start << ";";
    }
    std::vector<Topic> returnVector;

    DBClient.query(sql.str(),
                   [&](const MYSQL_ROW &rows) {
                       std::vector<Topic> topics;
                       if (rows[0] == nullptr) {
                           topics.push_back(Topic{
                                   std::stoul(rows[0]),
                                   User{std::stoul(rows[1])},
                                   rows[2],
                                   rows[3],
                                   rows[4]
                           });
                       } else {
                           callback(returnVector);
                       }
                   },
                   [&](const std::string &, int) {
                       callback({});
                   });


}

void TopicDaoImpl::getPostCount(unsigned long id, std::function<void(int)> &callback) {

    std::ostringstream sql;
    sql <<
        "SELECT COUNT(*)"
        "FROM Post p left JOIN Topic t on p.topicID = t.id"
        "WHERE t.id = " << id << ";";


    DBClient.query(sql.str(),
                   [&](const MYSQL_ROW &rows) {
                       std::vector<Topic> topics;
                       if (rows[0] == nullptr) {
                           callback(std::stoi(rows[0]));
                       }
                   },
                   [&](const std::string &, int) {
                       callback(-1);
                   });


}

void TopicDaoImpl::getById(unsigned long id, std::function<void(Topic)> &callback) {

    std::ostringstream sql;
    sql <<
        "SELECT id, creatorID, title, description, DATE_FORMAT(creationDate, '%d/%m/%Y') "
        "FROM Topic "
        "WHERE id = " << id << ";";

    DBClient.query(sql.str(),
                   [&](const MYSQL_ROW &rows) {

                       if (rows[0] == nullptr) {
                           callback(Topic{
                                   std::stoul(rows[0]),
                                   std::stoul(rows[1]),
                                   rows[2],
                                   rows[3],
                                   rows[4],
                                   rows[5],
                                   rows[6]});
                       }
                   },
                   [&](const std::string &, int) {
                       callback({});
                   });


}

