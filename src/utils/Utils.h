//
// Created by student on 2022-09-20.
//

#ifndef GETANDPOSTSERVERTEMPLATE_UTILS_H
#define GETANDPOSTSERVERTEMPLATE_UTILS_H


#include <string>
#include <express/Request.h>
#include <express/Response.h>

using std::string;

typedef std::basic_string<unsigned char> ustring;

class Utils {
public:
    static string getFieldByName(unsigned char *bodyData, const string &fieldName);

    static ustring createRandomSalt(size_t length);

    static void sendFile([[maybe_unused]] express::Request &(req), [[maybe_unused]] express::Response &(res));


    static string
    hashPassword(const string &password, const ustring &salt, int iterations = 4096, int hashLength = 16);

    static string charToHex(const unsigned char *inputString, size_t length);

    static ustring hexToChar(const std::string& inputString);

    static string escapeForHTML(const string &data);

    static string escapeForSQL(const string &data);

    static string hexToString(const string &inputString);
};


#endif //GETANDPOSTSERVERTEMPLATE_UTILS_H
