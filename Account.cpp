#include "Account.h"


// ������� ��� �������� ������ �� ������ � ���-�������
void Account::LoadCredentials()
{
    ifstream log("login.txt");
    ifstream pass("password.txt");
    ifstream name("Name.txt");

    if (!log.is_open() || !pass.is_open() || !name.is_open())
    {
        cerr << "������ ��� �������� ������!" << endl;
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

// ������� ��� ���������� ������ �� ���-������� � �����
void Account::SaveCredentials()
{
    ofstream log("login.txt");
    ofstream pass("password.txt");
    ofstream name("Name.txt");

    if (!log.is_open() || !pass.is_open() || !name.is_open())
    {
        cerr << "������ ��� �������� ������!" << endl;
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

// ���� ������������
void Account::Entrance()
{
    LoadCredentials();  // �������� ������� � ������� �� ������ � ���-�������

    string login_correct, pass_correct, name_correct;
    cout << "������� ���� �����: "; cin >> login_correct;
    cout << "������� ���� ������: "; cin >> pass_correct;

    // �������� ������ � ������ � ���-�������
    if (credentials.find(login_correct) != credentials.end() && credentials[login_correct].password == pass_correct)
    {
        cout << "������ ������� �����!" << endl;
    }
    else
    {
        cerr << "������ ��� ����� ������ �����������!" << endl;
    }
}

// ����������� ������������
void Account::Sign_up()
{
    LoadCredentials();  // �������� ������� � ������� �� ������ � ���-�������

    string log_cheker, pass_cheker, name_cheker;
    cout << "������� ��� ���: "; cin >> name_cheker;
    cout << "������� ���� �����: "; cin >> log_cheker;
    cout << "������� ���� ������: "; cin >> pass_cheker;

    // ��������, ���������� �� ����� ���
    if (credentials.find(log_cheker) != credentials.end())
    {
        cerr << "����� ����� ��� ����������!" << endl;
    }
    else
    {
        User user;
        user.name = name_cheker;
        user.password = pass_cheker;
        // ���������� ������ ������������ � ���-������� � ���������� ��������� � �����
        credentials[log_cheker] = user;
        SaveCredentials();
        cout << "����������� ������ �������!" << endl;
    }
}