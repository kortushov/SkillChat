#include "Message.h"

Message::Message(const string& message, const string& senderLogin, const string& senderName) : _message(message), _senderName(senderName), _senderLogin(senderLogin), _isPrivate(false)
{
}

Message::Message(const string& message, const string& senderName, const string& senderLogin, const string& reciever) : _message(message), _senderName(senderName), _senderLogin(senderLogin), _recieverLogin(reciever), _isPrivate(true)
{
}

string Message::GetSenderName() const
{
	return _senderLogin;
}

string Message::GetRecieverName() const
{
	return _recieverLogin;
}

string Message::GetMessage() const
{
	return _message;
}

bool Message::GetBool() const
{
	return _isPrivate;
}

void Message::ShowMessage() const
{
	cout << _senderName << ":" << _message << endl;
}
