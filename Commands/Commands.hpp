#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include "../User.hpp"
#include "../Channel.hpp"
#include "../Server.hpp"
#include "../Parsing.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class User;
class Channel;
class Server;

class Commands
{
    private:
        std::map<std::string, Commands*> _Commands;
        Server *_Server;
        bool _authRequired;
    public:
        Commands(Server *server);
        ~Commands();

        void ToUse(User *user);
        bool authRequired() const;
        //void execute(User *user, std::vector<std::string> arguments);

        void Invite(User *user, std::vector<std::string> obj);
        void Join(User *user, std::vector<std::string> obj);
        void Kick(User *user, std::vector<std::string> obj);

};

#endif