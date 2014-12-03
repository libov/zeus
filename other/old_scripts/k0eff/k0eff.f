      program k0eff
*****************************************************************
*     O. Behnke
*     06/2004
*     Purpose: Determine track-eff. vs pt
*     with using method from Wolfram Erdmanns
*     phd thesis page 37 ff
*
*     Input: read in from .txt file
*     1. Measured K0-yields vs pt and theta of K0
*     2. Measured K0-yields vs pt of decay pion with smaller pt
*
*     Output:
*     Track eff. vs pt of decay pion with smaller pt
*     written to .txt file
*****************************************************************

      IMPLICIT NONE

      REAL THTEST1, THTEST2
C
C---  Counters
C
      INTEGER I,IBIN,II,J,K,M,NS
      INTEGER I1,I2 
C
C---  auxiliary stuff
C
      INTEGER IAUX
      INTEGER NK0
C
C---  Iterations of procedure
C
      INTEGER MAXIT
      PARAMETER (MAXIT=8)
      INTEGER ITER
C
C---  Arrays for 'expected' numbers of K0 and efficiency vs pt
C     of 'slow pion'
C
      INTEGER MAXBIN
      PARAMETER(MAXBIN=80)
      REAL NEXP(MAXBIN), NEXP_RAW(MAXBIN), EFF0(MAXBIN), EFF(MAXBIN)
      REAL EFFSUM, EFFAVE
      INTEGER IACC
      INTEGER NB_HIG
      REAL EFFAV_HIG
C
C---  Input K0-data: vs transverse momentum of slow pion
C
      REAL PT_PIS(MAXBIN), NK0_PIS(MAXBIN)      
      INTEGER NPT_PIS
      PARAMETER (NPT_PIS=68)
      REAL PTMIN, PTMAX      
      PARAMETER (PTMIN=0.06, PTMAX=0.4)
      REAL DBIN
      PARAMETER(DBIN=(PTMAX-PTMIN)/NPT_PIS)

      INTEGER NPT_K0,NTH_K0
C      PARAMETER(NTH_K0=6,NPT_K0=8)
C      PARAMETER(NTH_K0=12,NPT_K0=16)   
C      PARAMETER(NTH_K0=24,NPT_K0=32)   
      PARAMETER(NTH_K0=48,NPT_K0=64)   
      REAL THMINK0, THMAXK0
      PARAMETER(THMINK0=30.,THMAXK0=150.)
      REAL PTMINK0, PTMAXK0
      PARAMETER(PTMINK0=0.4,PTMAXK0=2.)
      REAL DTHBIN, DPTBIN
      PARAMETER(DTHBIN=(THMAXK0-THMINK0)/NTH_K0)
      PARAMETER(DPTBIN=(PTMAXK0-PTMINK0)/NPT_K0)
C
C---  Input K0-data: vs pt and theta of K0
C
      INTEGER ITH_K0(MAXBIN,MAXBIN)
      REAL PT_K0(MAXBIN,MAXBIN), TH_K0(MAXBIN,MAXBIN)
      REAL NK0_K0(MAXBIN,MAXBIN)
      REAL NK0_RAW
C
C---  Isotropic K0-decays --> 2 degrees of freedom
C     to integrate over: PHI_S = angle between K0-z and pipi decay plane
C     COSTH_DE = costhetastar decay angle 
C
      REAL PHI_S 
      REAL COSPHI_S, SINPHI_S
      REAL COSTH_DE, SINTH_DE
C     Number of bins for COSTH_DE and PHI_S, can be varied here!
      INTEGER NCT,NAZ  
      PARAMETER (NCT=217,NAZ=231)    
C      PARAMETER (NCT=5,NAZ=5)    
C
C---  K0-kinematics 
C
      REAL RM_K0
      PARAMETER(RM_K0 = 0.49767)
      REAL P_K0, E_K0
      REAL GAMMA_K0, BETA_K0
      REAL COSTH_K0, SINTH_K0
