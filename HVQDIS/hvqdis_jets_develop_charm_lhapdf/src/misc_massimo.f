C.--------------------------------------------------------
C. MAPPING AND DILOG ROUTINES
C.--------------------------------------------------------
C.
C---------------------------------------------------------------
      SUBROUTINE MAP(A,R,XMIN,XMAX,X,XJAC)
      IMPLICIT DOUBLE PRECISION (A-Z)
      AT=1.D0-A
      XAT=1.D0/AT
      GMIN=XAT*XMIN**AT
      GMAX=XAT*XMAX**AT
      Y=GMIN+R*(GMAX-GMIN)
      X=(Y*AT)**XAT
      XJAC=(GMAX-GMIN)*X**A
      RETURN
      END
C---------------------------------------------------------------
C RHO DEPENDENT MAPPING FOR COSINE
      SUBROUTINE MAPSC(PARTH1,CTH1,XJAC,RO)
      IMPLICIT DOUBLE PRECISION (A-Z)
      BB = 1.D0 - RO*RO / 16.D0
      XLGBB = DLOG( (1.D0 + BB ) / ( 1.D0 - BB ) )
      YY = ( PARTH1 * 2.D0 - 1.D0 ) * XLGBB
      XJAC = 2.D0 * XLGBB
      EXPYY = DEXP(-YY)
      CTH1 = ( 1.D0 - EXPYY ) / ( 1.D0 + EXPYY ) / BB
      XJAC = XJAC * 2.D0 * EXPYY / BB
      XJAC = XJAC / ( 1.D0 + EXPYY ) / ( 1.D0 + EXPYY )
      RETURN
      END
C-----------------------------------------------------------------------
C LOGARITHMIC MAPPING AT LOWER LIMIT (MUST BE NONZERO)
      SUBROUTINE MAPS2(S2,X,SMIN,SMAX,DS)
      IMPLICIT DOUBLE PRECISION (A-Z)
      Y=SMAX/SMIN
      S2=SMIN*Y**X
      DS=S2*DLOG(Y)
      RETURN
      END
C-----------------------------------------------------------------------
C POWER MAPPING AT LOWER LIMIT
      SUBROUTINE MAPS3(S2,X,SMIN,SMAX,DS)
      IMPLICIT DOUBLE PRECISION (A-Z)
      DS = (SMAX - SMIN) / (SMAX*SMIN)
      S2 = SMIN / ( 1.D0 - X * DS * SMIN )
      DS = DS * S2**2
      RETURN
      END
C-----------------------------------------------------------------------
C LOGARITHMIC MAPPING AT UPPER LIMIT (MUST BE NONZERO)
      SUBROUTINE MAPS2U(S2,X,SMIN,SMAX,DS)
      IMPLICIT DOUBLE PRECISION (A-Z)
      Y=SMIN/SMAX
      S2=SMAX*Y**X
      DS=-S2*DLOG(Y)
      RETURN
      END
C     ---------------- END OF MAPPINGS ------------------------
C
C --- DILOG FUNCTION ---
      DOUBLE PRECISION FUNCTION DILOG(X)
      IMPLICIT DOUBLE PRECISION (A-Z)
      PARAMETER (PI6=1.644934066848226D+00)
      PARAMETER (EEN=1.D+00)
      PARAMETER (VIER=0.25D+00)
      PARAMETER (B2=+2.7777777777777778D-02)
      PARAMETER (B3=-2.7777777777777778D-04)
      PARAMETER (B4=+4.7241118669690098D-06)
      PARAMETER (B5=-9.1857730746619641D-08)
      PARAMETER (B6=+1.8978869988971001D-09)
      PARAMETER (B7=-4.0647616451442256D-11)
      PARAMETER (B8=+8.9216910204564523D-13)
    1 IF(X.LT.0.D0)GO TO 3
      IF(X.GT.0.5D0)GO TO 4
      Z=-DLOG(1.D0-X)
    7 Z2=Z*Z
      DILOG=Z*(Z2*(Z2*(Z2*(Z2*(Z2*(Z2*(Z2*B8+B7)+B6)
     1  +B5)+B4)+B3)+B2)+EEN)-Z2*VIER
      IF(X.GT.EEN)DILOG=-DILOG-.5D0*U*U+2.D0*PI6
      RETURN
    3 IF(X.GT.-EEN)GO TO 5
      Y=EEN/(EEN-X)
      Z=-DLOG(EEN-Y)
      Z2=Z*Z
      U=DLOG(Y)
      DILOG=Z*(Z2*(Z2*(Z2*(Z2*(Z2*(Z2*(Z2*B8+B7)+B6)
     1  +B5)+B4)+B3)+B2)+EEN)-Z2*VIER-U*(Z+.5D0*U)-PI6
      RETURN
    4 IF(X.GE.EEN)GO TO 10
      Y=EEN-X
      Z=-DLOG(X)
    6 U=DLOG(Y)
      Z2=Z*Z
      DILOG=-Z*(Z2*(Z2*(Z2*(Z2*(Z2*(Z2*(Z2*B8+B7)+B6)
     1  +B5)+B4)+B3)+B2)+EEN-U)+Z2*VIER+PI6
      IF(X.GT.EEN)DILOG=-DILOG-.5D0*Z*Z+PI6*2.D0
      RETURN
    5 Y=EEN/(EEN-X)
      Z=-DLOG(Y)
      Z2=Z*Z
      DILOG=-Z*(Z2*(Z2*(Z2*(Z2*(Z2*(Z2*(Z2*B8+B7)+B6)
     1  +B5)+B4)+B3)+B2)+EEN)-Z2*VIER
      RETURN
   10 IF(X.EQ.EEN)GO TO 20
      XX=1.D0/X
      IF(X.GT.2.D0)GO TO 11
      Z=DLOG(X)
      Y=1.D0-XX
      GO TO 6
   11 U=DLOG(X)
      Z=-DLOG(1.D0-XX)
      GO TO 7
   20 DILOG=PI6
      RETURN
      END


