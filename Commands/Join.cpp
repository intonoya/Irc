#include "Commands.hpp"

void Commands::Join(User *user, std::vector<std::string> obj)
{
    if (obj.empty())
    {
        user->ReplyMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "JOIN"));
        return ;
    }
    if (obj.size() == 1 && obj[0] == "0")
    {
        user->LeaveTheChannel(0);
        return ;
    }

    std::string channelName = obj[0];
    std::string channelPass = (obj.size() == 2) ? obj[1] : "";

    if (channelName[0] != '#' && channelName[0] != '&')
    {
        user->ReplyMsg(ERR_BADCHANMASK(user->getNickname(), channelName));
        return ;
    }
    Channel *channel = _Server->getChannel(channelName);
    if (channel == NULL)
    {
        channel = new Channel(channelName, channelPass, user);
        _Server->AddChannel(channelName, channelPass);
    }
    else
    {
        if (channel->getPass() != channelPass)
        {
            user->ReplyMsg(ERR_BADCHANNELKEY(user->getNickname(), channelName));
            return ;
        }
    }
    user->JoinTheChannel(channel);
    // there must be message to all users in the channel that user joined
}