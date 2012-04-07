*CMZ :  0.00/04 06/06/2000  12.14.14  by  Tancredi Carli
*CMZ :  0.00/03 24/11/98  19.19.22  by  Tancredi Carli
*CMZ :  0.00/02 28/12/97  12.21.20  by  Tancredi Carli
*-- Author : Tancredi Carli
       Subroutine HZHIJET2(IOFF,IFLAG,njetlab,jetslab)
*****************************************************************************
*
* comapred to hzhijet this routine has no cuts on kinematical quantities
* like q2 and y and has a sumEt cut of 12 instead of 17
*
*
* returned histogramms:
*
* Arguments: iflag=1 initialisation
*            iflag=2 filling
*            iflag=3 termination
*
* histograms ids:
* F1+F2+F3
* F1: 1000 syst error negativ 2000: syst error positiv
*
*              F2:
* ds/dQ2    :  100
* ds/dQ2dksi:  110
* ds/dQ2dEt :  120
* ds/dQ2Mjj :  130
* ds/dQ2detap: 140
* ds/dEtdetap: 150
* ds/dQ2dy:    160
* ds/dQ2xbj:   170
* ds/dQ2xp:    180
* ds/dQ2etafwd:190
* ds/dQ2etabkw:200
* ds/dQ2/detaboost: 210
* ds/dQ2etabreitfwd: 220
* ds/dQ2etabreitbckw: 230
* ds/dQ2dphi: 240
* ds/dxgamma: 260
* weights:    250
* ds/dQ2dksi: 270 (more bins)
*
* F3: 1: low Q2
*     2-6: to be defined
*     7: 200-300
*     8: 300-600
*     9: 600-5000
*****************************************************************************
*
	IMPLICIT NONE
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
*                                          subroutine-related var.
*                                          -----------------------
      Integer chjet,iflag,ioff
      CHARACTER*7 xxxx
      character*6 jetf
      Character rout*12
      logical lp,bin0
      Data lp/.false./
      Data rout/'**hzhijet: '/
      Data xxxx/'HIJET2'/
      Character string*80
      Integer ierr,nentry
      Data nentry/0/
      Real xw
*
      Integer id,id1
      Real nev,nsig
      Data nev/0./,nsig/0./
      Real x,y,q2,w2,rd,pi,dpi,xi,et,norm
      Real lox,loq2,shat,los,low2,xp,lum
      Parameter (pi=3.1415927,rd=180./pi,dpi=2*pi)
*
      Integer njetlab
      DOUBLE PRECISION Jetslab(maxhzjets,8)
      DOUBLE PRECISION Jetsel(maxhzjets,8)
*
      INTEGER i,j,k,l
*
      Real etmax,etmin,den,zpmax,zpmin,zp,eta,eta1,eta2,dphi,delphi
      Real xgamma
      Real phi1,phi2,pt1,pt2
*
      INTEGER IT, IM, IM1 , NQ2, II
      Save IT, IM, IM1
*
      INTEGER  NBINQ2LO, NBINXLO, NBINYLO, NBINETLO,NBINCFLO,NBINCBLLO,
     +     NBINXILO, NBINXPLO, NBINCPLO, NBINCBLO, NBINM2LO,
     +     NBINXLO5
      PARAMETER  (     NBINQ2LO=3, NBINXLO=4 , NBINXLO5=2, NBINYLO=4,
     +     NBINETLO=4, NBINXILO=4, NBINXPLO=4, NBINCPLO=5, NBINCBLO=4,
     +     NBINM2LO=4, NBINCFLO=5, NBINCBLLO=6)
      REAL XBINQ2LO(NBINQ2LO+1),XBINXLO(NBINXLO+1),XBINYLO(NBINYLO+1),
     +     XBINXLO0 (NBINXLO+1),XBINXLO1(NBINXLO+1),XBINXLO2(NBINXLO+1),
     +     XBINXLO3(NBINXLO+1),XBINXLO4(NBINXLO+1),XBINXLO5(NBINXLO+1),
     +     XBINETLO(NBINETLO+1),XBINXILO(NBINXILO+1),
     +     XBINXPLO(NBINXPLO+1),
     +     XBINXPLO1(NBINXPLO+1),XBINXPLO2(NBINXPLO+1),
     +     XBINXPLO3(NBINXPLO+1),XBINXPLO4(NBINXPLO+1),
     +     XBINCPLO(NBINCPLO+1),XBINCBLO(NBINCBLO+1),
     +     XBINM2LO(NBINM2LO+1),
     +     XBINCFLLO(NBINCFLO+1),XBINCBLLO(NBINCBLLO+1)
*
      DATA
     +     XBINQ2LO/ 10., 20., 35., 70./,
*
     +     XBINXLO  /0.0002, 0.00045, 0.0007 , 0.0012, 0.0030/
     +     XBINXLO1 /0.0001, 0.00018, 0.00025 , 0.00035, 0.00055/
     +     XBINXLO2 /0.0002, 0.00035, 0.00045 , 0.00060, 0.0010/
     +     XBINXLO3 /0.0004, 0.00050, 0.00070 , 0.0010, 0.00180/
     +     XBINXLO4 /0.0006, 0.0010 , 0.0014  , 0.0020, 0.0035/
     +     XBINXLO5 /0.0015, 0.0024 , 0.0030  , 0.0040, 0.0055/
*
     +     XBINYLO /0.2, 0.3, 0.4, 0.5, 0.6/
     +     XBINETLO/8.5, 11.5, 15., 20., 35./
     +     XBINXILO /0.005, 0.013, 0.02, 0.035, 0.10/
     +     XBINXPLO /0.007, 0.020, 0.04, 0.065, 0.13/
*
     +     XBINXPLO1/0.001, 0.004,0.010,0.030,0.06/
     +     XBINXPLO2/0.002, 0.007,0.020,0.050,0.10/
     +     XBINXPLO3/0.007, 0.020,0.040,0.080,0.20/
     +     XBINXPLO4/0.009, 0.035,0.080,0.200,0.50/
*
     +     XBINCPLO /0., 0.2, 0.4, 0.6, 0.9, 1.5 /
     +     XBINCBLO /0.8, 1.6, 2., 2.4 ,3.5 /
     +     XBINM2LO /15., 22., 31., 45., 85./
     +     XBINCFLLO /-1., 0., 1., 1.5, 2., 2.5/
     +     XBINCBLLO /-1., -0.5, 0., 0.5, 1., 1.5, 2.5/
*
       Integer nlow
       Parameter (nlow=35)
       Real SIGLO(nlow)
       Real estdsiglo(nlow),estcsiglo(nlow)
       Real esycsiglo(nlow)
       Real ehadpsiglo(nlow) ,ehadmsiglo(nlow)
       Real eempsiglo(nlow)  ,eemmsiglo(nlow)
*
       DATA
*          cross section dsigma
*                q2      1-3
     +     siglo/206.48,132.47,123.22,
*                dq2/xbj 4-7
     +           117.02,104.31,127.34,110.96,
*                dq2/dksi 8-11
     +           110.88,115.99,123.73,109.38,
*                dq2/etap 12-16
     +            98.66, 83.73, 92.31,105.26,82.80,
*                dq2/Et   17-20
     +           292.32,117.21, 43.51, 15.68,
*                dq2/Mjj 21-24
     +           152.28,162.58,110.30,28.918,
*                dq2/etafwd 25-29
     +             8.76,181.46,110.03, 93.55, 71.52,
*                dq2/etaback 30-35
     +            54.51,130.51,154.54, 93.71, 22.42,9.34/
*
       DATA
*          stat error data
*                q2      1-3
     +     estdsiglo/5.4,6.3,6.6,
*                dq2/xbj 4-7
     +               7.2,7.0,6.8,7.1,
*                dq2/dksi 8-11
     +               7.2,7.1,6.5,7.4,
*                dq2/etap 12-16
     +               7.2,8.2,8.0,7.4,8.8,
*                dq2/Et   17-20
     +               4.5,6.9,11.3,18.0,
*                dq2/Mjj 21-24
     +               5.9,5.9,7.5,14.4,
*                dq2/etafwd 25-29
     +              20.4,5.7,7.1,7.7,8.9,
*                dq2/etaback 30-35
     +              10.3,6.8,6.0,7.8,14.3,23.6/
*
       DATA
*          stat error correction factor
*                q2      1-3
     +     estcsiglo/6.3,6.1,6.6,
*                dq2/xbj 4-7
     +               8.0,6.1,8.1,8.2,
*                dq2/dksi 8-11
     +               9.1,8.6,5.8,8.4,
*                dq2/etap 12-16
     +               6.1,8.0,9.8,8.6,11.2,
*                dq2/Et   17-20
     +               5.3,7.4,10.3,10.7,
*                dq2/Mjj 21-24
     +               6.3,6.0,9.3,13.1,
*                dq2/etafwd 25-29
     +              10.5,6.9,7.1,8.1,9.2,
*                dq2/etaback 30-35
     +              10.8,7.7,6.6,9.5,9.5,15.1/
*
       DATA
*          syst error correction factor
*                q2      1-3
     +     esycsiglo/1.1,0.9,4.4,
*                dq2/xbj 4-7
     +              -3.6,1.0,7.2,2.7,
*                dq2/dksi 8-11
     +               7.4,1.3,-2.8,2.9,
*                dq2/etap 12-16
     +              -1.4,1.8,4.5,6.5,0.6,
*                dq2/Et   17-20
     +               4.3,-1.1,2.0,1.4,
*                dq2/Mjj 21-24
     +               6.5,-2.4,1.4,0.2,
*                dq2/etafwd 25-29
     +              1.6,0.4,2.2,7.0,2.0,
*                dq2/etaback 30-35
     +             -1.4,3.7,-0.8,5.6,8.4,0.5/
*
       DATA
*          hadronic energy scale plus
*                q2      1-3
     +     ehadpsiglo/15.3,13.0,13.0,
*                dq2/xbj 4-7
     +              15.5,13.3,13.0,13.0,
*                dq2/dksi 8-11
     +              14.1,15.3,13.0,13.3,
*                dq2/etap 12-16
     +              13.0,13.4,13.4,14.6,14.6,
*                dq2/Et   17-20
     +               13.0,13.0,19.2,19.4,
*                dq2/Mjj 21-24
     +               13.0,15.4,13.0,29.2,
*                dq2/etafwd 25-29
     +              13.0,13.0,15.9,13.8,13.5,
*                dq2/etaback 30-35
     +             18.1,13.9,13.0,13.0,13.0,22.2/
*
       DATA
*          hadronic energy scale minus
*                q2      1-3
     +     ehadmsiglo/-12.6,-12.0,-12.5,
*                dq2/xbj 4-7
     +              -14.5,-12.0,-12.0,-13.6,
*                dq2/dksi 8-11
     +              -14.1,-12.8,-12.0,-14.9,
*                dq2/etap 12-16
     +              -12.8,-12.1,-12.0,-12.0,-14.6,
*                dq2/Et   17-20
     +               -12.0,-13.5,-12.8,-22.6,
*                dq2/Mjj 21-24
     +               -12.0,-12.0,-20.3,-18.7,
*                dq2/etafwd 25-29
     +             -16.7,-12.0,-12.0,-12.0,-17.5,
*                dq2/etaback 30-35
     +             -18.1,-12.0,-12.0,-12.0,-14.3,-22.2/
*
       DATA
*          electromagnetic energy scale plus
*                q2      1-3
     +     eempsiglo/-2.4,-2.8,-2.0,
*                dq2/xbj 4-7
     +              -3.6,-2.0,-2.0,-5.5,
*                dq2/dksi 8-11
     +              -2.0,-2.0,-2.5,-2.8,
*                dq2/etap 12-16
     +              -2.0,-4.0,-3.8,-2.0,-3.1,
*                dq2/Et   17-20
     +               -2.8,-2.0,-2.0,-2.0,
*                dq2/Mjj 21-24
     +               -2.5,-2.0,-2.0,-2.0,
*                dq2/etafwd 25-29
     +             -2.0,-2.0,-2.0,-3.0,-4.8,
*                dq2/etaback 30-35
     +             -2.0,-2.0,-4.7,-4.8,-2.0,-11.1/
       DATA
*          electromagnetic energy scale minus
*                q2      1-3
     +     eemmsiglo/1.0,1.6,3.0,
*                dq2/xbj 4-7
     +               1.0, 2.5,1.0,1.0,
*                dq2/dksi 8-11
     +               1.0,1.0,3.3,2.2,
*                dq2/etap 12-16
     +               2.1,2.0, 3.2,1.0,1.0,
*                dq2/Et   17-20
     +               1.0,3.4,1.0,1.0,
*                dq2/Mjj 21-24
     +                2.8,2.7,1.0,2.1,
*                dq2/etafwd 25-29
     +             1.0,1.0,1.0,5.4,1.0,
*                dq2/etaback 30-35
     +             1.0,1.0,1.0,4.8,12.2,1.0/
*      LOW Q2
*      xbj
       Real sigxblo(NBINXLO)
       Real esigxbstatlo(NBINXLO)
       Real esigxbsymlo(NBINXLO),esigxbsyplo(NBINXLO)
       Real esigmxblo(NBINXLO),esigpxblo(NBINXLO)
*      ks
       Real sigkslo(NBINXILO)
       Real esigksstatlo(NBINXILO)
       Real esigkssymlo(NBINXILO),esigkssyplo(NBINXILO)
       Real esigmkslo(NBINXILO),esigpkslo(NBINXILO)
*      etap
       Real sigeplo(NBINCPLO)
       Real esigepstatlo(NBINCPLO)
       Real esigepsymlo(NBINCPLO),esigepsyplo(NBINCPLO)
       Real esigmeplo(NBINCPLO),esigpeplo(NBINCPLO)
*      et
       Real sigetlo(NBINETLO)
       Real esigetstatlo(NBINETLO)
       Real esigetsymlo(NBINETLO),esigetsyplo(NBINETLO)
       Real esigmetlo(NBINETLO),esigpetlo(NBINETLO)
*      MJJ
       Real sigmjlo(NBINM2LO)
       Real esigmjstatlo(NBINM2LO)
       Real esigmjsymlo(NBINM2LO),esigmjsyplo(NBINCPLO)
       Real esigmmjlo(NBINM2LO),esigpmjlo(NBINM2LO)
*      etafwd
       Real sigeflo(NBINCFLO)
       Real esigefstatlo(NBINCFLO)
       Real esigefsymlo(NBINCFLO),esigefsyplo(NBINCFLO)
       Real esigmeflo(NBINCFLO),esigpeflo(NBINCFLO)
*      etaback
       Real sigeblo(NBINCBLLO)
       Real esigebstatlo(NBINCBLLO)
       Real esigebsymlo(NBINCBLLO),esigebsyplo(NBINCBLLO)
       Real esigmeblo(NBINCBLLO),esigpeblo(NBINCBLLO)
*
*     HIGH Q2
*
      INTEGER
     + NBINQ2,
     + NBINX  ,NBINY  ,NBINET, NBINM2, NBINXP, NBINCB, NBINCP,
     + NBINCFB,NBINCBB,NBINCFL,NBINCBL,NBINXI,NBINXIALL,
     + NBINXI2,NBINXI7,NBINXI8,NBINXI9,NBINXI1,
     + NBINET7,NBINET8,NBINET9,
     + NBINM21,NBINM21new,
     + NBINXP7, NBINXP8, NBINXP9,
     + NBINCP1,
     + NBINX7, NBINX8, NBINX9,
     + NBINDPH
      PARAMETER  (
     + NBINQ2=8,
     + NBINX=8,NBINY=4,NBINET=4,NBINM2=4,NBINXP=7,NBINCB=7,NBINCP=5,
     + NBINCFB=7,NBINCBB=7,NBINCFL=5,NBINCBL=6,NBINXI=5,NBINXIALL=7,
     + NBINXI2=6,NBINXI7=5,NBINXI8=5,NBINXI9=4,NBINXI1=4,
     + NBINET7=4,NBINET8=4,NBINET9=4,
     + NBINM21=4,
     + NBINXP7=4,NBINXP8=4,NBINXP9=4,
     + NBINCP1=4,
     + NBINX7=4, NBINX8=4, NBINX9=4,
     + NBINDPH=10)
      Integer NBINETnew
      parameter (NBINETnew=5)
      REAL XBINX(NBINX+1),XBINY(NBINY+1),XBINET(NBINETnew+1),
     +     XBINM2(NBINM2+1), XBINXP(NBINXP+1),
     +     XBINCB(NBINCB+1), XBINCP(NBINCP+1), XBINCP1(NBINCP1+1),
     +     XBINCFB(NBINCFB+1),XBINCBB(NBINCBB+1),
     +     XBINCFL(NBINCFL+1),XBINCBL(NBINCBL+1),
     +     XBINXI1(NBINXI1+1),XBINXI2(NBINXI1+1),
     +     XBINXI3(NBINXI1+1),XBINXI4(NBINXI1+1),
     +     XBINXI(NBINXI+1),XBINXIALL(NBINXIALL+1),
     +     XBINXI7(NBINXI7+1),XBINXI8(NBINXI8+1),XBINXI9(NBINXI9+1),
     +     XBINQ2(NBINQ2+1),
     +     XBINET7(NBINET7+1), XBINET8(NBINET8+1),XBINET9(NBINET9+1),
     +     XBINM21(NBINM21+1),
     +     XBINXP7(NBINXP7+1), XBINXP8(NBINXP8+1), XBINXP9(NBINXP9+1),
     +     XBINX7(NBINX7+1), XBINX8(NBINX8+1), XBINX9(NBINX9+1),
     +     XBINDPH(NBINDPH+1)
*
      Real XQ2(NBINQ2LO+NBINQ2+2)
      REAL Q2BIN0,WIDTH
      Parameter (Q2BIN0=60.)
      Integer nq2bin,nq2bini
      Parameter (nq2bin=10,nq2bini=18)
      Real Q2BIN(nq2bin),Q2BINW(nq2bin)
      Real Q2BINI(nq2bini),Q2BINIW(nq2bini)
*
*                1   2   3  4  5  6  7     8    9    10
C     Data Q2BIN/10.,70.,0.,0.,0.,0.,200.,300.,600.,5000./
*
C     Data Q2BIN/ 5.,8.,15.,25.,40.,70.,200.,300.,600.,5000./
      Data Q2BIN/ 5.,10.,20.,35.,70.,100.,200.,300.,600.,5000./
      Data Q2BINI/ 5., 7., 9.,12.,16., 21., 28., 38., 50.,  70.,
     &          100.,150.,180.,200.,300.,600.,5000.,10000./
