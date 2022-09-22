//
// Created by student on 2022-09-20.
//

#ifndef GETANDPOSTSERVERTEMPLATE_UTILS_H
#define GETANDPOSTSERVERTEMPLATE_UTILS_H


#include <string>

class Utils {
public:
    static std::string GetFieldByName(unsigned char* bodyData, std::string fieldName);
};



#endif //GETANDPOSTSERVERTEMPLATE_UTILS_H
