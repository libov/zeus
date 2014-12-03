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
      IMPLICIT NONE
      
#include "partap.inc"
#include "tltevt.inc"
#include "vtxtup.inc"
#include "zdskey.inc"
#include "fmckin.inc"

* Orange include files:
#include "trk_ntup.inc"
#include "sintup.inc"
#include "evttup.inc"
#include "orangecrd.inc"


      Integer   Ierr, iwant, i, m, j, k
      Integer   iwant1,iwant2
      Integer   kk, jj, II, nzz,IMC



      TAKEEVENT=.TRUE.


c do true staff
      IMC=COUTAB(FMCKIN)
      IF (IMC.ne.0) then
      Iwant1=0
        CALL FILLTRUE(Iwant1) 
        if (iwant1.eq.1) call hf1(980,2.0,1.0)
      ENDIF


c      Get electron and BPRE
       iwant2=0
       CALL ELECTR(iwant2)
       if (iwant2.eq.1) call hf1(980, 6.0,1.0)

 
C do not take event in data if does not pass the cuts 
      IF (IMC.eq.0.and.iwant2.eq.0) TAKEEVENT=.FALSE.

C do not take event in data if does not pass the cuts
      IF (IMC.ne.0) then 
      if(Iwant2.eq.0.and.Iwant1.eq.0) TAKEEVENT=.FALSE.
      ENDIF 


      if (SiNcand.le.0)    TAKEEVENT=.FALSE.
   
** only high Q2
      if (SiNcand.ge.1) then
        if (SiQ2el(1).lt.20)   TAKEEVENT=.FALSE.
        if (Siecorr(3,1).lt.9.0)  TAKEEVENT=.FALSE.
        if (abs(Ora_Zvtx).gt.52.) TAKEEVENT=.FALSE.
      endif


 
      IERR=0

      RETURN
      END
