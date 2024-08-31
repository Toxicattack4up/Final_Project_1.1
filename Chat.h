#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

class Chat
{
public:
	bool running;
	void Users();
	void Read_message(string& filename);
	void Send_message(string& filename);
	void User_Choice();
};