//
// Created by student on 9/21/22.
//

#include <sstream>
#include "CommentDaoImpl.h"

void CommentDaoImpl::create(std::string content, int creatorID, int postID, std::function<void(bool)> callback) {

    std::ostringstream sql;
    sql <<
        "INSERT INTO Comment (creatorID, postID, commentText) "
        "VALUES (" << creatorID << ",'" << postID << "'" << content << "');";


    DBClient.exec(sql.str(),
                  [&]() { callback(true); },
                  [&](const std::string &, int) { callback(false); });

}

void CommentDaoImpl::getRecentCommentsOfPost(unsigned long id, int amount, int start,
                                             std::function<void(std::vector<Comment> &&)> callback) {

    std::ostringstream sql;
    sql <<
        "SELECT id, postID, creatorID, content, DATE_FORMAT(creationDate, '%d/%m/%Y') "
        "FROM Comment "
        "WHERE postID = " << id <<
        "ORDER BY creationDate DESC ";

    if (amount != -1) {
        sql <<
            "LIMIT " << amount <<
            "OFFSET " << start << ";";
    }

    std::vector<Comment> returnVector;

    DBClient.query(sql.str(),
                   [&](const MYSQL_ROW &rows) {
                       if (rows[0] == nullptr) {
                           returnVector.push_back(Comment{
                                   std::stoul(rows[0]),
                                   Post{std::stoul(rows[1])},
                                   User{std::stoul(rows[2])},
                                   rows[3],
                                   rows[4]
                           });
                       } else {
                           callback(std::move(returnVector));
                       }
                   },
                   [&](const std::string &, int) {
                       callback({});
                   });


}

void CommentDaoImpl::getCreator(unsigned long id, std::function<void(User &&)> callback) {

    std::ostringstream sql;
    sql <<
        "SELECT u.id, u.username , u.password, u.salt, DATE_FORMAT(u.creationDate, '%d/%m/%Y') "
        "FROM User u left JOIN Comment c on u.id = c.creatorID"
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

void CommentDaoImpl::getById(unsigned long id, std::function<void(Comment &&)> callback) {

    std::ostringstream sql;
    sql <<
        "SELECT id, postID, creatorID, content, DATE_FORMAT(creationDate, '%d/%m/%Y') "
        "FROM Comment "
        "WHERE id = " << id << ";";


    DBClient.query(sql.str(),
                   [&](const MYSQL_ROW &rows) {

                       if (rows[0] == nullptr) {
                           callback(Comment{
                                   std::stoul(rows[0]),
                                   Post{std::stoul(rows[1])},
                                   User{std::stoul(rows[2])},
                                   rows[3],
                                   rows[4]});
                       }
                   },
                   [&](const std::string &, int) {
                       callback({});
                   });


}
