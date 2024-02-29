#include "Commands.hpp"

void Commands::PrivMsg(User *user, std::vector<std::string> obj)
{
    if (obj.empty())
    {
        user->ReplyMsg(ERR_NOTEXTTOSEND(user->getNickname()));
        return;
    }
    std::string target = obj[0];
    std::string message = obj[1].substr(obj[1][0] == ':' ? 1 : 0);
    for (size_t i = 2; i < obj.size(); ++i)
        message.append(" " + obj[i]);
    if (target[0] == '#' || target[0] == '&')
    {
        Channel *channel = _Server->getChannel(target);
        if (!channel)
        {
            user->ReplyMsg(ERR_NOSUCHNICK(user->getNickname(), target));
            return;
        }
        if (!channel->isExist(user))
        {
            user->ReplyMsg(ERR_CANNOTSENDTOCHAN(user->getNickname(), target));
            return;
        }
        channel->sendMsg(user, RPL_MSG(user->getMessage(), "PRIVMSG", target, message));
        return;
    }

    User *new_user = _Server->getUser(target);
    if (!new_user)
    {
        user->ReplyMsg(ERR_NOSUCHNICK(user->getNickname(), target));
        return;
    }
    new_user->SendMsg(RPL_MSG(user->getMessage(), "PRIVMSG", target, message));
}