#ifndef BOT_HPP
#define BOT_HPP

# include <sstream>
# include <iostream>
# include <fstream>
# include <string>
# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <netdb.h>
# include <sys/uio.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <vector>


class Bot
{
    private:
        std::string _Host;
        int _Port;
        std::string _Psw;
        std::string _Nick;
        std::string _BUser;
        
        int _Socket;
        struct sockaddr_in _Address;

        int _BytesWritten;
        int _BytesRead;

        struct timeval _Start;
        struct timeval _End;
    
    public:
    
        Bot(std::string host, int port, std::string psw, std::string nick);
        ~Bot();

        int ConnectTheBot();
        int InitTheBot();
        void RunTheBot();
        void SendMsg(std::string const &msg);
        int Handle(std::string msg);
        std::string Parsing(std::string &data, std::string *msg);

        std::string ltrim(const std::string &s, const std::string &trimed);
        std::string rtrim(const std::string &s, const std::string &trimed);
        std::string trim(const std::string &s, const std::string &trimed);
        std::string ToString(int num);
        

        void Transfer(std::vector<std::string> obj);
        std::string Help();
        std::string Hello();
        std::string PythonTheCat();

};   

#endif