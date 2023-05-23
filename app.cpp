#include "winfiledialog.h"
#include "ttutile.h"
#include "json.hpp"

#include <iostream>
#include <map>
#include <filesystem>
#include <fstream>

using json = nlohmann::json;
namespace fs = std::filesystem;

int main(){
    winfiledialog myDialog;
    ttutile myUtile;

    char folderPath[MAX_PATH];
    myDialog.open(folderPath);

    std::string folderPathstr(folderPath);

    const char delim = '\\';

    std::vector<std::string> out;
    myUtile.tokenize(folderPathstr, delim, out);

    std::map<std::string, std::string> folderMap;
    std::string folderName = out.back();

    folderMap[folderName] = folderPathstr;

    json jsonData;

    for(const auto& pair : folderMap) {
        jsonData[pair.first] = pair.second;
    }

    fs::path cwd = fs::current_path() / "data";

    if(!fs::is_directory(cwd) || !fs::exists(cwd)){
        fs::create_directories(cwd);
    }

    std::string filePath = cwd.string() + "\\" + "folderPaths.json";

    std::ofstream file(filePath);
    if(file.is_open()){
        file << jsonData.dump(4);
        file.close();
        std::cout << "Saved data to path: " << filePath << '\n';
    } else {
        std::cout << "Failed to save data to path: " << filePath << '\n';
    }

    return 0;
}
