//
// Created by student on 9/21/22.
//

#include <sstream>
#include "PostDaoImpl.h"


void PostDaoImpl::create(const std::string& title, const std::string& content, unsigned long userID,
                         unsigned long topicId, std::function<void(bool)> callback) {

    // TODO: FIX THIS SHIT
    std::ostringstream sql;
    sql <<
        "INSERT INTO Post (creatorID, title) "
        "VALUES (" << userID << ",'" << title << "');";

    DBClient.exec(sql.str(),
                  [callback]() { callback(true); },
                  [callback](const std::string &, int) { callback(false); });


}

void PostDaoImpl::getRecentPostsOfTopic(unsigned long id, int amount, int start,
                                        std::function<void(std::vector<Post> &&)> callback) {
    std::ostringstream sql;
    sql <<
        "SELECT id,topicID, creatorID, title, content, DATE_FORMAT(creationDate, '%d/%m/%Y') "
        "FROM Post "
        "WHERE topicID = " << id <<
        "ORDER BY creationDate DESC ";

    if (amount != -1) {
        sql <<
            "LIMIT " << amount <<
            "OFFSET " << start << ";";
    }

    std::shared_ptr<std::vector<Post>> postsPtr = std::make_shared<std::vector<Post>>();

    DBClient.query(sql.str(),
                   [callback, postsPtr](const MYSQL_ROW &rows) {

                       if (rows[0] == nullptr) {
                           postsPtr->push_back(
                                   Post{std::stoul(rows[0]),
                                        Topic{std::stoul(rows[1])},
                                        User{std::stoul(rows[2])},
                                        rows[3],
                                        rows[4],
                                        rows[5]});
                       } else {
                           callback(std::move(*postsPtr));
                       }
                   },
                   [callback](const std::string &, int) {
                       callback({});
                   });
}

void PostDaoImpl::getCreator(unsigned long id, std::function<void(User &&)> callback) {

    std::ostringstream sql;
    sql <<
        "SELECT u.id, u.username , u.password, u.salt, DATE_FORMAT(u.creationDate, '%d/%m/%Y') "
        "FROM User u left JOIN Post p on u.id = p.creatorID"
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
                                   rows[5]
                           });
                       } else {
                           callback({});
                       }

                   },
                   [callback](const std::string &, int) {
                       callback({});
                   });


}

void PostDaoImpl::getTopic(unsigned long id, std::function<void(Topic &&)> callback) {

    std::ostringstream sql;
    sql <<
        "SELECT t.id, t.creatorID , t.title, t.description, DATE_FORMAT(t.creationDate, '%d/%m/%Y') "
        "FROM Topic t left JOIN Post p on u.id = p.creatorID"
        "WHERE id = " << id << ";";

    DBClient.query(sql.str(),
                   [callback](const MYSQL_ROW &rows) {
                       if (rows[0] == nullptr) {
                           callback(Topic{
                                   std::stoul(rows[0]),
                                   std::stoul(rows[1]),
                                   rows[2],
                                   rows[3],
                                   rows[4],
                                   rows[5]
                           });
                       } else {
                           callback({});
                       }
                   },
                   [callback](const std::string &, int) {
                       callback({});
                   });


}

void PostDaoImpl::getById(unsigned long id, std::function<void(Post &&)> callback) {

    std::ostringstream sql;
    sql <<
        "SELECT id, creatorID, title, description, DATE_FORMAT(creationDate, '%d/%m/%Y') "
        "FROM Topic "
        "WHERE id = " << id << ";";

    DBClient.query(sql.str(),
                   [callback](const MYSQL_ROW &rows) {

                       if (rows[0] == nullptr) {
                           callback(Post{
                                   std::stoul(rows[0]),
                                   Topic{std::stoul(rows[1])},
                                   User{std::stoul(rows[2])},
                                   rows[3],
                                   rows[4],
                                   rows[5]});
                       } else {
                           callback({});
                       }
                   },
                   [callback](const std::string &, int) {
                       callback({});
                   });


}

void PostDaoImpl::getCommentCount(unsigned long id, std::function<void(int)> callback) {
    std::ostringstream sql;
    sql <<
        "SELECT COUNT(*)"
        "FROM Post p left JOIN Comment c on p.id = c.creatorID"
        "WHERE p.id = " << id << ";";


    DBClient.query(sql.str(),
                   [callback](const MYSQL_ROW &rows) {
                       if (rows[0] == nullptr) {
                           callback(std::stoi(rows[0]));
                       } else {
                           callback(-1);
                       }
                   },
                   [callback](const std::string &, int) {
                       callback(-1);
                   });
}
