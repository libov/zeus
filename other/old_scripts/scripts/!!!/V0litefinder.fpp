      Subroutine V0litefinder(ierr,Tmode)
*----------------------------------------------------------------
*     
*  Input:
*  Tmode=1  ZTT tracks
*  Tmode=2 : REG/CTD  tracks  
*
*
*  Output:
*  Common block given by V0litetest.inc
* ierr=0 - everything is OK
* ierr=1 - error (usually, too small number of tracks)
* 
*
* 03.02.2005
* Ryuma Hori/Sergei Chekanov 
* Update on June 13, 2007 : new beam spot default is added
*----------------------------------------------------------------
* 19.06.2006
* bs spot infomation improved.
*----------------------------------------------------------------
* 19.06.2006
* nv0lite limit(<80) is added.
*----------------------------------------------------------------
      Implicit NONE	

#include "partap.inc"
#include "zdskey.inc"
#include "vcevtreg.inc"
#include "trk_ntup.inc"
#include "vtxtup.inc"
#include "vctrhl.inc"
#include "vcatcal.inc"      
#include "zttrhl.inc"
#include "ztprhl.inc"
#include "evttup.inc"

#include "beamspot.inc"
#include "v0tuplite.inc"
*
*************************************************************************
*
      Integer i,j,k
      Integer ierr
C Define variables
      Integer ntrk,nntrk
      integer imax
      parameter (imax=400)
      Integer ctdlayouter,ctdlayinner
      Integer Tmode
      Integer ctdndof,ctdcode
      Integer tr_charge(imax),tr_outerlayer(imax),tr_innerlayer(imax)
      Integer tr_id(imax)
      Real tr_hel(5,imax),tr_cov(15,imax),tr_ndof(imax)
      Real dca,chi,tlidcav
      Double precision mom1tr,mom2tr,pt1,pt2,ptk,tr_mom(imax)
      Real invmass,invmasse,invmasslam(2)
      Real eta1,eta2,etak,z1
      Real bs(3),par1(5),par2(5),par(5,2),cov(15,2),bfield(3)
      Real start(3),vertex(3),pvtx(3),vertexcov(6),newpar(3,2)
      Real newpar1(3),newpar2(3)
      Double precision mom1(4),mom2(4),momk(4)
      Real alpha,beta
      Real dlx,dly,dlz,PTmin
      parameter (PTmin=0.1) ! min PT on two tracks

      external tlidcav
      Real Mpion,Mp,Me
      data Mpion /0.139570/
      data Mp /0.938272/
      data Me /0.0000511/
      
      ierr = 0
      nntrk = 0
      nv0lite = 0
C     
C      if(Ora_RUNNR.le.56201) then ! defaults for e+ data
C         bs(1) = 1.8
C      elseif(Ora_RUNNR.gt.56201) then ! defaults for e- data
C         bs(1) = 1.35

      bs(2) = 0.
      bs(3) = Ora_zvtx

      if (Ora_RUNNR.le.37715) then
         bs(1) = 0.
         bs(2) = 0.
      elseif(Ora_RUNNR.le.51245.and.
     +       Ora_RUNNR.gt.37715) then     ! defaults for e+ data
         bs(1) = 1.92
         bs(2) = 0.17
      elseif(Ora_RUNNR.ge.52258.and.
     +       Ora_RUNNR.lt.60000)  then   ! defaults for e- data
         bs(1) = 1.33
         bs(2) = 0.20
      elseif(Ora_RUNNR.ge.60005) then   ! defaults for e+ data
         bs(1) = 1.92
         bs(2) = 0.17
      endif
    

 
C      write(*,*) 'beam spot fill in v0finder' 
C      write(*,*) "bs x  ",bspt_x,"bs y  ",bspt_y   
** get beam spot from Orange  
       if (bspt_prog.ne.0) then
         bs(1) =bspt_x
         bs(2) =bspt_y
         bs(3) =Ora_zvtx
        endif 

** get vertex 
      pvtx(1) = Ora_xvtx
      pvtx(2) = Ora_yvtx
      pvtx(3) = Ora_zvtx

      if(abs(pvtx(3)).gt.55)goto 999
      
