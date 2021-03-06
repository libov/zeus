      Subroutine V0litefinder(ierr,Tmode,selector)
*----------------------------------------------------------------
*  Input:
*  Tmode=1 : ZTT tracks
*  Tmode=2 : REG/CTD  tracks  
*  Output:
*  Common block given by V0litetest.inc
*  ierr=0 - everything is OK
*  ierr=1 - error (usually, too small number of tracks)
*  Last changes  07.03.2008 (optimization,comments,deleting unused variables,beauty,etc.)
*  rewritten from original code of Ryuma Hori/Sergei Chekanov  by Andrii Verbytskyi
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
C External functions
      external tlidcav	
	Real tlidcav 
C Input parameters
	Integer ierr,Tmode,selector
C Data and etc	 
      Integer imax
      parameter (imax=400)
      real CORRECTION
      data CORRECTION /1.003/ ! correction for momenta; this value taken from rtfit code; 
                              !orange uses this when value  via rtfit when it generates Tracking blocks 
			      !WARNING- This is ONLY change  than can produse difference in blocks generated by this finder with 
			      !selector=0 and v2007a.2/V0litefinder It will happen if pt<PTmin and pt>PTmin*CORRECTION
			      !Ofcource, there are also new parameters, so files genereted with v2007a.2/V0litefinder will be	
                              !a bit smaller 
      Real Mpion,Mp,Me,PTmin,DCAcut,CHIcut,COLL2Dcut,COLL3Dcut
      Integer CTDLAYOUTERcut
      data Mpion /0.139570/ !pion mass
      data Mp /0.938272/  !proton mass
      data Me /0.000511/   ! electron mass
      parameter (PTmin=0.0) ! min PT on two tracks - will be used only in "old" mode
      parameter (CTDLAYOUTERcut=0) !ill be used only in "old" mode
      parameter (DCAcut=2.0) ! min DCA on two tracks
      parameter (CHIcut=5.0) ! min CHI  of vertex 	
      parameter (COLL2Dcut=0.15)
      parameter (COLL3Dcut=0.30)
