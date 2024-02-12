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

    if (!channel->isAdmin(user))
    {
        user->ReplyMsg(ERR_CHANOPRIVSNEEDED(user->getNickname(), channelName));
        return ;
    }

    channel->kick(target, reason);
    target->LeaveTheChannel(channel);
    // there must be message to all users in the channel that user was kicked
}