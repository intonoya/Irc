#include "Server.hpp"

Server::Server(int port, std::string const &psw) : _Psw(psw)
{
    if (port <= 65535)
    {
        _Port = port;
    }
}

Server::~Server()
{
    for (std::map<int, User *>::iterator it = _User.begin(); it != _User.end(); ++it)
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
    Channel *newChannel = new Channel(name, psw, NULL);

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
        for (std::map<int, User *>::iterator it = _User.begin(); it != _User.end(); ++it)
        {
            if (it->second != user)
                it->second->SendMsg(":" + oldNickname + " NICK " + newNickname);
        }
    }
    _NewUser.erase(oldNickname);
    _NewUser.erase(newNickname);
    _NewUser[newNickname] = fd;
    user->setNickname(newNickname);
}

// Making, running the server: excepting messages, users and etc

void Server::RunTheServer()
{
    int result;
    int fds = _FileDescriptor;
    fd_set read, write, error;
    timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = 300000;
    FD_ZERO(&read);
    FD_ZERO(&write);
    FD_ZERO(&error);

    while (true)
    {
        if (_User.size())
        {
            for (std::map<int, User *>::iterator it = _User.begin(); it != _User.end(); ++it)
            {
                FD_SET(it->first, &read);
            }
            fds = std::max(fds, _User.rbegin()->first);
        }
        result = select(fds + 1, &read, &write, &error, &tv);
        if (result == -1)
        {
            std::cout << "\33[1;31mError: Select failed!\33[1;31m" << std::endl;
            exit(1);
        }
        else if (result)
        {
            for (std::map<int, User *>::iterator it = _User.begin(); it != _User.end(); ++it)
            {
                if (FD_ISSET(it->first, &write))
                {
                    FD_CLR(it->first, &write);
                    while (!(it->second->_Buffer).empty())
                    {
                        _Commands->ToUse(it->second); 
                        // send the data to the user/s;
                    }
                    it->second->_Buffer.clear();
                    if (it->second->_Quit)
                    {
                        DeleteUser(it); // delete the user;
                        break;
                    }
                }
                else if (FD_ISSET(it->first, &read))
                {
                    FD_CLR(it->first, &read);
                    if(!TheBuffer(it))
                        break;
                    FD_SET(it->first, &write);
                }
            }
        }
        else
            NewUser();
        // FD_ZERO(&read);
        // FD_ZERO(&write);
        // FD_ZERO(&error);
    }
}

bool    Server::TheBuffer(std::map<int, User*>::iterator &it)
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

    // Accepts a new connection to our server
    int _Socket = accept(_FileDescriptor, (struct sockaddr *)&_ClientAddress, &_AddLen);
    if (_Socket == -1)
    {
        std::cout << "Error: Can't accept a new connection!" << std::endl;
        return;
    }
    fcntl(_Socket, F_SETFL, O_NONBLOCK);

    // Getting the hostname and adding a new user
    char hostname[NI_MAXHOST];                                                                                              // NI_MAXHOST: maximum of the hostname
    getnameinfo((struct sockaddr *)&_ClientAddress, sizeof(_ClientAddress), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV); // NI_NUMERICSERV: the port is numeric
    User *_NewUser = new User(_Socket, hostname, 0, 0);
    _User.insert(std::make_pair(_Socket, _NewUser));
    std::cout << "New connection: " << _NewUser->getMessage() << std::endl;
    std::cout << "Users' connection: " << _User.size() << std::endl;
}

void Server::DeleteUser(std::map<int, User*>::iterator &it)
{
    std::cout << "User disconnected: " << it->second->getMessage() << std::endl;

    it->second->LeaveUser(0); // user leaves the channel

    close(it->first);
    _NewUser.erase(it->second->getNickname());
    delete it->second;
    _User.erase(it);
    std::cout << "Users' connection: " << _User.size() << std::endl;
}