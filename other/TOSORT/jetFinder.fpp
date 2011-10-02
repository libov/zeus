      SUBROUTINE MCJETS
*     
*     last changed by:
*     Author: Ana Yagues
*     Date: 2008/10/21
*     Changes: only stable B-hadrons (exclude excitations)
*             
*
*     last changed by:
*     
*     $Author: geiser $
*     $Date: 2009/02/25 18:52:42 $
*     $Revision: 1.7 $
*     
*     created by:
*     
*     Author: Massimo Corradi <massimo.corradi@desy.de>
*     Created: 2004/06/27 10:00:00
*     Copyright: 2004 (C) Massimo Corradi
*     
*     do hadron jets calling findjets
*     associates true muons to jets
*     jets in breitframe added (Benjamin Kahle 2005.06.30)
*------------------------------------------------------------------------------
*     
      implicit none
*     
      integer ipritab
      data ipritab  /100/
      save ipritab
      integer          nfmck,ierr,npart0
      integer          i,j,k,npart,elec_flag,first_parton
      integer          jpart(512)	
      integer          brjpart(512)	
      integer          np(10)
      integer          pid(512,10)
      integer          pflag(10)
      real             pjet(4,10)
      real             brpjet(4,10)
      real             labpjet(4,10)
      real             efvp(12,10),efve(12,10)
      integer nbrange,ncrange,nlrange
      parameter (nbrange=7,ncrange=3)     

      real ppp(4,512)
      real brppp(4,512) !particle in breit frame
      real lappp(4,512) !particle back lab frame
      DOUBLE PRECISION dppp(4,512) !particle in lab frame
      DOUBLE PRECISION dbrppp(4,512) !particle in breit frame

      integer ibs       ! flag for particle type
      integer partfmckid(512),brpartfmckid(512),ipart(512)

      integer jdebu
      data jdebu /0/

      real enesum,enelectron,enebeams
      real vjet(3),vmu(3),vptrel(2)

C     massimo's steering flags
      integer jfl_flag,jfm_flag,igen
      real etjetmc,etajmc
      real etjpart,etajpart
      real bretjetmc,bretajmc
      real bretjpart,bretajpart

*     
*------------------------------------------------------------------------------
*     
#include "partap.inc"
#include "fmckin.inc"
#include "mcjets.inc"
#include "fmcknt.inc"
#include "mckitp.inc"
*     
*     do the hadrons
*     
      
* parameter for boost
      DOUBLE PRECISION PLEP, PHAD
      INTEGER LAB_TO_BREIT
      INTEGER BREIT_TO_LAB
      PARAMETER        (LAB_TO_BREIT =0) !no rotation
C     PARAMETER        (LAB_TO_BREIT =2) !rotation
      PARAMETER        (BREIT_TO_LAB =1) !no rotation
C     PARAMETER        (BREIT_TO_LAB =3) !rotation
      DOUBLE PRECISION LEPTON(4)
      REAL PLEPTON
      DOUBLE PRECISION dbrpjet(4,nhjets_max) ! jets in breit
      DOUBLE PRECISION dlabpjet(4,nhjets_max) ! jets back in lab 
*     list of the beauty,charm hadrons and their daughters:
      integer dontake(512),idontake
      integer brange(2,nbrange),crange(2,ncrange)
c      data brange / 72, 75,
c     +     134, 145,
c     +     214, 215,
c     +     455, 455,
c     +     468, 495,
c     +     510, 515,
c     +     520, 521,
c     +     2349, 2378 /
c
c      data crange / 64, 71,
c     +     124, 133,
c     +     186, 189,
c     +     208, 209,
c     +     212, 213,
c     +     417, 426,
c     +     435, 440,
c     +     445, 446,
c     +     535, 547,
c     +     2337, 2348 /

c changed by Ana Yagues (2008.10.21)
c Consider stable particles whose lifetime
c is above 1.E-13s.

      data brange / 72, 75,
     +     214, 215,
     +     468, 471,
     +     480, 497,
     +     500, 501,
     +     504, 505,
     +     508, 509/

      data crange / 64, 69,
     +     208, 211,
     +     466,467/

      npjets=0
      nhjets=0
      nhbjets=0

      npmjets=0
      nhmjets=0
      nhbmjets=0

      nbrpjets=0
      nbrhjets=0
      nbrhbjets=0

      nbrpmjets=0
      nbrhmjets=0
      nbrhbmjets=0


      PLEP=dble(ora_mc_el)   
      PHAD=dble(ora_mc_ep)
      DO J = 1, 4
         LEPTON(J)       = 0D0
      ENDDO
      DO i = 1, 512
         DO J = 1, 4
            ppp(j,i)      = 0
            brppp(j,i)    = 0
            dppp(j,i)     = 0D0
            dbrppp(j,i)   = 0D0
         ENDDO
      ENDDO
      DO i = 1, nhjets_max
         DO J = 1, 4
            dbrpjet(j,i)     = 0D0
            dlabpjet(j,i)    = 0D0
         ENDDO
      ENDDO
      DO i = 1, 512
         jpart(512) = 0
         brjpart(512) = 0
      ENDDO

C     set massimo's steering flags
      jfl_flag=1
      jfm_flag=1
      etjetmc=1.5
      etajmc=3.0
      etjpart=2.5
      etajpart=3.0
      bretjetmc=2.5
      bretajmc=5.0              ! vinc
C     bretajmc=2.5
      bretjpart=2.5
      bretajpart=3.0
      igen=1


C     -------------------------------------------------------------      
C     TRUE HADRONS
C     -------------------------------------------------------------
C     defined as all fmckin=1

      nfmck= coutab(fmckin)
      
      if (nfmck.ne.0)then
c...  this is to make checksums ....
c     get the beam energies for checks
         if (nfmck.ge.2) then
            i=1
            call fettab(fmckin,id,i)
            enebeams=fmckin_p(4)
            i=2
            call fettab(fmckin,id,i)
            enebeams=enebeams+fmckin_p(4)
