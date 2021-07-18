#pragma once

#include <string>
#include <iostream>

using namespace std;

class Message
{
	string _message;
	string _senderName;
	string _senderLogin;
	string _recieverLogin;
	bool _isPrivate{ false };
public:
	Message(const string& message, const string& senderLogin, const string& senderName);
	Message(const string& message, const string& senderLogin, const string& senderName, const string& reciever);
	string GetSenderName() const;
	string GetRecieverName() const;
	string GetMessage() const;
	bool GetBool() const; // ���������� �������� ���������� _isprivate 
	void ShowMessage() const; // ����� �� ����� ��������� � ������� "��� �����������": "���������"
};