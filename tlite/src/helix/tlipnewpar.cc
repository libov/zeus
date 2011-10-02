//*****************************************************************************
// File:      LinearizedTrack.cc
// ----------------------------------------------------------------------------
//=============================================================================
// RCS Current Revision Record
//-----------------------------------------------------------------------------
// $Source: /afs/desy.de/user/s/stadie/zeus/cvsroot/tlite/src/helix/tlipnewpar.cc,v $
// $Revision: 1.5 $
// $Date: 2006/08/01 16:11:17 $
// $Author: stadie $
// $State: Exp $
// $Locker:  $
//*****************************************************************************
// tliphel calculates the four momentum using the track parameters at a
// reconstructed vertex.
// 
// Input:
//    par     - the track parameters at the vertex(theta, phi, curvature
//    bfieldz - the z component of the magnet field in kgauss
//    mass    - the mass of the particle
//
// Output:
//    p       - the four momentum
//
//*****************************************************************************
#include "LinearizedTrack.hh"


extern "C" {
  void tlipnewpar_(float par[3], float &bfieldz, float& mass, double p[4]) 
  {
    float B = bfieldz;
    if(B == 0) {
      B = VxLite::LinearizedTrack::BFIELD_TESLA * 10;
    }
    
    double pt = std::abs(VxLite::LinearizedTrack::CURVATURE_CONSTANT * B 
			 / par[2] * 0.1);
    p[0] = cos(par[1]) * pt;
    p[1] = sin(par[1]) * pt;
    double cottheta = 1 / tan(par[0]);
    p[2] = cottheta * pt;
    if(mass == 0) {
      mass = VxLite::LinearizedTrack::PI_PLUS_MASS;
    }
    p[3] = sqrt(mass * mass + (1 + cottheta * cottheta) * pt * pt); 
  }
}
