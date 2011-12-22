      subroutine helicityd (pel1,p_tr,prho,pos,th_gp,thel,phil,psil)
c      all  helicityd (pele,p_tr,prhod,pos,thelr,philr,psilr)

C
C  INPUT:
C   ppr(4) 4-momentum of initial proton     (px,py,pz,e)
C   pel1(4) 4-momentum of outgoing electron
C   pel(4) 4-momentum of initial electron
C   ppi(4)  4-momentum of pi+ (K+,mu+,e+...)
C   prho(4) 4-momentum of rho (phi,J/psi..)
C  OUTPUT
C   thel  cos(theta)
C   phil  angle between production plane and decay plane
C   psil  angle between production plane and electron plane
C

ccc      implicit none

      real pg(4),ppr(4),prho(4),xmrho,ppi(4),thel,phil
      real p_tr(4,2)
      real pcm(4),px(4),axis(3),pxr(4),zh(3),yh(3),xh(3),ppir(4)
      real Xpro,Ypro
      real Mcm,pgS(4),prhoS(4),pxS(4),ppiS(4)
      real tmp(3),tmp1(3)
      real pel(4),pelS(4),pel1(4),pel1S(4),psil
      real cphi,sphi,spsi,ptOUT
      real yBj,eps,RRR,weight,MC1_q2
      integer pos
      real th_gp,phi_test


      thelr=-100.
      philr=-100.
      psilr=-100.
      th_gp=-100.
      xmrho=prho(4)**2-prho(3)**2-prho(2)**2-prho(1)**2
      if(xmrho.gt.0.0) xmrho=sqrt(xmrho)

c electron momentum
      pel(1)=0.
      pel(2)=0.
      pel(3)=-27.5
      pel(4)=27.5
c proton momentum
      ppr(1)=0.
      ppr(2)=0.
      ppr(3)=920.
      ppr(4)=920. ! sqrt(ppr(1)**2+ppr(2)**2+ppr(3)**2+0.93827**2)

ccccccccccccccccccccccccccccccccc
      pg(1)=(pel(1)-pel1(1))
      pg(2)=(pel(2)-pel1(2))
      pg(3)=(pel(3)-pel1(3))
      pg(4)=(pel(4)-pel1(4))
ccccccccccccccccccccccccccccccccccc
c
      ppi(1)=p_tr(1,pos)
      ppi(2)=p_tr(2,pos)
      ppi(3)=p_tr(3,pos)
      ppi(4)=p_tr(4,pos)


      call vadd(pg,ppr,pcm,4)
      Mcm=pcm(4)**2 - pcm(1)**2 - pcm(2)**2 - pcm(3)**2
      if(Mcm.gt.0.0) Mcm = sqrt(Mcm)
      call lorenf(Mcm,pcm,pg,pgS) ! gamma
      call lorenf(Mcm,pcm,prho,prhoS) ! rho
ccc
      call lorenf(Mcm,pcm,ppi,ppiS) ! pion
      call lorenf(Mcm,pcm,pel,pelS) ! electron
      call lorenf(Mcm,pcm,pel1,pel1S) ! electron'
c dodane przeze mnie
c
c      call vunit(ppiS,ppi3,3)
c      th_gp=ppiS(3)/sqrt(ppiS(1)**2+ppiS(2)**2+ppiS(3)**2)
c
c koniec mojego
c
c      tmp(1)=pgS(1)
c      tmp(2)=pgS(2)
c      tmp(3)=pgS(3)
c od tego miejscz przerzucam do ukladu rho ???

      zh(1)=prhoS(1)
      zh(2)=prhoS(2)
      zh(3)=prhoS(3)
      call vunit(zh,zh,3)

      call cross(pgS,zh,yh)
      call vunit(yh,yh,3)

      call cross(yh,zh,xh)
      call lorenf(xmrho,prhoS,ppiS,ppir)
      call vunit(ppir,ppir,3)

      thel=vdot(ppir,zh,3) ! ???spr w kodzie dla generowanej czy tu koniec
ccc
      tmp(1)=ppir(1)
      tmp(2)=ppir(2)
      tmp(3)=ppir(3)
      call cross(zh,tmp,tmp1)
      call vunit(tmp1,tmp1,3)
      cphi=vdot(yh,tmp1,3)
      sphi=-vdot(xh,tmp1,3)

      if(abs(cphi).gt.1.0) then
         write(6,*) 'cphi',cphi
         cphi=0.9999*cphi/abs(cphi)
      endif

      phil=acos(cphi)
      if(sphi.lt.0.0) phil=6.2832-phil
ccc
c      Xpro=vdot(ppir,xh,3)
c      Ypro=vdot(ppir,yh,3)
c      phil=Xpro/sqrt(Xpro**2+Ypro**2)
c      phil=acos(phil)
c      if(Ypro.lt.0.) phil=6.2832-phil
c
c psi



      call cross(pelS,pel1S,axis)
      call vunit(axis,axis,3)
      psil=vdot(axis,yh,3)

c     phi_test=vdot(pelS,tmp1,3)
c     phil=acos(phi_test)

      if(abs(psil).gt.1.0) then
         psil=0.9999*psil/abs(psil)
      endif
      psil=acos(psil)
c
c      tmp(1)=pgS(1)
c      tmp(2)=pgS(2)
c      tmp(3)=pgS(3)
c
c c      call vunit(tmp,tmp,3)
      call cross(pgs,yh,tmp1)
      spsi=vdot(tmp1,axis,3)
      if(spsi.lt.0.0) psil=6.2832-psil

      return
      end


      subroutine cross (tmp2,zh,yh)
      Implicit none

      real yh(3),zh(3),tmp2(3)

      yh(1) = tmp2(2)*zh(3)-tmp2(3)*zh(2)
      yh(2) = tmp2(3)*zh(1)-tmp2(1)*zh(3)
      yh(3) = tmp2(1)*zh(2)-tmp2(2)*zh(1)

      return
      end


c *************************************
      SUBROUTINE LORENF (U,PS,PI,PF)
c *************************************

      IMPLICIT NONE
C
C CERN PROGLIB# U102    LORENF          .VERSION KERNFOR  4.04  821124

* ---->   real*8 version (privat)
*

      REAL U,PS,PI,PF,FN,PF4

      DIMENSION      PS(4),PI(4),PF(4)

      IF (PS(4).EQ.U) goto  17
      PF4  = (PI(4)*PS(4)-PI(3)*PS(3)-PI(2)*PS(2)-PI(1)*PS(1))/U
      FN   = (PF4+PI(4)) / (PS(4)+U)
      PF(1)= PI(1) - FN*PS(1)
      PF(2)= PI(2) - FN*PS(2)
      PF(3)= PI(3) - FN*PS(3)
      PF(4)= PF4
      GO TO 18

   17 PF(1)= PI(1)
      PF(2)= PI(2)
      PF(3)= PI(3)
      PF(4)= PI(4)

   18 CONTINUE

      RETURN

      END 