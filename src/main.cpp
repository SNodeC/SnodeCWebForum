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
#include <filesystem>

#include "utils/Utils.h"


using namespace std;

void sendFile([[maybe_unused]] express::Request &(req), [[maybe_unused]] express::Response &(res)) {

    const std::string path = "." + req.originalUrl;
    std::filesystem::path file(path);
    if (std::filesystem::exists(file)) {
        res.sendFile(path, [](int) {});
    } else {
        (res.sendStatus(400));
    }

}

int main(int argc, char *argv[]) {


/*
    database::mariadb::MariaDBConnectionDetails DBConnectionDetails;

    DBConnectionDetails.database = "Forum";
    DBConnectionDetails.username = "fidi";
    DBConnectionDetails.password = "1234";
    DBConnectionDetails.hostname = "localhost";
    DBConnectionDetails.port = 3307;
    DBConnectionDetails.socket = "/var/run/mysqld/mysqld.sock";
    DBConnectionDetails.flags = 0;

    database::mariadb::MariaDBClient DBClient(DBConnectionDetails);

    std::function<void(const std::string &, unsigned int)> onError = [](const std::string &, unsigned int) {};

    std::function<void()> onExec;

    DBClient.exec("INSERT into Users ( username, password) VALUES ('Fidi','Passwd');", []() {},
                  [](const std::string &, unsigned int) {});

    DBClient.commit([]() {}, [](const std::string &, unsigned int) {});
*/

/*
    database::mariadb::MariaDBConnection DBConnection(&DBClient, DBConnectionDetails);

    std::function<void(MYSQL_RES *)> onUseResult = [](MYSQL_RES *) {};
    std::function<void(const std::string &, unsigned int)> onError = [](const std::string &, unsigned int) {};

    std::function<void()> onConnecting;
    std::function<void()> onConnect;

    database::mariadb::commands::sync::MariaDBUseResultCommand DBCommand(onUseResult, onError);
    //database::mariadb::commands::async::MariaDBConnectCommand ConnectCommand(DBConnectionDetails,onConnecting,onConnect,onError);
    database::mariadb::commands::async::MariaDBQueryCommand QueryCommand("Select * From Users", onConnect, onError);

    // MYSQL mysql;
    utils::Timeval currentTime = 10000.0;
    // ((database::mariadb::MariaDBCommand *) &QueryCommand)->commandStart(&mysql, currentTime);

    QueryCommand.setMariaDBConnection(&DBConnection);
    DBConnection.commandStart(currentTime);
*/

    express::WebApp::init(argc, argv);

    express::legacy::in::WebApp legacyApp("getPost");

    //std::cout << std::filesystem::current_path() << std::endl;

    legacyApp.get("/home", []APPLICATION(req, res) {
        res.send(
                "<!DOCTYPE html>\n"
                "<html lang=\"en\">\n"
                "<head>\n"
                "    <meta charset=\"UTF-8\">\n"
                "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                "    <title>Our nice Forum</title>\n"
                "\n"
                "    <link rel=\"stylesheet\" href=\"/css/style.css\">\n"
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
                "    <script src=\"/js/main.js\"></script>\n"
                "</body>\n"
                "</html>"

        );

    });

    legacyApp.get("/css", sendFile);
    legacyApp.get("/js", sendFile);
    legacyApp.get("/assets/fonts", sendFile);
    legacyApp.get("/assets/images", sendFile);

    /*
       legacyApp.get("/home", []APPLICATION(req, res) {
           res.sendFile("/home/student/voc/projects/SnodeCWebForum/resources/style.css", [](int) {});
       });
   */
    /*   legacyApp.get("/css", []APPLICATION(req, res) {
           res.sendFile("/home/student/voc/projects/SnodeCWebForum/resources/style.css", [](int) {});
       });*/
    /*

         legacyApp.get("//", []APPLICATION(req, res) {
             res.send(
                     "<html>"
                     "<h1>  ka plan was passiert </h1>"
                     "</html>"
             );
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


