#include "User.hpp"

User::User()
{

}

User::~User()
{

}

User::User(int fd, std::string const &hostname, std::string const &nickname, std::string const &username) : _HostName(hostname), _Nickname(nickname), _UserName(username), _Registration(true), _isPass(true), _FileDescriptor(fd)
{

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

void User::setHostName( const std::string hostname)
{
    _HostName = hostname;
}

void User::setNickname(const std::string nickname)
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

void User::SendMsg(const std::string &msg)
{
    std::string buffer = msg + "\r\n";
    (void)_FileDescriptor;

    // delete this
    std::cout << _Nickname << ": " << buffer;
    //
    
    // uncomment this
    // if (send(_FileDescriptor, buffer.c_str(), buffer.length(), 0) < 0)
    //     std::cout << "\33[1;31mError: Can't send the message to the client!\33[1;31m" << std::endl;
}

void User::ReplyMsg(const std::string &msg)
{
    SendMsg(getMessage() + " " + msg);
}

void User::Registration()
{
    if (_isPass && !_UserName.empty() && !_Name.empty() && !_Nickname.empty())
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
            // delete channel; // xz nado ili net
            break;
        }
    }
}

void User::LeaveUser(int user)
{
    (void)user;
    for (std::vector<Channel *>::iterator it = _Channel.begin(); it != _Channel.end(); ++it)
        (*it)->part(this);
    _Channel.clear();
}