*
      Integer netbin
      Parameter (netbin=4)
      Real ETBIN(netbin),ETBINW(netbin)
      Data ETBIN/8.5,12.,17.,35./
*
      DATA
     +     XBINX /0.004,0.006,0.008,0.01,0.014,0.02,0.03,0.05, 0.2/,
     +     XBINY /0.2, 0.3, 0.4, 0.5, 0.6/,
     +     XBINET/8.5, 11.5,15.,20.,30.,60./,
C*TC Aug99 +     XBINET/8.5, 13.0, 20., 30., 60./,
C    +     XBINM2/10., 22.0, 30., 45., 95./,
     +     XBINM2/15., 25.0, 40., 60., 95./,
     +     XBINXP /0., 0.15, 0.25,0.35, 0.45, 0.55,0.7, 0.95 /,
     +     XBINCB /-0.8, 0., 0.3, 0.6, 0.9, 1.2, 1.5, 2.2 /,
     +     XBINCP /0., 0.2, 0.4, 0.6, 0.9, 1.5 /,
     +     XBINCP1 /0., 0.2, 0.45, 0.8, 1.5 /,
     +     XBINCFB /0., 1., 1.3, 1.7, 2.0, 2.2, 2.7, 4.5 /,
     +     XBINCBB /0., 1., 1.3, 1.7, 2.0, 2.2, 2.7, 4.5 /,
     +     XBINCFL /-1., 0., 1., 1.5, 2., 2.5/,
     +     XBINCBL /-1., -0.5, 0., 0.5, 1., 1.5, 2.5/,
     +     XBINXI /0.005,0.015,0.025,0.04,0.06,0.1/,
     +     XBINXI1/0.004,0.010,0.025,0.05,0.1/,
     +     XBINXI2/0.004,0.010,0.025,0.05,0.1/,
     +     XBINXI3/0.004,0.010,0.025,0.05,0.1/,
     +     XBINXI4/0.004,0.010,0.025,0.05,0.1/,
     +     XBINXIALL/0.002,0.005,0.015,0.025,0.04,0.06,0.1,0.2/,
C    +     XBINXI /0.005, 0.010,0.020,0.03,0.04,0.06,0.1/,
C*TC Aug 99XBINXI /0.001, 0.015, 0.03, 0.060,0.18/,
     +     XBINXI7 /0.01, 0.02, 0.03, 0.04, 0.06, 0.15 /,
     +     XBINXI8 /0.015, 0.025,0.035, 0.045, 0.065, 0.18/,
     +     XBINXI9 /0.025, 0.045, 0.065, 0.1, 0.3 /,
     +     XBINQ2/ 200.,235.,280.,350.,450.,600.,900.,
     +     1500.,5000./,
     +     XBINET7/8.5, 11.5, 15., 20., 35./,
     +     XBINET8/8.5, 11.5, 15., 20., 35./,
     +     XBINET9/8.5, 11.5, 15., 20., 35./,
     +     XBINM21 /15., 22., 31., 45., 85./,
     +     XBINXP7 /0.07, 0.15, 0.25, 0.35, 0.6/,
     +     XBINXP8 /0.08, 0.2, 0.35, 0.5, 0.8 /,
     +     XBINXP9 /0.18, 0.35, 0.55, 0.7, 0.95 /,
     +     XBINX7 /0.004, 0.0055, 0.0075, 0.01  ,0.015/,
     +     XBINX8 /0.006, 0.009 , 0.012,  0.017 ,0.03/,
     +     XBINX9 /0.012, 0.023 , 0.035,  0.06  ,0.2/
     +     XBINDPH/0.,40.,60.,80.,100.,120.,140.,160.,170,175.,180./
*
       Real sigq2(NBINQ2LO+NBINQ2)
       Real esigq2stat(NBINQ2LO+NBINQ2)
       Real esigq2stathi(NBINQ2)
       Real esigq2sym(NBINQ2LO+NBINQ2),esigq2syp(NBINQ2LO+NBINQ2)
       Real esigm(NBINQ2LO+NBINQ2),esigp(NBINQ2LO+NBINQ2)
       Real esigmhi(NBINQ2),esigphi(NBINQ2)
*
       Real sigq2hi(NBINQ2)
       Real sigksi1(NBINXI7),sigksi2(NBINXI8),sigksi3(NBINXI9)
       Real siget1(NBINET7),siget2(NBINET8),siget3(NBINET9)
       Real sigmj1(NBINM21),sigmj2(NBINM21),sigmj3(NBINM21)
       Real sigetap1(NBINCP),sigetap2(NBINCP),sigetap3(NBINCP)
       Real sigetep1(NBINCP1),sigetep2(NBINCP1),sigetep3(NBINCP1)
       Real sigxb1(NBINX7),sigxb2(NBINX8),sigxb3(NBINX9)
       Real sigetf1(NBINCFL),sigetf2(NBINCFL),sigetf3(NBINCFL)
       Real sigetb1(NBINCBL),sigetb2(NBINCBL),sigetb3(NBINCBL)
*
       Real estdq2hi(NBINQ2)
       Real estdksi1(NBINXI7),estdksi2(NBINXI8),estdksi3(NBINXI9)
       Real estdet1(NBINET7),estdet2(NBINET8),estdet3(NBINET9)
       Real estdmj1(NBINM21),estdmj2(NBINM21),estdmj3(NBINM21)
       Real estdetap1(NBINCP),estdetap2(NBINCP),estdetap3(NBINCP)
       Real estdetep1(NBINCP1),estdetep2(NBINCP1),estdetep3(NBINCP1)
       Real estdxb1(NBINX7),estdxb2(NBINX8),estdxb3(NBINX9)
       Real estdetf1(NBINCFL),estdetf2(NBINCFL),estdetf3(NBINCFL)
       Real estdetb1(NBINCBL),estdetb2(NBINCBL),estdetb3(NBINCBL)
*
       Real estcq2hi(NBINQ2)
       Real estcksi1(NBINXI7),estcksi2(NBINXI8),estcksi3(NBINXI9)
       Real estcet1(NBINET7),estcet2(NBINET8),estcet3(NBINET9)
       Real estcmj1(NBINM21),estcmj2(NBINM21),estcmj3(NBINM21)
       Real estcetap1(NBINCP),estcetap2(NBINCP),estcetap3(NBINCP)
       Real estcetep1(NBINCP1),estcetep2(NBINCP1),estcetep3(NBINCP1)
       Real estcxb1(NBINX7),estcxb2(NBINX8),estcxb3(NBINX9)
       Real estcetf1(NBINCFL),estcetf2(NBINCFL),estcetf3(NBINCFL)
       Real estcetb1(NBINCBL),estcetb2(NBINCBL),estcetb3(NBINCBL)
*
       Real esycq2hi(NBINQ2)
       Real esycksi1(NBINXI7),esycksi2(NBINXI8),esycksi3(NBINXI9)
       Real esycet1(NBINET7),esycet2(NBINET8),esycet3(NBINET9)
       Real esycmj1(NBINM21),esycmj2(NBINM21),esycmj3(NBINM21)
       Real esycetap1(NBINCP),esycetap2(NBINCP),esycetap3(NBINCP)
       Real esycetep1(NBINCP1),esycetep2(NBINCP1),esycetep3(NBINCP1)
       Real esycxb1(NBINX7),esycxb2(NBINX8),esycxb3(NBINX9)
       Real esycetf1(NBINCFL),esycetf2(NBINCFL),esycetf3(NBINCFL)
       Real esycetb1(NBINCBL),esycetb2(NBINCBL),esycetb3(NBINCBL)
*
       Real ehadpq2hi(NBINQ2)
       Real ehadpksi1(NBINXI7),ehadpksi2(NBINXI8),ehadpksi3(NBINXI9)
       Real ehadpet1(NBINET7),ehadpet2(NBINET8),ehadpet3(NBINET9)
       Real ehadpmj1(NBINM21),ehadpmj2(NBINM21),ehadpmj3(NBINM21)
       Real ehadpetap1(NBINCP),ehadpetap2(NBINCP),ehadpetap3(NBINCP)
       Real ehadpetep1(NBINCP1),ehadpetep2(NBINCP1),ehadpetep3(NBINCP1)
       Real ehadpxb1(NBINX7),ehadpxb2(NBINX8),ehadpxb3(NBINX9)
       Real ehadpetf1(NBINCFL),ehadpetf2(NBINCFL),ehadpetf3(NBINCFL)
       Real ehadpetb1(NBINCBL),ehadpetb2(NBINCBL),ehadpetb3(NBINCBL)
*
       Real ehadmq2hi(NBINQ2)
       Real ehadmksi1(NBINXI7),ehadmksi2(NBINXI8),ehadmksi3(NBINXI9)
       Real ehadmet1(NBINET7),ehadmet2(NBINET8),ehadmet3(NBINET9)
       Real ehadmmj1(NBINM21),ehadmmj2(NBINM21),ehadmmj3(NBINM21)
       Real ehadmetap1(NBINCP),ehadmetap2(NBINCP),ehadmetap3(NBINCP)
       Real ehadmetep1(NBINCP1),ehadmetep2(NBINCP1),ehadmetep3(NBINCP1)
       Real ehadmxb1(NBINX7),ehadmxb2(NBINX8),ehadmxb3(NBINX9)
       Real ehadmetf1(NBINCFL),ehadmetf2(NBINCFL),ehadmetf3(NBINCFL)
       Real ehadmetb1(NBINCBL),ehadmetb2(NBINCBL),ehadmetb3(NBINCBL)
*
       Real eemmq2hi(NBINQ2)
       Real eemmksi1(NBINXI7),eemmksi2(NBINXI8),eemmksi3(NBINXI9)
       Real eemmet1(NBINET7),eemmet2(NBINET8),eemmet3(NBINET9)
       Real eemmmj1(NBINM21),eemmmj2(NBINM21),eemmmj3(NBINM21)
       Real eemmetap1(NBINCP),eemmetap2(NBINCP),eemmetap3(NBINCP)
       Real eemmetep1(NBINCP1),eemmetep2(NBINCP1),eemmetep3(NBINCP1)
       Real eemmxb1(NBINX7),eemmxb2(NBINX8),eemmxb3(NBINX9)
       Real eemmetf1(NBINCFL),eemmetf2(NBINCFL),eemmetf3(NBINCFL)
       Real eemmetb1(NBINCBL),eemmetb2(NBINCBL),eemmetb3(NBINCBL)
*
       Real eempq2hi(NBINQ2)
       Real eempksi1(NBINXI7),eempksi2(NBINXI8),eempksi3(NBINXI9)
       Real eempet1(NBINET7),eempet2(NBINET8),eempet3(NBINET9)
       Real eempmj1(NBINM21),eempmj2(NBINM21),eempmj3(NBINM21)
       Real eempetap1(NBINCP),eempetap2(NBINCP),eempetap3(NBINCP)
       Real eempetep1(NBINCP1),eempetep2(NBINCP1),eempetep3(NBINCP1)
       Real eempxb1(NBINX7),eempxb2(NBINX8),eempxb3(NBINX9)
       Real eempetf1(NBINCFL),eempetf2(NBINCFL),eempetf3(NBINCFL)
       Real eempetb1(NBINCBL),eempetb2(NBINCBL),eempetb3(NBINCBL)
 
       Data sigq2hi/12.43,12.39,12.96,11.49,11.28,11.12,8.61,7.10/
*                dq2/ksi bin 1 9-13
       Data sigksi1/6.01, 7.50, 5.23, 5.17, 4.81/
*                dq2/ksi bin 2 14-18
       Data sigksi2/5.18, 7.15, 5.93, 6.93, 5.78/
*                dq2/ksi bin 3 19-22
       Data sigksi3/5.47, 6.39, 7.63, 6.90/
*                dq2/dEt bin 1 23-36
       Data siget1/14.50,7.96, 4.48, 1.92/
*                dq2/dEt bin 2 27-30
       Data siget2/13.95,9.65, 4.73, 2.87/
*                dq2/dEt bin 3 31-34
       Data siget3/11.42,6.99, 5.14, 3.20/
*                dq2/Mjj bin 1 35-36
       Data sigmj1/7.24,11.15,7.59, 2.98/
*                dq2/Mjj bin 2 39-42
       Data sigmj2/5.93,12.55,8.91, 4.19/
*                dq2/Mjj bin 3 43-46
       Data sigmj3/4.99, 8.89,8.44, 4.29/
*                dq2/etap bin 1 47-51
       Data sigetap1/6.93, 6.57,4.95, 5.46, 5.22/
*                dq2/etap bin 2 52-56
       Data sigetap2/7.35, 6.39,5.44, 6.34, 5.85/
*                dq2/etap bin 3 57-61
       Data sigetap3/5.93, 5.91,3.99,5.71, 5.09/
*                det/etap bin 1 62-65
       Data sigetep1/9.38,10.68,10.81,13.19/
*                det/etap bin 2 66-69
       Data sigetep2/6.12, 7.96, 6.93, 6.29/
*                det/etap bin 3 70-73
       Data sigetep3/4.59, 3.87, 4.98, 1.77/
*                dq2/xbj bin 1 74-77
       Data sigxb1/6.84, 8.19, 7.65, 5.84/
*                dq2/xbj bin 2 78-81
       Data sigxb2/6.84,8.19, 7.65, 5.84/
*                dq2/xbj bin 3 82-85
       Data sigxb3/6.51, 8.43, 9.95, 7.27/
*                dq2/etafwd bin 1 86-90
       Data sigetf1/0.40,10.55,7.77,5.81,4.18/
*                dq2/etafwd bin 2 91-93
       Data sigetf2/0.29,10.41,9.08,6.76,4.75/
*                dq2/etafwd bin 3 96-100
       Data sigetf3/0.00,6.88, 8.16,7.21,4.66/
*                dq2/etaback bin 1 101-106
       Data sigetb1/3.577,7.30,9.51,0.05,1.83,0.65/
*                dq2/etaback bin 2 107-112
       Data sigetb2/3.95,6.11,10.65,7.65,2.78,0.38/
*                dq2/etaback bin 3 113-118
       Data sigetb3/.90,4.03,8.65,8.10,3.61,0.79/
*
*          stat error data
       Data estdq2hi/5.0,5.0,5.2,5.4,5.7,5.8,6.4,6.8/
*                dq2/ksi bin 1 9-13
       Data estdksi1/7.7, 6.5, 7.5, 7.6, 8.1/
*                dq2/ksi bin 2 14-18
       Data estdksi2/8.2, 7.2, 7.9, 7.2, 7.6/
*                dq2/ksi bin 3 19-22
       Data estdksi3/ 8.2, 7.6, 6.9, 6.9/
*                dq2/dEt bin 1 23-36
       Data estdet1/4.7,6.2, 8.3, 12.8/
*                dq2/dEt bin 2 27-30
       Data estdet2/5.1,6.1, 8.4, 10.8/
*                dq2/dEt bin 3 31-34
       Data estdet3/5.8,7.1, 8.3, 9.6/
*                dq2/Mjj bin 1 35-36
       Data estdmj1/6.4,5.5,6.5, 10.3/
*                dq2/Mjj bin 2 39-42
       Data estdmj2/7.2,5.5,6.5, 9.2/
*                dq2/Mjj bin 3 43-46
       Data estdmj3/8.1, 6.6,6.8, 8.9/
*                dq2/etap bin 1 47-51
       Data estdetap1/6.8, 6.9,8.1, 7.5, 8.0/
*                dq2/etap bin 2 52-56
       Data estdetap2/7.0, 7.4,7.8, 7.5, 8.2/
*                dq2/etap bin 3 57-61
       Data estdetap3/7.7, 7.6,9.1,7.9, 8.9/
*                det/etap bin 1 62-65
       Data estdetep1/6.1,5.7,5.6,5.3/
*                det/etap bin 2 66-69
       Data estdetep2/7.4, 6.5, 7.0, 7.7/
*                det/etap bin 3 70-73
       Data estdetep3/8.6, 9.0, 8.1, 13.1/
*                dq2/xbj bin 1 74-77
       Data estdxb1/6.8, 6.1, 6.4, 7.4/
*                dq2/xbj bin 2 78-81
       Data estdxb2/7.3,6.4, 6.3, 7.0/
*                dq2/xbj bin 3 82-85
       Data estdxb3/7.1, 7.0, 7.2, 7.9/
*                dq2/etafwd bin 1 86-90
       Data estdetf1/24.3,6.1,6.3,6.9,7.6/
*                dq2/etafwd bin 2 91-93
       Data estdetf2/35.4,6.3,6.2,7.0,7.8/
*                dq2/etafwd bin 3 96-100
       Data estdetf3/0.00,7.8, 6.8,6.8,7.8/
*                dq2/etaback bin 1 101-106
       Data estdetb1/9.8,7.0,6.2,7.0,9.8,14.9/
*                dq2/etaback bin 2 107-112
       Data estdetb2/9.7,8.0,6.1,6.8,9.2,20.5/
*                dq2/etaback bin 3 113-118
       Data estdetb3/13.4,9.7,7.1,6.9,8.5,14.3/
*
*          stat error correction factor
*
       Data estcq2hi/2.5,2.2,2.3,2.0,2.2,2.2,2.6,2.8/
*                dq2/ksi bin 1 9-13
       Data estcksi1/3.9, 3.1, 3.3, 3.2, 4.0/
*                dq2/ksi bin 2 14-18
       Data estcksi2/2.9, 3.2, 3.5, 3.2, 2.7/
*                dq2/ksi bin 3 19-22
       Data estcksi3/3.4, 3.2, 3.0, 2.6/
*                dq2/dEt bin 1 23-36
       Data estcet1/  2.3,2.7, 3.7, 5.5/
*                dq2/dEt bin 2 27-30
       Data estcet2/ 2.1,2.7, 2.8, 3.7/
*                dq2/dEt bin 3 31-34
       Data estcet3/ 2.9,2.8, 3.2, 2.7/
*                dq2/Mjj bin 1 35-36
       Data estcmj1/ 2.6,2.9,3.2, 4.6/
*                dq2/Mjj bin 2 39-42
       Data estcmj2/ 2.2,2.7,2.9, 3.7/
*                dq2/Mjj bin 3 43-46
       Data estcmj3/ 3.0, 3.1,3.2, 3.2/
