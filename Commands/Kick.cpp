// #include "Commands.hpp"

// void Commands::Kick(User *user, std::string const &reason)
// {
//     std::vector<User *>::iterator tmp;
//     for (std::vector<User *>::iterator it = _Users.begin(); it != _Users.end(); it++)
//     {
//         (*it)->SendMsg(RPL_KICK(user->getMessage(), _name, user->getNickname(), reason));
//         if (*it == user)
//             tmp = it;
//     }
//     _Users.erase(tmp);
// }