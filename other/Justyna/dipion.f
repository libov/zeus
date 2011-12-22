      REAL FUNCTION dipion()

      Implicit none 
      include ?

      integer trtyp
      parameter (trtyp=3)
      Real mass,mass_k
      Parameter (mass=0.13957,mass_k=0.4937)
      real elastic_cut
      parameter (elastic_cut = 0.35)

      integer i

      real test,year,proc,whlumi
      real m_gen,t_gen,q2_gen,w_gen,
     $   th_tr_gen(2),ph_tr_gen(2),p_tr_gen(4,2),en_tr_gen(2)
     
      
      real minv,minv_el,minv_kk
      real p_tr(4,2)


      integer NUMBER_ELECTRON_TRK,electron_trk

      logical mc
      integer nvtx(2),ntr1,ntr2,no_el,pos,neg
      real p_trk(4,2),pt_trk(2),ph_trk(2),th_trk(2)
      real endpos_trk(3,2),endmom_trk(3,2),charge_trk(2)
      real pt_trak(2),en_tr(2),ph_tr(2),th_tr(2)
      
      real theta_el,phi_el,pele(4),e_pz
      real bestx, besty

      real prhod(4),th_gp,thelr,philr,psilr
      


      logical elastic_event,cut_event, box_cut


      vector val(35)

      real w_elec,q2_elec,t_rec,x_wyp

      real waga

      waga=1.
      elastic_event = .true.
      cut_event = .false.
      box_cut = .false. 

* cuts
* number of track 
* 
      call mc_variables(m_gen,t_gen,q2_gen,w_gen,
     $     th_tr_gen,ph_tr_gen,p_tr_gen,en_tr_gen)
      
      
      call weight_sub(waga)
      
      
      val(1) =  val(1) + 1
      if(.not.(btest(tltw(3),20))) goto 999 ! trigger selection

      call number_electron_trk1(trtyp,number_electron_trk,
     $     electron_trk,nvtx)

      val(2) =  val(2) + 1
      if ((trk_ntracks - number_electron_trk).ne.2) then 
         goto 999
      endif
      val(3) =  val(3) + 1
      
      call rem_elec_trk(mc,nvtx,ntr1,ntr2,p_trk,pt_trk,th_trk,
     +     ph_trk,
     +     endpos_trk,endmom_trk,charge_trk,no_el)


    

      CALL kontrol_variable(mass,ntr1,ntr2,th_trk,ph_trk,charge_trk,
     &     p_trk,ph_tr,th_tr,en_tr,p_tr,pt_trak,pos,neg)

      call inv_mass(p_tr,minv,minv_el,minv_kk)

      write(*,*) 'pos',pos
      

*      call trismmm(runnr,eventnr,p_tr,endmom_trk,endpos_trk,
*     +     zufopos,nzufos,zufoECAL,zufoEEMC,theta_el,dca_all,
*     +     dca_min,elast1,flaga_cal)
 
      call elasticity_cut(elastic_cut,elastic_event)
     
      if(.not.elastic_event) goto 999
      val(4) =  val(4) + 1

      if ((charge_trk(1)+charge_trk(2)).ne.0)  goto 999

c layers

c box cut       
      call electron_variables(en_tr,p_tr,th_tr,
     $     theta_el,phi_el,pele,e_pz,cut_event)


      bestx=SiPos(1,1)
      besty=SiPos(2,1)

      val(5) =  val(5) + 1

      call box_cut1(bestx,besty, box_cut)
      if (box_cut) goto 999


      val(6) =  val(6) + 1

      if (minv.lt.0.1.or.minv.gt.2.4) goto 999  

      val(7) =  val(7) + 1

      if(minv_kk.gt.1.01.and.minv_kk.le.1.03) goto 999

      val(7) =  val(7) + 1

      if (cut_event) goto 999
      val(8) =  val(8) + 1

      do i=1,4
         prhod(i)=p_tr(i,pos)+p_tr(i,neg)   
      enddo        
      
      call  helicityd (pele,p_tr,prhod,pos,th_gp,thelr,philr,psilr)


      call kinematic_variables(pele,theta_el,phi_el,e_pz,
     $     p_tr,w_elec,t_rec,q2_elec)

      if (w_elec.lt.40..or.w_elec.gt.1600.) goto 999

      val(9) =  val(9) + 1

      if (q2_elec.lt.5..or.q2_elec.gt.80.) then
         write(*,*) 'q2_elec',q2_elec
         goto 999
      endif
