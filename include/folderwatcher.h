#pragma once

#include <filesystem>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <string>
#include <functional>
#include <iostream>

enum class FileStatus {created, modified, erased};

class FolderWatcher{
    public:
    std::string path_to_watch;
    std::chrono::duration<int, std::milli> delay;

    FolderWatcher(std::string path_to_watch, std::chrono::duration<int, std::milli> delay);
    void start();

    private:
    std::unordered_map<std::string, std::filesystem::file_time_type> paths_;
    bool contains(const std::string &key);
};