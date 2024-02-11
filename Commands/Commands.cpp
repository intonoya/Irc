#include "Commands.hpp"

void Commands::ToUse(User *user)
{
    std::string str;
    if (user->_Buffer.find("\r\n") != std::string::npos)
    {
        str = user->_Buffer.substr(0, user->_Buffer.find("\r\n"));
        user->_Buffer.erase(0, str.size() + 2);
    }
    else
    {
        str = user->_Buffer.substr(0, user->_Buffer.find("\n"));
        user->_Buffer.erase(0, str.size() + 1);
    }
    std::string name = str.substr(0, str.find(" "));

    try
    {
        Commands *command = _commands.at(name);

        std::vector<std::string> arguments;

        std::string _Buffer;
        std::stringstream ss(str.substr(name.length(), str.length()));
        str.substr(name.size(), str.size());

        while (ss >> _Buffer)
            arguments.push_back(_Buffer);
        if (!user->is_registered() && command->authRequired())
        {
            user->reply(ERR_NOTREGISTERED(user->get_nickname()));
            return;
        }
        command->execute(user, arguments);
    }
    catch (const std::out_of_range &e)
    {
        user->reply(ERR_UNKNOWNCOMMAND(user->get_nickname(), name));
    }

    if (user->_Buffer.size())
        ToUse(user);
}