c     remove the scattered electron and save four-vector for boosts:
            do i=2,nfmck
               call FetTab(FMCKIN,ID,I)
               if(mod(FMCKIN_isthep,10000).eq.1.and.
     +              (FMCKIN_fmcprt.eq.23.or.FMCKIN_fmcprt.eq.24)) then
                  enelectron=fmckin_p(4)
                  PLEPTON = SQRT( FMCKIN_P(1)**2 +
     +                 FMCKIN_P(2)**2 +
     +                 FMCKIN_P(3)**2 )
                  LEPTON(1) = DBLE(FMCKIN_P(4)*FMCKIN_P(1)/PLEPTON)
                  LEPTON(2) = DBLE(FMCKIN_P(4)*FMCKIN_P(2)/PLEPTON)
                  LEPTON(3) = DBLE(FMCKIN_P(4)*FMCKIN_P(3)/PLEPTON)
                  LEPTON(4) = DBLE(FMCKIN_P(4))
                  goto 88
               endif
            enddo
 88         continue
         endif
c     ... ....
         
         npart     = 0
         elec_flag = 0
*     
         enesum=enelectron
         do i=1, nfmck     
            call FetTab(FMCKIN,ID,I)
            if(mod(FMCKIN_isthep,10000).eq.1 ) then
               if ( (FMCKIN_fmcprt.eq.23.or.
     +              FMCKIN_fmcprt.eq.24).and.
     +              elec_flag.eq.0) then
                  elec_flag = 1
                  goto 100
               endif
               if (etjetmc.gt.0.and.FMCKIN_fmcprt.ge.17
     +              .and.FMCKIN_fmcprt.le.22) goto 100
               
               npart = npart + 1
               if( npart.gt.512 )then
                  write(*,*)'KTJETS: Too many particles in FMCKIN!'
                  goto 100
               endif
C     ppp(1,npart) = FMCKIN_p(1)
C     ppp(2,npart) = FMCKIN_p(2)
C     ppp(3,npart) = FMCKIN_p(3)
C     ppp(4,npart) = FMCKIN_p(4)
               dppp(1,npart) = dble(FMCKIN_p(1))
               dppp(2,npart) = dble(FMCKIN_p(2))
               dppp(3,npart) = dble(FMCKIN_p(3))
               dppp(4,npart) = dble(FMCKIN_p(4))
               partfmckid(npart) = FMCKIN_ID
               enesum=enesum+FMCKIN_p(4)
            endif
 100        continue
         enddo
C     boost particle to breitframe HADRONS
         
         IF(npart.GT.0) THEN
            CALL KTBREI(LAB_TO_BREIT, ! BOOST MODALITY
     +           PLEP,          ! INCOMING LEPTON PZ
     +           PHAD,          ! INCOMING HADRON PZ
     +           LEPTON,        ! OUTCOMING LEPTON 4-P
     +           npart,         ! NO OF HADRONS
     +           dppp,          ! LAB FRAME HADRONS (double)
     +           dbrppp,        ! BREIT FRAME HADRONS (double)
     +           *998)          ! WARNING MESSAGE
         ELSE
            WRITE(*,*)'*** BOOSTHADRONS: NO HADRONS TO BOOST!'
         ENDIF
C     cast to real for findjets...
         IF(npart.GT.0) THEN	
            DO i = 1, npart
               DO J = 1, 4
                  ppp(j,i)    = real(dppp(j,i))
                  brppp(j,i)  = real(dbrppp(j,i))
               ENDDO
            ENDDO
         ENDIF
         
c     there may be  differences up to 0.1% at the parton level
c         if (abs((enesum/enebeams)-1.).gt.1.E-3) then
c            write(6,*) 'MCJETS: Warning Ehadrons,Ebeams=',
c     +           enesum,enebeams,enelectron
c         endif
         if (jdebu.eq.1) then
            print*,"npart hadron  ",npart
            do i = 1, npart
               print*,"breit hadron",brppp(1,i),brppp(2,i),
     +              brppp(3,i),brppp(4,i)      
            enddo
            do i = 1, npart
               print*,"lab hadron  ",ppp(1,i),ppp(2,i),
     +              ppp(3,i),ppp(4,i)      
            enddo
         endif
         
*     
*---------------massless--HADRONS----------------------------
         if (jfl_flag.gt.0) then
            call findjets(3212,jfl_flag,npart,ppp,etjetmc,
     +           etajmc,jpart,nhjets,pjet,efve,efvp,0,1,ierr)
             
            if (ierr.ne.0) then
               write(6,*) 'MCJETS: Findjets error
     +              in fmck jets',ierr
            endif         
            
            if (nhjets.gt.nhjets_max) then
               write(6,*)'MCJETS: Warning nhjets=',nhjets
               nhjets=nhjets_max
            endif
            if (jdebu.eq.1) print*,"no lab jets had ml",nhjets	
            do i=1,nhjets
               if (jdebu.eq.1) print*,"lab jets had ml",i,pjet(1,i),
     +              pjet(2,i),pjet(3,i),pjet(4,i)
               pxhjet(i)=pjet(1,i)
               pyhjet(i)=pjet(2,i)
               pzhjet(i)=pjet(3,i)
               ehjet(i)= pjet(4,i)
            enddo
            
*     pointer true info in fmcknt -> jet
            do j=1,fmck_nstor
               do i=1,npart
                  if (fmck_id(j).eq.partfmckid(i)) then
                     fmck_hadjet(j)=jpart(i)
                     goto 107
                  endif
               enddo	
 107           continue
            enddo
         endif
