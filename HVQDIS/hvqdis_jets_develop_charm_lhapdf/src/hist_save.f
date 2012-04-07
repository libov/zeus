C. SETUP HBOOK FILES
      SUBROUTINE SHIST(PREF)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      CHARACTER * 40 PREF,FNAME       
*  
      INTEGER NWPAWC,ISTAT
      PARAMETER (NWPAWC=1000000)
      COMMON /PAWC/ H(NWPAWC)
*
      CALL IHIST

      NBIN=25
      PI=2*DACOS(0D0)
*
      write(6,*) ' start histos ' 
*
      CALL HLIMIT(NWPAWC)
      CALL HROPEN(1,'HISTO',pref,'N',1024,ISTAT)
*
       Call hcdir('//PAWC',' ')
       call hmdir('hist','S')
       Call hcdir('//HISTO',' ')
       call hmdir('hist','S')
*
      call Hbook1(1,' Sig_tot ',3,0.,3.,0.)
      call Hbook1(2,' Sig_tot Muon ',3,0.,3.,0.)
*
      call Hbook1(100,'H1 Pt1     ',20,0.,20.,0.)
      call Hbook1(101,'H1 Pt2     ',20,0.,20.,0.)
      call Hbook1(102,'H1 eta1    ',10,-3.,4.,0.)
      call Hbook1(103,'H1 eta2    ',10,-3.,4.,0.)
      call Hbook1(110,'H1 all Pt1 ',20,0.,20.,0.)
      call Hbook1(111,'H1 all Pt2 ',20,0.,20.,0.)
      call Hbook1(112,'H1 all eta1',10,-3.,4.,0.)
      call Hbook1(113,'H1 all eta2',10,-3.,4.,0.)
      call Hbook1(104,'H1 Q2      ',10,0.1,2.,0.)
      call Hbook1(105,'H1 y       ',10,0.01,1.,0.)
      call Hbook1(106,'H1 phi12   ',68,0.,3.4,0.)
*
      call Hbook1(120,'H1 Pt1      mu',20,0.,20.,0.)
      call Hbook1(121,'H1 Pt2      mu',20,0.,20.,0.)
      call Hbook1(122,'H1 eta1     mu',10,-3.,4.,0.)
      call Hbook1(123,'H1 eta2     mu',10,-3.,4.,0.)
      call Hbook1(120,'H1 all Pt1  mu',20,0.,20.,0.)
      call Hbook1(131,'H1 all Pt2  mu',20,0.,20.,0.)
      call Hbook1(132,'H1 all eta1 mu',10,-3.,4.,0.)
      call Hbook1(133,'H1 all eta2 mu',10,-3.,4.,0.)
      call Hbook1(124,'H1 Q2       mu',10,0.1,2.,0.)
      call Hbook1(125,'H1 y        mu',10,0.01,1.,0.)
      call Hbook1(126,'H1 phi12    mu',68,0.,3.4,0.)
*
      call Hbook1(200,'Breit Etlead nojet     ',10, 0.,20.,0.)
      call Hbook1(201,'Breit Etlead pt nojet  ',10, 0.,20.,0.)
      call Hbook1(202,'Breit Etlead etalab    ',10,-3.,5.,0.)
      call Hbook1(203,'Breit Etlead Q2        ',10,0.1,2.2,0.)
      call Hbook1(204,'Breit Etlead y         ',20,0.05,1.,0.)
      call Hbook1(205,'Breit Etlead log10(x)  ',10,-5.0,-1.,0.)
*
      call Hbook1(210,'Breitincl Et      ',10, 0.,20.,0.)
      call Hbook1(211,'Breitincl Pt      ',10, 0.,20.,0.)
      call Hbook1(212,'Breitincl etalab  ',10,-3.,5.,0.)
      call Hbook1(213,'Breitincl Q2      ',10,0.1,2.2,0.) 
      call Hbook1(214,'Breitincl y       ',10,0.05,1.,0.)
      call Hbook1(215,'Breitincl log10(x)',10,-5.0,-1.,0.)
*
      call Hbook1(220,'Breit Et_leadcut incl Et  ',10, 0.,20.,0.)
      call Hbook1(221,'Breit Et_leadcut incl Pt  ',10, 0.,20.,0.)
      call Hbook1(222,'Breit Et_leadcut incl etalab ',10,-3.,5.,0.)
      call Hbook1(223,'Breit Et_leadcut incl Q2  ',10,0.1,2.2,0.)
      call Hbook1(224,'Breit Et_leadcut incl y   ',10,0.05,1.,0.)
      call Hbook1(225,'Breit Et_leadcut incl log10(x)',10,-5.0,-1.,0.)
