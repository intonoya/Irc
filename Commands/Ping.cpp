#include "Commands.hpp"

void Commands::Ping(User *user, std::vector<std::string> obj)
{
    if (obj.empty())
    {
        user->ReplyMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "PING"));
        return;
    }
    user->SendMsg(RPL_PING(user->getMessage(), obj[0]));
}