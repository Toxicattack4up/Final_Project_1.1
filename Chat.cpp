#include "Chat.h"

void Chat::Users()
{
	ifstream name("Name.txt");
	if (!name.is_open())
	{
		cerr << "Ошибка: файл не удалось открыть в Users";
		return;
	}

	string All_names;
	while (getline(name, All_names))
	{
		cout << All_names << endl;
	}
}

void Chat::Read_message(string& filename)
{
	while (running)
	{
		ifstream infile(filename);
		if (infile.is_open())
		{
			string massege;
			while (getline(infile, massege))
			{
				cout << "Введите сообщение: " << massege << endl;
			}
			infile.close();
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void Chat::Send_message(std::string& filename)
{
	while (running)
	{
		string massage;
		getline(cin, massage);
		ofstream outfile(filename, ios_base::app);
		if (outfile.is_open())
		{
			outfile << massage << endl;
			outfile.close();
		}
	}
}

void Chat::User_Choice()
{
	vector<string> Users;
	ifstream name("Name.txt", ios::in);
	if (!name.is_open())
	{
		cerr << "Ошибка: не удалось открыть файл в User_Choice" << endl;
		return;
	}

	string line;
	while (getline(name, line))
	{
		Users.push_back(line);
	}
	name.close();

	cout << "Список пользователей:" << endl;

	int i = 1;
	for (const auto& user : Users)
	{
		cout << i << ". " << user << endl;
		i++;
	}

	int choice;
	cout << "Введите имя пользователя: ";
	cin >> choice;
	if (choice < 1 || choice > Users.size())
	{
		cerr << "Ошибка: неверное имя пользователя" << endl;
		return;
	}

	string selectedUser = Users[choice - 1];
	cout << "Вы выбрали пользователя: " << selectedUser << endl;
}