C. PETERSON FRAGMENTATION (WITH OPTIONAL SEMI LEPTONIC DECAY)
      SUBROUTINE FRAG(DVEC,P1,P2)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION P1(0:3),P2(0:3),DVEC(10),BETA(3)
      COMMON/FRAGP/EPS,HFRAC,XMD,ISL
C M.C. add this coomon for IFRAG
      COMMON/FLAGS/ISCALER,ISCALEF,IALPHAS,IFRAG
C M.C. common to save quark before fragmentation
      DIMENSION QP1(0:3),QP2(0:3)
      COMMON/QUARKP/QP1,QP2
      PARAMETER (PI=3.14159265358979D0)

C M.C. save quark before fragmentation
      DO i=0,3
         QP1(i)=P1(i)
         QP2(i)=P2(i)
      ENDDO

      XMD2=XMD*XMD
C DO PETERSON ON QUARK 1
      Z1=RTSAFE(EPS,DVEC(1),0D0,1D0,0.01D0)
      IF (MOD(IFRAG,10).EQ.2) THEN ! M.C. SCALE E+P not P !
         P=DSQRT(P1(1)*P1(1)+P1(2)*P1(2)+P1(3)*P1(3))
         EPP=Z1*(P1(0)+P)
         EMP=XMD2/EPP
         Z1=0.5D0*(EPP-EMP)/P
      ENDIF
      P1(1)=Z1*P1(1)
      P1(2)=Z1*P1(2)
      P1(3)=Z1*P1(3)
      P1(0)=DSQRT(XMD2+P1(1)*P1(1)+P1(2)*P1(2)+P1(3)*P1(3))
C DO PETERSON ON QUARK 2
      Z2=RTSAFE(EPS,DVEC(2),0D0,1D0,0.01D0)
      IF (MOD(IFRAG,10).EQ.2) THEN ! M.C. SCALE E+P not P !
         P=DSQRT(P2(1)*P2(1)+P2(2)*P2(2)+P2(3)*P2(3))
         EPP=Z2*(P2(0)+P)
         EMP=XMD2/EPP
         Z2=0.5D0*(EPP-EMP)/P
      ENDIF
      P2(1)=Z2*P2(1)
      P2(2)=Z2*P2(2)
      P2(3)=Z2*P2(3)
      P2(0)=DSQRT(XMD2+P2(1)*P2(1)+P2(2)*P2(2)+P2(3)*P2(3))
C IF NO DECAY THEN RETURN
      IF(ISL.EQ.0)RETURN
      IF(ISL.EQ.1) then
C
C SEMI-LEPTONIC CHARM DECAY FOLLOWS
C
C THE MOMENTUM DISTRIBUTION OF THE SEMI-LEPTONIC DECAY ELECTRON 
C IN THE DECAYING HADRON REST FRAME IS FROM RAPGAP (VIA WOUTER 
C VERKERKE).  THE RAPGAP DISTRIBUTION HAS BEEN CROSS CHECKED 
C USING HERWIG BY KIRSTIN HEBBEL.
C
C THE DIRECTION OF THE ELECTRON IS ISOTROPIC.
C
C --> FIRST DECAY HADRON 1
C FIND BETA TO REST FRAME OF P1
      DO I=1,3
         BETA(I)=P1(I)/P1(0)
      ENDDO
C BOOST TO REST FRAME (AS A CHECK)
C      CALL BOOST(+1,BETA,P1)
C      CALL VWRITE(P1)
C      STOP
C GENERATE ELECTRON IN P1 REST FRAME
C ISOTROPIC THETA,PHI DISTRIBUTION
      THETA=DACOS(1D0-DVEC(3))
      IF(DVEC(9).GT.0.5D0)THETA=PI-THETA
      PHI=2D0*PI*DVEC(4)
C GENERATE SL 4-VECTOR IN REST
      P1(0)=XSLP(DVEC(5))
      P1(1)=P1(0)*DSIN(PHI)*DSIN(THETA)
      P1(2)=P1(0)*DCOS(PHI)*DSIN(THETA)
      P1(3)=P1(0)*DCOS(THETA)
C BOOST BACK TO LAB FRAME
      CALL BOOST(-1,BETA,P1)
C --> THEN DECAY HADRON 2
C FIND BETA TO REST FRAME OF P2
      DO I=1,3
         BETA(I)=P2(I)/P2(0)
      ENDDO
