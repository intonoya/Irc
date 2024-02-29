#include "User.hpp"

User::User(int fd, std::string hostname) :  _Nickname(), _UserName(), _HostName(hostname), _Name(), _Registration(false), _Pass(false), _FileDescriptor(fd)
{
    _Quit = false;
}

User::~User()
{

}

bool User::getPass()
{
    return (_Pass);
}

void User::setPass()
{
    _Pass = true;
}

std::string User::getHostName() const
{
    return (_HostName);
}

std::string User::getNickname() const
{
    return (_Nickname);
}

std::string User::getUserName() const
{
    return (_UserName);
}

std::string User::getName() const
{
    return (_Name);
}

std::string User::getMessage() const 
{ 
    std::string result = _Nickname;
    if (!_UserName.empty())
        result += "!" + _UserName;
    if (!_HostName.empty())
        result += "@" + _HostName;
    return result;
}

int User::getFd() const
{
    return (_FileDescriptor);
}

void User::setHostName( const std::string hostname)
{
    _HostName = hostname;
}

void User::setNickname(std::string nickname)
{
    _Nickname = nickname;
}

void User::setUserName(const std::string username)
{
    _UserName = username;
}

void User::setName(const std::string name)
{
    _Name = name;
}

void User::setRegistration(bool reg)
{
    _Registration = reg;
}

void User::setQuit(bool status)
{
    _Quit = status;
}

void User::SendMsg(const std::string &msg)
{
    std::string buffer = msg + "\r\n";

    if (send(_FileDescriptor, buffer.c_str(), buffer.length(), 0) < 0)
         std::cout << "\33[1;31mError: Can't send the message to the client!\33[1;31m" << std::endl;
}

void User::ReplyMsg(const std::string &msg)
{
    SendMsg(":" + getMessage() + " " + msg);
}

void User::Registration()
{
    if (_Pass && !_UserName.empty() && !_Name.empty() && !_Nickname.empty())
    {
        _Registration = true;
        ReplyMsg(RPL_WELCOME(_Nickname));
        std::cout << "Registered: " << this->getMessage() << std::endl;
    }
}

bool User::IsRegistered()
{
    return (_Registration);
}

void User::JoinTheChannel(Channel *channel)
{
    _Channel.push_back(channel);
    channel->join(this);
}

void User::LeaveTheChannel(Channel *channel)
{
    for(std::vector<Channel *>::iterator it = _Channel.begin(); it != _Channel.end(); ++it)
    {
        if(*it == channel)
        {
            it = _Channel.erase(it);
            break;
        }
    }
}

void User::DeleteUser(int del)
{
    (void)del;
    for (std::vector<Channel *>::iterator it = _Channel.begin(); it != _Channel.end(); ++it)
        (*it)->part(this);
    _Channel.clear();
}

void User::Init(std::string const &username, std::string const &name)
{
    _UserName = username;
    _Name = name;
}