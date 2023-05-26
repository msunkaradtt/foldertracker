#include "winfiledialog.h"
#include "ttutile.h"
#include "folderwatcher.h"

#include <iostream>
#include <map>

/*
Global Variables
*/
const char DELIM = '\\';

/*
UI Functions
*/
void selectSelection(int selection);
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
    }while(selection > 4 || selection < 1);

    selectSelection(selection);

    /*std::map<std::string, std::string> folderMapOut;
    myUtile.readjson(folderMapOut);*/

    return 0;
}

void selectSelection(int selection){
    switch (selection)
    {
    case 1:
    startTracking();
    break;
    case 2:
    addFile();
    break;
    case 3:
    printTrackedFolders();
    break;
    case 4:
    std::cout << "Quit" << selection << '\n';
    break;
    default:
    std::cout << "Selected option not accepted" << selection << '\n';
    break;
    }
}

void printTrackedFolders(){
    ttutile myUtile;
    std::map<std::string, std::string> folderMapOut;
    myUtile.readjson(folderMapOut);
    for(auto& pair : folderMapOut){
        std::cout << "The Following Folders Are Tracked" << '\n';
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
        FolderWatcher folderW {pair.second, std::chrono::milliseconds(1000)};
        trackerClass.push_back(folderW);
    }

    bool running = true;
    while(running){
        for(auto &ele : trackerClass){
            ele.start();
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