C BOOST TO REST FRAME (AS A CHECK)
C      CALL BOOST(+1,BETA,P2)
C      CALL VWRITE(P2)
C      STOP
C GENERATE ELECTRON IN P2 REST FRAME
C GENERATE ISOTROPIC THETA,PHI DISTRIBUTION
      THETA=DACOS(1D0-DVEC(6))
      IF(DVEC(10).GT.0.5D0)THETA=PI-THETA
      PHI=2D0*PI*DVEC(7)
C GENERATE SL 4-VECTOR IN REST
      P2(0)=XSLP(DVEC(8))
      P2(1)=P2(0)*DSIN(PHI)*DSIN(THETA)
      P2(2)=P2(0)*DCOS(PHI)*DSIN(THETA)
      P2(3)=P2(0)*DCOS(THETA)
C. BOOST BACK TO LAB FRAME
      CALL BOOST(-1,BETA,P2)
      ELSE IF (ISL.gt.10) then
         CALL MYDECAY2(ISL,P1,P2,DVEC)
      ENDIF
      RETURN
      END
C. RETURNS D AND J.  CALLED BY RTSAFE.
      SUBROUTINE FUNCD(EPS,U,X,F,DF)
      IMPLICIT DOUBLE PRECISION ( A-H,O-Z )
      F=XJ(X,EPS)/XJ(1D0,EPS)-U
      DF=XD(X,EPS)/XJ(1D0,EPS)
      RETURN
      END
C. PETERSON FRAGMENTATION FUNCTION WITH N=1
      FUNCTION XD(Z,EPS)
      IMPLICIT DOUBLE PRECISION ( A-H,O-Z )
      XD=Z*Z+(EPS-2D0)*Z+1D0
      XD=XD*XD
      XD=Z*(1D0-Z)*(1D0-Z)/XD
      RETURN
      END
C. PETERSON FRAGMENTATION FUNCTION INTEGRATED FROM 0 TO Z WITH N=1
      FUNCTION XJ(Z,EPS)
      IMPLICIT DOUBLE PRECISION ( A-H,O-Z )
      B=0.5D0*(2D0-EPS)
      OPB=1D0+B
      B2=B*B
      A2=1D0-B2
      A=DSQRT(A2)
      Z2=Z*Z
      ZMB=Z-B
      F=Z2-2D0*Z*B+1D0
      XJ = 0.5D0*DLOG(F) - Z*(Z*B-1D0)/(OPB*F)
     &   + (B2+B-1D0)*(DATAN(ZMB/A)-DATAN(-B/A))/(OPB*A) 
      RETURN
      END
C. CONCATENATE STR1 AND STR2 INTO STR
      SUBROUTINE STRCAT(STR1,STR2,STR)
      CHARACTER *(*) STR1,STR2,STR
      L1=ISTRL(STR1)
      L2=ISTRL(STR2)
      L =LEN(STR)
      IF(L.LT.L1+L2) THEN
          WRITE(*,*) 'ERROR: L1+L2>L IN STRCAT'
          WRITE(*,*) 'L1=',L1,' STR1=',STR1
          WRITE(*,*) 'L2=',L2,' STR2=',STR2
          WRITE(*,*) 'L=',L
          STOP
      ENDIF
      IF(L1.NE.0) STR(1:L1)=STR1(1:L1)
      IF(L2.NE.0) STR(L1+1:L1+L2)=STR2(1:L2)
      IF(L1+L2+1.LE.L) STR(L1+L2+1:L)= ' '
      END
C. RETURNS THE POSITION OF THE LAST NON-BLANK CHARACTER IN STRING
      FUNCTION ISTRL(STRING)
      CHARACTER * (*) STRING
      I = LEN(STRING)
      DOWHILE(I.GT.0.AND.STRING(I:I).EQ.' ')
         I=I-1
      ENDDO
      ISTRL = I
      END
C. GIVES BOOST IN TRANSVERSE PLANE SUCH THAT P1_T+P2_T=K_T
      SUBROUTINE PTKICK(XKT,PHI,P1,P2)
      IMPLICIT DOUBLE PRECISION ( A-H,O-Z )
      DIMENSION P1(0:3),P2(0:3)
      DIMENSION BETA(3)
      E=DSQRT(XKT**2+(P1(0)+P2(0))**2)
      BETA(1)=-XKT*DSIN(PHI)/E
      BETA(2)=-XKT*DCOS(PHI)/E
      BETA(3)=0D0
      CALL BOOST(-1,BETA,P1)
      CALL BOOST(-1,BETA,P2)
      RETURN
      END
C. WRITE A 4 VECTOR
      SUBROUTINE VWRITE(P)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION P(0:3)
      WRITE(*,*) 'P(0) = ',P(0)
      WRITE(*,*) 'P(1) = ',P(1)
      WRITE(*,*) 'P(2) = ',P(2)
      WRITE(*,*) 'P(3) = ',P(3)
      WRITE(*,*) 'P.P  = ',DOT(P,P)
      WRITE(*,*) ' '
      RETURN
      END
