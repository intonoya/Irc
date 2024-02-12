#include "Commands.hpp"

void Commands::Invite(User *user, std::vector<std::string> obj)
{
    if (obj.size() < 2)
    {
        user->ReplyMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "INVITE"));
        return ;
    }
    
    std::string userToInvite = obj[0];
    std::string channelName = obj[1];

    // uberi eto potom
    if (!_Server)
    {
        user->ReplyMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "INVITE"));
        return ;
    }
    //

    User *userToInvitePtr = _Server->getUser(userToInvite);
    Channel *channel = _Server->getChannel(channelName);
    
    if (!userToInvitePtr)
    {
        user->ReplyMsg(ERR_NOSUCHNICK(user->getNickname(), userToInvite));
        return ;
    }
    if (!channel)
    {
        user->ReplyMsg(ERR_NOSUCHCHANNEL(user->getNickname(), channelName));
        return ;
    }
    if (!channel->isExist(user))
    {
        user->ReplyMsg(ERR_NOTONCHANNEL(user->getNickname(), channelName));
        return ;
    }
    if (!channel->isAdmin(user))
    {
        user->ReplyMsg(ERR_CHANOPRIVSNEEDED(user->getNickname(), channelName));
        return ;
    }
    if (channel->isExist(userToInvitePtr))
    {
        user->ReplyMsg(ERR_USERONCHANNEL(user->getNickname(), userToInvite, channelName));
        return ;
    }

    userToInvitePtr->ReplyMsg(RPL_INVITING(user->getUserName(), user->getNickname(), channelName));
    user->ReplyMsg(RPL_INVITING(user->getUserName(), user->getNickname(), channelName));
    
    return ;
}