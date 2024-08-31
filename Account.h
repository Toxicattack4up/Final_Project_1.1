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
    unordered_map<string, User> credentials;  // Хеш-таблица для хранения логинов и паролей
    void LoadCredentials();                     // Загрузка данных из файлов в хеш-таблицу
    void SaveCredentials();                     // Сохранение данных из хеш-таблицы в файлы

public:
    void Entrance();                            // Вход пользователя
    void Sign_up();                             // Регистрация пользователя
};