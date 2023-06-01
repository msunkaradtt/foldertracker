#include "folderwatcher.h"

void displayTime(std::string &folderName, int &h, int &m, int &s) {
    system("clear");
    std::cout << folderName << " - " << h << ":"
    << m << ":"
    << s << '\n';
}

FolderWatcher::FolderWatcher(std::string path_to_watch, std::string folderName){ //std::chrono::duration<int, std::milli> delay
    this->path_to_watch = path_to_watch;
    this->folderName = folderName;

    for(auto &file : std::filesystem::recursive_directory_iterator(path_to_watch)){
        this->paths_[file.path().string()] = std::filesystem::last_write_time(file);
    }
}

void FolderWatcher::check(int &hour, int &min, int &sec, std::string &folderName){

    auto it = this->paths_.begin();
    while(it != this->paths_.end()){
        if(!std::filesystem::exists(it->first)){
            //std::cout << "File erased: " << it->first << '\n';
            this->timer(hour, min, sec);
            it = paths_.erase(it);
            displayTime(folderName, hour, min, sec);
        } else {
            it++;
        }
    }

    for(auto &file : std::filesystem::recursive_directory_iterator(this->path_to_watch)) {
        if(std::filesystem::exists(file)){
            auto current_file_last_write_time = std::filesystem::last_write_time(file);

            if(!this->contains(file.path().string())){
                this->paths_[file.path().string()] = current_file_last_write_time;
                this->timer(hour, min, sec);
                displayTime(folderName, hour, min, sec);
                //std::cout << "File created: " << file.path().string() << '\n';
            }
            else {
                if(this->paths_[file.path().string()] != current_file_last_write_time){
                    this->paths_[file.path().string()] = current_file_last_write_time;
                    this->timer(hour, min, sec);
                    displayTime(folderName, hour, min, sec);
                    //std::cout << "File modified: " << file.path().string() << '\n';
                }
            }
        }
    }
}

bool FolderWatcher::contains(const std::string &key){
    auto el = this->paths_.find(key);
    return el != this->paths_.end();
}

void FolderWatcher::timer(int &hour, int &min, int &sec){
    sec+=5;

    if(sec > 59){
        min++;
        sec = 0;
    }

    if(min > 59){
        hour++;
        sec = 0;
        min = 0;
    }
}