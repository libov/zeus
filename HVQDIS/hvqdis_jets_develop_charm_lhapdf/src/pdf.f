C.--------------------------------------------------------------
C. INTERFACE TO PDFS
C. INPUT:
C.              X = MOMENTUM FRACTION ( 0 < X < 1 )
C.              SCALE2 = SCALE SQUARED IN GEV^2
C.              LANGUAGE
C. OUTPUT:
C.              FILLS COMMON BLOCKS
C.              "COMMON/PDFG/GLUE"
C.              "COMMON/PDFQ /FU ,FD ,FS ,FC ,FB"
C.              "COMMON/PDFAQ/FUB,FDB,FSB,FCB,FBB"
C.              WITH MOMENTUM DENSITIES = X*PROBABILITY DENSITIES
C.
C. changed for using LHDPDF/LHAGLU
C.---------------------------------------------------------------
C      SUBROUTINE PDF(IIPDF,X,SCALE2)
      SUBROUTINE PDF(X,SCALE2)
      IMPLICIT none 
      character*20 parm(20)
      double precision value(20) 
      Double Precision GLUE,FU ,FD ,FS ,FC ,FB,CTQ6PDF
      Double Precision FUB,FDB,FSB,FCB,FBB
      Double Precision X,Scale2,scale,val,xx,qq
      Double Precision upv,dnv,usea,dsea,str,chm,bot,top,glu
      Double Precision h1pdfs
      
      INTEGER IQUARK,IPDF,IIPDF
      Integer n1,n2
      Parameter (n1=51,n2=51)

      Double Precision  XA(2),A(N1+N2)
      INTEGER NA(2),in
      Integer i1,i2
      DATA NA/n1,n2/

      Double Precision f_glu(n1,n2),f_upv(n1,n2)
      Double Precision f_dnv(n1,n2),f_usea(n1,n2)
      Double Precision f_dsea(n1,n2),f_str(n1,n2)
      Double Precision f_chm(n1,n2),f_bot(n1,n2)
      Double Precision xmin,xmax,xminL,xmaxL,xdif,x1(0:n1)
      Double Precision q2min,q2max,q2minL,q2maxL,q2dif,x2(0:n2)
      Integer igrid,j
      Double Precision DHFINT
      Double Precision xxx, qint, qqq, xl,g1,uv1,dv1,ds1,us1,ch1,bt1,st1

      COMMON/PDFF/IPDF
      COMMON/QUARKF/IQUARK
      COMMON/PDFG/GLUE
      COMMON/PDFQ /FU ,FD ,FS ,FC ,FB
      COMMON/PDFAQ/FUB,FDB,FSB,FCB,FBB
      Logical first
      Data first/.true./

      SCALE = DSQRT(SCALE2)
*      WRITE(*,*) 'SCALE', SCALE
      parm(1)='DEFAULT'

      if (first) then

         WRITE(*,*) 'LHAPDF WILL BE USED, set=', IPDF
C         val = IIPDF
         val = IPDF

         value(1)=val
         
C         WRITE(*,*) 'TRY CALL PDFSET'
         call pdfset(parm,value)
C         WRITE(*,*) 'PDFSET IS CALLED'
         call getdesc()
C         WRITE(*,*) 'GETDESC IS CALLED'
         xmin = 0.000002
         xmax = 1
         xminL=log(xmin)
         xmaxL=log(xmax)
         xdif=(xmaxL-xminL)/Real(n1-1)
         
         DO i1=1,n1
            x1(i1) = xminL + xdif*Real(i1-1)
c     write(6,*) x1(i1),i1
         ENDDO
         
         Q2min = 1.
         Q2max = 1000.
         q2minL=log(q2min)
         q2maxL=log(q2max)
         q2dif=(q2maxL-q2minL)/real(n2-1)
         
         DO i2=1,n2
            x2(i2) = q2minL + q2dif*Real(i2-1)