C Other variables
      Integer j,k,ntrk,nntrk,u,nm,mz,nv0litef,i,m,n,NUMB
      Integer iii,iik,jjk,ii
      Integer ctdlayouter,ctdlayinner,ctdndof,ctdcode
      Integer tr_charge(imax),tr_outerlayer(imax),tr_innerlayer(imax)
      Integer tr_id(imax),stt_par(imax),tr_ent(imax),charge(imax)
      
      Real tr_hel(5,imax),tr_cov(15,imax),tr_ndof(imax)
      Real dca,chi,dlx,dly,dlz,alpha,beta
      Real invmass,invmasse,invmasslamm(2)
      Real bs(3),par1(5),par2(5),par(5,2),cov(15,2),bfield(3)
      Real cov1(15),cov2(15) 
      Real start(3),vertex(3),pvtx(3),vertexcov(6),newpar(3,2)
      Real newpar1(3),newpar2(3),minn
      Real vmass	
      Double precision mom1(4),mom2(4),momk(4)
      Double precision mom1tr,mom2tr,pt1,pt2,tr_mom(imax)

       
       Real chiM(imax,imax),dcaM(imax,imax)
       Real flagK(imax,imax),vertexM(3,imax,imax)
       Double precision mom1M(3,imax),mom2M(3,imax)

      ierr = 0
      nntrk = 0
      nv0lite = 0
      NUMB=0

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

      
      
      
      if(abs(pvtx(3)).gt.55) goto 999
      

      if(Tmode .eq. 1)then   !get all parameters from ADAMO tables
      ntrk = coutab(ZTTRHL)
      if((ntrk .le.1).or.(ntrk .gt.imax)) goto 999

      do i=1,ntrk
            nntrk = nntrk + 1 
            Call fettab(ZTTRHL,ID,i)
            Call fettab(ZTPRHL,ID,ZTTRHL_ZTPRHL)
            ctdndof = ZTPRHL_Code/10000
            ctdcode = ZTPRHL_Code - ctdndof*10000
            ctdlayouter = ctdcode/100
            ctdlayinner = ctdcode - ctdlayouter*100
      	      do j=1,5
      	      tr_hel(j,nntrk) = ZTTRHL_hel(j)
      	      enddo
      	      do j=1,15
      	      tr_cov(j,nntrk) = ZTTRHL_cov(j)
      	      enddo
	  if ((Ora_RUNNR.ge.52244).and.(Ora_RUNNR.le.57123)) then!exclude 2005 data 
	  stt_par(nntrk)=-1
	  else		
	  stt_par(nntrk) =  (ZTTRHL_StCrCsCz/1000000)                   
	  endif
	  tr_ndof(nntrk) = ctdndof
            tr_mom(nntrk) = ZTTRHL_Mom
            tr_charge(nntrk) = sign(1.0,ZTTRHL_hel(2))
            tr_outerlayer(nntrk) = ctdlayouter
            tr_innerlayer(nntrk) = ctdlayinner
            tr_id(nntrk) = i      
            tr_ent(nntrk) =0
 997        continue
         enddo
           endif
         if(Tmode .eq. 2)then
         ntrk = coutab(VCTRHL)
         if((ntrk.le.1).or.(ntrk .gt.imax)) goto 999
         
		do i=1,ntrk
            nntrk = nntrk + 1
            Call fettab(VCTRHL,ID,i)
            Call fettab(VCATCAL,ID,i)          
            ctdlayouter = VCATCAL_KODSWM/100
            ctdlayinner = mod(VCATCAL_KODSWM,100)/10
            tr_hel(1,nntrk) = VCTRHL_azim
            tr_hel(2,nntrk) = VCTRHL_qovr
            tr_hel(3,nntrk) = VCTRHL_qxdh
            tr_hel(4,nntrk) = VCTRHL_zh
            tr_hel(5,nntrk) = VCTRHL_tdip
          
	            do j=1,15
	            tr_cov(j,nntrk) = VCTRHL_covm(j)
	            enddo
 
	    stt_par(nntrk)=-2

           tr_ndof(nntrk) = VCTRHL_ndf
            tr_mom(nntrk) = VCTRHL_pgevc
            tr_charge(nntrk) = sign(1.0,VCTRHL_qovr)
            tr_outerlayer(nntrk) = ctdlayouter
            tr_innerlayer(nntrk) = ctdlayinner
            tr_id(nntrk) = i
            tr_ent(nntrk) =0
  998        continue
          enddo
	  endif
		
          if(selector .eq. 0)then !then we start original (almost) code of Ryuma Hori/Sergei Chekanov
C         loop for all tracks      
          do i=1,nntrk-1
C     set 1st track parameter         
          mom1tr = tr_mom(i)
          do k=1,5
            par1(k) = tr_hel(k,i)
            par(k,1) = tr_hel(k,i)
          enddo
        
          do k=1,15
            cov(k,1) = tr_cov(k,i)
          cov1(k)= tr_cov(k,i)
		enddo
         
C            loop for 2nd tracks
          do j=i+1,nntrk 
C                set 2nd track parameter        
            mom2tr = tr_mom(j)
            do k=1,5
               par2(k) = tr_hel(k,j)
               par(k,2) = tr_hel(k,j)
            enddo
            
            do k=1,15
               cov(k,2) = tr_cov(k,j)
            cov2(k)= tr_cov(k,j)
		enddo
C     calculate DCA
            dca = tlidcav(par1,par2,start)

C     DCA cut
            if( abs(dca).gt.DCAcut)        goto 120

C     vertex refit using Vxlite
            Call vxlitefit(2,par,cov,start,
     +           vertex,vertexcov,chi,newpar)
      
C     chi2 cut
            if((chi.ge.CHIcut).or.(chi.le.0.))goto 120
		 if(tr_outerlayer(i) .lt. CTDLAYOUTERcut)goto 120  ! as we do not have this cut when we  read  ZTT/VC  we use it here 
 		 if(tr_outerlayer(j) .lt. CTDLAYOUTERcut)goto 120  
