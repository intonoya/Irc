#include "Bot.hpp"

int main(int argc, char **argv)
{
    
    if (argc != 5 || !*argv[4])
    {
        std::cout<<"\33[1;31mError: Argument error!\33[1;31m"<<std::endl;
        return 1;
    }

    Bot *bot = new Bot(argv[1], std::atoi(argv[2]), argv[3], argv[4]);

    delete bot;

    return 0;
}