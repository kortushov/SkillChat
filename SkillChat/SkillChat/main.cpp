#include <iostream>
#include <string>
#include <vector>
#include "Message.h"
#include "User.h"
#include "Chat.h"
#include <Windows.h>
#include <fstream>

using namespace std;

vector<Message> messages = { Message("Сообщение от Васи в common"s,"Вася"s,"Вася"s), Message("Сообщение от Васи Пете"s,"Вася"s, "Вася"s,"Петя"s) }; // Массив сообщений
vector<User> users = { User("Вася"s,"Вася"s, "123"s), User("Петя"s, "Петя"s,"321"), User("Олег"s,"Олег"s, "345"s) }; // Массив пользователей
User* currentUser = nullptr; // Указатель на текущего пользователя

void registration()		// Функция регистрации новых пользователей
{
	bool regPass{ false };	// Переменная для проверки успешности регистрации

	while (!regPass)	// Цикл while до успешной регистрации
	{
		string regLogin;
		cout << "Регистрация нового пользователя. Введите ваш логин" << endl;
		cin >> regLogin;			// Ввод с консоли логина
		auto it = users.begin();
		while (it != users.end())		// Пробегаем мо массиву зарегистрированных пользователей
			if (regLogin == (it++)->getLogin())	// Если занято, то выходим из цикла
			{
				cout << "Данный логин занят, введите другой" << endl;
				break;
			}
		if (it == users.end())		// Если дошли до конца массива и такого пользователя нет
		{
			string regPassword;	// Переменная Password тип string
			cout << "Введите пароль" << endl;
			cin >> regPassword;				// Ввод пароля с консоли
			if (regPassword.empty())		// Проверка на пустой пароль
			{
				cout << "Пароль должен содержать как минимум 1 символ" << endl;
				break;
			}
			string regName;		// Переменная имя пользователя
			cout << "Введите имя пользователя" << endl;
			cin >> regName;
			ofstream out("users.txt", std::ios::app);	// Создаем поток для вывода пользователя в фаил

			if (out.is_open())		// Проверка откытого файла
			{
				out << regName << " " << regLogin << " " << regPassword << endl;	// Записываем имя, логин и пароль пользователя
			}
			out.close();		// Закрываем вывод
			users.push_back(User(regName, regLogin, regPassword));	// Записываем объект с новым пользователем в массив пользователей
			cout << "Регистрация завершена успешна" << endl;
			regPass = true;		// Присваевам значение истина признаку успешности регистрации для выхода из цикла
			break;
		}

	}
}


void enter()		// Функция входа зарегестрированных пользователей
{
	bool enterPass{ false };	// Переменная проверки успешности входа
	while (!enterPass)		// Создаем цикл с проверкой условия успешности входа
	{
		string login;	// Переменная задаем логин пользователя
		cout << "Введите Логин или exit для выхода в основное меню" << endl; // Предлагаем ввести логин или выйти
		cin >> login;		// Считываем логин пользователя
		if (login == "exit") // Если пользователь ввел exit - выходим из цикла, возврат функции
		{
			break;
		}
		for (int i = 0; i < users.size(); i++)		// Цикл для прохода по массиву пользователей в поиске зарегистрированного
		{
			if (users[i].getLogin() == login)	// Условие равенства, совпадения
			{
				string password;	// Задаем переменную password
				cout << "Введите пароль" << endl;
				cin >> password;	// Ввод пароля с консоли
				if (users[i].getPassword() == password)	// Сравнение пароля у данного логина
				{
					cout << "Вход успешен" << endl;
					currentUser = &users[i];		// Присваеваем текущего пользователя по ссылке
					enterPass = true;			// Значение признака логина устанавливаем в true
					break;
				}
				else		// Если пароль не совпадает
				{
					cout << "Неверный пароль" << endl;	// Выводим сообщение и выходим из цикла
					break;
				}
			}
			else if (i + 1 == users.size())	// Если прошли до конца массива и не нашли данного логина
			{
				cout << "Нет пользователя с данным регистрационным именем" << endl;		// Выводим сообщение в консоль
			}
		}
	}
}