C     in case of ZTT tracking
      if(Tmode .eq. 1)then
         ntrk = coutab(ZTTRHL)
C     track selection. track>1
         if(ntrk .le.1)  goto 999
         if(ntrk .gt.imax)goto 999
C     loop
         do i=1,ntrk
            Call fettab(ZTTRHL,ID,i)
            Call fettab(ZTPRHL,ID,ZTTRHL_ZTPRHL)
C     track data fill
            ctdndof = ZTPRHL_Code/10000
            ctdcode = ZTPRHL_Code - ctdndof*10000
            ctdlayouter = ctdcode/100
            ctdlayinner = ctdcode - ctdlayouter*100
C     ctd layler cut
            if(ctdlayouter .lt. 3)goto 997
C     count track
            nntrk = nntrk + 1
C     data fill
            do j=1,5
               tr_hel(j,nntrk) = ZTTRHL_hel(j)
            enddo
            
            do j=1,15
               tr_cov(j,nntrk) = ZTTRHL_cov(j)
            enddo

            tr_ndof(nntrk) = ctdndof
            tr_mom(nntrk) = ZTTRHL_Mom
            tr_charge(nntrk) = sign(1.0,ZTTRHL_hel(2))
            tr_outerlayer(nntrk) = ctdlayouter
            tr_innerlayer(nntrk) = ctdlayinner
            tr_id(nntrk) = i      
 997        continue
         enddo
C     in case of REG or CTD tracking
      elseif(Tmode .eq. 2)then
         ntrk = coutab(VCTRHL)
C     track selection. track>1
         if(ntrk.le.1)goto 999  
         if(ntrk .gt.imax)goto 999
C     loop
         do i=1,ntrk
            Call fettab(VCTRHL,ID,i)
            Call fettab(VCATCAL,ID,i)
C     track data fill
            
            ctdlayouter = VCATCAL_KODSWM/100
            ctdlayinner = mod(VCATCAL_KODSWM,100)/10
C     ctd layler cut
            if(ctdlayouter .lt. 3)goto 998
C     count track
            nntrk = nntrk + 1
C     data fill
            tr_hel(1,nntrk) = VCTRHL_azim
            tr_hel(2,nntrk) = VCTRHL_qovr
            tr_hel(3,nntrk) = VCTRHL_qxdh
            tr_hel(4,nntrk) = VCTRHL_zh
            tr_hel(5,nntrk) = VCTRHL_tdip
            
            do j=1,15
               tr_cov(j,nntrk) = VCTRHL_covm(j)
            enddo
            
            tr_ndof(nntrk) = VCTRHL_ndf
            tr_mom(nntrk) = VCTRHL_pgevc
            tr_charge(nntrk) = sign(1.0,VCTRHL_qovr)
            tr_outerlayer(nntrk) = ctdlayouter
            tr_innerlayer(nntrk) = ctdlayinner
            tr_id(nntrk) = i
 998        continue
         enddo
      endif 

C     loop for all tracks      
      do i=1,nntrk-1
C     set 1st track parameter         
         mom1tr = tr_mom(i)
         do k=1,5
            par1(k) = tr_hel(k,i)
            par(k,1) = tr_hel(k,i)
         enddo
        
         do k=1,15
            cov(k,1) = tr_cov(k,i)
         enddo
         
C     loop for 2nd tracks
         do j=i+1,nntrk 
C     set 2nd track parameter        
            mom2tr = tr_mom(j)
            do k=1,5
               par2(k) = tr_hel(k,j)
               par(k,2) = tr_hel(k,j)
            enddo
            
            do k=1,15
               cov(k,2) = tr_cov(k,j)
            enddo
C     calculate DCA
            dca = tlidcav(par1,par2,start)

C     DCA cut
            if( abs(dca).gt.2.0)        goto 20

C     vertex refit using Vxlite
            Call vxlitefit(2,par,cov,start,
     +           vertex,vertexcov,chi,newpar)
C     chi2 cut
            if((chi.ge.5.0).or.(chi.le.0.))goto 20

C     charge cut (vxlite)
            if((newpar(3,1)*newpar(3,2)).gt.0)goto 20


