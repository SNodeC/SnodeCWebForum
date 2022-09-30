#ifndef RESPONSESERVICETEST_USERSERVICE_H
#define RESPONSESERVICETEST_USERSERVICE_H

#include <functional>
#include <string>
#include <vector>

#include "../daos/DaoInterfaces/UserDao.h"

using std::function;
using std::string;
using std::vector;

typedef std::basic_string<unsigned char> ustring;

namespace service {
    class UserService {
    private:
        static std::string hashPassword(const string& password, const ustring& salt);
        static ustring createNewSalt();
        static std::string createNewSessionToken();
        static std::string createAvatarURL(const std::string& username);
        static bool checkUserNameFormat(const string& username);
        static bool checkPasswordFormat(const string& password);

        UserDao& _userDao;

    public:
        enum UserCreationResult {
            SUCCESS =          0b000,
            INVALID_USERNAME = 0b001,
            INVALID_PASSWORD = 0b010,
            INTERNAL_ERROR =   0b100
        };

        static vector<string> getUserCreateErrorMessages(int errorCode);

        UserService() = delete;
        UserService(const UserService&) = delete;
        UserService(UserService&&) = delete;
        UserService& operator=(const UserService&) = delete;
        UserService& operator=(UserService&&) = delete;

        explicit UserService(UserDao& userDao);

        void createUser(const string& username, const string& password, function<void(int)> callback);
        void checkUserNameTaken(const string& username, function<void(bool)> callback);
        void checkUserPassword(const string& username, const string& password, function<void(bool)> callback);
        void checkUserSession(const string& username, const string& sessionToken, function<void(bool)> callback);
        void createNewUserSession(const string& username, function<void(bool, string&&)> callback);
    };
} // service

#endif //RESPONSESERVICETEST_USERSERVICE_H
