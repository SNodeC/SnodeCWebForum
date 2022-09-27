// Created by student on 2022-09-20.
//

#include <sstream>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include "Utils.h"

std::string Utils::GetFieldByName(unsigned char *bodyData, std::string fieldName) {

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

std::string Utils::escapeForHTML(std::string& data) {
    std::string result;
    result.reserve(data.size());
    for(size_t pos = 0; pos != data.size(); ++pos) {
        switch(data[pos]) {
            case '&':  result.append("&amp;");  break;
            case '\"': result.append("&quot;"); break;
            case '\'': result.append("&#39;");  break;
            case '<':  result.append("&lt;");   break;
            case '>':  result.append("&gt;");   break;
            default:   result.append(&data[pos], 1); break;
        }
    }
    return result;
}
