#include "Channel.hpp"

Channel::Channel()
{
}

Channel::~Channel()
{
}

Channel::Channel(Channel const &obj)
{
    *this = obj;
}

Channel::Channel(std::string const &name, std::string const &pass) : _Name(name), _Pass(pass)
{

}

// Channel &Channel::operator=(Channel const &obj)
// {
    
// }

std::string Channel::getPass()
{
    return (_Pass);
}
    
void Channel::setPass(std::string const &pass)
{
    _Pass = pass;
}

//void Channel::Join(User *user)
//{

//}

//void Channel::Part(User *user)
//{

//}

//void Channel::Kick(User *user, std::string const &msg)
//{

//}