// #include "Commands.hpp"

// void Commands::Invite(User *user, std::vector<std::string> _invite)
// {
//     if (_invite.empty() || _invite.size() < 2)
//     {
//         user->ReplyMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "WHO"));
//         return;
//     }
//     std::string username = _invite[0];
//     User *_NewUser = _server->getUserName(username);
//     if (!_NewUser)
//     {
//         user->ReplyMsg(ERR_NOSUCHNICK(user->getNickname(), username));
//         return;
//     }
//     std::string channel = _invite[1];
//     Channel *_NChannel = _server->getChannel(channel);
//     if (!_NChannel)
//     {
//         user->ReplyMsg(ERR_NOSUCHNICK(user->getNickname(), channel));
//         return;
//     }
//     if (!_NChannel->ItExists(user))
//     {
//         user->ReplyMsg(ERR_NOSUCHCHANNEL(user->getNickname(), channel));
//         return;
//     }
//     if (_NChannel->ItExists(user))
//     {
//         user->ReplyMsg(ERR_USERONCHANNEL(user->getNickname(), username, channel));
//         return;
//     }
//     _NewUser->SendMsg(RPL_INVITE(user->getMessage(), username, channel));
//     user->ReplyMsg(RPL_INVITING(user->getNickname(), username, channel));
// }