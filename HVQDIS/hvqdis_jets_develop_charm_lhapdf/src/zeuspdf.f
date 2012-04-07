      Double Precision FUNCTION ZEUSPDF(inden,XBJ,scale)
***********************************************************
* iden: quark density: as PDG labels
*       iden+10  error up
*       iden+100 error down
* xBJ
* scale is Q2
* 
**********************************************************
*
      implicit none
*
      Integer inden,iden
      Double Precision  XBJ,scale
      Real x,Q2
      Real Q2G1,Q2G2,TQ
      Real XG1,XG2,TX
      REAL ZL,ZH
      Integer i,j,iu1,iu2,ipdf,IQ2L,IQ2H,IXL,IXH
      Integer IQ2LOLD,IQ2HOLD,IXLOLD,IXHOLD
      Integer ngrid
      Parameter (ngrid=161)
      Real pdf2(ngrid,ngrid)
      Real eu2(ngrid,ngrid),ed2(ngrid,ngrid)
      Real pdf(-5:5,ngrid,ngrid)
      Real eu(-5:5,ngrid,ngrid),ed(-5:5,ngrid,ngrid)
      Integer icase
      Save pdf,eu,ed
      Save pdf2,eu2,ed2
*
      Logical first,lp
      data first/.true./,lp/.false./
* 
      Q2=scale*scale
      x=xbj 
*
      iu1=30 
      iu2=40 
*
      icase=0
      iden=inden   
      if (inden.ge. 10 ) then
       iden=inden-10
       icase=10
      endif
      if (inden.le.-10 ) then
       iden=inden+10
       icase=10
      endif
      if (inden.ge. 100) then
       iden=inden-100
       icase=100
      endif
      if (inden.le.-100) then
       iden=inden+100
       icase=100
      endif   
*
C      write(6,*) ' iden= ',iden,' inden= ',inden
*
      if (iden.lt.-5 .or. iden.gt.5 ) then
       write(6,*) '**zeuspdf: This PDf-id does not exist ! ',iden
      endif
*
      if (first) then
       first=.false.
*
C       IQ2LOLD=-1
C       IQ2HOLD=-1
C       IXLOLD=-1
C       IXHOLD=-1
*
*      read-in files
*
       do ipdf=-5,5       
        if (ipdf.eq.0) then
         open(unit=iu1,file='gluon_err_tot.dat',status='old')
        elseif(ipdf.eq.1) then
         open(unit=iu1,file='upval_err_tot.dat',status='old')
         open(unit=iu2,file='ubar_err_tot.dat',status='old')
        elseif(ipdf.eq.2) then
         open(unit=iu1,file='dnval_err_tot.dat',status='old')
         open(unit=iu2,file='dbar_err_tot.dat',status='old')
        elseif(ipdf.eq.3) then
         open(unit=iu1,file='sbar_err_tot.dat',status='old')
        elseif(ipdf.eq.4) then
         open(unit=iu1,file='cbar_err_tot.dat',status='old')
        elseif(ipdf.eq.5) then
         open(unit=iu1,file='bbar_err_tot.dat',status='old')
        elseif(ipdf.eq.-1) then
         open(unit=iu1,file='ubar_err_tot.dat',status='old')
        elseif(ipdf.eq.-2) then
         open(unit=iu1,file='dbar_err_tot.dat',status='old')
        elseif(ipdf.eq.-3) then
         open(unit=iu1,file='sbar_err_tot.dat',status='old')
        elseif(ipdf.eq.-4) then
         open(unit=iu1,file='cbar_err_tot.dat',status='old')
        elseif(ipdf.eq.-5) then
         open(unit=iu1,file='bbar_err_tot.dat',status='old')
C        elseif(ipdf.eq.100) then
*        total sea quarks   
C         open(unit=iu1,file='seaqk_err_tot.dat',status='old')
        endif
*
        do j=1,ngrid
         do i=1,ngrid
          read(iu1,*) pdf(ipdf,i,j),eu(ipdf,i,j),ed(ipdf,i,j)
C          write(6,*) ipdf,i,j, 
C     &    ' pdf= ',pdf(ipdf,i,j),' +-',eu(ipdf,i,j),ed(ipdf,i,j)
*
          if (icase.eq.10  ) then
           pdf(ipdf,i,j)=eu(ipdf,i,j)
          endif 
          if (icase.eq.100 ) then
           pdf(ipdf,i,j)=ed(ipdf,i,j)
          endif
*
         enddo
        enddo
*
        if (icase.eq.0   ) then
         write(6,*) ipdf,'**zeuspdf: reading entral PDF ! '           
        endif 
        if (icase.eq.10  ) then
         write(6,*) ipdf,'**zeuspdf: reading error up ! '           
        endif 
        if (icase.eq.100 ) then
         write(6,*) ipdf,'**zeuspdf: reading error down ! '
        endif
