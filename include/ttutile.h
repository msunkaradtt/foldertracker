#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class ttutile
{
    public:
    ttutile();
    ~ttutile();
    void tokenize(std::string const &str, const char delim, std::vector<std::string> &out);
};