*
      call Hbook1(230,'Breit Et_leadcut+Muon incl Et  ',10, 0.,20.,0.)
      call Hbook1(231,'Breit Et_leadcut+Muon incl Pt  ',10, 0.,20.,0.)
      call Hbook1(232,'Breit Et_leadcut+Muon incl etalab ',10,-3.,5.,0.)
      call Hbook1(233,'Breit Et_leadcut+Muon incl Q2  ',10,0.1,2.2,0.)
      call Hbook1(234,'Breit Et_leadcut+Muon incl y   ',10,0.05,1.,0.)
      call Hbook1(235,'Breit Et_leadcut+Muon incl lg(x)',10,-5.0,-1.,0.)
      call Hbook1(236,'Breit Muon1 incl Et  ',10, 0.,20.,0.)
      call Hbook1(237,'Breit Muon1 incl Eta ',10, -3.,5.,0.)
      call Hbook1(238,'Breit Muon2 incl Et  ',10, 0.,20.,0.)
      call Hbook1(239,'Breit Muon2 incl Eta ',10, -3.,5.,0.)
*
      call Hbook1(240,'Breit Et_leadcut evt Et  ',10, 0.,20.,0.)
      call Hbook1(241,'Breit Et_leadcut evt Pt  ',10, 0.,20.,0.)
      call Hbook1(242,'Breit Et_leadcut evt etalab ',10,-3.,4.,0.)
      call Hbook1(243,'Breit Et_leadcut evt Q2  ',10,0.1,2.2,0.)
      call Hbook1(244,'Breit Et_leadcut evt y   ',10,0.05,1.,0.)
      call Hbook1(245,'Breit Et_leadcut evt lg(x)',10,-5.0,-1.,0.)
*
      call Hbook1(250,'Breit Et_leadcut+Muon evt Et  ',10, 0.,20.,0.)
      call Hbook1(251,'Breit Et_leadcut+Muon evt Pt  ',10, 0.,20.,0.)
      call Hbook1(252,'Breit Et_leadcut+Muon evt etalab ',10,-3.,4.,0.)
      call Hbook1(253,'Breit Et_leadcut+Muon evt Q2  ',10,0.1,2.2,0.)
      call Hbook1(254,'Breit Et_leadcut+Muon evt y   ',10,0.05,1.,0.)
      call Hbook1(255,'Breit Et_leadcut+Muon evt lg(x)',10,-5.0,-1.,0.)
      call Hbook1(256,'Breit Muon1 incl Et  evt ',10, 0.,20.,0.)
      call Hbook1(257,'Breit Muon1 incl Eta evt ',10, -3.,5.,0.)
      call Hbook1(258,'Breit Muon2 incl Et  evt ',10, 0.,20.,0.)
      call Hbook1(259,'Breit Muon2 incl Eta evt ',10, -3.,5.,0.)
*
      call Hbook1(301,'Breit dijet ET1       ',10,0.,20.,0.)
      call Hbook1(302,'Breit dijet ET2       ',10,0.,20.,0.)
      call Hbook1(303,'Breit dijet PT1       ',10,0.,20.,0.)
      call Hbook1(304,'Breit dijetPT2       ',10,0.,20.,0.)
      call Hbook1(305,'Breit dijet etabkw    ',10,-3.,4.,0.)
      call Hbook1(306,'Breit dijet etafwd    ',10,-3.,4.,0.)
      call Hbook1(307,'Breit dijet log10(xi) ',10,-5.0,-1.,0.)
      call Hbook1(308,'Breit dijet Mjj       ',25,0.,100.,0.)
      call Hbook1(309,'Breit dijet Dphi      ',25,0.,3.2,0.)
      call Hbook1(310,'Breit dijet Dphi      ',150,0.,3.2,0.)
      call Hbook1(311,'Breit dijet Muon1 incl Et  ',10, 0.,20.,0.)
      call Hbook1(312,'Breit dijet Muon1 incl Eta ',10, -3.,5.,0.)
      call Hbook1(313,'Breit dijet Muon1 incl Et  ',10, 0.,20.,0.)
      call Hbook1(314,'Breit dijet Muon1 incl Eta ',10, -3.,5.,0.)
