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
        std::vector<User *> _User;
        std::string _Name;
        std::string _Pass;
        //User *_Admin;

    public:
        Channel();
        ~Channel();
        Channel(Channel const &obj);
        Channel(std::string const &name, std::string const &pass);
        std::string getPass();
        void setPass(std::string const &pass);
        void Join(User *user);
        void Part(User *user);
        void Kick(User *user, std::string const &msg);
};

#endif