C     charge cut (vxlite)
            if((newpar(3,1)*newpar(3,2)).gt.0)goto 120


C     get magnetic field for momentum calculation
            Call gufld(vertex,bfield)

C     calculate momentum using tlite
            do k=1,3
               newpar1(k) = newpar(k,1)
               newpar2(k) = newpar(k,2)
            enddo            
		newpar1(3) = newpar1(3)/CORRECTION
               newpar2(3) = newpar2(3)/CORRECTION
            
            Call tlipnewpar(newpar1,bfield(3),Mpion,mom1)
            Call tlipnewpar(newpar2,bfield(3),Mpion,mom2)

C     calculate Pi pt
            Call calpt(mom1,pt1)
            Call calpt(mom2,pt2)

C     momentum limitation
            if(pt1.lt.PTmin.or.pt2.lt.PTmin)       goto 120
            if(pt1 .gt. 1.0E7 .or. pt2 .gt. 1.0E7) goto 120


** get momenta 
            do k=1,4
               momk(k) = mom1(k) + mom2(k)
            enddo


C     calculate colinearity
            Call calcolinear(bs,vertex,momk,alpha,beta)
C     K0s xy plane colinearity cut
            if(alpha.ge.COLL2Dcut) goto 120
C     K0s 3D colinearity cut
            if(beta.ge.COLL3Dcut)   goto 120

C           write(*,*) "alpha3",alpha,",beta3",beta
C     count V0lite candidate 
	 if(nv0lite.ge.80)  goto 110 !fill   ent1,ent2 and then exit
            nv0lite = nv0lite + 1 
		
C     calculate K0s invariant mass
            call calmass(Mpion,Mpion,mom1,mom2,invmass)
C     M(ee)
            call calmass(Me,Me,mom1,mom2,invmasse)

C     lambda(ep) 
            if(newpar(3,1).gt.0)then
               call calmass(Mp,Mpion,mom1,mom2,invmasslamm(1))
            else
               call calmass(Mp,Mpion,mom2,mom1,invmasslamm(1))
            endif
C     anti-lambda(ep)
            if(newpar(3,1).lt.0)then
               call calmass(Mp,Mpion,mom1,mom2,invmasslamm(2))
            else
               call calmass(Mp,Mpion,mom2,mom1,invmasslamm(2))
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
            tT1_ID(nv0lite)     = i 
            tT2_ID(nv0lite)     = j
            tT1_Ndof(nv0lite) = tr_Ndof(i)
            tT2_Ndof(nv0lite) = tr_Ndof(j)            

            stt1(nv0lite)     = stt_par(i)
            stt2(nv0lite)     = stt_par(j)

            do k=1,3
            tP1(k,nv0lite) = real(mom1(k)) 
            tP2(k,nv0lite) = real(mom2(k))
            tPk(k,nv0lite) = real(momk(k))
            enddo

            tInvmass_K0(nv0lite)     = invmass
            tInvmass_Lambda(nv0lite) = invmasslamm(1)
            tInvmass_Alambda(nv0lite)= invmasslamm(2)
            tInvmass_ee(nv0lite) = invmasse
		tr_ent(i)=tr_ent(i)+1
		tr_ent(j)=tr_ent(j)+1


 120         continue
             enddo
	     enddo 	
 
 110         continue
          
	
        do ii=1,nv0lite
	ent1(ii)=tr_ent(tT1_ID(ii))	
	ent2(ii)=tr_ent(tT2_ID(ii))  
	enddo



        endif!end of Ryuma Hori/Sergei Chekanov code

C------------------------------------------------------------------------------------------

	if(selector .eq. 1) then !new algorithm
