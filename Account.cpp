#include "Account.h"


// Функция для загрузки данных из файлов в хеш-таблицу
void Account::LoadCredentials()
{
    ifstream log("login.txt");
    ifstream pass("password.txt");
    ifstream name("Name.txt");

    if (!log.is_open() || !pass.is_open() || !name.is_open())
    {
        cerr << "Ошибка при открытии файлов!" << endl;
        return;
    }

    string login, password, username;
    while (log >> login && pass >> password && name >> username)
    {
        User user;
        user.name = username;
        user.password = password;
        credentials[login] = user;
    }

    log.close();
    pass.close();
    name.close();
}

// Функция для сохранения данных из хеш-таблицы в файлы
void Account::SaveCredentials()
{
    ofstream log("login.txt");
    ofstream pass("password.txt");
    ofstream name("Name.txt");

    if (!log.is_open() || !pass.is_open() || !name.is_open())
    {
        cerr << "Ошибка при открытии файлов!" << endl;
        return;
    }

    for (const auto& pair : credentials)
    {
        log << pair.first << endl;
        pass << pair.second.password << endl;
        name << pair.second.name << endl;
    }

    log.close();
    pass.close();
    name.close();
}

// Вход пользователя
void Account::Entrance()
{
    LoadCredentials();  // Загрузка логинов и паролей из файлов в хеш-таблицу

    string login_correct, pass_correct, name_correct;
    cout << "Введите свой логин: "; cin >> login_correct;
    cout << "Введите свой пароль: "; cin >> pass_correct;

    // Проверка логина и пароля в хеш-таблице
    if (credentials.find(login_correct) != credentials.end() && credentials[login_correct].password == pass_correct)
    {
        cout << "Данные введены верно!" << endl;
    }
    else
    {
        cerr << "Пароль или логин введен неправильно!" << endl;
    }
}

// Регистрация пользователя
void Account::Sign_up()
{
    LoadCredentials();  // Загрузка логинов и паролей из файлов в хеш-таблицу

    string log_cheker, pass_cheker, name_cheker;
    cout << "Введите своё имя: "; cin >> name_cheker;
    cout << "Введите свой логин: "; cin >> log_cheker;
    cout << "Введите свой пароль: "; cin >> pass_cheker;

    // Проверка, существует ли логин уже
    if (credentials.find(log_cheker) != credentials.end())
    {
        cerr << "Такой логин уже существует!" << endl;
    }
    else
    {
        User user;
        user.name = name_cheker;
        user.password = pass_cheker;
        // Добавление нового пользователя в хеш-таблицу и сохранение изменений в файлы
        credentials[log_cheker] = user;
        SaveCredentials();
        cout << "Регистрация прошла успешно!" << endl;
    }
}