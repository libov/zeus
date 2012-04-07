      DOUBLE PRECISION FUNCTION SIG1(XX,VWGT)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION XX(10)
      DIMENSION DVEC(10),BET1(3),BET2(3)
      DIMENSION P1(0:3),P2(0:3),P3(0:3),Q(0:3)
      DIMENSION PPRO(0:3),PIEL(0:3),PSEL(0:3),PGAM(0:3)

      COMMON/BEAM/EPRO,EIEL
      COMMON/INVAR/XBJ,XIMIN,XM2,Q2
      COMMON/KINE/S,SP,BETA
      COMMON/FACTORS/EH2,CA,CF,XKGP,XKQP,N
      COMMON/PDFG/GLUE
      COMMON/FRACTION/X0,Y0
      COMMON/AZDEP/CTH22,STH12
      COMMON/FLAGS/ISCALER,ISCALEF,IALPHAS,IFRAG
      COMMON/LIMITS/Q2MIN,Q2MAX,XMIN,XMAX,YMIN,YMAX
      COMMON/FRAGP/EPS,HFRAC,XMD,ISL
      COMMON/MOMFRAC/XI

C Adopted from Massimo
      INTEGER IFL
      COMMON /DOFL/ IFL

      PARAMETER (TINY=1D-5)
      PARAMETER (PI=3.141592653589793D0)
      PARAMETER (PI3=PI*PI*PI)
      PARAMETER (PIB2=0.5D0*PI)
      PARAMETER (XME2=2.6D-7)
      PARAMETER (HBARC2=0.3894D6)
      PARAMETER (DTEST=1D-7)

      DATA NCOUNT/0/
      SAVE NCOUNT

C. SET IFAC2=0 AND IFACL=1 FOR L COMPONENT ONLY
C. SET IFAC2=1 AND IFACL=0 FOR 2 COMPONENT ONLY
      IFAC2=1
      IFACL=1
C Adopted from Massimo
      IF (IFL.EQ.0) IFACL=0
      IF (IFL.EQ.2) IFAC2=0
C. Y
      SS=4D0*EPRO*EIEL
      YU=MIN(YMAX,1D0)
      YL=MAX(YMIN,4*XM2/SS)
      XJACYBJ=YU-YL
      YBJ=YL+XJACYBJ*XX(1)
      OMYBJ=1D0-YBJ
C. Q2
      Q2U=MIN(YBJ*SS-4*XM2,Q2MAX)
      Q2L=MAX(XME2*YBJ*YBJ/OMYBJ,Q2MIN)
      XJACQ2=Q2U-Q2L
      Q2=Q2L+XJACQ2*XX(2)
C. CALCULATE XBJ AND CUT ON IT 
      XBJ=Q2/(YBJ*SS)
      IF( (XBJ.LE.MAX(0D0,XMIN)).OR.(XBJ.GE.MIN(1D0,XMAX) ))GOTO 1000
C. APPLY MAPPING ON XI
      XIMIN = XBJ*(4D0*XM2+Q2)/Q2
      IF(XIMIN.GE.1D0)GOTO 1000
      CALL BRM48(DVEC,1)
      CALL MAP(2D0,DVEC(1),XIMIN,1.D0,XI,XJACXI)
C. CALCULATE ENERGIES
      SH = Q2*(1D0-XBJ)/XBJ
      SPH = SH + Q2
      SP = XI*SPH
      S = SP - Q2
      SP3=SP*SP*SP