C Start stuff	
	do i=1,imax
 	     mom1M(1,i)=0
	     mom1M(2,i)=0
	     mom1M(3,i)=0
             mom2M(1,i)=0
             mom2M(2,i)=0
	     mom2M(3,i)=0
	     charge(i)=0					      
	     tr_ent(i)=0				      
       do j=1,imax
       flagK(i,j) = 0!
       flagK(i,i) = 4!settinng  diagonal elements to 4 to prevent  combine track with it 
       chiM(i,j) = 99999999! setting initial dca and chi to "big numbers"
       dcaM(i,j) = 99999999!
       enddo  
       enddo

C Start checking of all track combinations and store corresponding vertex parameters into arrays

	 do i=1,ntrk
         do j=i+1,ntrk 
               do k=1,5
               par1(k) = tr_hel(k,i)
               par(k,1) = tr_hel(k,i)
               par2(k) = tr_hel(k,j)
               par(k,2) = tr_hel(k,j)
               enddo
        	dcaM(i,j) = abs(tlidcav(par1,par2,start))
                dcaM(j,i)=dcaM(i,j)
	
	       if (dcaM(i,j).ge.DCAcut) goto 345
	       do k=1,15
               cov(k,1) = tr_cov(k,i)
               cov(k,2) = tr_cov(k,j)
               cov1(k)= tr_cov(k,i)
               cov2(k)= tr_cov(k,j) 
               enddo

       Call vxlitefit(2,par,cov,start,vertex,vertexcov,
     +chi,newpar)
       Call callcolinear_withpar(bs,vertex,newpar,alpha,beta)! this will compute colinearity for two tracks We neglect radial component of magnetic field so it will be the same colinearity.
	
        charge(i)=sign(1.0,newpar(3,1))

      if((sign(1.0,newpar(3,1)*newpar(3,2)).lt.0).and.(tr_mom(i).le.1E3)
     +.and.(tr_mom(j).le.1E3).and.(alpha.lt.COLL2Dcut)
     +.and.(beta.lt.COLL3Dcut).and.(chi.le.CHIcut).and.(chi.ge.0))then
	 
	  chiM(i,j) = chi
	  chiM(j,i) = chi
          Call gufld(vertex,bfield)!get the magnetic field 
          do k=1,3
               newpar1(k) = newpar(k,1)
               newpar2(k) = newpar(k,2)
            enddo            
	NUMB=NUMB+1
	    vertexM(1,i,j)=vertex(1)! store vertex into array
	    vertexM(2,i,j)=vertex(2)
	    vertexM(3,i,j)=vertex(3)
 	    newpar1(3) = newpar1(3)/CORRECTION ! correct curvature of tracks
            newpar2(3) = newpar2(3)/CORRECTION ! correct curvature of tracks
            Call tlipnewpar(newpar1,bfield(3),Mpion,mom1)!here we use only z component of field; we assume that Bz>>Br; But using boyh Bz and Br will change some tracks significantly;In any case it will not change most distributions
            Call tlipnewpar(newpar2,bfield(3),Mpion,mom2)
            do k=1,3
            mom1M(k,i)= mom1(k)
	    mom2M(k,j)=mom2(k)
	    enddo

            else  
            flagK(i,j)=3!mark combination of tracks as "bad" if it  was rejected withcuts
            flagK(j,i)=3


            endif
  345	    continue
	    enddo	
	    enddo
