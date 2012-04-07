      Real function pet(z)
*
      Real z
      Real Peps
*      Parameter (Peps=0.0382)
      Parameter (Peps=0.0035)

      Integer nbin
      Parameter (nbin=1000)
      Logical first
      Data first/.true./
      Save first
      Real petmax,rz,sum
      Save petmax,sum
*
      if (first) then
       write(6,*) '**Pet Peterson frag function eps= ',Peps
       first=.false.
       petmax=-999.
       sum=0.
       do i=1,nbin
        rz=real(i)/real(nbin)
        rpet=1./rz
        rpet=rpet*(1.-(1./rz)-(Peps/(1.-rz)) )**(-2.)
        sum=sum+rpet/real(nbin)
        if (petmax.lt.rpet)then
         petmax=rpet
        endif
       enddo
       write(6,*) '**pet: petmax= ',petmax,sum
      endif
*
      pet=1./z
      pet=pet*(1.-(1./z)-(Peps/(1.-z)) )**(-2.)
*
       pet=pet/petmax
C       pet=pet/sum
*
      return
      end
*
      Real function f1(z)
      implicit none
*
      Real z
      Real b,c,d
      Parameter (b=999.,c=0.884,d=0.0181)
      Integer i,nbin
      Parameter (nbin=1000)
      Logical first
      Data first/.true./
      Save first
      Real petmax,rz,pet,sum
      Save petmax,sum
*
      if (first) then
       write(6,*) '**F1 frag function b,c,d,= ',b,c,d
       sum=0.
       first=.false.
       petmax=-999.
       do i=1,nbin
        rz=real(i)/real(nbin)
*
        pet=1.+b*(1.-rz)
        if (rz.gt.1e-13) then
         pet=pet/rz
        else
         pet=0.
        endif
        pet=pet/(1.-c/rz-d/(1.-rz))**2
        sum=sum+pet/real(nbin)
        if (petmax.lt.pet)then
         petmax=pet
        endif
       enddo
       write(6,*) '**F1: petmax= ',petmax,sum
      endif
*
      pet=1.+b*(1.-z)
      if (z.gt.1e-13) then
       pet=pet/z
      else
       pet=0.
      endif
      pet=pet/(1.-c/z-d/(1.-z))**2
*
C      write(6,*) z,' F1= ',pet 
      f1=pet/petmax
C      f1=pet/sum
*     
      return
      end
*
      real function p8(z,mbE)
*********************************************
* mbE is the b-mass/Ebeam
* 
*
********************************************
      implicit none
      Real z
      Integer nbin,i,j
      Parameter (nbin=1000)
      Real a(5)
      Save a
      Logical first
      Data first/.true./
      Save first
      Real petmax,rz,pet,mbE,sum
      Save petmax,sum

      a(1)=-9.99
      a(2)=40.84
      a(3)=-82.26
      a(4)=80.9
      a(5)=-30.6
*
      if (first) then
*
       write(6,*) '**P8 frag function a= ',a
       first=.false.
       petmax=-999.
       do i=1,nbin
        rz=real(i)/real(nbin)
*
        pet=0.
        do j=1,5
         pet=pet+a(j)*rz**j
        enddo
        pet=rz*(1.-rz)*(rz-mbE)*(1.+pet)
        sum=sum+pet/real(nbin)
C        write(6,*) i,rz,'**P8: pet= ',pet
        if (petmax.lt.pet)then
         petmax=pet
        endif
       enddo
       write(6,*) '**P8: petmax= ',petmax,sum
      endif
*
      pet=0.
      do i=1,5
       pet=pet+a(i)*z**i
      enddo
      pet=z*(1.-z)*(z-mbE)*(1.+pet)
C        write(6,*) z,' pet= ',pet
*
       p8=pet
C      p8=pet/petmax
C      p8=pet/sum
*
      return
      end
*
      real function bow(z,mt)
********************************************
*
* recommanded within JETSET
*
********************************************
*
      implicit none
      Real z,mt,re
      Real Brb,bb,ba
      Parameter (Brb=1.,bb=1.2,ba=1.4)
      Integer i,nbin
      Parameter (nbin=1000)
      Logical first
      Data first/.true./
      Save first
      Real petmax,rz,rpet,sum
      Save petmax,sum
