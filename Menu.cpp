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
            account.Authorization();
            Menu::UserMenu();
            break;
        }
        case 2:
        {
            system("cls");
            Account account;
            account.Registration();
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
    bool exit = false;
    do
    {
        cout << " " << endl;
        cout << "Выберите что хотите сделать" << endl;
        cout << "1. Отправка сообщения конкретному пользователю" << endl;
        cout << "2. Сообщения для всех пользователей" << endl;
        cout << "3. Посмотреть свои чаты" << endl;
        cout << "4. Выход" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Выберите какому пользователю хотите написать сообщение" << endl;
            Chat chat;
            chat.User_Choice();
            break;
        case 2:
            All_message();
            break;
        case 3:

            break;
        case 4:
            exit = true;
            break;
        default:
            cout << "Вы сделали недопустимый выбор!" << endl;
            continue;
            break;
        }
    } while (!exit);
    return 0;
}

int Menu::All_message()
{
    int choice = 0;
    bool exit = false;
    do
    {
        cout << " " << endl;
        cout << "Сообщения из общего чата" << endl;
        Chat chat;
        chat.Print_All_message();

        cout << "Выберите что нужно сделать: " << endl;
        cout << "1. Написать всем сообщение" << endl;
        cout << "2. Вернуться в предыдущее меню" << endl;
        cout << "3. Выход из приложения" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            chat.Send_All_message();
            break;
        case 2:
            UserMenu();
        case 3:
            exit = true;
            break;
        default:
            cout << "Вы сделали недопустимый выбор!" << endl;
            continue;
            break;
        }
    } while (!exit);
    
    return 0;
};