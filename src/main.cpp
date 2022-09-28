//
// Created by student on 9/14/22.
//
#include <iostream>
#include <express/legacy/in/WebApp.h>
#include <database/mariadb/MariaDBConnection.h>
#include <database/mariadb/MariaDBClient.h>
#include <database/mariadb/MariaDBCommand.h>
#include <database/mariadb/MariaDBConnectionDetails.h>
#include <database/mariadb/commands/sync/MariaDBUseResultCommand.h>
#include <database/mariadb/MariaDBCommandSequence.h>
#include "daos/DaoImpl/UserDaoImpl.h"
#include "service/HTMLResponseCreationService.h"
#include "service/UserService.h"
#include "daos/DaoImpl/CommentDaoImpl.h"
#include "daos/DaoImpl/PostDaoImpl.h"
#include "daos/DaoImpl/TopicDaoImpl.h"


using namespace std;

void sendFile([[maybe_unused]] express::Request &(req), [[maybe_unused]] express::Response &(res)) {

    const std::string path = "." + req.originalUrl;
    std::cout << req.originalUrl << std::endl;
    res.sendFile(path, [&](int) { (res.sendStatus(400)); });
}


int main(int argc, char *argv[]) {

    static const string USERNAMECOOKIE = "Username";
    static const string SESSIONTOKEN = "SessionToken";

    const database::mariadb::MariaDBConnectionDetails DBConnectionDetails{
            "localhost",
            "fidi",
            "1234",
            "Forum",
            3307,
            "/var/run/mysqld/mysqld.sock",
            0
    };

    database::mariadb::MariaDBClient DBClient(DBConnectionDetails);


    UserDaoImpl userDao(DBClient);
    CommentDaoImpl commentDao(DBClient);
    PostDaoImpl postDao(DBClient);
    TopicDaoImpl topicDao(DBClient);


    service::HTMLResponseCreationService htmlResponseCreationService(commentDao, postDao, topicDao);
    service::UserService userService(userDao);

    express::WebApp::init(argc, argv);
    express::legacy::in::WebApp legacyApp("getPost");

    legacyApp.get("/t/:topic([1-9]+))", [&]APPLICATION(req, res) {

        unsigned long topicID = std::stoul(req.params["topic"]);

        string username = req.cookie(USERNAMECOOKIE);
        string sessionTkn = req.cookie(SESSIONTOKEN);

        userService.checkUserSession(username, sessionTkn, [&](bool b) {
            htmlResponseCreationService.createTopicOverviewResponseFromDao(topicID, b ? username : "",
                                                                           [&](string s) { res.send(s); });
        });

    });

    legacyApp.get("/t/:topic([1-9]+)/:post([1-9]+)", [&]APPLICATION(req, res) {

        unsigned long postID = std::stoul(req.params["post"]);

        string username = req.cookie(USERNAMECOOKIE);
        string sessionTkn = req.cookie(SESSIONTOKEN);

        userService.checkUserSession(username, sessionTkn, [&](bool b) {
            htmlResponseCreationService.createPostOverviewResponseFromDao(postID, b ? username : "",
                                                                           [&](string s) { res.send(s); });
        });

    });


    legacyApp.get("", [&]APPLICATION(req, res) {

        string username = req.cookie(USERNAMECOOKIE);
        string sessionTkn = req.cookie(SESSIONTOKEN);
        userService.checkUserSession(username, sessionTkn, [&](bool b) {
            htmlResponseCreationService.createHomeResponseFromDao(b ? username : "", [&](string s) { res.send(s); });
        });
    });


    legacyApp.get("/:dir(js|css|assets)/:suffix", sendFile);

    legacyApp.use([&]APPLICATION(req, res) {
        string username = req.cookie(USERNAMECOOKIE);
        string sessionTkn = req.cookie(SESSIONTOKEN);
        userService.checkUserSession(username, sessionTkn, [&](bool b) {
            res.status(404).send(service::HTMLResponseCreationService::createNotFoundResponse(b ? username : ""));
        });

    });

    /*  legacyApp.post("/", []APPLICATION(req, res) {
             //std::cout << "Cookie-Value of \"TestCookie\": " << req.cookie("TestCookie");
             std::cout << "Content-Type: " << req.get("Content-Type") << std::endl;
             std::cout << "Content-Length: " << req.get("Content-Length") << std::endl;

             req.body.push_back(0);
             std::cout << "Body: " << std::endl;
             std::cout << req.body.data() << std::endl;

             res.send("<html>"
                      "    <body>"
                      "        <h1> Username= " + Utils::GetFieldByName(req.body.data(), "UserName") + "</h1>"
                                                                                                       "        <h1> Password= " +
                      Utils::GetFieldByName(req.body.data(), "PassWord") + "</h1>"
                                                                           "    </body>"
                                                                           "</html>");

         });*/


    legacyApp.listen(8080, [](
            const express::legacy::in::WebApp::SocketAddress &socketAddress,
            int err
    ) -> void {
        if (err != 0) {
            std::cerr << "ListenFailed" <<
                      std::endl;
        } else {
            std::cout << "GetPostServer is listening on " << socketAddress.toString() << std::endl;
        }
    });

    return express::WebApp::start();

}


