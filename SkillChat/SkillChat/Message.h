#pragma once

#include <string>
#include <iostream>

using namespace std;

class Message // описание класса Message
{
	string _message;  // приватное поле сообщение
	string _senderName; // имя пользователя
	string _senderLogin; // логин пользователя
	string _recieverLogin; // логин получателя
	bool _isPrivate{ false }; // приватное сообщение
public:
	Message(const string& message, const string& senderLogin, const string& senderName); // конструктор объекта класса для общий сообщений
	Message(const string& message, const string& senderLogin, const string& senderName, const string& reciever); // конструктор объекта класса приватных сообщений
	string GetSenderName() const; // метод возвращает имя отправителя
	string GetRecieverName() const; // метод возвращает имя получателя
	string GetMessage() const; // метод возвращает сообщение
	bool GetBool() const; // возвращает значение переменной _isPrivate 
	void ShowMessage() const; // вывод на экран сообщения в формате "имя отправителя": "сообщение"
};