c     ----------------- massive -HADRONS--------------------
         
         if (jfm_flag.gt.0) then
            call findjets(3211,0,npart,ppp,etjetmc,
     +           etajmc,jpart,nhmjets,pjet,efve,efvp,0,1,ierr)
            if (ierr.ne.0) then
               write(6,*) 'MCJETS: Findjets error
     +              in fmck jets',ierr
            endif         
            
            if (nhmjets.gt.nhjets_max) then
               write(6,*)'MCJETS: Warning nhjets=',nhmjets
               nhmjets=nhjets_max
            endif
            
            if (jdebu.eq.1) print*,"n lab jets had massive",nhmjets	
            do i=1,nhmjets
               if (jdebu.eq.1) print*,"lab jets had massive",i,
     +              pjet(1,i),pjet(2,i),pjet(3,i),pjet(4,i)
               pxhmjet(i)=pjet(1,i)
               pyhmjet(i)=pjet(2,i)
               pzhmjet(i)=pjet(3,i)
               ehmjet(i)= pjet(4,i)
            enddo
            
            
*     pointer true-muon -> jet
	
C            do j=1,fmck_nstor
C	       write(6,*)"fmck_id(",j,") = ",fmck_id(j)
C            enddo
C            do i=1,npart
C	       write(6,*)"partfmckid(",i,") = ",partfmckid(i)	
C	    enddo
            do j=1,fmck_nstor
               do i=1,npart
                  if (fmck_id(j).eq.partfmckid(i)) then
                     fmck_mhadjet(j)=jpart(i)
C	       write(6,*)"fmck_mhadjet(",j,") = ",fmck_mhadjet(j)	
                     goto 117
                  endif
               enddo	
 117           continue
            enddo
         endif

*---  breitframe--massless-----HADRONS-------------------------
         if (jfl_flag.gt.0) then
            call findjets(3212,jfl_flag,npart,brppp,bretjetmc,
     +           bretajmc,brjpart,nbrhjets,brpjet,efve,efvp,0,4,ierr)
            
            if (ierr.ne.0) then
               write(6,*) 'MCJETS: Findjets error
     +              in fmck jets',ierr
            endif         
            
            if (nbrhjets.gt.nbrhjets_max) then
               write(6,*)'MCJETS: Warning nbrhjets=',nbrhjets
               nbrhjets=nbrhjets_max
            endif
C     boost jets back to labframe

            IF(nbrhjets.gt.0) THEN
               DO I = 1, nbrhjets
                  DO J = 1, 4
                     dbrpjet(j,i) = dble(brpjet(j,i)) 
                  ENDDO
               ENDDO
            ELSE
C               WRITE(*,*)'*** BOOSTJETS: NO JET TO BOOST!'
               RETURN
            ENDIF
C     
            CALL KTBREI(BREIT_TO_LAB, ! BOOST MODALITY
     +           PLEP,          ! INCOMING LEPTON PZ
     +           PHAD,          ! INCOMING HADRON PZ
     +           LEPTON,        ! OUTCOMING LEPTON 4-P
     +           nbrhjets,      ! NO OF JETS
     +           dbrpjet,       ! BREIT FRAME JETS
     +           dlabpjet,      ! LAB FRAME JETS
     +           *998)          ! WARNING MESSAGE
            
            
C     save to ntuple
            
            if (jdebu.eq.1) print*,"n breit jets had ml",nbrhjets	
            do i=1,nbrhjets
               pxbrhjet(i)=real(dlabpjet(1,i))
               pybrhjet(i)=real(dlabpjet(2,i))
               pzbrhjet(i)=real(dlabpjet(3,i))
               ebrhjet(i) =real(dlabpjet(4,i))
               if (jdebu.eq.1) print*,"breit jets had ml",i,
     +              pxbrhjet(i),pybrhjet(i),pzbrhjet(i),ebrhjet(i)
            enddo
            
*     pointer true info in fmcknt -> jet
            do j=1,fmck_nstor
               do i=1,npart
                  if (fmck_id(j).eq.partfmckid(i)) then
                     fmck_brhadjet(j)=brjpart(i)
                     goto 307
                  endif
               enddo	
 307           continue
            enddo
         endif
         
c     -----breitframe-- massive ----HADRONS-----------------
         
         if (jfm_flag.gt.0) then
            call findjets(3211,0,npart,brppp,bretjetmc,
     +           bretajmc,brjpart,nbrhmjets,brpjet,efve,efvp,0,4,ierr)
            if (ierr.ne.0) then
               write(6,*) 'MCJETS: Findjets error
     +              in fmck jets',ierr
            endif         
            
            if (nbrhmjets.gt.nbrhjets_max) then
               write(6,*)'MCJETS: Warning nbrhmjets=',nbrhmjets
               nbrhmjets=nbrhjets_max
            endif
            
C     boost jets back to labframe

            IF(nbrhmjets.gt.0) THEN
               DO I = 1, nbrhmjets
                  DO J = 1, 4
                     dbrpjet(j,i) = dble(brpjet(j,i)) 
                  ENDDO
               ENDDO
            ELSE
               WRITE(*,*)'*** BOOSTJETS: NO JET TO BOOST!'
               RETURN
            ENDIF
C     
            CALL KTBREI(BREIT_TO_LAB, ! BOOST MODALITY
     +           PLEP,          ! INCOMING LEPTON PZ
     +           PHAD,          ! INCOMING HADRON PZ
     +           LEPTON,        ! OUTCOMING LEPTON 4-P
     +           nbrhmjets,     ! NO OF JETS
     +           dbrpjet,       ! BREIT FRAME JETS
     +           dlabpjet,      ! LAB FRAME JETS
     +           *998)          ! WARNING MESSAGE
            
            
C     save to ntuple
            
            if (jdebu.eq.1) print*,"n breit jets had mass",nbrhmjets	
            if (nbrhmjets.gt.0) then
               do i=1,nbrhmjets
                  pxbrhmjet(i)=real(dlabpjet(1,i))
                  pybrhmjet(i)=real(dlabpjet(2,i))
                  pzbrhmjet(i)=real(dlabpjet(3,i))
                  ebrhmjet(i) =real(dlabpjet(4,i))
                  if (jdebu.eq.1) print*,"breit jets had mass",i,
     +                 pxbrhmjet(i),pybrhmjet(i),pzbrhmjet(i),
     +                 ebrhmjet(i)
               enddo
            endif
            
