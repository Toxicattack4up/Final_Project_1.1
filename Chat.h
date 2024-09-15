#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <locale>
#include <sstream>
#include <iomanip>
#include <filesystem> // Для работы с файловой системой


using namespace std; 
namespace fs = std::filesystem;

struct MyStruct
{
	string sender;
	string receiver;
	string time;
	string text;
};

class Chat
{
public:
	void Print_All_message();
	void Send_All_message();

	void Send_message(const string& sender, const string& reveicer);
	void Read_message(const string& user1, const string& user2);

	void ShowUserChats(const string& current_user);
	void User_Choice(const string& current_user);
};