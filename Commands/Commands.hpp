#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include "../User.hpp"
#include "../Channel.hpp"
#include "../Server.hpp"
#include "../Parsing.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>

class Server;
class User;

class Commands
{
    private:
        Server *_Server;
        std::map<std::string, Commands*> _Commands;
    public:
        Commands(Server *server);
        ~Commands();

        void ToUse(User *user);
        
        void Invite(User *user, std::vector<std::string> obj);
        void Join(User *user, std::vector<std::string> obj);
        void Kick(User *user, std::string const &reason);



};

#endif