C. CHECK IF ABOVE THRESHOLD
      RHO = 4D0*XM2/S
      IF(RHO.GE.1D0)GOTO 1000
      BETA = DSQRT(1D0-RHO)

      RHOX = (4D0*XM2+Q2)/SP
      ONEMRX = 1D0-RHOX

      TINY2 = XI*TINY/XBJ
      X = TINY2+(1D0-TINY2)*XX(3)*XX(3)
      XJACX = 2D0*XX(3)
      X = 1D0-X*ONEMRX
      XJACX = XJACX*ONEMRX

      OMEGA = 2D0*Y0
      RHOTILDE = 1D0 - X0 * ONEMRX

      ONEMX = 1D0 - X

      XJACY = 2D0
      Y = XJACY*XX(4)-1D0
      TTT=TINY+(1D0-TINY)*Y*Y
      XJACY=XJACY*2D0*DABS(Y)
      IF(Y.GT.0D0)THEN
        TH=TTT*PIB2
      ELSE
        TH=PI-TTT*PIB2
      ENDIF
      Y=DCOS(TH)
      XJACY=XJACY*DSIN(TH)*PIB2
      ONEPY = 1D0 + Y
      ONEMY = 1D0 - Y

      XJAC1 = PI
      THETA1 = XJAC1*XX(5)
      CTH1 = DCOS(THETA1)
      STH1 = DSIN(THETA1)
      STH12 = STH1*STH1

      XJAC2 = PI
      THETA2 = XJAC2*XX(6)
      CTH2 = DCOS(THETA2)
      CTH22 = CTH2*CTH2
C. JACOBIAN BETWEEN {R1,...,R7} <-> {Q2,YBJ,X,Y,XI,TH1,TH2}
      XJAC = XJACQ2*XJACYBJ*XJACX*XJACY*XJACXI*XJAC1*XJAC2
C. SETUP BOOST TO PROTON-GAMMA* CMS
      BET1(1)=0D0
      BET1(2)=0D0
      BET1(3)=(XI-1D0)/(1D0+XI-2D0*XBJ)
C. SETUP BOOST TO LAB FRAME
C. FIRST CONSTRUCT P(PROTON) AND Q(PHOTON) IN LAB FRAME
C. H1 AND ZEUS TAKE PROTON IN +Z DIRECTION
      PPRO(0)=EPRO
      PPRO(1)=0D0
      PPRO(2)=0D0
      PPRO(3)=EPRO
C. AND INCIDENT ELECTRON IN -Z DIRECTION
      PIEL(0)=EIEL
      PIEL(1)=0D0
      PIEL(2)=0D0
      PIEL(3)=-EIEL
C. THE SCATTERED ELECTRON ENERGY AND ANGLE ARE GIVEN 
C. IN TERMS OF Q2,Y AND ENERGY OF INCIDENT ELECTRON
      ESEL  =(Q2+4D0*EIEL*EIEL*OMYBJ)/(4D0*EIEL)
      CTHSEL=(Q2-4D0*EIEL*EIEL*OMYBJ)/(Q2+4D0*EIEL*EIEL*OMYBJ)
      STHSEL=DSQRT(1D0-CTHSEL*CTHSEL)
      PSEL(0)=ESEL
      PSEL(1)=0D0
      PSEL(2)=ESEL*STHSEL
      PSEL(3)=ESEL*CTHSEL
C. NOW TO FIND PHOTON FOUR VECTOR
      DO 10 I=0,3
 10   PGAM(I)=PIEL(I)-PSEL(I)
C. SET UP BOOST TO LAB FRAME
      DO 15 I=1,3
 15   BET2(I)=(PPRO(I)+PGAM(I))/(PPRO(0)+PGAM(0))
C. FIND BOOST DEPENDENT ROTATION ANGLE
      CALL RANGLE(PGAM,BET2,COSA,SINA)
C.

CCCCCCCCCCCCCCCCCCCCCCCCCCC
C FIRST COMES THE "EVENT" C
CCCCCCCCCCCCCCCCCCCCCCCCCCC

C THIS IS +F(X,Y)/(1-X)/(1+Y)/(1-Y)

      CALL MANDEL3(
     &  X,Y,CTH1,THETA2,
     &  T1,U1,TP,UP,S3,S4,S5,U6,U7,BETA5,DA,DB,
     &  P1,P2,P3)
*
C*TC>

C. SET AUX SCALE TO W2
C      XMX2=max(P1(1)**2+P1(2)**2,P2(1)**2+P2(2)**2)
C       XMX2=P1(1)**2+P1(2)**2
       XMX2=(P1(1)**2+P1(2)**2+P2(1)**2+P2(2)**2)/2.
