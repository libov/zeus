      subroutine dis_true
      implicit none
#include "partap.inc"
#include "fmckin.inc"
#include "distruetup.inc"
c
      integer i, nd, ndump, nev, nFMCKin
      logical Lepton, Boson, Gluon, Photon, Quark
      integer lepprt1,lepprt3
      data nev/0/ ndump/0/
c
c     initialzie
      call dis_true_init(nboson,  pboson,  idboson,  doboson)
      call dis_true_init(nlepton,   plepton,   idscatlep,   dolepton)
      call dis_true_init(nradpho, pradpho, idradpho, doradpho)
      call dis_true_init(nquark,  pquark,  idquark,  doquark)
      call dis_true_init(ngluon,  pgluon,  idgluon,  dogluon)
      QuarkPrt = 0
      nqg = 0
      nFMCKin = CouTab(FMCKin)
c
      call FetTab(FMCKin, id, 1)
      lepprt1 = FMCKin_FMCPrt
      call FetTab(FMCKin, id, 3)
      lepprt3 = FMCKin_FMCPrt
c
      do i = 1, nFMCKin
        call FetTab(FMCKin, id, i)
        Photon = (FMCKin_FMCPrt.eq.29)
        Lepton = (FMCKin_FMCPrt.ge.17.and.FMCKin_FMCPrt.le.28)
        Boson =  (FMCKin_FMCPrt.ge.29.and.FMCKin_FMCPrt.le.32)
        Gluon =  (FMCKin_FMCPrt.eq.33)
        Quark =  (FMCKin_FMCPrt.ge. 1.and.FMCKin_FMCPrt.le.12)

        if (FMCKin_Decay) then
          if (FMCKin_DaughterOf.eq.1
** N.Vlasov; next line is added to take into account a specific MC record
     &   .or.(FMCKin_DaughterOf.eq.3.and.lepprt1.eq.lepprt3)) then
            if (Boson) then
c             exchanged boson
              call Dis_True_store(nboson, 1, pboson, idboson, doboson)
            end if
          else if (FMCKin_DaughterOf.eq.2 .or.
     &             FMCKin_DaughterOf.eq.INULL) then
            if (Quark) then
c             incoming quark
              if (nquark.eq.0) QuarkPrt = FMCKin_FMCPrt
              call Dis_True_store(nquark, 1, pquark, idquark, doquark)
            else if (Gluon) then
c             incoming gluon
              call Dis_True_store(ngluon, 1, pgluon, idgluon, dogluon)
            end if
          end if

          if ((Quark .or. Gluon).and.FMCKin_DaughterOf.le.nFMCKin) then
c           radiated quark or gluon
            call dis_true_store(nqg, nmax_qg, pqg, idqg, doqg)
            if (nqg.le.nmax_qg) prtqg(nqg) = FMCKin_FMCPrt
          end if
        else if (Lepton) then
c         scattered lepton
          if (FMCKin_DaughterOf.eq.0 .or. FMCKin_DaughterOf.eq.1)
     &    call Dis_True_store(nlepton, 1, plepton, idscatlep, dolepton)
        else if (Photon) then
c         radiated photon
          if (FMCKin_DaughterOf.le.idscatlep)
     &    call Dis_True_store(nradpho, 1, pradpho, idradpho, doradpho)
        end if
      end do
c
      nev = nev + 1
      if (nboson.eq.0 .or. nev.le.ndump) then
        Call PriTab(FMCKin,ID,MINC,MAXC,ALLCOL)
      end if
      return
c-------------------------------------------
      entry dis_true_ndump(nd)
      ndump = nd
      end

      subroutine dis_true_init(n, p, id, d)
      implicit none
      integer k, n, id, d
      real p(5)
c
      n = 0
      id = 0
      d = 0
      do k = 1, 5
        p(k) = 0.0
      end do
      end

      subroutine dis_true_store(n, nmax, p, id, dof)
      implicit none
#include "fmckin.inc"
      integer k, n, nmax
      real p(5,nmax)
      integer id(nmax), dof(nmax)
c
      n = n + 1
      if (n.gt.nmax) return
      id(n)  = FMCKin_ID
      if (FMCKin_DaughterOf .lt.1023) then
        dof(n) =  FMCKin_DaughterOf
      else
        dof(n) = -1
      end if
      do k = 1, 5
        p(k,n) = FMCKin_p(k)
      end do
      end
