#include "Commands.hpp"

void Commands::Mode(User *user, std::vector<std::string> obj)
{
    if (obj.size() < 2 || obj[1] == user->getNickname())
        return;

    std::string channelName = obj[0];
    std::string mode = obj[1];
    std::string target = (obj.size() == 3) ? obj[2] : "";

    Channel *channel = _Server->getChannel(channelName);
    if (channel == NULL)
    {
        user->SendMsg(ERR_NOSUCHCHANNEL(user->getNickname(), channelName));
        return;
    }

    if (!channel->isAdmin(user) && !channel->isOperator(user))
    {
        user->SendMsg(ERR_CHANOPRIVSNEEDED(user->getNickname(), channelName));
        return;
    }

    channel->setMode(mode + target);
    channel->applyMode();
}