*
C      write(6,*) '**sig1: pt1= ',sqrt(P1(1)**2+P1(2)**2)
C      write(6,*) '**sig1: pt2= ',sqrt(P2(1)**2+P2(2)**2)
C      write(6,*) '**sig1: mu_r= ',sqrt(xmx2)
C. SET RENORMALIZATION SCALE
      CALL MSCALE(ISCALER,Q2,XM2,XMX2,XMUR2)
*
C. SET MASS FACTORIZATION SCALE
      CALL MSCALE(ISCALEF,Q2,XM2,XMX2,XMUF2)
      IF ( NCOUNT.EQ.0 ) THEN
         write(6,*) '**sig1: iscalef= ',iscaler
         write(6,*) '**sig1: mur= ',xmur2
         write(6,*) '**sig1: iscalef= ',iscalef
         write(6,*) '**sig1: muf= ',xmuf2
      END IF
C. CALCULATE STRONG COUPLING
      ALFAS=ALPHAS(IALPHAS,XMUR2,NEFF)
      B0=(33D0-2D0*NEFF)/3D0
C. CALCULATE EM COUPLING
      AEM2=HWUAEM(XMUR2)**2
C. FILL PDFS
      CALL PDF(XI,XMUF2)
C. OVERALL FACTOR
      XNORM = STH1*GLUE*ALFAS*ALFAS*Q2*EH2*N*XKGP/(64D0*PI3*XI)
      IF ( NCOUNT.EQ.0 ) THEN
        WRITE(*,*) 'ALFAS  = ',ALFAS
        WRITE(*,*) 'MUR2   = ',XMUR2
        WRITE(*,*) 'LOGMUR = ',DLOG(XMUR2/XM2)
        WRITE(*,*) 'MUF2   = ',XMUF2
        WRITE(*,*) 'LOGMUF = ',DLOG(XMUF2/XM2)
        WRITE(*,*) ' '
        WRITE(*,*) 'INTEGRATING NLO GLUON ...'
        WRITE(*,*) ' '
      END IF
C. CALL STRUCTURE FUNCTIONS

      CACF = CA*CF
      CFCF = CF*CF

C*TC<
C      Q(0)=(S-Q2)/(2D0*DSQRT(S))
C      Q(1)=0D0
C      Q(2)=0D0
C      Q(3)=-(S+Q2)/(2D0*DSQRT(S))
C      CALL BOOST(-1,BET1,Q)
C      CALL ROT(+1,Q,COSA,SINA)
C      CALL BOOST(-1,BET2,Q)
C      DO 20 I=0,3
C        IF(DABS(Q(I)-PGAM(I)).GT.DTEST)THEN
C           WRITE(*,*) 'TROUBLE IN ROTATION AND BOOST'
C           WRITE(*,*) I,DABS(Q(I)-PGAM(I))
C        ENDIF
C 20   CONTINUE

C. RANDOMIZE ABOUT Z AXIS
      CALL BRM48(DVEC,1)
      PHI=2D0*PI*DVEC(1)
      COSP=DCOS(PHI)
      SINP=DSIN(PHI)

      TMP1= P1(1)*COSP+P1(2)*SINP
      TMP2=-P1(1)*SINP+P1(2)*COSP
      P1(1)=TMP1
      P1(2)=TMP2
      TMP1= P2(1)*COSP+P2(2)*SINP
      TMP2=-P2(1)*SINP+P2(2)*COSP
      P2(1)=TMP1
      P2(2)=TMP2
      TMP1= P3(1)*COSP+P3(2)*SINP
      TMP2=-P3(1)*SINP+P3(2)*COSP
      P3(1)=TMP1
      P3(2)=TMP2

      CALL BOOST(-1,BET1,P1)
      CALL ROT(+1,P1,COSA,SINA)
      CALL BOOST(-1,BET2,P1)
      CALL BOOST(-1,BET1,P2)
      CALL ROT(+1,P2,COSA,SINA)
      CALL BOOST(-1,BET2,P2)
      CALL BOOST(-1,BET1,P3)
      CALL ROT(+1,P3,COSA,SINA)
      CALL BOOST(-1,BET2,P3)