c      if (q2_elec.lt.5.) goto 999
      val(10) = val(10)  + 1

      if (t_rec.gt.0.6) goto 999
      val(11) = val(11) + 1 

      
      
      call fcal_check




c      w_elec = 1.
c      t_rec  = 1.
c      q2_elec= 1.
      x_wyp = 1. 

      call con_plots(8000,w_elec,t_rec,q2_elec,minv,
     &     th_tr,ph_tr,p_tr,en_tr,x_wyp,waga)
      
      call helicity_plots(8000,thelr,philr,psilr)



 999  continue
      return
      end

**********************************************

      Subroutine mc_variables(m_gen,t_gen,q2_gen,w_gen,
     $   th_tr_gen,ph_tr_gen,p_tr_gen,en_tr_gen)

      Implicit none 
      include ?

      integer i
      real t_gen,m_gen,q2_gen,w_gen
      real th_tr_gen(2),ph_tr_gen(2)
      real p_tr_gen(4,2),en_tr_gen(2)

      t_gen    = -tg
      m_gen    = sqrt((ppi(4)+npi(4))**2-(ppi(1)+npi(1))**2
     +       -(ppi(2)+npi(2))**2-(ppi(3)+npi(3))**2 )
      q2_gen=q2
      W_gen    = Wgpg
         
      th_tr_gen(1) = atan2(sqrt(ppi(1)**2+ppi(2)**2),ppi(3))
      ph_tr_gen(1) = atan2(ppi(2),ppi(1))
      th_tr_gen(2) = atan2(sqrt(npi(1)**2+npi(2)**2),npi(3))
      ph_tr_gen(2) = atan2(npi(2),npi(1))
      
      do i=1,4
         p_tr_gen(i,1) = ppi(i)
         p_tr_gen(i,2) = npi(i)
      enddo
      en_tr_gen(1) = ppi(4)
      en_tr_gen(2) = npi(4)  
      

      return 
      end 

c      integer function electron(prob)

      Subroutine electron1(electron)

      Implicit none 
      include ?

      integer electron
      integer i, nel
      real prob 
      
      nel=0
      electron = 0
      prob = 0. 

      if (sincand.eq.0) then
         electron = 0 
         goto 98
      endif

      do i=1,Sincand
         if (prob.lt.SiProb(i)) then
            prob=SiProb(i)
            nel=i
         endif
      enddo

      


      if (Siprob(nel).lt.0.9) then 
         electron = 0 ! jesli elekton zero to fo nie znaleziono
      else
         electron  = nel 
      endif


 

c spr_bo ja chyba ignoruje ta rutynke

c1      call macz_elec(trk_ntracks,SiPos1,trk_endmom,trk_endpos,
c1     +     trk_isl,trk_elec)


 98   continue
      return 
      end




      subroutine number_electron_trk1(trtyp,number_electron_trk,
     $     electron_trk,nvtx)
      Implicit none 

      include ?


      integer j,i,trtyp,tr_el, tr_no_el
      integer nel
      integer electron,nvtx(2)
      integer number_electron_trk
      integer electron_trk
      
      
      

      call electron1(electron)
      
c      write (*,*)'number_electron_trk',trk_ntracks,
c     $     Sitrknr(electron),trtyp

      j=0
      tr_no_el = 0 
      tr_el = 0

      do i=1,2
          nvtx(i) = 0
      enddo

      do i = 1, trk_ntracks        
           if (trk_type(i).eq.trtyp) then 
c              write(*,*) 'electron1',i,tr_el,trk_type(i),electron,
c     $             Sitrknr(electron)
              if (i.eq.Sitrknr(electron)) then 
                 tr_el=tr_el+1   
                 electron_trk = Sitrknr(electron)
