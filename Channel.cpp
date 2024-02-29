#include "Channel.hpp"

Channel::Channel(std::string const &name, std::string const &pass, User *admin) : _name(name), _pass(pass), _admin(admin), _inviteOnly(false), _limit(0)
{

}

std::string Channel::getName()
{
    return (_name);
}

std::string Channel::getPass()
{
    return (_pass);
}

std::string Channel::getTopic()
{
    return (_topic);
}

std::vector<User *> Channel::getUsers()
{
    return (_users);
}

User *Channel::getUser(std::string const &nickname)
{
    for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
    {
        if ((*it)->getNickname() == nickname)
            return (*it);
    }
    return (NULL);
}

User *Channel::getAdmin()
{
    return (_admin);
}

int Channel::getLimit()
{
    return (_limit);
}

void Channel::setName(std::string const &name)
{
    _name = name;
}

void Channel::setPass(std::string const &pass)
{
    _pass = pass;
}

void Channel::setTopic(std::string const &topic)
{
    _topic = topic;
}

void Channel::setAdmin(User *admin)
{
    _admin = admin;
}

void Channel::setMode(std::string const &mode)
{
    _mode = mode;
}

void Channel::setOperator()
{
    std::string nickname = _mode.substr(2);
    User *user = this->getUser(nickname);
    if (user)
    {
        _operators.push_back(user);
        // this->sendMsg(_admin, "New operator added");
        this->sendMsg(_admin, RPL_CHANNELMODEIS(_admin->getNickname(), _name, "+o " + user->getNickname()));
        _admin->SendMsg(RPL_CHANNELMODEIS(_admin->getNickname(), _name, "+o " + user->getNickname()));
    }
    else
    {
        this->sendMsg(_admin, RPL_CHANNELMODEIS(_admin->getNickname(), _name, "-o " + nickname));
        _admin->SendMsg(RPL_CHANNELMODEIS(_admin->getNickname(), _name, "-o " + nickname));
    }
}

void Channel::setInvite(User *user)
{
    _invitees.push_back(user);
}

void Channel::unsetOperator()
{
    std::string nickname = _mode.substr(2);
    User *user = this->getUser(nickname);
    if (user)
    {
        for (std::vector<User *>::iterator it = _operators.begin(); it != _operators.end(); ++it)
        {
            if (*it == user)
            {
                _operators.erase(it);
                // this->sendMsg(_admin, "Operator removed");
                break;
            }
        }
    }
    this->sendMsg(_admin, RPL_CHANNELMODEIS(_admin->getNickname(), _name, "-o " + nickname));
    _admin->SendMsg(RPL_CHANNELMODEIS(_admin->getNickname(), _name, "-o " + nickname));
}

void Channel::unsetInvite(User *user)
{
    for (std::vector<User *>::iterator it = _invitees.begin(); it != _invitees.end(); ++it)
    {
        if (*it == user)
        {
            _invitees.erase(it);
            break;
        }
    }
}

