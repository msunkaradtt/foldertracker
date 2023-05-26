#include "winfiledialog.h"
#include "ttutile.h"
#include "folderwatcher.h"

#include <iostream>
#include <map>
#include <thread>
#include <chrono>

/*
Global Variables
*/
const char DELIM = '\\';

/*
UI Functions
*/
bool selectSelection(int selection);
void printTrackedFolders();
/*
App Functions
*/
void addFile();
void startTracking();

int main(){

    int selection;
    do{
        std::cout << "**********************************\n";
        std::cout << "DTT Folder Time Tracker (FTT)\n";
        std::cout << "**********************************\n";
        std::cout << "1 : 'Start Tracking'\n";
        std::cout << "2 : 'Add Folder For Tracking'\n";
        std::cout << "3 : 'Get Tracked Folders'\n";
        std::cout << "4 : 'Quit'\n";
        std::cout << "**********************************\n";
        std::cout << "Enter your choice:\n";
        std::cin >> selection;
    }while(!selectSelection(selection));

    return 0;
}

bool selectSelection(int selection){
    switch (selection)
    {
    case 1:
    startTracking();
    return false;
    break;
    case 2:
    addFile();
    return false;
    break;
    case 3:
    printTrackedFolders();
    return false;
    break;
    case 4:
    std::cout << "Quit" << '\n';
    return true;
    break;
    default:
    std::cout << "Selected option not accepted " << selection << '\n';
    return false;
    break;
    }
}

void printTrackedFolders(){
    ttutile myUtile;
    std::map<std::string, std::string> folderMapOut;
    myUtile.readjson(folderMapOut);

    std::cout << "The Following Folders Are Tracked" << '\n';
    for(auto& pair : folderMapOut){
        std::cout << "--------------------------------------" << '\n';
        std::cout << pair.second << '\n';
        std::cout << "--------------------------------------" << '\n';
    }
}

void startTracking(){

    ttutile myUtile;
    std::map<std::string, std::string> folderMapOut;
    myUtile.readjson(folderMapOut);

    std::vector<FolderWatcher> trackerClass;
    for(auto &pair : folderMapOut){
        FolderWatcher folderW {pair.second};
        trackerClass.push_back(folderW);
    }

    bool running = true;
    while(running){
        for(auto &ele : trackerClass){
            std::this_thread::sleep_for(std::chrono::microseconds(1000));
            ele.check();
        }
    }
}

void addFile(){
    winfiledialog myDialog;
    ttutile myUtile;

    char folderPath[MAX_PATH];
    myDialog.open(folderPath);

    std::string folderPathstr(folderPath);

    std::vector<std::string> out;
    myUtile.tokenize(folderPathstr, DELIM, out);

    std::map<std::string, std::string> folderMapIn;

    std::string folderName = out.back();

    folderMapIn[folderName] = folderPathstr;

    myUtile.savejson(folderMapIn);
}

