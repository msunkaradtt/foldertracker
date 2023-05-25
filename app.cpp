#include "winfiledialog.h"
#include "ttutile.h"

#include <iostream>
#include <map>

/*
Global Variables
*/
const char DELIM = '\\';

int main(){
    winfiledialog myDialog;
    ttutile myUtile;

    char folderPath[MAX_PATH];
    myDialog.open(folderPath);

    std::string folderPathstr(folderPath);

    std::vector<std::string> out;
    myUtile.tokenize(folderPathstr, DELIM, out);

    std::map<std::string, std::string> folderMap;
    std::string folderName = out.back();

    folderMap[folderName] = folderPathstr;

    myUtile.savejson(folderMap);

    return 0;
}