*
        if (ipdf.eq.1.or.ipdf.eq.2) then
         close(unit=iu1)
*
         do j=1,ngrid
          do i=1,ngrid
           read(iu2,*) pdf2(i,j),eu2(i,j),ed2(i,j)
           if (inden.ge. 10.or.inden.le.-10  ) then
            pdf2(i,j)=eu2(i,j)
           endif 
           if (inden.ge. 100.or.inden.le.-100) then
            pdf2(i,j)=ed2(i,j)
           endif
*
           pdf(ipdf,i,j)=pdf(ipdf,i,j)+pdf2(i,j)
C           eu(ipdf,i,j)=eu(ipdf,i,j)+eu2(i,j)
C           ed(ipdf,i,j)=ed(ipdf,i,j)+ed2(i,j)
          enddo
         enddo
        endif
*
        close(unit=iu2)
       enddo
*
      endif
*     
      IF (Q2.LT.0.39.OR.X.LT.1E-6) THEN
        write(6,*) '**zeuspdf: x or Q2 out of range ',x,Q2
        ZEUSPDF=0.
        RETURN
      ENDIF

C     Calculate grid points

      DO I=0,159
       IF(I.LE.71)THEN
        Q2G1=10**(5.*I/120.)-0.7
        Q2G2=10**(5.*(I+1)/120.)-0.7
       ELSEIF(I.EQ.72)THEN
        Q2G1=10**(5*I/120)-0.7
        Q2G2=10**(2*(I-71)/88 +3.)
       ELSE
        Q2G1=10**(2.*(I-72)/88. +3.)
        Q2G2=10**(2.*(I-71)/88. +3.)
       ENDIF
       IF (Q2.GE.Q2G1.AND.Q2.LT.Q2G2) THEN
        IQ2L=I+1
        IQ2H=I+2
        TQ=(Q2-Q2G1)/(Q2G2-Q2G1)
       ENDIF
      ENDDO
*
      DO I=0,159
       IF(I.LE.79)THEN
        XG1=10**(6.*I/120.-6.)
        XG2=10**(6.*(I+1)/120.-6.)
       ELSEIF(I.EQ.80)THEN
        XG1=10**(6*I/120-6.)
        XG2=10**(2./80.*(I-79)-2.)
       ELSE
        XG1=10**(2./80.*(I-80)-2.)
        XG2=10**(2./80.*(I-79)-2.)
       ENDIF
       IF (X.GE.XG1.AND.X.LT.XG2) THEN
        IXL=I+1
        IXH=I+2
        TX=(X-XG1)/(XG2-XG1)
       ENDIF
      ENDDO
*
      if ((IQ2LOLD.ne.IQ2L).or.(IQ2HOLD.ne.IQ2H)
     &    .or. (IXLOLD.ne.IXL).or.(IXHOLD.ne.IXH)) then
*
       IQ2LOLD=IQ2L
       IQ2HOLD=IQ2H
       IXLOLD=IXL
       IXHOLD=IXH
*
       if (lp) then
        write(6,*) '**zeuspdf: IXL= ',IXL,' IXH= ',IXH
        write(6,*) '**zeuspdf: IQ2L= ',IQ2L,' IQ2H= ',IQ2H
        write(6,*) '**zeuspdf: X= ',X,' Q2= ',Q2
       endif
      endif
      if (lp) then
C        write(6,*) iden,'*zeuspdf: pdf= ',
C     &  (1-TX) * pdf(iden,IXL,IQ2H),TX*pdf(iden,IXH,IQ2H)
      endif
*
C      if (lp.and.(iden.eq.1.or.iden.eq.2)) then  
C       write(6,*) iden,' pdf2: ',pdf2(IXL,IQ2H)
C       write(6,*) iden,' pdf : ',pdf(iden,IXL,IQ2H) 
C      endif
*
      ZH=(1-TX)*pdf(iden,IXL,IQ2H)+TX*pdf(iden,IXH,IQ2H)
      ZL=(1-TX)*pdf(iden,IXL,IQ2L)+TX*pdf(iden,IXH,IQ2L)
      ZEUSPDF=(1-TQ)*ZL+TQ*ZH
C      ZEUSPDF=ZL
*
      if (lp) write(6,*) iden,'**zeuspdf: zeuspdf= ',ZEUSPDF
* 
*      F2H=(1-TX)*F2V(IXL,IQ2H)+TX*F2V(IXH,IQ2H)
*      F2L=(1-TX)*F2V(IXL,IQ2L)+TX*F2V(IXH,IQ2L)
*      F2QCD=(1-TQ)*F2L+TQ*F2H
*
      RETURN 
      END








