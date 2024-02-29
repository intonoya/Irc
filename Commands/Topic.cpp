#include "Commands.hpp"

void Commands::Topic(User *user, std::vector<std::string> obj)
{
    if (obj.size() < 1)
    {
        user->SendMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "TOPIC"));
        return ;
    }
    Channel *channel = _Server->getChannel(obj[0]);
    if (channel == NULL)
    {
        user->SendMsg(ERR_NOSUCHCHANNEL(user->getNickname(), obj[0]));
        return ;
    }
    if (channel->getUser(user->getNickname()) == NULL)
    {
        user->SendMsg(ERR_NOTONCHANNEL(user->getNickname(), obj[0]));
        return ;
    }
    if (!channel->isAdmin(user) && !channel->isOperator(user))
    {
        user->SendMsg(ERR_CHANOPRIVSNEEDED(user->getNickname(), channel->getName()));
        return ;
    }
    if (channel->isOperator(user) && !channel->isTopicOperators())
    {
        user->SendMsg(RPL_NOTOPIC(user->getNickname(), channel->getName()));
        return ;
    }
    std::string topic = obj[1];
    for (size_t i = 2; i < obj.size(); i++)
        topic += " " + obj[i];
    channel->setTopic(topic);
    user->SendMsg(RPL_TOPIC(user->getNickname(), channel->getName(), channel->getTopic()));
}
