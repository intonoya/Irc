#include "Parsing.hpp"

void Parsing:: IsValidNumeric(const std::string &str) 
{
        if (str.empty()) 
        {
            throw std::runtime_error("\33[1;31mError: Empty string!\33[1;31m");
        }
        size_t i = 0;
        if (str[i] == '+') 
            i++;
        for (; i < str.size(); ++i) 
        {
            if (!isdigit(str[i])) 
            {
                throw std::runtime_error("\33[1;31mError: Not a valid numeric value\33[0m");
            }
        }
        int value = atoi(str.c_str());
        if (value < 1 || value > 65535) 
        {
            throw std::out_of_range("\33[1;31mError: Value out of range, only from 0 to 65535!\33[1;31m");
        }
    }

int Parsing::ItExists(User *user)
{
    for(std::vector<User *>::iterator it = _User.begin(); it != _User.end(); ++it)
    {
        if(*it == user)
            return 1;
        return 0;
    }
    return 0;
}