*                dq2/etap bin 1 47-51
       Data estcetap1/ 3.1, 3.2,3.6, 3.2, 4.6/
*                dq2/etap bin 2 52-56
       Data estcetap2/2.8, 2.8,2.7, 3.0, 4.2/
*                dq2/etap bin 3 57-61
       Data estcetap3/3.0, 3.0,3.0,3.1, 4.7/
*                det/etap bin 1 62-65
       Data estcetep1/2.7,2.6,2.2,3.0/
*                det/etap bin 2 66-69
       Data estcetep2/2.9, 2.7, 2.7, 3.9/
*                det/etap bin 3 70-73
       Data estcetep3/3.7, 2.9, 3.0, 4.1/
*                dq2/xbj bin 1 74-77
       Data estcxb1/ 3.1, 2.5, 3.0, 3.6/
*                dq2/xbj bin 2 78-81
       Data estcxb2/2.9,2.5, 2.4, 3.1/
*                dq2/xbj bin 3 82-85
       Data estcxb3/ 2.6, 2.7, 3.0, 3.7/
*                dq2/etafwd bin 1 86-90
       Data estcetf1/ 7.8,3.9,2.7,2.5,2.4/
*                dq2/etafwd bin 2 91-93
       Data estcetf2/19.6,3.2,2.4,2.5,2.2/
*                dq2/etafwd bin 3 96-100
       Data estcetf3/19.5,4.4, 3.1,2.4,2.1/
*                dq2/etaback bin 1 101-106
       Data estcetb1/5.2,3.8,3.7,2.9,1.7,1.8/
*                dq2/etaback bin 2 107-112
       Data estcetb2/4.4,3.4,3.0,2.8,2.0,1.5/
*                dq2/etaback bin 3 113-118
       Data estcetb3/4.5,4.2,4.2,3.3,2.0,1.3/
*
*          syst error correction factor
       Data esycq2hi/0.9,2.1,3.2,2.6,3.8,3.3,1.1,0.6/
*                dq2/ksi bin 1 9-13
       Data esycksi1/-1.0, 1.8, 2.3, 2.3, 2.7/
*                dq2/ksi bin 2 14-18
       Data esycksi2/3.2, 1.7, 2.6, 1.8, 4.1/
*                dq2/ksi bin 3 19-22
       Data esycksi3/2.4, 1.9, 1.0, 2.5/
*                dq2/dEt bin 1 23-36
       Data esycet1/1.1,2.8, 2.7, 2.3/
*                dq2/dEt bin 2 27-30
       Data esycet2/3.7,1.3, 2.5, 5.8/
*                dq2/dEt bin 3 31-34
       Data esycet3/1.2,3.2, 1.5, 1.4/
*                dq2/Mjj bin 1 35-36
       Data esycmj1/-0.2,1.6,2.4, 2.8/
*                dq2/Mjj bin 2 39-42
       Data esycmj2/ 2.2,0.9,3.9, 2.9/
*                dq2/Mjj bin 3 43-46
       Data esycmj3/-2.2, 0.0,1.0, 2.4/
*                dq2/etap bin 1 47-51
       Data esycetap1/3.1, 4.0,-1.8,-1.2, 4.0/
*                dq2/etap bin 2 52-56
       Data esycetap2/4.6, 2.7,3.2,-0.7, 3.0/
*                dq2/etap bin 3 57-61
       Data esycetap3/1.1, 2.2,-0.4,1.3, 3.8/
*                det/etap bin 1 62-65
       Data esycetep1/3.0,2.2,-0.2,2.3/
*                det/etap bin 2 66-69
       Data esycetep2/33.5, 4.2,-1.4, 2.6/
*                det/etap bin 3 70-73
       Data esycetep3/32.1, 3.0, 1.3, 5.5/
*                dq2/xbj bin 1 74-77
       Data esycxb1/0.9, 1.0, 2.1, 4.2/
*                dq2/xbj bin 2 78-81
       Data esycxb2/1.5,4.3, 3.0, 3.1/
*                dq2/xbj bin 3 82-85
       Data esycxb3/3.2, 3.3,0.9,1.0/
*                dq2/etafwd bin 1 86-90
       Data esycetf1/18.4,0.2,2.1,2.0,5.6/
*                dq2/etafwd bin 2 91-93
       Data esycetf2/-27.0,3.1,2.0,2.9,6.6/
*                dq2/etafwd bin 3 96-100
       Data esycetf3/-43.3,0.6, -0.1,1.4,6.2/
*                dq2/etaback bin 1 101-106
       Data esycetb1/ 4.1,-0.2,0.7,-0.6,-1.8,11.0/
*                dq2/etaback bin 2 107-112
       Data esycetb2/-1.2,3.6,1.5,1.2,0.8,7.1/
*                dq2/etaback bin 3 113-118
       Data esycetb3/1.5,-1.4,1.0,-0.3,0.0,3.1/
*
*          hadronic energy scale error plus
       Data ehadpq2hi/ 6.8, 6.8, 7.8, 6.8, 6.8, 6.8, 9.0, 7.8/
*                dq2/ksi bin 1 9-13
       Data ehadpksi1/13.6, 7.4,  6.8, 6.8, 9.0/
*                dq2/ksi bin 2 14-18
       Data ehadpksi2/13.8, 6.8, 11.8, 6.8,8.8/
*                dq2/ksi bin 3 19-22
       Data ehadpksi3/6.8, 9.4,  6.8, 7.8/
*                dq2/dEt bin 1 23-36
       Data ehadpet1/6.8,12.3,  8.0,29.1/
*                dq2/dEt bin 2 27-30
       Data ehadpet2/6.8, 8.5, 12.2, 9.0/
*                dq2/dEt bin 3 31-34
       Data ehadpet3/ 6.8, 6.8, 8.8, 19.1/
*                dq2/Mjj bin 1 35-38
       Data ehadpmj1/8.9, 6.8,10.3, 16.2/
*                dq2/Mjj bin 2 39-42
       Data ehadpmj2/6.8, 6.8, 6.8, 11.7/
*                dq2/Mjj bin 3 43-46
       Data ehadpmj3/6.8,13.0, 6.8, 18.4/
*                dq2/etap bin 1 47-51
       Data ehadpetap1/8.0, 6.8, 6.8,  6.8, 9.8/
*                dq2/etap bin 2 52-56
       Data ehadpetap2/6.8, 6.8, 6.8,  9.3, 6.8/
*                dq2/etap bin 3 57-61
       Data ehadpetap3/7.4, 6.8, 6.8,  7.2,16.6/
*                det/etap bin 1 62-65
       Data ehadpetep1/6.8, 6.8, 6.8,  6.8/
*                det/etap bin 2 66-69
       Data ehadpetep2/9.7, 6.8, 6.8,  9.6/
*                det/etap bin 3 70-73
       Data ehadpetep3/14.2,15.0, 9.7, 33.7/
*                dq2/xbj bin 1 74-77
       Data ehadpxb1/6.8, 8.9, 7.2, 8.3/
*                dq2/xbj bin 2 78-81
       Data ehadpxb2/7.5, 6.8, 8.1,  6.8/
*                dq2/xbj bin 3 82-85
       Data ehadpxb3/7.4,7.4, 7.0, 9.3/
*                dq2/etafwd bin 1 86-90
       Data ehadpetf1/14.4, 8.3, 6.8,  6.8, 12.4/
*                dq2/etafwd bin 2 91-95
       Data ehadpetf2/13.5, 6.8, 6.8,  6.8,  8.5/
*                dq2/etafwd bin 3 96-100
       Data ehadpetf3/6.8, 6.8, 6.8, 11.5,  7.6/
*                dq2/etaback bin 1 101-106
       Data ehadpetb1/11.5, 8.5, 6.8, 6.8, 6.8, 21.3/
*                dq2/etaback bin 2 107-112
       Data ehadpetb2/6.8, 6.8, 8.1, 7.4, 6.8, 23.8/
*                dq2/etaback bin 3 113-118
       Data ehadpetb3/7.5, 9.7, 9.6, 8.2, 6.8, 6.8/
*
*          hadronic energy scale error plus
       Data ehadmq2hi/-6.2,-6.0,-8.6,-6.8,-6.1,-6.0,-6.9,-6.0/
*                dq2/ksi bin 1 9-13
       Data ehadmksi1/-6.0,-6.0,-10.9,-6.0,-10.2/
*                dq2/ksi bin 2 14-18
       Data ehadmksi2/ -6.0,-6.0,-9.7,-6.1,-8.9/
*                dq2/ksi bin 3 19-22
       Data ehadmksi3/-6.0,-8.1,-8.9,-6.0/
*                dq2/dEt bin 1 23-36
       Data ehadmet1/-6.0,-6.9,-9.0,-17.1/
*                dq2/dEt bin 2 27-30
       Data ehadmet2/ -6.0,-6.8,-6.0,-16.0/
*                dq2/dEt bin 3 31-34
       Data ehadmet3/-6.0,-6.0,-12.0,-13.1/
*                dq2/Mjj bin 1 35-38
       Data ehadmmj1/-6.0,-6.0,-6.0,-15.9/
*                dq2/Mjj bin 2 39-42
       Data ehadmmj2/-8.3,-6.0,-6.0,-15.5/
*                dq2/Mjj bin 3 43-46
       Data ehadmmj3/-12.1,-6.0,-6.0,-15.8/
*                dq2/etap bin 1 47-51
       Data ehadmetap1/-7.6,-7.7,-7.4, -6.0,-6.0/
*                dq2/etap bin 2 52-56
       Data ehadmetap2/-6.0,-6.0,-11.4, -6.0,-10.1/
*                dq2/etap bin 3 57-61
       Data ehadmetap3/-6.0,-6.0,-12.9, -6.0,-6.0/
*                det/etap bin 1 62-65
       Data ehadmetep1/-7.2,-6.0,-7.9, -6.0/
*                det/etap bin 2 66-69
       Data ehadmetep2/-6.0, -6.0,-6.0,-10.4/
*                det/etap bin 3 70-73
       Data ehadmetep3/-13.6,-12.6,-11.8,-12.1/
*                dq2/xbj bin 1 74-77
       Data ehadmxb1/-6.0,-6.0, -8.1,-9.8/
*                dq2/xbj bin 2 78-81
       Data ehadmxb2/-6.0,-7.4,-6.0,-10.8/
*                dq2/xbj bin 3 82-85
       Data ehadmxb3/-6.0,-6.0,-7.5, -6.0/
*                dq2/etafwd bin 1 86-90
       Data ehadmetf1/-22.6,-12.4,-6.0, -6.0,-6.0/
*                dq2/etafwd bin 2 91-95
       Data ehadmetf2/-25.6,-8.4,-7.2, -6.9, -6.0/
*                dq2/etafwd bin 3 96-100
       Data ehadmetf3/-6.0,-6.7,-8.3,-6.0, -6.0/
*                dq2/etaback bin 1 101-106
       Data ehadmetb1/-9.0,-7.2,-6.9,-6.0,-6.0, -6.0/
*                dq2/etaback bin 2 107-112
       Data ehadmetb2/-7.5,-6.2,-6.0,-10.7,-7.2,-6.0/
*                dq2/etaback bin 3 113-118
       Data ehadmetb3/-7.5,-6.8,-6.0,-9.8,-6.0,-6.0/
*
*          electromagnetic energy scale plus
       Data eempq2hi/-4.7,-9.5,-2.4,-3.0,-2.4,-5.9,-2.4,-2.4/
*                dq2/ksi bin 1 9-13
       Data  eempksi1/-2.4,-2.4,-7.0,-10.4,-9.1/
*                dq2/ksi bin 2 14-18
       Data  eempksi2/-2.4,-6.6,-2.4,-9.6,-2.4/
*                dq2/ksi bin 3 19-22
       Data  eempksi3/-2.6,-2.4,-12.2,-2.4/
*                dq2/dEt bin 1 23-36
       Data  eempet1/-8.4,-2.4,-2.4,-2.4/
*                dq2/dEt bin 2 27-30
       Data  eempet2/-2.4,-11.7,-2.4,-4.7/
*                dq2/dEt bin 3 31-34
       Data  eempet3/-2.4,-2.8,-2.4,-2.4/
*                dq2/Mjj bin 1 35-38
       Data  eempmj1/-11.8,-2.4,-2.4,-2.4/
*                dq2/Mjj bin 2 39-42
       Data  eempmj2/-2.4,-13.0,-2.4,-2.4/
*                dq2/Mjj bin 3 43-46
       Data  eempmj3/-18.9,-2.4,-3.1,-2.4/
*                dq2/etap bin 1 47-51
       Data  eempetap1/-5.8,-4.8,-2.4, -3.4,-6.9/
*                dq2/etap bin 2 52-56
       Data  eempetap2/-5.3,-2.4,-12.5, -8.0,-2.4/
*                dq2/etap bin 3 57-61
       Data  eempetap3/-2.4,-17.2,-2.4, -16.4,-2.4/
*                det/etap bin 1 62-65
       Data  eempetep1/-4.9,-7.8,-8.0, -2.4/
*                det/etap bin 2 66-69
       Data  eempetep2/-2.9, -6.2,-4.6,-2.4/
*                det/etap bin 3 70-73
       Data  eempetep3/-2.8,-2.4,-2.4,-2.4/
*                dq2/xbj bin 1 74-77
       Data  eempxb1/-17.0,-2.4, -10.3,-4.8/
*                dq2/xbj bin 2 78-81
       Data  eempxb2/-9.2,-2.4,-2.4,-4.2/
*                dq2/xbj bin 3 82-85
       Data  eempxb3/ -2.4,-5.3,-2.4, -2.4/
*                dq2/etafwd bin 1 86-90
       Data  eempetf1/-2.4,-2.4,-2.4,-12.2, -10.2/
*                dq2/etafwd bin 2 91-95
       Data  eempetf2/ -2.4,-2.4,-2.4,-8.6, -3.8/
*                dq2/etafwd bin 3 96-100
       Data  eempetf3/-2.4,-2.4,-4.0,-2.4,-5.6/
*                dq2/etaback bin 1 101-106
       Data  eempetb1/-2.4,-2.4,-2.4,-15.0,-16.6, -16.4/
*                dq2/etaback bin 2 107-112
       Data  eempetb2/-2.4,-2.4,-3.5,-10.9,-23.5,-2.4/
*                dq2/etaback bin 3 113-118
       Data  eempetb3/-2.4,-2.4,-2.4,-13.2,-11.0,-22.2/
*                dq2/xbj 4-7
*          electromagnetic energy scale minus
       Data eemmq2hi/7.9,6.3,7.6,6.3,6.3,7.0,9.4,10.6/
*                dq2/ksi bin 1 9-13
       Data eemmksi1/6.3,-17.0,6.3,8.6,6.3/
*                dq2/ksi bin 2 14-18
       Data eemmksi2/6.3,6.3,6.3,15.5,9.1/
*                dq2/ksi bin 3 19-22
       Data eemmksi3/9.8,6.3,9.3,18.3/
*                dq2/dEt bin 1 23-36
       Data eemmet1/6.3,11.2,6.3,6.3/
*                dq2/dEt bin 2 27-30
       Data eemmet2/6.3,12.1,6.3,6.3/
*                dq2/dEt bin 3 31-34
       Data eemmet3/6.7,12.4,9.4,7.2/
*                dq2/Mjj bin 1 35-38
       Data eemmmj1/7.6,8.7,6.3,6.3/
*                dq2/Mjj bin 2 39-42
       Data eemmmj2/6.3, 6.3, 6.6, 6.3/
*                dq2/Mjj bin 3 43-46
       Data eemmmj3/6.3,15.1,7.2,6.3/
*                dq2/etap bin 1 47-51
       Data eemmetap1/6.3,7.8,6.3, 13.5,6.3/
*                dq2/etap bin 2 52-56
       Data eemmetap2/6.3,6.3,8.8, 6.3,6.3/
*                dq2/etap bin 3 57-61
       Data eemmetap3/6.3,15.6,19.4, 6.3,20.6/
*                det/etap bin 1 62-65
       Data eemmetep1/6.3,10.7,8.5, 2.4/
*                det/etap bin 2 66-69
       Data eemmetep2/6.8,15.6,6.5,10.0/
*                det/etap bin 3 70-73
       Data eemmetep3/6.3,10.0,6.3,7.5/
*                dq2/xbj bin 1 74-77
       Data eemmxb1/6.3,13.9, 6.3,10.2/
*                dq2/xbj bin 2 78-81
       Data eemmxb2/8.0,6.3,19.9,6.3/
*                dq2/xbj bin 3 82-85
       Data eemmxb3/7.2,6.3,15.1,6.3/
*                dq2/etafwd bin 1 86-90
       Data eemmetf1/6.3,6.3,10.5,10.3, 11.8/
*                dq2/etafwd bin 2 91-95
       Data eemmetf2/6.3,6.3,6.3,11.0, 19.8/
*                dq2/etafwd bin 3 96-100
       Data eemmetf3/6.3,6.3,6.3,16.0,15.3/
*                dq2/etaback bin 1 101-106
       Data eemmetb1/6.3,6.3,6.3,13.6,24.6, 34.0/
*                dq2/etaback bin 2 107-112
       Data eemmetb2/6.3,6.3,6.3,8.5,17.7,123.0/
*                dq2/etaback bin 3 113-118
       Data eemmetb3/6.3,6.3,6.3,13.0,27.5,36.3/
*
*********************************************************************
*
*                      Initialization
*
*********************************************************************
*
      IF (iflag.eq.1) then
*
*
*      Initialisation: The following MUST always be done
*      (i) make subdirectory in PAWC
*      (i) make subdirectory in o/p file
*
       write(6,*) ' %%%%%%%%%%%%%%%% '
*
       Call hcdir('//PAWC',' ')
       call hmdir(xxxx,'S')
       Call hcdir('//HISTO',' ')
       call hmdir(xxxx,'S')
*
       if (lp) then
        write(6,*) rout,'...start booking ! '
        write(6,*) rout,' offset= ',ioff
       endif
*
*      LOW Q2
*
       IM = 10000+ioff
       IM1= ioff
       Do k=0,nq2bin
        call hbook1(IM+k,'[s]?dijet!',1,0.5,1.5,0)
       enddo
*
       id=100
       NQ2=NBINQ2LO+NBINQ2+2
*
       Do i=1,NQ2
        if (i.le.NBINQ2LO+1) then
         XQ2(i)=XBINQ2LO(i)
        else
         XQ2(i)=XBINQ2(i-(NBINQ2LO+1))
        endif
