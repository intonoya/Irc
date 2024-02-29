#include "Commands.hpp"

void Commands::Pong(User *user, std::vector<std::string> obj)
{
    if (obj.empty())
    {
        user->ReplyMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "PONG"));
        return;
    }
    user->SendMsg(RPL_PING(user->getMessage(), obj[0]));
}