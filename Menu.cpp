#include "Menu.h"
#include <iostream>

int Menu::RunMenu()
{
    int choice;
    bool exit = false;
    do
    {
        cout << "����� ����������!" << endl;
        cout << "1.����" << endl;
        cout << "2.�����������" << endl;
        cout << "3.�����" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            system("cls");
            Account account;
            account.Entrance();
            Menu::UserMenu();
            break;
        }
        case 2:
        {
            system("cls");
            Account account;
            account.Sign_up();
            break;
        }
        case 3:
            exit = true;
            break;
        default:
            cout << "������ �������� ����� ����!" << endl;
            break;
        }
    } while (!exit);

    return 0;
}

int Menu::UserMenu()
{
    int choice = 0;
    do
    {
        cout << " �� � ���� ������������" << endl;
        cout << "��������, ��� ������ ������� � ������ ����" << endl;
        cout << "1. ��������� ��������� ������ ������������" << endl;
        cout << "2. ��������� ��������� ���� �������������" << endl;
        cout << "3. ���������� ��� � �������������" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            One_message();
            break;
        case 2:
            Chat chat;
            chat.Print_All_message();
            break;
        case 3:
            break;
        default:
            break;
        }
    } while (!exit);
    return 0;
}

int Menu::One_message()
{
    cout << "�������� ���� ������ �������� �� ������ ����" << endl;
    Chat chat;
    chat.User_Choice();
    ///
    return 0;
}

int Menu::All_message()
{
    return 0;
};