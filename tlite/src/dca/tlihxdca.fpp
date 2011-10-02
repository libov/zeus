      real function tlihxdca(mode,idtr1,idtr2)
******************************************************************************
* File:      VertexFitter.cc
* ----------------------------------------------------------------------------
*=============================================================================
* RCS Current Revision Record
*-----------------------------------------------------------------------------
* $Source: /afs/desy.de/user/s/stadie/zeus/cvsroot/tlite/src/dca/tlihxdca.fpp,v $
* $Revision: 1.1 $
* $Date: 2005/09/30 09:59:52 $
* $Author: stadie $
* $State: Exp $
* $Locker:  $
*****************************************************************************
*
*     **** determine DCA of 2 helices from track tables
*     **** front end to tlidca

*     **** parameters: mode  (2 = REG, 4 = ZTTRHL)
*     ****             idtr1 (table row pointer for first  track)
*     ****             idtr2 (table row pointer for second track)
*
*    Author:  Rainer Mankel                  Created:  12-Aug-05
*             DESY Hamburg                   Modified:  
*    Email:   Rainer.Mankel@desy.de          ZEUS Collaboration
*
      implicit none
*
#include "partap.inc"
#include "zdskey.inc"
#include "zttrhl.inc"
#include "vctrhl.inc"

      integer mode
      integer idtr1
      integer idtr2

      real par1(5),par2(5),tlidca
      integer ii

      if (mode.eq.4) then
         tlihxdca = 999999.
         ZTTRHL_ID = idtr1
         call gettab(ZTTRHL)
         do ii=1,5
            par1(ii) = ZTTRHL_hel(ii)
         enddo
         ZTTRHL_ID = idtr2
         call gettab(ZTTRHL)
         do ii=1,5
            par2(ii) = ZTTRHL_hel(ii)
         enddo
         tlihxdca = tlidca(par1,par2)
      elseif (mode.eq.2) then
         tlihxdca = 999999.
         VCTRHL_ID = idtr1
         call gettab(VCTRHL)
         par1(1) = VCTRHL_azim
         par1(2) = VCTRHL_qovr
         par1(3) = VCTRHL_qxdh
         par1(4) = VCTRHL_zh
         par1(5) = VCTRHL_tdip
         VCTRHL_ID = idtr2
         call gettab(VCTRHL)
         par2(1) = VCTRHL_azim
         par2(2) = VCTRHL_qovr
         par2(3) = VCTRHL_qxdh
         par2(4) = VCTRHL_zh
         par2(5) = VCTRHL_tdip
         tlihxdca = tlidca(par1,par2)
      else
         print *,' tlihxdca: non-supported mode ',mode
         tlihxdca = -2.
      endif
      end
