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
#include "daos/DaoInterfaces/UserDao.h"
#include "service/HTMLResponseCreationService.h"
#include "service/UserService.h"
#include "daos/DaoImpl/CommentDaoImpl.h"
#include "daos/DaoImpl/PostDaoImpl.h"
#include "daos/DaoImpl/TopicDaoImpl.h"


using namespace std;

void sendFile([[maybe_unused]] express::Request &(req), [[maybe_unused]] express::Response &(res)) {

    const std::string path = "." + req.originalUrl;
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

    topicDao.getPostCount(1, [](int count) {

        cout << count << endl;

/*        for (auto t: topics) {

            cout << t.title << endl;

        }*/

    });


    express::WebApp::init(argc, argv);

    express::legacy::in::WebApp legacyApp("getPost");

    legacyApp.get("/", [&]APPLICATION(req, res) {

        string username = req.cookie(USERNAMECOOKIE);
        string sessionTkn = req.cookie(SESSIONTOKEN);
        userService.checkUserSession(username, sessionTkn, [&](bool b) {
            htmlResponseCreationService.createHomeResponseFromDao(b ? username : "", [&](string s) { res.send(s); });
        });
    });


    legacyApp.get("/home", []APPLICATION(req, res) {

        res.send("<!DOCTYPE html>\n"
                 "<html lang=\"en\">\n"
                 "<head>\n"
                 "    <meta charset=\"UTF-8\">\n"
                 "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                 "    <title>Our nice Forum</title>\n"
                 "\n"
                 "    <link rel=\"stylesheet\" href=\"./css/style.css\">\n"
                 "    <link href='https://css.gg/heart.css' rel='stylesheet'>\n"
                 "\n"
                 "</head>\n"
                 "\n"
                 "<body>\n"
                 "    <header>\n"
                 "        <!--NavBar Section-->\n"
                 "        <div class=\"navbar\">\n"
                 "            <div class=\"brand\"><a href=\"home.html\"><h1>Unproblematic Internet Forum</h1></a></div>\n"
                 "            <div class=\"logout-align\">\n"
                 "                <div class=\"logout\"> \n"
                 "                    <span id=\"username\"> User </span>\n"
                 "                    <br>\n"
                 "                    <a id=\"logout\">Log out</a>\n"
                 "                </div>\n"
                 "            </div>\n"
                 "        </div>\n"
                 "    </header>\n"
                 "\n"
                 "    <div class=\"container\">\n"
                 "        \n"
                 "        <div class=\"subforum rainbow-box\">\n"
                 "\n"
                 "            <div class=\"subforum-title\">\n"
                 "                <div><h2>Topics</h2></div>\n"
                 "                <div class=\"right\"><a id=\"toggle-topic\"><h2 id=\"toggle-text\">+ Add new Topic</h2></a></div>\n"
                 "            </div>\n"
                 "\n"
                 "            <!-- TODO: add comment functionality-->\n"
                 "            <div id=\"hide_topic\" class=\"hidden\">\n"
                 "                <div class=\"rainbow-box\">\n"
                 "                    <textarea class=\"title\" name=\"topic-name\" rows=\"1\" cols=\"50\" placeholder=\"Topic Name goes here.\"></textarea><br>\n"
                 "                    <textarea class=\"content\" name=\"topic-description\" rows=\"4\" cols=\"50\" placeholder=\"Describe your Topic you want to add.\"></textarea><br>\n"
                 "                    <input  id=\"submit-topic\" class=\"submit\" type=\"submit\" value=\"Submit Topic\">\n"
                 "                </div>\n"
                 "            </div>\n"
                 "\n"
                 "\n"
                 "            <!-- TODO: duplicate those lines for multiple entries-->\n"
                 "            <!------------------------------------------------------------------>\n"
                 "            <div class=\"subforum-row\">\n"
                 "                <div class=\"subforum-icon subforum-column center\">\n"
                 "                    <i class=\"gg-heart center\"></i>\n"
                 "                </div>\n"
                 "\n"
                 "                <div class=\"subforum-description subforum-column\">\n"
                 "                    <!-- TODO: insert link to topic-->\n"
                 "                    <h4><a href=\"topic.html\">Title</a></h4>\n"
                 "                    <p>Description: Um was es halt da jetzt so geht in dem.</p>\n"
                 "                </div>\n"
                 "\n"
                 "                <!-- TODO: if counting not possible delete this div & change grid setup in style.css-->\n"
                 "                <div class=\"subforum-stats subforum-column center\">\n"
                 "                    <span>24 Subtopics</span>\n"
                 "                </div>\n"
                 "\n"
                 "                <!-- TODO: if last post not possible, delete or add in sth different, dont forget to change gris in style.css-->\n"
                 "                <div class=\"subforum-info subforum-column center\">\n"
                 "                    Last post by User on DATUM\n"
                 "                </div>\n"
                 "            </div>\n"
                 "\n"
                 "            <hr class=\"subforum-devider\">\n"
                 "            <!------------------------------------------------------------------>\n"
                 "\n"
                 "\n"
                 "            \n"
                 "           \n"
                 "        </div>\n"
                 "    </div>\n"
                 "\n"
                 "\n"
                 "    <footer>\n"
                 "        <span>\n"
                 "            &copy;  This is our snode.c project | All Rights Reserved to its respective owners and whatnot\n"
                 "            <br>  Asteriou Philipp, Boess Leopold, Demelmayr Martin & Zuehlke Samuel\n"
                 "        </span>\n"
                 "    </footer>\n"
                 "\n"
                 "    <script src=\"./js/main.js\"></script>\n"
                 "</body>\n"
                 "</html>"

        );

    });

    legacyApp.get("/:dir(js|css|assets)/:suffix", sendFile);

    legacyApp.get("/:topic/:post", []APPLICATION(req, res) {

        req.params["topic"];
        req.params["post"];


    });


    legacyApp.use([]APPLICATION(req, res) {
        res.status(404).send("<!DOCTYPE html>\n"
                             "<html lang=\"en\">\n"
                             "<head>\n"
                             "    <meta charset=\"UTF-8\">\n"
                             "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                             "    <title>Our nice Forum</title>\n"
                             "\n"
                             "    <link rel=\"stylesheet\" href=\"./css/style.css\">\n"
                             "    <link href='https://css.gg/heart.css' rel='stylesheet'>\n"
                             "\n"
                             "</head>\n"
                             "\n"
                             "<body>\n"
                             "    <header>\n"
                             "        <!--NavBar Section-->\n"
                             "        <div class=\"navbar\">\n"
                             "            <div class=\"brand\"><a href=\"home.html\"><h1>Unproblematic Internet Forum</h1></a></div>\n"
                             "        </div>\n"
                             "    </header>\n"
                             "\n"
                             "        \n"
                             "    <div class=\" rainbow-box\">\n"
                             "        <span class=\"error\">404</span>\n"
                             "        <h2 class=\"center\">Page not found</h2>\n"
                             "        <p class=\"center\">We looked all over but I thinkt the page you are looking for does not exist, \n"
                             "        <br> nor ever wil to be frank. Who knows honestly? We certainly dont. Maybe you? </p>\n"
                             "    </div>\n"
                             "\n"
                             "\n"
                             "    <footer>\n"
                             "        <span>\n"
                             "            &copy;  This is our snode.c project | All Rights Reserved to its respective owners and whatnot\n"
                             "            <br>  Asteriou Philipp, Boess Leopold, Demelmayr Martin & Zuehlke Samuel\n"
                             "        </span>\n"
                             "    </footer>\n"
                             "\n"
                             "    <script src=\"./js/main.js\"></script>\n"
                             "</body>\n"
                             "</html>"
        );
    });
    /*  legacyApp.get("/:(\\d*)", []APPLICATION(req, res) {
        sendFile(req, res);
    });*/

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