c                 write(*,*) 'electron',tr_el,electron_trk
              else
                 tr_no_el = tr_no_el + 1
c                 write(*,*) 'electron2',i,tr_no_el
                 if (tr_no_el.gt.2) then 
                    write(*,*) 'tr_no_el.gt.2',tr_no_el 
     $                   ! spr co to za przypadki
                 endif
                 j=j+1
                 nvtx(j) = i                   
              endif
           endif
      enddo 

      number_electron_trk = tr_el      ! jak jest 0 lub 1 to ok 
     

      return 
      end



      Subroutine inv_mass(p_tr,minv,minv_el,minv_kk)

      Implicit none

      integer i
      real p_tr(4,2)
      real p_help(3),en(2),en_kk(2)
      real en_el(2),sum_el_e2,sum_kk_e2, minv2_el,minv_el
      real sum_p2, sum_e2,minv,minv2,pt_data
      real mass_pi,mass_el,mass_k,minv_kk,minv2_kk
      parameter (mass_pi=0.139570)
      parameter (mass_K=0.4937)
      parameter (mass_el=0.0005)

      do i=1,3
         p_help(i)=p_tr(i,1)+p_tr(i,2)
      enddo
      do i=1,2
         en(i)   = sqrt(p_tr(4,i)**2 + mass_pi**2)
         en_el(i)= sqrt(p_tr(4,i)**2 + mass_el**2)
         en_kk(i)= sqrt(p_tr(4,i)**2 + mass_k**2)
      enddo
      sum_p2 = p_help(1)**2+ p_help(2)**2 + p_help(3)**2
      sum_e2 = (en(1) + en(2))**2
      sum_el_e2 = (en_el(1) + en_el(2))**2
      sum_kk_e2 = (en_kk(1) + en_kk(2))**2
      minv2=sum_e2-sum_p2
      minv2_el=sum_el_e2-sum_p2
      minv2_kk=sum_kk_e2-sum_p2
      if(minv2.le.0..or.minv2_el.le.0) then
         write(*,*) 'Masa_inv: Error in minv2'
      endif
      minv=sqrt(minv2)
      minv_el=sqrt(minv2_el)
      minv_KK=sqrt(minv2_KK)

      return
      end


      Subroutine helicity_plots(nr_his,thelr,philr,psilr)
      Implicit none 

      integer nr_his
      real thelr,philr,psilr
      
      call hfill(nr_his+50,thelr,0.,1.)
      call hfill(nr_his+51,philr,0.,1.)     
      call hfill(nr_his+52,psilr,0.,1.)     


      return
      end




      Subroutine  con_plots(nr_his,w,t,q2,mass,
     $     th,phi,p_tr,en,x,weight)

      Implicit none
      
      real weight
      real w,t,q2,mass
      real th(2),phi(2),p_tr(4,2)
      real en(2),x
      integer nr_his


     
      call hfill(nr_his+1,w,0.,weight)
      call hfill(nr_his+2,t,0.,weight)
      call hfill(nr_his+3,q2,0.,weight)
      call hfill(nr_his+4,mass,0.,weight)
      call hfill(nr_his+5,sqrt(p_tr(1,1)**2+p_tr(2,1)**2),0.,weight)      
      call hfill(nr_his+6,sqrt(p_tr(1,2)**2+p_tr(2,2)**2),0.,weight)         
      call hfill(nr_his+7,p_tr(1,1),0.,weight) 
      call hfill(nr_his+8,p_tr(1,2),0.,weight) 
      call hfill(nr_his+9,p_tr(2,1),0.,weight) 
      call hfill(nr_his+10,p_tr(2,2),0.,weight)      
      call hfill(nr_his+11,p_tr(3,1),0.,weight)       
      call hfill(nr_his+12,p_tr(3,2),0.,weight)       
      call hfill(nr_his+13,en(1),0.,weight)
      call hfill(nr_his+14,en(2),0.,weight)
      call hfill(nr_his+15,th(1),0.,weight)
      call hfill(nr_his+16,th(2),0.,weight)      
      call hfill(nr_his+17,phi(1),0.,weight)
      call hfill(nr_his+18,phi(2),0.,weight)
      call hfill(nr_his+19,w,0.,weight)


      return
      end
      

      Subroutine rem_elec_trk(mc,nvtx,ntr1,ntr2,p_trk,pt_trk,th_trk,
     +     ph_trk,
     +     endpos_trk,endmom_trk,charge_trk,no_el)
 


      Implicit none 
