      SUBROUTINE HZB(iflag)
*
      Implicit none
      Integer iflag
*
      DOUBLE PRECISION P1(0:3),P2(0:3),P3(0:3),PM1(0:3),PM2(0:3)
      LOGICAL PLOT
      COMMON/PLOTS/PLOT
      DOUBLE PRECISION XBJ,XIMIN,XM2,Q2
      COMMON/INVAR/XBJ,XIMIN,XM2,Q2
      DOUBLE PRECISION Q2MIN,Q2MAX,XMIN,XMAX,YMIN,YMAX
      COMMON/LIMITS/Q2MIN,Q2MAX,XMIN,XMAX,YMIN,YMAX
      DOUBLE PRECISION EPRO,EIEL
      COMMON/BEAM/EPRO,EIEL
      DOUBLE PRECISION ETAMAX,PTMIN,PTMAX
      COMMON/CUTS/ETAMAX,PTMIN,PTMAX
      INTEGER ISCALER,ISCALEF,IALPHAS,IFRAG
      COMMON/FLAGS/ISCALER,ISCALEF,IALPHAS,IFRAG
      DOUBLE PRECISION EPS,HFRAC,XMD
      Integer ISL
      COMMON/FRAGP/EPS,HFRAC,XMD,ISL
      DOUBLE PRECISION  XI
      COMMON/MOMFRAC/XI
      DOUBLE PRECISION sigtoth1,sigtotmh1,sigjeth1,sigjetmh1,sigbh1
      DOUBLE PRECISION sigjetmcon
      DOUBLE PRECISION sigbrtot,sigbreit,sigbreitm,sigbreitnj,sigb
      DOUBLE PRECISION sigincljet,siginclmu,siginclb
*
      DOUBLE PRECISION PPRO(4),PIEL(4),PSEL(4),PGAM(4)
      Double precision alfass
      Parameter (alfass=0.16956366)
      DOUBLE PRECISION Pmom(4)
      DOUBLE PRECISION TMP,WTXM,WTXTMP
      DOUBLE PRECISION PT,PTLAB,ETA,KSI
      Real sum,delta
      DOUBLE PRECISION PT1,PT2,ETA1,ETA2,PT3,ETA3
      DOUBLE PRECISION PTM1,PTM2,ETAM1,ETAM2,PMUM1,PMUM2
      Integer inthecon
      double precision drmin1,drmin2
      Real dtheta,dr,dephi,deteta,dephi1,deteta1
      Real th,th1,th2,ph1,ph2
      DOUBLE PRECISION W,Y
      DOUBLE PRECISION XM12,PHI12,PHI1,PHI2
      Real dphi,delphi
      DOUBLE PRECISION FFAC
      DOUBLE PRECISION EPERP,SRAPID,DOT,PHI
      DOUBLE PRECISION ESEL,CTHSEL,STHSEL 
      DOUBLE PRECISION DVEC(10)
      Real lum,lum1
      Integer iel,idum,ibeam,ierr
      DOUBLE PRECISION PHAD,PLEP
      Real pi,rd
      parameter (pi=3.1315927,rd=180./pi)
      Logical lp,lpp,first
      Data first/.true./
c      Data lp/.true./
      Data lp/.false./
      Data lpp/.false./      
c      Data lpp/.true./
      integer kula
      data kula /0/
      integer maxbinn
      parameter(maxbinn=100)
      DOUBLE PRECISION F2b(MaxBinN)
      real xmean,ymean,q2mean

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
      Integer ipjetsel(MAXHZJETS),isel 
      Logical muon,muon2,muon1,muon2acc,muon1acc
      Data muon/.true./
      Integer nev,i,ijet,ii,j,ib,ibar,npa,imuon,imuon2,nmuon,imucount,nb
      Integer nev1
      Integer imuonjet1,imuonjet2,imuonsel1,imuonsel2
      Integer id,k,imo1,imo2,nmo
      Real imu1,imu2,imuacc1,imuacc2
      Real costh,ptrel,pmuon(4),pjet(4),absp,absj
      Data nev/0/,imucount/0/
      Data nev1/0/
      Character*40 title
      Character*4 dir
      data dir/'HISB'/
*
      Real pb(4),pbar(4)
      DOUBLE PRECISION pbbar(4,2),pbbreit(4,2)
      real rpb(4,2)
      logical direct,indirect
      integer idir,indir,itau,ioth,iall
*
      Real q2old,xbjold
*
      Integer nx,nq2,nq2fine
      Parameter (nx=3,nq2=3,nq2fine=75)
      Real xq2(nq2+1),xx(nx+1)
      Real xq2fine(nq2fine+1)
*                   1     2    3   4    5     6    7   8    9    10
      Data xq2fine/2.00,2.50,3.00,3.50,4.00,4.50,5.00,5.50,6.00,6.50,
     &             7.00,8.00,9.00,10.0,11.0,12.0,13.0,14.0,16.0,18.0,
     &             20.0,22.0,24.0,27.0,30.0,33.0,36.0,39.0,42.0,45.0,
     &             47.0,50.0,55.0,60.0,65.0,70.0,75.0,80.0,85.0,90.0,
     &             95.0,100.,110.,120.,130.,140.,150.,160.,170.,180.,
     &             190.,200.,220.,240.,260.,280.,300.,320.,340.,380.,
     &             400.,440.,480.,520.,560.,600.,640.,680.,720.,760., 
     &             800.,840.,880.,920.,960.,1000./
*
      Integer netbins,nmuetbins,nzetbins
      Parameter (netbins=17,nmuetbins=13,nzetbins=3)
      Real etbins(netbins+1),muetbins(nmuetbins+1),zetbins(nzetbins+1)
      data etbins/0.,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,
     &           12.,14.,16.,18.,20.,25.,30./    
      data zetbins/6.,10.,13.,36./    
      data muetbins/0.,0.5,1.0,1.5,2.0,2.5,3.0,3.5,4.0,5.0,6.0,
     &            7.,8.,10./
*
      Integer muetzbin,muetazbin
      Parameter (muetzbin=3,muetazbin=3)
      Real etzbinmu(muetzbin+1),etazbinmu(muetazbin+1)
      Real etzbinmu2(muetzbin+1)
      Data etzbinmu/2.0,3.0,4.0,15.0/
      Data etzbinmu2/2.5,3.0,4.0,15.0/
      Data etazbinmu/-1.6,-0.15,0.45,1.3/
*
      Integer jetetzbin,jetetazbin
      Parameter (jetetzbin=3,jetetazbin=3)
      Real etzbinjet(jetetzbin+1),etazbinjet(jetetazbin+1)
      Data etzbinjet/6.0,10.0,13.0,36.0/
      Data etazbinjet/-2.0,0.0,0.5,2.0/
*
*
      DOUBLE PRECISION PLAB(4,NMXHEP),PBREIT(4,NMXHEP)
*        
      Real       cpt1,  cetal,    cetah
      Parameter (cpt1=5.0,cetal=-2.,cetah=2.5)        
*        
      real etab,etabar,etb,etbar
      real etafwd,etaselfwd
*     
*     my var
* km=1,2 kjetid=jet id from kt         
      integer kmuon,kmuon1,kmuon2,kjetid,kjetid1,kjetid2
C     bins for cross
C     Muon and jet eta
      real keta1
      real keta2
      real keta3
      real keta4
      real keta5
      parameter(keta1 =-1.6 )
      parameter(keta2 = -0.5)
      parameter(keta3 =0.2 )
      parameter(keta4 =0.9 )
      parameter(keta5 =2.5 )
      Real ketabin(5)
      Data ketabin/-1.6,-0.5,0.2,0.9,2.5/
C     Muon pt
      real kmuptc1
      real kmuptc2
      real kmuptc3
      real kmuptc4
      real kmuptc5
      parameter(kmuptc1 =1.5 )
      parameter(kmuptc2 =2.5 )
      parameter(kmuptc3 =4. )
      parameter(kmuptc4 =6. )
      parameter(kmuptc5 =10. )
      Real kmuptbin(5)
      Data kmuptbin/1.5,2.5,4.0,6.0,10.0/
C 
C     Jet pt
      real kjetpt1
      real kjetpt2
      real kjetpt3
      real kjetpt4
      parameter(kjetpt1 = 4.)
      parameter(kjetpt2 = 10.)
      parameter(kjetpt3 = 15.)
      parameter(kjetpt4 = 30.)
      Real kjetptbin(4)
      Data kjetptbin/4.0,10.0,15.0,30.0/
C Q2
      real xellog    
C Q2 x0
      real q20
      real q20x1
      real q20x2
      parameter(q20=2.)
      parameter(q20x1=-4.6)
      parameter(q20x2=-3.5)
      Real kq2x0bin(2)
      Data kq2x0bin/-4.6,-3.5/ 
C     Q2 x1
      real q21
      real q21x1
      real q21x2
      real q21x3
      real q21x4
      parameter(q21 =4. )
      parameter(q21x1 =-4.4 )
      parameter(q21x2 =-3.75 )
      parameter(q21x3 =-3.45 )
      parameter(q21x4 =-2.5)
      Real kq2x1bin(4)
      Data kq2x1bin/-4.4,-3.75,-3.45,-2.5/
C     Q2 x2
      real q22
      real q22x1
      real q22x2
      real q22x3
      parameter(q22 =20. )
      parameter(q22x1 =-3.6 )
      parameter(q22x2 =-3.0 )
      parameter(q22x3 =-1.0 )
      Real kq2x2bin(3)
      Data kq2x2bin/-3.6,-3.0,-1.0/
C     Q2 x22
      real q22x11
      real q22x21
      real q22x31
      real q22x41
      parameter(q22x11 =-3.6 )
      parameter(q22x21 =-3.0 )
      parameter(q22x31 =-1.0 )
      parameter(q22x41 =-0.5 )
      Real kq2x21bin(4)
      Data kq2x21bin/-3.6,-3.0,-1.0,-0.5/
C     Q2 x3
      real q23
      real q24	
      real q25
      real q26
      real q23x1
      real q23x2
      real q23x3
      parameter(q23 =45. )
      parameter(q24 =100. )
      parameter(q25 =250. )
      parameter(q26=3000.)
      parameter(q23x1 =-3.3 )
      parameter(q23x2 =-2.6 )
      parameter(q23x3 =-1.0 )
      Real kq2x3bin(3)
      Data kq2x3bin/-3.3,-2.6,-1.0/
C Q2 x4
      real q24x1
      real q24x2
      real q24x3
      parameter(q24x1=-3.0)
      parameter(q24x2=-2.3)
      parameter(q24x3=-1.0)
      Real kq2x4bin(3)
      Data kq2x4bin/-3.0,-2.3,-1.0/
c q2 x5
      real q25x1
      real q25x2
      parameter(q25x1=-2.5)
      parameter(q25x2=-1.0)
      Real kq2x5bin(2)
      Data kq2x5bin/-2.5,-1.0/
c q2 cross
      real q2_0
      real q2_1
      real q2_2
      real q2_3
      real q2_4
      real q2_5
      parameter (q2_0=2.0)
      parameter (q2_1=4.0)      
      parameter (q2_2=10.0)
      parameter (q2_3=25.0)
      parameter (q2_4=100.0)
      parameter (q2_5=1000.0)
      Real kq2bin(6)
      Data kq2bin/2.0,4.0,10.0,25.0,100.,1000./
      Real klogq2bin(6)
      Data klogq2bin/0.301,0.602,1.,1.3979,2.,3./
      REAL Kweq2
      real klogq2
      real kjetp,kjetene,kjetcut
      real ppeta,ppphi,ppthe,ppmom,ppmas
      real hfrac1

c     Variables for Philipp
      INTEGER NSEL4
      DOUBLE PRECISION JETSELLAB4(MAXHZJETS,8)

c     Binning for Philipp
      REAL petbins(8)
      DATA petbins/5.0, 8.0, 11.0, 14.0, 17.0, 20.0, 25.0, 35.0/
      REAL petabins(11)
      DATA petabins/-1.6, -0.8, -0.5, -0.2, 0.1,
     +     0.4, 0.7, 1.0, 1.3, 1.6, 2.2/
      REAL pq2bins(9)
      DATA pq2bins/5.0, 10.0, 20.0, 40.0, 70.0,
     +     120.0, 200.0, 400.0, 1000.0/
      REAL pxbins(7)
      DATA pxbins/0.00008, 0.0002, 0.0006, 0.0016, 0.005, 0.01, 0.1/

      REAL pxbins1(5)
      DATA pxbins1/0.00008, 0.0002, 0.0003, 0.0005, 0.003/
      REAL pxbins2(6)
      DATA pxbins2/0.0003, 0.0005, 0.0012, 0.002, 0.0035, 0.01/
      REAL pxbins3(5)
      DATA pxbins3/0.0008, 0.0018, 0.003, 0.006, 0.04/
      REAL pxbins4(4)
      DATA pxbins4/0.0016, 0.005, 0.016, 0.06/
      REAL pxbins5(3)
      DATA pxbins5/0.005, 0.02, 0.1/

      REAL petbins4(8)
      DATA petbins4/4.2, 8.0, 11.0, 14.0, 17.0, 20.0, 25.0, 35.0/
      REAL petabins4(12)
      DATA petabins4/-1.6, -1.1, -0.8, -0.5, -0.2, 0.1,
     +     0.4, 0.7, 1.0, 1.3, 1.6, 2.2/

      REAL logxbins(101)
      DATA logxbins/-5.0,-4.95,-4.9,-4.85,-4.8,-4.75,-4.7,-4.65,
     +              -4.6,-4.55,-4.5,-4.45,-4.4,-4.35,-4.3,-4.25,
     +              -4.2,-4.15,-4.1,-4.05,-4.0,-3.95,-3.9,-3.85,
     +              -3.8,-3.75,-3.7,-3.65,-3.6,-3.55,-3.5,-3.45,
     +              -3.4,-3.35,-3.3,-3.25,-3.2,-3.15,-3.1,-3.05,
     +              -3.0,-2.95,-2.9,-2.85,-2.8,-2.75,-2.7,-2.65,
     +              -2.6,-2.55,-2.5,-2.45,-2.4,-2.35,-2.3,-2.25,
     +              -2.2,-2.15,-2.1,-2.05,-2.0,-1.95,-1.9,-1.85,
     +              -1.8,-1.75,-1.7,-1.65,-1.6,-1.55,-1.5,-1.45,
     +              -1.4,-1.35,-1.3,-1.25,-1.2,-1.15,-1.1,-1.05,
     +              -1.0,-0.95,-0.9,-0.85,-0.8,-0.75,-0.7,-0.65,
     +              -0.6,-0.55,-0.5,-0.45,-0.4,-0.35,-0.3,-0.25,
     +              -0.2,-0.15,-0.1,-0.05,0.0/

      INTEGER nrjet

*     tworzymy histogramy
      if (iflag.eq.1) then
*
       write(6,*) ' create directory ',dir
       write(6,*) 'hfrac:', hfrac
*
       Call hcdir('//PAWC',' ')
       call hmdir(dir,'S')
       Call hcdir('//HISTO',' ')
       call hmdir(dir,'S')
       write(6,*) '**hzb: Version kula1  '
*
       call Hbook1(1,' Sig_tot '     ,5,0.,5.,0.)
       call Hbook1(2,' Sig_tot Muon ',3,0.,3.,0.)
********************************************************************
* jets
       call hbook1(11001  ,'jet 1 eta  ',100,-6.,6.,0.)
       call hbook1(11002  ,'jet 2 phi ',100,-6.,6.,0.)
       call hbook1(11003  ,'jet 3 et ',100,-6.,94.,0.)
       call hbook1(11004  ,'jet 4 E ',100,-6.,94.,0.)
       call hbook1(11005  ,'jet 5 px ',100,-50.,50.,0.)
       call hbook1(11006  ,'jet 6 py ',100,-50.,50.,0.)
       call hbook1(11007  ,'jet 7 pz ',100,-50.,50.,0.)
       call hbook1(11008  ,'jet 8 M ',100,0.,10.,0.)
*     muon
       call hbook1(11009  ,'muon phi ',80,-4.,4.,0.)
       call hbook1(11010  ,'muon the ',80,-4.,4.,0.)
       call hbook1(11011  ,'muon pseudorap ',80,-4.,4.,0.)
       call hbook1(11012  ,'muon px ',80,-20.,20.,0.)
       call hbook1(11013  ,'muon py ',80,-20.,20.,0.)
       call hbook1(11014  ,'muon pz ',80,-20.,20.,0.)
       call hbook1(11015  ,'muon pt ',60,0.,15.,0.)
       call hbook1(11016  ,'muon p ',80,0.,20.,0.)
       call hbook1(11017  ,'dphi no cuts ',80,-4.,4.,0.)
       call hbook1(11018  ,'deta no cuts',80,-4.,4.,0.)
       call hbook1(11019  ,'dR no cuts',40,0.,4.,0.)
       call hbook1(11020  ,'dphi ',80,-4.,4.,0.)
       call hbook1(11021  ,'det ',80,-4.,4.,0.)
       call hbook1(11022  ,'dR  ',40,0.,4.,0.)
* 
       call hbook1(11023  ,'muon phi bef cut ',80,-4.,4.,0.)
       call hbook1(11024  ,'jet phi bef cut',80,-4.,4.,0.)
*     partons
       call hbook1(11030  ,'phi part bef frag ',80,-4.,4.,0.)
       call hbook1(11031  ,'eta part bef frag ',80,-4.,4.,0.)
       call hbook1(11032  ,'phi part after frag ',80,-4.,4.,0.)
       call hbook1(11033  ,'eta part after frag ',80,-4.,4.,0.)
       call hbook1(11034  ,'mass part ',100,-20.,30.,0.)
       call hbook1(11035  ,'mass part  ',100,-20.,30.,0.)
       call hbook1(11036  ,'E^2-p^2 jet  ',100,-20.,30.,0.)

c     Histograms for Philipp
       CALL HBOOKB(30001,'ET(Jet)',7,petbins,0.)
       CALL HBOOKB(30002,'Eta(Jet)',10,petabins,0.)
       CALL HBOOKB(30003,'Q2',8,pq2bins,0.)
       CALL HBOOKB(30004,'x',6,pxbins,0.)

       CALL HBOOKB(31001,'x',4,pxbins1,0.)
       CALL HBOOKB(31002,'x',5,pxbins2,0.)
       CALL HBOOKB(31003,'x',4,pxbins3,0.)
       CALL HBOOKB(31004,'x',3,pxbins4,0.)
       CALL HBOOKB(31005,'x',2,pxbins5,0.)

       CALL HBOOKB(30101,'ET(Jet)',7,petbins4,0.)
       CALL HBOOKB(30102,'Eta(Jet)',11,petabins4,0.)
       CALL HBOOKB(30103,'Q2',8,pq2bins,0.)
       CALL HBOOKB(30104,'x',6,pxbins,0.)

       CALL HBOOKB(31101,'x',4,pxbins1,0.)
       CALL HBOOKB(31102,'x',5,pxbins2,0.)
       CALL HBOOKB(31103,'x',4,pxbins3,0.)
       CALL HBOOKB(31104,'x',3,pxbins4,0.)
       CALL HBOOKB(31105,'x',2,pxbins5,0.)

       CALL HBOOKB(32001,'log10(x)',100,logxbins,0.)

*      crosssections
*     etamu
       call hbookb(40001  ,'muon eta  ',4,ketabin,0.)
       call hbookb(40101  ,'muon eta  ',4,ketabin,0.)
       call hbook1(50001  ,'muon eta  ',4,ketabin(1),ketabin(5),0.)
*     etajet
       call hbookb(40002  ,'jet eta  ',4,ketabin,0.)
       call hbook1(50002  ,'jet eta  ',4,ketabin(1),ketabin(5),0.)
*     ptmu
       call hbookb(40003  ,'muon pt  ',4,kmuptbin,0.)
       call hbookb(40103  ,'muon pt  ',4,kmuptbin,0.)
       call hbook1(50003  ,'muon pt ',4,kmuptbin(1),kmuptbin(5),0.)
*     ptjet
       call hbookb(40004  ,'jet pt   ',3,kjetptbin,0.)
       call hbook1(50004  ,'jet pt   ',3,kjetptbin(1),kjetptbin(4),0.)
*     etjet
       call hbookb(40005  ,'jet et   ',3,kjetptbin,0.)
       call hbook1(50005  ,'jet et   ',3,kjetptbin(1),kjetptbin(4),0.)
*     q2  
       call hbookb(40010  ,'q2       ',5,kq2bin,0.)
       call hbook1(50010  ,'q2       ',5,kq2bin(1),kq2bin(6),0.)
       call hbookb(40011  ,'logq2    ',5,klogq2bin,0.)
       call hbook1(50011  ,'logq2    ',5,klogq2bin(1),klogq2bin(6),0.)
*     Q2X SPECIAL h1 COMPARISON
       call hbook1(50111,'dsi/dq2dx 1',1,0.00006237,0.00006363,0.)
       call hbook1(50112,'dsi/dq2dx 2',1,0.000198,0.000202,0.)
       call hbook1(50113,'dsi/dq2dx 3',1,0.000198,0.000202,0.)
       call hbook1(50114,'dsi/dq2dx 4',1,0.00078606,0.00080194,0.)
       call hbook1(50115,'dsi/dq2dx 5',1,0.00049599,0.00050601,0.)
       call hbook1(50116,'dsi/dq2dx 6',1,0.00197505,0.00201495,0.)
       call hbook1(50117,'dsi/dq2dx 7',1,0.00197505,0.00201495,0.)
       call hbook1(50118,'dsi/dq2dx 8',1,0.00496188,0.00506212,0.)
       call hbook1(50119,'dsi/dq2dx 9',1,0.00197505,0.00201495,0.)
       call hbook1(50120,'dsi/dq2dx 10',1,0.0099,0.0101,0.)
       call hbook1(50121,'dsi/dq2dx 11',1,0.0099,0.0101,0.)
*     Q2X SPECIAL h1 COMPARISON b->muon+jest
       call hbook1(60111,'dsi/dq2dx 1',1,0.00006237,0.00006363,0.)
       call hbook1(60112,'dsi/dq2dx 2',1,0.000198,0.000202,0.)
       call hbook1(60113,'dsi/dq2dx 3',1,0.000198,0.000202,0.)
       call hbook1(60114,'dsi/dq2dx 4',1,0.00078606,0.00080194,0.)
       call hbook1(60115,'dsi/dq2dx 5',1,0.00049599,0.00050601,0.)
       call hbook1(60116,'dsi/dq2dx 6',1,0.00197505,0.00201495,0.)
       call hbook1(60117,'dsi/dq2dx 7',1,0.00197505,0.00201495,0.)
       call hbook1(60118,'dsi/dq2dx 8',1,0.00496188,0.00506212,0.)
       call hbook1(60119,'dsi/dq2dx 9',1,0.00197505,0.00201495,0.)
       call hbook1(60120,'dsi/dq2dx 10',1,0.0099,0.0101,0.)
       call hbook1(60121,'dsi/dq2dx 11',1,0.0099,0.0101,0.)
*  0
       call hbook1(51001,'dsi/dq2dx spec',1,0.00006237,0.00006363,0.)
       call hbook1(51011,'dsi/dq2dx spec',1,0.00006237,0.00006363,0.)
       call hbook1(61011  ,'q2 special   ',10,2.97,3.03 ,0.)
       call hbook1(71011  ,'x  special   ',100,0.00006237,0.00006363,0.)
       call hbook1(81011  ,'y  special   ',100,0.,1.,0.)
       CALL HBOOK2(91011, 'Q2vsX spec',10,0.00006237,0.00006363
     &      ,10,2.97,3.03,0.)
* ***************
*  1
       call hbook1(51101,'dsi/dq2dx spec',1,0.000198,0.000202,0.)
       call hbook1(51111,'dsi/dq2dx spec',1,0.000198,0.000202,0.)
       call hbook1(61111  ,'q2 special   ',10,7.92,8.08 ,0.)
       call hbook1(71111  ,'x  special   ',100,0.000198,0.000202,0.)
       call hbook1(81111  ,'y  special   ',100,0.,1.,0.)
       CALL HBOOK2(91111, 'Q2vsX spec',10,0.000198,0.000202
     &      ,10,7.92,8.08 ,0.)
* ***************
*  2
       call hbook1(51201,'dsi/dq2dx spec',1,0.000198,0.000202,0.)
       call hbook1(51211,'dsi/dq2dx spec',1,0.000198,0.000202,0.)
       call hbook1(61211  ,'q2 special   ',10,11.88,12.12 ,0.)
       call hbook1(71211  ,'x  special   ',100,0.000198,0.000202,0.)
       call hbook1(81211  ,'y  special   ',100,0.,1.,0.)
       CALL HBOOK2(91211, 'Q2vsX spec',10,0.000198,0.000202
     &      ,10,11.88,12.12 ,0.)