*     pointer true-muon -> jet
            do j=1,fmck_nstor
               do i=1,npart
                  if (fmck_id(j).eq.partfmckid(i)) then
                     fmck_brmhadjet(j)=brjpart(i)
                     goto 317
                  endif
               enddo	
 317           continue
            enddo
         endif
         
         
C-------------------------------------------------------------
C     HADRONS WITH B MESON BEFORE DECAY
C-------------------------------------------------------------
c     now with beauty before decay
         
         npart=0
         ibs=0
         elec_flag=0
         enesum=enelectron
         call vzero(dontake,512)
         idontake=0
         do 101  i = 1, nfmck     
            call FetTab(FMCKIN,ID,I)
            ibs=0
c     skip if from a cascade decay from beauty/charm
            if (fmckin_daughterof.gt.0) then
               do k=1,idontake
                  if (dontake(k).eq.fmckin_daughterof) then
                     idontake=idontake+1
                     if (idontake.gt.512) idontake=1
                     dontake(idontake)=i
                     goto 101
                  endif
               enddo
            endif
c     keep if beauty (and tag it to skip its daughters) 
            do k=1,nbrange
               if (FMCKIN_fmcprt.ge.brange(1,k).and.
     +              FMCKIN_fmcprt.le.brange(2,k)) then
                  idontake=idontake+1
                  if(FMCKIN_fmcprt.eq.73.or.FMCKIN_fmcprt.eq.75.or.
     +                 FMCKIN_fmcprt.eq.214.or.FMCKIN_fmcprt.eq.468.or.
     +                 FMCKIN_fmcprt.eq.470.or.FMCKIN_fmcprt.eq.481.or.
     +                 FMCKIN_fmcprt.eq.482.or.FMCKIN_fmcprt.eq.484.or.
     +                 FMCKIN_fmcprt.eq.486.or.FMCKIN_fmcprt.eq.488.or.
     +                 FMCKIN_fmcprt.eq.490.or.FMCKIN_fmcprt.eq.492.or.
     +                 FMCKIN_fmcprt.eq.494.or.FMCKIN_fmcprt.eq.497.or.
     +                 FMCKIN_fmcprt.eq.500.or.FMCKIN_fmcprt.eq.504.or.
     +                 FMCKIN_fmcprt.eq.509) then
                     ibs=9
                  else
                     ibs=10
                  endif
                  if (idontake.gt.512) idontake=1
                  dontake(idontake)=i
                  goto 98
               endif
            enddo
c     keep if charm and tag it 
            do k=1,ncrange
               if (FMCKIN_fmcprt.ge.crange(1,k).and.
     +              FMCKIN_fmcprt.le.crange(2,k)) then
                  idontake=idontake+1
                  if(FMCKIN_fmcprt.eq.64.or.FMCKIN_fmcprt.eq.66.or.
     +                 FMCKIN_fmcprt.eq.68.or.FMCKIN_fmcprt.eq.208.or.
     +                 FMCKIN_fmcprt.eq.210.or.
     +                 FMCKIN_fmcprt.eq.466) then
                     ibs=7
                  else
                     ibs=8
                  endif
                  if (idontake.gt.512) idontake=1
                  dontake(idontake)=i
                  goto 98
               endif
            enddo
            
c     keep all decayed hadrons (but first electron)
            if (mod(FMCKIN_isthep,10000).eq.1) then
               if ((FMCKIN_fmcprt.eq.23.or.FMCKIN_fmcprt.eq.24) 
     &              .and.elec_flag.eq.0 )then
                  elec_flag = 1
                  goto 101
               endif
            else
               goto 101
            endif
            
 98         continue
            
            npart = npart + 1
            if( npart.gt.512 )then
               write(*,*)'KTJETS: Too many particles in FMCKIN!'
               goto 101
            endif
C     ppp(1,npart) = FMCKIN_p(1)
C     ppp(2,npart) = FMCKIN_p(2)
C     ppp(3,npart) = FMCKIN_p(3)
C     ppp(4,npart) = FMCKIN_p(4)
	    dppp(1,npart) = dble(FMCKIN_p(1))
            dppp(2,npart) = dble(FMCKIN_p(2))
            dppp(3,npart) = dble(FMCKIN_p(3))
            dppp(4,npart) = dble(FMCKIN_p(4))
            
            partfmckid(npart) = FMCKIN_ID
            ipart(npart) = ibs
            enesum=enesum+FMCKIN_P(4)
            
 101     continue
         
C     boost particle to breitframe
         
         IF(npart.GT.0) THEN
            CALL KTBREI(LAB_TO_BREIT, ! BOOST MODALITY
     +           PLEP,          ! INCOMING LEPTON PZ
     +           PHAD,          ! INCOMING HADRON PZ
     +           LEPTON,        ! OUTCOMING LEPTON 4-P
     +           npart,         ! NO OF HADRONS
     +           dppp,          ! LAB FRAME HADRONS (double)
     +           dbrppp,        ! BREIT FRAME HADRONS (double)
     +           *998)          ! WARNING MESSAGE
         ELSE
            WRITE(*,*)'*** BOOSTHADRONS: NO HADRONS TO BOOST!'
         ENDIF
C     cast to real for findjets...
         DO i = 1, npart
            DO J = 1, 4
               ppp(j,i)         = real(dppp(j,i))
C     lappp(j,i)       = real(dlappp(j,i))
               brppp(j,i)       = real(dbrppp(j,i))
            ENDDO
         ENDDO
C     
         if (abs((enesum/enebeams)-1.).gt.1.E-3) then
            write(6,*) 'MCJETS: Warning Ehadrons (B und.),
     +           Ebeams=', enesum,enebeams,enelectron
         endif
         
         if (jdebu.eq.1) then
            print*,"npart bhadrons  ",npart
            do i = 1, npart
               print*,"breit ",brppp(1,i),brppp(2,i),brppp(3,i),
     +              brppp(4,i)      
            enddo
            do i = 1, npart
               print*,"lab ",ppp(1,i),ppp(2,i),ppp(3,i),
     +              ppp(4,i)      
            enddo
         endif
         