int main()
{
	Chat chat;	// Создаем объект чат
	SetConsoleCP(1251);			// Устанавливаем кодировку 1251 для ввода/вывода
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	bool isExit{ false };		// Переменная для проверки выхода пользователя из чата
	bool isRecieverExists{ false };	// Проверка наличия принимающего сообщения с определенным именем
	string inUserName;			// Переменная для вывода имени из файла
	string inPassword;			// Переменная для вывода пароля из фаила
	string inLogin;				// Переменная для вывода логина из файла
	string reciever;			// Переменная для записи имени принимающего сообщение
	string command;		// Переменная для считывания пользовательских комманд
	ifstream in("users.txt");	// окрываем файл для чтения
	if (in.is_open())			// Если открытие успешно
	{
		while (in >> inUserName >> inLogin >> inPassword)	// Пока вывод из файла успешен, считываем имя, логин и пароль
		{
			users.push_back(User(inUserName, inLogin, inPassword));	// Считываем объект пользоватля в массив, вставляем в конец
		}
	}
	in.close();	// Закрываем файл после завершения вывода

	while (!isExit)	// Организуем цикл пока пользователь не решит выйти из чата
	{
		while (command != "exit")
		{
			cout << "Введите enter для входа или register для регистрации. Для выхода введите exit" << endl;
			cin >> command;		// Считываем комманду с консоли 
			if (!command.compare("exit"s))	// Если пользователь решил выйти, то выходим
			{
				isExit = true;
				continue;
			}
			if (!command.compare("register"s))	// Если пользователь решил зарегестрироваться вызываем функцию регистрации
			{
				registration();
			}
			if (!command.compare("enter"s))	// Если пользователь решил войти, то вызываем функцию enter()
			{
				enter();
			}
			if (currentUser != nullptr)	// Проверка на текущего пользователя
			{
				while (command.compare("exit"s)) // Организуем чат с проверкой на выход
				{
					cout << "Список доступных чатов с пользователями:" << endl;
					chat.ShowAvailableChats(users, *currentUser);	// Вывод зарегистрированных пользователей
					cout << "\nВыберите имя пользователя, которому хотите отправить сообщение или common для общего чата" << endl;
					cout << "Для выхода в меню входа и регистрации введите exit" << endl;
					cin >> command;	// Считываем комманду пользователя с консоли 
					if (!command.compare("exit"s))	// Если пользователь решил выйти - выходим из чата
					{
						continue;
					}
					if (!command.compare("common"s))	// Если пользователь решил войти в общий чат
					{
						cout << "\nВывод истории сообщений в чат common" << endl;
						chat.ShowCommon(messages);	// Вывести сохраненные общие сообщения
						cout << "\nВвод нового сообщения. Для выхода из чата введите endchat" << endl;
						while (command.compare("endchat"s))		// Проверка выхода из общего чата
						{
							getline(cin, command);			// Считываем ввод пользователя
							if (!command.compare("endchat"s))	// Если команда выход из общего чата. то выходим
							{
								break;
							}
							else		// Иначе выводим объект сообщения в массив 
							{
								messages.push_back(Message(command, currentUser->getLogin(), currentUser->getUserName())); // Запись объекта Message 
								messages[messages.size() - 1].ShowMessage(); // Выводим последнее сообщение
							}
						}
					}
					else				// Если пользователь входит в приватный чат
					{
						for (size_t i = 0; i < users.size(); i++)	// Сверяем логин с именами зарегестрированных пользователей
						{
							if (users[i].getLogin() == command)	// Условие совпадения
							{
								reciever = command;	// Присваеваеи имя того, кому пользователь решил отправить сообщение
								isRecieverExists = true; // Устанавливаем признак приватных сообщений
								break;
							}
							else if (i + 1 == users.size())	// Если в массиве не обнаружено данного пользователя
							{
								cout << "Данного пользователя не существует" << endl;
							}

						}
						if (isRecieverExists) // Если второй пользователь существует
						{
							chat.ShowPrivate(currentUser->getUserName(), reciever, messages);	// Выводим сообщения между этими пользователями
							cout << "Ввод новых сообщений. Для выхода из чата введите endchat" << endl;
							while (command.compare("endchat"s)) // Проверка на выход из чата 
							{
								getline(cin, command);		// Ввод сообщений с консоли
								if (!command.compare("endchat"s))	// Выходим если endchat
								{
									break;
								}
								else		// Если не выход, записываем сообщение в массив сообщений и выводим последнее
								{
									messages.push_back(Message(command, currentUser->getLogin(), currentUser->getUserName(), reciever));
									messages[messages.size() - 1].ShowMessage();
								}
							}
						}
						isRecieverExists = false; // Признак отсутствия второго пользователя
					}
				}
			}
			command.clear(); // Очистка ввода
		}
	}
	return 0;
}