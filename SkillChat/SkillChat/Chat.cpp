#include "Chat.h"
#include <iostream>

void Chat::ShowCommon(const std::vector<Message>& message) //вывод сообщений из общего чата
{
	const auto size = message.size();
	for (size_t c = 0; c < size; c++)
	{
		if (message[c].GetBool() == false)
		{
			message[c].ShowMessage();
		}
		else if (c + 1 == size)
		{
			cout << "Нет сообщений" << endl;
		}
	}
}

void Chat::ShowPrivate(const string& senderLogin, const string& recieverLogin, const std::vector<Message>& message) //вывод личных сообщений
{
	const auto size = message.size();
	for (size_t c = 0; c < size; c++)
	{
		if (message[c].GetBool() == true) //проверка того, что сообщение личное
		{
			if (senderLogin == message[c].GetSenderName() && recieverLogin == message[c].GetRecieverName()) // вывод если входящее сообщение для пользователя
			{
				message[c].ShowMessage();
			}
			else if (senderLogin == message[c].GetRecieverName() && recieverLogin == message[c].GetSenderName()) // вывод если исходящее от пользователя
			{
				message[c].ShowMessage();
			}
		}
		else if (c + 1 == size)
		{
			cout << "Нет сообщений" << endl;
		}
	}
}

void Chat::ShowAvailableChats(const vector<User>& users, const User& user) // вывод доступных чатов
{
	cout << "common" << endl;
	for (const auto& u : users)
	{
		if (u.getLogin() == user.getLogin())
		{
			continue; // пропуск текущего пользователя
		}
		else
		{
			u.DisplayUserLogin(); // вывод всех пользователей
		}
	}
}
