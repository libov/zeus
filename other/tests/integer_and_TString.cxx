#include <stdio.h>
#include <stdlib.h>
int integer_and_TString()
{

		TString 	ab="aaa";
		Int_t 	aab=1;
		//cout<<itoa(aab)<<endl;

		//char aaa[10]="aakl";
		char aaa[10];
		itoa(aab, aaa,10); // does not work
		//cout<<ab+aaa<<endl;

		return 0;
}