*---------------massless --B HADRONS----------------        
         
         if (jfl_flag.gt.0) then
            call findjets(3212,jfl_flag,npart,ppp,etjetmc,
     +           etajmc,jpart,nhbjets,pjet,efve,efvp,0,1,ierr)
            if (ierr.ne.0) then
               write(6,*) 'MCJETS: Findjets error
     +              in b undecayed hadron jets',ierr
            endif         
            
            
            if (nhbjets.gt.nhjets_max) then
               write(6,*)'MCJETS: Warning nhjets=',nhjets
               nhbjets=nhjets_max
            endif
            if (jdebu.eq.1) print*,"n lab jets bhad ml",nhbjets	

            call uzero(pid,1,nhbjets_max*512)
            do i=1,nhbjets
*     Changed by Verena Schoenberg (12/12/2008):
*     Store number of particles (i.e. stable B/C hadrons) per jet
*     and their FMCKIN IDs              
               np(i)=0
               pflag(i)=0
               do j=1,npart
                  if (jpart(j).eq.i) then 
                     if (ipart(j).eq.9.or.ipart(j).eq.10 ) then
                        pflag(i) = ipart(j)
                     else if (ipart(j).eq.7.or.ipart(j).eq.8 ) then
                        pflag(i) = ipart(j)
                     endif
                     np(i) = np(i)+1
                     if (np(i).le.nphbjets_max) then
                        pid(np(i),i) = partfmckid(j)
                     endif
                  endif
               enddo

	       if (jdebu.eq.1) print*,"lab jets bhad ml",i,
     +              pjet(1,i),pjet(2,i),pjet(3,i),pjet(4,i)
               pxhbjet(i)=pjet(1,i)
               pyhbjet(i)=pjet(2,i)
               pzhbjet(i)=pjet(3,i)
               ehbjet(i)=pjet(4,i)
               nphbjet(i)=np(i)
               flhbjet(i)=pflag(i)
               call ucopy(pid,phbjet,5120)
            enddo
            
*     pointer true-muon -> jet
            do j=1,fmck_nstor
               do i=1,npart
                  if (fmck_id(j).eq.partfmckid(i)) then
                     fmck_bhadjet(j)=jpart(i)
                     goto 127
                  endif
               enddo	
 127           continue
            enddo
         endif
         
*     -------------- massive ---B HADRONS-------------------------
         
         if (jfm_flag.gt.0) then
            call findjets(3211,0,npart,ppp,etjetmc,
     +           etajmc,jpart,nhbmjets,pjet,efve,efvp,0,1,ierr)
            if (ierr.ne.0) then
               write(6,*) 'MCJETS: Findjets error
     +              in b undecayed hadron jets',ierr
            endif         

            
            if (nhbmjets.gt.nhjets_max) then
               write(6,*)'MCJETS: Warning nhjets=',nhjets
               nhbmjets=nhjets_max
            endif
            
            if (jdebu.eq.1) print*,"no breit jets bhad mass",nhjets	

            call uzero(pid,1,nhbmjets_max*512)

            do i=1,nhbmjets
*     Changed by Verena Schoenberg (12/12/2008):
*     Store number of particles (i.e. stable B/C hadrons) per jet
*     and their FMCKIN IDs              
               np(i)=0
               pflag(i)=0
               do j=1,npart
                  if (jpart(j).eq.i) then 
                     if (ipart(j).eq.9.or.ipart(j).eq.10 ) then
                        pflag(i) = ipart(j)
                     else if (ipart(j).eq.7.or.ipart(j).eq.8 ) then
                        pflag(i) = ipart(j)
                     endif
                     np(i) = np(i)+1
                     if (np(i).le.nphbmjets_max) then
                        pid(np(i),i) = partfmckid(j)
                     endif
                  endif
               enddo

               if (jdebu.eq.1) print*,"lab jets bhad mass",i,
     +              brpjet(1,i),pjet(2,i),pjet(3,i),pjet(4,i)
               pxhbmjet(i)=pjet(1,i)
               pyhbmjet(i)=pjet(2,i)
               pzhbmjet(i)=pjet(3,i)
               ehbmjet(i) =pjet(4,i)
               nphbmjet(i)=np(i)
               flhbmjet(i)=pflag(i)
               call ucopy(pid,phbmjet,5120)
            enddo
            
*     pointer true-muon -> jet
            do j=1,fmck_nstor
               do i=1,npart
                  if (fmck_id(j).eq.partfmckid(i)) then
                     fmck_mbhadjet(j)=jpart(i)
                     goto 137
                  endif
               enddo	
 137           continue
            enddo
         endif
*---  breitframe--massless --B HADRONS----------------        
         
         if (jfl_flag.gt.0) then
            call findjets(3212,jfl_flag,npart,brppp,bretjetmc,
     +           bretajmc,brjpart,nbrhbjets,brpjet,efve,efvp,0,4,ierr)
            if (ierr.ne.0) then
               write(6,*) 'MCJETS: Findjets error
     +              in b undecayed hadron jets',ierr
            endif         
            
            if (nbrhbjets.gt.nbrhjets_max) then
               write(6,*)'MCJETS: Warning nbrhbjets=',nbrhbjets
               nbrhbjets=nbrhjets_max
            endif

C     boost jets back to labframe
            
            IF(nbrhbjets.gt.0) THEN
               DO I = 1, nbrhbjets
                  DO J = 1, 4
                     dbrpjet(j,i) = dble(brpjet(j,i)) 
                  ENDDO
               ENDDO
            ELSE
               WRITE(*,*)'*** BOOSTJETS: NO JET TO BOOST!'
               RETURN
            ENDIF
C     
            CALL KTBREI(BREIT_TO_LAB, ! BOOST MODALITY
     +           PLEP,          ! INCOMING LEPTON PZ
     +           PHAD,          ! INCOMING HADRON PZ
     +           LEPTON,        ! OUTCOMING LEPTON 4-P
     +           nbrhbjets,     ! NO OF JETS
     +           dbrpjet,       ! BREIT FRAME JETS
     +           dlabpjet,      ! LAB FRAME JETS
     +           *998)          ! WARNING MESSAGE


