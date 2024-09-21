#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <stdexcept>  // Для обработки исключений

// Структура для представления пользователя
struct User {
    std::string name;
    std::string password;
    std::string nickname;
};

class Account {
private:
    std::unordered_map<std::string, User> credentials;  // Мапа для хранения учетных данных пользователей
    std::string current_user;  // Текущий авторизованный пользователь

    // Загрузка учетных данных пользователей из файла
    void LoadCredentials();

    // Загрузка дополнительной информации о пользователях
    void LoadUserInfo();

    // Сохранение учетных данных в файл
    void SaveCredentials() const;

    // Сохранение информации о пользователе в файл
    void SaveUserInfo(const std::string& nickname, const std::string& name) const;

public:
    // Авторизация пользователя
    void Authorization();

    // Регистрация нового пользователя
    void Registration();

    // Получение текущего авторизованного пользователя
    std::string GetCurrentUser() const;
};
