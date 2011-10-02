      real function tlihxpdca(mode,idtr,xp,yp)
******************************************************************************
* File:      VertexFitter.cc
* ----------------------------------------------------------------------------
*=============================================================================
* RCS Current Revision Record
*-----------------------------------------------------------------------------
* $Source: /afs/desy.de/user/s/stadie/zeus/cvsroot/tlite/src/dca/tlihxpdca.fpp,v $
* $Revision: 1.1 $
* $Date: 2005/09/30 09:59:52 $
* $Author: stadie $
* $State: Exp $
* $Locker:  $
*****************************************************************************
*     **** determine DCA of helix to point from track table
*     **** front end to tlidcapoint

*     **** parameters: mode  (2 = REG, 4 = ZTTRHL)
*     ****             idtr  (table row pointer for track)
*     ****             xp    (x xoordinate of point)
*     ****             yp    (x xoordinate of point)
*
*    Author:  Rainer Mankel                  Created:  19-Sep-05
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
      integer idtr
      real xp
      real yp
      real tlidcapoint,par(5)

      if (mode.eq.4) then
         tlihxpdca = 999999.
         ZTTRHL_ID = idtr
         call gettab(ZTTRHL)
         tlihxpdca = tlidcapoint(ZTTRHL_hel,xp,yp)
      elseif (mode.eq.2) then
         tlihxpdca = 999999.
         VCTRHL_ID = idtr
         call gettab(VCTRHL)
         par(1) = VCTRHL_azim
         par(2) = VCTRHL_qovr
         par(3) = VCTRHL_qxdh
         par(4) = VCTRHL_zh
         par(5) = VCTRHL_tdip
         tlihxpdca = tlidcapoint(par,xp,yp)
      else
         print *,' tlihxpdca: non-supported mode ',mode
         tlihxpdca = -2.
      endif
      end
