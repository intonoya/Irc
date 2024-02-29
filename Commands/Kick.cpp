#include "Commands.hpp"

void Commands::Kick(User *user, std::vector<std::string> obj)
{
    if (obj.empty() || obj.size() < 3)
    {
        user->ReplyMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "KICK"));
        return ;
    }

    std::string channelName = obj[0];
    std::string nickname = obj[1];
    std::string reason = obj[2];

    if (reason[0] == ':')
    reason.erase(0, 1);

    for (size_t i = 3; i < obj.size(); i++)
        reason += " " + obj[i];

    if (channelName[0] != '#' && channelName[0] != '&')
    {
        user->ReplyMsg(ERR_NOSUCHCHANNEL(user->getNickname(), channelName));
        return ;
    }

    Channel *channel = _Server->getChannel(channelName);
    if (channel == NULL)
    {
        user->ReplyMsg(ERR_NOSUCHCHANNEL(user->getNickname(), channelName));
        return ;
    }

    User *target = channel->getUser(nickname);
    if (target == NULL)
    {
        user->ReplyMsg(ERR_NOSUCHNICK(user->getNickname(), nickname));
        return ;
    }

    if (!channel->isAdmin(user) && !channel->isOperator(user))
    {
        user->ReplyMsg(ERR_CHANOPRIVSNEEDED(user->getNickname(), channelName));
        return ;
    }

    channel->sendMsg(user, ":" + user->getNickname() + " KICK " + channelName + " " + nickname + " :" + reason);
    channel->unsetInvite(target);
    channel->kick(target, reason);
    target->LeaveTheChannel(channel);
}