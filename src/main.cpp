//
// Created by student on 9/14/22.
//
#include <iostream>
#include <numeric>
#include <express/legacy/in/WebApp.h>
#include <database/mariadb/MariaDBConnection.h>
#include <database/mariadb/MariaDBClient.h>
#include <database/mariadb/MariaDBCommand.h>
#include <database/mariadb/MariaDBConnectionDetails.h>
#include <database/mariadb/commands/sync/MariaDBUseResultCommand.h>
#include <database/mariadb/MariaDBCommandSequence.h>
#include <express/tls/in/WebApp.h>
#include "daos/DaoImpl/UserDaoImpl.h"
#include "service/HTMLResponseCreationService.h"
#include "service/UserService.h"
#include "daos/DaoImpl/CommentDaoImpl.h"
#include "daos/DaoImpl/PostDaoImpl.h"
#include "daos/DaoImpl/TopicDaoImpl.h"
#include "service/TopicService.h"
#include "service/PostService.h"
#include "service/CommentService.h"
#include "utils/Utils.h"


#define CERTF <PATH_TO_SERVER_CERTIFICATE_CHAIN_FILE>
#define KEYF <PATH_TO_SERVER_CERTIFICATE_KEY_FILE>
#define KEYFPASS <PASSWORD_OF_THE_SERVER_CERTIFICATE_KEY_FILE>

using std::string;
using std::shared_ptr;
using std::make_shared;
using std::ostringstream;