*
        if (lp) write(6,*) i,' xq2= ',XQ2(i)
       enddo
*
       Do i=1,nq2bini-1
        Q2BINIW(i)=Q2BINI(i+1)-Q2BINI(i)
        if (lp) write(6,*) i,' q2biniw= ',Q2BINIW(i)
       enddo
*
       Do i=1,nq2bin-1
        Q2BINW(i)=Q2BIN(i+1)-Q2BIN(i)
        if (lp) write(6,*) i,' q2binw= ',Q2BINW(i)
       enddo
*
       call hbookb(IM+id+1,'d[s]/dQ^2! / GeV^2!  ',NQ2BINI-1,Q2BINI,0)
       call hbarx(IM+id+1)
       call hbook1(IM1+id+1,'d[s]/dQ^2!/GeV^2!',30,Q2BINI(1),100.,0)
       call hbarx(IM1+id+1)
       call hbookb(IM+id+2,'d[s]/dQ^2! ! SumEtgt40',NQ2BIN-1,Q2BIN,0)
       call hbarx(IM+id+2)
       call hbook1(IM1+id+2,'d[s]/dQ^2! SumEtgt40',30,Q2BIN(1),100.,0)
       call hbarx(IM1+id+2)
*
       call hbookb(IM+id,'d[s]/dQ^2! / GeV^2!      ',NQ2-1,XQ2  ,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+id),'d[s]/dQ^2! / GeV^2! ',NQ2-1,XQ2  ,0)
       call hbookb(-1*(IM+1000+id),'d[s]/dQ^2! / GeV^2! systm',
     + NQ2-1,XQ2  ,0)
       call hbookb(-1*(IM+2000+id),'d[s]/dQ^2! / GeV^2! systp',
     + NQ2-1,XQ2  ,0)
*
       do i=1,NQ2-1
        if (i.le.NBINQ2LO) then
         j=i
         sigq2(i)=siglo(j)
         esigq2stat(i)=  sqrt((estdsiglo(j)/100.*siglo(j))**2 +
     +                        (estcsiglo(j)/100.*siglo(j))**2 )
         esigq2sym(i)=  sqrt((esycsiglo (j)/100.*siglo(j))**2 +
     +                       (ehadpsiglo(j)/100.*siglo(j))**2+
     +                       (eempsiglo (j)/100.*siglo(j))**2)
         esigq2syp(i)=  sqrt((esycsiglo (j)/100.*siglo(j))**2 +
     +                       (ehadpsiglo(j)/100.*siglo(j))**2+
     +                       (eempsiglo (j)/100.*siglo(j))**2)
        elseif (i.eq.NBINQ2LO+1) then
         sigq2(i)=0.
         esigq2stat(i) = 0.
         esigq2sym(i)  = 0.
         esigq2syp(i)  = 0.
        else
         j=i+1-NBINQ2LO
         sigq2(i)=sigq2hi(j)
         esigq2stat(i) = sqrt((estdq2hi(j)/100.*sigq2hi(j))**2 +
     +                        (estcq2hi(j)/100.*sigq2hi(j))**2 )
         esigq2sym(i)=  sqrt((esycq2hi(j)/100.*sigq2hi(j))**2 +
     +                       (ehadpq2hi(j)/100.*sigq2hi(j))**2+
     +                       (eempq2hi(j)/100.*sigq2hi(j))**2)
         esigq2syp(i)  =sqrt((esycq2hi(j)/100.*sigq2hi(j))**2 +
     +                       (ehadpq2hi(j)/100.*sigq2hi(j))**2+
     +                       (eempq2hi(j)/100.*sigq2hi(j))**2)
        endif
*
        esigm(i)=sqrt((esigq2stat(i)**2+esigq2sym(i)**2))
        esigp(i)=sqrt((esigq2stat(i)**2+esigq2syp(i)**2))
*
C        write(6,*) i,' sigq2= ',sigq2(i)
C        write(6,*) i,' esigm= ',esigm(i)
C        write(6,*) i,' esigp= ',esigp(i)
*
       enddo
*
       call hpak (-1*(IM+ID) ,sigq2)
       call hpak (-1*(IM+1000+ID),sigq2)
       call hpak (-1*(IM+2000+ID),sigq2)
       call hpake(-1*(IM+ID ),esigq2stat)
       call hpake(-1*(IM+1000+ID),esigm)
       call hpake(-1*(IM+2000+ID),esigp)
*       norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.,1)
       call HZHINRM(-1*(IM+1000+ID),0,1.,1)
       call HZHINRM(-1*(IM+2000+ID),0,1.,1)
*
       id=110
       call hbookb(IM+ID,'d^2![s]/dQ^2! d[x] ',
     +     NBINXILO  ,XBINXILO  ,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),'d^2![s]/dQ^2! d[x] ',
     +     NBINXILO  ,XBINXILO  ,0)
       call hbookb(-1*(IM+1000+ID),'d^2![s]/dQ^2! d[x] sigm ',
     +     NBINXILO  ,XBINXILO  ,0)
       call hbookb(-1*(IM+2000+ID),'d^2![s]/dQ^2! d[x] sigp',
     +     NBINXILO  ,XBINXILO  ,0)
*
       do i=1,NBINXILO
        j=7+i
        sigkslo(i)=siglo(j)
        esigksstatlo(i) = sqrt((estdsiglo(j)/100.*siglo(j))**2 +
     +                       (estcsiglo(j)/100.*siglo(j))**2 )
        esigkssymlo(i)=sqrt((esycsiglo (j)/100.*siglo(j))**2 +
     +                      (ehadpsiglo(j)/100.*siglo(j))**2+
     +                      (eempsiglo (j)/100.*siglo(j))**2)
        esigkssyplo(i)=sqrt((esycsiglo (j)/100.*siglo(j))**2 +
     +                      (ehadpsiglo(j)/100.*siglo(j))**2+
     +                      (eempsiglo (j)/100.*siglo(j))**2)
        esigmkslo(i)=sqrt((esigksstatlo(i)**2+esigkssymlo(i)**2))
        esigpkslo(i)=sqrt((esigksstatlo(i)**2+esigkssyplo(i)**2))
*
       enddo
*
       call hpak (-1*(IM+ID) ,sigkslo)
       call hpak (-1*(IM+1000+ID),sigkslo)
       call hpak (-1*(IM+2000+ID),sigkslo)
       call hpake(-1*(IM+ID),esigksstatlo)
       call hpake(-1*(IM+1000+ID),esigmkslo)
       call hpake(-1*(IM+2000+ID),esigpkslo)
*       norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BIN0,1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BIN0,1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BIN0,1)
*
       id=120
       call hbookb(IM+ID,'d^2![s]/dQ^2! dE?t,Breit!',
     +     NBINETLO ,XBINETLO,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),'d^2![s]/dQ^2! dE?t,Breit!',
     +     NBINETLO ,XBINETLO,0)
       call hbookb(-1*(IM+1000+ID),'d^2![s]/dQ^2! dE?t,Breit!',
     +     NBINETLO ,XBINETLO,0)
       call hbookb(-1*(IM+2000+ID),'d^2![s]/dQ^2! dE?t,Breit!',
     +     NBINETLO ,XBINETLO,0)
*
       do i=1,NBINETLO
        j=16+i
        sigetlo(i)=siglo(j)
        esigetstatlo(i) = sqrt((estdsiglo(j)/100.*siglo(j))**2 +
     +                       (estcsiglo(j)/100.*siglo(j))**2 )
        esigetsymlo(i)=sqrt((esycsiglo (j)/100.*siglo(j))**2 +
     +                      (ehadpsiglo(j)/100.*siglo(j))**2+
     +                      (eempsiglo (j)/100.*siglo(j))**2)
        esigetsyplo(i)=sqrt((esycsiglo (j)/100.*siglo(j))**2 +
     +                      (ehadpsiglo(j)/100.*siglo(j))**2+
     +                      (eempsiglo (j)/100.*siglo(j))**2)
        esigmetlo(i)=sqrt((esigetstatlo(i)**2+esigetsymlo(i)**2))
        esigpetlo(i)=sqrt((esigetstatlo(i)**2+esigetsyplo(i)**2))
*
       enddo
*
       call hpak (-1*(IM+ID) ,sigetlo)
       call hpak (-1*(IM+1000+ID),sigetlo)
       call hpak (-1*(IM+2000+ID),sigetlo)
       call hpake(-1*(IM+ID ),esigetstatlo)
       call hpake(-1*(IM+1000+ID),esigmetlo)
       call hpake(-1*(IM+2000+ID),esigpetlo)
*       norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BIN0,1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BIN0,1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BIN0,1)
*
       id=130
       call hbookb(IM+ID,'d^2![s]/dQ^2! dm?jj! / GeV',
     +     NBINM2LO  ,XBINM2LO  ,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),'d^2![s]/dQ^2! dm?jj! / GeV',
     +     NBINM2LO  ,XBINM2LO  ,0)
       call hbookb(-1*(IM+1000+ID),'d^2![s]/dQ^2! dm?jj! / GeV',
     +     NBINM2LO  ,XBINM2LO  ,0)
       call hbookb(-1*(IM+2000+ID),'d^2![s]/dQ^2! dm?jj! / GeV',
     +     NBINM2LO  ,XBINM2LO  ,0)
*
       do i=1,NBINM2LO
        j=20+i
        sigmjlo(i)=siglo(j)
        esigmjstatlo(i) = sqrt((estdsiglo(j)/100.*siglo(j))**2 +
     +                       (estcsiglo(j)/100.*siglo(j))**2 )
        esigmjsymlo(i)=sqrt((esycsiglo (j)/100.*siglo(j))**2 +
     +                      (ehadpsiglo(j)/100.*siglo(j))**2+
     +                      (eempsiglo (j)/100.*siglo(j))**2)
        esigmjsyplo(i)=sqrt((esycsiglo (j)/100.*siglo(j))**2 +
     +                      (ehadpsiglo(j)/100.*siglo(j))**2+
     +                      (eempsiglo (j)/100.*siglo(j))**2)
        esigmmjlo(i)=sqrt((esigmjstatlo(i)**2+esigmjsymlo(i)**2))
        esigpmjlo(i)=sqrt((esigmjstatlo(i)**2+esigmjsyplo(i)**2))
*
       enddo
*
       call hpak (-1*(IM+ID) ,sigmjlo)
       call hpak (-1*(IM+1000+ID),sigmjlo)
       call hpak (-1*(IM+2000+ID),sigmjlo)
       call hpake(-1*(IM+ID),esigmjstatlo)
       call hpake(-1*(IM+1000+ID),esigmmjlo)
       call hpake(-1*(IM+2000+ID),esigpmjlo)
*       norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BIN0,1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BIN0,1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BIN0,1)
*
       id=140
       call hbookb(IM+ID,'d^2![s]/dQ^2! d[c]'''  ,
     +     NBINCPLO  ,XBINCPLO  ,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),'d^2![s]/dQ^2! d[c]'''  ,
     +     NBINCPLO  ,XBINCPLO  ,0)
       call hbookb(-1*(IM+1000+ID),'d^2![s]/dQ^2! d[c]'''  ,
     +     NBINCPLO  ,XBINCPLO  ,0)
       call hbookb(-1*(IM+2000+ID),'d^2![s]/dQ^2! d[c]'''  ,
     +     NBINCPLO  ,XBINCPLO  ,0)
*
       do i=1,NBINCPLO
        j=11+i
        sigeplo(i)=siglo(j)
        esigepstatlo(i) = sqrt((estdsiglo(j)/100.*siglo(j))**2 +
     +                       (estcsiglo(j)/100.*siglo(j))**2 )
        esigepsymlo(i)=sqrt((esycsiglo (j)/100.*siglo(j))**2 +
     +                      (ehadpsiglo(j)/100.*siglo(j))**2+
     +                      (eempsiglo (j)/100.*siglo(j))**2)
        esigepsyplo(i)=sqrt((esycsiglo (j)/100.*siglo(j))**2 +
     +                      (ehadpsiglo(j)/100.*siglo(j))**2+
     +                      (eempsiglo (j)/100.*siglo(j))**2)
        esigmeplo(i)=sqrt((esigepstatlo(i)**2+esigepsymlo(i)**2))
        esigpeplo(i)=sqrt((esigepstatlo(i)**2+esigepsyplo(i)**2))
*
       enddo
*
       call hpak (-1*(IM+ID) ,sigeplo)
       call hpak (-1*(IM+1000+ID),sigeplo)
       call hpak (-1*(IM+2000+ID),sigeplo)
       call hpake(-1*(IM+ID ),esigepstatlo)
       call hpake(-1*(IM+1000+ID),esigmeplo)
       call hpake(-1*(IM+2000+ID),esigpeplo)
*       norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BIN0,1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BIN0,1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BIN0,1)
*
       ID=150
       write(string,'(a)')
     + 'd^2![s] / dEt d[c]'' '
       call hbookb(IM+ID,string,NBINCP1,XBINCP1,0)
*
       id=160
       call hbookb(IM+ID,'d^2![s]/dQ^2! dy'  ,
     +     NBINYLO   ,XBINYLO   ,0)
       call hbarx(IM+id)
*
       id=170
       call hbookb(IM+ID,'d^2![s]/dQ^2! dx?Bj!' ,
     +     NBINXLO   ,XBINXLO   ,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),'d^2![s]/dQ^2! dx?Bj!' ,
     +     NBINXLO   ,XBINXLO   ,0)
       call hbookb(-1*(IM+1000+ID),'d^2![s]/dQ^2! dx?Bj! syst m' ,
     +     NBINXLO   ,XBINXLO   ,0)
       call hbookb(-1*(IM+2000+ID),'d^2![s]/dQ^2! dx?Bj! syst p' ,
     +     NBINXLO   ,XBINXLO   ,0)
*
       do i=1,NBINXLO
        j=3+i
        sigxblo(i)=siglo(j)
        esigxbstatlo(i) = sqrt((estdsiglo(j)/100.*siglo(j))**2 +
     +                       (estcsiglo(j)/100.*siglo(j))**2 )
        esigxbsymlo(i)=sqrt((esycsiglo (j)/100.*siglo(j))**2 +
     +                      (ehadpsiglo(j)/100.*siglo(j))**2+
     +                      (eempsiglo (j)/100.*siglo(j))**2)
        esigxbsyplo(i)=sqrt((esycsiglo (j)/100.*siglo(j))**2 +
     +                      (ehadpsiglo(j)/100.*siglo(j))**2+
     +                      (eempsiglo (j)/100.*siglo(j))**2)
        esigmxblo(i)=sqrt((esigxbstatlo(i)**2+esigxbsymlo(i)**2))
        esigpxblo(i)=sqrt((esigxbstatlo(i)**2+esigxbsyplo(i)**2))
*
       enddo
*
       call hpak (-1*(IM+ID) ,sigxblo)
       call hpak (-1*(IM+1000+ID),sigxblo)
       call hpak (-1*(IM+2000+ID),sigxblo)
       call hpake(-1*(IM+ID ),esigxbstatlo)
       call hpake(-1*(IM+1000+ID),esigmxblo)
       call hpake(-1*(IM+2000+ID),esigpxblo)
*       norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BIN0,1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BIN0,1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BIN0,1)
*
       id=180
       call hbookb(IM+ID,'d^2![s]/dQ^2! dx?p!',
     +     NBINXPLO  ,XBINXPLO  ,0)
       call hbarx(IM+id)
*
       id=190
       call hbookb(IM+ID,'d^2![s]/dQ^2! d[c]?forw,lab!' ,
     +     NBINCFLO ,XBINCFLLO ,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),'d^2![s]/dQ^2! d[c]?forw,lab!' ,
     +     NBINCFLO ,XBINCFLLO ,0)
       call hbookb(-1*(IM+1000+ID),'d^2![s]/dQ^2! d[c]?forw,lab!' ,
     +     NBINCFLO ,XBINCFLLO ,0)
       call hbookb(-1*(IM+2000+ID),'d^2![s]/dQ^2! d[c]?forw,lab!' ,
     +     NBINCFLO ,XBINCFLLO ,0)
*
       do i=1,NBINCFLO
        j=24+i
        sigeflo(i)=siglo(j)
        esigefstatlo(i) = sqrt((estdsiglo(j)/100.*siglo(j))**2 +
     +                       (estcsiglo(j)/100.*siglo(j))**2 )
        esigmjsymlo(i)=sqrt((esycsiglo (j)/100.*siglo(j))**2 +
     +                      (ehadpsiglo(j)/100.*siglo(j))**2+
     +                      (eempsiglo (j)/100.*siglo(j))**2)
        esigefsyplo(i)=sqrt((esycsiglo (j)/100.*siglo(j))**2 +
     +                      (ehadpsiglo(j)/100.*siglo(j))**2+
     +                      (eempsiglo (j)/100.*siglo(j))**2)
        esigmeflo(i)=sqrt((esigefstatlo(i)**2+esigefsymlo(i)**2))
        esigpeflo(i)=sqrt((esigefstatlo(i)**2+esigefsyplo(i)**2))
*
       enddo
*
       call hpak (-1*(IM+ID) ,sigeflo)
       call hpak (-1*(IM+1000+ID),sigeflo)
       call hpak (-1*(IM+2000+ID),sigeflo)
       call hpake(-1*(IM+ID ),esigefstatlo)
       call hpake(-1*(IM+1000+ID),esigmeflo)
       call hpake(-1*(IM+2000+ID),esigpeflo)
*       norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BIN0,1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BIN0,1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BIN0,1)
*
       id=200
       call hbookb(IM+ID,'d^2![s]/dQ^2! d[c]?back,lab!',
     +     NBINCBLLO ,XBINCBLLO ,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),'d^2![s]/dQ^2! d[c]?back,lab!',
     +     NBINCBLLO ,XBINCBLLO ,0)
       call hbookb(-1*(IM+1000+ID),'d^2![s]/dQ^2! d[c]?back,lab!',
     +     NBINCBLLO ,XBINCBLLO ,0)
       call hbookb(-1*(IM+2000+ID),'d^2![s]/dQ^2! d[c]?back,lab!',
     +     NBINCBLLO ,XBINCBLLO ,0)