C. BOOST FOR ARBITRARY BETA. ISIGN GIVES RELATIVE DIRECTION OF BOOST
C. ISIGN=+1: FROM BETA TO REST
C.      =-1: FROM REST TO BETA
      SUBROUTINE BOOST(ISIGN,BETA,P)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION BETA(3),P(0:3),V(3)
      DO 1 I=1,3
 1    V(I)=P(I)
      B2=DOT3(BETA,BETA)
      G=1D0/DSQRT(1D0-B2)
      BV=DOT3(BETA,V)
      FT=G*(BV*(1D0-1D0/G)/B2-ISIGN*P(0))
      DO 2 I=1,3
         P(I)=V(I)+BETA(I)*FT
 2    CONTINUE
      P(0)=G*(P(0)-ISIGN*BV)
      RETURN
      END
C. FIND ROTATION ANGLE
      SUBROUTINE RANGLE(P,BETA,COSA,SINA)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION P(0:3),PTMP(0:3),V(3),BETA(3)
      DO 1 I=0,3
 1    PTMP(I)=P(I)
      CALL BOOST(+1,BETA,PTMP)
      DO 2 I=1,3
 2    V(I)=PTMP(I)
      R=DSQRT(DOT3(V,V))
      COSA=-PTMP(3)/R
      SINA=DSQRT(1D0-COSA**2)
      RETURN
      END
C. FIND ROTATION ANGLE (2ND VERSION)
      SUBROUTINE RANGLE2(P,BETA,COSA,SINA)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION P(0:3),PTMP(0:3),V(3),BETA(3)
      DO 1 I=0,3
 1        PTMP(I)=P(I)
      CALL BOOST(+1,BETA,PTMP)
      DO 2 I=1,3
 2        V(I)=PTMP(I)
      R=DSQRT(DOT3(V,V))
      COSA=-PTMP(3)/R
      SINA=-PTMP(2)/R
      RETURN
      END
C. ROTATE 3 VECTOR PART OF P ABOUT X AXIS
C. ISIGN=+1: COUNTER CLOCKWISE
C.       -1: CLOCKWISE
      SUBROUTINE ROT(ISIGN,P,COSA,SINA)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION P(0:3)
      T2=+COSA*P(2)+ISIGN*SINA*P(3)
      T3=-ISIGN*SINA*P(2)+COSA*P(3)
      P(2)=T2
      P(3)=T3
      RETURN
      END
C. RAPIDITY
      FUNCTION RAPID(P)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION P(0:3)
      AN=P(0)+P(3)
      AD=P(0)-P(3)
      RAPID=0.5D0*DLOG(AN/AD)
      RETURN
      END
C. PSEUDO-RAPIDITY
      FUNCTION SRAPID(P)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION P(0:3)
      PM=DSQRT(P(1)*P(1)+P(2)*P(2)+P(3)*P(3))
      AN=PM+P(3)
      AD=PM-P(3)
      R=AN/AD
      IF(R.LT.0)THEN
         WRITE(*,*) AN,AD
         SRAPID=1D20
         RETURN
      ENDIF
      SRAPID=0.5D0*DLOG(R)
      RETURN
      END
C. PT
      FUNCTION EPERP(P)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION P(0:3)
      EPERP=DSQRT(P(1)*P(1)+P(2)*P(2))
      RETURN
      END
C. PZ
      FUNCTION EPERPZ(P)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION P(0:3)
      EPERPZ=P(3)
      RETURN
      END
C. DOT PRODUCT
      FUNCTION DOT(P,Q)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION P(0:3),Q(0:3)
      DOT=P(0)*Q(0)-P(1)*Q(1)-P(2)*Q(2)-P(3)*Q(3)
      RETURN
      END
C. DOT PRODUCT
      FUNCTION DOT3(V,W)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION V(3),W(3)
      DOT3=V(1)*W(1)+V(2)*W(2)+V(3)*W(3)
      RETURN
      END
C. FUNCTION TO RECONSTRUCT AZIMUTHAL ANGLE
C. N=0 RETURNS   0<PHI<2PI
C. N=1 RETURNS -PI<PHI<+PI
      FUNCTION PHI(N,P)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION P(0:3)
      PI=2*DACOS(0D0)
      PT=EPERP(P)
      IF(P(2).GE.0.D0)THEN
         PHI=DACOS(P(1)/PT)
      ELSE
         PHI=DACOS(-P(1)/PT)+PI
      ENDIF
      IF(N.EQ.1)PHI=PHI-2*PI*IDNINT(0.5*PHI/PI)
      RETURN
      END
