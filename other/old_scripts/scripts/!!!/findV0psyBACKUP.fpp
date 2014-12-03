*********************
*     K0s finder    *
*                   *
*  Libov Vladyslav  *
*  February 2008    *
*                   *
*********************

      subroutine findV0psy

* Orange include files:
#include "trk_ntup.inc"
#include "vtxtup.inc"
#include "sintup.inc"
#include "beamspot.inc"
* My include file:
#include "V0psy.inc"
      integer i,j,v,vmin
      real pabs                      !total momentum of the cand.
      real pabs1,pabs2               !total momentum of the trks
      real fac1,fac2,fac3
      real x_disp
      real y_disp
      real z_disp
      real bs1,bs2
      parameter (ptmin=0.15)
      real pt1,pt2
      real coll2d(120),coll3d(120)
      real px,py,pz
      real coll2dmin

C       Initialize number of selected V0s
	nV0psy = 0
	if (trk_ntracks.le.1) goto 100
	if (trk_ntracks.gt.300) goto 100

C	write (*,*) 'Ora_vtx: ', Ora_xvtx, ' ', Ora_yvtx, ' ', Ora_zvtx, 'yoo '
C	if (bspt_prog.gt.0) write (*,*) 'Beamspot: ' ,bspt_x , ' ', bspt_y, ' ', bspt_z, 'yo '
C       if (bspt_prog.gt.0) write (*,*) 'Bspt_prog=0'

	write(*,*) 'Number of vertices: ', trk_nvert

	do i=1,trk_ntracks-1						!first track loop

	   if (SiTrkNr(1).eq.trk_id(i)) goto 20				!remove Sinistra electron
	   if (trk_layouter(i).lt.3) goto 20

	   do j=i+1,trk_ntracks						!second loop

	      if (SiTrkNr(1).eq.trk_id(j)) goto 10  			!remove Sinistra electron
	      if (trk_layouter(j).lt.3) goto 10
	      if (trk_charge(i)*trk_charge(j).ge.0.) goto 10		!take only opposite charge trks
	      pt1=sqrt(trk_px(i)**2+trk_py(i)**2)
	      pt2=sqrt(trk_px(j)**2+trk_py(j)**2)
	      if ((pt1.lt.ptmin).or.(pt2.lt.ptmin)) goto 10

C	      x_disp = Ora_xsecvtx(trk_vtx(i)) - Ora_xvtx
C	      y_disp = Ora_ysecvtx(trk_vtx(i)) - Ora_yvtx
C	      z_disp = Ora_zsecvtx(trk_vtx(i)) - Ora_zvtx
	      bs1=Ora_xvtx
	      bs2=Ora_yvtx
	      if (bspt_prog.gt.0) then
	         bs1=bspt_x
	         bs2=bspt_y
	      endif
C	      Candidate momentum
	      px = trk_px(i) + trk_px(j)
	      py = trk_py(i) + trk_py(j)
	      pz = trk_pz(i) + trk_pz(j)

	      coll2dmin=9999.
              vmin=1000

	      do v=1,trk_nvert

	         if (vtx_prim(v).eq.true) goto 30
		 x_disp = Ora_xsecvtx(vtx_id(v)) - bs1
	         y_disp = Ora_ysecvtx(vtx_id(v)) - bs2
	         z_disp = Ora_zsecvtx(vtx_id(v)) - Ora_zvtx
	         fac1 = sqrt(x_disp**2 + y_disp**2+z_disp**2)
     +           *sqrt(px**2+py**2+pz**2)
	         fac2=x_disp*px+y_disp*py+z_disp*pz
	         if ((fac1.gt.0.).and.(fac1.ge.fac2)) then
	            coll3d(v) = acos(fac2/fac1)
	         else
	            coll3d(v) = 999.
	         endif
	         fac1 = sqrt(x_disp**2 + y_disp**2)
     +           *sqrt(px**2+py**2)
	         fac2=x_disp*px+y_disp*py
	         if ((fac1.gt.0.).and.(fac1.ge.fac2)) then
	            coll2d(v) = acos(fac2/fac1)
	         else
	            coll2d(v) = 999.
	         endif

                 if (coll2d(v).lt.coll2dmin) then
	            coll2dmin=coll2d(v)
	            vmin=v
	         endif

 30	         continue
	      enddo


	      if (vmin.eq.1000) goto 10

	      if ((coll2d(vmin).gt.0.15).or.(coll3d(vmin).gt.0.3)) goto 10
C	      if (coll2dmin.gt.0.3) goto 10
C             if ((coll2d(vmin).gt.0.15).or.(coll3d(vmin).gt.0.3)) goto 10
	      nV0psy = nV0psy + 1

C	      ID of the track in the trk_ntracks array
	      tt1_id(nV0psy) = trk_id(i)
	      tt2_id(nV0psy) = trk_id(j)
C	      3-momentum of the pions
	      p1(1,nV0psy) = trk_px(i)
	      p1(2,nV0psy) = trk_py(i)
	      p1(3,nV0psy) = trk_pz(i)
	      p2(1,nV0psy) = trk_px(j)
	      p2(2,nV0psy) = trk_py(j)
	      p2(3,nV0psy) = trk_pz(j)
C             Candidate displacement
	      x_disp = Ora_xsecvtx(vtx_id(vmin)) - bs1
	      y_disp = Ora_ysecvtx(vtx_id(vmin)) - bs2
	      z_disp = Ora_zsecvtx(vtx_id(vmin)) - Ora_zvtx
C	      Decay length of the V0 candidate
	      v0dlen(nV0psy) = sqrt(x_disp**2 + y_disp**2 + z_disp**2)
C	      Collinearity angle of the V0 candidate
	      v0coll2d(nv0psy)=coll2d(vmin)
	      v0coll3d(nv0psy)=coll3d(vmin)
 10	      continue
	   enddo
 20	   continue
	enddo
 100 	continue
	write(*,*) 'Number of psy k0s: ', nv0psy
	return
	end