C     get magnetic field for momentum calculation
            Call gufld(vertex,bfield)

C     calculate momentum using tlite
            do k=1,3
               newpar1(k) = newpar(k,1)
               newpar2(k) = newpar(k,2)
            enddo            

            Call tlipnewpar(newpar1,bfield(3),Mpion,mom1)
            Call tlipnewpar(newpar2,bfield(3),Mpion,mom2)

C     calculate Pi pt
            Call calpt(mom1,pt1)
            Call calpt(mom2,pt2)

C     momentum limitation
            if(pt1.lt.PTmin.or.pt2.lt.PTmin)       goto 20
            if(pt1 .gt. 1.0E7 .or. pt2 .gt. 1.0E7) goto 20


** get momenta 
            do k=1,4
               momk(k) = mom1(k) + mom2(k)
            enddo


C     calculate colinearity
            Call calcolinear(bs,vertex,momk,alpha,beta)
C     K0s xy plane colinearity cut
            if(alpha.ge.0.15) goto 20
C     K0s 3D colinearity cut
            if(beta.ge.0.3)   goto 20

C           write(*,*) "alpha3",alpha,",beta3",beta
C     count V0lite candidate 
            nv0lite = nv0lite + 1 

C     calculate K0s invariant mass
            call calmass(Mpion,Mpion,mom1,mom2,invmass)
C     M(ee)
            call calmass(Me,Me,mom1,mom2,invmasse)

C     lambda(ep) 
            if(newpar(3,1).gt.0)then
               call calmass(Mp,Mpion,mom1,mom2,invmasslam(1))
            else
               call calmass(Mp,Mpion,mom2,mom1,invmasslam(1))
            endif
C     anti-lambda(ep)
            if(newpar(3,1).lt.0)then
               call calmass(Mp,Mpion,mom1,mom2,invmasslam(2))
            else
               call calmass(Mp,Mpion,mom2,mom1,invmasslam(2))
            endif
C     fill ntuple blocks
            tSecvtx(1,nv0lite) = vertex(1)
            tSecvtx(2,nv0lite) = vertex(2)
            tSecvtx(3,nv0lite) = vertex(3)
            tSecvtx_chi(nv0lite) = chi
            tSecvtx_dca(nv0lite) = dca
C collinearity cuts 
            tSecvtx_collin2(nv0lite)  = alpha 
            tSecvtx_collin3(nv0lite)  = beta

C fill decay lenght in 2D and 3D 
            dlx=vertex(1)-bs(1)
            dly=vertex(2)-bs(2)
            dlz=vertex(3)-bs(3)
            tSecvtx_dlen2(nv0lite)  = sqrt(dlx**2+dly**2)
            tSecvtx_dlen3(nv0lite)  = sqrt(dlx**2+dly**2+dlz**2)
 
            if(newpar(3,1) .ge.0)then               
               tQ1(nv0lite) = 1
               tQ2(nv0lite) = -1
            else
               tQ1(nv0lite) = -1
               tQ2(nv0lite) = 1
            endif
            
            tT1_Layinn(nv0lite) = tr_innerlayer(i)
            tT2_Layinn(nv0lite) = tr_innerlayer(j)
            tT1_Layout(nv0lite) = tr_outerlayer(i)
            tT2_Layout(nv0lite) = tr_outerlayer(j)
            tT1_ID(nv0lite)     = tr_id(i) 
            tT2_ID(nv0lite)     = tr_id(j)
            tT1_Ndof(nv0lite) = tr_Ndof(i)
            tT2_Ndof(nv0lite) = tr_Ndof(j)            

            do k=1,3
            tP1(k,nv0lite) = real(mom1(k)) 
            tP2(k,nv0lite) = real(mom2(k))
            tPk(k,nv0lite) = real(momk(k))
            enddo

            tInvmass_K0(nv0lite)     = invmass
            tInvmass_Lambda(nv0lite) = invmasslam(1)
            tInvmass_Alambda(nv0lite)= invmasslam(2)
            tInvmass_ee(nv0lite) = invmasse

 20         continue
         enddo
 10      continue
      enddo 
*  30    continue
      return

 999  continue
 
      ierr=1

      return
      end
      
      
