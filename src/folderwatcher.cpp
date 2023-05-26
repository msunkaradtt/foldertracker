#include "folderwatcher.h"

FolderWatcher::FolderWatcher(std::string path_to_watch, std::chrono::duration<int, std::milli> delay){
    this->path_to_watch = path_to_watch;
    this->delay = delay;
    for(auto &file : std::filesystem::recursive_directory_iterator(path_to_watch)){
        this->paths_[file.path().string()] = std::filesystem::last_write_time(file);
    }
}

void FolderWatcher::start(){
    std::this_thread::sleep_for(this->delay);

    auto it = this->paths_.begin();
    while(it != this->paths_.end()){
        if(!std::filesystem::exists(it->first)){
            std::cout << "File erased: " << this->path_to_watch << '\n';
            it = paths_.erase(it);
        } else {
            it++;
        }
    }

    for(auto &file : std::filesystem::recursive_directory_iterator(this->path_to_watch)) {
        auto current_file_last_write_time = std::filesystem::last_write_time(file);

        if(!this->contains(file.path().string())){
            this->paths_[file.path().string()] = current_file_last_write_time;
            std::cout << "File created: " << this->path_to_watch << '\n';
        } else {
            if(this->paths_[file.path().string()] != current_file_last_write_time){
                this->paths_[file.path().string()] = current_file_last_write_time;
                std::cout << "File modified: " << this->path_to_watch << '\n';
            }
        }
    }
}

bool FolderWatcher::contains(const std::string &key){
    auto el = this->paths_.find(key);
    return el != this->paths_.end();
}