*
      if (first) then
       write(6,*) '**Bow Bowler frag function a,b= ',ba,bb
       first=.false.
       petmax=-999.
       sum=0.
       do i=1,nbin
        rz=real(i)/real(nbin)
        bow=(rz**(1.+brb*bb*mt**2))
        if (bow.gt.1e-13) bow=1./bow
        re=-bb*mt**2
        if (rz.gt.1e-13) then
         re=re/rz
         bow=bow*(1.-rz)**ba*exp(re)
        else
         bow=0.
        endif
*
        sum=sum+bow/real(nbin)
        if (petmax.lt.bow)then
         petmax=bow
        endif
       enddo
       write(6,*) '**Bow petmax= ',petmax,sum
      endif
*
      bow=(z**(1.+brb*bb*mt**2))
      if (bow.gt.1e-13) bow=1./bow
      re=-bb*mt**2
      if (z.gt.1e-13) then
       re=re/z
       bow=bow*(1.-z)**ba*exp(re)
      else
       bow=0.
      endif
*
      bow=bow/petmax    
C      bow=bow/sum    
*
      return
      end
*
      real function fkart(z)
********************************************
*
* 
*
********************************************
*
      implicit none
      Real z
      Real ka
C      Parameter (ka=3.904)
      Parameter (ka=27.5)
      Integer i,nbin
      Parameter (nbin=1000)
      logical first
      data first/.true./
      save first
      real petmax,rz,rpet,sum
      save petmax,sum
*
      if (first) then
       write(6,*) '**Kart Kartevelishvili frag func ka= ',ka
       first=.false.
       petmax=-999.
       sum=0.
       do i=1,nbin
        rz=real(i)/real(nbin)
        fkart=(rz**ka)*(1.-rz)
        sum=sum+fkart/real(nbin)
        if (petmax.lt.fkart)then
         petmax=fkart
        endif
       enddo
       write(6,*) '**Kart petmax= ',petmax,sum
      endif
*
      fkart=(z**ka)*(1.-z)
      fkart=fkart/petmax
C      fkart=fkart/sum
      return
      end
*
      real function flund(z,mt)
********************************************
*
* recommended within JETSET
*
********************************************
      implicit none
      Real z 
      Real zb,za,mt,re
C     Parameter (zb=0.4,za=1.4)
      Parameter (zb=0.32,za=1.88)
      Integer i,nbin
      Parameter (nbin=1000)
      Logical first
      Data first/.true./
      Save first
      Real petmax,rz,rpet,sum
      Save petmax,sum
*
      if (first) then
       write(6,*) '**flund: frag function a,b= ',za,zb
       first=.false.
       petmax=-999.
       sum=0.
       do i=1,nbin
        rz=real(i)/real(nbin)
        if (rz.gt. 1e-13) then
         flund=1./rz 
        else
         flund=0.
        endif
*
        re=-zb*mt**2
C        re=-zb
        if (rz.gt. 1e-13) then
         re=re/rz
         flund=flund*(1.-rz)**za*exp(re)
        else
         flund=0.
        endif
        sum=sum+flund/real(nbin)
        if (petmax.lt.flund)then
         petmax=flund
        endif
       enddo
       write(6,*) '**flund petmax= ',petmax,sum
      endif
*
      if (z.gt. 1e-13) then
       flund=1./z 
      else
       flund=0.
      endif
*
      re=-zb*mt**2
C      re=-zb
      if (z.gt. 1e-13) then
       re=re/z
       flund=flund*(1.-z)**za*exp(re)
      else
       flund=0.
      endif
*
      flund=flund/petmax
C      flund=flund/sum
*
      return
      end
*
      real function sld(z)
      implicit none
*
      Real z
      Integer nbin,i
      Parameter (nbin=25)
      Real dz(nbin),zb(nbin+1),ez(nbin),syez(nbin),unez(nbin)
      Data zb/0.00,0.04,0.08,0.12,0.16,
     &        0.20,0.24,0.28,0.32,0.36,
     &        0.40,0.44,0.48,0.52,0.56,
     &        0.60,0.64,0.68,0.72,0.76,
     &        0.80,0.84,0.88,0.92,0.96,1.0/
