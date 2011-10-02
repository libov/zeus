#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <TString.h>
#include <TROOT.h>
using namespace std;

TString MakeDirectory (TString PathToDir)
{
    struct stat buffer;
    Int_t CurrentDirStatus, NewDirStatus;
    CurrentDirStatus = stat (PathToDir, &buffer);

    TString path;
    if (CurrentDirStatus != 0)
    {
        path = PathToDir;
        //NewDirStatus = mkdir (path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        cout << "Current status of the directory = " << CurrentDirStatus << endl;
        cout << "Folder with this name is creating" << endl;
    }
    else
    {
        path = PathToDir + "_1";
        NewDirStatus = mkdir (path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        cout << "Current status of the directory = " << CurrentDirStatus << endl;
        cout << "Folder with this name already exists" << endl;
    }
return path;
}

int main ()
{
TString PathToDir = "analysis";
TString RealPath = MakeDirectory (PathToDir);
cout << "Real path to new folder: \"" << RealPath << "\"" << endl;
return 0;
}
