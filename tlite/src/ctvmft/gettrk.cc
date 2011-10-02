#include <vector>
#include <iostream>
#include <cmath>
#include "LinearizedTrack.hh"
#include "ctvmft.h"

using namespace VxLite;

//std::vector<VxLite::LinearizedTrack*> gTracks;
//
//   Author: Tarta
//
// IN->  TRACK:  track no. (integer)
//       TYPE:   track bank name (character//4)
//       MASS:   mass associated to track (real)
//               0: no dE/dx anc CMS correction
//               gt.0: use it for dE/dx and CMS. Only e,mu,pi,K,p
//               supported 
//       RADIUS: radius to calculate dE/dx and CMS (real)
//       BEAM:   beam constraint fit flag (integer) **not implemented**
// OUT-> VRTX:   vertex association for this track from track bank
//               if any ** not implemented **
//       XM1:    track helix parameter (Cot,C,z0,D0,Phi0) (real array-5)
//       ELM1:   covariance matrix (real matrix 5x5)
//       IERR:   error code (integer)
//                0: OK    
//               -1: illegal track number
//               -2: illegal bank number
//                1: error from the unpacking routine
//                4: zero term in covariance matrix
//                5: correlation term > 1  in covariance matrix     
extern "C" {
  void gettrk_(const int& track,const char* type,const float& mass,
	       const float& radius,const int& beam,int& vrtx,float xm1[5],
	       float elm1[5][5],int& ierr, int ltype) 
  {
    //  INTEGER track,beam,vrtx,ierr
    //  CHARACTER*4 type
    //  REAL mass,radius,xm1(5),elm1(5,5),zpar1(5),zcov1(15)
    //(CDF:Ctg,Crv,Z0,D0,Phi) ZEUS:PhiH, Q/R, QDH, ZH,cot theta).
    //    (Crv,Phi,Ctg,D0,Z0).
    const int translate[5] = { 1,0,4,2,3};   
    //    std::cout << "reading track " << track << " " << type << " "
    //	      << mass << " " << radius << " " << vrtx << " " << ltype << "\n";
    LinearizedTrack* t = gTracks[track-1];
    if(! t) {
      ierr = -1;
      return;
    } 
//     std::cout << "helix center:" 
// 	      << (t->alpha()[2] + 1/t->alpha()[1]) * sin(t->alpha()[0]) << " " 
// 	      << (t->alpha()[2] + 1/t->alpha()[1]) * cos(t->alpha()[0]) << "\n";
    for(int i = 0; i < 5 ; ++i) {
      xm1[i] = t->alpha()[translate[i]];
      for(int j = i; j < 5 ; ++j) {
	elm1[i][j] = t->covalpha()[translate[i]][translate[j]];
	elm1[j][i] = t->covalpha()[translate[j]][translate[i]];
      }
    }
    xm1[0] *= 0.5;
    //xm1[3] *= -1;
    for(int i = 0; i < 5 ; ++i) {
      elm1[i][0] *= 0.5;
      elm1[0][i] *= 0.5;
      elm1[i][1] *= -1;
      elm1[1][i] *= -1;
    }
    xm1[1] *= -1;
    if(xm1[1] <  0) xm1[1] +=  2 * M_PI;
    if(xm1[1] <  0) {
      std::cout << "gettrk: second addition needed \n";
      xm1[1] +=  2 * M_PI;
    }
    ierr = 0; 
    //    std::cout << "track cov:" << elm1[0][0] << ", " 
    //	      << t->covalpha()[translate[0]][translate[0]] << "\n";
//     float track1[5]={0.6388943,9.2641776E-04,-12.28119,0.1847257,2.275871};
//     float track2[5]={-0.3420225,-1.1143032E-03,-12.65301,-4.5778926E-02,
// 		     3.464010};
//     float matrix1[15]={4.4519627E-05,-1.2202699E-09,-3.6059290E-03,
// 		       1.4552880E-07,-1.2501530E-08,8.1592857E-12,1.4460534E-07,
// 		       -1.4819885E-11,-4.6326613E-11,0.3309176,-1.5055033E-05,
// 		       1.1653831E-06,7.1228546E-06,-1.6982059E-06,4.5933709E-07};
//     float matrix2[15]={5.2620642E-05,-1.7791162E-09,-4.3883389E-03,2.5684884E-07,
// 		       -2.0232983E-08,1.2000366E-11,2.2028658E-07,-1.6547597E-10,
// 		       -5.8226257E-11,0.4132599,-2.6367790E-05,1.8426891E-06,
// 		       8.3876794E-06,-2.0421414E-06,5.6498709E-07};
//     //result: -0.220745,-0.0255024,-12.4358
//     const int translate[5] = { 2,0,4,3,1};
//    int k=0;
//    if(track == 1) {
//      for(int i = 0 ; i < 5; ++i) {
//        xm1[translate[i]] = track1[i];
//        for(int j = i;j < 5; ++j) {
// 	 elm1[translate[i]][translate[j]] = matrix1[k];
// 	 elm1[translate[j]][translate[i]] = matrix1[k];
// 	 k++;
//        }
//      }
//    }
//    else {   
//      for(int i = 0; i < 5 ; ++i) {
//        xm1[translate[i]] = track2[i];
//        for(int j = i; j < 5; ++j) {
// 	 elm1[translate[i]][translate[j]] = matrix2[k];
// 	 elm1[translate[j]][translate[i]] = matrix2[k];
// 	 ++k;
//        }
//      }
//    }		  
  } 
};
