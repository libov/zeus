//*****************************************************************************
// File:      VertexFitter.cc
// ----------------------------------------------------------------------------
//=============================================================================
// RCS Current Revision Record
//-----------------------------------------------------------------------------
// $Source: /afs/desy.de/user/s/stadie/zeus/cvsroot/tlite/src/dca/tliDcaPoint.cxx,v $
// $Revision: 1.1 $
// $Date: 2005/09/30 09:59:52 $
// $Author: stadie $
// $State: Exp $
// $Locker:  $
//****************************************************************************
//
// For given helix, determine distance of closest approach in xy plane
// to an arbitrary given point. The sign convention is positive if
// the point lies outside of the projected circle (as with DH).
//
//  Author:  Rainer Mankel                  Created:  19-Sep-05
//           DESY Hamburg                   Modified:
//  Email:   Rainer.Mankel@desy.de          ZEUS Collaboration
//
//
//  Parameters: parIn[5]     helix parameters (ZEUS convention)
//              point[2]     (x,y) of given point
//
//  Fortran:  real d,tlidcapoint
//            d = tlidcapoint(parIn,xpoint,ypoint)
//

#include <math.h>
#include <iostream>
using std::cout;
using std::endl;

float tliDcaPoint(const float parIn[5],const float covIn[15],
		  const float xPoint,const float yPoint,int covmode,
		  float& eDca) 
{
  const float& phiH = parIn[0];  // define shorthands for track par
  const float& QovR = parIn[1];
  const float& QDH = parIn[2];
  // float& zH = parIn[3];
  // float& cotTheta = parIn[4];

  float QR = 999999;
  if (QovR != 0) {
    QR =  1./QovR;
  } else {
    cout << " Error from tliDcaPoint:  QovR = " << QovR << endl;
  }

  float xC =   (QDH + QR) * sin(phiH); // helix center
  float yC = - (QDH + QR) * cos(phiH);

  float D0 = sqrt( (xPoint-xC)*(xPoint-xC) 
		   + (yPoint-yC)*(yPoint-yC) ) - fabs(QR);

  if (covmode>0) {
    // compute error of dca
    float Q = (QovR>0)? 1 : -1;
    float denom = sqrt( (xPoint-xC)*(xPoint-xC) 
			+ (yPoint-yC)*(yPoint-yC) );
    float d_QDH = ((xC-xPoint) * sin(phiH) - (yC-yPoint) * cos(phiH)) / denom;
    float d_QovR = (QR*QR) * ((-(xC-xPoint) * sin(phiH) + (yC-yPoint) * cos(phiH)) / denom
			      + Q);
    float d_phiH = ((xC-xPoint) * (QDH + QR) * cos(phiH) + (yC-yPoint) * (QDH + QR) * sin(phiH)) / denom;
    float sDca = d_QDH * d_QDH * covIn[9] + d_QovR * d_QovR * covIn[5] + d_phiH * d_phiH * covIn[0]
      + 2 * d_QDH * d_QovR * covIn[6]
      + 2 * d_QDH * d_phiH * covIn[2]
      + 2 * d_QovR * d_phiH * covIn[1];
    if (sDca>0) {
      eDca = sqrt(sDca);
    } else {
      cout << " Error from tliDcaPoint: sDca=" << sDca << endl;
      eDca = -1;
    }
  }

  // cout << " dca " << D0 << " error " << eDca << " sig " << D0/eDca << endl; 
  return D0;
}

// This is the Fortran-callable interface
extern "C" {
  float tlidcapoint_(const float* parIn,const float* covIn,
		     const float& xpoint,const float& ypoint,
		     const int& covmode,float& eDca) 
  { 
    return tliDcaPoint(parIn,covIn,xpoint,ypoint,covmode,eDca); 
  }
}
