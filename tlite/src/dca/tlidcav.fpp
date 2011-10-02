      real function tlidcav(par1,par2,v)
******************************************************************************
* File:      VertexFitter.cc
* ----------------------------------------------------------------------------
*=============================================================================
* RCS Current Revision Record
*-----------------------------------------------------------------------------
* $Source: /afs/desy.de/user/s/stadie/zeus/cvsroot/tlite/src/dca/tlidcav.fpp,v $
* $Revision: 1.1 $
* $Date: 2005/09/30 09:59:52 $
* $Author: stadie $
* $State: Exp $
* $Locker:  $
*****************************************************************************
*
*     **** determine DCA of 2 helices using Hessian method.
*     **** Return also middle point of DCA
*
*    Author:  Rainer Mankel                  Created:  15-Aug-05
*             DESY Hamburg                   Modified:  
*    Email:   Rainer.Mankel@desy.de          ZEUS Collaboration
*
      implicit none
*     **** external variables
      real par1(5)   ! helix parameters of track 1
      real par2(5)   ! helix parameters of track 2
      real v(3)      ! middle point of DCA vector

*     **** internal variables
      integer iter,maxiter,ii
      real v1(3),v2(3),dd,qr1,xh1,yh1,zh1,ct1,phih1,qr2,xh2,yh2,zh2,
     +     ct2,phih2,Txh,Tyh,Tzh,Tqr,Tt1,Tt2,phi1,phi2,grad1,grad2,
     +     hesse11,hesse22,hesse12,deth,dphi1,dphi2,gradEnd,
     +     dcalast1,dcalast2,dcalast3

      parameter (maxiter=20,gradEnd=0.001)

      qr1 = 1./par1(2)
      xh1 =   par1(3) * sin(par1(1))
      yh1 = - par1(3) * cos(par1(1))
      zh1 =   par1(4)
      ct1 =   par1(5)
      phih1 = par1(1)

      qr2 = 1./par2(2)
      xh2 =   par2(3) * sin(par2(1))
      yh2 = - par2(3) * cos(par2(1))
      zh2 =   par2(4)
      ct2 =   par2(5)
      phih2 = par2(1)

      Txh = xh2 - xh1 + qr2 * sin(phih2) - qr1 * sin(phih1)
      Tyh = yh2 - yh1 - qr2 * cos(phih2) + qr1 * cos(phih1)
      Tzh = zh2 - zh1 + qr2 * ct2 * phih2 - qr1 * ct1 * phih1
      Tqr = qr1 * qr2
      Tt1 = qr1 * ct1
      Tt2 = qr2 * ct2

*     **** initial value
      phi1 = phih1
      phi2 = phih2

      dcalast1 = 999999.
      dcalast2 = 999999.
      dcalast3 = 999999.

      do 10 iter=1,maxiter

*        **** test distance
         call rmhelixv(par1,phi1,v1)
         call rmhelixv(par2,phi2,v2)
         dd = (v2(1)-v1(1))**2
     +        + (v2(2)-v1(2))**2
     +        + (v2(3)-v1(3))**2
#ifdef VERBOSE
         print *,' tlidcav: iter ',iter,' distance ',sqrt(dd)
#endif
         tlidcav = sqrt(dd)

         grad1 = Txh * qr1 * cos(phi1) - Tqr * cos(phi1) * sin(phi2)
     +        + Tyh * qr1 * sin(phi1) + Tqr * sin(phi1) * cos(phi2)
     +        + Tzh * qr1 * ct1
     +        + Tt1**2 * phi1
     +        - Tt1 * Tt2 * phi2
         grad2 = - Txh * qr2 * cos(phi2) - Tqr * sin(phi1) * cos(phi2)
     +        - Tyh * qr2 * sin(phi2) + Tqr * cos(phi1) * sin(phi2)
     +        - Tzh * qr2 * ct2
     +        - Tt1 * Tt2 * phi1
     +        + Tt2**2 * phi2

*               **** stop when gradients are close to zero
         if (abs(grad1).lt.gradEnd.and.abs(grad2).lt.gradEnd) then
            go to 11
         endif
*               **** stop if repeatedly no minimization
         if (.not.(tlidcav.lt.dcalast1.or.tlidcav.lt.dcalast2
     +        .or.tlidcav.lt.dcalast3)) then
            go to 11
         else
            dcalast3 = dcalast2
            dcalast2 = dcalast1
            dcalast1 = tlidcav
         endif

         hesse11 = -Txh * qr1 * sin(phi1) + Tqr * sin(phi1) * sin(phi2)
     +        + Tyh * qr1 * cos(phi1) + Tqr * cos(phi1) * cos(phi2)
     +        + Tt1**2
         hesse22 = Txh * qr2 * sin(phi2) + Tqr * sin(phi1) * sin(phi2)
     +        - Tyh * qr2 * cos(phi2) + Tqr * cos(phi1) * cos(phi2)
     +        + Tt2**2
         hesse12 = -Tqr * (cos(phi1)*cos(phi2) + sin(phi1)*sin(phi2))
     +        - Tt1 * Tt2
         deth = hesse11 * hesse22 - hesse12**2

         dphi1 = - ( hesse22 * grad1 - hesse12 * grad2) / deth
         dphi2 = - (-hesse12 * grad1 + hesse11 * grad2) / deth

         phi1 = phi1 + dphi1
         phi2 = phi2 + dphi2
#ifdef VERBOSE
         print *,'     dphi1,dphi2=',dphi1,dphi2
#endif

 10   continue
 11   continue

      do ii=1,3
         v(ii) = 0.5 * (v1(ii) + v2(ii))
      enddo

      end



      subroutine rmhelixv(a,phi,vec)
      real a(5),phi,vec(3)
      real xh,yh,zh,qr,s
      xh =   a(3) * sin(a(1))
      yh = - a(3) * cos(a(1))
      zh =   a(4)
      qr = 1./a(2)
      s  = - qr * (phi-a(1))
      vec(1) = xh + qr * (-sin(phi)+sin(a(1)))
      vec(2) = yh + qr * ( cos(phi)-cos(a(1)))
      vec(3) = zh + s * a(5)
      end