C Start of looping on candidates
            nv0lite = 0

       do nv0litef=1,NUMB
		
       nm=1 ! set initial values for nm,mz,minn
       mz=2
       minn = 99999999+1 ! it should be  bigger than all  values of dca
       do iik=1,ntrk     ! Search for pair of tracks with minimal DCA; this is the main parameter to determinate good vertex
       do jjk=iik+1,ntrk	
       if( (dcaM(iik,jjk).lt.minn).and.(flagK(iik,jjk).lt.1)) then
       minn =  dcaM(iik,jjk)
       nm = iik
       mz = jjk
       endif
       enddo
       enddo
                
        if((minn.ge.DCAcut).or.(nv0lite.ge.80))  goto 900 ! We do not have more good candidates  
	nv0lite=nv0lite+1
       	vertex(1)= vertexM(1,nm,mz)
	vertex(2)= vertexM(2,nm,mz)
	vertex(3)= vertexM(3,nm,mz)
	momk(1)=mom1M(1,nm)+mom2M(1,mz)
	momk(2)=mom1M(2,nm)+mom2M(2,mz)
	momk(3)=mom1M(3,nm)+mom2M(3,mz)
	Call calcolinear(bs,vertex,momk,alpha,beta) ! this procedure is very "light-weight", its better to call it than to store two 400x400 real arrays

            do iii=1,ntrk
            flagK(iii,mz) = 2
            flagK(nm,iii) = 2
            flagK(mz,iii) = 2
            flagK(iii,nm) = 2 
            enddo  
	                  
            
            dlx = vertex(1)-bs(1)
            dly = vertex(2)-bs(2)
            dlz = vertex(3)-bs(3)
C Write to ntuple             
            tSecvtx(1,nv0lite) = vertex(1)
            tSecvtx(2,nv0lite) = vertex(2)
            tSecvtx(3,nv0lite) = vertex(3)
            tSecvtx_chi(nv0lite) = chiM(nm,mz)
            tSecvtx_dca(nv0lite) = dcaM(nm,mz)
            tSecvtx_collin2(nv0lite)  = alpha 
            tSecvtx_collin3(nv0lite)  = beta
            tSecvtx_dlen2(nv0lite)  = sqrt(dlx*dlx+dly*dly)
            tSecvtx_dlen3(nv0lite)  = sqrt(dlx*dlx+dly*dly+dlz*dlz)
 
            if (charge(nm).ge.0) then               
               tQ1(nv0lite) = 1
               tQ2(nv0lite) = -1
            else
               tQ1(nv0lite) = -1
               tQ2(nv0lite) = 1
            endif

            tT1_Layinn(nv0lite) = tr_innerlayer(nm)
            tT2_Layinn(nv0lite) = tr_innerlayer(mz)
            tT1_Layout(nv0lite) = tr_outerlayer(nm)
            tT2_Layout(nv0lite) = tr_outerlayer(mz)
            tT1_ID(nv0lite)     = nm 
            tT2_ID(nv0lite)     = mz
            tT1_Ndof(nv0lite) = tr_Ndof(nm)
            tT2_Ndof(nv0lite) = tr_Ndof(mz)  

            stt1(nv0lite)     = stt_par(nm)
            stt2(nv0lite)     = stt_par(mz)
            ent1(nv0lite)=1
	    ent2(nv0lite)=1

	    do k=1,3
            tP1(k,nv0lite) = real( mom1M(k,nm))
            tP2(k,nv0lite) = real(mom2M(k,mz))
	    tPk(k,nv0lite) = real(mom1M(k,nm)+mom2M(k,mz))
            enddo
		
            tInvmass_K0(nv0lite)=
     +vmass(Mpion,Mpion,1,-1,1,-1,mom1M,mom2M,nm,mz)
            tInvmass_Lambda(nv0lite)=
     +vmass(Mpion,Mp,-1,1,tQ1(nv0lite),tQ2(nv0lite),mom1M,mom2M,nm,mz)
            tInvmass_Alambda(nv0lite)=
     +vmass(Mp,Mpion,-1,1,tQ1(nv0lite),tQ2(nv0lite),mom1M,mom2M,nm,mz)
            tInvmass_ee(nv0lite)=
     +vmass(Mpion,Mpion,1,-1,1,-1,mom1M,mom2M,nm,mz)

	   enddo
    
  		endif ! end of new algorithm
 900   continue  
	return  !Everything is ok
 999  continue
 
      ierr=1

      return
      end
 
      Subroutine callcolinear_withpar(bs,secvtx,pars,alpha,beta)

