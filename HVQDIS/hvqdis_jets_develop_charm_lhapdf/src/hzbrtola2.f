*CMZ :  1.02/01 22/10/98  16.25.20  by  Tancredi Carli
*CMZ :  1.01/15 24/04/98  14.23.19  by  Tancredi Carli
*-- Author :
      subroutine hzbrtola2(njets,jetsin,jetsout)
****************************************************
*                                                  *
* boost jets from Breit to Lab                     *
* Input: numjets number of jets                    *
* jetsin:  Jets in Breit frame                     *
* jetsout: jets in lab frame                       *
*                                                  *
* see ttjtfind for def of jets( , )                *
*                                                  *
* This routines assumes that the boost to the      *
* Breit frame has been done according to the       *
* convention in HZBRT not in KTBREI                *
* otherwise the component below have to be         *
* switched again                                   *
*                                                  *
****************************************************
      Implicit none
*
*KEEP,HEPEVTP.
*
* HEP event prime common
* (for explanation see manual)
      Integer NMXHEP
      PARAMETER (NMXHEP=2000)
      Integer NEVHEP,NHEP,ISTHEP,IDHEP
      Integer JMOHEP,JDAHEP
      Double Precision PHEP,VHEP
      COMMON/HEPEVTP/NEVHEP,NHEP,ISTHEP(NMXHEP),IDHEP(NMXHEP),
     & JMOHEP(2,NMXHEP),JDAHEP(2,NMXHEP),PHEP(5,NMXHEP),VHEP(4,NMXHEP)
*
*KEEP,HERACMN.
*
* HERA common
*
*     GEN: Name of generator
*     XSEC: total cross section (in pb)
*     IHCHRG: charge of particle/parton times 3
*     NTOT : Number of total events
*     WTX  : event weight
*
      Character*8 Gen
      Double Precision Xsec
      Integer ihchrg
      Real    wtx, Ntot
      Common /HERACMN/ Xsec, Gen, ihchrg(nmxhep), Ntot,wtx
*
*KEEP,HZFUNC.
*
* Function declarations for Hztool functions
*
          DOUBLE PRECISION HzPhmang
          DOUBLE PRECISION HzDiskin
          DOUBLE PRECISION HzPhokin
          DOUBLE PRECISION HZETA
          DOUBLE PRECISION HZPHI
          DOUBLE PRECISION HZET
          DOUBLE PRECISION HZPT
          DOUBLE PRECISION HZTHETA
          DOUBLE PRECISION hzeekin
          Integer hzeebeam
          Integer hzeegamn
          Integer HzIpgamn
          Integer HzIdelec
          Integer HzIpgam
          Integer HzIbeam
          Integer HzLchge
          Integer HzLcomp
          Integer HzIdntro
*
*KEEP,HZJETCMN.
*
*     MAXHZJETS: maxmial number of jet allowed
*     NUMJETS: number of jets from jet algo
*     NSEL  : number of selected jets
*     IPJET : pointer to selected jets
*     JETS  : Jet variables (eta,phi,et,e,px,py,pz,m) in choosen frame
*     IJETNO: pointer which objects in PHEP common belong to jets
*
      INTEGER MAXHZJETS
      PARAMETER (MAXHZJETS=50)
      INTEGER NSEL,NUMJETS,IPJET(MAXHZJETS),IJETNO(NMXHEP)
      DOUBLE PRECISION JETS(MAXHZJETS,8)
*
      COMMON /HZJETCMN/JETS,NUMJETS,NSEL,IPJET,IJETNO
*
*
*KEND.
*
      Integer i,j,k,ioff
      Logical lp
      Data lp/.false./
      DOUBLE PRECISION Jetsin(maxhzjets,8),Jetsout(maxhzjets,8)
      Character rout*13
      Data rout/'**hzbrtola'/
      Integer iel,idum,ierr,ibeam,njets
      DOUBLE PRECISION PLEP,PHAD,PEL(4),P(4,nmxhep)
      DOUBLE PRECISION empz,en,px,py,pz,rap,phi,pt
      DOUBLE PRECISION ETAMAX,EPS
      DATA ETAMAX,EPS/10,1E-6/
*
      if (lp) then
       write(6,*) rout,' njets= ',njets
      endif
*                     reset
      do i=1,nmxhep
       do j=1,4
        p(j,i)=0.
       enddo
      enddo
