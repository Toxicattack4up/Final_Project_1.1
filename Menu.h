#pragma once

#include "Account.h"
#include "Chat.h"
#include <iostream>

class Menu
{
public:
	int RunMenu(Account& account);
	int UserMenu(Account& account);

	int All_message();
};