C save to ntuple

            if (jdebu.eq.1) print*,"n breit jets bhad ml",nbrhbjets	
            if (nbrhbjets.gt.0) then
               do i=1,nbrhbjets
                  pxbrhbjet(i)=real(dlabpjet(1,i))
                  pybrhbjet(i)=real(dlabpjet(2,i))
                  pzbrhbjet(i)=real(dlabpjet(3,i))
                  ebrhbjet(i) =real(dlabpjet(4,i))
                  if (jdebu.eq.1) print*,"breit jets bhad ml",i,
     +                 pxbrhbjet(i),pybrhbjet(i),pzbrhbjet(i),
     +                 ebrhbjet(i)
               enddo
            endif
            
*     pointer true-muon -> jet
            do j=1,fmck_nstor
               do i=1,npart
                  if (fmck_id(j).eq.partfmckid(i)) then
                     fmck_brbhadjet(j)=brjpart(i)
                     goto 327
                  endif
               enddo	
 327           continue
            enddo
         endif
         
*     --breitframe-- massive --B HADRONS--------------------------
         
         if (jfm_flag.gt.0) then
            call findjets(3211,0,npart,brppp,bretjetmc,
     +           bretajmc,brjpart,nbrhbmjets,brpjet,efve,efvp,0,4,ierr)
            if (ierr.ne.0) then
               write(6,*) 'MCJETS: Findjets error
     +              in b undecayed hadron jets',ierr
            endif         
            
            
            if (nbrhbmjets.gt.nbrhjets_max) then
               write(6,*)'MCJETS: Warning nbrhbmjets=',nbrhbmjets
               nbrhbmjets=nbrhjets_max
            endif
            
C     boost jets back to labframe
            
            IF(nbrhbmjets.gt.0) THEN
               DO I = 1, nbrhbmjets
                  DO J = 1, 4
                     dbrpjet(j,i) = dble(brpjet(j,i)) 
                  ENDDO
               ENDDO
            ELSE
               WRITE(*,*)'*** BOOSTJETS: NO JET TO BOOST!'
               RETURN
            ENDIF
C     
            CALL KTBREI(BREIT_TO_LAB, ! BOOST MODALITY
     +           PLEP,          ! INCOMING LEPTON PZ
     +           PHAD,          ! INCOMING HADRON PZ
     +           LEPTON,        ! OUTCOMING LEPTON 4-P
     +           nbrhbmjets,    ! NO OF JETS
     +           dbrpjet,       ! BREIT FRAME JETS
     +           dlabpjet,      ! LAB FRAME JETS
     +           *998)          ! WARNING MESSAGE
            
            
C     save to ntuple
            
            if (jdebu.eq.1) print*,"n breit jets bhad mass",nbrhbmjets	
            if (nbrhbmjets.gt.0)then
               do i=1,nbrhbmjets
                  pxbrhbmjet(i)=real(dlabpjet(1,i))
                  pybrhbmjet(i)=real(dlabpjet(2,i))
                  pzbrhbmjet(i)=real(dlabpjet(3,i))
                  ebrhbmjet(i) =real(dlabpjet(4,i))
                  if (jdebu.eq.1) print*,"breit jets bhad mass",i,
     +                 pxbrhbmjet(i),pybrhbmjet(i),pzbrhbmjet(i),
     +                 ebrhbmjet(i)
               enddo
            endif
            
*     pointer true-muon -> jet
            do j=1,fmck_nstor
               do i=1,npart
                  if (fmck_id(j).eq.partfmckid(i)) then
                     fmck_brmbhadjet(j)=brjpart(i)
                     goto 337
                  endif
               enddo	
 337           continue
            enddo
         endif
         
C     ---------------------------------------------------------
c     THE PARTON LEVEL
C     ---------------------------------------------------------


         idontake=0
         npart=0
         enesum=enelectron
c     pythia:
         if (igen.lt.3.or.igen.eq.6) then
c     take all the partons between the electron and
c     the first string!
            elec_flag=0
            first_parton=0
            do i = 1, nfmck     
               call FetTab(FMCKIN,ID,I)
               if (jdebu.eq.1) print*,i,FMCKIN_fmcprt,
     +              FMCKIN_isthep,FMCKIN_daughterof
               if (jdebu.eq.1) print*,"  ",FMCKIN_p
               if (mod(FMCKIN_isthep,10000).eq.1.and.
     +              (FMCKIN_fmcprt.eq.23.or.FMCKIN_fmcprt.eq.24).and. 
     +              elec_flag.eq.0)  then
                  if (jdebu.eq.1) print*,i,'electron' 
                  elec_flag=i
                  if (first_parton.eq.0) first_parton=i
c     take the partons:
               else if ((first_parton.gt.0.and.
     +                 FMCKIN_daughterof.lt.first_parton).or.
c     and the ISR photons
     +                 (first_parton.le.0.and.mod(FMCKIN_isthep,10000)
     +                 .eq.1.and.FMCKIN_fmcprt.eq.29).or.
c     and sometimes a remnant hadron
     +                 (first_parton.le.0.and.mod(FMCKIN_isthep,10000)
     +                 .le.2.and.FMCKIN_fmcprt.ge.54)) then
                  if (jdebu.eq.1) print*,i,'taken'
                  npart = npart + 1
                  if( npart.gt.512 )then
                     write(*,*)'KTJETS: Too many particles in FMCKIN!'
                     goto 122
                  endif
