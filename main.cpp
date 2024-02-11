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
        std::cout<<"\33[1;31mErrror: Argument error!\33[1;0m"<<std::endl;

    User *user = new User(1, "testHost", "testNick", "testUser");
    Channel *channel = new Channel("testChannel", "testPass", user);
    //Commands *invite = new Commands();

    channel->join(user);
    channel->kick(user, "test");

    std::vector<std::string> obj;
    obj.push_back("test1");
    obj.push_back("test2");
    // obj.push_back("test");
    //invite->Invite(user, obj);

    delete user;
    delete channel;

    return 0;
}