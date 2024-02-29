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
        std::string _topic;
        std::string _mode;

        User *_admin;

        bool    _inviteOnly;
        bool    _topicOperators;
        int     _limit;

        std::vector<User *> _users;
        std::vector<User *> _operators;
        std::vector<User *> _invitees;

    public:
        Channel(std::string const &name, std::string const &pass, User *admin);

        std::string getName();
        std::string getPass();
        std::string getTopic();
        std::vector<User *> getUsers();
        User *getUser(std::string const &nickname);
        User *getAdmin();
        int getLimit();

        void setName(std::string const &name);
        void setPass(std::string const &pass);
        void setTopic(std::string const &topic);
        void setAdmin(User *admin);
        void setMode(std::string const &mode);
        void setOperator();
        void setInvite(User *user);

        void unsetOperator();
        void unsetInvite(User *user);

        void applyMode();
        
        bool isAdmin(User *user);
        bool isOperator(User *user);
        bool isExist(User *user);
        bool isInvite(User *user);
        bool isInviteOnly();
        bool isTopicOperators();

        void join(User *user);
        void part(User *user);
        void kick(User *user, std::string const &msg);

        void sendMsg(User *user, std::string const &msg);

};

#endif