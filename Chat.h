#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <filesystem>  // Для работы с файловой системой


// проверка русского языка, если мы будем писать на for linux
namespace fs = std::filesystem;

struct MyStruct
{
    std::string sender;
    std::string receiver;
    std::string time;
    std::string text;
};

class Chat
{
public:
    void Print_All_message();
    void Send_All_message();

    void Send_message(const std::string& fromUser, const std::string& toUser);
    void Read_message(const std::string& user1, const std::string& user2);

    void ShowUserChats(const std::string& current_user);
    void User_Choice(const std::string& current_user);
};