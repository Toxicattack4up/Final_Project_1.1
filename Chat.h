#pragma once

#include "Account.h"
#include "Menu.h"
#include <thread>
#include <vector>
#include <locale>
#include <sstream>
#include <iomanip>
#include <filesystem> // Для работы с файловой системой

namespace fs = std::filesystem;

struct Message
{
    std::string sender;
    std::string receiver;
    std::string timestamp;
    std::string content;
};

class Chat
{
public:
    // Функции для работы с общим чатом
    void PrintAllMessages() const;
    void SendMessageToAll();

    // Функции для работы с личными сообщениями
    void SendMessage(const std::string& sender, const std::string& receiver);
    void ReadMessages(const std::string& user1, const std::string& user2) const;

    // Функции для отображения чатов пользователя
    void ShowUserChats(const std::string& currentUser) const;
    void UserChoice(const std::string& currentUser);
};