C     ppp(1,npart) = FMCKIN_p(1)
C     ppp(2,npart) = FMCKIN_p(2)
C     ppp(3,npart) = FMCKIN_p(3)
C     ppp(4,npart) = FMCKIN_p(4)
                  dppp(1,npart) = dble(FMCKIN_p(1))
                  dppp(2,npart) = dble(FMCKIN_p(2))
                  dppp(3,npart) = dble(FMCKIN_p(3))
                  dppp(4,npart) = dble(FMCKIN_p(4))
                  if (jdebu.eq.1) 
     +                 print*,i,'next', first_parton,elec_flag
                  ipart(npart) = FMCKIN_FMCprt
                  partfmckid(npart) = FMCKIN_ID
                  enesum=enesum+ FMCKIN_p(4)
                  if (FMCKIN_fmcprt.ne.29.and.first_parton.eq.0) then
                     first_parton=i
                  endif
               else if (first_parton.gt.0.and.FMCKIN_fmcprt.ge.54) then
                  goto 122
               endif
               if (jdebu.eq.1) print*,i,'next', first_parton,elec_flag
            enddo
 122        continue
         else if (igen.eq.3.or.igen.gt.6) then
c     herwig:          
c     take all the partons  with isthep=2 befor the first cluster
            elec_flag=0
            do i = 1, nfmck     
               call FetTab(FMCKIN,ID,I)
               if (mod(FMCKIN_isthep,10000).ge.160) goto 123
               if (FMCKIN_isthep.eq.2) then
                  npart = npart + 1
                  if( npart.gt.512 )then
                     write(*,*)'KTJETS: Too many particles in FMCKIN!'
                     goto 123
                  endif
C     ppp(1,npart) = FMCKIN_p(1)
C     ppp(2,npart) = FMCKIN_p(2)
C     ppp(3,npart) = FMCKIN_p(3)
C     ppp(4,npart) = FMCKIN_p(4)
                  dppp(1,npart) = dble(FMCKIN_p(1))
                  dppp(2,npart) = dble(FMCKIN_p(2))
                  dppp(3,npart) = dble(FMCKIN_p(3))
                  dppp(4,npart) = dble(FMCKIN_p(4))
	          ipart(npart) = FMCKIN_FMCprt
                  partfmckid(npart) = FMCKIN_ID
                  enesum=enesum+ FMCKIN_p(4)
               endif
            enddo
 123        continue 
         else
            goto 777
         endif
C     boost particles to breitframe
         
      IF(npart.GT.0) THEN
         CALL KTBREI(LAB_TO_BREIT, ! BOOST MODALITY
     +        PLEP,             ! INCOMING LEPTON PZ
     +        PHAD,             ! INCOMING HADRON PZ
     +        LEPTON,           ! OUTCOMING LEPTON 4-P
     +        npart,            ! NO OF HADRONS
     +        dppp,             ! LAB FRAME HADRONS (double)
     +        dbrppp,           ! BREIT FRAME HADRONS (double)
     +        *998)             ! WARNING MESSAGE
      ELSE
         WRITE(*,*)'*** BOOSTHADRONS: NO HADRONS TO BOOST!'
      ENDIF
C     cast to real for findjets...
      DO i = 1, npart
         DO J = 1, 4
            ppp(j,i)     = real(dppp(j,i))
            brppp(j,i)   = real(dbrppp(j,i))
         ENDDO
      ENDDO
C
      if (jdebu.eq.1) then
	 print*,"npart parton  ",npart
         if(npart.gt.0) then
            do i = 1, npart
               print*,"breit ",brppp(1,i),brppp(2,i),brppp(3,i),
     +              brppp(4,i)      
            enddo
            do i = 1, npart
               print*,"lab ",ppp(1,i),ppp(2,i),ppp(3,i),
     +              ppp(4,i)      
            enddo
         endif
      endif
      if (abs((enesum/enebeams)-1.).gt.1.E-3) then
         if (ipritab.lt.100) then
            write(6,*) 'MCJETS: Warning Epartons,Ebeams,Eele=',
     +           enesum,enebeams,Enelectron
            call setfor(fmckin,'ISTHEP','I12')
            call pritab(fmckin,id,1,nfmck,allcol)
            ipritab=ipritab+1
         endif
      endif
      
*     ------------------massless---PARTONS---------------------------
         if (jfl_flag.gt.0) then
            
            call findjets(3212,jfl_flag,npart,ppp,etjpart,
     +           etajpart,jpart,npjets,pjet,efve,efvp,0,1,ierr)
            if (ierr.ne.0) then
               write(6,*) 'MCJETS: Findjets error
     +              in parton jets',ierr
            endif         
            
            if (npjets.gt.nhjets_max) then
               write(6,*)'MCJETS: Warning nhjets=',nhjets
               npjets=nhjets_max
            endif
            if (jdebu.eq.1) print*,"n lab jets parton ml",npjets	
            do i=1,npjets
               if (jdebu.eq.1) print*,"lab jets parton ml",i,
     +              pjet(1,i),pjet(2,i),pjet(3,i),pjet(4,i)
               pxpjet(i)=pjet(1,i)
               pypjet(i)=pjet(2,i)
               pzpjet(i)=pjet(3,i)
               epjet(i)=pjet(4,i)
            enddo
            
*     pointer true-muon -> jet
            do j=1,fmck_nstor
               do i=1,npart
                  if (fmck_id(j).eq.partfmckid(i)) then
                     fmck_partjet(j)= jpart(i)
                     goto 147
                  endif
               enddo	
 147           continue
            enddo
         endif

            
*     ------------------massive--PARTONS----------------------------
         
         if (jfm_flag.gt.0) then
            call findjets(3211,0,npart,ppp,etjpart,
     +           etajpart,jpart,npmjets,pjet,efve,efvp,0,1,ierr)
            if (ierr.ne.0) then
               write(6,*) 'MCJETS: Findjets error
     +              in parton jets',ierr
            endif         

            
            if (npmjets.gt.nhjets_max) then
               write(6,*)'MCJETS: Warning nhjets=',nhjets
               npmjets=nhjets_max
            endif
            if (jdebu.eq.1) print*,"n lab jets parton massive",npmjets	
            do i=1,npmjets
               if (jdebu.eq.1) print*,"lab jets parton massive",i,
     +              pjet(1,i),pjet(2,i),pjet(3,i),pjet(4,i)
               pxpmjet(i)=pjet(1,i)
               pypmjet(i)=pjet(2,i)
               pzpmjet(i)=pjet(3,i)
               epmjet(i)=pjet(4,i)
            enddo
            
