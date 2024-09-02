#include "Chat.h"

void Chat::Print_All_message()
{
	vector<string> messages;
	string line;

	ifstream all_message("All_message.txt");
	if (!all_message.is_open())
	{
		cerr << "Ошибка: файл не удалось открыть" << endl;
		return;
	}

	while (getline(all_message, line))
	{
		messages.push_back(line);
	}
	all_message.close();

	for (const auto& message : messages)
	{
		cout << message << endl;
	}
}

void Chat::Send_All_message()
{
	string line;

	cout << "Введите сообщение всем пользователям: ";
	cin.ignore();
	getline(cin, line);

	ofstream out_message("All_message.txt", ios::app);
	if (!out_message.is_open())
	{
		cerr << "Ошибка: не удалось открыть файл" << endl;
		return;
	}

	out_message << line << endl;
	out_message.close();
}

void Chat::User_Choice()
{
	vector<string> Users;
	ifstream name("user_info.txt", ios::in);
	if (!name.is_open())
	{
		cerr << "Ошибка: не удалось открыть файл!" << endl;
		return;
	}

	string line;
	while (getline(name, line))
	{
		Users.push_back(line);
	}
	name.close();
	if (Users.empty())
	{
		cerr << "Ошибка: список пользователей пуст." << endl;
	}

	cout << "Имена пользователей:" << endl;

	int i = 1;
	for (const auto& user : Users)
	{
		cout << i << ". " << user << endl;
		i++;
	}

	int choice;
	cout << "Выберите пользователя с кем хотите начать чат (1 - " << Users.size() << "): ";
	cin >> choice;

	if (cin.fail() || choice < 1 || choice > Users.size())
	{
		cin.clear();
		cin.ignore();
		cerr << "Ошибка: такого пользователя не существует" << endl;
		return;
	}

	string selectedUser = Users[choice - 1];
	cout << "Вы выбрали пользователя: " << selectedUser << endl;
}