void Channel::applyMode()
{
    if (_mode[0] == '+')
    {
        if (_mode[1] == 'i')
        {
            _inviteOnly = true;
            this->sendMsg(_admin, RPL_CHANNELMODEIS(_admin->getNickname(), _name, "+i"));
            _admin->SendMsg(RPL_CHANNELMODEIS(_admin->getNickname(), _name, "+i"));
        }
        else if (_mode[1] == 't')
        {
            _topicOperators = true;
            this->sendMsg(_admin, RPL_CHANNELMODEIS(_admin->getNickname(), _name, "+t"));
            _admin->SendMsg(RPL_CHANNELMODEIS(_admin->getNickname(), _name, "+t"));
        }
        else if (_mode[1] == 'k')
        {
            _pass = _mode.substr(2);
            this->sendMsg(_admin, RPL_CHANNELMODEIS(_admin->getNickname(), _name, "+k " + _pass));
            _admin->SendMsg(RPL_CHANNELMODEIS(_admin->getNickname(), _name, "+k " + _pass));
        }
        else if (_mode[1] == 'o')
        {
            this->setOperator();
        }
        else if (_mode[1] == 'l')
        {
            std::string limit = _mode.substr(2);
            for (std::string::iterator it = limit.begin(); it != limit.end(); ++it)
            {
                if (!isdigit(*it))
                {
                    // this->sendMsg(_admin, "Invalid limit");
                    this->sendMsg(_admin, RPL_CHANNELMODEIS(_admin->getNickname(), _name, "-l"));
                    _admin->SendMsg(RPL_CHANNELMODEIS(_admin->getNickname(), _name, "-l"));
                    return ;
                }
            }
            
            _limit = atoi(limit.c_str());
            // this->sendMsg(_admin, "Channel limit is now " + std::to_string(_limit));
            this->sendMsg(_admin, RPL_CHANNELMODEIS(_admin->getNickname(), _name, "+l " + std::to_string(_limit)));
            _admin->SendMsg(RPL_CHANNELMODEIS(_admin->getNickname(), _name, "+l " + std::to_string(_limit)));
        }
    }
    else if (_mode[0] == '-')
    {
        if (_mode[1] == 'i')
        {
            _inviteOnly = false;
            // this->sendMsg(_admin, "Channel is no longer invite only");
            this->sendMsg(_admin, RPL_CHANNELMODEIS(_admin->getNickname(), _name, "-i"));   
            _admin->SendMsg(RPL_CHANNELMODEIS(_admin->getNickname(), _name, "-i"));
        }
        else if (_mode[1] == 't')
        {
            _topicOperators = false;
            // this->sendMsg(_admin, "Topic in channel is no longer moderated");
            this->sendMsg(_admin, RPL_CHANNELMODEIS(_admin->getNickname(), _name, "-t"));
            _admin->SendMsg(RPL_CHANNELMODEIS(_admin->getNickname(), _name, "-t"));
        }
        else if (_mode[1] == 'k')
        {
            _pass = "";
            // this->sendMsg(_admin, "Channel password is now removed");
            this->sendMsg(_admin, RPL_CHANNELMODEIS(_admin->getNickname(), _name, "-k"));
            _admin->SendMsg(RPL_CHANNELMODEIS(_admin->getNickname(), _name, "-k"));
        }
        else if (_mode[1] == 'o')
        {
            unsetOperator();
        }
        else if (_mode[1] == 'l')
        {
            _limit = 0;
            // this->sendMsg(_admin, "Channel limit is now removed");
            this->sendMsg(_admin, RPL_CHANNELMODEIS(_admin->getNickname(), _name, "-l"));
            _admin->SendMsg(RPL_CHANNELMODEIS(_admin->getNickname(), _name, "-l"));
        }
    }
    
    _mode.clear();
}

bool Channel::isAdmin(User *user)
{
    if (user == _admin)
        return (true);
    return (false);
}

bool Channel::isOperator(User *user)
{
    for (std::vector<User *>::iterator it = _operators.begin(); it != _operators.end(); ++it)
    {
        if (*it == user)
            return (true);
    }
    return (false);
}

bool Channel::isExist(User *user)
{
    for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
    {
        if (*it == user)
            return (true);
    }
    return (false);
}

bool Channel::isInvite(User *user)
{
    for (std::vector<User *>::iterator it = _invitees.begin(); it != _invitees.end(); ++it)
    {
        if (*it == user)
            return (true);
    }
    return (false);
}

bool Channel::isInviteOnly()
{
    return (_inviteOnly);
}

bool Channel::isTopicOperators()
{
    return (_topicOperators);
}

void Channel::join(User *user)
{
    _users.push_back(user);
}

void Channel::part(User *user)
{
    // for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
    // {
    //     if (*it == user)
    //     {
    //         _users.erase(it);
    //         break;
    //     }
    // }
    std::vector<User *>::iterator tmp;
    for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); it++)
    {
        (*it)->SendMsg(RPL_PART(user->getMessage(), _name));
        if (*it == user)
            tmp = it;
    }
    _users.erase(tmp);
}

void Channel::kick(User *user, std::string const &msg)
{
    // for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
    // {
    //     if (*it == user)
    //     {
    //         _users.erase(it);
    //         break;
    //     }
    // }
    // user->SendMsg(msg);


    std::vector<User *>::iterator tmp;
    for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); it++)
    {
        (*it)->SendMsg(RPL_KICK(user->getMessage(), _name, user->getNickname(), msg));
        if (*it == user)
            tmp = it;
    }
    _users.erase(tmp);
}

void Channel::sendMsg(User *user, std::string const &msg)
{
    for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
    {
        if (*it != user)
            (*it)->SendMsg(msg);
    }
}