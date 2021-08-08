#include <iostream>
#include "User.h"


User::User(const string& username, const string& password, Message* ptrCurrentMessage) : _username(username), _password(password), _ptrCurrentMessage(ptrCurrentMessage)
{
}

User::User(const string& username) : _username(username)
{
}

User::User(const string& username, const string& login, const string& password) : _username(username), _password(password), _login(login)
{
}

string User::getUserName() const
{
	return string(_username);
}

string User::getPassword() const
{
	return string(_password);
}

string User::getLogin() const
{
	return string(_login);
}


Message* User::getCurrentMessage() const
{
	return _ptrCurrentMessage;
}

void User::setUserName(const string& username)
{
	_username = username;
}

void User::DisplayUserName() const
{
	cout << _username << endl;
}

void User::DisplayUserLogin() const
{
	cout << _login << ", ";
}

void User::setPassword(const string& password)
{
	_password = password;
}

void User::setCurrentMessage(Message& ptrCurrentMessage)
{
	_ptrCurrentMessage = &ptrCurrentMessage;
}