C.
      function rtsafe(eps,u,x1,x2,xacc)
      IMPLICIT DOUBLE PRECISION ( A-H,O-Z )
      parameter (maxit=100)
      call funcd(eps,u,x1,fl,df)
      call funcd(eps,u,x2,fh,df)
      if((fl.gt.0..and.fh.gt.0.).or.(fl.lt.0..and.fh.lt.0.))pause
     *'root must be bracketed in rtsafe'
      if(fl.eq.0.)then
        rtsafe=x1
        return
      else if(fh.eq.0.)then
        rtsafe=x2
        return
      else if(fl.lt.0.)then
        xl=x1
        xh=x2
      else
        xh=x1
        xl=x2
      endif
      rtsafe=.5*(x1+x2)
      dxold=dabs(x2-x1)
      dx=dxold
      call funcd(eps,u,rtsafe,f,df)
      do 11 j=1,maxit
        if(((rtsafe-xh)*df-f)*((rtsafe-xl)*df-f).ge.0..or.dabs(2.*
     *f).gt.dabs(dxold*df) ) then
          dxold=dx
          dx=0.5*(xh-xl)
          rtsafe=xl+dx
          if(xl.eq.rtsafe)return
        else
          dxold=dx
          dx=f/df
          temp=rtsafe
          rtsafe=rtsafe-dx
          if(temp.eq.rtsafe)return
        endif
        if(dabs(dx).lt.xacc) return
        call funcd(eps,u,rtsafe,f,df)
        if(f.lt.0.) then
          xl=rtsafe
        else
          xh=rtsafe
        endif
11    continue
      pause 'rtsafe exceeding maximum iterations'
      return
      end
      SUBROUTINE MSCALE(ISCALE,Q2,M2,X2,MU2)
C.
C. ROUTINE TO SET THE RENORMALIZATION AND FACTORIZATION SCALES
C. (ACTUALLY, THE SQUARE OF THE SCALE)
C.
      DOUBLE PRECISION Q2,M2,X2,MU2,EPRO,EIEL
      INTEGER ISCALE
      COMMON/BEAM/EPRO,EIEL
      IF      ( ISCALE.EQ.1 ) THEN
        MU2 = 0.25D0 * M2
      ELSE IF ( ISCALE.EQ.2 ) THEN
        MU2 = M2
      ELSE IF ( ISCALE.EQ.3 ) THEN
        MU2 = 4.D0 * M2
      ELSE IF ( ISCALE.EQ.4 ) THEN
        MU2 = 0.25D0 * Q2
      ELSE IF ( ISCALE.EQ.5 ) THEN
        MU2 = Q2
      ELSE IF ( ISCALE.EQ.6 ) THEN
        MU2 = 4.D0 * Q2
      ELSE IF ( ISCALE.EQ.7 ) THEN
        MU2 = 0.25D0 * ( Q2 + M2 )
      ELSE IF ( ISCALE.EQ.8 ) THEN
        MU2 = ( Q2 + M2 )
      ELSE IF ( ISCALE.EQ.9 ) THEN
        MU2 = 4.D0 * ( Q2 + M2 )
      ELSE IF ( ISCALE.EQ.10 ) THEN
        MU2 = 0.25D0 * ( Q2 + 4.D0 * M2 )
      ELSE IF ( ISCALE.EQ.11 ) THEN
        MU2 = ( Q2 + 4.D0 * M2 )
      ELSE IF ( ISCALE.EQ.12 ) THEN
        MU2 = 4.D0 * ( Q2 + 4.D0 * M2 )
      ELSE IF ( ISCALE.EQ.13 ) THEN
        MU2 = 0.25D0 * ( Q2 + 4.D0 * M2 + X2 )
      ELSE IF ( ISCALE.EQ.14 ) THEN
        MU2 = ( Q2 + 4.D0 * M2 + X2 )
      ELSE IF ( ISCALE.EQ.15 ) THEN
        MU2 = 4.D0 * ( Q2 + 4.D0 * M2 + X2 )
      ELSE IF ( ISCALE.EQ.16 ) THEN
        MU2 = 0.25D0 * ( Q2 + X2 + M2 )
      ELSE IF ( ISCALE.EQ.17 ) THEN
        MU2 = ( Q2 + X2 + M2 )
      ELSE IF ( ISCALE.EQ.18 ) THEN
        MU2 = 4.D0 * ( Q2 + X2 + M2 )
      ELSE IF ( ISCALE.EQ.19 ) THEN
        MU2 = 0.25D0 * X2
      ELSE IF ( ISCALE.EQ.20 ) THEN
        MU2 = X2
      ELSE IF ( ISCALE.EQ.21 ) THEN
        MU2 = 4D0 * X2
      ELSE IF ( ISCALE.EQ.22 ) THEN  ! NEW (MW, 08/04/03)
        MU2 = max((0.25D0 * ( Q2 + 4.D0 * M2 )),4.D0 * M2)
      ELSE IF ( ISCALE.EQ.23 ) THEN
        MU2 = 16.D0 * ( Q2 + 4.D0 * M2 )
      ELSE
        WRITE(*,*) 'UNKNOWN SCALE CHOICE: ',ISCALE
        STOP
      END IF
      RETURN
      END

      SUBROUTINE MANDEL3(
     &  X,Y,CTH1,THETA2,
     &  T1,U1,TP,UP,S3,S4,S5,U6,U7,BETA5,DA,DB,
     &  P1,P2,K2)

      IMPLICIT DOUBLE PRECISION (A-Z)
      INTEGER I
      DIMENSION P1(0:3),P2(0:3),Q(0:3),K1(0:3),K2(0:3)
      DIMENSION BET(3)
      PARAMETER (SMALL=1D-15)
      PARAMETER (DTEST=1D-10)
      COMMON/INVAR/XBJ,XIMIN,XM2,Q2
      COMMON/KINE/S,SP,BETA

      M2=XM2
      SP2 = SP*SP
      SM1 = 1D0/S
      ONEMX = 1D0 - X
      ONEPY = 1D0 + Y

      IF ( ONEMX.LT.SMALL ) THEN
