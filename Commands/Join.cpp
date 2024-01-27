#include "Commands.hpp"

void Commands::Join(User *user, std::vector<std::string> obj)
{
    if (obj.empty())
    {
        user->ReplyMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "JOIN"));
        return;
    }
    if (arg.size() == 1 && arg[0] == "0")
    {
        user->LeaveUser(0); //recheck this part
        return;
    }
    std::string channel = arg[0];
    //std::string pass = arg.size() > 1 ? arg[1] : "";
    //std::map<std::string, std::string> ch = str_map(channel, pass);
    for (std::map<std::string, std::string>::iterator it = ch.begin(); it != ch.end(); ++it) //the ch part
    {
        channel = it->first;
        pass = it->second;
        if (channel[0] != '#' && channel[0] != '&')
        {
            user->reply(ERR_BADCHANMASK(user->getNickname(), channel));
            return;
        }
        Channel *new_channel = _server->getChannel(channel);
        if (!new_channel)
            new_channel = _server->AddChannel(channel, pass); // add AddChannel to the Server.hpp
        else if (new_channel->SizeOfTheUsers() == 0) //size of the users write the function
            new_channel->setPass(pass);
        if (new_channel->getPass() != "" && new_channel->get_pass() != pass) //write the function
        {
            user->ReplyMsg(ERR_BADCHANNELKEY(user->getNickname(), channel));
            return;
        }
        user->JoinTheChannel(new_channel);
    }
}