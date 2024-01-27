#ifndef SERVER_HPP  
# define SERVER_HPP

#include <iostream>
#include <string>
#include "Channel.hpp"

class Server
{
    private:
        short _Port;
        std::string &_Pass;
        Server();
        ~Server();
        //Server &operator=(Server const &obj);
    public:
        Channel *getName(std::string const &name);
    
};

#endif