#include "Account.h"


void Account::LoadCredentials()
{
    ifstream log("login.txt");
    ifstream pass("password.txt");
    ifstream name("Name.txt");

    if (!log.is_open() || !pass.is_open() || !name.is_open())
    {
        cerr << "Ошибка: не удалось открыть один из файлов!" << endl;
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

void Account::SaveCredentials()
{
    ofstream log("login.txt");
    ofstream pass("password.txt");
    ofstream name("Name.txt");

    if (!log.is_open() || !pass.is_open() || !name.is_open())
    {
        cerr << "Ошибка: не удалось открыть один из файлов!" << endl;
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

void Account::Authorization()
{
    LoadCredentials();

    string login_correct, pass_correct;
    bool validInput = false;

    while (!validInput)
    {
        cout << "Введите логин: ";
        cin >> login_correct;

        if (login_correct.empty())
        {
            cerr << "Логин не должен быть пустым!" << endl;
        }
        else if (credentials.find(login_correct) == credentials.end())
        {
            cerr << "Логин не найден! Попробуйте снова." << endl;
        }
        else
        {
            validInput = true; // Логин прошел все проверки, выход из цикла
        }
    }

    validInput = false;
    auto it = credentials.find(login_correct);

    if (it != credentials.end())
    {
        while (!validInput)
        {
            cout << "Введите пароль: ";
            cin >> pass_correct;

            if (pass_correct.empty())
            {
                cerr << "Пароль не должен быть пустым!" << endl;
                continue; // Возвращаемся в начало цикла
            }

            // Проверка пароля (предполагается, что используется хеширование)
            if (it->second.password == pass_correct) // Здесь заменить на сравнение хешей
            {
                cout << "Вы успешно авторизовались!" << endl;
                validInput = true; // Устанавливаем флаг, чтобы выйти из цикла
            }
            else
            {
                cerr << "Неправильный пароль! Попробуйте снова." << endl;
            }
        }
    }
    else
    {
        cerr << "Логин не найден!" << endl;
    }
}

void Account::Registration()
{
    LoadCredentials();

    string log_checker, pass_checker, name_checker;
    bool validInput = false;

    // Цикл для ввода логина
    while (!validInput)
    {
        cout << "Введите ваш логин: "; cin >> log_checker;

        if (log_checker.empty() || log_checker.find(' ') != string::npos)
        {
            cerr << "Логин не должен быть пустым или содержать пробелы!" << endl;
        }
        else if (credentials.find(log_checker) != credentials.end())
        {
            cerr << "Такой логин занят, введите другой!" << endl;
        }
        else
        {
            validInput = true;  // Логин прошел все проверки
        }
    }

    validInput = false;

    // Цикл для ввода пароля
    while (!validInput)
    {
        cout << "Введите пароль: ";
        // Вместо cin можно использовать безопасный ввод пароля
        cin >> pass_checker;

        if (pass_checker.length() < 8)
        {
            cerr << "Пароль должен содержать как минимум 8 символов!" << endl;
        }
        else
        {
            validInput = true;  // Пароль прошел все проверки
        }
    }

    // Цикл для ввода имени
    validInput = false;
    while (!validInput)
    {
        cout << "Введите ваше имя: ";
        cin >> name_checker;

        if (name_checker.empty())
        {
            cerr << "Имя не должно быть пустым!" << endl;
        }
        else
        {
            validInput = true;  // Имя прошло все проверки
        }
    }

    User user;
    user.name = name_checker;
    user.password = pass_checker;

    credentials[log_checker] = user;

    try
    {
        SaveCredentials();
    }
    catch (const exception& e)
    {
        cerr << "Ошибка сохранения данных: " << e.what() << endl;
        return;
    }

    cout << "Вы успешно зарегистрированы!" << endl;
}