*
      call hbook1(401,'  Etleading Delta   ',15,0.,15.,0.)
      call hbook1(402,'  Etleading SUM     ',15,0.,15.,0.)
      call hbook1(403,'  Etmean Delta      ',15,0.,15.,0.)
      call hbook1(404,'  Etmean Sum        ',15,0.,15.,0.)
      call hbook1(405,'  Etleading2 Delta  ',15,0.,15.,0.)
      call hbook1(406,'  Etleading2 SUM    ',15,0.,15.,0.)
*
      call hbook1(411,'  Etleading Delta  ',30,0.,15.,0.)
      call hbook1(412,'  Etleading SUM    ',30,0.,15.,0.)
      call hbook1(413,'  Etmean Delta     ',30,0.,15.,0.)
      call hbook1(414,'  Etmean Sum       ',30,0.,15.,0.)
      call hbook1(415,'  Etleading2 Delta ',30,0.,15.,0.)
      call hbook1(416,'  Etleading2 SUM   ',30,0.,15.,0.)
*
      call hbook1(421,'  Etleading1   ',90,0.,15.,0.)
      call hbook1(422,'  Etleading2   ',90,0.,15.,0.)
      call hbook1(423,'  Etmean       ',90,0.,15.,0.)
*
*
C      CALL STRCAT(PREF,'q2.out',FNAME)
C      CALL BBOOK(1,FNAME,NBIN,3.2D0,0D0)
C
C      CALL STRCAT(PREF,'x.out',FNAME)
C      CALL BBOOK(2,FNAME,NBIN,-1D0,-4D0)
C
C      CALL STRCAT(PREF,'y.out',FNAME)
C      CALL BBOOK(3,FNAME,NBIN,1D0,0D0)
C
C      CALL STRCAT(PREF,'w.out',FNAME)
C      CALL BBOOK(4,FNAME,NBIN,260D0,40D0)
C
C      CALL STRCAT(PREF,'phi.out',FNAME)
C      CALL BBOOK(5,FNAME,NBIN,PI,-PI)
C
C      CALL STRCAT(PREF,'pt.out',FNAME)
C      CALL BBOOK(6,FNAME,NBIN,10D0,0D0)
C
C      CALL STRCAT(PREF,'eta.out',FNAME)
C      CALL BBOOK(7,FNAME,NBIN,3D0,-3D0)
C
C      CALL STRCAT(PREF,'m.out',FNAME)
C      CALL BBOOK(8,FNAME,NBIN,25D0,0D0)
C
C      CALL STRCAT(PREF,'xi.out',FNAME)
C      CALL BBOOK(9,FNAME,NBIN,0D0,-5D0)
C
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
      DOUBLE PRECISION ETAMAX,PTMIN,PTMAX
      COMMON/CUTS/ETAMAX,PTMIN,PTMAX
      INTEGER ISCALER,ISCALEF,IALPHAS,IFRAG
      COMMON/FLAGS/ISCALER,ISCALEF,IALPHAS,IFRAG
      DOUBLE PRECISION EPS,HFRAC,XMD
      integer ISL
      COMMON/FRAGP/EPS,HFRAC,XMD,ISL
      DOUBLE PRECISION  XI
      COMMON/MOMFRAC/XI
*
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
c --- arguments
*
      Logical muon
      Data muon/.true./
      Integer nev,i,j,npa
      Data nev/0/
*
      Real       cpt1,  cetal,    cetah
      Parameter (cpt1=1.5,cetal=-2.,cetah=2.5)
*
      nev=nev+1
      if (nev.eq.1) then
       sigtot=0.
       sigbreit=0.
       sigtotm=0.
       sigbreitm=0.
*
       call HZHIJET(0,1,nsel,jetsel)
       call HZHIJET2(0,1,nsel,jetsel)
       call Hldir(' ','T')
      endif 
*
      call hcdir('//PAWC/hist',' ')
*
      IF(WGT.EQ.0D0)RETURN
*
C      if (lp) then
C       write(6,'(A,4f9.3)') ' p1= ',p1
C       write(6,'(A,4f9.3)') ' p2= ',p2
C      endif
*
      PT1=EPERP(P1)
      PT2=EPERP(P2)
      PT3=EPERP(P3)
      ETA1=SRAPID(P1)
      ETA2=SRAPID(P2)
      ETA3=SRAPID(P3)
*
      W=DSQRT(Q2*(1D0-XBJ)/XBJ)
      Y=Q2/XBJ/(4*EPRO*EIEL)
*
      XM12=DOT(P1,P1)+DOT(P2,P2)+2*DOT(P1,P2)
      XM12=DSQRT(XM12)
