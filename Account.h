#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

struct User
{
    string name;
    string password;
};

class Account
{
private:
    unordered_map<string, User> credentials;
    void LoadCredentials();
    void LoadUserInfo();
    void SaveCredentials();
    void SaveUserInfo(const string& login, const string& nickname, const string& name);

public:
    void Authorization();
    void Registration();
};