* S.Chekanov, modified by Andrii Verbytskyi for calculations with helix parameters 
* get 2D collinearity and 3D collinearity
** input: 
*         bs(3)   - beam spot
*         secvtx(3) - secondary vertex
*         mom(3)    - track parameters
** output:
*         alpha - 2D collinearity
*         beta  - 3D collinearity
         
      implicit none
	
	
      Real secvtx(3),bs(3)
      real pars(3,2)
      Real alpha,beta
      Double precision vtx1(3),mom(3)
      Double precision v0col,fac1,fac2
      mom(1)=dble(cos(pars(2,1))/abs(pars(3,1))
     ++cos(pars(2,2))/abs(pars(3,2)))
      mom(2)=dble(sin(pars(2,1))/abs(pars(3,1))
     ++sin(pars(2,2))/abs(pars(3,2)))
      mom(3)=dble(1/(tan(pars(1,1))*abs(pars(3,1)))+
     +1/(tan(pars(1,2))*abs(pars(3,2))))
     
      vtx1(1) = dble(secvtx(1)-bs(1))
      vtx1(2) = dble(secvtx(2)-bs(2))
      vtx1(3) = dble(secvtx(3)-bs(3))

* get 2D collinearity
             v0col = 9999.
             fac1 = sqrt(vtx1(1)**2 + vtx1(2)**2)
     +            * sqrt(mom(1)**2 + mom(2)**2)
             fac2 = vtx1(1)*mom(1) + vtx1(2)*mom(2)
             if ((fac1.gt.0.).and.(fac1.ge.fac2)) then
               v0col = acos(fac2/fac1)
             endif
             alpha =real(v0col)


** get 3D collinearity
             v0col = 9999.
             fac1 = sqrt(vtx1(1)**2 + vtx1(2)**2+ vtx1(3)**2)
     +            * sqrt(mom(1)**2 + mom(2)**2 + mom(3)**2)
             fac2 = vtx1(1)*mom(1) + vtx1(2)*mom(2) + vtx1(3)*mom(3) 
             if ((fac1.gt.0.).and.(fac1.ge.fac2)) then
               v0col = acos(fac2/fac1)
              endif  
              beta =real(v0col)

	return
      end



	
	 real  function vmass(m1,m2,etq1,etq2,q1,q2,mom1,mom2,nm,mz)
* Andrii Verbytskyi
* calculates V0 mass
** input: 
*         m1,m2   -  track masses
*         etq1,etq2 - expected track charges  - secondary vertex
*         q1,q2 -  track charges  - secondary vertex
*         nm,mz - track numbers in track parameters array
*         mom1(4,imax),mom2(4,imax)    - track parameters array
** output:
*         vmass - invariant mass

		implicit none
		real m1,m2
		integer q1,q2,etq1,etq2,nm,mz,k
		double precision mom1(3,400),mom2(3,400),momk(4)
		do k=1,3
		momk(k)=mom1(k,nm)+mom2(k,mz)
		enddo
	if((q1.eq.etq1).and.(q2.eq.etq2)) then
		
	momk(4)=sqrt(mom1(1,nm)*mom1(1,nm)+mom1(2,nm)*mom1(2,nm)
     ++mom1(3,nm)*mom1(3,nm)+m1*m1)
     ++sqrt(mom2(1,mz)*mom2(1,mz)+mom2(2,mz)*mom2(2,mz)
     ++mom2(3,mz)*mom2(3,mz)+m2*m2)

		elseif ((q1.eq.etq2).and.(q2.eq.etq1)) then
		momk(4)=sqrt(mom1(1,nm)*mom1(1,nm)+mom1(2,nm)*mom1(2,nm)
     ++mom1(3,nm)*mom1(3,nm)+m2*m2)
     ++sqrt(mom2(1,mz)*mom2(1,mz)+mom2(2,mz)*mom2(2,mz)
     ++mom2(3,mz)*mom2(3,mz)+m1*m1)
		elseif(abs(q1).ne.1.or.abs(q2).ne.1) then
		vmass=0.0
		return
		endif
		vmass=Real(sqrt(momk(4)*momk(4)-momk(1)*momk(1)  
     +-momk(2)*momk(2)-momk(3)*momk(3) ))
		return
		end 

		