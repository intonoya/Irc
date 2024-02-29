#ifndef SERVER_HPP  
# define SERVER_HPP

#include <iostream>
#include <string>
#include <map>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include "netdb.h" //for the network data operations

#include "User.hpp"
#include "Channel.hpp"
#include "./Commands/Commands.hpp"


class User;
class Channel;
class Commands;

class Server
{
    private:
        int _Port;
        int _FileDescriptor;
        std::string const &_Psw;
        sockaddr_in _Address;
        std::map<int, User*>          _User;
        std::map<std::string, int>      _NewUser;
        std::map<std::string, Channel*>	_Channel;
        typedef std::map<int, User*>::iterator  iterator;
        Commands *_Commands;
    public:
        
        Server();
        ~Server();
        Server &operator=(Server const &obj);
        Server(int port, std::string const &psw);
        int getPort() const;
        Channel *getName(std::string const &name);
        Channel *getChannel(std::string const &name);
        Channel *AddChannel(std::string const &name, std::string const &psw);
        std::string getPassword() const;

        User *getUser(std::string const &nickname);
        void setUser(User *user, std::string const &nickname, int fd);
        void addUser(User *user, int fd);
        
        void NewUser();
        void DeleteUser(iterator &it);
        int  InitTheServer();
        void RunTheServer();

        bool TheBuffer(iterator &it);
};

#endif