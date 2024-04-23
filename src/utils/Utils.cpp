// Created by student on 2022-09-20.
//

#include "Utils.h"
#include <express/Request.h>
#include <express/Response.h>
#include <iostream>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <sstream>

string Utils::getFieldByName(char *bodyData, const string &fieldName) {

  string bodyString(reinterpret_cast<char *>(bodyData));

  int index = bodyString.find(fieldName);
  int index2 = bodyString.find('=', index) + 1;
  int index3 = bodyString.find('&', index);

  string result = bodyString.substr(index2, index3 - (index2));
  return result;
}

ustring Utils::createRandomSalt(size_t length) {
  unsigned char salt[length];
  RAND_bytes(salt, length);
  return ustring{salt, length};
}

string Utils::hashPassword(const string &password, const ustring &salt,
                           int iterations, int hashLength) {

  const char *passPtr = password.c_str();
  const unsigned char *saltPtr = salt.c_str();

  int binaryHashLength = hashLength % 2 ? hashLength / 2 + 1 : hashLength / 2;

  unsigned char result[binaryHashLength];
  int success = PKCS5_PBKDF2_HMAC(passPtr, (int)(password.size() - 1), saltPtr,
                                  (int)salt.size() - 1, iterations, EVP_sha1(),
                                  binaryHashLength, result);
  if (success) {
    return charToHex(result, binaryHashLength);
  } else {
    return {};
  }
}

string Utils::charToHex(const unsigned char *inputString, size_t length) {
  std::ostringstream resultStream;

  for (size_t i = 0; i < length; ++i) {
    if (inputString[i] < 16) {
      resultStream << "0";
    }
    resultStream << std::hex << (int)inputString[i];
  }

  return resultStream.str();
}

ustring Utils::hexToChar(const std::string &inputString) {

  std::basic_ostringstream<unsigned char> result;

  for (int i = 0; i < inputString.length() / 2; ++i) {

    result << (unsigned char)std::stoul(inputString.substr(i * 2, 2), nullptr,
                                        16);
  }
  return result.str();
}

std::string Utils::hexToString(const std::string &inputString) {

  std::ostringstream result;

  for (int i = 0; i < inputString.length() / 2; ++i) {

    result << (char)std::stoul(inputString.substr(i * 2, 2), nullptr, 16);
  }
  return result.str();
}

void Utils::sendFile([[maybe_unused]] const std::shared_ptr<express::Request> &req,
    [[maybe_unused]] const std::shared_ptr<express::Response> &res) {

  const string path = "." + req->originalUrl;
  res->sendFile(path, [&](int) { (res->sendStatus(400)); });
}

string Utils::escapeForHTML(const string &data) {
  string result;
  result.reserve(data.size());
  for (size_t pos = 0; pos != data.size(); ++pos) {
    switch (data[pos]) {
    case '&':
      result.append("&amp;");
      break;
    case '\"':
      result.append("&quot;");
      break;
    case '\'':
      result.append("&#39;");
      break;
    case '<':
      result.append("&lt;");
      break;
    case '>':
      result.append("&gt;");
      break;
    default:
      result.append(&data[pos], 1);
      break;
    }
  }
  return result;
}

string Utils::escapeForSQL(const string &data) {
  string result;
  result.reserve(data.size());
  for (size_t pos = 0; pos != data.size(); ++pos) {
    switch (data[pos]) {
    case '\0':
      result.append("\\\0");
      break;
    case '\n':
      result.append("\\\n");
      break;
    case '\r':
      result.append("\\\r");
      break;
    case '\'':
      result.append("\\\'");
      break;
    case '\"':
      result.append("\\\"");
      break;
    case '\\':
      result.append("\\\\");
      break;
    case '\x1A':
      result.append("\\\x1A");
      break;
    default:
      result.append(&data[pos], 1);
      break;
    }
  }
  return result;
}
