#include "Server.hpp"

Server::Server(int port, std::string const &psw) : _Psw(psw) , _Commands(new Commands(this))
{
    if (port <= 65535)
    {
        _Port = port;
    }
    InitTheServer();
    RunTheServer();
}

Server::~Server()
{
    for (iterator it = _User.begin(); it != _User.end(); ++it)
    {
        delete it->second;
        close(it->first);
    }
    close(_FileDescriptor);
    for (std::map<std::string, Channel *>::iterator it = _Channel.begin(); it != _Channel.end(); ++it)
    {
        delete it->second;
    }
}

std::string Server::getPassword() const
{
    return (_Psw);
}

int Server::getPort() const
{
    if (_Port <= 65535)
        return (_Port);
    return (0);
}

Channel *Server::getName(std::string const &name)
{
    try
    {
        return _Channel.at(name);
    }
    catch (const std::exception &e)
    {
        return NULL;
    }
}

Channel *Server::getChannel(std::string const &name)
{
    try
    {
        return _Channel.at(name);
    }
    catch (const std::exception &e)
    {
        return NULL;
    }
}

Channel *Server::AddChannel(std::string const &name, std::string const &psw)
{
    Channel* newChannel = new Channel(name, psw, NULL); // mb nuzhen user

    _Channel.insert(std::make_pair(name, newChannel));
    return newChannel;
}

User *Server::getUser(std::string const &nickname)
{
    try
    {
        return _User.at(_NewUser.at(nickname));
    }
    catch (const std::exception &e)
    {
        return NULL;
    }
}

void Server::setUser(User *user, std::string const &newNickname, int fd)
{
    std::string oldNickname = user->getNickname();
    if (!oldNickname.empty())
    {
        for (iterator it = _User.begin(); it != _User.end(); ++it)
        {
            if (it->second != user)
                it->second->SendMsg(":" + oldNickname + " NICK " + newNickname);
        }
    }
    _NewUser.erase(oldNickname);
    _NewUser.erase(newNickname);
    _NewUser.insert(std::make_pair(newNickname, fd));
    // _NewUser[newNickname] = fd;
    // user->setNickname(newNickname);
}

// Making, running the server: excepting messages, users and etc

void    Server::InitTheServer()
{
    int opt = 1;

    _FileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (_FileDescriptor == -1)
    {
        std::cout<<"Error: Socket failed!"<<std::endl;
    }

    if (setsockopt(_FileDescriptor, SOL_SOCKET,SO_REUSEADDR, &opt, sizeof(opt)))
    {
        std::cout<<"Error: Setsockopt failed!"<<std::endl;
    }
    memset(&_Address, 0, sizeof(_Address));
    _Address.sin_family = AF_INET;
    _Address.sin_addr.s_addr = INADDR_ANY;
    _Address.sin_port = htons(_Port);

    if (bind(_FileDescriptor, (struct sockaddr*)&_Address, sizeof(_Address)) < 0)
    {
        std::cout<<"Error: Bind failed!"<<std::endl;
    }
    if (listen(_FileDescriptor, 100) < 0)
    {
        std::cout<<"Error: Listening failed!"<<std::endl;
    }
    fcntl(_FileDescriptor, F_SETFL, O_NONBLOCK);
}

void    Server::RunTheServer()
{
    int     _result, nfds = _FileDescriptor;
    fd_set  rd, wr, er;
    timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = 300000;
    FD_ZERO(&rd);
    FD_ZERO(&wr);
    FD_ZERO(&er);
    while(1)
    {
        if (_User.size())
        {
            for (iterator it = _User.begin(); it != _User.end(); ++it)
                FD_SET(it->first, &rd);
            nfds = std::max(nfds, _User.rbegin()->first);
        }

        _result = select(nfds + 1, &rd, &wr, &er, &tv);
        if (_result == -1)
        {
            std::cout << "\33[1;31mError: Select failed!\33[1;31m" << std::endl;
            exit(1);
        }
        else if (_result)
        {
            for (iterator it = _User.begin(); it != _User.end(); ++it)
            {
                if (FD_ISSET(it->first, &wr))
                {
                    FD_CLR(it->first, &wr);
                    while (!(it->second->_Buffer).empty())
                        _Commands->ToUse(it->second);
                    it->second->_Buffer.clear();
                    if ( it->second->_Quit) {
                        DeleteUser(it);
                        break ;
                    }
                }
                else if (FD_ISSET(it->first, &rd))
                {
                    FD_CLR(it->first, &rd);
                    if (!TheBuffer(it))
                        break ;
                    FD_SET(it->first, &wr);
                }
            }
        }
        else
            NewUser();
    }
}

bool    Server::TheBuffer(iterator &it)
{
    char    buffer[1024];
    int     value;

    while ((memset(buffer, 0, 1024), value = recv(it->first, buffer, 1024, 0)) != -1)
    {
        if (value == 0)
        {
            DeleteUser(it);
            return value;
        }
        it->second->_Buffer.append(buffer);
    }
    return value;
}


void Server::NewUser()
{
    sockaddr_in _ClientAddress;
    socklen_t _AddLen = sizeof(_ClientAddress);
    //memset(&_Address, 0, _ClientAddress);
    // Accepts a new connection to our server
    int _Socket = accept(_FileDescriptor, (struct sockaddr *)&_ClientAddress, &_AddLen);
    if (_Socket == -1)
    {
        //std::cout << "Error: Can't accept a new connection!" << std::endl;
        return;
    }
    fcntl(_Socket, F_SETFL, O_NONBLOCK);

    // Getting the hostname and adding a new user
    char hostname[NI_MAXHOST];                                                                                              // NI_MAXHOST: maximum of the hostname
    getnameinfo((struct sockaddr *)&_ClientAddress, sizeof(_ClientAddress), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV); // NI_NUMERICSERV: the port is numeric
    User *_NewUser = new User(_Socket, hostname);
    _User.insert(std::make_pair(_Socket, _NewUser));
    std::cout << "\x1b[32mNew connection: \x1b[32m" << _NewUser->getMessage() << std::endl;
    std::cout << "\x1b[32mUsers' connected: \x1b[32m" << _User.size() << std::endl;
}

void    Server::DeleteUser(iterator &it)
{
    std::cout << "\x1b[32mUser disconnected: \x1b[32m" << it->second->getMessage() << std::endl;

    // user leaves the channel: add a function in User class
    it->second->LeaveTheChannel(0);
    close(it->first);
    _NewUser.erase(it->second->getNickname());
    delete it->second;
    _User.erase(it);
    std::cout << "Users' connection: " << _User.size() << std::endl;
}