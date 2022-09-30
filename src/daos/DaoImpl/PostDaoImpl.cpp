//
// Created by student on 9/21/22.
//

#include <sstream>
#include "PostDaoImpl.h"
#include "../../utils/Utils.h"


void PostDaoImpl::create(const std::string &title, const std::string &content, unsigned long userID,
                         unsigned long topicId, std::function<void(bool)> callback) {

    std::ostringstream sql;
    sql <<
        "INSERT INTO Post (topicID, creatorID, title, content) "
        "VALUES (" << topicId << "," << userID << ",'" << Utils::escapeForSQL(title) << "','" << Utils::escapeForSQL(content) << "');";

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
        "WHERE topicID = " << id << " "
                                    "ORDER BY creationDate DESC ";

    if (amount != -1) {
        sql <<
            "LIMIT " << amount << " "
                                  "OFFSET " << start;
    }
    sql << ";";

    std::shared_ptr<std::vector<Post>> postsPtr = std::make_shared<std::vector<Post>>();

    DBClient.query(sql.str(),
                   [callback, postsPtr](const MYSQL_ROW &rows) {

                       if (rows != nullptr && rows[0] != nullptr) {
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

    std::shared_ptr<size_t> counterPtr = std::make_shared<size_t>(0);


    std::ostringstream sql;
    sql <<
        "SELECT u.id, u.username , u.passwordHash, u.salt, u.avatarURL, u.sessionToken , DATE_FORMAT(u.creationDate, '%d/%m/%Y') "
        "FROM User u left JOIN Post p on u.id = p.creatorID "
        "WHERE p.id = " << id << ";";

    DBClient.query(sql.str(),
                   [callback, counterPtr](const MYSQL_ROW &rows) {

                       if (rows != nullptr && rows[0] != nullptr) {
                           callback(User{
                                   std::stoul(rows[0]),
                                   rows[1],
                                   rows[2],
                                   Utils::hexToChar(rows[3]),
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

void PostDaoImpl::getTopic(unsigned long id, std::function<void(Topic &&)> callback) {
    std::shared_ptr<size_t> counterPtr = std::make_shared<size_t>(0);

    std::ostringstream sql;
    sql <<
        "SELECT t.id, t.creatorID , t.title, t.description, DATE_FORMAT(t.creationDate, '%d/%m/%Y') "
        "FROM Topic t left JOIN Post p on t.id = p.topicID "
        "WHERE p.id = " << id << ";";

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

void PostDaoImpl::getById(unsigned long id, std::function<void(Post &&)> callback) {
    std::shared_ptr<size_t> counterPtr = std::make_shared<size_t>(0);

    std::ostringstream sql;
    sql <<
        "SELECT id, topicID , creatorID, title, content, DATE_FORMAT(creationDate, '%d/%m/%Y') "
        "FROM Post "
        "WHERE id = " << id << ";";

    DBClient.query(sql.str(),
                   [callback, counterPtr](const MYSQL_ROW &rows) {

                       if (rows != nullptr && rows[0] != nullptr) {
                           callback(Post{
                                   std::stoul(rows[0]),
                                   Topic{std::stoul(rows[1])},
                                   User{std::stoul(rows[2])},
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

void PostDaoImpl::getCommentCount(unsigned long id, std::function<void(int)> callback) {

    std::shared_ptr<size_t> counterPtr = std::make_shared<size_t>(0);

    std::ostringstream sql;
    sql <<
        "SELECT COUNT(*) "
        "FROM Comment "
        "WHERE postID = " << id << ";";


    DBClient.query(sql.str(),
                   [callback, counterPtr](const MYSQL_ROW &rows) {
                       if (rows != nullptr && rows[0] != nullptr) {

                           callback(std::stoi(rows[0]));
                           ++(*counterPtr);

                       } else if (*counterPtr == 0) {

                           callback(-1);
                       }
                   },
                   [callback](const std::string &, int) {
                       callback(-1);
                   });
}