C SOFT LIMIT OF INVARIANTS
        STH1 = DSQRT(1D0-CTH1*CTH1)
        CTH2 = DCOS(THETA2)
        STH2 = DSIN(THETA2)
        T1 = -0.5D0*SP*(1D0-BETA*CTH1)
        U1 = -T1-SP
        TP = 0D0
        UP = -Q2
        S3 = 0D0
        S4 = 0D0
        S5 = S
        U6 = U1
        U7 = T1
        BETA5 = BETA
        IF ( (1D0-DABS(Y)).LT.SMALL) THEN
          FY = 0D0
        ELSE
          FY = DSQRT(1D0-Y*Y)
        END IF
        DA = 1D0 + BETA*FY*CTH2*STH1 + BETA*Y*CTH1
        DB = 1D0 - BETA*FY*CTH2*STH1 - BETA*Y*CTH1

        RS=DSQRT(S)
        D1=0.5D0/RS
        Q(0)=(S-Q2)*D1
        Q(1)=0D0
        Q(2)=0D0
        Q(3)=(S+Q2)*D1
        K2(0)=0D0
        K2(1)=0D0
        K2(2)=0D0
        K2(3)=0D0
        P1(0)=0.5D0*RS
        P1(1)=0.5D0*RS*BETA5*STH2*STH1
        P1(2)=0.5D0*RS*BETA5*CTH2*STH1
        P1(3)=0.5D0*RS*BETA5*CTH1
        P2(0)=P1(0)
        P2(1)=-P1(1)
        P2(2)=-P1(2)
        P2(3)=-P1(3)

        CALL ROT(-1,Q,-1D0,0D0)
C        CALL ROT(-1,K2,-1D0,0D0)
        CALL ROT(-1,P1,-1D0,0D0)
        CALL ROT(-1,P2,-1D0,0D0)

C        QTEST0=DABS(Q(0)-(S-Q2)/(2D0*DSQRT(S)))
C        QTEST1=DABS(Q(1))
C        QTEST2=DABS(Q(2))
C        QTEST3=DABS(Q(3)+(S+Q2)/(2D0*DSQRT(S)))
C        IF( (QTEST0.GT.DTEST).OR.(QTEST1.GT.DTEST).OR.
C     &      (QTEST2.GT.DTEST).OR.(QTEST3.GT.DTEST) )THEN
C           WRITE(*,*) 'TROUBLE IN KINE ON BOOST TO GAMMA-PARTON'
C           WRITE(*,*) QTEST0,QTEST1,QTEST2,QTEST3
C           CALL VWRITE(Q)
C           WRITE(*,*) (S-Q2)/(2D0*DSQRT(S)),0,0,-(S+Q2)/(2D0*DSQRT(S))
C           STOP
C        ENDIF

      ELSE IF ( ONEPY.LT.SMALL ) THEN
C COLLINEAR LIMIT OF INVARIANTS
        S5 = SP*X-Q2
        BETA5 = DSQRT(1D0-4.D0*M2/S5)
        T1 = -0.5D0*SP*(1D0-BETA5*CTH1)
        U1 = -0.5D0*X*SP*(1D0+BETA5*CTH1)
        TP = 0D0
        UP = S5-SP
        U1P=U1+Q2
        S3=-SP-UP-TP-U1P-T1
        S4=SP+U1+T1
        U6=-SP-TP-T1
        U7=-SP-UP-U1P
        DA = 1D0 + BETA*Y*CTH1
        DB = 1D0 - BETA*Y*CTH1
        
        STH1=DSQRT(1D0-CTH1*CTH1)
        STH2=DSIN(THETA2)
        CTH2=DCOS(THETA2)

        RS5=DSQRT(S5)
        D1=0.5D0/RS5
        SPUP=S+UP
        Q0=SPUP*D1
        QMOD=DSQRT(SPUP*SPUP+4D0*S5*Q2)*D1
        Q(0)=Q0
        Q(1)=0D0
        Q(2)=0D0
        Q(3)=QMOD
        K10=(S5-UP)*D1
C. COSPHI=-1 => SINPHI=0
        K1(0)=K10
        K1(1)=0D0
        K1(2)=0D0
        K1(3)=-K10
        K20=(S-S5)*D1
        K2(0)=K20
        K2(1)=0D0
        K2(2)=0D0
        K2(3)=QMOD-K10
        P1(0)=0.5D0*RS5
        P1(1)=0.5D0*RS5*BETA5*STH2*STH1
        P1(2)=0.5D0*RS5*BETA5*CTH2*STH1
        P1(3)=0.5D0*RS5*BETA5*CTH1
        P2(0)=P1(0)
        P2(1)=-P1(1)
        P2(2)=-P1(2)
        P2(3)=-P1(3)

        DO 50 I=1,3
           BET(I)=(Q(I)+K1(I))/(Q(0)+K1(0))
 50     CONTINUE

        CALL BOOST(+1,BET,Q)
        CALL ROT(-1,Q,-1D0,0D0)
        CALL BOOST(+1,BET,K2)
        CALL ROT(-1,K2,-1D0,0D0)
        CALL BOOST(+1,BET,P1)
        CALL ROT(-1,P1,-1D0,0D0)
        CALL BOOST(+1,BET,P2)
        CALL ROT(-1,P2,-1D0,0D0)

