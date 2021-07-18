#include <iostream>
#include <string>
#include <vector>
#include "Message.h"
#include "User.h"
#include "Chat.h"
#include <Windows.h>
#include <fstream>

using namespace std;

vector<Message> messages = { Message("Сообщение от Васи в common"s,"Вася"s,"Вася"s), Message("Сообщение от Васи Пете"s,"Вася"s, "Вася"s,"Петя"s) }; //Вектор сообщений
vector<User> users = { User("Вася"s,"Вася"s, "123"s), User("Петя"s, "Петя"s,"321"), User("Олег"s,"Олег"s, "345"s) }; //Вектор пользователей
User* currentUser = nullptr; //Указатель на активного сейчас пользователя

void registration()		//Функция регистрации новых пользователей
{
	bool regPass{ false };	//Переменная для проверки успешности регистрации

	while (!regPass)	//Пока регистрация не успешна
	{
		string regLogin;
		cout << "Регистрация" << endl;
		cout << "Введите желаемый логин" << endl;
		cin >> regLogin;			//Считываем желаемое пользователем имя
		auto it = users.begin();
		while (it != users.end())		//Сверяем его с именами других пользователей
			if (regLogin == (*it++).getLogin())	//Если оно занято, то выходим из цикла
			{
				cout << "Логин занят. Введите другой" << endl;
				break;
			}
		if (it == users.end())		//Если в векторе пользоваталей нет с таким же именем
		{
			string regPassword;	//Вводимый пользователем пароль
			cout << "Введите пароль" << endl;
			cin >> regPassword;				//Считываем желаемый пароль
			if (regPassword.empty())			//Если пароль пустой, то жалуемся на это и не даем пройти регистраци
			{
				cout << "Пароль должен содержать как минимум 1 символ" << endl;
				break;
			}
			string regName;		//Вводимое пользователем имя
			cout << "Введите отображаемое имя пользователя" << endl;
			cin >> regName;
			ofstream out("users.txt", std::ios::app);	//Создаем поток для записи в фаил

			if (out.is_open())		//Если получилось открыть фаил
			{
				out << regName << " " << regLogin << " " << regPassword << std::endl;	//Записываем имя и пароль введенне пользоватлем
			}
			out.close();		//Закрываем поток
			users.push_back(User(regName, regLogin, regPassword));	//Записываем пользователя в вектор пользователей
			cout << "Регистрация успешна" << endl;
			regPass = true;		//Указываем успешность регистрации для выхода из цикла
			break;
		}

	}
}


void enter()		//Функция входа зарегестрированных пользователей
{
	bool enterPass{ false };	//Переменная проверки успешности входа для выхода из цикла
	while (!enterPass)		//Пока вход не успешен
	{
		string login;	//Переменная для считывагия ввода имени пользователя
		cout << "Введите Логин" << endl;
		cin >> login;		//Считываем имя пользователя
		for (int i = 0; i < users.size(); i++)		//Сверяем его с именами зарегестрированных пользователей
		{
			if (users[i].getLogin() == login)	//Если есть совпадение
			{
				string password;	//Переменная для считывания ввода пароля
				cout << "Введите пароль" << endl;
				cin >> password;					//Считываем пароль
				if (users[i].getPassword() == password)	//Если пароль совпадает с паролем пользователя с данным именем
				{
					cout << "Вход успешен" << endl;
					currentUser = &users[i];		//Делаем данного пользователя активныс
					enterPass = true;					//Делаем вход успешным
					break;
				}
				else								//Если пароль не верен
				{
					cout << "Неверный пароль" << endl;	//Жалуемся на это и выходим из цикла
					break;
				}
			}
			else if ((i + 1 == users.size()))	//Если мы прошли по всему массиву пользователей и не нашли подхлдящего
			{
				cout << "Нет такого пользователя" << endl;		//Жалуемся на это
			}
		}
	}
}

