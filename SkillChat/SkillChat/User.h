#pragma once

#include "Message.h"
#include <string>

using namespace std;

class User
{
private:
	string _username; // ќтображаемое им€ пользовател€. ћожет быть одинаковым у разных пользователей
	string _password; // пароль
	string _login;    // логин. ”никален дл€ каждого пользовател€
	Message* _ptrCurrentMessage = nullptr; // указатель на текущее сообщение

public:
	User(const string& username, const string& password, Message* ptrCurrentMessage);
	explicit User(const string& username);
	User(const string& username, const string& login, const string& password);
	User() = default;
	~User() = default;

	string getUserName() const;
	string getPassword() const;
	string getLogin() const;
	Message* getCurrentMessage() const;
	void DisplayUserName() const; // вывод на экран имени пользовател€
	void DisplayUserLogin() const;// ¬ывод на экран логина пользовател€
	void setUserName(const string& username);
	void setPassword(const string& password);
	void setCurrentMessage(Message& ptrCurrentMessage);
};