* ***************
*  3
       call hbook1(51301,'dsi/dq2dx spec',1,0.00078606,0.00080194,0.)
       call hbook1(51311,'dsi/dq2dx spec',1,0.00078606,0.00080194,0.)
       call hbook1(61311  ,'q2 special   ',10,11.88,12.12 ,0.)
       call hbook1(71311  ,'x  special   ',100,0.00078606,0.00080194,0.)
       call hbook1(81311  ,'y  special   ',100,0.,1.,0.)
       CALL HBOOK2(91311, 'Q2vsX spec',10,0.00078606,0.00080194
     &      ,10,11.88,12.12 ,0.)
* ***************
*  4
       call hbook1(51401,'dsi/dq2dx spec',1,0.00049599,0.0005060,0.)
       call hbook1(51411,'dsi/dq2dx spec',1,0.00049599,0.0005060,0.)
       call hbook1(61411  ,'q2 special   ',10, 24.75,25.25,0.)
       call hbook1(71411  ,'x  special   ',100,0.00049599,0.0005060,0.)
       call hbook1(81411  ,'y  special   ',100,0.,1.,0.)
       CALL HBOOK2(91411, 'Q2vsX spec',10,0.00049599,0.0005060
     &      ,10,24.75,25.25 ,0.)
* ***************
*  5
       call hbook1(51501,'dsi/dq2dx spec',1,0.00197505,0.00201495,0.)
       call hbook1(51511,'dsi/dq2dx spec',1,0.00197505,0.00201495,0.)
       call hbook1(61511  ,'q2 special   ',10,24.75,25.25 ,0.)
       call hbook1(71511  ,'x  special   ',100,0.00197505,0.00201495,0.)
       call hbook1(81511  ,'y  special   ',100,0.,1.,0.)
       CALL HBOOK2(91511, 'Q2vsX spec',10,0.00197505,0.00201495
     &      ,10,24.75,25.25 ,0.)
* ***************
*  6
       call hbook1(51601,'dsi/dq2dx spec',1,0.00197505,0.00201495,0.)
       call hbook1(51611,'dsi/dq2dx spec',1,0.00197505,0.00201495,0.)
       call hbook1(61611  ,'q2 special   ',10, 59.4,60.6,0.)
       call hbook1(71611  ,'x  special   ',100,0.00197505,0.00201495,0.)
       call hbook1(81611  ,'y  special   ',100,0.,1.,0.)
       CALL HBOOK2(91611, 'Q2vsX spec',10,0.00197505,0.00201495
     &      ,10,59.4,60.6 ,0.)
* ***************
*  7
       call hbook1(51701,'dsi/dq2dx spec',1,0.00496188,0.00506212,0.)
       call hbook1(51711,'dsi/dq2dx spec',1,0.00496188,0.00506212,0.)
       call hbook1(61711  ,'q2 special   ',10, 59.4,60.6,0.)
       call hbook1(71711  ,'x  special   ',100,0.00496188,0.00506212,0.)
       call hbook1(81711  ,'y  special   ',100,0.,1.,0.)
       CALL HBOOK2(91711, 'Q2vsX spec',10,0.00496188,0.00506212
     &      ,10,59.4,60.6 ,0.)
* ***************
*  8
       call hbook1(51801,'dsi/dq2dx spec',1,0.00197505,0.00201495,0.)
       call hbook1(51811,'dsi/dq2dx spec',1,0.00197505,0.00201495,0.)
       call hbook1(61811  ,'q2 special   ',10,108.9,111.1 ,0.)
       call hbook1(71811  ,'x  special   ',100,0.00197505,0.00201495,0.)
       call hbook1(81811  ,'y  special   ',100,0.,1.,0.)
       CALL HBOOK2(91811, 'Q2vsX spec',10,0.00197505,0.00201495
     &      ,10, 108.9,111.1 ,0.)
* ***************
*  9
       call hbook1(51901,'dsi/dq2dx spec',1,0.0099,0.0101,0.)
       call hbook1(51911,'dsi/dq2dx spec',1,0.0099,0.0101,0.)
       call hbook1(61911  ,'q2 special   ',10,198.,202. ,0.)
       call hbook1(71911  ,'x  special   ',100,0.0099,0.0101,0.)
       call hbook1(81911  ,'y  special   ',100,0.,1.,0.)
       CALL HBOOK2(91911, 'Q2vsX spec',10,0.0099,0.0101
     &      ,10,198.,202. ,0.)
* ***************
*  10
       call hbook1(52001,'dsi/dq2dx spec',1,0.0099,0.0101,0.)
       call hbook1(52011,'dsi/dq2dx spec',1,0.0099,0.0101,0.)
       call hbook1(62011  ,'q2 special   ',10,594.,606. ,0.)
       call hbook1(72011  ,'x  special   ',100,0.0099,0.0101,0.)
       call hbook1(82011  ,'y  special   ',100,0.,1.,0.)
       CALL HBOOK2(92011, 'Q2vsX spec',10,0.0099,0.0101
     &      ,10,594.,606. ,0.)
* ***************
*     q2  x0
       call hbookb(140000  ,'q2 x0    ',1,kq2x0bin,0.)
       call hbook1(150000  ,'q2 x0    ',1,kq2x0bin(1),kq2x0bin(2),0.)
       call hbook1(160010  ,'q2 q2x0   ',100,0.,4.5 ,0.)
       call hbook1(170010  ,'x  q2x0    ',100,-5.,-1.,0.)
       call hbook1(180010  ,'y  q2x0    ',100,0.,1.,0.)
        
       call hbookb(144000  ,'q2 x0   ep->bX ',1,kq2x0bin,0.)
       call hbook1(144010  ,'q2 q2x0 ep->bX  ',100,0.,4.5 ,0.)
       call hbook1(144110  ,'x  q2x0 ep->bX   ',100,-5.,-1.,0.)
       call hbook1(144210  ,'y  q2x0 ep->bX   ',100,0.,1.,0.)
*     q2  x1
       call hbookb(140001  ,'q2 x1    ',3,kq2x1bin,0.)
       call hbook1(150001  ,'q2 x1    ',3,kq2x1bin(1),kq2x1bin(4),0.)
       call hbook1(160011  ,'q2 q2x1    ',100,0.,25. ,0.)
       call hbook1(170011  ,'x  q2x1    ',100,-5.,-1.,0.)
       call hbook1(180011  ,'y  q2x1    ',100,0.,1.,0.)
       call hbook1(160021  ,'q2 q2x1    ',100,0.,25. ,0.)
       call hbook1(170021  ,'x  q2x1    ',100,-5.,-1.,0.)
       call hbook1(180021  ,'y  q2x1    ',100,0.,1.,0.)
       call hbook1(160031  ,'q2 q2x1    ',100,0.,25. ,0.)
       call hbook1(170031  ,'x  q2x1    ',100,-5.,-1.,0.)
       call hbook1(180031  ,'y  q2x1    ',100,0.,1.,0.)
       
       call hbookb(144001  ,'q2 x1   ep->bX ',3,kq2x1bin,0.)
       call hbook1(144011  ,'q2 q2x1 ep->bX  ',100,0.,25. ,0.)
       call hbook1(144111  ,'x  q2x1 ep->bX   ',100,-5.,-1.,0.)
       call hbook1(144211  ,'y  q2x1 ep->bX   ',100,0.,1.,0.)
       call hbook1(144021  ,'q2 q2x1 ep->bX   ',100,0.,25. ,0.)
       call hbook1(144121  ,'x  q2x1 ep->bX   ',100,-5.,-1.,0.)
       call hbook1(144221  ,'y  q2x1 ep->bX   ',100,0.,1.,0.)
       call hbook1(144031  ,'q2 q2x1 ep->bX   ',100,0.,25. ,0.)
       call hbook1(144131  ,'x  q2x1 ep->bX   ',100,-5.,-1.,0.)
       call hbook1(144231  ,'y  q2x1 ep->bX   ',100,0.,1.,0.)

*     q2 x2
       call hbookb(140002  ,'q2 x2    ',2,kq2x2bin,0.)
       call hbook1(150002  ,'q2 x2    ',2,kq2x2bin(1),kq2x2bin(3),0.)
       call hbook1(160012  ,'q2 q2x2    ',100,0.,50. ,0.)
       call hbook1(170012  ,'x  q2x2    ',100,-5.,-1.,0.)
       call hbook1(180012  ,'y  q2x2    ',100,0.,1.,0.)
       call hbook1(160022  ,'q2 q2x2    ',100,0.,50. ,0.)
       call hbook1(170022  ,'x  q2x2    ',100,-5.,-1.,0.)
       call hbook1(180022  ,'y  q2x2    ',100,0.,1.,0.)
  
       call hbookb(144002  ,'q2 x2   ep->bX ',2,kq2x2bin,0.)
       call hbook1(144012  ,'q2 q2x2 ep->bX  ',100,0.,50. ,0.)
       call hbook1(144112  ,'x  q2x2 ep->bX   ',100,-5.,-1.,0.)
       call hbook1(144212  ,'y  q2x2 ep->bX   ',100,0.,1.,0.)
       call hbook1(144022  ,'q2 q2x2 ep->bX   ',100,0.,50. ,0.)
       call hbook1(144122  ,'x  q2x2 ep->bX   ',100,-5.,-1.,0.)
       call hbook1(144222  ,'y  q2x2 ep->bX   ',100,0.,1.,0.)
*     q2 x21
       call hbookb(140003  ,'q2 x22   ',3,kq2x21bin,0.)
       call hbook1(150003  ,'q2 x22   ',3,kq2x21bin(1),kq2x21bin(4),0.)
       call hbook1(160013  ,'q2 q2x22    ',100,0.,50. ,0.)
       call hbook1(170013  ,'x  q2x22    ',100,-5.,-1.,0.)
       call hbook1(180013  ,'y  q2x22    ',100,0.,1.,0.)
       call hbook1(160023  ,'q2 q2x22    ',100,0.,50. ,0.)
       call hbook1(170023  ,'x  q2x22    ',100,-5.,-1.,0.)
       call hbook1(180023  ,'y  q2x22    ',100,0.,1.,0.)
       call hbook1(160033  ,'q2 q2x22    ',100,0.,50. ,0.)
       call hbook1(170033  ,'x  q2x22    ',100,-5.,-1.,0.)
       call hbook1(180033  ,'y  q2x22    ',100,0.,1.,0.)
       call hbookb(144003  ,'q2 x22   ep->bX ',3,kq2x21bin,0.)
       call hbook1(144013  ,'q2 q2x22 ep->bX  ',100,0.,50. ,0.)
       call hbook1(144113  ,'x  q2x22 ep->bX   ',100,-5.,-1.,0.)
       call hbook1(144213  ,'y  q2x22 ep->bX   ',100,0.,1.,0.)
       call hbook1(144023  ,'q2 q2x22 ep->bX   ',100,0.,50. ,0.)
       call hbook1(144123  ,'x  q2x22 ep->bX   ',100,-5.,-1.,0.)
       call hbook1(144223  ,'y  q2x22 ep->bX   ',100,0.,1.,0.)
       call hbook1(144033  ,'q2 q2x22 ep->bX   ',100,0.,50. ,0.)
       call hbook1(144133  ,'x  q2x22 ep->bX   ',100,-5.,-1.,0.)
       call hbook1(144233  ,'y  q2x22 ep->bX   ',100,0.,1.,0.)
*     q2 x3
       call hbookb(140004  ,'q2 x3    ',2,kq2x3bin,0.)
       call hbook1(150004  ,'q2 x3    ',2,kq2x3bin(1),kq2x3bin(3),0.)
       call hbook1(160014  ,'q2 q2x3    ',100,50.,100. ,0.)
       call hbook1(170014  ,'x  q2x3    ',100,-5.,-1.,0.)
       call hbook1(180014  ,'y  q2x3    ',100,0.,1.,0.)
       call hbook1(160024  ,'q2 q2x3    ',100,50.,100. ,0.)
       call hbook1(170024  ,'x  q2x3    ',100,-5.,-1.,0.)
       call hbook1(180024  ,'y  q2x3    ',100,0.,1.,0.)
       call hbookb(144004  ,'q2 x3   ep->bX ',2,kq2x3bin,0.)
       call hbook1(144014  ,'q2 q2x3 ep->bX  ',100,50.,100. ,0.)
       call hbook1(144114  ,'x  q2x3 ep->bX   ',100,-5.,-1.,0.)
       call hbook1(144214  ,'y  q2x3 ep->bX   ',100,0.,1.,0.)
       call hbook1(144024  ,'q2 q2x3 ep->bX   ',100,50.,100. ,0.)
       call hbook1(144124  ,'x  q2x3 ep->bX   ',100,-5.,-1.,0.)
       call hbook1(144224  ,'y  q2x3 ep->bX   ',100,0.,1.,0.)
*     q2 x4
       call hbookb(140005  ,'q2 x4    ',2,kq2x4bin,0.)
       call hbook1(150005  ,'q2 x4    ',2,kq2x4bin(1),kq2x4bin(3),0.)
       call hbook1(160015  ,'q2 q2x4    ',100,50.,300. ,0.)
       call hbook1(170015  ,'x  q2x4    ',100,-5.,-1.,0.)
       call hbook1(180015  ,'y  q2x4    ',100,0.,1.,0.)
       call hbook1(160025  ,'q2 q2x4    ',100,50.,300. ,0.)
       call hbook1(170025  ,'x  q2x4    ',100,-5.,-1.,0.)
       call hbook1(180025  ,'y  q2x4    ',100,0.,1.,0.)
       call hbookb(144005  ,'q2 x4   ep->bX ',2,kq2x4bin,0.)
       call hbook1(144015  ,'q2 q2x4 ep->bX  ',100,50.,300. ,0.)
       call hbook1(144115  ,'x  q2x4 ep->bX   ',100,-5.,-1.,0.)
       call hbook1(144215  ,'y  q2x4 ep->bX   ',100,0.,1.,0.)
       call hbook1(144025  ,'q2 q2x4 ep->bX   ',100,50.,300. ,0.)
       call hbook1(144125  ,'x  q2x4 ep->bX   ',100,-5.,-1.,0.)
       call hbook1(144225  ,'y  q2x4 ep->bX   ',100,0.,1.,0.)
*     q2 x5
       call hbookb(140006  ,'q2 x5    ',1,kq2x5bin,0.)
       call hbook1(150006  ,'q2 x5    ',1,kq2x5bin(1),kq2x5bin(2),0.)
       call hbook1(160016  ,'q2 q2x5    ',100,50.,3050. ,0.)
       call hbook1(170016  ,'x  q2x5    ',100,-5.,-1.,0.)
       call hbook1(180016  ,'y  q2x5    ',100,0.,1.,0.)
       call hbookb(144006  ,'q2 x5   ep->bX ',1,kq2x5bin,0.)
       call hbook1(144016  ,'q2 q2x5 ep->bX  ',100,50.,3050. ,0.)
       call hbook1(144116  ,'x  q2x5 ep->bX   ',100,-5.,-1.,0.)
       call hbook1(144216  ,'y  q2x5 ep->bX   ',100,0.,1.,0.)
* q2 x full phase space
       call hbookb(90000  ,'q2 x0    ',1,kq2x0bin,0.)
       call hbook1(90010  ,'q2 x0    ',1,kq2x0bin(1),kq2x0bin(2),0.)
       call hbookb(90001  ,'q2 x1    ',3,kq2x1bin,0.)
       call hbook1(90011  ,'q2 x1    ',3,kq2x1bin(1),kq2x1bin(4),0.)
       call hbookb(90002  ,'q2 x2    ',2,kq2x2bin,0.)
       call hbook1(90012  ,'q2 x2    ',2,kq2x2bin(1),kq2x2bin(3),0.)
       call hbookb(90003  ,'q2 x22   ',3,kq2x21bin,0.)
       call hbook1(90013  ,'q2 x22   ',3,kq2x21bin(1),kq2x21bin(4),0.)
       call hbookb(90004  ,'q2 x3    ',2,kq2x3bin,0.)
       call hbook1(90014  ,'q2 x3    ',2,kq2x3bin(1),kq2x3bin(3),0.)
       call hbookb(90005  ,'q2 x4    ',2,kq2x4bin,0.)
       call hbook1(90015  ,'q2 x4    ',2,kq2x4bin(1),kq2x4bin(3),0.)
       call hbookb(90006  ,'q2 x5    ',1,kq2x5bin,0.)
       call hbook1(90016  ,'q2 x5    ',1,kq2x5bin(1),kq2x5bin(2),0.)
       
       do i=11001,11024
          call hidopt(i,'NSTAT')
       enddo
        do i=11030,11036
          call hidopt(i,'NSTAT')
       enddo
       call hidopt(90000,'NSTAT')
       call hidopt(90010,'NSTAT')
c
       call hidopt(140000,'NSTAT')
       call hidopt(144000,'NSTAT')
       call hidopt(150000,'NSTAT')
c
       call hidopt(144010,'NSTAT')
       call hidopt(144110,'NSTAT')
       call hidopt(144210,'NSTAT')
       call hidopt(160010,'NSTAT')
       call hidopt(170010,'NSTAT')
       call hidopt(180010,'NSTAT')
c
       call hidopt(144131,'NSTAT')
       call hidopt(144231,'NSTAT')
       call hidopt(160031,'NSTAT')
       call hidopt(170031,'NSTAT')
       call hidopt(180031,'NSTAT')
c
       call hidopt(144133,'NSTAT')
       call hidopt(144233,'NSTAT')
       call hidopt(160033,'NSTAT')
       call hidopt(170033,'NSTAT')
       call hidopt(180033,'NSTAT')
       do i=1,6
C 0-6
          call hidopt(140000+i,'NSTAT')
c 0-6
          call hidopt(144000+i,'NSTAT')
C 10-16
          call hidopt(144010+i,'NSTAT')
C 10-16
          call hidopt(144110+i,'NSTAT')
          call hidopt(144210+i,'NSTAT')
C 0-6
          call hidopt(150000+i,'NSTAT')
C 10-16
          call hidopt(160010+i,'NSTAT')
          call hidopt(170010+i,'NSTAT')
          call hidopt(180010+i,'NSTAT')
C
          call hidopt(90000+i,'NSTAT')
          call hidopt(90010+i,'NSTAT')
       enddo
       do i=1,5
C 21-25
          call hidopt(144020+i,'NSTAT')
C 21-25
          call hidopt(144120+i,'NSTAT')
          call hidopt(144220+i,'NSTAT')
C
          call hidopt(40000+i,'NSTAT')
          call hidopt(50000+i,'NSTAT')
C 21-25
          call hidopt(160020+i,'NSTAT')
          call hidopt(170020+i,'NSTAT')
          call hidopt(180020+i,'NSTAT')
       enddo
*     variables
       
********************************************************************
*
       xq2(1)=2.
       xq2(2)=10.
       xq2(3)=40.
       xq2(4)=1000.
       call hbookb(3   ,' Q2             ',nq2,xq2,0.)
       call hbookb(13  ,' muon Q2        ',nq2,xq2,0.)
       call hbookb(5113,' muon Q2 parton ',nq2,xq2,0.)
*
       call hbookb(5, '        Q2        ',nq2fine,xq2fine,0.)
       call hbookb(6,'    muon Q2        ',nq2fine,xq2fine,0.)
       call hbookb(5106,' muon Q2 parton ',nq2fine,xq2fine,0.)
*
       do i=1,nq2
        write(title,'(f9.0,A,F9.0)') xq2(i),' lt Q2 lt ',xq2(i+1)
        call Hbook1(20+i,title,50,xq2(i),xq2(i+1),0.)
       enddo
*
       xx(1)=-4.5
       xx(2)=-3.5
       xx(3)=-2.9
       xx(4)=-1.0
* 
       do i=1,nx
          write(title,'(f9.3,A,F9.3)') xx(i),' lt x lt ',xx(i+1)
          call Hbook1(30+i,title,50,xx(i),xx(i+1),0.)
       enddo
*
       call hbookb(4,' x ',nx,xx,0.)
       call hbookb(14,' muon x ',nx,xx,0.)
       call Hbook1(7,' x       ',50,xx(1),xx(4),0.)
       call Hbook1(8,' x muon  ',50,xx(1),xx(4),0.)
*
       call hbookb(1005,' x       ',nx,xx,0.)
       call hbookb(5114,' x muon  ',nx,xx,0.)
       call Hbook1(1007,' x       ',50,xx(1),xx(4),0.)
       call Hbook1(5108,' x muon  ',50,xx(1),xx(4),0.)
*
       call hbookb(10,' mu et  ZEUS bin  ',muetzbin,etzbinmu,0.)
       call hbookb(18,' mu et  ZEUS pt2.5 bin  ',muetzbin,etzbinmu2,0.)
       call hbookb(11,' mu eta ZEUS bin  ',muetazbin,etazbinmu,0.)
       call hbookb(15,' jetmu et  ZEUS bin ',jetetzbin,etzbinjet,0.)
       call hbookb(16,' jetmu eta ZEUS bin ',jetetazbin,etazbinjet,0.)
       call hbookb(17,' jet et ZEUS bin ',jetetzbin,etzbinjet,0.)
       call hbookb(19,' jet et ZEUS bin Q2gt10',jetetzbin,etzbinjet,0.)
*
       call Hbookb(5010,'DJM Etblab     ',netbins,etbins,0.)
       call Hbook1(5011,'DJM etablab    ',10, -3.,7.,0.)
       call Hbookb(5012,'DJM Etbbreit   ',netbins,etbins,0.)
       call Hbook1(5013,'DJM etabbreit  ',10,-3.,7.,0.)
       call hbookb(5017,'DJM jet et ZEUS bin ',jetetzbin,etzbinjet,0.)
       call Hbookb(5020,'DJM Etjetlab   ',netbins,etbins,0.)
       call Hbook1(5021,'DJM etalabjet  ',10,-3.,7.,0.)
       call Hbookb(5022,'DJM Etjetbreit ',netbins,etbins,0.)
       call Hbook1(5023,'DJM etajetbreit',10,-3.,7.,0.)
*
       call Hbook1(100,' Pt1 mu  ',30,0.,30.,0.)
       call Hbook1(101,' Pt2 mu  ',30,0.,30.,0.)
       call Hbook1(102,' eta1 mu ',10,-3.,4.,0.)
       call Hbook1(103,' eta2 mu ',10,-3.,4.,0.)
       call Hbook1(110,' all Pt1 ',20,0.,20.,0.)
       call Hbook1(111,' all Pt2 ',20,0.,20.,0.)
       call Hbook1(112,' all eta1',10,-3.,4.,0.)
       call Hbook1(113,' all eta2',10,-3.,4.,0.)
       call Hbook1(104,' Q2      ',10,0.1,3.1,0.)
       call Hbook1(105,' y       ',100,0.0,1.,0.)
       call Hbook1(106,' x       ',50,-11.0,-1.,0.)
*
       call Hbook1(120,'H1 Pt1      mu',20,0.,20.,0.)
       call Hbook1(121,'H1 Pt2      mu',20,0.,20.,0.)
       call Hbook1(122,'H1 eta1     mu',10,-3.,4.,0.)
       call Hbook1(123,'H1 eta2     mu',10,-3.,4.,0.)
       call Hbook1(130,'H1 all Pt1  mu',20,0.,20.,0.)
       call Hbook1(131,'H1 all Pt2  mu',20,0.,20.,0.)
       call Hbook1(132,'H1 all eta1 mu',10,-3.,4.,0.)
       call Hbook1(133,'H1 all eta2 mu',10,-3.,4.,0.)
       call Hbook1(124,'H1 Q2       mu',10,0.1,2.,0.)
       call Hbook1(125,'H1 y        mu',10,0.01,1.,0.)
       call Hbook1(126,'H1 phi12    mu',68,0.,3.4,0.)
*
       call Hbook1(240,'Breit Et_leadcut evt Et      ',10, 0.,20.,0.)
       call Hbook1(241,'Breit Et_leadcut evt Pt      ',10, 0.,20.,0.)
       call Hbook1(242,'Breit Et_leadcut evt etalab  ',10,-3.,4.,0.)
       call Hbook1(243,'Breit Et_leadcut evt Q2      ',10,0.1,2.2,0.)
       call Hbook1(244,'Breit Et_leadcut evt y       ',10,0.05,1.,0.)
       call Hbook1(245,'Breit Et_leadcut evt log10(x)',10,-5.0,-1.,0.)
*
       call Hbook1(250,'Breit Et_leadcut+Muon evt Et     ',7, 0.,21.,0.)
       call Hbook1(251,'Breit Et_leadcut+Muon evt Pt     ',5, 0.,20.,0.)
       call Hbook1(252,'Breit Et_leadcut+Muon evt etalab ',5,-3.,4.,0.)
       call Hbook1(253,'Breit Et_leadcut+Muon evt Q2     ',5,0.1,2.2,0.)
       call Hbook1(254,'Breit Et_leadcut+Muon evt y      ',5,0.05,1.,0.)
       call Hbook1(255,'Breit Et_leadcut+Muon evt lg(x)',10,-5.0,-1.,0.)
