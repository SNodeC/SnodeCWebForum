#include <random>

#include "utils/Utils.h"
#include "UserService.h"


typedef service::UserService cls;

namespace service {

#pragma region Constants

    const size_t SALT_LEN = 16;
    const size_t HASH_LEN = 16;
    const size_t HASH_ITERATIONS = 4096;

    const size_t USERNAME_MIN_LENGTH = 3;
    const size_t PASSWORD_MIN_LENGTH = 8;

#pragma endregion

#pragma region Constructors

    UserService::UserService(UserDao& userDao) : _userDao(userDao) {}

#pragma endregion

#pragma region Static Methods

    std::string cls::createAvatarURL(const std::string& username) {
        static const string avatarAPI{
                "https://avatars.dicebear.com/api/identicon/"
        };

        static const string settingsAPI{
                ".svg?b=%2311111199&scale=65&colorLevel=600"
        };

        return avatarAPI + username + settingsAPI;
    }

    bool cls::checkUserNameFormat(const std::string& username) {
        bool result = true;
        result &= username.length() >= USERNAME_MIN_LENGTH;
        return result;
    }

    bool cls::checkPasswordFormat(const std::string& password) {
        bool result = true;
        result &= password.length() >= USERNAME_MIN_LENGTH;
        return result;
    }

#pragma endregion

#pragma region Instance Methods

    void cls::createUser(const string& username, const string& password, function<void(int)> callback) {
        int result = UserCreationResult::SUCCESS;
        if(!checkUserNameFormat(username)) { // invalid username
            result |= UserCreationResult::INVALID_USERNAME;
        }

        if (!checkPasswordFormat(password)) { // invalid password
            result |= UserCreationResult::INVALID_PASSWORD;
        }

        if (result != UserCreationResult::SUCCESS) {
            callback(result);
            return;
        }

        string avatarURL = createAvatarURL(username);
        ustring salt = Utils::createRandomSalt(SALT_LEN);
        string hash = Utils::hashPassword(password, salt, HASH_ITERATIONS, HASH_LEN);

        function<void(bool)> createCallback = [callback](bool success) {
            callback(success ? UserCreationResult::SUCCESS : UserCreationResult::INTERNAL_ERROR);
        };

        _userDao.createUser(username, hash, salt, avatarURL, createCallback);
    }

    void cls::checkUserPassword(const string& username, const string& password, function<void(bool)> callback) {

    }

    void cls::checkUserSession(const string& username, const string& sessionCookie, function<void(bool)> callback) {

    }

    void cls::createNewUserSession(const string& username, function<void(string&&)> callback) {

    }

#pragma endregion

} // service