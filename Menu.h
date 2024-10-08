#pragma once
#include "Account.h"

// Класс для управления меню пользователя
class Menu
{
public:
    // Метод для очистки экрана и чтобы был красивый вывод
    void ClearScreen();
    // Метод для запуска основного меню
    // Возвращает код завершения программы
    int RunMenu(Account& account);

    // Меню для авторизованного пользователя
    // Возвращает код завершения программы
    int UserMenu(Account& account);

    // Метод для отображения всех сообщений
    // Возвращает код завершения программы
    int ShowAllMessages();
};