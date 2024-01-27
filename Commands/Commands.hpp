#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include "../User.hpp"
#include "../Channel.hpp"
#include "../Server.hpp"
#include "../Parsing.hpp"
#include <iostream>
#include <string>
#include <vector>


class Commands
{
    public:
        void Invite(User *user, std::vector<std::string> obj);
        void Join(User *user, std::vector<std::string> obj);
        void Kick(User *user, std::string const &reason);

};

#endif