*
       do i=1,NBINCBLLO
        j=29+i
        sigeblo(i)=siglo(j)
        esigebstatlo(i) = sqrt((estdsiglo(j)/100.*siglo(j))**2 +
     +                       (estcsiglo(j)/100.*siglo(j))**2 )
        esigebsymlo(i)=sqrt((esycsiglo (j)/100.*siglo(j))**2 +
     +                      (ehadpsiglo(j)/100.*siglo(j))**2+
     +                      (eempsiglo (j)/100.*siglo(j))**2)
        esigebsyplo(i)=sqrt((esycsiglo (j)/100.*siglo(j))**2 +
     +                      (ehadpsiglo(j)/100.*siglo(j))**2+
     +                      (eempsiglo (j)/100.*siglo(j))**2)
        esigmeblo(i)=sqrt((esigebstatlo(i)**2+esigebsymlo(i)**2))
        esigpeblo(i)=sqrt((esigebstatlo(i)**2+esigebsyplo(i)**2))
*
       enddo
*
       call hpak (-1*(IM+ID) ,sigeblo)
       call hpak (-1*(IM+1000+ID),sigeblo)
       call hpak (-1*(IM+2000+ID),sigeblo)
       call hpake(-1*(IM+ID ),esigebstatlo)
       call hpake(-1*(IM+1000+ID),esigmeblo)
       call hpake(-1*(IM+2000+ID),esigpeblo)
*       norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BIN0,1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BIN0,1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BIN0,1)
*
       Do k=1,6
*
C        write(6,*) ' book additional histos: k= ',k
*
        write(string,'(a,F5.0,a,F5.0,A)')
     +  'd^2![s] / dQ^2! d[x] (',
     +  q2bin(k),' lt Q^2! lt ',q2bin(k+1),' GeV^2!) '
*
        if (k.eq.1) then
         call hbookb(IM+110+k,string,NBINXI1  ,XBINXI1  ,0)
        else if (k.eq.2) then
         call hbookb(IM+110+k,string,NBINXI1  ,XBINXI2  ,0)
        else if (k.eq.3) then
         call hbookb(IM+110+k,string,NBINXI1  ,XBINXI3  ,0)
        else if (k.eq.4) then
         call hbookb(IM+110+k,string,NBINXI1  ,XBINXI4  ,0)
        else
         call hbookb(IM+110+k,string,NBINXI1  ,XBINXI4  ,0)
        endif
*
        call hbarx(IM+110+k)
        call hbook1(IM1+110+k,string,30,XBINXI(1),XBINXI(NBINXI+1),0)
        call hbarx(IM1+110+k)
*
        write(string,'(a,F5.0,a,F5.0,A)')
     +  'd^2![s] / dQ^2! dE?T! (',
     +  q2bin(k),' lt Q^2! lt ',q2bin(k+1),' GeV^2!) '
*
        call hbookb(IM+120+k,string,NBINETnew,XBINET,0)
        call hbarx(IM+120+k)
        call hbook1(IM1+120+k,string,30,XBINET(1),XBINET(NBINETnew+1),0)
        call hbarx(IM1+120+k)
 
*
        write(string,'(a,F5.0,a,F5.0,A)')
     +  'd^2![s] / dQ^2! dM?jj! (',
     +  q2bin(k),' lt Q^2! lt ',q2bin(k+1),' GeV^2!) '
*
        call hbookb(IM+130+k,string,NBINM2 ,XBINM2  ,0)
        call hbarx(IM+130+k)
        call hbook1(IM1+130+k,string,30,XBINM2(1),XBINM2(NBINM2+1),0)
        call hbarx(IM1+130+k)
*
        write(string,'(a,F5.0,a,F5.0,A)')
     +  'd^2![s] / dQ^2! detap (',
     +  q2bin(k),' lt Q^2! lt ',q2bin(k+1),' GeV^2!) '
*
        call hbookb(IM+140+k,string,NBINCP ,XBINCP  ,0)
        call hbarx(IM+140+k)
        call hbook1(IM1+140+k,string,30,XBINCP(1),XBINCP(NBINCP+1),0)
        call hbarx(IM1+140+k)
 
*
        write(string,'(a,F5.0,a,F5.0,A)')
     +  'd^2![s] / dQ^2! dy (',
     +  q2bin(k),' lt Q^2! lt ',q2bin(k+1),' GeV^2!) '
*
        call hbookb(IM+160+k,string,NBINY  ,XBINY   ,0)
        call hbarx(IM+160+k)
        call hbook1(IM1+160+k,string,30,XBINY(1),XBINY(NBINY+1),0)
        call hbarx(IM1+160+k)
*
        write(string,'(a,F5.0,a,F5.0,A)')
     +  'd^2![s] / dQ^2! dxbj (',
     +  q2bin(k),' lt Q^2! lt ',q2bin(k+1),' GeV^2!) '
*
        if (k.le.4) then
         Do ii=1,NBINXLO+1
          if (k.eq.1) XBINXLO0(ii)=XBINXLO1(ii)
          if (k.eq.2) XBINXLO0(ii)=XBINXLO2(ii)
          if (k.eq.3) XBINXLO0(ii)=XBINXLO3(ii)
          if (k.eq.4) XBINXLO0(ii)=XBINXLO4(ii)
         enddo
         II=NBINXLO
        else
         Do ii=1,NBINXLO5+1
          if (k.eq.5) XBINXLO0(ii)=XBINXLO5(ii)
         enddo
         II=NBINXLO5
        endif
        call hbookb(IM+170+k,string,II  ,XBINXLO0   ,0)
        call hbarx(IM+170+k)
        call hbook1(IM1+170+k,string,30,XBINXLO0(1),XBINXLO0(II+1),0)
        call hbarx(IM1+170+k)
*
        write(string,'(a,F5.0,a,F5.0,A)')
     +  'd^2![s] / dQ^2! dxp (',
     +  q2bin(k),' lt Q^2! lt ',q2bin(k+1),' GeV^2!) '
*
        if (k.eq.1) then
         call hbookb(IM+180+k,string,NBINXPLO ,XBINXPLO1  ,0)
        else if (k.eq.2) then
         call hbookb(IM+180+k,string,NBINXPLO ,XBINXPLO2  ,0)
        else if (k.eq.3) then
         call hbookb(IM+180+k,string,NBINXPLO ,XBINXPLO3  ,0)
        else if (k.eq.4) then
         call hbookb(IM+180+k,string,NBINXPLO ,XBINXPLO4  ,0)
        else
         call hbookb(IM+180+k,string,NBINXPLO ,XBINXPLO4  ,0)
        endif
 
        call hbarx(IM+180+k)
        call hbook1(IM1+180+k,string,30,-4.,-0.5,0)
        call hbarx(IM1+180+k)
 
*
        write(string,'(a,F5.0,a,F5.0,A)')
     +  'd^2![s] / dQ^2! d[c]?fwd! (',
     +  q2bin(k),' lt Q^2! lt ',q2bin(k+1),' GeV^2!) '
*
        call hbookb(IM+190+k,string,NBINCFL,XBINCFL ,0)
        call hbarx(IM+190+k)
        call hbook1(IM1+190+k,string,30,XBINCFL(1),XBINCFL(NBINCFL+1),0)
        call hbarx(IM1+190+k)
*
        write(string,'(a,F5.0,a,F5.0,A)')
     +  'd^2![s] / dQ^2! d[c]?back,lab! (',
     +  q2bin(k),' lt Q^2! lt ',q2bin(k+1),' GeV^2!) '
*
        call hbookb(IM+200+k,string,NBINCBL,XBINCBL ,0)
        call hbarx(IM+200+k)
        call hbook1(IM1+200+k,string,30,XBINCBL(1),XBINCBL(NBINCBL+1),0)
        call hbarx(IM1+200+k)
*
        if (k.eq.1) then
         write(string,'(a,F5.0,a,F5.0,A)')
     +   'd^2![s]/ dQ^2! d[c]?boost! 10 lt Q^2! lt 70 GeV^2!) '
         call hbookb(IM+210,string,NBINCB  ,XBINCB  ,0)
         call hbarx(IM+210)
        endif
*
        write(string,'(a,F5.0,a,F5.0,A)')
     +  'd^2![s] / dQ^2! d[c]?boost! (',
     +  q2bin(k),' lt Q^2! lt ',q2bin(k+1),' GeV^2!) '
*
        call hbookb(IM+210+k,string,NBINCB  ,XBINCB  ,0)
        call hbarx(IM+210+k)
*
        if (k.eq.1) then
         write(string,'(a,F5.0,a,F5.0,A)')
     +   'd^2![s]/ dQ^2! d[c]?fwd,Breit! 10 lt Q^2!lt 70 GeV^2!) '
         call hbookb(IM+220,string,NBINCFB,XBINCFB ,0)
         call hbarx(IM+220)
        endif
*
        write(string,'(a,F5.0,a,F5.0,A)')
     +  'd^2![s] / dQ^2! d[c]?fwd,Breit! (',
     +  q2bin(k),' \74 Q^2!\74 ',q2bin(k+1),' GeV^2!) '
*
        call hbookb(IM+220+k,string,NBINCFB,XBINCFB ,0)
        call hbarx(IM+220+k)
*
        if (k.eq.1) then
         write(string,'(a,F5.0,a,F5.0,A)')
     +   'd^2![s]/ dQ^2! d[c]?bkw,Breit! 10 lt Q^2! lt 70 GeV^2!) '
         call hbookb(IM+230,string,NBINCBB,XBINCBB ,0)
         call hbarx(IM+230)
        endif
*
        write(string,'(a,F5.0,a,F5.0,A)')
     +  'd^2![s] / dQ^2! d[c]?bkw,Breit! (',
     +  q2bin(k),' lt Q^2! lt ',q2bin(k+1),' GeV^2!) '
*
        call hbookb(IM+230+k,string,NBINCBB,XBINCBB ,0)
        call hbarx(IM+230+k)
*
        if (k.eq.1) then
         write(string,'(a,F5.0,a,F5.0,A)')
     +   'd^2![s]/ dQ^2! d[c]?bkw,Breit! 10 lt Q^2! lt 70 GeV^2!) '
         call hbookb(IM+240,string,NBINCBB,XBINCBB ,0)
         call hbarx(IM+240)
        endif
*
        write(string,'(a,F5.0,a,F5.0,A)')
     +  'd^2![s] / dQ^2! d[c]?bkw,Breit! (',
     +  q2bin(k),' lt Q^2! lt ',q2bin(k+1),' GeV^2!) '
*
        call hbookb(IM+240+k,string,NBINCBB,XBINCBB ,0)
        call hbarx(IM+240+k)
*
        write(string,'(a,F5.0,a,F5.0,A)')
     +  'd^2![s] / dQ^2! dxgamma (',
     +  q2bin(k),' lt Q^2! lt ',q2bin(k+1),' GeV^2!) '
*
        call hbook1(IM+260+k,string,10,0.,1.,0)
        call hbarx(IM+260+k)
*
       enddo
*
       do k=1,nq2bin
*
        write(string,'(a,F5.0,a,F5.0,A)')
     +  'd^2![s] / dQ^2! d[x] all bins (',
     +  q2bin(k),' lt Q^2! lt ',q2bin(k+1),' GeV^2!) '
*
        call hbookb(IM+270+k,string,NBINXIALL,XBINXIALL  ,0)
        call hbarx(IM+270+k)
       enddo
*
       Do k=0,6
        call hbook1(IM+250+k,' weights ',100,0.,100.,0)
        call hbarx(IM+250+k)
       enddo
*
       do k=1,netbin-1
        write(string,'(a,F5.0,a,F5.0,A)')
     +  'd^2![s] / dE?T!! detap (',
     +  etbin(k),' lt Et lt ',etbin(k+1),' GeV) '
*
        call hbookb(IM+150+k,string,NBINCP ,XBINCP  ,0)
        call hbarx(IM+150+k)
       enddo
*
*      HIGH Q2
*
       if (lp) write(6,*) ' booking high Q2 histos ! '
       ID=117
*
       write(string,'(a,F5.0,a,F5.0,A)')
     + 'd^2![s] / dQ^2! d[x] (',
     + q2bin(7),' lt Q^2! lt ',q2bin(8),' GeV^2!) '
*
       call hbookb(IM+ID,string,NBINXI7,XBINXI7,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),string,NBINXI7,XBINXI7,0)
       call hbookb(-1*(IM+ID+1000),string,NBINXI7,XBINXI7,0)
       call hbookb(-1*(IM+ID+2000),string,NBINXI7,XBINXI7,0)
       call hbook1(im1+ID,string,100,XBINXI7(1),XBINXI7(NBINXI7+1),0)
       call hbarx(im1+id)
*
       do i=1,NBINXI7
        estdksi1(i)    = sqrt((estdksi1 (i)/100.*sigksi1(i))**2 +
     +                        (estcksi1 (i)/100.*sigksi1(i))**2 )
        ehadpksi1(i)   = sqrt((esycksi1 (i)/100.*sigksi1(i))**2 +
     +                        (ehadpksi1(i)/100.*sigksi1(i))**2+
     +                        ( eempksi1(i)/100.*sigksi1(i))**2)
        ehadmksi1(i)   = sqrt((esycksi1 (i)/100.*sigksi1(i))**2 +
     +                       (ehadmksi1 (i)/100.*sigksi1(i))**2+
     +                       ( eemmksi1 (i)/100.*sigksi1(i))**2)
*
        ehadpksi1(i)=sqrt((estdksi1(i)**2+ehadpksi1(i)**2))
        ehadmksi1(i)=sqrt((estdksi1(i)**2+ehadmksi1(i)**2))
       enddo
*
       call hpak (-1*(IM+ID) ,sigksi1)
       call hpak (-1*(IM+1000+ID),sigksi1)
       call hpak (-1*(IM+2000+ID),sigksi1)
       call hpake(-1*(IM+ID ),estdksi1)
       call hpake(-1*(IM+1000+ID),ehadmksi1)
       call hpake(-1*(IM+2000+ID),ehadpksi1)
*                        norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BINW(7),1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BINW(7),1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BINW(7),1)
*
       ID=118
*
       write(string,'(a,F6.0,a,F6.0,A)')
     + 'd^2![s] / dQ^2! d[x] (',
     + q2bin(8),' lt Q^2! lt ',q2bin(9),' GeV^2!) '
*
       call hbookb(IM+ID,string,NBINXI8,XBINXI8,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),string,NBINXI8,XBINXI8,0)
       call hbookb(-1*(IM+ID+1000),string,NBINXI8,XBINXI8,0)
       call hbookb(-1*(IM+ID+2000),string,NBINXI8,XBINXI8,0)
       call hbook1(im1+ID,string,100,XBINXI8(1),XBINXI8(NBINXI8+1),0)
       call hbarx(im1+id)
*
       do i=1,NBINXI8
        estdksi2(i)    = sqrt((estdksi2 (i)/100.*sigksi2(i))**2 +
     +                        (estcksi2 (i)/100.*sigksi2(i))**2 )
        ehadpksi2(i)   = sqrt((esycksi2 (i)/100.*sigksi2(i))**2 +
     +                        (ehadpksi2(i)/100.*sigksi2(i))**2+
     +                        ( eempksi2(i)/100.*sigksi2(i))**2)
        ehadmksi2(i)   = sqrt((esycksi2 (i)/100.*sigksi2(i))**2 +
     +                       (ehadmksi2 (i)/100.*sigksi2(i))**2+
     +                       ( eemmksi2 (i)/100.*sigksi2(i))**2)
*
        ehadpksi2(i)=sqrt((estdksi2(i)**2+ehadpksi2(i)**2))
        ehadmksi2(i)=sqrt((estdksi2(i)**2+ehadmksi2(i)**2))
       enddo
*
       call hpak (-1*(IM+ID) ,sigksi2)
       call hpak (-1*(IM+1000+ID),sigksi2)
       call hpak (-1*(IM+2000+ID),sigksi2)
       call hpake(-1*(IM+ID ),estdksi2)
       call hpake(-1*(IM+1000+ID),ehadmksi2)
       call hpake(-1*(IM+2000+ID),ehadpksi2)
*                        norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BINW(8),1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BINW(8),1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BINW(8),1)
*
       ID=119
*
       write(string,'(a,F6.0,a,F6.0,A)')
     + 'd^2![s] / dQ^2! d[x] (',
     + q2bin(9),' lt Q^2! lt ',q2bin(10),' GeV^2!) '
*
       call hbookb(IM+ID,string,NBINXI9,XBINXI9,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),string,NBINXI9,XBINXI9,0)
       call hbookb(-1*(IM+ID+1000),string,NBINXI9,XBINXI9,0)
       call hbookb(-1*(IM+ID+2000),string,NBINXI9,XBINXI9,0)
       call hbook1(im1+ID,string,100,XBINXI9(1),XBINXI9(NBINXI9+1),0)
       call hbarx(im1+id)
*
       do i=1,NBINXI9
        estdksi3(i)    = sqrt((estdksi3 (i)/100.*sigksi3(i))**2 +
     +                        (estcksi3 (i)/100.*sigksi3(i))**2 )
        ehadpksi3(i)   = sqrt((esycksi3 (i)/100.*sigksi3(i))**2 +
     +                        (ehadpksi3(i)/100.*sigksi3(i))**2+
     +                        ( eempksi3(i)/100.*sigksi3(i))**2)
        ehadmksi3(i)   = sqrt((esycksi3 (i)/100.*sigksi3(i))**2 +
     +                       (ehadmksi3 (i)/100.*sigksi3(i))**2+
     +                       ( eemmksi3 (i)/100.*sigksi3(i))**2)
*
        ehadpksi3(i)=sqrt((estdksi3(i)**2+ehadpksi3(i)**2))
        ehadmksi3(i)=sqrt((estdksi3(i)**2+ehadmksi3(i)**2))
       enddo
*
       call hpak (-1*(IM+ID) ,sigksi3)
       call hpak (-1*(IM+1000+ID),sigksi3)
       call hpak (-1*(IM+2000+ID),sigksi3)
       call hpake(-1*(IM+ID ),estdksi3)
       call hpake(-1*(IM+1000+ID),ehadmksi3)
       call hpake(-1*(IM+2000+ID),ehadpksi3)
*                        norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BINW(9),1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BINW(9),1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BINW(9),1)
*
       ID=127
*
       write(string,'(a,F5.0,a,F5.0,A)')
     + 'd^2![s] / dQ^2! dE?t,Breit!(',
     + q2bin(7),' lt Q^2! lt ',q2bin(8),' GeV^2!) '