c     write(6,*) x2(i2),i2
         ENDDO
         
         IN=0
         
         DO i1=1,n1
            IN=IN+1
            A(IN) = x1(i1)
         ENDDO
         
         DO i2=1,N2
            IN=IN+1
            A(IN) = x2(i2)
         ENDDO
         
         DO i1 =1,n1
         DO i2 =1,n2
         xxx=exp(x1(i1))
         qint=exp(x2(i2))
         qqq=qint
         call structm(xxx,qqq,upv,dnv,usea,dsea,str,chm,bot,top,glu)
c     write(6,*) 'x and q in structm=', xxx, qqq
               f_upv(i1,i2)=upv
               f_dnv(i1,i2)=dnv
               f_usea(i1,i2)=usea
               f_dsea(i1,i2)=dsea
               f_str(i1,i2)=str
               f_chm(i1,i2)=chm
               f_bot(i1,i2)=bot
               f_glu(i1,i2)=glu
c     write(6,*) ' x ',xxx,x1(i1),i1,' q ',qqq,x2(i2),i2,f_glu(i1,i2)
c     write(6,*) ' x ',xxx,x1(i1),i1,' q ',qqq,x2(i2),i2,f_dnv(i1,i2)
            ENDDO
            
         ENDDO
         
         
         first=.false.
      endif
      
      qq=scale
      xx=x

      IF(xx.eq.0..or.qq.eq.0.) then
         FBB  = 0D0
         FCB  = 0D0
         FSB  = 0D0
         FUB  = 0D0
         FDB  = 0D0
         GLUE = 0D0
         FD   = 0D0
         FU   = 0D0
         FS   = 0D0
         FC   = 0D0
         FB   = 0D0
         return
      endif

c      write(6,*) ' xx ',xx,' q ',qq
         xa(1) = log(xx)
         xa(2) = log(qq)

         if(xa(1).lt.x1(1)) then
            write(6,*) '  x out of range ',xx,' min ',exp(x1(1))
            xa(1)=x1(1)
         endif
         if(xa(1).ge.x1(n1)) then
            write(6,*) '  x out of range ',xx,' max ',exp(x1(n1))
            xa(1)=x1(n1)
         endif
         if(xa(2).lt.x2(1)) then
            write(6,*) '  q2 out of range ',qq,' min ',exp(x2(1))
            xa(2)=x2(1)
         endif
         if(xa(2).ge.x2(n2)) then
            write(6,*) '  q2 out of range ',qq,' max ',exp(x2(n2))
            xa(2)=x2(n2)
         endif

         
         g1=DHFINT(2,XA,NA,A,f_glu)
         uv1=DHFINT(2,XA,NA,A,f_upv)
         dv1=DHFINT(2,XA,NA,A,f_dnv)
         us1=DHFINT(2,XA,NA,A,f_usea)
         ch1=DHFINT(2,XA,NA,A,f_chm)
         ds1=DHFINT(2,XA,NA,A,f_dsea)
         st1=DHFINT(2,XA,NA,A,f_str)
         bt1=DHFINT(2,XA,NA,A,f_bot)


c . FOR CHARM PRODUCTION IT'S JUST U,D,S AND GLUE
         FBB  = 0D0
         FCB  = 0D0
         FSB  = st1
         FUB  = us1
         FDB  = ds1
         GLUE = g1
         FD   = dv1+ds1
         FU   = uv1+us1
         FS   = st1
         FC   = 0D0
         FB   = 0D0

C. FOR BOTTOM PRODUCTION INCLUDE THE CHARM
         IF (IQUARK.EQ.2) THEN
           FCB = ch1
           FC = ch1
         ENDIF

c      IF(IQUARK.EQ.2)THEN
c         FCB  = CHM
c         FC   = CHM
c      ENDIF
c         WRITE(*,*) 'PDFs hier! x:', X
c         WRITE(*,*) 'PDFs hier! q2:', SCALE
c         WRITE(*,*) 'PDFs hier! gluon:', GLUE
*         WRITE(*,*) 'PDFs hier! gluon, fd-s:',GLUE, FD,FU,FS
      RETURN
      END





