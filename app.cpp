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

    std::map<std::string, std::string> folderMapIn;

    std::string folderName = out.back();
    folderMapIn[folderName] = folderPathstr;

    myUtile.savejson(folderMapIn);

    std::map<std::string, std::string> folderMapOut;
    myUtile.readjson(folderMapOut);

    return 0;
}
