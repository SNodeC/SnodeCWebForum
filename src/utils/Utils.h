//
// Created by student on 2022-09-20.
//

#ifndef GETANDPOSTSERVERTEMPLATE_UTILS_H
#define GETANDPOSTSERVERTEMPLATE_UTILS_H


#include <string>
#include <express/Request.h>
#include <express/Response.h>

typedef std::basic_string<unsigned char> ustring;

class Utils {
public:
    static std::string getFieldByName(unsigned char *bodyData, const std::string &fieldName);

    static ustring createRandomSalt(size_t length);

    static void sendFile([[maybe_unused]] express::Request &(req), [[maybe_unused]] express::Response &(res));


    static std::string
    hashPassword(const std::string &password, const ustring &salt, int iterations = 4096, int hashLength = 16);

    static std::string escapeForHTML(const std::string& data);

    static std::string escapeForSQL(const std::string& data);
};


#endif //GETANDPOSTSERVERTEMPLATE_UTILS_H