C. PETERSON FRAGMENTATION
      IF (IFRAG.EQ.1) THEN
         IF(ISL.EQ.0)THEN
            CALL BRM48(DVEC,2)
            CALL FRAG(DVEC,P1,P2)
         ELSEIF(ISL.EQ.1)THEN
            CALL BRM48(DVEC,10)
            CALL FRAG(DVEC,P1,P2)
         ELSE
            WRITE(*,*) 'UNKNOWN ISL: ',ISL
            STOP
         ENDIF
      ENDIF

      HEVENTG = CACF*FGGC_CACF
     &     (X,Y,XM2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DA,DB)
     &        + CFCF*FGGC_CFCF
     &     (X,Y,XM2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DA,DB)
      HEVENTG = HEVENTG*BETA5*S/(SP3*ONEPY*ONEMY*ONEMX)
      HEVENTL = CACF*FGLC_CACF
     &     (X,Y,XM2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DA,DB)
     &        + CFCF*FGLC_CFCF
     &     (X,Y,XM2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DA,DB)
      HEVENTL = HEVENTL*BETA5*S/(SP3*ONEPY*ONEMY*ONEMX)

C PLOT EVENT

      WGTG = HEVENTG*XNORM*XJAC
      WGTL = HEVENTL*XNORM*XJAC
      WGT2 = WGTG+3D0*WGTL
      WGTL = 2D0*WGTL
      WGT = (1D0+OMYBJ*OMYBJ)*WGT2*IFAC2-YBJ*YBJ*WGTL*IFACL
      WGT = 2D0*PI*AEM2*HBARC2*WGT/(YBJ*Q2*Q2)
      WGT = WGT*VWGT
*
      if (wgt.ne.wgt) then
       write(6,*) '**sig1: calling fhist EVENT p1,p2,p3= ',
     & p1,p2,p3
       write(6,*) '**sig1: start ' 
       write(6,*) '**sig1: wgt= ',wgt,' vwgt= ',vwgt,' XNORM= ',xnorm
       write(6,*) '**sig1: = HEVENTL',HEVENTL,' XJAC= ',XJAC
      endif
*
      CALL FHIST(WGT,P1,P2,P3)
      HWGT=WGT/VWGT

CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C THEN COMES THE "COUNTER-EVENT" C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

C COLLINEAR PART

      IF ( ONEPY.LT.OMEGA ) THEN

        YTMP = -1D0

        CALL MANDEL3(
     &    X,YTMP,CTH1,THETA2,
     &    T1,U1,TP,UP,S3,S4,S5,U6,U7,BETA5,DA,DB,
     &    P1,P2,P3)

        if ( P1(1).ne. P1(1)) then
         write(6,*) ' p1= ',p1
         write(6,*) ' COSP= ',COSP,' SINP= ',SINP
         write(6,*) ' X,YTMP,CTH1,THETA2= ',X,YTMP,CTH1,THETA2
         write(6,*) ' T1,U1,TP,UP,S3,S4,S5,U6,U7,BETA5,DA,DB= ',
     &   T1,U1,TP,UP,S3,S4,S5,U6,U7,BETA5,DA,DB
        endif

C. RANDOMIZE ABOUT Z AXIS
        TMP1= P1(1)*COSP+P1(2)*SINP
        TMP2=-P1(1)*SINP+P1(2)*COSP
        P1(1)=TMP1
        P1(2)=TMP2
        TMP1= P2(1)*COSP+P2(2)*SINP
        TMP2=-P2(1)*SINP+P2(2)*COSP
        P2(1)=TMP1
        P2(2)=TMP2
        TMP1= P3(1)*COSP+P3(2)*SINP
        TMP2=-P3(1)*SINP+P3(2)*COSP
        P3(1)=TMP1
        P3(2)=TMP2

        CALL BOOST(-1,BET1,P1)
        CALL ROT(+1,P1,COSA,SINA)
        CALL BOOST(-1,BET2,P1)
        CALL BOOST(-1,BET1,P2)
        CALL ROT(+1,P2,COSA,SINA)
        CALL BOOST(-1,BET2,P2)
        CALL BOOST(-1,BET1,P3)
        CALL ROT(+1,P3,COSA,SINA)
        CALL BOOST(-1,BET2,P3)

        IF (IFRAG.EQ.1) THEN
           CALL FRAG(DVEC,P1,P2)
        ENDIF

