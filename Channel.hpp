#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <string>
#include <vector>
#include "User.hpp"

class User;

class Channel
{
    private:
        std::string _name;
        std::string _pass;
        User *_admin;

        std::vector<User *> _users;

    public:
        // Channel();
        // ~Channel();
        // Channel(Channel const &obj);
        Channel(std::string const &name, std::string const &pass, User *admin);

        std::string getName();
        std::string getPass();
        std::vector<User *> getUsers();
        User *getUser(std::string const &nickname);

        void setName(std::string const &name);
        void setPass(std::string const &pass);
        
        bool isAdmin(User *user);
        bool isExist(User *user);

        void join(User *user);
        void part(User *user);
        void kick(User *user, std::string const &msg);
};

#endif