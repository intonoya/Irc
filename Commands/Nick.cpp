#include "Commands.hpp"

void Commands::Nick(User *user, std::vector<std::string> obj)
{
    if (user->IsRegistered())
    {
        user->ReplyMsg(ERR_ALREADYREGISTERED(user->getNickname()));
        return ;
    }
    if (obj.empty())
    {
        user->ReplyMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "NICK"));
        return;
    }
    if (!user->getPass())
    {
        user->ReplyMsg(ERR_ALREADYREGISTERED(user->getNickname()));
        return;
    }
    std::string nickname = obj[0];
    if (!Parsing::IsValidNick(nickname))
    {
        user->ReplyMsg(ERR_ERRONEUSNICKNAME(user->getNickname(), nickname));
        return;
    }
    User *new_user = _Server->getUser(nickname);
    if (new_user && new_user != user)
    {
        user->ReplyMsg(ERR_NICKNAMEINUSE(user->getNickname(), nickname));
        return;
    }
    _Server->setUser(user, nickname, user->getFd());
    user->setNickname(nickname);
    // if (user->IsRegistered())
    // {
    //     // std::cout << "NICK: " << user->getNickname() << std::endl;
    //     std::string old_nick = user->getNickname();
    //     user->setNickname(obj[0]);
    //     user->SendMsg(":" + old_nick + " NICK " + obj[0]);
    // }
    // else
    // {
    user->setNickname(obj[0]);
    user->Registration();
    // }
}