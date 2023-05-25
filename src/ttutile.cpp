#include <ttutile.h>

ttutile::ttutile(){}
ttutile::~ttutile(){}

void ttutile::tokenize(std::string const &str, const char delim, std::vector<std::string> &out){
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim))
    {
        out.push_back(s);
    }
}

void ttutile::savejson(std::map<std::string, std::string> mapData){
    for(const auto& pair : mapData){
        this->jsonData[pair.first] = pair.second;
    }
    fs::path cwd = fs::current_path() / "data";

    if(!fs::is_directory(cwd) || !fs::exists(cwd)){
        fs::create_directories(cwd);
    }

    std::string filePath = cwd.string() + "\\" + "folderPaths.json";

    std::ofstream file(filePath);
    if(file.is_open()){
        file << this->jsonData.dump(4);
        file.close();
        std::cout << "Saved data to path: " << filePath << '\n';
    } else {
        std::cout << "Failed to save data to path: " << filePath << '\n';
    }
}