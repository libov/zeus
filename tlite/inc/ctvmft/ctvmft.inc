C============ include file for the constrained fit module CTVMFT ===============

C  Dimension Parameters
      INTEGER MaxVtx,MaxTrk,MaxMcn,MaxItr, MAXDIM
      PARAMETER (MaxVtx = 3)               ! maximum number of vertices
      PARAMETER (MaxMcn = 4)               ! maximum number of mass constraints
      PARAMETER (MaxTrk=100)               ! maximum number of tracks
      PARAMETER (MaxItr =10)               ! maximum number if iteration steps

      INTEGER UDIM
      Parameter ( UDIM = MaxTrk*(MaxVtx+MaxMcn+60)
     &                 + MaxVtx*(MaxVtx+18) + MaxMcn*6 +MaxItr + 31 )

C maximum matrix dimension;
C    = 3 parameters per (vertex + possible primary) (x,y,z) 
C     +2 possible conversion constraints per vertex (Phi,Ctg)
C     +2 possible "pointing" constraints per vertex (Phi,Ctg)
C     +3 parameters per track (Crv, Phi, Ctg)
C     +  number of mass constraints
      PARAMETER (MAXDIM = 7*(MaxVtx+1) + 3*MaxTrk + MaxMcn)


C  Required Input Fit Specification
      INTEGER  NVERTX                     ! Number of vertices
      INTEGER  NMASSC                     ! Number of mass constraints
      INTEGER  NTRACK                     ! Number of tracks, this fit

      LOGICAL  TRKVTX(MaxTrk,MaxVtx)      ! (Track,Vertex) association table
      INTEGER  VTXPNT(MaxVtx,2)           ! vertex association information
      INTEGER  CVTX(MaxVtx)               ! Conversion constraint specification
      LOGICAL  TRKMCN(MaxTrk,MaxMcn)      ! (Track,Mass_Constraint) table
      REAL     CMASS (MaxMcn)             ! Constraint mass

C  Required Input Track Specifications
      CHARACTER*4 TKBANK(MaxTrk)          ! Track bank type (e.g. 'TRKS')
      INTEGER  LIST  (MaxTrk)             ! Track bank number
      REAL     TMASS (MaxTrk)             ! Track mass assignment

C  Fit input, collected using the input specifications
      REAL     PAR0  (5,MaxTrk)           ! Original track parameter values
      REAL     G   (5,5,MaxTrk)           ! Fitted track parameter covariances

C  Optional Input, Required Data for Pointing Constraints
      REAL     XYZPV0(3), EXYZPV(3,3)     ! "Primary" vertex; XYZ, covariance

      INTEGER RUNNUM,TRGNUM ! "you can't tell the players without a score card"
      INTEGER ITER                        ! number of iterative steps taken
      INTEGER NTSCUT                      ! total number of cut steps, this fit

C  Output; Results of the Fit
      INTEGER  MATDIM                     ! Dimension of the matrix, this fit
      INTEGER  NDOF                       ! Fit number of degrees of freedom
      LOGICAL  VtxVtx(MaxVtx,MaxVtx)      ! vertex geneology
      REAL     CHISQR(0:MaxItr)           ! Overall fit Chi Square result
      REAL     CHIT(MaxTrk)               ! Track contribution to Chi Square
      REAL     CHIV(0:MaxVtx)             ! Vertex fit Chi Squares
      REAL     PAR (5,MaxTrk)             ! Fitted track helix parameters
      REAL     PARDIF(5,MaxTrk)           ! Parameter differences (fit - input)
      REAL     FMCDIF(MaxMcn)             ! Mass constraint residuals
      REAL     PCON(MaxVtx,2)             ! Pointing constraint tests
      REAL     SANG(MaxVtx,2)             ! Pointing constraint tests
      REAL     XYZVRT(3,0:MaxVtx)         ! Primary, Secondary vertices
      REAL     TrkP4(MaxTrk,6)            ! Track Px,Py,Pz,E,Pt P
      REAL     VtxP4(4,MaxVtx)            ! vertex 4-momentum sum
      REAL     McnP4(4,MaxMcn)            ! 4-momentum sum for mass constraint
      REAL     DDA(MaxTrk,8)              ! d(Px,Py)/d(Crv,Phi,Xs,Ys)
      REAL     DXYZPV(3)                  ! Primary vertex displacement in fit
      INTEGER  VOFF(MaxVtx),TOFF(MaxTrk)  ! offset pointers into VMAT
      INTEGER  POFF(MaxVtx),COFF(MaxVtx)  ! offset pointers into VMAT
      INTEGER  MOFF                       ! offset pointers into VMAT

C  "Memory"
      INTEGER  TKERR (MaxTrk)             ! Track error flag, from previous fit
      INTEGER  IJKERR(3)                  ! error code reporting

      DOUBLE PRECISION VMAT(MAXDIM,MAXDIM+1) ! Covariance matrix, fit parameters

      REAL         XYZPV(3)
      EQUIVALENCE (XYZPV,XYZVRT(1,0))

      INTEGER UVWXYZ(UDIM)
      Equivalence (UVWXYZ, Iter)


C  CTC first approximation and track-vertex step parameters
      REAL    DRMAX, RVMAX, DZMAX, TRNMAX, DSMIN
C  Momentum scale conversion factor, from (cm)**-1 to Gev/c
      REAL    PSCALE



C  single precision stuff
      COMMON /CTVMFq/ RUNNUM,TRGNUM, ITER,NTSCUT
     >,       NVERTX,NMASSC,NTRACK                ! Fit specification
     >       ,TRKVTX,TRKMCN,VTXPNT,CMASS,CVTX     ! ...Fit specification
     >       ,VTXVTX                              ! vertex geneology
     >       ,TKBANK,LIST,TMASS                   ! Tracks to use
     >       ,MATDIM                              ! Fit matrix dimension
     >       ,TKERR                               ! Track "error memory"
     >       ,NDOF, CHISQR,CHIT,CHIV              ! Fit dimension, quality
     >       ,XYZPV0,EXYZPV                       ! initial "primary" vertex
     >       ,XYZVRT,DXYZPV                       ! vertex coordinate results
     >       ,PAR,G                               ! Track fit results
     >       ,TrkP4,VtxP4,McnP4,DDA
     >       ,VOFF,TOFF,POFF,COFF,MOFF            ! vertex,track VMAT pointers
     >       ,PAR0,PARDIF                         ! Input parameters, fit step
     >       ,FMCDIF,PCON,SANG                    ! Mass/Pointing satisfaction
     >       ,DRMAX,RVMAX,DZMAX,TRNMAX,DSMIN      ! CTVMFA constants
     >       ,IJKERR                              ! error code results
     >       ,PSCALE                              ! set, CTVMFT first entrance

C  double precision stuff
      COMMON/CTVMFr/ VMAT                         ! Fit parameter covariance


