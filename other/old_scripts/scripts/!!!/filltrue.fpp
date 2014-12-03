      subroutine FillTrue(Iwant)
*     ******************************
*
*----------------------------------------------------------------
* created by S.Chekanov, Nov 2001, to fill personal ntuple  
*----------------------------------------------------------------
*
      Implicit NONE

#include "partap.inc"
#include "zdskey.inc"
#include "vctpar.inc"
#include "myntuple.inc"
#include "ctrlcm.inc"
#include "mycom.inc"

* mc stuff
#include "usgevt.inc"
#include "fmckin.inc"
#include "fmcevt.inc"
#include "fmcpcd.inc"
#include "fmcprt.inc"

      CHARACTER*4 GENKEY_ARG  
      Integer   iwant, j, iWant1, imod, ipart  
      Integer   IMC,m,nnn,lista_had(512),I,Ierr
      real TRC,THE,HQ2,PQ,HX,HY,XX1,XX2,XX3,XX4   
      real sinv,pi2,etjet,MPROTON 
      parameter (pi2=6.28315, MPROTON=0.938272)
      integer icbeam, nfmck, nev2,mcphoton
      real RP, PVV(4), phpp(20,5),PT
      logical TRFIR
      data TRFIR /.TRUE./
      real xq2,xy,xw

  
      Iwant=0    
      mcphoton=0


      m=1  


      IF (TRFIR) THEN
      TRFIR=.FALSE.
      nev2=0
      ENDIF 


      MCEbeam=INT(1000*EBeam_Energy)
      MCPbeam=INT(1000*PBeam_Energy) 

      NFMCkin=0 
      if (coutab(FMCKIN).eq.0) goto 999 

      sinv = 4.*EBeam_Energy*PBeam_Energy + MPROTON**2

*
* Scattered electron:
*

      call fettab(fmckin,id,1)
      icbeam = FMCKIN_FMCPrt 

      nfmck=COUTAB(FMCKIN)  


      do 51  i =  3, nfmck 
c
      call fettab(fmckin,id,i)
      if ( FMCKIN_FMCPrt .ne. icbeam )     goto  51
      if (mod (FMCKin_isthep,1000) .ne. 1) goto  51 

          MCElec=fmckin_p(4)
          XX1=sqrt(fmckin_p(2)**2+fmckin_p(1)**2)
          XX2=fmckin_p(3)
        IF (XX2.ne.0.0) then 
          MCEthe=ATAN2(XX1,XX2)
        ELSE
          MCEthe=pi2/2. 
        ENDIF 

        DO m=1, 4
        PVV(m)=fmckin_p(m) 
        ENDDO 


        XX3=fmckin_p(1)
        XX4=fmckin_p(2)
        IF (XX3.ne.0.0) then  
          MCEphi=ATAN2(XX4,XX3)
        ELSE
          MCEphi=pi2 
        ENDIF 
        if (MCEphi.lt.0.) MCEphi = pi2 +MCEphi
      goto  61
c
   51 continue
c
   61 continue


       MCgam(1)=PVV(1)
       MCgam(2)=PVV(2) 
       MCgam(3)=PVV(3)+EBeam_Energy   
       MCgam(4)=PVV(4)-EBeam_Energy 

* results are the same !
       xq2 = 2.*EBeam_Energy*MCElec*(1.+cos(MCEthe))
       xy = 1.-MCElec/2./EBeam_Energy*(1. - cos(MCEthe))
       xw= sqrt ( xy*sinv - xq2 + (MPROTON**2) * (1-xy) ) 

*       write(6,*) 'Calculated values Q2=',xq2
*       write(6,*) 'Calculated values Y=',xy
*       write(6,*) 'Calculated values W=',xw 


*      MCQ2=Ora_MC_q2
*      MCYbj=Ora_MC_y
*      MCXbj=Ora_MC_x

