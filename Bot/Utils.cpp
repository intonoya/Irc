#include "Bot.hpp"

std::string Bot::ltrim(const std::string &s, const std::string &trimed)
{
    size_t start = s.find_first_not_of(trimed);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string Bot::rtrim(const std::string &s, const std::string &trimed)
{
    size_t end = s.find_last_not_of(trimed);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string Bot::trim(const std::string &s, const std::string &trimed) 
{ 
    return rtrim(ltrim(s, trimed), trimed);
}

std::string Bot::ToString(int num)
{
    std::stringstream stream;
    std::string str;
    stream << num;
    stream >> str;
    return str;
}