*     pointer true-muon -> jet
            do j=1,fmck_nstor
               do i=1,npart
                  if (fmck_id(j).eq.partfmckid(i)) then
                     fmck_mpartjet(j)=jpart(i)
                     goto 157
                  endif
               enddo	
 157           continue
            enddo
         endif
         
*     --breitframe------massless--PARTONS--------------------------
         if (jfl_flag.gt.0) then
            
            call findjets(3212,jfl_flag,npart,brppp,bretjpart,
     +           bretajpart,brjpart,nbrpjets,brpjet,efve,efvp,0,4,ierr)
            if (ierr.ne.0) then
               write(6,*) 'MCJETS: Findjets error
     +              in parton jets',ierr
            endif         
            
            if (nbrpjets.gt.nbrhjets_max) then
               write(6,*)'MCJETS: Warning nbrpjets=',nbrpjets
               nbrpjets=nbrhjets_max
            endif
            
C     boost jets back to labframe

            IF(nbrpjets.gt.0) THEN
               DO I = 1, nbrpjets
                  DO J = 1, 4
                     dbrpjet(j,i) = dble(brpjet(j,i)) 
                  ENDDO
               ENDDO
            ELSE
               WRITE(*,*)'*** BOOSTJETS: NO JET TO BOOST!'
               RETURN
            ENDIF
C     
            do i=1, nbrpjets
               if (jdebu.eq.1) print*,"breit before backb jets
     +              parton ml",i,dbrpjet(1,i),dbrpjet(2,i),
     +              dbrpjet(3,i),dbrpjet(4,i)
            enddo
            CALL KTBREI(BREIT_TO_LAB, ! BOOST MODALITY
     +           PLEP,          ! INCOMING LEPTON PZ
     +           PHAD,          ! INCOMING HADRON PZ
     +           LEPTON,        ! OUTCOMING LEPTON 4-P
     +           nbrpjets,      ! NO OF JETS
     +           dbrpjet,       ! BREIT FRAME JETS
     +           dlabpjet,      ! LAB FRAME JETS
     +           *998)          ! WARNING MESSAGE
            
            
C     save to ntuple
            if (jdebu.eq.1) print*,"no breit jets parton ml",nbrpjets	
            if (nbrpjets.gt.0) then
               do i=1,nbrpjets
                  pxbrpjet(i)=real(dlabpjet(1,i))
                  pybrpjet(i)=real(dlabpjet(2,i))
                  pzbrpjet(i)=real(dlabpjet(3,i))
                  ebrpjet(i) =real(dlabpjet(4,i))
                  if (jdebu.eq.1) print*,"breit jets parton ml",i,
     +                 pxbrpjet(i),pybrpjet(i),pzbrpjet(i),ebrpjet(i)
               enddo
            endif
            
*     pointer true-muon -> jet
            do j=1,fmck_nstor
               do i=1,npart
                  if (fmck_id(j).eq.partfmckid(i)) then
                     fmck_brpartjet(j)=brjpart(i)
                     goto 347
                  endif
               enddo	
 347           continue
            enddo
         endif

            
*     --breitframe------massive---PARTONS---------------------------
         
         if (jfm_flag.gt.0) then
            call findjets(3211,0,npart,brppp,bretjpart,
     +           bretajpart,brjpart,nbrpmjets,brpjet,efve,efvp,0,4,ierr)
            if (ierr.ne.0) then
               write(6,*) 'MCJETS: Findjets error
     +              in parton jets',ierr
            endif         
            
            
            if (nbrpmjets.gt.nbrhjets_max) then
               write(6,*)'MCJETS: Warning nbrpmjets=',nbrpmjets
               nbrpmjets=nbrhjets_max
            endif
            
C   boost jets back to labframe
            
            IF(nbrpmjets.gt.0) THEN
               DO I = 1, nbrpmjets
                  DO J = 1, 4
                     dbrpjet(j,i) = dble(brpjet(j,i)) 
                  ENDDO
               ENDDO
            ELSE
               WRITE(*,*)'*** BOOSTJETS: NO JET TO BOOST!'
               RETURN
            ENDIF
C     
            CALL KTBREI(BREIT_TO_LAB, ! BOOST MODALITY
     +           PLEP,          ! INCOMING LEPTON PZ
     +           PHAD,          ! INCOMING HADRON PZ
     +           LEPTON,        ! OUTCOMING LEPTON 4-P
     +           nbrpmjets,     ! NO OF JETS
     +           dbrpjet,       ! BREIT FRAME JETS
     +           dlabpjet,      ! LAB FRAME JETS
     +           *998)          ! WARNING MESSAGE
            
            
C     save to ntuple
            
            if (jdebu.eq.1) print*,"n breit jets parton massive",nbrpmjets	
            if (nbrpmjets.gt.0) then
               do i=1,nbrpmjets
                  pxbrpmjet(i)=real(dlabpjet(1,i))
                  pybrpmjet(i)=real(dlabpjet(2,i))
                  pzbrpmjet(i)=real(dlabpjet(3,i))
                  ebrpmjet(i) =real(dlabpjet(4,i))
                  if (jdebu.eq.1) print*,"breit jets parton massive",i,
     +                 pxbrpmjet(i),pybrpmjet(i),pzbrpmjet(i),
     +                 ebrpmjet(i)
               enddo
            endif

*     pointer true-muon -> jet
            do j=1,fmck_nstor
               do i=1,npart
                  if (fmck_id(j).eq.partfmckid(i)) then
                     fmck_brmpartjet(j)=brjpart(i)
                     goto 357
                  endif
               enddo	
 357           continue
            enddo
         endif
         
      endif

 777  continue

      return
 998  WRITE(*,*)'*** BOOSTHADRONS: WARNING FROM KTBREI. '
      end













