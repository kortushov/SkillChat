#include "Chat.h"
#include <iostream>

void Chat::ShowCommon(const std::vector<Message>& message) //����� ��������� �� ������ ����
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
			cout << "��� ���������" << endl;
		}
	}
}

void Chat::ShowPrivate(const string& senderLogin, const string& recieverLogin, const std::vector<Message>& message) //����� ������ ���������
{
	const auto size = message.size();
	for (size_t c = 0; c < size; c++)
	{
		if (message[c].GetBool() == true) //�������� ����, ��� ��������� ������
		{
			if (senderLogin == message[c].GetSenderName() && recieverLogin == message[c].GetRecieverName()) // ����� ���� �������� ��������� ��� ������������
			{
				message[c].ShowMessage();
			}
			else if (senderLogin == message[c].GetRecieverName() && recieverLogin == message[c].GetSenderName()) // ����� ���� ��������� �� ������������
			{
				message[c].ShowMessage();
			}
		}
		else if (c + 1 == size)
		{
			cout << "��� ���������" << endl;
		}
	}
}

void Chat::ShowAvailableChats(const vector<User>& users, const User& user) // ����� ��������� �����
{
	cout << "common" << endl;
	for (const auto& u : users)
	{
		if (u.getLogin() == user.getLogin())
		{
			continue; // ������� �������� ������������
		}
		else
		{
			u.DisplayUserLogin(); // ����� ���� �������������
		}
	}
}