C     FIRST THE PIECE FROM THE DISTRIBUTION -F(X,-1)/(1-X)/(1+Y)/2

        CEVENTG1 = CACF*FGGC_CACF
     &        (X,YTMP,XM2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DA,DB)
     &           + CFCF*FGGC_CFCF
     &        (X,YTMP,XM2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DA,DB)
        CEVENTG1 = -CEVENTG1*BETA5*S/(SP3*ONEPY*2D0*ONEMX)
        CEVENTL1 = CACF*FGLC_CACF
     &        (X,YTMP,XM2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DA,DB)
     &           + CFCF*FGLC_CFCF
     &        (X,YTMP,XM2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DA,DB)
        CEVENTL1 = -CEVENTL1*BETA5*S/(SP3*ONEPY*2D0*ONEMX)

C THEN THE COLLINEAR CONTRIBUTION

        FX = ONEMX*ONEMX*(1D0+1D0/(X*X))+1D0
        CEVENT2 = 16D0*CACF*BETA5*
     &  (DLOG(SP/XMUF2)+DLOG(SP/S)+2D0*DLOG(ONEMX)+DLOG(0.5D0*OMEGA))*
     &  FX/(SP*ONEMX*OMEGA)
        CEVENTG2 = CEVENT2*BGQED(X*T1,X*SP,XM2,Q2)
        CEVENTL2 = CEVENT2*BLQED(X*T1,X*SP,XM2,Q2)
        CEVENTG = CEVENTG1 + CEVENTG2
        CEVENTL = CEVENTL1 + CEVENTL2

C PLOT IT

        WGTG = CEVENTG*XNORM*XJAC
        WGTL = CEVENTL*XNORM*XJAC
        WGT2 = WGTG+3D0*WGTL
        WGTL = 2D0*WGTL
        WGT = (1D0+OMYBJ*OMYBJ)*WGT2*IFAC2-YBJ*YBJ*WGTL*IFACL
        WGT = 2D0*PI*AEM2*HBARC2*WGT/(YBJ*Q2*Q2)
        WGT = WGT*VWGT
*
C      write(6,*) '**sig1: calling fhist Counter-EVENT p1,p2,p3= ',
C     & p1,p2,p3
*
      if (wgt.ne.wgt) then
       write(6,*) '**sig1: calling fhist EVENT p1= ',p1
       write(6,*) '**sig1: calling fhist EVENT p2= ',p2
       write(6,*) '**sig1: calling fhist EVENT p3= ',p3
       write(6,*) '**sig1: collinear first ' 
       write(6,*) '**sig1: wgt= ',wgt,' vwgt= ',vwgt,' XNORM= ',xnorm
       write(6,*) '**sig1: HEVENTL=',HEVENTL,' XJAC= ',XJAC
       write(6,*) '**sig1: HBARC2= ',HBARC2,' YBJ = ',YBJ,' Q2= ',Q2
       write(6,*) '**sig1: WGT2= ',WGT2,' WGTL = ',WGTL
      endif
*
        CALL FHIST(WGT,P1,P2,P3)
        CWGT=WGT/VWGT

      ELSE

        CWGT=0D0

      END IF

C SOFT PART

      IF ( X.GT.RHOTILDE ) THEN

        XTMP = +1D0
        YTMP = -1D0

        CALL MANDEL3(
     &    XTMP,Y,CTH1,THETA2,
     &    T1,U1,TP,UP,S3,S4,S5,U6,U7,BETA5,DA,DB,
     &    P1,P2,P3)

        TMP1= P1(1)*COSP+P1(2)*SINP
        TMP2=-P1(1)*SINP+P1(2)*COSP
        P1(1)=TMP1
        P1(2)=TMP2
        TMP1= P2(1)*COSP+P2(2)*SINP
        TMP2=-P2(1)*SINP+P2(2)*COSP
        P2(1)=TMP1
        P2(2)=TMP2
        TMP1= P3(1)*COSP+P3(2)*SINP
        TMP2=-P3(1)*SINP+P3(2)*COSP
        P3(1)=TMP1
        P3(2)=TMP2
        
        CALL BOOST(-1,BET1,P1)
        CALL ROT(+1,P1,COSA,SINA)
        CALL BOOST(-1,BET2,P1)
        CALL BOOST(-1,BET1,P2)
        CALL ROT(+1,P2,COSA,SINA)
        CALL BOOST(-1,BET2,P2)
        CALL BOOST(-1,BET1,P3)
        CALL ROT(+1,P3,COSA,SINA)
        CALL BOOST(-1,BET2,P3)

        IF (IFRAG.EQ.1) THEN
           CALL FRAG(DVEC,P1,P2)
        ENDIF

