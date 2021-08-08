#pragma once

#include "Message.h"
#include <string>

using namespace std;

class User
{
private:
	string _username; // имя пользователя. Может быть одинаковым у разных пользователей
	string _password; // пароль
	string _login;    // логин пользователя. Уникален в пределах массива пользователей
	Message* _ptrCurrentMessage = nullptr; // указатель на текущее сообщение

public:
	User(const string& username, const string& password, Message* ptrCurrentMessage); // конструктор объекта класса
	explicit User(const string& username);
	User(const string& username, const string& login, const string& password);
	User() = default; // конструктор по умолчанию
	~User() = default; // деструктор

	string getUserName() const; // метод возвращает имя польователя
	string getPassword() const; // метод возвращает пароль
	string getLogin() const; // метод возвращает логин
	Message* getCurrentMessage() const; // метод возвращает указатель на текущее сообщение
	void DisplayUserName() const; // вывод на экран имени пользователя
	void DisplayUserLogin() const;// вывод на экран логина пользователя
	void setUserName(const string& username); // метод присваивает значение имени пользователя
	void setPassword(const string& password); // устанавливает пароль
	void setCurrentMessage(Message& ptrCurrentMessage); // устанавливает ссылку на указатель текущего сообщения 
};