//
// Created by student on 9/14/22.
//
#include <express/legacy/in/WebApp.h>
#include <iostream>

int main(int argc, char *argv[]) {

    express::WebApp::init(argc, argv
    );

    express::legacy::in::WebApp legacyApp("getPost");

    legacyApp.get("/", []APPLICATION(req, res) {
        res.cookie("Testcookie", "CookieValue", {{"Max-Age", "3600"}});
        res.send(
                "<html>"
                "    <head>"
                "        <style>"
                "            main {"
                "                min-height: 30em;"
                "                padding: 3em;"
                "                background-image: repeating-radial-gradient( circle at 0 0, #fff, #ddd 50px);"
                "            }"
                "            input[type=\"file\"] {"
                "                display: block;"
                "                margin: 2em;"
                "                padding: 2em;"
                "                border: 1px dotted;"
                "            }"
                "        </style>"
                "    </head>"
                "    <body>"
                "        <h1>Datei-Upload mit input type=\"file\"</h1>"
                "        <main>"
                "            <h2>Schicken Sie uns was Schickes!</h2>"
                "            <form method=\"post\" enctype=\"multipart/form-data\">"
                "                <label> Wählen Sie eine Textdatei (*.txt, *.html usw.) von Ihrem Rechner aus."
                "                    <input name=\"datei\" type=\"file\" size=\"50\" accept=\"text/*\">"
                "                </label>"
                "                <button>… und ab geht die Post!</button>"
                "            </form>"
                "        </main>"
                "    </body>"
                "</html>"
        );
    });
    legacyApp.post("/", []APPLICATION(req, res) {

        std::cout << "Cookie-Value of \"TestCookie\": " << req.cookie("TestCookie");

        std::cout << "Content-Type: " << req.header("Content-Type") << std::endl;
        std::cout << "Content-Length: " << req.header("Content-Length") << std::endl;

        req.body.push_back(0);
        std::cout << "Body: " << std::endl;
        std::cout << req.body.data() << std::endl;
        res.send("<html>"
                 "    <body>"
                 "        <h1>Thank you</h1>"
                 "    </body>"
                 "</html>");

    });

    legacyApp.listen(8080, [](
            const express::legacy::in::WebApp::SocketAddress &socketAddress,
            int err
    ) -> void {
        if (err != 0) {
            std::cerr << "ListenFailed" <<
                      std::endl;
        } else {
            std::cout << "GetPostServer is listening on" << socketAddress.

                    toString();

        }
    });

}