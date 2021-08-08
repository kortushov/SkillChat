#pragma once
#include "Message.h"
#include "User.h"
#include <vector>
#include <string>

using namespace std;

class Chat
{
public:
	void ShowCommon(const std::vector<Message>& message); // вывод сообщений из общего чата
	void ShowPrivate(const string& senderName, const string& recieverName, const std::vector<Message>& message); // вывод приватных сообщений
	void ShowAvailableChats(const vector<User>& users, const User& user); // вывод доступных чатов
};