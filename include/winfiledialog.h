#pragma once

#include<windows.h>
#include<shlobj.h>


class winfiledialog
{
    private:
    public:
    winfiledialog();
    ~winfiledialog();
    void open(char* outStr);
};