C
C---  K0 -> pipi kinematics
C
      REAL RM_PI
      PARAMETER(RM_PI = 0.13957)
      REAL P_DE, E_DE     
      REAL PL_PI_1, PT_PI_1, PL_PI_2, PT_PI_2
      REAL PTLAB_PI_1, PTLAB_PI_2 
      REAL PZ_PI_1, PZ_PI_2
C
C--   Renormalise data or not
C
      LOGICAL LREN
      PARAMETER (LREN=.TRUE.)
C
C---  Output data file names
C
      CHARACTER*11 TAG
      CHARACTER*12 TNAME
      CHARACTER*50 TINPPS, TINPK0
      CHARACTER*22 TOUT, TOUT1, TOUT2
      LOGICAL LMC
C
C---  Debug flag
C
      LOGICAL LDEB
      PARAMETER (LDEB=.FALSE.)
C      PARAMETER (LDEB=.TRUE.)
C
C
C---  Test the method: introduce artificial 
C     ineff.
      LOGICAL LART
      PARAMETER  (LART=.FALSE.)
      INTEGER NSUPP
      PARAMETER (NSUPP=8)  
      REAL RSUPP
      PARAMETER (RSUPP=1 .)

C---  Physical constants
C
      REAL PI
      PARAMETER(PI=3.1415927)
      REAL RTOD
      PARAMETER(RTOD=180./PI) 
C
C------------------------------------------------------------------------
C
C---  Calculate decay momenta and energy
C
       P_DE=SQRT(RM_K0*RM_K0/4. - RM_PI*RM_PI)
       E_DE=SQRT(RM_PI*RM_PI    + P_DE*P_DE)  
       PRINT*,'K0-pi pi decay momentum and energy'
       PRINT*,'P_DE, E_DE = ',P_DE, E_DE
C    
C---  Initialisations of arrays
C
      DO I=1,MAXBIN
         NK0_PIS(I) = 0.
         NEXP_RAW(I) = 0.
         NEXP(I) = 0.
         EFF(I) = 0.
         DO J=1,MAXBIN
           PT_K0(I,J) = 0.
           TH_K0(I,J) = 0.
           NK0_K0(I,J) = 0.
         ENDDO
      ENDDO
C
C---  Define file names:
C     Note: declaration of Tname has to be adjusted to proper character length!
C
      LMC=.FALSE.
      TAG = '__00_xxxxxx'
C      TAG = '__00_m20p90'
C      TAG = '__00_pg110x'
C      TAG = '__00_phi90r'
C     TAG = '__04_pospis'

      IF (LMC) then
         TINPPS =  'pi_mc'//tag//'.dat'   
         TINPK0 =  'k0_mc'//tag//'.dat'
         TOUT   =  'pts_mc'//tag//'.txt '
         TOUT1  =  'exp_mc'//tag//'.txt '
         TOUT2  =  'eff_mc'//tag//'.txt '
      ELSE
         TINPPS =  'pi_da'//tag//'.dat'   
         TINPK0 =  'k0_da'//tag//'.dat'
         TOUT   =  'pts_da'//tag//'.txt '
         TOUT1  =  'exp_da'//tag//'.txt '
         TOUT2  =  'eff_da'//tag//'.txt '
      ENDIF

      PRINT*,'Tout = ',TOUT
      PRINT*,'Tout1 = ',TOUT1
      PRINT*,'Tout2 = ',TOUT2
C
C---  Read in K0-data vs pt(pi)
C
        OPEN (UNIT=35,FILE=TINPPS,
     +      STATUS='OLD', ACCESS='SEQUENTIAL', FORM='FORMATTED')

C
C---  Data vs pt of slow pion
C
      NS = 0
      DO I=1,NPT_PIS
C
C---     Calculate pt(pis) bin
C
         PT_PIS(I) = PTMIN+FLOAT(I)*DBIN-0.5*DBIN
         READ (35,*) IAUX, IAUX, IAUX, IAUX,  NK0
C         READ (35,1010) IAUX, IAUX, IAUX, IAUX,  NK0
         NK0_PIS(I) = FLOAT(NK0)
         NS = NS + NK0_PIS(I) 
