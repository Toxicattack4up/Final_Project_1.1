#include "Account.h"


void Account::LoadCredentials()
{
    ifstream log("login.txt");
    ifstream pass("password.txt");
    ifstream name("Name.txt");

    if (!log.is_open() || !pass.is_open() || !name.is_open())
    {
        cerr << "Какая-то ошибка!" << endl;
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
        cerr << "Какая-то ошибка!" << endl;
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

void Account::Entrance()
{
    LoadCredentials();

    string login_correct, pass_correct;
    cout << "Введите логин: "; cin >> login_correct; 
    cout << "Введите пароль: "; cin >> pass_correct;

    if (credentials.find(login_correct) != credentials.end() && credentials[login_correct].password == pass_correct)
    {
        cout << "Вы успешно авторизовались!" << endl;
    }
    else
    {
        cerr << "Какая-то ошибка!" << endl;
    }
}

void Account::Sign_up()
{
    LoadCredentials();

    string log_cheker, pass_cheker, name_cheker;
    cout << "Введите ваш логин: "; cin >> log_cheker;
    if (credentials.find(log_cheker) != credentials.end())
    {
        cerr << "Такой логин занят введите другой!" << endl;
        return;
    }
    cout << "Введите пароль: "; cin >> pass_cheker;
    cout << "Введите ваше имя: "; cin >> name_cheker;

    User user;
    user.name = name_cheker;
    user.password = pass_cheker;
    credentials[log_cheker] = user;
    SaveCredentials();
    cout << "Вы успешно зарегистрированы!" << endl;
}