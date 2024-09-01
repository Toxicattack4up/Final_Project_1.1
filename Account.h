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
    void SaveCredentials();

public:
    void Entrance();
    void Sign_up();
};