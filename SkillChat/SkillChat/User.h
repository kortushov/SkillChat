#pragma once

#include "Message.h"
#include <string>

using namespace std;

class User
{
private:
	string _username; // ��� ������������. ����� ���� ���������� � ������ �������������
	string _password; // ������
	string _login;    // ����� ������������. �������� � �������� ������� �������������
	Message* _ptrCurrentMessage = nullptr; // ��������� �� ������� ���������

public:
	User(const string& username, const string& password, Message* ptrCurrentMessage); // ����������� ������� ������
	explicit User(const string& username);
	User(const string& username, const string& login, const string& password);
	User() = default; // ����������� �� ���������
	~User() = default; // ����������

	string getUserName() const; // ����� ���������� ��� �����������
	string getPassword() const; // ����� ���������� ������
	string getLogin() const; // ����� ���������� �����
	Message* getCurrentMessage() const; // ����� ���������� ��������� �� ������� ���������
	void DisplayUserName() const; // ����� �� ����� ����� ������������
	void DisplayUserLogin() const;// ����� �� ����� ������ ������������
	void setUserName(const string& username); // ����� ����������� �������� ����� ������������
	void setPassword(const string& password); // ������������� ������
	void setCurrentMessage(Message& ptrCurrentMessage); // ������������� ������ �� ��������� �������� ��������� 
};