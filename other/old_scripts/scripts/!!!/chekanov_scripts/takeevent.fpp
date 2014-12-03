      LOGICAL FUNCTION TAKEEVENT(IERR)
*Start_Documentation
*********************************************************************
C#
C#  Purpose:
C@#  <one line description>
C#
C#   <any further description>
C#
C#  Inputs: <input parameters>
C#
C#
C#  Outputs: <output parameters>
C#
C#
C#  Author:
C#  Date  :
C#  Dates modified  :
C#  Comments:
C#  Reference: <www, papers,etc>
*-------------------------------
*End_Documentation
*
* -----------
* S.Chekanov
* 25/06/2003
* ----------
* This routine comes from the official orange source code
*
* Select DIS events for single strange baryon production.
* Take only events with at least 1 svtx
* ----------

* I will introduce my cuts!!!!
*
* Use TLT DIS03 - TLTEVT_Subtrg(4),18 using btest
*              or TLTEVT_Subtrg(4),19 using jbit
*      (I am not going to apply this trigger now)
* DST9 (electron finder) already set in the control card.
*
* DIS loose cuts (tight them in the selection using PAW or fortran)
*
* |zvtx| < 55. (tight to |zvtx| < 50)
* yele < 0.95  ( " "  to yele < 0.8)
* yjb > 0.02   ( " "  to yjb > 0.04)
* No Ele_cor_ene > 8.
* No Q2 cut yet
* EmPz applied yet
*
* Note: Use electron with highest probability
*
      IMPLICIT NONE

#include "partap.inc"
#include "tltevt.inc"
#include "sintup.inc"
#include "vtxtup.inc"
#include "itakemy.inc"
#include "zdskey.inc"
#include "fmckin.inc"
#include "fmcevt.inc"
#include "zttrhl.inc"

* Orange include files:
#include "evttup.inc"
#include "v0tuplite.inc"
* standard Orange
#include "v0tup.inc"
#include "beamspot.inc"
#include "nt_mvdcor.inc"
#include "ztpruse.inc"



      Integer   Ierr,ie,NV0LL,NV,iwant,i,Iwant1
      real rspot(3)
      real xpt,x_disp, y_disp, z_disp
      real fac1,fac2, v0col,PPx,PPy,PPz
      real ptmin
      Integer nhit , ntrack,error
      Logical First
      save    First
      Data    First / .TRUE. /
      real mvddedxcr
      integer trk_mode,cor_mode,cal_mode,func_mode
      integer mvnhit
      real cutoff

      iwant=0
      Iwant1=0
      TAKEEVENT=.TRUE.
      ptmin=0.10



         IF (SiNcand.le.0) THEN
             TAKEEVENT=.FALSE.
             GOTO 99
         ENDIF

         IF (abs(Ora_Zvtx).gt.52.) THEN
             TAKEEVENT=.FALSE.
             GOTO 99
         ENDIF


        IF (SiQ2el(1).lt.1.0) THEN
             TAKEEVENT=.FALSE.
             GOTO 99
         ENDIF


         IF (Siecorr(3,1).lt.8.5) THEN
             TAKEEVENT=.FALSE.
             GOTO 99
         ENDIF



         IF (nv0lite.le.0) THEN
             TAKEEVENT=.FALSE.
             GOTO 99
         ENDIF



         rspot(1)=1.29
         rspot(2)=0.19
         rspot(3)=0.0

      if (bspt_prog.gt.0) then
         rspot(1)=bspt_x
         rspot(2)=bspt_y
         rspot(3)=bspt_z
       endif



*      do i=1, trk_ntracks
*      Call access_mvddedxcr(trk_id(i),mvddedx,ierr)
*      trk_dedxmvd(i) = mvddedx
*      enddo


*** noaw check V0
      NV0LL=0

      do i=1,nv0lite

        xpt=sqrt(tP1(1,i)**2 + tP1(2,i)**2)
        if (xpt.lt.ptmin) goto 8500

        xpt=sqrt(tP2(1,i)**2 + tP2(2,i)**2)
        if (xpt.lt.ptmin) goto 8500

      if (tT1_LAYOUT(i).le.2)      goto 8500
      if (tT2_LAYOUT(i).le.2)      goto 8500
      if (tInvmass_ee(i).lt.0.04)  goto 8500

      if (tSecvtx_collin2(i).lt.0.15) NV0LL=NV0LL+1


 8500 continue
      enddo


** take event!
      if (NV0LL.eq.0)  THEN
                  TAKEEVENT=.FALSE.
                  GOTO 99
       endif



      ntrack = coutab(ZTTRHL)

*     !input for corrction
      trk_mode = 3 !int
      cor_mode = 3 !int
      cal_mode = 2  !int
      cutoff=0.01 !real
      func_mode = 1  !int

c     call main routine
      call MVCcal_cormvddedx(Ora_RUNNR,trk_mode,cor_mode
     +     ,cal_mode,cutoff,func_mode,ierr)
      do i = 1,ntrack
         mvnhit = 0
         mvddedxcr = 0
         error = 0
         call MVCaccess_mvddedxcr(i,mvddedxcr,error)
         call MVCaccess_mvddedxnhit(i,mvnhit)

c     my ntuple variable I want to. these linked ../inc/nt_mvdcor.h
         rnhit(i) = mvnhit
         rndedxmvdcor(i) = mvddedxcr
         rndedxmvderr(i) = error
      enddo
      rnZTTRHLid = ntrack




 99   CONTINUE


** MC staff
      IF (COUTAB(FMCKIN).gt.0) then
      Call TrueINFO(Iwant1)
      IF (Iwant1.eq.1)  TAKEEVENT=.TRUE.  ! take event in MC
      ENDIF






      IERR=0

      RETURN
      END