*
      PHI1=PHI(0,P1)
      PHI2=PHI(0,P2)
      PI=2*DACOS(0D0)
      IF( DABS(PHI1-PHI2).GT.PI )THEN
         IF(PHI1.GT.PHI2)THEN
            PHI1=PHI1-2*PI
         ELSE
            PHI2=PHI2-2*PI
         ENDIF
      ENDIF
      PHI12=PHI1-PHI2
*
      FFAC=0.5D0
      IF(IFRAG.EQ.1)FFAC=HFRAC
      TMP=WGT*FFAC
*
      do i=0,3
       PM1(i)=P1(i)
       PM2(i)=P2(i)
      enddo
C      write(6,*) ' isl= ',isl
      IF(ISL.EQ.0)THEN
       CALL BRM48(DVEC,2)
       CALL FRAG(DVEC,PM2,PM1)
      ELSEIF(ISL.EQ.1)THEN
       CALL BRM48(DVEC,10)
C       write(6,*) ' dvec= ',dvec 
       CALL FRAG(DVEC,PM1,PM2)
      endif
C      write(6,*) ' Pm1, PM2 = ',Pm1, PM2 
*
      PTM1=EPERP(PM1)
      PTM2=EPERP(PM2)
      ETAM1=SRAPID(PM1)
      ETAM2=SRAPID(PM2)
*
      WGT=0D0
*
      wtx=tmp
*
*
C      if (lp) write(6,*) 'pt1 = ',pt1
*
C      IF(DABS(ETA1).LT.ETAMAX)THEN
C         IF(PLOT)CALL BFILL(6,PT1,TMP)
C      ENDIF
C      IF( (PT1.GT.PTMIN).AND.(PT1.LT.PTMAX) )THEN
C         IF(PLOT)CALL BFILL(7,ETA1,TMP)
C      ENDIF
      IF( (DABS(ETA1).LT.ETAMAX)
     &    .AND.(PT1.GT.PTMIN).AND.(PT1.LT.PTMAX) )THEN
C         IF(PLOT)CALL BFILL(1,DLOG10(Q2),TMP)
C         IF(PLOT)CALL BFILL(2,DLOG10(XBJ),TMP)
C         IF(PLOT)CALL BFILL(3,Y,TMP)
C         IF(PLOT)CALL BFILL(4,W,TMP)
C         IF(PLOT)CALL BFILL(5,PHI12,TMP)
C         IF(PLOT)CALL BFILL(8,XM12,TMP)
C         IF(PLOT)CALL BFILL(9,DLOG10(XI),TMP)
         WGT=TMP
      ENDIF
C      IF(DABS(ETA2).LT.ETAMAX)THEN
C         IF(PLOT)CALL BFILL(6,PT2,TMP)
C      ENDIF
C      IF( (PT2.GT.PTMIN).AND.(PT2.LT.PTMAX) )THEN
C         IF(PLOT)CALL BFILL(7,ETA2,TMP)
C      ENDIF
      IF( (DABS(ETA2).LT.ETAMAX)
     &    .AND.(PT2.GT.PTMIN).AND.(PT2.LT.PTMAX) )THEN
C         IF(PLOT)CALL BFILL(1,DLOG10(Q2),TMP)
C         IF(PLOT)CALL BFILL(2,DLOG10(XBJ),TMP)
C         IF(PLOT)CALL BFILL(3,Y,TMP)
C         IF(PLOT)CALL BFILL(4,W,TMP)
C         IF(PLOT)CALL BFILL(5,PHI12,TMP)
C         IF(PLOT)CALL BFILL(8,XM12,TMP)
C         IF(PLOT)CALL BFILL(9,DLOG10(XI),TMP)
         WGT=WGT+TMP
      ENDIF
*
*     H1 cross section
*
      if (lp) then
       write(6,*) ' '
       write(6,*) ' Event: ',nev
       write(6,'(3(A,f9.3))') ' Q2= ',q2,
     & ' x*10^-3= ',xbj*1000,' y= ',y
       write(6,'(A,2f9.3)') ' pt1, eta1 = ',pt1,eta1
       write(6,'(A,2f9.3)') ' pt2, eta2 = ',pt2,eta2
      endif 
*
      if ((Q2 .gt.2.  .and. q2.lt.100.).and.
     &    ( y .gt.0.05.and.  y.lt.0.7 ) )then
*  
       call Hfill(110,real(pt1)  ,0.,real(tmp))
       call Hfill(111,real(pt2)  ,0.,real(tmp))
       call Hfill(112,real(eta1) ,0.,real(tmp))
       call Hfill(113,real(eta2) ,0.,real(tmp))