*

      Data dz/0.000,0.000,0.000,0.110,0.188,
     &        0.204,0.213,0.268,0.340,0.398,
     &        0.505,0.587,0.677,0.796,0.991,
     &        1.241,1.622,2.092,2.671,3.102,
     &        3.290,2.953,1.897,0.753,0.009/
      Data ez/0.000,0.000,0.000,0.029,0.035,
     &        0.032,0.027,0.031,0.036,0.037,
     &        0.041,0.042,0.044,0.047,0.052,
     &        0.058,0.068,0.080,0.094,0.104,
     &        0.111,0.106,0.079,0.042,0.011/
      Data syez/0.000,0.000,0.000,0.004,0.005,
     &        0.006,0.008,0.009,0.011,0.012,
     &        0.014,0.015,0.016,0.017,0.018,
     &        0.018,0.020,0.028,0.046,0.071,
     &        0.084,0.065,0.094,0.051,0.004/
      Data unez/0.000,0.000,0.000,0.034,0.043,
     &        0.036,0.030,0.036,0.039,0.041,
     &        0.045,0.048,0.050,0.059,0.079,
     &        0.092,0.093,0.096,0.128,0.189,
     &        0.245,0.190,0.167,0.215,0.063/
*
      save zb,dz,ez
*
      Logical first
      Data first/.true./
      Save first
      Real petmax,rz,rpet,sum
      Save petmax,sum
*
      if (first) then
       write(6,*) '**SLD frag function  '
       call Hbook1(105, ' sld data        ',nbin, 0.,1.,0.)
       call Hbook1(106, ' sld data        ',nbin, 0.,1.,0.)
*
       call hpak(105,dz)
       call hpak(106,dz)
       call hpake(105,ez)
       do i=1,nbin
        syez(i)=sqrt(syez(i)**2+ez(i)**2+unez(i)**2)
       enddo
       call hpake(106,syez)
*
       first=.false.
       petmax=-999.
       sum=0.
       do i=1,nbin
        sum=sum+dz(i)/real(nbin)
        if (petmax.lt.dz(i))then
         petmax=dz(i)
        endif
       enddo
       write(6,*) '**SLD petmax= ',petmax,sum
      endif
*
      sld=0.
      do i=1,nbin
       if (zb(i).le.z.and.zb(i+1).gt.z) then
        sld=dz(i)
       endif 
      enddo
*
      sld=sld/petmax
C      sld=sld/sum
*
      return
      end
*    
      Real function fragfun(ifun,mb,mt)
****************************************
*
* returns z distribution according to a chosen
* fragmentation function (ref. SLD, PRD65 (2002) 092006)
*
* The routine uses the Monte Carlo rejection technique
* and is not very efficient, since the fragmenation
* function is always tested against a box (0,1,0.1)
*
* Tancredi Carli Oct.2002
*
****************************************
      implicit none
*                  mb b-quark mass
*                  mt should be transverse b-mass
*                  mbE should be mb/Ebeam (here: Ebeam=W/2)
      Real mb,rndm,mbE,mt
C      Parameter (mb=4.75,mbE=mb/91.)
      Integer i,nbin
      Parameter (nbin=1000)
      Real rz,ru,rpet,x
      Real pet,bow,fkart,flund,sld,f1,p8
      Integer it,itmax,ifun,ifunold
      Parameter (itmax=10000)
      Logical first
      Data first/.true./
      Save first
      Data ifunold/-999./
      Save ifunold
*
      mbE=mb/(91./2.)
*
      if (ifunold.ne.ifun) then
       ifunold=ifun
C       first=.true.
      endif
*
      if (first) then
       first=.false.
*                     2/4 recommended within JETSET
       if (ifun.eq.1) write(6,*) '**fragfun: Peterson '
       if (ifun.eq.2) write(6,*) '**fragfun: Bowler '
       if (ifun.eq.3) write(6,*) '**fragfun: Kartesvili '
       if (ifun.eq.4) write(6,*) '**fragfun: Lund '
       if (ifun.eq.5) write(6,*) '**fragfun: Sld '
       if (ifun.eq.6) write(6,*) '**fragfun: F1 '
       if (ifun.eq.7) write(6,*) '**fragfun: P8 '
      endif
*
       it=0.
 1     it=it+1 
       rz=rndm(123426.)
       ru=rndm(123427.)
       rpet=-1.
       if (ifun.eq.1) x=pet(rz)
       if (ifun.eq.2) x=bow(rz,mt)
       if (ifun.eq.3) x=fkart(rz)
       if (ifun.eq.4) x=flund(rz,mt)
       if (ifun.eq.5) x=sld(rz)
       if (ifun.eq.6) x=f1(rz)
       if (ifun.eq.7) x=p8(rz,mbE)
       if (ru.lt.x) then
        rpet=rz
       endif
       if (it.gt.itmax) then
        write(6,*) '**fragfun: too many iterations '
        rz=0. 
       endif
       if (rpet.eq.-1.) goto 1
 999   continue
       fragfun=rz

       return
       end