*
       call hbookb(IM+ID,string,NBINET7,XBINET7,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),string,NBINET7,XBINET7,0)
       call hbookb(-1*(IM+ID+1000),string,NBINET7,XBINET7,0)
       call hbookb(-1*(IM+ID+2000),string,NBINET7,XBINET7,0)
       call hbook1(im1+ID,string,100,XBINET7(1),XBINET7(NBINET7+1),0)
       call hbarx(im1+id)
*
       do i=1,NBINET7
        estdet1(i)    = sqrt((estdet1 (i)/100.*siget1(i))**2 +
     +                        (estcet1 (i)/100.*siget1(i))**2 )
        ehadpet1(i)   = sqrt((esycet1 (i)/100.*siget1(i))**2 +
     +                        (ehadpet1(i)/100.*siget1(i))**2+
     +                        ( eempet1(i)/100.*siget1(i))**2)
        ehadmet1(i)   = sqrt((esycet1 (i)/100.*siget1(i))**2 +
     +                       (ehadmet1 (i)/100.*siget1(i))**2+
     +                       ( eemmet1 (i)/100.*siget1(i))**2)
*
        ehadpet1(i)=sqrt((estdet1(i)**2+ehadpet1(i)**2))
        ehadmet1(i)=sqrt((estdet1(i)**2+ehadmet1(i)**2))
       enddo
*
       call hpak (-1*(IM+ID) ,siget1)
       call hpak (-1*(IM+1000+ID),siget1)
       call hpak (-1*(IM+2000+ID),siget1)
       call hpake(-1*(IM+ID ),estdet1)
       call hpake(-1*(IM+1000+ID),ehadmet1)
       call hpake(-1*(IM+2000+ID),ehadpet1)
*                        norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BINW(7),1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BINW(7),1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BINW(7),1)
*
       ID=128
*
       write(string,'(a,F6.0,a,F6.0,A)')
     + 'd^2![s] / dQ^2! dE?t,Breit! (',
     + q2bin(8),' lt Q^2! lt ',q2bin(9),' GeV^2!) '
*
       call hbookb(IM+ID,string,NBINET8,XBINET8,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),string,NBINET8,XBINET8,0)
       call hbookb(-1*(IM+ID+1000),string,NBINET8,XBINET8,0)
       call hbookb(-1*(IM+ID+2000),string,NBINET8,XBINET8,0)
       call hbook1(im1+ID,string,100,XBINET8(1),XBINET8(NBINET8+1),0)
       call hbarx(im1+id)
*
       do i=1,NBINET8
        estdet2(i)    = sqrt((estdet2 (i)/100.*siget2(i))**2 +
     +                        (estcet2 (i)/100.*siget2(i))**2 )
        ehadpet2(i)   = sqrt((esycet2 (i)/100.*siget2(i))**2 +
     +                        (ehadpet2(i)/100.*siget2(i))**2+
     +                        ( eempet2(i)/100.*siget2(i))**2)
        ehadmet2(i)   = sqrt((esycet2 (i)/100.*siget2(i))**2 +
     +                       (ehadmet2 (i)/100.*siget2(i))**2+
     +                       ( eemmet2 (i)/100.*siget2(i))**2)
*
        ehadpet2(i)=sqrt((estdet2(i)**2+ehadpet2(i)**2))
        ehadmet2(i)=sqrt((estdet2(i)**2+ehadmet2(i)**2))
       enddo
*
       call hpak (-1*(IM+ID) ,siget2)
       call hpak (-1*(IM+1000+ID),siget2)
       call hpak (-1*(IM+2000+ID),siget2)
       call hpake(-1*(IM+ID ),estdet2)
       call hpake(-1*(IM+1000+ID),ehadmet2)
       call hpake(-1*(IM+2000+ID),ehadpet2)
*                        norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BINW(8),1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BINW(8),1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BINW(8),1)
*
       ID=129
       write(string,'(a,F6.0,a,F6.0,A)')
     + 'd^2![s] / dQ^2! dE?t,Breit!(',
     + q2bin(9),' lt Q^2! lt ',q2bin(10),' GeV^2!) '
*
       call hbookb(IM+ID,string,NBINET9,XBINET9,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),string,NBINET9,XBINET9,0)
       call hbookb(-1*(IM+ID+1000),string,NBINET9,XBINET9,0)
       call hbookb(-1*(IM+ID+2000),string,NBINET9,XBINET9,0)
       call hbook1(im1+ID,string,100,XBINET9(1),XBINET9(NBINET9+1),0)
       call hbarx(im1+id)
*
       do i=1,NBINET9
        estdet3(i)    = sqrt((estdet3 (i)/100.*siget3(i))**2 +
     +                       (estcet3 (i)/100.*siget3(i))**2 )
        ehadpet3(i)   = sqrt((esycet3 (i)/100.*siget3(i))**2 +
     +                       (ehadpet3(i)/100.*siget3(i))**2+
     +                       (eempet3 (i)/100.*siget3(i))**2)
        ehadmet3(i)   = sqrt((esycet3 (i)/100.*siget3(i))**2 +
     +                       (ehadmet3(i)/100.*siget3(i))**2+
     +                       (eemmet3 (i)/100.*siget3(i))**2)
*
        ehadpet3(i)=sqrt((estdet3(i)**2+ehadpet3(i)**2))
        ehadmet3(i)=sqrt((estdet3(i)**2+ehadmet3(i)**2))
       enddo
*
       call hpak (-1*(IM+ID) ,siget3)
       call hpak (-1*(IM+1000+ID),siget3)
       call hpak (-1*(IM+2000+ID),siget3)
       call hpake(-1*(IM+ID ),estdet3)
       call hpake(-1*(IM+1000+ID),ehadmet3)
       call hpake(-1*(IM+2000+ID),ehadpet3)
*                        norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BINW(9),1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BINW(9),1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BINW(9),1)
*
       ID=137
       write(string,'(a,F5.0,a,F5.0,A)')
     + 'd^2![s] / dQ^2! dM?jj!  (',
     + q2bin(7),' lt Q^2! lt ',q2bin(8),' GeV^2!) '
*
       call hbookb(IM+ID,string,NBINM21,XBINM21,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),string,NBINM21,XBINM21,0)
       call hbookb(-1*(IM+ID+1000),string,NBINM21,XBINM21,0)
       call hbookb(-1*(IM+ID+2000),string,NBINM21,XBINM21,0)
       call hbook1(im1+ID,string,100,XBINM21(1),XBINM21(NBINM21+1),0)
       call hbarx(im1+id)
*
       do i=1,NBINM21
        estdmj1(i)    = sqrt((estdmj1 (i)/100.*sigmj1(i))**2 +
     +                        (estcmj1 (i)/100.*sigmj1(i))**2 )
        ehadpmj1(i)   = sqrt((esycmj1 (i)/100.*sigmj1(i))**2 +
     +                        (ehadpmj1(i)/100.*sigmj1(i))**2+
     +                        ( eempmj1(i)/100.*sigmj1(i))**2)
        ehadmmj1(i)   = sqrt((esycmj1 (i)/100.*sigmj1(i))**2 +
     +                       (ehadmmj1 (i)/100.*sigmj1(i))**2+
     +                       ( eemmmj1 (i)/100.*sigmj1(i))**2)
*
        ehadpmj1(i)=sqrt((estdmj1(i)**2+ehadpmj1(i)**2))
        ehadmmj1(i)=sqrt((estdmj1(i)**2+ehadmmj1(i)**2))
       enddo
*
       call hpak (-1*(IM+ID) ,sigmj1)
       call hpak (-1*(IM+1000+ID),sigmj1)
       call hpak (-1*(IM+2000+ID),sigmj1)
       call hpake(-1*(IM+ID ),estdmj1)
       call hpake(-1*(IM+1000+ID),ehadmmj1)
       call hpake(-1*(IM+2000+ID),ehadpmj1)
*                        norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BINW(7),1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BINW(7),1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BINW(7),1)
*
       ID=138
*
       write(string,'(a,F6.0,a,F6.0,A)')
     + 'd^2![s] / dQ^2! d dM?jj!  (',
     + q2bin(8),' lt Q^2! lt ',q2bin(9),' GeV^2!) '
*
       call hbookb(IM+ID,string,NBINM21,XBINM21,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),string,NBINM21,XBINM21,0)
       call hbookb(-1*(IM+ID+1000),string,NBINM21,XBINM21,0)
       call hbookb(-1*(IM+ID+2000),string,NBINM21,XBINM21,0)
       call hbook1(im1+ID,string,100,XBINM21(1),XBINM21(NBINM21+1),0)
       call hbarx(im1+id)
*
       do i=1,NBINM21
        estdmj2(i)    = sqrt((estdmj2 (i)/100.*sigmj2(i))**2 +
     +                       (estcmj2 (i)/100.*sigmj2(i))**2 )
        ehadpmj2(i)   = sqrt((esycmj2 (i)/100.*sigmj2(i))**2 +
     +                       (ehadpmj2(i)/100.*sigmj2(i))**2+
     +                       (eempmj2 (i)/100.*sigmj2(i))**2)
        ehadmmj2(i)   = sqrt((esycmj2 (i)/100.*sigmj2(i))**2 +
     +                       (ehadmmj2(i)/100.*sigmj2(i))**2+
     +                       ( eemmmj2(i)/100.*sigmj2(i))**2)
*
        ehadpmj2(i)=sqrt((estdmj2(i)**2+ehadpmj2(i)**2))
        ehadmmj2(i)=sqrt((estdmj2(i)**2+ehadmmj2(i)**2))
       enddo
*
       call hpak (-1*(IM+ID) ,sigmj2)
       call hpak (-1*(IM+1000+ID),sigmj2)
       call hpak (-1*(IM+2000+ID),sigmj2)
       call hpake(-1*(IM+ID ),estdmj2)
       call hpake(-1*(IM+1000+ID),ehadmmj2)
       call hpake(-1*(IM+2000+ID),ehadpmj2)
*                        norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BINW(8),1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BINW(8),1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BINW(8),1)
*
       ID=139
       write(string,'(a,F6.0,a,F6.0,A)')
     + 'd^2![s] / dQ^2! dM?jj!  (',
     + q2bin(9),' lt Q^2! lt ',q2bin(10),' GeV^2!) '
*
       call hbookb(IM+ID,string,NBINM21,XBINM21,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),string,NBINM21,XBINM21,0)
       call hbookb(-1*(IM+ID+1000),string,NBINM21,XBINM21,0)
       call hbookb(-1*(IM+ID+2000),string,NBINM21,XBINM21,0)
       call hbook1(im1+ID,string,100,XBINM21(1),XBINM21(NBINM21+1),0)
       call hbarx(im1+id)
*
       do i=1,NBINM21
        estdmj3(i)    = sqrt((estdmj3 (i)/100.*sigmj3(i))**2 +
     +                       (estcmj3 (i)/100.*sigmj3(i))**2 )
        ehadpmj3(i)   = sqrt((esycmj3 (i)/100.*sigmj3(i))**2 +
     +                       (ehadpmj3(i)/100.*sigmj3(i))**2+
     +                       ( eempmj3(i)/100.*sigmj3(i))**2)
        ehadmmj3(i)   = sqrt((esycmj3 (i)/100.*sigmj3(i))**2 +
     +                       (ehadmmj3(i)/100.*sigmj3(i))**2+
     +                       ( eemmmj3(i)/100.*sigmj3(i))**2)
*
        ehadpmj3(i)=sqrt((estdmj3(i)**2+ehadpmj3(i)**2))
        ehadmmj3(i)=sqrt((estdmj3(i)**2+ehadmmj3(i)**2))
       enddo
*
       call hpak (-1*(IM+ID) ,sigmj3)
       call hpak (-1*(IM+1000+ID),sigmj3)
       call hpak (-1*(IM+2000+ID),sigmj3)
       call hpake(-1*(IM+ID ),estdmj3)
       call hpake(-1*(IM+1000+ID),ehadmmj3)
       call hpake(-1*(IM+2000+ID),ehadpmj3)
*                        norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BINW(9),1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BINW(9),1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BINW(9),1)
*
       ID=147
       write(string,'(a,F5.0,a,F5.0,A)')
     + 'd^2![s] / dQ^2! d[c]'' ',
     + q2bin(7),' lt Q^2! lt ',q2bin(8),' GeV^2!) '
*
       call hbookb(IM+ID,string,NBINCP,XBINCP,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),string,NBINCP,XBINCP,0)
       call hbookb(-1*(IM+ID+1000),string,NBINCP,XBINCP,0)
       call hbookb(-1*(IM+ID+2000),string,NBINCP,XBINCP,0)
       call hbook1(im1+ID,string,100,XBINCP(1),XBINCP(NBINCP+1),0)
       call hbarx(im1+id)
*
       do i=1,NBINCP
        estdetap1(i)    = sqrt((estdetap1 (i)/100.*sigetap1(i))**2 +
     +                        (estcetap1 (i)/100.*sigetap1(i))**2 )
        ehadpetap1(i)   = sqrt((esycetap1 (i)/100.*sigetap1(i))**2 +
     +                        (ehadpetap1(i)/100.*sigetap1(i))**2+
     +                        ( eempetap1(i)/100.*sigetap1(i))**2)
        ehadmetap1(i)   = sqrt((esycetap1 (i)/100.*sigetap1(i))**2 +
     +                       (ehadmetap1 (i)/100.*sigetap1(i))**2+
     +                       ( eemmetap1 (i)/100.*sigetap1(i))**2)
*
        ehadpetap1(i)=sqrt((estdetap1(i)**2+ehadpetap1(i)**2))
        ehadmetap1(i)=sqrt((estdetap1(i)**2+ehadmetap1(i)**2))
       enddo
*
       call hpak (-1*(IM+ID) ,sigetap1)
       call hpak (-1*(IM+1000+ID),sigetap1)
       call hpak (-1*(IM+2000+ID),sigetap1)
       call hpake(-1*(IM+ID ),estdetap1)
       call hpake(-1*(IM+1000+ID),ehadmetap1)
       call hpake(-1*(IM+2000+ID),ehadpetap1)
*                        norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BINW(7),1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BINW(7),1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BINW(7),1)
*
       ID=148
       write(string,'(a,F5.0,a,F5.0,A)')
     + 'd^2![s] / dQ^2! d[c]'' ',
     + q2bin(8),' lt Q^2! lt ',q2bin(9),' GeV^2!) '
*
       call hbookb(IM+ID,string,NBINCP,XBINCP,0)
       call hbookb(-1*(IM+ID),string,NBINCP,XBINCP,0)
       call hbookb(-1*(IM+ID+1000),string,NBINCP,XBINCP,0)
       call hbookb(-1*(IM+ID+2000),string,NBINCP,XBINCP,0)
       call hbook1(im1+ID,string,100,XBINCP(1),XBINCP(NBINCP+1),0)
       call hbarx(im1+id)
*
       do i=1,NBINCP
        estdetap2(i)    = sqrt((estdetap2 (i)/100.*sigetap2(i))**2 +
     +                        (estcetap2 (i)/100.*sigetap2(i))**2 )
        ehadpetap2(i)   = sqrt((esycetap2 (i)/100.*sigetap2(i))**2 +
     +                        (ehadpetap2(i)/100.*sigetap2(i))**2+
     +                        ( eempetap2(i)/100.*sigetap2(i))**2)
        ehadmetap2(i)   = sqrt((esycetap2 (i)/100.*sigetap2(i))**2 +
     +                       (ehadmetap2 (i)/100.*sigetap2(i))**2+
     +                       ( eemmetap2 (i)/100.*sigetap2(i))**2)
*
        ehadpetap2(i)=sqrt((estdetap2(i)**2+ehadpetap2(i)**2))
        ehadmetap2(i)=sqrt((estdetap2(i)**2+ehadmetap2(i)**2))
       enddo
*
       call hpak (-1*(IM+ID) ,sigetap2)
       call hpak (-1*(IM+1000+ID),sigetap2)
       call hpak (-1*(IM+2000+ID),sigetap2)
       call hpake(-1*(IM+ID ),estdetap2)
       call hpake(-1*(IM+1000+ID),ehadmetap2)
       call hpake(-1*(IM+2000+ID),ehadpetap2)
*                        norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BINW(8),1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BINW(8),1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BINW(8),1)
*
       ID=149
       write(string,'(a,F5.0,a,F5.0,A)')
     + 'd^2![s] / dQ^2! d[c]'' ',
     + q2bin(9),' lt Q^2! lt ',q2bin(10),' GeV^2!) '
*
       call hbookb(IM+ID,string,NBINCP,XBINCP,0)
       call hbookb(-1*(IM+ID),string,NBINCP,XBINCP,0)
       call hbookb(-1*(IM+ID+1000),string,NBINCP,XBINCP,0)
       call hbookb(-1*(IM+ID+2000),string,NBINCP,XBINCP,0)
       call hbook1(im1+ID,string,100,XBINCP(1),XBINCP(NBINCP+1),0)
       call hbarx(im1+id)
*
       do i=1,NBINCP
        estdetap3(i)    = sqrt((estdetap3 (i)/100.*sigetap3(i))**2 +
     +                        (estcetap3 (i)/100.*sigetap3(i))**2 )
        ehadpetap3(i)   = sqrt((esycetap3 (i)/100.*sigetap3(i))**2 +
     +                        (ehadpetap3(i)/100.*sigetap3(i))**2+
     +                        ( eempetap3(i)/100.*sigetap3(i))**2)
        ehadmetap3(i)   = sqrt((esycetap3 (i)/100.*sigetap3(i))**2 +
     +                       (ehadmetap3 (i)/100.*sigetap3(i))**2+
     +                       ( eemmetap3 (i)/100.*sigetap3(i))**2)
*
        ehadpetap3(i)=sqrt((estdetap3(i)**2+ehadpetap3(i)**2))
        ehadmetap3(i)=sqrt((estdetap3(i)**2+ehadmetap3(i)**2))
       enddo
*
       call hpak (-1*(IM+ID) ,sigetap3)
       call hpak (-1*(IM+1000+ID),sigetap3)
       call hpak (-1*(IM+2000+ID),sigetap3)
       call hpake(-1*(IM+ID ),estdetap3)
       call hpake(-1*(IM+1000+ID),ehadmetap3)
       call hpake(-1*(IM+2000+ID),ehadpetap3)
*                        norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BINW(9),1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BINW(9),1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BINW(9),1)
*
       Do i=1,3
        ETBINW(i)=ETBIN(i+1)-ETBIN(i)
