#include "Commands.hpp"

void Commands::Join(User *user, std::vector<std::string> obj)
{
    if (!user->getPass())
    {
        user->ReplyMsg(ERR_NOTREGISTERED(user->getNickname()));
        return ;
    }
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

    for (int i = 2; i < (int)obj.size(); i++)
        channelPass += " " + obj[i];

    if (channelName[0] != '#' && channelName[0] != '&')
    {
        user->ReplyMsg(ERR_BADCHANMASK(user->getNickname(), channelName));
        return ;
    }
    Channel *channel = _Server->getChannel(channelName);
    if (channel == NULL)
    {
        // channel = new Channel(channelName, channelPass, user);
        _Server->AddChannel(channelName, channelPass);
        channel = _Server->getChannel(channelName);
    }
    else
    {
        if (channel->isInviteOnly() && !channel->isInvite(user))
        {
            user->ReplyMsg(ERR_INVITEONLYCHAN(user->getNickname(), channelName));
            return ;
        }
        if (!channel->isInvite(user))
        {
            if (channel->getPass() != channelPass)
            {
                user->ReplyMsg(ERR_BADCHANNELKEY(user->getNickname(), channelName));
                return ;
            }
        }
        if (channel->getLimit() && (int)channel->getUsers().size() >= channel->getLimit())
        {
            user->ReplyMsg(ERR_CHANNELISFULL(user->getNickname(), channelName));
            return ;
        }
    }
    if (channel->isExist(user))
    {
        user->ReplyMsg(ERR_USERONCHANNEL(user->getNickname(), user->getNickname(), channelName));
        return ;
    }

    if (channel->getUsers().size() == 0)
        channel->setAdmin(user);

    user->JoinTheChannel(channel);

    user->SendMsg(":" + user->getNickname() + " JOIN " + channelName);

    if (channel->getUsers().size() == 1)
    {
        // new admin message
        user->SendMsg(":" + user->getNickname() + " MODE " + channelName + " +o " + user->getNickname());
    }

    std::vector<User *> users = channel->getUsers();
    for (std::vector<User *>::iterator it = users.begin(); it != users.end(); ++it)
    {
        if (*it == channel->getAdmin())
            user->SendMsg(RPL_NAMREPLY(user->getNickname(), channelName, "@", (*it)->getNickname()));
        else
            user->SendMsg(RPL_NAMREPLY(user->getNickname(), channelName, "", (*it)->getNickname()));
    }

    user->SendMsg(RPL_ENDOFNAMES(user->getNickname(), channelName));
    channel->sendMsg(user, ":" + user->getNickname() + " JOIN " + channelName);
    if (channel->getTopic() != "")
        user->SendMsg(RPL_TOPIC(user->getNickname(), channelName, channel->getTopic()));
    channel->unsetInvite(user);
}
