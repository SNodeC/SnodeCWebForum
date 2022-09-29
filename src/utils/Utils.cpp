// Created by student on 2022-09-20.
//

#include <sstream>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <express/Request.h>
#include <iostream>
#include <express/Response.h>
#include "Utils.h"

std::string Utils::getFieldByName(unsigned char *bodyData, const std::string &fieldName) {

    std::string bodyString(reinterpret_cast<char *>(bodyData));

    int index = bodyString.find(fieldName);
    int index2 = bodyString.find('=', index) + 1;
    int index3 = bodyString.find('&', index);

    std::string result = bodyString.substr(index2, index3 - (index2));
    return result;
}

ustring Utils::createRandomSalt(size_t length) {
    unsigned char salt[length];
    RAND_bytes(salt, length);
    return ustring{salt, length};
}

std::string Utils::hashPassword(const std::string &password, const ustring &salt, int iterations, int hashLength) {

    std::ostringstream resultStream;

    const char *passPtr = password.c_str();
    const unsigned char *saltPtr = salt.c_str();
    unsigned char result[hashLength];
    int success = PKCS5_PBKDF2_HMAC(passPtr,
                                    (int) (password.size() - 1),
                                    saltPtr, (int) salt.size() - 1,
                                    iterations,
                                    EVP_sha1(),
                                    hashLength,
                                    result
    );
    if (success) {
        for (int i = 0; i < hashLength; ++i) {
            resultStream << std::hex << (int) result[i];
        }

        return resultStream.str();
    } else {
        return {};
    }
}

void Utils::sendFile([[maybe_unused]] express::Request &(req), [[maybe_unused]] express::Response &(res)) {

    const std::string path = "." + req.originalUrl;
    res.sendFile(path, [&](int) { (res.sendStatus(400)); });
}


std::string Utils::escapeForHTML(const std::string &data) {
    std::string result;
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

std::string Utils::escapeForSQL(const std::string& data)
{
    std::string result;
    result.reserve(data.size());
    for(size_t pos = 0; pos != data.size(); ++pos) {
        switch(data[pos]) {
            case '\0':   result.append("\\\0"); break;
            case '\n':   result.append("\\\n"); break;
            case '\r':   result.append("\\\r"); break;
            case '\'':   result.append("\\\'"); break;
            case '\"':   result.append("\\\""); break;
            case '\\':   result.append("\\\\"); break;
            case '\x1A': result.append("\\\x1A"); break;
            default:     result.append(&data[pos], 1); break;
        }
    }
}