*
* rutynka przepisuje zmienne z ntupli, 
* na zmienne z wyrzuconym torem od elektronu
*

      include ?

      Integer max_trk,no_el
      parameter (max_trk=2)
      real p_trk(4,max_trk),ph_trk(max_trk),th_trk(max_trk)
      real endpos_trk(3,max_trk),endmom_trk(3,max_trk)
      real pt_trk(max_trk),charge_trk(max_trk)
      integer ntr1,ntr2,FL_NO_EL (max_trk)
      integer i,j,nvtx(2)
      logical mc

      do i=1,2
         do j=1,4
            p_trk(j,i) = -100.
         enddo
         th_trk(i) = -100.
         pt_trk(i) = -100.
         ph_trk(i) = -100.
         charge_trk(i) =  -100.
         do j=1,3
            endpos_trk(j,i) = -100.
            endmom_trk(j,i) = -100.
         enddo
      enddo
      no_el = 0  
*      write(*,*)'**********'
      do i = 1,trk_ntracks
*         if (trk_type(i).eq.3) then
            if ((i.ne.nvtx(1)).and.(i.ne.nvtx(2))) goto 12
*            write(*,*) 'rutynka', nvtx(1),nvtx(2)
            no_el = no_el + 1
            if(no_el.ge.3)  then
               write(*,*)'NO_EL'
               goto 12
            endif
            do j=1,3
               endpos_trk(j,no_el) = trk_endpos (j,i)
               endmom_trk(j,no_el) = trk_endmom (j,i)
            enddo
            if (mc) then 
               p_trk(1,no_el) = trk_px(i)
               p_trk(2,no_el) = trk_py(i) 
               p_trk(3,no_el) = trk_pz(i) 
            else
               p_trk(1,no_el) = trk_px(i)!*(1.-0.0046)!*1.0046
               p_trk(2,no_el) = trk_py(i)!*(1.-0.0046)!*1.0046
               p_trk(3,no_el) = trk_pz(i)!*(1.-0.0046)!*1.0046
            endif
            th_trk(no_el) = atan2(sqrt(p_trk(1,no_el)**2+
     +           p_trk(2,no_el)**2),p_trk(3,no_el))
            pt_trk(no_el) = sqrt(p_trk(1,no_el)**2+p_trk(2,no_el)**2)
            ph_trk(no_el) = atan2(p_trk(2,no_el),p_trk(1,no_el))
            p_trk(4,no_el)=sqrt(p_trk(1,no_el)**2+p_trk(2,no_el)**2
     &           +p_trk(3,no_el)**2)
            charge_trk(no_el)   = trk_charge(i)
            fl_no_el(no_el)=i
*         enddo
 12   enddo
*     write (*,*) p_trk(3,1),p_trk(3,2), charge_trk
      ntr1=fl_no_el(1)
      ntr2=fl_no_el(2)     
      if(no_el.ne.2) then
         write(*,*)'RUUUUUUUUUUUUUUUU',no_el
      endif


      return
      end
c
c
c
c
      
      Subroutine kontrol_variable(mass,ntr1,ntr2,th_trk,ph_trk,
     &     charge_trk,p_trk,ph_tr,th_tr,en_tr,p_tr,pt_tr,pos,neg)

      Implicit none

      integer i
      integer pos,neg
      real th_trk(2),ph_trk(2)
      real p_trk(4,2)
      real ph_tr(2),en(2),charge_trk(2)
      real en_tr(2),p_tr(4,2),th_tr(2)
      real pt(2), pt_tr(2),ped(2),pt_tot(2)
      integer NTR1,NTR2,J
      real mass

      pos=0
      neg=0
 
      
      do i=1,2
         ped(i)   =  -100.
         en(i)    =  -100.
         pt(i)    =  -100.
         pt_tot(i)=  -100.
         ph_tr(i) =  -100.
         th_tr(i) =  -100.
         en_tr(i) =  -100.
         do j=1,4
            p_tr(j,i) =  -100.
         enddo
      enddo


      do i=1,2
         ped(i)   = p_trk(4,i)
         en(i)    = sqrt(ped(i)**2 + mass**2)
      enddo

      if (charge_trk(1).gt.0) then