*
C       if ((pt1.gt.2. .or. pt2.gt.2.) .and.
C     &   ((eta1.lt.1.154.and.eta1.gt.-0.76).or.
C     &    (eta2.lt.1.154.and.eta2.gt.-0.76))) then
*
*         pt1 is b-quark: H1 measures ep->b X
*
       if ((pt1.gt.2.) .and.
     &     (eta1.lt.1.154.and.eta1.gt.-0.76)) then
*
        sigtot=sigtot+tmp
        call Hfill(100,real(pt1)  ,0.,real(tmp))
        call Hfill(101,real(pt2)  ,0.,real(tmp))
        call Hfill(102,real(eta1) ,0.,real(tmp))
        call Hfill(103,real(eta2) ,0.,real(tmp))
        call Hfill(104,real(log10(q2)),0.,real(tmp))
        call Hfill(105,real(y)    ,0.,real(tmp))
        call Hfill(106,real(phi12),0.,real(tmp))
       endif
*
       if ((ptm1.gt.2.) .and.
     &     (etam1.lt.1.154.and.etam1.gt.-0.76)) then
*
        sigtotm=sigtotm+tmp*hfrac
        call Hfill(120,real(pt1)  ,0.,real(tmp*hfrac))
        call Hfill(121,real(pt2)  ,0.,real(tmp*hfrac))
        call Hfill(122,real(eta1) ,0.,real(tmp*hfrac))
        call Hfill(123,real(eta2) ,0.,real(tmp*hfrac))
        call Hfill(124,real(log10(q2)),0.,real(tmp*hfrac))
        call Hfill(125,real(y)    ,0.,real(tmp*hfrac))
        call Hfill(126,real(phi12),0.,real(tmp*hfrac))
       endif
      endif 
*
* new cross section definition in Breit Frame
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
      ESEL  =(Q2+4D0*EIEL*EIEL*(1.-Y))/(4D0*EIEL)
      CTHSEL=(Q2-4D0*EIEL*EIEL*(1.D0-Y))/(Q2+4D0*EIEL*EIEL*(1.D0-Y))
      STHSEL=DSQRT(1D0-CTHSEL*CTHSEL)
      PSEL(4)=ESEL
      PSEL(1)=0D0
      PSEL(2)=ESEL*STHSEL
      PSEL(3)=ESEL*CTHSEL
C. NOW TO FIND PHOTON FOUR VECTOR
      DO 10 I=1,4
 10   PGAM(I)=PIEL(I)-PSEL(I)
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
*                fill virtual boson
       i=3
       Do j=1,4
        PHEP(j,i)=PHEP(j,2)-PHEP(j,4)
       Enddo
       ISTHEP(i)=3
       IDHEP(i)=22

*                fill incoming parton
*
      GEN='DSN'
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
      IDHEP(nhep)=0
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
      IDHEP(nhep)=0
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
C      if (lp) then
C       pt=-p1(1)**2-p1(2)**2-p1(3)**2+p1(0)**2
C       pt=sqrt(pt)
C       write(6,*) ' P1= ',p1,pt
C       pt=-p2(1)**2-p2(2)**2-p2(3)**2+p2(0)**2
C       pt=sqrt(pt)
C       write(6,*) ' P2= ',p2,pt
C       pt=-p3(1)**2-p3(2)**2-p3(3)**2+p3(0)**2
C       pt=sqrt(pt)
C       write(6,*) ' P3= ',p3,pt
C      endif
      
      if (lp) write(6,*) ' Lab: ' 
      if (lp) call hzlihep(2)
*
       do i=1,nhep
        do j=1,4
         PLAB(j,i)=PHEP(j,i)
        enddo
       enddo
*
      call ktbrei(2,piel(3),ppro(3),psel,nhep,PLAB,PBREIT)
C       do i=1,nhep
C        write(6,'(i2,A,4(f9.3))') i,' pbreit= ',(pbreit(j,i),j=1,4)
C       enddo
*
       do i=5,nhep
        do j=1,4
         PHEP(j,i)=PBREIT(j,i)
        enddo
        PHEP(5,i)=-PHEP(1,i)**2-PHEP(2,i)**2-PHEP(3,i)**2
     &            +PHEP(4,i)**2
        PHEP(5,i)=sqrt(PHEP(5,i))
       enddo
