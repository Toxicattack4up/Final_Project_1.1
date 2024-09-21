#include "Account.h"

// Загрузка учетных данных пользователей из файла
void Account::LoadCredentials() {
    std::ifstream cred_file("credentials.txt");

    if (!cred_file.is_open()) {
        throw std::runtime_error("Ошибка: не удалось открыть файл credentials.txt для чтения.");
    }

    std::string login, password;
    while (cred_file >> login >> password) {
        User user;
        user.password = password;
        credentials[login] = user;
    }
}

// Загрузка дополнительной информации о пользователях
void Account::LoadUserInfo() {
    std::ifstream user_info_file("user_info.txt");

    if (!user_info_file.is_open()) {
        throw std::runtime_error("Ошибка: не удалось открыть файл user_info.txt для чтения.");
    }

    std::string login, nickname, name;
    while (user_info_file >> login >> nickname >> name) {
        auto it = credentials.find(login);
        if (it != credentials.end()) {
            it->second.nickname = nickname;
            it->second.name = name;
        }
    }
}

// Сохранение учетных данных в файл
void Account::SaveCredentials() const {
    std::ofstream cred_file("credentials.txt");

    if (!cred_file.is_open()) {
        throw std::runtime_error("Ошибка: не удалось открыть файл credentials.txt для записи.");
    }

    for (const auto& pair : credentials) {
        cred_file << pair.first << " " << pair.second.password << std::endl;
    }
}

// Сохранение информации о пользователе в файл
void Account::SaveUserInfo(const std::string& nickname, const std::string& name) const {
    std::ofstream user_info_file("user_info.txt", std::ios::app);

    if (!user_info_file.is_open()) {
        throw std::runtime_error("Ошибка: не удалось открыть файл user_info.txt для записи.");
    }

    user_info_file << nickname << " " << name << std::endl;
}

// Авторизация пользователя
void Account::Authorization() {
    LoadCredentials();

    std::string login, password;
    bool validInput = false;

    while (!validInput) {
        std::cout << "Введите логин: "; std::cin >> login;

        if (login.empty()) {
            std::cerr << "Логин не должен быть пустым!" << std::endl;
        }
        else if (credentials.find(login) == credentials.end()) {
            std::cerr << "Логин не найден! Попробуйте снова." << std::endl;
        }
        else {
            validInput = true;
        }
    }

    auto it = credentials.find(login);

    validInput = false;

    while (!validInput) {
        std::cout << "Введите пароль: "; std::cin >> password;

        if (password.empty()) {
            std::cerr << "Пароль не должен быть пустым!" << std::endl;
        }
        else if (it->second.password == password) {
            std::cout << "Вы успешно авторизовались!" << std::endl;
            current_user = login;  // Устанавливаем текущего пользователя
            validInput = true;
        }
        else {
            std::cerr << "Неправильный пароль! Попробуйте снова." << std::endl;
        }
    }
}

// Регистрация нового пользователя
void Account::Registration() {
    LoadCredentials();

    std::string login, password, nickname, name;
    bool validInput = false;

    // Ввод логина
    while (!validInput) {
        std::cout << "Введите логин: "; std::cin >> login;

        if (login.empty() || login.find(' ') != std::string::npos) {
            std::cerr << "Логин не должен быть пустым или содержать пробелы!" << std::endl;
        }
        else if (credentials.find(login) != credentials.end()) {
            std::cerr << "Такой логин уже существует, попробуйте другой!" << std::endl;
        }
        else {
            validInput = true;
        }
    }

    validInput = false;
    // Ввод пароля
    while (!validInput) {
        std::cout << "Введите пароль: "; std::cin >> password;

        if (password.length() < 8) {
            std::cerr << "Пароль должен содержать как минимум 8 символов!" << std::endl;
        }
        else {
            validInput = true;
        }
    }

    validInput = false;
    // Ввод ника
    while (!validInput) {
        std::cout << "Введите ник: "; std::cin >> nickname;

        if (nickname.empty() || nickname.find(' ') != std::string::npos) {
            std::cerr << "Ник не должен быть пустым или содержать пробелы!" << std::endl;
        }
        else {
            validInput = true;
        }
    }

    validInput = false;
    // Ввод имени
    while (!validInput) {
        std::cout << "Введите имя: "; std::cin >> name;

        if (name.empty() || name.find(' ') != std::string::npos) {
            std::cerr << "Имя не должно быть пустым или содержать пробелы!" << std::endl;
        }
        else {
            validInput = true;
        }
    }

    // Сохраняем данные пользователя
    User user{ name, password, nickname };
    credentials[login] = user;

    try {
        SaveCredentials();
        SaveUserInfo(nickname, name);
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка сохранения данных: " << e.what() << std::endl;
    }

    std::cout << "Регистрация успешна!" << std::endl;
}

// Получение текущего пользователя
std::string Account::GetCurrentUser() const {
    return current_user;
}