C        QTEST0=DABS(Q(0)-(S-Q2)/(2D0*DSQRT(S)))
C        QTEST1=DABS(Q(1))
C        QTEST2=DABS(Q(2))
C        QTEST3=DABS(Q(3)+(S+Q2)/(2D0*DSQRT(S)))
C        IF( (QTEST0.GT.DTEST).OR.(QTEST1.GT.DTEST).OR.
C     &      (QTEST2.GT.DTEST).OR.(QTEST3.GT.DTEST) )THEN
C           WRITE(*,*) 'TROUBLE IN KINE ON BOOST TO GAMMA-PARTON'
C           WRITE(*,*) QTEST0,QTEST1,QTEST2,QTEST3
C           CALL VWRITE(Q)
C           WRITE(*,*) (S-Q2)/(2D0*DSQRT(S)),0,0,-(S+Q2)/(2D0*DSQRT(S))
C           STOP
C        ENDIF

      ELSE
C INVARIANTS
        S5 = SP*X-Q2
        BETA5 = DSQRT(1D0-4D0*M2/S5)
        TP = -0.5D0*SP2*SM1*ONEMX*ONEPY
        UP = (-Q2*S5-0.5D0*SP2*ONEMX*(1D0-Y))*SM1
        RS5=DSQRT(S5)
        D1 = 0.5D0/RS5
        SPUP = S + UP
        Q0 = SPUP*D1
        QMOD = DSQRT(SPUP*SPUP+4D0*S5*Q2)*D1
        S5MUP = S5 - UP
        K10 = S5MUP*D1
        K20 = (S-S5)*D1
        COSPHI = 0.5D0*(-SP+2D0*K10*Q0)/K10/QMOD
        IF ( DABS(COSPHI).GT.(1D0-SMALL) ) THEN
          SINPHI = 0D0
        ELSE
          SINPHI = DSQRT(1D0-COSPHI*COSPHI)
        END IF

        STH1 = DSQRT(1D0-CTH1*CTH1)
        STH2 = DSIN(THETA2)
        CTH2 = DCOS(THETA2)

        T1 = -0.5D0*S5MUP*(1D0+BETA5*CTH2*STH1*SINPHI
     &                         +BETA5*     CTH1*COSPHI)
        U1 = -Q2-0.5D0*(SPUP+BETA5*QMOD*CTH1/D1)

        U1P=U1+Q2
        S3=-SP-UP-TP-U1P-T1
        S4=SP+U1+T1
        U6=-SP-TP-T1
        U7=-SP-UP-U1P
        IF ( (1D0-DABS(Y)).LT.SMALL ) THEN
          FY = 0D0
        ELSE
          FY = DSQRT(1D0-Y*Y)
        END IF
        DA = 1D0 + BETA*FY*CTH2*STH1 + BETA*Y*CTH1
        DB = 1D0 - BETA*FY*CTH2*STH1 - BETA*Y*CTH1

C. SETUP 4 VECTORS

        Q(0)=Q0
        Q(1)=0D0
        Q(2)=0D0
        Q(3)=QMOD
        K1(0)=K10
        K1(1)=0D0
        K1(2)=K10*SINPHI
        K1(3)=K10*COSPHI
        K2(0)=K20
        K2(1)=0D0
        K2(2)=K10*SINPHI
        K2(3)=QMOD+K10*COSPHI
        P1(0)=0.5D0*RS5
        P1(1)=0.5D0*RS5*BETA5*STH2*STH1
        P1(2)=0.5D0*RS5*BETA5*CTH2*STH1
        P1(3)=0.5D0*RS5*BETA5*CTH1
        P2(0)=P1(0)
        P2(1)=-P1(1)
        P2(2)=-P1(2)
        P2(3)=-P1(3)

        DO 100 I=1,3
           BET(I)=(Q(I)+K1(I))/(Q(0)+K1(0))
 100    CONTINUE

        CALL RANGLE2(Q,BET,COSA,SINA)

        CALL BOOST(+1,BET,Q)
        CALL ROT(-1,Q,COSA,SINA)
        CALL BOOST(+1,BET,K2)
        CALL ROT(-1,K2,COSA,SINA)
        CALL BOOST(+1,BET,P1)
        CALL ROT(-1,P1,COSA,SINA)
        CALL BOOST(+1,BET,P2)
        CALL ROT(-1,P2,COSA,SINA)

