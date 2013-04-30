// system headers
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

// ROOT headers
#include <TObjString.h>
#include <TObjArray.h>

// custom headers
#include <TCharmMeasurement.h>

TCharmMeasurement::TCharmMeasurement(TString name, TString name_for_legend, unsigned type):
fFilename(name),
fNpoints(0),
fNameForLegend(name_for_legend),
fFileType(type)
{
    read_data();
}

void TCharmMeasurement::read_data() {

    // open the file
    ifstream file(fFilename);
    if (file.good()) {
        cout << "\nINFO: opened " << fFilename << endl;
    } else {
        cout << "ERROR: could not open " << fFilename << endl;
        abort();
    }

    // extract data from the file
    string line;
    while ( file.good() ) {

        // read each line
        getline (file,line);
        TString line_str = line;

        // tokenize it, skip if empty
        TObjArray * tokens = line_str.Tokenize(" ");
        if (tokens -> IsEmpty()) continue;

        // extract data from tokens
        fQ2[fNpoints] = (((TObjString*) tokens->At(0)) -> GetString()).Atof();
        fX[fNpoints] = (((TObjString*) tokens->At(1)) -> GetString()).Atof();

        if (fFileType == 1) { //charm combination

            fValue[fNpoints] = (((TObjString*) tokens->At(3)) -> GetString()).Atof();
            fErrStat[fNpoints] = (((TObjString*) tokens->At(4)) -> GetString()).Atof();
            fErrTotalUp[fNpoints] = (((TObjString*) tokens->At(6)) -> GetString()).Atof();
            fErrTotalDown[fNpoints] = fErrTotalUp[fNpoints];

        } else if  (fFileType == 2) { // D+ and vertex

            fValue[fNpoints] = (((TObjString*) tokens->At(2)) -> GetString()).Atof();
            fErrStat[fNpoints] = (((TObjString*) tokens->At(3)) -> GetString()).Atof();
            fErrSystUp[fNpoints] = (((TObjString*) tokens->At(4)) -> GetString()).Atof();
            fErrSystDown[fNpoints] = (((TObjString*) tokens->At(5)) -> GetString()).Atof();
            fErrExtrapUp[fNpoints] = (((TObjString*) tokens->At(6)) -> GetString()).Atof();
            fErrExtrapDown[fNpoints] = (((TObjString*) tokens->At(7)) -> GetString()).Atof();
            fErrTotalUp[fNpoints] = sqrt( pow(fErrStat[fNpoints], 2) + pow(fErrSystUp[fNpoints], 2) + pow(fErrExtrapUp[fNpoints], 2));
            fErrTotalDown[fNpoints] = sqrt( pow(fErrStat[fNpoints], 2) + pow(fErrSystDown[fNpoints], 2) + pow(fErrExtrapDown[fNpoints], 2));

        } else if  (fFileType == 3) { // D*

            fValue[fNpoints] = (((TObjString*) tokens->At(2)) -> GetString()).Atof();
            fErrStat[fNpoints] = fValue[fNpoints]*(((TObjString*) tokens->At(3)) -> GetString()).Atof()/100;
            fErrSystDown[fNpoints] = fValue[fNpoints]*(((TObjString*) tokens->At(4)) -> GetString()).Atof()/100;
            fErrSystUp[fNpoints] = fValue[fNpoints]*(((TObjString*) tokens->At(5)) -> GetString()).Atof()/100;
            fErrExtrapDown[fNpoints] = fValue[fNpoints]*(((TObjString*) tokens->At(6)) -> GetString()).Atof()/100;
            fErrExtrapUp[fNpoints] = fValue[fNpoints]*(((TObjString*) tokens->At(7)) -> GetString()).Atof()/100;
            fErrTotalUp[fNpoints] = sqrt( pow(fErrStat[fNpoints], 2) + pow(fErrSystUp[fNpoints], 2) + pow(fErrExtrapUp[fNpoints], 2));
            fErrTotalDown[fNpoints] = sqrt( pow(fErrStat[fNpoints], 2) + pow(fErrSystDown[fNpoints], 2) + pow(fErrExtrapDown[fNpoints], 2));

        } else {
            cout << "ERROR: file type unknown " << endl;
            abort();
        }

        fNpoints++;
    }

    cout << "INFO: " << fNpoints << " entries in " << fFilename << " were found\n" << endl;
}
