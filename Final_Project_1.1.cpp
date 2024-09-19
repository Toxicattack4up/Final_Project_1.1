#include "Menu.h"
#include "Account.h"
#include "Chat.h"
#include <iostream>
#include <Windows.h>

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    Account account;  // Создаем объект Account
    Menu menu;

    menu.RunMenu(account);  // Передаем объект Account в меню
}