C
C---     Initialise efficiency array
C
         EFF0(I)=1.
C
C---     Debug statements
C
Cob         IF (LDEB) THEN
            PRINT*,'I,PT_PIS(I),NK0_PIS(I) = ',
     +           I,PT_PIS(I),NK0_PIS(I)
Cob         ENDIF

      ENDDO
C
C---  How many K0-decays have been collected?
C
      PRINT*,'NSUM(PIS) = ',NS
      CLOSE (UNIT=35, STATUS='KEEP')      
C
C---  Check input sum
C
      IF (NS.EQ.0) THEN
         PRINT*,'Error: Zero number of input K0'
         STOP
      ENDIF
 
Cob 1010 FORMAT(I4, I5, I5, I5, I7)
Cob for Andreas data format 
Cob 1010 FORMAT(I4, I5, I5, I5, I5)
Cob old format 1010 FORMAT(I2, I5, I5, I5, I5)

C
C---  Artificial inefficiency at low pt - if wanted
C
Cob      IF (LART) THEN
Cob         DO I=1,NSUPP
Cob            NK0_PIS(I)=NK0_PIS(I)/RSUPP
Cob         ENDDO
Cob      ENDIF
C
C---  Renormalise data
C 
C      IF (LREN) THEN
C         DO I=1,NPT_PIS
C            NK0_PIS(I) = NK0_PIS(I)/NS
C         ENDDO
C      ENDIF
C
C---  Read in K0-data vs pt(K0) and the(K0)
C
      OPEN (UNIT=36,FILE=TINPK0,
     +      STATUS='OLD', ACCESS='SEQUENTIAL', FORM='FORMATTED')
      NS = 0
      DO I=1,NTH_K0
         DO J=1,NPT_K0
C
C---        Binning 
C
            TH_K0(I,J) = THMINK0 + (I-0.5)*DTHBIN
            TH_K0(I,J) = TH_K0(I,J)/RTOD             
            PT_K0(I,J) = PTMINK0 + (J-0.5)*DPTBIN
C
C---        READ in values
C
C            READ (36,1011) IAUX, IAUX, IAUX, IAUX, IAUX, NK0
            READ (36,*) IAUX, IAUX, IAUX, IAUX, IAUX, NK0
            NK0_K0(I,J) = FLOAT(NK0)
            NS = NS + NK0_K0(I,J)            
C
C---        Check if values are ok
C 
            IF (SIN(TH_K0(I,J)).EQ.0.) THEN
               PRINT*,'Error: Unphysical theta'
               STOP
            ENDIF
C
C---        Debug printout
C
Cob           IF (LDEB) THEN
               PRINT*,'I,J,PT_K0(I,J), TH_K0(I,J), NK0_K0(I,J) = ',
     +         I,J,PT_K0(I,J),TH_K0(I,J),NK0_K0(I,J) 

Cob            ENDIF 
        ENDDO
      ENDDO

Cob 1011  FORMAT(I4, I5, I5, I5, I5, I7)
Cob for Andreas data format 
 1011 FORMAT(I4, I5, I5, I5, I5, I5)
C 1011 FORMAT(I2, I3, I5, I4, I4, I5)
C
C---  Print out statistics:
C
      PRINT*,'K0 NS = ',NS
      CLOSE (UNIT=36, STATUS='KEEP')
C
C---  Check input sum
C
      IF (NS.EQ.0) THEN
         PRINT*,'Error: Zero number of input K0'
         STOP
      ENDIF
C
C---  Entry point for iterations: stop after maxit
C
      IF (LART) THEN
         ITER=-1
      ELSE
         ITER=0
      ENDIF

 100  CONTINUE
      ITER = ITER+1
      IF (ITER.GT.MAXIT) GOTO 700
      PRINT*,'ITER = ',ITER

C---  Initialisations per iteration
C
      DO I=1,MAXBIN
         NEXP(I) = 0.
         EFF(I) = 0.
      ENDDO
C
C---  Loop over K0-theta bins0
C
      DO I=1,NTH_K0 
