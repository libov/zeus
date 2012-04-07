C. SETUP HBOOK FILES
      SUBROUTINE SHIST(PREF)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      CHARACTER * 40 PREF,FNAME       
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
*
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

      DOUBLE PRECISION sigtot,sigbreit,sigtotm,sigbreitm
      COMMON/RESULT/sigtot,sigbreit,sigtotm,sigbreitm
*
      Integer NJET
*
      INTEGER NWPAWC,ISTAT
      PARAMETER (NWPAWC=1000000)
      COMMON /PAWC/ H(NWPAWC)
*
      CALL IHIST

      NBIN=25
      PI=2*DACOS(0D0)
*
      write(6,*) '**hist: start histos ' 
*
      CALL HLIMIT(NWPAWC)
      CALL HROPEN(1,'HISTO',pref,'N',1024,ISTAT)
      call HLDIR('','L')
*
      GEN='HVQ'
*
      call hzb(1)
*
      RETURN
      END
*
*
C. FILL HBOOK FILES
*
      SUBROUTINE FHIST(WGT,P1,P2,P3)
*
C      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      IMPLICIT NONE
*
      DOUBLE PRECISION P1(0:3),P2(0:3),P3(0:3),PM1(0:3),PM2(0:3)
      LOGICAL PLOT
      COMMON/PLOTS/PLOT
      DOUBLE PRECISION XBJ,XIMIN,XM2,Q2
      COMMON/INVAR/XBJ,XIMIN,XM2,Q2
      DOUBLE PRECISION EPRO,EIEL
      COMMON/BEAM/EPRO,EIEL
      DOUBLE PRECISION ETAMIN,ETAMAX,PTMIN,PTMAX
      COMMON/CUTS/ETAMIN,ETAMAX,PTMIN,PTMAX
      INTEGER ISCALER,ISCALEF,IALPHAS,IFRAG
      COMMON/FLAGS/ISCALER,ISCALEF,IALPHAS,IFRAG
      DOUBLE PRECISION EPS,HFRAC,XMD
      integer ISL
      COMMON/FRAGP/EPS,HFRAC,XMD,ISL
      DOUBLE PRECISION  XI
      COMMON/MOMFRAC/XI
*
      Integer i,j
      DOUBLE PRECISION PPRO(4),PIEL(4),PSEL(4),PGAM(4)
      Integer NMAX
      Parameter (NMAX=10)
      DOUBLE PRECISION PLAB(4,NMAX),PBREIT(4,NMAX)
      DOUBLE PRECISION Pmom(4)
      DOUBLE PRECISION WGT,TMP
      DOUBLE PRECISION PT,ETA,KSI
      Real sum,delta
      DOUBLE PRECISION PT1,PT2,ETA1,ETA2,PT3,ETA3
      DOUBLE PRECISION PTM1,PTM2,ETAM1,ETAM2
      DOUBLE PRECISION W,Y
      DOUBLE PRECISION XM12,PHI12,PHI1,PHI2,PI
      Real dphi,delphi
      DOUBLE PRECISION FFAC
      DOUBLE PRECISION EPERP,SRAPID,DOT,PHI
      DOUBLE PRECISION ESEL,CTHSEL,STHSEL 
      DOUBLE PRECISION DVEC(10)
*
      Logical lp
C      Data lp/.true./
      Data lp/.false./
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

      DOUBLE PRECISION sigtot,sigbreit,sigtotm,sigbreitm
      COMMON/RESULT/sigtot,sigbreit,sigtotm,sigbreitm
*
      Integer NJET
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
      DOUBLE PRECISION JETSLAB(MAXHZJETS,8)
      DOUBLE PRECISION JETSEL(MAXHZJETS,8),JETSELLAB(MAXHZJETS,8)
*
C. FIRST CONSTRUCT P(PROTON) AND Q(PHOTON) IN LAB FRAME
C. H1 AND ZEUS TAKE PROTON IN +Z DIRECTION
      PPRO(4)=EPRO
      PPRO(1)=0D0
      PPRO(2)=0D0
      PPRO(3)=EPRO
C. AND INCIDENT ELECTRON IN -Z DIRECTION
      PIEL(4)=EIEL
      PIEL(1)=0D0
      PIEL(2)=0D0
      PIEL(3)=-EIEL
C. THE SCATTERED ELECTRON ENERGY AND ANGLE ARE GIVEN 
C. IN TERMS OF Q2,Y AND ENERGY OF INCIDENT ELECTRON
      W=DSQRT(Q2*(1D0-XBJ)/XBJ)
      Y=Q2/XBJ/(4*EPRO*EIEL)

*
C      ESEL  =(Q2+4D0*EIEL*EIEL*(1.-Y))/(4D0*EIEL)
C      CTHSEL=(Q2-4D0*EIEL*EIEL*(1.D0-Y))/(Q2+4D0*EIEL*EIEL*(1.D0-Y))
*

      ESEL  = Q2 / 4. / EIEL  +  (1.-y) * EIEL
      CTHSEL= Q2 / 2.D0 / EIEL / ESEL  -  1.D0 
*
C      write(6,*) ' esel= ',esel,' theta= ',acos(cthsel)*180./3.1415 
*
      STHSEL=DSQRT(1D0-CTHSEL*CTHSEL)
      PSEL(4)=ESEL
      PSEL(1)=0D0
      PSEL(2)=ESEL*STHSEL
      PSEL(3)=ESEL*CTHSEL
