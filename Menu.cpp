#include "Menu.h"
#include <iostream>
#include <cstdlib>  // Для использования system("cls")
#include <string>   // Для работы с std::string

using namespace std;

// Главное меню
int Menu::RunMenu(Account& account)
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
            account.Authorization();  // Авторизация пользователя
            system("cls");
            Menu menu;
            menu.UserMenu(account);  // Нестатический вызов через объект
            break;
        }
        case 2:
        {
            system("cls");
            account.Registration();  // Используем тот же объект account
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
int Menu::UserMenu(Account& account)
{
    int choice = 0;
    bool exit = false;
    Chat chat;  // Создаем объект чата для взаимодействия

    string current_user = account.GetCurrentUser();  // Получаем текущего пользователя после авторизации

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
            chat.User_Choice(current_user); // Передаем текущего пользователя
            break;
        case 2:
            system("cls");
            All_message();  // Нестатический вызов через объект
            break;
        case 3:
            system("cls");
            chat.ShowUserChats(current_user);  // Показать историю чатов с текущим пользователем
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