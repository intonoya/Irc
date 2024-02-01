#include "Channel.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "./Commands/Commands.hpp"

int main(int argc, char **argv)
{
    try
    {
        Parsing::IsValidNumeric(argv[1]);
    }
    catch(const std::exception& e)
    {
        std::cout<<e.what()<<std::endl;
        return 1;
    }
    if(argc != 3)
        std::cout<<"\33[1;31mErrror: Argument error!\33[1;31m"<<std::endl;
    return 0;
}