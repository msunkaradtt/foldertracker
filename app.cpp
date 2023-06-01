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

struct folderTime
{
    int sec;
    int min;
    int hr;
};


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
    std::map<std::string, folderTime> folderTimeOut;
    for(auto &pair : folderMapOut){
        FolderWatcher folderW {pair.second, pair.first};
        trackerClass.push_back(folderW);
        folderTime tim;
        tim.sec = 0;
        tim.min = 0;
        tim.hr = 0;
        folderTimeOut[pair.first] = tim;
    }

    bool running = true;
    while(running){
        for(auto &ele : trackerClass){
            std::this_thread::sleep_for(std::chrono::microseconds(5000));
            folderTime checkTim = folderTimeOut[ele.folderName];
            ele.check(checkTim.hr, checkTim.min, checkTim.sec, ele.folderName);

            folderTimeOut[ele.folderName].hr = checkTim.hr;
            folderTimeOut[ele.folderName].min = checkTim.min;
            folderTimeOut[ele.folderName].sec = checkTim.sec;

            /*std::system("clear");
            std::cout << ele.folderName << " - "
            << folderTimeOut[ele.folderName].hr << ":" <<
            folderTimeOut[ele.folderName].min << ":" <<
            folderTimeOut[ele.folderName].sec << '\n';*/
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