C        if (lp) write(6,*) i,' etbinw= ',ETBINW(i)
       enddo
*
       ID=157
       write(string,'(a,F5.0,a,F5.0,A)')
     + 'd^2![s] / dEt d[c]'' ',
     + etbin(1),' lt Et! lt ',etbin(2),' GeV) '
       call hbookb(IM+ID,string,NBINCP1,XBINCP1,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),string,NBINCP1,XBINCP1,0)
       call hbookb(-1*(IM+ID+1000),string,NBINCP1,XBINCP1,0)
       call hbookb(-1*(IM+ID+2000),string,NBINCP1,XBINCP1,0)
       call hbook1(im1+ID,string,100,XBINCP1(1),XBINCP1(NBINCP1+1),0)
       call hbarx(im1+id)
*
       do i=1,NBINCP1
        estdetep1(i)    = sqrt((estdetep1 (i)/100.*sigetep1(i))**2 +
     +                        (estcetep1 (i)/100.*sigetep1(i))**2 )
        ehadpetep1(i)   = sqrt((esycetep1 (i)/100.*sigetep1(i))**2 +
     +                        (ehadpetep1(i)/100.*sigetep1(i))**2+
     +                        ( eempetep1(i)/100.*sigetep1(i))**2)
        ehadmetep1(i)   = sqrt((esycetep1 (i)/100.*sigetep1(i))**2 +
     +                       (ehadmetep1 (i)/100.*sigetep1(i))**2+
     +                       ( eemmetep1 (i)/100.*sigetep1(i))**2)
*
        ehadpetep1(i)=sqrt((estdetep1(i)**2+ehadpetep1(i)**2))
        ehadmetep1(i)=sqrt((estdetep1(i)**2+ehadmetep1(i)**2))
       enddo
*
       call hpak (-1*(IM+ID) ,sigetep1)
       call hpak (-1*(IM+1000+ID),sigetep1)
       call hpak (-1*(IM+2000+ID),sigetep1)
       call hpake(-1*(IM+ID ),estdetep1)
       call hpake(-1*(IM+1000+ID),ehadmetep1)
       call hpake(-1*(IM+2000+ID),ehadpetep1)
*                        norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*ETBINW(1),1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*ETBINW(1),1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*ETBINW(1),1)
*
       ID=158
       write(string,'(a,F5.0,a,F5.0,A)')
     + 'd^2![s] / dEt d[c]'' ',
     + etbin(2),' lt Et lt ',etbin(3),' GeV!) '
       call hbookb(IM+ID,string,NBINCP1,XBINCP1,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),string,NBINCP1,XBINCP,0)
       call hbookb(-1*(IM+ID+1000),string,NBINCP1,XBINCP1,0)
       call hbookb(-1*(IM+ID+2000),string,NBINCP1,XBINCP1,0)
       call hbook1(im1+ID,string,100,XBINCP1(1),XBINCP1(NBINCP1+1),0)
       call hbarx(im1+id)
*
       do i=1,NBINCP1
        estdetep2(i)    = sqrt((estdetep2 (i)/100.*sigetep2(i))**2 +
     +                        (estcetep2 (i)/100.*sigetep2(i))**2 )
        ehadpetep2(i)   = sqrt((esycetep2 (i)/100.*sigetep2(i))**2 +
     +                        (ehadpetep2(i)/100.*sigetep2(i))**2+
     +                        ( eempetep2(i)/100.*sigetep2(i))**2)
        ehadmetep2(i)   = sqrt((esycetep2 (i)/100.*sigetep2(i))**2 +
     +                       (ehadmetep2 (i)/100.*sigetep2(i))**2+
     +                       ( eemmetep2 (i)/100.*sigetep2(i))**2)
*
        ehadpetep2(i)=sqrt((estdetep2(i)**2+ehadpetep2(i)**2))
        ehadmetep2(i)=sqrt((estdetep2(i)**2+ehadmetep2(i)**2))
       enddo
*
       call hpak (-1*(IM+ID) ,sigetep2)
       call hpak (-1*(IM+1000+ID),sigetep2)
       call hpak (-1*(IM+2000+ID),sigetep2)
       call hpake(-1*(IM+ID ),estdetep2)
       call hpake(-1*(IM+1000+ID),ehadmetep2)
       call hpake(-1*(IM+2000+ID),ehadpetep2)
*                        norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*ETBINW(2),1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*ETBINW(2),1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*ETBINW(2),1)
*
       ID=159
       write(string,'(a,F5.0,a,F5.0,A)')
     + 'd^2![s] / dEt d[c]'' ',
     + etbin(3),' lt Et lt ',etbin(4),' GeV) '
       call hbookb(IM+ID,string,NBINCP1,XBINCP1,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),string,NBINCP1,XBINCP,0)
       call hbookb(-1*(IM+ID+1000),string,NBINCP1,XBINCP1,0)
       call hbookb(-1*(IM+ID+2000),string,NBINCP1,XBINCP1,0)
       call hbook1(im1+ID,string,100,XBINCP1(1),XBINCP1(NBINCP1+1),0)
       call hbarx(im1+id)
*
       do i=1,NBINCP1
        estdetep3(i)    = sqrt((estdetep3 (i)/100.*sigetep3(i))**2 +
     +                        (estcetep3 (i)/100.*sigetep3(i))**2 )
        ehadpetep3(i)   = sqrt((esycetep3 (i)/100.*sigetep3(i))**2 +
     +                        (ehadpetep3(i)/100.*sigetep3(i))**2+
     +                        ( eempetep3(i)/100.*sigetep3(i))**2)
        ehadmetep3(i)   = sqrt((esycetep3 (i)/100.*sigetep3(i))**2 +
     +                       (ehadmetep3 (i)/100.*sigetep3(i))**2+
     +                       ( eemmetep3 (i)/100.*sigetep3(i))**2)
*
        ehadpetep3(i)=sqrt((estdetep3(i)**2+ehadpetep3(i)**2))
        ehadmetep3(i)=sqrt((estdetep3(i)**2+ehadmetep3(i)**2))
       enddo
*
       call hpak (-1*(IM+ID) ,sigetep3)
       call hpak (-1*(IM+1000+ID),sigetep3)
       call hpak (-1*(IM+2000+ID),sigetep3)
       call hpake(-1*(IM+ID ),estdetep3)
       call hpake(-1*(IM+1000+ID),ehadmetep3)
       call hpake(-1*(IM+2000+ID),ehadpetep3)
*                        norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*ETBINW(3),1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*ETBINW(3),1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*ETBINW(3),1)
 
*
       DO k=7,9
       ID=160+k
        write(string,'(a,F5.0,a,F5.0,A)')
     +  'd^2![s] / dQ^2! d[c]'' ',
     +  q2bin(k),' lt Q^2! lt ',q2bin(k+1),' GeV^2!) '
        call hbookb(IM+ID,string,NBINY   ,XBINY   ,0)
        call hbarx(IM+id)
       enddo
*
       ID=177
       write(string,'(a,F4.0,a,F4.0,A)')
     + 'd^2![s] / dQ^2! dx?Bj! (',
     + q2bin(7),' lt Q^2! lt ',q2bin(8),' GeV^2!) '
*
       call hbookb(IM+ID,string,NBINX7,XBINX7,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),string,NBINX7,XBINX7,0)
       call hbookb(-1*(IM+ID+1000),string,NBINX7,XBINX7,0)
       call hbookb(-1*(IM+ID+2000),string,NBINX7,XBINX7,0)
       call hbook1(im1+ID,string,100,XBINX7(1),XBINX7(NBINX7+1),0)
       call hbarx(im1+id)
*
       do i=1,NBINX7
        estdxb1(i)    = sqrt((estdxb1 (i)/100.*sigxb1(i))**2 +
     +                       (estcxb1 (i)/100.*sigxb1(i))**2 )
        ehadpxb1(i)   = sqrt((esycxb1 (i)/100.*sigxb1(i))**2 +
     +                       (ehadpxb1(i)/100.*sigxb1(i))**2+
     +                       (eempxb1 (i)/100.*sigxb1(i))**2)
        ehadmxb1(i)   = sqrt((esycxb1 (i)/100.*sigxb1(i))**2 +
     +                       (ehadmxb1(i)/100.*sigxb1(i))**2+
     +                       (eemmxb1 (i)/100.*sigxb1(i))**2)
*
        ehadpxb1(i)=sqrt((estdxb1(i)**2+ehadpxb1(i)**2))
        ehadmxb1(i)=sqrt((estdxb1(i)**2+ehadmxb1(i)**2))
       enddo
*
       call hpak (-1*(IM+ID) ,sigxb1)
       call hpak (-1*(IM+1000+ID),sigxb1)
       call hpak (-1*(IM+2000+ID),sigxb1)
       call hpake(-1*(IM+ID ),estdxb1)
       call hpake(-1*(IM+1000+ID),ehadmxb1)
       call hpake(-1*(IM+2000+ID),ehadpxb1)
*                        norm to bin width
       call HZHINRM(-1*(IM     +ID),0,1.*Q2BINW(7),1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BINW(7),1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BINW(7),1)
*
       ID=178
*
       write(string,'(a,F4.0,a,F4.0,A)')
     + 'd^2![s] / dQ^2! dx?Bj! (',
     + q2bin(8),' lt Q^2! lt ',q2bin(9),' GeV^2!) '
*
       call hbookb(IM+ID,string,NBINX8,XBINX8,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),string,NBINX8,XBINX8,0)
       call hbookb(-1*(IM+ID+1000),string,NBINX8,XBINX8,0)
       call hbookb(-1*(IM+ID+2000),string,NBINX8,XBINX8,0)
       call hbook1(im1+ID,string,100,XBINX8(1),XBINX8(NBINX8+1),0)
       call hbarx(im1+id)
*
       do i=1,NBINX8
        estdxb2(i)    = sqrt((estdxb2 (i)/100.*sigxb2(i))**2 +
     +                       (estcxb2 (i)/100.*sigxb2(i))**2 )
        ehadpxb2(i)   = sqrt((esycxb2 (i)/100.*sigxb2(i))**2 +
     +                       (ehadpxb2(i)/100.*sigxb2(i))**2+
     +                       (eempxb2 (i)/100.*sigxb2(i))**2)
        ehadmxb2(i)   = sqrt((esycxb2 (i)/100.*sigxb2(i))**2 +
     +                       (ehadmxb2(i)/100.*sigxb2(i))**2+
     +                       (eemmxb2 (i)/100.*sigxb2(i))**2)
*
        ehadpxb2(i)=sqrt((estdxb2(i)**2+ehadpxb2(i)**2))
        ehadmxb2(i)=sqrt((estdxb2(i)**2+ehadmxb2(i)**2))
       enddo
*
       call hpak (-1*(IM+ID) ,sigxb2)
       call hpak (-1*(IM+1000+ID),sigxb2)
       call hpak (-1*(IM+2000+ID),sigxb2)
       call hpake(-1*(IM+ID ),estdxb2)
       call hpake(-1*(IM+1000+ID),ehadmxb2)
       call hpake(-1*(IM+2000+ID),ehadpxb2)
*                        norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BINW(8),1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BINW(8),1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BINW(8),1)
*
       ID=179
*
       write(string,'(a,F6.0,a,F6.0,A)')
     + 'd^2![s] / dQ^2! dx?Bj! (',
     + q2bin(9),' lt Q^2! lt ',q2bin(10),' GeV^2!) '
*
       call hbookb(IM+ID,string,NBINX9,XBINX9,0)
       call hbarx(IM+id)
       call hbookb(-1*(IM+ID),string,NBINX9,XBINX9,0)
       call hbookb(-1*(IM+ID+1000),string,NBINX9,XBINX9,0)
       call hbookb(-1*(IM+ID+2000),string,NBINX9,XBINX9,0)
       call hbook1(im1+ID,string,100,XBINX9(1),XBINX9(NBINX9+1),0)
       call hbarx(im1+id)
*
       do i=1,NBINX9
        estdxb3(i)    = sqrt((estdxb3 (i)/100.*sigxb3(i))**2 +
     +                       (estcxb3 (i)/100.*sigxb3(i))**2 )
        ehadpxb3(i)   = sqrt((esycxb3 (i)/100.*sigxb3(i))**2 +
     +                       (ehadpxb3(i)/100.*sigxb3(i))**2+
     +                       (eempxb3 (i)/100.*sigxb3(i))**2)
        ehadmxb3(i)   = sqrt((esycxb3 (i)/100.*sigxb3(i))**2 +
     +                       (ehadmxb3(i)/100.*sigxb3(i))**2+
     +                       (eemmxb3 (i)/100.*sigxb3(i))**2)
*
        ehadpxb3(i)=sqrt((estdxb3(i)**2+ehadpxb3(i)**2))
        ehadmxb3(i)=sqrt((estdxb3(i)**2+ehadmxb3(i)**2))
       enddo
*
       call hpak (-1*(IM+ID) ,sigxb3)
       call hpak (-1*(IM+1000+ID),sigxb3)
       call hpak (-1*(IM+2000+ID),sigxb3)
       call hpake(-1*(IM+ID ),estdxb3)
       call hpake(-1*(IM+1000+ID),ehadmxb3)
       call hpake(-1*(IM+2000+ID),ehadpxb3)
*                        norm to bin width
       call HZHINRM(-1*(IM+ID) ,0,1.*Q2BINW(9),1)
       call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BINW(9),1)
       call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BINW(9),1)
*
       ID=180
       Do k=7,9
        write(string,'(a,F6.0,a,F6.0,A)')
     +  'd^2![s] / dQ^2! dx?p! (',
     +  q2bin(k),' lt Q^2! lt ',q2bin(k+1),' GeV^2!) '
*
        if (k.eq.7) call hbookb(IM+ID+k,string,NBINXP7,XBINXP7,0)
        if (k.eq.8) call hbookb(IM+ID+k,string,NBINXP8,XBINXP8,0)
        if (k.eq.9) call hbookb(IM+ID+k,string,NBINXP9,XBINXP9,0)
        call hbarx(IM+id)
       enddo
*
       Do k=7,9
        ID=190+k
        write(string,'(a,F6.0,a,F6.0,A)')
     +  'd^2![s] / dQ^2! d [c]?forw,lab!(',
     +  q2bin(k),' lt Q^2! lt ',q2bin(k+1),' GeV^2!) '
*
        call hbookb(IM+ID,string,NBINCFL ,XBINCFL ,0)
        call hbarx(IM+id)
        call hbookb(-1*(IM+ID),string,NBINCFL ,XBINCFL ,0)
        call hbookb(-1*(IM+ID+1000),string,NBINCFL ,XBINCFL ,0)
        call hbookb(-1*(IM+ID+2000),string,NBINCFL ,XBINCFL ,0)
        call hbook1(im1+ID,string,100,XBINCFL(1),XBINCFL(NBINCFL+1),0)
        call hbarx(im1+id)
*
        do i=1,NBINCFL
         if (k.eq.7) then
          estdetf1(i)    = sqrt((estdetf1(i)/100.*sigetf1(i))**2 +
     +                         (estcetf1 (i)/100.*sigetf1(i))**2 )
          ehadpetf1(i)   = sqrt((esycetf1(i)/100.*sigetf1(i))**2 +
     +                         (ehadpetf1(i)/100.*sigetf1(i))**2+
     +                         (eempetf1 (i)/100.*sigetf1(i))**2)
          ehadmetf1(i)   = sqrt((esycetf1(i)/100.*sigetf1(i))**2 +
     +                         (ehadmetf1(i)/100.*sigetf1(i))**2+
     +                         (eemmetf1 (i)/100.*sigetf1(i))**2)
*
          ehadpetf1(i)=sqrt((estdetf1(i)**2+ehadpetf1(i)**2))
          ehadmetf1(i)=sqrt((estdetf1(i)**2+ehadmetf1(i)**2))
         endif
         if (k.eq.8) then
          estdetf2(i)    = sqrt((estdetf2(i)/100.*sigetf2(i))**2 +
     +                         (estcetf2 (i)/100.*sigetf2(i))**2 )
          ehadpetf2(i)   = sqrt((esycetf2(i)/100.*sigetf2(i))**2 +
     +                         (ehadpetf2(i)/100.*sigetf2(i))**2+
     +                         (eempetf2 (i)/100.*sigetf2(i))**2)
          ehadmetf2(i)   = sqrt((esycetf2(i)/100.*sigetf2(i))**2 +
     +                         (ehadmetf2(i)/100.*sigetf2(i))**2+
     +                         (eemmetf2 (i)/100.*sigetf2(i))**2)
*
          ehadpetf2(i)=sqrt((estdetf2(i)**2+ehadpetf2(i)**2))
          ehadmetf2(i)=sqrt((estdetf2(i)**2+ehadmetf2(i)**2))
         endif
         if (k.eq.9) then
*
          estdetf3(i)    = sqrt((estdetf3(i)/100.*sigetf3(i))**2 +
     +                         (estcetf3 (i)/100.*sigetf3(i))**2 )
*
          ehadpetf3(i)   = sqrt((esycetf3(i)/100.*sigetf3(i))**2 +
     +                         (ehadpetf3(i)/100.*sigetf3(i))**2+
     +                         (eempetf3 (i)/100.*sigetf3(i))**2)
          ehadmetf3(i)   = sqrt((esycetf3(i)/100.*sigetf3(i))**2 +
     +                         (ehadmetf3(i)/100.*sigetf3(i))**2+
     +                         (eemmetf3 (i)/100.*sigetf3(i))**2)
*
 
*
          ehadpetf3(i)=sqrt((estdetf3(i)**2+ehadpetf3(i)**2))
          ehadmetf3(i)=sqrt((estdetf3(i)**2+ehadmetf3(i)**2))
         endif
        enddo
*
        if (k.eq.7) then
         call hpak (-1*(IM+ID) ,sigetf1)
         call hpak (-1*(IM+1000+ID),sigetf1)
         call hpak (-1*(IM+2000+ID),sigetf1)
         call hpake(-1*(IM+ID ),estdetf1)
         call hpake(-1*(IM+1000+ID),ehadmetf1)
         call hpake(-1*(IM+2000+ID),ehadpetf1)
        endif
        if (k.eq.8) then
         call hpak (-1*(IM+ID) ,sigetf2)
         call hpak (-1*(IM+1000+ID),sigetf2)
         call hpak (-1*(IM+2000+ID),sigetf2)
         call hpake(-1*(IM+ID),estdetf2)
         call hpake(-1*(IM+1000+ID),ehadmetf2)
         call hpake(-1*(IM+2000+ID),ehadpetf2)
        endif
        if (k.eq.9) then
         call hpak (-1*(IM+ID) ,sigetf3)
         call hpak (-1*(IM+1000+ID),sigetf3)
         call hpak (-1*(IM+2000+ID),sigetf3)
         call hpake(-1*(IM+ID ),estdetf3)
         call hpake(-1*(IM+1000+ID),ehadmetf3)
         call hpake(-1*(IM+2000+ID),ehadpetf3)
        endif