*
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
       call Hbook1(307,'Breit dijet log10(xi) ',10,-4.0,0.,0.)
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
       call Hbookb(1002,'DIS Q2        ',nq2fine,xq2fine,0.)
       call Hbook1(1003,'DIS y         ',10,0.05,0.85,0.)
       call Hbook1(1004,'DIS log10(x)  ',10,-5.0,-1.,0.)
*
       call Hbookb(1010,'DIS Etblab      ',netbins,etbins,0.)
       call Hbook1(1011,'DIS etablab     ',9,-2.5,6.5,0.)
       call Hbookb(1012,'DIS Etbbreit    ',netbins,etbins,0.)
       call Hbook1(1013,'DIS etabbreit   ',9,-2.5,6.5,0.)
       call Hbookb(1020,'DIS Etjetlab1   ',netbins,etbins,0.)
       call Hbook1(1021,'DIS etalabjet1  ',9,-2.5,6.5,0.)
       call Hbookb(1022,'DIS Etjetbreit1 ',netbins,etbins,0.)
       call Hbook1(1023,'DIS etajetbreit1',9,-2.5,6.5,0.)
       call Hbook1(1024,'DIS etalabjet1  ',18,-2.5,6.5,0.)
       call Hbook1(1025,'DIS etajetbreit1',18,-2.5,6.5,0.)
       call Hbook1(1026,'DIS etajetmulab ',18,-2.5,6.5,0.)
       call Hbook1(1027,'DIS etajetfwd   ',18,-2.5,6.5,0.)
*
       call Hbookb(1030,'DIS Etmu lab    ',nmuetbins,muetbins,0.)
       call Hbook1(1031,'DIS thmu lab    ',18, 0.,180.,0.)
       call Hbook1(1032,'DIS Etamulab    ',18,-2.5,6.5,0.)
       call Hbookb(1033,'DIS Pmulab      ',nmuetbins,muetbins,0.)
       call Hbook1(1034,'DIS log Etamulab ',20,-2.,1.,0.)
       call Hbookb(1040,'DIS Etjetlab2   ',netbins,etbins,0.)
       call Hbook1(1041,'DIS etalabjet2  ',9,-2.5,6.5,0.)
       call Hbookb(1050,'DIS Etjetbreit2 ',netbins,etbins,0.)
       call Hbook1(1051,'DIS etajetbreit2',9,-2.5,6.5,0.)
*
       call Hbookb(1110,'JET Etblab       ',netbins,etbins,0.)
       call Hbook1(1111,'JET etablab      ',9,-2.5,6.5,0.)
       call Hbookb(1112,'JET Etbbreit     ',netbins,etbins,0.)
       call Hbook1(1113,'JET etabbreit    ',9,-2.5,6.5,0.)
       call Hbookb(1120,'JET Etjetlab1    ',netbins,etbins,0.)
       call Hbook1(1121,'JET etalabjet1   ',9,-2.5,6.5,0.)
       call Hbookb(1122,'JET Etjetbreit1  ',netbins,etbins,0.)
       call Hbook1(1123,'JET etajetbreit1 ',9,-2.5,6.5,0.)
       call Hbook1(1124,'JET etalabjet1  ',18,-2.5,6.5,0.)
       call Hbook1(1125,'JET etajetbreit1',18,-2.5,6.5,0.)
       call Hbook1(1126,'JET etajetmulab ',18,-2.5,6.5,0.)
       call Hbook1(1127,'JET etajetfwd   ',18,-2.5,6.5,0.)
*
       call Hbookb(1130,'JET Etmu      ',nmuetbins,muetbins,0.)
       call Hbook1(1131,'JET thmu      ',18, 0.,180.,0.)
       call Hbook1(1132,'JET Etamulab  ',18,-2.5,6.5,0.)
       call Hbookb(1133,'JET Pmulab      ',nmuetbins,muetbins,0.)
       call Hbook1(1134,'JET log Etamulab ',20,-2.,1.,0.)
       call Hbookb(1140,'JET Etjetlab2    ',netbins,etbins,0.)
       call Hbook1(1141,'JET etalabjet2   ',9,-2.5,6.5,0.)
       call Hbookb(1150,'JET Etjetbreit2  ',netbins,etbins,0.)
       call Hbook1(1151,'JET etajetbreit2 ',9,-2.5,6.5,0.)
*
       call Hbookb(1114,'JET Etb maxpt      ',netbins,etbins,0.)
       call Hbook1(1115,'JET etalabb maxpt  ',10,-3.,6.,0.)
*
       call Hbookb(1102,'JET     Q2    ',nq2fine,xq2fine,0.)
       call Hbook1(1103,'JET y         ',10,0.05,0.85,0.)
       call Hbook1(1104,'JET log10(x)  ',10,-5.0,-1.0,0.)
*
       call Hbookb(1202,'DJM Q2        ',nq2fine,xq2fine,0.)
       call Hbook1(1203,'DJM y         ',10,0.05,0.85,0.)
       call Hbook1(1204,'DJM log10(x)  ',10,-5.0,-1.0,0.)
*
       call Hbookb(1210,'DJM Etblab       ',netbins,etbins,0.)
       call Hbook1(1211,'DJM etablab      ',9,-2.5,6.5,0.)
       call Hbookb(1212,'DJM Etbbreit     ',netbins,etbins,0.)
       call Hbook1(1213,'DJM etabbreit    ',9,-2.5,6.5,0.)
       call Hbookb(1220,'DJM Etjetlab1    ',netbins,etbins,0.)
       call Hbook1(1221,'DJM etalabjet1   ',9,-2.5,6.5,0.)
       call Hbookb(1222,'DJM Etjetbreit1  ',netbins,etbins,0.)
       call Hbook1(1223,'DJM etajetbreit1 ',9,-2.5,6.5,0.)
       call Hbook1(1224,'DJM etalabjet1  ',18,-2.5,6.5,0.)
       call Hbook1(1225,'DJM etajetbreit1',18,-2.5,6.5,0.)
       call Hbook1(1226,'DJM etajetmulab ',18,-2.5,6.5,0.)
       call Hbook1(1227,'DJM etajetfwd   ',18,-2.5,6.5,0.)
       call Hbook1(1228,'DJM Ptrel       ',20,0.,10.,0.)
       call Hbookb(1229,'DJM Etbbreitjetmu',netbins,etbins,0.)
*
       call Hbookb(1240,'DJM Etjetlab2    ',netbins,etbins,0.)
       call Hbook1(1241,'DJM etalabjet2   ',9,-2.5,6.5,0.)
       call Hbookb(1250,'DJM Etjetbreit2  ',netbins,etbins,0.)
       call Hbook1(1251,'DJM etajetbreit2 ',9,-2.5,6.5,0.)
*
       call Hbookb(1230,'DJM Etmu      ',nmuetbins,muetbins,0.)
       call Hbook1(1231,'DJM thmu      ',18, 0.,180.,0.)
       call Hbook1(1232,'DJM etamu     ',18,-2.5,6.5,0.)
       call Hbookb(1233,'DJM Pmulab    ',nmuetbins,muetbins,0.)
       call Hbook1(1234,'DJM log Etamulab ',20,-2.,1.,0.)
       call Hbook1(1235,'DJM Emu/Ejet    ',20,0.,1.5,0.)
       call Hbook1(1236,'DJM Ptmu/Ptjet  ',20,0.,1.,0.)
       call Hbook1(1237,'DJM Pzmu/Pzjet  ',20,0.,1.,0.)
*
       call Hbookb(1310,'DJM2 Etb       ',netbins,etbins,0.)
       call Hbook1(1311,'DJM2 etalabb   ',9,-2.5,6.5,0.)
       call Hbookb(1320,'DJM2 Etjetlab  ',netbins,etbins,0.)
       call Hbook1(1321,'DJM2 etalabjet ',9,-2.5,6.5,0.)
       call Hbookb(1330,'DJM2 Etmu1     ',nmuetbins,muetbins,0.)
       call Hbook1(1331,'DJM2 thmu      ',18, 0.,180.,0.)
       call Hbook1(1332,'DJM2 etamu     ',18,-2.5,6.5,0.)
       call Hbookb(1340,'DJM2 Etmu      ',nmuetbins,muetbins,0.)
       call Hbook1(1341,'DJM2 th2       ',18, 0.,180.,0.)
       call Hbookb(1350,'DJM2 dummy     ',nmuetbins,muetbins,0.)
       call Hbook1(1351,'DJM2 dummy     ',18, 0.,180.,0.)
       call Hbook1(1302,'DJM2 Q2        ',10,0.10,3.2,0.)
       call Hbook1(1303,'DJM2 y         ',10,0.05,0.85,0.)
       call Hbook1(1304,'DJM2 log10(x)  ',10,-5.0,-1.,0.)
*
       call Hbookb(1402,'MuNoJet Q2        ',nq2fine,xq2fine,0.)
       call Hbook1(1403,'MuNoJet y         ',10,0.05,0.85,0.)
       call Hbook1(1404,'MuNoJet log10(x)  ',10,-5.0,-1.,0.)
*
       call Hbookb(1410,'MuNoJet Etblab      ',netbins,etbins,0.)
       call Hbook1(1411,'MuNoJet etalabb     ',9,-2.5,6.5,0.)
       call Hbookb(1412,'MuNoJet Etbbreit    ',netbins,etbins,0.)
       call Hbook1(1413,'MuNoJet etabbreit   ',9,-2.5,6.5,0.)
       call Hbookb(1420,'MuNoJet Etjetlab1   ',netbins,etbins,0.)
       call Hbook1(1421,'MuNoJet etalabjet1  ',9,-2.5,6.5,0.)
       call Hbookb(1422,'MuNoJet Etjetbreit1 ',netbins,etbins,0.)
       call Hbook1(1423,'MuNoJet etajetbreit1',9,-2.5,6.5,0.)
       call Hbook1(1424,'MuNoJet etalabjet1  ',18,-2.5,6.5,0.)
       call Hbook1(1425,'MuNoJet etajetbreit1',18,-2.5,6.5,0.)
       call Hbook1(1426,'MuNoJet etajetmulab ',18,-2.5,6.5,0.)
       call Hbook1(1427,'MuNoJet etajetfwd ',18,-2.5,6.5,0.)
*
       call Hbookb(1430,'MuNoJet Etmu        ',nmuetbins,muetbins,0.)
       call Hbook1(1431,'MuNoJet thmu        ',18, 0.,180.,0.)
       call Hbook1(1432,'MuNoJet Etamulab    ',18,-2.5,6.5,0.)
       call Hbookb(1433,'MuNoJet Pmulab      ',nmuetbins,muetbins,0.)
       call Hbook1(1434,'MuNoJet log Etamulab ',20,-2.,1.,0.)
       call Hbookb(1440,'MuNoJet Etjetlab2   ',netbins,etbins,0.)
       call Hbook1(1441,'MuNoJet etalabjet2  ',9,-2.5,6.5,0.)
       call Hbookb(1450,'MuNoJet Etjetbreit2 ',netbins,etbins,0.)
       call Hbook1(1451,'MuNoJet etajetbreit2',9,-2.5,6.5,0.)
*
       if (gen.ne.'HVQ') then 
        call Hbookb(7010,'DIS Etblab dir      ',netbins,etbins,0.)
        call Hbook1(7011,'DIS etablab dir     ',9,-2.5,6.5,0.)
        call Hbookb(7012,'DIS Etbbreit dir    ',netbins,etbins,0.)
        call Hbook1(7013,'DIS etabbreit dir   ',9,-2.5,6.5,0.)
        call Hbookb(7020,'DIS Etjetlab1 dir   ',netbins,etbins,0.)
        call Hbook1(7021,'DIS etalabjet1 dir  ',9,-2.5,6.5,0.)
        call Hbookb(7022,'DIS Etjetbreit1 dir ',netbins,etbins,0.)
        call Hbook1(7023,'DIS etajetbreit1dir ',9,-2.5,6.5,0.)
        call Hbookb(7030,'DIS Etmu   dir      ',nmuetbins,muetbins,0.)
        call Hbook1(7031,'DIS thmu    dir     ',18, 0.,180.,0.)
        call Hbook1(7032,'DIS Etamulab dir    ',18,-2.5,6.5,0.)
        call Hbookb(7033,'DIS Pmulab   dir    ',nmuetbins,muetbins,0.)
*
        call Hbookb(7110,'JET Etblab   dir    ',netbins,etbins,0.)
        call Hbook1(7111,'JET etablab  dir    ',9,-2.5,6.5,0.)
        call Hbookb(7112,'JET Etbbreit dir    ',netbins,etbins,0.)
        call Hbook1(7113,'JET etabbreit dir   ',9,-2.5,6.5,0.)
        call Hbookb(7120,'JET Etjetlab1 dir   ',netbins,etbins,0.)
        call Hbook1(7121,'JET etalabjet1 dir  ',9,-2.5,6.5,0.)
        call Hbookb(7122,'JET Etjetbreit1 dir ',netbins,etbins,0.)
        call Hbook1(7123,'JET etajetbreit1 dir',9,-2.5,6.5,0.)
        call Hbookb(7130,'JET Etmu   dir      ',nmuetbins,muetbins,0.)
        call Hbook1(7131,'JET thmu   dir      ',18, 0.,180.,0.)
        call Hbook1(7132,'JET Etamulab dir    ',18,-2.5,6.5,0.)
        call Hbookb(7133,'JET Pmulab   dir    ',nmuetbins,muetbins,0.)
*
        call Hbookb(7210,'DJM Etblab     dir  ',netbins,etbins,0.)
        call Hbook1(7211,'DJM etablab    dir  ',9,-2.5,6.5,0.)
        call Hbookb(7212,'DJM Etbbreit   dir  ',netbins,etbins,0.)
        call Hbook1(7213,'DJM etabbreit  dir  ',9,-2.5,6.5,0.)
        call Hbookb(7220,'DJM Etjetlab1  dir  ',netbins,etbins,0.)
        call Hbook1(7221,'DJM etalabjet1  dir ',9,-2.5,6.5,0.)
        call Hbookb(7222,'DJM Etjetbreit1 dir ',netbins,etbins,0.)
        call Hbook1(7223,'DJM etajetbreit1 dir',9,-2.5,6.5,0.)
        call Hbookb(7230,'DJM Etmu   dir      ',nmuetbins,muetbins,0.)
        call Hbook1(7231,'DJM thmu    dir     ',18, 0.,180.,0.)
        call Hbook1(7232,'DJM Etamulab  dir   ',9,-2.5,6.5,0.)
        call Hbookb(7233,'DJM Pmulab   dir    ',nmuetbins,muetbins,0.)
*
        call Hbookb(6010,'DIS Etblab   indir    ',netbins,etbins,0.)
        call Hbook1(6011,'DIS etablab   indir   ',9,-2.5,6.5,0.)
        call Hbookb(6012,'DIS Etbbreit   indir  ',netbins,etbins,0.)
        call Hbook1(6013,'DIS etabbreit  indir  ',9,-2.5,6.5,0.)
        call Hbookb(6020,'DIS Etjetlab1  indir  ',netbins,etbins,0.)
        call Hbook1(6021,'DIS etalabjet1  indir ',9,-2.5,6.5,0.)
        call Hbookb(6022,'DIS Etjetbreit1 indir ',netbins,etbins,0.)
        call Hbook1(6023,'DIS etajetbreit1 indir',9,-2.5,6.5,0.)
        call Hbookb(6030,'DIS Etmu   indir      ',nmuetbins,muetbins,0.)
        call Hbook1(6031,'DIS thmu   indir      ',18, 0.,180.,0.)
        call Hbook1(6032,'DIS Etamulab  indir   ',9,-2.5,6.5,0.)
        call Hbookb(6033,'DIS Pmulab   indir    ',nmuetbins,muetbins,0.)
*
        call Hbookb(6110,'JET Etblab    indir   ',netbins,etbins,0.)
        call Hbook1(6111,'JET etablab    indir  ',9,-2.5,6.5,0.)
        call Hbookb(6112,'JET Etbbreit  indir   ',netbins,etbins,0.)
        call Hbook1(6113,'JET etabbreit  indir  ',9,-2.5,6.5,0.)
        call Hbookb(6120,'JET Etjetlab1   indir ',netbins,etbins,0.)
        call Hbook1(6121,'JET etalabjet1  indir ',9,-2.5,6.5,0.)
        call Hbookb(6122,'JET Etjetbreit1 indir ',netbins,etbins,0.)
        call Hbook1(6123,'JET etajetbreit1 indir',9,-2.5,6.5,0.)
        call Hbookb(6130,'JET Etmu    indir     ',nmuetbins,muetbins,0.)
        call Hbook1(6131,'JET thmu    indir     ',18, 0.,180.,0.)
        call Hbook1(6132,'JET Etamulab  indir   ',9,-2.5,6.5,0.)
        call Hbookb(6133,'JET Pmulab    indir   ',nmuetbins,muetbins,0.)
*
        call Hbookb(6210,'DJM Etblab     indir  ',netbins,etbins,0.)
        call Hbook1(6211,'DJM etablab    indir  ',9,-2.5,6.5,0.)
        call Hbookb(6212,'DJM Etbbreit   indir  ',netbins,etbins,0.)
        call Hbook1(6213,'DJM etabbreit  indir  ',9,-2.5,6.5,0.)
        call Hbookb(6220,'DJM Etjetlab1  indir  ',netbins,etbins,0.)
        call Hbook1(6221,'DJM etalabjet1 indir  ',9,-2.5,6.5,0.)
        call Hbookb(6222,'DJM Etjetbreit1  indir',netbins,etbins,0.)
        call Hbook1(6223,'DJM etajetbreit1 indir',9,-2.5,6.5,0.)
        call Hbookb(6230,'DJM Etmu   indir      ',nmuetbins,muetbins,0.)
        call Hbook1(6231,'DJM thmu   indir      ',18, 0.,180.,0.)
        call Hbook1(6232,'DJM Etamulab indir    ',9,-2.5,6.5,0.)
        call Hbookb(6233,'DJM Pmulab   indir    ',nmuetbins,muetbins,0.)
*
       endif
*
       call Hbookb(3002,'INCb Q2        ',nq2fine,xq2fine,0.)
       call Hbook1(3003,'INCb y         ',10,0.05,0.85,0.)
       call Hbook1(3004,'INCb log10(x)  ',10,-5.0,-1.,0.)
*
       call Hbookb(3010,'INCb Etblab      ',netbins,etbins,0.)
       call Hbook1(3011,'INCb etablab     ',9,-2.5,6.5,0.)
       call Hbookb(3012,'INCb Etbbreit    ',netbins,etbins,0.)
       call Hbook1(3013,'INCb etabbreit   ',9,-2.5,6.5,0.)
       call Hbookb(3020,'INCb Etjetlab    ',netbins,etbins,0.)
       call Hbook1(3021,'INCb etalabjet   ',18,-2.5,6.5,0.)
       call Hbookb(3022,'INCb Etjetbreit  ',netbins,etbins,0.)
       call Hbook1(3023,'INCb etajetbreit ',18,-2.5,6.5,0.)
       call Hbookb(3030,'INCb Etmu lab    ',nmuetbins,muetbins,0.)
       call Hbook1(3031,'INCb thmu lab    ',18, 0.,180.,0.)
       call Hbook1(3032,'INCb Etamulab    ',18,-2.5,6.5,0.)
       call Hbookb(3033,'INCb Pmulab      ',nmuetbins,muetbins,0.)
*
       call Hbookb(3102,'INCb Q2        ',nq2fine,xq2fine,0.)
       call Hbook1(3103,'INCb y         ',10,0.05,0.85,0.)
       call Hbook1(3104,'INCb log10(x)  ',10,-5.0,-1.,0.)
*
       call Hbookb(3110,'INCj Etblab      ',netbins,etbins,0.)
       call Hbook1(3111,'INCj etablab     ',9,-2.5,6.5,0.)
       call Hbookb(3112,'INCj Etbbreit    ',netbins,etbins,0.)
       call Hbook1(3113,'INCj etabbreit   ',9,-2.5,6.5,0.)
       call Hbookb(3120,'INCj Etjetlab    ',netbins,etbins,0.)
       call Hbook1(3121,'INCj etalabjet   ',18,-2.5,6.5,0.)
       call Hbookb(3122,'INCj Etjetbreit  ',netbins,etbins,0.)
       call Hbook1(3123,'INCj etajetbreit ',18,-2.5,6.5,0.)
       call Hbookb(3130,'INCj Etmu lab    ',nmuetbins,muetbins,0.)
       call Hbook1(3131,'INCj thmu lab    ',18, 0.,180.,0.)
       call Hbook1(3132,'INCj Etamulab    ',18,-2.5,6.5,0.)
       call Hbookb(3133,'INCj Pmulab      ',nmuetbins,muetbins,0.)
*
       call Hbookb(3202,'INCj Q2        ',nq2fine,xq2fine,0.)
       call Hbook1(3203,'INCj y         ',10,0.05,0.85,0.)
       call Hbook1(3204,'INCj log10(x)  ',10,-5.0,-1.,0.)
*
       call Hbookb(3210,'INCj Etblab      ',netbins,etbins,0.)
       call Hbook1(3211,'INCj etablab     ',9,-2.5,6.5,0.)
       call Hbookb(3212,'INCj Etbbreit    ',netbins,etbins,0.)
       call Hbook1(3213,'INCj etabbreit   ',9,-2.5,6.5,0.)
       call Hbookb(3220,'INCj Etjetlab    ',netbins,etbins,0.)
       call Hbook1(3221,'INCj etalabjet   ',18,-2.5,6.5,0.)
       call Hbookb(3222,'INCj Etjetbreit  ',netbins,etbins,0.)
       call Hbook1(3223,'INCj etajetbreit ',18,-2.5,6.5,0.)
       call Hbookb(3230,'INCj Etmu lab    ',nmuetbins,muetbins,0.)
       call Hbook1(3231,'INCj thmu lab    ',18, 0.,180.,0.)
       call Hbook1(3232,'INCb Etamulab    ',18,-2.5,6.5,0.)
       call Hbookb(3233,'INCb Pmulab      ',nmuetbins,muetbins,0.)
*
       call Hbook1(2010,'H1 DIS Etb       ',20, 0.,20.,0.)
       call Hbook1(2011,'H1 DIS etalabb   ',10,-3.,5.,0.)
       call Hbook1(2020,'H1 DIS Etjetlab  ',20, 0.,20.,0.)
       call Hbook1(2021,'H1 DIS etalabjet ',10,-3.,6.,0.)
       call Hbook1(2040,'H1 DIS Etjetlab2 ',20, 0.,20.,0.)
       call Hbook1(2041,'H1 DIS etalabjet2',10,-3.,6.,0.)
       call Hbook1(2030,'H1 DIS Etmu      ',40, 0.,10.,0.)
       call Hbook1(2031,'H1 DIS thmu      ',10, 0.,3.1,0.)
       call Hbook1(2002,'H1 DIS Q2        ',10,0.1,2.2,0.)
       call Hbook1(2003,'H1 DIS y         ',10,0.05,0.85,0.)
       call Hbook1(2004,'H1 DIS log10(x)  ',10,-5.0,-1.,0.)
*
       call Hbook1(2210,'H1 DJM Etb       ',20, 0.,20.,0.)
       call Hbook1(2211,'H1 DJM etalabb   ',10,-3.,5.,0.)
       call Hbook1(2220,'H1 DJM Etjetlab1 ',20, 0.,20.,0.)
       call Hbook1(2221,'H1 DJM etalabjet1',10,-3.,6.,0.)
       call Hbook1(2240,'H1 DJM Etjetlab2 ',20, 0.,20.,0.)
       call Hbook1(2241,'H1 DJM etalabjet2',10,-3.,6.,0.)
       call Hbook1(2230,'H1 DJM Etmu      ',40, 0.,10.,0.)
       call Hbook1(2231,'H1 DJM thmu      ',10, 0.,3.1,0.)
       call Hbook1(2202,'H1 DJM Q2        ',10,0.1,2.2,0.)
       call Hbook1(2203,'H1 DJM y         ',10,0.05,0.85,0.)
       call Hbook1(2204,'H1 DJM log10(x)  ',10,-5.0,-1.,0.)
*

*
*     call hbarx(0)
*     zerujemy zmioenne
       direct=.false.
       indirect=.false.
*
       sigbrtot=0.
       sigb=0.
       sigbreit=0.
       sigbreitnj=0.
       sigbreitm=0.
*
       sigtoth1=0.
       sigbh1=0.
       sigtotmh1=0.
       sigjeth1=0.
       sigjetmh1=0.
       sigjetmcon=0.
       sigincljet=0.
       siginclmu=0.
       siginclb=0.
*
       imu1=0.
       imu2=0.
       imuacc1=0.
       imuacc2=0.
       q2old=-1.
       xbjold=-1.
       idir=0.
       itau=0.
       ioth=0.
       indir=0.
