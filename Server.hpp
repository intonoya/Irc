#ifndef SERVER_HPP  
# define SERVER_HPP

#include <iostream>
#include <string>
//#include <vector> //not sure about this one
#include <map>
#include <unistd.h>
#include <fcntl.h>
#include "netdb.h" //for the network data operations

#include "User.hpp"
#include "Channel.hpp"

class User;
class Channel;

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
        //std::vector<User *>          _User;
        //std::vector<int>      _NewUser;
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
        
        void NewUser();
        void DeleteUser();
        void RunTheServer();

        bool TheBuffer(iterator &it);
};

#endif