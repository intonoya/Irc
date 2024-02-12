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

    try
    {
        Commands *command = _Commands.at(name);

        std::vector<std::string> arguments;

        std::string buf;
        std::stringstream ss(line.substr(name.size(), line.size()));
        line.substr(name.size(), line.size());

        while (ss >> buf)
            arguments.push_back(buf);
        if (!user->IsRegistered() && command->authRequired())
        {
            std::cout<<"blublu"<<std::endl;
            user->ReplyMsg(ERR_NOTREGISTERED(user->getNickname()));
            return;
        }
        //->execute(user, arguments);
    }
    catch (const std::out_of_range &e)
    {
        user->ReplyMsg(ERR_UNKNOWNCOMMAND(user->getNickname(), name)); 
    }

    if (user->_Buffer.size())
        ToUse(user);
}