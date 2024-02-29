#include "Commands.hpp"

void Commands::Part(User *user, std::vector<std::string> obj)
{
    if (obj.empty())
    {
        user->ReplyMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "PART"));
        return;
    }
    std::string channel = obj[0];
    Channel *newChannel = _Server->getChannel(channel);
    if (!newChannel)
    {
        user->ReplyMsg(ERR_NOSUCHCHANNEL(user->getNickname(), channel));
        return;
    }
    else if (!newChannel->isExist(user))
    {
        user->ReplyMsg(ERR_NOTONCHANNEL(user->getNickname(), channel));
        return;
    }
    newChannel->part(user);
    user->LeaveTheChannel(newChannel);
    newChannel->sendMsg(user, ":" + user->getNickname() + " PART " + channel);
    user->SendMsg(":" + user->getNickname() + " PART " + channel);
}