C
C---  Loop over K0-pt bins
C
         DO J=1,NPT_K0
C           If input data are empty jump to next bin          
            NK0_RAW = NK0_K0(I,J)  
            IF (NK0_RAW.EQ.0) GOTO 600
C
C---        Initialise number ofbins inside acceptance
C
            IACC=0
C
C---        Initialise the expected K0 raw yields from bin I,J
C           
            DO II=1,NPT_PIS
               NEXP_RAW(II)=0.
            ENDDO
C
C---        Initialise (average) eff. for bin I,J 
C           using information from last iteration
C
            EFFSUM = 0.
            EFFAVE = 0.
C
C---        Calculate K0-kinematics
C
            COSTH_K0 = COS(TH_K0(I,J))
            SINTH_K0 = SIN(TH_K0(I,J))
            P_K0 = PT_K0(I,J)/SINTH_K0 
            E_K0 = SQRT(P_K0*P_K0 + RM_K0*RM_K0)
            GAMMA_K0 = E_K0/RM_K0
            BETA_K0  = P_K0/E_K0
C
C---        Debug printout statements
C
            IF (LDEB) THEN
               PRINT*,
     +         'I,J, P_K0, E_K0, GAMMA_K0, BETA_K0,COSTH_K0,SINTH_K0=',
     +          I,J,P_K0,E_K0,GAMMA_K0,BETA_K0,COSTH_K0,SINTH_K0
            ENDIF
C
C---        Here begins loops over isotropic decay and production angles
C    
C---        Loop over K0-decay angle costhetastar
C  
            DO K=1,NCT     
               COSTH_DE = -1. + 2.*(K-0.5)/NCT 
               SINTH_DE = SQRT(1.-COSTH_DE*COSTH_DE)     
C              Calculate longitudinal and transverse momenta
C              of decay pions w.r.t K0-flight axis in lab
C              First Pion:
               PL_PI_1 =  GAMMA_K0 * P_DE * COSTH_DE + E_DE *
     +                    GAMMA_K0 * BETA_K0  
               PT_PI_1 =  P_DE * SINTH_DE
C              Second Pion:
C              Watch the sign flip for first term due to back
C              to back emission of the pions in K0-rest-frame 
               PL_PI_2 = -GAMMA_K0 * P_DE * COSTH_DE + E_DE *
     +                    GAMMA_K0 * BETA_K0  
               PT_PI_2 = -P_DE * SINTH_DE
C
C---           Debug printout statements
C
               IF (LDEB) THEN
                  PRINT*,
     +           'I,J,K, COSTH_DE, PL_PI_1, PT_PI_1, PL_PI_2, PT_PI_2=',
     +            I,J,K,COSTH_DE,PL_PI_1,PT_PI_1,PL_PI_2,PT_PI_2
               ENDIF    
C
C---           Loop over angle between K0-z and pi pi decay plane
C
               DO 580, M=1,NAZ
                  PHI_S = PI*(M-0.5)/NAZ            
Cob
Cob take out region in phis, if it has been done in the data selection cuts
Cob                  IF ((PHI_S*RTOD).LT.20.
Cob     +                 OR.(PHI_S*RTOD).GT.160.) GOTO 580 
Cob
                  COSPHI_S = COS(PHI_S)
                  SINPHI_S = SIN(PHI_S)
C
C---              Transverse momentum and pz of first pion in lab
C
                  PTLAB_PI_1 = SQRT(
     +            (PL_PI_1 * SINTH_K0 + PT_PI_1 * COSPHI_S*COSTH_K0)**2
     +            +  (PT_PI_1 * SINPHI_S)**2 ) 
                  PZ_PI_1 = PL_PI_1*COSTH_K0 - PT_PI_1*
     +            COSPHI_S*SINTH_K0
C
C---              Transverse momentum and pz of second pion in lab
C
                  PTLAB_PI_2 = SQRT(
     +            (PL_PI_2 * SINTH_K0 + PT_PI_2 * COSPHI_S*COSTH_K0)**2
     +            +  (PT_PI_2 * SINPHI_S)**2 ) 
                  PZ_PI_2 = PL_PI_2*COSTH_K0 - PT_PI_2*
     +            COSPHI_S*SINTH_K0
