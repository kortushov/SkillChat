#include <iostream>
#include <string>
#include <vector>
#include "Message.h"
#include "User.h"
#include "Chat.h"
#include <Windows.h>
#include <fstream>

using namespace std;

vector<Message> messages = { Message("��������� �� ���� � common"s,"����"s,"����"s), Message("��������� �� ���� ����"s,"����"s, "����"s,"����"s) }; //������ ���������
vector<User> users = { User("����"s,"����"s, "123"s), User("����"s, "����"s,"321"), User("����"s,"����"s, "345"s) }; //������ �������������
User* currentUser = nullptr; //��������� �� ��������� ������ ������������

void registration()		//������� ����������� ����� �������������
{
	bool regPass{ false };	//���������� ��� �������� ���������� �����������

	while (!regPass)	//���� ����������� �� �������
	{
		string regLogin;
		cout << "�����������" << endl;
		cout << "������� �������� �����" << endl;
		cin >> regLogin;			//��������� �������� ������������� ���
		auto it = users.begin();
		while (it != users.end())		//������� ��� � ������� ������ �������������
			if (regLogin == (*it++).getLogin())	//���� ��� ������, �� ������� �� �����
			{
				cout << "����� �����. ������� ������" << endl;
				break;
			}
		if (it == users.end())		//���� � ������� ������������� ��� � ����� �� ������
		{
			string regPassword;	//�������� ������������� ������
			cout << "������� ������" << endl;
			cin >> regPassword;				//��������� �������� ������
			if (regPassword.empty())			//���� ������ ������, �� �������� �� ��� � �� ���� ������ ����������
			{
				cout << "������ ������ ��������� ��� ������� 1 ������" << endl;
				break;
			}
			string regName;		//�������� ������������� ���
			cout << "������� ������������ ��� ������������" << endl;
			cin >> regName;
			ofstream out("users.txt", std::ios::app);	//������� ����� ��� ������ � ����

			if (out.is_open())		//���� ���������� ������� ����
			{
				out << regName << " " << regLogin << " " << regPassword << std::endl;	//���������� ��� � ������ �������� ������������
			}
			out.close();		//��������� �����
			users.push_back(User(regName, regLogin, regPassword));	//���������� ������������ � ������ �������������
			cout << "����������� �������" << endl;
			regPass = true;		//��������� ���������� ����������� ��� ������ �� �����
			break;
		}

	}
}


void enter()		//������� ����� ������������������ �������������
{
	bool enterPass{ false };	//���������� �������� ���������� ����� ��� ������ �� �����
	while (!enterPass)		//���� ���� �� �������
	{
		string login;	//���������� ��� ���������� ����� ����� ������������
		cout << "������� �����" << endl;
		cin >> login;		//��������� ��� ������������
		for (int i = 0; i < users.size(); i++)		//������� ��� � ������� ������������������ �������������
		{
			if (users[i].getLogin() == login)	//���� ���� ����������
			{
				string password;	//���������� ��� ���������� ����� ������
				cout << "������� ������" << endl;
				cin >> password;					//��������� ������
				if (users[i].getPassword() == password)	//���� ������ ��������� � ������� ������������ � ������ ������
				{
					cout << "���� �������" << endl;
					currentUser = &users[i];		//������ ������� ������������ ��������
					enterPass = true;					//������ ���� ��������
					break;
				}
				else								//���� ������ �� �����
				{
					cout << "�������� ������" << endl;	//�������� �� ��� � ������� �� �����
					break;
				}
			}
			else if ((i + 1 == users.size()))	//���� �� ������ �� ����� ������� ������������� � �� ����� �����������
			{
				cout << "��� ������ ������������" << endl;		//�������� �� ���
			}
		}
	}
}

