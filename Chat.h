#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <locale>

using namespace std;

class Chat
{
public:
	bool running;
	void Users();
	void Read_message(string& filename);
	void Send_message(string& filename);
	void Print_All_message();
	void Send_All_message();
	void User_Choice();
};