*
* $Id: fint.F,v 1.1.1.1 1996/02/15 17:48:36 mclareni Exp $
*
* $Log: fint.F,v $
* Revision 1.1.1.1  1996/02/15 17:48:36  mclareni
* Kernlib
*
*
          FUNCTION DHFINT(NARG,ARG,NENT,ENT,TABLE)
          Implicit None
C
C   INTERPOLATION ROUTINE. AUTHOR C. LETERTRE.
C   MODIFIED BY B. SCHORR, 1.07.1982.
C
          INTEGER   NENT(9)
          Double Precision      ARG(9),   ENT(9),   TABLE(9)
          INTEGER   INDEX(32)
          Double Precision       WEIGHT(32)
          Double Precision DHFINT
          Integer NARG,LMAX,ISTEP,KNOTS,N,NDIM,ISHIFT,I,K
          Integer LMIN,LOCA,LOCB,LOCC,LGFILE
          Double Precision X,H,ETA
          LOGICAL   MFLAG,    RFLAG
          DHFINT  =  0.
          IF(NARG .LT. 1  .OR.  NARG .GT. 5)  GOTO 300
          LMAX      =  0
          ISTEP     =  1
          KNOTS     =  1
          INDEX(1)  =  1
          WEIGHT(1) =  1.
          DO 100    N  =  1, NARG
             X     =  ARG(N)
             NDIM  =  NENT(N)
             LOCA  =  LMAX
             LMIN  =  LMAX + 1
             LMAX  =  LMAX + NDIM
             IF(NDIM .GT. 2)  GOTO 10
             IF(NDIM .EQ. 1)  GOTO 100
             H  =  X - ENT(LMIN)
             IF(H .EQ. 0.)  GOTO 90
             ISHIFT  =  ISTEP
             IF(X-ENT(LMIN+1) .EQ. 0.)  GOTO 21
             ISHIFT  =  0
             ETA     =  H / (ENT(LMIN+1) - ENT(LMIN))
             GOTO 30
  10         LOCB  =  LMAX + 1
  11         LOCC  =  (LOCA+LOCB) / 2
             IF(X-ENT(LOCC))  12, 20, 13
  12         LOCB  =  LOCC
             GOTO 14
  13         LOCA  =  LOCC
  14         IF(LOCB-LOCA .GT. 1)  GOTO 11
             LOCA    =  MIN0( MAX0(LOCA,LMIN), LMAX-1 )
             ISHIFT  =  (LOCA - LMIN) * ISTEP
             ETA     =  (X - ENT(LOCA)) / (ENT(LOCA+1) - ENT(LOCA))
             GOTO 30
  20         ISHIFT  =  (LOCC - LMIN) * ISTEP
  21         DO 22  K  =  1, KNOTS
                INDEX(K)  =  INDEX(K) + ISHIFT
  22            CONTINUE
             GOTO 90
  30         DO 31  K  =  1, KNOTS
                INDEX(K)         =  INDEX(K) + ISHIFT
                INDEX(K+KNOTS)   =  INDEX(K) + ISTEP
                WEIGHT(K+KNOTS)  =  WEIGHT(K) * ETA
                WEIGHT(K)        =  WEIGHT(K) - WEIGHT(K+KNOTS)
  31            CONTINUE
             KNOTS  =  2*KNOTS
  90         ISTEP  =  ISTEP * NDIM
 100         CONTINUE
          DO 200    K  =  1, KNOTS
             I  =  INDEX(K)
             DHFINT  =  DHFINT + WEIGHT(K) * TABLE(I)
 200         CONTINUE
          RETURN
 300      Continue
c          CALL KERMTR('E104.1',LGFILE,MFLAG,RFLAG)
          IF(MFLAG) THEN
             IF(LGFILE .EQ. 0) THEN
                WRITE(*,1000) NARG
             ELSE
                WRITE(LGFILE,1000) NARG
             ENDIF
          ENDIF
          IF(.NOT. RFLAG) CALL ABEND
          RETURN
1000      FORMAT('  HFUNCTION DHFINT ... NARG =',I6,
     +              '  NOT WITHIN RANGE')
          END