** as Leonid suggested

       MCQ2=xq2
       MCYbj=xy
       MCXbj=xw


       IF (MCQ2.ge.4)     goto 999 
       IF (MCYbj.ge.0.9)  goto 999
       IF (MCYbj.lt.0.06) goto 999

*      write(6,*) 'from table=', MCQ2, ' ', MCYbj 

C put information on the process
      CALL FETTAB(USGEVT, ID,1)  
      MCElec = USGEVT_IPA(1) 
C   write(6,*) ' Process =',MCElec 


C      call defgen(genkey_arg)

*** fill FMCkin table with hadrons and leptons and photons
*** All the particles with a lifetime larger than 1 ns (0.3 m)
      imod=0  ! ZDIS particles      
      ierr=0
      ipart=0 
      call get_hadsys(imod,0,0,ipart,lista_had,ierr)
      if (ierr .gt. 0) then
         write(6,*),
     +   'Error to get FMCkin table from get_hadsys',
     +        ierr,ipart
              goto 999 
      endif
      if (ipart.le.0.or.ipart.gt.500) then
         ierr=10 
         write (6,*) 'Error: from get_hadsys',ipart
         goto 999
      endif

      nnn=0 
      do i=1, ipart 
      call FetTab(FMCKin,ID,lista_had(i))
         if (FMCKin_FMCPrt .le. 22 .or.
     +       FMCKin_FMCPrt .gt. 1600) then
             goto 777
         endif

        nnn=nnn+1
        PPFMCkin(1,nnn)=fmckin_p(1)
        PPFMCkin(2,nnn)=fmckin_p(2) 
        PPFMCkin(3,nnn)=fmckin_p(3) 
        PPFMCkin(4,nnn)=fmckin_p(4)  
        IDFMCkin(nnn)  =fmckin_fmcprt
** get charge
        CALL FETTAB(FMCPrt,ID,fmckin_fmcprt)
        ICHARGE(nnn) = int(FMCPrt_Charge)

       TRC=sqrt(PPFMCkin(1,nnn)**2+PPFMCkin(2,nnn)**2)
       THE=ATAN2(TRC, PPFMCkin(3,nnn)) 
       RP=-log(tan(THE/2.0))
       PT= sqrt(fmckin_p(1)**2 + fmckin_p(2)**2 ) 

       IF (fmckin_fmcprt.eq.29) then
       IF (PT.gt.5 .and. abs(RP).lt.1.75) then  
          mcphoton=mcphoton+1

          phpp(mcphoton,1)=PPFMCkin(1,nnn) 
          phpp(mcphoton,2)=PPFMCkin(2,nnn)
          phpp(mcphoton,3)=PPFMCkin(3,nnn)
          phpp(mcphoton,4)=PPFMCkin(4,nnn) 

       call hf1(501,PT,1.)
       ENDIF  
       ENDIF

 777  continue  
      enddo 
      NFMCkin=nnn

      call hf1(580,1.0,1.) 
      call hf1(500,real(mcphoton),1.)

* do not reject on the basis of true photon energy
*      IF (mcphoton.eq.0) Goto 999 
    

       nev2=nev2+1
 
       if (mod(nev2,100).eq.0) then
       write(6,*) '-------------------------------'
       write(6,*) 'Found true photon  in  event', nev2
       write(6,*) '-------------------------------'
       write(6,119) 'true photon=',phpp(mcphoton,1), phpp(mcphoton,2),
     +     phpp(mcphoton,3),  phpp(mcphoton,4) 
       endif
119    FORMAT (A7,4F8.3)


      call hf1(580,2.0,1.)    

*      write(6,*) 'Photon is found on truth level', mcphoton 

** require than this photon can be reconstructed as a jet

      iWant1=0
      call KTTRUE(iWant1)
      if (iWant1.eq.0)  Goto 999 
*      write(6,*) 'Photon is reconstructed as true jet!' 
      call hf1(580,3.0,1.) 


      Iwant=1


 999  continue 
      End 