int main(int argc, char *argv[]) {

    std::basic_string<unsigned char> text((const unsigned char *) "passwort");

    std::string hex = Utils::charToHex(text.c_str(), text.length());

    Utils::hexToChar(hex);

    static const string USERNAMECOOKIE = "Username";
    static const string SESSIONTOKEN = "SessionToken";
    static const string ERRORSEP = ";";

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
    service::TopicService topicService(topicDao, userDao);
    service::PostService postService(postDao, userDao);
    service::CommentService commentService(commentDao, userDao);

    express::WebApp::init(argc, argv);
    express::legacy::in::WebApp legacyApp("getPost");

    legacyApp.get("/t/:topic([1-9]+))", [&]APPLICATION(req, res) {

        unsigned long topicID = std::stoul(req.params["topic"]);
        shared_ptr<string> userNamePtr = make_shared<string>(req.cookie(USERNAMECOOKIE));
        shared_ptr<string> sessionTknPtr = make_shared<string>(req.cookie(SESSIONTOKEN));

        userService.checkUserSession(*userNamePtr, *sessionTknPtr,
                                     [topicID, &topicService, userNamePtr, &htmlResponseCreationService, &res](bool b) {
                                         topicService.checkTopicId(topicID,
                                                                   [topicID, userNamePtr, &htmlResponseCreationService, &res](
                                                                           bool b) {
                                                                       if (b) {
                                                                           htmlResponseCreationService.createTopicOverviewResponseFromDao(
                                                                                   topicID, b ? *userNamePtr : "",
                                                                                   [&](std::string s) { res.send(s); });
                                                                       } else {
                                                                           res.status(404).send(
                                                                                   service::HTMLResponseCreationService::createNotFoundResponse(
                                                                                           b ? *userNamePtr : ""));
                                                                       }
                                                                   });
                                     });
    });

    legacyApp.get("/t/:topic([1-9]+)/:post([1-9]+)", [&]APPLICATION(req, res) {

        unsigned long topicID = std::stoul(req.params["topic"]);
        unsigned long postID = std::stoul(req.params["post"]);
        shared_ptr<string> userNamePtr = make_shared<string>(req.cookie(USERNAMECOOKIE));
        shared_ptr<string> sessionTknPtr = make_shared<string>(req.cookie(SESSIONTOKEN));

        userService.checkUserSession(
                *userNamePtr, *sessionTknPtr,
                [topicID, postID, &postService, userNamePtr, &htmlResponseCreationService, &res](
                        bool b) {
                    postService.checkPostId(
                            postID, topicID,
                            [postID, userNamePtr, &htmlResponseCreationService, &res](
                                    bool b) {
                                if (b) {
                                    htmlResponseCreationService.createPostOverviewResponseFromDao(
                                            postID, b ? *userNamePtr : "",
                                            [&](std::string s) { res.send(s); });
                                } else {
                                    res.status(404).send(
                                            service::HTMLResponseCreationService::createNotFoundResponse(
                                                    b ? *userNamePtr : ""));
                                }
                            });
                });
    });


    legacyApp.get("/t/", [&]APPLICATION(req, res) {

        shared_ptr<string> usernamePtr = make_shared<string>(req.cookie(USERNAMECOOKIE));
        shared_ptr<string> sessionTknPtr = make_shared<string>(req.cookie(SESSIONTOKEN));

        userService.checkUserSession((*usernamePtr), (*sessionTknPtr),
                                     [usernamePtr, &htmlResponseCreationService, &res](bool b) {
                                         htmlResponseCreationService.createHomeResponseFromDao(b ? (*usernamePtr) : "",
                                                                                               [&](std::string s) {
                                                                                                   res.send(s);
                                                                                               });
                                     });
    });

    legacyApp.get("/login/", [&]APPLICATION(req, res) {

        shared_ptr<string> usernamePtr = make_shared<string>(req.cookie(USERNAMECOOKIE));
        shared_ptr<string> sessionTknPtr = make_shared<string>(req.cookie(SESSIONTOKEN));


        userService.checkUserSession((*usernamePtr), (*sessionTknPtr),
                                     [usernamePtr, &res, &htmlResponseCreationService](bool b) {
                                         if (b) {
                                             htmlResponseCreationService.createHomeResponseFromDao((*usernamePtr),
                                                                                                   [&](std::string s) {
                                                                                                       res.send(s);
                                                                                                   });
                                         } else {
                                             res.send(service::HTMLResponseCreationService::createLoginPageResponse());
                                         }
                                     });
    });

    legacyApp.get("/register/", [&]APPLICATION(req, res) {

        shared_ptr<string> usernamePtr = make_shared<string>(req.cookie(USERNAMECOOKIE));
        shared_ptr<string> sessionTknPtr = make_shared<string>(req.cookie(SESSIONTOKEN));
        userService.checkUserSession(*usernamePtr, *sessionTknPtr, [&](bool b) {
            if (b) {
                htmlResponseCreationService.createHomeResponseFromDao(*usernamePtr,
                                                                      [&](std::string s) { res.send(s); });
            } else {
                res.send(service::HTMLResponseCreationService::createRegisterAccountResponse());
            }
        });
    });

    legacyApp.get("/:dir(js|css|assets)/:suffix", Utils::sendFile);

    legacyApp.post("/register/", [&]APPLICATION(req, res) {
        req.body.push_back(0);
        std::cout << req.body.data() << std::endl;

        shared_ptr<string> usernamePtr = make_shared<string>(Utils::getFieldByName(req.body.data(), "Username"));
        shared_ptr<string> passwordPtr = make_shared<string>(Utils::getFieldByName(req.body.data(), "Password"));

        userService.checkUserNameTaken((*usernamePtr), [usernamePtr, passwordPtr, &res, &userService](bool b) {
            if (b) {
                res.sendStatus(400);
            } else {
                userService.createUser((*usernamePtr), (*passwordPtr), [&](int err) {
                    if (err == service::UserService::SUCCESS) {
                        res.sendStatus(200);
                    } else {
                        std::vector<std::string> errorMessages = service::UserService::getUserCreateErrorMessages(err);
                        ostringstream errors;
                        for (const auto &error: errorMessages) {
                            errors << error << ";";
                        }
                        res.status(500).send(errors.str());
                    }
                });
            }
        });
    });

    legacyApp.post("/login/", [&]APPLICATION(req, res) {
        req.body.push_back(0);
        std::cout << req.body.data() << std::endl;

        shared_ptr<string> usernamePtr = make_shared<string>(Utils::getFieldByName(req.body.data(), "Username"));
        shared_ptr<string> passwordPtr = make_shared<string>(Utils::getFieldByName(req.body.data(), "Password"));

        userService.checkUserPassword(
                (*usernamePtr), (*passwordPtr),
                [usernamePtr, passwordPtr, &res, &userService](bool b) {
                    if (b) {
                        userService.createNewUserSession((*usernamePtr), [usernamePtr, &res](bool b, string s) {
                            if (b) {
                                res.cookie(USERNAMECOOKIE, (*usernamePtr),
                                           {{"Max-Age", "3600"}, {"path", "/"}, {"SameSite", "None"}});
                                res.cookie(SESSIONTOKEN, s, {{"Max-Age", "3600"}, {"path", "/"}, {"SameSite", "None"}});
                                res.sendStatus(200);
                            } else {
                                res.sendStatus(500);
                            }
                        });
                    } else {
                        res.sendStatus(400);
                    }
                });
    });

    legacyApp.post("/t", [&]APPLICATION(req, res) {

        req.body.push_back(0);
        std::cout << req.body.data() << std::endl;

        std::string title = Utils::getFieldByName(req.body.data(), "Title");
        std::string content = Utils::getFieldByName(req.body.data(), "Content");
        shared_ptr<string> usernamePtr = make_shared<string>(req.cookie(USERNAMECOOKIE));


        topicService.createTopic(title, content, *usernamePtr, [&](int err) {
            if (err == service::TopicService::SUCCESS) {
                res.sendStatus(200);

            } else {
                std::vector<std::string> errorMessages = service::TopicService::getTopicCreateErrorMessages(err);
                std::stringstream errors;
                for (const auto &error: errorMessages) {
                    errors << error << ERRORSEP;
                }
                res.status(500).send(errors.str());
            }
        });
    });

    legacyApp.post("/p/:topic([1-9]+))", [&]APPLICATION(req, res) {

        unsigned long topicID = std::stoul(req.params["topic"]);

        req.body.push_back(0);

        std::cout << req.body.data() << std::endl;

        std::string title = Utils::getFieldByName(req.body.data(), "Title");
        std::string content = Utils::getFieldByName(req.body.data(), "Content");
        shared_ptr<string> usernamePtr = make_shared<string>(req.cookie(USERNAMECOOKIE));


        postService.createPost(title, content, *usernamePtr, topicID, [&](int err) {
            if (err == service::PostService::SUCCESS) {
                res.sendStatus(200);

            } else {
                std::vector<std::string> errorMessages = service::PostService::getPostCreateErrorMessages(err);
                std::stringstream errors;
                for (const auto &error: errorMessages) {
                    errors << error << ERRORSEP;
                }
                res.status(500).send(errors.str());
            }
        });
    });

    legacyApp.post("/c/:post([1-9]+)", [&]APPLICATION(req, res) {

        unsigned long postID = std::stoul(req.params["post"]);

        req.body.push_back(0);
        std::cout << req.body.data() << std::endl;
        std::string content = Utils::getFieldByName(req.body.data(), "Content");
        std::string username = req.cookie(USERNAMECOOKIE);


        commentService.createComment(content, username, postID, [&](int err) {
            if (err == service::PostService::SUCCESS) {
                res.sendStatus(200);
            } else {
                std::vector<std::string> errorMessages = service::CommentService::getCommentCreateErrorMessages(err);
                std::stringstream errors;
                for (const auto &error: errorMessages) {
                    errors << error << ERRORSEP;
                }
                res.status(500).send(errors.str());
            }
        });
    });


    legacyApp.use([&]APPLICATION(req, res) {
        std::string username = req.cookie(USERNAMECOOKIE);
        std::string sessionTkn = req.cookie(SESSIONTOKEN);
        userService.checkUserSession(username, sessionTkn, [&](bool b) {
            res.status(404).send(service::HTMLResponseCreationService::createNotFoundResponse(b ? username : ""));
        });

    });


/*
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
*/

/*

      express::tls::in::WebApp tlsWebApp({{"certChain", CERTF},
                                      {"keyPEM", KEYF},
                                      {"password", KEYFPASS}});
      tlsWebApp.use(legacyApp);

*/


    legacyApp.listen(8080, [](
            const express::legacy::in::WebApp::SocketAddress &socketAddress,
            int err) {
        if (err != 0) {
            PLOG(FATAL) << "listen on port 8080";
        } else {
            VLOG(0) << "snode.c listening on port 8080 for legacy connections";
        }
    });
/*

      tlsWebApp.listen(8088, [](
              const express::legacy::in::WebApp::SocketAddress &socketAddress,
              int err) {
          if (err != 0) {
              PLOG(FATAL) << "listen on port 8088";
          } else {
              VLOG(0) << "snode.c listening on port 8088 for SSL/TLS connections";
          }
      });
*/

    return express::WebApp::start();

}


