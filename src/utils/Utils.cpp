// Created by student on 2022-09-20.
//

#include "Utils.h"
std::string Utils::GetFieldByName(unsigned char* bodyData, std::string fieldName) {

    std::string bodyString(reinterpret_cast<char *>(bodyData));

    int index = bodyString.find(fieldName);
    int index2 = bodyString.find('=', index ) +1;
    int index3 = bodyString.find('&', index);

    std::string result = bodyString.substr(index2, index3-(index2));
    return result;


}