C FIRST THE PIECE FROM THE DISTRIBUTION -F(1,Y)/(1-X)/(1+Y)/(1-Y)

        XEVENTG = CACF*FGGC_CACF
     &        (XTMP,Y,XM2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DA,DB)
     &          + CFCF*FGGC_CFCF
     &        (XTMP,Y,XM2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DA,DB)
        XEVENTG = -XEVENTG*BETA5*S/(SP3*ONEPY*ONEMY*ONEMX)
        XEVENTL = CACF*FGLC_CACF
     &        (XTMP,Y,XM2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DA,DB)
     &          + CFCF*FGLC_CFCF
     &        (XTMP,Y,XM2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DA,DB)
        XEVENTL = -XEVENTL*BETA5*S/(SP3*ONEPY*ONEMY*ONEMX)

C ADD SOFT-VIRTUAL

        ONEMRT = 1D0-RHOTILDE
        SVEVENTG = CACF*VOKG2(T1,SP,XM2,Q2,RHOTILDE)
     &           + CFCF*VQEDG2(T1,SP,XM2,Q2,RHOTILDE)
     &           + BGQED(T1,SP,XM2,Q2)*( 
     &           - 32D0*CACF*DLOG(ONEMRT)*DLOG(XMUF2/XM2)
     &           + 8D0*CF*B0*DLOG(XMUR2/XMUF2) )
        SVEVENTG = BETA*SVEVENTG/(SP*4D0*ONEMRT)
        SVEVENTL = CACF*VOKL2(T1,SP,XM2,Q2,RHOTILDE)
     &           + CFCF*VQEDL2(T1,SP,XM2,Q2,RHOTILDE)
     &           + BLQED(T1,SP,XM2,Q2)*( 
     &           - 32D0*CACF*DLOG(ONEMRT)*DLOG(XMUF2/XM2)
     &           + 8D0*CF*B0*DLOG(XMUR2/XMUF2) )
        SVEVENTL = BETA*SVEVENTL/(SP*4D0*ONEMRT)

C PLOT IT

        WGTG = ( XEVENTG + SVEVENTG )*XNORM*XJAC
        WGTL = ( XEVENTL + SVEVENTL )*XNORM*XJAC
        WGT2 = WGTG+3D0*WGTL
        WGTL = 2D0*WGTL
        WGT = (1D0+OMYBJ*OMYBJ)*WGT2*IFAC2-YBJ*YBJ*WGTL*IFACL
        WGT = 2D0*PI*AEM2*HBARC2*WGT/(YBJ*Q2*Q2)
        WGT = WGT*VWGT
*
C      write(6,*) '**sig1: calling fhist soft-virtual p1,p2,p3= ',
C     & p1,p2,p3
*
      if (wgt.ne.wgt) then
       write(6,*) '**sig1: calling fhist EVENT p1,p2,p3= ',
     & p1,p2,p3
       write(6,*) '**sig1: soft virtual ' 
       write(6,*) '**sig1: wgt= ',wgt,' vwgt= ',vwgt,' XNORM= ',xnorm
       write(6,*) '**sig1: = HEVENTL',HEVENTL,' XJAC= ',XJAC
      endif
*
        CALL FHIST(WGT,P1,P2,P3)
        SVWGT=WGT/VWGT