*                        norm to bin width
        call HZHINRM(-1*(IM+ID) ,0,1.*Q2BINW(K),1)
        call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BINW(K),1)
        call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BINW(K),1)
       enddo
*
       Do k=7,9
        ID=200+k
        write(string,'(a,F6.0,a,F6.0,A)')
     +  'd^2![s] / dQ^2! d[c]?back,lab!(',
     +  q2bin(k),' lt Q^2! lt ',q2bin(k+1),' GeV^2!) '
*
        call hbookb(IM+ID,string,NBINCBL ,XBINCBL ,0)
        call hbarx(IM+id)
        call hbookb(-1*(IM+ID),string,NBINCBL ,XBINCBL ,0)
        call hbookb(-1*(IM+ID+1000),string,NBINCBL ,XBINCBL ,0)
        call hbookb(-1*(IM+ID+2000),string,NBINCBL ,XBINCBL ,0)
        call hbook1(im1+ID,string,100,XBINCBL(1),XBINCBL(NBINCBL+1),0)
        call hbarx(im1+id)
*
        do i=1,NBINCBL
         if (k.eq.7) then
          estdetb1(i)    = sqrt((estdetb1(i)/100.*sigetb1(i))**2 +
     +                         (estcetb1 (i)/100.*sigetb1(i))**2 )
          ehadpetb1(i)   = sqrt((esycetb1(i)/100.*sigetb1(i))**2 +
     +                         (ehadpetb1(i)/100.*sigetb1(i))**2+
     +                         (eempetb1 (i)/100.*sigetb1(i))**2)
          ehadmetb1(i)   = sqrt((esycetb1(i)/100.*sigetb1(i))**2 +
     +                         (ehadmetb1(i)/100.*sigetb1(i))**2+
     +                         (eemmetb1 (i)/100.*sigetb1(i))**2)
*
          ehadpetb1(i)=sqrt((estdetb1(i)**2+ehadpetb1(i)**2))
          ehadmetb1(i)=sqrt((estdetb1(i)**2+ehadmetb1(i)**2))
         endif
         if (k.eq.8) then
          estdetb2(i)    = sqrt((estdetb2(i)/100.*sigetb2(i))**2 +
     +                         (estcetb2 (i)/100.*sigetb2(i))**2 )
          ehadpetb2(i)   = sqrt((esycetb2(i)/100.*sigetb2(i))**2 +
     +                         (ehadpetb2(i)/100.*sigetb2(i))**2+
     +                         (eempetb2 (i)/100.*sigetb2(i))**2)
          ehadmetb2(i)   = sqrt((esycetb2(i)/100.*sigetb2(i))**2 +
     +                         (ehadmetb2(i)/100.*sigetb2(i))**2+
     +                         (eemmetb2 (i)/100.*sigetb2(i))**2)
*
          ehadpetb2(i)=sqrt((estdetb2(i)**2+ehadpetb2(i)**2))
          ehadmetb2(i)=sqrt((estdetb2(i)**2+ehadmetb2(i)**2))
         endif
         if (k.eq.9) then
*
          estdetb3(i)    = sqrt((estdetb3(i)/100.*sigetb3(i))**2 +
     +                         (estcetb3 (i)/100.*sigetb3(i))**2 )
*
          ehadpetb3(i)   = sqrt((esycetb3(i)/100.*sigetb3(i))**2 +
     +                         (ehadpetb3(i)/100.*sigetb3(i))**2+
     +                         (eempetb3 (i)/100.*sigetb3(i))**2)
          ehadmetb3(i)   = sqrt((esycetb3(i)/100.*sigetb3(i))**2 +
     +                         (ehadmetb3(i)/100.*sigetb3(i))**2+
     +                         (eemmetb3 (i)/100.*sigetb3(i))**2)
*
          ehadpetb3(i)=sqrt((estdetb3(i)**2+ehadpetb3(i)**2))
          ehadmetb3(i)=sqrt((estdetb3(i)**2+ehadmetb3(i)**2))
         endif
        enddo
*
        if (k.eq.7) then
         call hpak (-1*(IM+ID) ,sigetb1)
         call hpak (-1*(IM+1000+ID),sigetb1)
         call hpak (-1*(IM+2000+ID),sigetb1)
         call hpake(-1*(IM+ID ),estdetb1)
         call hpake(-1*(IM+1000+ID),ehadmetb1)
         call hpake(-1*(IM+2000+ID),ehadpetb1)
        endif
        if (k.eq.8) then
         call hpak (-1*(IM+ID) ,sigetb2)
         call hpak (-1*(IM+1000+ID),sigetb2)
         call hpak (-1*(IM+2000+ID),sigetb2)
         call hpake(-1*(IM+ID),estdetb2)
         call hpake(-1*(IM+1000+ID),ehadmetb2)
         call hpake(-1*(IM+2000+ID),ehadpetb2)
        endif
        if (k.eq.9) then
         call hpak (-1*(IM+ID) ,sigetb3)
         call hpak (-1*(IM+1000+ID),sigetb3)
         call hpak (-1*(IM+2000+ID),sigetb3)
         call hpake(-1*(IM+ID ),estdetb3)
         call hpake(-1*(IM+1000+ID),ehadmetb3)
         call hpake(-1*(IM+2000+ID),ehadpetb3)
        endif
*                        norm to bin width
        call HZHINRM(-1*(IM+ID) ,0,1.*Q2BINW(K),1)
        call HZHINRM(-1*(IM+1000+ID),0,1.*Q2BINW(K),1)
        call HZHINRM(-1*(IM+2000+ID),0,1.*Q2BINW(K),1)
       enddo
*
       do k=7,9
        id=im+210+k
        call hbookb(ID,'d[s] / d[c]?boost!'     ,NBINCB  ,XBINCB  ,0)
        call hbarx(ID)
        id=im+220+k
        call hbookb(ID,'d[s] / d[c]?forw,Breit!',NBINCFB ,XBINCFB ,0)
        call hbarx(ID)
        id=im+230+k
        call hbookb(ID,'d[s] / d[c]?back,Breit!',NBINCBB ,XBINCBB ,0)
        call hbarx(ID)
       enddo
C       call Hldir(' ','T')
*
*********************************************************************
*
*                      Event Processing
*
*********************************************************************
*
      Else if(iflag.eq.2) then
*
*      Filling: The following MUST always be done
*      (i) move to the correct sub-directory in PAWC
*
       call hcdir('//PAWC/'//xxxx,' ')
*
       xw=wtx
*
       q2=real(HZDISKIN(1))
       x =real(HZDISKIN(2))
       y =real(HZDISKIN(3))
       w2=real(HZDISKIN(4))
*
       if (lp) then
        write(6,*) rout,' x= ',x,' q2= ',q2,' y= ',y,' wtx= ',wtx
       endif
*
C       if (q2.lt.5.) return
C       if (q2.gt.5000.) return
C       if (y.gt.0.6) return
C       if (y.lt.0.2) return
*
       if (lp) then
        write(6,*) rout,' Jets in Breit: ',numjets
        call hzlijet(numjets,jets)
        write(6,*) rout,' Jets in Lab: ',njetlab
        call hzlijet(njetlab,jetslab)
       endif
*
       Do i=1,nsel
        do j=1,8
         jetsel(i,j)=jets(ipjet(i),j)
        enddo
       enddo
*
       if (lp) then
        write(6,*) rout,' selected Jets in Breit: ',nsel
        call hzlijet(nsel,jetsel)
       endif
*
C      etmax=real(jetsel(1,3))
C      etmin=real(jetsel(2,3))
       etmax=sqrt(jetsel(1,5)**2+jetsel(1,6)**2)
       etmin=sqrt(jetsel(2,5)**2+jetsel(2,6)**2)
*
       nev=nev+wtx
       nsig=nsig+wtx**2
*
       if (lp) write(6,*) ' etmin= ',etmin,' etmax= ',etmax
       if (etmin+etmax.lt.12.) return
*
       k=0
       do i=1,nq2bin-1
C        write(6,*) q2bin(i),' < ',q2,' < ',q2bin(i+1)
        if (q2bin(i).le.q2.and.q2bin(i+1).gt.q2) then
         k=i
        endif
C        write(6,*) ' k= ',k
        if (k.ne.0) goto 9
       enddo
 9     continue
*
       if (lp) then
        write(6,*) ' k= ',k,' q2= ',q2
       endif
       if (k.eq.0) then
C        write(6,*) '**hzdijet2: k=0 ? q2= ',q2
        goto 10
       endif
*
       bin0=.false.
       if (q2.gt.10. .and. q2.le.70.) bin0=.true.
       if (lp) write(6,*) ' bin0= ',bin0,' q2= ',q2
*
       if (bin0) call hfill(im  ,1.,0.,wtx)
       call hfill(im+k,1.,0.,wtx)
*
       call hfill(im+100   ,q2,0.,wtx)
       call hfill(im+100+1 ,q2,0.,wtx)
       call hfill(im1+100+1 ,q2,0.,wtx)
       if (etmin+etmax.gt.40.) then
        call hfill(im +100+2 ,q2,0.,wtx)
        call hfill(im1+100+2,q2,0.,wtx)
       endif
*
       if (bin0) call hfill(IM+170   ,x,0.,wtx)
       call hfill(IM+170+k ,x,0.,wtx)
       call hfill(IM1+170+k ,x,0.,wtx)
*
       if (bin0) call hfill(IM+160   ,y,0.,wtx)
       call hfill(IM+160+k ,y,0.,wtx)
       call hfill(IM1+160+k ,y,0.,wtx)
*
       if (bin0) call hfill(IM+250 ,wtx,0.,1.)
       call hfill(IM+250+k ,wtx,0.,1.)
*
       et=(etmax+etmin)/2.
       if (lp) write(6,*) ' et= ',et
       if (bin0) call hfill(IM+120,et,0.,wtx)
       call hfill(IM+120+k ,et,0.,wtx)
       call hfill(IM1+120+k ,et,0.,wtx)
*
       shat=(JETSEL(1,5)+JETSEL(2,5))**2 +
     &      (JETSEL(1,6)+JETSEL(2,6))**2 +
     &      (JETSEL(1,7)+JETSEL(2,7))**2 -
     &      (JETSEL(1,4)+JETSEL(2,4))**2
       shat=-shat
       if (shat.gt.0.) then
        xi= x*(1.+shat/q2)
        shat=sqrt(shat)
       else
        xi=-999.
        shat=-999.
       endif
*
       if (bin0) call hfill(IM+130  ,shat,0.,wtx)
       call hfill(IM+130+k,shat,0.,wtx)
       call hfill(IM1+130+k,shat,0.,wtx)
*
       if (bin0) call hfill(IM+110  ,xi,0.,wtx)
       call hfill(IM+110+k,xi,0.,wtx)
       call hfill(IM1+110+k,xi,0.,wtx)
*
       call hfill(IM+270+k,xi,0.,wtx)
*
       if (xi.ne.0.) then
        xp= x/xi
       else
        xp=-1.
       endif
*
       if (bin0) call hfill(IM+180  ,xp,0.,wtx)
       call hfill(IM+180+k,xp,0.,wtx)
*
       if (xp.gt.0.) then
        xp=log10(xp)
        call hfill(IM1+180+k,xp,0.,wtx)
       else
        xp=-999.
       endif
*
       eta1=real(jetsel(1,1))
       eta2=real(jetsel(2,1))
       eta=max(eta1,eta2)
       if (bin0) call hfill(IM+220  ,eta,0.,wtx)
       call hfill(IM+220+k,eta,0.,wtx)
       eta=min(eta1,eta2)
       if (bin0) call hfill(IM+230  ,eta,0.,wtx)
       call hfill(IM+230+k,eta,0.,wtx)
*
       eta=abs(eta1-eta2)/2.
       if (bin0) call hfill(IM+140  ,eta,0.,wtx)
       call hfill(IM+140+k,eta,0.,wtx)
       call hfill(IM1+140+k,eta,0.,wtx)
*
       if (bin0) call hfill(IM+150  ,eta,0.,wtx)
       if (q2.gt.q2bin(1).and.q2.lt.q2bin(5) )then
*
        l=0
        do i=1,netbin-1
C          write(6,*) etbin(i),' < ',et,' < ',etbin(i+1)
         if (etbin(i).le.et.and.etbin(i+1).gt.et) then
          l=i
         endif
        enddo
        call hfill(IM+150+l,eta,0.,wtx)
        call hfill(IM1+150+l,eta,0.,wtx)
       endif
*
       eta=abs(eta1+eta2)/2.
       if (bin0) call hfill(IM+210  ,eta,0.,wtx)
       call hfill(IM+210+k,eta,0.,wtx)
       call hfill(IM1+210+k,eta,0.,wtx)
*
       eta1=real(jetslab(ipjet(1),1))
       eta2=real(jetslab(ipjet(2),1))
       eta=max(eta1,eta2)
       if (bin0) call hfill(IM+190  ,eta,0.,wtx)
       call hfill(IM+190+k,eta,0.,wtx)
       call hfill(IM1+190+k,eta,0.,wtx)
       if (lp) write(6,*) rout,' Etafwd= ',eta
*
       eta=min(eta1,eta2)
       if (bin0) call hfill(IM+200  ,eta,0.,wtx)
       call hfill(IM+200+k,eta,0.,wtx)
       call hfill(IM1+200+k,eta,0.,wtx)
       if (lp) write(6,*) rout,' Etabkw= ',eta
 
*
        phi1=real(jetsel(1,2))
        phi2=real(jetsel(2,2))
        dphi=phi1-phi2
        DELPHi=AMIN1(ABS(DPHI+DPI),ABS(DPHI),ABS(DPHI-DPI))*RD
        if (bin0) call hfill(IM+240  ,delphi,0.,wtx)
        call hfill(IM+240+k,delphi,0.,wtx)
*                how to include here Empz from hadrons ?? yjb ??
        xgamma=0.
        if (bin0) call hfill(IM+260  ,xgamma,0.,wtx)
        call hfill(IM+260+k,xgamma,0.,wtx)
*
 10    continue
*
       if (lp) write(6,*) rout,' at the end '
*********************************************************************
      Else if(iflag.eq.3) then
*      Termination: The following MUST always be done
*      (i) Move to the correct PAW subdirectory
*
       call hcdir('//PAWC/'//xxxx,' ')
*
C       call Hldir(' ',' ')
*
       if (nevhep.ne.0.) then
        x=nsig-nev**2/nevhep
       else
        write(6,*) ' nevhep is wrong nevhep= ',nevhep
        x=-1.
       endif
*
       if (x.gt.0.) then
        x=sqrt(x)
       else
        write(6,*) i,' x= ',x,' nsig= ',nsig,' nev= ',nev
        x=-1.
       endif
*
       if (xsec.ne.0.) then
        lum=wtx/xsec
       else
        write(6,*) rout,' xsec= ',xsec,' !! '
        lum=0.
       endif
*
       write(*,*) rout,' Luminosity = ',lum
*
       call HZHINRM(IM+100,0,lum,1)
       call HZHINRM(IM+101,0,lum,1)
       call HZHINRM(IM1+101,0,lum,1)
       call HZHINRM(IM+102,0,lum,1)
       call HZHINRM(IM1+102,0,lum,1)
*
       do k=1,nq2bin-1
        if (q2binw(k).gt.0. .and.
     &        (q2bin(k).ne.0. .and. q2bin(k+1).ne.0.)
     &  ) then
C         write(6,*) k,' binwidth= ',Q2BINW(k),' id= ',id
         call HZHINRM(IM+270+k,0,lum*Q2BINW(k),1)
        endif
       enddo
*
       do k=0,nq2bin-1
        do i=11,23
         if (i.ne.15) then
          id=IM+10*I+k
          id1=IM1+10*I+k
          if (k.ne.0) then
           if (q2binw(k).gt.0. .and.
     &        (q2bin(k).ne.0. .and. q2bin(k+1).ne.0.)
     &     ) then
*
C           write(6,*) k,' binwidth= ',Q2BINW(k),' id= ',id
            call HZHINRM(ID,0,lum*Q2BINW(k),1)
            if (i.ne.18.and.i.ne.21.and.i.ne.22.and.i.ne.23) then
C             write(6,*) ' norm i= ',i,' id1= ',id1
             if (i.ne.16.or.k.lt.7) then
              call HZHINRM(ID1,0,lum*Q2BINW(k),1)
             endif
            endif
*
            if (i.le.14 .or. (i.ge.17 .and. i.lt.20)
     &          .and.i.ne.18 ) then
             if (k.ge.7) then
C              call hzchisq(-id,id)
             endif
            endif
           endif
C          call hzhinfo(id,nn(k))
          else
C           write(6,*) k,' binwidth= ',Q2BIN0,' id= ',id
           call HZHINRM(id,0,lum*Q2BIN0,1)
           if (i.le.14 .or. (i.ge.17 .and. i.lt.20)
     &      .and.i.ne.18) then
C            call hzchisq(-id,id)
           endif
          endif
         endif
        enddo
       enddo
*
       Do k=0,netbin-1
        id=im+150+k
        if (k.ne.0) then
         norm=etbin(k+1)-etbin(k)
C         write(6,*) ' id= ',id,' norm= ',norm
         call HZHINRM(ID,0,lum*norm,1)
        else
         norm=etbin(netbin)-etbin(1)
C         write(6,*) ' id= ',id,' norm= ',norm
         call HZHINRM(ID,0,lum*Q2BIN0,1)
        endif
       enddo
*
       if (nev.eq.wtx) then
        if (nevhep.ne.0) then
         write(*,*) 'hz',xxxx,
     &   ' dijets sigma= ',nev,' +- ',nev**2+nsig/nevhep
        endif
       else
        if (lum.ne.0.) x=nev/lum
        write(*,*) 'hz',xxxx,
     & ' dijets sigma= ',x
       endif
*
      ENDIF
*
      RETURN
      END
