#pragma once
#include "Message.h"
#include "User.h"
#include <vector>
#include <string>

using namespace std;

class Chat
{
public:
	void ShowCommon(const std::vector<Message>& message); // ����� ��������� �� ������ ����
	void ShowPrivate(const string& senderName, const string& recieverName, const std::vector<Message>& message); // ����� ��������� ���������
	void ShowAvailableChats(const vector<User>& users, const User& user); // ����� ��������� �����
};