int main()
{
	Chat chat;	//Создаем объект чата
	SetConsoleCP(1251);			//Меняем настройки консоли для корректного ввода/вывода
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	bool isExit{ false };				//Переменная для проверки желания пользователем выйти
	bool isRecieverExists{ false };	//Проверка на существование принимающего сообщения с определенным именем
	string inUserName;			//Переменная для принятия имени из фаила
	string inPassword;			//Переменная для принятия пароля из фаила
	string inLogin;
	string reciever;			//Переменная для записи имени принимающего сообщение
	string command;		//Переменная для считывания пользовательских комманд
	ifstream in("users.txt");	// окрываем файл для чтения
	if (in.is_open())			//Если открытие успешно
	{
		while (in >> inUserName >> inLogin >> inPassword)	//Пока что-либо не сломалось или не дошли до конца фаила, считываем имя и пароль
		{
			users.push_back(User(inUserName, inLogin, inPassword));	//Записываем в вектор пользователя с таким именем и паролем
		}
	}
	in.close();	//Когда закончили с фаилом закрываем поток

	while (!isExit)	//Пока пользователь не решил выйти из программы
	{
		while (command != "exit")
		{
			cout << "Введите enter для входа или register для регистрации" << endl;
			cout << "Для выхода введите exit" << endl;
			cin >> command;		//Считываем комманду
			if (!command.compare("exit"s))	//Если пользователь решил выйти, то выходим
			{
				isExit = true;
				continue;
			}
			if (!command.compare("register"s))	//Если пользователь решил зарегестрироваться - регестрируемся
			{
				registration();
			}
			if (!command.compare("enter"s))	//Если пользователь решил войти, то входим
			{
				enter();
			}
			if (currentUser != nullptr)	//Если у нас есть активный пользователь
			{
				while (!command.compare("exit"s))//Пока он не решил выйти
				{
					chat.ShowAvailableChats(users, *currentUser);	//Показываем доступные этому пользователю чаты
					cout << "Введите логин, которому желаете написать или common для общего чата" << endl;
					cout << "Введите exit для выхода" << endl;
					cin >> command;	//Считываем комманду пользователя
					if (!command.compare("exits"))	//Если пользователь решил выйти - выходим
					{
						continue;
					}
					if (!command.compare("common"s))	//Если пользователь решил войти в общий чат
					{
						chat.ShowCommon(messages);	//Показать общие сообщение
						cout << "Можете писать сообщения" << endl;
						cout << "Введите endchat для выхода из чата" << endl;
						while (command.compare("endchat"s))//Пока пользователь не решил выйти из чата
						{
							getline(cin, command);			//Считываем ввод пользователя
							if (!command.compare("endchat"s))	//Если команда выход из чата. то выходим
							{
								break;
							}
							else					//Иначе записываем сообщение в вектор и показываем его 
							{
								messages.push_back(Message(command, currentUser->getLogin(), currentUser->getUserName()));
								messages[messages.size() - 1].ShowMessage();
							}
						}
					}
					else				//Если пользователь решил войти в приватный чат
					{
						for (size_t i = 0; i < users.size(); i++)		//Сверяем его с именами зарегестрированных пользователей
						{
							if (users[i].getLogin() == command)	//Если есть совпадение
							{
								reciever = command;	//Записываем имя того, кому польхователь решил отправить сообщение
								isRecieverExists = true;
								break;
							}
							else if ((i + 1 == users.size()))	//Если мы прошли по всему массиву пользователей и не нашли подхлдящего
							{
								cout << "Нет такого пользователя" << endl;		//Жалуемся на это
							}

						}
						if (isRecieverExists)
						{
							chat.ShowPrivate(currentUser->getUserName(), reciever, messages);	//Показываем сообщения между этими двумя пользователями
							cout << "Можете писать сообщения" << endl;
							cout << "Введите endchat для выхода из чата" << endl;
							while (command.compare("endchat"s)) //Пока пользователь не решил выйти из чата
							{
								getline(cin, command);			//Считываем команду пользователя
								if (!command.compare("endchat"s))	//Если выход - выходим
								{
									break;
								}
								else						//Если не выход, записываем сообщение в вектор сообщений и показываем
								{
									messages.push_back(Message(command, currentUser->getLogin(), currentUser->getUserName(), reciever));
									messages[messages.size() - 1].ShowMessage();
								}
							}
						}
						isRecieverExists = false;
					}
				}
			}
			command.clear();
		}
	}
}

