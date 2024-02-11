#include "Commands.hpp"

Commands::Commands(Server *server) : _Server(server)
{
    
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
        //Commands *command = _Commands.at(name); het hani commic

        std::vector<std::string> arguments;

        std::string buf;
        //std::stringstream ss(line.substr(name.length(), line.length())); het hani commic
        line.substr(name.size(), line.size());

        //while (ss >> buf) het hani commic
            arguments.push_back(buf);
        if (!user->IsRegistered()) // && command->authRequired()) het hani commic
        {
            std::cout<<"blublu"<<std::endl;
            //user->reply(ERR_NOTREGISTERED(user->getNickname())); het hani commic
            return;
        }
        //command->execute(user, arguments); het hani commic
    }
    catch (const std::out_of_range &e)
    {
        std::cout<<"blabla"<<std::endl;
        //user->reply(ERR_UNKNOWNCOMMAND(user->getNickname(), name)); het hani commic
    }

    if (user->_Buffer.size())
        ToUse(user);
}