C
C---              Debug printout statements
C
                  IF (LDEB) THEN
                     PRINT*,
     +              'I,J,K,M,PHI_S,PTLAB_PI_1,PTLAB_PI_2 = ',
     +               I,J,K,M,PHI_S,PTLAB_PI_1,PTLAB_PI_2
                  ENDIF    
C
C---              Require first pion to have pt of more than 400 MeV and
C                 second to have pt of less than 400 MeV. 
C                 This are the conditions the input data have been
C                 prepared with. 
                  IBIN=0
Cob                  THTEST1=ATAN2(PTLAB_PI_1,PZ_PI_1)*RTOD
Cob                  THTEST2=ATAN2(PTLAB_PI_2,PZ_PI_2)*RTOD
                  IF (PTLAB_PI_1.GT.0.4.AND.PTLAB_PI_2.LT.0.4
     +               .AND.PTLAB_PI_2.GT.0.1) THEN 
Cob H1 cut     +               .AND.PTLAB_PI_2.GT.0.06) THEN 

Cob
Cob
Cob     +               .AND.THTEST1.GT.5.AND.THTEST1.LT.175.
Cob     +               .AND.THTEST2.GT.5.AND.THTEST2.LT.175.) THEN
Cob
Cob
Cob THEN 
Cob
Cob---            Test, if pis are in angular acceptance!
Cob                     PRINT*,'I,J,K,M = ',I,J,K,M
Cob                     PRINT*,'PT1, PT2 = ',PTLAB_PI_1, PTLAB_PI_2  
Cob                      THTEST1=ATAN2(PTLAB_PI_1,PZ_PI_1)*RTOD
Cob                      THTEST2=ATAN2(PTLAB_PI_2,PZ_PI_2)*RTOD
Cob                      IF (THTEST1.LT.20.OR.THTEST2.LT.20) THEN
Cob                         PRINT*,'THTEST1,THTEST2 = ',THTEST1,THTEST2
Cob                      ENDIF
Cob                     PRINT*,'TH1 = ',ATAN2(PTLAB_PI_1,PZ_PI_1)*RTOD
Cob                     PRINT*,'TH2 = ',ATAN2(PTLAB_PI_2,PZ_PI_2)*RTOD

                     DO II=1,NPT_PIS
Cob                        PRINT*,'II,PTLAB_PI_2,PT_PIS =',
Cob     +                  II, PTLAB_PI_2,PT_PIS(II) 
C
C---                    Determine IBIN for pt of slow pion
C
                        IF (PTLAB_PI_2.LT.(PT_PIS(II)+0.5*DBIN)) THEN
                           IBIN=II
Cob                           PRINT*,'PTLAB_PI_2, IBIN = ',PTLAB_PI_2,IBIN
                           GOTO 500
                        ENDIF
                     ENDDO
 500                 CONTINUE
C
C
C---                Sum the number of decay angle bins that contribute to IBIN
C                   Sum the number of decay angle bins that contribute to
C                   any IBIN and matter for
C 
                     IF (IBIN.NE.0) THEN 
C                       Sum number of decay angle bins contributing to IBIN
                        NEXP_RAW(IBIN) = NEXP_RAW(IBIN) + 1.  
C                       Sum number of decay angle bins in acceptance region
                        IACC=IACC+1
C                       Sum efficiency for decay angle bins in acc. region
                        EFFSUM = EFFSUM + EFF0(IBIN)
                     ENDIF   
C
C---                 Debug statements
C
                     IF (LDEB) THEN
                        PRINT*,'IBIN,NEXP_RAW(IBIN) = ',
     +                  IBIN,NEXP_RAW(IBIN)
                     ENDIF
                  ENDIF

 580           CONTINUE
            ENDDO
C
C---        Calculate average eff. in acceptance region
C           
            IF (IACC.EQ.0.OR.EFFSUM.EQ.0.) GOTO 600
            EFFAVE = EFFSUM/IACC
