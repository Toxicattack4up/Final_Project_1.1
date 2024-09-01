#include "Chat.h"

void Chat::Users()
{
	ifstream name("Name.txt");
	if (!name.is_open())
	{
		cerr << "Ошибка: не удалось открыть файл в функ Users";
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
	/*while (running)
	{
		ifstream infile(filename);
		if (infile.is_open())
		{
			string massege;
			while (getline(infile, massege))
			{
				cout << "������� ���������: " << massege << endl;
			}
			infile.close();
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}*/
}

void Chat::Send_message(std::string& filename)
{
	/*while (running)
	{
		string massage;
		getline(cin, massage);
		ofstream outfile(filename, ios_base::app);
		if (outfile.is_open())
		{
			outfile << massage << endl;
			outfile.close();
		}
	}*/
}

void Chat::Print_All_message()
{
	vector<string> messages;
	string line;

	ifstream all_message("All_message.txt");
	if (!all_message.is_open())
	{
		cerr << "Ошибка: файл не удалось открыть";
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

	cout << "Введите сообщение всем пользователям: ";
	cin.ignore();
	getline(cin, line);

	messages.push_back(line);

	ofstream out_message("All_message.txt", ios::app);
	if (!out_message.is_open())
	{
		cerr << "Ошибка: не удалось открыть файл" << endl;
		return;
	}

	out_message << line << endl;
	out_message.close();

	for (const auto& message : messages)
	{
		cout << message << endl;
	}
}

void Chat::Send_All_message()
{

}

void Chat::User_Choice()
{
	vector<string> Users;
	ifstream name("Name.txt", ios::in);
	if (!name.is_open())
	{
		cerr << "Ошибка: не удалось открыть файл User_Choice" << endl;
		return;
	}

	string line;
	while (getline(name, line))
	{
		Users.push_back(line);
	}
	name.close();

	cout << "Имена пользователей:" << endl;

	int i = 1;
	for (const auto& user : Users)
	{
		cout << i << ". " << user << endl;
		i++;
	}

	int choice;
	cout << "Выберите имя пользователя: ";
	cin >> choice;
	if (choice < 1 || choice > Users.size())
	{
		cerr << "Ошибка: такого пользователя не существует" << endl;
		return;
	}

	string selectedUser = Users[choice - 1];
	cout << "Имя пользователя, которого вы выбрали: " << selectedUser << endl;
}
