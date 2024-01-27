#include <iostream>
#include <string>
#include <map>
#include <cstdio>
#include <cstdlib>
#include "Parsing.hpp"


void Parsing::IsValidNumeric(std::string const &str) 
{
     for (size_t i = 0; i < str.size(); ++i) 
     {
        char c = str[i];
        if (!(isdigit(c) || (c == '+' && i == 0)))
            throw std::runtime_error("\33[1;31mError: Only digits allowed\33[1;31m");
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
}