C COLLINEAR AND SOFT IF NEEDED

        IF ( ONEPY.LT.OMEGA ) THEN

          CALL MANDEL3(
     &      XTMP,YTMP,CTH1,THETA2,
     &      T1,U1,TP,UP,S3,S4,S5,U6,U7,BETA5,DA,DB,
     &      P1,P2,P3)

          TMP1= P1(1)*COSP+P1(2)*SINP
          TMP2=-P1(1)*SINP+P1(2)*COSP
          P1(1)=TMP1
          P1(2)=TMP2
          TMP1= P2(1)*COSP+P2(2)*SINP
          TMP2=-P2(1)*SINP+P2(2)*COSP
          P2(1)=TMP1
          P2(2)=TMP2
          TMP1= P3(1)*COSP+P3(2)*SINP
          TMP2=-P3(1)*SINP+P3(2)*COSP
          P3(1)=TMP1
          P3(2)=TMP2

          CALL BOOST(-1,BET1,P1)
          CALL ROT(+1,P1,COSA,SINA)
          CALL BOOST(-1,BET2,P1)
          CALL BOOST(-1,BET1,P2)
          CALL ROT(+1,P2,COSA,SINA)
          CALL BOOST(-1,BET2,P2)
          CALL BOOST(-1,BET1,P3)
          CALL ROT(+1,P3,COSA,SINA)
          CALL BOOST(-1,BET2,P3)

          IF (IFRAG.EQ.1) THEN
             CALL FRAG(DVEC,P1,P2)
          ENDIF

C FIRST THE PIECE FROM THE DISTRIBUTION +F(1,-1)/(1-X)/(1+Y)/2

          SCEVENTG1 = CACF*FGGC_CACF
     &         (XTMP,YTMP,XM2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DA,DB)
     &              + CFCF*FGGC_CFCF
     &         (XTMP,YTMP,XM2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DA,DB)
          SCEVENTG1 = SCEVENTG1*BETA5*S/(SP3*ONEPY*2D0*ONEMX)
          SCEVENTL1 = CACF*FGLC_CACF
     &         (XTMP,YTMP,XM2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DA,DB)
     &              + CFCF*FGLC_CFCF
     &         (XTMP,YTMP,XM2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DA,DB)
          SCEVENTL1 = SCEVENTL1*BETA5*S/(SP3*ONEPY*2D0*ONEMX)

C THEN THE COLLINEAR CONTRIBUTION

          FX = 1D0
          SCEVENT2 = -16D0*CACF*BETA5*
     &    (DLOG(SP/XMUF2)+DLOG(SP/S)+2D0*DLOG(ONEMX)+DLOG(0.5D0*OMEGA))*
     &    FX/(SP*ONEMX*OMEGA)
          SCEVENTG2 = SCEVENT2*BGQED(T1,SP,XM2,Q2)
          SCEVENTL2 = SCEVENT2*BLQED(T1,SP,XM2,Q2)
          SCEVENTG = SCEVENTG1 + SCEVENTG2
          SCEVENTL = SCEVENTL1 + SCEVENTL2

C PLOT IT

          WGTG = ( SCEVENTG )*XNORM*XJAC
          WGTL = ( SCEVENTL )*XNORM*XJAC
          WGT2 = WGTG+3D0*WGTL
          WGTL = 2D0*WGTL
          WGT = (1D0+OMYBJ*OMYBJ)*WGT2*IFAC2-YBJ*YBJ*WGTL*IFACL
          WGT = 2D0*PI*AEM2*HBARC2*WGT/(YBJ*Q2*Q2)
          WGT = WGT*VWGT
*
      if (wgt.ne.wgt) then
       write(6,*) '**sig1: calling fhist EVENT p1,p2,p3= ',
     & p1,p2,p3 
       write(6,*) '**sig1: collinear '
       write(6,*) '**sig1: wgt= ',wgt,' vwgt= ',vwgt,' XNORM= ',xnorm
       write(6,*) '**sig1: = HEVENTL',HEVENTL,' XJAC= ',XJAC
      endif
          CALL FHIST(WGT,P1,P2,P3)
          SCWGT=WGT/VWGT

        ELSE

          SCWGT=0D0

        END IF

        SWGT=SVWGT+SCWGT

      ELSE

        SWGT=0D0

      END IF

C SUM ALL CONTRIBUTIONS

      SIG1=HWGT+CWGT+SWGT

      NCOUNT = 1
      RETURN
C. REJECTED EVENTS GET WEIGHT ZERO
 1000 CONTINUE
      SIG1=0D0
      RETURN
      END