C       do i=1,nhep
C        write(6,'(i2,A,4(f9.3))') i,' pbreit= ',(phep(j,i),j=1,4)
C       enddo
*
       nsel=0
       Do i=1,maxhzjets
        do j=1,8
         jets(i,j)=0.
         jetsel(i,j)=0.
         jetslab(i,j)=0.
         jetsellab(i,j)=0.
        enddo
        ipjet(i)=0
       enddo
*
      if (lp) write(6,*) ' Breit: ' 
      if (lp) call hzlihep(2)
*
      CALL hzjtfind(3,1.d0,NJET,Jets)
*
      if (lp) then 
       write(6,*) ' Jets in Breit '
       call hzlijet(NJET,Jets)
      endif
*
      if (lp) then
C      write(6,*) ' ppro= ',ppro
C      write(6,*) ' piel= ',piel
C      write(6,*) ' psel= ',psel
C      write(6,*) ' p1= ',p1
C      write(6,*) ' p2= ',p2
C      write(6,*) ' pt1= ',pt1,' pt2= ',pt2
C      write(6,*) ' eta1= ',eta1,' eta2= ',eta2
*
C       do i=1,nhep
C        write(6,'(i2,A,4(f9.3))') i,' plab= ',(phep(j,i),j=1,4)
C       enddo
C       do i=1,4
C        pmom(i)=0.
C       enddo
C       do i=1,nhep
C        pmom(1)= pmom(1)+pbreit(1,i)
C        pmom(2)= pmom(2)+pbreit(2,i)
C        pmom(3)= pmom(3)+pbreit(3,i)
C        pmom(4)= pmom(4)+pbreit(4,i)
C        write(6,'(i2,A,4(f9.3))') i,' pbre= ',(pbreit(j,i),j=1,4)
C        enddo
C        write(6,'(2x,A,4(f9.3))') ' ptot= ',(pmom(j),j=1,4)
      endif 
*
*               transform back from Breit to Lab
*
      call hzbrtola2(njet,jets,jetslab)
*
      if (lp) then 
       write(6,*) ' Jets in Lab '
       call hzlijet(NJET,Jetslab)
      endif
*
       nsel=0
       do j=1,njet
*
*       apply jet cut
*
        pt=sqrt(jets(j,5)**2+jets(j,6)**2)
        if (pt.gt.cpt1
     &  .and. jetslab(j,1).gt.cetal .and. jetslab(j,1).lt.cetah) then
         nsel=nsel+1
         ipjet(nsel)=j
         do i=1,8
          jetsel(nsel,i)=jets(j,i)
          jetsellab(nsel,i)=jetslab(j,i)
         enddo
        endif
       enddo
*
      if ((Q2 .gt.2.  .and. q2.lt.100.).and.
     &    ( y .gt.0.05.and.  y.lt.0.7 ) )then
* 
C       write(6,*) ' Muon: '
C       write(6,*) '   pt1, pt2= ',ptm1,ptm2
C       write(6,*) ' eta1, eta2= ',etam1,etam2
*
       muon=.false.
       if ((ptm1.gt.2.) .and.
     &     (etam1.lt.1.3167.and.etam1.gt.-1.73517)) then
        muon=.true.
       endif
*
       if ((ptm2.gt.2.) .and.
     &     (etam2.lt.1.3167.and.etam2.gt.-1.73517)) then
        muon=.true.
       endif
*
       pt=sqrt(jetsel(1,5)**2+jetsel(1,6)**2)
       call Hfill(200,real(Jetsel(1,3))    ,0.,real(tmp))
       call Hfill(201,real(pt)             ,0.,real(tmp))
       call Hfill(202,real(jetsellab(1,1)) ,0.,real(tmp))
       call Hfill(203,real(log10(q2))             ,0.,real(tmp))
       call Hfill(204,real(y)              ,0.,real(tmp))
       call Hfill(205,real(log10(xbj))     ,0.,real(tmp))
*
       do i=1,nsel
        pt=sqrt(jetsel(i,5)**2+jetsel(i,6)**2)
        call Hfill(210,real(Jetsel(i,3)) ,0.,real(tmp))
        call Hfill(211,real(pt)          ,0.,real(tmp))
        call Hfill(212,real(jetsellab(i,1)) ,0.,real(tmp))
        call Hfill(213,real(log10(q2))        ,0.,real(tmp))
        call Hfill(214,real(y)         ,0.,real(tmp))
        call Hfill(215,real(log10(xbj)),0.,real(tmp))
       enddo
