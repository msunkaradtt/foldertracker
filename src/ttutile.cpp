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

void ttutile::savejson(std::map<std::string, std::string> &mapData){
    fs::path cwd = fs::current_path() / "data";

    if(!fs::is_directory(cwd) || !fs::exists(cwd)){
        fs::create_directories(cwd);
    }

    fs::path filePath = cwd / "folderPaths.json";
    std::map<std::string, std::string> tempMapData;
    if(fs::exists(filePath)){
        this->readjson(tempMapData);
        for(const auto& pair: mapData){
            if(tempMapData.count(pair.first)){
                std::cout << "The folder is already tracked: " << pair.first << " path: " << pair.second << '\n';
            } else{
                tempMapData[pair.first] = pair.second;
            }
        }
        if(!tempMapData.empty()){
            this->writejson(tempMapData, filePath);
        }
    } else {
        this->writejson(mapData, filePath);
    }
}

void ttutile::readjson(std::map<std::string, std::string> &mapData){
    fs::path cwd = fs::current_path() / "data";

    if(!fs::is_directory(cwd) || !fs::exists(cwd)){
        std::cerr << "Data Folder does not exist at: " << cwd.string() << '\n';
    }

    fs::path filePath = cwd / "folderPaths.json";
    if(!fs::exists(filePath)){
        std::cerr << "Data File does not exist at: " << filePath.string() << '\n';
    }

    std::ifstream file(filePath.string());

    if(!file.is_open()){
        std::cerr << "Failed to open file." << '\n';
    }

    file >> this->jsonData;

    if(!this->jsonData.is_object()){
        std::cerr << "Invalid JSON format. Expected an object." << '\n';
    }

    for(auto it = this->jsonData.begin(); it != this->jsonData.end(); ++it){
        if(it.value().is_string()){
            mapData[it.key()] = it.value();
        }
    }
}

void ttutile::writejson(std::map<std::string, std::string> &mapData, fs::path filePath){
    for(const auto& pair : mapData){
        this->jsonData[pair.first] = pair.second;
    }

    std::ofstream file(filePath.string());
    if(file.is_open()){
        file << this->jsonData.dump(4);
        file.close();
    } else {
        std::cerr << "Failed to save data to path: " << filePath.string() << '\n';
    }
}