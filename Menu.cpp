#include "Menu.h"
#include <iostream>

int Menu::RunMenu()
{
    int choice;
    bool exit = false;
    do
    {
        cout << "Добро пожаловать!" << endl;
        cout << "1. Вход" << endl;
        cout << "2. Регистрация" << endl;
        cout << "3. Выход" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            system("cls");
            Account account;
            account.Entrance();
            Menu::UserMenu();
            break;
        }
        case 2:
        {
            system("cls");
            Account account;
            account.Sign_up();
            break;
        }
        case 3:
            exit = true;
            break;
        default:
            cout << "Вы сделали недопустимый выбор!" << endl;
            break;
        }
    } while (!exit);

    return 0;
}

int Menu::UserMenu()
{
    int choice = 0;
    do
    {
        cout << "Добро пожаловать!" << endl;
        cout << "Выберите что хотите сделать" << endl;
        cout << "1. Отправка сообщения конкретному пользователю" << endl;
        cout << "2. Отправка сообщения всем пользователям" << endl;
        cout << "3. Посмотреть с кем уже есть чат" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            One_message();
            break;
        case 2:
            Chat chat;
            chat.Print_All_message();
            break;
        case 3:
            break;
        default:
            break;
        }
    } while (!exit);
    return 0;
}

int Menu::One_message()
{
    cout << "Выберите какому пользователю хотите написать сообщение" << endl;
    Chat chat;
    chat.User_Choice();
    return 0;
}

int Menu::All_message()
{
    return 0;
};