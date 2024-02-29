#include "Commands.hpp"

void Commands::UserCmd(User *user, std::vector<std::string> obj)
{
    if (obj.empty() || obj.size() < 4)
    {
        user->ReplyMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "USER"));
        return;
    }
    if (user->IsRegistered() || !user->getPass())
    {
        user->ReplyMsg(ERR_ALREADYREGISTERED(user->getNickname()));
        return;
    }
    std::string username = obj[0];
    std::string name = obj[3].substr(obj[3][0] == ':' ? 1 : 0);
    for (size_t i = 4; i < obj.size(); ++i)
        name.append(" " + obj[i]);
    user->Init(username, name);
    user->Registration();
}