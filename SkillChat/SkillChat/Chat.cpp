#include "Chat.h"
#include <iostream>

void Chat::ShowCommon(const std::vector<Message>& message) // функция вывода сообщений из общего чата
{
	const auto size = message.size(); // задаем размер массива
	for (size_t i = 0; i < size; i++)
	{
		if (message[i].GetBool() == false)
		{
			message[i].ShowMessage();
		}
		else if (i + 1 == size)
		{
			cout << "Сообщений нет" << endl;
		}
	}
}

void Chat::ShowPrivate(const string& senderLogin, const string& recieverLogin, const std::vector<Message>& message) // функция вывода приватных сообщений
{
	const auto size = message.size();
	for (size_t i = 0; i < size; i++)
	{
		if (message[i].GetBool() == true) // проверка того, что сообщение личное
		{
			if (senderLogin == message[i].GetSenderName() && recieverLogin == message[i].GetRecieverName()) // вывод если в сообщении входят оба пользователя
			{
				message[i].ShowMessage();
			}
			else if (senderLogin == message[i].GetRecieverName() && recieverLogin == message[i].GetSenderName()) // вывод если исходящее от второго пользователя
			{
				message[i].ShowMessage();
			}
		}
		else if (i + 1 == size)
		{
			cout << "Cообщений нет" << endl;
		}
	}
}

void Chat::ShowAvailableChats(const vector<User>& users, const User& user) // вывод доступных чатов
{
	cout << "common, ";
	for (auto i = users.begin(); i < users.end(); i++)
	{
		if (!((i + 2) >= users.end()))
		{
			if (!(i->getLogin() == user.getLogin()))
			{
				cout << i->getLogin() << ", ";
			}
			else continue;
		}
		else if ((i + 1)->getLogin() == user.getLogin())
		{
			cout << i->getLogin();
			break;
		}
	}
}