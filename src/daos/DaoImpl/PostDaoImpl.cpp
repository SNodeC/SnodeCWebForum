//
// Created by student on 9/21/22.
//

#include <sstream>
#include "PostDaoImpl.h"


void PostDaoImpl::create(std::string title, int userID,const std::function<void(bool)> &callback) {

    std::ostringstream sql;
    sql <<
        "INSERT INTO Post (creatorID, title) "
        "VALUES (" << userID << ",'" << title << "');";

    DBClient.exec(sql.str(),
                  [&]() { callback(true); },
                  [&](const std::string &, int) { callback(false); });


}

/*
void PostDaoImpl::getPost(unsigned long id, std::function<void(Post)> &callback) {

    std::ostringstream sql;
    sql << "SELECT id ,topicID, creatorID, title, content, DATE_FORMAT(creationDate, '%d/%m/%Y') "
           "FROM Post "
           "WHERE id = " << id << ";";

    DBClient.query(sql.str(), [&](const MYSQL_ROW &rows) {

        if (rows[0] == nullptr) {
            callback(Post{std::stoul(rows[0]), Topic{std::stoul(rows[1])}, User{std::stoul(rows[2])}, rows[3], rows[4],
                          rows[5]});
        }

    }, [&](const std::string &, int) {
        callback({});
    });


}
*/

void PostDaoImpl::getRecentPostsOfTopic(unsigned long id, int amount, int start,
                                        const std::function<void(std::vector<Post>&&)> &callback) {
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


    std::vector<Post> returnVector;

    DBClient.query(sql.str(),
                   [&](const MYSQL_ROW &rows) {

                       if (rows[0] == nullptr) {
                           returnVector.push_back(
                                   Post{std::stoul(rows[0]),
                                        Topic{std::stoul(rows[1])},
                                        User{std::stoul(rows[2])},
                                        rows[3],
                                        rows[4],
                                        rows[5]});
                       } else
                           callback(std::move(returnVector));


                   },
                   [&](const std::string &, int) {
                       callback({});
                   });


}

void PostDaoImpl::getCreator(unsigned long id,const std::function<void(User&&)> &callback) {

    std::ostringstream sql;
    sql <<
        "SELECT u.id, u.username , u.password, u.salt, DATE_FORMAT(u.creationDate, '%d/%m/%Y') "
        "FROM User u left JOIN Post p on u.id = p.creatorID"
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
                                   rows[5]
                           });
                       }

                   },
                   [&](const std::string &, int) {
                       callback({});
                   });


}

void PostDaoImpl::getTopic(unsigned long id,const std::function<void(Topic&&)> &callback) {

    std::ostringstream sql;
    sql <<
        "SELECT t.id, t.creatorID , t.title, t.description, DATE_FORMAT(t.creationDate, '%d/%m/%Y') "
        "FROM Topic t left JOIN Post p on u.id = p.creatorID"
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
                                   rows[5]
                           });
                       }
                   },
                   [&](const std::string &, int) {
                       callback({});
                   });


}

void PostDaoImpl::getById(unsigned long id,const std::function<void(Post&&)> &callback) {

    std::ostringstream sql;
    sql <<
        "SELECT id, creatorID, title, description, DATE_FORMAT(creationDate, '%d/%m/%Y') "
        "FROM Topic "
        "WHERE id = " << id << ";";

    DBClient.query(sql.str(),
                   [&](const MYSQL_ROW &rows) {

                       if (rows[0] == nullptr) {
                           callback(Post{
                                   std::stoul(rows[0]),
                                   Topic{std::stoul(rows[1])},
                                   User{std::stoul(rows[2])},
                                   rows[3],
                                   rows[4],
                                   rows[5]});
                       }
                   },
                   [&](const std::string &, int) {
                       callback({});
                   });


}

void PostDaoImpl::getCommentCount(unsigned long id,const std::function<void(int)> &callback) {
    std::ostringstream sql;
    sql <<
        "SELECT COUNT(*)"
        "FROM Post p left JOIN Comment c on p.id = c.posterID"
        "WHERE p.id = " << id << ";";


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
