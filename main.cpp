#include "Channel.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "./Commands/Commands.hpp"

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        std::cout<<"\33[1;31mError: Argument error!\33[1;31m"<<std::endl;
        return 1;
    }
    
    try
    {
        Parsing::IsValidNumeric(argv[1]);
        if (!*argv[2])
            throw std::runtime_error("Error: Empty string!");
    }
    catch(const std::exception& e)
    {
        std::cout<<e.what()<<std::endl;
        return 2;
    }

    Server *server = new Server(atoi(argv[1]), argv[2]);
    
    delete server;

    return 0;
}