C        QTEST0=DABS(Q(0)-(S-Q2)/(2D0*DSQRT(S)))
C        QTEST1=DABS(Q(1))
C        QTEST2=DABS(Q(2))
C        QTEST3=DABS(Q(3)+(S+Q2)/(2D0*DSQRT(S)))
C        IF( (QTEST0.GT.DTEST).OR.(QTEST1.GT.DTEST).OR.
C     &      (QTEST2.GT.DTEST).OR.(QTEST3.GT.DTEST) )THEN
C           WRITE(*,*) 'TROUBLE IN KINE ON BOOST TO GAMMA-PARTON'
C           WRITE(*,*) QTEST0,QTEST1,QTEST2,QTEST3
C           CALL VWRITE(Q)
C           WRITE(*,*) (S-Q2)/(2D0*DSQRT(S)),0,0,-(S+Q2)/(2D0*DSQRT(S))
C           STOP
C        ENDIF

      END IF

      RETURN
      END


C. MOMENTUM DISTRIBUTION OF S.L. DECAY ELECTRON IN DECAYING HADRON 
C. REST FRAME.  CONSTRUCTED FROM RAPGAP.
      FUNCTION XSLP(W)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION X(100),Y(100)
      DATA (Y(I),I=1,100)
     ./0.005D0,0.015D0,0.025D0,0.035D0,0.045D0,0.055D0,0.065D0,0.075D0,
     . 0.085D0,0.095D0,0.105D0,0.115D0,0.125D0,0.135D0,0.145D0,0.155D0,
     . 0.165D0,0.175D0,0.185D0,0.195D0,0.205D0,0.215D0,0.225D0,0.235D0,
     . 0.245D0,0.255D0,0.265D0,0.275D0,0.285D0,0.295D0,0.305D0,0.315D0,
     . 0.325D0,0.335D0,0.345D0,0.355D0,0.365D0,0.375D0,0.385D0,0.395D0,
     . 0.405D0,0.415D0,0.425D0,0.435D0,0.445D0,0.455D0,0.465D0,0.475D0,
     . 0.485D0,0.495D0,0.505D0,0.515D0,0.525D0,0.535D0,0.545D0,0.555D0,
     . 0.565D0,0.575D0,0.585D0,0.595D0,0.605D0,0.615D0,0.625D0,0.635D0,
     . 0.645D0,0.655D0,0.665D0,0.675D0,0.685D0,0.695D0,0.705D0,0.715D0,
     . 0.725D0,0.735D0,0.745D0,0.755D0,0.765D0,0.775D0,0.785D0,0.795D0,
     . 0.805D0,0.815D0,0.825D0,0.835D0,0.845D0,0.855D0,0.865D0,0.875D0,
     . 0.885D0,0.895D0,0.905D0,0.915D0,0.925D0,0.935D0,0.945D0,0.955D0,
     . 0.965D0,0.975D0,0.985D0,0.995/
      DATA (X(I),I=1,100)
     ./2.27095419D-6,6.40907359D-5,0.000283992431D0,0.000747542142D0,
     . 0.00153114012D0,0.00270397181D0,0.00432889369D0,0.00670635012D0,
     . 0.00915751168D0,0.0124587851D0,0.0168395622D0,0.0210398662D0,
     . 0.0263862532D0,0.0324726582D0,0.0400473697D0,0.0469448526D0,
     . 0.0553585288D0,0.0655330823D0,0.0745764878D0,0.0853817205D0,
     . 0.0981808314D0,0.109355546D0,0.122500483D0,0.137825328D0,
     . 0.151019202D0,0.166347618D0,0.182353112D0,0.199005223D0,
     . 0.218029686D0,0.234113968D0,0.252496847D0,0.271379278D0,
     . 0.290719306D0,0.310473354D0,0.332627308D0,0.353103092D0,
     . 0.371764512D0,0.392714704D0,0.413844929D0,0.435106779D0,
     . 0.456451837D0,0.47996997D0,0.499199122D0,0.520506361D0,
     . 0.541707224D0,0.562756334D0,0.583609485D0,0.606270509D0,
     . 0.624557968D0,0.644572227D0,0.664228665D0,0.683491264D0,
     . 0.702326029D0,0.72070109D0,0.738586793D0,0.755955775D0,
     . 0.774435074D0,0.790640441D0,0.804724478D0,0.81980088D0,
     . 0.834260044D0,0.848089339D0,0.861278649D0,0.873820354D0,
     . 0.885709312D0,0.896942826D0,0.907520601D0,0.917444702D0,
     . 0.926719489D0,0.936179743D0,0.944115048D0,0.950724761D0,
     . 0.957489635D0,0.963659147D0,0.969249984D0,0.974280607D0,
     . 0.978771173D0,0.98274346D0,0.986220794D0,0.989227988D0,
     . 0.991791295D0,0.994131301D0,0.995854174D0,0.997223568D0,
     . 0.998180435D0,0.998968635D0,0.999502371D0,0.999820871D0,
     . 0.999968345D0,1D0,1D0,1D0,1D0,1D0,1D0,1D0,1D0,1D0,1D0,1D0/
      DO 10 I=1,100
         IF(W.GT.X(I))GOTO 10
         IF(I.EQ.1)THEN
            XM=Y(I)/X(I)
            XB=Y(I)-XM*X(I)
         ELSE
            XM=( Y(I)-Y(I-1) )/( X(I) - X(I-1) )
            XB=Y(I)-XM*X(I)
         ENDIF
         TMP=XM*W+XB
         GOTO 100
 10   CONTINUE
 100  XSLP=TMP
      RETURN
      END
