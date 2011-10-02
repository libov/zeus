// C header file for CTVMFT developed by Mariner and Berge for CDF
//
//
#ifndef CTVMFT_H
#define CTVMFT_H


#define MaxVtx 3   //maximum number of vertices
#define MaxMcn 4   //maximum number of mass constraints
#define MaxTrk 100 //maximum number of tracks
#define MaxItr 10  //maximum number if iteration steps
#define UDIM MaxTrk*(MaxVtx+MaxMcn+60)+ MaxVtx*(MaxVtx+18) + MaxMcn*6 +MaxItr + 31
#define MAXDIM 7*(MaxVtx+1) + 3*MaxTrk + MaxMcn


extern "C" {
  extern struct {
    int RUNNUM,TRGNUM;         // "you can't tell the players without a score card"
    int ITER;                  // number of iterative steps taken
    int NTSCUT;                // total number of cut steps, this fit
    int NVERTX;                // Number of vertices
    int NMASSC;                // Number of mass constraints
    int NTRACK;                // Fit specification
    int TRKVTX[MaxVtx][MaxTrk];// (Vertex,Track) association table
    int TRKMCN[MaxMcn][MaxTrk];// (Mass_Constraint,Track) table
    int VTXPNT[2][MaxVtx];     // vertex association information
    float CMASS[MaxMcn];       // Constraint mass
    int CVTX[MaxVtx];          // Conversion constraint specification
    int VTXVTX[MaxVtx][MaxVtx];// vertex geneology
    char TKBANK[MaxTrk][4];    // Track bank type (e.g. 'TRKS')
    int LIST[MaxTrk];          // Track bank number
    float TMASS[MaxTrk];         // Track mass assignment
    int MATDIM;                // Dimension of the matrix, this fit
    int TKERR[MaxTrk];         // Track "error memory"
    int NDOF;                  // Fit number of degrees of freedom
    float CHISQR[MaxItr+1];    // Overall fit Chi Square result
    float CHIT[MaxTrk];        // Track contribution to Chi Square
    float CHIV[MaxVtx+1];      // Vertex fit Chi Squares
    float XYZPV0[3];           // "Primary" vertex; XYZ
    float EXYZPV[3][3];        // "Primary" vertex; covariance
    float XYZVRT[MaxVtx+1][3]; // Primary, Secondary vertices
    float DXYZPV[3];           // Primary vertex displacement in fit
    float PAR[MaxTrk][5];      // Fitted track helix parameters(CDF notation!)
    float G[MaxTrk][5][5];     // Fitted track parameter covariances(CDF notation!)
    float TrkP4[6][MaxTrk];    // Track Px,Py,Pz,E,Pt P
    float VtxP4[MaxVtx][4];    // vertex 4-momentum sum
    float McnP4[MaxMcn][4];    // 4-momentum sum for mass constraint
    float DDA[8][MaxTrk];      // d(Px,Py)/d(Crv,Phi,Xs,Ys)
    int VOFF[MaxVtx];          // offset pointers into VMAT
    int TOFF[MaxTrk];          // offset pointers into VMAT
    int POFF[MaxVtx];          // offset pointers into VMAT
    int COFF[MaxVtx];          // offset pointers into VMAT
    int MOFF;                  // offset pointers into VMAT
    float PAR0[MaxTrk][5];     // Original track parameter values
    float PARDIF[MaxTrk][5];   // Parameter differences (fit - input)
    float FMCDIF[MaxMcn];      // Mass constraint residuals
    float PCON[2][MaxVtx];     // Pointing constraint tests
    float SANG[2][MaxVtx];     // Pointing constraint tests             
    float DRMAX,RVMAX,DZMAX;   // CTVMFA constants
    float TRNMAX,DSMIN;        // CTVMFA constants
    int IJKERR[3];             // error code reporting
    float PSCALE;              // Momentum scale conversion factor, from (cm)**-1 to Gev/c
    //  int junk[4]; missing mem
  } ctvmfq_;
  extern struct {
    double VMAT[MAXDIM+1][MAXDIM]; // Covariance matrix, fit parameters
  } ctvmfr_;
  void ctvmft_(int &PRINT, int& LEVPRT,int &IERR);
};

namespace VxLite {
class LinearizedTrack;
}
std::vector<VxLite::LinearizedTrack*> gTracks;

#endif