C
C---        For the case of artificial ineff.
C           weight the K0-yields down
Cob            IF (ITER.EQ.0) THEN
Cob               NK0_K0(I,J) = NK0_K0(I,J)*EFFAVE
Cob            ENDIF                  
C
Cob            PRINT*,'I,J, EFFAVE = ',I,J,EFFAVE
Cob            PRINT*,'EFFAVE = ',EFFAVE
Cob            PRINT*,'NEXP_RAW = ',NEXP_RAW
Cob            IAUX=0


C
C---        Renormalise the expected yields contributing to 
C           bin of slow pion pt (This includes the correction
C           by the average efficiency in the acceptance region)
C
            DO II=1,NPT_PIS
                NEXP(II) = NEXP(II) + NK0_RAW/EFFSUM * NEXP_RAW(II)
            ENDDO     


 600        CONTINUE
         ENDDO
      ENDDO

      IF (ITER.EQ.0) GOTO 100
C
C---  Debug print statement
C
C      IF (LDEB) THEN
C         PRINT*,'NK0_PIS, NEXP = ',NK0_PIS,NEXP
C      ENDIF
C
C---  Renormalise expected Spectra
C
      IF (LREN) THEN

C     Shape normalised spectrum
C         NS = 0
C         DO I=1,NPT_PIS
C            NS = NS + NEXP(I)
C         ENDDO
C         IF (NS.EQ.0) THEN
C            PRINT*,'Error: Zero number of exp. K0'
C            STOP
C         ENDIF

C
C---   Normalise to last bin of data vs pt(pis)
C      --> to get there eff. = 1
C
         IF (NEXP(NPT_PIS).LE.0.) THEN
            PRINT*,'nexp(npt_pis) unphysical value bail out'
            RETURN
         ENDIF
C
C---     New (aug 08) normalise to last 5 bins
C
         nb_hig = 4
         I1  = NPT_PIS - nb_hig
         I2  = NPT_PIS
         EFFAV_hig = 0.
         DO I= I1,I2
            IF (NEXP(I).gt.0) then
              EFFAV_hig = EFFAV_hig + NK0_PIS(I)/NEXP(I)
            ENDIF
         ENDDO
         EFFAV_hig = EFFAV_hig/(nb_hig+1)

         DO I=1,NPT_PIS
Cob            NEXP(I) = NEXP(I)/NS
            NEXP(I) = NEXP(I)*EFFAV_hig
         ENDDO
      ENDIF


C
C---  Eff. Ratio 
C
      DO I=1,NPT_PIS
         IF (NEXP(I).GT.0.) THEN
            EFF(I)= NK0_PIS(I)/NEXP(I)
            EFF0(I)=EFF(I)
         ENDIF
      ENDDO
C
C---  Print out efficiencies per iteration
C

      PRINT*,'ITER, EFF = ',ITER,EFF
C
C---  Write out results
C
      IF (ITER.EQ.1) THEN
         WRITE(TOUT(22:22),'(I1)') ITER
         OPEN (75, FILE='iter/'//TOUT,STATUS='UNKNOWN')  
         DO I=1,NPT_PIS
            WRITE(75,*) NK0_PIS(I)
         ENDDO
      ENDIF
      CLOSE (UNIT=75, STATUS='KEEP')
      WRITE(TOUT1(22:22),'(I1)') ITER 
      OPEN (76, FILE='iter/'//TOUT1,STATUS='UNKNOWN')  
      DO I=1,NPT_PIS
         WRITE(76,*) NEXP(I)
      ENDDO
      CLOSE (UNIT=76, STATUS='KEEP')
      WRITE(TOUT2(22:22),'(I1)') ITER 
      OPEN (77, FILE='iter/'//TOUT2,STATUS='UNKNOWN')      
      DO I=1,NPT_PIS
         WRITE(77,*) EFF(I)
      ENDDO
      CLOSE (UNIT=77, STATUS='KEEP')

      GOTO 100
 700  CONTINUE


      STOP
      END

