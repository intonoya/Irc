#include "Commands.hpp"

void Commands::Invite(User *user, std::vector<std::string> obj)
{
    if (obj.size() < 2)
    {
        user->ReplyMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "INVITE"));
        return ;
    }
    user->ReplyMsg(RPL_INVITING(user->getUserName(), user->getNickname(), obj[0]));
    return ;
}