c      if (en(1).gt.en(2)) then
         pos=1
         neg=2
      else
         pos=2
         neg=1
      endif

      ph_tr(1) = ph_trk(pos)*(180/3.141592654)
      ph_tr(1)=180.-ph_tr(1)
      th_tr(1) = th_trk(pos)*(180/3.141592654)
      do i=1,4
         p_tr(i,1) =  p_trk(i,pos)
         p_tr(i,2) =  p_trk(i,neg)
      enddo


      do j=1,2
         en_tr(j)=sqrt(p_tr(4,j)**2 + mass**2)
         pt_tr(j) = sqrt(p_tr(1,j)**2+p_tr(2,j)**2)
      enddo

      ph_tr(2) = ph_trk(neg)*(180/3.141592654)
      ph_tr(2)=180.-ph_tr(2)
*      if (ph_tr(2).le.0) ph_tr(2)=180.-ph_tr(2)
      th_tr(2) = th_trk(neg)*(180/3.141592654)


      th_tr(1)=th_tr(1)*3.14159/180.
      th_tr(2)=th_tr(2)*3.14159/180.
      pos=1
      neg=2

      return
      end


     

      Subroutine elasticity_cut(elast_cut,elastic_event)
      Implicit none 

      include ?
      integer i
      real elast_cut
      logical elastic_event
      real ggg, sum_ene_zufo

      elastic_event = .true.

c      write(*,*) 'elast_cut',elast_cut

      sum_ene_zufo = 0. 
      do i=1,Nzufos
         ggg=0.
         ggg=atan2(sqrt(zufopos(1,i)**2+
     &        zufopos(2,i)**2),zufopos(3,i))
         ggg=ggg*180./3.14

         if (ggg.gt.2.2.and.ggg.lt.22.) then 
            sum_ene_zufo=sum_ene_zufo+zufoECAL(i)
	  goto 88
         endif

         if (tufo(1,i).eq.31.and.zufoECAL(i).gt.elast_cut) 
     $        elastic_event = .false.


 88      continue 
      enddo

c      if (sum_ene_zufo.gt.1.5) elastic_event = .false.
      
      return 
      end


      subroutine electron_variables(en_tr,p_tr,th_tr,
     $     theta_el,phi_el,pele,e_pz,cut_event)
      Implicit none 
      
      include ?

      real en_tr(2),p_tr(4,2),th_tr(2)
      real pele(4)
      real bestx,besty,bestz,bestE
      real electron,e_pz
      real theta_el,phi_el
      real E_pz1,E_elec
      real ene_el
      parameter (ene_el=27.5)
      logical cut_event
      cut_event=.false.

