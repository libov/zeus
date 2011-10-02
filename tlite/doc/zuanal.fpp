      Subroutine ZUANAL(IWant)
*     ************************
*     
*----------------------------------------------------------------
*     
*     Zeus User event ANALysis program. 
*     
*     The flag IWant is used to control the output of events. 
*     If IWant = 1 the event is written out; if IWant = 0 it is not.
*     
*----------------------------------------------------------------
*     
      Implicit NONE
      
#include "partap.inc"
#include "zdskey.inc"
#include "zttrhl.inc"



      Integer   iWant
      Integer   iErr
      Integer eventcount
      logical takeevent
      Logical First
      save    First
      Data    First / .TRUE. /
      Integer NTRKS
      Parameter(NTRKS=100)
      Real    par(5,NTRKS),cov(15,NTRKS),start(3),vertex(3),vertexcov(6)
      Real    newpar(3,NTRKS),chi,dca,par1(5),par2(5),tlidcav
      Real    weights(NTRKS)
      Real    cov1(15),cov2(15),bfieldz,bfield(3),chi2m,mass,mass2
      Double precision mom1(4),mom2(4),momcov1(10),momcov2(10)
      Double precision kmom(4),kmass,kcov(10)
      Real    parre1(5),parre2(5)
      Real    covre1(15),covre2(15),newpar1(3),newpar2(3)
      Real    xin(3),covxin(6),width(2),ndof
      Integer mode,err,iterations
      Integer ntracks,ii
      Integer i,j
      external tlidcav
*************************************************************************
*     By default do not write out the event
*     -------------------------------------

      iWant = 0
      iErr = 0
*     
C***********************************************
C     REJECT IF THE RECORD IS NOT AN EVENT (eg. BOR)
C***********************************************

      Call Fettab(ZDSkey,id,1)
      IF (ZDSKEY_GAFTyp(1:3) .NE. 'EVT') THEN
         RETURN
      ENDIF

C*******************************************
C     DO FIRST EVENT INITIALISATION AND PRINTOUT
C*******************************************
      
      If (First) then
         First = .false.
         write(*,*)'This is ZUANAL, first event'
         eventCount = 0
      EndIF   
      mode = 1
      mass  = 0.13957
      mass2 = 0.497648 
C get the primary vertex from the beam position           
      width(1) = 0.0120
      width(2) = 0.0030
      call vxlitebs(width,xin,covxin,iErr)               
      print *,'beam: ierr=',iErr,' vtx:',xin(1),',',xin(2),
     +     ',',xin(3)
      print *,'       cov=',covxin(1),',',covxin(2),',',
     +     covxin(3),',',covxin(4),',',covxin(5),',',
     +     covxin(6)     
      iterations = 5
      do i = 1,coutab(ZTTRHL) 
         ZTTRHL_ID = i;
         call gettab(ZTTRHL) 
         do ii=1,5
            par(ii,1) = ZTTRHL_hel(ii)
            par1(ii)  = ZTTRHL_hel(ii)
         enddo
         do ii=1,15
            cov(ii,1) = ZTTRHL_cov(ii)
            cov1(ii)  = ZTTRHL_cov(ii)
         enddo
         do j = i+1,coutab(ZTTRHL)
            ZTTRHL_ID = j;
            call gettab(ZTTRHL)
            do ii=1,5
               par(ii,2) = ZTTRHL_hel(ii)
               par2(ii)  = ZTTRHL_hel(ii)
            enddo
            do ii=1,15
               cov(ii,2) = ZTTRHL_cov(ii)
               cov2(ii) = ZTTRHL_cov(ii)
            enddo
C     distance of closest approach of the two tracks
            dca = tlidcav(par1,par2,start)
            print *,'dca=',dca,' start:',start(1),',',start(2),',',
     +           start(3)	
            ntracks = 2;
C     vertex fit
            call vxlitefit(ntracks,par,cov,start,vertex,
     +           vertexcov,chi,newpar)
            print *,'vertex: ',vertex(1),',',vertex(2),',',vertex(3),
     +           ' chi2=',chi                 
            do ii = 1,3
               vertex(ii) = xin(ii)
            enddo
            do ii = 1,6
               vertexcov(ii) = covxin(ii)
            enddo
C     vertex fit with beam constraint and deterministic annealing
C     filter            
            call vxlitedaffit(ntracks,par,cov,vertex,vertexcov,20,1,
     +           chi,ndof,weights,newpar)
            print *,'daf vertex: ',vertex(1),',',vertex(2),',',
     +           vertex(3),' chi2/ndof=',chi,'/',ndof          
            do ii = 1,3
               vertex(ii) = xin(ii)
            enddo
            do ii = 1,6
               vertexcov(ii) = covxin(ii)
            enddo
C     vertex constraining fit
            call vxlitefititcstr(ntracks,par,cov,iterations,vertex,
     +           vertexcov,chi,newpar)
            print *,'cstr vertex: ',vertex(1),',',vertex(2),',',
     +           vertex(3),' chi2=',chi
C     iterated fit
            call vxlitefitit(ntracks,par,cov,start,iterations,vertex,
     +           vertexcov,chi,newpar)
            print *,'it vertex: ',vertex(1),',',vertex(2),',',
     +           vertex(3),' chi2=',chi
C     get magnetic field at vertex position
            call gufld(vertex,bfield);
C     calculate the invariant mass for the vertex fitted tracks
            do ii=1,3
               newpar1(ii) = newpar(ii,1)
               newpar2(ii) = newpar(ii,2)
            enddo
            call tlipnewpar(newpar1,bfield(3),mass,mom1)
            call tlipnewpar(newpar2,bfield(3),mass,mom2)
            do ii=1,4
               kmom(ii) = mom1(ii) + mom2(ii)
            enddo
            kmass = sqrt(kmom(4)**2 - kmom(1)**2 - kmom(2)**2 
     +           - kmom(3)**2)
            print *,'mass from new parameters:',kmass
C     change reference point for tracks            
            call vcreref(0,0,par1,cov1,vertex(1),vertex(2),parre1, 
     +           covre1)
            call vcreref(0,0,par2,cov2,vertex(1),vertex(2),parre2, 
     +           covre2)
C     calculate four momentum at the new reference point
            call tliphel(parre1,covre1,bfield(3),mass,mode,mom1,
     +           momcov1)
            call tliphel(parre2,covre2,bfield(3),mass,mode,mom2,
     +           momcov2)
            print *,'P1:;',mom1(1),',',mom1(2),',',mom1(3),',',
     +           mom1(4)
            print *,'P2:;',mom2(1),',',mom2(2),',',mom2(3),',',
     +           mom2(4)
            do ii=1,4
               kmom(ii) = mom1(ii) + mom2(ii)
            enddo
            do ii=1,10
               kcov(ii) = momcov1(ii) + momcov2(ii)
            enddo
C     calculate the invariant mass
            kmass = sqrt(kmom(4)**2 - kmom(1)**2 - kmom(2)**2 
     +           - kmom(3)**2)
            print *,'mass from tracks:',kmass
C     do a mass constraint fit
            call tlifitm(kmom,kcov,mass2,chi2m,err)
            kmass = sqrt(kmom(4)**2 - kmom(1)**2 - kmom(2)**2 
     +           - kmom(3)**2)
            print *,'mass constraint: mass=',kmass,' chi2:',chi2m,
     +           '  err:',err               
         enddo
      enddo
      
      Return
      End
      
