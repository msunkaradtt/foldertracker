#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>
#include <fstream>

#include "json.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;
class ttutile
{
    private:
    json jsonData;
    public:
    ttutile();
    ~ttutile();
    void tokenize(std::string const &str, const char delim, std::vector<std::string> &out);
    void savejson(std::map<std::string, std::string> &mapData);
    void readjson(std::map<std::string, std::string> &mapData);
    private:
    void writejson(std::map<std::string, std::string> &mapData, fs::path filePath);
};