*
*     get electron and beams
*
      iel=HZIDELEC(idum)
      if (iel.eq.-1) then
       write(6,*) rout,' electron not found '
       return
      endif
*
      ierr=HZIBEAM(ibeam,idum)
      if (.not.(ierr.eq.1)) then
       write(6,*) rout,' beams not found ! '
       return
      endif
      Do i=1,4
       pel(i)=PHEP(i,iel)
      enddo
*
      ioff=0
*
      PHAD=PHEP(3,IBEAM)
      PLEP=PHEP(3,IDUM)
*
      if (PHAD.lt.800.) then
       write(6,*) ' Proton energy below 800 GeV'
       write(6,*) ' Please, make sure that you did not boost '
       write(6,*) ' the beam particles ! '
       write(6,*) ' -> The boost to the lab will be wrong ! '
      endif
*
*     Now  boost beam and electron from lab to Breit
*     for test purposes only
      if (ioff.ne.0) then
       Do i=1,4
        p(i,1)=PHEP(i,IBEAM)
        p(i,2)=PHEP(i,IDUM)
        P(i,3)=PHEP(i,iel)
       enddo
       call KTBREI(2,plep,phad,pel,ioff,P,P,*99)
      endif
*
*     Now  boost jets from Breit to lab
 
      Do i=1,njets
       P(4,i+ioff)=jetsin(i,4)
       P(1,i+ioff)=jetsin(i,5)
       P(2,i+ioff)=jetsin(i,6)
       P(3,i+ioff)=jetsin(i,7)
C       P(1,i+ioff)=-jetsin(i,5)
C       P(2,i+ioff)=-jetsin(i,6)
      enddo
*
      if (lp) then
       write(6,'(a,4f9.3)') ' Pel= ',pel
       write(6,'(2(a,f9.3))') ' plep= ',plep,' phad= ',phad
       do j=1,njets+ioff
        write(6,'(i3,a,4f9.3)') j,' p= ',(p(i,j),i=1,4)
       enddo
      endif
*
       call KTBREI(3,plep,phad,pel,njets+ioff,P,P,*99)
C       call KTBREI(1,plep,phad,pel,njets+ioff,P,P,*99)
*
C      if (lp) then
C       do j=1,njets+ioff
C        write(6,'(i3,a,4f9.3)') j,' q= ',(p(i,j),i=1,4)
C       enddo
C      endif
*
      do i=1,njets
       px=p(1,i+ioff)
       py=p(2,i+ioff)
       pz=p(3,i+ioff)
       en=p(4,i+ioff)
       pt=px**2+py**2
       empz=en**2-pz**2
*                 convert to eta a la KTCLUS (see ktmerg)
       IF (empz.LE.EPS*en**2) empz=pt
       IF (empz.GT.0.) THEN
        empz=0.5*LOG((en+ABS(pz))**2/empz)
        IF (empz.GT.ETAMAX) empz=ETAMAX+2.
       ELSE
        empz=ETAMAX+2.
       ENDIF
       rap=SIGN(empz,P(3,I+ioff))
       IF (px.NE.0.AND.py.NE.0) THEN
        phi=ATAN2(py,px)
C        write(6,*) i,'1 phi= ',phi
C        phi=ATAN(py/px)
C        write(6,*) i,'2 phi= ',phi
       ELSE
        phi=0.
       ENDIF
*
       if (pt.gt.0.) pt=sqrt(pt)
       Jetsout(i,1)=rap          ! eta
       Jetsout(i,2)=phi          ! phi
       Jetsout(i,3)=pt           ! Et
       Jetsout(i,4)=en           ! E
       Jetsout(i,5)=px           ! px
       Jetsout(i,6)=py           ! py
       Jetsout(i,7)=pz           ! pz
       Jetsout(i,8)=en**2-px**2-py**2-pz**2 ! m
       if (Jetsout(i,8).gt.0.) Jetsout(i,8)=sqrt(Jetsout(i,8))
*
      enddo
*
      if (lp) then
       do i=1,njets
        write(6,'(a,7(1x,f9.3))') 'jetsout= ',(jetsout(i,j),j=1,7)
       enddo
      endif
*
      return
 99   continue
      write(6,*) rout,' error on KTBREI ! '
      return
      end
