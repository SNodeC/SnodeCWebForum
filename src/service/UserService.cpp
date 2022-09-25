//
// Created by User on 25.09.2022.
//

#include "UserService.h"


typedef service::UserService cls;

namespace service
{
#pragma region Constants

#pragma endregion

#pragma region Constructors

    UserService::UserService(UserDao& userDao): _userDao(userDao) {}

#pragma endregion

#pragma region Static Methods

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