*
       pt=sqrt(jetsel(1,5)**2+jetsel(1,6)**2)
       if (pt.gt.ptmin) then
        sigbreit=sigbreit+tmp
        if (muon) then
         sigbreitm=sigbreitm+tmp*hfrac
        endif
*
        call Hfill(1,0.5,0.,real(tmp))
        if (q2.gt.20) then
         call Hfill(1,2.5,0.,real(tmp))
        else
         call Hfill(1,1.5,0.,real(tmp))
        endif
*
        if (muon) then
         call Hfill(2,0.5,0.,real(tmp*hfrac))
         if (q2.gt.20) then
          call Hfill(2,2.5,0.,real(tmp*hfrac))
         else
          call Hfill(2,1.5,0.,real(tmp*hfrac))
         endif
        endif
*
        do i=1,nsel
         pt=sqrt(jetsel(i,5)**2+jetsel(i,6)**2)
         call Hfill(220,real(Jetsel(i,3)) ,0.,real(tmp))
         call Hfill(221,real(pt)          ,0.,real(tmp))
         call Hfill(222,real(jetsellab(i,1)) ,0.,real(tmp))
         call Hfill(223,real(log10(q2))        ,0.,real(tmp))
         call Hfill(224,real(y)         ,0.,real(tmp))
         call Hfill(225,real(log10(xbj)),0.,real(tmp))
*
         if (muon) then
          call Hfill(230,real(Jetsel(i,3)) ,0.,real(tmp*hfrac))
          call Hfill(231,real(pt)          ,0.,real(tmp*hfrac))
          call Hfill(232,real(jetsellab(i,1)) ,0.,real(tmp*hfrac))
          call Hfill(233,real(log10(q2))        ,0.,real(tmp*hfrac))
          call Hfill(234,real(y)         ,0.,real(tmp*hfrac))
          call Hfill(235,real(log10(xbj)),0.,real(tmp*hfrac))
          call Hfill(236,real(ptm1),0.,real(tmp*hfrac))          
          call Hfill(237,real(etam1),0.,real(tmp*hfrac))          
          call Hfill(238,real(ptm2),0.,real(tmp*hfrac))          
          call Hfill(239,real(etam2),0.,real(tmp*hfrac))          
         endif
        enddo
*
        pt=sqrt(jetsel(1,5)**2+jetsel(1,6)**2)
        call Hfill(240,real(jetsel(1,3)) ,0.,real(tmp))
        call Hfill(241,real(pt)          ,0.,real(tmp))
        call Hfill(242,real(jetsellab(1,1)) ,0.,real(tmp))
        call Hfill(243,real(log10(q2))        ,0.,real(tmp))
        call Hfill(244,real(y)         ,0.,real(tmp))
        call Hfill(245,real(log10(xbj)),0.,real(tmp))
        if (muon) then
         call Hfill(250,real(Jetsel(1,3)) ,0.,real(tmp*hfrac))
         call Hfill(251,real(pt)          ,0.,real(tmp*hfrac))
         call Hfill(252,real(jetsellab(1,1)) ,0.,real(tmp*hfrac))
         call Hfill(253,real(log10(q2))        ,0.,real(tmp*hfrac))
         call Hfill(254,real(y)         ,0.,real(tmp*hfrac))
         call Hfill(255,real(log10(xbj)),0.,real(tmp*hfrac))
         call Hfill(256,real(ptm1),0.,real(tmp*hfrac))          
         call Hfill(257,real(etam1),0.,real(tmp*hfrac))          
         call Hfill(258,real(ptm2),0.,real(tmp*hfrac))          
         call Hfill(259,real(etam2),0.,real(tmp*hfrac))          
        endif
       endif
*
       if (nsel.ge.2) then
        pt1=sqrt(jetsel(1,5)**2+jetsel(1,6)**2)
        pt2=sqrt(jetsel(2,5)**2+jetsel(2,6)**2)
        if (pt2.gt.5. .and. pt1.gt.5.) then
*
         delta =pt1-pt2
         sum   =pt1+pt2
*
         call hfill(421,real(pt1),0.,wtx)
         call hfill(422,real(pt2),0.,wtx)
         call hfill(423,sum/2.,0.,wtx)
