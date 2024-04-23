//
// Created by student on 2022-09-20.
//

#ifndef GETANDPOSTSERVERTEMPLATE_UTILS_H
#define GETANDPOSTSERVERTEMPLATE_UTILS_H

#include <express/Request.h>
#include <express/Response.h>
#include <string>

using std::string;

typedef std::basic_string<unsigned char> ustring;

class Utils {
public:
  static string getFieldByName(char *bodyData, const string &fieldName);

  static ustring createRandomSalt(size_t length);

  static void
  sendFile([[maybe_unused]] const std::shared_ptr<express::Request> &(req),
           [[maybe_unused]] const std::shared_ptr<express::Response> &(res));

  static string hashPassword(const string &password, const ustring &salt,
                             int iterations = 4096, int hashLength = 16);

  static string charToHex(const unsigned char *inputString, size_t length);

  static ustring hexToChar(const std::string &inputString);

  static string escapeForHTML(const string &data);

  static string escapeForSQL(const string &data);

  static string hexToString(const string &inputString);
};

#endif // GETANDPOSTSERVERTEMPLATE_UTILS_H
