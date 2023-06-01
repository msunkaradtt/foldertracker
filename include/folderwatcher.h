#pragma once

#include <filesystem>
#include <unordered_map>
#include <iostream>

enum class FileStatus {created, modified, erased};

class FolderWatcher{
    public:
    std::string path_to_watch;
    std::string folderName;

    FolderWatcher(std::string path_to_watch, std::string folderName);
    void check(int &hour, int &min, int &sec, std::string &folderName);

    private:
    std::unordered_map<std::string, std::filesystem::file_time_type> paths_;
    bool contains(const std::string &key);
    void timer(int &hour, int &min, int &sec);
};