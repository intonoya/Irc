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
class Parsing;

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

        void Handle(User *user, std::vector<std::string> obj, std::string const cmd);
        
        void Pass(User *user, std::vector<std::string> obj);
        void Invite(User *user, std::vector<std::string> obj);
        void Join(User *user, std::vector<std::string> obj);
        void Kick(User *user, std::vector<std::string> obj);
        void Mode(User *user, std::vector<std::string> obj);
        void Topic(User *user, std::vector<std::string> obj);
        void PrivMsg(User *user, std::vector<std::string> obj);
        void Quit(User *user, std::vector<std::string> obj);
        void UserCmd(User *user, std::vector<std::string> obj);
        void Nick(User *user, std::vector<std::string> obj);
        void Notice(User *user, std::vector<std::string> obj);
        void Pong(User *user, std::vector<std::string> obj);
        void Ping(User *user, std::vector<std::string> obj);
        void Cap(User *user, std::vector<std::string> obj);
        void Who(User *user, std::vector<std::string> obj);
        void Part(User *user, std::vector<std::string> obj);
};

#endif