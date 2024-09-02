#include "Account.h"


void Account::LoadCredentials()
{
    ifstream cred_file("credentials.txt");

    if (!cred_file.is_open())
    {
        cerr << "Ошибка: не удалось открыть файл для чтения" << endl;
        return;
    }

    string login, password;
    while (cred_file >> login >> password)
    {
        User user;
        user.password = password;
        credentials[login] = user;
    }

    cred_file.close();
}

void Account::LoadUserInfo()
{
    ifstream user_info_file("user_info.txt");

    if (!user_info_file.is_open())
    {
        cerr << "Ошибка: не удалось открыть файл для чтения" << endl;
        return;
    }

    string login, nickname, name;
    while (user_info_file >> login >> nickname >> name)
    {
        if (credentials.find(login) != credentials.end())
        {
            credentials[login].nickname = nickname;
            credentials[login].name = name;
        }
    }

    user_info_file.close();
}


void Account::SaveCredentials()
{
    ofstream cred_file("credentials.txt");

    if (!cred_file.is_open())
    {
        cerr << "Ошибка: не удалось открыть файл для записи!" << endl;
        return;
    }

    for (const auto& pair : credentials)
    {
        cred_file << pair.first << " " << pair.second.password << endl;
    }
}

void Account::SaveUserInfo(const string& login, const string& nickname, const string& name)
{
    ofstream user_info_file("user_info.txt", ios::app);

    if (!user_info_file.is_open())
    {
        cerr << "Ошибка: не удалось открыть файл для записи" << endl;
        return;
    }

    user_info_file << login << " " << nickname << " " << name << endl;

    user_info_file.close();
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

    string login, password, nickname, name;
    bool validInput = false;

    // Цикл для ввода логина
    while (!validInput)
    {
        cout << "Введите ваш логин: "; cin >> login;

        if (login.empty() || login.find(' ') != string::npos)
        {
            cerr << "Логин не должен быть пустым или содержать пробелы!" << endl;
        }
        else if (credentials.find(login) != credentials.end())
        {
            cerr << "Такой логин занят, введите другой!" << endl;
        }
        else
        {
            validInput = true;  // Точка выхода
        }
    }

    validInput = false;
    // Цикл для ввода пароля
    while (!validInput)
    {
        cout << "Введите пароль: "; cin >> password;

        if (password.length() < 8)
        {
            cerr << "Пароль должен содержать как минимум 8 символов!" << endl;
        }
        else
        {
            validInput = true;  // Точка выхода
        }
    }
    validInput = false; // Обнуление

    // Цикл для ввода ника
    while (!validInput)
    {
        cout << "Введите ваш ник: " << endl; cin >> nickname;

        if (nickname.empty() || nickname.find(' ') != string::npos)
        {
            cerr << "Ник не должен быть пустым или содержать пробелы!" << endl;
            return;
        }
        else if (credentials.find(nickname) != credentials.end())
        {
            cout << "Такой ник уже занят, введите другой!" << endl;
        }
        else
        {
            validInput = true;  // Точка выхода
        }
    }
    validInput = false;
    // Цикл для ввода имени
    while (!validInput)
    {
        cout << "Введите ваше имя: ";
        cin >> name;

        if (name.empty() || name.find(' ') != string::npos)
        {
            cerr << "Имя не должно быть пустым или содержать пробелы!" << endl;
        }
        else
        {
            validInput = true;   // Точка выхода
        }
    }

    User user;
    user.name = name;
    user.password = password;

    credentials[login] = user;

    try
    {
        SaveCredentials();
        SaveUserInfo(login, nickname, name);
    }
    catch (const exception& e)
    {
        cerr << "Ошибка сохранения данных: " << e.what() << endl;
        return;
    }

    cout << "Вы успешно зарегистрированы!" << endl;
}