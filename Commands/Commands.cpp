#include "Commands.hpp"

Commands::Commands(Server *server) : _Server(server)
{
 
}

bool Commands::authRequired() const
{
    return (_authRequired);
}

void Commands::ToUse(User *user)
{
    std::string line;
    if (user->_Buffer.find("\r\n") != std::string::npos)
    {
        line = user->_Buffer.substr(0, user->_Buffer.find("\r\n"));
        user->_Buffer.erase(0, line.size() + 2);
    }
    else
    {
        line = user->_Buffer.substr(0, user->_Buffer.find("\n"));
        user->_Buffer.erase(0, line.size() + 1);
    }
    std::string name = line.substr(0, line.find(" "));
    Commands *command;
    if(_Commands.size() > 0)
        command = _Commands.at(name);
    else
        command = 0;
    std::vector<std::string> arguments;

    std::string buf;
    std::stringstream ss(line.substr(name.size(), line.size()));
    line.substr(name.size(), line.size());

    while (ss >> buf)
        arguments.push_back(buf);
    if(!name.compare("PASS"))
        Pass(user, arguments);
    if (!user->IsRegistered() && command && command->authRequired())
    {
        user->ReplyMsg(ERR_NOTREGISTERED(user->getNickname()));
        return;
    }
    Handle(user, arguments, name);
    if (user->_Buffer.size())
        ToUse(user);
}

void Commands::Handle(User *user, std::vector<std::string> obj, std::string const cmd)
{
    if(!cmd.compare("PASS"));
    else if(!cmd.compare("USER"))
        UserCmd(user, obj);
    else if(!cmd.compare("JOIN"))
        Join(user, obj);
    else if(!cmd.compare("QUIT"))
        Quit(user, obj);
    else if(!cmd.compare("INVITE"))
        Invite(user, obj);
    else if(!cmd.compare("KICK"))
        Kick(user, obj);
    else if(!cmd.compare("TOPIC"))
        Topic(user, obj);
    else if(!cmd.compare("PRIVMSG"))
        PrivMsg(user, obj);
    else if(!cmd.compare("NICK"))
        Nick(user, obj);
    else if(!cmd.compare("PONG"))
        Pong(user, obj);
    else if(!cmd.compare("PING"))
        Ping(user, obj);
    else if(!cmd.compare("MODE"))
       Mode(user, obj);
    else if(!cmd.compare("NOTICE"))
        Notice(user, obj);
    else if(!cmd.compare("CAP"))
        Cap(user, obj);
    else if(!cmd.compare("WHO"))
       Who(user, obj);
    else if(!cmd.compare("PART"))
        Part(user, obj);
    else
        user->ReplyMsg(ERR_UNKNOWNCOMMAND(user->getNickname(), cmd));
}