C. NOW TO FIND PHOTON FOUR VECTOR
      DO 10 I=1,4
 10   PGAM(I)=PIEL(I)-PSEL(I)
*
*
C      write(6,*) '**fhist: Q2= ',Q2,' x= ',xbj,' y= ',y
*
      if (lp) then 
       write(6,'(A,4f9.3)') ' PIEL= ',piel(1),piel(2),piel(3),piel(4)
       write(6,'(A,4f9.3)') ' PPRO= ',ppro(1),ppro(2),ppro(3),ppro(4)
       write(6,'(A,4f9.3)') ' PGAM= ',pgam(1),pgam(2),pgam(3),pgam(4)
       write(6,'(A,4f9.3)') ' PSEL= ',psel(1),psel(2),psel(3),psel(4)
       write(6,'(A,4f9.3)') '   P1= ',p1(1),p1(2),p1(3),p1(0)
       write(6,'(A,4f9.3)') '   P2= ',p2(1),p2(2),p2(3),p2(0)
       write(6,'(A,4f9.3)') '   P3= ',p3(1),p3(2),p3(3),p3(0)
       write(6,'(A,4f9.3)') ' PGES= ',psel(1)+p1(1)+p2(1)+p3(1),
     & psel(2)+p1(2)+p2(2)+p3(2),psel(3)+p1(3)+p2(3)+p3(3),
     & psel(4)+p1(0)+p2(0)+p3(0)
       write(6,*) ' E-Pz= ',
     & psel(4)+p1(0)+p2(0)+p3(0)-(psel(3)+p1(3)+p2(3)+p3(3)),
     & ' 2Ebeam= ',piel(4)*2
      endif
*
      nhep=0
      i=1
      PHEP(1,i)=0.
      PHEP(2,i)=0.
      PHEP(3,i)=EPRO
      PHEP(4,i)=EPRO
      ISTHEP(i)=3
      IDHEP(i)=2212
*
      i=2
      PHEP(1,i)=0.
      PHEP(2,i)=0.
      PHEP(3,i)=-EIEL
      PHEP(4,i)=EIEL
      ISTHEP(i)=3
      IDHEP(i)=-11
*                fill scattered electron
       i=4
       Do j=1,4
        PHEP(j,i)=PSEL(j)
       ENDDO
       ISTHEP(i)=1
       IDHEP(i)=-11
*
*                fill virtual boson
       i=3
       Do j=1,4
        PHEP(j,i)=PHEP(j,2)-PHEP(j,4)
       Enddo
       PHEP(5,i)=-PHEP(1,i)**2-PHEP(2,i)**2+
     &           -PHEP(3,i)**2+PHEP(4,i)**2
       if (PHEP(5,i).gt.0.)  PHEP(5,i)=sqrt(PHEP(5,i))
       ISTHEP(i)=3
       IDHEP(i)=22

*                fill incoming parton
*
      nhep=4
      nhep=nhep+1
      PHEP(1,nhep)=p1(1) 
      PHEP(2,nhep)=p1(2) 
      PHEP(3,nhep)=p1(3) 
      PHEP(4,nhep)=p1(0)
      PHEP(5,nhep)=-PHEP(1,nhep)**2-PHEP(2,nhep)**2+
     &             -PHEP(3,nhep)**2+PHEP(4,nhep)**2
      if (PHEP(5,nhep).gt.0.)  PHEP(5,nhep)=sqrt(PHEP(5,nhep))
      ISTHEP(nhep)=1
      IDHEP(nhep)=5
*
*
      nhep=nhep+1
      PHEP(1,nhep)=p2(1) 
      PHEP(2,nhep)=p2(2) 
      PHEP(3,nhep)=p2(3) 
      PHEP(4,nhep)=p2(0)
      PHEP(5,nhep)=-PHEP(1,nhep)**2-PHEP(2,nhep)**2+
     &             -PHEP(3,nhep)**2+PHEP(4,nhep)**2
      if (PHEP(5,nhep).gt.0.)  PHEP(5,nhep)=sqrt(PHEP(5,nhep))
      ISTHEP(nhep)=1
      IDHEP(nhep)=-5
*
      if (p3(1)+p3(2)+p3(3)+p3(0).gt.0.) then
       nhep=nhep+1
       PHEP(1,nhep)=p3(1) 
       PHEP(2,nhep)=p3(2) 
       PHEP(3,nhep)=p3(3) 
       PHEP(4,nhep)=p3(0)
       PHEP(5,nhep)=-PHEP(1,nhep)**2-PHEP(2,nhep)**2+
     &              -PHEP(3,nhep)**2+PHEP(4,nhep)**2
       if (PHEP(5,nhep).gt.0.)  PHEP(5,nhep)=sqrt(PHEP(5,nhep))
       ISTHEP(nhep)=1
       IDHEP(nhep)=0
      endif 
*
      wtx=wgt
      call hzb(2)
      wgt=wtx
*
 999  continue
      RETURN
      END
*
C. OUTPUT HBOOK FILES
      SUBROUTINE WHIST
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
*****
*
      call hzb(3)
*
      write(6,*) ' Output Histos here '
      call hcdir('//PAWC',' ')
      call hcdir('//HISTO',' ')
      CALL HROUT(0,ICYCLE,'T')
      CALL HREND('HISTO')
*
*****
*
      RETURN
      END