*
         if (pt1.gt.8.) then 
          call hfill(401,real(pt1),0.,wtx)
          call hfill(403,sum/2.,0.,wtx)
          call hfill(405,real(pt2),0.,wtx)
          call hfill(411,real(pt1),0.,wtx)
          call hfill(413,sum/2.,0.,wtx)
          call hfill(415,real(pt2),0.,wtx)
         endif

         if (sum.gt.13.) then
          call hfill(402,real(pt1),0.,wtx)
          call hfill(404,sum/2.,0.,wtx)
          call hfill(406,real(pt2),0.,wtx)
          call hfill(412,real(pt1),0.,wtx)
          call hfill(414,sum/2.,0.,wtx)
          call hfill(416,real(pt2),0.,wtx)
         endif
*    
        endif
       endif
*
* Now come dijets
*
       if (nsel.ge.2) then
        pt=sqrt(jetsel(1,5)**2+jetsel(1,6)**2)
        if (pt.gt.ptmin) then
         call Hfill(301,real(Jetsel(1,3))  ,0.,real(tmp))
         call Hfill(302,real(Jetsel(2,3))  ,0.,real(tmp))
         call Hfill(303,real(pt)           ,0.,real(tmp))
         pt=sqrt(jetsel(2,5)**2+jetsel(2,6)**2)
         call Hfill(304,real(pt)           ,0.,real(tmp))
         eta1=real(jetsellab(1,1))
         eta2=real(jetsellab(2,1))
         eta=min(eta1,eta2)
         call Hfill(305,real(eta)  ,0.,real(tmp))
         eta=max(eta1,eta2)
         call Hfill(306,real(eta)  ,0.,real(tmp))
*
         xm12=(JETSEL(1,5)+JETSEL(2,5))**2 +
     &        (JETSEL(1,6)+JETSEL(2,6))**2 +
     &        (JETSEL(1,7)+JETSEL(2,7))**2 -
     &        (JETSEL(1,4)+JETSEL(2,4))**2
         xm12=-xm12
         if (xm12.gt.0.) then
          ksi= xbj*(1.+xm12/q2)
          xm12=sqrt(xm12)
         else
          ksi=-999.
          xm12=-999.
         endif
         if (lp) write(6,*) ' ksi = ',ksi
         if (lp) write(6,*) ' Mas = ',xm12
 
         call Hfill(307,real(log10(ksi)),0.,real(tmp))
         call Hfill(308,real(xm12)      ,0.,real(tmp))
*
         dphi=jetsel(1,2)-jetsel(2,2)
         DELPHi=AMIN1(real(ABS(DPHI+2*pi)),real(ABS(DPHI)),
     &   real(ABS(DPHI-2*pi)))
         call Hfill(309,delphi,0.,real(tmp))  
         call Hfill(310,delphi,0.,real(tmp))  
*
         call Hfill(311,real(ptm1),0.,real(tmp*hfrac))  
         call Hfill(312,real(etam1),0.,real(tmp*hfrac))  
         call Hfill(313,real(ptm2),0.,real(tmp*hfrac))  
         call Hfill(314,real(etam2),0.,real(tmp*hfrac))  
*
         call HZHIJET2(0,2,nsel,jetsel)
*
         call HZHIJET(0,2,nsel,jetsel)
*
        endif
*
       endif
*
      endif
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
      COMMON/RESULT/sigtot,sigbreit,sigtotm,sigbreitm
*
      write(6,*) ' Total H1    cross section (pb): ',real(sigtot)*1000
      write(6,*) ' Total Breit cross section (pb): ',real(sigbreit)*1000
      write(6,*) ' Total H1    muon cross_se (pb): ',real(sigtotm)*1000
      write(6,*) ' Total Breit muon cross_se (pb): ',real(sigbreitm)*1000
*
       write(6,*) ' Output Histos here '
      call hcdir('//PAWC',' ')
      call hcdir('//HISTO',' ')
      CALL HROUT(0,ICYCLE,'T')
      CALL HREND('HISTO')
*
*****
C      CALL BINTE(1,FAC)
C      CALL BWRITE(1,1D0)
C      CALL BINTE(2,FAC)
C      CALL BWRITE(2,1D0)
C      CALL BINTE(3,FAC)
C      CALL BWRITE(3,1D0)
C      CALL BINTE(4,FAC)
C      CALL BWRITE(4,1D0)
C      CALL BINTE(5,FAC)
C      CALL BWRITE(5,1D0)
C      CALL BINTE(6,FAC)
C      CALL BWRITE(6,1D0)
C      CALL BINTE(7,FAC)
C      CALL BWRITE(7,1D0)
C      CALL BINTE(8,FAC)
C      CALL BWRITE(8,1D0)
C      CALL BINTE(9,FAC)
C      CALL BWRITE(9,1D0)

      RETURN
      END