int main()
{
	Chat chat;	//������� ������ ����
	SetConsoleCP(1251);			//������ ��������� ������� ��� ����������� �����/������
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	bool isExit{ false };				//���������� ��� �������� ������� ������������� �����
	bool isRecieverExists{ false };	//�������� �� ������������� ������������ ��������� � ������������ ������
	string inUserName;			//���������� ��� �������� ����� �� �����
	string inPassword;			//���������� ��� �������� ������ �� �����
	string inLogin;
	string reciever;			//���������� ��� ������ ����� ������������ ���������
	string command;		//���������� ��� ���������� ���������������� �������
	ifstream in("users.txt");	// �������� ���� ��� ������
	if (in.is_open())			//���� �������� �������
	{
		while (in >> inUserName >> inLogin >> inPassword)	//���� ���-���� �� ��������� ��� �� ����� �� ����� �����, ��������� ��� � ������
		{
			users.push_back(User(inUserName, inLogin, inPassword));	//���������� � ������ ������������ � ����� ������ � �������
		}
	}
	in.close();	//����� ��������� � ������ ��������� �����

	while (!isExit)	//���� ������������ �� ����� ����� �� ���������
	{
		while (command != "exit")
		{
			cout << "������� enter ��� ����� ��� register ��� �����������" << endl;
			cout << "��� ������ ������� exit" << endl;
			cin >> command;		//��������� ��������
			if (!command.compare("exit"s))	//���� ������������ ����� �����, �� �������
			{
				isExit = true;
				continue;
			}
			if (!command.compare("register"s))	//���� ������������ ����� ������������������ - ��������������
			{
				registration();
			}
			if (!command.compare("enter"s))	//���� ������������ ����� �����, �� ������
			{
				enter();
			}
			if (currentUser != nullptr)	//���� � ��� ���� �������� ������������
			{
				while (!command.compare("exit"s))//���� �� �� ����� �����
				{
					chat.ShowAvailableChats(users, *currentUser);	//���������� ��������� ����� ������������ ����
					cout << "������� �����, �������� ������� �������� ��� common ��� ������ ����" << endl;
					cout << "������� exit ��� ������" << endl;
					cin >> command;	//��������� �������� ������������
					if (!command.compare("exits"))	//���� ������������ ����� ����� - �������
					{
						continue;
					}
					if (!command.compare("common"s))	//���� ������������ ����� ����� � ����� ���
					{
						chat.ShowCommon(messages);	//�������� ����� ���������
						cout << "������ ������ ���������" << endl;
						cout << "������� endchat ��� ������ �� ����" << endl;
						while (command.compare("endchat"s))//���� ������������ �� ����� ����� �� ����
						{
							getline(cin, command);			//��������� ���� ������������
							if (!command.compare("endchat"s))	//���� ������� ����� �� ����. �� �������
							{
								break;
							}
							else					//����� ���������� ��������� � ������ � ���������� ��� 
							{
								messages.push_back(Message(command, currentUser->getLogin(), currentUser->getUserName()));
								messages[messages.size() - 1].ShowMessage();
							}
						}
					}
					else				//���� ������������ ����� ����� � ��������� ���
					{
						for (size_t i = 0; i < users.size(); i++)		//������� ��� � ������� ������������������ �������������
						{
							if (users[i].getLogin() == command)	//���� ���� ����������
							{
								reciever = command;	//���������� ��� ����, ���� ������������ ����� ��������� ���������
								isRecieverExists = true;
								break;
							}
							else if ((i + 1 == users.size()))	//���� �� ������ �� ����� ������� ������������� � �� ����� �����������
							{
								cout << "��� ������ ������������" << endl;		//�������� �� ���
							}

						}
						if (isRecieverExists)
						{
							chat.ShowPrivate(currentUser->getUserName(), reciever, messages);	//���������� ��������� ����� ����� ����� ��������������
							cout << "������ ������ ���������" << endl;
							cout << "������� endchat ��� ������ �� ����" << endl;
							while (command.compare("endchat"s)) //���� ������������ �� ����� ����� �� ����
							{
								getline(cin, command);			//��������� ������� ������������
								if (!command.compare("endchat"s))	//���� ����� - �������
								{
									break;
								}
								else						//���� �� �����, ���������� ��������� � ������ ��������� � ����������
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