c call electron1(electron)
      electron = 1

      bestx=Sipos(1,electron)
      besty=Sipos(2,electron)       
      bestz=Sipos(3,electron)  
      bestE=SiECorr(3,electron) 

      if (abs(bestx).gt.600.or.abs(besty).gt.600) then 
         cut_event = .true.
      endif
      theta_el=atan2(sqrt((bestx-Xvtx)**2+(bestY-Yvtx)**2),BESTZ-Zvtx)
      phi_el=atan2(besty-Yvtx,bestx-Xvtx)


    
      e_pz =en_tr(1)-p_tr(4,1)*cos(th_tr(1))
     $     +en_tr(2)-p_tr(4,2)*cos(th_tr(2))
      
      if (theta_el.eq.0.) then 
         E_elec=0.
      else
         E_elec=(2*ene_el-e_pz)/(1.-cos(theta_el))
      endif
      write (*,*) 'theta_el',theta_el,phi_el,e_elec

      pele(1)= E_elec*sin(theta_el)*cos(phi_el)
      pele(2)= E_elec*sin(theta_el)*sin(phi_el)     
      pele(3)= E_elec*cos(theta_el)
      pele(4)= E_elec

      E_pz1=bestE*(1.-cos(theta_el))+e_pz

      
      call hfill(110,E_elec,0.,1.)
      call hfill(111,pele(1),0.,1.)
      call hfill(112,pele(2),0.,1.)    
      call hfill(113,pele(3),0.,1.)


      return 
      end





      Subroutine kinematic_variables(pele,theta_el,phi_el,e_pz,
     $     p_tr,w_elec,t_rec,q2_elec)
      
      Implicit none

      real pele(4),theta_el,phi_el,e_pz
      real p_tr(4,2),E_elec
      real w_elec,t_rec,q2_elec
      real ene_el
      parameter (ene_el=27.5)
      

      E_elec = pele(4)
      Q2_elec=4*ene_el*E_elec*(1.-sin(0.5*theta_el)**2)
      W_elec = sqrt(2*920.*e_pz-Q2_elec+0.938**2)
      t_rec =(pele(1)+p_tr(1,1)+p_tr(1,2))**2
     $     +(pele(2)+p_tr(2,1)+p_tr(2,2))**2

      write (*,*) 't_rec',pele(1),p_tr(1,1),p_tr(1,2)
     $     ,pele(2),p_tr(2,1),p_tr(2,2),t_rec

      return
      end




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


      Subroutine box_cut1(bestx,besty, box_cut)

      Implicit none
      include ?

      real bestx,besty
      logical box_cut

      box_cut = .false.

      if ((bestx.lt.14..and.bestx.gt.-16.
     +     .and.abs(besty).lt.14.)) box_cut = .true.
      if ((((bestx+10.90).gt.-2.)
     +     .and.((bestx+10.90).lt.2.)
     +     ).and.besty.lt.0.) box_cut = .true.
      if ((((bestx-9.26).gt.-2.)
     +     .and.((bestx-9.26).lt.2)
     +     ).and.besty.gt.0.) box_cut = .true.

      return 
      end
      




      Subroutine fcal_check
      Implicit none 

      real e_emc_1r, e_emc_2r
      
      include ?

* energia w 1R hac 
* energia w 1r emc przy cieciu na 1r hac<1 i przy cieciu 1<1rhac<2


      e_emc_1r=CAL_E-Pex1IR(4)-f1rhac

      call hfill(21,e_emc_1r,0.,1.)
      call hfill(22,f1rhac,0.,1.)
      if (f1rhac.le.1) then 
          call hfill(23,e_emc_1r,0.,1.)
       elseif(f1rhac.gt.1.and.f1rhac.le.2.) then  
          call hfill(24,e_emc_1r,0.,1.)
       else
          call hfill(25,e_emc_1r,0.,1.)
       endif





      e_emc_2r=CAL_E-Pex2IR(4)-f2rhac

      call hfill(31,e_emc_2r,0.,1.)
      call hfill(32,f2rhac,0.,1.)
      if (f2rhac.le.1) then 
          call hfill(33,e_emc_2r,0.,1.)
       elseif(f2rhac.gt.1.and.f2rhac.le.2.) then  
          call hfill(34,e_emc_2r,0.,1.)
       else
          call hfill(35,e_emc_2r,0.,1.)
       endif










      return 
      end
      



      Subroutine weight_sub(weight_s)
      Implicit none 
      include ?
      
      real eps,epsg,RRR,weight_s
      real q2_gen
      
      parameter (epsg=0.99,eps=0.99)
      
      q2_gen=q2
      
      RRR=0.84*Q2_gen/(1.+0.122*Q2_gen)
      
      
      weight_s=(1./(1.+RRR*eps)) *(3./8./3.14159)*
     $     ( (1.-thel**2)*(1.+eps*cos(2.*(phil-psil))) +
     $        2.*eps*RRR*thel**2
     $     - sqrt(2.*eps*(1.+eps)*RRR)*
     $     cos(phil-psil)*2.*thel*sqrt(1.-thel**2) )
      weight_s=weight_s*4.0*3.14159



      return 
      end
