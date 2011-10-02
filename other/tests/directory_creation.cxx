#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <fcntl.h>
#include <iostream>
#include <TString.h>
#include <TROOT.h>
int directory_creation()
{
		char  s[256]="bla";
		mkdir(s);
		return 0;
}