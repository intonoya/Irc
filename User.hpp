#ifndef USER_HPP
# define USER_HPP

#include <string>
#include <iostream>
#include <sys/socket.h> //works only with linux
#include "Channel.hpp"
#include "Parsing.hpp"
#include <vector>

class User
{
    private:
        std::vector<Channel *> _Channel;
        std::string _HostName;
        std::string _Nickname;
        std::string _UserName;
        std::string _Name;
        bool _Registration;
        bool _Pass;
        int _FileDescriptor;

    public:

        User();
        ~User();

        std::string getHostName() const;
        std::string getNickname() const;
        std::string getUserName() const;
        std::string getName() const;
        std::string getMessage() const;

        void setHostName(const std::string hostname);
        void setNickname(const std::string nickname);
        void setUserName(const std::string username);
        void setName(const std::string name);
        
        void Registration(); //registors the user
        void IsRegistered(); //checks if the user is registered
        void ReplyMsg(const std::string &msg); //reply's to the client
        void SendMsg(const std::string &msg); //sends the message to the client
        void JoinTheChannel(Channel *channel); //
        void LeaveTheChannel(Channel *channel); //
        void LeaveUser(int delete); //

};

#endif