#pragma once

#include <filesystem>
#include <unordered_map>
#include <iostream>

enum class FileStatus {created, modified, erased};

class FolderWatcher{
    public:
    std::string path_to_watch;

    FolderWatcher(std::string path_to_watch);
    void check();

    private:
    std::unordered_map<std::string, std::filesystem::file_time_type> paths_;
    bool contains(const std::string &key);
};