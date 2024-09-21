#include "Menu.h"
#include "Chat.h"
#include <iostream>
#include <string>

void Menu::ClearScreen()
{
    std::cout << std::string(50, '\n');
}

int Menu::RunMenu(Account& account)
{
    int choice;
    bool exit = false;

    do
    {
        ClearScreen();
        std::cout << "==========================" << std::endl;
        std::cout << "Добро пожаловать!" << std::endl;
        std::cout << "1. Вход" << std::endl;
        std::cout << "2. Регистрация" << std::endl;
        std::cout << "3. Выход" << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << "Меню: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            account.Authorization();
            if (!account.GetCurrentUser().empty()) {
                UserMenu(account);
            }
            break;
        case 2:
            account.Registration();
            break;
        case 3:
            exit = true;
            break;
        default:
            std::cout << "Недопустимый выбор! Попробуйте снова." << std::endl;
            break;
        }
    } while (!exit);

    return 0;
}

int Menu::UserMenu(Account& account)
{
    int choice = 0;
    bool exit = false;
    Chat chat;

    std::string currentUser = account.GetCurrentUser();
    ClearScreen();
    do
    {
        std::cout << "==========================" << std::endl;
        std::cout << "Меню пользователя:" << std::endl;
        std::cout << "1. Отправка сообщения пользователю" << std::endl;
        std::cout << "2. Сообщения для всех пользователей" << std::endl;
        std::cout << "3. Посмотреть свои чаты" << std::endl;
        std::cout << "4. Выход" << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            chat.UserChoice(currentUser);
            break;
        case 2:
            ShowAllMessages();
            break;
        case 3:
            chat.ShowUserChats(currentUser);
            continue;
        case 4:
            exit = true;
            break;
        default:
            std::cout << "Недопустимый выбор! Попробуйте снова." << std::endl;
            break;
        }
    } while (!exit);

    return 0;
}

int Menu::ShowAllMessages()
{
    int choice = 0;
    bool exit = false;
    Chat chat;

    do
    {
        std::cout << "==========================" << std::endl;
        std::cout << "Общий чат:" << std::endl;
        chat.PrintAllMessages();
        std::cout << "==========================" << std::endl;
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Написать всем сообщение" << std::endl;
        std::cout << "2. Вернуться в предыдущее меню" << std::endl;
        std::cout << "3. Выход из приложения" << std::endl;
        std::cout << "Ваш выбор: "; std::cin >> choice;

        switch (choice)
        {
        case 1:
            chat.SendMessageToAll();
            break;
        case 2:
            ClearScreen();
            return 0;
        case 3:
            exit = true;
            break;
        default:
            std::cout << "Недопустимый выбор! Попробуйте снова." << std::endl;
            break;
        }
    } while (!exit);

    return 0;
}