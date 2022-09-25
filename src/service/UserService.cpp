#include <random>

#include "UserService.h"

typedef service::UserService cls;

namespace service
{
#pragma region Constants

    const size_t SALT_LEN = 16;

#pragma endregion

#pragma region Constructors

    UserService::UserService(UserDao& userDao): _userDao(userDao) {}

#pragma endregion

#pragma region Static Methods

ustring UserService::createRandomSalt(size_t length) {
    static std::random_device device;
    static std::mt19937 rng(device());
    static std::uniform_int_distribution<std::mt19937::result_type> distribution(0, 255);

    ustring result;
    for (size_t i = 0; i < length; ++i) {
        result += static_cast<unsigned char>(distribution(rng));
    }

    return result;
}

#pragma endregion

#pragma region Instance Methods

    void cls::createUser(const string& username, const string& password, function<void(bool)> callback) {

    }

    void cls::checkUserPassword(const string& username, const string& password, function<void(bool)> callback) {

    }

    void cls::checkUserSession(const string& username, const string& sessionCookie, function<void(bool)> callback) {

    }

    void cls::createNewUserSession(const string& username, function<void(string&&)> callback) {

    }

#pragma endregion

} // service