*
C       call HZHIJET2(0,1,nsel,jetsel)
C       call HZHIJET (0,1,nsel,jetsel)
*
      endif   
*     Koniec tworzenia histogramow
      if (iflag.eq.2) then
*         nev=nev+1
*     
         call hcdir('//PAWC/'//dir,' ')
*  
         q2  =real(HZDISKIN(1))
         xbj =real(HZDISKIN(2))
         y   =real(HZDISKIN(3))
C         write(6,*) ' q2 ',q2,' xbj ',xbj,' y ',y
*     
         PT1 =-999.
         PT2 =-999.
         ETA1=-999.
         ETA2=-999.
         PT3 =-999.
         ETA3=-999.
         th1=0.
         th2=0.
         ph1=0.
         ph2=0.
*
         do i=0,3
            pm1(i)=0.
            pm2(i)=0.
            p1(i) =0.
            p2(i) =0.
            p3(i) =0.
         enddo
*     
         if (GEN.eq.'HVQ') then
*
            if (q2.ne.q2old .and. xbj.ne.xbjold) then
               q2old=q2
               xbjold=xbj
*     
               muon1=.false.
               muon2=.false.
               
C     CALL BRM48 (DVEC, 1)
*     random gen
               CALL BRM48 (DVEC, 2)
*
C     if (real(dvec(2)).le.hfrac) then
               muon1=.true.
C     endif
*
C     if (real(dvec(1)).le.hfrac) then
               if (real(dvec(1)).le.hfrac/(2-hfrac)) then
                  muon2=.true.
               endif
*     
               CALL BRM48 (DVEC, 10)
               hfrac1=2*hfrac-hfrac**2
            endif
*     
            IF (WTX.EQ.0D0)RETURN
*     
            PT1=hzet(5)
            PT2=hzet(6)
            ETA1=hzeta(5)
            ETA2=hzeta(6)
            if (nhep.ge.7) then  
               PT3=hzet(7)
               ETA3=hzeta(7)
            endif
*
            do i=1,3
               P1(i)=PHEP(i,5)
               P2(i)=PHEP(i,6)
               if (nhep.ge.7) then  
                  P3(i)=PHEP(i,7)
               endif
            enddo
            P1(0)=PHEP(4,5)
            P2(0)=PHEP(4,6)
            if (nhep.ge.7) then  
               P3(0)=PHEP(4,7)
            endif
*     
*       factor 1000 to convert nb -> pb
            TMP=WTX*1000D0
            if(kula.lt.100)then
               write(6,*) 'wtx',wtx,'hfrac',hfrac1
               kula=kula+1
            endif
            WTX=0D0
            WTXM=0D0
*  
            do i=0,3
               PM1(i)=P1(i)
               PM2(i)=P2(i)
            enddo   
** before frag     
            ppmom=sqrt(PM1(1)**2+PM1(2)**2+PM1(3)**2)
            ppthe=acos(PM1(3)/ppmom)
            ppeta=LOG(tan(ppthe/2.))
            ppeta=SIGN(ppeta,PM1(3))
            ppphi=atan2(PM1(2),PM1(1))
            call Hfill(11030,real(ppphi),0.
     &           ,real(tmp*hfrac1))
            call Hfill(11031,real(ppeta),0.
     &           ,real(tmp*hfrac1))
            ppmom=sqrt(PM2(1)**2+PM2(2)**2+PM2(3)**2)
            ppthe=acos(PM2(3)/ppmom)
            ppeta=LOG(tan(ppthe/2.))
            ppeta=SIGN(ppeta,PM2(3))
            ppphi=atan2(PM2(2),PM2(1))
            call Hfill(11030,real(ppphi),0.
     &           ,real(tmp*hfrac1))
            call Hfill(11031,real(ppeta),0.
     &           ,real(tmp*hfrac1))
*     frag fun !!!!!
            CALL FRAG(DVEC,PM1,PM2)
*             
*     after frag
            ppmom=sqrt(PM1(1)**2+PM1(2)**2+PM1(3)**2)
            ppthe=acos(PM1(3)/ppmom)
            ppeta=LOG(tan(ppthe/2.))
            ppeta=SIGN(ppeta,PM1(3))
            ppphi=atan2(PM1(2),PM1(1))
            call Hfill(11032,real(ppphi),0.
     &           ,real(tmp*hfrac1))
            call Hfill(11033,real(ppeta),0.
     &           ,real(tmp*hfrac1))
            ppmom=sqrt(PM2(1)**2+PM2(2)**2+PM2(3)**2)
            ppthe=acos(PM2(3)/ppmom)
            ppeta=LOG(tan(ppthe/2.))
            ppeta=SIGN(ppeta,PM2(3))
            ppphi=atan2(PM2(2),PM2(1))
            call Hfill(11032,real(ppphi),0.
     &           ,real(tmp*hfrac1))
            call Hfill(11033,real(ppeta),0.
     &           ,real(tmp*hfrac1))
*************************************
         else
*     
            tmp=wtx
            wtxm=0D0
            hfrac=1D0
            muon1=.true.
            muon2=.true.
*     
            write(6,*) 'we are here'
            ptmin=6.
            plot=.true.
*     
         endif
*
         if (tmp.ne.tmp) then
            write(6,*) '**hzb: start tmp= ',tmp
*            call hzlihep(2)
            wtx=0D0
            return
         endif

*
*    find muon and b-quarks
*
         ptm1 =-1
         etam1=-999.
         pmum1=-1.
         ptm2 =-1
         etam2=-999.
         pmum2=-1.
*     
         imuon=-1
         imuon2=-1
         nmuon=0.
         inthecon=0.
         do i=1,nhep
            ppmas=sqrt(phep(4,i)**2
     &           -(phep(1,i)**2+phep(2,i)**2+phep(3,i)**2))
            call hfill(11034,real(ppmas),0.,real(tmp*hfrac1))
            if (abs(idhep(i)).eq.5.) then
*     beauty !!!!!
               if (idhep(i).eq.5) then
                  ib=i
                  etab=hzeta(i)  
                  etb =hzet(i)  
               endif
               if (idhep(i).eq.-5) then
                  ibar=i
                  etabar=hzeta(i)  
                  etbar =hzet(i)  
               endif
            endif 
*     muon !!!!!
*     Et1>Et2
            if (abs(idhep(i)).eq.13) then
*     find a muon in the acceptance
               th=hztheta(i)
*     this is the ZEUS acceptance, H1 acceptance is smaller
C     if (th*rd.gt.30. .and. th*rd.lt.160.) then 
               if (th*rd.ge.0. .and. th*rd.le.180.) then               
c              if (hzeta(i).gt.-1.6. .and. th*rd.lt.180.) then 
                  nmuon=nmuon+1
                  if (hzet(i).gt.ptm1.and.nmuon.eq.1) then
                     ptm1=hzet(i)
                     pmum1=sqrt(phep(1,i)**2+phep(2,i)**2+phep(3,i)**2)
                     etam1=hzeta(i)
                     th1=hztheta(i) 
                     ph1=hzphi(i) 
*     liczba mionow w akceptancji ZEUSA !!!!!
                     imuon=i
                  endif
*
                  if (hzet(i).gt.ptm2 .and. nmuon.gt.1) then
                     if (hzet(i).gt.ptm1) then
                        ptm2=ptm1
                        etam2=etam1
                        pmum2=pmum1
                        th2=th1
                        ph2=ph1
                        imuon2=imuon
*     
                        ptm1=hzet(i)  
                        etam1=hzeta(i)
                        pmum1=sqrt(phep(1,i)**2+phep(2,i)**2
     &                       +phep(3,i)**2)
                        th1=hztheta(i) 
                        ph1=hzphi(i) 
                        imuon=i
                     else
                        ptm2=hzet(i)
                        etam2=hzeta(i)
                        pmum2=sqrt(phep(1,i)**2+phep(2,i)**2
     &                       +phep(3,i)**2)
                        th2=hztheta(i) 
                        ph2=hzphi(i) 
                        imuon2=i
                     endif 
                  endif
               endif
            endif 
         enddo
*     muon was found 
         if (imuon.gt.0) imucount=imucount+1
*     
         if (lp) then
            if (ptm1.gt.0.) then 
               write(6,*) ' muon found ! ihep= ',imuon,ptm1,pmum1,th1*rd
               write(6,*) ' phep= ',phep(1,imuon),phep(2,imuon),
     &              phep(3,imuon),phep(4,imuon)
               write(6,*) ' number of muons: ',nmuon
            endif
            if (ptm2.gt.0) then
               write(6,*) ' second muon ihep= ',imuon2,ptm2,pmum2,th2*rd
               call hzlihep(2) 
*     
            endif 
         endif
*
         if (GEN.eq.'HVQ') then
*     MIUONS from HVQDIS !!!!!
            PTM1=-999.
            PTM2=-999.
            PMUM1=-999.
            PMUM2=-999.
            ETAM1=-999.
            ETAM2=-999.
            Th1=-999.
            Th2=-999.
            ph1=-999.
            ph2=-999.
            kmuon=0.
            kmuon1=-999.
            kmuon2=-999.
*     zwraca pt
            PTM1=EPERP(PM1)
            PMUM1=sqrt(PM1(1)**2+PM1(2)**2+PM1(3)**2)
            if(PMUM1.ne.0) then
               th1=acos(PM1(3)/PMUM1)
* 1->2
               ph1=atan2(PM1(2),PM1(1))
               etam1= LOG(tan(th1/2.))
               etam1=SIGN(etam1,PM1(3))
                 call Hfill(11023,real(ph1),0.
     &           ,real(tmp*hfrac1))
            endif
*     
            PTM2=EPERP(PM2)
            PMUM2=sqrt(PM2(1)**2+PM2(2)**2+PM2(3)**2)
            if(PMUM2.ne.0.and.muon2) then
               th2=acos(PM2(3)/PMUM2)
* 1->2
               ph2=atan2(PM2(2),PM2(1))
               etam2= LOG(tan(th2/2.))
               etam2=SIGN(etam2,pm2(3))
               call Hfill(11023,real(ph2),0.
     &           ,real(tmp*hfrac1))
            endif
         endif
*
*     get electron and beams
*
         iel=HZIDELEC(idum)
         if (iel.eq.-1) then
            write(6,*) '**hzb: electron not found '
            return
         endif
*     
         ierr=HZIBEAM(ibeam,idum)
         if (.not.(ierr.eq.1)) then
            write(6,*) '**hzb: beams not found ! '
            return
         endif
         Do i=1,4
            psel(i)=PHEP(i,iel)
         enddo
*
         PHAD=PHEP(3,IBEAM)
         PLEP=PHEP(3,IDUM)
c
c        NLO bands for Philipp
c
         IF ((Q2.GT.Q2MIN.AND.Q2.LT.Q2MAX).AND.
     +       (XBJ.GT.XMIN.AND.XBJ.LT.XMAX).AND.
     +       (Y.GT.0.02.AND.Y.LT.0.9)) THEN

           IF (plot) THEN
             CALL HFILL(32001,REAL(LOG10(XBJ)),0.,REAL(tmp))
           ENDIF

         ENDIF
*     
*     Labframe cross section
*
*     CUTS
         if ((Q2 .gt.Q2MIN .and. Q2.lt.Q2MAX).and.
     &        ( y .gt.YMIN.and.  y.lt.YMAX ).and. 
     &        ( xbj .gt.XMIN.and.  xbj.lt.XMAX ) )then

            nev=nev+1
*     find jets !!!!!
*     
            Do i=1,maxhzjets
               do j=1,8
                  jets(i,j)=0.
                  jetsel(i,j)=0.
                  jetslab(i,j)=0.
                  jetsellab(i,j)=0.
               enddo
               ipjet(i)=0
               ipjetsel(i)=0
            enddo
*     
*     Jetslab(Njet,x) = information about jets found
*     x= 1,2  rapidity, phi  of jet axis
*     3    Et  of jet
*     4-8  (E,px,py,pz,m) of jet axis

            CALL hzjtfind(3,1.d0,NJET,Jetslab)
*     
            do i=1,nhep
               ppmas=sqrt(phep(4,i)**2
     &              -(phep(1,i)**2+phep(2,i)**2+phep(3,i)**2))
               call hfill(11035,real(ppmas),0.,real(tmp*hfrac1))
            enddo
            nsel=0

c           Init for Philipp
            nsel4 = 0

            do j=1,njet
               pt=sqrt(jetslab(j,5)**2+jetslab(j,6)**2)
               kjetp=sqrt(jetslab(j,7)**2+pt**2)
               kjetene=jetslab(j,4)
               kjetcut=kjetene*pt/kjetp
               ppmas=kjetene**2-kjetp**2
               call hfill(11036,real(ppmas),0.
     &              ,real(tmp*hfrac1))
               if(kjetcut.gt.(jetslab(j,3)+0.01) .or.
     &              kjetcut.lt.(jetslab(j,3)-0.01))then
                  write(6,*)'Et!',kjetcut,'ktet',jetslab(j,3)
               endif
** !!!!!!!!!!!!!!!!!
               dephi=atan2(jetslab(j,6),jetslab(j,5))
               call Hfill(11024,real(dephi),0.
     &              ,real(tmp*hfrac1))
*               kjetcut=pt
               if (kjetcut.gt.5. 
*               if (jetslab(j,3).gt.5. 
*     &              .and. jetslab(j,1).gt.-1.0
c     &              .and. jetslab(j,1).gt.-2.0
c     &              .and.jetslab(j,1).lt.2.5) then
c     Jet selection for Philipp
     &              .and.jetslab(j,1).gt.-1.6
     &              .and.jetslab(j,1).lt.2.2) then               
                  nsel=nsel+1
                  ipjet(nsel)=j
C     ipjetsel(j)=nsel
                  do i=1,8
                     jetsellab(nsel,i)=jetslab(j,i)
                  enddo
               endif

c              Jets with ET > 4.2 GeV for Philipp
               IF (kjetcut.GT.4.2
     +             .AND.jetslab(j,1).GT.-1.6
     +             .AND.jetslab(j,1).LT.2.2) THEN
                 nsel4 = nsel4 + 1
                 DO i=1,8
                   jetsellab4(nsel4,i)=jetslab(j,i)
                 ENDDO
               ENDIF

            enddo
* !!!!!!!!!!!!!!!!!!!!!!!!! added
            wtx=tmp
            kjetid=999
            kjetid1=999
            kjetid2=999
            drmin1=999D0
            drmin2=999D0
            do i=1,nsel
               j=i
               dephi=atan2(jetsellab(j,6),jetsellab(j,5))-
     &              ph1
               dephi1=atan2(jetsellab(j,6),jetsellab(j,5))-
     &              ph2
               deteta=jetsellab(j,1)-etam1
               deteta1=jetsellab(j,1)-etam2
               if(dephi.gt.PI)then
                  dephi=2*PI-dephi
               endif 
               if(dephi.lt.(-1*PI))then
                  dephi=2*PI+dephi
               endif
               if(dephi1.gt.PI)then
                  dephi1=2*PI-dephi1
               endif 
               if(dephi1.lt.(-1*PI))then
                  dephi1=2*PI+dephi1
               endif
               call Hfill(11017,real(dephi),0.
     &              ,real(wtx*hfrac1))
               call Hfill(11017,real(dephi1),0.
     &              ,real(wtx*hfrac1))
               call Hfill(11018,real(deteta),0.
     &              ,real(wtx*hfrac1))
               call Hfill(11018,real(deteta1),0.
     &              ,real(wtx*hfrac1))
               dr=sqrt(dephi**2+deteta**2)             
               call Hfill(11019,real(dr),0.
     &              ,real(wtx*hfrac1))
               if(dr.le.0.7)then
                  if(drmin1.gt.dr)then
                        drmin1=dr
                        kjetid1=j
                  endif
C		  if(kjetid.gt.j)then	
C                     kjetid=j
C		  endif	
                  call Hfill(11020,real(dephi),0.
     &                 ,real(wtx*hfrac1))
                  call Hfill(11021,real(deteta),0.
     &                 ,real(wtx*hfrac1))
                  call Hfill(11022,real(dr),0.
     &                 ,real(wtx*hfrac1))
               endif
               dr=sqrt(dephi1**2+deteta1**2)
               call Hfill(11019,real(dr),0.
     &              ,real(wtx*hfrac1))

               if(dr.le.0.7)then
                  if(drmin2.gt.dr)then
                     drmin2=dr
                     kjetid2=j
                  endif
C		  if(kjetid.gt.j)then
C                     kjetid=j
C                  endif
                  call Hfill(11020,real(dephi1),0.
     &                 ,real(wtx*hfrac1))
                  call Hfill(11021,real(deteta1),0.
     &                 ,real(wtx*hfrac1))
                  call Hfill(11022,real(dr),0.
     &                 ,real(wtx*hfrac1))
       
               endif
            enddo
*     
*     pt1 is b-quark: H1 measures ep->b X
*     
*     in HVQDIS ptm1 is the muon from the bottom quark
*     since H1 measures ep-> b X this is correct        
*     in the other MCs, however, the muon can come either from
*     b or bbar therefore one has to divide by 2
*     since ptm1 is the highest Pt muon which can come from b or bbar
*
            
            if (gen.eq.'HVQ') then
               wtx=tmp
            else
*     H1 measure B-cross section
*     divide by 2, since one does not know where muon comes from
               wtx=tmp/2D0
            endif
*


c     Plots for Philipp

            IF (plot) THEN

               DO nrjet = 1, nsel

                  CALL HFILL(30001,REAL(jetsellab(nrjet,3)),0.
     +                 ,REAL(wtx))
                  CALL HFILL(30002,REAL(jetsellab(nrjet,1)),0.
     +                 ,REAL(wtx))
                  CALL HFILL(30003,REAL(Q2),0.,REAL(wtx))
                  CALL HFILL(30004,REAL(XBJ),0.,REAL(wtx))

                  IF (Q2.GT.5.0.AND.Q2.LT.20.0) THEN
                     CALL HFILL(31001,REAL(XBJ),0.,REAL(wtx))
                  ENDIF
                  IF (Q2.GT.20.0.AND.Q2.LT.60.0) THEN
                     CALL HFILL(31002,REAL(XBJ),0.,REAL(wtx))
                  ENDIF
                  IF (Q2.GT.60.0.AND.Q2.LT.120.0) THEN
                     CALL HFILL(31003,REAL(XBJ),0.,REAL(wtx))
                  ENDIF
                  IF (Q2.GT.120.AND.Q2.LT.400.0) THEN
                     CALL HFILL(31004,REAL(XBJ),0.,REAL(wtx))
                  ENDIF
                  IF (Q2.GT.400.0.AND.Q2.LT.1000.0) THEN
                     CALL HFILL(31005,REAL(XBJ),0.,REAL(wtx))
                  ENDIF

               ENDDO

               DO nrjet = 1, nsel4

                  CALL HFILL(30101,REAL(jetsellab4(nrjet,3)),0.
     +                 ,REAL(wtx))
                  CALL HFILL(30102,REAL(jetsellab4(nrjet,1)),0.
     +                 ,REAL(wtx))
                  CALL HFILL(30103,REAL(Q2),0.,REAL(wtx))
                  CALL HFILL(30104,REAL(XBJ),0.,REAL(wtx))

                  IF (Q2.GT.5.0.AND.Q2.LT.20.0) THEN
                     CALL HFILL(31101,REAL(XBJ),0.,REAL(wtx))
                  ENDIF
                  IF (Q2.GT.20.0.AND.Q2.LT.60.0) THEN
                     CALL HFILL(31102,REAL(XBJ),0.,REAL(wtx))
                  ENDIF
                  IF (Q2.GT.60.0.AND.Q2.LT.120.0) THEN
                     CALL HFILL(31103,REAL(XBJ),0.,REAL(wtx))
                  ENDIF
                  IF (Q2.GT.120.AND.Q2.LT.400.0) THEN
                     CALL HFILL(31104,REAL(XBJ),0.,REAL(wtx))
                  ENDIF
                  IF (Q2.GT.400.0.AND.Q2.LT.1000.0) THEN
                     CALL HFILL(31105,REAL(XBJ),0.,REAL(wtx))
                  ENDIF

               ENDDO

            ENDIF

            if (plot) then

               xellog=log10(xbj)
               kweq2=q21-q20
C H1 vs. Zeus
               call Hfill(50111,real(xbj),0.
     &              ,real(wtx/0.00000126))
               call Hfill(51001,real(xbj),0.
     &              ,real(wtx/0.000021))
               call Hfill(51011,real(xbj),0.
     &              ,real(wtx))
C
               call Hfill(50112,real(xbj),0.
     &              ,real(wtx/0.000004))               
               call Hfill(51101,real(xbj),0.
     &              ,real(wtx/0.000025))
               call Hfill(51111,real(xbj),0.
     &              ,real(wtx))
C
               call Hfill(50113,real(xbj),0.
     &              ,real(wtx/0.000004))
               call Hfill(51201,real(xbj),0.
     &              ,real(wtx/0.00001666666666666667))
               call Hfill(51211,real(xbj),0.
     &              ,real(wtx))
C
               call Hfill(50114,real(xbj),0.
     &              ,real(wtx/0.00001588)) 
               call Hfill(51301,real(xbj),0.
     &              ,real(wtx/0.00006616666666666667))
               call Hfill(51311,real(xbj),0.
     &              ,real(wtx))
C
                call Hfill(50115,real(xbj),0.
     &              ,real(wtx/0.00001002))
               call Hfill(51401,real(xbj),0.
     &              ,real(wtx/0.00002004))
               call Hfill(51411,real(xbj),0.
     &              ,real(wtx))
C
               call Hfill(50116,real(xbj),0.
     &              ,real(wtx/0.0000399))
               call Hfill(51501,real(xbj),0.
     &              ,real(wtx/0.0000798))
               call Hfill(51511,real(xbj),0.
     &              ,real(wtx))
C
               call Hfill(50117,real(xbj),0.
     &              ,real(wtx/0.0000399))
               call Hfill(51601,real(xbj),0.
     &              ,real(wtx/0.00003325))
               call Hfill(51611,real(xbj),0.
     &              ,real(wtx))
C
               call Hfill(50118,real(xbj),0.
     &              ,real(wtx/0.00010024))
               call Hfill(51701,real(xbj),0.
     &              ,real(wtx/0.00008353333333333333))
               call Hfill(51711,real(xbj),0.
     &              ,real(wtx))
C
               call Hfill(50119,real(xbj),0.
     &              ,real(wtx/0.0000399))
               call Hfill(51801,real(xbj),0.
     &              ,real(wtx/0.00001813636363636364))
               call Hfill(51811,real(xbj),0.
     &              ,real(wtx))
C
               call Hfill(50120,real(xbj),0.
     &              ,real(wtx/0.0002))
               call Hfill(51901,real(xbj),0.
     &              ,real(wtx/0.5))
               call Hfill(51911,real(xbj),0.
     &              ,real(wtx))
C
               call Hfill(50121,real(xbj),0.
     &              ,real(wtx/0.0002))
               call Hfill(52001,real(xbj),0.
     &              ,real(wtx/0.16666666666666666667))
               call Hfill(52011,real(xbj),0.
     &              ,real(wtx))
C ******************************************
               call Hfill(61011,real(q2),0.
     &              ,real(wtx))
               call Hfill(71011,real(xbj),0.
     &              ,real(wtx))
               call Hfill(81011,real(y),0.
     &              ,real(wtx))
               call Hfill(91011,real(xbj),real(q2)
     &              ,real(wtx))
C     
               call Hfill(61111,real(q2),0.
     &              ,real(wtx))
               call Hfill(71111,real(xbj),0.
     &              ,real(wtx))
               call Hfill(81111,real(y),0.
     &              ,real(wtx))
               call Hfill(91111,real(xbj),real(q2)
     &              ,real(wtx))
C     
               call Hfill(61211,real(q2),0.
     &              ,real(wtx))
               call Hfill(71211,real(xbj),0.
     &              ,real(wtx))
               call Hfill(81211,real(y),0.
     &              ,real(wtx))
               call Hfill(91211,real(xbj),real(q2)
     &              ,real(wtx))
C
               call Hfill(61311,real(q2),0.
     &              ,real(wtx))
               call Hfill(71311,real(xbj),0.
     &              ,real(wtx))
               call Hfill(81311,real(y),0.
     &              ,real(wtx))
               call Hfill(91311,real(xbj),real(q2)
     &              ,real(wtx))
C     
               call Hfill(61411,real(q2),0.
     &              ,real(wtx))
               call Hfill(71411,real(xbj),0.
     &              ,real(wtx))
               call Hfill(81411,real(y),0.
     &              ,real(wtx))
               call Hfill(91411,real(xbj),real(q2)
     &              ,real(wtx))
C     
               call Hfill(61511,real(q2),0.
     &              ,real(wtx))
               call Hfill(71511,real(xbj),0.
     &              ,real(wtx))
               call Hfill(81511,real(y),0.
     &              ,real(wtx))
               call Hfill(91511,real(xbj),real(q2)
     &              ,real(wtx))
C     
               call Hfill(61611,real(q2),0.
     &              ,real(wtx))
               call Hfill(71611,real(xbj),0.
     &              ,real(wtx))
               call Hfill(81611,real(y),0.
     &              ,real(wtx))
               call Hfill(91611,real(xbj),real(q2)
     &              ,real(wtx))
C
               call Hfill(61711,real(q2),0.
     &              ,real(wtx))
               call Hfill(71711,real(xbj),0.
     &              ,real(wtx))
               call Hfill(81711,real(y),0.
     &              ,real(wtx))
               call Hfill(91711,real(xbj),real(q2)
     &              ,real(wtx))
C     
               call Hfill(61811,real(q2),0.
     &              ,real(wtx))
               call Hfill(71811,real(xbj),0.
     &              ,real(wtx))
               call Hfill(81811,real(y),0.
     &              ,real(wtx))
               call Hfill(91811,real(xbj),real(q2)
     &              ,real(wtx))
C     
               call Hfill(61911,real(q2),0.
     &              ,real(wtx))
               call Hfill(71911,real(xbj),0.
     &              ,real(wtx))
               call Hfill(81911,real(y),0.
     &              ,real(wtx))
               call Hfill(91911,real(xbj),real(q2)
     &              ,real(wtx))
C     
               call Hfill(62011,real(q2),0.
     &              ,real(wtx))
               call Hfill(72011,real(xbj),0.
     &              ,real(wtx))
               call Hfill(82011,real(y),0.
     &              ,real(wtx))
               call Hfill(92011,real(xbj),real(q2)
     &              ,real(wtx))
*     ****************************************
              if(q2.ge.q20 .and.q2.le.q21)then
                  if(xellog.ge.q20x1 .and.xellog.le.q20x2)then
                     call Hfill(144000,real(xellog),0.
     &                    ,real(wtx/kweq2))
                  endif
*     1th bin 
                  if(xellog.ge.q20x1.and. xellog.lt.q20x2)then
                     call Hfill(144010,real(q2),0.
     &                    ,real(wtx))
                     call Hfill(144110,real(xellog),0.
     &                    ,real(wtx))
                     call Hfill(144210,real(y),0.
     &                    ,real(wtx))
                  endif
               endif
*     **************
               kweq2=q22-q21
               if(q2.ge.q21 .and.q2.le.q22)then
                  if(xellog.ge.q21x1 .and.xellog.le.q21x4)then
                     call Hfill(144001,real(xellog),0.
     &                    ,real(wtx/kweq2))
                  endif
*     1th bin 
                  if(xellog.ge.q21x1.and. xellog.lt.q21x2)then
                     call Hfill(144011,real(q2),0.
     &                    ,real(wtx))
                     call Hfill(144111,real(xellog),0.
     &                    ,real(wtx))
                     call Hfill(144211,real(y),0.
     &                    ,real(wtx))
                  endif
*     2th bin 
                  if(xellog.ge.q21x2.and. xellog.lt.q21x3)then
                     call Hfill(144021,real(q2),0.
     &                    ,real(wtx))
                     call Hfill(144121,real(xellog),0.
     &                    ,real(wtx))
                     call Hfill(144221,real(y),0.
     &                    ,real(wtx))
                  endif
*     3th bin 
                  if(xellog.ge.q21x3.and. xellog.le.q21x4)then
                     call Hfill(144031,real(q2),0.
     &                          ,real(wtx))
                     call Hfill(144131,real(xellog),0.
     &                    ,real(wtx))
                     call Hfill(144231,real(y),0.
     &                    ,real(wtx))
                  endif
               endif
*     **************
               kweq2=q23-q22
               if(q2.ge.q22 .and.q2.le.q23)then
                  if(xellog.ge.q22x1 .and.xellog.le.q22x3)then
                     call Hfill(144002,real(xellog),0.
     &                    ,real(wtx/kweq2))
                  endif
* 1th bin 
                  if(xellog.ge.q22x1.and. xellog.lt.q22x2)then
                     call Hfill(144012,real(q2),0.
     &                    ,real(wtx))
                     call Hfill(144112,real(xellog),0.
     &                    ,real(wtx))
                     call Hfill(144212,real(y),0.
     &                    ,real(wtx))
                  endif
*     2th bin 
                  if(xellog.ge.q22x2.and. xellog.lt.q22x3)then
                     call Hfill(144022,real(q2),0.
     &                    ,real(wtx))
                     call Hfill(144122,real(xellog),0.
     &                    ,real(wtx))
                     call Hfill(144222,real(y),0.
     &                    ,real(wtx))
                  endif
               endif
               if(q2.ge.q22 .and.q2.le.q23)then
                  if(xellog.ge.q22x11 .and.xellog.le.q22x41)then
                     call Hfill(144003,real(xellog),0.
     &                    ,real(wtx/kweq2))
                  endif
*     1th bin 
                  if(xellog.ge.q22x11.and. xellog.lt.q22x21)then
                     call Hfill(144013,real(q2),0.
     &                    ,real(wtx))
                     call Hfill(144113,real(xellog),0.
     &                    ,real(wtx))
                     call Hfill(144213,real(y),0.
     &                          ,real(wtx))
                  endif
*     2th bin 
                  if(xellog.ge.q22x21.and. xellog.lt.q22x31)then
                     call Hfill(144023,real(q2),0.
     &                    ,real(wtx))
                     call Hfill(144123,real(xellog),0.
     &                    ,real(wtx))
                     call Hfill(144223,real(y),0.
     &                    ,real(wtx))
                  endif
*     3th bin 
                  if(xellog.ge.q22x31.and. xellog.le.q22x41)then
                     call Hfill(144033,real(q2),0.
     &                    ,real(wtx))
                     call Hfill(144133,real(xellog),0.
     &                    ,real(wtx))
                     call Hfill(144233,real(y),0.
     &                    ,real(wtx))
                  endif
               endif
*     **************
               kweq2=q24-q23
               if(q2.ge.q23 .and.q2.le.q24)then
                  if(xellog.ge.q23x1 .and.xellog.le.q23x3)then
                     call Hfill(144004,real(xellog),0.
     &                    ,real(wtx/kweq2))
                  endif
*     1th bin 
                  if(xellog.ge.q23x1.and. xellog.lt.q23x2)then
                     call Hfill(144014,real(q2),0.
     &                    ,real(wtx))
                     call Hfill(144114,real(xellog),0.
     &                    ,real(wtx))
                     call Hfill(144214,real(y),0.
     &                    ,real(wtx))
                  endif
*     2th bin 
                  if(xellog.ge.q23x2.and. xellog.lt.q23x3)then
                     call Hfill(144024,real(q2),0.
     &                    ,real(wtx))
                     call Hfill(144124,real(xellog),0.
     &                    ,real(wtx))
                     call Hfill(144224,real(y),0.
     &                    ,real(wtx))
                  endif
               endif
*     **************
               kweq2=q25-q24
               if(q2.ge.q24 .and.q2.le.q25)then
                  if(xellog.ge.q24x1 .and.xellog.le.q24x3)then
                     call Hfill(144005,real(xellog),0.
     &                    ,real(wtx/kweq2))
                  endif
*     1th bin 
                  if(xellog.ge.q24x1.and. xellog.lt.q24x2)then
                     call Hfill(144015,real(q2),0.
     &                    ,real(wtx))
                     call Hfill(144115,real(xellog),0.
     &                    ,real(wtx))
                     call Hfill(144215,real(y),0.
     &                    ,real(wtx))
                  endif
*     2th bin 
                  if(xellog.ge.q24x2.and. xellog.lt.q24x3)then
                     call Hfill(144025,real(q2),0.
     &                    ,real(wtx))
                     call Hfill(144125,real(xellog),0.
     &                    ,real(wtx))
                     call Hfill(144225,real(y),0.
     &                    ,real(wtx))
                  endif
               endif
*     **************
               kweq2=q26-q25
               if(q2.ge.q25 .and.q2.le.q26)then
                  if(xellog.ge.q25x1 .and.xellog.le.q25x2)then
                     call Hfill(144006,real(xellog),0.
     &                    ,real(wtx/kweq2))
                  endif
*     1th bin 
                  if(xellog.ge.q25x1.and. xellog.lt.q25x2)then
                     call Hfill(144016,real(q2),0.
     &                    ,real(wtx))
                     call Hfill(144116,real(xellog),0.
     &                    ,real(wtx))
                     call Hfill(144216,real(y),0.
     &                    ,real(wtx))
                  endif
               endif
*     **************



               call Hfill(110,real(pt1)  ,0.,real(tmp))
               call Hfill(111,real(pt2)  ,0.,real(tmp))
               call Hfill(112,real(eta1) ,0.,real(tmp))
               call Hfill(113,real(eta2) ,0.,real(tmp))
*     
               call Hfill(2002,real(log10(q2)),0.,real(tmp))
               call Hfill(2003,real(y),0.,real(tmp))
               call Hfill(2004,real(log10(xbj)),0.,real(tmp))
*     
               call Hfill(2010,real(hzet(ib)),0.,real(tmp))
               call Hfill(2011,real(hzeta(ib)),0.,real(tmp))
*     
               call Hfill(2020,real(jetsellab(1,3)),0.,real(tmp))
               call Hfill(2021,real(jetsellab(1,1)),0.,real(tmp))
*     
               call Hfill(2040,real(jetsellab(2,3)),0.,real(tmp))
               call Hfill(2041,real(jetsellab(2,1)),0.,real(tmp))
*     total cross
* *****************************************************
                kweq2=q21-q20
                xellog=log10(xbj)
                if(q2.ge.q20 .and.q2.le.q21)then
                   if(xellog.ge.q20x1 .and.xellog.le.q20x2)then
                      call Hfill(90000,real(xellog),0.
     &                     ,real(wtx/kweq2))
                      call Hfill(90010,real(xellog),0.
     &                     ,real(wtx))
                   endif
                endif
* ********************
                kweq2=q22-q21
                xellog=log10(xbj)
                if(q2.ge.q21 .and.q2.le.q22)then
                   if(xellog.ge.q21x1 .and.xellog.le.q21x4)then
                      call Hfill(90001,real(xellog),0.
     &                     ,real(wtx/kweq2))
                      call Hfill(90011,real(xellog),0.
     &                     ,real(wtx))
                   endif
                endif
* ********************
                kweq2=q23-q22
                if(q2.ge.q22 .and.q2.le.q23)then
                   if(xellog.ge.q22x1 .and.xellog.le.q22x3)then
                      call Hfill(90002,real(xellog),0.
     &                     ,real(wtx/kweq2))
                      call Hfill(90012,real(xellog),0.
     &                     ,real(wtx))
                   endif
                endif
                if(q2.ge.q22 .and.q2.le.q23)then
                   if(xellog.ge.q22x11 .and.xellog.le.q22x41)then
                      call Hfill(90003,real(xellog),0.
     &                     ,real(wtx/kweq2))
                      call Hfill(90013,real(xellog),0.
     &                     ,real(wtx))
                   endif
                endif
* ********************
                kweq2=q24-q23
                if(q2.ge.q23 .and.q2.le.q24)then
                   if(xellog.ge.q23x1 .and.xellog.le.q23x3)then
                      call Hfill(90004,real(xellog),0.
     &                     ,real(wtx/kweq2))
                      call Hfill(90014,real(xellog),0.
     &                     ,real(wtx))
                   endif
                endif
* ********************
                kweq2=q25-q24
                if(q2.ge.q24 .and.q2.le.q25)then
                   if(xellog.ge.q24x1 .and.xellog.le.q24x3)then
                      call Hfill(90005,real(xellog),0.
     &                     ,real(wtx/kweq2))
                      call Hfill(90015,real(xellog),0.
     &                     ,real(wtx))
                   endif
                endif
* ********************
                kweq2=q26-q25
                if(q2.ge.q25 .and.q2.le.q26)then
                   if(xellog.ge.q25x1 .and.xellog.le.q25x2)then
                      call Hfill(90006,real(xellog),0.
     &                     ,real(wtx/kweq2))
                      call Hfill(90016,real(xellog),0.
     &                     ,real(wtx))
                   endif
                endif
* *****************************************************

               sigtoth1=sigtoth1+tmp
               if (nsel.ge.1) sigjeth1=sigjeth1+tmp
               if (hzet(ib).gt.5..and.etab.lt.2.5
     &              .and.etab.gt.-2.) then
                  sigbh1=sigbh1+tmp
               endif 
               
*     
               if (ptm1.gt.0 .and.muon1) then
                  call Hfill(2030,real(ptm1),0.,real(tmp))
                  call Hfill(2031,real(th1),0.,real(tmp))
               endif
C     if (ptm2.gt.0 .and.muon2) then
C     call Hfill(2030,real(ptm2),0.,real(tmp))
C     call Hfill(2031,real(th2),0.,real(tmp))
C     endif
            endif
*
*     zmiana !!!!!

*            if(th1*rd.gt.180.) write(6,*)'ERROR ThetaOutOfRange1',th1*rd
*            if(th2*rd.gt.180.) write(6,*)'ERROR ThetaOutOfRange2',th1*rd
            if ((ptm1.gt.1.5) .and.
     &           etam1.gt.-1.6 .and.th1*rd.lt.180.)then
*     
               imuacc1=imuacc1+wtx*hfrac1
               kmuon=1
               kmuon1=100.
            endif
            if ((ptm2.gt.1.5) .and.
     &           etam2.gt.-1.6 .and.th2*rd.lt.180.
     &           .and.muon2)then
               kmuon2=100.
            endif
            if ((ptm2.gt.1.5) .and.
     &           etam2.gt.-1.6 .and.th2*rd.lt.180.
     &           .and.kmuon.eq.1. 
     &           .and.muon2)then
*     
               imuacc2=imuacc2+wtx*hfrac1
            endif
*
            if ((ptm2.gt.1.5) .and.
     &           etam2.gt.-1.6 .and.th2*rd.lt.180.
     &           .and.kmuon.lt.1.and. muon2)then
*     
               kmuon=2
            endif
            if(kmuon.gt.0.)then
* we have a muon
* 1th only 1th
               inthecon=-999.
               if(kmuon1.gt.1..and. kmuon2.lt.1.)then
                  if(drmin1.lt.0.7)then
                     inthecon=1.
                     kjetid=kjetid1
                  endif
               endif
*     2th only 2th
               if(kmuon2.gt.1..and. kmuon1.lt.1.)then
                  if(drmin2.lt.0.7)then
                     inthecon=2
                     kjetid=kjetid2
                     etam1=etam2
                     th1=th2
                     ph1=ph2
                     ptm1=ptm2
                     pmum1=pmum2
                  endif
               endif
* 3rd 1th and 2th
               if(kmuon2.gt.1..and. kmuon1.gt.1.)then
                  if(drmin2.lt.0.7.and. drmin1.lt.0.7)then
                     if(ptm1.ge.ptm2)then
                        inthecon=1.
                        kjetid=kjetid1
                     else
                        inthecon=2
                        kjetid=kjetid2
                        etam1=etam2
                        th1=th2
                        ph1=ph2
                        ptm1=ptm2
                        pmum1=pmum2 
                     endif
                  else
                     if(drmin1.lt.0.7)then
                        inthecon=1.
                        kjetid=kjetid1
                     endif
                     if(drmin2.lt.0.7)then
                        inthecon=2
                        kjetid=kjetid2
                        etam1=etam2
                        th1=th2
                        ph1=ph2
                        ptm1=ptm2
                     endif
                  endif
               endif 
* *************************************************************
               if(plot)then
                  sigtotmh1=sigtotmh1+wtx*hfrac1
                  if (nsel.ge.1) then
                     sigjetmh1=sigjetmh1+wtx*hfrac1
                     if(inthecon.ge.1.)then
                        sigjetmcon=sigjetmcon+wtx*hfrac1
                     endif
                  endif
               endif
               if (plot) then
***************************************************************
*PLOTS in BENbin
                  if(nsel.ge.1..and. inthecon.ge.1.)then
                     call Hfill(40001,real(etam1),0.,real(wtx*hfrac1))
                     call Hfill(40101,real(etam1),0.,real(wtx*hfrac1))
                     call Hfill(40002,real(jetsellab(kjetid,1)),0.
     &                    ,real(wtx*hfrac1))
                     call Hfill(40003,real(ptm1),0.,real(wtx*hfrac1))
                     call Hfill(40103,real(ptm1),0.,real(wtx*hfrac1))
                     call Hfill(40004,real(sqrt(jetsellab(kjetid,5)**2
     &                    +jetsellab(kjetid,6)**2)),0.,real(wtx*hfrac1))
                     call Hfill(40005,real(jetsellab(kjetid,3)),0.
     &                    ,real(wtx*hfrac1))
                     call Hfill(50001,real(etam1),0.,real(wtx*hfrac1))
                     call Hfill(50002,real(jetsellab(kjetid,1)),0.
     &                    ,real(wtx*hfrac1))
                     call Hfill(50003,real(ptm1),0.,real(wtx*hfrac1))
                     call Hfill(50004,real(sqrt(jetsellab(kjetid,5)**2
     &                    +jetsellab(kjetid,6)**2)),0.,real(wtx*hfrac1))
                     call Hfill(50005,real(jetsellab(kjetid,3)),0.
     &                    ,real(wtx*hfrac1))
                     xellog=log10(xbj)
* ********************************************
* special cross
               call Hfill(60111,real(xbj),0.
     &              ,real(wtx/0.00000126))
               call Hfill(60112,real(xbj),0.
     &              ,real(wtx/0.000004))
               call Hfill(60113,real(xbj),0.
     &              ,real(wtx/0.000004))
               call Hfill(60114,real(xbj),0.
     &              ,real(wtx/0.00001588))
               call Hfill(60115,real(xbj),0.
     &              ,real(wtx/0.00001002))
               call Hfill(60116,real(xbj),0.
     &              ,real(wtx/0.0000399))
               call Hfill(60117,real(xbj),0.
     &              ,real(wtx/0.0000399))
               call Hfill(60118,real(xbj),0.
     &              ,real(wtx/0.00010024))
               call Hfill(60119,real(xbj),0.
     &              ,real(wtx/0.0000399))
               call Hfill(60120,real(xbj),0.
     &              ,real(wtx/0.0002))
               call Hfill(60121,real(xbj),0.
     &              ,real(wtx/0.0002))
* ********************************************
                     kweq2=q21-q20
                     if(q2.ge.q20 .and.q2.le.q21)then
                        if(xellog.ge.q20x1 .and.xellog.le.q20x2)then
                           call Hfill(140000,real(xellog),0.
     &                          ,real(wtx*hfrac1/kweq2))
                           call Hfill(150000,real(xellog),0.
     &                          ,real(wtx*hfrac1))
                        endif
* 1th bin 
                        if(xellog.ge.q20x1.and. xellog.lt.q20x2)then
                           call Hfill(160010,real(q2),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(170010,real(xellog),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(180010,real(y),0.
     &                          ,real(wtx*hfrac1))
                        endif
                     endif
* ********************************************
                     kweq2=q22-q21
                     if(q2.ge.q21 .and.q2.le.q22)then
                        if(xellog.ge.q21x1 .and.xellog.le.q21x4)then
                           call Hfill(140001,real(xellog),0.
     &                          ,real(wtx*hfrac1/kweq2))
                           call Hfill(150001,real(xellog),0.
     &                          ,real(wtx*hfrac1))
                        endif
* 1th bin 
                        if(xellog.ge.q21x1.and. xellog.lt.q21x2)then
                           call Hfill(160011,real(q2),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(170011,real(xellog),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(180011,real(y),0.
     &                          ,real(wtx*hfrac1))
                        endif
* 2th bin 
                        if(xellog.ge.q21x2.and. xellog.lt.q21x3)then
                           call Hfill(160021,real(q2),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(170021,real(xellog),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(180021,real(y),0.
     &                          ,real(wtx*hfrac1))
                        endif
* 3th bin 
                        if(xellog.ge.q21x3.and. xellog.le.q21x4)then
                           call Hfill(160031,real(q2),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(170031,real(xellog),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(180031,real(y),0.
     &                          ,real(wtx*hfrac1))
                        endif
                     endif
* ********************************************
                     kweq2=q23-q22
                     if(q2.ge.q22 .and.q2.le.q23)then
                        if(xellog.ge.q22x1 .and.xellog.le.q22x3)then
                           call Hfill(140002,real(xellog),0.
     &                          ,real(wtx*hfrac1/kweq2))
                           call Hfill(150002,real(xellog),0.
     &                          ,real(wtx*hfrac1)) 
                       endif
* 1th bin 
                        if(xellog.ge.q22x1.and. xellog.lt.q22x2)then
                           call Hfill(160012,real(q2),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(170012,real(xellog),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(180012,real(y),0.
     &                          ,real(wtx*hfrac1))
                        endif
* 2th bin 
                        if(xellog.ge.q22x2.and. xellog.lt.q22x3)then
                           call Hfill(160022,real(q2),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(170022,real(xellog),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(180022,real(y),0.
     &                          ,real(wtx*hfrac1))
                        endif
                     endif
                     if(q2.ge.q22 .and.q2.le.q23)then
                        if(xellog.ge.q22x11 .and.xellog.le.q22x41)then
                           call Hfill(140003,real(xellog),0.
     &                      ,real(wtx*hfrac1/kweq2))
                           call Hfill(150003,real(xellog),0.
     &                          ,real(wtx*hfrac1))
                        endif
*     1th bin 
                        if(xellog.ge.q22x11.and. xellog.lt.q22x21)then
                           call Hfill(160013,real(q2),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(170013,real(xellog),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(180013,real(y),0.
     &                          ,real(wtx*hfrac1))
                        endif
* 2th bin 
                        if(xellog.ge.q22x21.and. xellog.lt.q22x31)then
                           call Hfill(160023,real(q2),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(170023,real(xellog),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(180023,real(y),0.
     &                          ,real(wtx*hfrac1))
                        endif
* 3th bin 
                        if(xellog.ge.q22x31.and. xellog.le.q22x41)then
                           call Hfill(160033,real(q2),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(170033,real(xellog),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(180033,real(y),0.
     &                          ,real(wtx*hfrac1))
                        endif
                     endif
* ********************************************
                     kweq2=q24-q23
                     if(q2.ge.q23 .and.q2.le.q24)then
                        if(xellog.ge.q23x1 .and.xellog.le.q23x3)then
                           call Hfill(140004,real(xellog),0.
     &                          ,real(wtx*hfrac1/kweq2))
                           call Hfill(150004,real(xellog),0.
     &                      ,real(wtx*hfrac1))
                        endif
* 1th bin 
                        if(xellog.ge.q23x1.and. xellog.lt.q23x2)then
                           call Hfill(160014,real(q2),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(170014,real(xellog),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(180014,real(y),0.
     &                          ,real(wtx*hfrac1))
                        endif
* 2th bin 
                        if(xellog.ge.q23x2.and. xellog.lt.q23x3)then
                           call Hfill(160024,real(q2),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(170024,real(xellog),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(180024,real(y),0.
     &                          ,real(wtx*hfrac1))
                        endif
                     endif
* ********************************************
                     kweq2=q25-q24
                     if(q2.ge.q24 .and.q2.le.q25)then
                        if(xellog.ge.q24x1 .and.xellog.le.q24x3)then
                           call Hfill(140005,real(xellog),0.
     &                          ,real(wtx*hfrac1/kweq2))
                           call Hfill(150005,real(xellog),0.
     &                      ,real(wtx*hfrac1))
                        endif
* 1th bin 
                        if(xellog.ge.q24x1.and. xellog.lt.q24x2)then
                           call Hfill(160015,real(q2),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(170015,real(xellog),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(180015,real(y),0.
     &                          ,real(wtx*hfrac1))
                        endif
* 2th bin 
                        if(xellog.ge.q24x2.and. xellog.lt.q24x3)then
                           call Hfill(160025,real(q2),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(170025,real(xellog),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(180025,real(y),0.
     &                          ,real(wtx*hfrac1))
                        endif
                     endif
* ********************************************
                     kweq2=q26-q25
                     if(q2.ge.q25 .and.q2.le.q26)then
                        if(xellog.ge.q25x1 .and.xellog.le.q25x2)then
                           call Hfill(140006,real(xellog),0.
     &                          ,real(wtx*hfrac1/kweq2))
                           call Hfill(150006,real(xellog),0.
     &                      ,real(wtx*hfrac1))
                        endif
* 1th bin 
                        if(xellog.ge.q25x1.and. xellog.lt.q25x2)then
                           call Hfill(160016,real(q2),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(170016,real(xellog),0.
     &                          ,real(wtx*hfrac1))
                           call Hfill(180016,real(y),0.
     &                          ,real(wtx*hfrac1))
                        endif
                     endif
* ********************************************
                     if(q2.ge.q2_0 .and.q2.le.q2_5)then
                        call Hfill(40010,real(q2),0.,real(wtx*hfrac1))
                        call Hfill(50010,real(q2),0.,real(wtx*hfrac1))
                        call Hfill(40011,real(log10(q2)),0.
     &                       ,real(wtx*hfrac1))
                        call Hfill(50011,real(log10(q2)),0.
     &                       ,real(wtx*hfrac1))
                     endif
* HIST after cuts!!!!!!!
                     call Hfill(11001,real(jetsellab(kjetid,1)),0.
     &                    ,real(wtx*hfrac1))
                     call Hfill(11002,real(jetsellab(kjetid,2)),0.
     &                    ,real(wtx*hfrac1))
                     call Hfill(11003,real(jetsellab(kjetid,3)),0.
     &                    ,real(wtx*hfrac1))
                     call Hfill(11004,real(jetsellab(kjetid,4)),0.
     &                    ,real(wtx*hfrac1))
                     call Hfill(11005,real(jetsellab(kjetid,5)),0.
     &                    ,real(wtx*hfrac1))
                     call Hfill(11006,real(jetsellab(kjetid,6)),0.
     &                    ,real(wtx*hfrac1))
                     call Hfill(11007,real(jetsellab(kjetid,7)),0.
     &                    ,real(wtx*hfrac1))
                     call Hfill(11008,real(jetsellab(kjetid,8)),0.
     &                    ,real(wtx*hfrac1))
                     call Hfill(11009,real(ph1),0.
     &                    ,real(wtx*hfrac1))
                     call Hfill(11010,real(th1),0.
     &                    ,real(wtx*hfrac1))
                     call Hfill(11011,real(eta1),0.
     &                    ,real(wtx*hfrac1))
                     if(kmuon.eq.1)then
                        call Hfill(11012,real(PM1(1)),0.
     &                       ,real(wtx*hfrac1))
                        call Hfill(11013,real(PM1(2)),0.
     &                       ,real(wtx*hfrac1))
                        call Hfill(11014,real(PM1(3)),0.
     &                       ,real(wtx*hfrac1))
                     endif
                     if(kmuon.eq.2)then
                        call Hfill(11012,real(PM2(1)),0.
     &                       ,real(wtx*hfrac1))
                        call Hfill(11013,real(PM2(2)),0.
     &                       ,real(wtx*hfrac1))
                        call Hfill(11014,real(PM2(3)),0.
     &                       ,real(wtx*hfrac1))
                     endif
                     call Hfill(11015,real(ptm1),0.
     &                    ,real(wtx*hfrac1))
                     call Hfill(11016,real(pmum1),0.
     &                    ,real(wtx*hfrac1))
                        
                     call Hfill(2,1.5,0.,real(wtx*hfrac1))  
                     call Hfill(100,real(ptm1)    ,0.,real(wtx*hfrac1))
                     call Hfill(101,real(ptm2)    ,0.,real(wtx*hfrac1))
                     call Hfill(102,real(etam1)   ,0.,real(wtx*hfrac1))
                     call Hfill(103,real(etam2)   ,0.,real(wtx*hfrac1))
                   call Hfill(104,real(log10(q2)),0.,real(wtx*hfrac1))
                     call Hfill(105,real(y)       ,0.,real(wtx*hfrac1))
                   call Hfill(106,real(log10(xbj)),0.,real(wtx*hfrac1))
*     
                call Hfill(2202,real(log10(q2)),0.,real(wtx*hfrac1))
                     call Hfill(2203,real(y)       ,0.,real(wtx*hfrac1))
                     call Hfill(2204,real(log10(xbj)),0.
     &                    ,real(wtx*hfrac1))
*     
                 call Hfill(2210,real(hzet(ib)),0., real(wtx*hfrac1))
                call Hfill(2211,real(hzeta(ib)),0.,real(wtx*hfrac1))
*
                     call Hfill(2220,real(jetsellab(kjetid,3)),0.
     &                    ,real(wtx*hfrac1))
                     call Hfill(2221,real(jetsellab(kjetid,1)),0.
     &                    ,real(wtx*hfrac1))
                     call Hfill(2240,real(jetsellab(kjetid,3)),0.
     &                    ,real(wtx*hfrac1))
                     call Hfill(2241,real(jetsellab(kjetid,1)),0.
     &                    ,real(wtx*hfrac1))
*     
                     call Hfill(2230,real(ptm1)  ,0.,real(wtx*hfrac1))
                     call Hfill(2231,real(th1)   ,0.,real(wtx*hfrac1))
                  endif
               endif
            else
               wtx=0D0 
            endif
C Q2>4 y>0.05
         endif 
*
         wtx=0D0
*     
*     new cross section definition in Breit Frame
*     

         if (lp) write(6,*) '**hzb:  Lab: ' 
         if (lp) call hzlihep(2)
*     save all in lab frame
         
         do i=1,nhep
            do j=1,4
               PLAB(j,i)=PHEP(j,i)
            enddo
         enddo
*     KONIEC H1
*     
*     boost to Breit frame
         call ktbrei(2,plep,phad,psel,nhep,PLAB,PBREIT)
*
         do i=5,nhep
            do j=1,4
               PHEP(j,i)=PBREIT(j,i)
            enddo
            PHEP(5,i)=-PHEP(1,i)**2-PHEP(2,i)**2-PHEP(3,i)**2
     &           +PHEP(4,i)**2
            if(PHEP(5,i).gt.0.) PHEP(5,i)=sqrt(PHEP(5,i))
         enddo
*     
         if (lp) write(6,*) ' Breit: ' 
         if (lp) call hzlihep(2)
*     
         imuonjet1=0
         imuonjet2=0
         imuonsel1=0
         imuonsel2=0
         do i=1,NMXHEP
            IJETNO(i)=0.
         enddo
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
C     ipjetsel(j)=nsel
         enddo
*
         CALL hzjtfind(3,1.d0,NJET,Jets)
*     
         if (gen.ne.'HVQ') then
            if (imuon.ne.-1) then
C     write(6,*) ' muon is on ',imuon  
               do i=1,NHEP
C     write(6,*) i,' belongs to jet: ',IJETNO(i)
                  if (imuon.eq.i) then
                     imuonjet1=IJETNO(i)
                  endif
                  if (imuon2.eq.i) then
                     imuonjet2=IJETNO(i)
                  endif
               enddo
            endif
            if (lp) write(6,*)'imuonjet1,imuonjet2=',imuonjet1,imuonjet2
         else
            if (ptm1.gt.0 .and.muon1) then
               imuonjet1=IJETNO(5)
            endif
            if (ptm2.gt.0 .and.muon2) then
               imuonjet2=IJETNO(6)
            endif 
         endif
*
*     transform back from Breit to Lab
*     
         call hzbrtola2(njet,jets,jetslab)
*     
         nsel=0
         do j=1,njet
*     
*     apply jet cut
*     
            pt=sqrt(jets(j,5)**2+jets(j,6)**2)
            if (pt.gt.cpt1
     &           .and. jetslab(j,1).gt.cetal 
     &           .and. jetslab(j,1).lt.cetah) then
               nsel=nsel+1
               ipjet(nsel)=j
               if (j.eq.imuonjet1) imuonsel1=nsel
               if (j.eq.imuonjet2) imuonsel2=nsel
               do i=1,8
                  jetsel(nsel,i)=jets(j,i)
                  jetsellab(nsel,i)=jetslab(j,i)
               enddo
            endif
         enddo
*
         etafwd=-9999.
         ijet=2
         if (njet.lt.2) ijet=1
         do j=1,ijet
            if (etafwd.lt.jetslab(j,1)) then
               etafwd=jetslab(j,1)
            endif
         enddo
*     
         etaselfwd=-9999.
         do j=1,nsel
            if (etaselfwd.lt.jetsellab(j,1)) then
               etaselfwd=jetsellab(j,1)
            endif
         enddo
*     CIECIA breit
         if ((Q2 .gt.2.  .and. q2.lt.10000.).and.
     &        ( y  .gt.YMIN.and.  y.lt.YMAX ) )then
*     
            nev1=nev1+1.
            indirect=.false.
            direct=.false.
            if (gen.ne.'HVQ') then 
               if (imuon.gt.0) then
C     write(6,*) ' id= ', abs(IDHEP(JMOHEP(1,imuon)))
                  if ((abs(IDHEP(JMOHEP(1,imuon))).gt.400
     &                 .and.abs(IDHEP(JMOHEP(1,imuon))).lt.500).or.
     &                 (abs(IDHEP(JMOHEP(1,imuon))).gt.4000
     &                 .and.abs(IDHEP(JMOHEP(1,imuon))).lt.5000)
     &                 ) then
                     indirect=.true.
                     indir=indir+1
                  endif
*     
                  if ((abs(IDHEP(JMOHEP(1,imuon))).gt.500
     &                 .and.abs(IDHEP(JMOHEP(1,imuon))).lt.600).or.
     &                 (abs(IDHEP(JMOHEP(1,imuon))).gt.5000
     &               .and.abs(IDHEP(JMOHEP(1,imuon))).lt.6000)
     &                 ) then
                     direct=.true.
                     idir=idir+1
                  endif
                  if (abs(IDHEP(JMOHEP(1,imuon))).eq.15) then
                     itau=itau+1
                     imo1=JMOHEP(1,imuon)
                     if ((abs(IDHEP(JMOHEP(1,imo1))).gt.500
     &                    .and.abs(IDHEP(JMOHEP(1,imo1))).lt.600).or.
     &                    (abs(IDHEP(JMOHEP(1,imo1))).gt.5000
     &                    .and. abs(IDHEP(JMOHEP(1,imo1))).lt.6000)
     &                    ) then
                        direct=.true.
                     else if ((abs(IDHEP(JMOHEP(1,imo1))).gt.400
     &                       .and.abs(IDHEP(JMOHEP(1,imo1))).lt.500).or.
     &                       (abs(IDHEP(JMOHEP(1,imo1))).gt.4000
     &                       .and.abs(IDHEP(JMOHEP(1,imo1))).lt.5000)
     &                       ) then
                        indirect=.true.
                     endif
                  endif
*
                  if (indirect) then 
C     write(6,*) ' indirect decay ',IDHEP(JMOHEP(1,imuon))
                  elseif (direct) then
C     write(6,*) '   direct decay ',IDHEP(JMOHEP(1,imuon))
                  else
                     ioth=ioth+1
                     if (lp) write(6,*)' th1= ',th1*rd,' ptm1= ',ptm1
                     if (lp) write(6,*)'imuon=',imuon,'imuon2= ',imuon2
                     nmo=0
                     if (lp) write(6,*) ' Mothers: '
                     imo1=JMOHEP(1,imuon)
                     if (lp) write(6,*) imo1,' id= ',IDHEP(imo1)
                     imo2=imo1
 1788                continue
                     nmo=nmo+1
                     if (nmo.gt.10) goto 1789
                     imo2=JMOHEP(1,imo2)
                     if (lp) write(6,*) imo2,' id= '
     &                    ,IDHEP(JMOHEP(1,imo2)) 
                     if (abs(IDHEP(imo2)).eq.5) goto 1789
                     goto 1788
 1789                continue 
C     call hzlihep(2)
                  endif
               endif
            endif
*
            
            if (lp) then 
C     write(6,*) ' Jets in Breit '
C     call hzlijet(njet,jets)
               write(6,*) ' Jets in Lab '
               call hzlijet(njet,jetslab)
            endif
*     
            if (plot) then
               sigbrtot=sigbrtot+tmp
               if ((hzet(ib).gt.cpt1.and.etab.lt.cetah
     &              .and.etab.gt.cetal).or.
     &              (hzet(ibar).gt.cpt1.and.etabar.lt.cetah
     &              .and.etabar.gt.cetal
     &              )) then
                  sigb=sigb+tmp
               endif 
*     
               call Hfill(1,0.5,0.,real(tmp))
*     
               call Hfill(1002,real(q2),0.,real(tmp))
               call Hfill(1003,real(y),0.,real(tmp))
               call Hfill(1004,real(log10(xbj)),0.,real(tmp))
               call Hfill(1005,real(log10(xbj)),0.,real(tmp))
               call Hfill(1007,real(log10(xbj)),0.,real(tmp))
*
               call Hfill(1010,real(etb)         ,0.,real(tmp))
               call Hfill(1011,real(etab)        ,0.,real(tmp))
               call Hfill(1012,real(hzet(ib))    ,0.,real(tmp))
               call Hfill(1013,real(hzeta(ib))   ,0.,real(tmp))
*
               call Hfill(1020,real(jetslab(1,3)),0.,real(tmp))
               call Hfill(1021,real(jetslab(1,1)),0.,real(tmp))
               call Hfill(1022,real(jets(1,3))   ,0.,real(tmp))
               call Hfill(1023,real(jets(1,1))   ,0.,real(tmp))
               call Hfill(1024,real(jetslab(1,1)),0.,real(tmp))
               call Hfill(1025,real(jets(1,1))   ,0.,real(tmp))
               call Hfill(1027,etafwd            ,0.,real(tmp))
*     
               call Hfill(1040,real(jetslab(2,3)),0.,real(tmp))
               call Hfill(1041,real(jetslab(2,1)),0.,real(tmp))
               call Hfill(1050,real(jets(2,3))   ,0.,real(tmp))
               call Hfill(1051,real(jets(2,1))   ,0.,real(tmp))
*
               if (gen.ne.'HVQ') then
                  if (direct) then        
                     call Hfill(7010,real(etb)         ,0.,real(tmp))
                     call Hfill(7011,real(etab)        ,0.,real(tmp))
                     call Hfill(7012,real(hzet(ib))    ,0.,real(tmp))
                     call Hfill(7013,real(hzeta(ib))   ,0.,real(tmp))
*     
                     call Hfill(7020,real(jetslab(1,3)),0.,real(tmp))
                     call Hfill(7021,real(jetslab(1,1)),0.,real(tmp))
                     call Hfill(7022,real(jets(1,3))   ,0.,real(tmp))
                     call Hfill(7023,real(jets(1,1))   ,0.,real(tmp))
*     
                     call Hfill(7040,real(jetslab(2,3)),0.,real(tmp))
                     call Hfill(7041,real(jetslab(2,1)),0.,real(tmp))
                     call Hfill(7050,real(jets(2,3))   ,0.,real(tmp))
                     call Hfill(7051,real(jets(2,1))   ,0.,real(tmp))
                  elseif (indirect) then
                     call Hfill(6010,real(etb)         ,0.,real(tmp))
                     call Hfill(6011,real(etab)        ,0.,real(tmp))
                     call Hfill(6012,real(hzet(ib))    ,0.,real(tmp))
                     call Hfill(6013,real(hzeta(ib))   ,0.,real(tmp))
*     
                     call Hfill(6020,real(jetslab(1,3)),0.,real(tmp))
                     call Hfill(6021,real(jetslab(1,1)),0.,real(tmp))
                     call Hfill(6022,real(jets(1,3))   ,0.,real(tmp))
                     call Hfill(6023,real(jets(1,1))   ,0.,real(tmp))
*
                     call Hfill(6040,real(jetslab(2,3)),0.,real(tmp))
                     call Hfill(6041,real(jetslab(2,1)),0.,real(tmp))
                     call Hfill(6050,real(jets(2,3))   ,0.,real(tmp))
                     call Hfill(6051,real(jets(2,1))   ,0.,real(tmp))
                  endif
               endif
*
C     call Hfill(10001,real(hzeta(ib)),real(jetslab(1,1)),real(tmp))
C     call Hfill(10002,real(hzet (ib)),real(jetslab(1,3)),real(tmp))
*     
            endif
*
            if (lp) write(6,*) ' ptm1= ',ptm1,' etam1= ',etam1
            muon=.false.
*     
            muon1acc=.false.
            muon2acc=.false.
*     
C !!!!!!            if (plot.and.muon1) imuacc1=imuacc1+tmp
C     if ((pmum1.gt.2.) .and.
C     &     (th1*rd.gt.30..and.th1*rd.lt.160.)) then
*
            if (((pmum1.gt.2.0) .and.
     &           (etam1.gt.-1.6.and.etam1.lt.-0.9)
     &           ).or.
     &           ((ptm1.gt.2.0).and.
     &           (etam1.gt.-0.9.and.etam1.lt.1.3)
     &           )) then
*     
               if (muon1) then 
                  muon=.true. 
                  muon1acc=.true.
                  if (plot) imu1=imu1+tmp
               endif
            endif
*
c !!!!!            if (plot.and.muon2) imuacc2=imuacc2+tmp
C     if ((pmum2.gt.2.) .and.
C     &      (th2*rd.gt.30..and.th2*rd.lt.160.)) then
*     
            if (((pmum2.gt.2.) .and.
     &           (etam2.gt.-1.6.and.etam2.lt.-0.9)
     &           ).or.
     &           ((ptm2.gt.2.).and.
     &           (etam2.gt.-0.9.and.etam2.lt.1.3)
     &           )) then
*     
*     Do it only if the b had a chance
*     to decay to a muon (see above) 
               if (muon2) then 
                  muon=.true.
                  muon2acc=.true.
                  if (plot) imu2=imu2+tmp
               endif 
            endif
*
*
*     this is the ZEUS scenario: >>
*     
*     prob that B-meson->mu: hfrac
*     prob. to have >=1 muon: 2*hfrac-hfrac**2
*     prob. to have  =2 muon: hfrac**2
*     prob to have Nmu=2 under condition to have Mnu>=1: hfrac/(2-hfrac)
*     multiply cross-section (at least 1 muon) with 2*hfrac-hfrac**2
*     
            wtxtmp=tmp*(2D0*hfrac-hfrac**2D0)
            if (muon) wtxm=tmp*(2D0*hfrac-hfrac**2D0)
*     
C     if (muon) wtxm= tmp*(1. - (1.-hfrac)*(1.-hfrac) ) 
*     
            if (plot) then
               if (ptm1.gt.0.and.muon1) then
                  call Hfill(1030,real(ptm1)  ,0.,real(wtxtmp))
                  call Hfill(1034,real(log10(ptm1)) ,0.,real(wtxtmp))
                  call Hfill(1031,real(th1*rd),0.,real(wtxtmp))
                  call Hfill(1032,real(etam1) ,0.,real(wtxtmp))
                  call Hfill(1033,real(pmum1) ,0.,real(wtxtmp))
               endif
               if (ptm2.gt.0 .and.muon2) then
                  call Hfill(1030,real(ptm2)  ,0.,real(wtxtmp))
                  call Hfill(1034,real(log10(ptm2)) ,0.,real(wtxtmp))
                  call Hfill(1031,real(th2*rd),0.,real(wtxtmp))
                  call Hfill(1032,real(etam2) ,0.,real(wtxtmp))
                  call Hfill(1033,real(pmum2) ,0.,real(wtxtmp))
               endif
               if (imuonjet1.gt.0) then
                  call Hfill(1026,real(jetslab(imuonjet1,1)),0.
     &                 ,real(wtxtmp))
               endif
               if (imuonjet2.gt.0) then
                  call Hfill(1026,real(jetslab(imuonjet2,1)),0.
     &                 ,real(wtxtmp))
               endif
*     
               if (gen.ne.'HVQ') then
                  if (direct) then
                     if (ptm1.gt.0 .and.muon1) then
                        call Hfill(7030,real(ptm1)  ,0.,real(wtxtmp))
                        call Hfill(7031,real(th1*rd),0.,real(wtxtmp))
                        call Hfill(7032,real(etam1) ,0.,real(wtxtmp))
                        call Hfill(7033,real(pmum1) ,0.,real(wtxtmp))
                     endif
                     if (ptm2.gt.0 .and.muon2) then
                        call Hfill(7030,real(ptm2)  ,0.,real(wtxtmp))
                        call Hfill(7031,real(th2*rd),0.,real(wtxtmp))
                        call Hfill(7032,real(etam2) ,0.,real(wtxtmp))
                        call Hfill(7033,real(pmum2) ,0.,real(wtxtmp))
                     endif
                  elseif (indirect) then
                     if (ptm1.gt.0 .and.muon1) then
                        call Hfill(6030,real(ptm1)  ,0.,real(wtxtmp))
                        call Hfill(6031,real(th1*rd),0.,real(wtxtmp))
                        call Hfill(6032,real(etam1) ,0.,real(wtxtmp))
                        call Hfill(6033,real(pmum1) ,0.,real(wtxtmp))
                     endif
                     if (ptm2.gt.0 .and.muon2) then
                        call Hfill(6030,real(ptm2)  ,0.,real(wtxtmp))
                        call Hfill(6031,real(th2*rd),0.,real(wtxtmp))
                        call Hfill(6032,real(etam2) ,0.,real(wtxtmp))
                        call Hfill(6033,real(pmum2) ,0.,real(wtxtmp))
                     endif
                  endif
               endif        
            endif
*
            if (muon) then 
*
               if (plot) then
                  sigbreitnj=sigbreitnj+wtxm
                  call Hfill(1,2.5,0.,real(wtxm))
*     
                  call Hfill(1402,real(q2),0.,real(wtxm))
                  call Hfill(1403,real(y),0.,real(wtxm))
                  call Hfill(1404,real(log10(xbj)),0.,real(wtxm))
*     
                  call Hfill(1410,real(etb)         ,0.,real(wtxm))
                  call Hfill(1411,real(etab)        ,0.,real(wtxm))
                  call Hfill(1412,real(hzet(ib))    ,0.,real(wtxm))
                  call Hfill(1413,real(hzeta(ib))   ,0.,real(wtxm))
                  call Hfill(1420,real(jetslab(1,3)),0.,real(wtxm))
                  call Hfill(1421,real(jetslab(1,1)),0.,real(wtxm))
                  call Hfill(1422,real(jets(1,3))   ,0.,real(wtxm))
                  call Hfill(1423,real(jets(1,1))   ,0.,real(wtxm))
                  call Hfill(1424,real(jetslab(1,1)),0.,real(wtxm))
                  call Hfill(1425,real(jets(1,1))   ,0.,real(wtxm))
                  call Hfill(1427,etafwd            ,0.,real(wtxm))
                  if (imuonjet1.gt.0 .and. muon1acc) then
                     call Hfill(1426,real(jetslab(imuonjet1,1)),0.
     &               ,real(wtxm))
                  endif
                  if (imuonjet2.gt.0 .and. muon2acc) then
                     call Hfill(1426,real(jetslab(imuonjet2,1)),0.
     &                    ,real(wtxm))
                  endif
*     
                  call Hfill(1440,real(jetslab(2,3)),0.,real(wtxm))
                  call Hfill(1441,real(jetslab(2,1)),0.,real(wtxm))
                  call Hfill(1450,real(jets(2,3))   ,0.,real(wtxm))
                  call Hfill(1451,real(jets(2,1))   ,0.,real(wtxm))
*     
                  if (ptm1.gt.0 .and. muon1 .and.muon1acc) then
                     call Hfill(1430,real(ptm1)  ,0.,real(wtxm))
                     call Hfill(1434,real(log10(ptm1))  ,0.,real(wtxm))
                     call Hfill(1431,real(th1*rd),0.,real(wtxm))
                     call Hfill(1433,real(pmum1),  0.,real(wtxm))
                     call Hfill(1432,real(etam1) ,0.,real(wtxm))
                  endif  
                  if (ptm2.gt.0 .and. muon2 .and.muon2acc) then
                     call Hfill(1430,real(ptm2),  0.,real(wtxm))
                     call Hfill(1434,real(log10(ptm1))  ,0.,real(wtxm))
                     call Hfill(1431,real(th2*rd),0.,real(wtxm))
                     call Hfill(1433,real(pmum2),  0.,real(wtxm))
                     call Hfill(1432,real(etam2), 0.,real(wtxm))
                  endif
               endif
            endif
*
            pt=sqrt(jetsel(1,5)**2+jetsel(1,6)**2)
            if (pt.gt.ptmin) then
*     
               if (plot) then
*     
                  call Hfill(1102,real(q2),0.,real(tmp))
                  call Hfill(1103,real(y),0.,real(tmp))
                  call Hfill(1104,real(log10(xbj)),0.,real(tmp))
*     
                  call Hfill(1110,real(etb)         ,0.,real(tmp))
                  call Hfill(1111,real(etab)        ,0.,real(tmp))
                  call Hfill(1112,real(hzet(ib))    ,0.,real(tmp))
                  call Hfill(1113,real(hzeta(ib))   ,0.,real(tmp))
                  call Hfill(1120,real(jetsellab(1,3)),0.,real(tmp))
                  call Hfill(1121,real(jetsellab(1,1)),0.,real(tmp))
                  call Hfill(1122,real(jetsel(1,3)) ,0.,real(tmp))
                  call Hfill(1123,real(jetsel(1,1)) ,0.,real(tmp))
                  call Hfill(1124,real(jetsellab(1,1)),0.,real(tmp))
                  call Hfill(1125,real(jetsel(1,1))   ,0.,real(tmp))
                  call Hfill(1127,etaselfwd ,0.,real(tmp))
*     
                  call Hfill(1140,real(jetslab(2,3)),0.,real(tmp))
                  call Hfill(1141,real(jetslab(2,1)),0.,real(tmp))
                  call Hfill(1150,real(jets(2,3))   ,0.,real(tmp))
                  call Hfill(1151,real(jets(2,1))   ,0.,real(tmp))
*     
                  if (hzet(ib).gt.hzet(ibar)) then
                     ii=ib
                  else
                     ii=ibar
                  endif
                  call Hfill(1114,real(hzet(ii)) ,0.,real(tmp))
                  call Hfill(1115,real(hzeta(ii)),0.,real(tmp))
*     
                  if (ptm1.gt.0 .and. muon1) then
                     call Hfill(1130,real(ptm1),  0.,real(wtxtmp))
                     call Hfill(1134,real(log10(ptm1)),0.,real(wtxtmp))
                     call Hfill(1131,real(th1*rd),0.,real(wtxtmp))
                     call Hfill(1132,real(etam1), 0.,real(wtxtmp))
                     call Hfill(1133,real(pmum1) ,0.,real(wtxtmp))
                  endif 
                  if (ptm2.gt.0 .and. muon2) then
                     call Hfill(1130,real(ptm2),  0.,real(wtxtmp))
                     call Hfill(1134,real(log10(ptm2)),0.,real(wtxtmp))
                     call Hfill(1131,real(th2*rd),0.,real(wtxtmp))
                     call Hfill(1132,real(etam2), 0.,real(wtxtmp))
                     call Hfill(1133,real(pmum2) ,0.,real(wtxtmp))
                  endif
                  if (imuonsel1.gt.0) then
                     call Hfill(1126,real(jetsellab(imuonsel1,1))
     &                    ,0.,real(wtxtmp))
                  endif
                  if (imuonsel2.gt.0) then
                     call Hfill(1126,real(jetsellab(imuonsel2,1))
     &                ,0.,real(wtxtmp))
                  endif
*     
                  if (gen.ne.'HVQ') then
                     if (direct) then
                        call Hfill(7110,real(etb)         ,0.,real(tmp))
                        call Hfill(7111,real(etab)        ,0.,real(tmp))
                        call Hfill(7112,real(hzet(ib))    ,0.,real(tmp))
                        call Hfill(7113,real(hzeta(ib))   ,0.,real(tmp))
                        call Hfill(7120,real(jetsellab(1,3)),0.
     &                       ,real(tmp))
                        call Hfill(7121,real(jetsellab(1,1)),0.
     &                       ,real(tmp))
                        call Hfill(7122,real(jetsel(1,3)) ,0.,real(tmp))
                        call Hfill(7123,real(jetsel(1,1)) ,0.,real(tmp))
*     
                        call Hfill(7140,real(jetslab(2,3)),0.,real(tmp))
                        call Hfill(7141,real(jetslab(2,1)),0.,real(tmp))
                        call Hfill(7150,real(jets(2,3))   ,0.,real(tmp))
                        call Hfill(7151,real(jets(2,1))   ,0.,real(tmp))
*     
                        if (ptm1.gt.0 .and. muon1) then
                           call Hfill(7130,real(ptm1),  0.,real(wtxm))
                           call Hfill(7131,real(th1*rd),0.,real(wtxm))
                           call Hfill(7132,real(etam1), 0.,real(wtxm))
                           call Hfill(7133,real(pmum1) ,0.,real(wtxm))
                        endif 
                        if (ptm2.gt.0 .and. muon2) then
                           call Hfill(7130,real(ptm2),  0.,real(wtxm))
                           call Hfill(7131,real(th2*rd),0.,real(wtxm))
                           call Hfill(7132,real(etam2), 0.,real(wtxm))
                           call Hfill(7133,real(pmum2) ,0.,real(wtxm))
                        endif
                     elseif (indirect) then
                        call Hfill(6110,real(etb)         ,0.,real(tmp))
                        call Hfill(6111,real(etab)        ,0.,real(tmp))
                        call Hfill(6112,real(hzet(ib))    ,0.,real(tmp))
                        call Hfill(6113,real(hzeta(ib))   ,0.,real(tmp))
                        call Hfill(6120,real(jetsellab(1,3)),0.
     &                       ,real(tmp))
                        call Hfill(6121,real(jetsellab(1,1)),0.
     &                       ,real(tmp))
                        call Hfill(6122,real(jetsel(1,3)) ,0.,real(tmp))
                        call Hfill(6123,real(jetsel(1,1)) ,0.,real(tmp))
*     
                        call Hfill(6140,real(jetslab(2,3)),0.,real(tmp))
                        call Hfill(6141,real(jetslab(2,1)),0.,real(tmp))
                        call Hfill(6150,real(jets(2,3))   ,0.,real(tmp))
                        call Hfill(6151,real(jets(2,1))   ,0.,real(tmp))
*     
                        if (ptm1.gt.0 .and. muon1) then
                           call Hfill(6130,real(ptm1),  0.,real(wtxm))
                           call Hfill(6131,real(th1*rd),0.,real(wtxm))
                           call Hfill(6132,real(etam1), 0.,real(wtxm))
                           call Hfill(6133,real(pmum1) ,0.,real(wtxm))
                        endif 
                        if (ptm2.gt.0 .and. muon2) then
                           call Hfill(6130,real(ptm2),  0.,real(wtxm))
                           call Hfill(6131,real(th2*rd),0.,real(wtxm))
                           call Hfill(6132,real(etam2), 0.,real(wtxm))
                           call Hfill(6133,real(pmum2) ,0.,real(wtxm))
                        endif
                     endif
                  endif
*     
               endif
*
               if (plot) then
                  do j=1,2 
                     if ((j.eq.1.and.
     &                    (hzet(ib).gt.cpt1.and.etab.lt.cetah
     &                    .and.etab.gt.cetal))
     &                    .or.
     &                    (j.eq.2.and.
     &                    (hzet(ibar).gt.cpt1.and.etabar.lt.cetah
     &                    .and.etabar.gt.cetal))
     &                    ) then
*     
                        siginclb= siginclb+tmp
                        call Hfill(3002,real(q2),0.,real(tmp))
                        call Hfill(3003,real(y),0.,real(tmp))
                        call Hfill(3004,real(log10(xbj)),0.,real(tmp))
*     
                        if (j.eq.1) then
                           call Hfill(3010,real(etb)      ,0.,real(tmp))
                           call Hfill(3011,real(etab)     ,0.,real(tmp))
                           call Hfill(3012,real(hzet(ib)) ,0.,real(tmp))
                           call Hfill(3013,real(hzeta(ib)),0.,real(tmp))
                        else
                           call Hfill(3010,real(etbar)    ,0.,real(tmp))
                           call Hfill(3011,real(etabar)   ,0.,real(tmp))
                           call Hfill(3012,real(hzet(ibar)),0.
     &                          ,real(tmp))
                           call Hfill(3013,real(hzeta(ibar)),0.
     &                          ,real(tmp))
                        endif
*     
                        call Hfill(3020,real(jetslab(1,3)),0.,real(tmp))
                        call Hfill(3021,real(jetslab(1,1)),0.,real(tmp))
                        call Hfill(3022,real(jets(1,3))   ,0.,real(tmp))
                        call Hfill(3023,real(jets(1,1))   ,0.,real(tmp))
                        if (ptm1.gt.0.and.muon1) then
                           call Hfill(3030,real(ptm1)  ,0.,real(wtxtmp))
                           call Hfill(3031,real(th1*rd),0.,real(wtxtmp))
                           call Hfill(3032,real(etam1) ,0.,real(wtxtmp))
                           call Hfill(3033,real(pmum1) ,0.,real(wtxtmp))
                        endif
                        if (ptm2.gt.0 .and.muon2) then
                           call Hfill(3030,real(ptm2)  ,0.,real(wtxtmp))
                           call Hfill(3031,real(th2*rd),0.,real(wtxtmp))
                           call Hfill(3032,real(etam2) ,0.,real(wtxtmp))
                           call Hfill(3033,real(pmum2) ,0.,real(wtxtmp))
                        endif
                     endif
                  enddo
*
                  do i=1,nsel
                     pt=sqrt(jetsel(1,5)**2+jetsel(1,6)**2)
                     if (pt.gt.ptmin.and.muon) then
                        sigincljet=sigincljet+tmp
*     
                        call Hfill(3102,real(q2),0.,real(wtxtmp))
                        call Hfill(3103,real(y),0.,real(wtxtmp))
                        call Hfill(3104,real(log10(xbj)),0.
     &                       ,real(wtxtmp))
*     
                        call Hfill(3110,real(etb)    ,0.,real(wtxtmp))
                        call Hfill(3111,real(etab)   ,0.,real(wtxtmp))
                        call Hfill(3112,real(hzet(ib)),0.,real(wtxtmp))
                        call Hfill(3113,real(hzeta(ib)),0.,real(wtxtmp))
*     
                        call Hfill(3120,real(jetsellab(i,3)),0.
     &                       ,real(wtxtmp))
                        call Hfill(3121,real(jetsellab(i,1)),0.
     &                       ,real(wtxtmp))
                        call Hfill(3122,real(jetsel(i,3))   ,0.
     &                       ,real(wtxtmp))
                        call Hfill(3123,real(jetsel(i,1))   ,0.
     &                   ,real(wtxtmp))
                        if (ptm1.gt.0.and.muon1) then
                           call Hfill(3130,real(ptm1)  ,0.,real(wtxtmp))
                           call Hfill(3131,real(th1*rd),0.,real(wtxtmp))
                           call Hfill(3132,real(etam1) ,0.,real(wtxtmp))
                           call Hfill(3133,real(pmum1) ,0.,real(wtxtmp))
                        endif
                        if (ptm2.gt.0 .and.muon2) then
                           call Hfill(3130,real(ptm2)  ,0.,real(wtxtmp))
                           call Hfill(3131,real(th2*rd),0.,real(wtxtmp))
                           call Hfill(3132,real(etam2) ,0.,real(wtxtmp))
                           call Hfill(3133,real(pmum2) ,0.,real(wtxtmp))
                        endif
                     endif
                  enddo
*     
                  do j=1,2 
                     if ((j.eq.1.and.muon1acc).or.
     &                    (j.eq.2.and.muon2acc)
     &                    ) then
                        siginclmu=siginclmu+wtxtmp
*     
                        call Hfill(3202,real(q2),0.,real(wtxtmp))
                        call Hfill(3203,real(y),0.,real(wtxtmp))
                        call Hfill(3204,real(log10(xbj)),0.
     &                   ,real(wtxtmp))
*     
                        call Hfill(3210,real(etb)      ,0.,real(wtxtmp))
                        call Hfill(3211,real(etab)     ,0.,real(wtxtmp))
                        call Hfill(3212,real(hzet(ib)) ,0.,real(wtxtmp))
                        call Hfill(3213,real(hzeta(ib)),0.,real(wtxtmp))
*     
                        if (j.eq.1) i=imuonsel1
                        if (j.eq.2) i=imuonsel2
                        call Hfill(3220,real(jetsellab(i,3)),0.
     &                       ,real(wtxtmp))
                        call Hfill(3221,real(jetsellab(i,1)),0.
     &                       ,real(wtxtmp))
                        call Hfill(3222,real(jetsel(i,3))   ,0.
     &                       ,real(wtxtmp))
                        call Hfill(3223,real(jetsel(i,1))   ,0.
     &                       ,real(wtxtmp))
*     
                        if (ptm1.gt.0.and.muon1) then
                           call Hfill(3230,real(ptm1)  ,0.,real(wtxtmp))
                           call Hfill(3231,real(th1*rd),0.,real(wtxtmp))
                           call Hfill(3232,real(etam1) ,0.,real(wtxtmp))
                           call Hfill(3233,real(pmum1) ,0.,real(wtxtmp))
                        endif
                        if (ptm2.gt.0 .and.muon2) then
                           call Hfill(3230,real(ptm2)  ,0.,real(wtxtmp))
                           call Hfill(3231,real(th2*rd),0.,real(wtxtmp))
                           call Hfill(3232,real(etam2) ,0.,real(wtxtmp))
                           call Hfill(3233,real(pmum2) ,0.,real(wtxtmp))
                        endif
                     endif
                  enddo
               endif
*
*
               if (muon) wtx=wtxm 
               if (plot) then
                  sigbreit=sigbreit+tmp
                  call Hfill(1,1.5,0.,real(tmp))
                  if (muon) then
                     sigbreitm=sigbreitm+wtxm
                     call Hfill(1,3.5,0.,real(wtxm))
                  endif
*     
                  if (lp) write(6,*) ' q2= ',q2,' xbj= ',xbj
*     
                  call Hfill(3,real(q2) ,0.,real(tmp))
                  call Hfill(5,real(q2) ,0.,real(tmp))
*     
                  call Hfill(4,real(log10(xbj)),0.,real(tmp))        
                  call Hfill(7,real(log10(xbj)),0.,real(tmp))        
*     
                  if (muon2) then
                     call Hfill(1310,real(hzet(ib)),0.,real(wtxm))
                     call Hfill(1311,real(hzeta(ib)),0.,real(wtxm))
                     call Hfill(1320,real(jetslab(1,3)),0.,real(wtxm))
                     call Hfill(1321,real(jetslab(1,1)),0.,real(wtxm))
*     
                     if (ptm1.gt.0.and.muon1) then
                        call Hfill(1330,real(ptm1),0.,real(wtxm))
                        call Hfill(1331,real(th1*rd),0.,real(wtxm))
                        call Hfill(1332,real(etam1),0.,real(wtxm))
                     endif
                     if (ptm2.gt.0.and.muon2) then
                        call Hfill(1340,real(ptm2),0.,real(wtxm))
                        call Hfill(1341,real(th2*rd),0.,real(wtxm))
                        call Hfill(1342,real(etam2),0.,real(wtxm))
                     endif
                     call Hfill(1302,real(q2),0.,real(wtxm))
                     call Hfill(1303,real(y),0.,real(wtxm))
                     call Hfill(1304,real(log10(xbj)),0.,real(wtxm))
                  endif
* 
                  if (muon) then
*     
                     call Hfill(1202,real(q2),0.,real(wtxm))
                     call Hfill(1203,real(y),0.,real(wtxm))
                     call Hfill(1204,real(log10(xbj)),0.,real(wtxm))
*     
                     call Hfill(1210,real(etb)         ,0.,real(wtxm))
                     call Hfill(1211,real(etab)        ,0.,real(wtxm))
                     call Hfill(1212,real(hzet(ib))    ,0.,real(wtxm))
                     call Hfill(1213,real(hzeta(ib))   ,0.,real(wtxm))
                     call Hfill(1220,real(jetsellab(1,3)),0.,real(wtxm))
                     call Hfill(1221,real(jetsellab(1,1)),0.,real(wtxm))
                     call Hfill(1222,real(jetsel(1,3)),0.,real(wtxm))
                     call Hfill(  17,real(jetsel(1,3)),0.,real(wtxm))
                     if (q2.gt.10.) then 
                        call Hfill(  19,real(jetsel(1,3)),0.,real(wtxm))
                     endif
                     call Hfill(1223,real(jetsel(1,1)) ,0.,real(wtxm))
                     call Hfill(1224,real(jetsellab(1,1)),0.,real(wtxm))
                     call Hfill(1225,real(jetsel(1,1))   ,0.,real(wtxm))
                     call Hfill(1227,etaselfwd,0.,real(wtxm))
*     
                     if (imuonsel1.gt.0.and.muon1acc) then
                        call Hfill(1226,real(jetsellab(imuonsel1,1)),0.
     &                       ,real(wtxm))
                        call Hfill(1229,real(jetsel(imuonsel1,3)),0.
     &                   ,real(wtxm))
*
                        pmuon(1)=pmum1*sin(ph1)*cos(th1)
                        pmuon(2)=pmum1*cos(ph1)*cos(th1)
                        pmuon(3)=pmum1*sin(th1)
                        pmuon(4)=pmum1
                        costh=0.
                        absj=0.
                        absp=0.
                        do k=1,3
                           costh=pmuon(k)*jetsellab(imuonsel1,4+k)+costh  
                           absp=pmuon(k)**2+absp
                           absj= jetsellab(imuonsel1,4+k)**2+absj
                        enddo
                        absp=sqrt(absp)
                        absj=sqrt(absj)
                        costh=costh/(absp*absj)
                        ptrel=pmum1*sqrt(1-costh**2)
*     
                        call Hfill(1228,real(ptrel),0.,real(wtxm))
*     
                        absj=jetsellab(imuonsel1,4)
                        call Hfill(1235,real(pmum1/absj),0.,real(wtxm))
                        if (pmum1.gt.absj) then
*
                        endif
                        absp=sqrt(pmuon(1)**2+pmuon(2)**2)
                        absp=absp/jetsellab(imuonsel1,3)
                        call Hfill(1236,real(absp),0.,real(wtxm))
*     
                        absj=jetsellab(imuonsel1,7)
                        call Hfill(1237,real(pmuon(3)/absj),0.
     &                   ,real(wtxm))
*     
                     endif
*
                     if (imuonsel2.gt.0.and.muon2acc) then
                        call Hfill(1226,real(jetsellab(imuonsel2,1)),0.
     &                       ,real(wtxm))
                        call Hfill(1229,real(jetsel(imuonsel2,3)),0.
     &                       ,real(wtxm))
C     call Hfill(12,real(jetsel(imuonsel2,3)),0.,real(wtxm))
C     call Hfill(13,real(jetsel(imuonsel2,1)),0.,real(wtxm))
*     
                        pmuon(1)=pmum2*sin(ph2)*cos(th2)
                        pmuon(2)=pmum2*cos(ph2)*cos(th2)
                        pmuon(3)=pmum2*sin(th2)
                        pmuon(4)=pmum2
                        costh=0.
                        absj=0.
                        absp=0.
                        do k=1,3
                           costh=pmuon(k)*jetsellab(imuonsel2,4+k)+costh  
                           absp=pmuon(k)**2+absp
                           absj= jetsellab(imuonsel2,4+k)**2+absj
                        enddo
                        absp=sqrt(absp)
                        absj=sqrt(absj)
                        costh=costh/(absp*absj)
                        ptrel=pmum2*sqrt(1-costh**2)
                        call Hfill(1228,real(ptrel),0.,real(wtxm))
*     
                        absj=jetsellab(imuonsel2,4)
                        call Hfill(1235,real(pmum2/absj),0.,real(wtxm))
                        absp=sqrt(pmuon(1)**2+pmuon(2)**2)
                        absp=absp/jetsellab(imuonsel2,3)
                        call Hfill(1236,real(absp),0.,real(wtxm))
*     
                        absj=jetsellab(imuonsel2,7)
                        call Hfill(1237,real(pmuon(3)/absj),0.
     &                       ,real(wtxm))
                     endif
*     
                     call Hfill(1240,real(jetslab(2,3)),0.,real(wtxm))
                     call Hfill(1241,real(jetslab(2,1)),0.,real(wtxm))
                     call Hfill(1250,real(jets(2,3))   ,0.,real(wtxm))
                     call Hfill(1251,real(jets(2,1))   ,0.,real(wtxm))
*     
                     if (ptm1.gt.0.and.muon1.and.muon1acc) then
                        call Hfill(1230,real(ptm1)    ,0.,real(wtxm))
                        call Hfill(1234,real(log10(ptm1)),0.,real(wtxm))
                        call Hfill(1231,real(th1*rd)  ,0.,real(wtxm))
                        call Hfill(1232,real(etam1)   ,0.,real(wtxm))
                        call Hfill(1233,real(pmum1)   ,0.,real(wtxm))
                        call Hfill(1234,real(ptm1)    ,0.,real(wtxm))
*     
                        call Hfill(10,real(ptm1),   0.,real(wtxm))
                        call Hfill(18,real(ptm1),   0.,real(wtxm))
                        call Hfill(11,real(etam1),  0.,real(wtxm))
                        call Hfill(12,real(etam1),  0.,real(wtxm))
                     endif
                     if (ptm2.gt.0.and.muon2.and.muon2acc) then
                        call Hfill(1230,real(ptm2),   0.,real(wtxm))
                        call Hfill(1234,real(log10(ptm2)),0.,real(wtxm))
                        call Hfill(1231,real(th2*rd), 0.,real(wtxm))
                        call Hfill(1232,real(etam2),  0.,real(wtxm))
                        call Hfill(1233,real(pmum2)  ,0.,real(wtxm))
*     
                        call Hfill(10,real(ptm2),   0.,real(wtxm))
                        call Hfill(18,real(ptm2),   0.,real(wtxm))
                        call Hfill(11,real(etam2),  0.,real(wtxm))
                        call Hfill(12,real(etam2),  0.,real(wtxm))
*
                     endif
*     
                     call Hfill(2,0.5,0.,real(wtxm))
*     
                     call Hfill(13,real(q2) ,0.,real(wtxm))
                     call Hfill(6 ,real(q2) ,0.,real(wtxm))
*     
                     call Hfill(14,real(log10(xbj)),0.,real(wtxm))
                     call Hfill(8, real(log10(xbj)),0.,real(wtxm))                
*     
                     do i=1,nq2
                        if (xq2(i).lt.q2.and.xq2(i+1).gt.q2) then
                           call Hfill(20+i,real(q2),0.,real(wtxm))
                        endif
                     enddo
*
                     do i=1,nx
                        if (xx(i).lt.log10(xbj)
     &                       .and.xx(i+1).gt.log10(xbj)) then
                           call Hfill(30+i,real(log10(xbj)),0.
     &                          ,real(wtxm))
                        endif
                     enddo
                  endif
*     
                  pt=sqrt(jetsel(1,5)**2+jetsel(1,6)**2)
                  call Hfill(240,real(jetsel(1,3)) ,0.,real(tmp))
                  call Hfill(241,real(pt)          ,0.,real(tmp))
                  call Hfill(242,real(jetslab(1,1)),0.,real(tmp))
                  call Hfill(243,real(log10(q2))     ,0.,real(tmp))
                  call Hfill(244,real(y)         ,0.,real(tmp))
                  call Hfill(245,real(log10(xbj)),0.,real(tmp))
                  if (muon) then
                     call Hfill(250,real(Jetsel(1,3)) ,0.,real(wtxm))
                     call Hfill(251,real(pt)          ,0.,real(wtxm))
                     call Hfill(252,real(jetslab(1,1)) ,0.,real(wtxm))
                     call Hfill(253,real(log10(q2))      ,0.,real(wtxm))
                     call Hfill(254,real(y)         ,0.,real(wtxm))
                     call Hfill(255,real(log10(xbj)),0.,real(wtxm))
*     
                     call Hfill(256,real(ptm1) ,0.,real(wtxm))          
                     call Hfill(257,real(etam1),0.,real(wtxm))          
                     call Hfill(258,real(ptm2) ,0.,real(wtxm))          
                     call Hfill(259,real(etam2),0.,real(wtxm))          
                  endif
               endif
*     
               if (gen.ne.'hvq') then
                  do j=1,2
                     do i=1,4
                        rpb (i,j)=0
                        pbbar(i,j)=0
                     enddo
                  enddo
*
                  nb=0
                  if (etab.gt.cetal.and.etab.lt.cetah) then
                     nb=nb+1
                     do i=1,4
                        pbbar(i,nb)=phep(i,ib)
                     enddo
                  endif
                  if (etabar.gt.cetal.and.etabar.lt.cetah) then
                     nb=nb+1
                     do i=1,4
                        pbbar(i,nb)=phep(i,ibar)
                     enddo
                  endif
*     
C     if (lp) write(6,*) ' ib=',ib,' ibar= ',ibar,' should be 4 and 6 '
*     
                  do j=1,nb 
                     do i=1,4
                        rpb (i,j)=pbbar(i,j)
                        if (lp) write(6,*) ' pbbar= ',pbbar(i,j)
                     enddo
                  enddo
*     
                  if (nb.gt.0) then
                     call bmatch(dir,240,nb,rpb,nsel,jetsel)
*     
C     call bmatch(dir,100,nb,rpb,nsel,jetsellab)
*     
                  endif
               endif
*     
            endif
*
*     here ends OUR scenario: <<
*     
*
            if (nsel.ge.2) then
               pt1=sqrt(jetsel(1,5)**2+jetsel(1,6)**2)
               pt2=sqrt(jetsel(2,5)**2+jetsel(2,6)**2)
               if (pt2.gt.5. .and. pt1.gt.5.) then
*     
                  delta =pt1-pt2
                  sum   =pt1+pt2
*     
                  call hfill(421,real(pt1),0.,real(wtxm))
                  call hfill(422,real(pt2),0.,real(wtxm))
                  call hfill(423,sum/2.,0.,real(wtxm))
*     
                  if (pt1.gt.8.) then 
                     call hfill(401,real(pt1),0.,real(wtxm))
                     call hfill(403,sum/2.,0.,real(wtxm))
                     call hfill(405,real(pt2),0.,real(wtxm))
                     call hfill(411,real(pt1),0.,real(wtxm))
                     call hfill(413,sum/2.,0.,real(wtxm))
                     call hfill(415,real(pt2),0.,real(wtxm))
                  endif
                  
                  if (sum.gt.13.) then
                     call hfill(402,real(pt1),0.,real(wtxm))
                     call hfill(404,sum/2.,0.,real(wtxm))
                     call hfill(406,real(pt2),0.,real(wtxm))
                     call hfill(412,real(pt1),0.,real(wtxm))
                     call hfill(414,sum/2.,0.,real(wtxm))
                     call hfill(416,real(pt2),0.,real(wtxm))
                  endif    
               endif
            endif
*     
*     Now come dijets
*     
            if (nsel.ge.2) then
               pt=sqrt(jetsel(1,5)**2+jetsel(1,6)**2)
               if (pt.gt.ptmin) then
                  call Hfill(301,real(Jetsel(1,3))  ,0.,real(wtxm))
                  call Hfill(302,real(Jetsel(2,3))  ,0.,real(wtxm))
                  call Hfill(303,real(pt)           ,0.,real(wtxm))
                  pt=sqrt(jetsel(2,5)**2+jetsel(2,6)**2)
                  call Hfill(304,real(pt)           ,0.,real(wtxm))
                  eta1=real(jetsellab(1,1))
                  eta2=real(jetsellab(2,1))
                  eta=min(eta1,eta2)
                  call Hfill(305,real(eta)  ,0.,real(wtxm))
                  eta=max(eta1,eta2)
                  call Hfill(306,real(eta)  ,0.,real(wtxm))
*     
                  xm12=(JETSEL(1,5)+JETSEL(2,5))**2 +
     &                 (JETSEL(1,6)+JETSEL(2,6))**2 +
     &             (JETSEL(1,7)+JETSEL(2,7))**2 -
     &                 (JETSEL(1,4)+JETSEL(2,4))**2
                  xm12=-xm12
                  if (xm12.gt.0.) then
                     ksi= xbj*(1.+xm12/q2)
                     xm12=sqrt(xm12)
                  else
                     ksi=-999.
                     xm12=-999.
                  endif
C     if (lp) write(6,*) ' ksi = ',ksi
C     if (lp) write(6,*) ' Mas = ',xm12
C 
                  call Hfill(307,real(log10(ksi)),0.,real(wtxm))
                  call Hfill(308,real(xm12)      ,0.,real(wtxm))
*     
                  dphi=jetsel(1,2)-jetsel(2,2)
                  DELPHi=AMIN1(real(ABS(DPHI+2*pi)),real(ABS(DPHI)),
     &             real(ABS(DPHI-2*pi)))
                  call Hfill(309,delphi,0.,real(wtxm))  
                  call Hfill(310,delphi,0.,real(wtxm))  
*     
                  call Hfill(311,real(ptm1),0.,real(wtxm))  
                  call Hfill(312,real(etam1),0.,real(wtxm))  
                  call Hfill(313,real(ptm2),0.,real(wtxm))  
                  call Hfill(314,real(etam2),0.,real(wtxm))  
*
C     call HZHIJET2(0,2,nsel,jetsel)
*     
C     call HZHIJET(0,2,nsel,jetsel)
*     
               endif
            endif
C end of breit cuts !!!!!B
         endif

*                    
         if (gen.ne.'HVQ') then
            if (muon) then
               do i=1,nhep
                  do j=1,4
                     PHEP(j,i)=PLAB(j,i)
                  enddo
               enddo
*     
               if (lpp) then
                  write(6,*) ' Before '
                  call hzlihep(2) 
               endif  
*     
               call HZHEPTOP
*     
               do i=1,nhep
                  do j=1,4
                     PLAB(j,i)=PHEP(j,i)
                  enddo
               enddo
*     
               if (lpp) then 
                  write(6,*) ' after '
                  call hzlihep(2) 
               endif
*     
               do i=1,nhep
                  if (idhep(i).eq.5) then
                     ib=i
                  endif 
               enddo
*     
*     boost to Breit frame
               call ktbrei(2,plep,phad,psel,nhep,PLAB,PBREIT)
*     
*
               do i=5,nhep
                  do j=1,4
                     PHEP(j,i)=PBREIT(j,i)
                  enddo
                  PHEP(5,i)=-PHEP(1,i)**2-PHEP(2,i)**2-PHEP(3,i)**2
     &                 +PHEP(4,i)**2
                  if(PHEP(5,i).gt.0.) PHEP(5,i)=sqrt(PHEP(5,i))
               enddo
*     
               if (lpp) then  
                  write(6,*) ' Breit partons: ' 
                  call hzlihep(2)
               endif
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
               CALL hzjtfind(3,1.d0,NJET,Jets)
*     
*     transform back from Breit to Lab
*     
               call hzbrtola2(njet,jets,jetslab)
*
               nsel=0
               do j=1,njet
*     
*     apply jet cut !!!!!!
*
                  pt=sqrt(jets(j,5)**2+jets(j,6)**2)
                  if (pt.gt.cpt1
     &                 .and. jetslab(j,1).gt.cetal 
     &                 .and. jetslab(j,1).lt.cetah) then
                     nsel=nsel+1
                     ipjet(nsel)=j
                     do i=1,8
                        jetsel(nsel,i)=jets(j,i)
                        jetsellab(nsel,i)=jetslab(j,i)
                     enddo
                  endif
               enddo
*
               if ((Q2 .gt.2.  .and. q2.lt.1000.).and.
     &              ( y .gt.YMIN .and.  y.lt.YMAX ) )then
*     
*     
                  pt=sqrt(jetsel(1,5)**2+jetsel(1,6)**2)
                  if (pt.gt.ptmin) then
*     
                     call Hfill(5113,real(q2) ,0.,real(wtxm))
                     call Hfill(5106,real(q2) ,0.,real(wtxm))
*     
                     call Hfill(5114,real(log10(xbj)),0.,real(wtxm))
                     call Hfill(5108,real(log10(xbj)),0.,real(wtxm))                
*     
                     call Hfill(5010,real(etb)         ,0.,real(wtxm))
                     call Hfill(5011,real(etab)        ,0.,real(wtxm))
                     call Hfill(5012,real(hzet(ib))    ,0.,real(wtxm))
                     call Hfill(5013,real(hzeta(ib))   ,0.,real(wtxm))
                     call Hfill(5017,real(jetsel(1,3)),0.,real(wtxm))
                     call Hfill(5020,real(jetsellab(1,3)),0.,real(wtxm))
                     call Hfill(5021,real(jetsellab(1,1)),0.,real(wtxm))
                     call Hfill(5022,real(jetsel(1,3)) ,0.,real(wtxm))
                     call Hfill(5023,real(jetsel(1,1)) ,0.,real(wtxm))
*     
                  endif
               endif 
*     
            endif
         endif 
      endif
*     koniec liczenia !!!!!
*     
      if (iflag.eq.3) then
*     
         call hcdir('//PAWC/'//dir,' ')
*     
         write(6,*) ' # of events with muons: ',imucount,' out of: ',nev
*     
         write(6,*) ' All:           1. muons: ',imuacc1,
     &        ' 2. muon ',imuacc2
         if (imuacc1.ne.0 .and. imuacc2.ne.0) then
            write(6,'(2(A,F10.3,A,F10.3,A))') 
     &           ' In acc: 1. muons: ',imu1,': ',imu1/imuacc1,
     &           ' %', ' 2. muon ',imu2,': ',imu2/imuacc2,' %'
         endif
*     
         if (gen.ne.'HVQ') then
            write(6,*) ' Norm Histos here: xsec= ',xsec
            if (xsec.ne.0.) then
               lum=nev/xsec
               lum1=nev1/xsec
            else
               write(6,*) ' xsec= ',xsec,' !! '
               lum=0.
               lum1=0.
            endif
         else  
            lum=1.
            lum1=1.
         endif
*
         iall=indir+idir+itau+ioth
         if (iall.ne.0) then
            write(6,*) 'indirect decay ',indir,' in % ',
     &           real(indir)*100/real(iall)
            write(6,*) '  direct decay ',idir ,' in % ',
     &           real(idir)*100/real(iall)
            write(6,*) '     tau decay ',itau ,' in % ',
     &           real(itau)*100/real(iall)
            write(6,*) '   other decay ',ioth ,' in % ',
     &           real(ioth)*100/real(iall)
         endif
*     *F2b HVQNLO
         
*     
         write(6,*) ' Norm Histos here: lum= ',lum,'lumbreit lum1',lum1
*     
         if (lum.ne.0) then
*     
            write(6,*) ' ZEUS scenario in Lab frame Q2>2'
            write(6,*) ' Total      sig (pb): ',real(sigtoth1)/lum
            write(6,*) ' b tot  sig (pb): ',real(sigbh1)/lum
            write(6,*) ' >=1jets sig (pb): '
     &       ,real(sigjeth1)/lum
            write(6,*) ' muon +no cuts on jet sig (pb): '
     &           ,real(sigtotmh1)/lum
            write(6,*) ' muon+jet    sig (pb): ',real(sigjetmh1)/lum
            write(6,*) ' muon+jet+cone sig (pb): ',real(sigjetmcon)/lum
*     
            write(6,*) ' ZEUS scenario in Breit frame Q2>2 '
            write(6,*) ' tot        sig (pb): ',real(sigbrtot)/lum1
            write(6,*) ' b.cross    sig (pb): ',real(sigb)/lum1
            write(6,*) ' >=1jet sig (pb): ',real(sigbreit)/lum1
            write(6,*) ' muon nojet cut sig (pb): ',real(sigbreitnj)/lum1
            write(6,*) ' muon+jet   sig (pb): ',real(sigbreitm)/lum1
* 
            write(6,*) 'incl jet   sig (pb):',real(sigincljet)/lum1
            write(6,*) 'incl muon  sig (pb):',real(siginclmu)/lum1
            write(6,*) 'incl b     sig (pb):',real(siginclb)/lum1
            write(6,*) 'generator:',GEN,'hfrac',hfrac
****************************************************

c     Normalisation for Philipp
            CALL HZHINRM(30001,0,lum,1)
            CALL HZHINRM(30002,0,lum,1)
            CALL HZHINRM(30003,0,lum,1)
            CALL HZHINRM(30004,0,lum,1)

            CALL HZHINRM(31001,0,lum,1)
            CALL HZHINRM(31002,0,lum,1)
            CALL HZHINRM(31003,0,lum,1)
            CALL HZHINRM(31004,0,lum,1)
            CALL HZHINRM(31005,0,lum,1)

            CALL HZHINRM(30101,0,lum,1)
            CALL HZHINRM(30102,0,lum,1)
            CALL HZHINRM(30103,0,lum,1)
            CALL HZHINRM(30104,0,lum,1)

            CALL HZHINRM(31101,0,lum,1)
            CALL HZHINRM(31102,0,lum,1)
            CALL HZHINRM(31103,0,lum,1)
            CALL HZHINRM(31104,0,lum,1)
            CALL HZHINRM(31105,0,lum,1)

            call HZHINRM(40001,0,lum,1)
            call HZHINRM(40002,0,lum,1)
            call HZHINRM(40003,0,lum,1)
            call HZHINRM(40004,0,lum,1)
            call HZHINRM(40005,0,lum,1)
            call HZHINRM(140000,0,lum,1)            
            call HZHINRM(144000,0,lum,1)            
            call HZHINRM(140001,0,lum,1)            
            call HZHINRM(144001,0,lum,1)
            call HZHINRM(140002,0,lum,1)            
            call HZHINRM(144002,0,lum,1)
            call HZHINRM(140003,0,lum,1)            
            call HZHINRM(144003,0,lum,1)
            call HZHINRM(140004,0,lum,1)            
            call HZHINRM(144004,0,lum,1)
            call HZHINRM(140005,0,lum,1)            
            call HZHINRM(144005,0,lum,1)
            call HZHINRM(140006,0,lum,1)            
            call HZHINRM(144006,0,lum,1)
            call HZHINRM(40010,0,lum,1)
            call HZHINRM(40011,0,lum,1)
            call HZHINRM(90000,0,lum,1)
            call HZHINRM(90001,0,lum,1)
            call HZHINRM(90002,0,lum,1)
            call HZHINRM(90003,0,lum,1)
            call HZHINRM(90004,0,lum,1)
            call HZHINRM(90005,0,lum,1)
            call HZHINRM(90006,0,lum,1)
*************************************************
            call HZHINRM(2,0,lum,1)
            call HZHINRM(3,0,lum,1)
            call HZHINRM(4,0,lum,1)
            call HZHINRM(5,0,lum,1)
            call HZHINRM(6,0,lum,1)
*     
            call HZHINRM(10,0,lum,1)
            call HZHINRM(11,0,lum,1)
C     call HZHINRM(12,0,lum,1)
            call HZHINRM(13,0,lum,1)
            call HZHINRM(14,0,lum,1)
            call HZHINRM(15,0,lum,1)
            call HZHINRM(16,0,lum,1)
            call HZHINRM(17,0,lum,1)
            call HZHINRM(19,0,lum,1)
            call HZHINRM(18,0,lum,1)
*     
            call HZHINRM(1005,0,lum,1)
            call HZHINRM(1007,0,lum,1)
*
            call HZHINRM(5113,0,lum,1)
            call HZHINRM(5106,0,lum,1)
            call HZHINRM(5114,0,lum,1)
            call HZHINRM(5010,0,lum,1)
            call HZHINRM(5011,0,lum,1)
            call HZHINRM(5012,0,lum,1)
            call HZHINRM(5013,0,lum,1)
            call HZHINRM(5020,0,lum,1)
            call HZHINRM(5021,0,lum,1)
            call HZHINRM(5022,0,lum,1)
            call HZHINRM(5023,0,lum,1)
*     
            call HZHINRM(1402,0,lum,1)
            call HZHINRM(1403,0,lum,1)
            call HZHINRM(1404,0,lum,1)
            do i=0,3
               call HZHINRM(1410+i,0,lum,1)
               call HZHINRM(1420+i,0,lum,1)
            enddo 
            call HZHINRM(1430,0,lum,1)
            call HZHINRM(1431,0,lum,1)
            call HZHINRM(1432,0,lum,1)
*     
            do i=0,5
C     call HZHINRM(200+I,0,lum,1)
C     call HZHINRM(210+I,0,lum,1)
C     call HZHINRM(220+I,0,lum,1)
C     call HZHINRM(230+I,0,lum,1)
C     if (i.ne.5) call HZHINRM(235+I,0,lum,1)
               call HZHINRM(240+I,0,lum,1)
               call HZHINRM(250+I,0,lum,1)
               if (i.ne.5) call HZHINRM(250+I,0,lum,1)
C     if (i.ne.0) call HZHINRM(300+I,0,lum,1)
               if (i.ne.0) call HZHINRM(400+I,0,lum,1)
               if (i.ne.0) call HZHINRM(410+I,0,lum,1)
            enddo
*
            do j=0,3
               do i=0,1
                  do k=1,5
                     id=1000+J*100+10*k+I 
                     call HZHINRM(ID,0,lum,1)
                     if ((j.eq.0 .or. j.eq.0) .and.k.ne.5) then
                        id=2000+J*100+10*k+I
                        call HZHINRM(ID,0,lum,1)
                     endif
                  enddo
               enddo
            enddo   
*     
            do i=0,2
               do j=0,3
                  do k=1,3
                     id=3000+i*100+10*k+I 
                     if (.not.(j.eq.0.and.(i.ge.0.or.i.lt.2)) ) then
                        call HZHINRM(ID,0,lum,1)
                     endif
                  enddo
               enddo   
            enddo
*
            if (gen.ne.'HVQ') then
               do j=0,2
                  do i=0,1
                     do k=1,3
                        id=6000+J*100+10*k+I 
                        call HZHINRM(ID,0,lum,1)
                        id=7000+J*100+10*k+I
                        call HZHINRM(ID,0,lum,1)
                     enddo
                  enddo
               enddo   
            endif
*     
            call HZHINRM(1012,0,lum,1)
            call HZHINRM(1013,0,lum,1)
            call HZHINRM(1112,0,lum,1)
            call HZHINRM(1113,0,lum,1)
            call HZHINRM(1212,0,lum,1)
            call HZHINRM(1213,0,lum,1)
*
            call HZHINRM(1114,0,lum,1)
            call HZHINRM(1115,0,lum,1)
*     
            call HZHINRM(1022,0,lum,1)
            call HZHINRM(1023,0,lum,1)
            call HZHINRM(1122,0,lum,1)
            call HZHINRM(1123,0,lum,1)
            call HZHINRM(1222,0,lum,1)
            call HZHINRM(1223,0,lum,1)
*     
            call HZHINRM(1228,0,lum,1)
            call HZHINRM(1235,0,lum,1)
            call HZHINRM(1236,0,lum,1)
            call HZHINRM(1237,0,lum,1)
            
            call HZHINRM(1229,0,lum,1)
*     
            Do i=0,4
               Do j=4,7
                  if (i.ne.3) then 
                     id=1000+i*100+20+j
                     call HZHINRM(id,0,lum,1)
                  endif 
               enddo
            enddo  
*
            call HZHINRM(1032,0,lum,1)
            call HZHINRM(1132,0,lum,1)
            call HZHINRM(1232,0,lum,1)
            call HZHINRM(1332,0,lum,1)
*     
            call HZHINRM(1033,0,lum,1)
            call HZHINRM(1133,0,lum,1)
            call HZHINRM(1133,0,lum,1)
            call HZHINRM(1233,0,lum,1)
*     
            call HZHINRM(1034,0,lum,1)
            call HZHINRM(1134,0,lum,1)
            call HZHINRM(1134,0,lum,1)
            call HZHINRM(1234,0,lum,1)
* 
            do j=0,3
               id=1000+J*100+2
               call HZHINRM(ID,0,lum,1)
               id=1000+J*100+3
               call HZHINRM(ID,0,lum,1)
               id=1000+J*100+4
               call HZHINRM(ID,0,lum,1)
*     
               if (j.ne.1 .and. j.ne.3) then
                  id=2000+J*100+2
                  call HZHINRM(ID,0,lum,1)
                  id=2000+J*100+3
                  call HZHINRM(ID,0,lum,1)
                  id=2000+J*100+4
                  call HZHINRM(ID,0,lum,1)
               endif
            enddo
*     
         endif
*     
         if (gen.eq.'HVQ') then
            xsec=1.        
            wtx=1D0      
         endif
*     
C     write(6,*) ' xsec= ',xsec,' wtx= ',wtx 
C     call HZHIJET2(0,3,nsel,jetsel)
*     call HZHIJET (0,3,nsel,jetsel)
*
      endif  
*
*     
 999  continue
      RETURN
      END
*     
      subroutine bmatch(dir,id,nb,pb,njets,jets)
************************************************
* computes efficiency and purity of b-jets
*     id: histo ID-offset to store eff+pur
*     p1(4): first  b-jet
*     p2(4): second b-jet
*     jet array: jets nejt: number of jets
*************************************************
      Implicit none
      integer id,id1,id2,id3,id4
*     
      INTEGER MAXHZJETS
      PARAMETER (MAXHZJETS=50)     
      DOUBLE PRECISION JETS(MAXHZJETS,8)
      Integer i,j,k,njets,nb
      real pb(4,2)
      real etai,phii,dpz,dpt2,dtemp,dr,dptb
      real etaj,phij
      logical lp,first
      data lp/.false./,first/.true./
      integer noi,noj
*
      Integer nx,ny,ntw,iad
      Real xmin,xmax,ymin,ymax,xleft,xright,binw,hie,hi
      Character*80 title,titnew
      Logical hexist
      Integer nmax
      Integer nbin,ibin,ima,jma
      Parameter (nmax=200)
      Real xbins(nmax) 
*
      CHARACTER*7 xxxx
      CHARACTER*4 dir
      CHARACTER*16 string
      Data xxxx/'BMAT'/
*
      call hgive( id, title, nx, xmin, xmax, ny, ymin, ymax, ntw, iad )
*     
      if( nx .eq. 0 ) then
         write(6,*) xxxx,' histo with 0 bins, id= ',id
         return
      elseif( nx .gt. nmax ) then
         write(6,*) xxxx,' histo with #bins>max, id= ',id,nx,nmax
         return
      endif
*
      do i=1,nmax
         xbins(i)=0.
      enddo
*     careful with last bin!
      do i=1,nx
*     lower edge of bin
         call hix(id,i,xleft)
*     upper edge of bin
         xright=xmax
         if(i.lt.nx) call hix(id,i+1,xright)
*     bin width
C     binw = xright-xleft
*     bin content
C     write(6,*) '  bin #, xl,xr, cont ', i,xleft,xright
*     normalized contents
         xbins(i)=xleft
      enddo
*     
      xbins(nx+1)=xright
*     
      if (lp) then
         write(6,*) xxxx,id,' Binning = ',(xbins(i),i=1,nx+1)
      endif
*     
      IF (first) then
         write(6,*) '**bmatch: create ',xxxx
         Call hcdir('//PAWC/'//dir,' ')
         call hmdir(xxxx,'S')
         Call hcdir('//HISTO/'//dir,' ')
         call hmdir(xxxx,'S')
         first=.false.
      endif
*     
      write(string,'(A,A,A,A)') '//PAWC/',dir,'/',xxxx
C     write(6,*) ' change to dir= ',string
      call hcdir(string,' ')
*     
      id1=id+100000
      id2=id+200000
      id3=id+300000
      id4=id+400000
*     
C      write(6,*) ' hexist(id1) ',hexist(id1)
      if (.not.hexist(id1)) then
         write(6,*) xxxx,' histos booked ! ' 
         call hbookb(id1,title,nx,xbins,0.)
         call hbookb(id2,title,nx,xbins,0.)
         call hbookb(id3,title,nx,xbins,0.)
         call hbookb(id4,title,nx,xbins,0.)
         call hbarx(id1)
         call hbarx(id2)
         call hbarx(id3)
         call hbarx(id4)
      endif 
*
      if (lp) then
         write(6,*) '**bmatch: b-vector nb= ',nb
         do j=1,nb
            write(6,'(I2,A,4f9.3)') j, '   b= ',(pb(i,j),i=1,4)
         enddo
*     
         write(6,*) '**bmatch: jets '
         call hzlijet(njets,jets)
      endif
*           loop over b-vector and jets
      ima=-1
*     
      do i=1,nb
         jma=-1
c     ---               get particle momentum components
         dpz = pb(3,i)
         dpt2 = pb(1,i)**2+pb(2,i)**2
         dtemp = (SQRT(dpt2+dpz**2)+ABS(dpz))**2
c ---               check if calculation is possible
         if (dpt2.le.4.25E-18*dtemp) then
            etai = 20.D0
         else
c     ---              get amount of pseudo-rapidity
            etai = 0.5D0*LOG(dtemp/dpt2)
         endif
         etai=SIGN(etai,dpz)
*     
c     ---      check if calculation is possible
         if (dpt2.EQ.0.D0) THEN
            phii=0.
         else
c     ---   get azimutal angle (phi)
            phii=ATAN2(pb(2,i),pb(1,i))
         endif
*     
         do j=1,njets
*     
c ---               get particle momentum components
            dpz = jets(j,7)
            dpt2 = jets(j,5)**2+jets(j,6)**2
            dtemp = (SQRT(dpt2+dpz**2)+ABS(dpz))**2
c     ---               check if calculation is possible
            if (dpt2.le.4.25E-18*dtemp) then
               etaj = 20.D0
            else
c     ---               get amount of pseudo-rapidity
               etaj = 0.5D0*LOG(dtemp/dpt2)
            endif
            etaj=SIGN(etaj,dpz)
*     
c ---      check if calculation is possible
            if (dpt2.EQ.0.D0) THEN
               phij=0.
            else
c     ---    get azimutal angle (phi)
               phij=ATAN2(jets(j,6),jets(j,5))
            endif
*     
            if (lp) write(6,*) i,j,' etai, phii= ',etai,phii,
     &           ' etaj, phij= ',etaj,phij
*     
            dr=sqrt((etai-etaj)**2+(phii-phij)**2)
            if (dr.lt.1.) then
               if (lp) write(6,*) ' match i,j= ',i,j
               jma=j
               ima=i
            endif          
*     
            dpt2= sqrt(jets(j,5)**2+jets(j,6)**2)
            if (i.eq.1) then
               call Hfill(id1,real(dpt2),0.,1.)
            endif
*     
         enddo
*     
         dptb = sqrt(pb(1,i)**2+pb(2,i)**2)
         call Hfill(id3,real(dptb),0.,1.)
*     
         if (lp) write(6,*) ' dptb, dpt2= ',dptb,dpt2
         if (lp) write(6,*) ' ima, jma= ',ima,jma
         
*
         if (jma.ne.-1) then 
            call Hfill(id2,real(dptb),0.,1.)
            call Hfill(id4,real(dpt2),0.,1.)
         endif  
*     
      enddo
*     
      if (lp.and.ima.eq.-1) write(6,*) '**bmatch: no match '
*     
      call hcdir('//PAWC/'//dir,' ')
*     
      return
      end
