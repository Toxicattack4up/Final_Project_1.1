#include "Menu.h"
#include <iostream>
#include <cstdlib>  // Для использования system("cls")

using namespace std;

// Главное меню
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
        cout << "Меню: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            system("cls");
            Account account;
            account.Authorization();
            system("cls");
            Menu::UserMenu();
            break;
        }
        case 2:
        {
            system("cls");
            Account account;
            account.Registration();
            system("cls");
            break;
        }
        case 3:
            exit = true;
            break;
        default:
            cout << "Недопустимый выбор!" << endl;
            break;
        }
    } while (!exit);

    return 0;
}

// Меню пользователя
int Menu::UserMenu()
{
    int choice = 0;
    bool exit = false;
    Chat chat;  // Создаем объект чата для взаимодействия

    do
    {
        cout << "Меню пользователя:" << endl;
        cout << "1. Отправка сообщения конкретному пользователю" << endl;
        cout << "2. Сообщения для всех пользователей" << endl;
        cout << "3. Посмотреть свои чаты" << endl;
        cout << "4. Выход" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls");
            chat.User_Choice();  // Выбор пользователя для отправки сообщения
            break;
        case 2:
            system("cls");
            Menu::All_message();  // Вызов меню для общего чата
            break;
        case 3:
            system("cls");
            chat.ShowUserChats();  // Показать историю чатов
            break;
        case 4:
            exit = true;
            break;
        default:
            cout << "Недопустимый выбор!" << endl;
            break;
        }
    } while (!exit);

    return 0;
}

// Меню для общего чата
int Menu::All_message()
{
    int choice = 0;
    bool exit = false;
    Chat chat;  // Используем объект чата для взаимодействия

    do
    {
        cout << "Общий чат:" << endl;
        chat.Print_All_message();  // Печатаем все сообщения общего чата
        cout << "Меню:" << endl;
        cout << "1. Написать всем сообщение" << endl;
        cout << "2. Вернуться в предыдущее меню" << endl;
        cout << "3. Выход из приложения" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls");
            chat.Send_All_message();  // Отправить сообщение в общий чат
            break;
        case 2:
            system("cls");
            return 0;  // Вернуться в предыдущее меню (меню пользователя)
        case 3:
            exit = true;
            break;
        default:
            cout << "Недопустимый выбор!" << endl;
            break;
        }
    } while (!exit);

    return 0;
}
