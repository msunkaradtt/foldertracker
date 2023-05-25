#include "winfiledialog.h"

#include <windows.h>
#include <shlobj.h>
#include <iostream>

winfiledialog::winfiledialog(){}
winfiledialog::~winfiledialog(){}

void winfiledialog::open(char* outStr){
    BROWSEINFOA bi = {};
    bi.hwndOwner = NULL;
    bi.lpszTitle = "DTT Folder Tracker: Select Folder";
    bi.ulFlags = BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS;

    LPITEMIDLIST pidl = SHBrowseForFolderA(&bi);
    if (pidl != NULL) {
        if (SHGetPathFromIDListA(pidl, outStr)) {
        } else {
            printf("Error getting folder path.\n");
        }

        CoTaskMemFree(pidl);
    } else {
        DWORD error = CommDlgExtendedError();
        if (error != 0) {
            printf("Error: %lu\n", error);
        } else {
            printf("Folder selection canceled by the user.\n");
        }
    }
}