      FUNCTION FAQG0(X,Y,M2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DP,DM)
C
C THIS IS THE EH*EL PIECE OF F_AQ_G (I.E. TERM 2) IN 3 CASES
C 1) SOFT LIMIT
C 2) COLLINEAR LIMIT
C 3) HARD
C
C LIMITS CHECK UNDER THETA2 INTEGRATION: 12/5/94
C LIMITS CHECK W/O   THETA2 INTEGRATION: 3/2/95
C
C IT IS TP*M^AQ_G(3) OF THE PAPER
C THERE IS AN OVERALL FACTOR OF G^4 EL EH N CF UNDERSTOND
C
      IMPLICIT DOUBLE PRECISION (A-Z)
      PARAMETER (DELTAS=1.0D-6)
      PARAMETER (DELTAC=1.0D-7)

      ONEMX = 1.D0 - X
      ONEPY = 1.D0 + Y

      IF ( ONEMX.LT.DELTAS ) THEN
        FAQG0 = 0.D0
      ELSE IF ( ONEPY.LT.DELTAC ) THEN
        FAQG0 = 0.D0
      ELSE
        M4 = M2*M2
        M6 = M2*M4
        M8 = M2*M6
        Q4 = Q2*Q2
        Q6 = Q2*Q4
        S52 = S5*S5
        S53 = S5*S52
        S54 = S5*S53
        S5M1 = 1.D0/S5
        S5M2 = S5M1*S5M1
        S42 = S4*S4
        S4M1 = 1.D0/S4
        S4M2 = S4M1*S4M1
        S32 = S3*S3
        S3M1 = 1.D0/S3
        S3M2 = S3M1*S3M1
        S2 = S*S
        SM1 = 1.D0/S
        SPM1 = 1.D0/SP
        SPM2 = SPM1*SPM1
        U62 = U6*U6
        U63 = U6*U62
        U6M1 = 1.D0/U6
        U6M2 = U6M1*U6M1
        U7M1 = 1.D0/U7
        U7M2 = U7M1*U7M1
        TP2 = TP*TP
        TP3 = TP*TP2
        TP4 = TP*TP3
        TPM1 = 1.D0/TP
        UP2 = UP*UP
        UP3 = UP*UP2
        UPM1 = 1.D0/UP
        UPM2 = UPM1*UPM1
        T12 = T1*T1
        T13 = T1*T12
        T1M1 = 1.D0/T1
        T1M2 = T1M1*T1M1
        U1M1 = 1.D0/U1
        U1M2 = U1M1*U1M1
        U1P = U1+Q2

        TERM2 =
     &    + M2*T1*U1M1*S5M1*UP*TPM1 * (  - 16*SM1 )
     &    + M2*T1*U1M1*S5M1*TPM1*Q2 * (  - 16*SM1 )
     &    + M2*T1*U1M1*S5M1 * (  - 32*SM1 )
     &    + M2*T1*S5M1*UPM1*TPM1*U7M1*Q2 * ( 16 )
     &    + M2*T1*S5M1*TPM1*U7M1 * ( 16 )
     &    + M2*U1M1*U1P*S5M1*UPM1 * ( 16 )
     &    + M2*U1M1*U1P*S5M1 * (  - 16*SM1 )
     &    + M2*U1M1*S3*S5M1*UPM1*TPM1 * ( 16*SP )
     &    + M2*U1M1*S3*S5M1*UPM1 * ( 32 )
     &    + M2*U1M1*S4*S5M1*TPM1 * ( 16*SM1*SP )
     &    + M2*U1M1*S5M1*UPM1*TPM1*U6*Q2 * (  - 16 )
     &    + M2*U1M1*S5M1*UPM1*TPM1*Q2 * ( 16*SP )
     &    + M2*U1M1*S5M1*UPM1*Q2 * ( 16 )
     &    + M2*U1M1*S5M1*UP*TPM1 * (  - 16*SM1*SP )
     &    + M2*U1M1*S5M1*TPM1*U6 * (  - 16 )
     &    + M2*U1M1*S5M1*TPM1*Q2 * (  - 16*SM1*SP )
     &    + M2*U1M1*S5M1*TPM1 * ( 16*SP )
     &    + M2*U1M1*S5M1 * ( 16 - 16*SM1*SP )
     &    + M2*S3*S5M1*TPM1*U7M1 * (  - 16*SM1*SP )
     &    + M2*S4*S5M1*UPM1*TPM1*U7M1 * (  - 16*SP )
     &    + M2*S4*S5M1*UPM1*U7M1 * (  - 32 )
     &    + M2*S5M1*UPM1*TPM1*U7M1*Q2 * (  - 16*SP )
     &    + M2*S5M1*UPM1*U7M1*Q2 * (  - 32 )
     &    + M2*S5M1*UPM1 * (  - 16 )
     &    + M2*S5M1*UP*TPM1*U6*U7M1 * ( 16*SM1 )
     &    + M2*S5M1*UP*TPM1*U7M1 * ( 16*SM1*SP )
     &    + M2*S5M1*TPM1*U6*U7M1*Q2 * ( 16*SM1 )
     &    + M2*S5M1*TPM1*U7M1*Q2 * ( 16*SM1*SP )
     &    + M2*S5M1*TPM1*U7M1 * (  - 16*SP )
     &    + M2*S5M1*U6*U7M1 * ( 32*SM1 )
     &    + M2*S5M1*U7M1*Q2 * ( 16*SM1 )
     &    + M2*S5M1*U7M1 * (  - 16 + 16*SM1*SP )
     &    + M2*S5M1 * ( 16*SM1 )
     &    + T1*U1M1*U1P*S4*S5M1*UPM1*TPM1 * ( 8 )
     &    + T1*U1M1*U1P*S4*S5M1*TPM1 * (  - 16*SM1 )
     &    + T1*U1M1*S3*S4*S5M1*UPM1*TPM1 * ( 16 )
     &    + T1*U1M1*S3*S5M1*UPM1*TPM1*U7 * ( 8 )
     &    + T1*U1M1*S3*S5M1*UPM1*TPM1*Q2 * ( 8 )
     &    + T1*U1M1*S3*S5M1*TPM1*U6 * (  - 16*SM1 )
     &    + T1*U1M1*S3*S5M1*TPM1*U7 * (  - 8*SM1 )
     &    + T1*U1M1*S3*S5M1*TPM1*Q2 * (  - 8*SM1 )
     &    + T1*U1M1*S4*S5M1*TPM1*Q2 * ( 8*SM1 )
     &    + T1*U1M1*S4*S5M1*TPM1 * ( 8 - 16*SM1*SP )
     &    + T1*U1M1*S5M1*UP*TPM1*U6 * (  - 8*SM1 )
     &    + T1*U1M1*S5M1*TPM1*U6*Q2 * (  - 8*SM1 )
     &    + T1*U1M1*UPM1*TPM1*Q2 * (  - 8 )
     &    + T1*U1M1*TPM1 * (  - 8 )
     &    + T1*S4*S5M1*UPM1*TPM1*U7M1*Q2 * (  - 24 )
     &    + T1*S4*S5M1*UPM1*TPM1 * (  - 16 )
     &    + T1*S4*S5M1*TPM1*U6*U7M1 * ( 16*SM1 )
     &    + T1*S4*S5M1*TPM1*U7M1 * (  - 16 + 8*SM1*SP )
     &    + T1*S4*S5M1*TPM1 * ( 8*SM1 )
     &    + T1*S42*S5M1*UPM1*TPM1*U7M1 * (  - 16 )
     &    + T1*S5M1*UPM1*TPM1*U7M1*Q4 * (  - 16 )
     &    + T1*S5M1*UPM1*TPM1*Q2 * (  - 16 )
     &    + T1*S5M1*UP*TPM1*U6*U7M1 * ( 8*SM1 )
     &    + T1*S5M1*TPM1*U6*U7M1*Q2 * ( 8*SM1 )
     &    + T1*S5M1*TPM1*U7M1*Q2 * (  - 16 )
     &    + T1*S5M1*TPM1 * (  - 16 )
     &    + T1*S5M1*U7M1*Q2 * (  - 8*SM1 )
     &    + T1*S5M1 * (  - 8*SM1 )
     &    + T12*U1M1*S4*S5M1*TPM1 * (  - 16*SM1 )
     &    + U1M1*U1P*S3*S5M1*UPM1*TPM1*U6 * ( 16 )
     &    + U1M1*U1P*S3*S5M1*TPM1*U6 * (  - 8*SM1 )
     &    + U1M1*U1P*S4*S5M1*UPM1 * (  - 8 )
     &    + U1M1*U1P*S4*S5M1*TPM1 * (  - 16*SM1*SP )
     &    + U1M1*U1P*S5M1*UPM1*TPM1*U6*Q2 * ( 16 )
     &    + U1M1*U1P*S5M1*TPM1*U6 * ( 16 )
     &    + U1M1*U1P*S5M1*U6 * ( 8*SM1 )
     &    + U1M1*S3*S4*S5M1*UPM1*TPM1 * ( 8*SP )
     &    + U1M1*S3*S5M1*UPM1*TPM1*U6*Q2 * ( 8 )
     &    + U1M1*S3*S5M1*TPM1*U6*Q2 * ( 8*SM1 )
     &    + U1M1*S3*S5M1*TPM1*U6 * ( 16 - 8*SM1*SP )
     &    + U1M1*S3*TPM1 * ( 8*SM1*SP )
     &    + U1M1*S32*S5M1*UPM1*TPM1*U6 * ( 16 )
     &    + U1M1*UPM1*Q2 * ( 8 )
     &    + U1M1*Q2 * (  - 8*SM1 )
     &    + U1P*S4*S5M1*UPM1*TPM1*U6*U7M1 * (  - 8 )
     &    + U1P*S4*S5M1*TPM1*U6*U7M1 * ( 8*SM1 )
     &    + S3*S4*S5M1*UPM1*TPM1*U6*U7M1 * (  - 16 )
     &    + S3*S4*S5M1*UPM1*TPM1*U7M1 * (  - 8*SP )
     &    + S3*S5M1*UPM1*TPM1*U6*U7M1*Q2 * (  - 8 )
     &    + S3*S5M1*UPM1*TPM1*U6 * (  - 8 )
     &    + S3*S5M1*UPM1*U7M1*Q2 * ( 8 )
     &    + S3*S5M1*UPM1 * ( 8 )
     &    + S3*S5M1*TPM1*U6*U7M1*Q2 * ( 8*SM1 )
     &    + S3*S5M1*TPM1*U6*U7M1 * (  - 8 + 16*SM1*SP )
     &    + S3*S5M1*TPM1*U6 * ( 16*SM1 )
     &    + S3*S5M1*TPM1*U62*U7M1 * ( 16*SM1 )
     &    + S3*S5M1*TPM1*U7M1*Q2 * ( 16*SM1*SP )
     &    + S3*S5M1*TPM1 * ( 16*SM1*SP )
     &    + S4*TPM1*U7M1 * (  - 8*SM1*SP )
     &    + UPM1*TPM1*U6*U7M1*Q2 * ( 8 )
     &    + UPM1*U7M1*Q2 * (  - 8 )
     &    + TPM1*U6*U7M1 * ( 8 )
     &    + U7M1*Q2 * ( 8*SM1 )

        FAQG0 = TP*TERM2

      END IF

      RETURN
      END
      FUNCTION FAQGC
     &         (X,Y,M2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DP,DM)
C
C THIS IS THE EH*EH PIECE OF F_AQ_G (I.E. TERM 1) IN 3 CASES
C 1) SOFT LIMIT
C 2) COLLINEAR LIMIT
C 3) HARD
C
C LIMITS CHECK UNDER THETA2 INTEGRATION: 12/5/94
C LIMITS CHECK W/O   THETA2 INTEGRATION: 3/2/95, 3/29/95
C
C IT IS TP*M^AQ_G(3) OF THE PAPER
C THERE IS AN OVERALL FACTOR OF G^4 EH^2 N CF UNDERSTOOD
C
      IMPLICIT DOUBLE PRECISION (A-Z)

      COMMON/AZDEP/CTH22,STH12

      PARAMETER (DELTAS=1.0D-5)
      PARAMETER (DELTAC=1.0D-7)

      ONEMX = 1.D0 - X
      ONEPY = 1.D0 + Y

      IF ( ONEMX.LT.DELTAS ) THEN
C         WRITE(*,*) 'IN SOFT LIMIT'
        FAQGC = -8.D0*BGQED(T1,SP,M2,Q2)
      ELSE IF ( ONEPY.LT.DELTAC ) THEN
C         WRITE(*,*) 'IN COLLINEAR LIMIT'
        BETA52 = 1.D0-4.D0*M2/S5
        XSP2 = X*X*SP*SP
        FH = XSP2/X/T1/U1*(M2-ONEMX*S5*BETA52*CTH22*STH12/X/X)-S5
        FAQGC = 16.D0*(2.D0*M2-Q2)*FH/X/T1/U1
     &        - 8.D0*(X*X-2.D0*X+2.D0)*(XSP2/X/T1/U1-2.D0)/X/X
      ELSE
C         WRITE(*,*) 'IN HARD'
        M4 = M2*M2
        Q4 = Q2*Q2
        S52 = S5*S5
        S53 = S5*S52
        S54 = S5*S53
        S5M1 = 1.D0/S5
        S5M2 = S5M1*S5M1
        S42 = S4*S4
        S4M1 = 1.D0/S4
        S4M2 = S4M1*S4M1
        S32 = S3*S3
        S3M1 = 1.D0/S3
        S3M2 = S3M1*S3M1
        S2 = S*S
        SM1 = 1.D0/S
        SP2 = SP*SP
        SPM1 = 1.D0/SP
        SPM2 = SPM1*SPM1
        U62 = U6*U6
        U63 = U6*U62
        U6M1 = 1.D0/U6
        U6M2 = U6M1*U6M1
        U7M1 = 1.D0/U7
        U7M2 = U7M1*U7M1
        TP2 = TP*TP
        TP3 = TP*TP2
        TP4 = TP*TP3
        TPM1 = 1.D0/TP
        TPM2 = TPM1*TPM1
        UP2 = UP*UP
        UP3 = UP*UP2
        UPM1 = 1.D0/UP
        UPM2 = UPM1*UPM1
        T12 = T1*T1
        T13 = T1*T12
        T1M1 = 1.D0/T1
        T1M2 = T1M1*T1M1
        U1M1 = 1.D0/U1
        U1M2 = U1M1*U1M1
        U1P = U1+Q2

        TERM1 =
     &    + M2*T1*S4*TPM2*U7M2 * ( 16 )
     &    + M2*T1*S4*TPM2*U7M1 * ( 32*U1M1 )
     &    + M2*T1*S4*TPM2 * ( 16*U1M2 )
     &    + M2*T1*UP*TPM2*U7M2 * ( 16 )
     &    + M2*T1*UP*TPM2*U7M1 * ( 16*U1M1 )
     &    + M2*T1*TPM2*U7M2*Q2 * ( 16 )
     &    + M2*T1*TPM2*U7M1*Q2 * ( 16*U1M1 )
     &    + M2*S3*TPM2*U6*U7M2 * ( 16 )
     &    + M2*S3*TPM2*U6*U7M1 * ( 32*U1M1 )
     &    + M2*S3*TPM2*U6 * ( 16*U1M2 )
     &    + M2*S3*TPM2*U7M2 * ( 16*SP )
     &    + M2*S3*TPM2*U7M1 * ( 16*SP*U1M1 )
     &    + M2*S4*TPM2*U7M1 * ( 16*SP*U1M1 )
     &    + M2*S4*TPM2 * ( 16*SP*U1M2 )
     &    + M2*S5*TPM1*U7M1 * (  - 32*U1M1 )
     &    + M2*UP*TPM2*U6*U7M1 * ( 16*U1M1 )
     &    + M2*UP*TPM2*U6 * ( 16*U1M2 )
     &    + M2*UP*TPM2*U7M1 * ( 32*SP*U1M1 )
     &    + M2*TPM2*U6*U7M1*Q2 * ( 16*U1M1 )
     &    + M2*TPM2*U6*Q2 * ( 16*U1M2 )
     &    + M2*TPM2*U7M1*Q2 * ( 32*SP*U1M1 )
     &    + M2*TPM1*U7M2*Q2 * (  - 16 )
     &    + M2*TPM1*U7M1*Q2 * (  - 16*U1M1 )
     &    + M2*TPM1*U7M1 * ( 16 - 16*U1M1*U1P )
     &    + M2*TPM1*Q2 * (  - 32*U1M2 )
     &    + M2*TPM1 * ( 16*U1M2*U1P - 16*U1M1 )
     &    + M4*TPM1*U7M2 * ( 32 )
     &    + M4*TPM1*U7M1 * ( 64*U1M1 )
     &    + M4*TPM1 * ( 32*U1M2 )
     &    + T1*S3*TPM2*U7M1*Q2 * ( 16*U1M1 )
     &    + T1*S3*TPM2 * ( 16*U1M1 )
     &    + T1*S4*S5*TPM2*U7M1 * (  - 16*U1M1 )
     &    + T1*S4*TPM2*U7M2*Q2 * (  - 8 )
     &    + T1*S4*TPM2*U7M1*Q2 * (  - 8*U1M1 )
     &    + T1*S4*TPM2*U7M1 * (  - 8*U1M1*U1P )
     &    + T1*S4*TPM2*Q2 * (  - 8*U1M2 )
     &    + T1*S4*TPM2 * (  - 8*U1M1 )
     &    + T1*S5*UP*TPM2*U7M1 * (  - 8*U1M1 )
     &    + T1*S5*TPM2*U7M1*Q2 * (  - 8*U1M1 )
     &    + T1*UP*TPM2*U7M2*Q2 * (  - 8 )
     &    + T1*UP*TPM2*U7M1 * (  - 8 )
     &    + T1*TPM2*U7M2*Q4 * (  - 8 )
     &    + T1*TPM2*U7M1*Q2 * (  - 8 )
     &    + S3*S5*TPM2*U6*U7M1 * (  - 16*U1M1 )
     &    + S3*S5*TPM2*U7M1 * (  - 8*SP*U1M1 )
     &    + S3*TPM2*U6*U7M2*Q2 * (  - 8 )
     &    + S3*TPM2*U6*U7M1*Q2 * (  - 8*U1M1 )
     &    + S3*TPM2*U6*U7M1 * (  - 8*U1M1*U1P )
     &    + S3*TPM2*U6*Q2 * (  - 8*U1M2 )
     &    + S3*TPM2*U6 * (  - 8*U1M1 )
     &    + S3*TPM2*U7M2*Q2 * (  - 8*SP )
     &    + S3*TPM2*U7M1 * (  - 8*SP )
     &    + S4*S5*TPM2*U7M1 * (  - 8*SP*U1M1 )
     &    + S4*TPM2*U6*U7M1 * ( 16*U1M1*U1P )
     &    + S4*TPM2 * (  - 8*SP*U1M2*U1P )
     &    + S5*UP*TPM2*U6*U7M1 * (  - 8*U1M1 )
     &    + S5*TPM2*U6*U7M1*Q2 * (  - 8*U1M1 )
     &    + S5*TPM1*U7M1*Q2 * ( 16*U1M1 )
     &    + UP*TPM2*U6 * (  - 8*U1M2*U1P )
     &    + TPM2*U6*Q2 * (  - 8*U1M2*U1P )

        FAQGC = TP*TERM1

      END IF

      RETURN
      END
      FUNCTION FAQGD(X,Y,M2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DP,DM)
C
C THIS IS THE EL*EL PIECE OF F_AQ_G (I.E. TERM 3) IN 3 CASES
C 1) SOFT LIMIT
C 2) COLLINEAR LIMIT
C 3) HARD
C
C LIMITS CHECK UNDER THETA2 INTEGRATION: 12/5/94
C LIMITS CHECK W/O   THETA2 INTEGRATION: 3/2/95
C
C IT IS TP*M^AQ_G(3) OF THE PAPER
C THERE IS AN OVERALL FACTOR OF G^4 EL^2 N CF UNDERSTOOD
C
      IMPLICIT DOUBLE PRECISION (A-Z)
      PARAMETER (DELTAS=1.0D-6)
      PARAMETER (DELTAC=1.0D-7)

      ONEMX = 1.D0 - X
      ONEPY = 1.D0 + Y

      IF ( ONEMX.LT.DELTAS ) THEN
        FAQGD = 0.D0
      ELSE IF ( ONEPY.LT.DELTAC ) THEN
        FAQGD = 0.D0
      ELSE
        Q4 = Q2*Q2
        S52 = S5*S5
        S53 = S5*S52
        S54 = S5*S53
        S5M1 = 1.D0/S5
        S5M2 = S5M1*S5M1
        S42 = S4*S4
        S4M1 = 1.D0/S4
        S4M2 = S4M1*S4M1
        S32 = S3*S3
        S3M1 = 1.D0/S3
        S3M2 = S3M1*S3M1
        S2 = S*S
        SM1 = 1.D0/S
        SM2 = SM1*SM1
        SPM1 = 1.D0/SP
        SPM2 = SPM1*SPM1
        U62 = U6*U6
        U63 = U6*U62
        U6M1 = 1.D0/U6
        U6M2 = U6M1*U6M1
        U7M1 = 1.D0/U7
        U7M2 = U7M1*U7M1
        TP2 = TP*TP
        TP3 = TP*TP2
        TP4 = TP*TP3
        TPM1 = 1.D0/TP
        UP2 = UP*UP
        UP3 = UP*UP2
        UPM1 = 1.D0/UP
        UPM2 = UPM1*UPM1
        T12 = T1*T1
        T13 = T1*T12
        T1M1 = 1.D0/T1
        T1M2 = T1M1*T1M1
        U1M1 = 1.D0/U1
        U1M2 = U1M1*U1M1
        U1P = U1+Q2

        TERM3 =
     &    + M2*SM2*S5M2*UP * (  - 16*SP )
     &    + M2*SM2*S5M2*TP*Q2 * (  - 16 )
     &    + M2*SM2*S5M2*Q2 * (  - 16*SP )
     &    + M2*SM1*S5M2*UPM1*TP * (  - 32*SP )
     &    + M2*SM1*S5M2*UPM1*TP2 * (  - 32 )
     &    + M2*SM1*S5M2*TP * (  - 32 )
     &    + M2*S5M2*UPM2*TP*Q2 * (  - 16 )
     &    + M2*S5M2*UPM2*Q2 * (  - 16*SP )
     &    + M2*S5M2*UPM1 * (  - 16*SP )
     &    + SM2*T1*S4*S5M2*Q2 * (  - 8 )
     &    + SM2*U1P*S4*S5M2 * (  - 8*SP )
     &    + SM2*S3*S5M2*U6*Q2 * (  - 8 )
     &    + SM2*S3*S5M2*U7 * (  - 8*SP )
     &    + SM2*S3*S5M2*Q2 * (  - 8*SP )
     &    + SM1*T1*S4*S5M2*UPM1*TP * (  - 16 )
     &    + SM1*T1*S4*S5M2*UPM1*Q2 * (  - 8 )
     &    + SM1*T1*S4*S5M2*UPM1 * (  - 8*SP )
     &    + SM1*T1*S4*S5M2 * (  - 8 )
     &    + SM1*T1*S5M2*UPM1*TP*U7 * (  - 8 )
     &    + SM1*T1*S5M2*UPM1*TP*Q2 * (  - 8 )
     &    + SM1*T1*S5M2*UPM1*U6*Q2 * ( 16 )
     &    + SM1*T1*S5M2*U6 * ( 16 )
     &    + SM1*U1P*S4*S5M2*UPM1*TP * (  - 8 )
     &    + SM1*U1P*S5M2*UPM1*TP*U6 * (  - 8 )
     &    + SM1*S3*S4*S5M2*UPM1 * ( 16*SP )
     &    + SM1*S3*S5M2*UPM1*TP*U6 * (  - 16 )
     &    + SM1*S3*S5M2*UPM1*TP*U7 * (  - 8 )
     &    + SM1*S3*S5M2*UPM1*TP*Q2 * (  - 8 )
     &    + SM1*S3*S5M2*UPM1*U6*Q2 * (  - 8 )
     &    + SM1*S3*S5M2*UPM1*U6 * (  - 8*SP )
     &    + SM1*S3*S5M2*U6 * (  - 8 )
     &    + SM1*S5M1*UPM1*TP*Q2 * ( 16 )
     &    + T1*S4*S5M2*UPM2*Q2 * (  - 8 )
     &    + T1*S5M2*UPM2*U7*Q2 * (  - 8 )
     &    + T1*S5M2*UPM2*Q4 * (  - 8 )
     &    + T1*S5M2*UPM1*U7 * (  - 8 )
     &    + T1*S5M2*UPM1*Q2 * (  - 8 )
     &    + U1P*S5M2*UPM2*U6*Q2 * (  - 8 )
     &    + U1P*S5M2*UPM1*U6 * (  - 8 )
     &    + S3*S5M2*UPM2*U6*Q2 * (  - 8 )

        FAQGD = TP*TERM3

      END IF

      RETURN
      END
      FUNCTION FAQL0(X,Y,M2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DP,DM)
C
C THIS IS THE EH*EL PIECE OF F_AQ_L (I.E. TERM 2) IN 3 CASES
C 1) SOFT LIMIT
C 2) COLLINEAR LIMIT
C 3) HARD
C
C LIMITS CHECK UNDER THETA2 INTEGRATION: 12/5/94
C LIMITS CHECK W/O   THETA2 INTEGRATION: 2/15/95
C
C IT IS TP*M^AQ_L(3) OF THE PAPER
C THERE IS AN OVERALL FACTOR OF G^4 EL EH N CF UNDERSTOND
C
      IMPLICIT DOUBLE PRECISION (A-Z)
      PARAMETER (DELTAS=1.0D-6)
      PARAMETER (DELTAC=1.0D-7)

      ONEMX = 1.D0 - X
      ONEPY = 1.D0 + Y

      IF ( ONEMX.LT.DELTAS ) THEN
        FAQL0 = 0.D0
      ELSE IF ( ONEPY.LT.DELTAC ) THEN
        FAQL0 = 0.D0
      ELSE
        M4 = M2*M2
        M6 = M2*M4
        M8 = M2*M6
        Q4 = Q2*Q2
        Q6 = Q2*Q4
        S52 = S5*S5
        S53 = S5*S52
        S54 = S5*S53
        S5M1 = 1.D0/S5
        S5M2 = S5M1*S5M1
        S42 = S4*S4
        S4M1 = 1.D0/S4
        S4M2 = S4M1*S4M1
        S32 = S3*S3
        S3M1 = 1.D0/S3
        S3M2 = S3M1*S3M1
        S2 = S*S
        SM1 = 1.D0/S
        SPM1 = 1.D0/SP
        SPM2 = SPM1*SPM1
        U62 = U6*U6
        U63 = U6*U62
        U6M1 = 1.D0/U6
        U6M2 = U6M1*U6M1
        U7M1 = 1.D0/U7
        U7M2 = U7M1*U7M1
        TP2 = TP*TP
        TP3 = TP*TP2
        TP4 = TP*TP3
        TPM1 = 1.D0/TP
        UP2 = UP*UP
        UP3 = UP*UP2
        UPM1 = 1.D0/UP
        UPM2 = UPM1*UPM1
        T12 = T1*T1
        T13 = T1*T12
        T1M1 = 1.D0/T1
        T1M2 = T1M1*T1M1
        U1M1 = 1.D0/U1
        U1M2 = U1M1*U1M1
        U1P = U1+Q2

        TERM2 =
     &    + M2*T1*S5M1*UPM1*TP*Q2 * (  - 64*SPM2*U1M1 )
     &    + M2*T1*S5M1*UPM1*Q2 * (  - 64*SPM1*U1M1 )
     &    + M2*S5M1*UPM1*TP*U6*U7M1*Q2 * ( 64*SPM2 )
     &    + M2*S5M1*UPM1*TP*U7M1*Q2 * ( 32*SPM1 )
     &    + M2*S5M1*UPM1*TP*Q2 * (  - 32*SPM1*U1M1 )
     &    + M2*S5M1*UPM1*U6*U7M1*Q2 * ( 64*SPM1 )
     &    + M2*S5M1*UPM1*U7M1*Q2 * ( 32 )
     &    + M2*S5M1*UPM1*Q2 * (  - 32*U1M1 )
     &    + T1*S3*S5M1*UPM1*TPM1*U6*Q2 * (  - 16*SPM1*U1M1 )
     &    + T1*S3*S5M1*UPM1*U6*Q2 * (  - 32*SPM2*U1M1 )
     &    + T1*S4*S5M1*UPM1*TPM1*U6*U7M1*Q2 * ( 16*SPM1 )
     &    + T1*S4*S5M1*UPM1*TPM1*U7M1*Q2 * ( 16 )
     &    + T1*S4*S5M1*UPM1*TPM1*Q2 * (  - 16*U1M1 )
     &    + T1*S4*S5M1*UPM1*U6*U7M1*Q2 * ( 32*SPM2 )
     &    + T1*S4*S5M1*UPM1*U7M1*Q2 * ( 16*SPM1 )
     &    + T1*S4*S5M1*UPM1*Q2 * (  - 32*SPM1*U1M1 )
     &    + T1*S5M1*UPM1*TPM1*U6*U7M1*Q4 * (  - 32*SPM1 )
     &    + T1*S5M1*UPM1*TPM1*U6*Q4 * ( 32*SPM1*U1M1 )
     &    + T1*S5M1*UPM1*TPM1*U62*U7M1*Q4 * (  - 32*SPM2 )
     &    + T1*S5M1*UPM1*TP*U7M1*Q4 * (  - 16*SPM2 )
     &    + T1*S5M1*UPM1*TP*Q2 * (  - 16*SPM2 )
     &    + T1*S5M1*UPM1*U6*Q2 * (  - 16*SPM2*U1M1*U1P + 16*SPM2 )
     &    + T1*S5M1*UPM1*U6*Q4 * ( 16*SPM2*U1M1 )
     &    + T1*S5M1*UPM1*U7M1*Q4 * (  - 16*SPM1 )
     &    + T1*S5M1*UPM1*U7*Q2 * (  - 16*SPM1*U1M1 )
     &    + T1*S5M1*UPM1*Q2 * (  - 16*SPM1 )
     &    + T1*S5M1*UPM1*Q4 * (  - 16*SPM1*U1M1 )
     &    + T1*S5M1*TPM1*U6*U7M1*Q2 * (  - 32*SPM1 )
     &    + T1*S5M1*TPM1*U6*Q2 * ( 32*SPM1*U1M1 )
     &    + T1*S5M1*TPM1*U62*U7M1*Q2 * (  - 32*SPM2 )
     &    + T1*S5M1*U6*U7M1*Q2 * ( 16*SPM2 )
     &    + T1*S5M1*U6*Q2 * (  - 16*SPM2*U1M1 )
     &    + T12*S4*S5M1*UPM1*TPM1*Q2 * (  - 16*SPM1*U1M1 )
     &    + T12*S4*S5M1*UPM1*Q2 * (  - 32*SPM2*U1M1 )
     &    + T12*S5M1*UPM1*TPM1*U6*Q4 * ( 32*SPM2*U1M1 )
     &    + T12*S5M1*UPM1*U7*Q2 * (  - 16*SPM2*U1M1 )
     &    + T12*S5M1*UPM1*Q4 * (  - 16*SPM2*U1M1 )
     &    + T12*S5M1*TPM1*U6*Q2 * ( 32*SPM2*U1M1 )
     &    + S3*S5M1*UPM1*TPM1*U6*U7M1*Q2 * ( 16 )
     &    + S3*S5M1*UPM1*TPM1*U6*Q2 * (  - 16*U1M1 )
     &    + S3*S5M1*UPM1*TPM1*U62*U7M1*Q2 * ( 16*SPM1 )
     &    + S3*S5M1*UPM1*U6*U7M1*Q2 * ( 32*SPM1 )
     &    + S3*S5M1*UPM1*U6*Q2 * (  - 16*SPM1*U1M1 )
     &    + S3*S5M1*UPM1*U62*U7M1*Q2 * ( 32*SPM2 )
     &    + S5M1*UPM1*TP*U6*Q2 * ( 16*SPM2*U1M1*U1P )
     &    + S5M1*UPM1*U6*U7M1*Q2 * ( 16*SPM1*U1P )
     &    + S5M1*UPM1*U6*Q2 * ( 16*SPM1*U1M1*U1P )
     &    + S5M1*UPM1*U62*U7M1*Q2 * ( 16*SPM2*U1P )

        FAQL0 = TP*TERM2

      END IF

      RETURN
      END
      FUNCTION FAQLC
     &         (X,Y,M2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DP,DM)
C
C THIS IS THE EH*EH PIECE OF F_AQ_L (I.E. TERM 1) IN 3 CASES
C 1) SOFT LIMIT
C 2) COLLINEAR LIMIT
C 3) HARD
C
C LIMITS CHECK UNDER THETA2 INTEGRATION: 12/5/94
C LIMITS CHECK W/O   THETA2 INTEGRATION: 3/2/95, 3/29/95
C
C IT IS TP*M^AQ_L(3) OF THE PAPER
C THERE IS AN OVERALL FACTOR OF G^4 EH^2 N CF UNDERSTOOD
C
      IMPLICIT DOUBLE PRECISION (A-Z)

      COMMON/AZDEP/CTH22,STH12

      PARAMETER (DELTAS=1.0D-5)
      PARAMETER (DELTAC=1.0D-7)

      ONEMX = 1.D0 - X
      ONEPY = 1.D0 + Y

      IF ( ONEMX.LT.DELTAS ) THEN
C         WRITE(*,*) 'IN SOFT LIMIT'
        FAQLC = -8.D0*BLQED(T1,SP,M2,Q2)
      ELSE IF ( ONEPY.LT.DELTAC ) THEN
C         WRITE(*,*) 'IN COLLINEAR LIMIT'
        BETA52 = 1.D0-4.D0*M2/S5
        XSP2 = X*X*SP*SP
        FH = XSP2/X/T1/U1*(M2-ONEMX*S5*BETA52*CTH22*STH12/X/X)-S5
        FAQLC = 32.D0*Q2*FH/XSP2
      ELSE
C         WRITE(*,*) 'IN HARD'
        Q4 = Q2*Q2
        S52 = S5*S5
        S53 = S5*S52
        S54 = S5*S53
        S5M1 = 1.D0/S5
        S5M2 = S5M1*S5M1
        S42 = S4*S4
        S4M1 = 1.D0/S4
        S4M2 = S4M1*S4M1
        S32 = S3*S3
        S3M1 = 1.D0/S3
        S3M2 = S3M1*S3M1
        S2 = S*S
        SM1 = 1.D0/S
        SP2 = SP*SP
        SPM1 = 1.D0/SP
        SPM2 = SPM1*SPM1
        U62 = U6*U6
        U63 = U6*U62
        U6M1 = 1.D0/U6
        U6M2 = U6M1*U6M1
        U7M1 = 1.D0/U7
        U7M2 = U7M1*U7M1
        TP2 = TP*TP
        TP3 = TP*TP2
        TP4 = TP*TP3
        TPM1 = 1.D0/TP
        TPM2 = TPM1*TPM1
        UP2 = UP*UP
        UP3 = UP*UP2
        UPM1 = 1.D0/UP
        UPM2 = UPM1*UPM1
        T12 = T1*T1
        T13 = T1*T12
        T1M1 = 1.D0/T1
        T1M2 = T1M1*T1M1
        U1M1 = 1.D0/U1
        U1M2 = U1M1*U1M1
        U1P = U1+Q2


        TERM1 =
     &    + M2*T1*TPM1*U6*U7M1*Q2 * ( 64*SPM2*U1M1 )
     &    + M2*T1*TPM1*U7M1*Q2 * ( 32*SPM1*U1M1 )
     &    + M2*T1*TPM1*Q2 * (  - 32*SPM1*U1M2 )
     &    + M2*T12*TPM1*Q2 * (  - 32*SPM2*U1M2 )
     &    + M2*TPM1*U6*U7M2*Q2 * (  - 32*SPM1 )
     &    + M2*TPM1*U6*U7M1*Q2 * ( 32*SPM1*U1M1 )
     &    + M2*TPM1*U62*U7M2*Q2 * (  - 32*SPM2 )
     &    + M2*TPM1*U7M1*Q2 * ( 32*U1M1 )
     &    + T1*S3*TPM2*U6*U7M1*Q2 * ( 32*SPM1*U1M1 )
     &    + T1*S3*TPM2*U6*Q2 * (  - 16*SPM1*U1M2 )
     &    + T1*S3*TPM2*U62*U7M1*Q2 * ( 32*SPM2*U1M1 )
     &    + T1*S4*TPM2*U6*U7M2*Q2 * (  - 16*SPM1 )
     &    + T1*S4*TPM2*U6*U7M1*Q2 * ( 32*SPM1*U1M1 )
     &    + T1*S4*TPM2*U62*U7M2*Q2 * (  - 16*SPM2 )
     &    + T1*S4*TPM2*U7M1*Q2 * ( 16*U1M1 )
     &    + T1*S4*TPM2*Q2 * (  - 16*U1M2 )
     &    + T1*UP*TPM2*U6*U7M2*Q2 * (  - 16*SPM1 )
     &    + T1*UP*TPM2*U6*U7M1*Q2 * ( 32*SPM1*U1M1 )
     &    + T1*UP*TPM2*U6*Q2 * (  - 16*SPM1*U1M2 )
     &    + T1*UP*TPM2*U62*U7M2*Q2 * (  - 16*SPM2 )
     &    + T1*UP*TPM2*U62*U7M1*Q2 * ( 16*SPM2*U1M1 )
     &    + T1*TPM2*U6*U7M2*Q4 * (  - 16*SPM1 )
     &    + T1*TPM2*U6*U7M1*Q4 * ( 32*SPM1*U1M1 )
     &    + T1*TPM2*U6*Q4 * (  - 16*SPM1*U1M2 )
     &    + T1*TPM2*U62*U7M2*Q4 * (  - 16*SPM2 )
     &    + T1*TPM2*U62*U7M1*Q4 * ( 16*SPM2*U1M1 )
     &    + T1*TPM1*U6*U7M1*Q2 * ( 16*SPM2 )
     &    + T1*TPM1*U6*Q2 * ( 16*SPM2*U1M2*U1P )
     &    + T1*TPM1*U6*Q4 * (  - 16*SPM2*U1M2 )
     &    + T1*TPM1*U7M1*Q4 * (  - 16*SPM1*U1M1 )
     &    + T1*TPM1*Q2 * (  - 16*SPM1*U1M1 )
     &    + T12*S3*TPM2*U6*Q2 * (  - 16*SPM2*U1M2 )
     &    + T12*S4*TPM2*U6*U7M1*Q2 * ( 32*SPM2*U1M1 )
     &    + T12*S4*TPM2*U7M1*Q2 * ( 16*SPM1*U1M1 )
     &    + T12*S4*TPM2*Q2 * (  - 32*SPM1*U1M2 )
     &    + T12*UP*TPM2*U6*U7M1*Q2 * ( 16*SPM2*U1M1 )
     &    + T12*UP*TPM2*U6*Q2 * (  - 16*SPM2*U1M2 )
     &    + T12*TPM2*U6*U7M1*Q4 * ( 16*SPM2*U1M1 )
     &    + T12*TPM2*U6*Q4 * (  - 16*SPM2*U1M2 )
     &    + T12*TPM1*U7M1*Q4 * (  - 16*SPM2*U1M1 )
     &    + T12*TPM1*Q2 * (  - 16*SPM2*U1M1 )
     &    + T13*S4*TPM2*Q2 * (  - 16*SPM2*U1M2 )
     &    + S3*TPM2*U6*U7M2*Q2 * (  - 16 )
     &    + S3*TPM2*U6*U7M1*Q2 * ( 16*U1M1 )
     &    + S3*TPM2*U62*U7M2*Q2 * (  - 32*SPM1 )
     &    + S3*TPM2*U62*U7M1*Q2 * ( 16*SPM1*U1M1 )
     &    + S3*TPM2*U63*U7M2*Q2 * (  - 16*SPM2 )
     &    + TPM1*U6*U7M1*Q2 * (  - 16*SPM1*U1M1*U1P )
     &    + TPM1*U62*U7M1*Q2 * (  - 16*SPM2*U1M1*U1P )

        FAQLC = TP*TERM1

      END IF

      RETURN
      END
      FUNCTION FAQLD(X,Y,M2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DP,DM)
C
C THIS IS THE EL*EL PIECE OF F_AQ_L (I.E. TERM 3) IN 3 CASES
C 1) SOFT LIMIT
C 2) COLLINEAR LIMIT
C 3) HARD
C
C LIMITS CHECK UNDER THETA2 INTEGRATION: 12/5/94
C LIMITS CHECK W/O   THETA2 INTEGRATION: 2/15/95
C
C IT IS TP*M^AQ_L(3) OF THE PAPER
C THERE IS AN OVERALL FACTOR OF G^4 EL^2 N CF UNDERSTOOD
C
      IMPLICIT DOUBLE PRECISION (A-Z)
      PARAMETER (DELTAS=1.0D-6)
      PARAMETER (DELTAC=1.0D-7)

      ONEMX = 1.D0 - X
      ONEPY = 1.D0 + Y

      IF ( ONEMX.LT.DELTAS ) THEN
        FAQLD = 0.D0
      ELSE IF ( ONEPY.LT.DELTAC ) THEN
        FAQLD = 0.D0
      ELSE
        Q4 = Q2*Q2
        S52 = S5*S5
        S53 = S5*S52
        S54 = S5*S53
        S5M1 = 1.D0/S5
        S5M2 = S5M1*S5M1
        S42 = S4*S4
        S4M1 = 1.D0/S4
        S4M2 = S4M1*S4M1
        S32 = S3*S3
        S3M1 = 1.D0/S3
        S3M2 = S3M1*S3M1
        S2 = S*S
        SM1 = 1.D0/S
        SPM1 = 1.D0/SP
        SPM2 = SPM1*SPM1
        U62 = U6*U6
        U63 = U6*U62
        U6M1 = 1.D0/U6
        U6M2 = U6M1*U6M1
        U7M1 = 1.D0/U7
        U7M2 = U7M1*U7M1
        TP2 = TP*TP
        TP3 = TP*TP2
        TP4 = TP*TP3
        TPM1 = 1.D0/TP
        UP2 = UP*UP
        UP3 = UP*UP2
        UPM1 = 1.D0/UP
        UPM2 = UPM1*UPM1
        T12 = T1*T1
        T13 = T1*T12
        T1M1 = 1.D0/T1
        T1M2 = T1M1*T1M1
        U1M1 = 1.D0/U1
        U1M2 = U1M1*U1M1
        U1P = U1+Q2

        TERM3 =
     &    + M2*S5M2*UPM2*TP*Q2 * (  - 32 )
     &    + M2*S5M2*UPM2*TP2*Q2 * (  - 64*SPM1 )
     &    + M2*S5M2*UPM2*TP3*Q2 * (  - 32*SPM2 )
     &    + T1*S4*S5M2*UPM2*TP*Q2 * (  - 16*SPM1 )
     &    + T1*S4*S5M2*UPM2*TP2*Q2 * (  - 16*SPM2 )
     &    + T1*S5M2*UPM2*TP*U7*Q2 * (  - 16*SPM1 )
     &    + T1*S5M2*UPM2*TP*Q4 * (  - 16*SPM1 )
     &    + T1*S5M2*UPM2*TP2*U7*Q2 * (  - 16*SPM2 )
     &    + T1*S5M2*UPM2*TP2*Q4 * (  - 16*SPM2 )
     &    + T1*S5M2*UPM1*TP*U6*Q2 * ( 32*SPM2 )
     &    + U1P*S5M2*UPM2*TP*U6*Q2 * (  - 16*SPM1 )
     &    + U1P*S5M2*UPM2*TP2*U6*Q2 * (  - 16*SPM2 )
     &    + S3*S5M2*UPM2*TP*U6*Q2 * (  - 16*SPM1 )
     &    + S3*S5M2*UPM2*TP2*U6*Q2 * (  - 16*SPM2 )

        FAQLD = TP*TERM3

      END IF

      RETURN
      END
      FUNCTION FGGC_CACF
     &         (X,Y,M2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DP,DM)
C
C THIS IS THE CA*CF TERM OF FGGC IN 3 CASES
C 1) SOFT LIMIT
C 2) COLLINEAR LIMIT
C 3) HARD
C
C LIMITS CHECK UNDER THETA2 INTEGRATION: 11/23/94
C LIMITS CHECK W/O   THETA2 INTEGRATION: 3/1/95, 3/29/95
C
C IT IS TP*(UP+Q2*S5/S)*M^G_G(3) OF THE PAPER
C THERE IS AN OVERALL FACTOR OF G^4 EH^2 N CA CF UNDERSTOOD
C
      IMPLICIT DOUBLE PRECISION (A-Z)

      COMMON/AZDEP/CTH22,STH12

      PARAMETER (DELTAS=1.0D-5)
      PARAMETER (DELTAC=1.0D-7)

      ONEMX = 1.D0 - X
      ONEPY = 1.D0 + Y
      ONEMY = 1.D0 - Y

      IF ( ONEMX.LT.DELTAS ) THEN
C         WRITE(*,*) 'TAKING SOFT'
C (1-Y*Y)*(1-X)**2*(K1P2)*SP**2
        P1 = -8.D0*S*T1*ONEMY/SP/DP
C (1-Y*Y)*(1-X)**2*(K1P1)*SP**2
        P2 = -8.D0*S*U1*ONEMY/SP/DM
C (1-Y*Y)*(1-X)**2*(P1P2)*SP**2
        P3 = +8.D0*(S-2.D0*M2)*ONEMY*ONEPY/DP/DM
        RSPS2 = (SP/S)**2
        FGGC_CACF = 2.D0*RSPS2*BGQED(T1,SP,M2,Q2)*(P1+P2-P3)
      ELSE IF ( ONEPY.LT.DELTAC ) THEN
C         WRITE(*,*) 'TAKING COLLINEAR'
        BETA52 = 1.D0-4.D0*M2/S5
        XSP2 = X*X*SP*SP
        FH = 2.D0*(X*X-2.D0*X+2.D0)*(M2*XSP2/X/T1/U1-S5)/X/X
     &      - ONEMX*ONEMX*S5*BETA52*CTH22*STH12*XSP2/T1/U1/X**5
        FGGC_CACF = -32.D0*(2*M2-Q2)*XSP2*FH/X/T1/U1/S
     &    + 32.D0*((X*X-X+1.D0)**2)*XSP2*(XSP2/X/T1/U1-2.D0)/S/X**4
      ELSE
C         WRITE(*,*) 'TAKING HARD'
        M4 = M2*M2
        M6 = M4*M2
        Q4 = Q2*Q2
        Q6 = Q2*Q4
        S52 = S5*S5
        S53 = S5*S52
        S42 = S4*S4
        S4M1 = 1.D0/S4
        S32 = S3*S3
        S3M1 = 1.D0/S3
        SM1 = 1.D0/S
        SP2 = SP*SP
        U62 = U6*U6
        U63 = U6*U62
        U6M1 = 1.D0/U6
        U7M1 = 1.D0/U7
        U7M2 = U7M1*U7M1
        TP2 = TP*TP
        TP3 = TP*TP2
        TPM1 = 1.D0/TP
        TPM2 = TPM1*TPM1
        UP2 = UP*UP
        UP3 = UP*UP2
        T12 = T1*T1
        T13 = T1*T12
        T1M1 = 1.D0/T1
        U1M1 = 1.D0/U1
        U1M2 = U1M1*U1M1
        U1P = U1+Q2
        U1P2 = U1P*U1P

        FGGC_CACF =
     &+ M2*SP*S5*S4M1*S3M1*U6M1 * (  - 32*U1M1 )
     &+ M2*SP*S5*S4M1*S3M1*U7M1 * (  - 32*T1M1 )
     &+ M2*SP*S5*S4M1*U6M1 * (  - 24*T1M1*U1M1 )
     &+ M2*SP*S5*S3M1*U6M1*U7M1 * (  - 24*T1M1 )
     &+ M2*SP*S5*TPM1*U6M1*U7M1 * (  - 16*U1M1 )
     &+ M2*SP*S5*TPM1*U7M1 * (  - 16*T1M1*U1M1 )
     &+ M2*SP*S5*U6M1*U7M1 * ( 16*T1M1*U1M1 )
     &+ M2*SP*S4M1*S3*TPM1*U7M1 * ( 4*T1M1 - 16*U1M1 )
     &+ M2*SP*S4M1*S3*TPM1 * ( 28*T1M1*U1M1 )
     &+ M2*SP*S4M1*S3*U6M1 * (  - 8*T1M1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*SP*S4M1*UP*TPM1*U7M1 * ( 8*U1M1 )
     &+ M2*SP*S4M1*TPM1*U6*U7M1 * ( 40*T1M1 )
     &+ M2*SP*S4M1*TPM1*U6 * ( 8*T1M1*U1M1 )
     &+ M2*SP*S4M1*TPM1*U7M1 * ( 8 )
     &+ M2*SP*S4M1*TPM1*Q2 * ( 8*U1M2 )
     &+ M2*SP*S4M1*TPM1 * (  - 8*U1M1 )
     &+ M2*SP*S4M1*U6M1*Q2 * (  - 16*U1M2 )
     &+ M2*SP*S4M1*U6M1 * (  - 24*U1M1 )
     &+ M2*SP*S4M1*U7M1 * ( 16*T1M1 )
     &+ M2*SP*S4M1 * ( 16*T1M1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*SP*S4*S3M1*TPM1*U6M1*U7M1 * ( 28 )
     &+ M2*SP*S4*S3M1*TPM1*U6M1 * ( 4*U1M1 )
     &+ M2*SP*S4*S3M1*TPM1*U7M1 * (  - 16*U1M1 )
     &+ M2*SP*S4*S3M1*U6M1*U7M1 * (  - 8*T1M1 )
     &+ M2*SP*S4*TPM2*U7M1 * ( 32*U1M1 )
     &+ M2*SP*S4*TPM2 * ( 32*U1M2 )
     &+ M2*SP*S4*TPM1*U6M1 * (  - 8*U1M2 )
     &+ M2*SP*S4*TPM1*U7M1 * ( 24*T1M1*U1M1 )
     &+ M2*SP*S3M1*UP*TPM1*U7M1 * ( 8*U1M1 )
     &+ M2*SP*S3M1*TPM1*U6M1*U7M1 * ( 8*T1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*SP*S3M1*TPM1*U6M1 * ( 40*T1*U1M1 )
     &+ M2*SP*S3M1*TPM1*U7M2*Q2 * ( 8 )
     &+ M2*SP*S3M1*TPM1*U7M1 * (  - 8 )
     &+ M2*SP*S3M1*TPM1 * ( 8*U1M1 )
     &+ M2*SP*S3M1*U6M1*U7M1 * ( 16 )
     &+ M2*SP*S3M1*U6M1 * ( 16*U1M1 )
     &+ M2*SP*S3M1*U7M2*Q2 * (  - 16*T1M1 )
     &+ M2*SP*S3M1*U7M1 * (  - 24*T1M1 )
     &+ M2*SP*S3*TPM2*U7M2 * ( 32 )
     &+ M2*SP*S3*TPM2*U7M1 * ( 32*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*SP*S3*TPM1*U6M1*U7M1 * ( 24*U1M1 )
     &+ M2*SP*S3*TPM1*U7M2 * (  - 8*T1M1 )
     &+ M2*SP*UP*TPM2*U7M1 * ( 64*U1M1 )
     &+ M2*SP*UP*TPM1*U6M1*U7M1 * ( 8*U1M1 )
     &+ M2*SP*UP*TPM1*U7M1 * ( 8*T1M1*U1M1 )
     &+ M2*SP*TPM2*U7M1*Q2 * ( 64*U1M1 )
     &+ M2*SP*TPM1*U6M1*U7M1 * (  - 4 - 8*T1*U1M1 )
     &+ M2*SP*TPM1*U6M1*Q2 * ( 8*U1M2 )
     &+ M2*SP*TPM1*U6M1 * (  - 12*U1M1 )
     &+ M2*SP*TPM1*U6*U7M1 * (  - 8*T1M1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*SP*TPM1*U7M2*Q2 * ( 8*T1M1 )
     &+ M2*SP*TPM1*U7M2 * ( 8 )
     &+ M2*SP*TPM1*U7M1 * (  - 12*T1M1 )
     &+ M2*SP*TPM1 * (  - 4*T1M1*U1M1 + 8*U1M2 )
     &+ M2*SP*U6M1*U7M1 * (  - 8*T1M1 )
     &+ M2*SP*U6M1 * (  - 8*T1M1*U1M1 )
     &+ M2*SP2*TPM1*U6M1*U7M1 * (  - 8*U1M1 )
     &+ M2*SP2*TPM1*U7M1 * (  - 8*T1M1*U1M1 )
     &+ M2*SP2*U6M1*U7M1 * (  - 16*T1M1*U1M1 )
     &+ M2*U1P*S5*S4M1*S3M1*U7M1 * (  - 32*T1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*U1P*S5*S3M1*U6M1*U7M1 * (  - 32*T1M1 )
     &+ M2*U1P*S4M1*S3M1*TP*U7M1 * (  - 8*T1M1 )
     &+ M2*U1P*S4M1*S3M1*U6*U7M1 * (  - 16*T1M1 )
     &+ M2*U1P*S4M1*S3*TPM1*U7M1 * ( 16*T1M1 )
     &+ M2*U1P*S4M1*TPM1*U6*U7M1 * ( 24*T1M1 )
     &+ M2*U1P*S4M1*U7M1 * ( 20*T1M1 )
     &+ M2*U1P*S4*S3M1*TPM1*U6M1*U7M1 * ( 24 )
     &+ M2*U1P*S4*S3M1*U6M1*U7M1 * (  - 16*T1M1 )
     &+ M2*U1P*S3M1*TPM1*U6M1*U7M1 * ( 16*T1 )
     &+ M2*U1P*S3M1*TPM1*U7M2 * (  - 32*T1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*U1P*S3M1*TPM1*U7M1 * ( 8 )
     &+ M2*U1P*S3M1*TP*U6M1*U7M1 * (  - 8*T1M1 )
     &+ M2*U1P*S3M1*TP*U7M2 * (  - 32*T1M1 )
     &+ M2*U1P*S3M1*U6M1*U7M1 * ( 20 )
     &+ M2*U1P*S3M1*U7M2*Q2 * (  - 16*T1M1 )
     &+ M2*U1P*S3M1*U7M2 * (  - 56 )
     &+ M2*U1P*S3*TPM1*U7M2 * (  - 32*T1M1 )
     &+ M2*U1P*TPM1*U7M2 * (  - 32 )
     &+ M2*U1P*TPM1*U7M1 * ( 8*T1M1 )
     &+ M2*U1P*U7M2 * (  - 56*T1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S5*S4M1*S3M1*UP*U6M1 * (  - 24*U1M1 )
     &+ M2*S5*S4M1*S3M1*UP*U7M1 * (  - 24*T1M1 + 16*U1M1 )
     &+ M2*S5*S4M1*S3M1*TP*U6M1 * ( 16*T1M1 - 24*U1M1 )
     &+ M2*S5*S4M1*S3M1*TP*U7M1 * (  - 24*T1M1 )
     &+ M2*S5*S4M1*S3M1*U6M1*U7 * (  - 32*U1M1 )
     &+ M2*S5*S4M1*S3M1*U6M1*Q2 * (  - 72*U1M1 )
     &+ M2*S5*S4M1*S3M1*U6M1 * ( 32 - 32*T1*U1M1 )
     &+ M2*S5*S4M1*S3M1*U6*U7M1 * (  - 32*T1M1 )
     &+ M2*S5*S4M1*S3M1*U7M1*Q2 * (  - 40*T1M1 + 16*U1M1 )
     &+ M2*S5*S4M1*S3M1*U7M1 * ( 32 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S5*S4M1*S3M1 * ( 32*T1M1 + 32*U1M1 )
     &+ M2*S5*S4M1*S3*TPM1*U7M1 * ( 8*T1M1 + 8*U1M1 )
     &+ M2*S5*S4M1*S3*TPM1 * ( 8*T1M1*U1M1 )
     &+ M2*S5*S4M1*S3*U6M1 * (  - 32*T1M1*U1M1 )
     &+ M2*S5*S4M1*UP*TPM1*U7M1 * (  - 16*U1M1 )
     &+ M2*S5*S4M1*UP*U6M1 * (  - 32*T1M1*U1M1 )
     &+ M2*S5*S4M1*TPM1*U6*U7M1 * ( 8*T1M1 - 8*U1M1 )
     &+ M2*S5*S4M1*TPM1*U6 * ( 8*T1M1*U1M1 - 32*U1M2 )
     &+ M2*S5*S4M1*TPM1*U7M1*Q2 * (  - 16*U1M1 )
     &+ M2*S5*S4M1*TPM1*U7M1 * ( 8 + 8*T1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S5*S4M1*TPM1 * ( 8*U1M1 )
     &+ M2*S5*S4M1*TP*U6M1 * (  - 24*T1M1*U1M1 - 32*U1M2 )
     &+ M2*S5*S4M1*U6M1*U7 * (  - 32*T1M1*U1M1 )
     &+ M2*S5*S4M1*U6M1*Q2 * (  - 80*T1M1*U1M1 - 16*U1M2 )
     &+ M2*S5*S4M1*U6M1 * ( 32*T1M1 )
     &+ M2*S5*S4M1*U7M1 * ( 40*U1M1 )
     &+ M2*S5*S4M1 * (  - 56*U1M2 )
     &+ M2*S5*S4*S3M1*TPM1*U6M1*U7M1 * ( 8 )
     &+ M2*S5*S4*S3M1*TPM1*U6M1 * ( 8*U1M1 )
     &+ M2*S5*S4*S3M1*TPM1*U7M1 * ( 8*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S5*S4*S3M1*U6M1*U7M1 * (  - 32*T1M1 )
     &+ M2*S5*S4*TPM1*U6M1*U7M1 * (  - 8*U1M1 )
     &+ M2*S5*S4*TPM1*U6M1 * (  - 32*U1M2 )
     &+ M2*S5*S4*TPM1*U7M1 * ( 8*T1M1*U1M1 )
     &+ M2*S5*S3M1*UP*TPM1*U7M1 * (  - 16*U1M1 )
     &+ M2*S5*S3M1*UP*U6M1*U7M1 * (  - 32*T1M1 )
     &+ M2*S5*S3M1*TPM1*U6M1*U7M1 * ( 8*T1 )
     &+ M2*S5*S3M1*TPM1*U6M1 * ( 8*T1*U1M1 )
     &+ M2*S5*S3M1*TPM1*U6*U7M1 * ( 8*U1M1 )
     &+ M2*S5*S3M1*TPM1*U7M2 * (  - 32*T1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S5*S3M1*TPM1*U7M1*Q2 * (  - 16*U1M1 )
     &+ M2*S5*S3M1*TPM1*U7M1 * ( 8 - 8*T1*U1M1 )
     &+ M2*S5*S3M1*TPM1 * ( 8*U1M1 )
     &+ M2*S5*S3M1*TP*U6M1*U7M1 * (  - 24*T1M1 )
     &+ M2*S5*S3M1*TP*U7M2 * (  - 32*T1M1 )
     &+ M2*S5*S3M1*U6M1*U7M1*Q2 * (  - 48*T1M1 )
     &+ M2*S5*S3M1*U6M1 * ( 32*T1M1 )
     &+ M2*S5*S3M1*U7M2*Q2 * (  - 16*T1M1 )
     &+ M2*S5*S3M1*U7M2 * (  - 56 )
     &+ M2*S5*S3M1*U7M1 * ( 40*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S5*S3*TPM1*U6M1*U7M1 * ( 8*U1M1 )
     &+ M2*S5*S3*TPM1*U7M2 * (  - 32*T1M1 )
     &+ M2*S5*S3*TPM1*U7M1 * (  - 8*T1M1*U1M1 )
     &+ M2*S5*TPM1*U6M1*U7M1 * ( 8 + 8*T1*U1M1 )
     &+ M2*S5*TPM1*U6M1 * ( 8*U1M1 )
     &+ M2*S5*TPM1*U6*U7M1 * ( 8*T1M1*U1M1 )
     &+ M2*S5*TPM1*U7M2 * (  - 32 )
     &+ M2*S5*TPM1*U7M1 * ( 8*T1M1 - 96*U1M1 )
     &+ M2*S5*TPM1 * ( 8*T1M1*U1M1 - 32*U1M2 )
     &+ M2*S5*U6M1*U7M1 * ( 32*T1M1 + 40*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S5*U6M1 * ( 32*T1M1*U1M1 - 56*U1M2 )
     &+ M2*S5*U7M2 * (  - 56*T1M1 )
     &+ M2*S5*U7M1 * ( 40*T1M1*U1M1 )
     &+ M2*S52*S4M1*S3M1*U6M1 * ( 32*T1M1 - 16*U1M1 )
     &+ M2*S52*S4M1*S3M1*U7M1 * (  - 16*T1M1 + 32*U1M1 )
     &+ M2*S52*S4M1*U6M1 * (  - 16*T1M1*U1M1 )
     &+ M2*S52*S3M1*U6M1*U7M1 * (  - 16*T1M1 )
     &+ M2*S52*U6M1*U7M1 * ( 32*T1M1*U1M1 )
     &+ M2*S4M1*S3M1*UP*U6M1 * (  - 8*T1*U1M1 )
     &+ M2*S4M1*S3M1*UP*U6*U7M1 * (  - 8*T1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S4M1*S3M1*UP*U7M1*Q2 * (  - 32*U1M1 )
     &+ M2*S4M1*S3M1*UP*U7M1 * (  - 8 )
     &+ M2*S4M1*S3M1*UP * (  - 8*U1M1 )
     &+ M2*S4M1*S3M1*UP2*U7M1 * (  - 16*U1M1 )
     &+ M2*S4M1*S3M1*TP*U6M1*U7 * (  - 8*U1M1 )
     &+ M2*S4M1*S3M1*TP*U6M1*Q2 * (  - 16*U1M1 )
     &+ M2*S4M1*S3M1*TP*U6M1 * (  - 8 )
     &+ M2*S4M1*S3M1*TP*U7M1*Q2 * (  - 8*T1M1 )
     &+ M2*S4M1*S3M1*TP * (  - 8*T1M1 )
     &+ M2*S4M1*S3M1*TP2*U6M1 * (  - 16*T1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S4M1*S3M1*U6M1*U7 * (  - 16*T1*U1M1 )
     &+ M2*S4M1*S3M1*U6M1*Q2 * (  - 24*T1*U1M1 )
     &+ M2*S4M1*S3M1*U6*U7M1*Q2 * (  - 8*T1M1 )
     &+ M2*S4M1*S3M1*U7M1*Q2 * (  - 24 )
     &+ M2*S4M1*S3M1*U7M1*Q4 * (  - 16*U1M1 )
     &+ M2*S4M1*S3M1*Q2 * (  - 24*U1M1 )
     &+ M2*S4M1*S3M1 * (  - 32 )
     &+ M2*S4M1*S3*UP*TPM1*U7M1 * ( 8*T1M1 - 8*U1M1 )
     &+ M2*S4M1*S3*UP*TPM1 * ( 40*T1M1*U1M1 )
     &+ M2*S4M1*S3*TPM1*U6*U7M1 * (  - 8*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S4M1*S3*TPM1*U6 * (  - 8*U1M2 )
     &+ M2*S4M1*S3*TPM1*U7M1*Q2 * (  - 8*U1M1 )
     &+ M2*S4M1*S3*TPM1*U7M1 * ( 24 )
     &+ M2*S4M1*S3*TPM1*U7 * ( 24*T1M1*U1M1 )
     &+ M2*S4M1*S3*TPM1*Q2 * ( 80*T1M1*U1M1 + 8*U1M2 )
     &+ M2*S4M1*S3*TPM1 * ( 8*T1M1 + 24*U1M1 )
     &+ M2*S4M1*S3*U6M1*U7 * (  - 16*T1M1*U1M1 )
     &+ M2*S4M1*S3*U6M1*Q2 * (  - 16*T1M1*U1M1 - 16*U1M2 )
     &+ M2*S4M1*S3*U7M1 * ( 8*T1M1 )
     &+ M2*S4M1*S3 * ( 16*T1M1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S4M1*S32*TPM1*U7M1 * ( 8*T1M1 )
     &+ M2*S4M1*S32*TPM1 * ( 24*T1M1*U1M1 )
     &+ M2*S4M1*UP*TPM1*U6*U7M1 * ( 28*T1M1 )
     &+ M2*S4M1*UP*TPM1*U6 * ( 4*T1M1*U1M1 - 8*U1M2 )
     &+ M2*S4M1*UP*TPM1*U7M1*Q2 * (  - 24*U1M1 )
     &+ M2*S4M1*UP*TPM1*U7M1 * (  - 4 + 24*T1*U1M1 )
     &+ M2*S4M1*UP*TPM1*Q2 * ( 8*U1M2 )
     &+ M2*S4M1*UP*TPM1 * (  - 12*U1M1 )
     &+ M2*S4M1*UP*U6M1*Q2 * (  - 16*U1M2 )
     &+ M2*S4M1*UP*U6M1 * (  - 24*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S4M1*UP*U7M1 * ( 16*T1M1 )
     &+ M2*S4M1*UP * ( 16*T1M1*U1M1 )
     &+ M2*S4M1*UP2*TPM1*U7M1 * (  - 8*U1M1 )
     &+ M2*S4M1*TPM1*U6*U7M1*Q2 * ( 44*T1M1 - 16*U1M1 )
     &+ M2*S4M1*TPM1*U6*U7M1 * (  - 8 )
     &+ M2*S4M1*TPM1*U6*U7 * ( 16*T1M1*U1M1 - 32*U1M2 )
     &+ M2*S4M1*TPM1*U6*Q2 * ( 12*T1M1*U1M1 - 16*U1M2 )
     &+ M2*S4M1*TPM1*U6 * ( 8*T1M1 - 88*U1M1 )
     &+ M2*S4M1*TPM1*U62*U7M1 * ( 24*T1M1 )
     &+ M2*S4M1*TPM1*U62 * ( 8*T1M1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S4M1*TPM1*U7M1*Q2 * ( 4 + 40*T1*U1M1 )
     &+ M2*S4M1*TPM1*U7M1*Q4 * (  - 16*U1M1 )
     &+ M2*S4M1*TPM1*U7 * ( 8*U1M1 )
     &+ M2*S4M1*TPM1*Q2 * ( 8*T1*U1M2 - 4*U1M1 )
     &+ M2*S4M1*TPM1*Q4 * ( 8*U1M2 )
     &+ M2*S4M1*TPM1 * ( 8 )
     &+ M2*S4M1*TP*U6M1*U7 * (  - 8*T1M1*U1M1 - 32*U1M2 )
     &+ M2*S4M1*TP*U6M1*Q2 * (  - 16*T1M1*U1M1 - 48*U1M2 )
     &+ M2*S4M1*TP*U6M1 * (  - 8*T1M1 - 16*U1M1 )
     &+ M2*S4M1*U6M1*U7*Q2 * (  - 16*U1M2 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S4M1*U6M1*Q2 * (  - 16*T1*U1M2 - 24*U1M1 )
     &+ M2*S4M1*U6M1*Q4 * (  - 32*U1M2 )
     &+ M2*S4M1*U6M1 * ( 64 )
     &+ M2*S4M1*U6*U7M1 * ( 16*T1M1 )
     &+ M2*S4M1*U6 * ( 8*T1M1*U1M1 )
     &+ M2*S4M1*U7M1*Q2 * ( 4*T1M1 + 8*U1M1 )
     &+ M2*S4M1*U7M1 * ( 64 )
     &+ M2*S4M1*U7 * ( 20*T1M1*U1M1 - 56*U1M2 )
     &+ M2*S4M1*Q2 * ( 24*T1M1*U1M1 - 40*U1M2 )
     &+ M2*S4M1 * ( 8*T1M1 - 64*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S4*S3M1*UP*TPM1*U6M1*U7M1 * ( 40 )
     &+ M2*S4*S3M1*UP*TPM1*U6M1 * ( 8*U1M1 )
     &+ M2*S4*S3M1*UP*TPM1*U7M1 * (  - 8*U1M1 )
     &+ M2*S4*S3M1*TPM1*U6M1*U7M1*Q2 * ( 56 )
     &+ M2*S4*S3M1*TPM1*U6M1*U7 * ( 16*U1M1 )
     &+ M2*S4*S3M1*TPM1*U6M1*Q2 * ( 16*U1M1 )
     &+ M2*S4*S3M1*TPM1*U6M1 * ( 8 )
     &+ M2*S4*S3M1*TPM1*U7M2*Q2 * ( 8 )
     &+ M2*S4*S3M1*TPM1*U7M2 * (  - 8*T1 )
     &+ M2*S4*S3M1*TPM1*U7M1*Q2 * (  - 8*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S4*S3M1*TPM1*U7M1 * ( 24 - 8*T1*U1M1 )
     &+ M2*S4*S3M1*TPM1 * ( 24*U1M1 )
     &+ M2*S4*S3M1*U6M1*U7M1 * ( 16 )
     &+ M2*S4*S3M1*U6M1 * ( 8*U1M1 )
     &+ M2*S4*S3M1*U7M2*Q2 * (  - 16*T1M1 )
     &+ M2*S4*TPM2*U7M2 * ( 32*T1 )
     &+ M2*S4*TPM2*U7M1 * ( 64*T1*U1M1 )
     &+ M2*S4*TPM2 * ( 32*T1*U1M2 )
     &+ M2*S4*TPM1*U6M1*U7M1*Q2 * (  - 16*U1M1 )
     &+ M2*S4*TPM1*U6M1*U7M1 * (  - 8 - 8*T1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S4*TPM1*U6M1*U7 * (  - 32*U1M2 )
     &+ M2*S4*TPM1*U6M1*Q2 * (  - 8*U1M2 )
     &+ M2*S4*TPM1*U6M1 * (  - 8*T1*U1M2 - 88*U1M1 )
     &+ M2*S4*TPM1*U7M2*Q2 * ( 8*T1M1 )
     &+ M2*S4*TPM1*U7M2 * ( 8 )
     &+ M2*S4*TPM1*U7M1*Q2 * ( 16*T1M1*U1M1 )
     &+ M2*S4*TPM1*U7M1 * ( 8*U1M1 )
     &+ M2*S42*S3M1*TPM1*U6M1*U7M1 * ( 24 )
     &+ M2*S42*S3M1*TPM1*U6M1 * ( 8*U1M1 )
     &+ M2*S3M1*UP*TPM1*U6M1*U7M1 * ( 4*T1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S3M1*UP*TPM1*U6M1 * ( 28*T1*U1M1 )
     &+ M2*S3M1*UP*TPM1*U6*U7M1 * ( 24*U1M1 )
     &+ M2*S3M1*UP*TPM1*U7M2*Q2 * ( 8 )
     &+ M2*S3M1*UP*TPM1*U7M2 * (  - 8*T1 )
     &+ M2*S3M1*UP*TPM1*U7M1*Q2 * (  - 24*U1M1 )
     &+ M2*S3M1*UP*TPM1*U7M1 * (  - 12 )
     &+ M2*S3M1*UP*TPM1 * (  - 4*U1M1 )
     &+ M2*S3M1*UP*U6M1*U7M1 * ( 16 )
     &+ M2*S3M1*UP*U6M1 * ( 16*U1M1 )
     &+ M2*S3M1*UP*U7M2*Q2 * (  - 16*T1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S3M1*UP*U7M1 * (  - 24*T1M1 )
     &+ M2*S3M1*UP2*TPM1*U7M1 * (  - 8*U1M1 )
     &+ M2*S3M1*TPM1*U6M1*U7M1*Q2 * (  - 4*T1 )
     &+ M2*S3M1*TPM1*U6M1*U7M1 * ( 8*T12 )
     &+ M2*S3M1*TPM1*U6M1*U7 * ( 24*T1*U1M1 )
     &+ M2*S3M1*TPM1*U6M1*Q2 * ( 68*T1*U1M1 )
     &+ M2*S3M1*TPM1*U6M1 * ( 8*T1 + 24*T12*U1M1 )
     &+ M2*S3M1*TPM1*U6*U7M2*Q2 * ( 8 )
     &+ M2*S3M1*TPM1*U6*U7M1*Q2 * ( 40*U1M1 )
     &+ M2*S3M1*TPM1*U7M2*Q2 * ( 16*T1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S3M1*TPM1*U7M2*Q4 * ( 8 )
     &+ M2*S3M1*TPM1*U7M1*Q2 * (  - 12 - 16*T1*U1M1 )
     &+ M2*S3M1*TPM1*U7M1*Q4 * (  - 16*U1M1 )
     &+ M2*S3M1*TPM1*U7M1 * (  - 88*T1 )
     &+ M2*S3M1*TPM1*Q2 * ( 4*U1M1 )
     &+ M2*S3M1*TPM1 * ( 8 - 8*T1*U1M1 )
     &+ M2*S3M1*TP*U6M1*U7M1*Q2 * (  - 8*T1M1 )
     &+ M2*S3M1*TP*U6M1 * (  - 8*T1M1 )
     &+ M2*S3M1*TP*U7M2*Q2 * (  - 16*T1M1 )
     &+ M2*S3M1*TP*U7M1 * (  - 16*T1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S3M1*U6M1*U7M1*Q2 * ( 4 )
     &+ M2*S3M1*U6M1*U7M1 * ( 8*T1 )
     &+ M2*S3M1*U6M1*U7 * ( 20*U1M1 )
     &+ M2*S3M1*U6M1*Q2 * ( 24*U1M1 )
     &+ M2*S3M1*U6M1 * ( 8 + 16*T1*U1M1 )
     &+ M2*S3M1*U6*U7M2*Q2 * (  - 16*T1M1 )
     &+ M2*S3M1*U7M2*Q2 * ( 16 )
     &+ M2*S3M1*U7M2*Q4 * (  - 16*T1M1 )
     &+ M2*S3M1*U7M1*Q2 * (  - 24*T1M1 + 8*U1M1 )
     &+ M2*S3M1*U7M1 * (  - 64 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S3M1 * ( 64*T1M1 + 64*U1M1 )
     &+ M2*S3*TPM2*U6*U7M2 * ( 32 )
     &+ M2*S3*TPM2*U6*U7M1 * ( 64*U1M1 )
     &+ M2*S3*TPM2*U6 * ( 32*U1M2 )
     &+ M2*S3*TPM1*U6M1*U7M1*Q2 * ( 16*U1M1 )
     &+ M2*S3*TPM1*U6M1*Q2 * ( 8*U1M2 )
     &+ M2*S3*TPM1*U6*U7M2 * (  - 8*T1M1 )
     &+ M2*S3*TPM1*U6*U7M1 * (  - 8*T1M1*U1M1 )
     &+ M2*S3*TPM1*U7M2*Q2 * ( 24*T1M1 )
     &+ M2*S3*TPM1*U7M1*Q2 * (  - 16*T1M1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*S3*TPM1*U7M1 * (  - 88*T1M1 + 8*U1M1 )
     &+ M2*S3*TPM1 * (  - 8*T1M1*U1M1 + 8*U1M2 )
     &+ M2*UP*TPM2*U6*U7M1 * ( 32*U1M1 )
     &+ M2*UP*TPM2*U6 * ( 32*U1M2 )
     &+ M2*UP*TPM2*U7M2 * ( 32*T1 )
     &+ M2*UP*TPM2*U7M1 * ( 32*T1*U1M1 )
     &+ M2*UP*TPM1*U6M1*U7M1*Q2 * (  - 8*U1M1 )
     &+ M2*UP*TPM1*U6M1*U7M1 * ( 8 - 16*T1*U1M1 )
     &+ M2*UP*TPM1*U6M1*Q2 * ( 8*U1M2 )
     &+ M2*UP*TPM1*U6M1 * (  - 8*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*UP*TPM1*U6*U7M1 * (  - 16*T1M1*U1M1 )
     &+ M2*UP*TPM1*U7M2*Q2 * ( 8*T1M1 )
     &+ M2*UP*TPM1*U7M2 * ( 8 )
     &+ M2*UP*TPM1*U7M1*Q2 * (  - 8*T1M1*U1M1 )
     &+ M2*UP*TPM1*U7M1 * (  - 8*T1M1 )
     &+ M2*UP*TPM1 * ( 8*T1M1*U1M1 + 8*U1M2 )
     &+ M2*TPM2*U6*U7M1*Q2 * ( 32*U1M1 )
     &+ M2*TPM2*U6*Q2 * ( 32*U1M2 )
     &+ M2*TPM2*U7M2*Q2 * ( 32*T1 )
     &+ M2*TPM2*U7M1*Q2 * ( 32*T1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*TPM1*U6M1*U7M1*Q2 * ( 16 - 16*T1*U1M1 )
     &+ M2*TPM1*U6M1*U7M1*Q4 * (  - 8*U1M1 )
     &+ M2*TPM1*U6M1*U7M1 * ( 24*T1 )
     &+ M2*TPM1*U6M1*U7 * ( 8*U1M1 )
     &+ M2*TPM1*U6M1*Q2 * ( 8*T1*U1M2 )
     &+ M2*TPM1*U6M1*Q4 * ( 8*U1M2 )
     &+ M2*TPM1*U6M1 * ( 8 + 24*T1*U1M1 )
     &+ M2*TPM1*U6*U7M2*Q2 * ( 8*T1M1 )
     &+ M2*TPM1*U6*U7M2 * ( 8 )
     &+ M2*TPM1*U6*U7M1*Q2 * (  - 16*T1M1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M2*TPM1*U6*U7M1 * ( 24*T1M1 + 8*U1M1 )
     &+ M2*TPM1*U6 * ( 24*T1M1*U1M1 )
     &+ M2*TPM1*U7M2*Q2 * (  - 8 )
     &+ M2*TPM1*U7M2*Q4 * ( 8*T1M1 )
     &+ M2*TPM1*U7M1*Q2 * (  - 8*T1M1 - 64*U1M1 )
     &+ M2*TPM1*U7M1*Q4 * (  - 8*T1M1*U1M1 )
     &+ M2*TPM1*U7M1 * ( 8*T1*U1M1 )
     &+ M2*TPM1*U7 * (  - 32*U1M2 )
     &+ M2*TPM1*Q2 * ( 16*T1M1*U1M1 - 40*U1M2 )
     &+ M2*TPM1 * ( 8*T1M1 + 8*T1*U1M2 )
        FGGC_CACF = FGGC_CACF
     &+ M2*U6M1*U7M1*Q2 * (  - 16*T1M1 + 8*U1M1 )
     &+ M2*U6M1*U7M1 * ( 64 )
     &+ M2*U6M1*U7 * (  - 56*U1M2 )
     &+ M2*U6M1*Q2 * (  - 16*T1M1*U1M1 - 40*U1M2 )
     &+ M2*U6M1 * (  - 32*T1M1 - 64*U1M1 )
     &+ M2*U7M2*Q2 * ( 16*T1M1 )
     &+ M2*U7M1*Q2 * ( 8*T1M1*U1M1 )
     &+ M2*U7M1 * (  - 64*T1M1 )
     &+ M2 * ( 64*T1M1*U1M1 )
     &+ M4*SP*S4M1*S3M1*U6M1 * ( 96*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M4*SP*S4M1*S3M1*U7M1 * ( 96*T1M1 )
     &+ M4*SP*S4M1*TPM1*U7M1 * ( 16*T1M1 + 16*U1M1 )
     &+ M4*SP*S4M1*TPM1 * (  - 16*T1M1*U1M1 - 16*U1M2 )
     &+ M4*SP*S4M1*U6M1 * ( 32*U1M2 )
     &+ M4*SP*S3M1*TPM1*U6M1*U7M1 * (  - 16 )
     &+ M4*SP*S3M1*TPM1*U6M1 * ( 16*U1M1 )
     &+ M4*SP*S3M1*TPM1*U7M2 * (  - 16 )
     &+ M4*SP*S3M1*TPM1*U7M1 * ( 16*U1M1 )
     &+ M4*SP*S3M1*U7M2 * ( 32*T1M1 )
     &+ M4*SP*TPM1*U6M1*U7M1 * (  - 48*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M4*SP*TPM1*U6M1 * (  - 16*U1M2 )
     &+ M4*SP*TPM1*U7M2 * (  - 16*T1M1 )
     &+ M4*SP*TPM1*U7M1 * (  - 48*T1M1*U1M1 )
     &+ M4*SP*U6M1*U7M1 * (  - 128*T1M1*U1M1 )
     &+ M4*U1P*S4M1*S3M1*U7M1 * ( 64*T1M1 )
     &+ M4*U1P*S3M1*U6M1*U7M1 * ( 64*T1M1 )
     &+ M4*U1P*S3M1*U7M2 * ( 32*T1M1 )
     &+ M4*S5*S4M1*S3M1*U6M1 * ( 64*T1M1 + 96*U1M1 )
     &+ M4*S5*S4M1*S3M1*U7M1 * ( 96*T1M1 + 64*U1M1 )
     &+ M4*S5*S4M1*U6M1 * ( 96*T1M1*U1M1 + 32*U1M2 )
        FGGC_CACF = FGGC_CACF
     &+ M4*S5*S3M1*U6M1*U7M1 * ( 96*T1M1 )
     &+ M4*S5*S3M1*U7M2 * ( 32*T1M1 )
     &+ M4*S5*U6M1*U7M1 * ( 64*T1M1*U1M1 )
     &+ M4*S4M1*S3M1*UP*U7M1 * (  - 128*U1M1 )
     &+ M4*S4M1*S3M1*TP*U6M1 * (  - 128*T1M1 )
     &+ M4*S4M1*S3M1*U6M1*U7 * ( 64*U1M1 )
     &+ M4*S4M1*S3M1*U6M1*Q2 * ( 96*U1M1 )
     &+ M4*S4M1*S3M1*U6M1 * ( 64*T1*U1M1 )
     &+ M4*S4M1*S3M1*U6*U7M1 * ( 64*T1M1 )
     &+ M4*S4M1*S3M1*U7M1*Q2 * ( 32*T1M1 - 128*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M4*S4M1*S3*TPM1*U7M1 * (  - 48*T1M1 - 16*U1M1 )
     &+ M4*S4M1*S3*TPM1 * (  - 48*T1M1*U1M1 - 16*U1M2 )
     &+ M4*S4M1*S3*U6M1 * ( 64*T1M1*U1M1 + 32*U1M2 )
     &+ M4*S4M1*UP*TPM1*U7M1 * (  - 16*T1M1 - 48*U1M1 )
     &+ M4*S4M1*UP*TPM1 * ( 16*T1M1*U1M1 - 16*U1M2 )
     &+ M4*S4M1*UP*U6M1 * ( 96*T1M1*U1M1 + 32*U1M2 )
     &+ M4*S4M1*TPM1*U6*U7M1 * (  - 48*T1M1 - 48*U1M1 )
     &+ M4*S4M1*TPM1*U6 * (  - 48*T1M1*U1M1 - 48*U1M2 )
     &+ M4*S4M1*TPM1*U7M1*Q2 * (  - 16*T1M1 - 48*U1M1 )
     &+ M4*S4M1*TPM1*U7M1 * (  - 16 - 16*T1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M4*S4M1*TPM1*Q2 * ( 16*T1M1*U1M1 - 16*U1M2 )
     &+ M4*S4M1*TPM1 * (  - 16*T1*U1M2 - 16*U1M1 )
     &+ M4*S4M1*TP*U6M1 * ( 32*U1M2 )
     &+ M4*S4M1*U6M1*U7 * ( 64*T1M1*U1M1 + 32*U1M2 )
     &+ M4*S4M1*U6M1*Q2 * ( 192*T1M1*U1M1 + 128*U1M2 )
     &+ M4*S4M1*U6M1 * ( 32*T1*U1M2 - 32*U1M1 )
     &+ M4*S4M1*U7M1 * (  - 64*T1M1 - 64*U1M1 )
     &+ M4*S4M1 * (  - 64*T1M1*U1M1 - 32*U1M2 )
     &+ M4*S4*S3M1*TPM1*U6M1*U7M1 * (  - 48 )
     &+ M4*S4*S3M1*TPM1*U6M1 * (  - 48*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M4*S4*S3M1*TPM1*U7M2 * (  - 16 )
     &+ M4*S4*S3M1*TPM1*U7M1 * (  - 16*U1M1 )
     &+ M4*S4*S3M1*U6M1*U7M1 * ( 64*T1M1 )
     &+ M4*S4*S3M1*U7M2 * ( 32*T1M1 )
     &+ M4*S4*TPM1*U6M1*U7M1 * (  - 48*U1M1 )
     &+ M4*S4*TPM1*U6M1 * (  - 48*U1M2 )
     &+ M4*S4*TPM1*U7M2 * (  - 16*T1M1 )
     &+ M4*S4*TPM1*U7M1 * (  - 16*T1M1*U1M1 )
     &+ M4*S3M1*UP*TPM1*U6M1*U7M1 * ( 16 )
     &+ M4*S3M1*UP*TPM1*U6M1 * (  - 16*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M4*S3M1*UP*TPM1*U7M2 * (  - 16 )
     &+ M4*S3M1*UP*TPM1*U7M1 * (  - 48*U1M1 )
     &+ M4*S3M1*UP*U6M1*U7M1 * ( 96*T1M1 )
     &+ M4*S3M1*UP*U7M2 * ( 32*T1M1 )
     &+ M4*S3M1*TPM1*U6M1*U7M1*Q2 * ( 16 )
     &+ M4*S3M1*TPM1*U6M1*U7M1 * (  - 48*T1 )
     &+ M4*S3M1*TPM1*U6M1*Q2 * (  - 16*U1M1 )
     &+ M4*S3M1*TPM1*U6M1 * (  - 48*T1*U1M1 )
     &+ M4*S3M1*TPM1*U6*U7M2 * (  - 16 )
     &+ M4*S3M1*TPM1*U6*U7M1 * (  - 16*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M4*S3M1*TPM1*U7M2*Q2 * (  - 16 )
     &+ M4*S3M1*TPM1*U7M2 * (  - 48*T1 )
     &+ M4*S3M1*TPM1*U7M1*Q2 * (  - 48*U1M1 )
     &+ M4*S3M1*TPM1*U7M1 * (  - 16 - 48*T1*U1M1 )
     &+ M4*S3M1*TPM1 * (  - 16*U1M1 )
     &+ M4*S3M1*TP*U7M2 * ( 32*T1M1 )
     &+ M4*S3M1*U6M1*U7M1*Q2 * ( 128*T1M1 )
     &+ M4*S3M1*U6M1*U7M1 * (  - 64 )
     &+ M4*S3M1*U6M1 * (  - 64*U1M1 )
     &+ M4*S3M1*U6*U7M2 * ( 32*T1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M4*S3M1*U7M2*Q2 * ( 96*T1M1 )
     &+ M4*S3M1*U7M2 * (  - 32 )
     &+ M4*S3M1*U7M1 * (  - 32*T1M1 - 64*U1M1 )
     &+ M4*S3*TPM1*U6M1*U7M1 * (  - 16*U1M1 )
     &+ M4*S3*TPM1*U6M1 * (  - 16*U1M2 )
     &+ M4*S3*TPM1*U7M2 * (  - 48*T1M1 )
     &+ M4*S3*TPM1*U7M1 * (  - 48*T1M1*U1M1 )
     &+ M4*UP*TPM1*U6M1*U7M1 * ( 16*U1M1 )
     &+ M4*UP*TPM1*U6M1 * (  - 16*U1M2 )
     &+ M4*UP*TPM1*U7M2 * (  - 16*T1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M4*UP*TPM1*U7M1 * ( 16*T1M1*U1M1 )
     &+ M4*TPM1*U6M1*U7M1*Q2 * ( 16*U1M1 )
     &+ M4*TPM1*U6M1*U7M1 * (  - 16 - 16*T1*U1M1 )
     &+ M4*TPM1*U6M1*Q2 * (  - 16*U1M2 )
     &+ M4*TPM1*U6M1 * (  - 16*T1*U1M2 - 16*U1M1 )
     &+ M4*TPM1*U6*U7M2 * (  - 16*T1M1 )
     &+ M4*TPM1*U6*U7M1 * (  - 16*T1M1*U1M1 )
     &+ M4*TPM1*U7M2*Q2 * (  - 16*T1M1 )
     &+ M4*TPM1*U7M2 * ( 32 )
     &+ M4*TPM1*U7M1*Q2 * ( 16*T1M1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M4*TPM1*U7M1 * (  - 16*T1M1 + 64*U1M1 )
     &+ M4*TPM1 * (  - 16*T1M1*U1M1 + 32*U1M2 )
     &+ M4*U6M1*U7M1 * (  - 64*U1M1 )
     &+ M4*U6M1 * (  - 32*U1M2 )
     &+ M4*U7M2 * (  - 32*T1M1 )
     &+ M4*U7M1 * (  - 64*T1M1*U1M1 )
     &+ M6*S4M1*S3M1*U6M1 * (  - 128*T1M1 - 128*U1M1 )
     &+ M6*S4M1*S3M1*U7M1 * (  - 128*T1M1 - 128*U1M1 )
     &+ M6*S4M1*U6M1 * (  - 128*T1M1*U1M1 - 128*U1M2 )
     &+ M6*S3M1*U6M1*U7M1 * (  - 128*T1M1 )
        FGGC_CACF = FGGC_CACF
     &+ M6*S3M1*U7M2 * (  - 128*T1M1 )
     &+ M6*U6M1*U7M1 * (  - 128*T1M1*U1M1 )
     &+ SP*S5*S4M1*S3*TPM1*U7M1 * (  - 4*T1M1 )
     &+ SP*S5*S4M1*S3*TPM1 * ( 4*T1M1*U1M1 )
     &+ SP*S5*S4M1*S3*U6M1 * ( 8*T1M1*U1M1 )
     &+ SP*S5*S4M1*TPM1*U6*U7M1 * ( 4*T1M1 )
     &+ SP*S5*S4M1*TPM1*U6 * (  - 8*T1M1*U1M1 )
     &+ SP*S5*S4M1*U6M1 * (  - 8*U1M1 )
     &+ SP*S5*S4M1*U7M1 * (  - 8*T1M1 )
     &+ SP*S5*S4M1 * (  - 8*T1M1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ SP*S5*S4*S3M1*TPM1*U6M1*U7M1 * ( 4 )
     &+ SP*S5*S4*S3M1*TPM1*U6M1 * (  - 4*U1M1 )
     &+ SP*S5*S4*S3M1*U6M1*U7M1 * ( 8*T1M1 )
     &+ SP*S5*S4*TPM2*U7M1 * (  - 16*U1M1 )
     &+ SP*S5*S4*TPM1*U7M1 * (  - 4*T1M1*U1M1 )
     &+ SP*S5*S3M1*TPM1*U6M1*U7M1 * (  - 8*T1 )
     &+ SP*S5*S3M1*TPM1*U6M1 * ( 4*T1*U1M1 )
     &+ SP*S5*S3M1*U6M1*U7M1 * (  - 8 )
     &+ SP*S5*S3M1*U6M1 * (  - 8*U1M1 )
     &+ SP*S5*S3M1*U7M1 * (  - 8*T1M1 )
        FGGC_CACF = FGGC_CACF
     &+ SP*S5*S3*TPM2*U7M1 * (  - 16*U1M1 )
     &+ SP*S5*S3*TPM1*U6M1*U7M1 * (  - 4*U1M1 )
     &+ SP*S5*TPM1*U6M1*U7M1 * (  - 4 + 4*T1*U1M1 )
     &+ SP*S5*TPM1*U6*U7M1 * ( 4*T1M1*U1M1 )
     &+ SP*S5*TPM1 * (  - 4*T1M1*U1M1 )
     &+ SP*S52*S4M1*S3M1*U6M1 * (  - 8*U1M1 )
     &+ SP*S52*S4M1*S3M1*U7M1 * (  - 8*T1M1 )
     &+ SP*S52*S4M1*TPM1*U7M1 * (  - 4*T1M1 )
     &+ SP*S52*S4M1*TPM1 * ( 4*T1M1*U1M1 )
     &+ SP*S52*S4M1*U6M1 * ( 8*T1M1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ SP*S52*S3M1*TPM1*U6M1*U7M1 * ( 4 )
     &+ SP*S52*S3M1*TPM1*U6M1 * (  - 4*U1M1 )
     &+ SP*S52*S3M1*U6M1*U7M1 * ( 8*T1M1 )
     &+ SP*S52*TPM1*U6M1*U7M1 * ( 8*U1M1 )
     &+ SP*S52*TPM1*U7M1 * ( 8*T1M1*U1M1 )
     &+ SP*S4M1*S3*TPM1*U6*U7M1 * ( 4*T1M1 )
     &+ SP*S4*S3M1*TPM1*U6M1 * ( 4*T1*U1M1 )
     &+ SP*S4*TPM2*Q2 * (  - 16*U1M2 )
     &+ SP*S4*TPM2 * (  - 16*U1M1 )
     &+ SP*S4*TPM1*U6M1*U7M1 * (  - 12 )
        FGGC_CACF = FGGC_CACF
     &+ SP*S4*TPM1*U6M1*Q2 * ( 4*U1M2 )
     &+ SP*S4*TPM1*U6M1 * ( 4*U1M1 )
     &+ SP*S3*TPM2*U7M2*Q2 * (  - 16 )
     &+ SP*S3*TPM2*U7M1 * (  - 16 )
     &+ SP*S3*TPM1*U7M2*Q2 * ( 4*T1M1 )
     &+ SP*S3*TPM1*U7M1 * ( 4*T1M1 )
     &+ SP*S3*TPM1 * (  - 12*T1M1*U1M1 )
     &+ SP*TPM1*U7M2*Q2 * (  - 4 )
     &+ SP*TPM1*U7M1 * ( 4 )
     &+ SP*TPM1*Q2 * (  - 4*U1M2 )
        FGGC_CACF = FGGC_CACF
     &+ SP*TPM1 * ( 4*U1M1 )
     &+ U1P*S5*S4M1*S3M1*TP*U7M1 * ( 8*T1M1 )
     &+ U1P*S5*S4M1*S3M1*U6*U7M1 * ( 8*T1M1 )
     &+ U1P*S5*S4M1*TPM1*U6*U7M1 * ( 4*T1M1 )
     &+ U1P*S5*S4M1*U7M1 * ( 4*T1M1 )
     &+ U1P*S5*S4*S3M1*TPM1*U6M1*U7M1 * ( 4 )
     &+ U1P*S5*S4*S3M1*U6M1*U7M1 * ( 8*T1M1 )
     &+ U1P*S5*S3M1*TPM1*U7M1 * (  - 4 )
     &+ U1P*S5*S3M1*TP*U6M1*U7M1 * ( 8*T1M1 )
     &+ U1P*S5*S3M1*U6M1*U7M1 * ( 4 )
        FGGC_CACF = FGGC_CACF
     &+ U1P*S5*S3M1*U7M1 * (  - 16*T1M1 )
     &+ U1P*S5*TPM1*U7M1 * (  - 4*T1M1 )
     &+ U1P*S4M1*TPM1*U62*U7M1 * (  - 4*T1M1 )
     &+ U1P*S4M1*U6*U7M1 * (  - 4*T1M1 )
     &+ U1P*S4*S3M1*TPM1*U7M1 * (  - 4 )
     &+ U1P*S4*S3M1*U6M1*U7M1 * (  - 4 )
     &+ U1P*S42*S3M1*TPM1*U6M1*U7M1 * (  - 4 )
     &+ U1P*S3M1*TPM1*U7M2*Q2 * ( 16*T1 )
     &+ U1P*S3M1*TPM1*U7M1 * ( 16*T1 )
     &+ U1P*S3M1*TP*U7M2*Q2 * ( 16*T1M1 )
        FGGC_CACF = FGGC_CACF
     &+ U1P*S3M1*TP*U7M1 * ( 16*T1M1 )
     &+ U1P*S3M1*U7M2*Q2 * ( 28 )
     &+ U1P*S3M1*U7M1 * ( 20 )
     &+ U1P*S3*TPM1*U7M2*Q2 * ( 16*T1M1 )
     &+ U1P*S3*TPM1*U7M1 * ( 16*T1M1 )
     &+ U1P*TPM1*U6*U7M1 * (  - 4*T1M1 )
     &+ U1P*TPM1*U7M2*Q2 * ( 16 )
     &+ U1P*TPM1*U7M1 * ( 16 )
     &+ U1P*U7M2*Q2 * ( 28*T1M1 )
     &+ U1P*U7M1 * ( 20*T1M1 )
        FGGC_CACF = FGGC_CACF
     &+ S5*S4M1*S3M1*UP*U6M1 * ( 8*T1*U1M1 )
     &+ S5*S4M1*S3M1*UP*U6*U7M1 * ( 8*T1M1 )
     &+ S5*S4M1*S3M1*TP*U6M1*U7 * ( 8*U1M1 )
     &+ S5*S4M1*S3M1*TP*U6M1*Q2 * ( 8*U1M1 )
     &+ S5*S4M1*S3M1*U6M1*U7 * ( 8*T1*U1M1 )
     &+ S5*S4M1*S3M1*U6M1*Q2 * ( 16*T1*U1M1 )
     &+ S5*S4M1*S3M1*U6*U7M1*Q2 * ( 8*T1M1 )
     &+ S5*S4M1*S3M1*U7M1*Q2 * ( 8 )
     &+ S5*S4M1*S3M1*Q2 * ( 8*U1M1 )
     &+ S5*S4M1*S3M1 * ( 16 )
        FGGC_CACF = FGGC_CACF
     &+ S5*S4M1*S3*UP*TPM1*U7M1 * (  - 8*T1M1 + 4*U1M1 )
     &+ S5*S4M1*S3*UP*TPM1 * ( 4*T1M1*U1M1 )
     &+ S5*S4M1*S3*TPM1*U6*U7M1 * (  - 4*T1M1 + 4*U1M1 )
     &+ S5*S4M1*S3*TPM1*U6 * (  - 4*T1M1*U1M1 )
     &+ S5*S4M1*S3*TPM1*U7M1*Q2 * (  - 20*T1M1 - 4*U1M1 )
     &+ S5*S4M1*S3*TPM1*U7 * ( 4*T1M1*U1M1 )
     &+ S5*S4M1*S3*TPM1*Q2 * ( 8*T1M1*U1M1 )
     &+ S5*S4M1*S3*TPM1 * (  - 12*T1M1 - 8*U1M1 )
     &+ S5*S4M1*S3*U6M1*U7 * ( 8*T1M1*U1M1 )
     &+ S5*S4M1*S3*U6M1*Q2 * ( 8*T1M1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ S5*S4M1*S3 * (  - 12*T1M1*U1M1 )
     &+ S5*S4M1*UP*TPM1*U6*U7M1 * ( 4*T1M1 )
     &+ S5*S4M1*UP*TPM1*U6 * (  - 4*T1M1*U1M1 )
     &+ S5*S4M1*UP*TPM1*U7M1 * (  - 4 - 4*T1*U1M1 )
     &+ S5*S4M1*UP*U6M1 * (  - 8*U1M1 )
     &+ S5*S4M1*UP*U7M1 * (  - 8*T1M1 )
     &+ S5*S4M1*UP * (  - 8*T1M1*U1M1 )
     &+ S5*S4M1*TPM1*U6*U7M1*Q2 * ( 4*T1M1 )
     &+ S5*S4M1*TPM1*U6*U7M1 * ( 16 )
     &+ S5*S4M1*TPM1*U6*Q2 * (  - 16*T1M1*U1M1 + 16*U1M2 )
        FGGC_CACF = FGGC_CACF
     &+ S5*S4M1*TPM1*U6 * (  - 12*T1M1 + 8*U1M1 )
     &+ S5*S4M1*TPM1*U7M1*Q2 * (  - 8 - 4*T1*U1M1 )
     &+ S5*S4M1*TPM1*U7 * (  - 4*U1M1 )
     &+ S5*S4M1*TPM1*Q2 * (  - 4*U1M1 )
     &+ S5*S4M1*TPM1 * (  - 4 )
     &+ S5*S4M1*TP*U6M1*U7 * ( 8*T1M1*U1M1 )
     &+ S5*S4M1*TP*U6M1*Q2 * ( 8*T1M1*U1M1 + 16*U1M2 )
     &+ S5*S4M1*U6M1*U7 * (  - 16*U1M1 )
     &+ S5*S4M1*U6M1*Q2 * (  - 24*U1M1 )
     &+ S5*S4M1*U6M1 * (  - 16 )
        FGGC_CACF = FGGC_CACF
     &+ S5*S4M1*U6*U7M1 * (  - 12*T1M1 )
     &+ S5*S4M1*U7M1*Q2 * (  - 24*T1M1 + 4*U1M1 )
     &+ S5*S4M1*U7M1 * (  - 4 )
     &+ S5*S4M1*U7 * ( 4*T1M1*U1M1 )
     &+ S5*S4M1*Q2 * (  - 20*T1M1*U1M1 + 28*U1M2 )
     &+ S5*S4M1 * (  - 48*T1M1 - 20*U1M1 )
     &+ S5*S4*S3M1*UP*TPM1*U6M1*U7M1 * ( 4 )
     &+ S5*S4*S3M1*UP*TPM1*U6M1 * (  - 8*U1M1 )
     &+ S5*S4*S3M1*UP*TPM1*U7M1 * ( 4*U1M1 )
     &+ S5*S4*S3M1*TPM1*U6M1*U7M1*Q2 * ( 4 )
        FGGC_CACF = FGGC_CACF
     &+ S5*S4*S3M1*TPM1*U6M1*U7M1 * (  - 4*T1 )
     &+ S5*S4*S3M1*TPM1*U6M1*Q2 * (  - 20*U1M1 )
     &+ S5*S4*S3M1*TPM1*U6M1 * (  - 12 - 4*T1*U1M1 )
     &+ S5*S4*S3M1*TPM1*U7M1*Q2 * (  - 4*U1M1 )
     &+ S5*S4*S3M1*TPM1*U7M1 * (  - 8 + 4*T1*U1M1 )
     &+ S5*S4*S3M1*U6M1*U7M1 * (  - 12 )
     &+ S5*S4*TPM2*U7M1 * (  - 32*T1*U1M1 )
     &+ S5*S4*TPM1*U6M1*U7M1 * ( 16 + 4*T1*U1M1 )
     &+ S5*S4*TPM1*U6M1*Q2 * ( 16*U1M2 )
     &+ S5*S4*TPM1*U6M1 * ( 8*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ S5*S4*TPM1*U7M1 * (  - 4*U1M1 )
     &+ S5*S3M1*UP*TPM1*U6M1*U7M1 * (  - 4*T1 )
     &+ S5*S3M1*UP*TPM1*U6M1 * ( 4*T1*U1M1 )
     &+ S5*S3M1*UP*TPM1*U6*U7M1 * (  - 4*U1M1 )
     &+ S5*S3M1*UP*TPM1 * (  - 4*U1M1 )
     &+ S5*S3M1*UP*U6M1*U7M1 * (  - 8 )
     &+ S5*S3M1*UP*U6M1 * (  - 8*U1M1 )
     &+ S5*S3M1*UP*U7M1 * (  - 8*T1M1 )
     &+ S5*S3M1*TPM1*U6M1*U7M1*Q2 * (  - 16*T1 )
     &+ S5*S3M1*TPM1*U6M1*U7 * ( 4*T1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ S5*S3M1*TPM1*U6M1*Q2 * ( 8*T1*U1M1 )
     &+ S5*S3M1*TPM1*U6M1 * (  - 12*T1 )
     &+ S5*S3M1*TPM1*U6*U7M1*Q2 * (  - 4*U1M1 )
     &+ S5*S3M1*TPM1*U7M2*Q2 * ( 16*T1 )
     &+ S5*S3M1*TPM1*U7M1 * ( 8*T1 )
     &+ S5*S3M1*TPM1*Q2 * (  - 8*U1M1 )
     &+ S5*S3M1*TPM1 * (  - 4 + 16*T1*U1M1 )
     &+ S5*S3M1*TP*U7M2*Q2 * ( 16*T1M1 )
     &+ S5*S3M1*U6M1*U7M1*Q2 * (  - 24 )
     &+ S5*S3M1*U6M1*U7 * ( 4*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ S5*S3M1*U6M1*Q2 * (  - 20*U1M1 )
     &+ S5*S3M1*U6M1 * (  - 48 - 12*T1*U1M1 )
     &+ S5*S3M1*U7M2*Q2 * ( 28 )
     &+ S5*S3M1*U7M1*Q2 * (  - 8*T1M1 + 4*U1M1 )
     &+ S5*S3M1*U7M1 * (  - 20 )
     &+ S5*S3M1 * (  - 16*T1M1 - 4*U1M1 )
     &+ S5*S3*TPM2*U6*U7M1 * (  - 32*U1M1 )
     &+ S5*S3*TPM1*U6*U7M1 * ( 4*T1M1*U1M1 )
     &+ S5*S3*TPM1*U7M2*Q2 * ( 16*T1M1 )
     &+ S5*S3*TPM1*U7M1 * ( 8*T1M1 - 4*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ S5*S3*TPM1 * ( 16*T1M1*U1M1 )
     &+ S5*UP*TPM2*U6*U7M1 * (  - 16*U1M1 )
     &+ S5*UP*TPM2*U7M1 * (  - 16*T1*U1M1 )
     &+ S5*TPM2*U6*U7M1*Q2 * (  - 16*U1M1 )
     &+ S5*TPM2*U7M1*Q2 * (  - 16*T1*U1M1 )
     &+ S5*TPM1*U6M1*U7M1*Q2 * (  - 4 - 8*T1*U1M1 )
     &+ S5*TPM1*U6M1*U7 * (  - 4*U1M1 )
     &+ S5*TPM1*U6M1*Q2 * (  - 4*U1M1 )
     &+ S5*TPM1*U6M1 * (  - 4 - 8*T1*U1M1 )
     &+ S5*TPM1*U6*U7M1*Q2 * (  - 8*T1M1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ S5*TPM1*U6*U7M1 * (  - 8*T1M1 - 4*U1M1 )
     &+ S5*TPM1*U7M2*Q2 * ( 16 )
     &+ S5*TPM1*U7M1*Q2 * ( 64*U1M1 )
     &+ S5*TPM1*U7M1 * ( 8 - 4*T1*U1M1 )
     &+ S5*TPM1*Q2 * (  - 4*T1M1*U1M1 + 16*U1M2 )
     &+ S5*TPM1 * (  - 4*T1M1 + 8*U1M1 )
     &+ S5*U6M1*U7M1*Q2 * ( 8*T1M1 + 4*U1M1 )
     &+ S5*U6M1*U7M1 * (  - 4 )
     &+ S5*U6M1*Q2 * ( 8*T1M1*U1M1 + 28*U1M2 )
     &+ S5*U6M1 * ( 16*T1M1 - 20*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ S5*U7M2*Q2 * ( 28*T1M1 )
     &+ S5*U7M1*Q2 * ( 4*T1M1*U1M1 )
     &+ S5*U7M1 * (  - 20*T1M1 )
     &+ S5 * (  - 4*T1M1*U1M1 )
     &+ S52*S4M1*S3M1*UP*U6M1 * ( 8*U1M1 )
     &+ S52*S4M1*S3M1*UP*U7M1 * ( 8*T1M1 )
     &+ S52*S4M1*S3M1*TP*U6M1 * ( 8*U1M1 )
     &+ S52*S4M1*S3M1*TP*U7M1 * ( 8*T1M1 )
     &+ S52*S4M1*S3M1*U6M1*Q2 * ( 8*U1M1 )
     &+ S52*S4M1*S3M1*U6M1 * (  - 16 )
        FGGC_CACF = FGGC_CACF
     &+ S52*S4M1*S3M1*U7M1*Q2 * ( 8*T1M1 )
     &+ S52*S4M1*S3M1*U7M1 * (  - 16 )
     &+ S52*S4M1*S3M1 * (  - 16*T1M1 - 16*U1M1 )
     &+ S52*S4M1*UP*TPM1*U7M1 * ( 4*T1M1 + 8*U1M1 )
     &+ S52*S4M1*UP*TPM1 * (  - 4*T1M1*U1M1 )
     &+ S52*S4M1*UP*U6M1 * (  - 8*T1M1*U1M1 )
     &+ S52*S4M1*TPM1*U6*U7M1 * ( 16*U1M1 )
     &+ S52*S4M1*TPM1*U7M1*Q2 * ( 4*T1M1 + 8*U1M1 )
     &+ S52*S4M1*TPM1*Q2 * (  - 4*T1M1*U1M1 )
     &+ S52*S4M1*TP*U6M1 * ( 8*T1M1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ S52*S4M1*U6M1*Q2 * (  - 8*T1M1*U1M1 )
     &+ S52*S4M1*U6M1 * (  - 16*T1M1 )
     &+ S52*S4M1*U7M1 * ( 4*T1M1 - 4*U1M1 )
     &+ S52*S4M1 * ( 4*T1M1*U1M1 )
     &+ S52*S4*TPM1*U6M1*U7M1 * ( 16*U1M1 )
     &+ S52*S3M1*UP*TPM1*U6M1*U7M1 * (  - 4 )
     &+ S52*S3M1*UP*TPM1*U6M1 * ( 4*U1M1 )
     &+ S52*S3M1*UP*TPM1*U7M1 * ( 8*U1M1 )
     &+ S52*S3M1*UP*U6M1*U7M1 * (  - 8*T1M1 )
     &+ S52*S3M1*TPM1*U6M1*U7M1*Q2 * (  - 4 )
        FGGC_CACF = FGGC_CACF
     &+ S52*S3M1*TPM1*U6M1*Q2 * ( 4*U1M1 )
     &+ S52*S3M1*TPM1*U7M1*Q2 * ( 8*U1M1 )
     &+ S52*S3M1*TPM1*U7M1 * ( 16*T1*U1M1 )
     &+ S52*S3M1*TP*U6M1*U7M1 * ( 8*T1M1 )
     &+ S52*S3M1*U6M1*U7M1*Q2 * (  - 8*T1M1 )
     &+ S52*S3M1*U6M1*U7M1 * ( 4 )
     &+ S52*S3M1*U6M1 * (  - 16*T1M1 + 4*U1M1 )
     &+ S52*S3M1*U7M1 * (  - 4*U1M1 )
     &+ S52*S3*TPM1*U7M1 * ( 16*T1M1*U1M1 )
     &+ S52*TPM1*U7M1 * ( 32*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ S52*U6M1*U7M1 * (  - 16*T1M1 - 4*U1M1 )
     &+ S52*U6M1 * (  - 16*T1M1*U1M1 )
     &+ S52*U7M1 * (  - 4*T1M1*U1M1 )
     &+ S53*S4M1*S3M1*U6M1 * (  - 16*T1M1 )
     &+ S53*S4M1*S3M1*U7M1 * (  - 16*U1M1 )
     &+ S53*U6M1*U7M1 * (  - 16*T1M1*U1M1 )
     &+ S4M1*S3*UP*TPM1*U6 * ( 4*T1M1*U1M1 )
     &+ S4M1*S3*TPM1*U6*U7M1*Q2 * (  - 4*T1M1 - 4*U1M1 )
     &+ S4M1*S3*TPM1*U6*U7M1 * ( 4 )
     &+ S4M1*S3*TPM1*U6*Q2 * ( 4*U1M2 )
        FGGC_CACF = FGGC_CACF
     &+ S4M1*S3*TPM1*U6 * (  - 8*T1M1 + 4*U1M1 )
     &+ S4M1*S3*TPM1*U62*U7M1 * ( 4*T1M1 )
     &+ S4M1*S3*TPM1*U7M1*Q2 * ( 4*T1*U1M1 )
     &+ S4M1*S3*TPM1*U7 * (  - 4*U1M1 )
     &+ S4M1*S3*TPM1*Q2 * (  - 4*U1M1 )
     &+ S4M1*S3*TPM1 * ( 4*T1*U1M1 )
     &+ S4M1*S3*U7 * (  - 4*T1M1*U1M1 )
     &+ S4M1*S3*Q2 * (  - 12*T1M1*U1M1 )
     &+ S4M1*S3 * (  - 8*T1M1 )
     &+ S4M1*S32*TPM1*U6 * ( 4*T1M1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ S4M1*S32*TPM1*U7M1*Q2 * (  - 4*U1M1 )
     &+ S4M1*S32*TPM1*U7 * (  - 4*T1M1*U1M1 )
     &+ S4M1*S32*TPM1*Q2 * (  - 4*T1M1*U1M1 )
     &+ S4M1*S32*TPM1 * (  - 4*U1M1 )
     &+ S4M1*UP*TPM1*U6*U7M1 * (  - 12 )
     &+ S4M1*UP*TPM1*U6*Q2 * ( 4*U1M2 )
     &+ S4M1*UP*TPM1*U6 * ( 4*U1M1 )
     &+ S4M1*TPM1*U6*U7M1*Q2 * (  - 24 )
     &+ S4M1*TPM1*U6*U7*Q2 * ( 16*U1M2 )
     &+ S4M1*TPM1*U6*U7 * ( 16*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ S4M1*TPM1*U6*Q2 * ( 20*U1M1 )
     &+ S4M1*TPM1*U6*Q4 * ( 20*U1M2 )
     &+ S4M1*TPM1*U6 * (  - 12 )
     &+ S4M1*TP*U6M1*U7*Q2 * ( 16*U1M2 )
     &+ S4M1*TP*U6M1*U7 * ( 16*U1M1 )
     &+ S4M1*TP*U6M1*Q2 * ( 16*U1M1 )
     &+ S4M1*TP*U6M1*Q4 * ( 16*U1M2 )
     &+ S4M1*U6*U7M1*Q2 * (  - 8*T1M1 )
     &+ S4M1*U6 * (  - 8*T1M1 )
     &+ S4M1*U7M1*Q2 * ( 8 )
        FGGC_CACF = FGGC_CACF
     &+ S4M1*U7*Q2 * ( 28*U1M2 )
     &+ S4M1*U7 * ( 20*U1M1 )
     &+ S4M1*Q2 * ( 28*U1M1 )
     &+ S4M1*Q4 * ( 28*U1M2 )
     &+ S4M1 * ( 16 )
     &+ S4*S3M1*UP*TPM1*U6M1*U7M1 * ( 4*T1 )
     &+ S4*S3M1*TPM1*U6M1*Q2 * (  - 4*T1*U1M1 )
     &+ S4*S3M1*TPM1*U6M1 * (  - 8*T1 + 4*T12*U1M1 )
     &+ S4*S3M1*TPM1*U6*U7M1*Q2 * ( 4*U1M1 )
     &+ S4*S3M1*TPM1*U6*U7M1 * ( 4 )
        FGGC_CACF = FGGC_CACF
     &+ S4*S3M1*TPM1*U7M2*Q2 * ( 4*T1 )
     &+ S4*S3M1*TPM1*U7M1*Q2 * (  - 4*T1*U1M1 )
     &+ S4*S3M1*TPM1*U7M1 * ( 4*T1 )
     &+ S4*S3M1*TPM1 * ( 4*T1*U1M1 )
     &+ S4*S3M1*U6M1*U7M1*Q2 * (  - 8 )
     &+ S4*S3M1*U6M1 * (  - 8 )
     &+ S4*TPM2*U6*U7M1*Q2 * ( 32*U1M1 )
     &+ S4*TPM2*U6*U7M1 * ( 32 )
     &+ S4*TPM2*U7M2*Q2 * (  - 16*T1 )
     &+ S4*TPM2*U7M1*Q2 * (  - 32*T1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ S4*TPM2*U7M1 * (  - 16*T1 )
     &+ S4*TPM2*Q2 * (  - 16*T1*U1M2 )
     &+ S4*TPM2 * (  - 16*T1*U1M1 )
     &+ S4*TPM1*U6M1*U7M1*Q2 * (  - 12 - 4*T1*U1M1 )
     &+ S4*TPM1*U6M1*U7M1 * ( 4*T1 )
     &+ S4*TPM1*U6M1*U7*Q2 * ( 16*U1M2 )
     &+ S4*TPM1*U6M1*U7 * ( 16*U1M1 )
     &+ S4*TPM1*U6M1*Q2 * ( 4*T1*U1M2 + 16*U1M1 )
     &+ S4*TPM1*U6M1*Q4 * ( 16*U1M2 )
     &+ S4*TPM1*U6M1 * (  - 12 + 4*T1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ S4*TPM1*U6*U7M1*Q2 * ( 4*T1M1*U1M1 )
     &+ S4*TPM1*U6*U7M1 * ( 4*T1M1 )
     &+ S4*TPM1*U7M2*Q2 * (  - 4 )
     &+ S4*TPM1*U7M1*Q2 * ( 4*U1M1 )
     &+ S4*TPM1*U7M1 * (  - 8 )
     &+ S4*TPM1 * (  - 4*U1M1 )
     &+ S42*S3M1*TPM1*U6M1*U7M1 * ( 4*T1 )
     &+ S42*S3M1*TPM1*U7M1*Q2 * (  - 4*U1M1 )
     &+ S42*S3M1*TPM1*U7M1 * (  - 4 )
     &+ S3M1*UP*TPM1*U7M2*Q2 * ( 4*T1 )
        FGGC_CACF = FGGC_CACF
     &+ S3M1*UP*TPM1*U7M1 * ( 4*T1 )
     &+ S3M1*UP*TPM1 * (  - 12*T1*U1M1 )
     &+ S3M1*TPM1*U6M1*U7 * (  - 4*T12*U1M1 )
     &+ S3M1*TPM1*U6M1*Q2 * (  - 4*T12*U1M1 )
     &+ S3M1*TPM1*U7M2*Q4 * ( 4*T1 )
     &+ S3M1*TPM1*U7M1*Q2 * ( 4*T1 )
     &+ S3M1*TPM1*Q2 * (  - 24*T1*U1M1 )
     &+ S3M1*TPM1 * (  - 12*T1 )
     &+ S3M1*U6M1*U7 * (  - 4*T1*U1M1 )
     &+ S3M1*U6M1*Q2 * (  - 12*T1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ S3M1*U6M1 * (  - 8*T1 )
     &+ S3M1*U7M1*Q2 * ( 8 )
     &+ S3M1*Q2 * ( 8*U1M1 )
     &+ S3M1 * ( 16 )
     &+ S3*TPM2*U6*U7M2*Q2 * (  - 16 )
     &+ S3*TPM2*U6*U7M1*Q2 * (  - 32*U1M1 )
     &+ S3*TPM2*U6*U7M1 * (  - 16 )
     &+ S3*TPM2*U6*Q2 * (  - 16*U1M2 )
     &+ S3*TPM2*U6 * (  - 16*U1M1 )
     &+ S3*TPM2*U7M1*Q2 * ( 32*T1*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ S3*TPM2 * ( 32*T1*U1M1 )
     &+ S3*TPM1*U6M1*U7M1*Q2 * ( 4*T1*U1M1 )
     &+ S3*TPM1*U6M1 * ( 4*T1*U1M1 )
     &+ S3*TPM1*U6*U7M2*Q2 * ( 4*T1M1 )
     &+ S3*TPM1*U6*U7M1*Q2 * (  - 4*T1M1*U1M1 )
     &+ S3*TPM1*U6*U7M1 * ( 4*T1M1 )
     &+ S3*TPM1*U6 * ( 4*T1M1*U1M1 )
     &+ S3*TPM1*U7M1*Q2 * ( 4*U1M1 )
     &+ S3*TPM1*U7M1 * (  - 4 )
     &+ S3*TPM1*Q2 * (  - 12*T1M1*U1M1 - 4*U1M2 )
        FGGC_CACF = FGGC_CACF
     &+ S3*TPM1 * (  - 12*T1M1 - 8*U1M1 )
     &+ UP*TPM2*U6*Q2 * (  - 16*U1M2 )
     &+ UP*TPM2*U6 * (  - 16*U1M1 )
     &+ UP*TPM2*U7M2*Q2 * (  - 16*T1 )
     &+ UP*TPM2*U7M1 * (  - 16*T1 )
     &+ UP*TPM1*U7M2*Q2 * (  - 4 )
     &+ UP*TPM1*U7M1 * ( 4 )
     &+ UP*TPM1*Q2 * (  - 4*U1M2 )
     &+ UP*TPM1 * ( 4*U1M1 )
     &+ TPM2*U6*Q2 * (  - 16*U1M1 )
        FGGC_CACF = FGGC_CACF
     &+ TPM2*U6*Q4 * (  - 16*U1M2 )
     &+ TPM2*U7M2*Q4 * (  - 16*T1 )
     &+ TPM2*U7M1*Q2 * (  - 16*T1 )
     &+ TPM1*U6M1*U7M1*Q2 * (  - 4*T12*U1M1 )
     &+ TPM1*U6M1*U7 * (  - 4*T1*U1M1 )
     &+ TPM1*U6M1*Q2 * (  - 4*T1*U1M1 )
     &+ TPM1*U6M1 * (  - 4*T12*U1M1 )
     &+ TPM1*U6*U7M2*Q2 * (  - 4 )
     &+ TPM1*U6*U7M1*Q2 * ( 4*U1M1 )
     &+ TPM1*U6*U7M1 * (  - 8 )
        FGGC_CACF = FGGC_CACF
     &+ TPM1*U6 * (  - 4*U1M1 )
     &+ TPM1*U62*U7M1*Q2 * (  - 4*T1M1*U1M1 )
     &+ TPM1*U62*U7M1 * (  - 4*T1M1 )
     &+ TPM1*U7M2*Q4 * (  - 4 )
     &+ TPM1*U7M1*Q2 * ( 20 + 4*T1*U1M1 )
     &+ TPM1*U7M1 * (  - 4*T1 )
     &+ TPM1*U7*Q2 * ( 16*U1M2 )
     &+ TPM1*U7 * ( 16*U1M1 )
     &+ TPM1*Q2 * (  - 4*T1*U1M2 + 36*U1M1 )
     &+ TPM1*Q4 * ( 12*U1M2 )
        FGGC_CACF = FGGC_CACF
     &+ TPM1 * ( 32 - 8*T1*U1M1 )
     &+ U6M1*U7M1*Q2 * ( 8 )
     &+ U6M1*U7*Q2 * ( 28*U1M2 )
     &+ U6M1*U7 * ( 20*U1M1 )
     &+ U6M1*Q2 * ( 28*U1M1 )
     &+ U6M1*Q4 * ( 28*U1M2 )
     &+ U6M1 * ( 16 )
     &+ U7M1*Q2 * ( 8*T1M1 )
     &+ Q2 * ( 8*T1M1*U1M1 )
     &+ 16*T1M1

        FGGC_CACF = FGGC_CACF*TP*(UP+Q2*S5/S)

      END IF

      RETURN
      END
      FUNCTION FGGC_CFCF
     &         (X,Y,M2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DP,DM)
C
C THIS IS THE CF*CF TERM OF FGGC IN 3 CASES
C 1) SOFT LIMIT
C 2) COLLINEAR LIMIT
C 3) HARD
C
C LIMITS CHECK UNDER THETA2 INTEGRATION: 11/23/94
C LIMITS CHECK W/O   THETA2 INTEGRATION: 3/2/95
C
C IT IS TP*(UP+Q2*S5/S) M^G_G(3) OF THE PAPER
C THERE IS AN OVERALL FACTOR OF  G^4 EH^2 N CF CF UNDERSTOOD
C
      IMPLICIT DOUBLE PRECISION (A-Z)
      PARAMETER (DELTAS=1.0D-5)
      PARAMETER (DELTAC=1.0D-7)

      ONEMX = 1.D0 - X
      ONEPY = 1.D0 + Y
      ONEMY = 1.D0 - Y

      IF ( ONEMX.LT.DELTAS ) THEN
C (1-Y*Y)*(1-X)**2*(P1P2)*SP**2
        P1 = +8.D0*(S-2.D0*M2)*ONEMY*ONEPY/DP/DM
C (1-Y*Y)*(1-X)**2*(P1P1)*SP**2
        P2 = +16.D0*M2*ONEMY*ONEPY/DM/DM
C (1-Y*Y)*(1-X)**2*(P2P2)*SP**2
        P3 = +16.D0*M2*ONEMY*ONEPY/DP/DP
        RSPS2 = (SP/S)**2
        FGGC_CFCF = 2.D0*RSPS2*BGQED(T1,SP,M2,Q2)*(2.D0*P1-P2-P3)
      ELSE IF ( ONEPY.LT.DELTAC ) THEN
        FGGC_CFCF = 0.D0
      ELSE
        M4 = M2*M2
        M6 = M4*M2
        Q4 = Q2*Q2
        Q6 = Q2*Q4
        S52 = S5*S5
        S53 = S5*S52
        S42 = S4*S4
        S4M1 = 1.D0/S4
        S4M2 = S4M1*S4M1
        S32 = S3*S3
        S3M1 = 1.D0/S3
        S3M2 = S3M1*S3M1
        SM1 = 1.D0/S
        SP2 = SP*SP
        U62 = U6*U6
        U63 = U6*U62
        U6M1 = 1.D0/U6
        U6M2 = U6M1*U6M1
        U7M1 = 1.D0/U7
        U7M2 = U7M1*U7M1
        TP2 = TP*TP
        TP3 = TP*TP2
        TPM1 = 1.D0/TP
        TPM2 = TPM1*TPM1
        UP2 = UP*UP
        UP3 = UP*UP2
        T12 = T1*T1
        T13 = T1*T12
        T1M1 = 1.D0/T1
        T1M2 = T1M1*T1M1
        U1M1 = 1.D0/U1
        U1M2 = U1M1*U1M1
        U1P = U1+Q2
        U1P2 = U1P*U1P

        FGGC_CFCF =
     &+ M2*SP*S5*S4M2 * ( 64*T1M1*U1M1 )
     &+ M2*SP*S5*S4M1*S3M1*U6M1 * ( 64*U1M1 )
     &+ M2*SP*S5*S4M1*S3M1*U7M1 * ( 64*T1M1 )
     &+ M2*SP*S5*S4M1*U6M1 * ( 48*T1M1*U1M1 )
     &+ M2*SP*S5*S4M1*U7M1 * ( 48*T1M1*U1M1 )
     &+ M2*SP*S5*S3M2*U6M1*U7M1 * ( 64 )
     &+ M2*SP*S5*S3M1*U6M1*U7M1 * ( 48*T1M1 + 48*U1M1 )
     &+ M2*SP*S5*U6M1*U7M1 * (  - 32*T1M1*U1M1 )
     &+ M2*SP*S4M2*S3 * ( 64*T1M1*U1M1 )
     &+ M2*SP*S4M1*S3*U6M1 * ( 16*T1M1*U1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2*SP*S4M1*S3*U7M1 * ( 16*T1M1*U1M1 )
     &+ M2*SP*S4M1*U6M1*Q2 * ( 32*U1M2 )
     &+ M2*SP*S4M1*U6M1 * ( 48*U1M1 )
     &+ M2*SP*S4M1*U7M1 * ( 48*T1M1 )
     &+ M2*SP*S4M1 * ( 32*T1M1*U1M1 )
     &+ M2*SP*S4*S3M2*U6M1*U7M1 * ( 64 )
     &+ M2*SP*S4*S3M1*U6M1*U7M1 * ( 16*T1M1 + 16*U1M1 )
     &+ M2*SP*S3M1*U6M1*U7M1 * ( 32 )
     &+ M2*SP*S3M1*U6M1 * ( 48*U1M1 )
     &+ M2*SP*S3M1*U7M2*Q2 * ( 32*T1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2*SP*S3M1*U7M1 * ( 48*T1M1 )
     &+ M2*SP*U6M2*Q2 * (  - 32*U1M2 )
     &+ M2*SP*U6M2 * (  - 32*U1M1 )
     &+ M2*SP*U6M1*U7M1 * ( 16*T1M1 + 16*U1M1 )
     &+ M2*SP*U6M1 * ( 16*T1M1*U1M1 - 32*U1M2 )
     &+ M2*SP*U7M2*Q2 * (  - 32*T1M2 )
     &+ M2*SP*U7M2 * (  - 32*T1M1 )
     &+ M2*SP*U7M1 * (  - 32*T1M2 + 16*T1M1*U1M1 )
     &+ M2*SP2*U6M1*U7M1 * ( 32*T1M1*U1M1 )
     &+ M2*U1P*S5*S4M1*S3M1*U7M1 * ( 64*T1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2*U1P*S5*S3M1*U6M1*U7M1 * ( 64*T1M1 )
     &+ M2*U1P*S4M1*S3M1*TP*U7M1 * ( 16*T1M1 )
     &+ M2*U1P*S4M1*S3M1*U6*U7M1 * ( 32*T1M1 )
     &+ M2*U1P*S4*S3M1*U6M1*U7M1 * ( 32*T1M1 )
     &+ M2*U1P*S3M2*U7M2*Q2 * (  - 32 )
     &+ M2*U1P*S3M2*U7M1 * (  - 32 )
     &+ M2*U1P*S3M1*TP*U6M1*U7M1 * ( 16*T1M1 )
     &+ M2*U1P*S3M1*TP*U7M2 * ( 64*T1M1 )
     &+ M2*U1P*S3M1*U7M2*Q2 * ( 32*T1M1 )
     &+ M2*U1P*S3M1*U7M2 * ( 64 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2*U1P*U7M2*Q2 * (  - 32*T1M2 )
     &+ M2*U1P*U7M2 * ( 64*T1M1 )
     &+ M2*U1P*U7M1 * (  - 32*T1M2 )
     &+ M2*S5*S4M2*Q2 * ( 64*T1M1*U1M1 - 32*U1M2 )
     &+ M2*S5*S4M2 * ( 64*T1M1 + 64*U1M1 )
     &+ M2*S5*S4M1*S3M1*UP*U6M1 * ( 48*U1M1 )
     &+ M2*S5*S4M1*S3M1*UP*U7M1 * ( 48*T1M1 - 32*U1M1 )
     &+ M2*S5*S4M1*S3M1*TP*U6M1 * (  - 32*T1M1 + 48*U1M1 )
     &+ M2*S5*S4M1*S3M1*TP*U7M1 * ( 48*T1M1 )
     &+ M2*S5*S4M1*S3M1*U6M1*U7 * ( 64*U1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2*S5*S4M1*S3M1*U6M1*Q2 * ( 144*U1M1 )
     &+ M2*S5*S4M1*S3M1*U6M1 * (  - 64 + 64*T1*U1M1 )
     &+ M2*S5*S4M1*S3M1*U6*U7M1 * ( 64*T1M1 )
     &+ M2*S5*S4M1*S3M1*U7M1*Q2 * ( 80*T1M1 - 32*U1M1 )
     &+ M2*S5*S4M1*S3M1*U7M1 * (  - 64 )
     &+ M2*S5*S4M1*S3M1 * (  - 64*T1M1 - 64*U1M1 )
     &+ M2*S5*S4M1*S3*U6M1 * ( 64*T1M1*U1M1 )
     &+ M2*S5*S4M1*S3*U7M1 * ( 64*T1M1*U1M1 )
     &+ M2*S5*S4M1*UP*U6M1 * ( 64*T1M1*U1M1 )
     &+ M2*S5*S4M1*UP*U7M1 * ( 64*T1M2 + 48*T1M1*U1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2*S5*S4M1*TP*U6M1 * ( 48*T1M1*U1M1 + 64*U1M2 )
     &+ M2*S5*S4M1*TP*U7M1 * ( 64*T1M1*U1M1 )
     &+ M2*S5*S4M1*U6M1*U7 * ( 64*T1M1*U1M1 )
     &+ M2*S5*S4M1*U6M1*Q2 * ( 160*T1M1*U1M1 + 32*U1M2 )
     &+ M2*S5*S4M1*U6M1 * (  - 64*T1M1 )
     &+ M2*S5*S4M1*U6*U7M1 * ( 64*T1M1*U1M1 )
     &+ M2*S5*S4M1*U7M1*Q2 * ( 128*T1M2 + 176*T1M1*U1M1 )
     &+ M2*S5*S4M1*U7M1 * (  - 64*U1M1 )
     &+ M2*S5*S4M1 * ( 64*T1M2 + 64*U1M2 )
     &+ M2*S5*S4*S3M1*U6M1*U7M1 * ( 64*T1M1 + 64*U1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2*S5*S3M2*U6M1*U7M1*Q2 * ( 64 )
     &+ M2*S5*S3M2*U6M1 * ( 64 )
     &+ M2*S5*S3M2*U7M2*Q2 * (  - 32 )
     &+ M2*S5*S3M2*U7M1 * ( 64 )
     &+ M2*S5*S3M1*UP*U6M2 * ( 64*U1M1 )
     &+ M2*S5*S3M1*UP*U6M1*U7M1 * ( 64*T1M1 + 48*U1M1 )
     &+ M2*S5*S3M1*TP*U6M1*U7M1 * ( 48*T1M1 + 64*U1M1 )
     &+ M2*S5*S3M1*TP*U7M2 * ( 64*T1M1 )
     &+ M2*S5*S3M1*U6M2*Q2 * ( 128*U1M1 )
     &+ M2*S5*S3M1*U6M2 * ( 64 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2*S5*S3M1*U6M1*U7M1*Q2 * ( 96*T1M1 + 176*U1M1 )
     &+ M2*S5*S3M1*U6M1*U7M1 * ( 64*T1*U1M1 )
     &+ M2*S5*S3M1*U6M1 * (  - 64*T1M1 )
     &+ M2*S5*S3M1*U7M2*Q2 * ( 32*T1M1 )
     &+ M2*S5*S3M1*U7M2 * ( 64 )
     &+ M2*S5*S3M1*U7M1 * (  - 64*U1M1 )
     &+ M2*S5*U6M2*Q2 * (  - 32*U1M2 )
     &+ M2*S5*U6M2 * ( 64*U1M1 )
     &+ M2*S5*U6M1*U7M1 * (  - 64*T1M1 - 64*U1M1 )
     &+ M2*S5*U6M1 * (  - 64*T1M1*U1M1 + 64*U1M2 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2*S5*U7M2*Q2 * (  - 32*T1M2 )
     &+ M2*S5*U7M2 * ( 64*T1M1 )
     &+ M2*S5*U7M1 * ( 64*T1M2 - 64*T1M1*U1M1 )
     &+ M2*S52*S4M1*S3M1*U6M1 * (  - 64*T1M1 + 32*U1M1 )
     &+ M2*S52*S4M1*S3M1*U7M1 * ( 32*T1M1 - 64*U1M1 )
     &+ M2*S52*S4M1*U6M1 * ( 32*T1M1*U1M1 )
     &+ M2*S52*S4M1*U7M1 * ( 32*T1M1*U1M1 )
     &+ M2*S52*S3M1*U6M1*U7M1 * ( 32*T1M1 + 32*U1M1 )
     &+ M2*S52*U6M1*U7M1 * (  - 64*T1M1*U1M1 )
     &+ M2*S4M2*S3*Q2 * ( 64*T1M1*U1M1 - 32*U1M2 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2*S4M2*S3 * ( 64*T1M1 + 64*U1M1 )
     &+ M2*S4M2*UP*Q2 * (  - 32*U1M2 )
     &+ M2*S4M2*UP * (  - 32*U1M1 )
     &+ M2*S4M2*TP * (  - 32*T1M1 )
     &+ M2*S4M2*U6 * (  - 32*T1M1 )
     &+ M2*S4M2*U7*Q2 * (  - 32*U1M2 )
     &+ M2*S4M2*U7 * (  - 32*U1M1 )
     &+ M2*S4M2*Q2 * (  - 64*U1M1 )
     &+ M2*S4M2*Q4 * (  - 64*U1M2 )
     &+ M2*S4M1*S3M1*UP*U6M1 * ( 16*T1*U1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2*S4M1*S3M1*UP*U6*U7M1 * ( 16*T1M1 )
     &+ M2*S4M1*S3M1*UP*U7M1*Q2 * ( 64*U1M1 )
     &+ M2*S4M1*S3M1*UP*U7M1 * ( 16 )
     &+ M2*S4M1*S3M1*UP * ( 16*U1M1 )
     &+ M2*S4M1*S3M1*UP2*U7M1 * ( 32*U1M1 )
     &+ M2*S4M1*S3M1*TP*U6M1*U7 * ( 16*U1M1 )
     &+ M2*S4M1*S3M1*TP*U6M1*Q2 * ( 32*U1M1 )
     &+ M2*S4M1*S3M1*TP*U6M1 * ( 16 )
     &+ M2*S4M1*S3M1*TP*U7M1*Q2 * ( 16*T1M1 )
     &+ M2*S4M1*S3M1*TP * ( 16*T1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2*S4M1*S3M1*TP2*U6M1 * ( 32*T1M1 )
     &+ M2*S4M1*S3M1*U6M1*U7 * ( 32*T1*U1M1 )
     &+ M2*S4M1*S3M1*U6M1*Q2 * ( 48*T1*U1M1 )
     &+ M2*S4M1*S3M1*U6*U7M1*Q2 * ( 16*T1M1 )
     &+ M2*S4M1*S3M1*U7M1*Q2 * ( 48 )
     &+ M2*S4M1*S3M1*U7M1*Q4 * ( 32*U1M1 )
     &+ M2*S4M1*S3M1*Q2 * ( 48*U1M1 )
     &+ M2*S4M1*S3M1 * ( 64 )
     &+ M2*S4M1*S3*U6M1*U7 * ( 32*T1M1*U1M1 )
     &+ M2*S4M1*S3*U6M1*Q2 * ( 32*T1M1*U1M1 + 32*U1M2 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2*S4M1*S3*U6*U7M1 * ( 32*T1M1*U1M1 )
     &+ M2*S4M1*S3*U7M1*Q2 * ( 16*T1M1*U1M1 )
     &+ M2*S4M1*S3 * (  - 32*T1M2 - 32*U1M2 )
     &+ M2*S4M1*UP*U6M1*Q2 * ( 32*U1M2 )
     &+ M2*S4M1*UP*U6M1 * ( 48*U1M1 )
     &+ M2*S4M1*UP*U6*U7M1 * ( 64*T1M2 + 16*T1M1*U1M1 )
     &+ M2*S4M1*UP*U7M1 * ( 32*T1M1 + 16*U1M1 )
     &+ M2*S4M1*UP * ( 48*T1M1*U1M1 - 32*U1M2 )
     &+ M2*S4M1*TP*U6M1*U7 * ( 16*T1M1*U1M1 + 64*U1M2 )
     &+ M2*S4M1*TP*U6M1*Q2 * ( 32*T1M1*U1M1 + 96*U1M2 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2*S4M1*TP*U6M1 * ( 16*T1M1 + 32*U1M1 )
     &+ M2*S4M1*TP*U7M1 * ( 48*T1M1 )
     &+ M2*S4M1*TP * (  - 32*T1M2 + 48*T1M1*U1M1 )
     &+ M2*S4M1*U6M1*U7*Q2 * ( 32*U1M2 )
     &+ M2*S4M1*U6M1*Q2 * ( 32*T1*U1M2 + 48*U1M1 )
     &+ M2*S4M1*U6M1*Q4 * ( 64*U1M2 )
     &+ M2*S4M1*U6M1 * (  - 128 )
     &+ M2*S4M1*U6*U7M1*Q2 * ( 128*T1M2 + 32*T1M1*U1M1 )
     &+ M2*S4M1*U6 * ( 64*T1M2 )
     &+ M2*S4M1*U7M1*Q2 * ( 144*T1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2*S4M1*U7M1*Q4 * ( 32*T1M1*U1M1 )
     &+ M2*S4M1*U7M1 * (  - 128 )
     &+ M2*S4M1*U7 * ( 64*U1M2 )
     &+ M2*S4M1*Q2 * ( 160*T1M1*U1M1 - 32*U1M2 )
     &+ M2*S4M1 * ( 192*T1M1 + 192*U1M1 )
     &+ M2*S4*S3M2*U6M1*U7M1*Q2 * ( 64 )
     &+ M2*S4*S3M2*U6M1 * ( 64 )
     &+ M2*S4*S3M2*U7M2*Q2 * (  - 32 )
     &+ M2*S4*S3M2*U7M1 * ( 64 )
     &+ M2*S4*S3M1*U6M2 * (  - 32 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2*S4*S3M1*U6M1*U7M1*Q2 * ( 16*U1M1 )
     &+ M2*S4*S3M1*U6M1*U7M1 * ( 32*T1*U1M1 )
     &+ M2*S4*S3M1*U7M2*Q2 * ( 32*T1M1 )
     &+ M2*S4*S3M1*U7M2 * (  - 32 )
     &+ M2*S3M2*UP*U7M2*Q2 * (  - 32 )
     &+ M2*S3M2*UP*U7M1 * (  - 32 )
     &+ M2*S3M2*TP*U6M1 * (  - 32 )
     &+ M2*S3M2*U6M1 * (  - 32*T1 )
     &+ M2*S3M2*U7M2*Q4 * (  - 32 )
     &+ M2*S3M2*U7M1*Q2 * (  - 32 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2*S3M1*UP*U6M2 * ( 64*T1*U1M1 )
     &+ M2*S3M1*UP*U6M1*U7M1 * ( 48 + 16*T1*U1M1 )
     &+ M2*S3M1*UP*U6M1 * ( 32*U1M1 )
     &+ M2*S3M1*UP*U7M2*Q2 * ( 32*T1M1 )
     &+ M2*S3M1*UP*U7M2 * (  - 32 )
     &+ M2*S3M1*UP*U7M1 * ( 48*T1M1 + 16*U1M1 )
     &+ M2*S3M1*TP*U6M2 * (  - 32 )
     &+ M2*S3M1*TP*U6M1*U7M1*Q2 * ( 16*T1M1 )
     &+ M2*S3M1*TP*U6M1*U7M1 * ( 48 )
     &+ M2*S3M1*TP*U6M1 * ( 16*T1M1 + 48*U1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2*S3M1*TP*U7M2*Q2 * ( 32*T1M1 )
     &+ M2*S3M1*TP*U7M1 * ( 32*T1M1 )
     &+ M2*S3M1*U6M2*Q2 * ( 128*T1*U1M1 )
     &+ M2*S3M1*U6M2 * ( 64*T1 )
     &+ M2*S3M1*U6M1*U7M1*Q2 * ( 160 + 32*T1*U1M1 )
     &+ M2*S3M1*U6M1*U7M1*Q4 * ( 32*U1M1 )
     &+ M2*S3M1*U6M1*Q2 * ( 144*U1M1 )
     &+ M2*S3M1*U6M1 * ( 192 )
     &+ M2*S3M1*U6*U7M2*Q2 * ( 32*T1M1 )
     &+ M2*S3M1*U7M2*Q2 * (  - 96 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2*S3M1*U7M2*Q4 * ( 32*T1M1 )
     &+ M2*S3M1*U7M1*Q2 * ( 48*T1M1 )
     &+ M2*S3M1*U7M1 * ( 192 )
     &+ M2*S3M1 * (  - 128*T1M1 - 128*U1M1 )
     &+ M2*U6M2*U7*Q2 * (  - 32*U1M2 )
     &+ M2*U6M2*U7 * (  - 32*U1M1 )
     &+ M2*U6M2*Q2 * (  - 32*T1*U1M2 - 32*U1M1 )
     &+ M2*U6M2*Q4 * (  - 32*U1M2 )
     &+ M2*U6M2 * ( 64*T1*U1M1 )
     &+ M2*U6M1*U7M1*Q2 * ( 32*T1M1 - 16*U1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2*U6M1*U7M1 * (  - 128 )
     &+ M2*U6M1*U7 * ( 64*U1M2 )
     &+ M2*U6M1*Q2 * ( 32*T1M1*U1M1 )
     &+ M2*U6M1 * ( 64*T1M1 - 32*T1*U1M2 + 192*U1M1 )
     &+ M2*U6*U7M2*Q2 * (  - 32*T1M2 )
     &+ M2*U6*U7M2 * (  - 32*T1M1 )
     &+ M2*U6*U7M1 * ( 64*T1M2 )
     &+ M2*U7M2*Q2 * (  - 64*T1M1 )
     &+ M2*U7M1*Q2 * (  - 16*T1M1*U1M1 )
     &+ M2*U7M1 * ( 192*T1M1 + 64*U1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ M2 * (  - 128*T1M1*U1M1 )
     &+ M4*SP*S4M2 * (  - 64*T1M1*U1M1 )
     &+ M4*SP*S4M1*S3M1*U6M1 * (  - 192*U1M1 )
     &+ M4*SP*S4M1*S3M1*U7M1 * (  - 192*T1M1 )
     &+ M4*SP*S4M1*U6M1 * (  - 64*U1M2 )
     &+ M4*SP*S4M1*U7M1 * (  - 64*T1M2 )
     &+ M4*SP*S3M2*U6M1*U7M1 * (  - 64 )
     &+ M4*SP*S3M1*U6M2 * (  - 64*U1M1 )
     &+ M4*SP*S3M1*U7M2 * (  - 64*T1M1 )
     &+ M4*SP*U6M2 * ( 64*U1M2 )
        FGGC_CFCF = FGGC_CFCF
     &+ M4*SP*U6M1*U7M1 * ( 256*T1M1*U1M1 )
     &+ M4*SP*U7M2 * ( 64*T1M2 )
     &+ M4*U1P*S4M1*S3M1*U7M1 * (  - 128*T1M1 )
     &+ M4*U1P*S4M1*U7M1 * (  - 64*T1M2 )
     &+ M4*U1P*S3M2*U6M1*U7M1 * (  - 64 )
     &+ M4*U1P*S3M2*U7M2 * ( 64 )
     &+ M4*U1P*S3M1*U6M1*U7M1 * (  - 128*T1M1 )
     &+ M4*U1P*S3M1*U7M2 * (  - 64*T1M1 )
     &+ M4*U1P*U7M2 * ( 64*T1M2 )
     &+ M4*S5*S4M2 * ( 64*T1M2 - 64*T1M1*U1M1 + 64*U1M2 )
        FGGC_CFCF = FGGC_CFCF
     &+ M4*S5*S4M1*S3M1*U6M1 * (  - 128*T1M1 - 192*U1M1 )
     &+ M4*S5*S4M1*S3M1*U7M1 * (  - 192*T1M1 - 128*U1M1 )
     &+ M4*S5*S4M1*U6M1 * (  - 192*T1M1*U1M1 - 64*U1M2 )
     &+ M4*S5*S4M1*U7M1 * (  - 64*T1M2 - 192*T1M1*U1M1 )
     &+ M4*S5*S3M2*U6M2 * ( 64 )
     &+ M4*S5*S3M2*U6M1*U7M1 * (  - 64 )
     &+ M4*S5*S3M2*U7M2 * ( 64 )
     &+ M4*S5*S3M1*U6M2 * (  - 64*U1M1 )
     &+ M4*S5*S3M1*U6M1*U7M1 * (  - 192*T1M1 - 192*U1M1 )
     &+ M4*S5*S3M1*U7M2 * (  - 64*T1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ M4*S5*U6M2 * ( 64*U1M2 )
     &+ M4*S5*U6M1*U7M1 * (  - 128*T1M1*U1M1 )
     &+ M4*S5*U7M2 * ( 64*T1M2 )
     &+ M4*S4M2*S3 * ( 64*T1M2 - 64*T1M1*U1M1 + 64*U1M2 )
     &+ M4*S4M2*UP * (  - 64*T1M1*U1M1 + 64*U1M2 )
     &+ M4*S4M2*TP * ( 64*T1M2 - 64*T1M1*U1M1 )
     &+ M4*S4M2*U6 * ( 64*T1M2 - 64*T1M1*U1M1 )
     &+ M4*S4M2*U7 * (  - 64*T1M1*U1M1 + 64*U1M2 )
     &+ M4*S4M2*Q2 * (  - 128*T1M1*U1M1 + 64*U1M2 )
     &+ M4*S4M2 * ( 128*T1M1 + 128*U1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ M4*S4M1*S3M1*UP*U7M1 * ( 256*U1M1 )
     &+ M4*S4M1*S3M1*TP*U6M1 * ( 256*T1M1 )
     &+ M4*S4M1*S3M1*U6M1*U7 * (  - 128*U1M1 )
     &+ M4*S4M1*S3M1*U6M1*Q2 * (  - 192*U1M1 )
     &+ M4*S4M1*S3M1*U6M1 * (  - 128*T1*U1M1 )
     &+ M4*S4M1*S3M1*U6*U7M1 * (  - 128*T1M1 )
     &+ M4*S4M1*S3M1*U7M1*Q2 * (  - 64*T1M1 + 256*U1M1 )
     &+ M4*S4M1*S3*U6M1 * (  - 128*T1M1*U1M1 - 64*U1M2 )
     &+ M4*S4M1*S3*U7M1 * (  - 64*T1M2 - 128*T1M1*U1M1 )
     &+ M4*S4M1*UP*U6M1 * (  - 192*T1M1*U1M1 - 64*U1M2 )
        FGGC_CFCF = FGGC_CFCF
     &+ M4*S4M1*UP*U7M1 * (  - 64*T1M2 )
     &+ M4*S4M1*TP*U6M1 * (  - 64*U1M2 )
     &+ M4*S4M1*TP*U7M1 * (  - 64*T1M2 - 192*T1M1*U1M1 )
     &+ M4*S4M1*U6M1*U7 * (  - 128*T1M1*U1M1 - 64*U1M2 )
     &+ M4*S4M1*U6M1*Q2 * (  - 384*T1M1*U1M1 - 256*U1M2 )
     &+ M4*S4M1*U6M1 * (  - 64*T1*U1M2 + 64*U1M1 )
     &+ M4*S4M1*U6*U7M1 * (  - 64*T1M2 - 128*T1M1*U1M1 )
     &+ M4*S4M1*U7M1*Q2 * (  - 64*T1M2 - 64*T1M1*U1M1 )
     &+ M4*S4M1*U7M1 * ( 64*T1M1 )
     &+ M4*S4M1 * ( 128*T1M2 + 64*T1M1*U1M1 + 128*U1M2 )
        FGGC_CFCF = FGGC_CFCF
     &+ M4*S4*S3M2*U6M2 * ( 64 )
     &+ M4*S4*S3M2*U6M1*U7M1 * (  - 64 )
     &+ M4*S4*S3M2*U7M2 * ( 64 )
     &+ M4*S4*S3M1*U6M2 * (  - 64*U1M1 )
     &+ M4*S4*S3M1*U6M1*U7M1 * (  - 128*T1M1 - 128*U1M1 )
     &+ M4*S4*S3M1*U7M2 * (  - 64*T1M1 )
     &+ M4*S3M2*UP*U6M1*U7M1 * (  - 64 )
     &+ M4*S3M2*UP*U7M2 * ( 64 )
     &+ M4*S3M2*TP*U6M2 * ( 64 )
     &+ M4*S3M2*TP*U6M1*U7M1 * (  - 64 )
        FGGC_CFCF = FGGC_CFCF
     &+ M4*S3M2*U6M2 * ( 64*T1 )
     &+ M4*S3M2*U6M1*U7M1*Q2 * (  - 64 )
     &+ M4*S3M2*U6M1*U7M1 * (  - 64*T1 )
     &+ M4*S3M2*U6M1 * ( 128 )
     &+ M4*S3M2*U7M1 * ( 128 )
     &+ M4*S3M1*UP*U6M2 * (  - 64*U1M1 )
     &+ M4*S3M1*UP*U6M1*U7M1 * (  - 192*T1M1 )
     &+ M4*S3M1*UP*U7M2 * (  - 64*T1M1 )
     &+ M4*S3M1*TP*U6M2 * (  - 64*U1M1 )
     &+ M4*S3M1*TP*U6M1*U7M1 * (  - 192*U1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ M4*S3M1*TP*U7M2 * (  - 64*T1M1 )
     &+ M4*S3M1*U6M2*U7 * (  - 64*U1M1 )
     &+ M4*S3M1*U6M2*Q2 * (  - 128*U1M1 )
     &+ M4*S3M1*U6M2 * ( 128 - 64*T1*U1M1 )
     &+ M4*S3M1*U6M1*U7M1*Q2 * (  - 256*T1M1 - 64*U1M1 )
     &+ M4*S3M1*U6M1*U7M1 * ( 64 - 128*T1*U1M1 )
     &+ M4*S3M1*U6M1 * ( 64*U1M1 )
     &+ M4*S3M1*U6*U7M2 * (  - 64*T1M1 )
     &+ M4*S3M1*U7M2*Q2 * (  - 192*T1M1 )
     &+ M4*S3M1*U7M2 * ( 128 )
        FGGC_CFCF = FGGC_CFCF
     &+ M4*S3M1*U7M1 * ( 64*T1M1 )
     &+ M4*U6M2*U7 * ( 64*U1M2 )
     &+ M4*U6M2 * ( 64*T1*U1M2 + 128*U1M1 )
     &+ M4*U6M1 * ( 128*U1M2 )
     &+ M4*U6*U7M2 * ( 64*T1M2 )
     &+ M4*U7M2*Q2 * (  - 64*T1M2 )
     &+ M4*U7M2 * ( 128*T1M1 )
     &+ M4*U7M1 * ( 128*T1M2 )
     &+ M6*S4M2 * ( 128*T1M2 + 256*T1M1*U1M1 + 128*U1M2 )
     &+ M6*S4M1*S3M1*U6M1 * ( 256*T1M1 + 256*U1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ M6*S4M1*S3M1*U7M1 * ( 256*T1M1 + 256*U1M1 )
     &+ M6*S4M1*U6M1 * ( 256*T1M1*U1M1 + 256*U1M2 )
     &+ M6*S4M1*U7M1 * ( 256*T1M2 + 256*T1M1*U1M1 )
     &+ M6*S3M2*U6M2 * ( 128 )
     &+ M6*S3M2*U6M1*U7M1 * ( 256 )
     &+ M6*S3M2*U7M2 * ( 128 )
     &+ M6*S3M1*U6M2 * ( 256*U1M1 )
     &+ M6*S3M1*U6M1*U7M1 * ( 256*T1M1 + 256*U1M1 )
     &+ M6*S3M1*U7M2 * ( 256*T1M1 )
     &+ M6*U6M2 * ( 128*U1M2 )
        FGGC_CFCF = FGGC_CFCF
     &+ M6*U6M1*U7M1 * ( 256*T1M1*U1M1 )
     &+ M6*U7M2 * ( 128*T1M2 )
     &+ SP*S5*S4M1*S3*U6M1 * (  - 16*T1M1*U1M1 )
     &+ SP*S5*S4M1*S3*U7M1 * (  - 16*T1M1*U1M1 )
     &+ SP*S5*S4M1*U6M1 * ( 16*U1M1 )
     &+ SP*S5*S4M1*U7M1 * ( 16*T1M1 )
     &+ SP*S5*S4*S3M1*U6M1*U7M1 * (  - 16*T1M1 - 16*U1M1 )
     &+ SP*S5*S3M1*U6M1 * ( 16*U1M1 )
     &+ SP*S5*S3M1*U7M1 * ( 16*T1M1 )
     &+ SP*S52*S4M1*S3M1*U6M1 * ( 16*U1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ SP*S52*S4M1*S3M1*U7M1 * ( 16*T1M1 )
     &+ SP*S52*S4M1*U6M1 * (  - 16*T1M1*U1M1 )
     &+ SP*S52*S4M1*U7M1 * (  - 16*T1M1*U1M1 )
     &+ SP*S52*S3M1*U6M1*U7M1 * (  - 16*T1M1 - 16*U1M1 )
     &+ SP*S4M1*S3 * (  - 32*T1M1*U1M1 )
     &+ SP*S4*S3M1*U6M1*U7M1 * (  - 32 )
     &+ SP*U6M1*Q2 * ( 16*U1M2 )
     &+ SP*U6M1 * ( 16*U1M1 )
     &+ SP*U7M2*Q2 * ( 16*T1M1 )
     &+ SP*U7M1 * ( 16*T1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ U1P*S5*S4M1*S3M1*TP*U7M1 * (  - 16*T1M1 )
     &+ U1P*S5*S4M1*S3M1*U6*U7M1 * (  - 16*T1M1 )
     &+ U1P*S5*S4*S3M1*U6M1*U7M1 * (  - 16*T1M1 )
     &+ U1P*S5*S3M1*TP*U6M1*U7M1 * (  - 16*T1M1 )
     &+ U1P*S5*S3M1*U7M1 * ( 32*T1M1 )
     &+ U1P*S3M1*TP*U7M2*Q2 * (  - 32*T1M1 )
     &+ U1P*S3M1*TP*U7M1 * (  - 32*T1M1 )
     &+ U1P*S3M1*U7M2*Q2 * (  - 32 )
     &+ U1P*S3M1*U7M1 * (  - 16 )
     &+ U1P*U7M2*Q2 * (  - 32*T1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ U1P*U7M1 * (  - 16*T1M1 )
     &+ S5*S4M1*S3M1*UP*U6M1 * (  - 16*T1*U1M1 )
     &+ S5*S4M1*S3M1*UP*U6*U7M1 * (  - 16*T1M1 )
     &+ S5*S4M1*S3M1*TP*U6M1*U7 * (  - 16*U1M1 )
     &+ S5*S4M1*S3M1*TP*U6M1*Q2 * (  - 16*U1M1 )
     &+ S5*S4M1*S3M1*U6M1*U7 * (  - 16*T1*U1M1 )
     &+ S5*S4M1*S3M1*U6M1*Q2 * (  - 32*T1*U1M1 )
     &+ S5*S4M1*S3M1*U6*U7M1*Q2 * (  - 16*T1M1 )
     &+ S5*S4M1*S3M1*U7M1*Q2 * (  - 16 )
     &+ S5*S4M1*S3M1*Q2 * (  - 16*U1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ S5*S4M1*S3M1 * (  - 32 )
     &+ S5*S4M1*S3*U6M1*U7 * (  - 16*T1M1*U1M1 )
     &+ S5*S4M1*S3*U6M1*Q2 * (  - 16*T1M1*U1M1 )
     &+ S5*S4M1*S3*U6*U7M1 * (  - 16*T1M1*U1M1 )
     &+ S5*S4M1*S3*U7M1*Q2 * (  - 16*T1M1*U1M1 )
     &+ S5*S4M1*S3 * ( 32*T1M1*U1M1 )
     &+ S5*S4M1*UP*U6M1 * ( 16*U1M1 )
     &+ S5*S4M1*UP*U6*U7M1 * (  - 16*T1M1*U1M1 )
     &+ S5*S4M1*UP * ( 16*T1M1*U1M1 )
     &+ S5*S4M1*TP*U6M1*U7 * (  - 16*T1M1*U1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ S5*S4M1*TP*U6M1*Q2 * (  - 16*T1M1*U1M1 - 32*U1M2 )
     &+ S5*S4M1*TP*U7M1*Q2 * ( 16*T1M1*U1M1 )
     &+ S5*S4M1*TP*U7M1 * ( 16*T1M1 )
     &+ S5*S4M1*TP * ( 16*T1M1*U1M1 )
     &+ S5*S4M1*U6M1*U7 * ( 32*U1M1 )
     &+ S5*S4M1*U6M1*Q2 * ( 48*U1M1 )
     &+ S5*S4M1*U6M1 * ( 32 )
     &+ S5*S4M1*U6*U7M1*Q2 * (  - 32*T1M1*U1M1 )
     &+ S5*S4M1*U6*U7M1 * ( 32*T1M1 )
     &+ S5*S4M1*U7M1*Q2 * ( 16*T1M1 + 16*U1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ S5*S4M1*U7M1 * ( 32 )
     &+ S5*S4M1*Q2 * ( 32*T1M1*U1M1 - 32*U1M2 )
     &+ S5*S4M1 * ( 64*T1M1 + 64*U1M1 )
     &+ S5*S4*S3M1*U6M1*U7M1*Q2 * (  - 16*U1M1 )
     &+ S5*S4*S3M1*U6M1*U7M1 * ( 32 - 16*T1*U1M1 )
     &+ S5*S3M1*UP*U6M1*U7M1 * ( 16 - 16*T1*U1M1 )
     &+ S5*S3M1*UP*U7M1 * ( 16*T1M1 )
     &+ S5*S3M1*TP*U6M1*U7M1*Q2 * ( 16*U1M1 )
     &+ S5*S3M1*TP*U6M1*U7M1 * ( 16 )
     &+ S5*S3M1*TP*U6M1 * ( 16*U1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ S5*S3M1*TP*U7M2*Q2 * (  - 32*T1M1 )
     &+ S5*S3M1*U6M1*U7M1*Q2 * ( 32 - 32*T1*U1M1 )
     &+ S5*S3M1*U6M1*Q2 * ( 16*U1M1 )
     &+ S5*S3M1*U6M1 * ( 64 + 32*T1*U1M1 )
     &+ S5*S3M1*U7M2*Q2 * (  - 32 )
     &+ S5*S3M1*U7M1*Q2 * ( 16*T1M1 + 16*U1M1 )
     &+ S5*S3M1*U7M1 * ( 64 )
     &+ S5*S3M1 * ( 32*T1M1 + 32*U1M1 )
     &+ S5*U6M1*U7M1*Q2 * (  - 16*T1M1 + 16*U1M1 )
     &+ S5*U6M1*U7M1 * ( 32 )
        FGGC_CFCF = FGGC_CFCF
     &+ S5*U6M1*Q2 * (  - 16*T1M1*U1M1 - 32*U1M2 )
     &+ S5*U6M1 * (  - 32*T1M1 + 64*U1M1 )
     &+ S5*U7M2*Q2 * (  - 32*T1M1 )
     &+ S5*U7M1*Q2 * ( 16*T1M1*U1M1 )
     &+ S5*U7M1 * ( 64*T1M1 - 32*U1M1 )
     &+ S5 * ( 32*T1M1*U1M1 )
     &+ S52*S4M1*S3M1*UP*U6M1 * (  - 16*U1M1 )
     &+ S52*S4M1*S3M1*UP*U7M1 * (  - 16*T1M1 )
     &+ S52*S4M1*S3M1*TP*U6M1 * (  - 16*U1M1 )
     &+ S52*S4M1*S3M1*TP*U7M1 * (  - 16*T1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ S52*S4M1*S3M1*U6M1*Q2 * (  - 16*U1M1 )
     &+ S52*S4M1*S3M1*U6M1 * ( 32 )
     &+ S52*S4M1*S3M1*U7M1*Q2 * (  - 16*T1M1 )
     &+ S52*S4M1*S3M1*U7M1 * ( 32 )
     &+ S52*S4M1*S3M1 * ( 32*T1M1 + 32*U1M1 )
     &+ S52*S4M1*UP*U6M1 * ( 16*T1M1*U1M1 )
     &+ S52*S4M1*UP*U7M1 * (  - 16*T1M1*U1M1 )
     &+ S52*S4M1*TP*U6M1 * (  - 16*T1M1*U1M1 )
     &+ S52*S4M1*TP*U7M1 * ( 16*T1M1*U1M1 )
     &+ S52*S4M1*U6M1*Q2 * ( 16*T1M1*U1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ S52*S4M1*U6M1 * ( 32*T1M1 )
     &+ S52*S4M1*U7M1*Q2 * (  - 48*T1M1*U1M1 )
     &+ S52*S4M1*U7M1 * ( 32*U1M1 )
     &+ S52*S3M1*UP*U6M1*U7M1 * ( 16*T1M1 - 16*U1M1 )
     &+ S52*S3M1*TP*U6M1*U7M1 * (  - 16*T1M1 + 16*U1M1 )
     &+ S52*S3M1*U6M1*U7M1*Q2 * ( 16*T1M1 - 48*U1M1 )
     &+ S52*S3M1*U6M1 * ( 32*T1M1 )
     &+ S52*S3M1*U7M1 * ( 32*U1M1 )
     &+ S52*U6M1*U7M1 * ( 32*T1M1 + 32*U1M1 )
     &+ S52*U6M1 * ( 32*T1M1*U1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ S52*U7M1 * ( 32*T1M1*U1M1 )
     &+ S53*S4M1*S3M1*U6M1 * ( 32*T1M1 )
     &+ S53*S4M1*S3M1*U7M1 * ( 32*U1M1 )
     &+ S53*U6M1*U7M1 * ( 32*T1M1*U1M1 )
     &+ S4M1*S3*U6*U7M1*Q2 * (  - 16*T1M1*U1M1 )
     &+ S4M1*S3*U7M1*Q2 * ( 16*U1M1 )
     &+ S4M1*S3*Q2 * (  - 16*T1M1*U1M1 + 16*U1M2 )
     &+ S4M1*S3 * (  - 16*T1M1 - 16*U1M1 )
     &+ S4M1*UP*U6*U7M1 * (  - 32*T1M1 )
     &+ S4M1*UP*Q2 * ( 16*U1M2 )
        FGGC_CFCF = FGGC_CFCF
     &+ S4M1*UP * ( 16*U1M1 )
     &+ S4M1*TP*U6M1*U7*Q2 * (  - 32*U1M2 )
     &+ S4M1*TP*U6M1*U7 * (  - 32*U1M1 )
     &+ S4M1*TP*U6M1*Q2 * (  - 32*U1M1 )
     &+ S4M1*TP*U6M1*Q4 * (  - 32*U1M2 )
     &+ S4M1*TP * ( 16*T1M1 )
     &+ S4M1*U6*U7M1*Q2 * (  - 48*T1M1 )
     &+ S4M1*U6 * (  - 16*T1M1 )
     &+ S4M1*U7M1*Q2 * (  - 16 )
     &+ S4M1*U7*Q2 * (  - 32*U1M2 )
        FGGC_CFCF = FGGC_CFCF
     &+ S4M1*U7 * (  - 16*U1M1 )
     &+ S4M1*Q2 * (  - 16*U1M1 )
     &+ S4M1*Q4 * (  - 16*U1M2 )
     &+ S4M1 * (  - 32 )
     &+ S4*S3M1*U6M1*U7M1*Q2 * (  - 16 - 16*T1*U1M1 )
     &+ S4*S3M1*U6M1 * (  - 16 )
     &+ S4*S3M1*U7M2*Q2 * ( 16 )
     &+ S4*S3M1*U7M1*Q2 * ( 16*U1M1 )
     &+ S4*S3M1*U7M1 * (  - 16 )
     &+ S3M1*UP*U6M1 * (  - 32*T1*U1M1 )
        FGGC_CFCF = FGGC_CFCF
     &+ S3M1*UP*U7M2*Q2 * ( 16 )
     &+ S3M1*UP*U7M1 * ( 16 )
     &+ S3M1*TP*U6M1 * ( 16 )
     &+ S3M1*U6M1*Q2 * (  - 48*T1*U1M1 )
     &+ S3M1*U6M1 * (  - 16*T1 )
     &+ S3M1*U7M2*Q4 * ( 16 )
     &+ S3M1*Q2 * (  - 16*U1M1 )
     &+ S3M1 * (  - 32 )
     &+ U6M1*U7M1*Q2 * (  - 16 + 16*T1*U1M1 )
     &+ U6M1*U7*Q2 * (  - 32*U1M2 )
        FGGC_CFCF = FGGC_CFCF
     &+ U6M1*U7 * (  - 16*U1M1 )
     &+ U6M1*Q2 * ( 16*T1*U1M2 - 32*U1M1 )
     &+ U6M1*Q4 * (  - 32*U1M2 )
     &+ U6M1 * (  - 32 - 16*T1*U1M1 )
     &+ U6*U7M2*Q2 * ( 16*T1M1 )
     &+ U6*U7M1*Q2 * ( 16*T1M1*U1M1 )
     &+ U6*U7M1 * (  - 16*T1M1 )
     &+ U7M1*Q2 * (  - 16*T1M1 - 32*U1M1 )
     &+ U7M1 * (  - 32 )
     &+ Q2 * (  - 16*T1M1*U1M1 )
     &- 32*T1M1 - 32*U1M1

        FGGC_CFCF = FGGC_CFCF*TP*(UP+Q2*S5/S)

      END IF

      RETURN
      END
      FUNCTION FGLC_CACF
     &         (X,Y,M2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DP,DM)
C
C THIS IS THE CA*CF TERM OF FGLC IN 3 CASES
C 1) SOFT LIMIT
C 2) COLLINEAR LIMIT
C 3) HARD
C
C LIMITS CHECK UNDER THETA2 INTEGRATION: 11/7/94
C LIMITS CHECK W/O   THETA2 INTEGRATION: 3/2/95, 3/29/95
C
C IT IS TP*(UP+Q2*S5/S)*M^G_L(3) OF THE PAPER
C THERE IS AN OVERALL FACTOR OF G^4 EH^2 N CA CF UNDERSTOOD
C
      IMPLICIT DOUBLE PRECISION (A-Z)

      COMMON/AZDEP/CTH22,STH12

      PARAMETER (DELTAS=1.0D-5)
      PARAMETER (DELTAC=1.0D-7)

      ONEMX = 1.D0 - X
      ONEPY = 1.D0 + Y
      ONEMY = 1.D0 - Y

      IF ( ONEMX.LT.DELTAS ) THEN
C         WRITE(*,*) 'TAKING SOFT'
C (1-Y*Y)*(1-X)**2*(K1P2)*SP**2
        P1 = -8.D0*S*T1*ONEMY/SP/DP
C (1-Y*Y)*(1-X)**2*(K1P1)*SP**2
        P2 = -8.D0*S*U1*ONEMY/SP/DM
C (1-Y*Y)*(1-X)**2*(P1P2)*SP**2
        P3 = +8.D0*(S-2.D0*M2)*ONEMY*ONEPY/DP/DM
        RSPS2 = (SP/S)**2
        FGLC_CACF = 2.D0*RSPS2*BLQED(T1,SP,M2,Q2)*(P1+P2-P3)
      ELSE IF ( ONEPY.LT.DELTAC ) THEN
C         WRITE(*,*) 'TAKING COLLINEAR'
        BETA52 = 1.D0-4.D0*M2/S5
        XSP2 = X*X*SP*SP
        FH = 2.D0*(X*X-2.D0*X+2.D0)*(M2*XSP2/X/T1/U1-S5)/X/X
     &      - ONEMX*ONEMX*S5*BETA52*CTH22*STH12*XSP2/T1/U1/X**5
        FGLC_CACF = -64.D0*Q2*FH/S
      ELSE
C         WRITE(*,*) 'TAKING HARD'
        M4 = M2*M2
        Q4 = Q2*Q2
        Q6 = Q2*Q4
        S52 = S5*S5
        S53 = S5*S52
        S42 = S4*S4
        S4M1 = 1.D0/S4
        S32 = S3*S3
        S3M1 = 1.D0/S3
        SM1 = 1.D0/S
        SP2 = SP*SP
        U62 = U6*U6
        U63 = U6*U62
        U6M1 = 1.D0/U6
        U7M1 = 1.D0/U7
        U7M2 = U7M1*U7M1
        TP2 = TP*TP
        TP3 = TP*TP2
        TPM1 = 1.D0/TP
        TPM2 = TPM1*TPM1
        UP2 = UP*UP
        UP3 = UP*UP2
        T12 = T1*T1
        T13 = T1*T12
        T1M1 = 1.D0/T1
        U1M1 = 1.D0/U1
        U1M2 = U1M1*U1M1
        U1P = U1+Q2
        U1P2 = U1P*U1P

        FGLC_CACF =
     &+ M2*SP*U1P*S3M1*U6*U7M2 * ( 8*T1M1 )
     &+ M2*SP*S5*S4M1*S3M1*TP*U6M1 * ( 4*U1M1 )
     &+ M2*SP*S5*S4M1*S3M1*TP*U7M1 * ( 4*T1M1 )
     &+ M2*SP*S5*S4M1*S3M1*U6M1 * ( 8*T1*U1M1 )
     &+ M2*SP*S5*S4M1*S3M1*U6*U7M1 * ( 8*T1M1 )
     &+ M2*SP*S5*S4M1*U6M1 * ( 8*T1*U1M2 + 8*U1M1 )
     &+ M2*SP*S5*S3M1*U6*U7M2 * ( 8*T1M1 )
     &+ M2*SP*S5*S3M1*U7M1 * ( 8*T1M1 )
     &+ M2*SP*S4M1*S3M1*UP*TP*U7M1 * ( 8*U1M1 )
     &+ M2*SP*S4M1*S3M1*UP*U6*U7M1 * (  - 4*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*SP*S4M1*S3M1*UP*U7M1 * (  - 4*T1*U1M1 )
     &+ M2*SP*S4M1*S3M1*TP*U7M1 * ( 4 + 16*U1M1*Q2 )
     &+ M2*SP*S4M1*S3M1*TP * ( 4*U1M1 )
     &+ M2*SP*S4M1*S3M1*U6*U7M1 * (  - 4*U1M1*Q2 )
     &+ M2*SP*S4M1*S3M1*U7M1 * (  - 4*T1*U1M1*Q2 )
     &+ M2*SP*S4M1*S3*TPM1*U6*U7M1 * (  - 4*T1M1 + 2*U1M1 )
     &+ M2*SP*S4M1*S3*TPM1*U7M1 * ( 2*T1*U1M1 )
     &+ M2*SP*S4M1*S3*TPM1 * (  - 4*T1*U1M2 - 8*U1M1 )
     &+ M2*SP*S4M1*S3*U6M1 * ( 8*T1*U1M2 )
     &+ M2*SP*S4M1*S3*U7M1 * (  - 6*T1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*SP*S4M1*UP*TPM1*U6*U7M1 * (  - 6*U1M1 )
     &+ M2*SP*S4M1*UP*TPM1*U7M1 * (  - 6*T1*U1M1 )
     &+ M2*SP*S4M1*UP*TPM1 * (  - 4*T1*U1M2 )
     &+ M2*SP*S4M1*UP*U6M1 * ( 8*T1*U1M2 )
     &+ M2*SP*S4M1*TPM1*U6*U7M1 * (  - 8 + 8*T1*U1M1 - 6*U1M1*Q2 )
     &+ M2*SP*S4M1*TPM1*U6 * (  - 12*T1*U1M2 )
     &+ M2*SP*S4M1*TPM1*U62*U7M1 * (  - 8*T1M1 + 8*U1M1 )
     &+ M2*SP*S4M1*TPM1*U7M1 * (  - 6*T1*U1M1*Q2 + 4*T12*U1M1 )
     &+ M2*SP*S4M1*TPM1 * (  - 4*T1*U1M2*Q2 - 8*T12*U1M2 )
     &+ M2*SP*S4M1*TP*U6M1 * ( 8*T1*U1M2 + 8*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*SP*S4M1*TP*U7M1 * (  - 4*T1M1 )
     &+ M2*SP*S4M1*U6M1*U7 * ( 8*T1*U1M2 )
     &+ M2*SP*S4M1*U6M1 * ( 16*T1*U1M2*Q2 + 12*T1*U1M1 + 16*T12*U1M2 )
     &+ M2*SP*S4M1*U6*U7M1 * (  - 4*T1M1 + 4*U1M1 )
     &+ M2*SP*S4M1*U7M1 * (  - 2 + 4*T1*U1M1 )
     &+ M2*SP*S4M1 * (  - 8*T1*U1M2 + 2*U1M1 )
     &+ M2*SP*S4*S3M1*TPM1*U6M1 * (  - 4*T1*U1M1 )
     &+ M2*SP*S4*S3M1*TPM1*U6*U7M2 * (  - 4 )
     &+ M2*SP*S4*S3M1*TPM1*U6*U7M1 * ( 2*U1M1 )
     &+ M2*SP*S4*S3M1*TPM1*U7M1 * (  - 8 + 2*T1*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*SP*S4*S3M1*U6M1 * (  - 6*U1M1 )
     &+ M2*SP*S4*S3M1*U6*U7M2 * ( 8*T1M1 )
     &+ M2*SP*S4*TPM1*U6M1*U7M1 * ( 6*T1*U1M1 )
     &+ M2*SP*S4*TPM1*U6M1 * (  - 12*T1*U1M2 )
     &+ M2*SP*S4*TPM1*U6*U7M2 * (  - 4*T1M1 )
     &+ M2*SP*S4*TPM1*U6*U7M1 * ( 2*T1M1*U1M1 )
     &+ M2*SP*S4*TPM1*U7M1 * ( 8*U1M1 )
     &+ M2*SP*S3M1*UP*TPM1*U6*U7M2 * (  - 4 )
     &+ M2*SP*S3M1*UP*TPM1*U6*U7M1 * (  - 6*U1M1 )
     &+ M2*SP*S3M1*UP*TPM1*U7M1 * (  - 6*T1*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*SP*S3M1*UP*U6*U7M2 * ( 8*T1M1 )
     &+ M2*SP*S3M1*TPM1*U6M1 * (  - 8*T12*U1M1 )
     &+ M2*SP*S3M1*TPM1*U6*U7M2 * (  - 12*T1 - 4*Q2 )
     &+ M2*SP*S3M1*TPM1*U6*U7M1 * ( 8*T1*U1M1 - 6*U1M1*Q2 )
     &+ M2*SP*S3M1*TPM1*U62*U7M2 * (  - 8 )
     &+ M2*SP*S3M1*TPM1*U62*U7M1 * ( 4*U1M1 )
     &+ M2*SP*S3M1*TPM1*U7M1 * (  - 6*T1*U1M1*Q2 + 8*T12*U1M1 )
     &+ M2*SP*S3M1*TPM1 * (  - 8*T1*U1M1 )
     &+ M2*SP*S3M1*TP*U6M1 * (  - 4*U1M1 )
     &+ M2*SP*S3M1*TP*U6*U7M2 * ( 8*T1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*SP*S3M1*TP*U7M1 * ( 8*T1M1 )
     &+ M2*SP*S3M1*U6M1 * (  - 4*T1*U1M1 )
     &+ M2*SP*S3M1*U6*U7M2 * (  - 8 + 8*T1M1*Q2 )
     &+ M2*SP*S3M1*U6*U7M1 * ( 12*T1M1 + 4*U1M1 )
     &+ M2*SP*S3M1*U62*U7M2 * ( 16*T1M1 )
     &+ M2*SP*S3M1*U7M1 * ( 2 + 4*T1*U1M1 )
     &+ M2*SP*S3M1 * (  - 2*U1M1 )
     &+ M2*SP*S3*TPM1*U6M1*U7M1 * ( 2*T1*U1M1 )
     &+ M2*SP*S3*TPM1*U6M1 * (  - 4*T1*U1M2 )
     &+ M2*SP*S3*TPM1*U6*U7M2 * (  - 12*T1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*SP*S3*TPM1*U6*U7M1 * ( 6*T1M1*U1M1 )
     &+ M2*SP*S3*TPM1*U7M1 * ( 8*U1M1 )
     &+ M2*SP*UP*TPM1*U6M1*U7M1 * ( 2*T1*U1M1 )
     &+ M2*SP*UP*TPM1*U6M1 * (  - 4*T1*U1M2 )
     &+ M2*SP*UP*TPM1*U6*U7M2 * (  - 4*T1M1 )
     &+ M2*SP*UP*TPM1*U6*U7M1 * ( 2*T1M1*U1M1 )
     &+ M2*SP*UP*TPM1*U7M1 * ( 4*U1M1 )
     &+ M2*SP*TPM1*U6M1*U7M1 * ( 2*T1*U1M1*Q2 - 4*T12*U1M1 )
     &+ M2*SP*TPM1*U6M1 * (  - 4*T1*U1M2*Q2 - 8*T12*U1M2 )
     &+ M2*SP*TPM1*U6*U7M2 * ( 8 - 4*T1M1*Q2 )
        FGLC_CACF = FGLC_CACF
     &+ M2*SP*TPM1*U6*U7M1 * ( 2*T1M1*U1M1*Q2 - 12*U1M1 )
     &+ M2*SP*TPM1*U62*U7M2 * (  - 8*T1M1 )
     &+ M2*SP*TPM1*U62*U7M1 * (  - 4*T1M1*U1M1 )
     &+ M2*SP*TPM1*U7M1 * (  - 4 - 12*T1*U1M1 + 4*U1M1*Q2 )
     &+ M2*SP*TPM1 * ( 8*T1*U1M2 - 4*U1M1 )
     &+ M2*SP*U6M1*U7M1 * (  - 2 )
     &+ M2*SP*U6M1 * (  - 8*T1*U1M2 + 8*U1M1 )
     &+ M2*SP*U6*U7M2 * (  - 8*T1M1 )
     &+ M2*SP*U7M1 * ( 8*T1M1 + 32*U1M1 )
     &+ M2*SP * (  - 2*T1M1*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*SP2*S5*S4M1*S3M1*U7M1 * (  - 8*U1M1 )
     &+ M2*SP2*S5*U6M1*U7M1 * (  - 8*T1M1*U1M1 )
     &+ M2*SP2*S4M1*S3*TPM1*U7M1 * ( 2*U1M1 )
     &+ M2*SP2*S4M1*TPM1*U6*U7M1 * ( 8*U1M1 )
     &+ M2*SP2*S4M1*TPM1*U7M1 * ( 4*T1*U1M1 )
     &+ M2*SP2*S4M1*TPM1 * (  - 4*T1*U1M2 )
     &+ M2*SP2*S4M1*U6M1 * ( 8*T1*U1M2 )
     &+ M2*SP2*S4M1*U7M1 * (  - 4*U1M1 )
     &+ M2*SP2*S4*S3M1*TPM1*U7M1 * ( 2*U1M1 )
     &+ M2*SP2*S4*TPM1*U6M1*U7M1 * ( 6*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*SP2*S4*TPM1*U7M1 * ( 2*T1M1*U1M1 )
     &+ M2*SP2*S3M1*TPM1*U6*U7M2 * (  - 4 )
     &+ M2*SP2*S3M1*TPM1*U6*U7M1 * ( 4*U1M1 )
     &+ M2*SP2*S3M1*TPM1*U7M1 * ( 8*T1*U1M1 )
     &+ M2*SP2*S3M1*U6*U7M2 * ( 8*T1M1 )
     &+ M2*SP2*S3M1*U7M1 * (  - 4*U1M1 )
     &+ M2*SP2*S3*TPM1*U6M1*U7M1 * ( 2*U1M1 )
     &+ M2*SP2*S3*TPM1*U7M1 * ( 6*T1M1*U1M1 )
     &+ M2*SP2*TPM1*U6M1*U7M1 * (  - 4*T1*U1M1 )
     &+ M2*SP2*TPM1*U6M1 * (  - 4*T1*U1M2 )
        FGLC_CACF = FGLC_CACF
     &+ M2*SP2*TPM1*U6*U7M2 * (  - 4*T1M1 )
     &+ M2*SP2*TPM1*U6*U7M1 * (  - 4*T1M1*U1M1 )
     &+ M2*SP2*TPM1*U7M1 * (  - 20*U1M1 )
     &+ M2*U1P*S4M1*S3M1*TP*U6*U7M1 * (  - 8*T1M1 )
     &+ M2*U1P*S4M1*S3M1*TP*U7M1 * ( 4 )
     &+ M2*U1P*S4M1*S3M1*TP2*U7M1 * (  - 4*T1M1 )
     &+ M2*U1P*S4M1*TP*U7M1 * (  - 2*T1M1 )
     &+ M2*U1P*S4M1*U6*U7M1 * (  - 4*T1M1 )
     &+ M2*U1P*S3M1*TP*U7M1 * ( 8*T1M1 )
     &+ M2*U1P*S3M1*U62*U7M2 * ( 8*T1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*U1P*S3M1*U7M1 * ( 4 )
     &+ M2*S5*S4M1*S3M1*TP*U6M1 * (  - 16 - 8*T1*U1M1 )
     &+ M2*S5*S4M1*S3M1*TP*U6*U7M1 * (  - 8*T1M1 )
     &+ M2*S5*S4M1*S3M1*TP * (  - 16*T1M1 )
     &+ M2*S5*S4M1*S3M1*TP2*U6M1 * (  - 8*T1M1 )
     &+ M2*S5*S4M1*S3M1*U6M1 * ( 8*T12*U1M1 )
     &+ M2*S5*S4M1*S3M1*U6*U7M1 * (  - 8 )
     &+ M2*S5*S4M1*S3M1*U62*U7M1 * ( 8*T1M1 )
     &+ M2*S5*S4M1*S3M1 * (  - 32 - 8*T1*U1M1 )
     &+ M2*S5*S4M1*U6M1 * ( 8*T1*U1M1 + 8*T12*U1M2 )
        FGLC_CACF = FGLC_CACF
     &+ M2*S5*S4M1*U6*U7M1 * (  - 4*T1M1 )
     &+ M2*S5*S4M1 * (  - 4*U1M1 )
     &+ M2*S5*S3M1*U6M1 * (  - 4*T1*U1M1 )
     &+ M2*S5*S3M1*U6*U7M1 * ( 8*T1M1 )
     &+ M2*S5*S3M1*U62*U7M2 * ( 8*T1M1 )
     &+ M2*S5*S3M1*U7M1 * (  - 4 )
     &+ M2*S4M1*S3M1*UP*TP*U7M1 * ( 4 )
     &+ M2*S4M1*S3M1*UP*TP * ( 4*U1M1 )
     &+ M2*S4M1*S3M1*UP*U6M1 * ( 4*T12*U1M1 )
     &+ M2*S4M1*S3M1*UP*U6*U7M1 * ( 8 + 8*T1*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*S4M1*S3M1*UP*U6 * (  - 4*U1M1 )
     &+ M2*S4M1*S3M1*UP*U62*U7M1 * ( 4*T1M1 - 12*U1M1 )
     &+ M2*S4M1*S3M1*UP*U7M1 * (  - 4*T1 - 12*T12*U1M1 )
     &+ M2*S4M1*S3M1*UP * ( 8*T1*U1M1 )
     &+ M2*S4M1*S3M1*TP*U6M1*U7 * (  - 8*T1*U1M1 )
     &+ M2*S4M1*S3M1*TP*U6M1 * (  - 12*T1*U1M1*Q2 - 4*T1 )
     &+ M2*S4M1*S3M1*TP*U6*U7M1 * (  - 4 - 4*T1M1*Q2 + 8*U1M1*Q2 )
     &+ M2*S4M1*S3M1*TP*U6 * (  - 4*T1M1 + 12*U1M1 )
     &+ M2*S4M1*S3M1*TP*U7M1 * ( 8*T1*U1M1*Q2 + 12*T1 + 4*Q2 )
     &+ M2*S4M1*S3M1*TP*U7 * ( 4*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*S4M1*S3M1*TP * (  - 4*T1*U1M1 + 8*U1M1*Q2 )
     &+ M2*S4M1*S3M1*TP2*U6M1*U7 * (  - 4*U1M1 )
     &+ M2*S4M1*S3M1*TP2*U6M1 * (  - 4*U1M1*Q2 )
     &+ M2*S4M1*S3M1*TP2*U7M1 * ( 8*U1M1*Q2 )
     &+ M2*S4M1*S3M1*U6M1 * ( 4*T12*U1M1*Q2 )
     &+ M2*S4M1*S3M1*U6*U7M1 * ( 24*T1*U1M1*Q2 + 8*T1 + 8*Q2 )
     &+ M2*S4M1*S3M1*U6 * ( 8*T1*U1M1 - 4*U1M1*Q2 )
     &+ M2*S4M1*S3M1*U62*U7M1 * (  - 8 + 4*T1M1*Q2 - 20*U1M1*Q2 )
     &+ M2*S4M1*S3M1*U7M1 * (  - 4*T1*Q2 - 20*T12*U1M1*Q2 )
     &+ M2*S4M1*S3M1 * ( 8*T1*U1M1*Q2 - 8*T12*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*S4M1*S3*TPM1*U6*U7M1 * ( 8 + 4*T1*U1M1 )
     &+ M2*S4M1*S3*TPM1*U6 * ( 4*U1M1 )
     &+ M2*S4M1*S3*TPM1*U62*U7M1 * (  - 4*T1M1 )
     &+ M2*S4M1*S3*TPM1 * (  - 8*T1*U1M1 - 4*T12*U1M2 )
     &+ M2*S4M1*S3*U6M1 * ( 8*T12*U1M2 )
     &+ M2*S4M1*S3*U6*U7M1 * (  - 8*T1M1 )
     &+ M2*S4M1*UP*TPM1*U6*U7M1 * ( 4 )
     &+ M2*S4M1*UP*TPM1*U6 * (  - 4*U1M1 )
     &+ M2*S4M1*UP*TPM1*U62*U7M1 * (  - 6*U1M1 )
     &+ M2*S4M1*UP*TPM1*U7M1 * (  - 6*T12*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*S4M1*UP*TPM1 * (  - 4*T12*U1M2 )
     &+ M2*S4M1*UP*U6M1 * ( 8*T12*U1M2 )
     &+ M2*S4M1*UP*U6*U7M1 * (  - 2*T1M1 )
     &+ M2*S4M1*UP*U7M1 * ( 2 )
     &+ M2*S4M1*UP * (  - 8*U1M1 )
     &+ M2*S4M1*TPM1*U6*U7M1 * ( 4*T12*U1M1 + 4*Q2 )
     &+ M2*S4M1*TPM1*U6 * (  - 12*T12*U1M2 - 4*U1M1*Q2 )
     &+ M2*S4M1*TPM1*U62*U7M1 * ( 12*T1*U1M1 - 6*U1M1*Q2 )
     &+ M2*S4M1*TPM1*U62 * ( 8*U1M1 )
     &+ M2*S4M1*TPM1*U63*U7M1 * (  - 8*T1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*S4M1*TPM1*U7M1 * (  - 6*T12*U1M1*Q2 )
     &+ M2*S4M1*TPM1 * (  - 4*T12*U1M2*Q2 - 4*T13*U1M2 )
     &+ M2*S4M1*TP*U6M1*U7 * ( 8*U1M1 )
     &+ M2*S4M1*TP*U6M1 * ( 8*T12*U1M2 + 8*U1M1*Q2 )
     &+ M2*S4M1*TP*U6*U7M1 * (  - 8*T1M1 )
     &+ M2*S4M1*TP*U7M1 * ( 2*T1M1*Q2 )
     &+ M2*S4M1*TP * ( 2*T1M1 + 8*U1M1 )
     &+ M2*S4M1*U6M1*U7 * ( 8*T12*U1M2 )
     &+ M2*S4M1*U6M1 * ( 16*T12*U1M2*Q2 + 16*T12*U1M1 + 8*T13*U1M2 )
     &+ M2*S4M1*U6*U7M1 * ( 10 - 2*T1M1*Q2 + 16*T1*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*S4M1*U6 * ( 8*T1M1 + 22*U1M1 )
     &+ M2*S4M1*U7M1 * ( 6*T1 + 2*Q2 )
     &+ M2*S4M1*U7 * ( 4*U1M1 )
     &+ M2*S4M1 * (  - 8 + 2*T1*U1M1 - 8*T12*U1M2 - 4*U1M1*Q2 )
     &+ M2*S4*S3M1*TPM1*U6M1 * (  - 4*T12*U1M1 )
     &+ M2*S4*S3M1*TPM1*U6*U7M1 * (  - 8 + 4*T1*U1M1 )
     &+ M2*S4*S3M1*TPM1*U62*U7M2 * (  - 4 )
     &+ M2*S4*S3M1*TPM1*U7M1 * ( 4*T1 )
     &+ M2*S4*S3M1*TPM1 * ( 8*T1*U1M1 )
     &+ M2*S4*S3M1*U6M1 * (  - 8*T1*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*S4*S3M1*U62*U7M2 * ( 8*T1M1 )
     &+ M2*S4*TPM1*U6M1 * (  - 12*T12*U1M2 )
     &+ M2*S4*TPM1*U6*U7M1 * ( 4*U1M1 )
     &+ M2*S4*TPM1*U62*U7M2 * (  - 4*T1M1 )
     &+ M2*S4*TPM1*U7M1 * ( 12*T1*U1M1 )
     &+ M2*S3M1*UP*TPM1*U62*U7M2 * (  - 4 )
     &+ M2*S3M1*UP*TPM1*U62*U7M1 * (  - 6*U1M1 )
     &+ M2*S3M1*UP*TPM1*U7M1 * (  - 4*T1 - 6*T12*U1M1 )
     &+ M2*S3M1*UP*TPM1 * ( 4*T1*U1M1 )
     &+ M2*S3M1*UP*U6M1 * (  - 2*T1*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*S3M1*UP*U62*U7M2 * ( 8*T1M1 )
     &+ M2*S3M1*UP*U7M1 * (  - 8 )
     &+ M2*S3M1*UP * ( 2*U1M1 )
     &+ M2*S3M1*TPM1*U6M1 * (  - 8*T13*U1M1 )
     &+ M2*S3M1*TPM1*U6*U7M1 * ( 12*T12*U1M1 )
     &+ M2*S3M1*TPM1*U62*U7M2 * (  - 12*T1 - 4*Q2 )
     &+ M2*S3M1*TPM1*U62*U7M1 * ( 4*T1*U1M1 - 6*U1M1*Q2 )
     &+ M2*S3M1*TPM1*U63*U7M2 * (  - 4 )
     &+ M2*S3M1*TPM1*U7M1 * (  - 4*T1*Q2 - 6*T12*U1M1*Q2 + 8*T12 )
     &+ M2*S3M1*TPM1 * ( 4*T1*U1M1*Q2 )
        FGLC_CACF = FGLC_CACF
     &+ M2*S3M1*TP*U6M1*U7 * (  - 2*U1M1 )
     &+ M2*S3M1*TP*U6M1 * ( 2 - 8*T1*U1M1 )
     &+ M2*S3M1*TP*U62*U7M2 * ( 8*T1M1 )
     &+ M2*S3M1*TP*U7M1 * ( 8 )
     &+ M2*S3M1*U6M1*U7 * (  - 4*T1*U1M1 )
     &+ M2*S3M1*U6M1 * (  - 6*T1*U1M1*Q2 + 8*T1 )
     &+ M2*S3M1*U6*U7M1 * ( 2 + 16*T1*U1M1 )
     &+ M2*S3M1*U6 * ( 6*U1M1 )
     &+ M2*S3M1*U62*U7M2 * (  - 8 + 8*T1M1*Q2 )
     &+ M2*S3M1*U62*U7M1 * ( 16*T1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*S3M1*U63*U7M2 * ( 8*T1M1 )
     &+ M2*S3M1*U7M1 * ( 22*T1 - 8*Q2 )
     &+ M2*S3M1 * (  - 8 + 10*T1*U1M1 + 2*U1M1*Q2 )
     &+ M2*S3*TPM1*U6M1 * (  - 4*T12*U1M2 )
     &+ M2*S3*TPM1*U6*U7M1 * ( 12*U1M1 )
     &+ M2*S3*TPM1*U62*U7M2 * (  - 12*T1M1 )
     &+ M2*S3*TPM1*U7M1 * ( 4*T1*U1M1 )
     &+ M2*UP*TPM1*U6M1*U7M1 * ( 2*T12*U1M1 )
     &+ M2*UP*TPM1*U6M1 * (  - 4*T12*U1M2 )
     &+ M2*UP*TPM1*U6*U7M1 * ( 2*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*UP*TPM1*U62*U7M2 * (  - 4*T1M1 )
     &+ M2*UP*TPM1*U62*U7M1 * ( 2*T1M1*U1M1 )
     &+ M2*UP*TPM1*U7M1 * ( 2*T1*U1M1 )
     &+ M2*TPM1*U6M1*U7M1 * ( 2*T12*U1M1*Q2 )
     &+ M2*TPM1*U6M1 * (  - 4*T12*U1M2*Q2 - 4*T13*U1M2 )
     &+ M2*TPM1*U6*U7M1 * (  - 16*T1*U1M1 + 2*U1M1*Q2 )
     &+ M2*TPM1*U62*U7M2 * ( 8 - 4*T1M1*Q2 )
     &+ M2*TPM1*U62*U7M1 * ( 2*T1M1*U1M1*Q2 + 4*U1M1 )
     &+ M2*TPM1*U63*U7M2 * (  - 4*T1M1 )
     &+ M2*TPM1*U7M1 * ( 2*T1*U1M1*Q2 + 4*T12*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M2*TPM1 * ( 8*T12*U1M2 )
     &+ M2*U6M1*U7M1 * (  - 8*T1*U1M1*Q2 - 2*T1 )
     &+ M2*U6M1 * ( 2*T1*U1M1 - 8*T12*U1M2 )
     &+ M2*U6*U7M1 * (  - 8*T1M1*U1M1*Q2 + 2*T1M1 + 16*U1M1 )
     &+ M2*U6 * (  - 2*T1M1*U1M1 )
     &+ M2*U62*U7M2 * (  - 8*T1M1 )
     &+ M2*U7M1 * ( 8 + 16*T1*U1M1 + 16*U1M1*Q2 )
     &+ M2 * ( 8*U1M1 )
     &+ M4*SP*S4M1*S3M1*TP*U6M1 * (  - 16*U1M1 )
     &+ M4*SP*S4M1*S3M1*TP*U7M1 * (  - 16*T1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M4*SP*S4M1*S3M1*U6M1 * (  - 16*T1*U1M1 )
     &+ M4*SP*S4M1*S3M1*U6*U7M1 * (  - 16*T1M1 + 16*U1M1 )
     &+ M4*SP*S4M1*S3M1*U7M1 * ( 16*T1*U1M1 )
     &+ M4*SP*S4M1*U6M1 * (  - 32*T1*U1M2 - 16*U1M1 )
     &+ M4*SP*S3M1*U6*U7M2 * (  - 32*T1M1 )
     &+ M4*SP*S3M1*U7M1 * (  - 16*T1M1 )
     &+ M4*SP*U6M1*U7M1 * ( 16*U1M1 )
     &+ M4*SP*U7M1 * ( 16*T1M1*U1M1 )
     &+ M4*SP2*S4M1*S3M1*U7M1 * ( 16*U1M1 )
     &+ M4*SP2*U6M1*U7M1 * ( 16*T1M1*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ M4*S4M1*S3M1*TP*U6M1 * ( 16 - 16*T1*U1M1 )
     &+ M4*S4M1*S3M1*TP*U6*U7M1 * (  - 16*T1M1 )
     &+ M4*S4M1*S3M1*TP * ( 16*T1M1 )
     &+ M4*S4M1*S3M1*TP2*U6M1 * ( 16*T1M1 )
     &+ M4*S4M1*S3M1*U6M1 * (  - 16*T12*U1M1 )
     &+ M4*S4M1*S3M1*U6*U7M1 * ( 16 + 32*T1*U1M1 )
     &+ M4*S4M1*S3M1*U62*U7M1 * (  - 16*T1M1 )
     &+ M4*S4M1*S3M1 * ( 32 + 16*T1*U1M1 )
     &+ M4*S4M1*TP*U6M1 * ( 16*U1M1 )
     &+ M4*S4M1*U6M1 * (  - 16*T1*U1M1 - 32*T12*U1M2 )
        FGLC_CACF = FGLC_CACF
     &+ M4*S4M1 * ( 16*U1M1 )
     &+ M4*S3M1*TP*U7M1 * ( 16*T1M1 )
     &+ M4*S3M1*U6*U7M1 * (  - 16*T1M1 )
     &+ M4*S3M1*U62*U7M2 * (  - 32*T1M1 )
     &+ M4*S3M1*U7M1 * ( 16 )
     &+ M4*U7M1 * ( 32*U1M1 )
     &+ SP*U1P*S3M1*TPM1*U6*U7M2 * (  - 8*T1 )
     &+ SP*U1P*S3M1*TP*U6*U7M2 * (  - 8*T1M1 )
     &+ SP*U1P*S3M1*U6*U7M2 * (  - 14 )
     &+ SP*U1P*S3*TPM1*U6*U7M2 * (  - 8*T1M1 )
        FGLC_CACF = FGLC_CACF
     &+ SP*U1P*TPM1*U6*U7M2 * (  - 8 )
     &+ SP*U1P*U6*U7M2 * (  - 14*T1M1 )
     &+ SP*S5*S4M1*S3*TPM1*U6*U7M1 * ( 2*T1M1 )
     &+ SP*S5*S4M1*UP*TPM1*U6*U7M1 * ( 4*U1M1 )
     &+ SP*S5*S4M1*UP*U7M1 * ( 2*U1M1 )
     &+ SP*S5*S4M1*TPM1*U6*U7M1 * ( 4 + 4*T1*U1M1 + 4*U1M1*Q2 )
     &+ SP*S5*S4M1*TPM1*U6 * (  - 8*T1*U1M2 )
     &+ SP*S5*S4M1*TPM1*U62*U7M1 * ( 4*U1M1 )
     &+ SP*S5*S4M1*TP*U6M1 * (  - 8*T1*U1M2 - 4*U1M1 )
     &+ SP*S5*S4M1*U7M1 * ( 2 - 2*T1*U1M1 + 2*U1M1*Q2 )
        FGLC_CACF = FGLC_CACF
     &+ SP*S5*S4M1 * (  - 14*T1*U1M2 - 2*U1M1 )
     &+ SP*S5*S4*S3M1*TPM1*U6M1 * ( 2*T1*U1M1 )
     &+ SP*S5*S4*TPM1*U6M1*U7M1 * ( 4*T1*U1M1 )
     &+ SP*S5*S4*TPM1*U6M1 * (  - 8*T1*U1M2 )
     &+ SP*S5*S4*TPM1*U7M1 * ( 4*U1M1 )
     &+ SP*S5*S3M1*UP*TPM1*U7M1 * ( 4*T1*U1M1 )
     &+ SP*S5*S3M1*UP*U7M1 * ( 2*U1M1 )
     &+ SP*S5*S3M1*TPM1*U6*U7M2 * (  - 8*T1 )
     &+ SP*S5*S3M1*TPM1*U6*U7M1 * ( 4*T1*U1M1 )
     &+ SP*S5*S3M1*TPM1*U7M1 * ( 4*T1*U1M1*Q2 + 4*T12*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ SP*S5*S3M1*TPM1 * ( 4*T1*U1M1 )
     &+ SP*S5*S3M1*TP*U6*U7M2 * (  - 8*T1M1 )
     &+ SP*S5*S3M1*TP*U7M1 * (  - 4*T1M1 )
     &+ SP*S5*S3M1*U6*U7M2 * (  - 14 )
     &+ SP*S5*S3M1*U6*U7M1 * (  - 2*U1M1 )
     &+ SP*S5*S3M1*U7M1 * (  - 2 + 2*U1M1*Q2 )
     &+ SP*S5*S3M1 * ( 2*U1M1 )
     &+ SP*S5*S3*TPM1*U6*U7M2 * (  - 8*T1M1 )
     &+ SP*S5*S3*TPM1*U6*U7M1 * ( 4*T1M1*U1M1 )
     &+ SP*S5*S3*TPM1*U7M1 * ( 4*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ SP*S5*TPM1*U6*U7M2 * (  - 8 )
     &+ SP*S5*TPM1*U6*U7M1 * ( 12*U1M1 )
     &+ SP*S5*TPM1*U7M1 * ( 2 + 12*T1*U1M1 )
     &+ SP*S5*TPM1 * (  - 8*T1*U1M2 + 2*U1M1 )
     &+ SP*S5*U6M1 * (  - 14*T1*U1M2 - 4*U1M1 )
     &+ SP*S5*U6*U7M2 * (  - 14*T1M1 )
     &+ SP*S5*U7M1 * (  - 4*T1M1 - 4*U1M1 )
     &+ SP*S52*S4M1*S3M1*U6*U7M1 * (  - 4*U1M1 )
     &+ SP*S52*S4M1*S3M1*U7M1 * (  - 4*T1*U1M1 )
     &+ SP*S52*U6M1*U7M1 * (  - 4*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ SP*S52*U7M1 * (  - 4*T1M1*U1M1 )
     &+ SP*S4M1*S3*TPM1*U6*U7M1 * ( 2 + 2*T1*U1M1 - 4*U1M1*Q2 )
     &+ SP*S4M1*S3*TPM1*U6 * (  - 2*T1*U1M2 - 6*U1M1 )
     &+ SP*S4M1*S3*U7M1 * (  - 2*U1M1*Q2 )
     &+ SP*S4M1*S3 * (  - 2*U1M1 )
     &+ SP*S4M1*S32*TPM1*U6*U7M1 * ( 2*T1M1 )
     &+ SP*S4M1*UP*TPM1*U6*U7M1 * (  - 2*T1*U1M1 )
     &+ SP*S4M1*UP*TPM1*U6 * (  - 2*T1*U1M2 )
     &+ SP*S4M1*TPM1*U6*U7M1 * (  - 2*T1*U1M1*Q2 )
     &+ SP*S4M1*TPM1*U6*U7 * (  - 8*T1*U1M2 )
        FGLC_CACF = FGLC_CACF
     &+ SP*S4M1*TPM1*U6 * (  - 10*T1*U1M2*Q2 )
     &+ SP*S4M1*TP*U6M1*U7 * (  - 8*T1*U1M2 )
     &+ SP*S4M1*TP*U6M1 * (  - 8*T1*U1M2*Q2 )
     &+ SP*S4M1*U7M1 * ( 2*T1*U1M1*Q2 )
     &+ SP*S4M1*U7 * (  - 14*T1*U1M2 )
     &+ SP*S4M1 * (  - 14*T1*U1M2*Q2 + 2*T1*U1M1 )
     &+ SP*S4*S3M1*TPM1*U6*U7M2 * (  - 2*T1 )
     &+ SP*S4*S3M1*TPM1*U6*U7M1 * ( 2*T1*U1M1 )
     &+ SP*S4*S3M1*TPM1*U7M1 * (  - 4*T1*U1M1*Q2 - 6*T1 )
     &+ SP*S4*S3M1*TPM1 * ( 2*T1*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ SP*S4*S3M1*U7M1 * (  - 2 - 2*U1M1*Q2 )
     &+ SP*S4*TPM2*U6*U7M2 * ( 8*T1 )
     &+ SP*S4*TPM2*U6*U7M1 * (  - 16*T1*U1M1 )
     &+ SP*S4*TPM2*U7M1 * (  - 8*T12*U1M1 )
     &+ SP*S4*TPM2 * ( 16*T12*U1M2 )
     &+ SP*S4*TPM1*U6M1*U7 * (  - 8*T1*U1M2 )
     &+ SP*S4*TPM1*U6M1 * (  - 8*T1*U1M2*Q2 - 4*T12*U1M2 )
     &+ SP*S4*TPM1*U6*U7M2 * ( 2 )
     &+ SP*S4*TPM1*U6*U7M1 * (  - 4*U1M1 )
     &+ SP*S4*TPM1*U7M1 * ( 4 + 2*T1*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ SP*S4*TPM1 * (  - 2*U1M1 )
     &+ SP*S42*S3M1*TPM1*U6M1 * ( 2*T1*U1M1 )
     &+ SP*S3M1*UP*TPM1*U6*U7M2 * (  - 2*T1 )
     &+ SP*S3M1*UP*TPM1*U6*U7M1 * (  - 2*T1*U1M1 )
     &+ SP*S3M1*TPM1*U6*U7M2 * (  - 2*T1*Q2 )
     &+ SP*S3M1*TPM1*U6*U7M1 * (  - 2*T1*U1M1*Q2 )
     &+ SP*S3M1*U6*U7M1 * ( 2 + 2*U1M1*Q2 )
     &+ SP*S3*TPM2*U6*U7M1 * (  - 16*T1*U1M1 )
     &+ SP*S3*TPM2*U6 * ( 8*T1*U1M2 )
     &+ SP*S3*TPM2*U62*U7M2 * ( 16 )
        FGLC_CACF = FGLC_CACF
     &+ SP*S3*TPM2*U62*U7M1 * (  - 8*U1M1 )
     &+ SP*S3*TPM1*U6*U7M1 * ( 2*U1M1 )
     &+ SP*S3*TPM1*U62*U7M2 * (  - 4*T1M1 )
     &+ SP*S3*TPM1*U7M1 * (  - 2 - 4*T1*U1M1 )
     &+ SP*S3*TPM1 * ( 2*T1*U1M2 + 4*U1M1 )
     &+ SP*UP*TPM2*U6*U7M2 * ( 8*T1 )
     &+ SP*UP*TPM2*U6*U7M1 * (  - 16*T1*U1M1 )
     &+ SP*UP*TPM2*U6 * ( 8*T1*U1M2 )
     &+ SP*UP*TPM1*U6*U7M2 * ( 2 )
     &+ SP*UP*TPM1*U6*U7M1 * (  - 2*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ SP*UP*TPM1*U7M1 * (  - 2*T1*U1M1 )
     &+ SP*UP*TPM1 * ( 2*T1*U1M2 )
     &+ SP*TPM2*U6*U7M2 * ( 8*T1*Q2 )
     &+ SP*TPM2*U6*U7M1 * (  - 16*T1*U1M1*Q2 )
     &+ SP*TPM2*U6 * ( 8*T1*U1M2*Q2 )
     &+ SP*TPM1*U6*U7M2 * ( 2*Q2 )
     &+ SP*TPM1*U6*U7M1 * ( 14 - 4*T1*U1M1 + 10*U1M1*Q2 )
     &+ SP*TPM1*U6 * (  - 2*U1M1 )
     &+ SP*TPM1*U62*U7M2 * ( 4 )
     &+ SP*TPM1*U62*U7M1 * ( 2*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ SP*TPM1*U7M1 * ( 10*T1*U1M1*Q2 - 2*T1 + 2*T12*U1M1 )
     &+ SP*TPM1*U7 * (  - 8*T1*U1M2 )
     &+ SP*TPM1 * (  - 6*T1*U1M2*Q2 + 14*T1*U1M1 + 4*T12*U1M2 )
     &+ SP*U6M1*U7 * (  - 14*T1*U1M2 )
     &+ SP*U6M1 * (  - 14*T1*U1M2*Q2 )
     &+ SP2*S5*TPM1*U7M1 * ( 8*U1M1 )
     &+ SP2*S4*TPM2*U7M1 * (  - 8*T1*U1M1 )
     &+ SP2*S4*TPM2 * ( 8*T1*U1M2 )
     &+ SP2*S4*TPM1*U6M1 * (  - 2*T1*U1M2 )
     &+ SP2*S3*TPM2*U6*U7M2 * ( 8 )
        FGLC_CACF = FGLC_CACF
     &+ SP2*S3*TPM2*U6*U7M1 * (  - 8*U1M1 )
     &+ SP2*S3*TPM1*U6*U7M2 * (  - 2*T1M1 )
     &+ SP2*TPM1*U6*U7M2 * ( 2 )
     &+ SP2*TPM1*U6*U7M1 * ( 2*U1M1 )
     &+ SP2*TPM1*U7M1 * ( 2*T1*U1M1 )
     &+ SP2*TPM1 * ( 2*T1*U1M2 )
     &+ U1P*S5*S4M1*S3M1*TP*U6*U7M1 * ( 4*T1M1 )
     &+ U1P*S5*S4M1*U6*U7M1 * ( 2*T1M1 )
     &+ U1P*S5*S3M1*TP*U7M1 * (  - 4*T1M1 )
     &+ U1P*S5*S3M1*U7M1 * (  - 2 )
        FGLC_CACF = FGLC_CACF
     &+ U1P*S4M1*S3*TPM1*U62*U7M1 * (  - 4*T1M1 )
     &+ U1P*S4M1*S3*U6*U7M1 * (  - 2*T1M1 )
     &+ U1P*S4M1*U62*U7M1 * (  - 4*T1M1 )
     &+ U1P*S4*S3M1*U7M1 * ( 2 )
     &+ U1P*S3M1*TPM1*U6*U7M1 * (  - 4*T1 )
     &+ U1P*S3M1*TPM1*U62*U7M2 * (  - 8*T1 )
     &+ U1P*S3M1*TP*U6*U7M1 * (  - 4*T1M1 )
     &+ U1P*S3M1*TP*U62*U7M2 * (  - 8*T1M1 )
     &+ U1P*S3M1*U6*U7M1 * (  - 12 )
     &+ U1P*S3M1*U62*U7M2 * (  - 14 )
        FGLC_CACF = FGLC_CACF
     &+ U1P*S3*TPM1*U62*U7M2 * (  - 8*T1M1 )
     &+ U1P*TPM1*U62*U7M2 * (  - 8 )
     &+ U1P*U62*U7M2 * (  - 14*T1M1 )
     &+ S5*S4M1*S3M1*UP*U6*U7M1 * (  - 4 )
     &+ S5*S4M1*S3M1*UP * (  - 4*T1*U1M1 )
     &+ S5*S4M1*S3M1*TP*U6M1*U7 * ( 4*T1*U1M1 )
     &+ S5*S4M1*S3M1*TP*U6M1 * ( 4*T1*U1M1*Q2 )
     &+ S5*S4M1*S3M1*U6*U7M1 * (  - 8*T1*U1M1*Q2 - 4*T1 - 4*Q2 )
     &+ S5*S4M1*S3M1*U6 * (  - 4*T1*U1M1 )
     &+ S5*S4M1*S3M1*U62*U7M1 * ( 4 + 4*U1M1*Q2 )
        FGLC_CACF = FGLC_CACF
     &+ S5*S4M1*S3M1*U7M1 * ( 4*T12*U1M1*Q2 )
     &+ S5*S4M1*S3M1 * (  - 4*T1*U1M1*Q2 + 4*T12*U1M1 )
     &+ S5*S4M1*S3*TPM1*U6 * ( 2*U1M1 )
     &+ S5*S4M1*S3*TPM1*U62*U7M1 * (  - 2*T1M1 )
     &+ S5*S4M1*S3*U6*U7M1 * (  - 2*T1M1 )
     &+ S5*S4M1*S3 * ( 6*U1M1 )
     &+ S5*S4M1*UP*TPM1*U6*U7M1 * (  - 2 + 4*T1*U1M1 )
     &+ S5*S4M1*UP*TPM1*U6 * ( 2*U1M1 )
     &+ S5*S4M1*UP * ( 4*U1M1 )
     &+ S5*S4M1*TPM1*U6*U7M1 * ( 4*T1*U1M1*Q2 - 2*Q2 )
        FGLC_CACF = FGLC_CACF
     &+ S5*S4M1*TPM1*U6 * (  - 4*T1*U1M1 - 8*T12*U1M2 + 2*U1M1*Q2 )
     &+ S5*S4M1*TPM1*U62*U7M1 * ( 4 + 8*T1*U1M1 )
     &+ S5*S4M1*TP*U6M1*U7 * (  - 4*U1M1 )
     &+ S5*S4M1*TP*U6M1 * (  - 8*T1*U1M1 - 8*T12*U1M2 - 4*U1M1*Q2 )
     &+ S5*S4M1*TP*U7M1 * ( 2*U1M1*Q2 )
     &+ S5*S4M1*U6*U7M1 * ( 2 - 2*T1*U1M1 + 4*U1M1*Q2 )
     &+ S5*S4M1*U6 * (  - 4*T1M1 )
     &+ S5*S4M1*U62*U7M1 * (  - 4*T1M1 )
     &+ S5*S4M1*U7M1 * (  - 4*T1*U1M1*Q2 )
     &+ S5*S4M1*U7 * (  - 2*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ S5*S4M1 * ( 4 - 18*T1*U1M1 - 14*T12*U1M2 + 2*U1M1*Q2 )
     &+ S5*S4*S3M1*TPM1*U6M1 * (  - 2*T12*U1M1 )
     &+ S5*S4*S3M1*TPM1*U7M1 * ( 2*T1 )
     &+ S5*S4*S3M1*U6M1 * (  - 2*T1*U1M1 )
     &+ S5*S4*S3M1*U7M1 * ( 6 )
     &+ S5*S4*TPM1*U6M1 * (  - 8*T12*U1M2 )
     &+ S5*S4*TPM1*U7M1 * ( 8*T1*U1M1 )
     &+ S5*S3M1*UP*TPM1*U6*U7M1 * ( 4*T1*U1M1 )
     &+ S5*S3M1*UP*TPM1*U7M1 * ( 2*T1 )
     &+ S5*S3M1*UP*TPM1 * (  - 2*T1*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ S5*S3M1*UP*U7M1 * ( 4 )
     &+ S5*S3M1*TPM1*U6*U7M1 * ( 4*T1*U1M1*Q2 - 4*T1 + 8*T12*U1M1 )
     &+ S5*S3M1*TPM1*U62*U7M2 * (  - 8*T1 )
     &+ S5*S3M1*TPM1*U7M1 * ( 2*T1*Q2 )
     &+ S5*S3M1*TPM1 * (  - 2*T1*U1M1*Q2 + 4*T12*U1M1 )
     &+ S5*S3M1*TP*U6*U7M1 * (  - 8*T1M1 )
     &+ S5*S3M1*TP*U62*U7M2 * (  - 8*T1M1 )
     &+ S5*S3M1*TP*U7M1 * ( 2*U1M1*Q2 )
     &+ S5*S3M1*U6M1*U7 * ( 2*T1*U1M1 )
     &+ S5*S3M1*U6M1 * ( 2*T1*U1M1*Q2 - 4*T1 - 4*T12*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ S5*S3M1*U6*U7M1 * (  - 18 - 2*T1*U1M1 - 4*U1M1*Q2 )
     &+ S5*S3M1*U62*U7M2 * (  - 14 )
     &+ S5*S3M1*U7M1 * ( 4*T1*U1M1*Q2 + 4*Q2 )
     &+ S5*S3M1 * ( 4 + 2*T1*U1M1 )
     &+ S5*S3*TPM1*U6*U7M1 * ( 8*U1M1 )
     &+ S5*S3*TPM1*U62*U7M2 * (  - 8*T1M1 )
     &+ S5*TPM1*U6*U7M1 * ( 16*T1*U1M1 )
     &+ S5*TPM1*U62*U7M2 * (  - 8 )
     &+ S5*TPM1 * (  - 8*T12*U1M2 )
     &+ S5*U6M1*U7M1 * ( 4*T1*U1M1*Q2 )
        FGLC_CACF = FGLC_CACF
     &+ S5*U6M1 * (  - 14*T12*U1M2 )
     &+ S5*U6*U7M1 * ( 4*T1M1*U1M1*Q2 - 2*U1M1 )
     &+ S5*U62*U7M2 * (  - 14*T1M1 )
     &+ S5*U7M1 * (  - 4 - 2*T1*U1M1 - 8*U1M1*Q2 )
     &+ S5 * (  - 4*U1M1 )
     &+ S52*S4M1*S3M1*TP*U6M1 * ( 4 + 4*T1*U1M1 )
     &+ S52*S4M1*S3M1*TP*U6*U7M1 * ( 4*T1M1 )
     &+ S52*S4M1*S3M1*TP * ( 4*T1M1 )
     &+ S52*S4M1*S3M1*U6*U7M1 * (  - 8*T1*U1M1 )
     &+ S52*S4M1*S3M1 * ( 8 )
        FGLC_CACF = FGLC_CACF
     &+ S52*S4M1*TP*U6M1 * (  - 4*U1M1 )
     &+ S52*S4M1*U6*U7M1 * ( 2*T1M1 )
     &+ S52*S4M1 * (  - 2*U1M1 )
     &+ S52*S3M1*TP*U7M1 * (  - 4*T1M1 )
     &+ S52*S3M1*U6M1 * ( 2*T1*U1M1 )
     &+ S52*S3M1*U7M1 * (  - 2 )
     &+ S52*U7M1 * (  - 8*U1M1 )
     &+ S4M1*S3*UP*TPM1*U6*U7M1 * ( 2*T1*U1M1 )
     &+ S4M1*S3*UP*TPM1*U6 * (  - 2*U1M1 )
     &+ S4M1*S3*TPM1*U6*U7M1 * ( 2*T1*U1M1*Q2 + 4*Q2 )
        FGLC_CACF = FGLC_CACF
     &+ S4M1*S3*TPM1*U6 * ( 4 - 2*T1*U1M1 - 2*T12*U1M2 - 2*U1M1*Q2 )
     &+ S4M1*S3*TPM1*U62*U7M1 * ( 2 + 2*T1*U1M1 - 4*U1M1*Q2 )
     &+ S4M1*S3*U6*U7M1 * (  - 2*U1M1*Q2 )
     &+ S4M1*S3*U7M1 * (  - 2*T1*U1M1*Q2 + 2*Q2 )
     &+ S4M1*S3*U7 * ( 2*U1M1 )
     &+ S4M1*S3 * ( 2 - 2*T1*U1M1 + 2*U1M1*Q2 )
     &+ S4M1*S32*TPM1*U6 * (  - 2*U1M1 )
     &+ S4M1*S32*TPM1*U62*U7M1 * ( 2*T1M1 )
     &+ S4M1*UP*TPM1*U6*U7M1 * ( 8*T1*U1M1*Q2 - 4*T12*U1M1 )
     &+ S4M1*UP*TPM1*U6 * ( 4*T1*U1M1 - 2*T12*U1M2 )
        FGLC_CACF = FGLC_CACF
     &+ S4M1*UP*TPM1*U62*U7M1 * (  - 4 + 2*T1*U1M1 - 4*U1M1*Q2 )
     &+ S4M1*UP*U6*U7M1 * (  - 2 - 2*U1M1*Q2 )
     &+ S4M1*UP*U7M1 * (  - 2*T1*U1M1*Q2 )
     &+ S4M1*UP * (  - 2*T1*U1M1 )
     &+ S4M1*UP2*TPM1*U6*U7M1 * ( 2*T1*U1M1 )
     &+ S4M1*TPM1*U6*U7M1 * ( 6*T1*U1M1*Q4 - 8*T12*U1M1*Q2 )
     &+ S4M1*TPM1*U6*U7 * (  - 4*T1*U1M1 - 8*T12*U1M2 )
     &+ S4M1*TPM1*U6 * (  - 10*T12*U1M2*Q2 - 4*T12*U1M1 )
     &+ S4M1*TPM1*U62*U7M1 * ( 10*T1*U1M1*Q2 + 4*T1 - 4*U1M1*Q4-4*Q2 )
     &+ S4M1*TPM1*U62 * ( 4 + 12*T1*U1M1 + 4*U1M1*Q2 )
        FGLC_CACF = FGLC_CACF
     &+ S4M1*TPM1*U63*U7M1 * (  - 4 - 4*U1M1*Q2 )
     &+ S4M1*TP*U6M1*U7 * (  - 4*T1*U1M1 - 8*T12*U1M2 )
     &+ S4M1*TP*U6M1 * (  - 4*T1*U1M1*Q2 - 8*T12*U1M2*Q2 )
     &+ S4M1*TP*U7M1 * ( 2*U1M1*Q4 + 2*Q2 )
     &+ S4M1*TP * ( 6 + 8*T1*U1M1 + 6*U1M1*Q2 )
     &+ S4M1*U6*U7M1 * (  - 2*T1*U1M1*Q2 + 2*U1M1*Q4 + 6*Q2 )
     &+ S4M1*U6 * ( 16 + 14*T1*U1M1 + 12*U1M1*Q2 )
     &+ S4M1*U7M1 * (  - 6*T1*U1M1*Q4 + 4*T12*U1M1*Q2 )
     &+ S4M1*U7 * (  - 12*T1*U1M1 - 14*T12*U1M2 )
     &+ S4M1 * (  - 18*T1*U1M1*Q2 - 14*T12*U1M2*Q2 + 4*T12*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ S4*S3M1*UP*TPM1*U6*U7M1 * ( 2*T1*U1M1 )
     &+ S4*S3M1*UP*TPM1*U7M1 * (  - 2*T1 )
     &+ S4*S3M1*TPM1*U6M1*U7 * (  - 4*T12*U1M1 )
     &+ S4*S3M1*TPM1*U6M1 * (  - 4*T12*U1M1*Q2 )
     &+ S4*S3M1*TPM1*U6*U7M1 * ( 2*T1*U1M1*Q2 - 2*T1 + 2*T12*U1M1 )
     &+ S4*S3M1*TPM1*U62*U7M2 * (  - 2*T1 )
     &+ S4*S3M1*TPM1*U7M1 * (  - 2*T1*Q2 - 4*T12*U1M1*Q2 )
     &+ S4*S3M1*TPM1 * ( 4*T1*U1M1*Q2 + 4*T1 + 2*T12*U1M1 )
     &+ S4*S3M1*U6M1*U7 * (  - 2*T1*U1M1 )
     &+ S4*S3M1*U6M1 * (  - 2*T1*U1M1*Q2 )
        FGLC_CACF = FGLC_CACF
     &+ S4*S3M1*U6*U7M1 * (  - 2 - 2*U1M1*Q2 )
     &+ S4*S3M1*U7M1 * (  - 2*T1*U1M1*Q2 )
     &+ S4*S3M1 * ( 2 + 2*U1M1*Q2 )
     &+ S4*TPM2*U6*U7M1 * (  - 16*T12*U1M1 )
     &+ S4*TPM2*U62*U7M2 * ( 8*T1 )
     &+ S4*TPM2 * ( 8*T13*U1M2 )
     &+ S4*TPM1*U6M1*U7M1 * (  - 4*T12*U1M1*Q2 )
     &+ S4*TPM1*U6M1*U7 * (  - 8*T12*U1M2 )
     &+ S4*TPM1*U6M1 * (  - 8*T12*U1M2*Q2 - 4*T12*U1M1 - 2*T13*U1M2 )
     &+ S4*TPM1*U6*U7M1 * (  - 2 - 2*T1*U1M1 - 4*U1M1*Q2 )
        FGLC_CACF = FGLC_CACF
     &+ S4*TPM1*U62*U7M2 * ( 2 )
     &+ S4*TPM1*U7M1 * ( 8*T1*U1M1*Q2 + 4*T1 + 2*T12*U1M1 )
     &+ S4*TPM1 * ( 10*T1*U1M1 )
     &+ S42*S3M1*TPM1*U6M1 * ( 2*T12*U1M1 )
     &+ S42*S3M1*TPM1*U7M1 * (  - 2*T1 )
     &+ S3M1*UP*TPM1*U6*U7M1 * ( 8*T1*U1M1*Q2 + 4*T1 + 2*T12*U1M1 )
     &+ S3M1*UP*TPM1*U62*U7M2 * (  - 2*T1 )
     &+ S3M1*UP*TPM1*U62*U7M1 * (  - 4*T1*U1M1 )
     &+ S3M1*UP*TPM1*U7M1 * (  - 4*T12*U1M1*Q2 )
     &+ S3M1*UP*TPM1 * (  - 4*T12*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ S3M1*UP*U6*U7M1 * (  - 2 - 2*U1M1*Q2 )
     &+ S3M1*UP*U7M1 * (  - 2*T1*U1M1*Q2 )
     &+ S3M1*UP * (  - 2*T1*U1M1 )
     &+ S3M1*UP2*TPM1*U6*U7M1 * ( 2*T1*U1M1 )
     &+ S3M1*TPM1*U6*U7M1*(6*T1*U1M1*Q4+4*T1*Q2+10*T12*U1M1*Q2+12*T12 )
     &+ S3M1*TPM1*U6 * ( 4*T12*U1M1 )
     &+ S3M1*TPM1*U62*U7M2 * (  - 2*T1*Q2 )
     &+ S3M1*TPM1*U62*U7M1 * (  - 8*T1*U1M1*Q2 - 4*T1 )
     &+ S3M1*TPM1*U7M1*(-4*T12*U1M1*Q4 + 4*T12*Q2 - 4*T13*U1M1*Q2 )
     &+ S3M1*TPM1 * (  - 4*T12*U1M1*Q2 + 4*T12 - 4*T13*U1M1 )
        FGLC_CACF = FGLC_CACF
     &+ S3M1*TP*U6*U7M1 * ( 8 )
     &+ S3M1*TP*U7M1 * ( 2*U1M1*Q4 + 6*Q2 )
     &+ S3M1*TP * ( 6 + 2*U1M1*Q2 )
     &+ S3M1*U6M1*U7 * (  - 4*T12*U1M1 )
     &+ S3M1*U6M1 * (  - 4*T12*U1M1*Q2 )
     &+ S3M1*U6*U7M1 * (  - 2*T1*U1M1*Q2 + 14*T1 - 6*U1M1*Q4 - 6*Q2 )
     &+ S3M1*U62*U7M1 * ( 4 + 4*U1M1*Q2 )
     &+ S3M1*U7M1 * ( 2*T1*U1M1*Q4 + 12*T1*Q2 )
     &+ S3M1 * ( 6*T1*U1M1*Q2 + 16*T1 )
     &+ S3*TPM2*U6 * ( 8*T12*U1M2 )
        FGLC_CACF = FGLC_CACF
     &+ S3*TPM2*U62*U7M1 * (  - 16*T1*U1M1 )
     &+ S3*TPM2*U63*U7M2 * ( 8 )
     &+ S3*TPM1*U6*U7M1 * ( 10 - 2*T1*U1M1 + 8*U1M1*Q2 )
     &+ S3*TPM1*U6 * ( 4*U1M1 )
     &+ S3*TPM1*U62*U7M1 * (  - 4*T1M1*U1M1*Q2 - 4*T1M1 + 2*U1M1 )
     &+ S3*TPM1*U63*U7M2 * (  - 2*T1M1 )
     &+ S3*TPM1*U7M1 * (  - 4*T1*U1M1*Q2 )
     &+ S3*TPM1 * (  - 2*T1*U1M1 + 2*T12*U1M2 )
     &+ UP*TPM2*U6*U7M1 * (  - 8*T12*U1M1 )
     &+ UP*TPM2*U6 * ( 8*T12*U1M2 )
        FGLC_CACF = FGLC_CACF
     &+ UP*TPM2*U62*U7M2 * ( 8*T1 )
     &+ UP*TPM2*U62*U7M1 * (  - 8*T1*U1M1 )
     &+ UP*TPM1*U6*U7M1 * (  - 2 - 4*T1*U1M1 )
     &+ UP*TPM1*U62*U7M2 * ( 2 )
     &+ UP*TPM1*U62*U7M1 * ( 2*U1M1 )
     &+ UP*TPM1*U7M1 * ( 2*T12*U1M1 )
     &+ UP*TPM1 * (  - 2*T1*U1M1 + 2*T12*U1M2 )
     &+ TPM2*U6*U7M1 * (  - 8*T12*U1M1*Q2 )
     &+ TPM2*U6 * ( 8*T12*U1M2*Q2 )
     &+ TPM2*U62*U7M2 * ( 8*T1*Q2 )
        FGLC_CACF = FGLC_CACF
     &+ TPM2*U62*U7M1 * (  - 8*T1*U1M1*Q2 )
     &+ TPM1*U6*U7M1 * ( 4*T1*U1M1*Q2 - 2*T1 - 2*T12*U1M1 - 2*Q2 )
     &+ TPM1*U6 * (  - 2*T1*U1M1 )
     &+ TPM1*U62*U7M2 * ( 2*Q2 )
     &+ TPM1*U62*U7M1 * ( 10 - 2*T1*U1M1 + 10*U1M1*Q2 )
     &+ TPM1*U63*U7M2 * ( 2 )
     &+ TPM1*U7M1 * ( 10*T12*U1M1*Q2 )
     &+ TPM1*U7 * (  - 8*T12*U1M2 )
     &+ TPM1*(-2*T1*U1M1*Q2-6*T12*U1M2*Q2+10*T12*U1M1 + 2*T13*U1M2 )
     &+ U6M1*U7 * (  - 14*T12*U1M2 )
        FGLC_CACF = FGLC_CACF
     &+ U6M1 * (  - 14*T12*U1M2*Q2 )
     &+ U6*U7M1 * ( 14 - 2*U1M1*Q2 )
     &+ U6 * (  - 2*U1M1 )
     &+ U7M1 * (  - 2*T1*U1M1*Q2 - 2*T1 + 2*Q2 )
     &+ 4 + 14*T1*U1M1 + 2*U1M1*Q2

        FGLC_CACF = FGLC_CACF*TP*(UP+Q2*S5/S)
        FGLC_CACF = -4.D0*Q2*FGLC_CACF/SP/SP

      END IF

      RETURN
      END
      FUNCTION FGLC_CFCF
     &         (X,Y,M2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DP,DM)
C
C THIS IS THE CF*CF TERM OF FGLC IN 3 CASES
C 1) SOFT LIMIT
C 2) COLLINEAR LIMIT
C 3) HARD
C
C LIMITS CHECK UNDER THETA2 INTEGRATION: 11/8/94
C LIMITS CHECK W/O   THETA2 INTEGRATION: 2/15/95
C
C IT IS TP*(UP+Q2*S5/S)*M^G_L(3) OF THE PAPER
C THERE IS AN OVERALL FACTOR OF  G^4 EH^2 N CF CF  UNDERSTOOD
C
      IMPLICIT DOUBLE PRECISION (A-Z)

      PARAMETER (DELTAS=1.0D-5)
      PARAMETER (DELTAC=1.0D-7)

      ONEMX = 1.D0 - X
      ONEPY = 1.D0 + Y
      ONEMY = 1.D0 - Y

      IF ( ONEMX.LT.DELTAS ) THEN
C (1-Y*Y)*(1-X)**2*(P1P2)*SP**2
        P1 = +8.D0*(S-2.D0*M2)*ONEMY*ONEPY/DP/DM
C (1-Y*Y)*(1-X)**2*(P1P1)*SP**2
        P2 = +16.D0*M2*ONEMY*ONEPY/DM/DM
C (1-Y*Y)*(1-X)**2*(P2P2)*SP**2
        P3 = +16.D0*M2*ONEMY*ONEPY/DP/DP
        RSPS2 = (SP/S)**2
        FGLC_CFCF = 2.D0*RSPS2*BLQED(T1,SP,M2,Q2)*(2.D0*P1-P2-P3)
      ELSE IF ( ONEPY.LT.DELTAC ) THEN
        FGLC_CFCF = 0.D0
      ELSE
        M4 = M2*M2
        Q4 = Q2*Q2
        Q6 = Q2*Q4
        S52 = S5*S5
        S53 = S5*S52
        S42 = S4*S4
        S4M1 = 1.D0/S4
        S4M2 = S4M1*S4M1
        S32 = S3*S3
        S3M1 = 1.D0/S3
        S3M2 = S3M1*S3M1
        SM1 = 1.D0/S
        SP2 = SP*SP
        U62 = U6*U6
        U63 = U6*U62
        U6M1 = 1.D0/U6
        U6M2 = U6M1*U6M1
        U7M1 = 1.D0/U7
        U7M2 = U7M1*U7M1
        TP2 = TP*TP
        TP3 = TP*TP2
        TPM1 = 1.D0/TP
        TPM2 = TPM1*TPM1
        UP2 = UP*UP
        UP3 = UP*UP2
        T12 = T1*T1
        T13 = T1*T12
        T1M1 = 1.D0/T1
        T1M2 = T1M1*T1M1
        U1M1 = 1.D0/U1
        U1M2 = U1M1*U1M1
        U1P = U1+Q2
        U1P2 = U1P*U1P

        FGLC_CFCF =
     &+ M2*SP*U1P*S3M2*U6*U7M2 * ( 16 )
     &+ M2*SP*U1P*S3M1*U6*U7M2 * (  - 16*T1M1 )
     &+ M2*SP*U1P*U6*U7M2 * ( 16*T1M2 )
     &+ M2*SP*S5*S4M2 * ( 16*T1*U1M2 - 16*U1M1 )
     &+ M2*SP*S5*S4M1*S3M1*TP*U6M1 * (  - 8*U1M1 )
     &+ M2*SP*S5*S4M1*S3M1*TP*U7M1 * (  - 8*T1M1 )
     &+ M2*SP*S5*S4M1*S3M1*U6M1 * (  - 16*T1*U1M1 )
     &+ M2*SP*S5*S4M1*S3M1*U6*U7M1 * (  - 16*T1M1 )
     &+ M2*SP*S5*S4M1*U6M1 * (  - 16*T1*U1M2 - 16*U1M1 )
     &+ M2*SP*S5*S4M1*U6*U7M1 * (  - 16*T1M2 + 8*T1M1*U1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*SP*S5*S4M1*U7M1 * ( 8*U1M1 )
     &+ M2*SP*S5*S3M2*U6*U7M2 * ( 16 )
     &+ M2*SP*S5*S3M2*U7M1 * (  - 16 )
     &+ M2*SP*S5*S3M1*U6M2 * (  - 16*T1*U1M1 )
     &+ M2*SP*S5*S3M1*U6M1*U7M1 * ( 8*T1*U1M1 )
     &+ M2*SP*S5*S3M1*U6*U7M2 * (  - 16*T1M1 )
     &+ M2*SP*S5*S3M1*U7M1 * (  - 16*T1M1 + 8*U1M1 )
     &+ M2*SP*S5*U6M2 * ( 16*T1*U1M2 )
     &+ M2*SP*S5*U6*U7M2 * ( 16*T1M2 )
     &+ M2*SP*S4M2*S3 * ( 16*T1*U1M2 - 16*U1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*SP*S4M2*UP * ( 16*T1*U1M2 )
     &+ M2*SP*S4M2*U7 * ( 16*T1*U1M2 )
     &+ M2*SP*S4M2 * ( 32*T1*U1M2*Q2 )
     &+ M2*SP*S4M1*S3M1*UP*TP*U7M1 * (  - 16*U1M1 )
     &+ M2*SP*S4M1*S3M1*UP*U6*U7M1 * ( 8*U1M1 )
     &+ M2*SP*S4M1*S3M1*UP*U7M1 * ( 8*T1*U1M1 )
     &+ M2*SP*S4M1*S3M1*TP*U7M1 * (  - 8 - 32*U1M1*Q2 )
     &+ M2*SP*S4M1*S3M1*TP * (  - 8*U1M1 )
     &+ M2*SP*S4M1*S3M1*U6*U7M1 * ( 8*U1M1*Q2 )
     &+ M2*SP*S4M1*S3M1*U7M1 * ( 8*T1*U1M1*Q2 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*SP*S4M1*S3*U6M1 * (  - 16*T1*U1M2 )
     &+ M2*SP*S4M1*S3*U6*U7M1 * (  - 16*T1M2 + 16*T1M1*U1M1 )
     &+ M2*SP*S4M1*S3*U7M1 * ( 16*U1M1 )
     &+ M2*SP*S4M1*UP*U6M1 * (  - 16*T1*U1M2 )
     &+ M2*SP*S4M1*UP*U6*U7M1 * ( 16*T1M1*U1M1 )
     &+ M2*SP*S4M1*UP*U7M1 * ( 8*U1M1 )
     &+ M2*SP*S4M1*TP*U6M1 * (  - 16*T1*U1M2 - 16*U1M1 )
     &+ M2*SP*S4M1*TP*U6*U7M1 * ( 16*T1M1*U1M1 )
     &+ M2*SP*S4M1*TP*U7M1 * ( 8*T1M1*U1M1*Q2 + 32*T1M1 + 32*U1M1 )
     &+ M2*SP*S4M1*U6M1*U7 * (  - 16*T1*U1M2 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*SP*S4M1*U6M1 * (  - 32*T1*U1M2*Q2 - 24*T1*U1M1 -32*T12*U1M2)
     &+ M2*SP*S4M1*U6*U7M1 * ( 40*T1M1*U1M1*Q2 + 24*U1M1 )
     &+ M2*SP*S4M1*U6 * ( 16*T1M1*U1M1 )
     &+ M2*SP*S4M1*U62*U7M1 * ( 16*T1M1*U1M1 )
     &+ M2*SP*S4M1*U7M1 * ( 8 + 8*T1*U1M1 + 32*U1M1*Q2 )
     &+ M2*SP*S4M1 * ( 32*T1*U1M2 )
     &+ M2*SP*S4*S3M2*U6*U7M2 * ( 16 )
     &+ M2*SP*S4*S3M2*U7M1 * (  - 16 )
     &+ M2*SP*S4*S3M1*U6M2 * (  - 16*T1*U1M1 )
     &+ M2*SP*S4*S3M1*U6M1*U7M1 * ( 16*T1*U1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*SP*S4*S3M1*U6*U7M2 * (  - 16*T1M1 )
     &+ M2*SP*S4*S3M1*U7M1 * ( 16*U1M1 )
     &+ M2*SP*S3M2*UP*U6*U7M2 * ( 16 )
     &+ M2*SP*S3M2*U6*U7M2 * ( 16*Q2 )
     &+ M2*SP*S3M1*UP*U6M1*U7M1 * ( 16*T1*U1M1 )
     &+ M2*SP*S3M1*UP*U6*U7M2 * (  - 16*T1M1 )
     &+ M2*SP*S3M1*UP*U7M1 * ( 8*U1M1 )
     &+ M2*SP*S3M1*TP*U6M1*U7M1 * ( 16*T1*U1M1 + 8*U1M1*Q2 )
     &+ M2*SP*S3M1*TP*U6M1 * ( 32*U1M1 )
     &+ M2*SP*S3M1*TP*U6*U7M2 * (  - 16*T1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*SP*S3M1*TP*U7M1 * (  - 16*T1M1 + 32*U1M1 )
     &+ M2*SP*S3M1*U6M1*U7M1 * ( 40*T1*U1M1*Q2 + 16*T1 + 16*T12*U1M1 )
     &+ M2*SP*S3M1*U6*U7M2 * ( 32 - 16*T1M1*Q2 )
     &+ M2*SP*S3M1*U6*U7M1 * (  - 24*T1M1 + 8*U1M1 )
     &+ M2*SP*S3M1*U62*U7M2 * (  - 32*T1M1 )
     &+ M2*SP*S3M1*U7M1 * ( 24*T1*U1M1 + 32*U1M1*Q2 )
     &+ M2*SP*S3M1 * ( 8*U1M1 )
     &+ M2*SP*U6M2*U7 * ( 16*T1*U1M2 )
     &+ M2*SP*U6M2 * ( 16*T1*U1M2*Q2 + 32*T12*U1M2 )
     &+ M2*SP*U6M1*U7M1 * ( 24*T1*U1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*SP*U6M1 * ( 32*T1*U1M2 )
     &+ M2*SP*U6*U7M2 * ( 32*T1M1 )
     &+ M2*SP*U6*U7M1 * ( 24*T1M1*U1M1 )
     &+ M2*SP*U62*U7M2 * ( 32*T1M2 )
     &+ M2*SP*U7M1 * (  - 16*U1M1 )
     &+ M2*SP2*S5*S4M1*S3M1*U7M1 * ( 16*U1M1 )
     &+ M2*SP2*S5*S4M1*U7M1 * ( 8*T1M1*U1M1 )
     &+ M2*SP2*S5*S3M1*U6M1*U7M1 * ( 8*U1M1 )
     &+ M2*SP2*S5*U6M1*U7M1 * ( 16*T1M1*U1M1 )
     &+ M2*SP2*S4M1*S3*U7M1 * ( 8*T1M1*U1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*SP2*S4M1*TP*U7M1 * ( 16*T1M1*U1M1 )
     &+ M2*SP2*S4M1*U6M1 * (  - 16*T1*U1M2 )
     &+ M2*SP2*S4M1*U6*U7M1 * ( 16*T1M1*U1M1 )
     &+ M2*SP2*S4M1*U7M1 * ( 24*U1M1 )
     &+ M2*SP2*S4*S3M1*U6M1*U7M1 * ( 8*U1M1 )
     &+ M2*SP2*S3M1*TP*U6M1*U7M1 * ( 16*U1M1 )
     &+ M2*SP2*S3M1*U6M1*U7M1 * ( 16*T1*U1M1 )
     &+ M2*SP2*S3M1*U6*U7M2 * (  - 16*T1M1 )
     &+ M2*SP2*S3M1*U7M1 * ( 24*U1M1 )
     &+ M2*SP2*U6M2 * ( 16*T1*U1M2 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*SP2*U6M1*U7M1 * ( 16*U1M1 )
     &+ M2*SP2*U6*U7M2 * ( 16*T1M2 )
     &+ M2*SP2*U7M1 * ( 16*T1M1*U1M1 )
     &+ M2*U1P*S4M1*S3M1*TP*U6*U7M1 * ( 16*T1M1 )
     &+ M2*U1P*S4M1*S3M1*TP*U7M1 * (  - 8 )
     &+ M2*U1P*S4M1*S3M1*TP2*U7M1 * ( 8*T1M1 )
     &+ M2*U1P*S4M1*TP*U6*U7M1 * ( 16*T1M2 )
     &+ M2*U1P*S4M1*U62*U7M1 * ( 16*T1M2 )
     &+ M2*U1P*S3M2*U6*U7M1 * ( 16 )
     &+ M2*U1P*S3M2*U62*U7M2 * ( 16 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*U1P*S3M1*TP*U7M1 * (  - 16*T1M1 )
     &+ M2*U1P*S3M1*U62*U7M2 * (  - 16*T1M1 )
     &+ M2*U1P*U62*U7M2 * ( 16*T1M2 )
     &+ M2*S5*S4M2 * ( 16*T12*U1M2 )
     &+ M2*S5*S4M1*S3M1*TP*U6M1 * ( 32 + 16*T1*U1M1 )
     &+ M2*S5*S4M1*S3M1*TP*U6*U7M1 * ( 16*T1M1 )
     &+ M2*S5*S4M1*S3M1*TP * ( 32*T1M1 )
     &+ M2*S5*S4M1*S3M1*TP2*U6M1 * ( 16*T1M1 )
     &+ M2*S5*S4M1*S3M1*U6M1 * (  - 16*T12*U1M1 )
     &+ M2*S5*S4M1*S3M1*U6*U7M1 * ( 16 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*S5*S4M1*S3M1*U62*U7M1 * (  - 16*T1M1 )
     &+ M2*S5*S4M1*S3M1 * ( 64 + 16*T1*U1M1 )
     &+ M2*S5*S4M1*TP*U6*U7M1 * ( 16*T1M2 )
     &+ M2*S5*S4M1*U6M1 * (  - 16*T1*U1M1 - 16*T12*U1M2 )
     &+ M2*S5*S4M1*U6*U7M1 * ( 16*U1M1 )
     &+ M2*S5*S4M1 * ( 16*U1M1 )
     &+ M2*S5*S3M2*U62*U7M2 * ( 16 )
     &+ M2*S5*S3M1*TP*U6M2 * ( 16*T1*U1M1 )
     &+ M2*S5*S3M1*U6*U7M1 * (  - 16*T1M1 )
     &+ M2*S5*S3M1*U62*U7M2 * (  - 16*T1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*S5*S3M1*U7M1 * ( 16 + 16*T1*U1M1 )
     &+ M2*S5*U6M2 * ( 16*T12*U1M2 )
     &+ M2*S5*U62*U7M2 * ( 16*T1M2 )
     &+ M2*S4M2*S3 * ( 16*T12*U1M2 )
     &+ M2*S4M2*UP * ( 16*T1*U1M1 + 16*T12*U1M2 )
     &+ M2*S4M2*TP * (  - 16 - 16*T1*U1M1 - 16*U1M1*Q2 )
     &+ M2*S4M2*U6 * (  - 16 - 16*T1*U1M1 - 16*U1M1*Q2 )
     &+ M2*S4M2*U7 * ( 16*T1*U1M1 + 16*T12*U1M2 )
     &+ M2*S4M2 * ( 32*T1*U1M1*Q2 + 32*T12*U1M2*Q2 )
     &+ M2*S4M1*S3M1*UP*TP*U7M1 * (  - 8 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*S4M1*S3M1*UP*TP * (  - 8*U1M1 )
     &+ M2*S4M1*S3M1*UP*U6M1 * (  - 8*T12*U1M1 )
     &+ M2*S4M1*S3M1*UP*U6*U7M1 * (  - 16 - 16*T1*U1M1 )
     &+ M2*S4M1*S3M1*UP*U6 * ( 8*U1M1 )
     &+ M2*S4M1*S3M1*UP*U62*U7M1 * (  - 8*T1M1 + 24*U1M1 )
     &+ M2*S4M1*S3M1*UP*U7M1 * ( 8*T1 + 24*T12*U1M1 )
     &+ M2*S4M1*S3M1*UP * (  - 16*T1*U1M1 )
     &+ M2*S4M1*S3M1*TP*U6M1*U7 * ( 16*T1*U1M1 )
     &+ M2*S4M1*S3M1*TP*U6M1 * ( 24*T1*U1M1*Q2 + 8*T1 )
     &+ M2*S4M1*S3M1*TP*U6*U7M1 * ( 8 + 8*T1M1*Q2 - 16*U1M1*Q2 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*S4M1*S3M1*TP*U6 * ( 8*T1M1 - 24*U1M1 )
     &+ M2*S4M1*S3M1*TP*U7M1 * (  - 16*T1*U1M1*Q2 - 24*T1 - 8*Q2 )
     &+ M2*S4M1*S3M1*TP*U7 * (  - 8*U1M1 )
     &+ M2*S4M1*S3M1*TP * ( 8*T1*U1M1 - 16*U1M1*Q2 )
     &+ M2*S4M1*S3M1*TP2*U6M1*U7 * ( 8*U1M1 )
     &+ M2*S4M1*S3M1*TP2*U6M1 * ( 8*U1M1*Q2 )
     &+ M2*S4M1*S3M1*TP2*U7M1 * (  - 16*U1M1*Q2 )
     &+ M2*S4M1*S3M1*U6M1 * (  - 8*T12*U1M1*Q2 )
     &+ M2*S4M1*S3M1*U6*U7M1 * (  - 48*T1*U1M1*Q2 - 16*T1 - 16*Q2 )
     &+ M2*S4M1*S3M1*U6 * (  - 16*T1*U1M1 + 8*U1M1*Q2 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*S4M1*S3M1*U62*U7M1 * ( 16 - 8*T1M1*Q2 + 40*U1M1*Q2 )
     &+ M2*S4M1*S3M1*U7M1 * ( 8*T1*Q2 + 40*T12*U1M1*Q2 )
     &+ M2*S4M1*S3M1 * (  - 16*T1*U1M1*Q2 + 16*T12*U1M1 )
     &+ M2*S4M1*S3*U6M1 * (  - 16*T12*U1M2 )
     &+ M2*S4M1*S3*U6*U7M1 * ( 32*U1M1 )
     &+ M2*S4M1*S3*U62*U7M1 * (  - 16*T1M2 )
     &+ M2*S4M1*S3 * ( 16*U1M1 )
     &+ M2*S4M1*UP*U6M1 * (  - 16*T12*U1M2 )
     &+ M2*S4M1*UP*U6*U7M1 * ( 8*U1M1 )
     &+ M2*S4M1*UP*U62*U7M1 * ( 8*T1M1*U1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*S4M1*UP * ( 16*U1M1 )
     &+ M2*S4M1*TP*U6M1*U7 * (  - 16*U1M1 )
     &+ M2*S4M1*TP*U6M1 * (  - 16*T12*U1M2 - 16*U1M1*Q2 )
     &+ M2*S4M1*TP*U6*U7M1 * ( 8*T1M1*U1M1*Q2 + 48*T1M1 + 48*U1M1 )
     &+ M2*S4M1*TP*U6 * (  - 8*T1M1*U1M1 )
     &+ M2*S4M1*TP*U7M1 * (  - 16*T1M1*Q2 + 8*U1M1*Q2 )
     &+ M2*S4M1*TP * (  - 8*U1M1 )
     &+ M2*S4M1*U6M1*U7 * (  - 16*T12*U1M2 )
     &+ M2*S4M1*U6M1 * (- 32*T12*U1M2*Q2-32*T12*U1M1-16*T13*U1M2 )
     &+ M2*S4M1*U6*U7M1 * (  - 24 - 16*T1M1*Q2 + 8*U1M1*Q2 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*S4M1*U6 * (  - 32*T1M1 - 24*U1M1 )
     &+ M2*S4M1*U62*U7M1 * ( 32*T1M1*U1M1*Q2 + 8*T1M1 + 32*U1M1 )
     &+ M2*S4M1*U7M1 * ( 24*T1*U1M1*Q2 )
     &+ M2*S4M1 * ( 16 + 24*T1*U1M1 + 32*T12*U1M2 + 16*U1M1*Q2 )
     &+ M2*S4*S3M2*U62*U7M2 * ( 16 )
     &+ M2*S4*S3M1*U6M2 * (  - 16*T12*U1M1 )
     &+ M2*S4*S3M1*U62*U7M2 * (  - 16*T1M1 )
     &+ M2*S4*S3M1*U7M1 * ( 16 + 32*T1*U1M1 )
     &+ M2*S3M2*UP*U6*U7M1 * ( 16 )
     &+ M2*S3M2*UP*U62*U7M2 * ( 16 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*S3M2*TP*U6*U7M1 * (  - 16 )
     &+ M2*S3M2*TP*U7M1 * (  - 16*Q2 )
     &+ M2*S3M2*TP * (  - 16 )
     &+ M2*S3M2*U6*U7M1 * (  - 16*T1 + 16*Q2 )
     &+ M2*S3M2*U62*U7M2 * ( 16*Q2 )
     &+ M2*S3M2*U7M1 * (  - 16*T1*Q2 )
     &+ M2*S3M2 * (  - 16*T1 )
     &+ M2*S3M1*UP*U6M1*U7M1 * ( 8*T12*U1M1 )
     &+ M2*S3M1*UP*U62*U7M2 * (  - 16*T1M1 )
     &+ M2*S3M1*UP*U7M1 * ( 16 + 8*T1*U1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*S3M1*TP*U6M2*U7 * ( 16*T1*U1M1 )
     &+ M2*S3M1*TP*U6M2 * ( 16*T1*U1M1*Q2 )
     &+ M2*S3M1*TP*U6M1*U7M1 * ( 8*T1*U1M1*Q2 - 8*T1 )
     &+ M2*S3M1*TP*U6M1 * ( 48*T1*U1M1 - 16*U1M1*Q2 )
     &+ M2*S3M1*TP*U62*U7M2 * (  - 16*T1M1 )
     &+ M2*S3M1*TP*U7M1 * (  - 8 + 48*T1*U1M1 + 8*U1M1*Q2 )
     &+ M2*S3M1*U6M2*U7 * ( 16*T12*U1M1 )
     &+ M2*S3M1*U6M2 * ( 16*T12*U1M1*Q2 )
     &+ M2*S3M1*U6M1*U7M1 * ( 32*T12*U1M1*Q2 )
     &+ M2*S3M1*U6M1 * (  - 16*T1*U1M1*Q2 - 32*T1 + 8*T12*U1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*S3M1*U6*U7M1 * ( 24 + 24*U1M1*Q2 )
     &+ M2*S3M1*U62*U7M2 * ( 32 - 16*T1M1*Q2 )
     &+ M2*S3M1*U62*U7M1 * (  - 32*T1M1 )
     &+ M2*S3M1*U63*U7M2 * (  - 16*T1M1 )
     &+ M2*S3M1*U7M1 * ( 8*T1*U1M1*Q2 - 24*T1 + 32*T12*U1M1 + 16*Q2 )
     &+ M2*S3M1 * ( 16 - 24*T1*U1M1 )
     &+ M2*U6M2*U7 * ( 16*T12*U1M2 )
     &+ M2*U6M2 * ( 16*T12*U1M2*Q2 + 16*T13*U1M2 )
     &+ M2*U6M1*U7M1 * ( 16*T1*U1M1*Q2 )
     &+ M2*U6M1 * ( 32*T12*U1M2 )
        FGLC_CFCF = FGLC_CFCF
     &+ M2*U6*U7M1 * ( 16*T1M1*U1M1*Q2 )
     &+ M2*U62*U7M2 * ( 32*T1M1 )
     &+ M2*U63*U7M2 * ( 16*T1M2 )
     &+ M2*U7M1 * (  - 16 - 32*U1M1*Q2 )
     &+ M2 * (  - 16*U1M1 )
     &+ M4*SP*S4M2 * ( 32*T1*U1M2 + 32*U1M1 )
     &+ M4*SP*S4M1*S3M1*TP*U6M1 * ( 32*U1M1 )
     &+ M4*SP*S4M1*S3M1*TP*U7M1 * ( 32*T1M1 )
     &+ M4*SP*S4M1*S3M1*U6M1 * ( 32*T1*U1M1 )
     &+ M4*SP*S4M1*S3M1*U6*U7M1 * ( 32*T1M1 - 32*U1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ M4*SP*S4M1*S3M1*U7M1 * (  - 32*T1*U1M1 )
     &+ M4*SP*S4M1*TP*U7M1 * ( 32*T1M2 )
     &+ M4*SP*S4M1*U6M1 * ( 64*T1*U1M2 + 32*U1M1 )
     &+ M4*SP*S4M1*U6*U7M1 * ( 32*T1M2 - 32*T1M1*U1M1 )
     &+ M4*SP*S4M1*U7M1 * (  - 32*U1M1 )
     &+ M4*SP*S3M2*U6*U7M2 * ( 32 )
     &+ M4*SP*S3M2*U7M1 * ( 32 )
     &+ M4*SP*S3M1*TP*U6M2 * ( 32*U1M1 )
     &+ M4*SP*S3M1*U6M2 * ( 32*T1*U1M1 )
     &+ M4*SP*S3M1*U6M1*U7M1 * (  - 32*T1*U1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ M4*SP*S3M1*U6*U7M2 * ( 64*T1M1 )
     &+ M4*SP*S3M1*U7M1 * ( 32*T1M1 - 32*U1M1 )
     &+ M4*SP*U6M2 * ( 32*T1*U1M2 )
     &+ M4*SP*U6M1*U7M1 * (  - 32*U1M1 )
     &+ M4*SP*U6*U7M2 * ( 32*T1M2 )
     &+ M4*SP*U7M1 * (  - 32*T1M1*U1M1 )
     &+ M4*SP2*S4M1*S3M1*U7M1 * (  - 32*U1M1 )
     &+ M4*SP2*S4M1*U7M1 * (  - 32*T1M1*U1M1 )
     &+ M4*SP2*S3M1*U6M1*U7M1 * (  - 32*U1M1 )
     &+ M4*SP2*U6M1*U7M1 * (  - 32*T1M1*U1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ M4*S4M2*TP * (  - 32*T1M1 - 32*U1M1 )
     &+ M4*S4M2*U6 * (  - 32*T1M1 - 32*U1M1 )
     &+ M4*S4M2 * ( 32*T1*U1M1 + 32*T12*U1M2 )
     &+ M4*S4M1*S3M1*TP*U6M1 * (  - 32 + 32*T1*U1M1 )
     &+ M4*S4M1*S3M1*TP*U6*U7M1 * ( 32*T1M1 )
     &+ M4*S4M1*S3M1*TP * (  - 32*T1M1 )
     &+ M4*S4M1*S3M1*TP2*U6M1 * (  - 32*T1M1 )
     &+ M4*S4M1*S3M1*U6M1 * ( 32*T12*U1M1 )
     &+ M4*S4M1*S3M1*U6*U7M1 * (  - 32 - 64*T1*U1M1 )
     &+ M4*S4M1*S3M1*U62*U7M1 * ( 32*T1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ M4*S4M1*S3M1 * (  - 64 - 32*T1*U1M1 )
     &+ M4*S4M1*TP*U6M1 * (  - 32*U1M1 )
     &+ M4*S4M1*TP*U6*U7M1 * ( 32*T1M2 )
     &+ M4*S4M1*U6M1 * ( 32*T1*U1M1 + 64*T12*U1M2 )
     &+ M4*S4M1*U6*U7M1 * (  - 32*T1M1 - 64*U1M1 )
     &+ M4*S4M1*U62*U7M1 * ( 32*T1M2 )
     &+ M4*S4M1 * (  - 32*U1M1 )
     &+ M4*S3M2*TP*U6M1 * (  - 32 )
     &+ M4*S3M2*TP*U7M1 * (  - 32 )
     &+ M4*S3M2*U6M1 * (  - 32*T1 )
        FGLC_CFCF = FGLC_CFCF
     &+ M4*S3M2*U6*U7M1 * ( 32 )
     &+ M4*S3M2*U62*U7M2 * ( 32 )
     &+ M4*S3M2*U7M1 * (  - 32*T1 )
     &+ M4*S3M1*TP*U6M2 * ( 32*T1*U1M1 )
     &+ M4*S3M1*TP*U7M1 * (  - 32*T1M1 )
     &+ M4*S3M1*U6M2 * ( 32*T12*U1M1 )
     &+ M4*S3M1*U6M1 * (  - 32*T1*U1M1 )
     &+ M4*S3M1*U6*U7M1 * ( 32*T1M1 )
     &+ M4*S3M1*U62*U7M2 * ( 64*T1M1 )
     &+ M4*S3M1*U7M1 * (  - 32 - 64*T1*U1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ M4*U6M2 * ( 32*T12*U1M2 )
     &+ M4*U62*U7M2 * ( 32*T1M2 )
     &+ M4*U7M1 * (  - 64*U1M1 )
     &+ SP*U1P*S3M1*TP*U6*U7M2 * ( 16*T1M1 )
     &+ SP*U1P*S3M1*U6*U7M2 * ( 16 )
     &+ SP*U1P*U6*U7M2 * ( 16*T1M1 )
     &+ SP*S5*S4M1*UP*U7M1 * (  - 8*U1M1 )
     &+ SP*S5*S4M1*TP*U6M1 * ( 16*T1*U1M2 + 8*U1M1 )
     &+ SP*S5*S4M1*TP*U6*U7M1 * ( 8*T1M1*U1M1 )
     &+ SP*S5*S4M1*U6*U7M1 * (  - 8*T1M1*U1M1*Q2 - 8*T1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ SP*S5*S4M1*U7M1 * ( 8*T1*U1M1 - 16*U1M1*Q2 )
     &+ SP*S5*S4M1 * ( 16*T1*U1M2 )
     &+ SP*S5*S3M1*UP*U7M1 * (  - 8*U1M1 )
     &+ SP*S5*S3M1*TP*U6M1*U7M1 * ( 8*T1*U1M1 )
     &+ SP*S5*S3M1*TP*U6*U7M2 * ( 16*T1M1 )
     &+ SP*S5*S3M1*TP*U7M1 * ( 8*T1M1 )
     &+ SP*S5*S3M1*U6M1*U7M1 * (  - 8*T1*U1M1*Q2 )
     &+ SP*S5*S3M1*U6M1 * (  - 8*T1*U1M1 )
     &+ SP*S5*S3M1*U6*U7M2 * ( 16 )
     &+ SP*S5*S3M1*U6*U7M1 * ( 8*U1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ SP*S5*S3M1*U7M1 * (  - 16*U1M1*Q2 )
     &+ SP*S5*U6M1*U7M1 * ( 8*T1*U1M1 )
     &+ SP*S5*U6M1 * ( 16*T1*U1M2 + 8*U1M1 )
     &+ SP*S5*U6*U7M2 * ( 16*T1M1 )
     &+ SP*S5*U6*U7M1 * ( 8*T1M1*U1M1 )
     &+ SP*S5*U7M1 * ( 8*T1M1 + 16*U1M1 )
     &+ SP*S52*S4M1*S3M1*U6*U7M1 * ( 8*U1M1 )
     &+ SP*S52*S4M1*S3M1*U7M1 * ( 8*T1*U1M1 )
     &+ SP*S52*U6M1*U7M1 * ( 8*U1M1 )
     &+ SP*S52*U7M1 * ( 8*T1M1*U1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ SP*S4M1*S3*U6*U7M1 * (  - 8*T1M1*U1M1*Q2 - 8*T1M1 - 8*U1M1 )
     &+ SP*S4M1*S3*U62*U7M1 * (  - 8*T1M1*U1M1 )
     &+ SP*S4M1*S3 * (  - 8*T1*U1M2 + 8*U1M1 )
     &+ SP*S4M1*UP*U6*U7M1 * (  - 8*U1M1 )
     &+ SP*S4M1*UP * (  - 8*T1*U1M2 )
     &+ SP*S4M1*TP*U6M1*U7 * ( 16*T1*U1M2 )
     &+ SP*S4M1*TP*U6M1 * ( 16*T1*U1M2*Q2 )
     &+ SP*S4M1*TP*U6*U7M1 * ( 8*T1M1*U1M1*Q2 + 8*T1M1 )
     &+ SP*S4M1*U6*U7M1 * (  - 16*U1M1*Q2 )
     &+ SP*S4M1*U6 * (  - 8*U1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ SP*S4M1*U62*U7M1 * ( 8*T1M1*U1M1*Q2 + 8*T1M1 )
     &+ SP*S4M1*U7 * ( 16*T1*U1M2 )
     &+ SP*S4M1 * ( 8*T1*U1M2*Q2 )
     &+ SP*S4*S3M1*U6M1*U7M1 * (  - 8*T1*U1M1*Q2 - 8*T12*U1M1 )
     &+ SP*S4*S3M1*U6M1 * (  - 8*T1*U1M1 )
     &+ SP*S4*S3M1*U6*U7M2 * (  - 8 )
     &+ SP*S4*S3M1*U7M1 * ( 8 - 8*T1*U1M1 )
     &+ SP*S3M1*UP*U6*U7M2 * (  - 8 )
     &+ SP*S3M1*UP*U7M1 * (  - 8*T1*U1M1 )
     &+ SP*S3M1*TP*U6M1*U7M1 * ( 8*T1*U1M1*Q2 )
        FGLC_CFCF = FGLC_CFCF
     &+ SP*S3M1*TP*U6M1 * ( 8*T1*U1M1 )
     &+ SP*S3M1*U6M1*U7M1 * ( 8*T12*U1M1*Q2 )
     &+ SP*S3M1*U6M1 * ( 8*T12*U1M1 )
     &+ SP*S3M1*U6*U7M2 * (  - 8*Q2 )
     &+ SP*S3M1*U7M1 * (  - 16*T1*U1M1*Q2 - 8*T1 )
     &+ SP*U6M1*U7 * ( 16*T1*U1M2 )
     &+ SP*U6M1 * ( 16*T1*U1M2*Q2 - 16*T12*U1M2 )
     &+ SP*U6*U7M1 * (  - 8*U1M1 )
     &+ SP*U62*U7M2 * (  - 16*T1M1 )
     &+ SP*U7M1 * ( 8 - 8*T1*U1M1 + 16*U1M1*Q2 )
        FGLC_CFCF = FGLC_CFCF
     &+ SP * ( 8*U1M1 )
     &+ SP2*S5*S4M1*U6*U7M1 * (  - 8*T1M1*U1M1 )
     &+ SP2*S5*S3M1*U6M1*U7M1 * (  - 8*T1*U1M1 )
     &+ SP2*S4M1*S3*U6*U7M1 * (  - 8*T1M1*U1M1 )
     &+ SP2*S4*S3M1*U6M1*U7M1 * (  - 8*T1*U1M1 )
     &+ SP2*U6M1 * (  - 8*T1*U1M2 )
     &+ SP2*U6*U7M2 * (  - 8*T1M1 )
     &+ U1P*S5*S4M1*S3M1*TP*U6*U7M1 * (  - 8*T1M1 )
     &+ U1P*S5*S3M1*TP*U7M1 * ( 8*T1M1 )
     &+ U1P*S4M1*TP*U6*U7M1 * ( 8*T1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ U1P*S4M1*U62*U7M1 * ( 16*T1M1 )
     &+ U1P*S3M1*TP*U6*U7M1 * ( 8*T1M1 )
     &+ U1P*S3M1*TP*U62*U7M2 * ( 16*T1M1 )
     &+ U1P*S3M1*U6*U7M1 * ( 16 )
     &+ U1P*S3M1*U62*U7M2 * ( 16 )
     &+ U1P*U62*U7M2 * ( 16*T1M1 )
     &+ S5*S4M1*S3M1*UP*U6*U7M1 * ( 8 )
     &+ S5*S4M1*S3M1*UP * ( 8*T1*U1M1 )
     &+ S5*S4M1*S3M1*TP*U6M1*U7 * (  - 8*T1*U1M1 )
     &+ S5*S4M1*S3M1*TP*U6M1 * (  - 8*T1*U1M1*Q2 )
        FGLC_CFCF = FGLC_CFCF
     &+ S5*S4M1*S3M1*U6*U7M1 * ( 16*T1*U1M1*Q2 + 8*T1 + 8*Q2 )
     &+ S5*S4M1*S3M1*U6 * ( 8*T1*U1M1 )
     &+ S5*S4M1*S3M1*U62*U7M1 * (  - 8 - 8*U1M1*Q2 )
     &+ S5*S4M1*S3M1*U7M1 * (  - 8*T12*U1M1*Q2 )
     &+ S5*S4M1*S3M1 * ( 8*T1*U1M1*Q2 - 8*T12*U1M1 )
     &+ S5*S4M1*S3 * (  - 8*U1M1 )
     &+ S5*S4M1*UP*U6*U7M1 * (  - 8*U1M1 )
     &+ S5*S4M1*UP * (  - 8*U1M1 )
     &+ S5*S4M1*TP*U6M1*U7 * ( 8*U1M1 )
     &+ S5*S4M1*TP*U6M1 * ( 16*T1*U1M1 + 16*T12*U1M2 + 8*U1M1*Q2 )
        FGLC_CFCF = FGLC_CFCF
     &+ S5*S4M1*TP*U6*U7M1 * ( 8*T1M1*U1M1*Q2 + 8*T1M1 + 8*U1M1 )
     &+ S5*S4M1*TP*U7M1 * (  - 8*U1M1*Q2 )
     &+ S5*S4M1*U6*U7M1 * ( 16*T1*U1M1 - 24*U1M1*Q2 )
     &+ S5*S4M1*U6 * ( 8*T1M1 )
     &+ S5*S4M1*U62*U7M1 * ( 8*T1M1 )
     &+ S5*S4M1 * (  - 8 + 24*T1*U1M1 + 16*T12*U1M2 - 8*U1M1*Q2 )
     &+ S5*S4*S3M1*U7M1 * (  - 8 )
     &+ S5*S3M1*UP*U7M1 * (  - 8 - 8*T1*U1M1 )
     &+ S5*S3M1*TP*U6M1*U7M1 * ( 8*T1*U1M1*Q2 )
     &+ S5*S3M1*TP*U6M1 * ( 8*T1*U1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ S5*S3M1*TP*U6*U7M1 * ( 16*T1M1 )
     &+ S5*S3M1*TP*U62*U7M2 * ( 16*T1M1 )
     &+ S5*S3M1*TP*U7M1 * ( 8*T1*U1M1 - 8*U1M1*Q2 )
     &+ S5*S3M1*U6M1 * ( 8*T1 + 8*T12*U1M1 )
     &+ S5*S3M1*U6*U7M1 * ( 24 + 16*T1*U1M1 )
     &+ S5*S3M1*U62*U7M2 * ( 16 )
     &+ S5*S3M1*U7M1 * (  - 24*T1*U1M1*Q2 - 8*Q2 )
     &+ S5*S3M1 * (  - 8 )
     &+ S5*U6M1*U7M1 * (  - 8*T1*U1M1*Q2 )
     &+ S5*U6M1 * ( 16*T12*U1M2 )
        FGLC_CFCF = FGLC_CFCF
     &+ S5*U6*U7M1 * (  - 8*T1M1*U1M1*Q2 + 16*U1M1 )
     &+ S5*U62*U7M2 * ( 16*T1M1 )
     &+ S5*U7M1 * ( 8 + 16*T1*U1M1 + 16*U1M1*Q2 )
     &+ S5 * ( 8*U1M1 )
     &+ S52*S4M1*S3M1*TP*U6M1 * (  - 8 - 8*T1*U1M1 )
     &+ S52*S4M1*S3M1*TP*U6*U7M1 * (  - 8*T1M1 )
     &+ S52*S4M1*S3M1*TP * (  - 8*T1M1 )
     &+ S52*S4M1*S3M1*U6*U7M1 * ( 16*T1*U1M1 )
     &+ S52*S4M1*S3M1 * (  - 16 )
     &+ S52*S4M1*TP*U6M1 * ( 8*U1M1 )
        FGLC_CFCF = FGLC_CFCF
     &+ S52*S3M1*TP*U7M1 * ( 8*T1M1 )
     &+ S52*U7M1 * ( 16*U1M1 )
     &+ S4M1*S3*U6 * ( 8*U1M1 )
     &+ S4M1*S3*U62*U7M1 * (  - 8*T1M1*U1M1*Q2 - 8*T1M1 - 8*U1M1 )
     &+ S4M1*S3 * (  - 8*T12*U1M2 )
     &+ S4M1*UP*U6*U7M1 * (  - 8 - 8*T1*U1M1 - 8*U1M1*Q2 )
     &+ S4M1*UP*U7M1 * ( 8*T1*U1M1*Q2 )
     &+ S4M1*UP * (  - 8*T12*U1M2 )
     &+ S4M1*TP*U6M1*U7 * ( 8*T1*U1M1 + 16*T12*U1M2 )
     &+ S4M1*TP*U6M1 * ( 8*T1*U1M1*Q2 + 16*T12*U1M2*Q2 )
        FGLC_CFCF = FGLC_CFCF
     &+ S4M1*TP*U6*U7M1 * ( 8 + 8*T1M1*U1M1*Q4 + 8*T1M1*Q2+8*U1M1*Q2 )
     &+ S4M1*TP*U7M1 * (  - 8*U1M1*Q4 - 8*Q2 )
     &+ S4M1*TP * (  - 8 - 8*T1*U1M1 - 8*U1M1*Q2 )
     &+ S4M1*U6*U7M1 * ( 8*T1 - 24*U1M1*Q4 - 32*Q2 )
     &+ S4M1*U6 * (  - 32 - 16*T1*U1M1 - 24*U1M1*Q2 )
     &+ S4M1*U62*U7M1 * ( 8*T1M1*U1M1*Q4 + 8*T1M1*Q2 )
     &+ S4M1*U7M1 * ( 16*T1*U1M1*Q4 - 8*T12*U1M1*Q2 )
     &+ S4M1*U7 * ( 16*T1*U1M1 + 16*T12*U1M2 )
     &+ S4M1 * ( 24*T1*U1M1*Q2 + 8*T12*U1M2*Q2 - 8*T12*U1M1 )
     &+ S4*S3M1*U6M1*U7M1 * (  - 8*T12*U1M1*Q2 )
        FGLC_CFCF = FGLC_CFCF
     &+ S4*S3M1*U6M1 * (  - 8*T12*U1M1 )
     &+ S4*S3M1*U62*U7M2 * (  - 8 )
     &+ S4*S3M1*U7M1 * ( 8*T1 - 8*T12*U1M1 )
     &+ S3M1*UP*U6*U7M1 * (  - 8*T1*U1M1 + 8*U1M1*Q2 )
     &+ S3M1*UP*U62*U7M2 * (  - 8 )
     &+ S3M1*UP*U7M1 * (  - 8*T1*U1M1*Q2 )
     &+ S3M1*UP * (  - 8*T1*U1M1 )
     &+ S3M1*TP*U6M1*U7M1 * ( 8*T1*U1M1*Q4 )
     &+ S3M1*TP*U6M1*U7 * ( 8*T1*U1M1 )
     &+ S3M1*TP*U6M1 * ( 16*T1*U1M1*Q2 )
        FGLC_CFCF = FGLC_CFCF
     &+ S3M1*TP*U6*U7M1 * (  - 8 )
     &+ S3M1*TP*U7M1 * ( 8*T1*U1M1*Q2 - 8*U1M1*Q4 - 8*Q2 )
     &+ S3M1*TP * (  - 8 + 8*T1*U1M1 - 8*U1M1*Q2 )
     &+ S3M1*U6M1*U7M1 * ( 8*T12*U1M1*Q4 )
     &+ S3M1*U6M1*U7 * ( 16*T12*U1M1 )
     &+ S3M1*U6M1 * ( 24*T12*U1M1*Q2 )
     &+ S3M1*U6*U7M1 * (  - 16*T1 + 16*U1M1*Q4 + 8*Q2 )
     &+ S3M1*U6 * ( 8*T1*U1M1 )
     &+ S3M1*U62*U7M2 * (  - 8*Q2 )
     &+ S3M1*U62*U7M1 * (  - 8 - 8*U1M1*Q2 )
        FGLC_CFCF = FGLC_CFCF
     &+ S3M1*U7M1 * (  - 24*T1*U1M1*Q4 - 24*T1*Q2 )
     &+ S3M1 * (  - 32*T1*U1M1*Q2 - 32*T1 )
     &+ U6M1*U7M1 * (  - 8*T12*U1M1*Q2 )
     &+ U6M1*U7 * ( 16*T12*U1M2 )
     &+ U6M1 * ( 16*T12*U1M2*Q2 - 8*T12*U1M1 - 8*T13*U1M2 )
     &+ U6*U7M1 * (  - 16 - 16*T1*U1M1 + 16*U1M1*Q2 )
     &+ U6 * ( 8*U1M1 )
     &+ U62*U7M1 * (  - 8*T1M1*U1M1*Q2 - 8*T1M1 )
     &+ U63*U7M2 * (  - 8*T1M1 )
     &+ U7M1 * ( 16*T1*U1M1*Q2 + 8*T1 )
     &- 16*T1*U1M1

        FGLC_CFCF = FGLC_CFCF*TP*(UP+Q2*S5/S)
        FGLC_CFCF = -4.D0*Q2*FGLC_CFCF/SP/SP

      END IF

      RETURN
      END
      FUNCTION FQG0(X,Y,M2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DP,DM)
C
C THIS IS THE EH*EL PIECE OF F_Q_G (I.E. TERM 2) IN 3 CASES
C 1) SOFT LIMIT
C 2) COLLINEAR LIMIT
C 3) HARD
C
C LIMITS CHECK UNDER THETA2 INTEGRATION: 12/2/94
C LIMITS CHECK W/O   THETA2 INTEGRATION: 3/2/95
C
C IT IS TP*M^Q_G(3) OF THE PAPER
C THERE IS AN OVERALL FACTOR OF G^4 EL EH N CF UNDERSTOND
C
      IMPLICIT DOUBLE PRECISION (A-Z)
      PARAMETER (DELTAS=1.0D-7)
      PARAMETER (DELTAC=1.0D-7)

      ONEMX = 1.D0 - X
      ONEPY = 1.D0 + Y

      IF ( ONEMX.LT.DELTAS ) THEN
        FQG0 = 0.D0
      ELSE IF ( ONEPY.LT.DELTAC ) THEN
        FQG0 = 0.D0
      ELSE
        M4 = M2*M2
        M6 = M2*M4
        M8 = M2*M6
        Q4 = Q2*Q2
        Q6 = Q2*Q4
        S52 = S5*S5
        S53 = S5*S52
        S54 = S5*S53
        S5M1 = 1.D0/S5
        S5M2 = S5M1*S5M1
        S42 = S4*S4
        S4M1 = 1.D0/S4
        S4M2 = S4M1*S4M1
        S32 = S3*S3
        S3M1 = 1.D0/S3
        S3M2 = S3M1*S3M1
        S2 = S*S
        SM1 = 1.D0/S
        SPM1 = 1.D0/SP
        SPM2 = SPM1*SPM1
        U62 = U6*U6
        U63 = U6*U62
        U6M1 = 1.D0/U6
        U6M2 = U6M1*U6M1
        U7M1 = 1.D0/U7
        U7M2 = U7M1*U7M1
        TP2 = TP*TP
        TP3 = TP*TP2
        TP4 = TP*TP3
        TPM1 = 1.D0/TP
        UP2 = UP*UP
        UP3 = UP*UP2
        UPM1 = 1.D0/UP
        UPM2 = UPM1*UPM1
        T12 = T1*T1
        T13 = T1*T12
        T1M1 = 1.D0/T1
        T1M2 = T1M1*T1M1
        U1M1 = 1.D0/U1
        U1M2 = U1M1*U1M1
        U1P = U1+Q2

        TERM2 =
     &    + M2*SM1*SP*S3*S5M1*TPM1*U7M1 * ( 16 )
     &    + M2*SM1*SP*S4*S5M1*TPM1 * (  - 16*U1M1 )
     &    + M2*SM1*SP*S5M1*UP*TPM1*U7M1 * (  - 16 )
     &    + M2*SM1*SP*S5M1*UP*TPM1 * ( 16*U1M1 )
     &    + M2*SM1*SP*S5M1*TPM1*U7M1*Q2 * (  - 16 )
     &    + M2*SM1*SP*S5M1*TPM1*Q2 * ( 16*U1M1 )
     &    + M2*SM1*SP*S5M1*U7M1 * (  - 16 )
     &    + M2*SM1*SP*S5M1 * ( 16*U1M1 )
     &    + M2*SM1*T1*S5M1*UP*TPM1 * ( 16*U1M1 )
     &    + M2*SM1*T1*S5M1*TPM1*Q2 * ( 16*U1M1 )
     &    + M2*SM1*T1*S5M1 * ( 32*U1M1 )
     &    + M2*SM1*S5M1*UP*TPM1*U6*U7M1 * (  - 16 )
     &    + M2*SM1*S5M1*TPM1*U6*U7M1*Q2 * (  - 16 )
     &    + M2*SM1*S5M1*U6*U7M1 * (  - 32 )
     &    + M2*SM1*S5M1*U7M1*Q2 * (  - 16 )
     &    + M2*SM1*S5M1 * (  - 16 + 16*U1M1*U1P )
     &    + M2*SP*S3*S5M1*UPM1*TPM1 * (  - 16*U1M1 )
     &    + M2*SP*S4*S5M1*UPM1*TPM1*U7M1 * ( 16 )
     &    + M2*SP*S5M1*UPM1*TPM1*U7M1*Q2 * ( 16 )
     &    + M2*SP*S5M1*UPM1*TPM1*Q2 * (  - 16*U1M1 )
     &    + M2*SP*S5M1*TPM1*U7M1 * ( 16 )
     &    + M2*SP*S5M1*TPM1 * (  - 16*U1M1 )
     &    + M2*T1*S5M1*UPM1*TPM1*U7M1*Q2 * (  - 16 )
     &    + M2*T1*S5M1*TPM1*U7M1 * (  - 16 )
     &    + M2*S3*S5M1*UPM1 * (  - 32*U1M1 )
     &    + M2*S4*S5M1*UPM1*U7M1 * ( 32 )
     &    + M2*S5M1*UPM1*TPM1*U6*Q2 * ( 16*U1M1 )
     &    + M2*S5M1*UPM1*U7M1*Q2 * ( 32 )
     &    + M2*S5M1*UPM1*Q2 * (  - 16*U1M1 )
     &    + M2*S5M1*UPM1 * ( 16 - 16*U1M1*U1P )
     &    + M2*S5M1*TPM1*U6 * ( 16*U1M1 )
     &    + M2*S5M1*U7M1 * ( 16 )
     &    + M2*S5M1 * (  - 16*U1M1 )
     &    + SM1*SP*T1*S4*S5M1*TPM1*U7M1 * (  - 8 )
     &    + SM1*SP*T1*S4*S5M1*TPM1 * ( 16*U1M1 )
     &    + SM1*SP*S3*S5M1*TPM1*U6*U7M1 * (  - 16 )
     &    + SM1*SP*S3*S5M1*TPM1*U6 * ( 8*U1M1 )
     &    + SM1*SP*S3*S5M1*TPM1*U7M1*Q2 * (  - 16 )
     &    + SM1*SP*S3*S5M1*TPM1 * (  - 16 )
     &    + SM1*SP*S3*TPM1 * (  - 8*U1M1 )
     &    + SM1*SP*S4*S5M1*TPM1 * ( 16*U1M1*U1P )
     &    + SM1*SP*S4*TPM1*U7M1 * ( 8 )
     &    + SM1*T1*S3*S5M1*TPM1*U6 * ( 16*U1M1 )
     &    + SM1*T1*S3*S5M1*TPM1*U7 * ( 8*U1M1 )
     &    + SM1*T1*S3*S5M1*TPM1*Q2 * ( 8*U1M1 )
     &    + SM1*T1*S4*S5M1*TPM1*U6*U7M1 * (  - 16 )
     &    + SM1*T1*S4*S5M1*TPM1*Q2 * (  - 8*U1M1 )
     &    + SM1*T1*S4*S5M1*TPM1 * (  - 8 + 16*U1M1*U1P )
     &    + SM1*T1*S5M1*UP*TPM1*U6*U7M1 * (  - 8 )
     &    + SM1*T1*S5M1*UP*TPM1*U6 * ( 8*U1M1 )
     &    + SM1*T1*S5M1*TPM1*U6*U7M1*Q2 * (  - 8 )
     &    + SM1*T1*S5M1*TPM1*U6*Q2 * ( 8*U1M1 )
     &    + SM1*T1*S5M1*U7M1*Q2 * ( 8 )
     &    + SM1*T1*S5M1 * ( 8 )
     &    + SM1*T12*S4*S5M1*TPM1 * ( 16*U1M1 )
     &    + SM1*S3*S5M1*TPM1*U6*U7M1*Q2 * (  - 8 )
     &    + SM1*S3*S5M1*TPM1*U6*Q2 * (  - 8*U1M1 )
     &    + SM1*S3*S5M1*TPM1*U6 * (  - 16 + 8*U1M1*U1P )
     &    + SM1*S3*S5M1*TPM1*U62*U7M1 * (  - 16 )
     &    + SM1*S4*S5M1*TPM1*U6*U7M1 * (  - 8*U1P )
     &    + SM1*S5M1*U6 * (  - 8*U1M1*U1P )
     &    + SM1*U7M1*Q2 * (  - 8 )
     &    + SM1*Q2 * ( 8*U1M1 )
     &    + SP*S3*S4*S5M1*UPM1*TPM1*U7M1 * ( 8 )
     &    + SP*S3*S4*S5M1*UPM1*TPM1 * (  - 8*U1M1 )
     &    + T1*S3*S4*S5M1*UPM1*TPM1 * (  - 16*U1M1 )
     &    + T1*S3*S5M1*UPM1*TPM1*U7 * (  - 8*U1M1 )
     &    + T1*S3*S5M1*UPM1*TPM1*Q2 * (  - 8*U1M1 )
     &    + T1*S4*S5M1*UPM1*TPM1*U7M1*Q2 * ( 24 )
     &    + T1*S4*S5M1*UPM1*TPM1 * ( 16 - 8*U1M1*U1P )
     &    + T1*S4*S5M1*TPM1*U7M1 * ( 16 )
     &    + T1*S4*S5M1*TPM1 * (  - 8*U1M1 )
     &    + T1*S42*S5M1*UPM1*TPM1*U7M1 * ( 16 )
     &    + T1*S5M1*UPM1*TPM1*U7M1*Q4 * ( 16 )
     &    + T1*S5M1*UPM1*TPM1*Q2 * ( 16 )
     &    + T1*S5M1*TPM1*U7M1*Q2 * ( 16 )
     &    + T1*S5M1*TPM1 * ( 16 )
     &    + T1*UPM1*TPM1*Q2 * ( 8*U1M1 )
     &    + T1*TPM1 * ( 8*U1M1 )
     &    + S3*S4*S5M1*UPM1*TPM1*U6*U7M1 * ( 16 )
     &    + S3*S5M1*UPM1*TPM1*U6*U7M1*Q2 * ( 8 )
     &    + S3*S5M1*UPM1*TPM1*U6*Q2 * (  - 8*U1M1 )
     &    + S3*S5M1*UPM1*TPM1*U6 * ( 8 - 16*U1M1*U1P )
     &    + S3*S5M1*UPM1*U7M1*Q2 * (  - 8 )
     &    + S3*S5M1*UPM1 * (  - 8 )
     &    + S3*S5M1*TPM1*U6*U7M1 * ( 8 )
     &    + S3*S5M1*TPM1*U6 * (  - 16*U1M1 )
     &    + S32*S5M1*UPM1*TPM1*U6 * (  - 16*U1M1 )
     &    + S4*S5M1*UPM1*TPM1*U6*U7M1 * ( 8*U1P )
     &    + S4*S5M1*UPM1 * ( 8*U1M1*U1P )
     &    + S5M1*UPM1*TPM1*U6*Q2 * (  - 16*U1M1*U1P )
     &    + S5M1*TPM1*U6 * (  - 16*U1M1*U1P )
     &    + UPM1*TPM1*U6*U7M1*Q2 * (  - 8 )
     &    + UPM1*U7M1*Q2 * ( 8 )
     &    + UPM1*Q2 * (  - 8*U1M1 )
     &    + TPM1*U6*U7M1 * (  - 8 )

        FQG0 = TP*TERM2

      END IF

      RETURN
      END
      FUNCTION FQGC
     &         (X,Y,M2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DP,DM)
C
C THIS IS THE EH*EH PIECE OF F_Q_G (I.E. TERM 1) IN 3 CASES
C 1) SOFT LIMIT
C 2) COLLINEAR LIMIT
C 3) HARD
C
C LIMITS CHECK UNDER THETA2 INTEGRATION: 12/2/94
C LIMITS CHECK W/O   THETA2 INTEGRATION: 3/2/95, 3/29/95
C
C IT IS TP*M^Q_G(3) OF THE PAPER
C THERE IS AN OVERALL FACTOR OF G^4 EH^2 N CF UNDERSTOOD
C
      IMPLICIT DOUBLE PRECISION (A-Z)

      COMMON/AZDEP/CTH22,STH12

      PARAMETER (DELTAS=1.0D-7)
      PARAMETER (DELTAC=1.0D-7)


      ONEMX = 1.D0 - X
      ONEPY = 1.D0 + Y

      IF ( ONEMX.LT.DELTAS ) THEN
C         WRITE(*,*) 'IN SOFT LIMIT'
        FQGC = -8.D0*BGQED(T1,SP,M2,Q2)
      ELSE IF ( ONEPY.LT.DELTAC ) THEN
C         WRITE(*,*) 'IN COLLINEAR LIMIT'
        BETA52 = 1.D0-4.D0*M2/S5
        XSP2 = X*X*SP*SP
        FH = XSP2/X/T1/U1*(M2-ONEMX*S5*BETA52*CTH22*STH12/X/X)-S5
        FQGC = 16.D0*(2.D0*M2-Q2)*FH/X/T1/U1
     &        - 8.D0*(X*X-2.D0*X+2.D0)*(XSP2/X/T1/U1-2.D0)/X/X
      ELSE
C         WRITE(*,*) 'IN HARD'
        M4 = M2*M2
        Q4 = Q2*Q2
        S52 = S5*S5
        S53 = S5*S52
        S54 = S5*S53
        S5M1 = 1.D0/S5
        S5M2 = S5M1*S5M1
        S42 = S4*S4
        S4M1 = 1.D0/S4
        S4M2 = S4M1*S4M1
        S32 = S3*S3
        S3M1 = 1.D0/S3
        S3M2 = S3M1*S3M1
        S2 = S*S
        SM1 = 1.D0/S
        SP2 = SP*SP
        SPM1 = 1.D0/SP
        SPM2 = SPM1*SPM1
        U62 = U6*U6
        U63 = U6*U62
        U6M1 = 1.D0/U6
        U6M2 = U6M1*U6M1
        U7M1 = 1.D0/U7
        U7M2 = U7M1*U7M1
        TP2 = TP*TP
        TP3 = TP*TP2
        TP4 = TP*TP3
        TPM1 = 1.D0/TP
        TPM2 = TPM1*TPM1
        UP2 = UP*UP
        UP3 = UP*UP2
        UPM1 = 1.D0/UP
        UPM2 = UPM1*UPM1
        T12 = T1*T1
        T13 = T1*T12
        T1M1 = 1.D0/T1
        T1M2 = T1M1*T1M1
        U1M1 = 1.D0/U1
        U1M2 = U1M1*U1M1
        U1P = U1+Q2

        TERM1 =
     &    + M2*T1*S4*TPM2*U7M2 * ( 16 )
     &    + M2*T1*S4*TPM2*U7M1 * ( 32*U1M1 )
     &    + M2*T1*S4*TPM2 * ( 16*U1M2 )
     &    + M2*T1*UP*TPM2*U7M2 * ( 16 )
     &    + M2*T1*UP*TPM2*U7M1 * ( 16*U1M1 )
     &    + M2*T1*TPM2*U7M2*Q2 * ( 16 )
     &    + M2*T1*TPM2*U7M1*Q2 * ( 16*U1M1 )
     &    + M2*S3*TPM2*U6*U7M2 * ( 16 )
     &    + M2*S3*TPM2*U6*U7M1 * ( 32*U1M1 )
     &    + M2*S3*TPM2*U6 * ( 16*U1M2 )
     &    + M2*S3*TPM2*U7M2 * ( 16*SP )
     &    + M2*S3*TPM2*U7M1 * ( 16*SP*U1M1 )
     &    + M2*S4*TPM2*U7M1 * ( 16*SP*U1M1 )
     &    + M2*S4*TPM2 * ( 16*SP*U1M2 )
     &    + M2*S5*TPM1*U7M1 * (  - 32*U1M1 )
     &    + M2*UP*TPM2*U6*U7M1 * ( 16*U1M1 )
     &    + M2*UP*TPM2*U6 * ( 16*U1M2 )
     &    + M2*UP*TPM2*U7M1 * ( 32*SP*U1M1 )
     &    + M2*TPM2*U6*U7M1*Q2 * ( 16*U1M1 )
     &    + M2*TPM2*U6*Q2 * ( 16*U1M2 )
     &    + M2*TPM2*U7M1*Q2 * ( 32*SP*U1M1 )
     &    + M2*TPM1*U7M2*Q2 * (  - 16 )
     &    + M2*TPM1*U7M1*Q2 * (  - 16*U1M1 )
     &    + M2*TPM1*U7M1 * ( 16 - 16*U1M1*U1P )
     &    + M2*TPM1*Q2 * (  - 32*U1M2 )
     &    + M2*TPM1 * ( 16*U1M2*U1P - 16*U1M1 )
     &    + M4*TPM1*U7M2 * ( 32 )
     &    + M4*TPM1*U7M1 * ( 64*U1M1 )
     &    + M4*TPM1 * ( 32*U1M2 )
     &    + T1*S3*TPM2*U7M1*Q2 * ( 16*U1M1 )
     &    + T1*S3*TPM2 * ( 16*U1M1 )
     &    + T1*S4*S5*TPM2*U7M1 * (  - 16*U1M1 )
     &    + T1*S4*TPM2*U7M2*Q2 * (  - 8 )
     &    + T1*S4*TPM2*U7M1*Q2 * (  - 8*U1M1 )
     &    + T1*S4*TPM2*U7M1 * (  - 8*U1M1*U1P )
     &    + T1*S4*TPM2*Q2 * (  - 8*U1M2 )
     &    + T1*S4*TPM2 * (  - 8*U1M1 )
     &    + T1*S5*UP*TPM2*U7M1 * (  - 8*U1M1 )
     &    + T1*S5*TPM2*U7M1*Q2 * (  - 8*U1M1 )
     &    + T1*UP*TPM2*U7M2*Q2 * (  - 8 )
     &    + T1*UP*TPM2*U7M1 * (  - 8 )
     &    + T1*TPM2*U7M2*Q4 * (  - 8 )
     &    + T1*TPM2*U7M1*Q2 * (  - 8 )
     &    + S3*S5*TPM2*U6*U7M1 * (  - 16*U1M1 )
     &    + S3*S5*TPM2*U7M1 * (  - 8*SP*U1M1 )
     &    + S3*TPM2*U6*U7M2*Q2 * (  - 8 )
     &    + S3*TPM2*U6*U7M1*Q2 * (  - 8*U1M1 )
     &    + S3*TPM2*U6*U7M1 * (  - 8*U1M1*U1P )
     &    + S3*TPM2*U6*Q2 * (  - 8*U1M2 )
     &    + S3*TPM2*U6 * (  - 8*U1M1 )
     &    + S3*TPM2*U7M2*Q2 * (  - 8*SP )
     &    + S3*TPM2*U7M1 * (  - 8*SP )
     &    + S4*S5*TPM2*U7M1 * (  - 8*SP*U1M1 )
     &    + S4*TPM2*U6*U7M1 * ( 16*U1M1*U1P )
     &    + S4*TPM2 * (  - 8*SP*U1M2*U1P )
     &    + S5*UP*TPM2*U6*U7M1 * (  - 8*U1M1 )
     &    + S5*TPM2*U6*U7M1*Q2 * (  - 8*U1M1 )
     &    + S5*TPM1*U7M1*Q2 * ( 16*U1M1 )
     &    + UP*TPM2*U6 * (  - 8*U1M2*U1P )
     &    + TPM2*U6*Q2 * (  - 8*U1M2*U1P )

        FQGC = TP*TERM1

      END IF

      RETURN
      END
      FUNCTION FQGD(X,Y,M2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DP,DM)
C
C THIS IS THE EL*EL PIECE OF F_Q_G (I.E. TERM 3) IN 3 CASES
C 1) SOFT LIMIT
C 2) COLLINEAR LIMIT
C 3) HARD
C
C LIMITS CHECK UNDER THETA2 INTEGRATION: 12/2/94
C LIMITS CHECK W/O   THETA2 INTEGRATION: 3/2/95
C
C IT IS TP*M^Q_G(3) OF THE PAPER
C THERE IS AN OVERALL FACTOR OF G^4 EL^2 N CF UNDERSTOOD
C
      IMPLICIT DOUBLE PRECISION (A-Z)
      PARAMETER (DELTAS=1.0D-7)
      PARAMETER (DELTAC=1.0D-7)

      ONEMX = 1.D0 - X
      ONEPY = 1.D0 + Y

      IF ( ONEMX.LT.DELTAS ) THEN
        FQGD = 0.D0
      ELSE IF ( ONEPY.LT.DELTAC ) THEN
        FQGD = 0.D0
      ELSE
        Q4 = Q2*Q2
        S52 = S5*S5
        S53 = S5*S52
        S54 = S5*S53
        S5M1 = 1.D0/S5
        S5M2 = S5M1*S5M1
        S42 = S4*S4
        S4M1 = 1.D0/S4
        S4M2 = S4M1*S4M1
        S32 = S3*S3
        S3M1 = 1.D0/S3
        S3M2 = S3M1*S3M1
        S2 = S*S
        SM1 = 1.D0/S
        SM2 = SM1*SM1
        SPM1 = 1.D0/SP
        SPM2 = SPM1*SPM1
        U62 = U6*U6
        U63 = U6*U62
        U6M1 = 1.D0/U6
        U6M2 = U6M1*U6M1
        U7M1 = 1.D0/U7
        U7M2 = U7M1*U7M1
        TP2 = TP*TP
        TP3 = TP*TP2
        TP4 = TP*TP3
        TPM1 = 1.D0/TP
        UP2 = UP*UP
        UP3 = UP*UP2
        UPM1 = 1.D0/UP
        UPM2 = UPM1*UPM1
        T12 = T1*T1
        T13 = T1*T12
        T1M1 = 1.D0/T1
        T1M2 = T1M1*T1M1
        U1M1 = 1.D0/U1
        U1M2 = U1M1*U1M1
        U1P = U1+Q2

        TERM3 =
     &    + M2*SM2*S5M2*UP * (  - 16*SP )
     &    + M2*SM2*S5M2*TP*Q2 * (  - 16 )
     &    + M2*SM2*S5M2*Q2 * (  - 16*SP )
     &    + M2*SM1*S5M2*UPM1*TP * (  - 32*SP )
     &    + M2*SM1*S5M2*UPM1*TP2 * (  - 32 )
     &    + M2*SM1*S5M2*TP * (  - 32 )
     &    + M2*S5M2*UPM2*TP*Q2 * (  - 16 )
     &    + M2*S5M2*UPM2*Q2 * (  - 16*SP )
     &    + M2*S5M2*UPM1 * (  - 16*SP )
     &    + SM2*T1*S4*S5M2*Q2 * (  - 8 )
     &    + SM2*U1P*S4*S5M2 * (  - 8*SP )
     &    + SM2*S3*S5M2*U6*Q2 * (  - 8 )
     &    + SM2*S3*S5M2*U7 * (  - 8*SP )
     &    + SM2*S3*S5M2*Q2 * (  - 8*SP )
     &    + SM1*T1*S4*S5M2*UPM1*TP * (  - 16 )
     &    + SM1*T1*S4*S5M2*UPM1*Q2 * (  - 8 )
     &    + SM1*T1*S4*S5M2*UPM1 * (  - 8*SP )
     &    + SM1*T1*S4*S5M2 * (  - 8 )
     &    + SM1*T1*S5M2*UPM1*TP*U7 * (  - 8 )
     &    + SM1*T1*S5M2*UPM1*TP*Q2 * (  - 8 )
     &    + SM1*T1*S5M2*UPM1*U6*Q2 * ( 16 )
     &    + SM1*T1*S5M2*U6 * ( 16 )
     &    + SM1*U1P*S4*S5M2*UPM1*TP * (  - 8 )
     &    + SM1*U1P*S5M2*UPM1*TP*U6 * (  - 8 )
     &    + SM1*S3*S4*S5M2*UPM1 * ( 16*SP )
     &    + SM1*S3*S5M2*UPM1*TP*U6 * (  - 16 )
     &    + SM1*S3*S5M2*UPM1*TP*U7 * (  - 8 )
     &    + SM1*S3*S5M2*UPM1*TP*Q2 * (  - 8 )
     &    + SM1*S3*S5M2*UPM1*U6*Q2 * (  - 8 )
     &    + SM1*S3*S5M2*UPM1*U6 * (  - 8*SP )
     &    + SM1*S3*S5M2*U6 * (  - 8 )
     &    + SM1*S5M1*UPM1*TP*Q2 * ( 16 )
     &    + T1*S4*S5M2*UPM2*Q2 * (  - 8 )
     &    + T1*S5M2*UPM2*U7*Q2 * (  - 8 )
     &    + T1*S5M2*UPM2*Q4 * (  - 8 )
     &    + T1*S5M2*UPM1*U7 * (  - 8 )
     &    + T1*S5M2*UPM1*Q2 * (  - 8 )
     &    + U1P*S5M2*UPM2*U6*Q2 * (  - 8 )
     &    + U1P*S5M2*UPM1*U6 * (  - 8 )
     &    + S3*S5M2*UPM2*U6*Q2 * (  - 8 )

        FQGD = TP*TERM3

      END IF

      RETURN
      END
      FUNCTION FQL0(X,Y,M2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DP,DM)
C
C THIS IS THE EH*EL PIECE OF F_Q_L (I.E. TERM 2) IN 3 CASES
C 1) SOFT LIMIT
C 2) COLLINEAR LIMIT
C 3) HARD
C
C LIMITS CHECK UNDER THETA2 INTEGRATION: 12/1/94
C LIMITS CHECK W/O   THETA2 INTEGRATION: 2/15/95
C
C IT IS TP*M^Q_L(3) OF THE PAPER
C THERE IS AN OVERALL FACTOR OF G^4 EL EH N CF UNDERSTOND
C
      IMPLICIT DOUBLE PRECISION (A-Z)
      PARAMETER (DELTAS=1.0D-7)
      PARAMETER (DELTAC=1.0D-7)

      ONEMX = 1.D0 - X
      ONEPY = 1.D0 + Y

      IF ( ONEMX.LT.DELTAS ) THEN
        FQL0 = 0.D0
      ELSE IF ( ONEPY.LT.DELTAC ) THEN
        FQL0 = 0.D0
      ELSE
        M4 = M2*M2
        M6 = M2*M4
        M8 = M2*M6
        Q4 = Q2*Q2
        Q6 = Q2*Q4
        S52 = S5*S5
        S53 = S5*S52
        S54 = S5*S53
        S5M1 = 1.D0/S5
        S5M2 = S5M1*S5M1
        S42 = S4*S4
        S4M1 = 1.D0/S4
        S4M2 = S4M1*S4M1
        S32 = S3*S3
        S3M1 = 1.D0/S3
        S3M2 = S3M1*S3M1
        S2 = S*S
        SM1 = 1.D0/S
        SPM1 = 1.D0/SP
        SPM2 = SPM1*SPM1
        U62 = U6*U6
        U63 = U6*U62
        U6M1 = 1.D0/U6
        U6M2 = U6M1*U6M1
        U7M1 = 1.D0/U7
        U7M2 = U7M1*U7M1
        TP2 = TP*TP
        TP3 = TP*TP2
        TP4 = TP*TP3
        TPM1 = 1.D0/TP
        UP2 = UP*UP
        UP3 = UP*UP2
        UPM1 = 1.D0/UP
        UPM2 = UPM1*UPM1
        T12 = T1*T1
        T13 = T1*T12
        T1M1 = 1.D0/T1
        T1M2 = T1M1*T1M1
        U1M1 = 1.D0/U1
        U1M2 = U1M1*U1M1
        U1P = U1+Q2

        TERM21 =
     &    + M2*T1*S5M1*UPM1*TP2*Q2 * ( 64.D0*SPM2*U1M1 )
     &    + M2*T1*S5M1*UPM1*TP*Q2 * ( 64.D0*SPM1*U1M1 )
     &    + M2*S5M1*UPM1*TP2*U6*U7M1*Q2 * (  - 64.D0*SPM2 )
     &    + M2*S5M1*UPM1*TP2*U7M1*Q2 * (  - 32.D0*SPM1 )
     &    + M2*S5M1*UPM1*TP2*Q2 * ( 32.D0*SPM1*U1M1 )
     &    + M2*S5M1*UPM1*TP*U6*U7M1*Q2 * (  - 64.D0*SPM1 )
     &    + M2*S5M1*UPM1*TP*U7M1*Q2 * (  - 32.D0 )
     &    + M2*S5M1*UPM1*TP*Q2 * ( 32.D0*U1M1 )
     &    + T12*S4*S5M1*UPM1*TP*Q2 * ( 32.D0*SPM2*U1M1 )
     &    + T12*S4*S5M1*UPM1*Q2 * ( 16.D0*SPM1*U1M1 )
     &    + T12*S5M1*UPM1*TP*U7*Q2 * ( 16.D0*SPM2*U1M1 )
     &    + T12*S5M1*UPM1*TP*Q4 * ( 16.D0*SPM2*U1M1 )
     &    + T12*S5M1*UPM1*U6*Q4 * (  - 32.D0*SPM2*U1M1 )
     &    + T12*S5M1*U6*Q2 * (  - 32.D0*SPM2*U1M1 )
        TERM22 =
     &    + T1*S3*S5M1*UPM1*TP*U6*Q2 * ( 32.D0*SPM2*U1M1 )
     &    + T1*S3*S5M1*UPM1*U6*Q2 * ( 16.D0*SPM1*U1M1 )
     &    + T1*S4*S5M1*UPM1*TP*U6*U7M1*Q2 * (  - 32.D0*SPM2 )
     &    + T1*S4*S5M1*UPM1*TP*U7M1*Q2 * (  - 16.D0*SPM1 )
     &    + T1*S4*S5M1*UPM1*TP*Q2 * ( 32.D0*SPM1*U1M1 )
     &    + T1*S4*S5M1*UPM1*U6*U7M1*Q2 * (  - 16.D0*SPM1 )
     &    + T1*S4*S5M1*UPM1*U7M1*Q2 * (  - 16.D0 )
     &    + T1*S4*S5M1*UPM1*Q2 * ( 16.D0*U1M1 )
     &    + T1*S5M1*UPM1*TP2*U7M1*Q4 * ( 16.D0*SPM2 )
     &    + T1*S5M1*UPM1*TP2*Q2 * ( 16.D0*SPM2 )
     &    + T1*S5M1*UPM1*TP*U6*Q4 * (  - 16.D0*SPM2*U1M1 )
     &    + T1*S5M1*UPM1*TP*U6*Q2 * ( 16.D0*SPM2*U1M1*U1P - 16.D0*SPM2 )
     &    + T1*S5M1*UPM1*TP*U7*Q2 * ( 16.D0*SPM1*U1M1 )
        TERM23 =
     &    + T1*S5M1*UPM1*TP*U7M1*Q4 * ( 16.D0*SPM1 )
     &    + T1*S5M1*UPM1*TP*Q4 * ( 16.D0*SPM1*U1M1 )
     &    + T1*S5M1*UPM1*TP*Q2 * ( 16.D0*SPM1 )
     &    + T1*S5M1*UPM1*U62*U7M1*Q4 * ( 32.D0*SPM2 )
     &    + T1*S5M1*UPM1*U6*U7M1*Q4 * ( 32.D0*SPM1 )
     &    + T1*S5M1*UPM1*U6*Q4 * (  - 32.D0*SPM1*U1M1 )
     &    + T1*S5M1*TP*U6*U7M1*Q2 * (  - 16.D0*SPM2 )
     &    + T1*S5M1*TP*U6*Q2 * ( 16.D0*SPM2*U1M1 )
     &    + T1*S5M1*U62*U7M1*Q2 * ( 32.D0*SPM2 )
     &    + T1*S5M1*U6*U7M1*Q2 * ( 32.D0*SPM1 )
     &    + T1*S5M1*U6*Q2 * (  - 32.D0*SPM1*U1M1 )
     &    + S3*S5M1*UPM1*TP*U62*U7M1*Q2 * (  - 32.D0*SPM2 )
     &    + S3*S5M1*UPM1*TP*U6*U7M1*Q2 * (  - 32.D0*SPM1 )
        TERM24 =
     &    + S3*S5M1*UPM1*TP*U6*Q2 * ( 16.D0*SPM1*U1M1 )
     &    + S3*S5M1*UPM1*U62*U7M1*Q2 * (  - 16.D0*SPM1 )
     &    + S3*S5M1*UPM1*U6*U7M1*Q2 * (  - 16.D0 )
     &    + S3*S5M1*UPM1*U6*Q2 * ( 16.D0*U1M1 )
     &    + S5M1*UPM1*TP2*U6*Q2 * (  - 16.D0*SPM2*U1M1*U1P )
     &    + S5M1*UPM1*TP*U62*U7M1*Q2 * (  - 16.D0*SPM2*U1P )
     &    + S5M1*UPM1*TP*U6*U7M1*Q2 * (  - 16.D0*SPM1*U1P )
     &    + S5M1*UPM1*TP*U6*Q2 * (  - 16.D0*SPM1*U1M1*U1P )

        FQL0 = TERM21 + TERM22 + TERM23 + TERM24

      END IF

      RETURN
      END
      FUNCTION FQLC
     &         (X,Y,M2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DP,DM)
C
C THIS IS THE EH*EH PIECE OF F_Q_L (I.E. TERM 1) IN 3 CASES
C 1) SOFT LIMIT
C 2) COLLINEAR LIMIT
C 3) HARD
C
C LIMITS CHECK UNDER THETA2 INTEGRATION: 2/15/95
C LIMITS CHECK W/O   THETA2 INTEGRATION: 3/2/95, 3/29/95
C
C IT IS TP*M^Q_L(3) OF THE PAPER
C THERE IS AN OVERALL FACTOR OF G^4 EH^2 N CF UNDERSTOOD
C
      IMPLICIT DOUBLE PRECISION (A-Z)

      COMMON/AZDEP/CTH22,STH12

      PARAMETER (DELTAS=1.0D-7)
      PARAMETER (DELTAC=1.0D-7)

      ONEMX = 1.D0 - X
      ONEPY = 1.D0 + Y

      IF ( ONEMX.LT.DELTAS ) THEN
C         WRITE(*,*) 'IN SOFT LIMIT'
        FQLC = -8.D0*BLQED(T1,SP,M2,Q2)
      ELSE IF ( ONEPY.LT.DELTAC ) THEN
C         WRITE(*,*) 'IN COLLINEAR LIMIT'
        BETA52 = 1.D0-4.D0*M2/S5
        XSP2 = X*X*SP*SP
        FH = XSP2/X/T1/U1*(M2-ONEMX*S5*BETA52*CTH22*STH12/X/X)-S5
        FQLC = 32.D0*Q2*FH/XSP2
      ELSE
C         WRITE(*,*) 'IN HARD'
        S52 = S5*S5
        S53 = S5*S52
        S54 = S5*S53
        S5M1 = 1.D0/S5
        S5M2 = S5M1*S5M1
        S42 = S4*S4
        S4M1 = 1.D0/S4
        S4M2 = S4M1*S4M1
        S32 = S3*S3
        S3M1 = 1.D0/S3
        S3M2 = S3M1*S3M1
        S2 = S*S
        SM1 = 1.D0/S
        SP2 = SP*SP
        SPM1 = 1.D0/SP
        SPM2 = SPM1*SPM1
        U62 = U6*U6
        U63 = U6*U62
        U6M1 = 1.D0/U6
        U6M2 = U6M1*U6M1
        U7M1 = 1.D0/U7
        U7M2 = U7M1*U7M1
        TP2 = TP*TP
        TP3 = TP*TP2
        TP4 = TP*TP3
        TPM1 = 1.D0/TP
        TPM2 = TPM1*TPM1
        UP2 = UP*UP
        UP3 = UP*UP2
        UPM1 = 1.D0/UP
        UPM2 = UPM1*UPM1
        T12 = T1*T1
        T13 = T1*T12
        T1M1 = 1.D0/T1
        T1M2 = T1M1*T1M1
        U1M1 = 1.D0/U1
        U1M2 = U1M1*U1M1
        U1P = U1+Q2

        TERM1 =
     &    + TPM2*SP*T1*U1M2*S3*U6 * (  - 4 )
     &    + TPM2*SP*T1*U1M2*U6*Q2 * (  - 4 )
     &    + TPM2*SP*T1*U1M2*U6 * (  - 4*UP )
     &    + TPM2*SP*T1*U1M1*S3*U6*U7M1 * ( 8 )
     &    + TPM2*SP*T1*U1M1*S4*U6*U7M1 * ( 8 )
     &    + TPM2*SP*T1*U1M1*U6*U7M1*Q2 * ( 8 )
     &    + TPM2*SP*T1*U1M1*U6*U7M1 * ( 8*UP )
     &    + TPM2*SP*T1*S4*U6*U7M2 * (  - 4 )
     &    + TPM2*SP*T1*U6*U7M2*Q2 * (  - 4 )
     &    + TPM2*SP*T1*U6*U7M2 * (  - 4*UP )
     &    + TPM2*SP*T12*U1M2*S4 * (  - 8 )
     &    + TPM2*SP*T12*U1M1*S4*U7M1 * ( 4 )
     &    + TPM2*SP*U1M1*S3*U62*U7M1 * ( 4 )
     &    + TPM2*SP*S3*U62*U7M2 * (  - 8 )
     &    + TPM2*SP2*T1*U1M2*S4 * (  - 4 )
     &    + TPM2*SP2*T1*U1M1*S4*U7M1 * ( 4 )
     &    + TPM2*SP2*U1M1*S3*U6*U7M1 * ( 4 )
     &    + TPM2*SP2*S3*U6*U7M2 * (  - 4 )
     &    + TPM2*T1*U1M1*S3*U62*U7M1 * ( 8 )
     &    + TPM2*T1*U1M1*U62*U7M1*Q2 * ( 4 )
     &    + TPM2*T1*U1M1*U62*U7M1 * ( 4*UP )
     &    + TPM2*T1*S4*U62*U7M2 * (  - 4 )
     &    + TPM2*T1*U62*U7M2*Q2 * (  - 4 )
     &    + TPM2*T1*U62*U7M2 * (  - 4*UP )
     &    + TPM2*T12*U1M2*S3*U6 * (  - 4 )
     &    + TPM2*T12*U1M2*U6*Q2 * (  - 4 )
     &    + TPM2*T12*U1M2*U6 * (  - 4*UP )
     &    + TPM2*T12*U1M1*S4*U6*U7M1 * ( 8 )
     &    + TPM2*T12*U1M1*U6*U7M1*Q2 * ( 4 )
     &    + TPM2*T12*U1M1*U6*U7M1 * ( 4*UP )
     &    + TPM2*T13*U1M2*S4 * (  - 4 )
     &    + TPM2*S3*U63*U7M2 * (  - 4 )
     &    + TPM1*M2*SP*T1*U1M2 * (  - 8 )
     &    + TPM1*M2*SP*T1*U1M1*U7M1 * ( 8 )
     &    + TPM1*M2*SP*U1M1*U6*U7M1 * ( 8 )
     &    + TPM1*M2*SP*U6*U7M2 * (  - 8 )
     &    + TPM1*M2*SP2*U1M1*U7M1 * ( 8 )
     &    + TPM1*M2*T1*U1M1*U6*U7M1 * ( 16 )
     &    + TPM1*M2*T12*U1M2 * (  - 8 )
     &    + TPM1*M2*U62*U7M2 * (  - 8 )
     &    + TPM1*SP*T1*U1M1*U7M1*Q2 * (  - 4 )
     &    + TPM1*SP*T1*U1M1 * (  - 4 )
     &    + TPM1*SP*U1M1*U6*U7M1 * (  - 4*U1P )
     &    + TPM1*T1*U1M2*U6*Q2 * (  - 4 )
     &    + TPM1*T1*U1M2*U6 * ( 4*U1P )
     &    + TPM1*T1*U6*U7M1 * ( 4 )
     &    + TPM1*T12*U1M1*U7M1*Q2 * (  - 4 )
     &    + TPM1*T12*U1M1 * (  - 4 )
     &    + TPM1*U1M1*U62*U7M1 * (  - 4*U1P )

        FQLC = TP*TERM1
        FQLC = 4.D0*Q2*FQLC/SP/SP

      END IF

      RETURN
      END
      FUNCTION FQLD(X,Y,M2,Q2,S,SP,T1,U1,TP,UP,S3,S4,S5,U6,U7,DP,DM)
C
C THIS IS THE EL*EL PIECE OF F_Q_L (I.E. TERM 3) IN 3 CASES
C 1) SOFT LIMIT
C 2) COLLINEAR LIMIT
C 3) HARD
C
C LIMITS CHECK UNDER THETA2 INTEGRATION: 12/1/94
C LIMITS CHECK W/O   THETA2 INTEGRATION: 2/15/95
C
C IT IS TP*M^Q_L(3) OF THE PAPER
C THERE IS AN OVERALL FACTOR OF G^4 EL^2 N CF UNDERSTOOD
C
      IMPLICIT DOUBLE PRECISION (A-Z)
      PARAMETER (DELTAS=1.0D-7)
      PARAMETER (DELTAC=1.0D-7)

      ONEMX = 1.D0 - X
      ONEPY = 1.D0 + Y

      IF ( ONEMX.LT.DELTAS ) THEN
        FQLD = 0.D0
      ELSE IF ( ONEPY.LT.DELTAC ) THEN
        FQLD = 0.D0
      ELSE
        Q4 = Q2*Q2
        S52 = S5*S5
        S53 = S5*S52
        S54 = S5*S53
        S5M1 = 1.D0/S5
        S5M2 = S5M1*S5M1
        S42 = S4*S4
        S4M1 = 1.D0/S4
        S4M2 = S4M1*S4M1
        S32 = S3*S3
        S3M1 = 1.D0/S3
        S3M2 = S3M1*S3M1
        S2 = S*S
        SM1 = 1.D0/S
        SPM1 = 1.D0/SP
        SPM2 = SPM1*SPM1
        U62 = U6*U6
        U63 = U6*U62
        U6M1 = 1.D0/U6
        U6M2 = U6M1*U6M1
        U7M1 = 1.D0/U7
        U7M2 = U7M1*U7M1
        TP2 = TP*TP
        TP3 = TP*TP2
        TP4 = TP*TP3
        TPM1 = 1.D0/TP
        UP2 = UP*UP
        UP3 = UP*UP2
        UPM1 = 1.D0/UP
        UPM2 = UPM1*UPM1
        T12 = T1*T1
        T13 = T1*T12
        T1M1 = 1.D0/T1
        T1M2 = T1M1*T1M1
        U1M1 = 1.D0/U1
        U1M2 = U1M1*U1M1
        U1P = U1+Q2

        TERM3 =
     &    + M2*S5M2*UPM2*TP4 * (  - 32.D0*SPM2*Q2 )
     &    + M2*S5M2*UPM2*TP3 * (  - 64.D0*SPM1*Q2 )
     &    + M2*S5M2*UPM2*TP2 * (  - 32.D0*Q2 )
     &    + T1*S4*S5M2*UPM2*TP3 * (  - 16.D0*SPM2*Q2 )
     &    + T1*S4*S5M2*UPM2*TP2 * (  - 16.D0*SPM1*Q2 )
     &    + T1*S5M2*UPM1*TP2*U6 * ( 32.D0*SPM2*Q2 )
     &    + T1*S5M2*UPM2*TP3*U7 * (  - 16.D0*SPM2*Q2 )
     &    + T1*S5M2*UPM2*TP3 * (  - 16.D0*SPM2*Q4 )
     &    + T1*S5M2*UPM2*TP2*U7 * (  - 16.D0*SPM1*Q2 )
     &    + T1*S5M2*UPM2*TP2 * (  - 16.D0*SPM1*Q4 )
     &    + U1P*S5M2*UPM2*TP3*U6 * (  - 16.D0*SPM2*Q2 )
     &    + U1P*S5M2*UPM2*TP2*U6 * (  - 16.D0*SPM1*Q2 )
     &    + S3*S5M2*UPM2*TP3*U6 * (  - 16.D0*SPM2*Q2 )
     &    + S3*S5M2*UPM2*TP2*U6 * (  - 16.D0*SPM1*Q2 )

        FQLD = TERM3

      END IF

      RETURN
      END
CBH      DOUBLE PRECISION FUNCTION VOKGAM2(SP,T1,U1,M2,Q2,DEL,S4MAX,S4,MU)
      DOUBLE PRECISION FUNCTION VOKG2(T1,SP,M2,Q2,RHOTILDE)
C
C HERE WE COMPUTE THE EXPRESSION FOR THE CA*CF PART OF THE
C SOFT PLUS VIRTUAL MATRIX ELEMENT.
C
      IMPLICIT DOUBLE PRECISION (A-Z)
      INTEGER I
      DIMENSION SPV(46)
      PARAMETER( PI = 3.14159265359D0 )
      DATA ZETA2/1.644934066848226D+00/
C
CSR      LOGDEL = DLOG(DEL/M2)
CSR      LOGDEL2 = LOGDEL*LOGDEL
C HERE WE REPLACE THE LOGDEL TERMS BY INTEGRALS OVER S4
CBH OH NO WE DON'T
CBH        DIST = S4MAX - DEL
CBH       L11 = DLOG(S4/M2)
CBH        L12 = DLOG(S4MAX/M2)
CBH        LOGDEL = L12 - DIST/S4
CBH        LOGDEL2 = L12*L12 -2.0D0*DIST*L11/S4
C
CBH WE REPLACE LOG(DEL/M2) = ARBITRARY
CBH SINCE WE SUBTRACT IT OFF LATER ANYHOW
      LOGDEL = -0.1D0
      LOGDEL2 = LOGDEL*LOGDEL
CBH NOW THE NEW SOFT PARAMETER
      LNB = 0.5D0*DLOG(1.D0-RHOTILDE)
      LNBX2 = LNB*LNB
CBH THE Q2 COMING INTO THE ROUTINE IS POSITIVE
CBH BUT IN THIS ROUTINE THE Q2 SHOULD BE NEGATIVE
CBH SO WE CHANGE THE SIGN HERE
      QTMP = Q2
      Q2 = -QTMP
CBH
      S = SP + Q2
      U1 = -SP-T1
CBH I HAVE REMOVED ALL OF THE MU DEPENDENCE BY HAND.  SEE BELOW
CSR      MU2 = M2
CBH      MU2 = MU*MU
CBH      CEP = 1.D0/16.D0/PI/PI
      S1 = 4.0D0*M2 -S
      S1M1 = 1.D0/S1
      T = T1+M2
      U = U1+M2
      XSQ = DSQRT(1.0D0 - 4.0D0*M2/S)
      YSQ = DSQRT(1.0D0 - 4.0D0*M2/Q2)
      X = (1.D0 - XSQ)/(1.D0 + XSQ)
      SQ = S*XSQ
      SQM = 1.D0/SQ
      SP = S - Q2
      Y = (1.D0-YSQ)/(1.D0+YSQ)
      X1 = (1.D0+YSQ)/2.D0
      X2 = (1.D0-YSQ)/2.D0
      AA = DSQRT(4.D0*M2 -Q2)
      AA2 = 4.D0*M2 -Q2
      BB = DSQRT(-Q2)
      CC = DSQRT(4.D0*M2*Q2/S - Q2)
      LAT = T*T + M2*M2 + Q2*Q2 - 2.D0*T*M2 - 2.D0*T*Q2 - 2*M2*Q2
      LAU = U*U + M2*M2 + Q2*Q2 - 2.D0*U*M2 - 2.D0*U*Q2 - 2*M2*Q2
      LH = DSQRT(LAT)
      LHP = DSQRT(LAU)
      LOG1 = DLOG(X)
      LOG2 = DLOG(S/M2)
CBH
      LOG1X2 = LOG1*LOG1
      LOG2X2 = LOG2*LOG2
      LOGSP = DLOG(SP/M2)
      LOGSPX2 = LOGSP*LOGSP
CBH
      LOG3 = DLOG(-T1/M2)
      LOG3X2 = LOG3*LOG3
      LOG4 = DLOG(-U1/M2)
      LOG4X2 = LOG4*LOG4
      LOG5 = DLOG(1.D0-X)
      LOG6 = DLOG(1.D0+X)
      LOG7 = DLOG(-Y)
      LOG7X2 = LOG7*LOG7
      LOG8 = DLOG(-Q2/S)
      LOG9 = DLOG(X1)
      LOG10 = DLOG(-X2)
CBH      LOGMU = DLOG(MU2/M2)
      LOGQ1 = DLOG((AA+CC)*(AA+CC)/4.D0/M2)
      LOGQ2 = DLOG((AA-BB)/(AA+BB))
      LOGQ3 = DLOG((AA-CC)/(AA-BB))
      LOGQ3X2 = LOGQ3*LOGQ3
      DLOG1 = DILOG(-X)
      DLOG2 = DILOG(X)
      DLOG3 = DILOG(T1/M2 + 1.D0)
      DLOG4 = DILOG(U1/M2 + 1.D0)
      DLOG5 = DILOG(1.D0-U1/X/T1)
      DLOG6 = DILOG(1.D0-T1/X/U1)
      DLOG7 = DILOG(Q2*X1/M2)
      DLOG8 = DILOG(Q2*X2/M2)
      DLOGQ1 = DILOG((AA-BB)/(AA-CC))
      DLOGQ2 = DILOG((AA-CC)/(AA+BB))
      DLOGQ3 = DILOG((BB+CC)/(AA+CC))
      DLOGQ4 = DILOG((CC-BB)/(AA+CC))
      DLOGQ5 = DILOG(S/SP)
      DLOGQ6T = DILOG((T1+AA2+LH)/(T1-YSQ*(LH+Q2*YSQ)))
      DLOGQ6U = DILOG((U1+AA2+LHP)/(U1-YSQ*(LHP+Q2*YSQ)))
      DLOGQ7T = DILOG((T1+AA2+LH)/(T1+YSQ*(LH-Q2*YSQ)))
      DLOGQ7U = DILOG((U1+AA2+LHP)/(U1+YSQ*(LHP-Q2*YSQ)))
      DLOGQ8T = DILOG((T1+AA2-LH)/(T1-YSQ*(LH+Q2*YSQ)))
      DLOGQ8U = DILOG((U1+AA2-LHP)/(U1-YSQ*(LHP+Q2*YSQ)))
      DLOGQ9T = DILOG((T1+AA2-LH)/(T1+YSQ*(LH-Q2*YSQ)))
      DLOGQ9U = DILOG((U1+AA2-LHP)/(U1+YSQ*(LHP-Q2*YSQ)))
      DLOGQ10T = DILOG( (T1*(Q2 - T - M2 - LH) - 2.D0*M2*LH)/
     &     (T1*(Q2 - T - M2 + LH)))
      DLOGQ10U = DILOG( (U1*(Q2 - U - M2 - LHP) - 2.D0*M2*LHP)/
     &     (U1*(Q2 - U - M2 + LHP)))
      DLOGQ11T = DILOG( (T1*(Q2 - T - M2 - LH) - 2.D0*M2*LH)/
     &     (T1*(Q2 - T - M2 - LH)))
      DLOGQ11U = DILOG( (U1*(Q2 - U - M2 - LHP) - 2.D0*M2*LHP)/
     &     (U1*(Q2 - U - M2 - LHP)))
      DLOGQ12T = DILOG( (Q2 - T - M2 + LH)/(Q2 - T - M2 - LH))
      DLOGQ12U = DILOG( (Q2 - U - M2 + LHP)/(Q2 - U - M2 - LHP))
      DLOGQ13T = DILOG( (M2 - T - LH)/(M2 - T))
      DLOGQ13U = DILOG( (M2 - U - LHP)/(M2 - U))
C MORE USEFUL DEFINITIONS:
CBH      CFCA = 4.D0
      M22 = M2*M2
      M23 = M2*M22
      T1P2 = T1*T1
      T1P3 = T1*T1P2
      T1P4 = T1*T1P3
      T1P5 = T1*T1P4
      T1P6 = T1*T1P5
      T1M1 = 1.D0/T1
      T1M2 = T1M1*T1M1
      T1M3 = T1M2*T1M1
      U1P2 = U1*U1
      U1P3 = U1*U1P2
      U1P4 = U1*U1P3
      U1P5 = U1*U1P4
      U1P6 = U1*U1P5
      U1M1 = 1.D0/U1
      U1M2 = U1M1*U1M1
      U1M3 = U1M1*U1M2
      UM1 = 1.D0/U
      UM2 = UM1*UM1
      TM1 = 1.D0/T
      TM2 = TM1*TM1
      Q22 = Q2*Q2
      Q23 = Q2*Q22
      Q24 = Q22*Q22
      TB = T1M1*U1M1
      SM1 = 1.D0/S
      SM2 = SM1*SM1
      SQM1 = 1.D0/SQ
      SPM1 = 1.D0/SP
      SPM2 = SPM1*SPM1
      SPM3 = SPM1*SPM2
      SPM4 = SPM2*SPM2
      LHM1 = 1.D0/LH
      LHM2 = LHM1*LHM1
      LHM3 = LHM1*LHM2
      LHM4 = LHM2*LHM2
      LHM5 = LHM2*LHM3
      LHPM1 = 1.D0/LHP
      LHPM2 = LHPM1*LHPM1
      LHPM3 = LHPM1*LHPM2
      LHPM4 = LHPM2*LHPM2
      LHPM5 = LHPM2*LHPM3
      XSQM1 = 1.D0/XSQ
CBH      LOG1X2 = LOG1*LOG1
CBH
      ONEMBETA = 1.D0 - XSQ
      ONEMBETAM1 = 1.D0/ONEMBETA
      ONEPBETA = 1.D0 + XSQ
      ONEPBETAM1 = 1.D0/ONEPBETA
CBH
      LI2B = DILOG(2.D0*XSQ*ONEPBETAM1)
      LIT1 = DILOG(1.D0+2.D0*T1*SPM1*ONEMBETAM1)
      LIU1 = DILOG(1.D0+2.D0*U1*SPM1*ONEMBETAM1)
      LIT2 = DILOG(1.D0+0.5D0*SP*ONEPBETA*T1M1)
      LIU2 = DILOG(1.D0+0.5D0*SP*ONEPBETA*U1M1)
      LNBT = DLOG(-0.5D0*SP*T1M1*ONEMBETA)
      LNBTX2 = LNBT*LNBT
      LNBU = DLOG(-0.5D0*SP*U1M1*ONEMBETA)
      LNBUX2 = LNBU*LNBU
CBH
      BQED =
     &  (( -4*(T1 + U1)**2*M22 - 2*M2*( Q2*( T1P2 + U1P2)
     &  + 2*T1*U1*(T1 + U1)) + T1*U1*(T1P2 + U1P2 -
     &  2*Q2*(T1 + U1) + 2* Q22)) *T1M2*U1M2 )
      MQED =
     &  (   M2*(U1*T1M2 + T1*U1M2 - U1M1 - T1M1
     &  -3*Q2*(T1M2 + U1M2) + 2*Q22*(U1M1*T1M2 + T1M1*U1M2)
     &  -8*M2*(Q2/2.D0*(T1M3+U1M3)+U1M1*T1M1 + T1M2 + U1M2)
     &  -8*M22*(T1M3 + U1M3 + U1M1*T1M2 + T1M1*U1M2)))
C
C HERE IS THE MATRIX ELEMENT.
C
      SPV(1) =
     &  +M23*LOG1*LOG5*SQM*(-512*TB-256*U1M2-256*
     &  T1M2)
     &  +M23*LOG1*LOG6*SQM*(512*TB+256*U1M2+256*
     &  T1M2)
     &  +M23*LOG1*LOG3*SQM*(-256*TB-256*T1M2)
     &  +M23*LOG1*LOG4*SQM*(-256*TB-256*U1M2)
     &  +M23*LOG1*SQM*LOGQ1*(256*TB+128*U1M2+128*
     &  T1M2)
     &  +M23*LOG3*LHM4*(128*U1M1*T1P2*TM1*Q2+128*T1*TM1*Q2)
     &  +M23*DLOG2*SQM*(-512*TB-256*U1M2-256*T1M2
     &  )
     &  +M23*DLOG1*SQM*(512*TB+256*U1M2+256*T1M2)
     &  +M23*ZETA2*SQM*(-1792*TB-896*U1M2-896*
     &  T1M2)
     &  +M23*ZETA2*LHM5*(128*U1M1*T1P2*Q2+128*T1*Q2)
     &  +M23*SQM*LOG8*LOGQ2*(256*TB+128*U1M2+128*
     &  T1M2)
      SPV(2) =
     &  +M23*SQM*DLOGQ1*(512*TB+256*U1M2+256*T1M2)
     &  +M23*SQM*DLOGQ2*(512*TB+256*U1M2+256*T1M2)
     &  +M23*SQM*DLOGQ3*(512*TB+256*U1M2+256*T1M2)
     &  +M23*SQM*DLOGQ4*(-512*TB-256*U1M2-256*
     &  T1M2)
     &  +M23*SQM*LOGQ3X2*(256*TB+128*U1M2+128*T1M2
     &  )
     &  +M23*LHM5*DLOGQ6T*(-128*U1M1*T1P2*Q2-128*T1*Q2)
     &  +M23*LHM5*DLOGQ7T*(-128*U1M1*T1P2*Q2-128*T1*Q2)
     &  +M23*LHM5*DLOGQ8T*(128*U1M1*T1P2*Q2+128*T1*Q2)
     &  +M23*LHM5*DLOGQ9T*(128*U1M1*T1P2*Q2+128*T1*Q2)
     &  +M23*LHM5*DLOGQ10T*(128*U1M1*T1P2*Q2+128*T1*Q2)
     &  +M23*LHM5*DLOGQ11T*(128*U1M1*T1P2*Q2+128*T1*Q2)
     &  +M23*LHM5*DLOGQ12T*(-128*U1M1*T1P2*Q2-128*T1*Q2)
     &  +M23*LHM5*DLOGQ13T*(-256*U1M1*T1P2*Q2-256*T1*Q2)
     &  +M22*LOG1X2*SQM*(-32*U1M1-32*T1M1)
     &  +M22*LOG1X2*(-32*U1M1*SPM1-32*T1M1*SPM1)
      SPV(3) =
     &  +M22*LOG1*LOG5*SQM*(-128*U1*T1M2+256*TB*Q2
     &  -640*U1M1-128*U1M2*T1-640*T1M1)
     &  +M22*LOG1*LOG6*SQM*(128*U1*T1M2-256*TB*Q2+
     &  768*U1M1+128*U1M2*T1+768*T1M1)
     &  +M22*LOG1*LOG3*SQM*(-128*U1*T1M2+128*TB*Q2
     &  -384*U1M1-384*T1M1)
     &  +M22*LOG1*LOG4*SQM*(128*TB*Q2-384*U1M1-128*
     &  U1M2*T1-384*T1M1)
     &  +M22*LOG1*SQM*LOGQ1*(64*U1*T1M2-128*TB*Q2+
     &  384*U1M1+64*U1M2*T1+384*T1M1)
     &  +M22*LOG1*SQM*(-256*U1*T1M1*Q2*SPM2+128*U1*T1M1*
     &  SPM1-256*U1M1*T1*Q2*SPM2+128*U1M1*T1*SPM1-384*U1M1*Q2*
     &  SPM1+128*U1M1-384*T1M1*Q2*SPM1+128*T1M1-512*Q2*SPM2+
     &  256*SPM1)
     &  +M22*LOG3X2*(64*TB)
     &  +M22*LOG3*LOG4*(128*TB+128*U1M2+128*T1M2)
      SPV(4) =
     &  +M22*LOG3*LHM2*(32*U1M1*T1P3*TM2+32*U1M1*T1P2*TM1+32
     &  *U1M1*T1P2*TM2*Q2+32*T1P2*TM2+32*T1*TM1+32*T1*TM2*Q2)
     &  +M22*LOG3*LHM4*(-128*U1*T1*TM1*Q2-32*U1M1*T1P4*TM1+
     &  192*U1M1*T1P3*TM1*Q2+32*U1M1*T1P2*TM1*Q22-32*T1P3*TM1+64*
     &  T1P2*TM1*Q2+32*T1*TM1*Q22)
     &  +M22*LOG3*(16*U1*T1M2*TM1-32*U1M1*T1*TM2+16*U1M1*
     &  TM1+32*T1M1*TM1-32*TM2)
     &  +M22*LOG4X2*(64*TB)
     &  +M22*LOG4*(32*U1M1*UM1+16*U1M2*T1*UM1+16*T1M1*UM1)
     &  +M22*DLOG2*SQM*(-128*U1*T1M2+256*TB*Q2-640
     &  *U1M1-128*U1M2*T1-640*T1M1)
     &  +M22*DLOG3*(16*U1*T1M3+16*TB+32*T1M2)
     &  +M22*DLOG4*(16*TB+32*U1M2+16*U1M3*T1)
     &  +M22*DLOG1*SQM*(128*U1*T1M2-256*TB*Q2+768*
     &  U1M1+128*U1M2*T1+768*T1M1)
     &  +M22*ZETA2*SQM*(-448*U1*T1M2+896*TB*Q2-
     &  2432*U1M1-448*U1M2*T1-2432*T1M1)
      SPV(5) =
     &  +M22*ZETA2*LHM1*(-64*U1M1)
     &  +M22*ZETA2*LHM3*(32*U1M1*T1P2-64*U1M1*T1*Q2+32*T1-
     &  64*Q2)
     &  +M22*ZETA2*LHM5*(-128*U1*T1*Q2-32*U1M1*T1P4+224*
     &  U1M1*T1P2*Q22-32*T1P3-128*T1P2*Q2+224*T1*Q22)
     &  +M22*ZETA2*LHPM1*(-64*T1M1)
     &  +M22*ZETA2*LHPM3*(-64*U1*T1M1*Q2-128*Q2)
     &  +M22*ZETA2*(-16*U1*T1M3-96*TB+192*U1M1*
     &  SPM1-256*U1M2-16*U1M3*T1+192*T1M1*SPM1-256*T1M2)
     &  +M22*SQM*LOG8*LOGQ2*(64*U1*T1M2-128*TB*Q2+
     &  384*U1M1+64*U1M2*T1+384*T1M1)
     &  +M22*SQM*DLOGQ1*(128*U1*T1M2-256*TB*Q2+768*
     &  U1M1+128*U1M2*T1+768*T1M1)
     &  +M22*SQM*DLOGQ2*(128*U1*T1M2-256*TB*Q2+768*
     &  U1M1+128*U1M2*T1+768*T1M1)
     &  +M22*SQM*DLOGQ3*(128*U1*T1M2-256*TB*Q2+768*
     &  U1M1+128*U1M2*T1+768*T1M1)
      SPV(6) =
     &  +M22*SQM*DLOGQ4*(-128*U1*T1M2+256*TB*Q2-
     &  768*U1M1-128*U1M2*T1-768*T1M1)
     &  +M22*SQM*LOGQ3X2*(64*U1*T1M2-128*TB*Q2+384*
     &  U1M1+64*U1M2*T1+384*T1M1)
     &  +M22*LOG9*LHM2*(-128*U1M1*Q2*X1+128*U1M1*Q2*X2-128*
     &  T1M1*Q2*X1+128*T1M1*Q2*X2)
     &  +M22*LOG9*LHM4*(-192*U1M1*T1P2*Q2*X1+192*U1M1*T1P2*Q2
     &  *X2+192*U1M1*T1*Q22*X1-192*U1M1*T1*Q22*X2-192*T1*Q2*X1+
     &  192*T1*Q2*X2+192*Q22*X1-192*Q22*X2)
     &  +M22*LOG9*LHPM2*(-128*U1M1*Q2*X1+128*U1M1*Q2*X2-64*
     &  T1M1*Q2*X1+64*T1M1*Q2*X2)
     &  +M22*LOG10*LHM2*(128*U1M1*Q2*X1-128*U1M1*Q2*X2+128*
     &  T1M1*Q2*X1-128*T1M1*Q2*X2)
     &  +M22*LOG10*LHM4*(192*U1M1*T1P2*Q2*X1-192*U1M1*T1P2*Q2*
     &  X2-192*U1M1*T1*Q22*X1+192*U1M1*T1*Q22*X2+192*T1*Q2*X1-192
     &  *T1*Q2*X2-192*Q22*X1+192*Q22*X2)
      SPV(7) =
     &  +M22*LOG10*LHPM2*(128*U1M1*Q2*X1-128*U1M1*Q2*X2+64*
     &  T1M1*Q2*X1-64*T1M1*Q2*X2)
     &  +M22*LHM1*DLOGQ6T*(64*U1M1)
     &  +M22*LHM1*DLOGQ7T*(64*U1M1)
     &  +M22*LHM1*DLOGQ8T*(-64*U1M1)
     &  +M22*LHM1*DLOGQ9T*(-64*U1M1)
     &  +M22*LHM1*DLOGQ10T*(-64*U1M1)
     &  +M22*LHM1*DLOGQ11T*(-64*U1M1)
     &  +M22*LHM1*DLOGQ12T*(64*U1M1)
     &  +M22*LHM1*DLOGQ13T*(128*U1M1)
     &  +M22*LHM2*(-32*U1M1*T1P2*TM1-32*U1M1*T1*TM1*Q2-32
     &  *T1*TM1-32*TM1*Q2)
     &  +M22*LHM3*DLOGQ6T*(-32*U1M1*T1P2+64*U1M1*T1*Q2-32*T1
     &  +64*Q2)
     &  +M22*LHM3*DLOGQ7T*(-32*U1M1*T1P2+64*U1M1*T1*Q2-32*T1
     &  +64*Q2)
      SPV(8) =
     &  +M22*LHM3*DLOGQ8T*(32*U1M1*T1P2-64*U1M1*T1*Q2+32*T1-
     &  64*Q2)
     &  +M22*LHM3*DLOGQ9T*(32*U1M1*T1P2-64*U1M1*T1*Q2+32*T1-
     &  64*Q2)
     &  +M22*LHM3*DLOGQ10T*(32*U1M1*T1P2-64*U1M1*T1*Q2+32*T1-
     &  64*Q2)
     &  +M22*LHM3*DLOGQ11T*(32*U1M1*T1P2-64*U1M1*T1*Q2+32*T1-
     &  64*Q2)
     &  +M22*LHM3*DLOGQ12T*(-32*U1M1*T1P2+64*U1M1*T1*Q2-32*T1
     &  +64*Q2)
     &  +M22*LHM3*DLOGQ13T*(-64*U1M1*T1P2+128*U1M1*T1*Q2-64*
     &  T1+128*Q2)
     &  +M22*LHM5*DLOGQ6T*(128*U1*T1*Q2+32*U1M1*T1P4-224*U1M1*
     &  T1P2*Q22+32*T1P3+128*T1P2*Q2-224*T1*Q22)
     &  +M22*LHM5*DLOGQ7T*(128*U1*T1*Q2+32*U1M1*T1P4-224*U1M1*
     &  T1P2*Q22+32*T1P3+128*T1P2*Q2-224*T1*Q22)
      SPV(9) =
     &  +M22*LHM5*DLOGQ8T*(-128*U1*T1*Q2-32*U1M1*T1P4+224*
     &  U1M1*T1P2*Q22-32*T1P3-128*T1P2*Q2+224*T1*Q22)
     &  +M22*LHM5*DLOGQ9T*(-128*U1*T1*Q2-32*U1M1*T1P4+224*
     &  U1M1*T1P2*Q22-32*T1P3-128*T1P2*Q2+224*T1*Q22)
     &  +M22*LHM5*DLOGQ10T*(-128*U1*T1*Q2-32*U1M1*T1P4+224*
     &  U1M1*T1P2*Q22-32*T1P3-128*T1P2*Q2+224*T1*Q22)
     &  +M22*LHM5*DLOGQ11T*(-128*U1*T1*Q2-32*U1M1*T1P4+224*
     &  U1M1*T1P2*Q22-32*T1P3-128*T1P2*Q2+224*T1*Q22)
     &  +M22*LHM5*DLOGQ12T*(128*U1*T1*Q2+32*U1M1*T1P4-224*U1M1*
     &  T1P2*Q22+32*T1P3+128*T1P2*Q2-224*T1*Q22)
     &  +M22*LHM5*DLOGQ13T*(256*U1*T1*Q2+64*U1M1*T1P4-448*U1M1*
     &  T1P2*Q22+64*T1P3+256*T1P2*Q2-448*T1*Q22)
     &  +M22*LHPM1*DLOGQ6U*(64*T1M1)
     &  +M22*LHPM1*DLOGQ7U*(64*T1M1)
     &  +M22*LHPM1*DLOGQ8U*(-64*T1M1)
     &  +M22*LHPM1*DLOGQ9U*(-64*T1M1)
     &  +M22*LHPM1*DLOGQ10U*(-64*T1M1)
      SPV(10) =
     &  +M22*LHPM1*DLOGQ11U*(-64*T1M1)
     &  +M22*LHPM1*DLOGQ12U*(64*T1M1)
     &  +M22*LHPM1*DLOGQ13U*(128*T1M1)
     &  +M22*LHPM3*DLOGQ6U*(64*U1*T1M1*Q2+128*Q2)
     &  +M22*LHPM3*DLOGQ7U*(64*U1*T1M1*Q2+128*Q2)
     &  +M22*LHPM3*DLOGQ8U*(-64*U1*T1M1*Q2-128*Q2)
     &  +M22*LHPM3*DLOGQ9U*(-64*U1*T1M1*Q2-128*Q2)
     &  +M22*LHPM3*DLOGQ10U*(-64*U1*T1M1*Q2-128*Q2)
     &  +M22*LHPM3*DLOGQ11U*(-64*U1*T1M1*Q2-128*Q2)
     &  +M22*LHPM3*DLOGQ12U*(64*U1*T1M1*Q2+128*Q2)
     &  +M22*LHPM3*DLOGQ13U*(128*U1*T1M1*Q2+256*Q2)
     &  +M22*LOG7X2*(32*U1M1*SPM1+32*T1M1*SPM1)
     &  +M22*DLOG7*(128*TB+128*U1M2+128*T1M2)
     &  +M22*DLOG8*(128*TB+128*U1M2+128*T1M2)
     &  +M22* (32*U1M1*TM1+32*T1M1*TM1)
     &  +M2*LOG1X2*SQM*(48+8*U1*T1M1+8*U1M1*T1-24*U1M1*Q2
     &  -24*T1M1*Q2-32*BQED)
      SPV(11) =
     &  +M2*LOG1X2*(16*U1P2*T1M1*Q2*SPM3-16*U1P2*T1M1*SPM2+32*
     &  U1*T1M1*Q2*SPM2-16*U1*T1M1*SPM1+16*U1*Q2*SPM3-80*U1*SPM2
     &  +16*U1M1*T1P2*Q2*SPM3-16*U1M1*T1P2*SPM2+32*U1M1*T1*Q2*
     &  SPM2-16*U1M1*T1*SPM1+16*U1M1*Q2*SPM1+16*T1*Q2*SPM3-80*
     &  T1*SPM2+16*T1M1*Q2*SPM1+64*Q2*SPM2-64*SPM1)
     &  +M2*LOG1*LOG5*SQM*(-256-64*U1*T1M1-64*U1*T1M2*Q2
     &  -64*U1M1*T1+128*TB*Q22-64*U1M1*Q2-64*U1M2*T1*Q2
     &  +64*U1M2*Q22-64*T1M1*Q2+64*T1M2*Q22+64*BQED)
     &  +M2*LOG1*LOG6*SQM*(64+32*U1*T1M1+64*U1*T1M2*Q2+32*
     &  U1M1*T1-128*TB*Q22+160*U1M1*Q2+64*U1M2*T1*Q2-64*
     &  U1M2*Q22+160*T1M1*Q2-64*T1M2*Q22+64*BQED)
     &  +M2*LOG1*LOG3*SQM*(-32-32*U1*T1M1-64*U1*T1M2*Q2+
     &  64*TB*Q22-96*U1M1*Q2-64*T1M1*Q2+64*T1M2*Q22)
     &  +M2*LOG1*LOG4*SQM*(-32-32*U1M1*T1+64*TB*
     &  Q22-64*U1M1*Q2-64*U1M2*T1*Q2+64*U1M2*Q22-96*T1M1*Q2)
     &  +M2*LOG1*SQM*LOGQ1*(32+16*U1*T1M1+32*U1*T1M2*Q2+16*
     &  U1M1*T1-64*TB*Q22+80*U1M1*Q2+32*U1M2*T1*Q2-32*
     &  U1M2*Q22+80*T1M1*Q2-32*T1M2*Q22)
      SPV(12) =
     &  +M2*LOG1*SQM*(128+192*U1P3*T1M1*Q2*SPM3+64*U1P3*
     &  T1M1*SPM2-192*U1P2*T1M1*Q22*SPM3+256*U1P2*T1M1*Q2*SPM2-
     &  32*U1P2*T1M1*S1M1+160*U1P2*T1M1*SPM1+384*U1P2*Q2*SPM3+384*
     &  U1*T1*Q2*SPM3-128*U1*T1*SPM2-384*U1*T1M1*Q22*SPM2+32*U1*
     &  T1M1*Q2*S1M1-64*U1*T1M1*Q2*SPM1+128*U1*T1M1-192*U1*Q22*
     &  SPM3+640*U1*Q2*SPM2+32*U1*S1M1+96*U1*SPM1+192*U1M1*T1P3*
     &  Q2*SPM3+64*U1M1*T1P3*SPM2-192*U1M1*T1P2*Q22*SPM3+256*
     &  U1M1*T1P2*Q2*SPM2-32*U1M1*T1P2*S1M1+160*U1M1*T1P2*SPM1-
     &  384*U1M1*T1*Q22*SPM2+32*U1M1*T1*Q2*S1M1-64*U1M1*T1*Q2*SPM1
     &  +128*U1M1*T1-160*U1M1*Q22*SPM1-96*U1M1*Q2+384*T1P2*Q2*
     &  SPM3-192*T1*Q22*SPM3+640*T1*Q2*SPM2+32*T1*S1M1+96*T1*
     &  SPM1-160*T1M1*Q22*SPM1-96*T1M1*Q2-512*Q22*SPM2-64*Q2*
     &  S1M1+128*Q2*SPM1-64*BQED*LOGDEL)
     &  +M2*LOG3X2*(32*U1M1+32*T1M1)
     &  +M2*LOG3*LOG4*(64*U1M1+64*U1M2*Q2+64*T1M1+64*T1M2*Q2
     &  )
      SPV(13) =
     &  +M2*LOG3*LHM2*(-32*U1*T1*TM1+48*U1M1*T1P4*TM2-16*
     &  U1M1*T1P3*TM1+48*U1M1*T1P3*TM2*Q2+48*T1P3*TM2-48*T1P2*TM1
     &  +48*T1P2*TM2*Q2)
     &  +M2*LOG3*LHM4*(32*U1*T1P3*TM1-192*U1*T1P2*TM1*Q2+32*U1*
     &  T1*TM1*Q22-32*U1M1*T1P5*TM1+80*U1M1*T1P4*TM1*Q2+96*U1M1*
     &  T1P3*TM1*Q22-16*U1M1*T1P2*TM1*Q23-112*T1P3*TM1*Q2+128*
     &  T1P2*TM1*Q22-16*T1*TM1*Q23)
     &  +M2*LOG3*(16*U1*T1M1*TM1-48*U1M1*T1P2*TM2+32*U1M1*T1*
     &  TM1+16*U1M1*T1*TM2*Q2-48*T1*TM2-16*T1M1*TM1*Q2+48*TM1
     &  +16*TM2*Q2)
     &  +M2*LOG4X2*(32*U1M1+32*T1M1)
     &  +M2*LOG4*LHPM2*(-16*U1P3*T1M1*UM1+16*U1P2*T1M1*UM1*Q2
     &  -16*U1P2*UM1+16*U1*UM1*Q2)
     &  +M2*LOG4*(-16*U1P2*T1M1*UM2-16*U1*UM2+16*U1M1*T1*
     &  UM1-16*U1M1*UM1*Q2+16*UM1)
      SPV(14) =
     &  +M2*DLOG2*SQM*(-256-64*U1*T1M1-64*U1*T1M2*Q2-64*
     &  U1M1*T1+128*TB*Q22-64*U1M1*Q2-64*U1M2*T1*Q2+64*
     &  U1M2*Q22-64*T1M1*Q2+64*T1M2*Q22+64*BQED)
     &  +M2*DLOG3*(16*U1M1+48*T1M1-16*T1M2*Q2)
     &  +M2*DLOG4*(48*U1M1-16*U1M2*Q2+16*T1M1)
     &  +M2*DLOG1*SQM*(64+32*U1*T1M1+64*U1*T1M2*Q2+32*
     &  U1M1*T1-128*TB*Q22+160*U1M1*Q2+64*U1M2*T1*Q2-64*
     &  U1M2*Q22+160*T1M1*Q2-64*T1M2*Q22+64*BQED)
     &  +M2*ZETA2*SQM*(-608-176*U1*T1M1-224*U1*T1M2*Q2-
     &  176*U1M1*T1+448*TB*Q22-368*U1M1*Q2-224*U1M2*T1*Q2
     &  +224*U1M2*Q22-368*T1M1*Q2+224*T1M2*Q22-32*BQED)
     &  +M2*ZETA2*LHM1*(-32*U1M1*T1-48*U1M1*Q2)
     &  +M2*ZETA2*LHM3*(-32*U1*T1+32*U1*Q2-16*U1M1*T1P3+240
     &  *U1M1*T1P2*Q2-176*U1M1*T1*Q22-48*T1P2+272*T1*Q2-48*Q22)
     &  +M2*ZETA2*LHM5*(32*U1*T1P3-128*U1*T1P2*Q2+96*U1*T1*Q22
     &  +16*U1M1*T1P5-160*U1M1*T1P4*Q2+272*U1M1*T1P3*Q22-128*
     &  U1M1*T1P2*Q23+48*T1P4-288*T1P3*Q2+368*T1P2*Q22-128*T1*Q23
     &  )
      SPV(15) =
     &  +M2*ZETA2*LHPM1*(-16-32*U1*T1M1-48*T1M1*Q2)
     &  +M2*ZETA2*LHPM3*(144*U1P2*T1M1*Q2+16*U1P2-128*U1*T1M1*
     &  Q22+160*U1*Q2+16*T1*Q2-48*Q22)
     &  +M2*ZETA2*(-96*U1P2*T1M1*Q2*SPM3+96*U1P2*T1M1*SPM2-
     &  192*U1*T1M1*Q2*SPM2+96*U1*T1M1*SPM1-96*U1*Q2*SPM3+480*U1*
     &  SPM2-96*U1M1*T1P2*Q2*SPM3+96*U1M1*T1P2*SPM2-192*U1M1*T1*
     &  Q2*SPM2+96*U1M1*T1*SPM1-96*U1M1*Q2*SPM1-96*U1M1-96*
     &  U1M2*Q2-96*T1*Q2*SPM3+480*T1*SPM2-96*T1M1*Q2*SPM1-96*
     &  T1M1-96*T1M2*Q2-384*Q2*SPM2+384*SPM1)
     &  +M2*SQM*LOG8*LOGQ2*(32+16*U1*T1M1+32*U1*T1M2*Q2+16
     &  *U1M1*T1-64*TB*Q22+80*U1M1*Q2+32*U1M2*T1*Q2-32*
     &  U1M2*Q22+80*T1M1*Q2-32*T1M2*Q22)
     &  +M2*SQM*DLOGQ1*(64+32*U1*T1M1+64*U1*T1M2*Q2+32*
     &  U1M1*T1-128*TB*Q22+160*U1M1*Q2+64*U1M2*T1*Q2-64*
     &  U1M2*Q22+160*T1M1*Q2-64*T1M2*Q22)
     &  +M2*SQM*DLOGQ2*(64+32*U1*T1M1+64*U1*T1M2*Q2+32*
     &  U1M1*T1-128*TB*Q22+160*U1M1*Q2+64*U1M2*T1*Q2-64*
     &  U1M2*Q22+160*T1M1*Q2-64*T1M2*Q22)
      SPV(16) =
     &  +M2*SQM*DLOGQ3*(64+32*U1*T1M1+64*U1*T1M2*Q2+32*
     &  U1M1*T1-128*TB*Q22+160*U1M1*Q2+64*U1M2*T1*Q2-64*
     &  U1M2*Q22+160*T1M1*Q2-64*T1M2*Q22)
     &  +M2*SQM*DLOGQ4*(-64-32*U1*T1M1-64*U1*T1M2*Q2-32*
     &  U1M1*T1+128*TB*Q22-160*U1M1*Q2-64*U1M2*T1*Q2+64*
     &  U1M2*Q22-160*T1M1*Q2+64*T1M2*Q22)
     &  +M2*SQM*LOGQ3X2*(32+16*U1*T1M1+32*U1*T1M2*Q2+16*
     &  U1M1*T1-64*TB*Q22+80*U1M1*Q2+32*U1M2*T1*Q2-32*
     &  U1M2*Q22+80*T1M1*Q2-32*T1M2*Q22)
     &  +M2*LOG9*LHM2*(-16*U1M1*T1P2*X1+16*U1M1*T1P2*X2+144*
     &  U1M1*T1*Q2*X1-144*U1M1*T1*Q2*X2-128*U1M1*Q22*X1+128*U1M1*
     &  Q22*X2-16*T1*X1+16*T1*X2+144*Q2*X1-144*Q2*X2)
     &  +M2*LOG9*LHM4*(64*U1*T1*Q2*X1-64*U1*T1*Q2*X2+64*U1*Q22*
     &  X1-64*U1*Q22*X2+48*U1M1*T1P4*X1-48*U1M1*T1P4*X2-240*U1M1*
     &  T1P3*Q2*X1+240*U1M1*T1P3*Q2*X2+176*U1M1*T1P2*Q22*X1-176*
     &  U1M1*T1P2*Q22*X2-112*U1M1*T1*Q23*X1+112*U1M1*T1*Q23*X2+48
     &  *T1P3*X1-48*T1P3*X2-176*T1P2*Q2*X1+176*T1P2*Q2*X2+240*T1*Q22
     &  *X1-240*T1*Q22*X2-112*Q23*X1+112*Q23*X2)
      SPV(17) =
     &  +M2*LOG9*LHPM2*(16*U1P2*T1M1*X1-16*U1P2*T1M1*X2+128*U1
     &  *T1M1*Q2*X1-128*U1*T1M1*Q2*X2+32*U1*X1-32*U1*X2+16*U1M1*T1
     &  *Q2*X1-16*U1M1*T1*Q2*X2-48*U1M1*Q22*X1+48*U1M1*Q22*X2-
     &  128*T1M1*Q22*X1+128*T1M1*Q22*X2+144*Q2*X1-144*Q2*X2)
     &  +M2*LOG9*(64*U1*T1M1*Q2*SPM2*X1-64*U1*T1M1*Q2*SPM2*X2
     &  -64*U1*T1M1*SPM1*X1+64*U1*T1M1*SPM1*X2+64*U1M1*T1*Q2*SPM2
     &  *X1-64*U1M1*T1*Q2*SPM2*X2-64*U1M1*T1*SPM1*X1+64*U1M1*T1*
     &  SPM1*X2+96*U1M1*Q2*SPM1*X1-96*U1M1*Q2*SPM1*X2-128*U1M1*X1
     &  +128*U1M1*X2+96*T1M1*Q2*SPM1*X1-96*T1M1*Q2*SPM1*X2-112*
     &  T1M1*X1+112*T1M1*X2+128*Q2*SPM2*X1-128*Q2*SPM2*X2-128*
     &  SPM1*X1+128*SPM1*X2)
     &  +M2*LOG10*LHM2*(16*U1M1*T1P2*X1-16*U1M1*T1P2*X2-144*
     &  U1M1*T1*Q2*X1+144*U1M1*T1*Q2*X2+128*U1M1*Q22*X1-128*U1M1*
     &  Q22*X2+16*T1*X1-16*T1*X2-144*Q2*X1+144*Q2*X2)
      SPV(18) =
     &  +M2*LOG10*LHM4*(-64*U1*T1*Q2*X1+64*U1*T1*Q2*X2-64*U1*
     &  Q22*X1+64*U1*Q22*X2-48*U1M1*T1P4*X1+48*U1M1*T1P4*X2+240*
     &  U1M1*T1P3*Q2*X1-240*U1M1*T1P3*Q2*X2-176*U1M1*T1P2*Q22*X1+
     &  176*U1M1*T1P2*Q22*X2+112*U1M1*T1*Q23*X1-112*U1M1*T1*Q23*X2
     &  -48*T1P3*X1+48*T1P3*X2+176*T1P2*Q2*X1-176*T1P2*Q2*X2-240*T1
     &  *Q22*X1+240*T1*Q22*X2+112*Q23*X1-112*Q23*X2)
     &  +M2*LOG10*LHPM2*(-16*U1P2*T1M1*X1+16*U1P2*T1M1*X2-
     &  128*U1*T1M1*Q2*X1+128*U1*T1M1*Q2*X2-32*U1*X1+32*U1*X2-16*
     &  U1M1*T1*Q2*X1+16*U1M1*T1*Q2*X2+48*U1M1*Q22*X1-48*U1M1*Q22
     &  *X2+128*T1M1*Q22*X1-128*T1M1*Q22*X2-144*Q2*X1+144*Q2*X2)
     &  +M2*LOG10*(-64*U1*T1M1*Q2*SPM2*X1+64*U1*T1M1*Q2*SPM2*
     &  X2+64*U1*T1M1*SPM1*X1-64*U1*T1M1*SPM1*X2-64*U1M1*T1*Q2*
     &  SPM2*X1+64*U1M1*T1*Q2*SPM2*X2+64*U1M1*T1*SPM1*X1-64*U1M1*
     &  T1*SPM1*X2-96*U1M1*Q2*SPM1*X1+96*U1M1*Q2*SPM1*X2+128*U1M1
     &  *X1-128*U1M1*X2-96*T1M1*Q2*SPM1*X1+96*T1M1*Q2*SPM1*X2+
     &  112*T1M1*X1-112*T1M1*X2-128*Q2*SPM2*X1+128*Q2*SPM2*X2+128
     &  *SPM1*X1-128*SPM1*X2)
      SPV(19) =
     &  +M2*LHM1*DLOGQ6T*(32*U1M1*T1+48*U1M1*Q2)
     &  +M2*LHM1*DLOGQ7T*(32*U1M1*T1+48*U1M1*Q2)
     &  +M2*LHM1*DLOGQ8T*(-32*U1M1*T1-48*U1M1*Q2)
     &  +M2*LHM1*DLOGQ9T*(-32*U1M1*T1-48*U1M1*Q2)
     &  +M2*LHM1*DLOGQ10T*(-32*U1M1*T1-48*U1M1*Q2)
     &  +M2*LHM1*DLOGQ11T*(-32*U1M1*T1-48*U1M1*Q2)
     &  +M2*LHM1*DLOGQ12T*(32*U1M1*T1+48*U1M1*Q2)
     &  +M2*LHM1*DLOGQ13T*(64*U1M1*T1+96*U1M1*Q2)
     &  +M2*LHM2*(32*U1*T1M1*Q2-48*U1M1*T1P3*TM1-48*U1M1*
     &  T1P2*TM1*Q2+32*U1M1*T1P2+32*U1M1*T1*Q2-32*U1M1*Q22-48*
     &  T1P2*TM1-48*T1*TM1*Q2+32*T1-32*T1M1*Q22+64*Q2)
     &  +M2*LHM3*DLOGQ6T*(32*U1*T1-32*U1*Q2+16*U1M1*T1P3-240*
     &  U1M1*T1P2*Q2+176*U1M1*T1*Q22+48*T1P2-272*T1*Q2+48*Q22)
     &  +M2*LHM3*DLOGQ7T*(32*U1*T1-32*U1*Q2+16*U1M1*T1P3-240*
     &  U1M1*T1P2*Q2+176*U1M1*T1*Q22+48*T1P2-272*T1*Q2+48*Q22)
     &  +M2*LHM3*DLOGQ8T*(-32*U1*T1+32*U1*Q2-16*U1M1*T1P3+240
     &  *U1M1*T1P2*Q2-176*U1M1*T1*Q22-48*T1P2+272*T1*Q2-48*Q22)
      SPV(20) =
     &  +M2*LHM3*DLOGQ9T*(-32*U1*T1+32*U1*Q2-16*U1M1*T1P3+240
     &  *U1M1*T1P2*Q2-176*U1M1*T1*Q22-48*T1P2+272*T1*Q2-48*Q22)
     &  +M2*LHM3*DLOGQ10T*(-32*U1*T1+32*U1*Q2-16*U1M1*T1P3+
     &  240*U1M1*T1P2*Q2-176*U1M1*T1*Q22-48*T1P2+272*T1*Q2-48*Q22
     &  )
     &  +M2*LHM3*DLOGQ11T*(-32*U1*T1+32*U1*Q2-16*U1M1*T1P3+
     &  240*U1M1*T1P2*Q2-176*U1M1*T1*Q22-48*T1P2+272*T1*Q2-48*Q22
     &  )
     &  +M2*LHM3*DLOGQ12T*(32*U1*T1-32*U1*Q2+16*U1M1*T1P3-240*
     &  U1M1*T1P2*Q2+176*U1M1*T1*Q22+48*T1P2-272*T1*Q2+48*Q22)
     &  +M2*LHM3*DLOGQ13T*(64*U1*T1-64*U1*Q2+32*U1M1*T1P3-480*
     &  U1M1*T1P2*Q2+352*U1M1*T1*Q22+96*T1P2-544*T1*Q2+96*Q22)
     &  +M2*LHM5*DLOGQ6T*(-32*U1*T1P3+128*U1*T1P2*Q2-96*U1*T1*
     &  Q22-16*U1M1*T1P5+160*U1M1*T1P4*Q2-272*U1M1*T1P3*Q22+128*
     &  U1M1*T1P2*Q23-48*T1P4+288*T1P3*Q2-368*T1P2*Q22+128*T1*Q23
     &  )
      SPV(21) =
     &  +M2*LHM5*DLOGQ7T*(-32*U1*T1P3+128*U1*T1P2*Q2-96*U1*T1*
     &  Q22-16*U1M1*T1P5+160*U1M1*T1P4*Q2-272*U1M1*T1P3*Q22+128*
     &  U1M1*T1P2*Q23-48*T1P4+288*T1P3*Q2-368*T1P2*Q22+128*T1*Q23
     &  )
     &  +M2*LHM5*DLOGQ8T*(32*U1*T1P3-128*U1*T1P2*Q2+96*U1*T1*Q22
     &  +16*U1M1*T1P5-160*U1M1*T1P4*Q2+272*U1M1*T1P3*Q22-128*
     &  U1M1*T1P2*Q23+48*T1P4-288*T1P3*Q2+368*T1P2*Q22-128*T1*Q23
     &  )
     &  +M2*LHM5*DLOGQ9T*(32*U1*T1P3-128*U1*T1P2*Q2+96*U1*T1*Q22
     &  +16*U1M1*T1P5-160*U1M1*T1P4*Q2+272*U1M1*T1P3*Q22-128*
     &  U1M1*T1P2*Q23+48*T1P4-288*T1P3*Q2+368*T1P2*Q22-128*T1*Q23
     &  )
     &  +M2*LHM5*DLOGQ10T*(32*U1*T1P3-128*U1*T1P2*Q2+96*U1*T1*Q22
     &  +16*U1M1*T1P5-160*U1M1*T1P4*Q2+272*U1M1*T1P3*Q22-128*
     &  U1M1*T1P2*Q23+48*T1P4-288*T1P3*Q2+368*T1P2*Q22-128*T1*Q23
     &  )
      SPV(22) =
     &  +M2*LHM5*DLOGQ11T*(32*U1*T1P3-128*U1*T1P2*Q2+96*U1*T1*Q22
     &  +16*U1M1*T1P5-160*U1M1*T1P4*Q2+272*U1M1*T1P3*Q22-128*
     &  U1M1*T1P2*Q23+48*T1P4-288*T1P3*Q2+368*T1P2*Q22-128*T1*Q23
     &  )
     &  +M2*LHM5*DLOGQ12T*(-32*U1*T1P3+128*U1*T1P2*Q2-96*U1*T1*
     &  Q22-16*U1M1*T1P5+160*U1M1*T1P4*Q2-272*U1M1*T1P3*Q22+128*
     &  U1M1*T1P2*Q23-48*T1P4+288*T1P3*Q2-368*T1P2*Q22+128*T1*Q23
     &  )
     &  +M2*LHM5*DLOGQ13T*(-64*U1*T1P3+256*U1*T1P2*Q2-192*U1*T1*
     &  Q22-32*U1M1*T1P5+320*U1M1*T1P4*Q2-544*U1M1*T1P3*Q22+256*
     &  U1M1*T1P2*Q23-96*T1P4+576*T1P3*Q2-736*T1P2*Q22+256*T1*Q23
     &  )
     &  +M2*LHPM1*DLOGQ6U*(16+32*U1*T1M1+48*T1M1*Q2)
     &  +M2*LHPM1*DLOGQ7U*(16+32*U1*T1M1+48*T1M1*Q2)
     &  +M2*LHPM1*DLOGQ8U*(-16-32*U1*T1M1-48*T1M1*Q2)
     &  +M2*LHPM1*DLOGQ9U*(-16-32*U1*T1M1-48*T1M1*Q2)
     &  +M2*LHPM1*DLOGQ10U*(-16-32*U1*T1M1-48*T1M1*Q2)
      SPV(23) =
     &  +M2*LHPM1*DLOGQ11U*(-16-32*U1*T1M1-48*T1M1*Q2)
     &  +M2*LHPM1*DLOGQ12U*(16+32*U1*T1M1+48*T1M1*Q2)
     &  +M2*LHPM1*DLOGQ13U*(32+64*U1*T1M1+96*T1M1*Q2)
     &  +M2*LHPM3*DLOGQ6U*(-144*U1P2*T1M1*Q2-16*U1P2+128*U1*
     &  T1M1*Q22-160*U1*Q2-16*T1*Q2+48*Q22)
     &  +M2*LHPM3*DLOGQ7U*(-144*U1P2*T1M1*Q2-16*U1P2+128*U1*
     &  T1M1*Q22-160*U1*Q2-16*T1*Q2+48*Q22)
     &  +M2*LHPM3*DLOGQ8U*(144*U1P2*T1M1*Q2+16*U1P2-128*U1*T1M1*
     &  Q22+160*U1*Q2+16*T1*Q2-48*Q22)
     &  +M2*LHPM3*DLOGQ9U*(144*U1P2*T1M1*Q2+16*U1P2-128*U1*T1M1*
     &  Q22+160*U1*Q2+16*T1*Q2-48*Q22)
     &  +M2*LHPM3*DLOGQ10U*(144*U1P2*T1M1*Q2+16*U1P2-128*U1*T1M1
     &  *Q22+160*U1*Q2+16*T1*Q2-48*Q22)
     &  +M2*LHPM3*DLOGQ11U*(144*U1P2*T1M1*Q2+16*U1P2-128*U1*T1M1
     &  *Q22+160*U1*Q2+16*T1*Q2-48*Q22)
     &  +M2*LHPM3*DLOGQ12U*(-144*U1P2*T1M1*Q2-16*U1P2+128*U1*
     &  T1M1*Q22-160*U1*Q2-16*T1*Q2+48*Q22)
      SPV(24)=
     &  +M2*LHPM3*DLOGQ13U*(-288*U1P2*T1M1*Q2-32*U1P2+256*U1*
     &  T1M1*Q22-320*U1*Q2-32*T1*Q2+96*Q22)
     &  +M2*LOG7X2*(-16*U1P2*T1M1*Q2*SPM3+16*U1P2*T1M1*SPM2
     &  -32*U1*T1M1*Q2*SPM2+16*U1*T1M1*SPM1-16*U1*Q2*SPM3+80*U1*
     &  SPM2-16*U1M1*T1P2*Q2*SPM3+16*U1M1*T1P2*SPM2-32*U1M1*T1*Q2
     &  *SPM2+16*U1M1*T1*SPM1-16*U1M1*Q2*SPM1-16*T1*Q2*SPM3+80*
     &  T1*SPM2-16*T1M1*Q2*SPM1-64*Q2*SPM2+64*SPM1)
     &  +M2*DLOG7*(64*U1M1+64*U1M2*Q2+64*T1M1+64*T1M2*Q2)
     &  +M2*DLOG8*(64*U1M1+64*U1M2*Q2+64*T1M1+64*T1M2*Q2)
     &  +M2* (16*U1*T1M1*UM1+64*U1*T1M1*SPM1-16*U1*T1M2+48*
     &  U1M1*T1*TM1+64*U1M1*T1*SPM1-16*U1M1*TM1*Q2+16*U1M1-16*
     &  U1M2*T1-16*T1M1*TM1*Q2+16*T1M1+16*UM1+48*TM1+128*
     &  SPM1)
     &  +XSQM1*LOG1X2*(16*BQED)
     &  +XSQM1*LOG1*LOG5*(-32*BQED)
     &  +XSQM1*LOG1*LOG6*(-32*BQED)
     &  +XSQM1*LOG1*(32*BQED*LOGDEL)
      SPV(25) =
     &  +XSQM1*DLOG2*(-32*BQED)
     &  +XSQM1*DLOG1*(-32*BQED)
     &  +XSQM1*ZETA2*(16*BQED)
     &  +LOG1X2*SQM*(4*U1P2*T1M1-12*U1*T1M1*Q2+20*U1+4*
     &  U1M1*T1P2-12*U1M1*T1*Q2+8*U1M1*Q22+20*T1+8*T1M1*Q22-
     &  32*Q2)
     &  +LOG1X2*(8*U1P4*T1M1*SPM3-16*U1P3*T1M1*Q2*SPM3+24*U1P3
     &  *T1M1*SPM2+24*U1P3*SPM3+32*U1P2*T1*SPM3+8*U1P2*T1M1*Q22*
     &  SPM3-48*U1P2*T1M1*Q2*SPM2+28*U1P2*T1M1*SPM1-32*U1P2*Q2*
     &  SPM3+64*U1P2*SPM2+32*U1*T1P2*SPM3-32*U1*T1*Q2*SPM3+80*U1*
     &  T1*SPM2+24*U1*T1M1*Q22*SPM2-56*U1*T1M1*Q2*SPM1+8*U1*Q22*
     &  SPM3-96*U1*Q2*SPM2+60*U1*SPM1+8*U1M1*T1P4*SPM3-16*U1M1*
     &  T1P3*Q2*SPM3+24*U1M1*T1P3*SPM2+8*U1M1*T1P2*Q22*SPM3-48*
     &  U1M1*T1P2*Q2*SPM2+28*U1M1*T1P2*SPM1+24*U1M1*T1*Q22*SPM2-
     &  56*U1M1*T1*Q2*SPM1+32*U1M1*Q22*SPM1+24*T1P3*SPM3-32*T1P2*
     &  Q2*SPM3+64*T1P2*SPM2+8*T1*Q22*SPM3-96*T1*Q2*SPM2+60*T1*
     &  SPM1+32*T1M1*Q22*SPM1+32*Q22*SPM2-96*Q2*SPM1-8*BQED)
      SPV(26) =
     &  +LOG1*LOG5*SQM*(32*U1P2*T1M1-96*U1*T1M1*Q2+32*U1+
     &  32*U1M1*T1P2-96*U1M1*T1*Q2-64*TB*Q23+128*U1M1*Q22
     &  +32*T1+128*T1M1*Q22-128*Q2)
     &  +LOG1*LOG6*SQM*(-48*U1P2*T1M1+144*U1*T1M1*Q2-112*
     &  U1-48*U1M1*T1P2+144*U1M1*T1*Q2+64*TB*Q23-160*
     &  U1M1*Q22-112*T1-160*T1M1*Q22+256*Q2)
     &  +LOG1*LOG3*SQM*(16*U1P2*T1M1-48*U1*T1M1*Q2+48*U1+32
     &  *U1M1*T1P2-96*U1M1*T1*Q2-32*TB*Q23+96*U1M1*Q22+
     &  64*T1+64*T1M1*Q22-128*Q2)
     &  +LOG1*LOG3*(-16*BQED)
     &  +LOG1*LOG4*SQM*(32*U1P2*T1M1-96*U1*T1M1*Q2+64*U1+16
     &  *U1M1*T1P2-48*U1M1*T1*Q2-32*TB*Q23+64*U1M1*Q22+
     &  48*T1+96*T1M1*Q22-128*Q2)
     &  +LOG1*LOG4*(16*BQED)
     &  +LOG1*SQM*LOGQ1*(-24*U1P2*T1M1+72*U1*T1M1*Q2-56*U1
     &  -24*U1M1*T1P2+72*U1M1*T1*Q2+32*TB*Q23-80*U1M1*
     &  Q22-56*T1-80*T1M1*Q22+128*Q2)
      SPV(27) =
     &  +LOG1*SQM*(48*U1P4*T1M1*Q2*SPM3+16*U1P4*T1M1*SPM2-
     &  96*U1P3*T1M1*Q22*SPM3+64*U1P3*T1M1*Q2*SPM2-8*U1P3*T1M1*
     &  S1M1+32*U1P3*T1M1*SPM1+144*U1P3*Q2*SPM3+16*U1P3*SPM2+192
     &  *U1P2*T1*Q2*SPM3-32*U1P2*T1*SPM2+48*U1P2*T1M1*Q23*SPM3-192
     &  *U1P2*T1M1*Q22*SPM2+16*U1P2*T1M1*Q2*S1M1-16*U1P2*T1M1*Q2*
     &  SPM1+24*U1P2*T1M1-192*U1P2*Q22*SPM3+288*U1P2*Q2*SPM2+32*
     &  U1P2*SPM1+192*U1*T1P2*Q2*SPM3-32*U1*T1P2*SPM2-192*U1*T1*Q22
     &  *SPM3+448*U1*T1*Q2*SPM2+16*U1*T1*S1M1+112*U1*T1M1*Q23*
     &  SPM2-8*U1*T1M1*Q22*S1M1-80*U1*T1M1*Q22*SPM1-40*U1*T1M1*
     &  Q2+48*U1*Q23*SPM3-480*U1*Q22*SPM2-16*U1*Q2*S1M1+112*U1*
     &  Q2*SPM1+40*U1+48*U1M1*T1P4*Q2*SPM3+16*U1M1*T1P4*SPM2-96*
     &  U1M1*T1P3*Q22*SPM3+64*U1M1*T1P3*Q2*SPM2-8*U1M1*T1P3*S1M1)
      SPV(28) = LOG1*SQM*(
     &    +32*U1M1*T1P3*SPM1+48*U1M1*T1P2*Q23*SPM3-192*U1M1*T1P2*
     &    Q22*SPM2+16*U1M1*T1P2*Q2*S1M1-16*U1M1*T1P2*Q2*SPM1+24*
     &    U1M1*T1P2+112*U1M1*T1*Q23*SPM2-8*U1M1*T1*Q22*S1M1-80*
     &    U1M1*T1*Q22*SPM1-40*U1M1*T1*Q2+64*U1M1*Q23*SPM1+16*U1M1
     &    *Q22+144*T1P3*Q2*SPM3+16*T1P3*SPM2-192*T1P2*Q22*SPM3+288
     &    *T1P2*Q2*SPM2+32*T1P2*SPM1+48*T1*Q23*SPM3-480*T1*Q22*SPM2
     &    -16*T1*Q2*S1M1+112*T1*Q2*SPM1+40*T1+64*T1M1*Q23*SPM1+
     &    16*T1M1*Q22+160*Q23*SPM2+16*Q22*S1M1-224*Q22*SPM1-48*
     &    Q2)
     &    +LOG3X2*(-8*U1*T1M1-8*U1M1*T1-16*TB*Q22+16
     &    *U1M1*Q2+16*T1M1*Q2+8*BQED)
     &    +LOG3*LOG4*(-16*U1*T1M1-16*U1M1*T1-32*TB*Q22
     &    +32*U1M1*Q2+32*T1M1*Q2-16*BQED)
     &    +LOG3*LHM2*(-32*U1*T1P2*TM1+16*U1M1*T1P5*TM2-16*
     &    U1M1*T1P4*TM1+16*U1M1*T1P4*TM2*Q2+24*U1M1*T1P3*TM1*Q2-8*
     &    U1M1*T1P2*TM1*Q22+16*T1P4*TM2-56*T1P3*TM1+16*T1P3*TM2*Q2
     &    +24*T1P2*TM1*Q2)
      SPV(29) =
     &  +LOG3*LHM4*(32*U1*T1P4*TM1-64*U1*T1P3*TM1*Q2+32*U1*T1P2
     &  *TM1*Q22-8*U1M1*T1P6*TM1-8*U1M1*T1P5*TM1*Q2+40*U1M1*T1P4
     &  *TM1*Q22-24*U1M1*T1P3*TM1*Q23+24*T1P5*TM1-72*T1P4*TM1*Q2
     &  +72*T1P3*TM1*Q22-24*T1P2*TM1*Q23)
     &  +LOG3*(-16*U1M1*T1P3*TM2+24*U1M1*T1P2*TM1+16*U1M1*
     &  T1P2*TM2*Q2-16*U1M1*T1*TM1*Q2-16*T1P2*TM2+16*T1*TM1+16*
     &  T1*TM2*Q2-16*TM1*Q2+32*BQED*LOGDEL)
     &  +LOG4X2*(-8*U1*T1M1-8*U1M1*T1-16*TB*Q22+16
     &  *U1M1*Q2+16*T1M1*Q2+8*BQED)
     &  +LOG4*LHPM2*(-8*U1P4*T1M1*UM1+16*U1P3*T1M1*UM1*Q2-
     &  16*U1P3*UM1-8*U1P2*T1M1*UM1*Q22+16*U1P2*UM1*Q2)
     &  +LOG4*(-16*U1P3*T1M1*UM2+24*U1P2*T1M1*UM1-16*U1P2*
     &  UM2+16*U1*UM1-32*BQED*LOGDEL)
     &  +DLOG2*SQM*(32*U1P2*T1M1-96*U1*T1M1*Q2+32*U1+32*
     &  U1M1*T1P2-96*U1M1*T1*Q2-64*TB*Q23+128*U1M1*Q22+
     &  32*T1+128*T1M1*Q22-128*Q2)
     &  +DLOG3*(16+8*U1M1*T1-16*U1M1*Q2)
CBH HERE (ABOVE) I REMOVE THE LOGMU DEPENDENCE BY HAND
CBH     &    UM2+16*U1*UM1-32*BQED*LOGDEL+32*BQED*LOGMU)
      SPV(30) =
     &  +DLOG4*(16+8*U1*T1M1-16*T1M1*Q2)
     &  +DLOG1*SQM*(-48*U1P2*T1M1+144*U1*T1M1*Q2-112*U1-
     &  48*U1M1*T1P2+144*U1M1*T1*Q2+64*TB*Q23-160*U1M1*
     &  Q22-112*T1-160*T1M1*Q22+256*Q2)
     &  +ZETA2*SQM*(136*U1P2*T1M1-408*U1*T1M1*Q2+232*U1+
     &  136*U1M1*T1P2-408*U1M1*T1*Q2-224*TB*Q23+496*U1M1*
     &  Q22+232*T1+496*T1M1*Q22-640*Q2)
     &  +ZETA2*LHM1*(8*U1+56*U1M1*T1P2-72*U1M1*T1*Q2+16*
     &  U1M1*Q22+80*T1-32*Q2)
     &  +ZETA2*LHM3*(-24*U1*T1P2+32*U1*T1*Q2-8*U1*Q22-64*
     &  U1M1*T1P4+176*U1M1*T1P3*Q2-160*U1M1*T1P2*Q22+48*U1M1*T1*
     &  Q23-96*T1P3+192*T1P2*Q2-112*T1*Q22+16*Q23)
     &  +ZETA2*LHM5*(16*U1*T1P4-48*U1*T1P3*Q2+48*U1*T1P2*Q22-
     &  16*U1*T1*Q23+16*U1M1*T1P6-64*U1M1*T1P5*Q2+96*U1M1*T1P4*Q22
     &  -64*U1M1*T1P3*Q23+16*U1M1*T1P2*Q24+32*T1P5-112*T1P4*Q2+
     &  144*T1P3*Q22-80*T1P2*Q23+16*T1*Q24)
     &  +ZETA2*LHPM1*(48*U1P2*T1M1-60*U1*T1M1*Q2+76*U1+4*T1
     &  +16*T1M1*Q22-36*Q2)
      SPV(31) =
     &  +ZETA2*LHPM3*(-40*U1P4*T1M1+116*U1P3*T1M1*Q2-60*U1P3
     &  -4*U1P2*T1-112*U1P2*T1M1*Q22+140*U1P2*Q2+8*U1*T1*Q2+36*U1
     &  *T1M1*Q23-100*U1*Q22-4*T1*Q22+20*Q23)
     &  +ZETA2*(-32-48*U1P4*T1M1*SPM3+96*U1P3*T1M1*Q2*SPM3
     &  -144*U1P3*T1M1*SPM2-144*U1P3*SPM3-192*U1P2*T1*SPM3-48*
     &  U1P2*T1M1*Q22*SPM3+288*U1P2*T1M1*Q2*SPM2-168*U1P2*T1M1*
     &  SPM1+192*U1P2*Q2*SPM3-384*U1P2*SPM2-192*U1*T1P2*SPM3+192*
     &  U1*T1*Q2*SPM3-480*U1*T1*SPM2-144*U1*T1M1*Q22*SPM2+336*U1*
     &  T1M1*Q2*SPM1-48*U1*Q22*SPM3+576*U1*Q2*SPM2-360*U1*SPM1-
     &  48*U1M1*T1P4*SPM3+96*U1M1*T1P3*Q2*SPM3-144*U1M1*T1P3*SPM2
     &  -48*U1M1*T1P2*Q22*SPM3+288*U1M1*T1P2*Q2*SPM2-168*U1M1*
     &  T1P2*SPM1-144*U1M1*T1*Q22*SPM2+336*U1M1*T1*Q2*SPM1+16*
     &  TB*Q22-192*U1M1*Q22*SPM1-144*T1P3*SPM3+192*T1P2*
     &  Q2*SPM3-384*T1P2*SPM2-48*T1*Q22*SPM3+576*T1*Q2*SPM2-360*
     &  T1*SPM1-192*T1M1*Q22*SPM1-192*Q22*SPM2+576*Q2*SPM1-24*
     &  BQED)
      SPV(32) =
     &  +SQM*LOG8*LOGQ2*(-24*U1P2*T1M1+72*U1*T1M1*Q2-56*U1
     &  -24*U1M1*T1P2+72*U1M1*T1*Q2+32*TB*Q23-80*U1M1*
     &  Q22-56*T1-80*T1M1*Q22+128*Q2)
     &  +SQM*DLOGQ1*(-48*U1P2*T1M1+144*U1*T1M1*Q2-112*U1-
     &  48*U1M1*T1P2+144*U1M1*T1*Q2+64*TB*Q23-160*U1M1*
     &  Q22-112*T1-160*T1M1*Q22+256*Q2)
     &  +SQM*DLOGQ2*(-48*U1P2*T1M1+144*U1*T1M1*Q2-112*U1-
     &  48*U1M1*T1P2+144*U1M1*T1*Q2+64*TB*Q23-160*U1M1*
     &  Q22-112*T1-160*T1M1*Q22+256*Q2)
     &  +SQM*DLOGQ3*(-48*U1P2*T1M1+144*U1*T1M1*Q2-112*U1-
     &  48*U1M1*T1P2+144*U1M1*T1*Q2+64*TB*Q23-160*U1M1*
     &  Q22-112*T1-160*T1M1*Q22+256*Q2)
     &  +SQM*DLOGQ4*(48*U1P2*T1M1-144*U1*T1M1*Q2+112*U1+48*
     &  U1M1*T1P2-144*U1M1*T1*Q2-64*TB*Q23+160*U1M1*Q22
     &  +112*T1+160*T1M1*Q22-256*Q2)
     &  +SQM*LOGQ3X2*(-24*U1P2*T1M1+72*U1*T1M1*Q2-56*U1-
     &  24*U1M1*T1P2+72*U1M1*T1*Q2+32*TB*Q23-80*U1M1*Q22
     &  -56*T1-80*T1M1*Q22+128*Q2)
      SPV(33) =
     &  +LOG9*LHM2*(16*U1*T1*X1-16*U1*T1*X2+16*U1*Q2*X1-16*U1*
     &  Q2*X2-56*U1M1*T1P3*X1+56*U1M1*T1P3*X2+112*U1M1*T1P2*Q2*X1-
     &  112*U1M1*T1P2*Q2*X2-128*U1M1*T1*Q22*X1+128*U1M1*T1*Q22*X2+
     &  40*U1M1*Q23*X1-40*U1M1*Q23*X2-40*T1P2*X1+40*T1P2*X2+112*
     &  T1*Q2*X1-112*T1*Q2*X2+8*T1M1*Q23*X1-8*T1M1*Q23*X2-80*Q22
     &  *X1+80*Q22*X2)
     &  +LOG9*LHM4*(-16*U1*T1P3*X1+16*U1*T1P3*X2+16*U1*T1P2*Q2
     &  *X1-16*U1*T1P2*Q2*X2+16*U1*T1*Q22*X1-16*U1*T1*Q22*X2-16*U1*
     &  Q23*X1+16*U1*Q23*X2+24*U1M1*T1P5*X1-24*U1M1*T1P5*X2-56*
     &  U1M1*T1P4*Q2*X1+56*U1M1*T1P4*Q2*X2+56*U1M1*T1P3*Q22*X1-56*
     &  U1M1*T1P3*Q22*X2-40*U1M1*T1P2*Q23*X1+40*U1M1*T1P2*Q23*X2+
     &  16*U1M1*T1*Q24*X1-16*U1M1*T1*Q24*X2+8*T1P4*X1-8*T1P4*X2-
     &  40*T1P3*Q2*X1+40*T1P3*Q2*X2+72*T1P2*Q22*X1-72*T1P2*Q22*X2-
     &  56*T1*Q23*X1+56*T1*Q23*X2+16*Q24*X1-16*Q24*X2)
      SPV(34) =
     &  +LOG9*LHPM2*(-32*U1P3*T1M1*X1+32*U1P3*T1M1*X2+100*
     &  U1P2*T1M1*Q2*X1-100*U1P2*T1M1*Q2*X2-44*U1P2*X1+44*U1P2*X2-4
     &  *U1*T1*X1+4*U1*T1*X2-104*U1*T1M1*Q22*X1+104*U1*T1M1*Q22*X2
     &  +124*U1*Q2*X1-124*U1*Q2*X2-4*U1M1*T1*Q22*X1+4*U1M1*T1*Q22
     &  *X2+20*U1M1*Q23*X1-20*U1M1*Q23*X2+8*T1*Q2*X1-8*T1*Q2*X2
     &  +36*T1M1*Q23*X1-36*T1M1*Q23*X2-100*Q22*X1+100*Q22*X2)
     &  +LOG9*(-48*U1P3*T1M1*Q2*SPM3*X1+48*U1P3*T1M1*Q2*SPM3*
     &  X2+48*U1P2*T1M1*Q22*SPM3*X1-48*U1P2*T1M1*Q22*SPM3*X2-96*
     &  U1P2*T1M1*Q2*SPM2*X1+96*U1P2*T1M1*Q2*SPM2*X2+8*U1P2*T1M1*
     &  SPM1*X1-8*U1P2*T1M1*SPM1*X2-96*U1P2*Q2*SPM3*X1+96*U1P2*Q2*
     &  SPM3*X2+32*U1P2*SPM2*X1-32*U1P2*SPM2*X2-96*U1*T1*Q2*SPM3*X1
     &  +96*U1*T1*Q2*SPM3*X2+64*U1*T1*SPM2*X1-64*U1*T1*SPM2*X2+112
     &  *U1*T1M1*Q22*SPM2*X1-112*U1*T1M1*Q22*SPM2*X2-64*U1*T1M1*Q2
     &  *SPM1*X1+64*U1*T1M1*Q2*SPM1*X2+40*U1*T1M1*X1-40*U1*T1M1*X2
     &  +48*U1*Q22*SPM3*X1-48*U1*Q22*SPM3*X2-224*U1*Q2*SPM2*X1+
     &  224*U1*Q2*SPM2*X2+72*U1*SPM1*X1-72*U1*SPM1*X2-48*U1M1*T1P3*
     &  Q2*SPM3*X1+48*U1M1*T1P3*Q2*SPM3*X2+48*U1M1*T1P2*Q22*SPM3*X1)
      SPV(35) = LOG9*(
     &    -48*U1M1*T1P2*Q22*SPM3*X2-96*U1M1*T1P2*Q2*SPM2*X1+96*U1M1
     &    *T1P2*Q2*SPM2*X2+8*U1M1*T1P2*SPM1*X1-8*U1M1*T1P2*SPM1*X2+
     &    112*U1M1*T1*Q22*SPM2*X1-112*U1M1*T1*Q22*SPM2*X2-64*U1M1*T1
     &    *Q2*SPM1*X1+64*U1M1*T1*Q2*SPM1*X2+44*U1M1*T1*X1-44*U1M1*T1
     &    *X2+64*U1M1*Q22*SPM1*X1-64*U1M1*Q22*SPM1*X2-76*U1M1*Q2*
     &    X1+76*U1M1*Q2*X2-96*T1P2*Q2*SPM3*X1+96*T1P2*Q2*SPM3*X2+32*
     &    T1P2*SPM2*X1-32*T1P2*SPM2*X2+48*T1*Q22*SPM3*X1-48*T1*Q22*
     &    SPM3*X2-224*T1*Q2*SPM2*X1+224*T1*Q2*SPM2*X2+72*T1*SPM1*X1
     &    -72*T1*SPM1*X2+64*T1M1*Q22*SPM1*X1-64*T1M1*Q22*SPM1*X2
     &    -60*T1M1*Q2*X1+60*T1M1*Q2*X2+160*Q22*SPM2*X1-160*Q22*
     &    SPM2*X2-160*Q2*SPM1*X1+160*Q2*SPM1*X2+108*X1-108*X2)
     &    +LOG10*LHM2*(-16*U1*T1*X1+16*U1*T1*X2-16*U1*Q2*X1+16
     &    *U1*Q2*X2+56*U1M1*T1P3*X1-56*U1M1*T1P3*X2-112*U1M1*T1P2*Q2*
     &    X1+112*U1M1*T1P2*Q2*X2+128*U1M1*T1*Q22*X1-128*U1M1*T1*Q22*
     &    X2-40*U1M1*Q23*X1+40*U1M1*Q23*X2+40*T1P2*X1-40*T1P2*X2-
     &    112*T1*Q2*X1+112*T1*Q2*X2-8*T1M1*Q23*X1+8*T1M1*Q23*X2+80*
     &    Q22*X1-80*Q22*X2)
      SPV(36) =
     &  +LOG10*LHM4*(16*U1*T1P3*X1-16*U1*T1P3*X2-16*U1*T1P2*Q2*
     &  X1+16*U1*T1P2*Q2*X2-16*U1*T1*Q22*X1+16*U1*T1*Q22*X2+16*U1*
     &  Q23*X1-16*U1*Q23*X2-24*U1M1*T1P5*X1+24*U1M1*T1P5*X2+56*
     &  U1M1*T1P4*Q2*X1-56*U1M1*T1P4*Q2*X2-56*U1M1*T1P3*Q22*X1+56*
     &  U1M1*T1P3*Q22*X2+40*U1M1*T1P2*Q23*X1-40*U1M1*T1P2*Q23*X2-
     &  16*U1M1*T1*Q24*X1+16*U1M1*T1*Q24*X2-8*T1P4*X1+8*T1P4*X2+
     &  40*T1P3*Q2*X1-40*T1P3*Q2*X2-72*T1P2*Q22*X1+72*T1P2*Q22*X2+
     &  56*T1*Q23*X1-56*T1*Q23*X2-16*Q24*X1+16*Q24*X2)
     &  +LOG10*LHPM2*(32*U1P3*T1M1*X1-32*U1P3*T1M1*X2-100*U1P2
     &  *T1M1*Q2*X1+100*U1P2*T1M1*Q2*X2+44*U1P2*X1-44*U1P2*X2+4*U1*
     &  T1*X1-4*U1*T1*X2+104*U1*T1M1*Q22*X1-104*U1*T1M1*Q22*X2-
     &  124*U1*Q2*X1+124*U1*Q2*X2+4*U1M1*T1*Q22*X1-4*U1M1*T1*Q22*X2
     &  -20*U1M1*Q23*X1+20*U1M1*Q23*X2-8*T1*Q2*X1+8*T1*Q2*X2-36
     &  *T1M1*Q23*X1+36*T1M1*Q23*X2+100*Q22*X1-100*Q22*X2)
      SPV(37) =
     &  +LOG10*(48*U1P3*T1M1*Q2*SPM3*X1-48*U1P3*T1M1*Q2*SPM3*X2
     &  -48*U1P2*T1M1*Q22*SPM3*X1+48*U1P2*T1M1*Q22*SPM3*X2+96*
     &  U1P2*T1M1*Q2*SPM2*X1-96*U1P2*T1M1*Q2*SPM2*X2-8*U1P2*T1M1*
     &  SPM1*X1+8*U1P2*T1M1*SPM1*X2+96*U1P2*Q2*SPM3*X1-96*U1P2*Q2*
     &  SPM3*X2-32*U1P2*SPM2*X1+32*U1P2*SPM2*X2+96*U1*T1*Q2*SPM3*X1
     &  -96*U1*T1*Q2*SPM3*X2-64*U1*T1*SPM2*X1+64*U1*T1*SPM2*X2-112
     &  *U1*T1M1*Q22*SPM2*X1+112*U1*T1M1*Q22*SPM2*X2+64*U1*T1M1*Q2
     &  *SPM1*X1-64*U1*T1M1*Q2*SPM1*X2-40*U1*T1M1*X1+40*U1*T1M1*X2
     &  -48*U1*Q22*SPM3*X1+48*U1*Q22*SPM3*X2+224*U1*Q2*SPM2*X1-
     &  224*U1*Q2*SPM2*X2-72*U1*SPM1*X1+72*U1*SPM1*X2+48*U1M1*T1P3*
     &  Q2*SPM3*X1-48*U1M1*T1P3*Q2*SPM3*X2-48*U1M1*T1P2*Q22*SPM3*X1
     &  +48*U1M1*T1P2*Q22*SPM3*X2+96*U1M1*T1P2*Q2*SPM2*X1-96*U1M1
     &  *T1P2*Q2*SPM2*X2-8*U1M1*T1P2*SPM1*X1+8*U1M1*T1P2*SPM1*X2-
     &  112*U1M1*T1*Q22*SPM2*X1+112*U1M1*T1*Q22*SPM2*X2+64*U1M1*T1
     &  *Q2*SPM1*X1-64*U1M1*T1*Q2*SPM1*X2-44*U1M1*T1*X1+44*U1M1*T1
     &  *X2-64*U1M1*Q22*SPM1*X1+64*U1M1*Q22*SPM1*X2+76*U1M1*Q2*X1)
      SPV(38) = LOG10*(
     &    -76*U1M1*Q2*X2+96*T1P2*Q2*SPM3*X1-96*T1P2*Q2*SPM3*X2-32*
     &    T1P2*SPM2*X1+32*T1P2*SPM2*X2-48*T1*Q22*SPM3*X1+48*T1*Q22*
     &    SPM3*X2+224*T1*Q2*SPM2*X1-224*T1*Q2*SPM2*X2-72*T1*SPM1*X1
     &    +72*T1*SPM1*X2-64*T1M1*Q22*SPM1*X1+64*T1M1*Q22*SPM1*X2
     &    +60*T1M1*Q2*X1-60*T1M1*Q2*X2-160*Q22*SPM2*X1+160*Q22*
     &    SPM2*X2+160*Q2*SPM1*X1-160*Q2*SPM1*X2-108*X1+108*X2)
     &    +LHM1*DLOGQ6T*(-8*U1-56*U1M1*T1P2+72*U1M1*T1*Q2-16*
     &    U1M1*Q22-80*T1+32*Q2)
     &    +LHM1*DLOGQ7T*(-8*U1-56*U1M1*T1P2+72*U1M1*T1*Q2-16*
     &    U1M1*Q22-80*T1+32*Q2)
     &    +LHM1*DLOGQ8T*(8*U1+56*U1M1*T1P2-72*U1M1*T1*Q2+16*
     &    U1M1*Q22+80*T1-32*Q2)
     &    +LHM1*DLOGQ9T*(8*U1+56*U1M1*T1P2-72*U1M1*T1*Q2+16*
     &    U1M1*Q22+80*T1-32*Q2)
     &    +LHM1*DLOGQ10T*(8*U1+56*U1M1*T1P2-72*U1M1*T1*Q2+16*
     &    U1M1*Q22+80*T1-32*Q2)
      SPV(39) =
     &  +LHM1*DLOGQ11T*(8*U1+56*U1M1*T1P2-72*U1M1*T1*Q2+16*
     &  U1M1*Q22+80*T1-32*Q2)
     &  +LHM1*DLOGQ12T*(-8*U1-56*U1M1*T1P2+72*U1M1*T1*Q2-16*
     &  U1M1*Q22-80*T1+32*Q2)
     &  +LHM1*DLOGQ13T*(-16*U1-112*U1M1*T1P2+144*U1M1*T1*Q2-
     &  32*U1M1*Q22-160*T1+64*Q2)
     &  +LHM2*(-8*U1*T1-8*U1*T1M1*Q22+16*U1*Q2-16*U1M1*
     &  T1P4*TM1-16*U1M1*T1P3*TM1*Q2+16*U1M1*T1P3+24*U1M1*T1P2*Q2
     &  -16*U1M1*T1*Q22+8*U1M1*Q23-16*T1P3*TM1-16*T1P2*TM1*Q2
     &  +8*T1P2+40*T1*Q2+8*T1M1*Q23-24*Q22)
     &  +LHM3*DLOGQ6T*(24*U1*T1P2-32*U1*T1*Q2+8*U1*Q22+64*U1M1
     &  *T1P4-176*U1M1*T1P3*Q2+160*U1M1*T1P2*Q22-48*U1M1*T1*Q23+
     &  96*T1P3-192*T1P2*Q2+112*T1*Q22-16*Q23)
     &  +LHM3*DLOGQ7T*(24*U1*T1P2-32*U1*T1*Q2+8*U1*Q22+64*U1M1
     &  *T1P4-176*U1M1*T1P3*Q2+160*U1M1*T1P2*Q22-48*U1M1*T1*Q23+
     &  96*T1P3-192*T1P2*Q2+112*T1*Q22-16*Q23)
      SPV(40) =
     &  +LHM3*DLOGQ8T*(-24*U1*T1P2+32*U1*T1*Q2-8*U1*Q22-64*
     &  U1M1*T1P4+176*U1M1*T1P3*Q2-160*U1M1*T1P2*Q22+48*U1M1*T1*
     &  Q23-96*T1P3+192*T1P2*Q2-112*T1*Q22+16*Q23)
     &  +LHM3*DLOGQ9T*(-24*U1*T1P2+32*U1*T1*Q2-8*U1*Q22-64*
     &  U1M1*T1P4+176*U1M1*T1P3*Q2-160*U1M1*T1P2*Q22+48*U1M1*T1*
     &  Q23-96*T1P3+192*T1P2*Q2-112*T1*Q22+16*Q23)
     &  +LHM3*DLOGQ10T*(-24*U1*T1P2+32*U1*T1*Q2-8*U1*Q22-64*
     &  U1M1*T1P4+176*U1M1*T1P3*Q2-160*U1M1*T1P2*Q22+48*U1M1*T1*
     &  Q23-96*T1P3+192*T1P2*Q2-112*T1*Q22+16*Q23)
     &  +LHM3*DLOGQ11T*(-24*U1*T1P2+32*U1*T1*Q2-8*U1*Q22-64*
     &  U1M1*T1P4+176*U1M1*T1P3*Q2-160*U1M1*T1P2*Q22+48*U1M1*T1*
     &  Q23-96*T1P3+192*T1P2*Q2-112*T1*Q22+16*Q23)
     &  +LHM3*DLOGQ12T*(24*U1*T1P2-32*U1*T1*Q2+8*U1*Q22+64*
     &  U1M1*T1P4-176*U1M1*T1P3*Q2+160*U1M1*T1P2*Q22-48*U1M1*T1*
     &  Q23+96*T1P3-192*T1P2*Q2+112*T1*Q22-16*Q23)
     &  +LHM3*DLOGQ13T*(48*U1*T1P2-64*U1*T1*Q2+16*U1*Q22+128*
     &  U1M1*T1P4-352*U1M1*T1P3*Q2+320*U1M1*T1P2*Q22-96*U1M1*T1*
     &  Q23+192*T1P3-384*T1P2*Q2+224*T1*Q22-32*Q23)
      SPV(41) =
     &  +LHM5*DLOGQ6T*(-16*U1*T1P4+48*U1*T1P3*Q2-48*U1*T1P2*Q22
     &  +16*U1*T1*Q23-16*U1M1*T1P6+64*U1M1*T1P5*Q2-96*U1M1*T1P4*
     &  Q22+64*U1M1*T1P3*Q23-16*U1M1*T1P2*Q24-32*T1P5+112*T1P4*
     &  Q2-144*T1P3*Q22+80*T1P2*Q23-16*T1*Q24)
     &  +LHM5*DLOGQ7T*(-16*U1*T1P4+48*U1*T1P3*Q2-48*U1*T1P2*Q22
     &  +16*U1*T1*Q23-16*U1M1*T1P6+64*U1M1*T1P5*Q2-96*U1M1*T1P4*
     &  Q22+64*U1M1*T1P3*Q23-16*U1M1*T1P2*Q24-32*T1P5+112*T1P4*
     &  Q2-144*T1P3*Q22+80*T1P2*Q23-16*T1*Q24)
     &  +LHM5*DLOGQ8T*(16*U1*T1P4-48*U1*T1P3*Q2+48*U1*T1P2*Q22-
     &  16*U1*T1*Q23+16*U1M1*T1P6-64*U1M1*T1P5*Q2+96*U1M1*T1P4*Q22
     &  -64*U1M1*T1P3*Q23+16*U1M1*T1P2*Q24+32*T1P5-112*T1P4*Q2+
     &  144*T1P3*Q22-80*T1P2*Q23+16*T1*Q24)
     &  +LHM5*DLOGQ9T*(16*U1*T1P4-48*U1*T1P3*Q2+48*U1*T1P2*Q22-
     &  16*U1*T1*Q23+16*U1M1*T1P6-64*U1M1*T1P5*Q2+96*U1M1*T1P4*Q22
     &  -64*U1M1*T1P3*Q23+16*U1M1*T1P2*Q24+32*T1P5-112*T1P4*Q2+
     &  144*T1P3*Q22-80*T1P2*Q23+16*T1*Q24)
      SPV(42) =
     &  +LHM5*DLOGQ10T*(16*U1*T1P4-48*U1*T1P3*Q2+48*U1*T1P2*Q22
     &  -16*U1*T1*Q23+16*U1M1*T1P6-64*U1M1*T1P5*Q2+96*U1M1*T1P4*
     &  Q22-64*U1M1*T1P3*Q23+16*U1M1*T1P2*Q24+32*T1P5-112*T1P4*
     &  Q2+144*T1P3*Q22-80*T1P2*Q23+16*T1*Q24)
     &  +LHM5*DLOGQ11T*(16*U1*T1P4-48*U1*T1P3*Q2+48*U1*T1P2*Q22
     &  -16*U1*T1*Q23+16*U1M1*T1P6-64*U1M1*T1P5*Q2+96*U1M1*T1P4*
     &  Q22-64*U1M1*T1P3*Q23+16*U1M1*T1P2*Q24+32*T1P5-112*T1P4*
     &  Q2+144*T1P3*Q22-80*T1P2*Q23+16*T1*Q24)
     &  +LHM5*DLOGQ12T*(-16*U1*T1P4+48*U1*T1P3*Q2-48*U1*T1P2*
     &  Q22+16*U1*T1*Q23-16*U1M1*T1P6+64*U1M1*T1P5*Q2-96*U1M1*
     &  T1P4*Q22+64*U1M1*T1P3*Q23-16*U1M1*T1P2*Q24-32*T1P5+112*
     &  T1P4*Q2-144*T1P3*Q22+80*T1P2*Q23-16*T1*Q24)
     &  +LHM5*DLOGQ13T*(-32*U1*T1P4+96*U1*T1P3*Q2-96*U1*T1P2*
     &  Q22+32*U1*T1*Q23-32*U1M1*T1P6+128*U1M1*T1P5*Q2-192*U1M1*
     &  T1P4*Q22+128*U1M1*T1P3*Q23-32*U1M1*T1P2*Q24-64*T1P5+224*
     &  T1P4*Q2-288*T1P3*Q22+160*T1P2*Q23-32*T1*Q24)
     &  +LHPM1*DLOGQ6U*(-48*U1P2*T1M1+60*U1*T1M1*Q2-76*U1-4*
     &  T1-16*T1M1*Q22+36*Q2)
      SPV(43) =
     &  +LHPM1*DLOGQ7U*(-48*U1P2*T1M1+60*U1*T1M1*Q2-76*U1-4*
     &  T1-16*T1M1*Q22+36*Q2)
     &  +LHPM1*DLOGQ8U*(48*U1P2*T1M1-60*U1*T1M1*Q2+76*U1+4*T1
     &  +16*T1M1*Q22-36*Q2)
     &  +LHPM1*DLOGQ9U*(48*U1P2*T1M1-60*U1*T1M1*Q2+76*U1+4*T1
     &  +16*T1M1*Q22-36*Q2)
     &  +LHPM1*DLOGQ10U*(48*U1P2*T1M1-60*U1*T1M1*Q2+76*U1+4*T1
     &  +16*T1M1*Q22-36*Q2)
     &  +LHPM1*DLOGQ11U*(48*U1P2*T1M1-60*U1*T1M1*Q2+76*U1+4*T1
     &  +16*T1M1*Q22-36*Q2)
     &  +LHPM1*DLOGQ12U*(-48*U1P2*T1M1+60*U1*T1M1*Q2-76*U1-4
     &  *T1-16*T1M1*Q22+36*Q2)
     &  +LHPM1*DLOGQ13U*(-96*U1P2*T1M1+120*U1*T1M1*Q2-152*U1
     &  -8*T1-32*T1M1*Q22+72*Q2)
     &  +LHPM3*DLOGQ6U*(40*U1P4*T1M1-116*U1P3*T1M1*Q2+60*U1P3+
     &  4*U1P2*T1+112*U1P2*T1M1*Q22-140*U1P2*Q2-8*U1*T1*Q2-36*U1*
     &  T1M1*Q23+100*U1*Q22+4*T1*Q22-20*Q23)
      SPV(44) =
     &  +LHPM3*DLOGQ7U*(40*U1P4*T1M1-116*U1P3*T1M1*Q2+60*U1P3+
     &  4*U1P2*T1+112*U1P2*T1M1*Q22-140*U1P2*Q2-8*U1*T1*Q2-36*U1*
     &  T1M1*Q23+100*U1*Q22+4*T1*Q22-20*Q23)
     &  +LHPM3*DLOGQ8U*(-40*U1P4*T1M1+116*U1P3*T1M1*Q2-60*U1P3
     &  -4*U1P2*T1-112*U1P2*T1M1*Q22+140*U1P2*Q2+8*U1*T1*Q2+36*U1
     &  *T1M1*Q23-100*U1*Q22-4*T1*Q22+20*Q23)
     &  +LHPM3*DLOGQ9U*(-40*U1P4*T1M1+116*U1P3*T1M1*Q2-60*U1P3
     &  -4*U1P2*T1-112*U1P2*T1M1*Q22+140*U1P2*Q2+8*U1*T1*Q2+36*U1
     &  *T1M1*Q23-100*U1*Q22-4*T1*Q22+20*Q23)
     &  +LHPM3*DLOGQ10U*(-40*U1P4*T1M1+116*U1P3*T1M1*Q2-60*
     &  U1P3-4*U1P2*T1-112*U1P2*T1M1*Q22+140*U1P2*Q2+8*U1*T1*Q2+
     &  36*U1*T1M1*Q23-100*U1*Q22-4*T1*Q22+20*Q23)
     &  +LHPM3*DLOGQ11U*(-40*U1P4*T1M1+116*U1P3*T1M1*Q2-60*
     &  U1P3-4*U1P2*T1-112*U1P2*T1M1*Q22+140*U1P2*Q2+8*U1*T1*Q2+
     &  36*U1*T1M1*Q23-100*U1*Q22-4*T1*Q22+20*Q23)
     &  +LHPM3*DLOGQ12U*(40*U1P4*T1M1-116*U1P3*T1M1*Q2+60*U1P3
     &  +4*U1P2*T1+112*U1P2*T1M1*Q22-140*U1P2*Q2-8*U1*T1*Q2-36*U1
     &  *T1M1*Q23+100*U1*Q22+4*T1*Q22-20*Q23)
      SPV(45) =
     &  +LHPM3*DLOGQ13U*(80*U1P4*T1M1-232*U1P3*T1M1*Q2+120*U1P3
     &  +8*U1P2*T1+224*U1P2*T1M1*Q22-280*U1P2*Q2-16*U1*T1*Q2-72*
     &  U1*T1M1*Q23+200*U1*Q22+8*T1*Q22-40*Q23)
     &  +DLOG6*(16*BQED)
     &  +DLOG5*(-16*BQED)
     &  +LOG7X2*(-8*U1P4*T1M1*SPM3+16*U1P3*T1M1*Q2*SPM3-24*
     &  U1P3*T1M1*SPM2-24*U1P3*SPM3-32*U1P2*T1*SPM3-8*U1P2*T1M1*
     &  Q22*SPM3+48*U1P2*T1M1*Q2*SPM2-28*U1P2*T1M1*SPM1+32*U1P2*
     &  Q2*SPM3-64*U1P2*SPM2-32*U1*T1P2*SPM3+32*U1*T1*Q2*SPM3-80*
     &  U1*T1*SPM2-24*U1*T1M1*Q22*SPM2+56*U1*T1M1*Q2*SPM1-8*U1*
     &  Q22*SPM3+96*U1*Q2*SPM2-60*U1*SPM1-8*U1M1*T1P4*SPM3+16*
     &  U1M1*T1P3*Q2*SPM3-24*U1M1*T1P3*SPM2-8*U1M1*T1P2*Q22*SPM3
     &  +48*U1M1*T1P2*Q2*SPM2-28*U1M1*T1P2*SPM1-24*U1M1*T1*Q22*
     &  SPM2+56*U1M1*T1*Q2*SPM1-32*U1M1*Q22*SPM1-24*T1P3*SPM3+
     &  32*T1P2*Q2*SPM3-64*T1P2*SPM2-8*T1*Q22*SPM3+96*T1*Q2*SPM2
     &  -60*T1*SPM1-32*T1M1*Q22*SPM1-32*Q22*SPM2+96*Q2*SPM1)
     &  +DLOG7*(-16*U1*T1M1-16*U1M1*T1-32*TB*Q22+
     &  32*U1M1*Q2+32*T1M1*Q2)
      SPV(46) =
     &  +DLOG8*(-16*U1*T1M1-16*U1M1*T1-32*TB*Q22+
     &  32*U1M1*Q2+32*T1M1*Q2)
     &  +(-120-32*U1P3*T1M1*SPM2+16*U1P2*T1M1*UM1+48*U1P2
     &  *T1M1*Q2*SPM2-80*U1P2*T1M1*SPM1-64*U1P2*SPM2-64*U1*T1*
     &  SPM2+112*U1*T1M1*Q2*SPM1-56*U1*T1M1+16*U1*UM1+48*U1*Q2*
     &  SPM2-176*U1*SPM1-32*U1M1*T1P3*SPM2+16*U1M1*T1P2*TM1+48*
     &  U1M1*T1P2*Q2*SPM2-80*U1M1*T1P2*SPM1-16*U1M1*T1*TM1*Q2+112
     &  *U1M1*T1*Q2*SPM1-64*U1M1*T1+88*U1M1*Q2-64*T1P2*SPM2+16*
     &  T1*TM1+48*T1*Q2*SPM2-176*T1*SPM1+88*T1M1*Q2-16*TM1*Q2+
     &  160*Q2*SPM1+32*BQED*LOGDEL2)
CBH HERE (ABOVE) I REMOVE THE LOGMU DEPENDENCE BY HAND
CBH     &    160*Q2*SPM1+32*BQED*LOGDEL2-32*BQED*LOGDEL*LOGMU)
C SUM CONTRIBUTIONS AND MULTIPLY BY COMMON FACTOR:
      SPLUSV = 0.D0
      DO 10 I = 1,46
C           WRITE(6,1000) I,SPV(I)
   10 SPLUSV = SPLUSV + SPV(I)
C
C DIVIDE BY 8 IN ORDER TO GET THE NORMALIZATION CORRECT.
C THE - IN THE DEFIN. CANCELS THE - FROM THE GL. POL.
CBH        VOKGAM2 = SVCACF/8.0D0
C
 1000 FORMAT('SPV(',I3,')  =  ',D20.10)
CBH SUBTRACT OFF THE OLD SOFT FINITE PIECES
      SPLUSV = SPLUSV - (
     &  SQM * (  - 64*M2*LOGDEL*LOG1 - 32*M2*ZETA2 + 64*M2*LOG1*LOG5
     &  + 64*M2*LOG1*LOG6 - 32*M2*LOG1X2 + 64*M2*DLOG2 + 64*M2*DLOG1 )
     &  + XSQM1 * ( 32*LOGDEL*LOG1 + 16*ZETA2 - 32*LOG1*LOG5
     &  - 32*LOG1*LOG6 + 16*LOG1X2 - 32*DLOG2 - 32*DLOG1 )
     &  - 16*LOG4*LOG3 - 32*LOG4*LOGDEL + 16*LOG4*LOG1 + 8*LOG4X2
     &  + 32*LOG3*LOGDEL - 16*LOG3*LOG1 + 8*LOG3X2 + 32*LOGDEL2
     &  - 24*ZETA2 - 8*LOG1X2 + 16*DLOG6 - 16*DLOG5 )*BQED
CBH ADD ON THE NEW SOFT FINITE PIECES
      SPLUSV = SPLUSV + (
     &  SQM * ( - 64*M2*LI2B - 128*M2*LNB*LOG1 + 32*M2*LOG1*LOG2
     &  - 64*M2*LOG1*LOGSP - 16*M2*LOG1X2 ) + XSQM1 * ( 32*LI2B
     &  + 64*LNB*LOG1 - 16*LOG1*LOG2 + 32*LOG1*LOGSP + 8*LOG1X2 )
     &  + 16*LIT1 - 16*LIT2 + 16*LIU1 - 16*LIU2 + 64*LNB*LOG3
     &  + 64*LNB*LOG4 + 128*LNBX2 - 8*LOG1X2 - 16*LOG2*LOG3 - 24*ZETA2
     &  - 16*LOG2*LOG4 + 32*LOG2*LOGSP - 8*LOG2X2 + 32*LOG3*LOGSP
     &  + 32*LOG4*LOGSP - 32*LOGSPX2 + 8*LNBTX2 + 8*LNBUX2 )*BQED
CBH SWITCH Q2 BACK TO POSITIVE
      Q2 = QTMP
CBH GET THE NORMALIZATION CORRECT
      VOKG2 = SPLUSV
      RETURN
      END
CBH      DOUBLE PRECISION FUNCTION VOKL2(SP,T1,U1,M2,Q2,DEL,S4MAX,S4,MU)
      DOUBLE PRECISION FUNCTION VOKL2(T1,SP,M2,Q2,RHOTILDE)
C
C HERE WE COMPUTE THE EXPRESSION FOR THE CA*CF PART OF THE
C SOFT PLUS VIRTUAL MATRIX ELEMENT.
C
      IMPLICIT DOUBLE PRECISION (A-Z)
      INTEGER I
      DIMENSION VPS(40)
      PARAMETER( PI = 3.14159265359D0 )
      DATA ZETA2/1.644934066848226D+00/
C
CSR      LOGDEL = DLOG(DEL/M2)
CSR      LOGDEL2 = LOGDEL*LOGDEL
CSR HERE WE REPLACE THE LOGDEL TERMS BY INTEGRALS OVER S4
CBH OH NO WE DON'T
CBH        DIST = S4MAX - DEL
CBH        L11 = DLOG(S4/M2)
CBH        L12 = DLOG(S4MAX/M2)
CBH        LOGDEL = L12 - DIST/S4
CBH        LOGDEL2 = L12*L12 -2.0D0*DIST*L11/S4
CBH
CBH WE REPLACE LOG(DEL/M2) = ARBITRARY
CBH SINCE WE SUBTRACT IT OFF LATER ANYHOW
      LOGDEL = -0.1D0
      LOGDEL2 = LOGDEL*LOGDEL
CBH NOW THE NEW SOFT PARAMETER
      LNB = 0.5D0*DLOG(1.D0-RHOTILDE)
      LNBX2 = LNB*LNB
CBH THE Q2 COMING INTO THE ROUTINE IS POSITIVE
CBH BUT IN THIS ROUTINE THE Q2 SHOULD BE NEGATIVE
CBH SO WE CHANGE THE SIGN HERE
      QTMP = Q2
      Q2 = -QTMP
CBH
      S = SP + Q2
      U1 = -SP-T1
c      LOGDEL=2.D0*LNB+DLOG(-U1/M2)
c      LOGDEL2=LOGDEL*LOGDEL
CBH I HAVE REMOVED ALL OF THE MU DEPENDENCE BY HAND.  SEE BELOW
CSR      MU2 = M2
CBH      MU2 = MU*MU
CBH      CEP = 1.D0/16.D0/PI/PI
      S1 = 4.0D0*M2 -S
      S1M1 = 1.D0/S1
      T = T1+M2
      U = U1+M2
      XSQ = DSQRT(1.0D0 - 4.0D0*M2/S)
      YSQ = DSQRT(1.0D0 - 4.0D0*M2/Q2)
      X = (1.D0 - XSQ)/(1.D0 + XSQ)
      SQ = S*XSQ
      SQM = 1.D0/SQ
      Y = (1.D0-YSQ)/(1.D0+YSQ)
      X1 = (1.D0+YSQ)/2.D0
      X2 = (1.D0-YSQ)/2.D0
      AA = DSQRT(4.D0*M2 -Q2)
      AA2 = 4.D0*M2 -Q2
      BB = DSQRT(-Q2)
      CC = DSQRT(4.D0*M2*Q2/S - Q2)
      LAT = T*T + M2*M2 + Q2*Q2 - 2.D0*T*M2 - 2.D0*T*Q2 - 2*M2*Q2
      LAU = U*U + M2*M2 + Q2*Q2 - 2.D0*U*M2 - 2.D0*U*Q2 - 2*M2*Q2
      LH = DSQRT(LAT)
      LHP = DSQRT(LAU)
      LOG1 = DLOG(X)
      LOG2 = DLOG(S/M2)
CBH
      LOG1X2 = LOG1*LOG1
      LOG2X2 = LOG2*LOG2
      LOGSP = DLOG(SP/M2)
      LOGSPX2 = LOGSP*LOGSP
CBH
      LOG3 = DLOG(-T1/M2)
      LOG3X2 = LOG3*LOG3
      LOG4 = DLOG(-U1/M2)
      LOG4X2 = LOG4*LOG4
      LOG5 = DLOG(1.D0-X)
      LOG6 = DLOG(1.D0+X)
      LOG7 = DLOG(-Y)
      LOG7X2 = LOG7*LOG7
      LOG8 = DLOG(-Q2/S)
      LOG9 = DLOG(X1)
      LOG10 = DLOG(-X2)
CBH      LOGMU = DLOG(MU2/M2)
      LOGQ1 = DLOG((AA+CC)*(AA+CC)/4.D0/M2)
      LOGQ2 = DLOG((AA-BB)/(AA+BB))
      LOGQ3 = DLOG((AA-CC)/(AA-BB))
      LOGQ3X2 = LOGQ3*LOGQ3
      DLOG1 = DILOG(-X)
      DLOG2 = DILOG(X)
      DLOG3 = DILOG(T1/M2 + 1.D0)
      DLOG4 = DILOG(U1/M2 + 1.D0)
      DLOG5 = DILOG(1.D0-U1/X/T1)
      DLOG6 = DILOG(1.D0-T1/X/U1)
      DLOG7 = DILOG(Q2*X1/M2)
      DLOG8 = DILOG(Q2*X2/M2)
      DLOGQ1 = DILOG((AA-BB)/(AA-CC))
      DLOGQ2 = DILOG((AA-CC)/(AA+BB))
      DLOGQ3 = DILOG((BB+CC)/(AA+CC))
      DLOGQ4 = DILOG((CC-BB)/(AA+CC))
      DLOGQ5 = DILOG(S/SP)
      DLOGQ6T = DILOG((T1+AA2+LH)/(T1-YSQ*(LH+Q2*YSQ)))
      DLOGQ6U = DILOG((U1+AA2+LHP)/(U1-YSQ*(LHP+Q2*YSQ)))
      DLOGQ7T = DILOG((T1+AA2+LH)/(T1+YSQ*(LH-Q2*YSQ)))
      DLOGQ7U = DILOG((U1+AA2+LHP)/(U1+YSQ*(LHP-Q2*YSQ)))
      DLOGQ8T = DILOG((T1+AA2-LH)/(T1-YSQ*(LH+Q2*YSQ)))
      DLOGQ8U = DILOG((U1+AA2-LHP)/(U1-YSQ*(LHP+Q2*YSQ)))
      DLOGQ9T = DILOG((T1+AA2-LH)/(T1+YSQ*(LH-Q2*YSQ)))
      DLOGQ9U = DILOG((U1+AA2-LHP)/(U1+YSQ*(LHP-Q2*YSQ)))
      DLOGQ10T = DILOG( (T1*(Q2 - T - M2 - LH) - 2.D0*M2*LH)/
     &     (T1*(Q2 - T - M2 + LH)))
      DLOGQ10U = DILOG( (U1*(Q2 - U - M2 - LHP) - 2.D0*M2*LHP)/
     &     (U1*(Q2 - U - M2 + LHP)))
      DLOGQ11T = DILOG( (T1*(Q2 - T - M2 - LH) - 2.D0*M2*LH)/
     &     (T1*(Q2 - T - M2 - LH)))
      DLOGQ11U = DILOG( (U1*(Q2 - U - M2 - LHP) - 2.D0*M2*LHP)/
     &     (U1*(Q2 - U - M2 - LHP)))
      DLOGQ12T = DILOG( (Q2 - T - M2 + LH)/(Q2 - T - M2 - LH))
      DLOGQ12U = DILOG( (Q2 - U - M2 + LHP)/(Q2 - U - M2 - LHP))
      DLOGQ13T = DILOG( (M2 - T - LH)/(M2 - T))
      DLOGQ13U = DILOG( (M2 - U - LHP)/(M2 - U))
C MORE USEFUL DEFINITIONS:
CBH      CFCA = 4.D0
      M22 = M2*M2
      M23 = M2*M22
      T1P2 = T1*T1
      T1P3 = T1*T1P2
      T1P4 = T1*T1P3
      T1P5 = T1*T1P4
      T1P6 = T1*T1P5
      T1M1 = 1.D0/T1
      T1M2 = T1M1*T1M1
      T1M3 = T1M2*T1M1
      U1P2 = U1*U1
      U1P3 = U1*U1P2
      U1P4 = U1*U1P3
      U1P5 = U1*U1P4
      U1P6 = U1*U1P5
      U1M1 = 1.D0/U1
      U1M2 = U1M1*U1M1
      U1M3 = U1M1*U1M2
      UM1 = 1.D0/U
      UM2 = UM1*UM1
      TM1 = 1.D0/T
      TM2 = TM1*TM1
      Q22 = Q2*Q2
      Q23 = Q2*Q22
      Q24 = Q22*Q22
      TB = T1M1*U1M1
      SM1 = 1.D0/S
      SM2 = SM1*SM1
      SQM1 = 1.D0/SQ
      SPM1 = 1.D0/SP
      SPM2 = SPM1*SPM1
      SPM3 = SPM1*SPM2
      SPM4 = SPM2*SPM2
      LHM1 = 1.D0/LH
      LHM2 = LHM1*LHM1
      LHM3 = LHM1*LHM2
      LHM4 = LHM2*LHM2
      LHM5 = LHM2*LHM3
      LHPM1 = 1.D0/LHP
      LHPM2 = LHPM1*LHPM1
      LHPM3 = LHPM1*LHPM2
      LHPM4 = LHPM2*LHPM2
      LHPM5 = LHPM2*LHPM3
      XSQM1 = 1.D0/XSQ
CBH      LOG1X2 = LOG1*LOG1
CBH
      ONEMBETA = 1.D0 - XSQ
      ONEMBETAM1 = 1.D0/ONEMBETA
      ONEPBETA = 1.D0 + XSQ
      ONEPBETAM1 = 1.D0/ONEPBETA
CBH
      LI2B = DILOG(2.D0*XSQ*ONEPBETAM1)
      LIT1 = DILOG(1.D0+2.D0*T1*SPM1*ONEMBETAM1)
      LIU1 = DILOG(1.D0+2.D0*U1*SPM1*ONEMBETAM1)
      LIT2 = DILOG(1.D0+0.5D0*SP*ONEPBETA*T1M1)
      LIU2 = DILOG(1.D0+0.5D0*SP*ONEPBETA*U1M1)
      LNBT = DLOG(-0.5D0*SP*T1M1*ONEMBETA)
      LNBTX2 = LNBT*LNBT
      LNBU = DLOG(-0.5D0*SP*U1M1*ONEMBETA)
      LNBUX2 = LNBU*LNBU
c      WRITE(*,*) 'LI2B = ',LI2B
c      WRITE(*,*) 'LIT1 = ',LIT1
c      WRITE(*,*) 'LIU1 = ',LIU1
c      WRITE(*,*) 'LIT2 = ',LIT2
c      WRITE(*,*) 'LIU2 = ',LIU2
c      WRITE(*,*) 'LNBT = ',LNBT
c      WRITE(*,*) 'LNBU = ',LNBU
CBH
      BQED = -S + M2*SP*SP*T1M1*U1M1
      MQED =2*M22*U1*T1M2 + 2*M22*T1M1 - M2*T1M1*S
     &  + 2*M22*T1*U1M2 + 2*M22*U1M1 - M2*U1M1*S
C
C HERE IS THE MATRIX ELEMENT.
C
      VPS(1) =
     &  +M22*LOG1*LOG5*SQM*(128+64*U1*T1M1+64*U1M1*T1)
     &  +M22*LOG1*LOG6*SQM*(-128-64*U1*T1M1-64*U1M1*T1)
     &  +M22*LOG1*LOG3*SQM*(64+32*U1*T1M1+32*U1M1*T1)
     &  +M22*LOG1*LOG4*SQM*(64+32*U1*T1M1+32*U1M1*T1)
     &  +M22*LOG1*SQM*LOGQ1*(-64-32*U1*T1M1-32*U1M1*T1)
     &  +M22*LOG1*SQM*(32*U1*T1M1*Q2*S1M1-64*U1*S1M1+32*
     &  U1M1*T1*Q2*S1M1-64*T1*S1M1+64*Q2*S1M1)
     &  +M22*LOG3*LHM2*(-16*U1*TM1*Q2-16*U1M1*T1P2*TM1*Q2-
     &  32*T1*TM1*Q2)
     &  +M22*LOG3*LHM4*(64*U1*T1P2*TM1*Q2-32*U1*T1*TM1*Q22-48
     &  *U1M1*T1P3*TM1*Q22+96*T1P3*TM1*Q2-80*T1P2*TM1*Q22)
     &  +M22*LOG4*LHPM2*(-16*U1P2*T1M1*UM1*Q2-32*U1*UM1*Q2-
     &  16*T1*UM1*Q2)
     &  +M22*DLOG2*SQM*(128+64*U1*T1M1+64*U1M1*T1)
     &  +M22*DLOG1*SQM*(-128-64*U1*T1M1-64*U1M1*T1)
     &  +M22*ZETA2*SQM*(448+224*U1*T1M1+224*U1M1*T1)
     &  +M22*ZETA2*LHM1*(-16*U1*T1M1+16*U1M1*T1)
      VPS(2) =
     &  +M22*ZETA2*LHM3*(-16*U1*Q2-16*U1M1*T1P2*Q2-32*T1*Q2
     &  )
     &  +M22*ZETA2*LHM5*(64*U1*T1P2*Q2-32*U1*T1*Q22-48*U1M1*
     &  T1P3*Q22+96*T1P3*Q2-80*T1P2*Q22)
     &  +M22*ZETA2*LHPM1*(16*U1*T1M1-16*U1M1*T1)
     &  +M22*ZETA2*LHPM3*(-32*U1P2*T1M1*Q2-32*U1*Q2)
     &  +M22*SQM*LOG8*LOGQ2*(-64-32*U1*T1M1-32*U1M1*T1)
     &  +M22*SQM*DLOGQ1*(-128-64*U1*T1M1-64*U1M1*T1)
     &  +M22*SQM*DLOGQ2*(-128-64*U1*T1M1-64*U1M1*T1)
     &  +M22*SQM*DLOGQ3*(-128-64*U1*T1M1-64*U1M1*T1)
     &  +M22*SQM*DLOGQ4*(128+64*U1*T1M1+64*U1M1*T1)
     &  +M22*SQM*LOGQ3X2*(-64-32*U1*T1M1-32*U1M1*T1)
     &  +M22*LOG9*LHPM2*(-16*U1*T1M1*Q2*X1+16*U1*T1M1*Q2*X2
     &  +16*U1M1*T1*Q2*X1-16*U1M1*T1*Q2*X2)
     &  +M22*LOG10*LHPM2*(16*U1*T1M1*Q2*X1-16*U1*T1M1*Q2*X2-
     &  16*U1M1*T1*Q2*X1+16*U1M1*T1*Q2*X2)
     &  +M22*LHM1*DLOGQ6T*(16*U1*T1M1-16*U1M1*T1)
      VPS(3) =
     &  +M22*LHM1*DLOGQ7T*(16*U1*T1M1-16*U1M1*T1)
     &  +M22*LHM1*DLOGQ8T*(-16*U1*T1M1+16*U1M1*T1)
     &  +M22*LHM1*DLOGQ9T*(-16*U1*T1M1+16*U1M1*T1)
     &  +M22*LHM1*DLOGQ10T*(-16*U1*T1M1+16*U1M1*T1)
     &  +M22*LHM1*DLOGQ11T*(-16*U1*T1M1+16*U1M1*T1)
     &  +M22*LHM1*DLOGQ12T*(16*U1*T1M1-16*U1M1*T1)
     &  +M22*LHM1*DLOGQ13T*(32*U1*T1M1-32*U1M1*T1)
     &  +M22*LHM3*DLOGQ6T*(16*U1*Q2+16*U1M1*T1P2*Q2+32*T1*Q2)
     &  +M22*LHM3*DLOGQ7T*(16*U1*Q2+16*U1M1*T1P2*Q2+32*T1*Q2)
     &  +M22*LHM3*DLOGQ8T*(-16*U1*Q2-16*U1M1*T1P2*Q2-32*T1*Q2
     &  )
     &  +M22*LHM3*DLOGQ9T*(-16*U1*Q2-16*U1M1*T1P2*Q2-32*T1*Q2
     &  )
     &  +M22*LHM3*DLOGQ10T*(-16*U1*Q2-16*U1M1*T1P2*Q2-32*T1*Q2
     &  )
     &  +M22*LHM3*DLOGQ11T*(-16*U1*Q2-16*U1M1*T1P2*Q2-32*T1*Q2
     &  )
      VPS(4) =
     &  +M22*LHM3*DLOGQ12T*(16*U1*Q2+16*U1M1*T1P2*Q2+32*T1*Q2)
     &  +M22*LHM3*DLOGQ13T*(32*U1*Q2+32*U1M1*T1P2*Q2+64*T1*Q2)
     &  +M22*LHM5*DLOGQ6T*(-64*U1*T1P2*Q2+32*U1*T1*Q22+48*
     &  U1M1*T1P3*Q22-96*T1P3*Q2+80*T1P2*Q22)
     &  +M22*LHM5*DLOGQ7T*(-64*U1*T1P2*Q2+32*U1*T1*Q22+48*
     &  U1M1*T1P3*Q22-96*T1P3*Q2+80*T1P2*Q22)
     &  +M22*LHM5*DLOGQ8T*(64*U1*T1P2*Q2-32*U1*T1*Q22-48*U1M1*
     &  T1P3*Q22+96*T1P3*Q2-80*T1P2*Q22)
     &  +M22*LHM5*DLOGQ9T*(64*U1*T1P2*Q2-32*U1*T1*Q22-48*U1M1*
     &  T1P3*Q22+96*T1P3*Q2-80*T1P2*Q22)
     &  +M22*LHM5*DLOGQ10T*(64*U1*T1P2*Q2-32*U1*T1*Q22-48*U1M1*
     &  T1P3*Q22+96*T1P3*Q2-80*T1P2*Q22)
     &  +M22*LHM5*DLOGQ11T*(64*U1*T1P2*Q2-32*U1*T1*Q22-48*U1M1*
     &  T1P3*Q22+96*T1P3*Q2-80*T1P2*Q22)
     &  +M22*LHM5*DLOGQ12T*(-64*U1*T1P2*Q2+32*U1*T1*Q22+48*
     &  U1M1*T1P3*Q22-96*T1P3*Q2+80*T1P2*Q22)
     &  +M22*LHM5*DLOGQ13T*(-128*U1*T1P2*Q2+64*U1*T1*Q22+96*
     &  U1M1*T1P3*Q22-192*T1P3*Q2+160*T1P2*Q22)
      VPS(5) =
     &  +M22*LHPM1*DLOGQ6U*(-16*U1*T1M1+16*U1M1*T1)
     &  +M22*LHPM1*DLOGQ7U*(-16*U1*T1M1+16*U1M1*T1)
     &  +M22*LHPM1*DLOGQ8U*(16*U1*T1M1-16*U1M1*T1)
     &  +M22*LHPM1*DLOGQ9U*(16*U1*T1M1-16*U1M1*T1)
     &  +M22*LHPM1*DLOGQ10U*(16*U1*T1M1-16*U1M1*T1)
     &  +M22*LHPM1*DLOGQ11U*(16*U1*T1M1-16*U1M1*T1)
     &  +M22*LHPM1*DLOGQ12U*(-16*U1*T1M1+16*U1M1*T1)
     &  +M22*LHPM1*DLOGQ13U*(-32*U1*T1M1+32*U1M1*T1)
     &  +M22*LHPM3*DLOGQ6U*(32*U1P2*T1M1*Q2+32*U1*Q2)
     &  +M22*LHPM3*DLOGQ7U*(32*U1P2*T1M1*Q2+32*U1*Q2)
     &  +M22*LHPM3*DLOGQ8U*(-32*U1P2*T1M1*Q2-32*U1*Q2)
     &  +M22*LHPM3*DLOGQ9U*(-32*U1P2*T1M1*Q2-32*U1*Q2)
     &  +M22*LHPM3*DLOGQ10U*(-32*U1P2*T1M1*Q2-32*U1*Q2)
     &  +M22*LHPM3*DLOGQ11U*(-32*U1P2*T1M1*Q2-32*U1*Q2)
     &  +M22*LHPM3*DLOGQ12U*(32*U1P2*T1M1*Q2+32*U1*Q2)
     &  +M22*LHPM3*DLOGQ13U*(64*U1P2*T1M1*Q2+64*U1*Q2)
     &  +M2*LOG1X2*SQM*(-16*U1-16*T1+16*Q2-32*BQED)
      VPS(6) =
     &  +M2*LOG1X2*(4*U1P2*T1M1*SPM1+12*U1*SPM1+4*U1M1*T1P2*
     &  SPM1+12*T1*SPM1)
     &  +M2*LOG1*LOG5*SQM*(32*U1P2*T1M1-32*U1*T1M1*Q2+160*U1
     &  +32*U1M1*T1P2-32*U1M1*T1*Q2+160*T1-128*Q2+64*BQED)
     &  +M2*LOG1*LOG6*SQM*(-32*U1P2*T1M1+32*U1*T1M1*Q2-96*
     &  U1-32*U1M1*T1P2+32*U1M1*T1*Q2-96*T1+64*Q2+64*BQED)
     &  +M2*LOG1*LOG3*SQM*(16*U1P2*T1M1-16*U1*T1M1*Q2+48*U1
     &  +16*U1M1*T1P2-16*U1M1*T1*Q2+48*T1-32*Q2)
     &  +M2*LOG1*LOG4*SQM*(16*U1P2*T1M1-16*U1*T1M1*Q2+48*U1
     &  +16*U1M1*T1P2-16*U1M1*T1*Q2+48*T1-32*Q2)
     &  +M2*LOG1*SQM*LOGQ1*(-16*U1P2*T1M1+16*U1*T1M1*Q2-48*
     &  U1-16*U1M1*T1P2+16*U1M1*T1*Q2-48*T1+32*Q2)
      VPS(7) =
     &  +M2*LOG1*SQM*(16*U1P3*T1M1*S1M1-16*U1P3*T1M1*SPM1-
     &  16*U1P2*T1M1*Q2*S1M1+16*U1P2*T1M1*Q2*SPM1-32*U1P2*T1M1+64*
     &  U1P2*Q2*SPM2-32*U1P2*S1M1+128*U1*T1*Q2*SPM2-96*U1*T1*S1M1
     &  +32*U1*T1*SPM1+24*U1*T1M1*Q2+112*U1*Q2*S1M1+48*U1*Q2*SPM1
     &  -16*U1+16*U1M1*T1P3*S1M1-16*U1M1*T1P3*SPM1-16*U1M1*T1P2*
     &  Q2*S1M1+16*U1M1*T1P2*Q2*SPM1-32*U1M1*T1P2+24*U1M1*T1*Q2+
     &  64*T1P2*Q2*SPM2-32*T1P2*S1M1+112*T1*Q2*S1M1+48*T1*Q2*SPM1
     &  -16*T1-64*Q22*S1M1-16*Q2-64*BQED*LOGDEL)
     &  +M2*LOG3X2*(-16)
     &  +M2*LOG3*LOG4*(-32-32*U1*T1M1-32*U1M1*T1)
     &  +M2*LOG3*LHM2*(4*U1P2*T1P2*TM2-4*U1P2*T1*TM2*Q2+24*U1*
     &  T1P2*TM1-32*U1*T1*TM1*Q2+8*U1M1*T1P4*TM1-4*U1M1*T1P4*TM2*
     &  Q2-36*U1M1*T1P3*TM1*Q2-4*U1M1*T1P3*TM2*Q22+16*U1M1*T1P2*
     &  TM1*Q22+4*T1P4*TM2+40*T1P3*TM1+8*T1P3*TM2*Q2-68*T1P2*
     &  TM1*Q2-4*T1P2*TM2*Q22+16*T1*TM1*Q22)
      VPS(8) =
     &  +M2*LOG3*LHM4*(16*U1P2*T1P2*TM1*Q2-16*U1P2*T1*TM1*Q22-
     &  16*U1*T1P4*TM1+104*U1*T1P3*TM1*Q2-64*U1*T1P2*TM1*Q22+8*U1*
     &  T1*TM1*Q23+12*U1M1*T1P5*TM1*Q2-64*U1M1*T1P4*TM1*Q22+20*
     &  U1M1*T1P3*TM1*Q23-24*T1P5*TM1+132*T1P4*TM1*Q2-136*T1P3*
     &  TM1*Q22+28*T1P2*TM1*Q23)
     &  +M2*LOG3*(4*U1*T1*TM2-4*U1M1*T1P3*TM2)
     &  +M2*LOG4X2*(-16)
     &  +M2*LOG4*LHPM2*(8*U1P4*T1M1*UM1-24*U1P3*T1M1*UM1*Q2+
     &  16*U1P3*UM1+8*U1P2*T1*UM1+16*U1P2*T1M1*UM1*Q22-48*U1P2*
     &  UM1*Q2-24*U1*T1*UM1*Q2+16*U1*UM1*Q22)
     &  +M2*LOG4*(-8*U1P3*T1M1*UM2)
     &  +M2*DLOG2*SQM*(32*U1P2*T1M1-32*U1*T1M1*Q2+160*U1+32
     &  *U1M1*T1P2-32*U1M1*T1*Q2+160*T1-128*Q2+64*BQED)
     &  +M2*DLOG3*(-8+8*U1M1*T1)
     &  +M2*DLOG4*(-8+8*U1*T1M1)
     &  +M2*DLOG1*SQM*(-32*U1P2*T1M1+32*U1*T1M1*Q2-96*U1
     &  -32*U1M1*T1P2+32*U1M1*T1*Q2-96*T1+64*Q2+64*BQED)
      VPS(9) =
     &  +M2*ZETA2*SQM*(112*U1P2*T1M1-112*U1*T1M1*Q2+464*U1
     &  +112*U1M1*T1P2-112*U1M1*T1*Q2+464*T1-352*Q2-32*BQED)
     &  +M2*ZETA2*LHM1*(8*U1*T1M1*Q2-24*U1-8*U1M1*T1*Q2-8*T1
     &  +16*Q2)
     &  +M2*ZETA2*LHM3*(16*U1P2*Q2+24*U1*T1P2+8*U1*T1*Q2+8*U1*
     &  Q22+8*U1M1*T1P4-12*U1M1*T1P3*Q2+8*U1M1*T1P2*Q22+40*T1P3
     &  -20*T1P2*Q2+16*T1*Q22)
     &  +M2*ZETA2*LHM5*(-16*U1*T1P4+72*U1*T1P3*Q2-80*U1*T1P2*
     &  Q22+24*U1*T1*Q23+12*U1M1*T1P5*Q2-24*U1M1*T1P4*Q22+12*
     &  U1M1*T1P3*Q23-24*T1P5+68*T1P4*Q2-80*T1P3*Q22+36*T1P2*Q23
     &  )
     &  +M2*ZETA2*LHPM1*(-4*U1P2*T1M1-8*U1*T1M1*Q2-8*U1+8*
     &  U1M1*T1*Q2-20*T1+16*Q2)
     &  +M2*ZETA2*LHPM3*(12*U1P4*T1M1+8*U1P3*T1M1*Q2+16*U1P3
     &  +4*U1P2*T1+28*U1P2*T1M1*Q22-16*U1P2*Q2+40*U1*T1*Q2+16*U1*
     &  Q22+16*T1P2*Q2-12*T1*Q22)
      VPS(10) =
     &  +M2*ZETA2*(32-24*U1P2*T1M1*SPM1+48*U1*T1M1-72*U1*
     &  SPM1-24*U1M1*T1P2*SPM1+48*U1M1*T1-72*T1*SPM1)
     &  +M2*SQM*LOG8*LOGQ2*(-16*U1P2*T1M1+16*U1*T1M1*Q2-48
     &  *U1-16*U1M1*T1P2+16*U1M1*T1*Q2-48*T1+32*Q2)
     &  +M2*SQM*DLOGQ1*(-32*U1P2*T1M1+32*U1*T1M1*Q2-96*U1
     &  -32*U1M1*T1P2+32*U1M1*T1*Q2-96*T1+64*Q2)
     &  +M2*SQM*DLOGQ2*(-32*U1P2*T1M1+32*U1*T1M1*Q2-96*U1
     &  -32*U1M1*T1P2+32*U1M1*T1*Q2-96*T1+64*Q2)
     &  +M2*SQM*DLOGQ3*(-32*U1P2*T1M1+32*U1*T1M1*Q2-96*U1
     &  -32*U1M1*T1P2+32*U1M1*T1*Q2-96*T1+64*Q2)
     &  +M2*SQM*DLOGQ4*(32*U1P2*T1M1-32*U1*T1M1*Q2+96*U1+32
     &  *U1M1*T1P2-32*U1M1*T1*Q2+96*T1-64*Q2)
     &  +M2*SQM*LOGQ3X2*(-16*U1P2*T1M1+16*U1*T1M1*Q2-48*U1
     &  -16*U1M1*T1P2+16*U1M1*T1*Q2-48*T1+32*Q2)
     &  +M2*LOG9*LHM2*(16*U1P2*T1M1*Q2*X1-16*U1P2*T1M1*Q2*X2+
     &  56*U1*Q2*X1-56*U1*Q2*X2+24*U1M1*T1P2*Q2*X1-24*U1M1*T1P2*Q2*X2
     &  -8*U1M1*T1*Q22*X1+8*U1M1*T1*Q22*X2+48*T1*Q2*X1-48*T1*Q2*
     &  X2-8*Q22*X1+8*Q22*X2)
      VPS(11) =
     &  +M2*LOG9*LHM4*(-16*U1P2*T1*Q2*X1+16*U1P2*T1*Q2*X2+16*
     &  U1P2*Q22*X1-16*U1P2*Q22*X2-32*U1*T1P2*Q2*X1+32*U1*T1P2*Q2*X2
     &  -16*U1*T1*Q22*X1+16*U1*T1*Q22*X2+16*U1*Q23*X1-16*U1*Q23*
     &  X2+40*U1M1*T1P3*Q22*X1-40*U1M1*T1P3*Q22*X2-8*U1M1*T1P2*
     &  Q23*X1+8*U1M1*T1P2*Q23*X2-64*T1P3*Q2*X1+64*T1P3*Q2*X2+56*
     &  T1P2*Q22*X1-56*T1P2*Q22*X2+8*T1*Q23*X1-8*T1*Q23*X2)
     &  +M2*LOG9*LHPM2*(4*U1P3*T1M1*X1-4*U1P3*T1M1*X2+32*U1P2*
     &  T1M1*Q2*X1-32*U1P2*T1M1*Q2*X2-4*U1*T1*X1+4*U1*T1*X2+12*U1*
     &  T1M1*Q22*X1-12*U1*T1M1*Q22*X2+32*U1*Q2*X1-32*U1*Q2*X2+16*
     &  U1M1*T1P2*Q2*X1-16*U1M1*T1P2*Q2*X2-12*U1M1*T1*Q22*X1+12*
     &  U1M1*T1*Q22*X2+64*T1*Q2*X1-64*T1*Q2*X2)
     &  +M2*LOG9*(-4*U1*T1M1*X1+4*U1*T1M1*X2+4*U1M1*T1*X1-
     &  4*U1M1*T1*X2)
     &  +M2*LOG10*LHM2*(-16*U1P2*T1M1*Q2*X1+16*U1P2*T1M1*Q2*X2
     &  -56*U1*Q2*X1+56*U1*Q2*X2-24*U1M1*T1P2*Q2*X1+24*U1M1*T1P2*Q2
     &  *X2+8*U1M1*T1*Q22*X1-8*U1M1*T1*Q22*X2-48*T1*Q2*X1+48*T1*
     &  Q2*X2+8*Q22*X1-8*Q22*X2)
      VPS(12) =
     &  +M2*LOG10*LHM4*(16*U1P2*T1*Q2*X1-16*U1P2*T1*Q2*X2-16*
     &  U1P2*Q22*X1+16*U1P2*Q22*X2+32*U1*T1P2*Q2*X1-32*U1*T1P2*Q2*X2
     &  +16*U1*T1*Q22*X1-16*U1*T1*Q22*X2-16*U1*Q23*X1+16*U1*Q23*
     &  X2-40*U1M1*T1P3*Q22*X1+40*U1M1*T1P3*Q22*X2+8*U1M1*T1P2*
     &  Q23*X1-8*U1M1*T1P2*Q23*X2+64*T1P3*Q2*X1-64*T1P3*Q2*X2-56*
     &  T1P2*Q22*X1+56*T1P2*Q22*X2-8*T1*Q23*X1+8*T1*Q23*X2)
     &  +M2*LOG10*LHPM2*(-4*U1P3*T1M1*X1+4*U1P3*T1M1*X2-32*
     &  U1P2*T1M1*Q2*X1+32*U1P2*T1M1*Q2*X2+4*U1*T1*X1-4*U1*T1*X2-12
     &  *U1*T1M1*Q22*X1+12*U1*T1M1*Q22*X2-32*U1*Q2*X1+32*U1*Q2*X2
     &  -16*U1M1*T1P2*Q2*X1+16*U1M1*T1P2*Q2*X2+12*U1M1*T1*Q22*X1-
     &  12*U1M1*T1*Q22*X2-64*T1*Q2*X1+64*T1*Q2*X2)
     &  +M2*LOG10*(4*U1*T1M1*X1-4*U1*T1M1*X2-4*U1M1*T1*X1+4*
     &  U1M1*T1*X2)
     &  +M2*LHM1*DLOGQ6T*(-8*U1*T1M1*Q2+24*U1+8*U1M1*T1*Q2+8
     &  *T1-16*Q2)
     &  +M2*LHM1*DLOGQ7T*(-8*U1*T1M1*Q2+24*U1+8*U1M1*T1*Q2+8
     &  *T1-16*Q2)
      VPS(13) =
     &  +M2*LHM1*DLOGQ8T*(8*U1*T1M1*Q2-24*U1-8*U1M1*T1*Q2-8*T1
     &  +16*Q2)
     &  +M2*LHM1*DLOGQ9T*(8*U1*T1M1*Q2-24*U1-8*U1M1*T1*Q2-8*T1
     &  +16*Q2)
     &  +M2*LHM1*DLOGQ10T*(8*U1*T1M1*Q2-24*U1-8*U1M1*T1*Q2-8*
     &  T1+16*Q2)
     &  +M2*LHM1*DLOGQ11T*(8*U1*T1M1*Q2-24*U1-8*U1M1*T1*Q2-8*
     &  T1+16*Q2)
     &  +M2*LHM1*DLOGQ12T*(-8*U1*T1M1*Q2+24*U1+8*U1M1*T1*Q2+
     &  8*T1-16*Q2)
     &  +M2*LHM1*DLOGQ13T*(-16*U1*T1M1*Q2+48*U1+16*U1M1*T1*Q2
     &  +16*T1-32*Q2)
     &  +M2*LHM2*(-4*U1P2*T1*TM1+4*U1P2*TM1*Q2+8*U1*T1M1*
     &  Q22-16*U1*Q2+4*U1M1*T1P3*TM1*Q2+4*U1M1*T1P2*TM1*Q22+8*
     &  U1M1*T1*Q22-4*T1P3*TM1-8*T1P2*TM1*Q2+4*T1*TM1*Q22-16*T1
     &  *Q2+16*Q22)
      VPS(14) =
     &  +M2*LHM3*DLOGQ6T*(-16*U1P2*Q2-24*U1*T1P2-8*U1*T1*Q2-8*
     &  U1*Q22-8*U1M1*T1P4+12*U1M1*T1P3*Q2-8*U1M1*T1P2*Q22-40*
     &  T1P3+20*T1P2*Q2-16*T1*Q22)
     &  +M2*LHM3*DLOGQ7T*(-16*U1P2*Q2-24*U1*T1P2-8*U1*T1*Q2-8*
     &  U1*Q22-8*U1M1*T1P4+12*U1M1*T1P3*Q2-8*U1M1*T1P2*Q22-40*
     &  T1P3+20*T1P2*Q2-16*T1*Q22)
     &  +M2*LHM3*DLOGQ8T*(16*U1P2*Q2+24*U1*T1P2+8*U1*T1*Q2+8*U1*
     &  Q22+8*U1M1*T1P4-12*U1M1*T1P3*Q2+8*U1M1*T1P2*Q22+40*T1P3
     &  -20*T1P2*Q2+16*T1*Q22)
     &  +M2*LHM3*DLOGQ9T*(16*U1P2*Q2+24*U1*T1P2+8*U1*T1*Q2+8*U1*
     &  Q22+8*U1M1*T1P4-12*U1M1*T1P3*Q2+8*U1M1*T1P2*Q22+40*T1P3
     &  -20*T1P2*Q2+16*T1*Q22)
     &  +M2*LHM3*DLOGQ10T*(16*U1P2*Q2+24*U1*T1P2+8*U1*T1*Q2+8*U1
     &  *Q22+8*U1M1*T1P4-12*U1M1*T1P3*Q2+8*U1M1*T1P2*Q22+40*T1P3
     &  -20*T1P2*Q2+16*T1*Q22)
     &  +M2*LHM3*DLOGQ11T*(16*U1P2*Q2+24*U1*T1P2+8*U1*T1*Q2+8*U1
     &  *Q22+8*U1M1*T1P4-12*U1M1*T1P3*Q2+8*U1M1*T1P2*Q22+40*T1P3
     &  -20*T1P2*Q2+16*T1*Q22)
      VPS(15) =
     &  +M2*LHM3*DLOGQ12T*(-16*U1P2*Q2-24*U1*T1P2-8*U1*T1*Q2-8
     &  *U1*Q22-8*U1M1*T1P4+12*U1M1*T1P3*Q2-8*U1M1*T1P2*Q22-40*
     &  T1P3+20*T1P2*Q2-16*T1*Q22)
     &  +M2*LHM3*DLOGQ13T*(-32*U1P2*Q2-48*U1*T1P2-16*U1*T1*Q2-
     &  16*U1*Q22-16*U1M1*T1P4+24*U1M1*T1P3*Q2-16*U1M1*T1P2*Q22-
     &  80*T1P3+40*T1P2*Q2-32*T1*Q22)
     &  +M2*LHM5*DLOGQ6T*(16*U1*T1P4-72*U1*T1P3*Q2+80*U1*T1P2*Q22
     &  -24*U1*T1*Q23-12*U1M1*T1P5*Q2+24*U1M1*T1P4*Q22-12*U1M1*
     &  T1P3*Q23+24*T1P5-68*T1P4*Q2+80*T1P3*Q22-36*T1P2*Q23)
     &  +M2*LHM5*DLOGQ7T*(16*U1*T1P4-72*U1*T1P3*Q2+80*U1*T1P2*Q22
     &  -24*U1*T1*Q23-12*U1M1*T1P5*Q2+24*U1M1*T1P4*Q22-12*U1M1*
     &  T1P3*Q23+24*T1P5-68*T1P4*Q2+80*T1P3*Q22-36*T1P2*Q23)
     &  +M2*LHM5*DLOGQ8T*(-16*U1*T1P4+72*U1*T1P3*Q2-80*U1*T1P2*
     &  Q22+24*U1*T1*Q23+12*U1M1*T1P5*Q2-24*U1M1*T1P4*Q22+12*
     &  U1M1*T1P3*Q23-24*T1P5+68*T1P4*Q2-80*T1P3*Q22+36*T1P2*Q23
     &  )
      VPS(16) =
     &  +M2*LHM5*DLOGQ9T*(-16*U1*T1P4+72*U1*T1P3*Q2-80*U1*T1P2*
     &  Q22+24*U1*T1*Q23+12*U1M1*T1P5*Q2-24*U1M1*T1P4*Q22+12*
     &  U1M1*T1P3*Q23-24*T1P5+68*T1P4*Q2-80*T1P3*Q22+36*T1P2*Q23
     &  )
     &  +M2*LHM5*DLOGQ10T*(-16*U1*T1P4+72*U1*T1P3*Q2-80*U1*T1P2*
     &  Q22+24*U1*T1*Q23+12*U1M1*T1P5*Q2-24*U1M1*T1P4*Q22+12*
     &  U1M1*T1P3*Q23-24*T1P5+68*T1P4*Q2-80*T1P3*Q22+36*T1P2*Q23
     &  )
     &  +M2*LHM5*DLOGQ11T*(-16*U1*T1P4+72*U1*T1P3*Q2-80*U1*T1P2*
     &  Q22+24*U1*T1*Q23+12*U1M1*T1P5*Q2-24*U1M1*T1P4*Q22+12*
     &  U1M1*T1P3*Q23-24*T1P5+68*T1P4*Q2-80*T1P3*Q22+36*T1P2*Q23
     &  )
     &  +M2*LHM5*DLOGQ12T*(16*U1*T1P4-72*U1*T1P3*Q2+80*U1*T1P2*
     &  Q22-24*U1*T1*Q23-12*U1M1*T1P5*Q2+24*U1M1*T1P4*Q22-12*
     &  U1M1*T1P3*Q23+24*T1P5-68*T1P4*Q2+80*T1P3*Q22-36*T1P2*Q23
     &  )
      VPS(17) =
     &  +M2*LHM5*DLOGQ13T*(32*U1*T1P4-144*U1*T1P3*Q2+160*U1*T1P2*
     &  Q22-48*U1*T1*Q23-24*U1M1*T1P5*Q2+48*U1M1*T1P4*Q22-24*
     &  U1M1*T1P3*Q23+48*T1P5-136*T1P4*Q2+160*T1P3*Q22-72*T1P2*
     &  Q23)
     &  +M2*LHPM1*DLOGQ6U*(4*U1P2*T1M1+8*U1*T1M1*Q2+8*U1-8*
     &  U1M1*T1*Q2+20*T1-16*Q2)
     &  +M2*LHPM1*DLOGQ7U*(4*U1P2*T1M1+8*U1*T1M1*Q2+8*U1-8*
     &  U1M1*T1*Q2+20*T1-16*Q2)
     &  +M2*LHPM1*DLOGQ8U*(-4*U1P2*T1M1-8*U1*T1M1*Q2-8*U1+8*
     &  U1M1*T1*Q2-20*T1+16*Q2)
     &  +M2*LHPM1*DLOGQ9U*(-4*U1P2*T1M1-8*U1*T1M1*Q2-8*U1+8*
     &  U1M1*T1*Q2-20*T1+16*Q2)
     &  +M2*LHPM1*DLOGQ10U*(-4*U1P2*T1M1-8*U1*T1M1*Q2-8*U1+8
     &  *U1M1*T1*Q2-20*T1+16*Q2)
     &  +M2*LHPM1*DLOGQ11U*(-4*U1P2*T1M1-8*U1*T1M1*Q2-8*U1+8
     &  *U1M1*T1*Q2-20*T1+16*Q2)
     &  +M2*LHPM1*DLOGQ12U*(4*U1P2*T1M1+8*U1*T1M1*Q2+8*U1-8*
     &  U1M1*T1*Q2+20*T1-16*Q2)
      VPS(18) =
     &  +M2*LHPM1*DLOGQ13U*(8*U1P2*T1M1+16*U1*T1M1*Q2+16*U1-16
     &  *U1M1*T1*Q2+40*T1-32*Q2)
     &  +M2*LHPM3*DLOGQ6U*(-12*U1P4*T1M1-8*U1P3*T1M1*Q2-16*
     &  U1P3-4*U1P2*T1-28*U1P2*T1M1*Q22+16*U1P2*Q2-40*U1*T1*Q2-16
     &  *U1*Q22-16*T1P2*Q2+12*T1*Q22)
     &  +M2*LHPM3*DLOGQ7U*(-12*U1P4*T1M1-8*U1P3*T1M1*Q2-16*
     &  U1P3-4*U1P2*T1-28*U1P2*T1M1*Q22+16*U1P2*Q2-40*U1*T1*Q2-16
     &  *U1*Q22-16*T1P2*Q2+12*T1*Q22)
     &  +M2*LHPM3*DLOGQ8U*(12*U1P4*T1M1+8*U1P3*T1M1*Q2+16*U1P3
     &  +4*U1P2*T1+28*U1P2*T1M1*Q22-16*U1P2*Q2+40*U1*T1*Q2+16*U1*
     &  Q22+16*T1P2*Q2-12*T1*Q22)
     &  +M2*LHPM3*DLOGQ9U*(12*U1P4*T1M1+8*U1P3*T1M1*Q2+16*U1P3
     &  +4*U1P2*T1+28*U1P2*T1M1*Q22-16*U1P2*Q2+40*U1*T1*Q2+16*U1*
     &  Q22+16*T1P2*Q2-12*T1*Q22)
     &  +M2*LHPM3*DLOGQ10U*(12*U1P4*T1M1+8*U1P3*T1M1*Q2+16*U1P3
     &  +4*U1P2*T1+28*U1P2*T1M1*Q22-16*U1P2*Q2+40*U1*T1*Q2+16*U1*
     &  Q22+16*T1P2*Q2-12*T1*Q22)
      VPS(19) =
     &  +M2*LHPM3*DLOGQ11U*(12*U1P4*T1M1+8*U1P3*T1M1*Q2+16*U1P3
     &  +4*U1P2*T1+28*U1P2*T1M1*Q22-16*U1P2*Q2+40*U1*T1*Q2+16*U1*
     &  Q22+16*T1P2*Q2-12*T1*Q22)
     &  +M2*LHPM3*DLOGQ12U*(-12*U1P4*T1M1-8*U1P3*T1M1*Q2-16*
     &  U1P3-4*U1P2*T1-28*U1P2*T1M1*Q22+16*U1P2*Q2-40*U1*T1*Q2-16
     &  *U1*Q22-16*T1P2*Q2+12*T1*Q22)
     &  +M2*LHPM3*DLOGQ13U*(-24*U1P4*T1M1-16*U1P3*T1M1*Q2-32*
     &  U1P3-8*U1P2*T1-56*U1P2*T1M1*Q22+32*U1P2*Q2-80*U1*T1*Q2-32
     &  *U1*Q22-32*T1P2*Q2+24*T1*Q22)
     &  +M2*LOG7X2*(-4*U1P2*T1M1*SPM1-12*U1*SPM1-4*U1M1*
     &  T1P2*SPM1-12*T1*SPM1)
     &  +M2*DLOG7*(-32-32*U1*T1M1-32*U1M1*T1)
     &  +M2*DLOG8*(-32-32*U1*T1M1-32*U1M1*T1)
     &  +M2*(8*U1P2*T1M1*UM1-16*U1*T1M1*Q2*S1M1-4*U1*TM1+
     &  32*U1*S1M1+4*U1M1*T1P2*TM1-16*U1M1*T1*Q2*S1M1+32*T1*S1M1
     &  -32*Q2*S1M1)
     &  +XSQM1*LOG1X2*(16*BQED)
      VPS(20) =
     &  +XSQM1*LOG1*LOG5*(-32*BQED)
     &  +XSQM1*LOG1*LOG6*(-32*BQED)
     &  +XSQM1*LOG1*(32*BQED*LOGDEL)
     &  +XSQM1*DLOG2*(-32*BQED)
     &  +XSQM1*DLOG1*(-32*BQED)
     &  +XSQM1*ZETA2*(16*BQED)
     &  +LOG1X2*SQM*(-4*U1P2-8*U1*T1+8*U1*Q2-4*T1P2+8*T1
     &  *Q2-4*Q22)
     &  +LOG1X2*(4*U1P3*SPM2+12*U1P2*T1*SPM2-4*U1P2*Q2*SPM2+8
     &  *U1P2*SPM1+12*U1*T1P2*SPM2-8*U1*T1*Q2*SPM2+16*U1*T1*SPM1-
     &  8*U1*Q2*SPM1+4*T1P3*SPM2-4*T1P2*Q2*SPM2+8*T1P2*SPM1-8*T1*
     &  Q2*SPM1-8*BQED)
     &  +LOG1*LOG5*SQM*(32*U1P2+64*U1*T1-64*U1*Q2+32*T1P2-
     &  64*T1*Q2+32*Q22)
     &  +LOG1*LOG6*SQM*(-16*U1P2-32*U1*T1+32*U1*Q2-16*T1P2
     &  +32*T1*Q2-16*Q22)
     &  +LOG1*LOG3*SQM*(8*U1P2+16*U1*T1-16*U1*Q2+8*T1P2-16*
     &  T1*Q2+8*Q22)
      VPS(21) =
     &  +LOG1*LOG3*(-16*BQED)
     &  +LOG1*LOG4*SQM*(8*U1P2+16*U1*T1-16*U1*Q2+8*T1P2-16*
     &  T1*Q2+8*Q22)
     &  +LOG1*LOG4*(16*BQED)
     &  +LOG1*SQM*LOGQ1*(-8*U1P2-16*U1*T1+16*U1*Q2-8*T1P2
     &  +16*T1*Q2-8*Q22)
      VPS(22) =
     &  +LOG1*SQM*(4*U1P4*T1M1*S1M1-4*U1P4*T1M1*SPM1-10*
     &  U1P3*T1M1*Q2*S1M1+8*U1P3*T1M1*Q2*SPM1-8*U1P3*T1M1+16*U1P3*
     &  Q2*SPM2-4*U1P3*SPM1+48*U1P2*T1*Q2*SPM2-20*U1P2*T1*S1M1+8*
     &  U1P2*T1*SPM1+8*U1P2*T1M1*Q22*S1M1-4*U1P2*T1M1*Q22*SPM1+
     &  14*U1P2*T1M1*Q2-16*U1P2*Q22*SPM2+16*U1P2*Q2*S1M1+16*U1P2*Q2
     &  *SPM1-12*U1P2+48*U1*T1P2*Q2*SPM2-20*U1*T1P2*S1M1+8*U1*T1P2
     &  *SPM1-32*U1*T1*Q22*SPM2+52*U1*T1*Q2*S1M1+16*U1*T1*Q2*SPM1
     &  -8*U1*T1-2*U1*T1M1*Q23*S1M1-6*U1*T1M1*Q22-28*U1*Q22*
     &  S1M1-12*U1*Q22*SPM1+6*U1*Q2+4*U1M1*T1P4*S1M1-4*U1M1*
     &  T1P4*SPM1-10*U1M1*T1P3*Q2*S1M1+8*U1M1*T1P3*Q2*SPM1-8*U1M1
     &  *T1P3+8*U1M1*T1P2*Q22*S1M1-4*U1M1*T1P2*Q22*SPM1+14*U1M1*
     &  T1P2*Q2-2*U1M1*T1*Q23*S1M1-6*U1M1*T1*Q22+16*T1P3*Q2*SPM2
     &  -4*T1P3*SPM1-16*T1P2*Q22*SPM2+16*T1P2*Q2*S1M1+16*T1P2*Q2*
     &  SPM1-12*T1P2-28*T1*Q22*S1M1-12*T1*Q22*SPM1+6*T1*Q2+12*
     &  Q23*S1M1+4*Q22)
     &  +LOG3X2*(-8*U1-8*T1+8*Q2+8*BQED)
     &  +LOG3*LOG4*(-16*U1-16*T1+16*Q2-16*BQED)
      VPS(23) =
     &  +LOG3*LHM2*(4*U1P2*T1P3*TM2-4*U1P2*T1P2*TM2*Q2+24*U1*
     &  T1P3*TM1-16*U1*T1P2*TM1*Q2+4*U1M1*T1P5*TM1-4*U1M1*T1P5*
     &  TM2*Q2-18*U1M1*T1P4*TM1*Q2-4*U1M1*T1P4*TM2*Q22+18*U1M1*
     &  T1P3*TM1*Q22-4*U1M1*T1P2*TM1*Q23+4*T1P5*TM2+24*T1P4*TM1
     &  +8*T1P4*TM2*Q2-50*T1P3*TM1*Q2-4*T1P3*TM2*Q22+18*T1P2*TM1
     &  *Q22)
     &  +LOG3*LHM4*(-4*U1P2*T1P4*TM1+12*U1P2*T1P3*TM1*Q2-12*
     &  U1P2*T1P2*TM1*Q22+4*U1P2*T1*TM1*Q23-16*U1*T1P5*TM1+40*U1*
     &  T1P4*TM1*Q2-32*U1*T1P3*TM1*Q22+8*U1*T1P2*TM1*Q23+10*U1M1*
     &  T1P6*TM1*Q2-22*U1M1*T1P5*TM1*Q22+14*U1M1*T1P4*TM1*Q23-2*
     &  U1M1*T1P3*TM1*Q24-16*T1P6*TM1+50*T1P5*TM1*Q2-54*T1P4*TM1*
     &  Q22+22*T1P3*TM1*Q23-2*T1P2*TM1*Q24)
     &  +LOG3*(4*U1*T1P2*TM2-4*U1*T1*TM1-4*U1M1*T1P4*TM2+4*
     &  U1M1*T1P2*TM1*Q2-4*T1P2*TM1+32*BQED*LOGDEL)
     &  +LOG4X2*(-8*U1-8*T1+8*Q2+8*BQED)
      VPS(24) =
     &  +LOG4*LHPM2*(4*U1P5*T1M1*UM1-12*U1P4*T1M1*UM1*Q2+12*
     &  U1P4*UM1+8*U1P3*T1*UM1+12*U1P3*T1M1*UM1*Q22-24*U1P3*UM1*
     &  Q2-8*U1P2*T1*UM1*Q2-4*U1P2*T1M1*UM1*Q23+12*U1P2*UM1*Q22)
     &  +LOG4*(-8*U1P4*T1M1*UM2+4*U1P3*T1M1*UM1+4*U1P2*T1M1
     &  *UM1*Q2-4*U1P2*UM1-32*BQED*LOGDEL)
     &  +DLOG2*SQM*(32*U1P2+64*U1*T1-64*U1*Q2+32*T1P2-64*T1
     &  *Q2+32*Q22)
     &  +DLOG3*(-4*U1-4*T1+4*Q2)
     &  +DLOG4*(-4*U1-4*T1+4*Q2)
     &  +DLOG1*SQM*(-16*U1P2-32*U1*T1+32*U1*Q2-16*T1P2+
     &  32*T1*Q2-16*Q22)
     &  +ZETA2*SQM*(88*U1P2+176*U1*T1-176*U1*Q2+88*T1P2-
     &  176*T1*Q2+88*Q22)
     &  +ZETA2*LHM1*(4*U1P2+4*U1*Q2+4*U1M1*T1P3+12*T1*Q2-4*
     &  Q22)
CBH HERE (ABOVE) I REMOVE THE LOGMU DEPENDENCE BY HAND
CBH     &    *UM1*Q2-4*U1P2*UM1-32*BQED*LOGDEL+32*BQED*LOGMU)
      VPS(25) =
     &  +ZETA2*LHM3*(-4*U1P2*T1P2+8*U1P2*T1*Q2-4*U1P2*Q22+4
     &  *U1*T1P3-4*U1*T1P2*Q2-4*U1M1*T1P5+8*U1M1*T1P4*Q2-4*U1M1*
     &  T1P3*Q22-4*T1P4+8*T1P2*Q22-4*T1*Q23)
     &  +ZETA2*LHM5*(-8*U1*T1P5+28*U1*T1P4*Q2-36*U1*T1P3*Q22
     &  +20*U1*T1P2*Q23-4*U1*T1*Q24+4*T1P5*Q2-12*T1P4*Q22+12*
     &  T1P3*Q23-4*T1P2*Q24)
     &  +ZETA2*LHPM1*(8*U1P3*T1M1+4*U1P2*T1M1*Q2-4*U1P2+4*U1
     &  *T1+12*U1*Q2+4*T1P2-4*Q22)
     &  +ZETA2*LHPM3*(-8*U1P5*T1M1+12*U1P4*T1M1*Q2-8*U1P3*T1
     &  -4*U1P3*Q2-4*U1P2*T1P2+20*U1P2*T1*Q2-4*U1P2*T1M1*Q23+8*
     &  U1P2*Q22+8*U1*T1P2*Q2-16*U1*T1*Q22-4*U1*Q23-4*T1P2*Q22+
     &  4*T1*Q23)
     &  +ZETA2*(-24*U1P3*SPM2-72*U1P2*T1*SPM2+24*U1P2*Q2*
     &  SPM2-48*U1P2*SPM1-72*U1*T1P2*SPM2+48*U1*T1*Q2*SPM2-96*U1*
     &  T1*SPM1+48*U1*Q2*SPM1+16*U1-24*T1P3*SPM2+24*T1P2*Q2*SPM2
     &  -48*T1P2*SPM1+48*T1*Q2*SPM1+16*T1-16*Q2-24*BQED)
     &  +SQM*LOG8*LOGQ2*(-8*U1P2-16*U1*T1+16*U1*Q2-8*T1P2
     &  +16*T1*Q2-8*Q22)
      VPS(26) =
     &  +SQM*DLOGQ1*(-16*U1P2-32*U1*T1+32*U1*Q2-16*T1P2+
     &  32*T1*Q2-16*Q22)
     &  +SQM*DLOGQ2*(-16*U1P2-32*U1*T1+32*U1*Q2-16*T1P2+
     &  32*T1*Q2-16*Q22)
     &  +SQM*DLOGQ3*(-16*U1P2-32*U1*T1+32*U1*Q2-16*T1P2+
     &  32*T1*Q2-16*Q22)
     &  +SQM*DLOGQ4*(16*U1P2+32*U1*T1-32*U1*Q2+16*T1P2-32*
     &  T1*Q2+16*Q22)
     &  +SQM*LOGQ3X2*(-8*U1P2-16*U1*T1+16*U1*Q2-8*T1P2+
     &  16*T1*Q2-8*Q22)
      VPS(27) =
     &  +LOG9*LHM2*(-8*U1P2*T1*X1+8*U1P2*T1*X2-4*U1P2*T1M1*
     &  Q22*X1+4*U1P2*T1M1*Q22*X2+12*U1P2*Q2*X1-12*U1P2*Q2*X2-24*
     &  U1*T1P2*X1+24*U1*T1P2*X2+22*U1*T1*Q2*X1-22*U1*T1*Q2*X2+2*U1*
     &  T1M1*Q23*X1-2*U1*T1M1*Q23*X2-8*U1*Q22*X1+8*U1*Q22*X2-8*
     &  U1M1*T1P4*X1+8*U1M1*T1P4*X2+30*U1M1*T1P3*Q2*X1-30*U1M1*T1P3
     &  *Q2*X2-18*U1M1*T1P2*Q22*X1+18*U1M1*T1P2*Q22*X2+4*U1M1*T1*
     &  Q23*X1-4*U1M1*T1*Q23*X2-32*T1P3*X1+32*T1P3*X2+44*T1P2*Q2*
     &  X1-44*T1P2*Q2*X2-10*T1*Q22*X1+10*T1*Q22*X2-2*Q23*X1+2*
     &  Q23*X2)
      VPS(28) =
     &  +LOG9*LHM4*(4*U1P2*T1P3*X1-4*U1P2*T1P3*X2-12*U1P2*T1P2*
     &  Q2*X1+12*U1P2*T1P2*Q2*X2+12*U1P2*T1*Q22*X1-12*U1P2*T1*Q22*X2
     &  -4*U1P2*Q23*X1+4*U1P2*Q23*X2+8*U1*T1P4*X1-8*U1*T1P4*X2-12
     &  *U1*T1P3*Q2*X1+12*U1*T1P3*Q2*X2-4*U1*T1P2*Q22*X1+4*U1*T1P2*
     &  Q22*X2+12*U1*T1*Q23*X1-12*U1*T1*Q23*X2-4*U1*Q24*X1+4*U1*
     &  Q24*X2-10*U1M1*T1P5*Q2*X1+10*U1M1*T1P5*Q2*X2+22*U1M1*T1P4*
     &  Q22*X1-22*U1M1*T1P4*Q22*X2-14*U1M1*T1P3*Q23*X1+14*U1M1*
     &  T1P3*Q23*X2+2*U1M1*T1P2*Q24*X1-2*U1M1*T1P2*Q24*X2+16*T1P5*
     &  X1-16*T1P5*X2-46*T1P4*Q2*X1+46*T1P4*Q2*X2+42*T1P3*Q22*X1-
     &  42*T1P3*Q22*X2-10*T1P2*Q23*X1+10*T1P2*Q23*X2-2*T1*Q24*X1+
     &  2*T1*Q24*X2)
     &  +LOG9*LHPM2*(-12*U1P4*T1M1*X1+12*U1P4*T1M1*X2+24*
     &  U1P3*T1M1*Q2*X1-24*U1P3*T1M1*Q2*X2-12*U1P3*X1+12*U1P3*X2-16
     &  *U1P2*T1*X1+16*U1P2*T1*X2-12*U1P2*T1M1*Q22*X1+12*U1P2*T1M1*
     &  Q22*X2+20*U1P2*Q2*X1-20*U1P2*Q2*X2-4*U1*T1P2*X1+4*U1*T1P2*X2
     &  +28*U1*T1*Q2*X1-28*U1*T1*Q2*X2-4*U1*Q22*X1+4*U1*Q22*X2-4*
     &  U1M1*T1P2*Q22*X1+4*U1M1*T1P2*Q22*X2+4*U1M1*T1*Q23*X1-4*
     &  U1M1*T1*Q23*X2+8*T1P2*Q2*X1-8*T1P2*Q2*X2-16*T1*Q22*X1+16*
     &  T1*Q22*X2-4*Q23*X1+4*Q23*X2)
      VPS(29) =
     &  +LOG9*(4*U1P3*T1M1*SPM1*X1-4*U1P3*T1M1*SPM1*X2-4*U1P2
     &  *T1M1*Q2*SPM1*X1+4*U1P2*T1M1*Q2*SPM1*X2+20*U1P2*T1M1*X1-20
     &  *U1P2*T1M1*X2-16*U1P2*Q2*SPM2*X1+16*U1P2*Q2*SPM2*X2+8*U1P2*
     &  SPM1*X1-8*U1P2*SPM1*X2-32*U1*T1*Q2*SPM2*X1+32*U1*T1*Q2*SPM2
     &  *X2+8*U1*T1*SPM1*X1-8*U1*T1*SPM1*X2-6*U1*T1M1*Q2*X1+6*U1*
     &  T1M1*Q2*X2-12*U1*Q2*SPM1*X1+12*U1*Q2*SPM1*X2+32*U1*X1-32*
     &  U1*X2+4*U1M1*T1P3*SPM1*X1-4*U1M1*T1P3*SPM1*X2-4*U1M1*T1P2*
     &  Q2*SPM1*X1+4*U1M1*T1P2*Q2*SPM1*X2+16*U1M1*T1P2*X1-16*U1M1*
     &  T1P2*X2-12*U1M1*T1*Q2*X1+12*U1M1*T1*Q2*X2-16*T1P2*Q2*SPM2*X1
     &  +16*T1P2*Q2*SPM2*X2+8*T1P2*SPM1*X1-8*T1P2*SPM1*X2-12*T1*Q2
     &  *SPM1*X1+12*T1*Q2*SPM1*X2+36*T1*X1-36*T1*X2-2*Q2*X1+2*Q2*
     &  X2)
      VPS(30) =
     &  +LOG10*LHM2*(8*U1P2*T1*X1-8*U1P2*T1*X2+4*U1P2*T1M1*Q22
     &  *X1-4*U1P2*T1M1*Q22*X2-12*U1P2*Q2*X1+12*U1P2*Q2*X2+24*U1*
     &  T1P2*X1-24*U1*T1P2*X2-22*U1*T1*Q2*X1+22*U1*T1*Q2*X2-2*U1*
     &  T1M1*Q23*X1+2*U1*T1M1*Q23*X2+8*U1*Q22*X1-8*U1*Q22*X2+8*
     &  U1M1*T1P4*X1-8*U1M1*T1P4*X2-30*U1M1*T1P3*Q2*X1+30*U1M1*T1P3
     &  *Q2*X2+18*U1M1*T1P2*Q22*X1-18*U1M1*T1P2*Q22*X2-4*U1M1*T1*
     &  Q23*X1+4*U1M1*T1*Q23*X2+32*T1P3*X1-32*T1P3*X2-44*T1P2*Q2*
     &  X1+44*T1P2*Q2*X2+10*T1*Q22*X1-10*T1*Q22*X2+2*Q23*X1-2*
     &  Q23*X2)
      VPS(31) =
     &  +LOG10*LHM4*(-4*U1P2*T1P3*X1+4*U1P2*T1P3*X2+12*U1P2*
     &  T1P2*Q2*X1-12*U1P2*T1P2*Q2*X2-12*U1P2*T1*Q22*X1+12*U1P2*T1*
     &  Q22*X2+4*U1P2*Q23*X1-4*U1P2*Q23*X2-8*U1*T1P4*X1+8*U1*T1P4*
     &  X2+12*U1*T1P3*Q2*X1-12*U1*T1P3*Q2*X2+4*U1*T1P2*Q22*X1-4*U1*
     &  T1P2*Q22*X2-12*U1*T1*Q23*X1+12*U1*T1*Q23*X2+4*U1*Q24*X1-4
     &  *U1*Q24*X2+10*U1M1*T1P5*Q2*X1-10*U1M1*T1P5*Q2*X2-22*U1M1*
     &  T1P4*Q22*X1+22*U1M1*T1P4*Q22*X2+14*U1M1*T1P3*Q23*X1-14*
     &  U1M1*T1P3*Q23*X2-2*U1M1*T1P2*Q24*X1+2*U1M1*T1P2*Q24*X2-16
     &  *T1P5*X1+16*T1P5*X2+46*T1P4*Q2*X1-46*T1P4*Q2*X2-42*T1P3*Q22*
     &  X1+42*T1P3*Q22*X2+10*T1P2*Q23*X1-10*T1P2*Q23*X2+2*T1*Q24*
     &  X1-2*T1*Q24*X2)
     &  +LOG10*LHPM2*(12*U1P4*T1M1*X1-12*U1P4*T1M1*X2-24*U1P3*
     &  T1M1*Q2*X1+24*U1P3*T1M1*Q2*X2+12*U1P3*X1-12*U1P3*X2+16*U1P2
     &  *T1*X1-16*U1P2*T1*X2+12*U1P2*T1M1*Q22*X1-12*U1P2*T1M1*Q22*
     &  X2-20*U1P2*Q2*X1+20*U1P2*Q2*X2+4*U1*T1P2*X1-4*U1*T1P2*X2-28
     &  *U1*T1*Q2*X1+28*U1*T1*Q2*X2+4*U1*Q22*X1-4*U1*Q22*X2+4*U1M1
     &  *T1P2*Q22*X1-4*U1M1*T1P2*Q22*X2-4*U1M1*T1*Q23*X1+4*U1M1*
     &  T1*Q23*X2-8*T1P2*Q2*X1+8*T1P2*Q2*X2+16*T1*Q22*X1-16*T1*Q22
     &  *X2+4*Q23*X1-4*Q23*X2)
      VPS(32) =
     &  +LOG10*(-4*U1P3*T1M1*SPM1*X1+4*U1P3*T1M1*SPM1*X2+4*
     &  U1P2*T1M1*Q2*SPM1*X1-4*U1P2*T1M1*Q2*SPM1*X2-20*U1P2*T1M1*X1
     &  +20*U1P2*T1M1*X2+16*U1P2*Q2*SPM2*X1-16*U1P2*Q2*SPM2*X2-8*
     &  U1P2*SPM1*X1+8*U1P2*SPM1*X2+32*U1*T1*Q2*SPM2*X1-32*U1*T1*Q2*
     &  SPM2*X2-8*U1*T1*SPM1*X1+8*U1*T1*SPM1*X2+6*U1*T1M1*Q2*X1-6
     &  *U1*T1M1*Q2*X2+12*U1*Q2*SPM1*X1-12*U1*Q2*SPM1*X2-32*U1*X1+
     &  32*U1*X2-4*U1M1*T1P3*SPM1*X1+4*U1M1*T1P3*SPM1*X2+4*U1M1*
     &  T1P2*Q2*SPM1*X1-4*U1M1*T1P2*Q2*SPM1*X2-16*U1M1*T1P2*X1+16*
     &  U1M1*T1P2*X2+12*U1M1*T1*Q2*X1-12*U1M1*T1*Q2*X2+16*T1P2*Q2*
     &  SPM2*X1-16*T1P2*Q2*SPM2*X2-8*T1P2*SPM1*X1+8*T1P2*SPM1*X2+
     &  12*T1*Q2*SPM1*X1-12*T1*Q2*SPM1*X2-36*T1*X1+36*T1*X2+2*Q2*X1
     &  -2*Q2*X2)
     &  +LHM1*DLOGQ6T*(-4*U1P2-4*U1*Q2-4*U1M1*T1P3-12*T1*Q2
     &  +4*Q22)
     &  +LHM1*DLOGQ7T*(-4*U1P2-4*U1*Q2-4*U1M1*T1P3-12*T1*Q2
     &  +4*Q22)
     &  +LHM1*DLOGQ8T*(4*U1P2+4*U1*Q2+4*U1M1*T1P3+12*T1*Q2-4*
     &  Q22)
      VPS(33) =
     &  +LHM1*DLOGQ9T*(4*U1P2+4*U1*Q2+4*U1M1*T1P3+12*T1*Q2-4*
     &  Q22)
     &  +LHM1*DLOGQ10T*(4*U1P2+4*U1*Q2+4*U1M1*T1P3+12*T1*Q2-4
     &  *Q22)
     &  +LHM1*DLOGQ11T*(4*U1P2+4*U1*Q2+4*U1M1*T1P3+12*T1*Q2-4
     &  *Q22)
     &  +LHM1*DLOGQ12T*(-4*U1P2-4*U1*Q2-4*U1M1*T1P3-12*T1*Q2
     &  +4*Q22)
     &  +LHM1*DLOGQ13T*(-8*U1P2-8*U1*Q2-8*U1M1*T1P3-24*T1*Q2
     &  +8*Q22)
     &  +LHM2*(-4*U1P2*T1P2*TM1+4*U1P2*T1*TM1*Q2+4*U1P2*T1
     &  -4*U1P2*Q2+4*U1*T1P2-10*U1*T1*Q2-2*U1*T1M1*Q23+8*U1*Q22
     &  +4*U1M1*T1P4*TM1*Q2+4*U1M1*T1P3*TM1*Q22-6*U1M1*T1P3*Q2-
     &  2*U1M1*T1*Q23-4*T1P4*TM1-8*T1P3*TM1*Q2+8*T1P3+4*T1P2*TM1
     &  *Q22-4*T1P2*Q2+8*T1*Q22-4*Q23)
      VPS(34) =
     &  +LHM3*DLOGQ6T*(4*U1P2*T1P2-8*U1P2*T1*Q2+4*U1P2*Q22-4*U1
     &  *T1P3+4*U1*T1P2*Q2+4*U1M1*T1P5-8*U1M1*T1P4*Q2+4*U1M1*T1P3*
     &  Q22+4*T1P4-8*T1P2*Q22+4*T1*Q23)
     &  +LHM3*DLOGQ7T*(4*U1P2*T1P2-8*U1P2*T1*Q2+4*U1P2*Q22-4*U1
     &  *T1P3+4*U1*T1P2*Q2+4*U1M1*T1P5-8*U1M1*T1P4*Q2+4*U1M1*T1P3*
     &  Q22+4*T1P4-8*T1P2*Q22+4*T1*Q23)
     &  +LHM3*DLOGQ8T*(-4*U1P2*T1P2+8*U1P2*T1*Q2-4*U1P2*Q22+4
     &  *U1*T1P3-4*U1*T1P2*Q2-4*U1M1*T1P5+8*U1M1*T1P4*Q2-4*U1M1*
     &  T1P3*Q22-4*T1P4+8*T1P2*Q22-4*T1*Q23)
     &  +LHM3*DLOGQ9T*(-4*U1P2*T1P2+8*U1P2*T1*Q2-4*U1P2*Q22+4
     &  *U1*T1P3-4*U1*T1P2*Q2-4*U1M1*T1P5+8*U1M1*T1P4*Q2-4*U1M1*
     &  T1P3*Q22-4*T1P4+8*T1P2*Q22-4*T1*Q23)
     &  +LHM3*DLOGQ10T*(-4*U1P2*T1P2+8*U1P2*T1*Q2-4*U1P2*Q22+
     &  4*U1*T1P3-4*U1*T1P2*Q2-4*U1M1*T1P5+8*U1M1*T1P4*Q2-4*U1M1*
     &  T1P3*Q22-4*T1P4+8*T1P2*Q22-4*T1*Q23)
     &  +LHM3*DLOGQ11T*(-4*U1P2*T1P2+8*U1P2*T1*Q2-4*U1P2*Q22+
     &  4*U1*T1P3-4*U1*T1P2*Q2-4*U1M1*T1P5+8*U1M1*T1P4*Q2-4*U1M1*
     &  T1P3*Q22-4*T1P4+8*T1P2*Q22-4*T1*Q23)
      VPS(35) =
     &  +LHM3*DLOGQ12T*(4*U1P2*T1P2-8*U1P2*T1*Q2+4*U1P2*Q22-4*
     &  U1*T1P3+4*U1*T1P2*Q2+4*U1M1*T1P5-8*U1M1*T1P4*Q2+4*U1M1*
     &  T1P3*Q22+4*T1P4-8*T1P2*Q22+4*T1*Q23)
     &  +LHM3*DLOGQ13T*(8*U1P2*T1P2-16*U1P2*T1*Q2+8*U1P2*Q22-8*
     &  U1*T1P3+8*U1*T1P2*Q2+8*U1M1*T1P5-16*U1M1*T1P4*Q2+8*U1M1*
     &  T1P3*Q22+8*T1P4-16*T1P2*Q22+8*T1*Q23)
     &  +LHM5*DLOGQ6T*(8*U1*T1P5-28*U1*T1P4*Q2+36*U1*T1P3*Q22-
     &  20*U1*T1P2*Q23+4*U1*T1*Q24-4*T1P5*Q2+12*T1P4*Q22-12*T1P3*
     &  Q23+4*T1P2*Q24)
     &  +LHM5*DLOGQ7T*(8*U1*T1P5-28*U1*T1P4*Q2+36*U1*T1P3*Q22-
     &  20*U1*T1P2*Q23+4*U1*T1*Q24-4*T1P5*Q2+12*T1P4*Q22-12*T1P3*
     &  Q23+4*T1P2*Q24)
     &  +LHM5*DLOGQ8T*(-8*U1*T1P5+28*U1*T1P4*Q2-36*U1*T1P3*Q22
     &  +20*U1*T1P2*Q23-4*U1*T1*Q24+4*T1P5*Q2-12*T1P4*Q22+12*
     &  T1P3*Q23-4*T1P2*Q24)
      VPS(36) =
     &  +LHM5*DLOGQ9T*(-8*U1*T1P5+28*U1*T1P4*Q2-36*U1*T1P3*Q22
     &  +20*U1*T1P2*Q23-4*U1*T1*Q24+4*T1P5*Q2-12*T1P4*Q22+12*
     &  T1P3*Q23-4*T1P2*Q24)
     &  +LHM5*DLOGQ10T*(-8*U1*T1P5+28*U1*T1P4*Q2-36*U1*T1P3*Q22
     &  +20*U1*T1P2*Q23-4*U1*T1*Q24+4*T1P5*Q2-12*T1P4*Q22+12*
     &  T1P3*Q23-4*T1P2*Q24)
     &  +LHM5*DLOGQ11T*(-8*U1*T1P5+28*U1*T1P4*Q2-36*U1*T1P3*Q22
     &  +20*U1*T1P2*Q23-4*U1*T1*Q24+4*T1P5*Q2-12*T1P4*Q22+12*
     &  T1P3*Q23-4*T1P2*Q24)
     &  +LHM5*DLOGQ12T*(8*U1*T1P5-28*U1*T1P4*Q2+36*U1*T1P3*Q22-
     &  20*U1*T1P2*Q23+4*U1*T1*Q24-4*T1P5*Q2+12*T1P4*Q22-12*T1P3*
     &  Q23+4*T1P2*Q24)
     &  +LHM5*DLOGQ13T*(16*U1*T1P5-56*U1*T1P4*Q2+72*U1*T1P3*Q22
     &  -40*U1*T1P2*Q23+8*U1*T1*Q24-8*T1P5*Q2+24*T1P4*Q22-24*
     &  T1P3*Q23+8*T1P2*Q24)
     &  +LHPM1*DLOGQ6U*(-8*U1P3*T1M1-4*U1P2*T1M1*Q2+4*U1P2-4
     &  *U1*T1-12*U1*Q2-4*T1P2+4*Q22)
      VPS(37) =
     &  +LHPM1*DLOGQ7U*(-8*U1P3*T1M1-4*U1P2*T1M1*Q2+4*U1P2-4
     &  *U1*T1-12*U1*Q2-4*T1P2+4*Q22)
     &  +LHPM1*DLOGQ8U*(8*U1P3*T1M1+4*U1P2*T1M1*Q2-4*U1P2+4*U1
     &  *T1+12*U1*Q2+4*T1P2-4*Q22)
     &  +LHPM1*DLOGQ9U*(8*U1P3*T1M1+4*U1P2*T1M1*Q2-4*U1P2+4*U1
     &  *T1+12*U1*Q2+4*T1P2-4*Q22)
     &  +LHPM1*DLOGQ10U*(8*U1P3*T1M1+4*U1P2*T1M1*Q2-4*U1P2+4*
     &  U1*T1+12*U1*Q2+4*T1P2-4*Q22)
     &  +LHPM1*DLOGQ11U*(8*U1P3*T1M1+4*U1P2*T1M1*Q2-4*U1P2+4*
     &  U1*T1+12*U1*Q2+4*T1P2-4*Q22)
     &  +LHPM1*DLOGQ12U*(-8*U1P3*T1M1-4*U1P2*T1M1*Q2+4*U1P2-
     &  4*U1*T1-12*U1*Q2-4*T1P2+4*Q22)
     &  +LHPM1*DLOGQ13U*(-16*U1P3*T1M1-8*U1P2*T1M1*Q2+8*U1P2
     &  -8*U1*T1-24*U1*Q2-8*T1P2+8*Q22)
     &  +LHPM3*DLOGQ6U*(8*U1P5*T1M1-12*U1P4*T1M1*Q2+8*U1P3*T1+
     &  4*U1P3*Q2+4*U1P2*T1P2-20*U1P2*T1*Q2+4*U1P2*T1M1*Q23-8*U1P2*
     &  Q22-8*U1*T1P2*Q2+16*U1*T1*Q22+4*U1*Q23+4*T1P2*Q22-4*T1*
     &  Q23)
      VPS(38) =
     &  +LHPM3*DLOGQ7U*(8*U1P5*T1M1-12*U1P4*T1M1*Q2+8*U1P3*T1+
     &  4*U1P3*Q2+4*U1P2*T1P2-20*U1P2*T1*Q2+4*U1P2*T1M1*Q23-8*U1P2*
     &  Q22-8*U1*T1P2*Q2+16*U1*T1*Q22+4*U1*Q23+4*T1P2*Q22-4*T1*
     &  Q23)
     &  +LHPM3*DLOGQ8U*(-8*U1P5*T1M1+12*U1P4*T1M1*Q2-8*U1P3*T1
     &  -4*U1P3*Q2-4*U1P2*T1P2+20*U1P2*T1*Q2-4*U1P2*T1M1*Q23+8*
     &  U1P2*Q22+8*U1*T1P2*Q2-16*U1*T1*Q22-4*U1*Q23-4*T1P2*Q22+
     &  4*T1*Q23)
     &  +LHPM3*DLOGQ9U*(-8*U1P5*T1M1+12*U1P4*T1M1*Q2-8*U1P3*T1
     &  -4*U1P3*Q2-4*U1P2*T1P2+20*U1P2*T1*Q2-4*U1P2*T1M1*Q23+8*
     &  U1P2*Q22+8*U1*T1P2*Q2-16*U1*T1*Q22-4*U1*Q23-4*T1P2*Q22+
     &  4*T1*Q23)
     &  +LHPM3*DLOGQ10U*(-8*U1P5*T1M1+12*U1P4*T1M1*Q2-8*U1P3*
     &  T1-4*U1P3*Q2-4*U1P2*T1P2+20*U1P2*T1*Q2-4*U1P2*T1M1*Q23+8*
     &  U1P2*Q22+8*U1*T1P2*Q2-16*U1*T1*Q22-4*U1*Q23-4*T1P2*Q22+
     &  4*T1*Q23)
      VPS(39) =
     &  +LHPM3*DLOGQ11U*(-8*U1P5*T1M1+12*U1P4*T1M1*Q2-8*U1P3*
     &  T1-4*U1P3*Q2-4*U1P2*T1P2+20*U1P2*T1*Q2-4*U1P2*T1M1*Q23+8*
     &  U1P2*Q22+8*U1*T1P2*Q2-16*U1*T1*Q22-4*U1*Q23-4*T1P2*Q22+
     &  4*T1*Q23)
     &  +LHPM3*DLOGQ12U*(8*U1P5*T1M1-12*U1P4*T1M1*Q2+8*U1P3*T1
     &  +4*U1P3*Q2+4*U1P2*T1P2-20*U1P2*T1*Q2+4*U1P2*T1M1*Q23-8*
     &  U1P2*Q22-8*U1*T1P2*Q2+16*U1*T1*Q22+4*U1*Q23+4*T1P2*Q22-
     &  4*T1*Q23)
     &  +LHPM3*DLOGQ13U*(16*U1P5*T1M1-24*U1P4*T1M1*Q2+16*U1P3*T1
     &  +8*U1P3*Q2+8*U1P2*T1P2-40*U1P2*T1*Q2+8*U1P2*T1M1*Q23-16*
     &  U1P2*Q22-16*U1*T1P2*Q2+32*U1*T1*Q22+8*U1*Q23+8*T1P2*Q22
     &  -8*T1*Q23)
     &  +DLOG6*(16*BQED)
     &  +DLOG5*(-16*BQED)
     &  +LOG7X2*(-4*U1P3*SPM2-12*U1P2*T1*SPM2+4*U1P2*Q2*SPM2
     &  -8*U1P2*SPM1-12*U1*T1P2*SPM2+8*U1*T1*Q2*SPM2-16*U1*T1*
     &  SPM1+8*U1*Q2*SPM1-4*T1P3*SPM2+4*T1P2*Q2*SPM2-8*T1P2*SPM1
     &  +8*T1*Q2*SPM1)
      VPS(40) =
     &  +DLOG7*(-16*U1-16*T1+16*Q2)
     &  +DLOG8*(-16*U1-16*T1+16*Q2)
     &  +(8*U1P3*T1M1*UM1-4*U1P2*T1M1*Q2*S1M1-8*U1P2*T1M1+
     &  8*U1P2*S1M1-16*U1P2*SPM1-4*U1*T1*TM1+16*U1*T1*S1M1-32*U1*
     &  T1*SPM1+4*U1*T1M1*Q22*S1M1+6*U1*T1M1*Q2-20*U1*Q2*S1M1-
     &  24*U1+4*U1M1*T1P3*TM1-4*U1M1*T1P2*Q2*S1M1-4*U1M1*T1P2+4*
     &  U1M1*T1*Q22*S1M1+6*U1M1*T1*Q2+8*T1P2*S1M1-16*T1P2*SPM1-
     &  20*T1*Q2*S1M1-28*T1+8*Q22*S1M1+12*Q2+32*BQED*LOGDEL2)
CBH HERE (ABOVE) I REMOVE THE LOGMU DEPENDENCE BY HAND
CBH     &    20*T1*Q2*S1M1-28*T1+8*Q22*S1M1+12*Q2+32*BQED*LOGDEL2-32
CBH     &    *BQED*LOGDEL*LOGMU)
C SUM CONTRIBUTIONS AND MULTIPLY BY COMMON FACTOR:
      SPLUSV = 0.D0
      DO 10 I = 1,40
C           WRITE(6,1000) I,VPS(I)
   10 SPLUSV = SPLUSV + VPS(I)
C
CBH     SVCACF_L = SPLUSV
C DIVIDE BY -8 TO GET NORMALIZATION RIGHT
CBH        VOKL2 = SVCACF_L/-8.0D0
C
 1000 FORMAT('VPS(',I3,')  =  ',D20.10)
CBH      RETURN
CBH      END
CBH SUBTRACT OFF THE OLD SOFT FINITE PIECES
      SPLUSV = SPLUSV - (
     &  SQM * (  - 64*M2*LOGDEL*LOG1 - 32*M2*ZETA2 + 64*M2*LOG1*LOG5
     &  + 64*M2*LOG1*LOG6 - 32*M2*LOG1X2 + 64*M2*DLOG2 + 64*M2*DLOG1 )
     &  + XSQM1 * ( 32*LOGDEL*LOG1 + 16*ZETA2 - 32*LOG1*LOG5
     &  - 32*LOG1*LOG6 + 16*LOG1X2 - 32*DLOG2 - 32*DLOG1 )
     &  - 16*LOG4*LOG3 - 32*LOG4*LOGDEL + 16*LOG4*LOG1 + 8*LOG4X2
     &  + 32*LOG3*LOGDEL - 16*LOG3*LOG1 + 8*LOG3X2 + 32*LOGDEL2
     &  - 24*ZETA2 - 8*LOG1X2 + 16*DLOG6 - 16*DLOG5 )*BQED
CBH ADD ON THE NEW SOFT FINITE PIECES
      SPLUSV = SPLUSV + (
     &  SQM * ( - 64*M2*LI2B - 128*M2*LNB*LOG1 + 32*M2*LOG1*LOG2
     &  - 64*M2*LOG1*LOGSP - 16*M2*LOG1X2 ) + XSQM1 * ( 32*LI2B
     &  + 64*LNB*LOG1 - 16*LOG1*LOG2 + 32*LOG1*LOGSP + 8*LOG1X2 )
     &  + 16*LIT1 - 16*LIT2 + 16*LIU1 - 16*LIU2 + 64*LNB*LOG3
     &  + 64*LNB*LOG4 + 128*LNBX2 - 8*LOG1X2 - 16*LOG2*LOG3 - 24*ZETA2
     &  - 16*LOG2*LOG4 + 32*LOG2*LOGSP - 8*LOG2X2 + 32*LOG3*LOGSP
     &  + 32*LOG4*LOGSP - 32*LOGSPX2 + 8*LNBTX2 + 8*LNBUX2 )*BQED
CBH SWITCH Q2 BACK TO POSITIVE
      Q2 = QTMP
CBH GET THE NORMALIZATION CORRECT
      VOKL2 = -4.D0*Q2*SPLUSV/(SP*SP)
      RETURN
      END
CBH      DOUBLE PRECISION FUNCTION VQEDGAM2(SP,T1,U1,M2,Q2,DEL,S4MAX,S4,MU)
      DOUBLE PRECISION FUNCTION VQEDG2(T1,SP,M2,Q2,RHOTILDE)
C
C HERE WE COMPUTE THE EXPRESSION FOR THE CF*CF PART OF THE
C SOFT PLUS VIRTUAL MATRIX ELEMENT.
C
      IMPLICIT DOUBLE PRECISION (A-Z)
      INTEGER I
      DIMENSION VPS(77)
      PARAMETER( PI = 3.14159265359D0 )
      DATA ZETA2/1.644934066848226D+00/
C
CSR      LOGDEL = DLOG(DEL/M2)
CSR      LOGDEL2 = LOGDEL*LOGDEL
C HERE WE REPLACE THE LOGDEL TERMS BY INTEGRALS OVER S4
CBH OH NO WE DON'T
CBH        DIST = S4MAX - DEL
CBH        L11 = DLOG(S4/M2)
CBH        L12 = DLOG(S4MAX/M2)
CBH        LOGDEL = L12 - DIST/S4
CBH        LOGDEL2 = L12*L12 -2.0D0*DIST*L11/S4
C
CBH WE REPLACE LOG(DEL/M2) = ARBITRARY
CBH SINCE WE SUBTRACT IT OFF LATER ANYHOW
      LOGDEL = -0.1D0
      LOGDEL2 = LOGDEL*LOGDEL
CBH NOW THE NEW SOFT PARAMETER
      LNB = 0.5D0*DLOG(1.D0-RHOTILDE)
      LNBX2 = LNB*LNB
CBH THE Q2 COMING INTO THE ROUTINE IS POSITIVE
CBH BUT IN THIS ROUTINE THE Q2 SHOULD BE NEGATIVE
CBH SO WE CHANGE THE SIGN HERE
      QTMP = Q2
      Q2 = -QTMP
CBH
      S = SP + Q2
      U1 = -SP-T1
CBH THERE IS NO LOGMU DEPENDENCE IN THE CF*CF PIECE
CSR      MU2 = M2
CBH      MU2 = MU*MU
CBH      CEP = 1.D0/16.D0/PI/PI
      S1 = 4.0D0*M2 -S
      S1M1 = 1.D0/S1
      T = T1+M2
      U = U1+M2
      XSQ = DSQRT(1.0D0 - 4.0D0*M2/S)
      YSQ = DSQRT(1.0D0 - 4.0D0*M2/Q2)
      X = (1.D0 - XSQ)/(1.D0 + XSQ)
      SQ = S*XSQ
      SQM = 1.D0/SQ
      SP = S - Q2
      Y = (1.D0-YSQ)/(1.D0+YSQ)
      X1 = (1.D0+YSQ)/2.D0
      X2 = 1.0D0 - X1
      AA = DSQRT(4.D0*M2 -Q2)
      AA2 = 4.D0*M2 -Q2
      BB = DSQRT(-Q2)
      CC = DSQRT(4.D0*M2*Q2/S - Q2)
      LAT = T*T + M2*M2 + Q2*Q2 - 2.D0*T*M2 - 2.D0*T*Q2 - 2*M2*Q2
      LAU = U*U + M2*M2 + Q2*Q2 - 2.D0*U*M2 - 2.D0*U*Q2 - 2*M2*Q2
      LH = DSQRT(LAT)
      LHP = DSQRT(LAU)
      LOG1 = DLOG(X)
      LOG2 = DLOG(S/M2)
CBH
      LOG1X2 = LOG1*LOG1
      LOG2X2 = LOG2*LOG2
      LOGSP = DLOG(SP/M2)
      LOGSPX2 = LOGSP*LOGSP
CBH
      LOG3 = DLOG(-T1/M2)
      LOG3X2 = LOG3*LOG3
      LOG4 = DLOG(-U1/M2)
      LOG4X2 = LOG4*LOG4
      LOG5 = DLOG(1.D0-X)
      LOG6 = DLOG(1.D0+X)
      LOG7 = DLOG(-Y)
      LOG7X2 = LOG7*LOG7
      LOG8 = DLOG(-Q2/S)
      LOG9 = DLOG(X1)
      LOG10 = DLOG(-X2)
CBH      LOGMU = DLOG(MU2/M2)
      LOGQ1 = DLOG((AA+CC)*(AA+CC)/4.D0/M2)
      LOGQ2 = DLOG((AA-BB)/(AA+BB))
      LOGQ3 = DLOG((AA-CC)/(AA-BB))
      LOGQ3X2 = LOGQ3*LOGQ3
      DLOG1 = DILOG(-X)
      DLOG2 = DILOG(X)
      DLOG3 = DILOG(T1/M2 + 1.D0)
      DLOG4 = DILOG(U1/M2 + 1.D0)
      DLOG5 = DILOG(1.D0-U1/X/T1)
      DLOG6 = DILOG(1.D0-T1/X/U1)
      DLOG7 = DILOG(Q2*X1/M2)
      DLOG8 = DILOG(Q2*X2/M2)
      DLOGQ1 = DILOG((AA-BB)/(AA-CC))
      DLOGQ2 = DILOG((AA-CC)/(AA+BB))
      DLOGQ3 = DILOG((BB+CC)/(AA+CC))
      DLOGQ4 = DILOG((CC-BB)/(AA+CC))
      DLOGQ5 = DILOG(S/SP)
      DLOGQ6T = DILOG((T1+AA2+LH)/(T1-YSQ*(LH+Q2*YSQ)))
      DLOGQ6U = DILOG((U1+AA2+LHP)/(U1-YSQ*(LHP+Q2*YSQ)))
      DLOGQ7T = DILOG((T1+AA2+LH)/(T1+YSQ*(LH-Q2*YSQ)))
      DLOGQ7U = DILOG((U1+AA2+LHP)/(U1+YSQ*(LHP-Q2*YSQ)))
      DLOGQ8T = DILOG((T1+AA2-LH)/(T1-YSQ*(LH+Q2*YSQ)))
      DLOGQ8U = DILOG((U1+AA2-LHP)/(U1-YSQ*(LHP+Q2*YSQ)))
      DLOGQ9T = DILOG((T1+AA2-LH)/(T1+YSQ*(LH-Q2*YSQ)))
      DLOGQ9U = DILOG((U1+AA2-LHP)/(U1+YSQ*(LHP-Q2*YSQ)))
      DLOGQ10T = DILOG( (T1*(Q2 - T - M2 - LH) - 2.D0*M2*LH)/
     &     (T1*(Q2 - T - M2 + LH)))
      DLOGQ10U = DILOG( (U1*(Q2 - U - M2 - LHP) - 2.D0*M2*LHP)/
     &     (U1*(Q2 - U - M2 + LHP)))
      DLOGQ11T = DILOG( (T1*(Q2 - T - M2 - LH) - 2.D0*M2*LH)/
     &     (T1*(Q2 - T - M2 - LH)))
      DLOGQ11U = DILOG( (U1*(Q2 - U - M2 - LHP) - 2.D0*M2*LHP)/
     &     (U1*(Q2 - U - M2 - LHP)))
      DLOGQ12T = DILOG( (Q2 - T - M2 + LH)/(Q2 - T - M2 - LH))
      DLOGQ12U = DILOG( (Q2 - U - M2 + LHP)/(Q2 - U - M2 - LHP))
      DLOGQ13T = DILOG( (M2 - T - LH)/(M2 - T))
      DLOGQ13U = DILOG( (M2 - U - LHP)/(M2 - U))
C MORE USEFUL DEFINITIONS:
      M22 = M2*M2
      M23 = M2*M22
      M24 = M22*M22
      T1P2 = T1*T1
      T1P3 = T1*T1P2
      T1P4 = T1*T1P3
      T1P5 = T1*T1P4
      T1P6 = T1*T1P5
      T1M1 = 1.D0/T1
      T1M2 = T1M1*T1M1
      T1M3 = T1M2*T1M1
      U1P2 = U1*U1
      U1P3 = U1*U1P2
      U1P4 = U1*U1P3
      U1P5 = U1*U1P4
      U1P6 = U1*U1P5
      U1M1 = 1.D0/U1
      U1M2 = U1M1*U1M1
      U1M3 = U1M1*U1M2
      UM1 = 1.D0/U
      UM2 = UM1*UM1
      TM1 = 1.D0/T
      TM2 = TM1*TM1
      Q22 = Q2*Q2
      Q23 = Q2*Q22
      Q24 = Q22*Q22
      Q25 = Q22*Q23
      TB = T1M1*U1M1
      SM1 = 1.D0/S
      SM2 = SM1*SM1
      SM3 = SM1*SM2
      SQM1 = 1.D0/SQ
      SPM1 = 1.D0/SP
      SPM2 = SPM1*SPM1
      SPM3 = SPM1*SPM2
      SPM4 = SPM2*SPM2
      LHM1 = 1.D0/LH
      LHM2 = LHM1*LHM1
      LHM3 = LHM1*LHM2
      LHM4 = LHM2*LHM2
      LHM5 = LHM2*LHM3
      LHPM1 = 1.D0/LHP
      LHPM2 = LHPM1*LHPM1
      LHPM3 = LHPM1*LHPM2
      LHPM4 = LHPM2*LHPM2
      LHPM5 = LHPM2*LHPM3
      XSQM1 = 1.D0/XSQ
CBH      LOG1X2 = LOG1*LOG1
CBH
      ONEMBETA = 1.D0 - XSQ
      ONEMBETAM1 = 1.D0/ONEMBETA
      ONEPBETA = 1.D0 + XSQ
      ONEPBETAM1 = 1.D0/ONEPBETA
CBH
      LI2B = DILOG(2.D0*XSQ*ONEPBETAM1)
      LIT1 = DILOG(1.D0+2.D0*T1*SPM1*ONEMBETAM1)
      LIU1 = DILOG(1.D0+2.D0*U1*SPM1*ONEMBETAM1)
      LIT2 = DILOG(1.D0+0.5D0*SP*ONEPBETA*T1M1)
      LIU2 = DILOG(1.D0+0.5D0*SP*ONEPBETA*U1M1)
      LNBT = DLOG(-0.5D0*SP*T1M1*ONEMBETA)
      LNBTX2 = LNBT*LNBT
      LNBU = DLOG(-0.5D0*SP*U1M1*ONEMBETA)
      LNBUX2 = LNBU*LNBU
CBH
      BQED =
     &  (( -4*(T1 + U1)**2*M22 - 2*M2*( Q2*( T1P2 + U1P2)
     &  + 2*T1*U1*(T1 + U1)) + T1*U1*(T1P2 + U1P2 -
     &  2*Q2*(T1 + U1) + 2* Q22)) *T1M2*U1M2 )
      MQED =
     &  (   M2*(U1*T1M2 + T1*U1M2 - U1M1 - T1M1
     &  -3*Q2*(T1M2 + U1M2) + 2*Q22*(U1M1*T1M2 + T1M1*U1M2)
     &  -8*M2*(Q2/2.D0*(T1M3+U1M3)+U1M1*T1M1 + T1M2 + U1M2)
     &  -8*M22*(T1M3 + U1M3 + U1M1*T1M2 + T1M1*U1M2)))
C
C HERE IS THE MATRIX ELEMENT.
C
      VPS(1) =
     &  +M24*LOG3*LHM4*(-512*U1M1*T1*TM1*Q2-512*TM1*Q2)
     &  +M24*LOG4*LHPM4*(-512*U1*T1M1*UM1*Q2-512*UM1*Q2)
     &  +M24*ZETA2*LHM5*(-512*U1M1*T1*Q2-512*Q2)
     &  +M24*ZETA2*LHPM5*(-512*U1*T1M1*Q2-512*Q2)
     &  +M24*LHM5*DLOGQ6T*(512*U1M1*T1*Q2+512*Q2)
     &  +M24*LHM5*DLOGQ7T*(512*U1M1*T1*Q2+512*Q2)
     &  +M24*LHM5*DLOGQ8T*(-512*U1M1*T1*Q2-512*Q2)
     &  +M24*LHM5*DLOGQ9T*(-512*U1M1*T1*Q2-512*Q2)
     &  +M24*LHM5*DLOGQ10T*(-512*U1M1*T1*Q2-512*Q2)
     &  +M24*LHM5*DLOGQ11T*(-512*U1M1*T1*Q2-512*Q2)
     &  +M24*LHM5*DLOGQ12T*(512*U1M1*T1*Q2+512*Q2)
     &  +M24*LHM5*DLOGQ13T*(1024*U1M1*T1*Q2+1024*Q2)
     &  +M24*LHPM5*DLOGQ6U*(512*U1*T1M1*Q2+512*Q2)
     &  +M24*LHPM5*DLOGQ7U*(512*U1*T1M1*Q2+512*Q2)
     &  +M24*LHPM5*DLOGQ8U*(-512*U1*T1M1*Q2-512*Q2)
     &  +M24*LHPM5*DLOGQ9U*(-512*U1*T1M1*Q2-512*Q2)
     &  +M24*LHPM5*DLOGQ10U*(-512*U1*T1M1*Q2-512*Q2)
      VPS(2) =
     &  +M24*LHPM5*DLOGQ11U*(-512*U1*T1M1*Q2-512*Q2)
     &  +M24*LHPM5*DLOGQ12U*(512*U1*T1M1*Q2+512*Q2)
     &  +M24*LHPM5*DLOGQ13U*(1024*U1*T1M1*Q2+1024*Q2)
     &  +M23*LOG1*LOG5*SQM*(1024*TB+512*U1M2+512*
     &  T1M2)
     &  +M23*LOG1*LOG6*SQM*(-1024*TB-512*U1M2-512*
     &  T1M2)
     &  +M23*LOG1*LOG3*SQM*(512*TB+512*T1M2)
     &  +M23*LOG1*LOG4*SQM*(512*TB+512*U1M2)
     &  +M23*LOG1*SQM*LOGQ1*(-512*TB-256*U1M2-256*
     &  T1M2)
     &  +M23*LOG3*LHM2*(-128*U1M1*T1P2*TM2-384*U1M1*T1*TM1-
     &  128*U1M1*T1*TM2*Q2-128*T1*TM2-384*TM1-128*TM2*Q2)
     &  +M23*LOG3*LHM4*(128*U1M1*T1P3*TM1-1024*U1M1*T1P2*TM1*Q2
     &  +128*U1M1*T1*TM1*Q22+128*T1P2*TM1-1280*T1*TM1*Q2-128*
     &  TM1*Q22)
     &  +M23*LOG3*(128*U1M1*TM2+128*T1M1*TM2)
      VPS(3) =
     &  +M23*LOG4*LHPM2*(-128*U1P2*T1M1*UM2-384*U1*T1M1*UM1
     &  -128*U1*T1M1*UM2*Q2-128*U1*UM2-384*UM1-128*UM2*Q2)
     &  +M23*LOG4*LHPM4*(128*U1P3*T1M1*UM1-1024*U1P2*T1M1*UM1*
     &  Q2+128*U1P2*UM1+128*U1*T1M1*UM1*Q22-1280*U1*UM1*Q2-128*
     &  UM1*Q22)
     &  +M23*LOG4*(128*U1M1*UM2+128*T1M1*UM2)
     &  +M23*DLOG2*SQM*(1024*TB+512*U1M2+512*T1M2)
     &  +M23*DLOG1*SQM*(-1024*TB-512*U1M2-512*
     &  T1M2)
     &  +M23*ZETA2*SQM*(3584*TB+1792*U1M2+1792*
     &  T1M2)
     &  +M23*ZETA2*LHM1*(256*TB+256*T1M2)
     &  +M23*ZETA2*LHM3*(-384-384*U1M1*T1+512*U1M1*Q2+512*
     &  T1M1*Q2)
     &  +M23*ZETA2*LHM5*(128*U1M1*T1P3-256*U1M1*T1P2*Q2-640*
     &  U1M1*T1*Q22+128*T1P2-512*T1*Q2-896*Q22)
     &  +M23*ZETA2*LHPM1*(256*TB+256*U1M2)
      VPS(4) =
     &  +M23*ZETA2*LHPM3*(-384-384*U1*T1M1+512*U1M1*Q2+512
     &  *T1M1*Q2)
     &  +M23*ZETA2*LHPM5*(128*U1P3*T1M1-256*U1P2*T1M1*Q2+128*
     &  U1P2-640*U1*T1M1*Q22-512*U1*Q2-896*Q22)
     &  +M23*SQM*LOG8*LOGQ2*(-512*TB-256*U1M2-256*
     &  T1M2)
     &  +M23*SQM*DLOGQ1*(-1024*TB-512*U1M2-512*
     &  T1M2)
     &  +M23*SQM*DLOGQ2*(-1024*TB-512*U1M2-512*
     &  T1M2)
     &  +M23*SQM*DLOGQ3*(-1024*TB-512*U1M2-512*
     &  T1M2)
     &  +M23*SQM*DLOGQ4*(1024*TB+512*U1M2+512*T1M2)
     &  +M23*SQM*LOGQ3X2*(-512*TB-256*U1M2-256*
     &  T1M2)
     &  +M23*LOG9*LHM2*(768*TB*Q2*X1-768*TB*Q2*
     &  X2+768*T1M2*Q2*X1-768*T1M2*Q2*X2)
      VPS(5) =
     &  +M23*LOG9*LHM4*(768*U1M1*T1*Q2*X1-768*U1M1*T1*Q2*X2-
     &  768*U1M1*Q22*X1+768*U1M1*Q22*X2-768*T1M1*Q22*X1+768*T1M1
     &  *Q22*X2+768*Q2*X1-768*Q2*X2)
     &  +M23*LOG9*LHPM2*(768*TB*Q2*X1-768*TB*Q2*
     &  X2+768*U1M2*Q2*X1-768*U1M2*Q2*X2)
     &  +M23*LOG9*LHPM4*(768*U1*T1M1*Q2*X1-768*U1*T1M1*Q2*X2-
     &  768*U1M1*Q22*X1+768*U1M1*Q22*X2-768*T1M1*Q22*X1+768*T1M1
     &  *Q22*X2+768*Q2*X1-768*Q2*X2)
     &  +M23*LOG10*LHM2*(-768*TB*Q2*X1+768*TB*
     &  Q2*X2-768*T1M2*Q2*X1+768*T1M2*Q2*X2)
     &  +M23*LOG10*LHM4*(-768*U1M1*T1*Q2*X1+768*U1M1*T1*Q2*X2
     &  +768*U1M1*Q22*X1-768*U1M1*Q22*X2+768*T1M1*Q22*X1-768*
     &  T1M1*Q22*X2-768*Q2*X1+768*Q2*X2)
     &  +M23*LOG10*LHPM2*(-768*TB*Q2*X1+768*TB
     &  *Q2*X2-768*U1M2*Q2*X1+768*U1M2*Q2*X2)
     &  +M23*LOG10*LHPM4*(-768*U1*T1M1*Q2*X1+768*U1*T1M1*Q2*X2
     &  +768*U1M1*Q22*X1-768*U1M1*Q22*X2+768*T1M1*Q22*X1-768*
     &  T1M1*Q22*X2-768*Q2*X1+768*Q2*X2)
      VPS(6) =
     &  +M23*LHM1*DLOGQ6T*(-256*TB-256*T1M2)
     &  +M23*LHM1*DLOGQ7T*(-256*TB-256*T1M2)
     &  +M23*LHM1*DLOGQ8T*(256*TB+256*T1M2)
     &  +M23*LHM1*DLOGQ9T*(256*TB+256*T1M2)
     &  +M23*LHM1*DLOGQ10T*(256*TB+256*T1M2)
     &  +M23*LHM1*DLOGQ11T*(256*TB+256*T1M2)
     &  +M23*LHM1*DLOGQ12T*(-256*TB-256*T1M2)
     &  +M23*LHM1*DLOGQ13T*(-512*TB-512*T1M2)
     &  +M23*LHM2*(128*U1M1*T1*TM1+128*U1M1*TM1*Q2+128*T1M1
     &  *TM1*Q2+128*TM1)
     &  +M23*LHM3*DLOGQ6T*(384+384*U1M1*T1-512*U1M1*Q2-512*
     &  T1M1*Q2)
     &  +M23*LHM3*DLOGQ7T*(384+384*U1M1*T1-512*U1M1*Q2-512*
     &  T1M1*Q2)
     &  +M23*LHM3*DLOGQ8T*(-384-384*U1M1*T1+512*U1M1*Q2+512*
     &  T1M1*Q2)
     &  +M23*LHM3*DLOGQ9T*(-384-384*U1M1*T1+512*U1M1*Q2+512*
     &  T1M1*Q2)
      VPS(7) =
     &  +M23*LHM3*DLOGQ10T*(-384-384*U1M1*T1+512*U1M1*Q2+512
     &  *T1M1*Q2)
     &  +M23*LHM3*DLOGQ11T*(-384-384*U1M1*T1+512*U1M1*Q2+512
     &  *T1M1*Q2)
     &  +M23*LHM3*DLOGQ12T*(384+384*U1M1*T1-512*U1M1*Q2-512*
     &  T1M1*Q2)
     &  +M23*LHM3*DLOGQ13T*(768+768*U1M1*T1-1024*U1M1*Q2-1024*
     &  T1M1*Q2)
     &  +M23*LHM5*DLOGQ6T*(-128*U1M1*T1P3+256*U1M1*T1P2*Q2+640
     &  *U1M1*T1*Q22-128*T1P2+512*T1*Q2+896*Q22)
     &  +M23*LHM5*DLOGQ7T*(-128*U1M1*T1P3+256*U1M1*T1P2*Q2+640
     &  *U1M1*T1*Q22-128*T1P2+512*T1*Q2+896*Q22)
     &  +M23*LHM5*DLOGQ8T*(128*U1M1*T1P3-256*U1M1*T1P2*Q2-640*
     &  U1M1*T1*Q22+128*T1P2-512*T1*Q2-896*Q22)
     &  +M23*LHM5*DLOGQ9T*(128*U1M1*T1P3-256*U1M1*T1P2*Q2-640*
     &  U1M1*T1*Q22+128*T1P2-512*T1*Q2-896*Q22)
     &  +M23*LHM5*DLOGQ10T*(128*U1M1*T1P3-256*U1M1*T1P2*Q2-640*
     &  U1M1*T1*Q22+128*T1P2-512*T1*Q2-896*Q22)
      VPS(8) =
     &  +M23*LHM5*DLOGQ11T*(128*U1M1*T1P3-256*U1M1*T1P2*Q2-640*
     &  U1M1*T1*Q22+128*T1P2-512*T1*Q2-896*Q22)
     &  +M23*LHM5*DLOGQ12T*(-128*U1M1*T1P3+256*U1M1*T1P2*Q2+
     &  640*U1M1*T1*Q22-128*T1P2+512*T1*Q2+896*Q22)
     &  +M23*LHM5*DLOGQ13T*(-256*U1M1*T1P3+512*U1M1*T1P2*Q2+
     &  1280*U1M1*T1*Q22-256*T1P2+1024*T1*Q2+1792*Q22)
     &  +M23*LHPM1*DLOGQ6U*(-256*TB-256*U1M2)
     &  +M23*LHPM1*DLOGQ7U*(-256*TB-256*U1M2)
     &  +M23*LHPM1*DLOGQ8U*(256*TB+256*U1M2)
     &  +M23*LHPM1*DLOGQ9U*(256*TB+256*U1M2)
     &  +M23*LHPM1*DLOGQ10U*(256*TB+256*U1M2)
     &  +M23*LHPM1*DLOGQ11U*(256*TB+256*U1M2)
     &  +M23*LHPM1*DLOGQ12U*(-256*TB-256*U1M2)
     &  +M23*LHPM1*DLOGQ13U*(-512*TB-512*U1M2)
     &  +M23*LHPM2*(128*U1*T1M1*UM1+128*U1M1*UM1*Q2+128*
     &  T1M1*UM1*Q2+128*UM1)
     &  +M23*LHPM3*DLOGQ6U*(384+384*U1*T1M1-512*U1M1*Q2-512*
     &  T1M1*Q2)
      VPS(9) =
     &  +M23*LHPM3*DLOGQ7U*(384+384*U1*T1M1-512*U1M1*Q2-512*
     &  T1M1*Q2)
     &  +M23*LHPM3*DLOGQ8U*(-384-384*U1*T1M1+512*U1M1*Q2+512
     &  *T1M1*Q2)
     &  +M23*LHPM3*DLOGQ9U*(-384-384*U1*T1M1+512*U1M1*Q2+512
     &  *T1M1*Q2)
     &  +M23*LHPM3*DLOGQ10U*(-384-384*U1*T1M1+512*U1M1*Q2+
     &  512*T1M1*Q2)
     &  +M23*LHPM3*DLOGQ11U*(-384-384*U1*T1M1+512*U1M1*Q2+
     &  512*T1M1*Q2)
     &  +M23*LHPM3*DLOGQ12U*(384+384*U1*T1M1-512*U1M1*Q2-512*
     &  T1M1*Q2)
     &  +M23*LHPM3*DLOGQ13U*(768+768*U1*T1M1-1024*U1M1*Q2-1024
     &  *T1M1*Q2)
     &  +M23*LHPM5*DLOGQ6U*(-128*U1P3*T1M1+256*U1P2*T1M1*Q2-
     &  128*U1P2+640*U1*T1M1*Q22+512*U1*Q2+896*Q22)
     &  +M23*LHPM5*DLOGQ7U*(-128*U1P3*T1M1+256*U1P2*T1M1*Q2-
     &  128*U1P2+640*U1*T1M1*Q22+512*U1*Q2+896*Q22)
      VPS(10) =
     &  +M23*LHPM5*DLOGQ8U*(128*U1P3*T1M1-256*U1P2*T1M1*Q2+128*
     &  U1P2-640*U1*T1M1*Q22-512*U1*Q2-896*Q22)
     &  +M23*LHPM5*DLOGQ9U*(128*U1P3*T1M1-256*U1P2*T1M1*Q2+128*
     &  U1P2-640*U1*T1M1*Q22-512*U1*Q2-896*Q22)
     &  +M23*LHPM5*DLOGQ10U*(128*U1P3*T1M1-256*U1P2*T1M1*Q2+128*
     &  U1P2-640*U1*T1M1*Q22-512*U1*Q2-896*Q22)
     &  +M23*LHPM5*DLOGQ11U*(128*U1P3*T1M1-256*U1P2*T1M1*Q2+128*
     &  U1P2-640*U1*T1M1*Q22-512*U1*Q2-896*Q22)
     &  +M23*LHPM5*DLOGQ12U*(-128*U1P3*T1M1+256*U1P2*T1M1*Q2-
     &  128*U1P2+640*U1*T1M1*Q22+512*U1*Q2+896*Q22)
     &  +M23*LHPM5*DLOGQ13U*(-256*U1P3*T1M1+512*U1P2*T1M1*Q2-
     &  256*U1P2+1280*U1*T1M1*Q22+1024*U1*Q2+1792*Q22)
     &  +M23* (-160*TB*UM1-160*TB*TM1+64*
     &  U1M1*T1M2*TM1*Q2-512*U1M1*T1M2+64*U1M2*T1M1*UM1*Q2-512*
     &  U1M2*T1M1-128*U1M2*UM1+64*U1M3*UM1*Q2-512*U1M3-128*
     &  T1M2*TM1+64*T1M3*TM1*Q2-512*T1M3)
     &  +M22*LOG1X2*SQM*(64*U1M1+64*T1M1)
      VPS(11) =
     &  +M22*LOG1X2*(64*U1M1*SPM1+64*T1M1*SPM1)
     &  +M22*LOG1*LOG5*SQM*(256*U1*T1M2-512*TB*Q2+
     &  1280*U1M1+256*U1M2*T1+1280*T1M1)
     &  +M22*LOG1*LOG6*SQM*(-256*U1*T1M2+512*TB*Q2
     &  -1536*U1M1-256*U1M2*T1-1536*T1M1)
     &  +M22*LOG1*LOG3*SQM*(256*U1*T1M2-256*TB*Q2+768
     &  *U1M1+768*T1M1)
     &  +M22*LOG1*LOG4*SQM*(-256*TB*Q2+768*U1M1+256
     &  *U1M2*T1+768*T1M1)
     &  +M22*LOG1*SQM*LOGQ1*(-128*U1*T1M2+256*TB*Q2
     &  -768*U1M1-128*U1M2*T1-768*T1M1)
     &  +M22*LOG1*SQM*(512*U1*T1M1*Q2*SPM2-256*U1*T1M1*SPM1
     &  +512*U1M1*T1*Q2*SPM2-256*U1M1*T1*SPM1+768*U1M1*Q2*SPM1-
     &  256*U1M1+768*T1M1*Q2*SPM1-256*T1M1+1024*Q2*SPM2-512*
     &  SPM1)
      VPS(12) =
     &  +M22*LOG3*LHM2*(64*U1*TM1-256*U1M1*T1P3*TM2-256*U1M1*
     &  T1P2*TM1-192*U1M1*T1P2*TM2*Q2+64*U1M1*T1*TM1*Q2+64*U1M1*
     &  T1*TM2*Q22-320*T1P2*TM2-384*T1*TM1-320*T1*TM2*Q2-128*
     &  TM1*Q2)
     &  +M22*LOG3*LHM4*(-96*U1*T1P2*TM1+480*U1*T1*TM1*Q2+96*
     &  U1M1*T1P4*TM1-480*U1M1*T1P3*TM1*Q2-64*U1M1*T1P2*TM1*Q22+
     &  128*U1M1*T1*TM1*Q23+64*T1P3*TM1-192*T1P2*TM1*Q2-512*T1*
     &  TM1*Q22+64*TM1*Q23)
     &  +M22*LOG3*(-32*U1*T1M2*TM1+192*U1M1*T1*TM2-160*U1M1
     &  *TM1-192*T1M1*TM1+64*T1M1*TM2*Q2+320*TM2)
     &  +M22*LOG4*LHPM2*(-256*U1P3*T1M1*UM2-256*U1P2*T1M1*UM1
     &  -192*U1P2*T1M1*UM2*Q2-320*U1P2*UM2+64*U1*T1M1*UM1*Q2+64*
     &  U1*T1M1*UM2*Q22-384*U1*UM1-320*U1*UM2*Q2+64*T1*UM1-128*
     &  UM1*Q2)
     &  +M22*LOG4*LHPM4*(96*U1P4*T1M1*UM1-480*U1P3*T1M1*UM1*Q2
     &  +64*U1P3*UM1-96*U1P2*T1*UM1-64*U1P2*T1M1*UM1*Q22-192*
     &  U1P2*UM1*Q2+480*U1*T1*UM1*Q2+128*U1*T1M1*UM1*Q23-512*U1*
     &  UM1*Q22+64*UM1*Q23)
      VPS(13) =
     &  +M22*LOG4*(192*U1*T1M1*UM2-192*U1M1*UM1+64*U1M1*UM2*
     &  Q2-32*U1M2*T1*UM1-160*T1M1*UM1+320*UM2)
     &  +M22*DLOG2*SQM*(256*U1*T1M2-512*TB*Q2+1280*
     &  U1M1+256*U1M2*T1+1280*T1M1)
     &  +M22*DLOG3*(-32*U1*T1M3+96*TB-64*T1M2)
     &  +M22*DLOG4*(96*TB-64*U1M2-32*U1M3*T1)
     &  +M22*DLOG1*SQM*(-256*U1*T1M2+512*TB*Q2-
     &  1536*U1M1-256*U1M2*T1-1536*T1M1)
     &  +M22*ZETA2*SQM*(896*U1*T1M2-1792*TB*Q2+4864
     &  *U1M1+896*U1M2*T1+4864*T1M1)
     &  +M22*ZETA2*LHM1*(-128*TB*Q2+384*U1M1+384*
     &  T1M1)
     &  +M22*ZETA2*LHM3*(64*U1-192*U1M1*T1P2+128*U1M1*Q22-
     &  320*T1+384*T1M1*Q22+64*Q2)
     &  +M22*ZETA2*LHM5*(-96*U1*T1P2+480*U1*T1*Q2-96*U1M1*
     &  T1P4+864*U1M1*T1P3*Q2-1536*U1M1*T1P2*Q22+960*U1M1*T1*Q23
     &  -128*T1P3+1536*T1P2*Q2-1984*T1*Q22+512*Q23)
      VPS(14) =
     &  +M22*ZETA2*LHPM1*(-128*TB*Q2+384*U1M1+384*
     &  T1M1)
     &  +M22*ZETA2*LHPM3*(-192*U1P2*T1M1-320*U1+384*U1M1*
     &  Q22+64*T1+128*T1M1*Q22+64*Q2)
     &  +M22*ZETA2*LHPM5*(-96*U1P4*T1M1+864*U1P3*T1M1*Q2-128
     &  *U1P3-96*U1P2*T1-1536*U1P2*T1M1*Q22+1536*U1P2*Q2+480*U1*T1*
     &  Q2+960*U1*T1M1*Q23-1984*U1*Q22+512*Q23)
     &  +M22*ZETA2*(32*U1*T1M3-192*TB-384*U1M1*SPM1
     &  +64*U1M2+32*U1M3*T1-384*T1M1*SPM1+64*T1M2)
     &  +M22*SQM*LOG8*LOGQ2*(-128*U1*T1M2+256*TB*Q2
     &  -768*U1M1-128*U1M2*T1-768*T1M1)
     &  +M22*SQM*DLOGQ1*(-256*U1*T1M2+512*TB*Q2-
     &  1536*U1M1-256*U1M2*T1-1536*T1M1)
     &  +M22*SQM*DLOGQ2*(-256*U1*T1M2+512*TB*Q2-
     &  1536*U1M1-256*U1M2*T1-1536*T1M1)
     &  +M22*SQM*DLOGQ3*(-256*U1*T1M2+512*TB*Q2-
     &  1536*U1M1-256*U1M2*T1-1536*T1M1)
      VPS(15)=
     &  +M22*SQM*DLOGQ4*(256*U1*T1M2-512*TB*Q2+1536*
     &  U1M1+256*U1M2*T1+1536*T1M1)
     &  +M22*SQM*LOGQ3X2*(-128*U1*T1M2+256*TB*Q2-
     &  768*U1M1-128*U1M2*T1-768*T1M1)
     &  +M22*LOG9*LHM2*(128*U1M1*T1*X1-128*U1M1*T1*X2-192*
     &  TB*Q22*X1+192*TB*Q22*X2+448*U1M1*Q2*X1-448
     &  *U1M1*Q2*X2+832*T1M1*Q2*X1-832*T1M1*Q2*X2+192*T1M2*Q22*X1
     &  -192*T1M2*Q22*X2+128*X1-128*X2)
     &  +M22*LOG9*LHM4*(-192*U1M1*T1P3*X1+192*U1M1*T1P3*X2+
     &  1344*U1M1*T1P2*Q2*X1-1344*U1M1*T1P2*Q2*X2-1472*U1M1*T1*Q22*X1
     &  +1472*U1M1*T1*Q22*X2+832*U1M1*Q23*X1-832*U1M1*Q23*X2-
     &  192*T1P2*X1+192*T1P2*X2+1728*T1*Q2*X1-1728*T1*Q2*X2+448*T1M1
     &  *Q23*X1-448*T1M1*Q23*X2-1472*Q22*X1+1472*Q22*X2)
     &  +M22*LOG9*LHPM2*(128*U1*T1M1*X1-128*U1*T1M1*X2-192*
     &  TB*Q22*X1+192*TB*Q22*X2+832*U1M1*Q2*X1-832
     &  *U1M1*Q2*X2+192*U1M2*Q22*X1-192*U1M2*Q22*X2+448*T1M1*Q2*
     &  X1-448*T1M1*Q2*X2+128*X1-128*X2)
      VPS(16) =
     &  +M22*LOG9*LHPM4*(-192*U1P3*T1M1*X1+192*U1P3*T1M1*X2+
     &  1344*U1P2*T1M1*Q2*X1-1344*U1P2*T1M1*Q2*X2-192*U1P2*X1+192*
     &  U1P2*X2-1472*U1*T1M1*Q22*X1+1472*U1*T1M1*Q22*X2+1728*U1*Q2*
     &  X1-1728*U1*Q2*X2+448*U1M1*Q23*X1-448*U1M1*Q23*X2+832*
     &  T1M1*Q23*X1-832*T1M1*Q23*X2-1472*Q22*X1+1472*Q22*X2)
     &  +M22*LOG9*(128*TB*X1-128*TB*X2+64*U1M2
     &  *X1-64*U1M2*X2+64*T1M2*X1-64*T1M2*X2)
     &  +M22*LOG10*LHM2*(-128*U1M1*T1*X1+128*U1M1*T1*X2+192*
     &  TB*Q22*X1-192*TB*Q22*X2-448*U1M1*Q2*X1+448
     &  *U1M1*Q2*X2-832*T1M1*Q2*X1+832*T1M1*Q2*X2-192*T1M2*Q22*X1
     &  +192*T1M2*Q22*X2-128*X1+128*X2)
     &  +M22*LOG10*LHM4*(192*U1M1*T1P3*X1-192*U1M1*T1P3*X2-
     &  1344*U1M1*T1P2*Q2*X1+1344*U1M1*T1P2*Q2*X2+1472*U1M1*T1*Q22*X1
     &  -1472*U1M1*T1*Q22*X2-832*U1M1*Q23*X1+832*U1M1*Q23*X2+
     &  192*T1P2*X1-192*T1P2*X2-1728*T1*Q2*X1+1728*T1*Q2*X2-448*T1M1
     &  *Q23*X1+448*T1M1*Q23*X2+1472*Q22*X1-1472*Q22*X2)
      VPS(17) =
     &  +M22*LOG10*LHPM2*(-128*U1*T1M1*X1+128*U1*T1M1*X2+192
     &  *TB*Q22*X1-192*TB*Q22*X2-832*U1M1*Q2*X1+
     &  832*U1M1*Q2*X2-192*U1M2*Q22*X1+192*U1M2*Q22*X2-448*T1M1*
     &  Q2*X1+448*T1M1*Q2*X2-128*X1+128*X2)
     &  +M22*LOG10*LHPM4*(192*U1P3*T1M1*X1-192*U1P3*T1M1*X2-
     &  1344*U1P2*T1M1*Q2*X1+1344*U1P2*T1M1*Q2*X2+192*U1P2*X1-192*
     &  U1P2*X2+1472*U1*T1M1*Q22*X1-1472*U1*T1M1*Q22*X2-1728*U1*Q2*
     &  X1+1728*U1*Q2*X2-448*U1M1*Q23*X1+448*U1M1*Q23*X2-832*
     &  T1M1*Q23*X1+832*T1M1*Q23*X2+1472*Q22*X1-1472*Q22*X2)
     &  +M22*LOG10*(-128*TB*X1+128*TB*X2-64*
     &  U1M2*X1+64*U1M2*X2-64*T1M2*X1+64*T1M2*X2)
     &  +M22*LHM1*DLOGQ6T*(128*TB*Q2-384*U1M1-384*T1M1
     &  )
     &  +M22*LHM1*DLOGQ7T*(128*TB*Q2-384*U1M1-384*T1M1
     &  )
     &  +M22*LHM1*DLOGQ8T*(-128*TB*Q2+384*U1M1+384*
     &  T1M1)
      VPS(18) =
     &  +M22*LHM1*DLOGQ9T*(-128*TB*Q2+384*U1M1+384*
     &  T1M1)
     &  +M22*LHM1*DLOGQ10T*(-128*TB*Q2+384*U1M1+384*
     &  T1M1)
     &  +M22*LHM1*DLOGQ11T*(-128*TB*Q2+384*U1M1+384*
     &  T1M1)
     &  +M22*LHM1*DLOGQ12T*(128*TB*Q2-384*U1M1-384*T1M1
     &  )
     &  +M22*LHM1*DLOGQ13T*(256*TB*Q2-768*U1M1-768*T1M1
     &  )
     &  +M22*LHM2*(-128+272*U1M1*T1P2*TM1+208*U1M1*T1*TM1*
     &  Q2-128*U1M1*T1+128*TB*Q22-64*U1M1*TM1*Q22-128*
     &  U1M1*Q2+336*T1*TM1-128*T1M1*Q2+128*T1M2*Q22+336*TM1*Q2
     &  )
     &  +M22*LHM3*DLOGQ6T*(-64*U1+192*U1M1*T1P2-128*U1M1*Q22
     &  +320*T1-384*T1M1*Q22-64*Q2)
     &  +M22*LHM3*DLOGQ7T*(-64*U1+192*U1M1*T1P2-128*U1M1*Q22
     &  +320*T1-384*T1M1*Q22-64*Q2)
      VPS(19) =
     &  +M22*LHM3*DLOGQ8T*(64*U1-192*U1M1*T1P2+128*U1M1*Q22-
     &  320*T1+384*T1M1*Q22+64*Q2)
     &  +M22*LHM3*DLOGQ9T*(64*U1-192*U1M1*T1P2+128*U1M1*Q22-
     &  320*T1+384*T1M1*Q22+64*Q2)
     &  +M22*LHM3*DLOGQ10T*(64*U1-192*U1M1*T1P2+128*U1M1*Q22-
     &  320*T1+384*T1M1*Q22+64*Q2)
     &  +M22*LHM3*DLOGQ11T*(64*U1-192*U1M1*T1P2+128*U1M1*Q22-
     &  320*T1+384*T1M1*Q22+64*Q2)
     &  +M22*LHM3*DLOGQ12T*(-64*U1+192*U1M1*T1P2-128*U1M1*Q22
     &  +320*T1-384*T1M1*Q22-64*Q2)
     &  +M22*LHM3*DLOGQ13T*(-128*U1+384*U1M1*T1P2-256*U1M1*
     &  Q22+640*T1-768*T1M1*Q22-128*Q2)
     &  +M22*LHM5*DLOGQ6T*(96*U1*T1P2-480*U1*T1*Q2+96*U1M1*T1P4
     &  -864*U1M1*T1P3*Q2+1536*U1M1*T1P2*Q22-960*U1M1*T1*Q23+128
     &  *T1P3-1536*T1P2*Q2+1984*T1*Q22-512*Q23)
     &  +M22*LHM5*DLOGQ7T*(96*U1*T1P2-480*U1*T1*Q2+96*U1M1*T1P4
     &  -864*U1M1*T1P3*Q2+1536*U1M1*T1P2*Q22-960*U1M1*T1*Q23+128
     &  *T1P3-1536*T1P2*Q2+1984*T1*Q22-512*Q23)
      VPS(20) =
     &  +M22*LHM5*DLOGQ8T*(-96*U1*T1P2+480*U1*T1*Q2-96*U1M1*
     &  T1P4+864*U1M1*T1P3*Q2-1536*U1M1*T1P2*Q22+960*U1M1*T1*Q23
     &  -128*T1P3+1536*T1P2*Q2-1984*T1*Q22+512*Q23)
     &  +M22*LHM5*DLOGQ9T*(-96*U1*T1P2+480*U1*T1*Q2-96*U1M1*
     &  T1P4+864*U1M1*T1P3*Q2-1536*U1M1*T1P2*Q22+960*U1M1*T1*Q23
     &  -128*T1P3+1536*T1P2*Q2-1984*T1*Q22+512*Q23)
     &  +M22*LHM5*DLOGQ10T*(-96*U1*T1P2+480*U1*T1*Q2-96*U1M1*
     &  T1P4+864*U1M1*T1P3*Q2-1536*U1M1*T1P2*Q22+960*U1M1*T1*Q23
     &  -128*T1P3+1536*T1P2*Q2-1984*T1*Q22+512*Q23)
     &  +M22*LHM5*DLOGQ11T*(-96*U1*T1P2+480*U1*T1*Q2-96*U1M1*
     &  T1P4+864*U1M1*T1P3*Q2-1536*U1M1*T1P2*Q22+960*U1M1*T1*Q23
     &  -128*T1P3+1536*T1P2*Q2-1984*T1*Q22+512*Q23)
     &  +M22*LHM5*DLOGQ12T*(96*U1*T1P2-480*U1*T1*Q2+96*U1M1*T1P4
     &  -864*U1M1*T1P3*Q2+1536*U1M1*T1P2*Q22-960*U1M1*T1*Q23+128
     &  *T1P3-1536*T1P2*Q2+1984*T1*Q22-512*Q23)
     &  +M22*LHM5*DLOGQ13T*(192*U1*T1P2-960*U1*T1*Q2+192*U1M1*
     &  T1P4-1728*U1M1*T1P3*Q2+3072*U1M1*T1P2*Q22-1920*U1M1*T1*Q23
     &  +256*T1P3-3072*T1P2*Q2+3968*T1*Q22-1024*Q23)
      VPS(21) =
     &  +M22*LHPM1*DLOGQ6U*(128*TB*Q2-384*U1M1-384*T1M1
     &  )
     &  +M22*LHPM1*DLOGQ7U*(128*TB*Q2-384*U1M1-384*T1M1
     &  )
     &  +M22*LHPM1*DLOGQ8U*(-128*TB*Q2+384*U1M1+384*
     &  T1M1)
     &  +M22*LHPM1*DLOGQ9U*(-128*TB*Q2+384*U1M1+384*
     &  T1M1)
     &  +M22*LHPM1*DLOGQ10U*(-128*TB*Q2+384*U1M1+384*
     &  T1M1)
     &  +M22*LHPM1*DLOGQ11U*(-128*TB*Q2+384*U1M1+384*
     &  T1M1)
     &  +M22*LHPM1*DLOGQ12U*(128*TB*Q2-384*U1M1-384*
     &  T1M1)
     &  +M22*LHPM1*DLOGQ13U*(256*TB*Q2-768*U1M1-768*
     &  T1M1)
      VPS(22) =
     &  +M22*LHPM2*(-128+272*U1P2*T1M1*UM1+208*U1*T1M1*UM1
     &  *Q2-128*U1*T1M1+336*U1*UM1+128*TB*Q22-128*U1M1*
     &  Q2+128*U1M2*Q22-64*T1M1*UM1*Q22-128*T1M1*Q2+336*UM1*Q2
     &  )
     &  +M22*LHPM3*DLOGQ6U*(192*U1P2*T1M1+320*U1-384*U1M1*Q22
     &  -64*T1-128*T1M1*Q22-64*Q2)
     &  +M22*LHPM3*DLOGQ7U*(192*U1P2*T1M1+320*U1-384*U1M1*Q22
     &  -64*T1-128*T1M1*Q22-64*Q2)
     &  +M22*LHPM3*DLOGQ8U*(-192*U1P2*T1M1-320*U1+384*U1M1*
     &  Q22+64*T1+128*T1M1*Q22+64*Q2)
     &  +M22*LHPM3*DLOGQ9U*(-192*U1P2*T1M1-320*U1+384*U1M1*
     &  Q22+64*T1+128*T1M1*Q22+64*Q2)
     &  +M22*LHPM3*DLOGQ10U*(-192*U1P2*T1M1-320*U1+384*U1M1*
     &  Q22+64*T1+128*T1M1*Q22+64*Q2)
     &  +M22*LHPM3*DLOGQ11U*(-192*U1P2*T1M1-320*U1+384*U1M1*
     &  Q22+64*T1+128*T1M1*Q22+64*Q2)
      VPS(23) =
     &  +M22*LHPM3*DLOGQ12U*(192*U1P2*T1M1+320*U1-384*U1M1*Q22
     &  -64*T1-128*T1M1*Q22-64*Q2)
     &  +M22*LHPM3*DLOGQ13U*(384*U1P2*T1M1+640*U1-768*U1M1*Q22
     &  -128*T1-256*T1M1*Q22-128*Q2)
     &  +M22*LHPM5*DLOGQ6U*(96*U1P4*T1M1-864*U1P3*T1M1*Q2+128*
     &  U1P3+96*U1P2*T1+1536*U1P2*T1M1*Q22-1536*U1P2*Q2-480*U1*T1*
     &  Q2-960*U1*T1M1*Q23+1984*U1*Q22-512*Q23)
     &  +M22*LHPM5*DLOGQ7U*(96*U1P4*T1M1-864*U1P3*T1M1*Q2+128*
     &  U1P3+96*U1P2*T1+1536*U1P2*T1M1*Q22-1536*U1P2*Q2-480*U1*T1*
     &  Q2-960*U1*T1M1*Q23+1984*U1*Q22-512*Q23)
     &  +M22*LHPM5*DLOGQ8U*(-96*U1P4*T1M1+864*U1P3*T1M1*Q2-128
     &  *U1P3-96*U1P2*T1-1536*U1P2*T1M1*Q22+1536*U1P2*Q2+480*U1*T1*
     &  Q2+960*U1*T1M1*Q23-1984*U1*Q22+512*Q23)
     &  +M22*LHPM5*DLOGQ9U*(-96*U1P4*T1M1+864*U1P3*T1M1*Q2-128
     &  *U1P3-96*U1P2*T1-1536*U1P2*T1M1*Q22+1536*U1P2*Q2+480*U1*T1*
     &  Q2+960*U1*T1M1*Q23-1984*U1*Q22+512*Q23)
      VPS(24) =
     &  +M22*LHPM5*DLOGQ10U*(-96*U1P4*T1M1+864*U1P3*T1M1*Q2-
     &  128*U1P3-96*U1P2*T1-1536*U1P2*T1M1*Q22+1536*U1P2*Q2+480*U1*
     &  T1*Q2+960*U1*T1M1*Q23-1984*U1*Q22+512*Q23)
     &  +M22*LHPM5*DLOGQ11U*(-96*U1P4*T1M1+864*U1P3*T1M1*Q2-
     &  128*U1P3-96*U1P2*T1-1536*U1P2*T1M1*Q22+1536*U1P2*Q2+480*U1*
     &  T1*Q2+960*U1*T1M1*Q23-1984*U1*Q22+512*Q23)
     &  +M22*LHPM5*DLOGQ12U*(96*U1P4*T1M1-864*U1P3*T1M1*Q2+128*
     &  U1P3+96*U1P2*T1+1536*U1P2*T1M1*Q22-1536*U1P2*Q2-480*U1*T1*
     &  Q2-960*U1*T1M1*Q23+1984*U1*Q22-512*Q23)
     &  +M22*LHPM5*DLOGQ13U*(192*U1P4*T1M1-1728*U1P3*T1M1*Q2+256
     &  *U1P3+192*U1P2*T1+3072*U1P2*T1M1*Q22-3072*U1P2*Q2-960*U1*T1
     &  *Q2-1920*U1*T1M1*Q23+3968*U1*Q22-1024*Q23)
     &  +M22*LOG7X2*(-64*U1M1*SPM1-64*T1M1*SPM1)
      VPS(25) =
     &  +M22* (-16*U1*T1M2*TM1+160*TB*UM1*Q2+160*
     &  TB*TM1*Q2-192*TB-32*U1M1*T1M2*TM1*Q22-64
     &  *U1M1*T1M2*Q2-352*U1M1*UM1-256*U1M1*TM1-16*U1M2*T1*UM1
     &  -32*U1M2*T1M1*UM1*Q22-64*U1M2*T1M1*Q2+112*U1M2*UM1*Q2
     &  -384*U1M2-320*U1M3*Q2-256*T1M1*UM1-352*T1M1*TM1+112*
     &  T1M2*TM1*Q2-384*T1M2-320*T1M3*Q2)
     &  +M2*LOG1X2*SQM*(-96-16*U1*T1M1-16*U1M1*T1+48*
     &  U1M1*Q2+48*T1M1*Q2+64*BQED)
     &  +M2*LOG1X2*(-32*U1P2*T1M1*Q2*SPM3+32*U1P2*T1M1*SPM2-
     &  64*U1*T1M1*Q2*SPM2+32*U1*T1M1*SPM1-32*U1*Q2*SPM3+160*U1*
     &  SPM2-32*U1M1*T1P2*Q2*SPM3+32*U1M1*T1P2*SPM2-64*U1M1*T1*Q2
     &  *SPM2+32*U1M1*T1*SPM1-32*U1M1*Q2*SPM1-32*T1*Q2*SPM3+160
     &  *T1*SPM2-32*T1M1*Q2*SPM1-128*Q2*SPM2+128*SPM1)
      VPS(26) =
     &  +M2*LOG1*LOG5*SQM*(512+128*U1*T1M1+128*U1*T1M2*Q2+
     &  128*U1M1*T1-256*TB*Q22+128*U1M1*Q2+128*U1M2*T1*Q2
     &  -128*U1M2*Q22+128*T1M1*Q2-128*T1M2*Q22-128*BQED)
     &  +M2*LOG1*LOG6*SQM*(-128-64*U1*T1M1-128*U1*T1M2*Q2
     &  -64*U1M1*T1+256*TB*Q22-320*U1M1*Q2-128*U1M2*T1*
     &  Q2+128*U1M2*Q22-320*T1M1*Q2+128*T1M2*Q22-128*BQED)
     &  +M2*LOG1*LOG3*SQM*(64+64*U1*T1M1+128*U1*T1M2*Q2-128*
     &  TB*Q22+192*U1M1*Q2+128*T1M1*Q2-128*T1M2*Q22)
     &  +M2*LOG1*LOG4*SQM*(64+64*U1M1*T1-128*TB*Q22
     &  +128*U1M1*Q2+128*U1M2*T1*Q2-128*U1M2*Q22+192*T1M1*Q2)
     &  +M2*LOG1*SQM*LOGQ1*(-64-32*U1*T1M1-64*U1*T1M2*Q2-
     &  32*U1M1*T1+128*TB*Q22-160*U1M1*Q2-64*U1M2*T1*Q2+
     &  64*U1M2*Q22-160*T1M1*Q2+64*T1M2*Q22)
      VPS(27) =
     &  +M2*LOG1*SQM*(-256-384*U1P3*T1M1*Q2*SPM3-128*U1P3*
     &  T1M1*SPM2+384*U1P2*T1M1*Q22*SPM3-512*U1P2*T1M1*Q2*SPM2+
     &  64*U1P2*T1M1*S1M1-320*U1P2*T1M1*SPM1-768*U1P2*Q2*SPM3-768*
     &  U1*T1*Q2*SPM3+256*U1*T1*SPM2+768*U1*T1M1*Q22*SPM2-64*U1*
     &  T1M1*Q2*S1M1+128*U1*T1M1*Q2*SPM1-256*U1*T1M1+384*U1*Q22*
     &  SPM3-1280*U1*Q2*SPM2-64*U1*S1M1-192*U1*SPM1-384*U1M1*
     &  T1P3*Q2*SPM3-128*U1M1*T1P3*SPM2+384*U1M1*T1P2*Q22*SPM3-
     &  512*U1M1*T1P2*Q2*SPM2+64*U1M1*T1P2*S1M1-320*U1M1*T1P2*SPM1
     &  +768*U1M1*T1*Q22*SPM2-64*U1M1*T1*Q2*S1M1+128*U1M1*T1*Q2*
     &  SPM1-256*U1M1*T1+320*U1M1*Q22*SPM1+192*U1M1*Q2-768*T1P2
     &  *Q2*SPM3+384*T1*Q22*SPM3-1280*T1*Q2*SPM2-64*T1*S1M1-192*
     &  T1*SPM1+320*T1M1*Q22*SPM1+192*T1M1*Q2+1024*Q22*SPM2+
     &  128*Q2*S1M1-256*Q2*SPM1+128*BQED*LOGDEL+64*BQED)
     &  +M2*LOG3*LHM2*(256*U1*T1*TM1-64*U1*TM1*Q2-144*U1M1*T1P4
     &  *TM2+80*U1M1*T1P3*TM1-48*U1M1*T1P3*TM2*Q2-160*U1M1*T1P2*
     &  TM1*Q2+96*U1M1*T1P2*TM2*Q22+128*U1M1*T1*TM1*Q22-208*T1P3
     &  *TM2+304*T1P2*TM1-208*T1P2*TM2*Q2-352*T1*TM1*Q2+64*TM1*
     &  Q22)
      VPS(28) =
     &  +M2*LOG3*LHM4*(-240*U1*T1P3*TM1+768*U1*T1P2*TM1*Q2-144
     &  *U1*T1*TM1*Q22+96*U1M1*T1P4*TM1*Q2-256*U1M1*T1P3*TM1*Q22
     &  +320*U1M1*T1P2*TM1*Q23-32*U1M1*T1*TM1*Q24-208*T1P4*TM1
     &  +928*T1P3*TM1*Q2-880*T1P2*TM1*Q22+160*T1*TM1*Q23)
     &  +M2*LOG3*(-16*U1*T1M1*TM1+112*U1M1*T1P2*TM2-112*U1M1
     &  *T1*TM1-32*U1M1*TM2*Q22+240*T1*TM2-32*T1M1*TM1*Q2-320*
     &  TM1+112*TM2*Q2)
     &  +M2*LOG4*LHPM2*(-144*U1P4*T1M1*UM2+80*U1P3*T1M1*UM1-
     &  48*U1P3*T1M1*UM2*Q2-208*U1P3*UM2-160*U1P2*T1M1*UM1*Q2+96*
     &  U1P2*T1M1*UM2*Q22+304*U1P2*UM1-208*U1P2*UM2*Q2+256*U1*T1*
     &  UM1+128*U1*T1M1*UM1*Q22-352*U1*UM1*Q2-64*T1*UM1*Q2+64*
     &  UM1*Q22)
     &  +M2*LOG4*LHPM4*(96*U1P4*T1M1*UM1*Q2-208*U1P4*UM1-240*
     &  U1P3*T1*UM1-256*U1P3*T1M1*UM1*Q22+928*U1P3*UM1*Q2+768*U1P2
     &  *T1*UM1*Q2+320*U1P2*T1M1*UM1*Q23-880*U1P2*UM1*Q22-144*U1*
     &  T1*UM1*Q22-32*U1*T1M1*UM1*Q24+160*U1*UM1*Q23)
      VPS(29) =
     &  +M2*LOG4*(112*U1P2*T1M1*UM2-112*U1*T1M1*UM1+240*U1*UM2
     &  -16*U1M1*T1*UM1-32*U1M1*UM1*Q2-32*T1M1*UM2*Q22-320*
     &  UM1+112*UM2*Q2)
     &  +M2*DLOG2*SQM*(512+128*U1*T1M1+128*U1*T1M2*Q2+128*
     &  U1M1*T1-256*TB*Q22+128*U1M1*Q2+128*U1M2*T1*Q2-
     &  128*U1M2*Q22+128*T1M1*Q2-128*T1M2*Q22-128*BQED)
     &  +M2*DLOG3*(32*U1M1-32*T1M1+32*T1M2*Q2)
     &  +M2*DLOG4*(-32*U1M1+32*U1M2*Q2+32*T1M1)
     &  +M2*DLOG1*SQM*(-128-64*U1*T1M1-128*U1*T1M2*Q2-64*
     &  U1M1*T1+256*TB*Q22-320*U1M1*Q2-128*U1M2*T1*Q2+
     &  128*U1M2*Q22-320*T1M1*Q2+128*T1M2*Q22-128*BQED)
     &  +M2*ZETA2*SQM*(1216+352*U1*T1M1+448*U1*T1M2*Q2+352
     &  *U1M1*T1-896*TB*Q22+736*U1M1*Q2+448*U1M2*T1*Q2-
     &  448*U1M2*Q22+736*T1M1*Q2-448*T1M2*Q22+64*BQED)
     &  +M2*ZETA2*LHM1*(-32*U1*T1M1+32*U1M1*T1-64*TB
     &  *Q22+96*U1M1*Q2+192*T1M1*Q2-64*T1M2*Q22)
      VPS(30) =
     &  +M2*ZETA2*LHM3*(224*U1*T1-224*U1*Q2+144*U1M1*T1P3-704*
     &  U1M1*T1P2*Q2+992*U1M1*T1*Q22-320*U1M1*Q23+368*T1P2-1120*
     &  T1*Q2-128*T1M1*Q23+704*Q22)
     &  +M2*ZETA2*LHM5*(-192*U1*T1P3+544*U1*T1P2*Q2-352*U1*T1*
     &  Q22-144*U1M1*T1P5+704*U1M1*T1P4*Q2-1296*U1M1*T1P3*Q22+
     &  1056*U1M1*T1P2*Q23-320*U1M1*T1*Q24-400*T1P4+1504*T1P3*Q2-
     &  1808*T1P2*Q22+768*T1*Q23-64*Q24)
     &  +M2*ZETA2*LHPM1*(32*U1*T1M1-32*U1M1*T1-64*TB*
     &  Q22+192*U1M1*Q2-64*U1M2*Q22+96*T1M1*Q2)
     &  +M2*ZETA2*LHPM3*(144*U1P3*T1M1-704*U1P2*T1M1*Q2+368*
     &  U1P2+224*U1*T1+992*U1*T1M1*Q22-1120*U1*Q2-128*U1M1*Q23-
     &  224*T1*Q2-320*T1M1*Q23+704*Q22)
     &  +M2*ZETA2*LHPM5*(-144*U1P5*T1M1+704*U1P4*T1M1*Q2-400*
     &  U1P4-192*U1P3*T1-1296*U1P3*T1M1*Q22+1504*U1P3*Q2+544*U1P2*
     &  T1*Q2+1056*U1P2*T1M1*Q23-1808*U1P2*Q22-352*U1*T1*Q22-320*
     &  U1*T1M1*Q24+768*U1*Q23-64*Q24)
      VPS(31) =
     &  +M2*ZETA2*(192*U1P2*T1M1*Q2*SPM3-192*U1P2*T1M1*SPM2+
     &  384*U1*T1M1*Q2*SPM2-192*U1*T1M1*SPM1+192*U1*Q2*SPM3-960*U1
     &  *SPM2+192*U1M1*T1P2*Q2*SPM3-192*U1M1*T1P2*SPM2+384*U1M1*
     &  T1*Q2*SPM2-192*U1M1*T1*SPM1+192*U1M1*Q2*SPM1-32*U1M2*Q2
     &  +192*T1*Q2*SPM3-960*T1*SPM2+192*T1M1*Q2*SPM1-32*T1M2*Q2
     &  +768*Q2*SPM2-768*SPM1)
     &  +M2*SQM*LOG8*LOGQ2*(-64-32*U1*T1M1-64*U1*T1M2*Q2-
     &  32*U1M1*T1+128*TB*Q22-160*U1M1*Q2-64*U1M2*T1*Q2+
     &  64*U1M2*Q22-160*T1M1*Q2+64*T1M2*Q22)
     &  +M2*SQM*DLOGQ1*(-128-64*U1*T1M1-128*U1*T1M2*Q2-64*
     &  U1M1*T1+256*TB*Q22-320*U1M1*Q2-128*U1M2*T1*Q2+
     &  128*U1M2*Q22-320*T1M1*Q2+128*T1M2*Q22)
     &  +M2*SQM*DLOGQ2*(-128-64*U1*T1M1-128*U1*T1M2*Q2-64*
     &  U1M1*T1+256*TB*Q22-320*U1M1*Q2-128*U1M2*T1*Q2+
     &  128*U1M2*Q22-320*T1M1*Q2+128*T1M2*Q22)
      VPS(32) =
     &  +M2*SQM*DLOGQ3*(-128-64*U1*T1M1-128*U1*T1M2*Q2-64*
     &  U1M1*T1+256*TB*Q22-320*U1M1*Q2-128*U1M2*T1*Q2+
     &  128*U1M2*Q22-320*T1M1*Q2+128*T1M2*Q22)
     &  +M2*SQM*DLOGQ4*(128+64*U1*T1M1+128*U1*T1M2*Q2+64*
     &  U1M1*T1-256*TB*Q22+320*U1M1*Q2+128*U1M2*T1*Q2-
     &  128*U1M2*Q22+320*T1M1*Q2-128*T1M2*Q22)
     &  +M2*SQM*LOGQ3X2*(-64-32*U1*T1M1-64*U1*T1M2*Q2-32*
     &  U1M1*T1+128*TB*Q22-160*U1M1*Q2-64*U1M2*T1*Q2+64*
     &  U1M2*Q22-160*T1M1*Q2+64*T1M2*Q22)
     &  +M2*LOG9*LHM2*(-48*U1*T1M1*Q2*X1+48*U1*T1M1*Q2*X2-48*
     &  U1*X1+48*U1*X2+112*U1M1*T1P2*X1-112*U1M1*T1P2*X2-208*U1M1*
     &  T1*Q2*X1+208*U1M1*T1*Q2*X2-192*TB*Q23*X1+192*U1M1*
     &  T1M1*Q23*X2+480*U1M1*Q22*X1-480*U1M1*Q22*X2+128*T1*X1-
     &  128*T1*X2+352*T1M1*Q22*X1-352*T1M1*Q22*X2-96*T1M2*Q23*X1
     &  +96*T1M2*Q23*X2-160*Q2*X1+160*Q2*X2)
      VPS(33) =
     &  +M2*LOG9*LHM4*(48*U1*T1P2*X1-48*U1*T1P2*X2-224*U1*T1*Q2*
     &  X1+224*U1*T1*Q2*X2-208*U1*Q22*X1+208*U1*Q22*X2-144*U1M1*
     &  T1P4*X1+144*U1M1*T1P4*X2+608*U1M1*T1P3*Q2*X1-608*U1M1*T1P3*
     &  Q2*X2-1040*U1M1*T1P2*Q22*X1+1040*U1M1*T1P2*Q22*X2+736*U1M1
     &  *T1*Q23*X1-736*U1M1*T1*Q23*X2-288*U1M1*Q24*X1+288*U1M1*
     &  Q24*X2-192*T1P3*X1+192*T1P3*X2+576*T1P2*Q2*X1-576*T1P2*Q2*X2
     &  -928*T1*Q22*X1+928*T1*Q22*X2-64*T1M1*Q24*X1+64*T1M1*Q24
     &  *X2+608*Q23*X1-608*Q23*X2)
     &  +M2*LOG9*LHPM2*(112*U1P2*T1M1*X1-112*U1P2*T1M1*X2-208*
     &  U1*T1M1*Q2*X1+208*U1*T1M1*Q2*X2+128*U1*X1-128*U1*X2-48*
     &  U1M1*T1*Q2*X1+48*U1M1*T1*Q2*X2-192*TB*Q23*X1+192*
     &  TB*Q23*X2+352*U1M1*Q22*X1-352*U1M1*Q22*X2-96*
     &  U1M2*Q23*X1+96*U1M2*Q23*X2-48*T1*X1+48*T1*X2+480*T1M1*
     &  Q22*X1-480*T1M1*Q22*X2-160*Q2*X1+160*Q2*X2)
      VPS(34) =
     &  +M2*LOG9*LHPM4*(-144*U1P4*T1M1*X1+144*U1P4*T1M1*X2+
     &  608*U1P3*T1M1*Q2*X1-608*U1P3*T1M1*Q2*X2-192*U1P3*X1+192*U1P3*
     &  X2+48*U1P2*T1*X1-48*U1P2*T1*X2-1040*U1P2*T1M1*Q22*X1+1040*
     &  U1P2*T1M1*Q22*X2+576*U1P2*Q2*X1-576*U1P2*Q2*X2-224*U1*T1*Q2*
     &  X1+224*U1*T1*Q2*X2+736*U1*T1M1*Q23*X1-736*U1*T1M1*Q23*X2-
     &  928*U1*Q22*X1+928*U1*Q22*X2-64*U1M1*Q24*X1+64*U1M1*Q24*X2
     &  -208*T1*Q22*X1+208*T1*Q22*X2-288*T1M1*Q24*X1+288*T1M1*
     &  Q24*X2+608*Q23*X1-608*Q23*X2)
     &  +M2*LOG9*(-128*U1*T1M1*Q2*SPM2*X1+128*U1*T1M1*Q2*SPM2*
     &  X2+128*U1*T1M1*SPM1*X1-128*U1*T1M1*SPM1*X2-128*U1M1*T1*Q2*
     &  SPM2*X1+128*U1M1*T1*Q2*SPM2*X2+128*U1M1*T1*SPM1*X1-128*
     &  U1M1*T1*SPM1*X2-64*TB*Q2*X1+64*TB*Q2*X2-192
     &  *U1M1*Q2*SPM1*X1+192*U1M1*Q2*SPM1*X2+224*U1M1*X1-224*U1M1
     &  *X2-192*T1M1*Q2*SPM1*X1+192*T1M1*Q2*SPM1*X2+224*T1M1*X1-
     &  224*T1M1*X2-256*Q2*SPM2*X1+256*Q2*SPM2*X2+256*SPM1*X1-256
     &  *SPM1*X2)
      VPS(35) =
     &  +M2*LOG10*LHM2*(48*U1*T1M1*Q2*X1-48*U1*T1M1*Q2*X2+48*U1
     &  *X1-48*U1*X2-112*U1M1*T1P2*X1+112*U1M1*T1P2*X2+208*U1M1*T1
     &  *Q2*X1-208*U1M1*T1*Q2*X2+192*TB*Q23*X1-192*U1M1*
     &  T1M1*Q23*X2-480*U1M1*Q22*X1+480*U1M1*Q22*X2-128*T1*X1+
     &  128*T1*X2-352*T1M1*Q22*X1+352*T1M1*Q22*X2+96*T1M2*Q23*X1
     &  -96*T1M2*Q23*X2+160*Q2*X1-160*Q2*X2)
     &  +M2*LOG10*LHM4*(-48*U1*T1P2*X1+48*U1*T1P2*X2+224*U1*T1*
     &  Q2*X1-224*U1*T1*Q2*X2+208*U1*Q22*X1-208*U1*Q22*X2+144*U1M1
     &  *T1P4*X1-144*U1M1*T1P4*X2-608*U1M1*T1P3*Q2*X1+608*U1M1*T1P3*
     &  Q2*X2+1040*U1M1*T1P2*Q22*X1-1040*U1M1*T1P2*Q22*X2-736*U1M1
     &  *T1*Q23*X1+736*U1M1*T1*Q23*X2+288*U1M1*Q24*X1-288*U1M1*
     &  Q24*X2+192*T1P3*X1-192*T1P3*X2-576*T1P2*Q2*X1+576*T1P2*Q2*X2
     &  +928*T1*Q22*X1-928*T1*Q22*X2+64*T1M1*Q24*X1-64*T1M1*Q24
     &  *X2-608*Q23*X1+608*Q23*X2)
      VPS(36) =
     &  +M2*LOG10*LHPM2*(-112*U1P2*T1M1*X1+112*U1P2*T1M1*X2+
     &  208*U1*T1M1*Q2*X1-208*U1*T1M1*Q2*X2-128*U1*X1+128*U1*X2+48*
     &  U1M1*T1*Q2*X1-48*U1M1*T1*Q2*X2+192*TB*Q23*X1-192*
     &  TB*Q23*X2-352*U1M1*Q22*X1+352*U1M1*Q22*X2+96*
     &  U1M2*Q23*X1-96*U1M2*Q23*X2+48*T1*X1-48*T1*X2-480*T1M1*
     &  Q22*X1+480*T1M1*Q22*X2+160*Q2*X1-160*Q2*X2)
     &  +M2*LOG10*LHPM4*(144*U1P4*T1M1*X1-144*U1P4*T1M1*X2-608*
     &  U1P3*T1M1*Q2*X1+608*U1P3*T1M1*Q2*X2+192*U1P3*X1-192*U1P3*X2
     &  -48*U1P2*T1*X1+48*U1P2*T1*X2+1040*U1P2*T1M1*Q22*X1-1040*
     &  U1P2*T1M1*Q22*X2-576*U1P2*Q2*X1+576*U1P2*Q2*X2+224*U1*T1*Q2*
     &  X1-224*U1*T1*Q2*X2-736*U1*T1M1*Q23*X1+736*U1*T1M1*Q23*X2+
     &  928*U1*Q22*X1-928*U1*Q22*X2+64*U1M1*Q24*X1-64*U1M1*Q24*X2
     &  +208*T1*Q22*X1-208*T1*Q22*X2+288*T1M1*Q24*X1-288*T1M1*
     &  Q24*X2-608*Q23*X1+608*Q23*X2)
      VPS(37) =
     &  +M2*LOG10*(128*U1*T1M1*Q2*SPM2*X1-128*U1*T1M1*Q2*SPM2*X2
     &  -128*U1*T1M1*SPM1*X1+128*U1*T1M1*SPM1*X2+128*U1M1*T1*Q2*
     &  SPM2*X1-128*U1M1*T1*Q2*SPM2*X2-128*U1M1*T1*SPM1*X1+128*
     &  U1M1*T1*SPM1*X2+64*TB*Q2*X1-64*TB*Q2*X2+192
     &  *U1M1*Q2*SPM1*X1-192*U1M1*Q2*SPM1*X2-224*U1M1*X1+224*U1M1
     &  *X2+192*T1M1*Q2*SPM1*X1-192*T1M1*Q2*SPM1*X2-224*T1M1*X1+
     &  224*T1M1*X2+256*Q2*SPM2*X1-256*Q2*SPM2*X2-256*SPM1*X1+256
     &  *SPM1*X2)
     &  +M2*LHM1*DLOGQ6T*(32*U1*T1M1-32*U1M1*T1+64*TB*
     &  Q22-96*U1M1*Q2-192*T1M1*Q2+64*T1M2*Q22)
     &  +M2*LHM1*DLOGQ7T*(32*U1*T1M1-32*U1M1*T1+64*TB*
     &  Q22-96*U1M1*Q2-192*T1M1*Q2+64*T1M2*Q22)
     &  +M2*LHM1*DLOGQ8T*(-32*U1*T1M1+32*U1M1*T1-64*TB
     &  *Q22+96*U1M1*Q2+192*T1M1*Q2-64*T1M2*Q22)
     &  +M2*LHM1*DLOGQ9T*(-32*U1*T1M1+32*U1M1*T1-64*TB
     &  *Q22+96*U1M1*Q2+192*T1M1*Q2-64*T1M2*Q22)
      VPS(38) =
     &  +M2*LHM1*DLOGQ10T*(-32*U1*T1M1+32*U1M1*T1-64*U1M1*
     &  T1M1*Q22+96*U1M1*Q2+192*T1M1*Q2-64*T1M2*Q22)
     &  +M2*LHM1*DLOGQ11T*(-32*U1*T1M1+32*U1M1*T1-64*U1M1*
     &  T1M1*Q22+96*U1M1*Q2+192*T1M1*Q2-64*T1M2*Q22)
     &  +M2*LHM1*DLOGQ12T*(32*U1*T1M1-32*U1M1*T1+64*TB*
     &  Q22-96*U1M1*Q2-192*T1M1*Q2+64*T1M2*Q22)
     &  +M2*LHM1*DLOGQ13T*(64*U1*T1M1-64*U1M1*T1+128*TB*
     &  Q22-192*U1M1*Q2-384*T1M1*Q2+128*T1M2*Q22)
     &  +M2*LHM2*(-128*U1*T1M1*Q2+32*U1+168*U1M1*T1P3*TM1+
     &  80*U1M1*T1P2*TM1*Q2-112*U1M1*T1P2-88*U1M1*T1*TM1*Q22-176*
     &  U1M1*T1*Q2-96*TB*Q23+192*U1M1*Q22+240*T1P2*TM1+
     &  240*T1*TM1*Q2-144*T1+192*T1M1*Q22-32*T1M2*Q23-432*Q2)
     &  +M2*LHM3*DLOGQ6T*(-224*U1*T1+224*U1*Q2-144*U1M1*T1P3+
     &  704*U1M1*T1P2*Q2-992*U1M1*T1*Q22+320*U1M1*Q23-368*T1P2+
     &  1120*T1*Q2+128*T1M1*Q23-704*Q22)
      VPS(39) =
     &  +M2*LHM3*DLOGQ7T*(-224*U1*T1+224*U1*Q2-144*U1M1*T1P3+
     &  704*U1M1*T1P2*Q2-992*U1M1*T1*Q22+320*U1M1*Q23-368*T1P2+
     &  1120*T1*Q2+128*T1M1*Q23-704*Q22)
     &  +M2*LHM3*DLOGQ8T*(224*U1*T1-224*U1*Q2+144*U1M1*T1P3-704*
     &  U1M1*T1P2*Q2+992*U1M1*T1*Q22-320*U1M1*Q23+368*T1P2-1120*
     &  T1*Q2-128*T1M1*Q23+704*Q22)
     &  +M2*LHM3*DLOGQ9T*(224*U1*T1-224*U1*Q2+144*U1M1*T1P3-704*
     &  U1M1*T1P2*Q2+992*U1M1*T1*Q22-320*U1M1*Q23+368*T1P2-1120*
     &  T1*Q2-128*T1M1*Q23+704*Q22)
     &  +M2*LHM3*DLOGQ10T*(224*U1*T1-224*U1*Q2+144*U1M1*T1P3-704
     &  *U1M1*T1P2*Q2+992*U1M1*T1*Q22-320*U1M1*Q23+368*T1P2-1120
     &  *T1*Q2-128*T1M1*Q23+704*Q22)
     &  +M2*LHM3*DLOGQ11T*(224*U1*T1-224*U1*Q2+144*U1M1*T1P3-704
     &  *U1M1*T1P2*Q2+992*U1M1*T1*Q22-320*U1M1*Q23+368*T1P2-1120
     &  *T1*Q2-128*T1M1*Q23+704*Q22)
     &  +M2*LHM3*DLOGQ12T*(-224*U1*T1+224*U1*Q2-144*U1M1*T1P3+
     &  704*U1M1*T1P2*Q2-992*U1M1*T1*Q22+320*U1M1*Q23-368*T1P2+
     &  1120*T1*Q2+128*T1M1*Q23-704*Q22)
      VPS(40) =
     &  +M2*LHM3*DLOGQ13T*(-448*U1*T1+448*U1*Q2-288*U1M1*T1P3+
     &  1408*U1M1*T1P2*Q2-1984*U1M1*T1*Q22+640*U1M1*Q23-736*T1P2
     &  +2240*T1*Q2+256*T1M1*Q23-1408*Q22)
     &  +M2*LHM5*DLOGQ6T*(192*U1*T1P3-544*U1*T1P2*Q2+352*U1*T1*Q22
     &  +144*U1M1*T1P5-704*U1M1*T1P4*Q2+1296*U1M1*T1P3*Q22-1056*
     &  U1M1*T1P2*Q23+320*U1M1*T1*Q24+400*T1P4-1504*T1P3*Q2+1808*
     &  T1P2*Q22-768*T1*Q23+64*Q24)
     &  +M2*LHM5*DLOGQ7T*(192*U1*T1P3-544*U1*T1P2*Q2+352*U1*T1*Q22
     &  +144*U1M1*T1P5-704*U1M1*T1P4*Q2+1296*U1M1*T1P3*Q22-1056*
     &  U1M1*T1P2*Q23+320*U1M1*T1*Q24+400*T1P4-1504*T1P3*Q2+1808*
     &  T1P2*Q22-768*T1*Q23+64*Q24)
     &  +M2*LHM5*DLOGQ8T*(-192*U1*T1P3+544*U1*T1P2*Q2-352*U1*T1*
     &  Q22-144*U1M1*T1P5+704*U1M1*T1P4*Q2-1296*U1M1*T1P3*Q22+
     &  1056*U1M1*T1P2*Q23-320*U1M1*T1*Q24-400*T1P4+1504*T1P3*Q2-
     &  1808*T1P2*Q22+768*T1*Q23-64*Q24)
     &  +M2*LHM5*DLOGQ9T*(-192*U1*T1P3+544*U1*T1P2*Q2-352*U1*T1*
     &  Q22-144*U1M1*T1P5+704*U1M1*T1P4*Q2-1296*U1M1*T1P3*Q22+
     &  1056*U1M1*T1P2*Q23-320*U1M1*T1*Q24-400*T1P4+1504*T1P3*Q2-
     &  1808*T1P2*Q22+768*T1*Q23-64*Q24)
      VPS(41) =
     &  +M2*LHM5*DLOGQ10T*(-192*U1*T1P3+544*U1*T1P2*Q2-352*U1*T1*
     &  Q22-144*U1M1*T1P5+704*U1M1*T1P4*Q2-1296*U1M1*T1P3*Q22+
     &  1056*U1M1*T1P2*Q23-320*U1M1*T1*Q24-400*T1P4+1504*T1P3*Q2-
     &  1808*T1P2*Q22+768*T1*Q23-64*Q24)
     &  +M2*LHM5*DLOGQ11T*(-192*U1*T1P3+544*U1*T1P2*Q2-352*U1*T1*
     &  Q22-144*U1M1*T1P5+704*U1M1*T1P4*Q2-1296*U1M1*T1P3*Q22+
     &  1056*U1M1*T1P2*Q23-320*U1M1*T1*Q24-400*T1P4+1504*T1P3*Q2-
     &  1808*T1P2*Q22+768*T1*Q23-64*Q24)
     &  +M2*LHM5*DLOGQ12T*(192*U1*T1P3-544*U1*T1P2*Q2+352*U1*T1*
     &  Q22+144*U1M1*T1P5-704*U1M1*T1P4*Q2+1296*U1M1*T1P3*Q22-
     &  1056*U1M1*T1P2*Q23+320*U1M1*T1*Q24+400*T1P4-1504*T1P3*Q2+
     &  1808*T1P2*Q22-768*T1*Q23+64*Q24)
     &  +M2*LHM5*DLOGQ13T*(384*U1*T1P3-1088*U1*T1P2*Q2+704*U1*T1*
     &  Q22+288*U1M1*T1P5-1408*U1M1*T1P4*Q2+2592*U1M1*T1P3*Q22-
     &  2112*U1M1*T1P2*Q23+640*U1M1*T1*Q24+800*T1P4-3008*T1P3*Q2+
     &  3616*T1P2*Q22-1536*T1*Q23+128*Q24)
      VPS(42) =
     &  +M2*LHPM1*DLOGQ6U*(-32*U1*T1M1+32*U1M1*T1+64*U1M1*
     &  T1M1*Q22-192*U1M1*Q2+64*U1M2*Q22-96*T1M1*Q2)
     &  +M2*LHPM1*DLOGQ7U*(-32*U1*T1M1+32*U1M1*T1+64*U1M1*
     &  T1M1*Q22-192*U1M1*Q2+64*U1M2*Q22-96*T1M1*Q2)
     &  +M2*LHPM1*DLOGQ8U*(32*U1*T1M1-32*U1M1*T1-64*TB*
     &  Q22+192*U1M1*Q2-64*U1M2*Q22+96*T1M1*Q2)
     &  +M2*LHPM1*DLOGQ9U*(32*U1*T1M1-32*U1M1*T1-64*TB*
     &  Q22+192*U1M1*Q2-64*U1M2*Q22+96*T1M1*Q2)
     &  +M2*LHPM1*DLOGQ10U*(32*U1*T1M1-32*U1M1*T1-64*TB*
     &  Q22+192*U1M1*Q2-64*U1M2*Q22+96*T1M1*Q2)
     &  +M2*LHPM1*DLOGQ11U*(32*U1*T1M1-32*U1M1*T1-64*TB*
     &  Q22+192*U1M1*Q2-64*U1M2*Q22+96*T1M1*Q2)
     &  +M2*LHPM1*DLOGQ12U*(-32*U1*T1M1+32*U1M1*T1+64*U1M1*
     &  T1M1*Q22-192*U1M1*Q2+64*U1M2*Q22-96*T1M1*Q2)
     &  +M2*LHPM1*DLOGQ13U*(-64*U1*T1M1+64*U1M1*T1+128*U1M1*
     &  T1M1*Q22-384*U1M1*Q2+128*U1M2*Q22-192*T1M1*Q2)
      VPS(43) =
     &  +M2*LHPM2*(168*U1P3*T1M1*UM1+80*U1P2*T1M1*UM1*Q2-112*
     &  U1P2*T1M1+240*U1P2*UM1-88*U1*T1M1*UM1*Q22-176*U1*T1M1*Q2
     &  +240*U1*UM1*Q2-144*U1-128*U1M1*T1*Q2-96*TB*Q23+
     &  192*U1M1*Q22-32*U1M2*Q23+32*T1+192*T1M1*Q22-432*Q2)
     &  +M2*LHPM3*DLOGQ6U*(-144*U1P3*T1M1+704*U1P2*T1M1*Q2-368*
     &  U1P2-224*U1*T1-992*U1*T1M1*Q22+1120*U1*Q2+128*U1M1*Q23+
     &  224*T1*Q2+320*T1M1*Q23-704*Q22)
     &  +M2*LHPM3*DLOGQ7U*(-144*U1P3*T1M1+704*U1P2*T1M1*Q2-368*
     &  U1P2-224*U1*T1-992*U1*T1M1*Q22+1120*U1*Q2+128*U1M1*Q23+
     &  224*T1*Q2+320*T1M1*Q23-704*Q22)
     &  +M2*LHPM3*DLOGQ8U*(144*U1P3*T1M1-704*U1P2*T1M1*Q2+368*
     &  U1P2+224*U1*T1+992*U1*T1M1*Q22-1120*U1*Q2-128*U1M1*Q23-
     &  224*T1*Q2-320*T1M1*Q23+704*Q22)
     &  +M2*LHPM3*DLOGQ9U*(144*U1P3*T1M1-704*U1P2*T1M1*Q2+368*
     &  U1P2+224*U1*T1+992*U1*T1M1*Q22-1120*U1*Q2-128*U1M1*Q23-
     &  224*T1*Q2-320*T1M1*Q23+704*Q22)
      VPS(44) =
     &  +M2*LHPM3*DLOGQ10U*(144*U1P3*T1M1-704*U1P2*T1M1*Q2+368*
     &  U1P2+224*U1*T1+992*U1*T1M1*Q22-1120*U1*Q2-128*U1M1*Q23-
     &  224*T1*Q2-320*T1M1*Q23+704*Q22)
     &  +M2*LHPM3*DLOGQ11U*(144*U1P3*T1M1-704*U1P2*T1M1*Q2+368*
     &  U1P2+224*U1*T1+992*U1*T1M1*Q22-1120*U1*Q2-128*U1M1*Q23-
     &  224*T1*Q2-320*T1M1*Q23+704*Q22)
     &  +M2*LHPM3*DLOGQ12U*(-144*U1P3*T1M1+704*U1P2*T1M1*Q2-368
     &  *U1P2-224*U1*T1-992*U1*T1M1*Q22+1120*U1*Q2+128*U1M1*Q23
     &  +224*T1*Q2+320*T1M1*Q23-704*Q22)
     &  +M2*LHPM3*DLOGQ13U*(-288*U1P3*T1M1+1408*U1P2*T1M1*Q2-
     &  736*U1P2-448*U1*T1-1984*U1*T1M1*Q22+2240*U1*Q2+256*U1M1*
     &  Q23+448*T1*Q2+640*T1M1*Q23-1408*Q22)
     &  +M2*LHPM5*DLOGQ6U*(144*U1P5*T1M1-704*U1P4*T1M1*Q2+400*
     &  U1P4+192*U1P3*T1+1296*U1P3*T1M1*Q22-1504*U1P3*Q2-544*U1P2*
     &  T1*Q2-1056*U1P2*T1M1*Q23+1808*U1P2*Q22+352*U1*T1*Q22+320*
     &  U1*T1M1*Q24-768*U1*Q23+64*Q24)
      VPS(45) =
     &  +M2*LHPM5*DLOGQ7U*(144*U1P5*T1M1-704*U1P4*T1M1*Q2+400*
     &  U1P4+192*U1P3*T1+1296*U1P3*T1M1*Q22-1504*U1P3*Q2-544*U1P2*
     &  T1*Q2-1056*U1P2*T1M1*Q23+1808*U1P2*Q22+352*U1*T1*Q22+320*
     &  U1*T1M1*Q24-768*U1*Q23+64*Q24)
     &  +M2*LHPM5*DLOGQ8U*(-144*U1P5*T1M1+704*U1P4*T1M1*Q2-400*
     &  U1P4-192*U1P3*T1-1296*U1P3*T1M1*Q22+1504*U1P3*Q2+544*U1P2*
     &  T1*Q2+1056*U1P2*T1M1*Q23-1808*U1P2*Q22-352*U1*T1*Q22-320*
     &  U1*T1M1*Q24+768*U1*Q23-64*Q24)
     &  +M2*LHPM5*DLOGQ9U*(-144*U1P5*T1M1+704*U1P4*T1M1*Q2-400*
     &  U1P4-192*U1P3*T1-1296*U1P3*T1M1*Q22+1504*U1P3*Q2+544*U1P2*
     &  T1*Q2+1056*U1P2*T1M1*Q23-1808*U1P2*Q22-352*U1*T1*Q22-320*
     &  U1*T1M1*Q24+768*U1*Q23-64*Q24)
     &  +M2*LHPM5*DLOGQ10U*(-144*U1P5*T1M1+704*U1P4*T1M1*Q2-400
     &  *U1P4-192*U1P3*T1-1296*U1P3*T1M1*Q22+1504*U1P3*Q2+544*U1P2*
     &  T1*Q2+1056*U1P2*T1M1*Q23-1808*U1P2*Q22-352*U1*T1*Q22-320*
     &  U1*T1M1*Q24+768*U1*Q23-64*Q24)
      VPS(46) =
     &  +M2*LHPM5*DLOGQ11U*(-144*U1P5*T1M1+704*U1P4*T1M1*Q2-400
     &  *U1P4-192*U1P3*T1-1296*U1P3*T1M1*Q22+1504*U1P3*Q2+544*U1P2*
     &  T1*Q2+1056*U1P2*T1M1*Q23-1808*U1P2*Q22-352*U1*T1*Q22-320*
     &  U1*T1M1*Q24+768*U1*Q23-64*Q24)
     &  +M2*LHPM5*DLOGQ12U*(144*U1P5*T1M1-704*U1P4*T1M1*Q2+400*
     &  U1P4+192*U1P3*T1+1296*U1P3*T1M1*Q22-1504*U1P3*Q2-544*U1P2*
     &  T1*Q2-1056*U1P2*T1M1*Q23+1808*U1P2*Q22+352*U1*T1*Q22+320*
     &  U1*T1M1*Q24-768*U1*Q23+64*Q24)
     &  +M2*LHPM5*DLOGQ13U*(288*U1P5*T1M1-1408*U1P4*T1M1*Q2+800*
     &  U1P4+384*U1P3*T1+2592*U1P3*T1M1*Q22-3008*U1P3*Q2-1088*U1P2*
     &  T1*Q2-2112*U1P2*T1M1*Q23+3616*U1P2*Q22+704*U1*T1*Q22+640*
     &  U1*T1M1*Q24-1536*U1*Q23+128*Q24)
     &  +M2*LOG7X2*(32*U1P2*T1M1*Q2*SPM3-32*U1P2*T1M1*SPM2+64*
     &  U1*T1M1*Q2*SPM2-32*U1*T1M1*SPM1+32*U1*Q2*SPM3-160*U1*SPM2
     &  +32*U1M1*T1P2*Q2*SPM3-32*U1M1*T1P2*SPM2+64*U1M1*T1*Q2*
     &  SPM2-32*U1M1*T1*SPM1+32*U1M1*Q2*SPM1+32*T1*Q2*SPM3-160*
     &  T1*SPM2+32*T1M1*Q2*SPM1+128*Q2*SPM2-128*SPM1)
      VPS(47) =
     &  +M2* (-152*U1*T1M1*UM1-32*U1*T1M1*TM1-128*U1*T1M1*
     &  SPM1+112*U1*T1M2-32*U1M1*T1*UM1-152*U1M1*T1*TM1-128*
     &  U1M1*T1*SPM1-32*TB*UM1*Q22-32*TB*TM1*Q22
     &  -128*TB*Q2+160*U1M1*T1M2*Q22+32*U1M1*UM1*Q2+128
     &  *U1M1*TM1*Q2+160*U1M1+112*U1M2*T1+160*U1M2*T1M1*Q22-
     &  208*U1M2*Q2+128*T1M1*UM1*Q2+32*T1M1*TM1*Q2+160*T1M1-208
     &  *T1M2*Q2-304*UM1-304*TM1-256*SPM1)
     &  +XSQM1*LOG1X2*(-32*BQED)
     &  +XSQM1*LOG1*LOG5*(64*BQED)
     &  +XSQM1*LOG1*LOG6*(64*BQED)
     &  +XSQM1*LOG1*(-64*BQED*LOGDEL-32*BQED)
     &  +XSQM1*DLOG2*(64*BQED)
     &  +XSQM1*DLOG1*(64*BQED)
     &  +XSQM1*ZETA2*(-32*BQED)
     &  +LOG1X2*SQM*(-8*U1P2*T1M1+24*U1*T1M1*Q2-40*U1-8*
     &  U1M1*T1P2+24*U1M1*T1*Q2-16*U1M1*Q22-40*T1-16*T1M1*Q22
     &  +64*Q2)
      VPS(48) =
     &  +LOG1X2*(-16*U1P4*T1M1*SPM3+32*U1P3*T1M1*Q2*SPM3-48*
     &  U1P3*T1M1*SPM2-48*U1P3*SPM3-64*U1P2*T1*SPM3-16*U1P2*T1M1*
     &  Q22*SPM3+96*U1P2*T1M1*Q2*SPM2-56*U1P2*T1M1*SPM1+64*U1P2*
     &  Q2*SPM3-128*U1P2*SPM2-64*U1*T1P2*SPM3+64*U1*T1*Q2*SPM3-
     &  160*U1*T1*SPM2-48*U1*T1M1*Q22*SPM2+112*U1*T1M1*Q2*SPM1-16
     &  *U1*Q22*SPM3+192*U1*Q2*SPM2-120*U1*SPM1-16*U1M1*T1P4*SPM3
     &  +32*U1M1*T1P3*Q2*SPM3-48*U1M1*T1P3*SPM2-16*U1M1*T1P2*Q22*
     &  SPM3+96*U1M1*T1P2*Q2*SPM2-56*U1M1*T1P2*SPM1-48*U1M1*T1*
     &  Q22*SPM2+112*U1M1*T1*Q2*SPM1-64*U1M1*Q22*SPM1-48*T1P3*
     &  SPM3+64*T1P2*Q2*SPM3-128*T1P2*SPM2-16*T1*Q22*SPM3+192*T1
     &  *Q2*SPM2-120*T1*SPM1-64*T1M1*Q22*SPM1-64*Q22*SPM2+192*
     &  Q2*SPM1)
     &  +LOG1*LOG5*SQM*(-64*U1P2*T1M1+192*U1*T1M1*Q2-64*U1
     &  -64*U1M1*T1P2+192*U1M1*T1*Q2+128*TB*Q23-256*U1M1
     &  *Q22-64*T1-256*T1M1*Q22+256*Q2)
     &  +LOG1*LOG6*SQM*(96*U1P2*T1M1-288*U1*T1M1*Q2+224*U1+
     &  96*U1M1*T1P2-288*U1M1*T1*Q2-128*TB*Q23+320*U1M1*
     &  Q22+224*T1+320*T1M1*Q22-512*Q2)
      VPS(49) =
     &  +LOG1*LOG3*SQM*(-32*U1P2*T1M1+96*U1*T1M1*Q2-96*U1-
     &  64*U1M1*T1P2+192*U1M1*T1*Q2+64*TB*Q23-192*U1M1*
     &  Q22-128*T1-128*T1M1*Q22+256*Q2)
     &  +LOG1*LOG4*SQM*(-64*U1P2*T1M1+192*U1*T1M1*Q2-128*U1
     &  -32*U1M1*T1P2+96*U1M1*T1*Q2+64*TB*Q23-128*U1M1*
     &  Q22-96*T1-192*T1M1*Q22+256*Q2)
     &  +LOG1*SQM*LOGQ1*(48*U1P2*T1M1-144*U1*T1M1*Q2+112*U1+
     &  48*U1M1*T1P2-144*U1M1*T1*Q2-64*TB*Q23+160*U1M1*
     &  Q22+112*T1+160*T1M1*Q22-256*Q2)
     &  +LOG1*SQM*(-96*U1P4*T1M1*Q2*SPM3-32*U1P4*T1M1*SPM2
     &  +192*U1P3*T1M1*Q22*SPM3-128*U1P3*T1M1*Q2*SPM2+16*U1P3*
     &  T1M1*S1M1-64*U1P3*T1M1*SPM1-288*U1P3*Q2*SPM3-32*U1P3*SPM2
     &  -384*U1P2*T1*Q2*SPM3+64*U1P2*T1*SPM2-96*U1P2*T1M1*Q23*SPM3
     &  +384*U1P2*T1M1*Q22*SPM2-32*U1P2*T1M1*Q2*S1M1+32*U1P2*T1M1
     &  *Q2*SPM1-48*U1P2*T1M1+384*U1P2*Q22*SPM3-576*U1P2*Q2*SPM2)
      VPS(50) = LOG1*SQM*(
     &    -64*U1P2*SPM1-384*U1*T1P2*Q2*SPM3+64*U1*T1P2*SPM2+384*U1*
     &    T1*Q22*SPM3-896*U1*T1*Q2*SPM2-32*U1*T1*S1M1-224*U1*T1M1*
     &    Q23*SPM2+16*U1*T1M1*Q22*S1M1+160*U1*T1M1*Q22*SPM1+80*U1
     &    *T1M1*Q2-96*U1*Q23*SPM3+960*U1*Q22*SPM2+32*U1*Q2*S1M1-
     &    224*U1*Q2*SPM1-80*U1-96*U1M1*T1P4*Q2*SPM3-32*U1M1*T1P4*
     &    SPM2+192*U1M1*T1P3*Q22*SPM3-128*U1M1*T1P3*Q2*SPM2+16*
     &    U1M1*T1P3*S1M1-64*U1M1*T1P3*SPM1-96*U1M1*T1P2*Q23*SPM3+
     &    384*U1M1*T1P2*Q22*SPM2-32*U1M1*T1P2*Q2*S1M1+32*U1M1*T1P2*Q2
     &    *SPM1-48*U1M1*T1P2-224*U1M1*T1*Q23*SPM2+16*U1M1*T1*Q22*
     &    S1M1+160*U1M1*T1*Q22*SPM1+80*U1M1*T1*Q2-128*U1M1*Q23*
     &    SPM1-32*U1M1*Q22-288*T1P3*Q2*SPM3-32*T1P3*SPM2+384*T1P2*
     &    Q22*SPM3-576*T1P2*Q2*SPM2-64*T1P2*SPM1-96*T1*Q23*SPM3+
     &    960*T1*Q22*SPM2+32*T1*Q2*S1M1-224*T1*Q2*SPM1-80*T1-128*
     &    T1M1*Q23*SPM1-32*T1M1*Q22-320*Q23*SPM2-32*Q22*S1M1+
     &    448*Q22*SPM1+96*Q2)
      VPS(51) =
     &  +LOG3*LHM2*(192*U1*T1P2*TM1-64*U1*T1*TM1*Q2-24*U1M1*
     &  T1P5*TM2+56*U1M1*T1P4*TM1+16*U1M1*T1P4*TM2*Q2-120*U1M1*
     &  T1P3*TM1*Q2+40*U1M1*T1P3*TM2*Q22+96*U1M1*T1P2*TM1*Q22-32
     &  *U1M1*T1*TM1*Q23-16*T1P4*TM2+216*T1P3*TM1-16*T1P3*TM2*Q2
     &  -280*T1P2*TM1*Q2+96*T1*TM1*Q22)
     &  +LOG3*LHM4*(-144*U1*T1P4*TM1+288*U1*T1P3*TM1*Q2-144*U1
     &  *T1P2*TM1*Q22-8*U1M1*T1P6*TM1+40*U1M1*T1P5*TM1*Q2-104*
     &  U1M1*T1P4*TM1*Q22+120*U1M1*T1P3*TM1*Q23-48*U1M1*T1P2*TM1*
     &  Q24-136*T1P5*TM1+408*T1P4*TM1*Q2-408*T1P3*TM1*Q22+136*
     &  T1P2*TM1*Q23)
     &  +LOG3*(24*U1M1*T1P3*TM2-48*U1M1*T1P2*TM1+32*U1M1*T1*
     &  TM1*Q2-32*U1M1*T1*TM2*Q22+32*U1M1*TM1*Q22+32*T1P2*TM2
     &  -64*T1*TM1+32*T1*TM2*Q2-32*TM1*Q2)
     &  +LOG4*LHPM2*(-24*U1P5*T1M1*UM2+56*U1P4*T1M1*UM1+16*
     &  U1P4*T1M1*UM2*Q2-16*U1P4*UM2-120*U1P3*T1M1*UM1*Q2+40*U1P3*
     &  T1M1*UM2*Q22+216*U1P3*UM1-16*U1P3*UM2*Q2+192*U1P2*T1*UM1
     &  +96*U1P2*T1M1*UM1*Q22-280*U1P2*UM1*Q2-64*U1*T1*UM1*Q2-32
     &  *U1*T1M1*UM1*Q23+96*U1*UM1*Q22)
      VPS(52) =
     &  +LOG4*LHPM4*(-8*U1P6*T1M1*UM1+40*U1P5*T1M1*UM1*Q2-
     &  136*U1P5*UM1-144*U1P4*T1*UM1-104*U1P4*T1M1*UM1*Q22+408*
     &  U1P4*UM1*Q2+288*U1P3*T1*UM1*Q2+120*U1P3*T1M1*UM1*Q23-408*
     &  U1P3*UM1*Q22-144*U1P2*T1*UM1*Q22-48*U1P2*T1M1*UM1*Q24+
     &  136*U1P2*UM1*Q23)
     &  +LOG4*(24*U1P3*T1M1*UM2-48*U1P2*T1M1*UM1+32*U1P2*UM2
     &  +32*U1*T1M1*UM1*Q2-32*U1*T1M1*UM2*Q22-64*U1*UM1+32*U1*
     &  UM2*Q2+32*T1M1*UM1*Q22-32*UM1*Q2)
     &  +DLOG2*SQM*(-64*U1P2*T1M1+192*U1*T1M1*Q2-64*U1-64*
     &  U1M1*T1P2+192*U1M1*T1*Q2+128*TB*Q23-256*U1M1*Q22
     &  -64*T1-256*T1M1*Q22+256*Q2)
     &  +DLOG3*(-32-16*U1*T1M1-32*U1M1*T1-32*TB*Q22
     &  +64*U1M1*Q2+32*T1M1*Q2)
     &  +DLOG4*(-32-32*U1*T1M1-16*U1M1*T1-32*TB*Q22
     &  +32*U1M1*Q2+64*T1M1*Q2)
     &  +DLOG1*SQM*(96*U1P2*T1M1-288*U1*T1M1*Q2+224*U1+96*
     &  U1M1*T1P2-288*U1M1*T1*Q2-128*TB*Q23+320*U1M1*Q22
     &  +224*T1+320*T1M1*Q22-512*Q2)
      VPS(53) =
     &  +ZETA2*SQM*(-272*U1P2*T1M1+816*U1*T1M1*Q2-464*U1
     &  -272*U1M1*T1P2+816*U1M1*T1*Q2+448*TB*Q23-992*
     &  U1M1*Q22-464*T1-992*T1M1*Q22+1280*Q2)
     &  +ZETA2*LHM1*(16*U1*T1M1*Q2-80*U1-112*U1M1*T1P2+256*
     &  U1M1*T1*Q2+32*TB*Q23-160*U1M1*Q22-160*T1-32*
     &  T1M1*Q22+160*Q2)
     &  +ZETA2*LHM3*(128*U1*T1P2-192*U1*T1*Q2+64*U1*Q22+112*
     &  U1M1*T1P4-416*U1M1*T1P3*Q2+560*U1M1*T1P2*Q22-320*U1M1*T1*
     &  Q23+64*U1M1*Q24+208*T1P3-496*T1P2*Q2+384*T1*Q22-96*Q23
     &  )
     &  +ZETA2*LHM5*(-64*U1*T1P4+192*U1*T1P3*Q2-192*U1*T1P2*
     &  Q22+64*U1*T1*Q23-32*U1M1*T1P6+160*U1M1*T1P5*Q2-320*U1M1*
     &  T1P4*Q22+320*U1M1*T1P3*Q23-160*U1M1*T1P2*Q24+32*U1M1*T1*
     &  Q25-80*T1P5+304*T1P4*Q2-432*T1P3*Q22+272*T1P2*Q23-64*T1*
     &  Q24)
     &  +ZETA2*LHPM1*(-112*U1P2*T1M1+256*U1*T1M1*Q2-160*U1+
     &  16*U1M1*T1*Q2+32*TB*Q23-32*U1M1*Q22-80*T1-160*
     &  T1M1*Q22+160*Q2)
      VPS(54) =
     &  +ZETA2*LHPM3*(112*U1P4*T1M1-416*U1P3*T1M1*Q2+208*U1P3
     &  +128*U1P2*T1+560*U1P2*T1M1*Q22-496*U1P2*Q2-192*U1*T1*Q2-
     &  320*U1*T1M1*Q23+384*U1*Q22+64*T1*Q22+64*T1M1*Q24-96*
     &  Q23)
     &  +ZETA2*LHPM5*(-32*U1P6*T1M1+160*U1P5*T1M1*Q2-80*U1P5
     &  -64*U1P4*T1-320*U1P4*T1M1*Q22+304*U1P4*Q2+192*U1P3*T1*Q2+
     &  320*U1P3*T1M1*Q23-432*U1P3*Q22-192*U1P2*T1*Q22-160*U1P2*
     &  T1M1*Q24+272*U1P2*Q23+64*U1*T1*Q23+32*U1*T1M1*Q25-64*U1
     &  *Q24)
     &  +ZETA2*(64+96*U1P4*T1M1*SPM3-192*U1P3*T1M1*Q2*SPM3+
     &  288*U1P3*T1M1*SPM2+288*U1P3*SPM3+384*U1P2*T1*SPM3+96*U1P2*
     &  T1M1*Q22*SPM3-576*U1P2*T1M1*Q2*SPM2+336*U1P2*T1M1*SPM1-
     &  384*U1P2*Q2*SPM3+768*U1P2*SPM2+384*U1*T1P2*SPM3-384*U1*T1*Q2
     &  *SPM3+960*U1*T1*SPM2+288*U1*T1M1*Q22*SPM2-672*U1*T1M1*Q2*
     &  SPM1+48*U1*T1M1+96*U1*Q22*SPM3-1152*U1*Q2*SPM2+720*U1*
     &  SPM1+96*U1M1*T1P4*SPM3-192*U1M1*T1P3*Q2*SPM3+288*U1M1*
     &  T1P3*SPM2+96*U1M1*T1P2*Q22*SPM3-576*U1M1*T1P2*Q2*SPM2+336
     &  *U1M1*T1P2*SPM1+288*U1M1*T1*Q22*SPM2-672*U1M1*T1*Q2*SPM1)
      VPS(55) = ZETA2*(
     &    +48*U1M1*T1+64*TB*Q22+384*U1M1*Q22*SPM1-96*
     &    U1M1*Q2+288*T1P3*SPM3-384*T1P2*Q2*SPM3+768*T1P2*SPM2+96*
     &    T1*Q22*SPM3-1152*T1*Q2*SPM2+720*T1*SPM1+384*T1M1*Q22*
     &    SPM1-96*T1M1*Q2+384*Q22*SPM2-1152*Q2*SPM1)
     &    +SQM*LOG8*LOGQ2*(48*U1P2*T1M1-144*U1*T1M1*Q2+112*U1
     &    +48*U1M1*T1P2-144*U1M1*T1*Q2-64*TB*Q23+160*U1M1*
     &    Q22+112*T1+160*T1M1*Q22-256*Q2)
     &    +SQM*DLOGQ1*(96*U1P2*T1M1-288*U1*T1M1*Q2+224*U1+96*
     &    U1M1*T1P2-288*U1M1*T1*Q2-128*TB*Q23+320*U1M1*Q22
     &    +224*T1+320*T1M1*Q22-512*Q2)
     &    +SQM*DLOGQ2*(96*U1P2*T1M1-288*U1*T1M1*Q2+224*U1+96*
     &    U1M1*T1P2-288*U1M1*T1*Q2-128*TB*Q23+320*U1M1*Q22
     &    +224*T1+320*T1M1*Q22-512*Q2)
     &    +SQM*DLOGQ3*(96*U1P2*T1M1-288*U1*T1M1*Q2+224*U1+96*
     &    U1M1*T1P2-288*U1M1*T1*Q2-128*TB*Q23+320*U1M1*Q22
     &    +224*T1+320*T1M1*Q22-512*Q2)
      VPS(56) =
     &  +SQM*DLOGQ4*(-96*U1P2*T1M1+288*U1*T1M1*Q2-224*U1-
     &  96*U1M1*T1P2+288*U1M1*T1*Q2+128*TB*Q23-320*U1M1*
     &  Q22-224*T1-320*T1M1*Q22+512*Q2)
     &  +SQM*LOGQ3X2*(48*U1P2*T1M1-144*U1*T1M1*Q2+112*U1+48
     &  *U1M1*T1P2-144*U1M1*T1*Q2-64*TB*Q23+160*U1M1*Q22
     &  +112*T1+160*T1M1*Q22-256*Q2)
     &  +LOG9*LHM2*(-96*U1*T1*X1+96*U1*T1*X2+32*U1*T1M1*Q22*
     &  X1-32*U1*T1M1*Q22*X2-64*U1*Q2*X1+64*U1*Q2*X2+64*U1M1*T1P3*
     &  X1-64*U1M1*T1P3*X2-248*U1M1*T1P2*Q2*X1+248*U1M1*T1P2*Q2*X2
     &  +328*U1M1*T1*Q22*X1-328*U1M1*T1*Q22*X2+48*TB*Q24*
     &  X1-48*TB*Q24*X2-224*U1M1*Q23*X1+224*U1M1*Q23*X2
     &  -32*T1P2*X1+32*T1P2*X2-88*T1*Q2*X1+88*T1*Q2*X2-64*T1M1*
     &  Q23*X1+64*T1M1*Q23*X2+184*Q22*X1-184*Q22*X2)
      VPS(57) =
     &  +LOG9*LHM4*(80*U1*T1P3*X1-80*U1*T1P3*X2-96*U1*T1P2*Q2*X1
     &  +96*U1*T1P2*Q2*X2-48*U1*T1*Q22*X1+48*U1*T1*Q22*X2+64*U1*
     &  Q23*X1-64*U1*Q23*X2-24*U1M1*T1P5*X1+24*U1M1*T1P5*X2+120*
     &  U1M1*T1P4*Q2*X1-120*U1M1*T1P4*Q2*X2-216*U1M1*T1P3*Q22*X1+
     &  216*U1M1*T1P3*Q22*X2+200*U1M1*T1P2*Q23*X1-200*U1M1*T1P2*Q23
     &  *X2-112*U1M1*T1*Q24*X1+112*U1M1*T1*Q24*X2+32*U1M1*Q25*X1
     &  -32*U1M1*Q25*X2+56*T1P4*X1-56*T1P4*X2-104*T1P3*Q2*X1+104*
     &  T1P3*Q2*X2-24*T1P2*Q22*X1+24*T1P2*Q22*X2+136*T1*Q23*X1-136
     &  *T1*Q23*X2-64*Q24*X1+64*Q24*X2)
     &  +LOG9*LHPM2*(64*U1P3*T1M1*X1-64*U1P3*T1M1*X2-248*U1P2*
     &  T1M1*Q2*X1+248*U1P2*T1M1*Q2*X2-32*U1P2*X1+32*U1P2*X2-96*U1*
     &  T1*X1+96*U1*T1*X2+328*U1*T1M1*Q22*X1-328*U1*T1M1*Q22*X2-
     &  88*U1*Q2*X1+88*U1*Q2*X2+32*U1M1*T1*Q22*X1-32*U1M1*T1*Q22*X2
     &  +48*TB*Q24*X1-48*TB*Q24*X2-64*U1M1*Q23*X1
     &  +64*U1M1*Q23*X2-64*T1*Q2*X1+64*T1*Q2*X2-224*T1M1*Q23*X1
     &  +224*T1M1*Q23*X2+184*Q22*X1-184*Q22*X2)
      VPS(58) =
     &  +LOG9*LHPM4*(-24*U1P5*T1M1*X1+24*U1P5*T1M1*X2+120*
     &  U1P4*T1M1*Q2*X1-120*U1P4*T1M1*Q2*X2+56*U1P4*X1-56*U1P4*X2+
     &  80*U1P3*T1*X1-80*U1P3*T1*X2-216*U1P3*T1M1*Q22*X1+216*U1P3*
     &  T1M1*Q22*X2-104*U1P3*Q2*X1+104*U1P3*Q2*X2-96*U1P2*T1*Q2*X1+
     &  96*U1P2*T1*Q2*X2+200*U1P2*T1M1*Q23*X1-200*U1P2*T1M1*Q23*X2-
     &  24*U1P2*Q22*X1+24*U1P2*Q22*X2-48*U1*T1*Q22*X1+48*U1*T1*Q22*
     &  X2-112*U1*T1M1*Q24*X1+112*U1*T1M1*Q24*X2+136*U1*Q23*X1-
     &  136*U1*Q23*X2+64*T1*Q23*X1-64*T1*Q23*X2+32*T1M1*Q25*X1-
     &  32*T1M1*Q25*X2-64*Q24*X1+64*Q24*X2)
     &  +LOG9*(96*U1P3*T1M1*Q2*SPM3*X1-96*U1P3*T1M1*Q2*SPM3*X2
     &  -96*U1P2*T1M1*Q22*SPM3*X1+96*U1P2*T1M1*Q22*SPM3*X2+192*
     &  U1P2*T1M1*Q2*SPM2*X1-192*U1P2*T1M1*Q2*SPM2*X2-16*U1P2*T1M1*
     &  SPM1*X1+16*U1P2*T1M1*SPM1*X2+192*U1P2*Q2*SPM3*X1-192*U1P2*
     &  Q2*SPM3*X2-64*U1P2*SPM2*X1+64*U1P2*SPM2*X2+192*U1*T1*Q2*
     &  SPM3*X1-192*U1*T1*Q2*SPM3*X2-128*U1*T1*SPM2*X1+128*U1*T1*
     &  SPM2*X2-224*U1*T1M1*Q22*SPM2*X1+224*U1*T1M1*Q22*SPM2*X2+
     &  128*U1*T1M1*Q2*SPM1*X1-128*U1*T1M1*Q2*SPM1*X2-40*U1*T1M1*X1)
      VPS(59) = LOG9*(
     &    +40*U1*T1M1*X2-96*U1*Q22*SPM3*X1+96*U1*Q22*SPM3*X2+448*
     &    U1*Q2*SPM2*X1-448*U1*Q2*SPM2*X2-144*U1*SPM1*X1+144*U1*SPM1*
     &    X2+96*U1M1*T1P3*Q2*SPM3*X1-96*U1M1*T1P3*Q2*SPM3*X2-96*U1M1
     &    *T1P2*Q22*SPM3*X1+96*U1M1*T1P2*Q22*SPM3*X2+192*U1M1*T1P2*Q2
     &    *SPM2*X1-192*U1M1*T1P2*Q2*SPM2*X2-16*U1M1*T1P2*SPM1*X1+16*
     &    U1M1*T1P2*SPM1*X2-224*U1M1*T1*Q22*SPM2*X1+224*U1M1*T1*Q22*
     &    SPM2*X2+128*U1M1*T1*Q2*SPM1*X1-128*U1M1*T1*Q2*SPM1*X2-40*
     &    U1M1*T1*X1+40*U1M1*T1*X2-128*U1M1*Q22*SPM1*X1+128*U1M1*
     &    Q22*SPM1*X2+96*U1M1*Q2*X1-96*U1M1*Q2*X2+192*T1P2*Q2*SPM3*
     &    X1-192*T1P2*Q2*SPM3*X2-64*T1P2*SPM2*X1+64*T1P2*SPM2*X2-96*
     &    T1*Q22*SPM3*X1+96*T1*Q22*SPM3*X2+448*T1*Q2*SPM2*X1-448*T1*
     &    Q2*SPM2*X2-144*T1*SPM1*X1+144*T1*SPM1*X2-128*T1M1*Q22*
     &    SPM1*X1+128*T1M1*Q22*SPM1*X2+96*T1M1*Q2*X1-96*T1M1*Q2*X2
     &    -320*Q22*SPM2*X1+320*Q22*SPM2*X2+320*Q2*SPM1*X1-320*Q2*
     &    SPM1*X2-112*X1+112*X2)
      VPS(60) =
     &  +LOG10*LHM2*(96*U1*T1*X1-96*U1*T1*X2-32*U1*T1M1*Q22*X1
     &  +32*U1*T1M1*Q22*X2+64*U1*Q2*X1-64*U1*Q2*X2-64*U1M1*T1P3*X1
     &  +64*U1M1*T1P3*X2+248*U1M1*T1P2*Q2*X1-248*U1M1*T1P2*Q2*X2-
     &  328*U1M1*T1*Q22*X1+328*U1M1*T1*Q22*X2-48*TB*Q24*X1
     &  +48*TB*Q24*X2+224*U1M1*Q23*X1-224*U1M1*Q23*X2+
     &  32*T1P2*X1-32*T1P2*X2+88*T1*Q2*X1-88*T1*Q2*X2+64*T1M1*Q23*
     &  X1-64*T1M1*Q23*X2-184*Q22*X1+184*Q22*X2)
     &  +LOG10*LHM4*(-80*U1*T1P3*X1+80*U1*T1P3*X2+96*U1*T1P2*Q2
     &  *X1-96*U1*T1P2*Q2*X2+48*U1*T1*Q22*X1-48*U1*T1*Q22*X2-64*U1*
     &  Q23*X1+64*U1*Q23*X2+24*U1M1*T1P5*X1-24*U1M1*T1P5*X2-120*
     &  U1M1*T1P4*Q2*X1+120*U1M1*T1P4*Q2*X2+216*U1M1*T1P3*Q22*X1-
     &  216*U1M1*T1P3*Q22*X2-200*U1M1*T1P2*Q23*X1+200*U1M1*T1P2*Q23
     &  *X2+112*U1M1*T1*Q24*X1-112*U1M1*T1*Q24*X2-32*U1M1*Q25*X1
     &  +32*U1M1*Q25*X2-56*T1P4*X1+56*T1P4*X2+104*T1P3*Q2*X1-104*
     &  T1P3*Q2*X2+24*T1P2*Q22*X1-24*T1P2*Q22*X2-136*T1*Q23*X1+136
     &  *T1*Q23*X2+64*Q24*X1-64*Q24*X2)
      VPS(61) =
     &  +LOG10*LHPM2*(-64*U1P3*T1M1*X1+64*U1P3*T1M1*X2+248*
     &  U1P2*T1M1*Q2*X1-248*U1P2*T1M1*Q2*X2+32*U1P2*X1-32*U1P2*X2+
     &  96*U1*T1*X1-96*U1*T1*X2-328*U1*T1M1*Q22*X1+328*U1*T1M1*Q22*
     &  X2+88*U1*Q2*X1-88*U1*Q2*X2-32*U1M1*T1*Q22*X1+32*U1M1*T1*
     &  Q22*X2-48*TB*Q24*X1+48*TB*Q24*X2+64*U1M1*
     &  Q23*X1-64*U1M1*Q23*X2+64*T1*Q2*X1-64*T1*Q2*X2+224*T1M1*
     &  Q23*X1-224*T1M1*Q23*X2-184*Q22*X1+184*Q22*X2)
     &  +LOG10*LHPM4*(24*U1P5*T1M1*X1-24*U1P5*T1M1*X2-120*U1P4*
     &  T1M1*Q2*X1+120*U1P4*T1M1*Q2*X2-56*U1P4*X1+56*U1P4*X2-80*
     &  U1P3*T1*X1+80*U1P3*T1*X2+216*U1P3*T1M1*Q22*X1-216*U1P3*T1M1*
     &  Q22*X2+104*U1P3*Q2*X1-104*U1P3*Q2*X2+96*U1P2*T1*Q2*X1-96*
     &  U1P2*T1*Q2*X2-200*U1P2*T1M1*Q23*X1+200*U1P2*T1M1*Q23*X2+24*
     &  U1P2*Q22*X1-24*U1P2*Q22*X2+48*U1*T1*Q22*X1-48*U1*T1*Q22*X2
     &  +112*U1*T1M1*Q24*X1-112*U1*T1M1*Q24*X2-136*U1*Q23*X1+136
     &  *U1*Q23*X2-64*T1*Q23*X1+64*T1*Q23*X2-32*T1M1*Q25*X1+32*
     &  T1M1*Q25*X2+64*Q24*X1-64*Q24*X2)
      VPS(62) =
     &  +LOG10*(-96*U1P3*T1M1*Q2*SPM3*X1+96*U1P3*T1M1*Q2*SPM3*
     &  X2+96*U1P2*T1M1*Q22*SPM3*X1-96*U1P2*T1M1*Q22*SPM3*X2-192*
     &  U1P2*T1M1*Q2*SPM2*X1+192*U1P2*T1M1*Q2*SPM2*X2+16*U1P2*T1M1*
     &  SPM1*X1-16*U1P2*T1M1*SPM1*X2-192*U1P2*Q2*SPM3*X1+192*U1P2*
     &  Q2*SPM3*X2+64*U1P2*SPM2*X1-64*U1P2*SPM2*X2-192*U1*T1*Q2*
     &  SPM3*X1+192*U1*T1*Q2*SPM3*X2+128*U1*T1*SPM2*X1-128*U1*T1*
     &  SPM2*X2+224*U1*T1M1*Q22*SPM2*X1-224*U1*T1M1*Q22*SPM2*X2-
     &  128*U1*T1M1*Q2*SPM1*X1+128*U1*T1M1*Q2*SPM1*X2+40*U1*T1M1*X1
     &  -40*U1*T1M1*X2+96*U1*Q22*SPM3*X1-96*U1*Q22*SPM3*X2-448*
     &  U1*Q2*SPM2*X1+448*U1*Q2*SPM2*X2+144*U1*SPM1*X1-144*U1*SPM1*
     &  X2-96*U1M1*T1P3*Q2*SPM3*X1+96*U1M1*T1P3*Q2*SPM3*X2+96*U1M1
     &  *T1P2*Q22*SPM3*X1-96*U1M1*T1P2*Q22*SPM3*X2-192*U1M1*T1P2*Q2
     &  *SPM2*X1+192*U1M1*T1P2*Q2*SPM2*X2+16*U1M1*T1P2*SPM1*X1-16*
     &  U1M1*T1P2*SPM1*X2+224*U1M1*T1*Q22*SPM2*X1-224*U1M1*T1*Q22*
     &  SPM2*X2-128*U1M1*T1*Q2*SPM1*X1+128*U1M1*T1*Q2*SPM1*X2+40*
     &  U1M1*T1*X1-40*U1M1*T1*X2+128*U1M1*Q22*SPM1*X1-128*U1M1*
     &  Q22*SPM1*X2-96*U1M1*Q2*X1+96*U1M1*Q2*X2-192*T1P2*Q2*SPM3*X1)
      VPS(63) = LOG10*(
     &    +192*T1P2*Q2*SPM3*X2+64*T1P2*SPM2*X1-64*T1P2*SPM2*X2+96*
     &    T1*Q22*SPM3*X1-96*T1*Q22*SPM3*X2-448*T1*Q2*SPM2*X1+448*T1*
     &    Q2*SPM2*X2+144*T1*SPM1*X1-144*T1*SPM1*X2+128*T1M1*Q22*
     &    SPM1*X1-128*T1M1*Q22*SPM1*X2-96*T1M1*Q2*X1+96*T1M1*Q2*X2
     &    +320*Q22*SPM2*X1-320*Q22*SPM2*X2-320*Q2*SPM1*X1+320*Q2*
     &    SPM1*X2+112*X1-112*X2)
     &    +LHM1*DLOGQ6T*(-16*U1*T1M1*Q2+80*U1+112*U1M1*T1P2-256
     &    *U1M1*T1*Q2-32*TB*Q23+160*U1M1*Q22+160*T1+32*
     &    T1M1*Q22-160*Q2)
     &    +LHM1*DLOGQ7T*(-16*U1*T1M1*Q2+80*U1+112*U1M1*T1P2-256
     &    *U1M1*T1*Q2-32*TB*Q23+160*U1M1*Q22+160*T1+32*
     &    T1M1*Q22-160*Q2)
     &    +LHM1*DLOGQ8T*(16*U1*T1M1*Q2-80*U1-112*U1M1*T1P2+256*
     &    U1M1*T1*Q2+32*TB*Q23-160*U1M1*Q22-160*T1-32*
     &    T1M1*Q22+160*Q2)
     &    +LHM1*DLOGQ9T*(16*U1*T1M1*Q2-80*U1-112*U1M1*T1P2+256*
     &    U1M1*T1*Q2+32*TB*Q23-160*U1M1*Q22-160*T1-32*
     &    T1M1*Q22+160*Q2)
      VPS(64) =
     &  +LHM1*DLOGQ10T*(16*U1*T1M1*Q2-80*U1-112*U1M1*T1P2+256*
     &  U1M1*T1*Q2+32*TB*Q23-160*U1M1*Q22-160*T1-32*
     &  T1M1*Q22+160*Q2)
     &  +LHM1*DLOGQ11T*(16*U1*T1M1*Q2-80*U1-112*U1M1*T1P2+256*
     &  U1M1*T1*Q2+32*TB*Q23-160*U1M1*Q22-160*T1-32*
     &  T1M1*Q22+160*Q2)
     &  +LHM1*DLOGQ12T*(-16*U1*T1M1*Q2+80*U1+112*U1M1*T1P2-
     &  256*U1M1*T1*Q2-32*TB*Q23+160*U1M1*Q22+160*T1+32*
     &  T1M1*Q22-160*Q2)
     &  +LHM1*DLOGQ13T*(-32*U1*T1M1*Q2+160*U1+224*U1M1*T1P2-
     &  512*U1M1*T1*Q2-64*TB*Q23+320*U1M1*Q22+320*T1+64*
     &  T1M1*Q22-320*Q2)
     &  +LHM2*(48*U1*T1+32*U1*T1M1*Q22-80*U1*Q2+32*U1M1*T1P4
     &  *TM1-24*U1M1*T1P3-32*U1M1*T1P2*TM1*Q22-32*U1M1*T1P2*Q2+
     &  88*U1M1*T1*Q22+16*TB*Q24-48*U1M1*Q23+32*T1P3*TM1
     &  +32*T1P2*TM1*Q2+16*T1P2-160*T1*Q2-32*T1M1*Q23+112*Q22)
      VPS(65) =
     &  +LHM3*DLOGQ6T*(-128*U1*T1P2+192*U1*T1*Q2-64*U1*Q22-112
     &  *U1M1*T1P4+416*U1M1*T1P3*Q2-560*U1M1*T1P2*Q22+320*U1M1*T1*
     &  Q23-64*U1M1*Q24-208*T1P3+496*T1P2*Q2-384*T1*Q22+96*Q23
     &  )
     &  +LHM3*DLOGQ7T*(-128*U1*T1P2+192*U1*T1*Q2-64*U1*Q22-112
     &  *U1M1*T1P4+416*U1M1*T1P3*Q2-560*U1M1*T1P2*Q22+320*U1M1*T1*
     &  Q23-64*U1M1*Q24-208*T1P3+496*T1P2*Q2-384*T1*Q22+96*Q23
     &  )
     &  +LHM3*DLOGQ8T*(128*U1*T1P2-192*U1*T1*Q2+64*U1*Q22+112*
     &  U1M1*T1P4-416*U1M1*T1P3*Q2+560*U1M1*T1P2*Q22-320*U1M1*T1*
     &  Q23+64*U1M1*Q24+208*T1P3-496*T1P2*Q2+384*T1*Q22-96*Q23
     &  )
     &  +LHM3*DLOGQ9T*(128*U1*T1P2-192*U1*T1*Q2+64*U1*Q22+112*
     &  U1M1*T1P4-416*U1M1*T1P3*Q2+560*U1M1*T1P2*Q22-320*U1M1*T1*
     &  Q23+64*U1M1*Q24+208*T1P3-496*T1P2*Q2+384*T1*Q22-96*Q23
     &  )
      VPS(66) =
     &  +LHM3*DLOGQ10T*(128*U1*T1P2-192*U1*T1*Q2+64*U1*Q22+112*
     &  U1M1*T1P4-416*U1M1*T1P3*Q2+560*U1M1*T1P2*Q22-320*U1M1*T1*
     &  Q23+64*U1M1*Q24+208*T1P3-496*T1P2*Q2+384*T1*Q22-96*Q23
     &  )
     &  +LHM3*DLOGQ11T*(128*U1*T1P2-192*U1*T1*Q2+64*U1*Q22+112*
     &  U1M1*T1P4-416*U1M1*T1P3*Q2+560*U1M1*T1P2*Q22-320*U1M1*T1*
     &  Q23+64*U1M1*Q24+208*T1P3-496*T1P2*Q2+384*T1*Q22-96*Q23
     &  )
     &  +LHM3*DLOGQ12T*(-128*U1*T1P2+192*U1*T1*Q2-64*U1*Q22-
     &  112*U1M1*T1P4+416*U1M1*T1P3*Q2-560*U1M1*T1P2*Q22+320*U1M1*
     &  T1*Q23-64*U1M1*Q24-208*T1P3+496*T1P2*Q2-384*T1*Q22+96*
     &  Q23)
     &  +LHM3*DLOGQ13T*(-256*U1*T1P2+384*U1*T1*Q2-128*U1*Q22-
     &  224*U1M1*T1P4+832*U1M1*T1P3*Q2-1120*U1M1*T1P2*Q22+640*U1M1
     &  *T1*Q23-128*U1M1*Q24-416*T1P3+992*T1P2*Q2-768*T1*Q22+
     &  192*Q23)
      VPS(67) =
     &  +LHM5*DLOGQ6T*(64*U1*T1P4-192*U1*T1P3*Q2+192*U1*T1P2*Q22
     &  -64*U1*T1*Q23+32*U1M1*T1P6-160*U1M1*T1P5*Q2+320*U1M1*T1P4
     &  *Q22-320*U1M1*T1P3*Q23+160*U1M1*T1P2*Q24-32*U1M1*T1*Q25
     &  +80*T1P5-304*T1P4*Q2+432*T1P3*Q22-272*T1P2*Q23+64*T1*Q24
     &  )
     &  +LHM5*DLOGQ7T*(64*U1*T1P4-192*U1*T1P3*Q2+192*U1*T1P2*Q22
     &  -64*U1*T1*Q23+32*U1M1*T1P6-160*U1M1*T1P5*Q2+320*U1M1*T1P4
     &  *Q22-320*U1M1*T1P3*Q23+160*U1M1*T1P2*Q24-32*U1M1*T1*Q25
     &  +80*T1P5-304*T1P4*Q2+432*T1P3*Q22-272*T1P2*Q23+64*T1*Q24
     &  )
     &  +LHM5*DLOGQ8T*(-64*U1*T1P4+192*U1*T1P3*Q2-192*U1*T1P2*
     &  Q22+64*U1*T1*Q23-32*U1M1*T1P6+160*U1M1*T1P5*Q2-320*U1M1*
     &  T1P4*Q22+320*U1M1*T1P3*Q23-160*U1M1*T1P2*Q24+32*U1M1*T1*
     &  Q25-80*T1P5+304*T1P4*Q2-432*T1P3*Q22+272*T1P2*Q23-64*T1*
     &  Q24)
      VPS(68) =
     &  +LHM5*DLOGQ9T*(-64*U1*T1P4+192*U1*T1P3*Q2-192*U1*T1P2*
     &  Q22+64*U1*T1*Q23-32*U1M1*T1P6+160*U1M1*T1P5*Q2-320*U1M1*
     &  T1P4*Q22+320*U1M1*T1P3*Q23-160*U1M1*T1P2*Q24+32*U1M1*T1*
     &  Q25-80*T1P5+304*T1P4*Q2-432*T1P3*Q22+272*T1P2*Q23-64*T1*
     &  Q24)
     &  +LHM5*DLOGQ10T*(-64*U1*T1P4+192*U1*T1P3*Q2-192*U1*T1P2*
     &  Q22+64*U1*T1*Q23-32*U1M1*T1P6+160*U1M1*T1P5*Q2-320*U1M1*
     &  T1P4*Q22+320*U1M1*T1P3*Q23-160*U1M1*T1P2*Q24+32*U1M1*T1*
     &  Q25-80*T1P5+304*T1P4*Q2-432*T1P3*Q22+272*T1P2*Q23-64*T1*
     &  Q24)
     &  +LHM5*DLOGQ11T*(-64*U1*T1P4+192*U1*T1P3*Q2-192*U1*T1P2*
     &  Q22+64*U1*T1*Q23-32*U1M1*T1P6+160*U1M1*T1P5*Q2-320*U1M1*
     &  T1P4*Q22+320*U1M1*T1P3*Q23-160*U1M1*T1P2*Q24+32*U1M1*T1*
     &  Q25-80*T1P5+304*T1P4*Q2-432*T1P3*Q22+272*T1P2*Q23-64*T1*
     &  Q24)
      VPS(69) =
     &  +LHM5*DLOGQ12T*(64*U1*T1P4-192*U1*T1P3*Q2+192*U1*T1P2*Q22
     &  -64*U1*T1*Q23+32*U1M1*T1P6-160*U1M1*T1P5*Q2+320*U1M1*T1P4
     &  *Q22-320*U1M1*T1P3*Q23+160*U1M1*T1P2*Q24-32*U1M1*T1*Q25
     &  +80*T1P5-304*T1P4*Q2+432*T1P3*Q22-272*T1P2*Q23+64*T1*Q24
     &  )
     &  +LHM5*DLOGQ13T*(128*U1*T1P4-384*U1*T1P3*Q2+384*U1*T1P2*Q22
     &  -128*U1*T1*Q23+64*U1M1*T1P6-320*U1M1*T1P5*Q2+640*U1M1*
     &  T1P4*Q22-640*U1M1*T1P3*Q23+320*U1M1*T1P2*Q24-64*U1M1*T1*
     &  Q25+160*T1P5-608*T1P4*Q2+864*T1P3*Q22-544*T1P2*Q23+128*
     &  T1*Q24)
     &  +LHPM1*DLOGQ6U*(112*U1P2*T1M1-256*U1*T1M1*Q2+160*U1-16*
     &  U1M1*T1*Q2-32*TB*Q23+32*U1M1*Q22+80*T1+160*T1M1
     &  *Q22-160*Q2)
     &  +LHPM1*DLOGQ7U*(112*U1P2*T1M1-256*U1*T1M1*Q2+160*U1-16*
     &  U1M1*T1*Q2-32*TB*Q23+32*U1M1*Q22+80*T1+160*T1M1
     &  *Q22-160*Q2)
      VPS(70) =
     &  +LHPM1*DLOGQ8U*(-112*U1P2*T1M1+256*U1*T1M1*Q2-160*U1+
     &  16*U1M1*T1*Q2+32*TB*Q23-32*U1M1*Q22-80*T1-160*
     &  T1M1*Q22+160*Q2)
     &  +LHPM1*DLOGQ9U*(-112*U1P2*T1M1+256*U1*T1M1*Q2-160*U1+
     &  16*U1M1*T1*Q2+32*TB*Q23-32*U1M1*Q22-80*T1-160*
     &  T1M1*Q22+160*Q2)
     &  +LHPM1*DLOGQ10U*(-112*U1P2*T1M1+256*U1*T1M1*Q2-160*U1
     &  +16*U1M1*T1*Q2+32*TB*Q23-32*U1M1*Q22-80*T1-160
     &  *T1M1*Q22+160*Q2)
     &  +LHPM1*DLOGQ11U*(-112*U1P2*T1M1+256*U1*T1M1*Q2-160*U1
     &  +16*U1M1*T1*Q2+32*TB*Q23-32*U1M1*Q22-80*T1-160
     &  *T1M1*Q22+160*Q2)
     &  +LHPM1*DLOGQ12U*(112*U1P2*T1M1-256*U1*T1M1*Q2+160*U1-16
     &  *U1M1*T1*Q2-32*TB*Q23+32*U1M1*Q22+80*T1+160*
     &  T1M1*Q22-160*Q2)
     &  +LHPM1*DLOGQ13U*(224*U1P2*T1M1-512*U1*T1M1*Q2+320*U1-32
     &  *U1M1*T1*Q2-64*TB*Q23+64*U1M1*Q22+160*T1+320*
     &  T1M1*Q22-320*Q2)
      VPS(71) =
     &  +LHPM2*(32*U1P4*T1M1*UM1-24*U1P3*T1M1+32*U1P3*UM1-
     &  32*U1P2*T1M1*UM1*Q22-32*U1P2*T1M1*Q2+32*U1P2*UM1*Q2+16*
     &  U1P2+48*U1*T1+88*U1*T1M1*Q22-160*U1*Q2+32*U1M1*T1*Q22+
     &  16*TB*Q24-32*U1M1*Q23-80*T1*Q2-48*T1M1*Q23+112*
     &  Q22)
     &  +LHPM3*DLOGQ6U*(-112*U1P4*T1M1+416*U1P3*T1M1*Q2-208*
     &  U1P3-128*U1P2*T1-560*U1P2*T1M1*Q22+496*U1P2*Q2+192*U1*T1*Q2
     &  +320*U1*T1M1*Q23-384*U1*Q22-64*T1*Q22-64*T1M1*Q24+96*
     &  Q23)
     &  +LHPM3*DLOGQ7U*(-112*U1P4*T1M1+416*U1P3*T1M1*Q2-208*
     &  U1P3-128*U1P2*T1-560*U1P2*T1M1*Q22+496*U1P2*Q2+192*U1*T1*Q2
     &  +320*U1*T1M1*Q23-384*U1*Q22-64*T1*Q22-64*T1M1*Q24+96*
     &  Q23)
     &  +LHPM3*DLOGQ8U*(112*U1P4*T1M1-416*U1P3*T1M1*Q2+208*U1P3
     &  +128*U1P2*T1+560*U1P2*T1M1*Q22-496*U1P2*Q2-192*U1*T1*Q2-
     &  320*U1*T1M1*Q23+384*U1*Q22+64*T1*Q22+64*T1M1*Q24-96*
     &  Q23)
      VPS(72) =
     &  +LHPM3*DLOGQ9U*(112*U1P4*T1M1-416*U1P3*T1M1*Q2+208*U1P3
     &  +128*U1P2*T1+560*U1P2*T1M1*Q22-496*U1P2*Q2-192*U1*T1*Q2-
     &  320*U1*T1M1*Q23+384*U1*Q22+64*T1*Q22+64*T1M1*Q24-96*
     &  Q23)
     &  +LHPM3*DLOGQ10U*(112*U1P4*T1M1-416*U1P3*T1M1*Q2+208*U1P3
     &  +128*U1P2*T1+560*U1P2*T1M1*Q22-496*U1P2*Q2-192*U1*T1*Q2-
     &  320*U1*T1M1*Q23+384*U1*Q22+64*T1*Q22+64*T1M1*Q24-96*
     &  Q23)
     &  +LHPM3*DLOGQ11U*(112*U1P4*T1M1-416*U1P3*T1M1*Q2+208*U1P3
     &  +128*U1P2*T1+560*U1P2*T1M1*Q22-496*U1P2*Q2-192*U1*T1*Q2-
     &  320*U1*T1M1*Q23+384*U1*Q22+64*T1*Q22+64*T1M1*Q24-96*
     &  Q23)
     &  +LHPM3*DLOGQ12U*(-112*U1P4*T1M1+416*U1P3*T1M1*Q2-208*
     &  U1P3-128*U1P2*T1-560*U1P2*T1M1*Q22+496*U1P2*Q2+192*U1*T1*Q2
     &  +320*U1*T1M1*Q23-384*U1*Q22-64*T1*Q22-64*T1M1*Q24+96*
     &  Q23)
      VPS(73) =
     &  +LHPM3*DLOGQ13U*(-224*U1P4*T1M1+832*U1P3*T1M1*Q2-416*
     &  U1P3-256*U1P2*T1-1120*U1P2*T1M1*Q22+992*U1P2*Q2+384*U1*T1*
     &  Q2+640*U1*T1M1*Q23-768*U1*Q22-128*T1*Q22-128*T1M1*Q24
     &  +192*Q23)
     &  +LHPM5*DLOGQ6U*(32*U1P6*T1M1-160*U1P5*T1M1*Q2+80*U1P5+
     &  64*U1P4*T1+320*U1P4*T1M1*Q22-304*U1P4*Q2-192*U1P3*T1*Q2-320
     &  *U1P3*T1M1*Q23+432*U1P3*Q22+192*U1P2*T1*Q22+160*U1P2*T1M1*
     &  Q24-272*U1P2*Q23-64*U1*T1*Q23-32*U1*T1M1*Q25+64*U1*Q24
     &  )
     &  +LHPM5*DLOGQ7U*(32*U1P6*T1M1-160*U1P5*T1M1*Q2+80*U1P5+
     &  64*U1P4*T1+320*U1P4*T1M1*Q22-304*U1P4*Q2-192*U1P3*T1*Q2-320
     &  *U1P3*T1M1*Q23+432*U1P3*Q22+192*U1P2*T1*Q22+160*U1P2*T1M1*
     &  Q24-272*U1P2*Q23-64*U1*T1*Q23-32*U1*T1M1*Q25+64*U1*Q24
     &  )
     &  +LHPM5*DLOGQ8U*(-32*U1P6*T1M1+160*U1P5*T1M1*Q2-80*U1P5
     &  -64*U1P4*T1-320*U1P4*T1M1*Q22+304*U1P4*Q2+192*U1P3*T1*Q2+
     &  320*U1P3*T1M1*Q23-432*U1P3*Q22-192*U1P2*T1*Q22-160*U1P2*
     &  T1M1*Q24+272*U1P2*Q23+64*U1*T1*Q23+32*U1*T1M1*Q25-64*U1
     &  *Q24)
      VPS(74) =
     &  +LHPM5*DLOGQ9U*(-32*U1P6*T1M1+160*U1P5*T1M1*Q2-80*U1P5
     &  -64*U1P4*T1-320*U1P4*T1M1*Q22+304*U1P4*Q2+192*U1P3*T1*Q2+
     &  320*U1P3*T1M1*Q23-432*U1P3*Q22-192*U1P2*T1*Q22-160*U1P2*
     &  T1M1*Q24+272*U1P2*Q23+64*U1*T1*Q23+32*U1*T1M1*Q25-64*U1
     &  *Q24)
     &  +LHPM5*DLOGQ10U*(-32*U1P6*T1M1+160*U1P5*T1M1*Q2-80*U1P5
     &  -64*U1P4*T1-320*U1P4*T1M1*Q22+304*U1P4*Q2+192*U1P3*T1*Q2+
     &  320*U1P3*T1M1*Q23-432*U1P3*Q22-192*U1P2*T1*Q22-160*U1P2*
     &  T1M1*Q24+272*U1P2*Q23+64*U1*T1*Q23+32*U1*T1M1*Q25-64*U1
     &  *Q24)
     &  +LHPM5*DLOGQ11U*(-32*U1P6*T1M1+160*U1P5*T1M1*Q2-80*U1P5
     &  -64*U1P4*T1-320*U1P4*T1M1*Q22+304*U1P4*Q2+192*U1P3*T1*Q2+
     &  320*U1P3*T1M1*Q23-432*U1P3*Q22-192*U1P2*T1*Q22-160*U1P2*
     &  T1M1*Q24+272*U1P2*Q23+64*U1*T1*Q23+32*U1*T1M1*Q25-64*U1
     &  *Q24)
      VPS(75) =
     &  +LHPM5*DLOGQ12U*(32*U1P6*T1M1-160*U1P5*T1M1*Q2+80*U1P5+
     &  64*U1P4*T1+320*U1P4*T1M1*Q22-304*U1P4*Q2-192*U1P3*T1*Q2-320
     &  *U1P3*T1M1*Q23+432*U1P3*Q22+192*U1P2*T1*Q22+160*U1P2*T1M1*
     &  Q24-272*U1P2*Q23-64*U1*T1*Q23-32*U1*T1M1*Q25+64*U1*Q24
     &  )
     &  +LHPM5*DLOGQ13U*(64*U1P6*T1M1-320*U1P5*T1M1*Q2+160*U1P5
     &  +128*U1P4*T1+640*U1P4*T1M1*Q22-608*U1P4*Q2-384*U1P3*T1*Q2
     &  -640*U1P3*T1M1*Q23+864*U1P3*Q22+384*U1P2*T1*Q22+320*U1P2*
     &  T1M1*Q24-544*U1P2*Q23-128*U1*T1*Q23-64*U1*T1M1*Q25+128*
     &  U1*Q24)
      VPS(76) =
     &  +LOG7X2*(16*U1P4*T1M1*SPM3-32*U1P3*T1M1*Q2*SPM3+48*
     &  U1P3*T1M1*SPM2+48*U1P3*SPM3+64*U1P2*T1*SPM3+16*U1P2*T1M1*
     &  Q22*SPM3-96*U1P2*T1M1*Q2*SPM2+56*U1P2*T1M1*SPM1-64*U1P2*
     &  Q2*SPM3+128*U1P2*SPM2+64*U1*T1P2*SPM3-64*U1*T1*Q2*SPM3+
     &  160*U1*T1*SPM2+48*U1*T1M1*Q22*SPM2-112*U1*T1M1*Q2*SPM1+16
     &  *U1*Q22*SPM3-192*U1*Q2*SPM2+120*U1*SPM1+16*U1M1*T1P4*SPM3
     &  -32*U1M1*T1P3*Q2*SPM3+48*U1M1*T1P3*SPM2+16*U1M1*T1P2*Q22*
     &  SPM3-96*U1M1*T1P2*Q2*SPM2+56*U1M1*T1P2*SPM1+48*U1M1*T1*
     &  Q22*SPM2-112*U1M1*T1*Q2*SPM1+64*U1M1*Q22*SPM1+48*T1P3*
     &  SPM3-64*T1P2*Q2*SPM3+128*T1P2*SPM2+16*T1*Q22*SPM3-192*T1
     &  *Q2*SPM2+120*T1*SPM1+64*T1M1*Q22*SPM1+64*Q22*SPM2-192*
     &  Q2*SPM1)
      VPS(77) =
     &  +(224+64*U1P3*T1M1*SPM2-32*U1P2*T1M1*UM1-96*U1P2*
     &  T1M1*Q2*SPM2+160*U1P2*T1M1*SPM1+128*U1P2*SPM2+128*U1*T1*
     &  SPM2+32*U1*T1M1*UM1*Q2-224*U1*T1M1*Q2*SPM1+104*U1*T1M1-
     &  64*U1*UM1-16*U1*TM1-96*U1*Q2*SPM2+352*U1*SPM1+64*U1M1*
     &  T1P3*SPM2-32*U1M1*T1P2*TM1-96*U1M1*T1P2*Q2*SPM2+160*U1M1*
     &  T1P2*SPM1+32*U1M1*T1*TM1*Q2-224*U1M1*T1*Q2*SPM1+104*U1M1*
     &  T1-32*TB*Q22-128*U1M1*Q2+128*T1P2*SPM2-16*T1*UM1
     &  -64*T1*TM1-96*T1*Q2*SPM2+352*T1*SPM1-128*T1M1*Q2-320*Q2
     &  *SPM1-64*BQED*LOGDEL-32*BQED-64*MQED)
C SUM CONTRIBUTIONS AND MULTIPLY BY COMMON FACTOR:
      SPLUSV = 0.D0
      DO 10 I = 1,77
C        PRINT '(''0     VPS  = '',D20.7)',VPS(I)
   10 SPLUSV = SPLUSV + VPS(I)
C DIVIDE BY 16 TO GET THE NORMALIZATION CORRECT
C THE - IN THE DEF. CANCEL THE - FROM THE GL. POL.
CBH        VQEDGAM2 = SVCFCF/16.0D0
C
 1000 FORMAT('VPS(',I2,') =',D20.10)
CBH SUBTRACT OFF OLD FINITE SOFT PIECES
      SPLUSV = SPLUSV - ( SQM * ( 128*M2*LOGDEL*LOG1
     &  + 64*M2*ZETA2 - 128*M2*LOG1*LOG5 - 128*M2*LOG1*LOG6
     &  + 64*M2*LOG1 + 64*M2*LOG1X2 - 128*M2*DLOG2 - 128*M2*DLOG1 )
     &  + XSQM1 * (  - 64*LOGDEL*LOG1 - 32*ZETA2 + 64*LOG1*LOG5
     &  + 64*LOG1*LOG6 - 32*LOG1 - 32*LOG1X2 + 64*DLOG2 + 64*DLOG1 )
     &  + 32 - 64*LOGDEL )*BQED
CBH ADD ON NEW FINITE SOFT PIECES
      SPLUSV = SPLUSV + ( SQM * ( 128*M2*LI2B
     &  + 256*M2*LNB*LOG1 - 64*M2*LOG1*LOG2 + 128*M2*LOG1*LOGSP
     &  + 32*M2*LOG1X2 ) + XSQM1 * (  - 64*LI2B - 128*LNB*LOG1
     &  + 32*LOG1*LOG2 - 64*LOG1*LOGSP - 32*LOG1 - 16*LOG1X2 )
     &  - 128*LNB + 32*LOG2 - 64*LOGSP )*BQED
CBH SWITCH Q2 BACK TO POSITIVE
      Q2 = QTMP
CBH GET THE NORMALIZATION CORRECT
      VQEDG2 = SPLUSV
      RETURN
      END
CBH      DOUBLE PRECISION FUNCTION VQEDL2(SP,T1,U1,M2,Q2,DEL,S4MAX,S4,MU)
      DOUBLE PRECISION FUNCTION VQEDL2(T1,SP,M2,Q2,RHOTILDE)
C
C HERE WE COMPUTE THE EXPRESSION FOR THE CF*CF PART OF THE
C SOFT PLUS VIRTUAL MATRIX ELEMENT.
C
      IMPLICIT DOUBLE PRECISION (A-Z)
      INTEGER I
      DIMENSION VPS(63)
      PARAMETER( PI = 3.14159265359D0 )
      DATA ZETA2/1.644934066848226D+00/
C
CSR      LOGDEL = DLOG(DEL/M2)
CSR      LOGDEL2 = LOGDEL*LOGDEL
CSR HERE WE REPLACE THE LOGDEL TERMS BY INTEGRALS OVER S4
CBH OH NO WE DON'T
CBH        DIST = S4MAX - DEL
CBH           L11 = DLOG(S4/M2)
CBH           L12 = DLOG(S4MAX/M2)
CBH           LOGDEL = L12 - DIST/S4
CBH           LOGDEL2 = L12*L12 -2.0D0*DIST*L11/S4
C
CBH HERE REPLACE LOG(DEL/M2) = ARBITRARY
CBH SINCE WE SUBTRACT IT OFF LATER ANYHOW
      LOGDEL = -0.1D0
      LOGDEL2 = LOGDEL*LOGDEL
CBH NOW THE NEW SOFT PARAMETER
      LNB = 0.5D0*DLOG(1.D0-RHOTILDE)
      LNBX2 = LNB*LNB
CBH THE Q2 COMING INTO THE ROUTINE IS POSITIVE
CBH BUT IN THIS ROUTINE THE Q2 SHOULD BE NEGATIVE
CBH SO WE CHANGE THE SIGN HERE
      QTMP = Q2
      Q2 = -QTMP
CBH
      S = SP + Q2
      U1 = -SP-T1
CBH THERE IS NO LOGMU DEPENDENCE IN THE CF*CF PIECE
CSR      MU2 = M2
CBH      MU2 = MU*MU
CBH      CEP = 1.D0/16.D0/PI/PI
      S1 = 4.0D0*M2 -S
      S1M1 = 1.D0/S1
      T = T1+M2
      U = U1+M2
      XSQ = DSQRT(1.0D0 - 4.0D0*M2/S)
      YSQ = DSQRT(1.0D0 - 4.0D0*M2/Q2)
      X = (1.D0 - XSQ)/(1.D0 + XSQ)
      SQ = S*XSQ
      SQM = 1.D0/SQ
      Y = (1.D0-YSQ)/(1.D0+YSQ)
      X1 = (1.D0+YSQ)/2.D0
      X2 = 1.0D0 - X1
      AA = DSQRT(4.D0*M2 -Q2)
      AA2 = 4.D0*M2 -Q2
      BB = DSQRT(-Q2)
      CC = DSQRT(4.D0*M2*Q2/S - Q2)
      LAT = T*T + M2*M2 + Q2*Q2 - 2.D0*T*M2 - 2.D0*T*Q2 - 2*M2*Q2
      LAU = U*U + M2*M2 + Q2*Q2 - 2.D0*U*M2 - 2.D0*U*Q2 - 2*M2*Q2
      LH = DSQRT(LAT)
      LHP = DSQRT(LAU)
      LOG1 = DLOG(X)
      LOG2 = DLOG(S/M2)
CBH
      LOG1X2 = LOG1*LOG1
      LOG2X2 = LOG2*LOG2
      LOGSP = DLOG(SP/M2)
      LOGSPX2 = LOGSP*LOGSP
CBH
      LOG3 = DLOG(-T1/M2)
      LOG3X2 = LOG3*LOG3
      LOG4 = DLOG(-U1/M2)
      LOG4X2 = LOG4*LOG4
      LOG5 = DLOG(1.D0-X)
      LOG6 = DLOG(1.D0+X)
      LOG7 = DLOG(-Y)
      LOG7X2 = LOG7*LOG7
      LOG8 = DLOG(-Q2/S)
      LOG9 = DLOG(X1)
      LOG10 = DLOG(-X2)
CBH      LOGMU = DLOG(MU2/M2)
      LOGQ1 = DLOG((AA+CC)*(AA+CC)/4.D0/M2)
      LOGQ2 = DLOG((AA-BB)/(AA+BB))
      LOGQ3 = DLOG((AA-CC)/(AA-BB))
      LOGQ3X2 = LOGQ3*LOGQ3
      DLOG1 = DILOG(-X)
      DLOG2 = DILOG(X)
      DLOG3 = DILOG(T1/M2 + 1.D0)
      DLOG4 = DILOG(U1/M2 + 1.D0)
      DLOG5 = DILOG(1.D0-U1/X/T1)
      DLOG6 = DILOG(1.D0-T1/X/U1)
      DLOG7 = DILOG(Q2*X1/M2)
      DLOG8 = DILOG(Q2*X2/M2)
      DLOGQ1 = DILOG((AA-BB)/(AA-CC))
      DLOGQ2 = DILOG((AA-CC)/(AA+BB))
      DLOGQ3 = DILOG((BB+CC)/(AA+CC))
      DLOGQ4 = DILOG((CC-BB)/(AA+CC))
      DLOGQ5 = DILOG(S/SP)
      DLOGQ6T = DILOG((T1+AA2+LH)/(T1-YSQ*(LH+Q2*YSQ)))
      DLOGQ6U = DILOG((U1+AA2+LHP)/(U1-YSQ*(LHP+Q2*YSQ)))
      DLOGQ7T = DILOG((T1+AA2+LH)/(T1+YSQ*(LH-Q2*YSQ)))
      DLOGQ7U = DILOG((U1+AA2+LHP)/(U1+YSQ*(LHP-Q2*YSQ)))
      DLOGQ8T = DILOG((T1+AA2-LH)/(T1-YSQ*(LH+Q2*YSQ)))
      DLOGQ8U = DILOG((U1+AA2-LHP)/(U1-YSQ*(LHP+Q2*YSQ)))
      DLOGQ9T = DILOG((T1+AA2-LH)/(T1+YSQ*(LH-Q2*YSQ)))
      DLOGQ9U = DILOG((U1+AA2-LHP)/(U1+YSQ*(LHP-Q2*YSQ)))
      DLOGQ10T = DILOG( (T1*(Q2 - T - M2 - LH) - 2.D0*M2*LH)/
     &     (T1*(Q2 - T - M2 + LH)))
      DLOGQ10U = DILOG( (U1*(Q2 - U - M2 - LHP) - 2.D0*M2*LHP)/
     &     (U1*(Q2 - U - M2 + LHP)))
      DLOGQ11T = DILOG( (T1*(Q2 - T - M2 - LH) - 2.D0*M2*LH)/
     &     (T1*(Q2 - T - M2 - LH)))
      DLOGQ11U = DILOG( (U1*(Q2 - U - M2 - LHP) - 2.D0*M2*LHP)/
     &     (U1*(Q2 - U - M2 - LHP)))
      DLOGQ12T = DILOG( (Q2 - T - M2 + LH)/(Q2 - T - M2 - LH))
      DLOGQ12U = DILOG( (Q2 - U - M2 + LHP)/(Q2 - U - M2 - LHP))
      DLOGQ13T = DILOG( (M2 - T - LH)/(M2 - T))
      DLOGQ13U = DILOG( (M2 - U - LHP)/(M2 - U))
C MORE USEFUL DEFINITIONS:
CBH      CF2 = 16.D0/9.D0
      M22 = M2*M2
      M23 = M2*M22
      M24 = M22*M22
      T1P2 = T1*T1
      T1P3 = T1*T1P2
      T1P4 = T1*T1P3
      T1P5 = T1*T1P4
      T1P6 = T1*T1P5
      T1P7 = T1*T1P6
      T1M1 = 1.D0/T1
      T1M2 = T1M1*T1M1
      T1M3 = T1M2*T1M1
      U1P2 = U1*U1
      U1P3 = U1*U1P2
      U1P4 = U1*U1P3
      U1P5 = U1*U1P4
      U1P6 = U1*U1P5
csr  this line ws giving me problems on the vax, so I factored out a
csr   factor of u1p2 from the piece of the expression in vps(43) that
csr   had a term containing u1p7
csr      U1P7 = U1*U1P6
      U1M1 = 1.D0/U1
      U1M2 = U1M1*U1M1
      U1M3 = U1M1*U1M2
      UM1 = 1.D0/U
      UM2 = UM1*UM1
      TM1 = 1.D0/T
      TM2 = TM1*TM1
      Q22 = Q2*Q2
      Q23 = Q2*Q22
      Q24 = Q22*Q22
      Q25 = Q22*Q23
      TB = T1M1*U1M1
      SM1 = 1.D0/S
      SM2 = SM1*SM1
      SM3 = SM1*SM2
      SQM1 = 1.D0/SQ
      SPM1 = 1.D0/SP
      SPM2 = SPM1*SPM1
      SPM3 = SPM1*SPM2
      SPM4 = SPM2*SPM2
      LHM1 = 1.D0/LH
      LHM2 = LHM1*LHM1
      LHM3 = LHM1*LHM2
      LHM4 = LHM2*LHM2
      LHM5 = LHM2*LHM3
      LHPM1 = 1.D0/LHP
      LHPM2 = LHPM1*LHPM1
      LHPM3 = LHPM1*LHPM2
      LHPM4 = LHPM2*LHPM2
      LHPM5 = LHPM2*LHPM3
      XSQM1 = 1.D0/XSQ
CBH      LOG1X2 = LOG1*LOG1
CBH
      ONEMBETA = 1.D0 - XSQ
      ONEMBETAM1 = 1.D0/ONEMBETA
      ONEPBETA = 1.D0 + XSQ
      ONEPBETAM1 = 1.D0/ONEPBETA
CBH
      LI2B = DILOG(2.D0*XSQ*ONEPBETAM1)
      LIT1 = DILOG(1.D0+2.D0*T1*SPM1*ONEMBETAM1)
      LIU1 = DILOG(1.D0+2.D0*U1*SPM1*ONEMBETAM1)
      LIT2 = DILOG(1.D0+0.5D0*SP*ONEPBETA*T1M1)
      LIU2 = DILOG(1.D0+0.5D0*SP*ONEPBETA*U1M1)
      LNBT = DLOG(-0.5D0*SP*T1M1*ONEMBETA)
      LNBTX2 = LNBT*LNBT
      LNBU = DLOG(-0.5D0*SP*U1M1*ONEMBETA)
      LNBUX2 = LNBU*LNBU
CBH
      BQED = -S + M2*SP*SP*T1M1*U1M1
      MQED =2*M22*U1*T1M2 + 2*M22*T1M1 - M2*T1M1*S
     &  + 2*M22*T1*U1M2 + 2*M22*U1M1 - M2*U1M1*S
C
C HERE IS THE MATRIX ELEMENT.
C
      VPS(1) =
     &  +M23*LOG3*LHM2*(-64*U1P2*T1M1*TM1-64*U1*TM1+64*U1M1
     &  *T1P2*TM1+64*T1*TM1)
     &  +M23*LOG3*LHM4*(32*U1P2*TM1*Q2-96*U1*T1*TM1*Q2-288*
     &  U1M1*T1P3*TM1*Q2-416*T1P2*TM1*Q2)
     &  +M23*LOG4*LHPM2*(64*U1P2*T1M1*UM1+64*U1*UM1-64*U1M1*
     &  T1P2*UM1-64*T1*UM1)
     &  +M23*LOG4*LHPM4*(-288*U1P3*T1M1*UM1*Q2-416*U1P2*UM1*Q2
     &  -96*U1*T1*UM1*Q2+32*T1P2*UM1*Q2)
     &  +M23*ZETA2*LHM3*(-64*U1P2*T1M1-64*U1+64*U1M1*T1P2+
     &  64*T1)
     &  +M23*ZETA2*LHM5*(32*U1P2*Q2-96*U1*T1*Q2-288*U1M1*T1P3*
     &  Q2-416*T1P2*Q2)
     &  +M23*ZETA2*LHPM3*(64*U1P2*T1M1+64*U1-64*U1M1*T1P2-64
     &  *T1)
     &  +M23*ZETA2*LHPM5*(-288*U1P3*T1M1*Q2-416*U1P2*Q2-96*U1
     &  *T1*Q2+32*T1P2*Q2)
     &  +M23*LHM3*DLOGQ6T*(64*U1P2*T1M1+64*U1-64*U1M1*T1P2-64*
     &  T1)
      VPS(2) =
     &  +M23*LHM3*DLOGQ7T*(64*U1P2*T1M1+64*U1-64*U1M1*T1P2-64*
     &  T1)
     &  +M23*LHM3*DLOGQ8T*(-64*U1P2*T1M1-64*U1+64*U1M1*T1P2+
     &  64*T1)
     &  +M23*LHM3*DLOGQ9T*(-64*U1P2*T1M1-64*U1+64*U1M1*T1P2+
     &  64*T1)
     &  +M23*LHM3*DLOGQ10T*(-64*U1P2*T1M1-64*U1+64*U1M1*T1P2
     &  +64*T1)
     &  +M23*LHM3*DLOGQ11T*(-64*U1P2*T1M1-64*U1+64*U1M1*T1P2
     &  +64*T1)
     &  +M23*LHM3*DLOGQ12T*(64*U1P2*T1M1+64*U1-64*U1M1*T1P2-64
     &  *T1)
     &  +M23*LHM3*DLOGQ13T*(128*U1P2*T1M1+128*U1-128*U1M1*T1P2
     &  -128*T1)
     &  +M23*LHM5*DLOGQ6T*(-32*U1P2*Q2+96*U1*T1*Q2+288*U1M1*
     &  T1P3*Q2+416*T1P2*Q2)
     &  +M23*LHM5*DLOGQ7T*(-32*U1P2*Q2+96*U1*T1*Q2+288*U1M1*
     &  T1P3*Q2+416*T1P2*Q2)
      VPS(3) =
     &  +M23*LHM5*DLOGQ8T*(32*U1P2*Q2-96*U1*T1*Q2-288*U1M1*T1P3*
     &  Q2-416*T1P2*Q2)
     &  +M23*LHM5*DLOGQ9T*(32*U1P2*Q2-96*U1*T1*Q2-288*U1M1*T1P3*
     &  Q2-416*T1P2*Q2)
     &  +M23*LHM5*DLOGQ10T*(32*U1P2*Q2-96*U1*T1*Q2-288*U1M1*T1P3*
     &  Q2-416*T1P2*Q2)
     &  +M23*LHM5*DLOGQ11T*(32*U1P2*Q2-96*U1*T1*Q2-288*U1M1*T1P3*
     &  Q2-416*T1P2*Q2)
     &  +M23*LHM5*DLOGQ12T*(-32*U1P2*Q2+96*U1*T1*Q2+288*U1M1*
     &  T1P3*Q2+416*T1P2*Q2)
     &  +M23*LHM5*DLOGQ13T*(-64*U1P2*Q2+192*U1*T1*Q2+576*U1M1*
     &  T1P3*Q2+832*T1P2*Q2)
     &  +M23*LHPM3*DLOGQ6U*(-64*U1P2*T1M1-64*U1+64*U1M1*T1P2
     &  +64*T1)
     &  +M23*LHPM3*DLOGQ7U*(-64*U1P2*T1M1-64*U1+64*U1M1*T1P2
     &  +64*T1)
     &  +M23*LHPM3*DLOGQ8U*(64*U1P2*T1M1+64*U1-64*U1M1*T1P2-64
     &  *T1)
      VPS(4) =
     &  +M23*LHPM3*DLOGQ9U*(64*U1P2*T1M1+64*U1-64*U1M1*T1P2-64
     &  *T1)
     &  +M23*LHPM3*DLOGQ10U*(64*U1P2*T1M1+64*U1-64*U1M1*T1P2-
     &  64*T1)
     &  +M23*LHPM3*DLOGQ11U*(64*U1P2*T1M1+64*U1-64*U1M1*T1P2-
     &  64*T1)
     &  +M23*LHPM3*DLOGQ12U*(-64*U1P2*T1M1-64*U1+64*U1M1*T1P2
     &  +64*T1)
     &  +M23*LHPM3*DLOGQ13U*(-128*U1P2*T1M1-128*U1+128*U1M1*
     &  T1P2+128*T1)
     &  +M23*LHPM5*DLOGQ6U*(288*U1P3*T1M1*Q2+416*U1P2*Q2+96*U1*T1
     &  *Q2-32*T1P2*Q2)
     &  +M23*LHPM5*DLOGQ7U*(288*U1P3*T1M1*Q2+416*U1P2*Q2+96*U1*T1
     &  *Q2-32*T1P2*Q2)
     &  +M23*LHPM5*DLOGQ8U*(-288*U1P3*T1M1*Q2-416*U1P2*Q2-96*U1
     &  *T1*Q2+32*T1P2*Q2)
      VPS(5) =
     &  +M23*LHPM5*DLOGQ9U*(-288*U1P3*T1M1*Q2-416*U1P2*Q2-96*U1
     &  *T1*Q2+32*T1P2*Q2)
     &  +M23*LHPM5*DLOGQ10U*(-288*U1P3*T1M1*Q2-416*U1P2*Q2-96*
     &  U1*T1*Q2+32*T1P2*Q2)
     &  +M23*LHPM5*DLOGQ11U*(-288*U1P3*T1M1*Q2-416*U1P2*Q2-96*
     &  U1*T1*Q2+32*T1P2*Q2)
     &  +M23*LHPM5*DLOGQ12U*(288*U1P3*T1M1*Q2+416*U1P2*Q2+96*U1*
     &  T1*Q2-32*T1P2*Q2)
     &  +M23*LHPM5*DLOGQ13U*(576*U1P3*T1M1*Q2+832*U1P2*Q2+192*U1*
     &  T1*Q2-64*T1P2*Q2)
     &  +M22*LOG1*LOG5*SQM*(-256-128*U1*T1M1-128*U1M1*T1)
     &  +M22*LOG1*LOG6*SQM*(256+128*U1*T1M1+128*U1M1*T1)
     &  +M22*LOG1*LOG3*SQM*(-128-64*U1*T1M1-64*U1M1*T1)
     &  +M22*LOG1*LOG4*SQM*(-128-64*U1*T1M1-64*U1M1*T1)
     &  +M22*LOG1*SQM*LOGQ1*(128+64*U1*T1M1+64*U1M1*T1)
     &  +M22*LOG1*SQM*(-64*U1*T1M1*Q2*S1M1+128*U1*S1M1-64
     &  *U1M1*T1*Q2*S1M1+128*T1*S1M1-128*Q2*S1M1)
      VPS(6) =
     &  +M22*LOG3*LHM2*(32*U1P2*T1M1*TM1*Q2-128*U1P2*TM1+16*U1
     &  *T1P2*TM2-112*U1*T1*TM1+16*U1*T1*TM2*Q2+128*U1*TM1*Q2-16*
     &  U1M1*T1P4*TM2-16*U1M1*T1P3*TM1-16*U1M1*T1P3*TM2*Q2-64*
     &  U1M1*T1P2*TM1*Q2+32*T1*TM1*Q2)
     &  +M22*LOG3*LHM4*(16*U1P2*T1P2*TM1+16*U1P2*TM1*Q22+96*U1
     &  *T1P3*TM1-464*U1*T1P2*TM1*Q2+80*U1*T1*TM1*Q22+96*U1M1*T1P5
     &  *TM1-496*U1M1*T1P4*TM1*Q2+304*U1M1*T1P3*TM1*Q22+176*T1P4*
     &  TM1-1024*T1P3*TM1*Q2+304*T1P2*TM1*Q22)
     &  +M22*LOG3*(-32*U1*TM2-32*T1*TM2)
     &  +M22*LOG4*LHPM2*(-16*U1P4*T1M1*UM2-16*U1P3*T1M1*UM1
     &  -16*U1P3*T1M1*UM2*Q2+16*U1P2*T1*UM2-64*U1P2*T1M1*UM1*Q2-
     &  112*U1*T1*UM1+16*U1*T1*UM2*Q2+32*U1*UM1*Q2+32*U1M1*T1P2*
     &  UM1*Q2-128*T1P2*UM1+128*T1*UM1*Q2)
     &  +M22*LOG4*LHPM4*(96*U1P5*T1M1*UM1-496*U1P4*T1M1*UM1*Q2
     &  +176*U1P4*UM1+96*U1P3*T1*UM1+304*U1P3*T1M1*UM1*Q22-1024*
     &  U1P3*UM1*Q2+16*U1P2*T1P2*UM1-464*U1P2*T1*UM1*Q2+304*U1P2*
     &  UM1*Q22+80*U1*T1*UM1*Q22+16*T1P2*UM1*Q22)
      VPS(7) =
     &  +M22*LOG4*(-32*U1*UM2-32*T1*UM2)
     &  +M22*DLOG2*SQM*(-256-128*U1*T1M1-128*U1M1*T1)
     &  +M22*DLOG1*SQM*(256+128*U1*T1M1+128*U1M1*T1)
     &  +M22*ZETA2*SQM*(-896-448*U1*T1M1-448*U1M1*T1)
     &  +M22*ZETA2*LHM1*(-64-32*U1*T1M1-32*U1M1*T1)
     &  +M22*ZETA2*LHM3*(-96*U1P2-80*U1*T1-96*U1*Q2-48*U1M1
     &  *T1P3-96*U1M1*T1P2*Q2-32*T1P2-192*T1*Q2)
     &  +M22*ZETA2*LHM5*(16*U1P2*T1P2-16*U1P2*T1*Q2-32*U1P2*Q22
     &  +96*U1*T1P3-480*U1*T1P2*Q2+160*U1*T1*Q22+96*U1M1*T1P5-288
     &  *U1M1*T1P4*Q2+288*U1M1*T1P3*Q22+176*T1P4-816*T1P3*Q2+416*
     &  T1P2*Q22)
     &  +M22*ZETA2*LHPM1*(-64-32*U1*T1M1-32*U1M1*T1)
     &  +M22*ZETA2*LHPM3*(-48*U1P3*T1M1-96*U1P2*T1M1*Q2-32*
     &  U1P2-80*U1*T1-192*U1*Q2-96*T1P2-96*T1*Q2)
     &  +M22*ZETA2*LHPM5*(96*U1P5*T1M1-288*U1P4*T1M1*Q2+176*
     &  U1P4+96*U1P3*T1+288*U1P3*T1M1*Q22-816*U1P3*Q2+16*U1P2*T1P2
     &  -480*U1P2*T1*Q2+416*U1P2*Q22-16*U1*T1P2*Q2+160*U1*T1*Q22-
     &  32*T1P2*Q22)
      VPS(8) =
     &  +M22*SQM*LOG8*LOGQ2*(128+64*U1*T1M1+64*U1M1*T1)
     &  +M22*SQM*DLOGQ1*(256+128*U1*T1M1+128*U1M1*T1)
     &  +M22*SQM*DLOGQ2*(256+128*U1*T1M1+128*U1M1*T1)
     &  +M22*SQM*DLOGQ3*(256+128*U1*T1M1+128*U1M1*T1)
     &  +M22*SQM*DLOGQ4*(-256-128*U1*T1M1-128*U1M1*T1)
     &  +M22*SQM*LOGQ3X2*(128+64*U1*T1M1+64*U1M1*T1)
     &  +M22*LOG9*LHM2*(32*U1P2*T1M1*X1-32*U1P2*T1M1*X2-16*
     &  U1P2*T1M2*Q2*X1+16*U1P2*T1M2*Q2*X2-272*U1*T1M1*Q2*X1+272*U1*
     &  T1M1*Q2*X2+32*U1*X1-32*U1*X2-32*U1M1*T1P2*X1+32*U1M1*T1P2*
     &  X2-48*U1M1*T1*Q2*X1+48*U1M1*T1*Q2*X2-32*T1*X1+32*T1*X2-
     &  304*Q2*X1+304*Q2*X2)
     &  +M22*LOG9*LHM4*(-48*U1P2*T1M1*Q22*X1+48*U1P2*T1M1*
     &  Q22*X2-16*U1P2*Q2*X1+16*U1P2*Q2*X2-16*U1*T1*Q2*X1+16*U1*T1*
     &  Q2*X2+80*U1*Q22*X1-80*U1*Q22*X2+208*U1M1*T1P3*Q2*X1-208*
     &  U1M1*T1P3*Q2*X2-16*U1M1*T1P2*Q22*X1+16*U1M1*T1P2*Q22*X2+
     &  208*T1P2*Q2*X1-208*T1P2*Q2*X2+112*T1*Q22*X1-112*T1*Q22*X2)
      VPS(9) =
     &  +M22*LOG9*LHPM2*(-32*U1P2*T1M1*X1+32*U1P2*T1M1*X2-48
     &  *U1*T1M1*Q2*X1+48*U1*T1M1*Q2*X2-32*U1*X1+32*U1*X2+32*U1M1*
     &  T1P2*X1-32*U1M1*T1P2*X2-272*U1M1*T1*Q2*X1+272*U1M1*T1*Q2*X2
     &  -16*U1M2*T1P2*Q2*X1+16*U1M2*T1P2*Q2*X2+32*T1*X1-32*T1*X2-
     &  304*Q2*X1+304*Q2*X2)
     &  +M22*LOG9*LHPM4*(208*U1P3*T1M1*Q2*X1-208*U1P3*T1M1*Q2*X2
     &  -16*U1P2*T1M1*Q22*X1+16*U1P2*T1M1*Q22*X2+208*U1P2*Q2*X1-
     &  208*U1P2*Q2*X2-16*U1*T1*Q2*X1+16*U1*T1*Q2*X2+112*U1*Q22*X1-
     &  112*U1*Q22*X2-48*U1M1*T1P2*Q22*X1+48*U1M1*T1P2*Q22*X2-16*
     &  T1P2*Q2*X1+16*T1P2*Q2*X2+80*T1*Q22*X1-80*T1*Q22*X2)
     &  +M22*LOG10*LHM2*(-32*U1P2*T1M1*X1+32*U1P2*T1M1*X2+16
     &  *U1P2*T1M2*Q2*X1-16*U1P2*T1M2*Q2*X2+272*U1*T1M1*Q2*X1-272*U1
     &  *T1M1*Q2*X2-32*U1*X1+32*U1*X2+32*U1M1*T1P2*X1-32*U1M1*T1P2
     &  *X2+48*U1M1*T1*Q2*X1-48*U1M1*T1*Q2*X2+32*T1*X1-32*T1*X2+
     &  304*Q2*X1-304*Q2*X2)
      VPS(10) =
     &  +M22*LOG10*LHM4*(48*U1P2*T1M1*Q22*X1-48*U1P2*T1M1*Q22*
     &  X2+16*U1P2*Q2*X1-16*U1P2*Q2*X2+16*U1*T1*Q2*X1-16*U1*T1*Q2*X2
     &  -80*U1*Q22*X1+80*U1*Q22*X2-208*U1M1*T1P3*Q2*X1+208*U1M1*
     &  T1P3*Q2*X2+16*U1M1*T1P2*Q22*X1-16*U1M1*T1P2*Q22*X2-208*T1P2
     &  *Q2*X1+208*T1P2*Q2*X2-112*T1*Q22*X1+112*T1*Q22*X2)
     &  +M22*LOG10*LHPM2*(32*U1P2*T1M1*X1-32*U1P2*T1M1*X2+48*
     &  U1*T1M1*Q2*X1-48*U1*T1M1*Q2*X2+32*U1*X1-32*U1*X2-32*U1M1*
     &  T1P2*X1+32*U1M1*T1P2*X2+272*U1M1*T1*Q2*X1-272*U1M1*T1*Q2*X2
     &  +16*U1M2*T1P2*Q2*X1-16*U1M2*T1P2*Q2*X2-32*T1*X1+32*T1*X2+
     &  304*Q2*X1-304*Q2*X2)
     &  +M22*LOG10*LHPM4*(-208*U1P3*T1M1*Q2*X1+208*U1P3*T1M1*
     &  Q2*X2+16*U1P2*T1M1*Q22*X1-16*U1P2*T1M1*Q22*X2-208*U1P2*Q2*
     &  X1+208*U1P2*Q2*X2+16*U1*T1*Q2*X1-16*U1*T1*Q2*X2-112*U1*Q22*
     &  X1+112*U1*Q22*X2+48*U1M1*T1P2*Q22*X1-48*U1M1*T1P2*Q22*X2
     &  +16*T1P2*Q2*X1-16*T1P2*Q2*X2-80*T1*Q22*X1+80*T1*Q22*X2)
     &  +M22*LHM1*DLOGQ6T*(64+32*U1*T1M1+32*U1M1*T1)
     &  +M22*LHM1*DLOGQ7T*(64+32*U1*T1M1+32*U1M1*T1)
      VPS(11) =
     &  +M22*LHM1*DLOGQ8T*(-64-32*U1*T1M1-32*U1M1*T1)
     &  +M22*LHM1*DLOGQ9T*(-64-32*U1*T1M1-32*U1M1*T1)
     &  +M22*LHM1*DLOGQ10T*(-64-32*U1*T1M1-32*U1M1*T1)
     &  +M22*LHM1*DLOGQ11T*(-64-32*U1*T1M1-32*U1M1*T1)
     &  +M22*LHM1*DLOGQ12T*(64+32*U1*T1M1+32*U1M1*T1)
     &  +M22*LHM1*DLOGQ13T*(128+64*U1*T1M1+64*U1M1*T1)
     &  +M22*LHM2*(-16*U1*T1*TM1+64*U1*T1M1*Q2-16*U1*TM1*Q2
     &  +16*U1M1*T1P3*TM1+16*U1M1*T1P2*TM1*Q2+64*U1M1*T1*Q2+128*
     &  Q2)
     &  +M22*LHM3*DLOGQ6T*(96*U1P2+80*U1*T1+96*U1*Q2+48*U1M1*
     &  T1P3+96*U1M1*T1P2*Q2+32*T1P2+192*T1*Q2)
     &  +M22*LHM3*DLOGQ7T*(96*U1P2+80*U1*T1+96*U1*Q2+48*U1M1*
     &  T1P3+96*U1M1*T1P2*Q2+32*T1P2+192*T1*Q2)
     &  +M22*LHM3*DLOGQ8T*(-96*U1P2-80*U1*T1-96*U1*Q2-48*U1M1
     &  *T1P3-96*U1M1*T1P2*Q2-32*T1P2-192*T1*Q2)
     &  +M22*LHM3*DLOGQ9T*(-96*U1P2-80*U1*T1-96*U1*Q2-48*U1M1
     &  *T1P3-96*U1M1*T1P2*Q2-32*T1P2-192*T1*Q2)
      VPS(12) =
     &  +M22*LHM3*DLOGQ10T*(-96*U1P2-80*U1*T1-96*U1*Q2-48*
     &  U1M1*T1P3-96*U1M1*T1P2*Q2-32*T1P2-192*T1*Q2)
     &  +M22*LHM3*DLOGQ11T*(-96*U1P2-80*U1*T1-96*U1*Q2-48*
     &  U1M1*T1P3-96*U1M1*T1P2*Q2-32*T1P2-192*T1*Q2)
     &  +M22*LHM3*DLOGQ12T*(96*U1P2+80*U1*T1+96*U1*Q2+48*U1M1*
     &  T1P3+96*U1M1*T1P2*Q2+32*T1P2+192*T1*Q2)
     &  +M22*LHM3*DLOGQ13T*(192*U1P2+160*U1*T1+192*U1*Q2+96*
     &  U1M1*T1P3+192*U1M1*T1P2*Q2+64*T1P2+384*T1*Q2)
     &  +M22*LHM5*DLOGQ6T*(-16*U1P2*T1P2+16*U1P2*T1*Q2+32*U1P2*
     &  Q22-96*U1*T1P3+480*U1*T1P2*Q2-160*U1*T1*Q22-96*U1M1*T1P5
     &  +288*U1M1*T1P4*Q2-288*U1M1*T1P3*Q22-176*T1P4+816*T1P3*Q2
     &  -416*T1P2*Q22)
     &  +M22*LHM5*DLOGQ7T*(-16*U1P2*T1P2+16*U1P2*T1*Q2+32*U1P2*
     &  Q22-96*U1*T1P3+480*U1*T1P2*Q2-160*U1*T1*Q22-96*U1M1*T1P5
     &  +288*U1M1*T1P4*Q2-288*U1M1*T1P3*Q22-176*T1P4+816*T1P3*Q2
     &  -416*T1P2*Q22)
      VPS(13) =
     &  +M22*LHM5*DLOGQ8T*(16*U1P2*T1P2-16*U1P2*T1*Q2-32*U1P2*Q22
     &  +96*U1*T1P3-480*U1*T1P2*Q2+160*U1*T1*Q22+96*U1M1*T1P5-288
     &  *U1M1*T1P4*Q2+288*U1M1*T1P3*Q22+176*T1P4-816*T1P3*Q2+416*
     &  T1P2*Q22)
     &  +M22*LHM5*DLOGQ9T*(16*U1P2*T1P2-16*U1P2*T1*Q2-32*U1P2*Q22
     &  +96*U1*T1P3-480*U1*T1P2*Q2+160*U1*T1*Q22+96*U1M1*T1P5-288
     &  *U1M1*T1P4*Q2+288*U1M1*T1P3*Q22+176*T1P4-816*T1P3*Q2+416*
     &  T1P2*Q22)
     &  +M22*LHM5*DLOGQ10T*(16*U1P2*T1P2-16*U1P2*T1*Q2-32*U1P2*
     &  Q22+96*U1*T1P3-480*U1*T1P2*Q2+160*U1*T1*Q22+96*U1M1*T1P5
     &  -288*U1M1*T1P4*Q2+288*U1M1*T1P3*Q22+176*T1P4-816*T1P3*Q2
     &  +416*T1P2*Q22)
     &  +M22*LHM5*DLOGQ11T*(16*U1P2*T1P2-16*U1P2*T1*Q2-32*U1P2*
     &  Q22+96*U1*T1P3-480*U1*T1P2*Q2+160*U1*T1*Q22+96*U1M1*T1P5
     &  -288*U1M1*T1P4*Q2+288*U1M1*T1P3*Q22+176*T1P4-816*T1P3*Q2
     &  +416*T1P2*Q22)
      VPS(14) =
     &  +M22*LHM5*DLOGQ12T*(-16*U1P2*T1P2+16*U1P2*T1*Q2+32*U1P2*
     &  Q22-96*U1*T1P3+480*U1*T1P2*Q2-160*U1*T1*Q22-96*U1M1*T1P5
     &  +288*U1M1*T1P4*Q2-288*U1M1*T1P3*Q22-176*T1P4+816*T1P3*Q2
     &  -416*T1P2*Q22)
     &  +M22*LHM5*DLOGQ13T*(-32*U1P2*T1P2+32*U1P2*T1*Q2+64*U1P2*
     &  Q22-192*U1*T1P3+960*U1*T1P2*Q2-320*U1*T1*Q22-192*U1M1*T1P5
     &  +576*U1M1*T1P4*Q2-576*U1M1*T1P3*Q22-352*T1P4+1632*T1P3*Q2
     &  -832*T1P2*Q22)
     &  +M22*LHPM1*DLOGQ6U*(64+32*U1*T1M1+32*U1M1*T1)
     &  +M22*LHPM1*DLOGQ7U*(64+32*U1*T1M1+32*U1M1*T1)
     &  +M22*LHPM1*DLOGQ8U*(-64-32*U1*T1M1-32*U1M1*T1)
     &  +M22*LHPM1*DLOGQ9U*(-64-32*U1*T1M1-32*U1M1*T1)
     &  +M22*LHPM1*DLOGQ10U*(-64-32*U1*T1M1-32*U1M1*T1)
     &  +M22*LHPM1*DLOGQ11U*(-64-32*U1*T1M1-32*U1M1*T1)
     &  +M22*LHPM1*DLOGQ12U*(64+32*U1*T1M1+32*U1M1*T1)
     &  +M22*LHPM1*DLOGQ13U*(128+64*U1*T1M1+64*U1M1*T1)
      VPS(15) =
     &  +M22*LHPM2*(16*U1P3*T1M1*UM1+16*U1P2*T1M1*UM1*Q2-16*
     &  U1*T1*UM1+64*U1*T1M1*Q2+64*U1M1*T1*Q2-16*T1*UM1*Q2+128*Q2
     &  )
     &  +M22*LHPM3*DLOGQ6U*(48*U1P3*T1M1+96*U1P2*T1M1*Q2+32*U1P2
     &  +80*U1*T1+192*U1*Q2+96*T1P2+96*T1*Q2)
     &  +M22*LHPM3*DLOGQ7U*(48*U1P3*T1M1+96*U1P2*T1M1*Q2+32*U1P2
     &  +80*U1*T1+192*U1*Q2+96*T1P2+96*T1*Q2)
     &  +M22*LHPM3*DLOGQ8U*(-48*U1P3*T1M1-96*U1P2*T1M1*Q2-32*
     &  U1P2-80*U1*T1-192*U1*Q2-96*T1P2-96*T1*Q2)
     &  +M22*LHPM3*DLOGQ9U*(-48*U1P3*T1M1-96*U1P2*T1M1*Q2-32*
     &  U1P2-80*U1*T1-192*U1*Q2-96*T1P2-96*T1*Q2)
     &  +M22*LHPM3*DLOGQ10U*(-48*U1P3*T1M1-96*U1P2*T1M1*Q2-32*
     &  U1P2-80*U1*T1-192*U1*Q2-96*T1P2-96*T1*Q2)
     &  +M22*LHPM3*DLOGQ11U*(-48*U1P3*T1M1-96*U1P2*T1M1*Q2-32*
     &  U1P2-80*U1*T1-192*U1*Q2-96*T1P2-96*T1*Q2)
     &  +M22*LHPM3*DLOGQ12U*(48*U1P3*T1M1+96*U1P2*T1M1*Q2+32*
     &  U1P2+80*U1*T1+192*U1*Q2+96*T1P2+96*T1*Q2)
      VPS(16) =
     &  +M22*LHPM3*DLOGQ13U*(96*U1P3*T1M1+192*U1P2*T1M1*Q2+64*
     &  U1P2+160*U1*T1+384*U1*Q2+192*T1P2+192*T1*Q2)
     &  +M22*LHPM5*DLOGQ6U*(-96*U1P5*T1M1+288*U1P4*T1M1*Q2-176
     &  *U1P4-96*U1P3*T1-288*U1P3*T1M1*Q22+816*U1P3*Q2-16*U1P2*T1P2
     &  +480*U1P2*T1*Q2-416*U1P2*Q22+16*U1*T1P2*Q2-160*U1*T1*Q22+
     &  32*T1P2*Q22)
     &  +M22*LHPM5*DLOGQ7U*(-96*U1P5*T1M1+288*U1P4*T1M1*Q2-176
     &  *U1P4-96*U1P3*T1-288*U1P3*T1M1*Q22+816*U1P3*Q2-16*U1P2*T1P2
     &  +480*U1P2*T1*Q2-416*U1P2*Q22+16*U1*T1P2*Q2-160*U1*T1*Q22+
     &  32*T1P2*Q22)
     &  +M22*LHPM5*DLOGQ8U*(96*U1P5*T1M1-288*U1P4*T1M1*Q2+176*
     &  U1P4+96*U1P3*T1+288*U1P3*T1M1*Q22-816*U1P3*Q2+16*U1P2*T1P2
     &  -480*U1P2*T1*Q2+416*U1P2*Q22-16*U1*T1P2*Q2+160*U1*T1*Q22-
     &  32*T1P2*Q22)
     &  +M22*LHPM5*DLOGQ9U*(96*U1P5*T1M1-288*U1P4*T1M1*Q2+176*
     &  U1P4+96*U1P3*T1+288*U1P3*T1M1*Q22-816*U1P3*Q2+16*U1P2*T1P2
     &  -480*U1P2*T1*Q2+416*U1P2*Q22-16*U1*T1P2*Q2+160*U1*T1*Q22-
     &  32*T1P2*Q22)
      VPS(17) =
     &  +M22*LHPM5*DLOGQ10U*(96*U1P5*T1M1-288*U1P4*T1M1*Q2+176*
     &  U1P4+96*U1P3*T1+288*U1P3*T1M1*Q22-816*U1P3*Q2+16*U1P2*T1P2
     &  -480*U1P2*T1*Q2+416*U1P2*Q22-16*U1*T1P2*Q2+160*U1*T1*Q22-
     &  32*T1P2*Q22)
     &  +M22*LHPM5*DLOGQ11U*(96*U1P5*T1M1-288*U1P4*T1M1*Q2+176*
     &  U1P4+96*U1P3*T1+288*U1P3*T1M1*Q22-816*U1P3*Q2+16*U1P2*T1P2
     &  -480*U1P2*T1*Q2+416*U1P2*Q22-16*U1*T1P2*Q2+160*U1*T1*Q22-
     &  32*T1P2*Q22)
     &  +M22*LHPM5*DLOGQ12U*(-96*U1P5*T1M1+288*U1P4*T1M1*Q2-
     &  176*U1P4-96*U1P3*T1-288*U1P3*T1M1*Q22+816*U1P3*Q2-16*U1P2*
     &  T1P2+480*U1P2*T1*Q2-416*U1P2*Q22+16*U1*T1P2*Q2-160*U1*T1*
     &  Q22+32*T1P2*Q22)
     &  +M22*LHPM5*DLOGQ13U*(-192*U1P5*T1M1+576*U1P4*T1M1*Q2-
     &  352*U1P4-192*U1P3*T1-576*U1P3*T1M1*Q22+1632*U1P3*Q2-32*U1P2
     &  *T1P2+960*U1P2*T1*Q2-832*U1P2*Q22+32*U1*T1P2*Q2-320*U1*T1*
     &  Q22+64*T1P2*Q22)
      VPS(18) =
     &  +M22*(32*U1*T1M1*TM1+128*U1*T1M2+32*U1M1*T1*UM1+
     &  128*U1M1+128*U1M2*T1+128*T1M1+32*UM1+32*TM1)
     &  +M2*LOG1X2*SQM*(32*U1+32*T1-32*Q2+64*BQED)
     &  +M2*LOG1X2*(-8*U1P2*T1M1*SPM1-24*U1*SPM1-8*U1M1*T1P2*
     &  SPM1-24*T1*SPM1)
     &  +M2*LOG1*LOG5*SQM*(-64*U1P2*T1M1+64*U1*T1M1*Q2-320*
     &  U1-64*U1M1*T1P2+64*U1M1*T1*Q2-320*T1+256*Q2-128*BQED)
     &  +M2*LOG1*LOG6*SQM*(64*U1P2*T1M1-64*U1*T1M1*Q2+192*U1
     &  +64*U1M1*T1P2-64*U1M1*T1*Q2+192*T1-128*Q2-128*BQED)
     &  +M2*LOG1*LOG3*SQM*(-32*U1P2*T1M1+32*U1*T1M1*Q2-96*U1
     &  -32*U1M1*T1P2+32*U1M1*T1*Q2-96*T1+64*Q2)
     &  +M2*LOG1*LOG4*SQM*(-32*U1P2*T1M1+32*U1*T1M1*Q2-96*U1
     &  -32*U1M1*T1P2+32*U1M1*T1*Q2-96*T1+64*Q2)
     &  +M2*LOG1*SQM*LOGQ1*(32*U1P2*T1M1-32*U1*T1M1*Q2+96*U1
     &  +32*U1M1*T1P2-32*U1M1*T1*Q2+96*T1-64*Q2)
      VPS(19) =
     &  +M2*LOG1*SQM*(-32*U1P3*T1M1*S1M1+32*U1P3*T1M1*SPM1
     &  +32*U1P2*T1M1*Q2*S1M1-32*U1P2*T1M1*Q2*SPM1+64*U1P2*T1M1-
     &  128*U1P2*Q2*SPM2+64*U1P2*S1M1-256*U1*T1*Q2*SPM2+192*U1*T1*
     &  S1M1-64*U1*T1*SPM1-48*U1*T1M1*Q2-224*U1*Q2*S1M1-96*U1*Q2*
     &  SPM1+32*U1-32*U1M1*T1P3*S1M1+32*U1M1*T1P3*SPM1+32*U1M1*
     &  T1P2*Q2*S1M1-32*U1M1*T1P2*Q2*SPM1+64*U1M1*T1P2-48*U1M1*T1*
     &  Q2-128*T1P2*Q2*SPM2+64*T1P2*S1M1-224*T1*Q2*S1M1-96*T1*Q2*
     &  SPM1+32*T1+128*Q22*S1M1+32*Q2+128*BQED*LOGDEL+64*BQED)
     &  +M2*LOG3*LHM2*(-96*U1P2*T1*TM1+48*U1P2*TM1*Q2+16*U1*
     &  T1P3*TM2-168*U1*T1P2*TM1+16*U1*T1P2*TM2*Q2+168*U1*T1*TM1*Q2
     &  -32*U1*TM1*Q22-24*U1M1*T1P5*TM2-48*U1M1*T1P4*TM1-16*
     &  U1M1*T1P4*TM2*Q2+56*U1M1*T1P3*TM1*Q2+8*U1M1*T1P3*TM2*Q22
     &  +16*U1M1*T1P2*TM1*Q22-24*T1P4*TM2-168*T1P3*TM1-32*T1P3*
     &  TM2*Q2+96*T1P2*TM1*Q2-8*T1P2*TM2*Q22-48*T1*TM1*Q22)
      VPS(20) =
     &  +M2*LOG3*LHM4*(40*U1P2*T1P3*TM1-80*U1P2*T1P2*TM1*Q2+40*
     &  U1P2*T1*TM1*Q22+176*U1*T1P4*TM1-560*U1*T1P3*TM1*Q2+224*U1*
     &  T1P2*TM1*Q22-32*U1*T1*TM1*Q23+88*U1M1*T1P6*TM1-288*U1M1*
     &  T1P5*TM1*Q2+328*U1M1*T1P4*TM1*Q22-64*U1M1*T1P3*TM1*Q23+
     &  240*T1P5*TM1-816*T1P4*TM1*Q2+512*T1P3*TM1*Q22-64*T1P2*TM1*
     &  Q23)
     &  +M2*LOG3*(-48*U1*T1*TM2+32*U1*TM1+8*U1M1*T1P3*TM2-
     &  16*U1M1*T1P2*TM1-40*T1P2*TM2+48*T1*TM1+16*T1*TM2*Q2)
     &  +M2*LOG4*LHPM2*(-24*U1P5*T1M1*UM2-48*U1P4*T1M1*UM1-
     &  16*U1P4*T1M1*UM2*Q2-24*U1P4*UM2+16*U1P3*T1*UM2+56*U1P3*
     &  T1M1*UM1*Q2+8*U1P3*T1M1*UM2*Q22-168*U1P3*UM1-32*U1P3*UM2
     &  *Q2-168*U1P2*T1*UM1+16*U1P2*T1*UM2*Q2+16*U1P2*T1M1*UM1*Q22
     &  +96*U1P2*UM1*Q2-8*U1P2*UM2*Q22-96*U1*T1P2*UM1+168*U1*T1*
     &  UM1*Q2-48*U1*UM1*Q22+48*T1P2*UM1*Q2-32*T1*UM1*Q22)
      VPS(21) =
     &  +M2*LOG4*LHPM4*(88*U1P6*T1M1*UM1-288*U1P5*T1M1*UM1*Q2+
     &  240*U1P5*UM1+176*U1P4*T1*UM1+328*U1P4*T1M1*UM1*Q22-816*
     &  U1P4*UM1*Q2+40*U1P3*T1P2*UM1-560*U1P3*T1*UM1*Q2-64*U1P3*
     &  T1M1*UM1*Q23+512*U1P3*UM1*Q22-80*U1P2*T1P2*UM1*Q2+224*
     &  U1P2*T1*UM1*Q22-64*U1P2*UM1*Q23+40*U1*T1P2*UM1*Q22-32*U1*
     &  T1*UM1*Q23)
     &  +M2*LOG4*(8*U1P3*T1M1*UM2-16*U1P2*T1M1*UM1-40*U1P2*UM2
     &  -48*U1*T1*UM2+48*U1*UM1+16*U1*UM2*Q2+32*T1*UM1)
     &  +M2*DLOG2*SQM*(-64*U1P2*T1M1+64*U1*T1M1*Q2-320*U1-
     &  64*U1M1*T1P2+64*U1M1*T1*Q2-320*T1+256*Q2-128*BQED)
     &  +M2*DLOG3*(-16-16*U1M1*T1)
     &  +M2*DLOG4*(-16-16*U1*T1M1)
     &  +M2*DLOG1*SQM*(64*U1P2*T1M1-64*U1*T1M1*Q2+192*U1+64
     &  *U1M1*T1P2-64*U1M1*T1*Q2+192*T1-128*Q2-128*BQED)
     &  +M2*ZETA2*SQM*(-224*U1P2*T1M1+224*U1*T1M1*Q2-928*
     &  U1-224*U1M1*T1P2+224*U1M1*T1*Q2-928*T1+704*Q2+64*BQED)
     &  +M2*ZETA2*LHM1*(16*U1*T1M1*Q2-64*U1-32*U1M1*T1P2+16*
     &  U1M1*T1*Q2-64*T1+32*Q2)
      VPS(22) =
     &  +M2*ZETA2*LHM3*(-48*U1P2*T1-80*U1*T1P2-112*U1*T1*Q2+
     &  32*U1*Q22-8*U1M1*T1P4-48*U1M1*T1P3*Q2+48*U1M1*T1P2*Q22-
     &  88*T1P3-176*T1P2*Q2+112*T1*Q22)
     &  +M2*ZETA2*LHM5*(32*U1P2*T1P3-48*U1P2*T1P2*Q2+16*U1P2*T1*
     &  Q22+144*U1*T1P4-432*U1*T1P3*Q2+336*U1*T1P2*Q22-48*U1*T1*
     &  Q23+24*U1M1*T1P6-96*U1M1*T1P5*Q2+120*U1M1*T1P4*Q22-48*
     &  U1M1*T1P3*Q23+152*T1P5-432*T1P4*Q2+440*T1P3*Q22-160*T1P2*
     &  Q23)
     &  +M2*ZETA2*LHPM1*(-32*U1P2*T1M1+16*U1*T1M1*Q2-64*U1+
     &  16*U1M1*T1*Q2-64*T1+32*Q2)
     &  +M2*ZETA2*LHPM3*(-8*U1P4*T1M1-48*U1P3*T1M1*Q2-88*U1P3
     &  -80*U1P2*T1+48*U1P2*T1M1*Q22-176*U1P2*Q2-48*U1*T1P2-112*
     &  U1*T1*Q2+112*U1*Q22+32*T1*Q22)
     &  +M2*ZETA2*LHPM5*(24*U1P6*T1M1-96*U1P5*T1M1*Q2+152*U1P5
     &  +144*U1P4*T1+120*U1P4*T1M1*Q22-432*U1P4*Q2+32*U1P3*T1P2-
     &  432*U1P3*T1*Q2-48*U1P3*T1M1*Q23+440*U1P3*Q22-48*U1P2*T1P2*Q2
     &  +336*U1P2*T1*Q22-160*U1P2*Q23+16*U1*T1P2*Q22-48*U1*T1*Q23
     &  )
      VPS(23) =
     &  +M2*ZETA2*(32+48*U1P2*T1M1*SPM1+16*U1*T1M1+144*U1*
     &  SPM1+48*U1M1*T1P2*SPM1+16*U1M1*T1+144*T1*SPM1)
     &  +M2*SQM*LOG8*LOGQ2*(32*U1P2*T1M1-32*U1*T1M1*Q2+96*U1
     &  +32*U1M1*T1P2-32*U1M1*T1*Q2+96*T1-64*Q2)
     &  +M2*SQM*DLOGQ1*(64*U1P2*T1M1-64*U1*T1M1*Q2+192*U1+64
     &  *U1M1*T1P2-64*U1M1*T1*Q2+192*T1-128*Q2)
     &  +M2*SQM*DLOGQ2*(64*U1P2*T1M1-64*U1*T1M1*Q2+192*U1+64
     &  *U1M1*T1P2-64*U1M1*T1*Q2+192*T1-128*Q2)
     &  +M2*SQM*DLOGQ3*(64*U1P2*T1M1-64*U1*T1M1*Q2+192*U1+64
     &  *U1M1*T1P2-64*U1M1*T1*Q2+192*T1-128*Q2)
     &  +M2*SQM*DLOGQ4*(-64*U1P2*T1M1+64*U1*T1M1*Q2-192*U1
     &  -64*U1M1*T1P2+64*U1M1*T1*Q2-192*T1+128*Q2)
     &  +M2*SQM*LOGQ3X2*(32*U1P2*T1M1-32*U1*T1M1*Q2+96*U1+
     &  32*U1M1*T1P2-32*U1M1*T1*Q2+96*T1-64*Q2)
      VPS(24) =
     &  +M2*LOG9*LHM2*(-48*U1P2*T1M1*Q2*X1+48*U1P2*T1M1*Q2*X2
     &  +48*U1P2*X1-48*U1P2*X2+96*U1*T1*X1-96*U1*T1*X2+80*U1*T1M1*
     &  Q22*X1-80*U1*T1M1*Q22*X2-384*U1*Q2*X1+384*U1*Q2*X2+64*
     &  U1M1*T1P3*X1-64*U1M1*T1P3*X2-96*U1M1*T1P2*Q2*X1+96*U1M1*
     &  T1P2*Q2*X2+48*U1M1*T1*Q22*X1-48*U1M1*T1*Q22*X2+112*T1P2*X1
     &  -112*T1P2*X2-336*T1*Q2*X1+336*T1*Q2*X2+224*Q22*X1-224*Q22
     &  *X2)
     &  +M2*LOG9*LHM4*(-8*U1P2*T1P2*X1+8*U1P2*T1P2*X2+32*U1P2*
     &  T1*Q2*X1-32*U1P2*T1*Q2*X2-24*U1P2*Q22*X1+24*U1P2*Q22*X2-32*
     &  U1*T1P3*X1+32*U1*T1P3*X2+128*U1*T1P2*Q2*X1-128*U1*T1P2*Q2*X2+
     &  112*U1*T1*Q22*X1-112*U1*T1*Q22*X2-16*U1*Q23*X1+16*U1*Q23*X2
     &  -64*U1M1*T1P5*X1+64*U1M1*T1P5*X2+192*U1M1*T1P4*Q2*X1-192*
     &  U1M1*T1P4*Q2*X2-208*U1M1*T1P3*Q22*X1+208*U1M1*T1P3*Q22*X2+
     &  16*U1M1*T1P2*Q23*X1-16*U1M1*T1P2*Q23*X2-88*T1P4*X1+88*T1P4*
     &  X2+384*T1P3*Q2*X1-384*T1P3*Q2*X2-72*T1P2*Q22*X1+72*T1P2*Q22
     &  *X2-96*T1*Q23*X1+96*T1*Q23*X2)
      VPS(25) =
     &  +M2*LOG9*LHPM2*(64*U1P3*T1M1*X1-64*U1P3*T1M1*X2-96*U1P2
     &  *T1M1*Q2*X1+96*U1P2*T1M1*Q2*X2+112*U1P2*X1-112*U1P2*X2+96*
     &  U1*T1*X1-96*U1*T1*X2+48*U1*T1M1*Q22*X1-48*U1*T1M1*Q22*X2-
     &  336*U1*Q2*X1+336*U1*Q2*X2-48*U1M1*T1P2*Q2*X1+48*U1M1*T1P2*Q2*
     &  X2+80*U1M1*T1*Q22*X1-80*U1M1*T1*Q22*X2+48*T1P2*X1-48*T1P2
     &  *X2-384*T1*Q2*X1+384*T1*Q2*X2+224*Q22*X1-224*Q22*X2)
     &  +M2*LOG9*LHPM4*(-64*U1P5*T1M1*X1+64*U1P5*T1M1*X2+192*
     &  U1P4*T1M1*Q2*X1-192*U1P4*T1M1*Q2*X2-88*U1P4*X1+88*U1P4*X2-
     &  32*U1P3*T1*X1+32*U1P3*T1*X2-208*U1P3*T1M1*Q22*X1+208*U1P3*
     &  T1M1*Q22*X2+384*U1P3*Q2*X1-384*U1P3*Q2*X2-8*U1P2*T1P2*X1+8*
     &  U1P2*T1P2*X2+128*U1P2*T1*Q2*X1-128*U1P2*T1*Q2*X2+16*U1P2*T1M1*
     &  Q23*X1-16*U1P2*T1M1*Q23*X2-72*U1P2*Q22*X1+72*U1P2*Q22*X2
     &  +32*U1*T1P2*Q2*X1-32*U1*T1P2*Q2*X2+112*U1*T1*Q22*X1-112*U1*
     &  T1*Q22*X2-96*U1*Q23*X1+96*U1*Q23*X2-24*T1P2*Q22*X1+24*
     &  T1P2*Q22*X2-16*T1*Q23*X1+16*T1*Q23*X2)
     &  +M2*LOG9*(-32*U1*T1M1*X1+32*U1*T1M1*X2-32*U1M1*T1*X1
     &  +32*U1M1*T1*X2-64*X1+64*X2)
      VPS(26) =
     &  +M2*LOG10*LHM2*(48*U1P2*T1M1*Q2*X1-48*U1P2*T1M1*Q2*X2-
     &  48*U1P2*X1+48*U1P2*X2-96*U1*T1*X1+96*U1*T1*X2-80*U1*T1M1*
     &  Q22*X1+80*U1*T1M1*Q22*X2+384*U1*Q2*X1-384*U1*Q2*X2-64*
     &  U1M1*T1P3*X1+64*U1M1*T1P3*X2+96*U1M1*T1P2*Q2*X1-96*U1M1*
     &  T1P2*Q2*X2-48*U1M1*T1*Q22*X1+48*U1M1*T1*Q22*X2-112*T1P2*X1
     &  +112*T1P2*X2+336*T1*Q2*X1-336*T1*Q2*X2-224*Q22*X1+224*Q22
     &  *X2)
     &  +M2*LOG10*LHM4*(8*U1P2*T1P2*X1-8*U1P2*T1P2*X2-32*U1P2*T1*
     &  Q2*X1+32*U1P2*T1*Q2*X2+24*U1P2*Q22*X1-24*U1P2*Q22*X2+32*U1*
     &  T1P3*X1-32*U1*T1P3*X2-128*U1*T1P2*Q2*X1+128*U1*T1P2*Q2*X2-112
     &  *U1*T1*Q22*X1+112*U1*T1*Q22*X2+16*U1*Q23*X1-16*U1*Q23*X2+
     &  64*U1M1*T1P5*X1-64*U1M1*T1P5*X2-192*U1M1*T1P4*Q2*X1+192*
     &  U1M1*T1P4*Q2*X2+208*U1M1*T1P3*Q22*X1-208*U1M1*T1P3*Q22*X2-
     &  16*U1M1*T1P2*Q23*X1+16*U1M1*T1P2*Q23*X2+88*T1P4*X1-88*T1P4*
     &  X2-384*T1P3*Q2*X1+384*T1P3*Q2*X2+72*T1P2*Q22*X1-72*T1P2*Q22
     &  *X2+96*T1*Q23*X1-96*T1*Q23*X2)
      VPS(27) =
     &  +M2*LOG10*LHPM2*(-64*U1P3*T1M1*X1+64*U1P3*T1M1*X2+96*
     &  U1P2*T1M1*Q2*X1-96*U1P2*T1M1*Q2*X2-112*U1P2*X1+112*U1P2*X2-
     &  96*U1*T1*X1+96*U1*T1*X2-48*U1*T1M1*Q22*X1+48*U1*T1M1*Q22*X2
     &  +336*U1*Q2*X1-336*U1*Q2*X2+48*U1M1*T1P2*Q2*X1-48*U1M1*T1P2*
     &  Q2*X2-80*U1M1*T1*Q22*X1+80*U1M1*T1*Q22*X2-48*T1P2*X1+48*
     &  T1P2*X2+384*T1*Q2*X1-384*T1*Q2*X2-224*Q22*X1+224*Q22*X2)
     &  +M2*LOG10*LHPM4*(64*U1P5*T1M1*X1-64*U1P5*T1M1*X2-192*
     &  U1P4*T1M1*Q2*X1+192*U1P4*T1M1*Q2*X2+88*U1P4*X1-88*U1P4*X2+
     &  32*U1P3*T1*X1-32*U1P3*T1*X2+208*U1P3*T1M1*Q22*X1-208*U1P3*
     &  T1M1*Q22*X2-384*U1P3*Q2*X1+384*U1P3*Q2*X2+8*U1P2*T1P2*X1-8*
     &  U1P2*T1P2*X2-128*U1P2*T1*Q2*X1+128*U1P2*T1*Q2*X2-16*U1P2*T1M1*
     &  Q23*X1+16*U1P2*T1M1*Q23*X2+72*U1P2*Q22*X1-72*U1P2*Q22*X2
     &  -32*U1*T1P2*Q2*X1+32*U1*T1P2*Q2*X2-112*U1*T1*Q22*X1+112*U1*
     &  T1*Q22*X2+96*U1*Q23*X1-96*U1*Q23*X2+24*T1P2*Q22*X1-24*
     &  T1P2*Q22*X2+16*T1*Q23*X1-16*T1*Q23*X2)
     &  +M2*LOG10*(32*U1*T1M1*X1-32*U1*T1M1*X2+32*U1M1*T1*X1-
     &  32*U1M1*T1*X2+64*X1-64*X2)
      VPS(28) =
     &  +M2*LHM1*DLOGQ6T*(-16*U1*T1M1*Q2+64*U1+32*U1M1*T1P2-
     &  16*U1M1*T1*Q2+64*T1-32*Q2)
     &  +M2*LHM1*DLOGQ7T*(-16*U1*T1M1*Q2+64*U1+32*U1M1*T1P2-
     &  16*U1M1*T1*Q2+64*T1-32*Q2)
     &  +M2*LHM1*DLOGQ8T*(16*U1*T1M1*Q2-64*U1-32*U1M1*T1P2+16*
     &  U1M1*T1*Q2-64*T1+32*Q2)
     &  +M2*LHM1*DLOGQ9T*(16*U1*T1M1*Q2-64*U1-32*U1M1*T1P2+16*
     &  U1M1*T1*Q2-64*T1+32*Q2)
     &  +M2*LHM1*DLOGQ10T*(16*U1*T1M1*Q2-64*U1-32*U1M1*T1P2+16*
     &  U1M1*T1*Q2-64*T1+32*Q2)
     &  +M2*LHM1*DLOGQ11T*(16*U1*T1M1*Q2-64*U1-32*U1M1*T1P2+16*
     &  U1M1*T1*Q2-64*T1+32*Q2)
     &  +M2*LHM1*DLOGQ12T*(-16*U1*T1M1*Q2+64*U1+32*U1M1*T1P2-
     &  16*U1M1*T1*Q2+64*T1-32*Q2)
     &  +M2*LHM1*DLOGQ13T*(-32*U1*T1M1*Q2+128*U1+64*U1M1*T1P2
     &  -32*U1M1*T1*Q2+128*T1-64*Q2)
      VPS(29) =
     &  +M2*LHM2*(24*U1P2*T1M1*Q2-8*U1P2-16*U1*T1P2*TM1-16*U1
     &  *T1*TM1*Q2-24*U1*T1-32*U1*T1M1*Q22+152*U1*Q2+24*U1M1*T1P4
     &  *TM1+16*U1M1*T1P3*TM1*Q2-40*U1M1*T1P3-8*U1M1*T1P2*TM1*
     &  Q22+40*U1M1*T1P2*Q2-64*U1M1*T1*Q22+24*T1P3*TM1+32*T1P2*
     &  TM1*Q2-56*T1P2+8*T1*TM1*Q22+168*T1*Q2-96*Q22)
     &  +M2*LHM3*DLOGQ6T*(48*U1P2*T1+80*U1*T1P2+112*U1*T1*Q2-32*
     &  U1*Q22+8*U1M1*T1P4+48*U1M1*T1P3*Q2-48*U1M1*T1P2*Q22+88*
     &  T1P3+176*T1P2*Q2-112*T1*Q22)
     &  +M2*LHM3*DLOGQ7T*(48*U1P2*T1+80*U1*T1P2+112*U1*T1*Q2-32*
     &  U1*Q22+8*U1M1*T1P4+48*U1M1*T1P3*Q2-48*U1M1*T1P2*Q22+88*
     &  T1P3+176*T1P2*Q2-112*T1*Q22)
     &  +M2*LHM3*DLOGQ8T*(-48*U1P2*T1-80*U1*T1P2-112*U1*T1*Q2+
     &  32*U1*Q22-8*U1M1*T1P4-48*U1M1*T1P3*Q2+48*U1M1*T1P2*Q22-
     &  88*T1P3-176*T1P2*Q2+112*T1*Q22)
     &  +M2*LHM3*DLOGQ9T*(-48*U1P2*T1-80*U1*T1P2-112*U1*T1*Q2+
     &  32*U1*Q22-8*U1M1*T1P4-48*U1M1*T1P3*Q2+48*U1M1*T1P2*Q22-
     &  88*T1P3-176*T1P2*Q2+112*T1*Q22)
      VPS(30) =
     &  +M2*LHM3*DLOGQ10T*(-48*U1P2*T1-80*U1*T1P2-112*U1*T1*Q2+
     &  32*U1*Q22-8*U1M1*T1P4-48*U1M1*T1P3*Q2+48*U1M1*T1P2*Q22-
     &  88*T1P3-176*T1P2*Q2+112*T1*Q22)
     &  +M2*LHM3*DLOGQ11T*(-48*U1P2*T1-80*U1*T1P2-112*U1*T1*Q2+
     &  32*U1*Q22-8*U1M1*T1P4-48*U1M1*T1P3*Q2+48*U1M1*T1P2*Q22-
     &  88*T1P3-176*T1P2*Q2+112*T1*Q22)
     &  +M2*LHM3*DLOGQ12T*(48*U1P2*T1+80*U1*T1P2+112*U1*T1*Q2-32*
     &  U1*Q22+8*U1M1*T1P4+48*U1M1*T1P3*Q2-48*U1M1*T1P2*Q22+88*
     &  T1P3+176*T1P2*Q2-112*T1*Q22)
     &  +M2*LHM3*DLOGQ13T*(96*U1P2*T1+160*U1*T1P2+224*U1*T1*Q2-64
     &  *U1*Q22+16*U1M1*T1P4+96*U1M1*T1P3*Q2-96*U1M1*T1P2*Q22+
     &  176*T1P3+352*T1P2*Q2-224*T1*Q22)
     &  +M2*LHM5*DLOGQ6T*(-32*U1P2*T1P3+48*U1P2*T1P2*Q2-16*U1P2*
     &  T1*Q22-144*U1*T1P4+432*U1*T1P3*Q2-336*U1*T1P2*Q22+48*U1*T1*
     &  Q23-24*U1M1*T1P6+96*U1M1*T1P5*Q2-120*U1M1*T1P4*Q22+48*
     &  U1M1*T1P3*Q23-152*T1P5+432*T1P4*Q2-440*T1P3*Q22+160*T1P2*
     &  Q23)
      VPS(31) =
     &  +M2*LHM5*DLOGQ7T*(-32*U1P2*T1P3+48*U1P2*T1P2*Q2-16*U1P2*
     &  T1*Q22-144*U1*T1P4+432*U1*T1P3*Q2-336*U1*T1P2*Q22+48*U1*T1*
     &  Q23-24*U1M1*T1P6+96*U1M1*T1P5*Q2-120*U1M1*T1P4*Q22+48*
     &  U1M1*T1P3*Q23-152*T1P5+432*T1P4*Q2-440*T1P3*Q22+160*T1P2*
     &  Q23)
     &  +M2*LHM5*DLOGQ8T*(32*U1P2*T1P3-48*U1P2*T1P2*Q2+16*U1P2*T1*
     &  Q22+144*U1*T1P4-432*U1*T1P3*Q2+336*U1*T1P2*Q22-48*U1*T1*
     &  Q23+24*U1M1*T1P6-96*U1M1*T1P5*Q2+120*U1M1*T1P4*Q22-48*
     &  U1M1*T1P3*Q23+152*T1P5-432*T1P4*Q2+440*T1P3*Q22-160*T1P2*
     &  Q23)
     &  +M2*LHM5*DLOGQ9T*(32*U1P2*T1P3-48*U1P2*T1P2*Q2+16*U1P2*T1*
     &  Q22+144*U1*T1P4-432*U1*T1P3*Q2+336*U1*T1P2*Q22-48*U1*T1*
     &  Q23+24*U1M1*T1P6-96*U1M1*T1P5*Q2+120*U1M1*T1P4*Q22-48*
     &  U1M1*T1P3*Q23+152*T1P5-432*T1P4*Q2+440*T1P3*Q22-160*T1P2*
     &  Q23)
      VPS(32) =
     &  +M2*LHM5*DLOGQ10T*(32*U1P2*T1P3-48*U1P2*T1P2*Q2+16*U1P2*T1*
     &  Q22+144*U1*T1P4-432*U1*T1P3*Q2+336*U1*T1P2*Q22-48*U1*T1*
     &  Q23+24*U1M1*T1P6-96*U1M1*T1P5*Q2+120*U1M1*T1P4*Q22-48*
     &  U1M1*T1P3*Q23+152*T1P5-432*T1P4*Q2+440*T1P3*Q22-160*T1P2*
     &  Q23)
     &  +M2*LHM5*DLOGQ11T*(32*U1P2*T1P3-48*U1P2*T1P2*Q2+16*U1P2*T1*
     &  Q22+144*U1*T1P4-432*U1*T1P3*Q2+336*U1*T1P2*Q22-48*U1*T1*
     &  Q23+24*U1M1*T1P6-96*U1M1*T1P5*Q2+120*U1M1*T1P4*Q22-48*
     &  U1M1*T1P3*Q23+152*T1P5-432*T1P4*Q2+440*T1P3*Q22-160*T1P2*
     &  Q23)
     &  +M2*LHM5*DLOGQ12T*(-32*U1P2*T1P3+48*U1P2*T1P2*Q2-16*U1P2*
     &  T1*Q22-144*U1*T1P4+432*U1*T1P3*Q2-336*U1*T1P2*Q22+48*U1*T1*
     &  Q23-24*U1M1*T1P6+96*U1M1*T1P5*Q2-120*U1M1*T1P4*Q22+48*
     &  U1M1*T1P3*Q23-152*T1P5+432*T1P4*Q2-440*T1P3*Q22+160*T1P2*
     &  Q23)
      VPS(33) =
     &  +M2*LHM5*DLOGQ13T*(-64*U1P2*T1P3+96*U1P2*T1P2*Q2-32*U1P2*
     &  T1*Q22-288*U1*T1P4+864*U1*T1P3*Q2-672*U1*T1P2*Q22+96*U1*T1*
     &  Q23-48*U1M1*T1P6+192*U1M1*T1P5*Q2-240*U1M1*T1P4*Q22+96*
     &  U1M1*T1P3*Q23-304*T1P5+864*T1P4*Q2-880*T1P3*Q22+320*T1P2*
     &  Q23)
     &  +M2*LHPM1*DLOGQ6U*(32*U1P2*T1M1-16*U1*T1M1*Q2+64*U1-16*
     &  U1M1*T1*Q2+64*T1-32*Q2)
     &  +M2*LHPM1*DLOGQ7U*(32*U1P2*T1M1-16*U1*T1M1*Q2+64*U1-16*
     &  U1M1*T1*Q2+64*T1-32*Q2)
     &  +M2*LHPM1*DLOGQ8U*(-32*U1P2*T1M1+16*U1*T1M1*Q2-64*U1+
     &  16*U1M1*T1*Q2-64*T1+32*Q2)
     &  +M2*LHPM1*DLOGQ9U*(-32*U1P2*T1M1+16*U1*T1M1*Q2-64*U1+
     &  16*U1M1*T1*Q2-64*T1+32*Q2)
     &  +M2*LHPM1*DLOGQ10U*(-32*U1P2*T1M1+16*U1*T1M1*Q2-64*U1
     &  +16*U1M1*T1*Q2-64*T1+32*Q2)
     &  +M2*LHPM1*DLOGQ11U*(-32*U1P2*T1M1+16*U1*T1M1*Q2-64*U1
     &  +16*U1M1*T1*Q2-64*T1+32*Q2)
      VPS(34) =
     &  +M2*LHPM1*DLOGQ12U*(32*U1P2*T1M1-16*U1*T1M1*Q2+64*U1-16
     &  *U1M1*T1*Q2+64*T1-32*Q2)
     &  +M2*LHPM1*DLOGQ13U*(64*U1P2*T1M1-32*U1*T1M1*Q2+128*U1-
     &  32*U1M1*T1*Q2+128*T1-64*Q2)
     &  +M2*LHPM2*(24*U1P4*T1M1*UM1+16*U1P3*T1M1*UM1*Q2-40*
     &  U1P3*T1M1+24*U1P3*UM1-16*U1P2*T1*UM1-8*U1P2*T1M1*UM1*Q22
     &  +40*U1P2*T1M1*Q2+32*U1P2*UM1*Q2-56*U1P2-16*U1*T1*UM1*Q2-
     &  24*U1*T1-64*U1*T1M1*Q22+8*U1*UM1*Q22+168*U1*Q2+24*U1M1*
     &  T1P2*Q2-32*U1M1*T1*Q22-8*T1P2+152*T1*Q2-96*Q22)
     &  +M2*LHPM3*DLOGQ6U*(8*U1P4*T1M1+48*U1P3*T1M1*Q2+88*U1P3+
     &  80*U1P2*T1-48*U1P2*T1M1*Q22+176*U1P2*Q2+48*U1*T1P2+112*U1*
     &  T1*Q2-112*U1*Q22-32*T1*Q22)
     &  +M2*LHPM3*DLOGQ7U*(8*U1P4*T1M1+48*U1P3*T1M1*Q2+88*U1P3+
     &  80*U1P2*T1-48*U1P2*T1M1*Q22+176*U1P2*Q2+48*U1*T1P2+112*U1*
     &  T1*Q2-112*U1*Q22-32*T1*Q22)
     &  +M2*LHPM3*DLOGQ8U*(-8*U1P4*T1M1-48*U1P3*T1M1*Q2-88*U1P3
     &  -80*U1P2*T1+48*U1P2*T1M1*Q22-176*U1P2*Q2-48*U1*T1P2-112*
     &  U1*T1*Q2+112*U1*Q22+32*T1*Q22)
      VPS(35) =
     &  +M2*LHPM3*DLOGQ9U*(-8*U1P4*T1M1-48*U1P3*T1M1*Q2-88*U1P3
     &  -80*U1P2*T1+48*U1P2*T1M1*Q22-176*U1P2*Q2-48*U1*T1P2-112*
     &  U1*T1*Q2+112*U1*Q22+32*T1*Q22)
     &  +M2*LHPM3*DLOGQ10U*(-8*U1P4*T1M1-48*U1P3*T1M1*Q2-88*
     &  U1P3-80*U1P2*T1+48*U1P2*T1M1*Q22-176*U1P2*Q2-48*U1*T1P2-
     &  112*U1*T1*Q2+112*U1*Q22+32*T1*Q22)
     &  +M2*LHPM3*DLOGQ11U*(-8*U1P4*T1M1-48*U1P3*T1M1*Q2-88*
     &  U1P3-80*U1P2*T1+48*U1P2*T1M1*Q22-176*U1P2*Q2-48*U1*T1P2-
     &  112*U1*T1*Q2+112*U1*Q22+32*T1*Q22)
     &  +M2*LHPM3*DLOGQ12U*(8*U1P4*T1M1+48*U1P3*T1M1*Q2+88*U1P3
     &  +80*U1P2*T1-48*U1P2*T1M1*Q22+176*U1P2*Q2+48*U1*T1P2+112*
     &  U1*T1*Q2-112*U1*Q22-32*T1*Q22)
     &  +M2*LHPM3*DLOGQ13U*(16*U1P4*T1M1+96*U1P3*T1M1*Q2+176*U1P3
     &  +160*U1P2*T1-96*U1P2*T1M1*Q22+352*U1P2*Q2+96*U1*T1P2+224*
     &  U1*T1*Q2-224*U1*Q22-64*T1*Q22)
      VPS(36) =
     &  +M2*LHPM5*DLOGQ6U*(-24*U1P6*T1M1+96*U1P5*T1M1*Q2-152*
     &  U1P5-144*U1P4*T1-120*U1P4*T1M1*Q22+432*U1P4*Q2-32*U1P3*T1P2
     &  +432*U1P3*T1*Q2+48*U1P3*T1M1*Q23-440*U1P3*Q22+48*U1P2*T1P2
     &  *Q2-336*U1P2*T1*Q22+160*U1P2*Q23-16*U1*T1P2*Q22+48*U1*T1*
     &  Q23)
     &  +M2*LHPM5*DLOGQ7U*(-24*U1P6*T1M1+96*U1P5*T1M1*Q2-152*
     &  U1P5-144*U1P4*T1-120*U1P4*T1M1*Q22+432*U1P4*Q2-32*U1P3*T1P2
     &  +432*U1P3*T1*Q2+48*U1P3*T1M1*Q23-440*U1P3*Q22+48*U1P2*T1P2
     &  *Q2-336*U1P2*T1*Q22+160*U1P2*Q23-16*U1*T1P2*Q22+48*U1*T1*
     &  Q23)
     &  +M2*LHPM5*DLOGQ8U*(24*U1P6*T1M1-96*U1P5*T1M1*Q2+152*U1P5
     &  +144*U1P4*T1+120*U1P4*T1M1*Q22-432*U1P4*Q2+32*U1P3*T1P2-
     &  432*U1P3*T1*Q2-48*U1P3*T1M1*Q23+440*U1P3*Q22-48*U1P2*T1P2*Q2
     &  +336*U1P2*T1*Q22-160*U1P2*Q23+16*U1*T1P2*Q22-48*U1*T1*Q23
     &  )
      VPS(37) =
     &  +M2*LHPM5*DLOGQ9U*(24*U1P6*T1M1-96*U1P5*T1M1*Q2+152*U1P5
     &  +144*U1P4*T1+120*U1P4*T1M1*Q22-432*U1P4*Q2+32*U1P3*T1P2-
     &  432*U1P3*T1*Q2-48*U1P3*T1M1*Q23+440*U1P3*Q22-48*U1P2*T1P2*Q2
     &  +336*U1P2*T1*Q22-160*U1P2*Q23+16*U1*T1P2*Q22-48*U1*T1*Q23
     &  )
     &  +M2*LHPM5*DLOGQ10U*(24*U1P6*T1M1-96*U1P5*T1M1*Q2+152*U1P5
     &  +144*U1P4*T1+120*U1P4*T1M1*Q22-432*U1P4*Q2+32*U1P3*T1P2-
     &  432*U1P3*T1*Q2-48*U1P3*T1M1*Q23+440*U1P3*Q22-48*U1P2*T1P2*Q2
     &  +336*U1P2*T1*Q22-160*U1P2*Q23+16*U1*T1P2*Q22-48*U1*T1*Q23
     &  )
     &  +M2*LHPM5*DLOGQ11U*(24*U1P6*T1M1-96*U1P5*T1M1*Q2+152*U1P5
     &  +144*U1P4*T1+120*U1P4*T1M1*Q22-432*U1P4*Q2+32*U1P3*T1P2-
     &  432*U1P3*T1*Q2-48*U1P3*T1M1*Q23+440*U1P3*Q22-48*U1P2*T1P2*Q2
     &  +336*U1P2*T1*Q22-160*U1P2*Q23+16*U1*T1P2*Q22-48*U1*T1*Q23
     &  )
      VPS(38) =
     &  +M2*LHPM5*DLOGQ12U*(-24*U1P6*T1M1+96*U1P5*T1M1*Q2-152*
     &  U1P5-144*U1P4*T1-120*U1P4*T1M1*Q22+432*U1P4*Q2-32*U1P3*T1P2
     &  +432*U1P3*T1*Q2+48*U1P3*T1M1*Q23-440*U1P3*Q22+48*U1P2*T1P2
     &  *Q2-336*U1P2*T1*Q22+160*U1P2*Q23-16*U1*T1P2*Q22+48*U1*T1*
     &  Q23)
     &  +M2*LHPM5*DLOGQ13U*(-48*U1P6*T1M1+192*U1P5*T1M1*Q2-304*
     &  U1P5-288*U1P4*T1-240*U1P4*T1M1*Q22+864*U1P4*Q2-64*U1P3*T1P2
     &  +864*U1P3*T1*Q2+96*U1P3*T1M1*Q23-880*U1P3*Q22+96*U1P2*T1P2
     &  *Q2-672*U1P2*T1*Q22+320*U1P2*Q23-32*U1*T1P2*Q22+96*U1*T1*
     &  Q23)
     &  +M2*LOG7X2*(8*U1P2*T1M1*SPM1+24*U1*SPM1+8*U1M1*T1P2*
     &  SPM1+24*T1*SPM1)
     &  +M2*(128-8*U1P2*T1M1*UM1+32*U1*T1M1*Q2*S1M1+64*U1*
     &  T1M1+40*U1*UM1+48*U1*TM1-64*U1*S1M1-8*U1M1*T1P2*TM1+
     &  32*U1M1*T1*Q2*S1M1+64*U1M1*T1-64*U1M1*Q2+48*T1*UM1+40*T1
     &  *TM1-64*T1*S1M1-64*T1M1*Q2-16*UM1*Q2-16*TM1*Q2+64*Q2*
     &  S1M1)
      VPS(39) =
     &  +XSQM1*LOG1X2*(-32*BQED)
     &  +XSQM1*LOG1*LOG5*(64*BQED)
     &  +XSQM1*LOG1*LOG6*(64*BQED)
     &  +XSQM1*LOG1*(-64*BQED*LOGDEL-32*BQED)
     &  +XSQM1*DLOG2*(64*BQED)
     &  +XSQM1*DLOG1*(64*BQED)
     &  +XSQM1*ZETA2*(-32*BQED)
     &  +LOG1X2*SQM*(8*U1P2+16*U1*T1-16*U1*Q2+8*T1P2-16*T1*
     &  Q2+8*Q22)
     &  +LOG1X2*(-8*U1P3*SPM2-24*U1P2*T1*SPM2+8*U1P2*Q2*SPM2
     &  -16*U1P2*SPM1-24*U1*T1P2*SPM2+16*U1*T1*Q2*SPM2-32*U1*T1*
     &  SPM1+16*U1*Q2*SPM1-8*T1P3*SPM2+8*T1P2*Q2*SPM2-16*T1P2*
     &  SPM1+16*T1*Q2*SPM1)
     &  +LOG1*LOG5*SQM*(-64*U1P2-128*U1*T1+128*U1*Q2-64*
     &  T1P2+128*T1*Q2-64*Q22)
     &  +LOG1*LOG6*SQM*(32*U1P2+64*U1*T1-64*U1*Q2+32*T1P2-
     &  64*T1*Q2+32*Q22)
      VPS(40) =
     &  +LOG1*LOG3*SQM*(-16*U1P2-32*U1*T1+32*U1*Q2-16*T1P2
     &  +32*T1*Q2-16*Q22)
     &  +LOG1*LOG4*SQM*(-16*U1P2-32*U1*T1+32*U1*Q2-16*T1P2
     &  +32*T1*Q2-16*Q22)
     &  +LOG1*SQM*LOGQ1*(16*U1P2+32*U1*T1-32*U1*Q2+16*T1P2-
     &  32*T1*Q2+16*Q22)
      VPS(41) =
     &  +LOG1*SQM*(-8*U1P4*T1M1*S1M1+8*U1P4*T1M1*SPM1+20*
     &  U1P3*T1M1*Q2*S1M1-16*U1P3*T1M1*Q2*SPM1+16*U1P3*T1M1-32*
     &  U1P3*Q2*SPM2+8*U1P3*SPM1-96*U1P2*T1*Q2*SPM2+40*U1P2*T1*S1M1
     &  -16*U1P2*T1*SPM1-16*U1P2*T1M1*Q22*S1M1+8*U1P2*T1M1*Q22*
     &  SPM1-28*U1P2*T1M1*Q2+32*U1P2*Q22*SPM2-32*U1P2*Q2*S1M1-32
     &  *U1P2*Q2*SPM1+24*U1P2-96*U1*T1P2*Q2*SPM2+40*U1*T1P2*S1M1-
     &  16*U1*T1P2*SPM1+64*U1*T1*Q22*SPM2-104*U1*T1*Q2*S1M1-32*U1*
     &  T1*Q2*SPM1+16*U1*T1+4*U1*T1M1*Q23*S1M1+12*U1*T1M1*Q22+
     &  56*U1*Q22*S1M1+24*U1*Q22*SPM1-12*U1*Q2-8*U1M1*T1P4*S1M1
     &  +8*U1M1*T1P4*SPM1+20*U1M1*T1P3*Q2*S1M1-16*U1M1*T1P3*Q2*
     &  SPM1+16*U1M1*T1P3-16*U1M1*T1P2*Q22*S1M1+8*U1M1*T1P2*Q22*
     &  SPM1-28*U1M1*T1P2*Q2+4*U1M1*T1*Q23*S1M1+12*U1M1*T1*Q22
     &  -32*T1P3*Q2*SPM2+8*T1P3*SPM1+32*T1P2*Q22*SPM2-32*T1P2*Q2*
     &  S1M1-32*T1P2*Q2*SPM1+24*T1P2+56*T1*Q22*S1M1+24*T1*Q22*
     &  SPM1-12*T1*Q2-24*Q23*S1M1-8*Q22)
      VPS(42) =
     &  +LOG3*LHM2*(-32*U1P2*T1P2*TM1+16*U1P2*T1*TM1*Q2-96*U1*
     &  T1P3*TM1+72*U1*T1P2*TM1*Q2-24*U1*T1*TM1*Q22-4*U1M1*T1P6*
     &  TM2-12*U1M1*T1P5*TM1+4*U1M1*T1P5*TM2*Q2+36*U1M1*T1P4*TM1
     &  *Q2+12*U1M1*T1P4*TM2*Q22-24*U1M1*T1P3*TM1*Q22+4*U1M1*
     &  T1P3*TM2*Q23-20*T1P5*TM2-68*T1P4*TM1-24*T1P4*TM2*Q2+108*
     &  T1P3*TM1*Q2-4*T1P3*TM2*Q22-32*T1P2*TM1*Q22+8*T1*TM1*Q23
     &  )
     &  +LOG3*LHM4*(24*U1P2*T1P4*TM1-48*U1P2*T1P3*TM1*Q2+24*U1P2
     &  *T1P2*TM1*Q22+80*U1*T1P5*TM1-192*U1*T1P4*TM1*Q2+144*U1*T1P3
     &  *TM1*Q22-32*U1*T1P2*TM1*Q23+12*U1M1*T1P7*TM1-52*U1M1*
     &  T1P6*TM1*Q2+68*U1M1*T1P5*TM1*Q22-28*U1M1*T1P4*TM1*Q23+76
     &  *T1P6*TM1-204*T1P5*TM1*Q2+188*T1P4*TM1*Q22-68*T1P3*TM1*
     &  Q23+8*T1P2*TM1*Q24)
     &  +LOG3*(-16*U1*T1P2*TM2+24*U1*T1*TM1+12*U1M1*T1P4*TM2
     &  -8*U1M1*T1P3*TM1-4*U1M1*T1P3*TM2*Q2-4*T1P3*TM2+16*T1P2*
     &  TM1+16*T1P2*TM2*Q2-24*T1*TM1*Q2)
      VPS(43) =
     &  +LOG4*LHPM2*(-4*U1P6*T1M1*UM2-12*U1P5*T1M1*UM1+4*
     &  U1P5*T1M1*UM2*Q2-20*U1P5*UM2+36*U1P4*T1M1*UM1*Q2+12*U1P4*
     &  T1M1*UM2*Q22-68*U1P4*UM1-24*U1P4*UM2*Q2-96*U1P3*T1*UM1-
     &  24*U1P3*T1M1*UM1*Q22+4*U1P3*T1M1*UM2*Q23+108*U1P3*UM1*Q2
     &  -4*U1P3*UM2*Q22-32*U1P2*T1P2*UM1+72*U1P2*T1*UM1*Q2-32*
     &  U1P2*UM1*Q22+16*U1*T1P2*UM1*Q2-24*U1*T1*UM1*Q22+8*U1*UM1*
     &  Q23)
     &  +LOG4*LHPM4*U1P2*(12*U1P5*T1M1*UM1-52*U1P4*T1M1*UM1*Q2+76*
     &  U1P4*UM1+80*U1P3*T1*UM1+68*U1P3*T1M1*UM1*Q22-204*U1P3*UM1
     &  *Q2+24*U1P2*T1P2*UM1-192*U1P2*T1*UM1*Q2-28*U1P2*T1M1*UM1*
     &  Q23+188*U1P2*UM1*Q22-48*U1*T1P2*UM1*Q2+144*U1*T1*UM1*
     &  Q22-68*U1*UM1*Q23+24*T1P2*UM1*Q22-32*T1*UM1*
     &  Q23+8*UM1*Q24)
     &  +LOG4*(12*U1P4*T1M1*UM2-8*U1P3*T1M1*UM1-4*U1P3*T1M1*
     &  UM2*Q2-4*U1P3*UM2-16*U1P2*T1*UM2+16*U1P2*UM1+16*U1P2*UM2
     &  *Q2+24*U1*T1*UM1-24*U1*UM1*Q2)
      VPS(44) =
     &  +DLOG2*SQM*(-64*U1P2-128*U1*T1+128*U1*Q2-64*T1P2+
     &  128*T1*Q2-64*Q22)
     &  +DLOG3*(-8*U1-8*T1+8*Q2)
     &  +DLOG4*(-8*U1-8*T1+8*Q2)
     &  +DLOG1*SQM*(32*U1P2+64*U1*T1-64*U1*Q2+32*T1P2-64*T1
     &  *Q2+32*Q22)
     &  +ZETA2*SQM*(-176*U1P2-352*U1*T1+352*U1*Q2-176*T1P2
     &  +352*T1*Q2-176*Q22)
     &  +ZETA2*LHM1*(-32*U1*T1+8*U1*Q2-16*U1M1*T1P3+8*U1M1*
     &  T1P2*Q2-48*T1P2+32*T1*Q2-8*Q22)
     &  +ZETA2*LHM3*(-8*U1P2*T1P2+8*U1P2*T1*Q2-8*U1*T1P3-8*U1
     &  *T1P2*Q2+16*U1*T1*Q22+16*U1M1*T1P5-40*U1M1*T1P4*Q2+32*
     &  U1M1*T1P3*Q22-8*U1M1*T1P2*Q23+32*T1P4-72*T1P3*Q2+56*T1P2*
     &  Q22-16*T1*Q23)
     &  +ZETA2*LHM5*(8*U1P2*T1P4-24*U1P2*T1P3*Q2+24*U1P2*T1P2*
     &  Q22-8*U1P2*T1*Q23+32*U1*T1P5-104*U1*T1P4*Q2+120*U1*T1P3*
     &  Q22-56*U1*T1P2*Q23+8*U1*T1*Q24+8*T1P6-40*T1P5*Q2+72*T1P4
     &  *Q22-56*T1P3*Q23+16*T1P2*Q24)
      VPS(45) =
     &  +ZETA2*LHPM1*(-16*U1P3*T1M1+8*U1P2*T1M1*Q2-48*U1P2-
     &  32*U1*T1+32*U1*Q2+8*T1*Q2-8*Q22)
     &  +ZETA2*LHPM3*(16*U1P5*T1M1-40*U1P4*T1M1*Q2+32*U1P4-8*
     &  U1P3*T1+32*U1P3*T1M1*Q22-72*U1P3*Q2-8*U1P2*T1P2-8*U1P2*T1*
     &  Q2-8*U1P2*T1M1*Q23+56*U1P2*Q22+8*U1*T1P2*Q2+16*U1*T1*Q22
     &  -16*U1*Q23)
     &  +ZETA2*LHPM5*(8*U1P6+32*U1P5*T1-40*U1P5*Q2+8*U1P4*T1P2
     &  -104*U1P4*T1*Q2+72*U1P4*Q22-24*U1P3*T1P2*Q2+120*U1P3*T1*Q22
     &  -56*U1P3*Q23+24*U1P2*T1P2*Q22-56*U1P2*T1*Q23+16*U1P2*Q24
     &  -8*U1*T1P2*Q23+8*U1*T1*Q24)
     &  +ZETA2*(48*U1P3*SPM2+144*U1P2*T1*SPM2-48*U1P2*Q2*SPM2
     &  +96*U1P2*SPM1+144*U1*T1P2*SPM2-96*U1*T1*Q2*SPM2+192*U1*T1*
     &  SPM1-96*U1*Q2*SPM1+16*U1+48*T1P3*SPM2-48*T1P2*Q2*SPM2+
     &  96*T1P2*SPM1-96*T1*Q2*SPM1+16*T1-16*Q2)
     &  +SQM*LOG8*LOGQ2*(16*U1P2+32*U1*T1-32*U1*Q2+16*T1P2-
     &  32*T1*Q2+16*Q22)
      VPS(46) =
     &  +SQM*DLOGQ1*(32*U1P2+64*U1*T1-64*U1*Q2+32*T1P2-64*T1
     &  *Q2+32*Q22)
     &  +SQM*DLOGQ2*(32*U1P2+64*U1*T1-64*U1*Q2+32*T1P2-64*T1
     &  *Q2+32*Q22)
     &  +SQM*DLOGQ3*(32*U1P2+64*U1*T1-64*U1*Q2+32*T1P2-64*T1
     &  *Q2+32*Q22)
     &  +SQM*DLOGQ4*(-32*U1P2-64*U1*T1+64*U1*Q2-32*T1P2+64
     &  *T1*Q2-32*Q22)
     &  +SQM*LOGQ3X2*(16*U1P2+32*U1*T1-32*U1*Q2+16*T1P2-32*
     &  T1*Q2+16*Q22)
     &  +LOG9*LHM2*(28*U1P2*T1*X1-28*U1P2*T1*X2+4*U1P2*T1M1*Q22
     &  *X1-4*U1P2*T1M1*Q22*X2-16*U1P2*Q2*X1+16*U1P2*Q2*X2+104*U1*
     &  T1P2*X1-104*U1*T1P2*X2-116*U1*T1*Q2*X1+116*U1*T1*Q2*X2-4*U1*
     &  T1M1*Q23*X1+4*U1*T1M1*Q23*X2+64*U1*Q22*X1-64*U1*Q22*X2+
     &  32*U1M1*T1P4*X1-32*U1M1*T1P4*X2-80*U1M1*T1P3*Q2*X1+80*U1M1*
     &  T1P3*Q2*X2+44*U1M1*T1P2*Q22*X1-44*U1M1*T1P2*Q22*X2-12*U1M1
     &  *T1*Q23*X1+12*U1M1*T1*Q23*X2+124*T1P3*X1-124*T1P3*X2-172*
     &  T1P2*Q2*X1+172*T1P2*Q2*X2+112*T1*Q22*X1-112*T1*Q22*X2-32*
     &  Q23*X1+32*Q23*X2)
      VPS(47) =
     &  +LOG9*LHM4*(-16*U1P2*T1P3*X1+16*U1P2*T1P3*X2+24*U1P2*
     &  T1P2*Q2*X1-24*U1P2*T1P2*Q2*X2-8*U1P2*Q23*X1+8*U1P2*Q23*X2-
     &  48*U1*T1P4*X1+48*U1*T1P4*X2+88*U1*T1P3*Q2*X1-88*U1*T1P3*Q2*X2
     &  -24*U1*T1P2*Q22*X1+24*U1*T1P2*Q22*X2-24*U1*T1*Q23*X1+24*U1
     &  *T1*Q23*X2+8*U1*Q24*X1-8*U1*Q24*X2-12*U1M1*T1P6*X1+12*
     &  U1M1*T1P6*X2+52*U1M1*T1P5*Q2*X1-52*U1M1*T1P5*Q2*X2-68*U1M1*
     &  T1P4*Q22*X1+68*U1M1*T1P4*Q22*X2+28*U1M1*T1P3*Q23*X1-28*
     &  U1M1*T1P3*Q23*X2-68*T1P5*X1+68*T1P5*X2+164*T1P4*Q2*X1-164*
     &  T1P4*Q2*X2-116*T1P3*Q22*X1+116*T1P3*Q22*X2+12*T1P2*Q23*X1-
     &  12*T1P2*Q23*X2+8*T1*Q24*X1-8*T1*Q24*X2)
     &  +LOG9*LHPM2*(32*U1P4*T1M1*X1-32*U1P4*T1M1*X2-80*U1P3*
     &  T1M1*Q2*X1+80*U1P3*T1M1*Q2*X2+124*U1P3*X1-124*U1P3*X2+104*
     &  U1P2*T1*X1-104*U1P2*T1*X2+44*U1P2*T1M1*Q22*X1-44*U1P2*T1M1*
     &  Q22*X2-172*U1P2*Q2*X1+172*U1P2*Q2*X2+28*U1*T1P2*X1-28*U1*
     &  T1P2*X2-116*U1*T1*Q2*X1+116*U1*T1*Q2*X2-12*U1*T1M1*Q23*X1+
     &  12*U1*T1M1*Q23*X2+112*U1*Q22*X1-112*U1*Q22*X2+4*U1M1*T1P2*
     &  Q22*X1-4*U1M1*T1P2*Q22*X2-4*U1M1*T1*Q23*X1+4*U1M1*T1*Q23
     &  *X2-16*T1P2*Q2*X1+16*T1P2*Q2*X2+64*T1*Q22*X1-64*T1*Q22*X2
     &  -32*Q23*X1+32*Q23*X2)
      VPS(48) =
     &  +LOG9*LHPM4*(-12*U1P6*T1M1*X1+12*U1P6*T1M1*X2+52*U1P5
     &  *T1M1*Q2*X1-52*U1P5*T1M1*Q2*X2-68*U1P5*X1+68*U1P5*X2-48*
     &  U1P4*T1*X1+48*U1P4*T1*X2-68*U1P4*T1M1*Q22*X1+68*U1P4*T1M1*
     &  Q22*X2+164*U1P4*Q2*X1-164*U1P4*Q2*X2-16*U1P3*T1P2*X1+16*U1P3
     &  *T1P2*X2+88*U1P3*T1*Q2*X1-88*U1P3*T1*Q2*X2+28*U1P3*T1M1*Q23*
     &  X1-28*U1P3*T1M1*Q23*X2-116*U1P3*Q22*X1+116*U1P3*Q22*X2+24
     &  *U1P2*T1P2*Q2*X1-24*U1P2*T1P2*Q2*X2-24*U1P2*T1*Q22*X1+24*U1P2*
     &  T1*Q22*X2+12*U1P2*Q23*X1-12*U1P2*Q23*X2-24*U1*T1*Q23*X1+
     &  24*U1*T1*Q23*X2+8*U1*Q24*X1-8*U1*Q24*X2-8*T1P2*Q23*X1+8*
     &  T1P2*Q23*X2+8*T1*Q24*X1-8*T1*Q24*X2)
      VPS(49) =
     &  +LOG9*(-8*U1P3*T1M1*SPM1*X1+8*U1P3*T1M1*SPM1*X2+8*
     &  U1P2*T1M1*Q2*SPM1*X1-8*U1P2*T1M1*Q2*SPM1*X2-32*U1P2*T1M1*X1
     &  +32*U1P2*T1M1*X2+32*U1P2*Q2*SPM2*X1-32*U1P2*Q2*SPM2*X2-16*
     &  U1P2*SPM1*X1+16*U1P2*SPM1*X2+64*U1*T1*Q2*SPM2*X1-64*U1*T1*Q2
     &  *SPM2*X2-16*U1*T1*SPM1*X1+16*U1*T1*SPM1*X2+24*U1*T1M1*Q2*X1
     &  -24*U1*T1M1*Q2*X2+24*U1*Q2*SPM1*X1-24*U1*Q2*SPM1*X2-96*U1*
     &  X1+96*U1*X2-8*U1M1*T1P3*SPM1*X1+8*U1M1*T1P3*SPM1*X2+8*
     &  U1M1*T1P2*Q2*SPM1*X1-8*U1M1*T1P2*Q2*SPM1*X2-32*U1M1*T1P2*X1
     &  +32*U1M1*T1P2*X2+24*U1M1*T1*Q2*X1-24*U1M1*T1*Q2*X2+32*T1P2
     &  *Q2*SPM2*X1-32*T1P2*Q2*SPM2*X2-16*T1P2*SPM1*X1+16*T1P2*SPM1
     &  *X2+24*T1*Q2*SPM1*X1-24*T1*Q2*SPM1*X2-96*T1*X1+96*T1*X2+
     &  32*Q2*X1-32*Q2*X2)
      VPS(50) =
     &  +LOG10*LHM2*(-28*U1P2*T1*X1+28*U1P2*T1*X2-4*U1P2*T1M1*
     &  Q22*X1+4*U1P2*T1M1*Q22*X2+16*U1P2*Q2*X1-16*U1P2*Q2*X2-104*
     &  U1*T1P2*X1+104*U1*T1P2*X2+116*U1*T1*Q2*X1-116*U1*T1*Q2*X2+4*
     &  U1*T1M1*Q23*X1-4*U1*T1M1*Q23*X2-64*U1*Q22*X1+64*U1*Q22*X2
     &  -32*U1M1*T1P4*X1+32*U1M1*T1P4*X2+80*U1M1*T1P3*Q2*X1-80*
     &  U1M1*T1P3*Q2*X2-44*U1M1*T1P2*Q22*X1+44*U1M1*T1P2*Q22*X2+12
     &  *U1M1*T1*Q23*X1-12*U1M1*T1*Q23*X2-124*T1P3*X1+124*T1P3*X2
     &  +172*T1P2*Q2*X1-172*T1P2*Q2*X2-112*T1*Q22*X1+112*T1*Q22*X2
     &  +32*Q23*X1-32*Q23*X2)
     &  +LOG10*LHM4*(16*U1P2*T1P3*X1-16*U1P2*T1P3*X2-24*U1P2*T1P2
     &  *Q2*X1+24*U1P2*T1P2*Q2*X2+8*U1P2*Q23*X1-8*U1P2*Q23*X2+48*U1
     &  *T1P4*X1-48*U1*T1P4*X2-88*U1*T1P3*Q2*X1+88*U1*T1P3*Q2*X2+24*
     &  U1*T1P2*Q22*X1-24*U1*T1P2*Q22*X2+24*U1*T1*Q23*X1-24*U1*T1*
     &  Q23*X2-8*U1*Q24*X1+8*U1*Q24*X2+12*U1M1*T1P6*X1-12*U1M1*
     &  T1P6*X2-52*U1M1*T1P5*Q2*X1+52*U1M1*T1P5*Q2*X2+68*U1M1*T1P4*
     &  Q22*X1-68*U1M1*T1P4*Q22*X2-28*U1M1*T1P3*Q23*X1+28*U1M1*
     &  T1P3*Q23*X2+68*T1P5*X1-68*T1P5*X2-164*T1P4*Q2*X1+164*T1P4*Q2
     &  *X2+116*T1P3*Q22*X1-116*T1P3*Q22*X2-12*T1P2*Q23*X1+12*T1P2
     &  *Q23*X2-8*T1*Q24*X1+8*T1*Q24*X2)
      VPS(51) =
     &  +LOG10*LHPM2*(-32*U1P4*T1M1*X1+32*U1P4*T1M1*X2+80*
     &  U1P3*T1M1*Q2*X1-80*U1P3*T1M1*Q2*X2-124*U1P3*X1+124*U1P3*X2-
     &  104*U1P2*T1*X1+104*U1P2*T1*X2-44*U1P2*T1M1*Q22*X1+44*U1P2*
     &  T1M1*Q22*X2+172*U1P2*Q2*X1-172*U1P2*Q2*X2-28*U1*T1P2*X1+28*
     &  U1*T1P2*X2+116*U1*T1*Q2*X1-116*U1*T1*Q2*X2+12*U1*T1M1*Q23*X1
     &  -12*U1*T1M1*Q23*X2-112*U1*Q22*X1+112*U1*Q22*X2-4*U1M1*
     &  T1P2*Q22*X1+4*U1M1*T1P2*Q22*X2+4*U1M1*T1*Q23*X1-4*U1M1*T1
     &  *Q23*X2+16*T1P2*Q2*X1-16*T1P2*Q2*X2-64*T1*Q22*X1+64*T1*Q22
     &  *X2+32*Q23*X1-32*Q23*X2)
     &  +LOG10*LHPM4*(12*U1P6*T1M1*X1-12*U1P6*T1M1*X2-52*U1P5*
     &  T1M1*Q2*X1+52*U1P5*T1M1*Q2*X2+68*U1P5*X1-68*U1P5*X2+48*U1P4
     &  *T1*X1-48*U1P4*T1*X2+68*U1P4*T1M1*Q22*X1-68*U1P4*T1M1*Q22*
     &  X2-164*U1P4*Q2*X1+164*U1P4*Q2*X2+16*U1P3*T1P2*X1-16*U1P3*T1P2
     &  *X2-88*U1P3*T1*Q2*X1+88*U1P3*T1*Q2*X2-28*U1P3*T1M1*Q23*X1+
     &  28*U1P3*T1M1*Q23*X2+116*U1P3*Q22*X1-116*U1P3*Q22*X2-24*U1P2
     &  *T1P2*Q2*X1+24*U1P2*T1P2*Q2*X2+24*U1P2*T1*Q22*X1-24*U1P2*T1*
     &  Q22*X2-12*U1P2*Q23*X1+12*U1P2*Q23*X2+24*U1*T1*Q23*X1-24*
     &  U1*T1*Q23*X2-8*U1*Q24*X1+8*U1*Q24*X2+8*T1P2*Q23*X1-8*T1P2
     &  *Q23*X2-8*T1*Q24*X1+8*T1*Q24*X2)
      VPS(52) =
     &  +LOG10*(8*U1P3*T1M1*SPM1*X1-8*U1P3*T1M1*SPM1*X2-8*U1P2
     &  *T1M1*Q2*SPM1*X1+8*U1P2*T1M1*Q2*SPM1*X2+32*U1P2*T1M1*X1-32
     &  *U1P2*T1M1*X2-32*U1P2*Q2*SPM2*X1+32*U1P2*Q2*SPM2*X2+16*U1P2*
     &  SPM1*X1-16*U1P2*SPM1*X2-64*U1*T1*Q2*SPM2*X1+64*U1*T1*Q2*
     &  SPM2*X2+16*U1*T1*SPM1*X1-16*U1*T1*SPM1*X2-24*U1*T1M1*Q2*X1
     &  +24*U1*T1M1*Q2*X2-24*U1*Q2*SPM1*X1+24*U1*Q2*SPM1*X2+96*U1*
     &  X1-96*U1*X2+8*U1M1*T1P3*SPM1*X1-8*U1M1*T1P3*SPM1*X2-8*
     &  U1M1*T1P2*Q2*SPM1*X1+8*U1M1*T1P2*Q2*SPM1*X2+32*U1M1*T1P2*X1
     &  -32*U1M1*T1P2*X2-24*U1M1*T1*Q2*X1+24*U1M1*T1*Q2*X2-32*T1P2
     &  *Q2*SPM2*X1+32*T1P2*Q2*SPM2*X2+16*T1P2*SPM1*X1-16*T1P2*SPM1
     &  *X2-24*T1*Q2*SPM1*X1+24*T1*Q2*SPM1*X2+96*T1*X1-96*T1*X2-
     &  32*Q2*X1+32*Q2*X2)
     &  +LHM1*DLOGQ6T*(32*U1*T1-8*U1*Q2+16*U1M1*T1P3-8*U1M1*
     &  T1P2*Q2+48*T1P2-32*T1*Q2+8*Q22)
     &  +LHM1*DLOGQ7T*(32*U1*T1-8*U1*Q2+16*U1M1*T1P3-8*U1M1*
     &  T1P2*Q2+48*T1P2-32*T1*Q2+8*Q22)
     &  +LHM1*DLOGQ8T*(-32*U1*T1+8*U1*Q2-16*U1M1*T1P3+8*U1M1*
     &  T1P2*Q2-48*T1P2+32*T1*Q2-8*Q22)
      VPS(53) =
     &  +LHM1*DLOGQ9T*(-32*U1*T1+8*U1*Q2-16*U1M1*T1P3+8*U1M1*
     &  T1P2*Q2-48*T1P2+32*T1*Q2-8*Q22)
     &  +LHM1*DLOGQ10T*(-32*U1*T1+8*U1*Q2-16*U1M1*T1P3+8*U1M1
     &  *T1P2*Q2-48*T1P2+32*T1*Q2-8*Q22)
     &  +LHM1*DLOGQ11T*(-32*U1*T1+8*U1*Q2-16*U1M1*T1P3+8*U1M1
     &  *T1P2*Q2-48*T1P2+32*T1*Q2-8*Q22)
     &  +LHM1*DLOGQ12T*(32*U1*T1-8*U1*Q2+16*U1M1*T1P3-8*U1M1*
     &  T1P2*Q2+48*T1P2-32*T1*Q2+8*Q22)
     &  +LHM1*DLOGQ13T*(64*U1*T1-16*U1*Q2+32*U1M1*T1P3-16*U1M1*
     &  T1P2*Q2+96*T1P2-64*T1*Q2+16*Q22)
     &  +LHM2*(-12*U1P2*T1-4*U1P2*T1M1*Q22+16*U1P2*Q2-32*U1
     &  *T1P2+68*U1*T1*Q2+4*U1*T1M1*Q23-40*U1*Q22+4*U1M1*T1P5*
     &  TM1-4*U1M1*T1P4*TM1*Q2-8*U1M1*T1P4-12*U1M1*T1P3*TM1*Q22
     &  +20*U1M1*T1P3*Q2-4*U1M1*T1P2*TM1*Q23-8*U1M1*T1P2*Q22+12
     &  *U1M1*T1*Q23+20*T1P4*TM1+24*T1P3*TM1*Q2-44*T1P3+4*T1P2*
     &  TM1*Q22+40*T1P2*Q2-60*T1*Q22+16*Q23)
      VPS(54) =
     &  +LHM3*DLOGQ6T*(8*U1P2*T1P2-8*U1P2*T1*Q2+8*U1*T1P3+8*U1*
     &  T1P2*Q2-16*U1*T1*Q22-16*U1M1*T1P5+40*U1M1*T1P4*Q2-32*U1M1
     &  *T1P3*Q22+8*U1M1*T1P2*Q23-32*T1P4+72*T1P3*Q2-56*T1P2*Q22
     &  +16*T1*Q23)
     &  +LHM3*DLOGQ7T*(8*U1P2*T1P2-8*U1P2*T1*Q2+8*U1*T1P3+8*U1*
     &  T1P2*Q2-16*U1*T1*Q22-16*U1M1*T1P5+40*U1M1*T1P4*Q2-32*U1M1
     &  *T1P3*Q22+8*U1M1*T1P2*Q23-32*T1P4+72*T1P3*Q2-56*T1P2*Q22
     &  +16*T1*Q23)
     &  +LHM3*DLOGQ8T*(-8*U1P2*T1P2+8*U1P2*T1*Q2-8*U1*T1P3-8*U1
     &  *T1P2*Q2+16*U1*T1*Q22+16*U1M1*T1P5-40*U1M1*T1P4*Q2+32*
     &  U1M1*T1P3*Q22-8*U1M1*T1P2*Q23+32*T1P4-72*T1P3*Q2+56*T1P2*
     &  Q22-16*T1*Q23)
     &  +LHM3*DLOGQ9T*(-8*U1P2*T1P2+8*U1P2*T1*Q2-8*U1*T1P3-8*U1
     &  *T1P2*Q2+16*U1*T1*Q22+16*U1M1*T1P5-40*U1M1*T1P4*Q2+32*
     &  U1M1*T1P3*Q22-8*U1M1*T1P2*Q23+32*T1P4-72*T1P3*Q2+56*T1P2*
     &  Q22-16*T1*Q23)
      VPS(55) =
     &  +LHM3*DLOGQ10T*(-8*U1P2*T1P2+8*U1P2*T1*Q2-8*U1*T1P3-8*
     &  U1*T1P2*Q2+16*U1*T1*Q22+16*U1M1*T1P5-40*U1M1*T1P4*Q2+32*
     &  U1M1*T1P3*Q22-8*U1M1*T1P2*Q23+32*T1P4-72*T1P3*Q2+56*T1P2*
     &  Q22-16*T1*Q23)
     &  +LHM3*DLOGQ11T*(-8*U1P2*T1P2+8*U1P2*T1*Q2-8*U1*T1P3-8*
     &  U1*T1P2*Q2+16*U1*T1*Q22+16*U1M1*T1P5-40*U1M1*T1P4*Q2+32*
     &  U1M1*T1P3*Q22-8*U1M1*T1P2*Q23+32*T1P4-72*T1P3*Q2+56*T1P2*
     &  Q22-16*T1*Q23)
     &  +LHM3*DLOGQ12T*(8*U1P2*T1P2-8*U1P2*T1*Q2+8*U1*T1P3+8*U1*
     &  T1P2*Q2-16*U1*T1*Q22-16*U1M1*T1P5+40*U1M1*T1P4*Q2-32*U1M1
     &  *T1P3*Q22+8*U1M1*T1P2*Q23-32*T1P4+72*T1P3*Q2-56*T1P2*Q22
     &  +16*T1*Q23)
     &  +LHM3*DLOGQ13T*(16*U1P2*T1P2-16*U1P2*T1*Q2+16*U1*T1P3+16*
     &  U1*T1P2*Q2-32*U1*T1*Q22-32*U1M1*T1P5+80*U1M1*T1P4*Q2-64*
     &  U1M1*T1P3*Q22+16*U1M1*T1P2*Q23-64*T1P4+144*T1P3*Q2-112*
     &  T1P2*Q22+32*T1*Q23)
      VPS(56) =
     &  +LHM5*DLOGQ6T*(-8*U1P2*T1P4+24*U1P2*T1P3*Q2-24*U1P2*T1P2*
     &  Q22+8*U1P2*T1*Q23-32*U1*T1P5+104*U1*T1P4*Q2-120*U1*T1P3*
     &  Q22+56*U1*T1P2*Q23-8*U1*T1*Q24-8*T1P6+40*T1P5*Q2-72*T1P4
     &  *Q22+56*T1P3*Q23-16*T1P2*Q24)
     &  +LHM5*DLOGQ7T*(-8*U1P2*T1P4+24*U1P2*T1P3*Q2-24*U1P2*T1P2*
     &  Q22+8*U1P2*T1*Q23-32*U1*T1P5+104*U1*T1P4*Q2-120*U1*T1P3*
     &  Q22+56*U1*T1P2*Q23-8*U1*T1*Q24-8*T1P6+40*T1P5*Q2-72*T1P4
     &  *Q22+56*T1P3*Q23-16*T1P2*Q24)
     &  +LHM5*DLOGQ8T*(8*U1P2*T1P4-24*U1P2*T1P3*Q2+24*U1P2*T1P2*
     &  Q22-8*U1P2*T1*Q23+32*U1*T1P5-104*U1*T1P4*Q2+120*U1*T1P3*
     &  Q22-56*U1*T1P2*Q23+8*U1*T1*Q24+8*T1P6-40*T1P5*Q2+72*T1P4
     &  *Q22-56*T1P3*Q23+16*T1P2*Q24)
     &  +LHM5*DLOGQ9T*(8*U1P2*T1P4-24*U1P2*T1P3*Q2+24*U1P2*T1P2*
     &  Q22-8*U1P2*T1*Q23+32*U1*T1P5-104*U1*T1P4*Q2+120*U1*T1P3*
     &  Q22-56*U1*T1P2*Q23+8*U1*T1*Q24+8*T1P6-40*T1P5*Q2+72*T1P4
     &  *Q22-56*T1P3*Q23+16*T1P2*Q24)
      VPS(57) =
     &  +LHM5*DLOGQ10T*(8*U1P2*T1P4-24*U1P2*T1P3*Q2+24*U1P2*T1P2*
     &  Q22-8*U1P2*T1*Q23+32*U1*T1P5-104*U1*T1P4*Q2+120*U1*T1P3*
     &  Q22-56*U1*T1P2*Q23+8*U1*T1*Q24+8*T1P6-40*T1P5*Q2+72*T1P4
     &  *Q22-56*T1P3*Q23+16*T1P2*Q24)
     &  +LHM5*DLOGQ11T*(8*U1P2*T1P4-24*U1P2*T1P3*Q2+24*U1P2*T1P2*
     &  Q22-8*U1P2*T1*Q23+32*U1*T1P5-104*U1*T1P4*Q2+120*U1*T1P3*
     &  Q22-56*U1*T1P2*Q23+8*U1*T1*Q24+8*T1P6-40*T1P5*Q2+72*T1P4
     &  *Q22-56*T1P3*Q23+16*T1P2*Q24)
     &  +LHM5*DLOGQ12T*(-8*U1P2*T1P4+24*U1P2*T1P3*Q2-24*U1P2*T1P2
     &  *Q22+8*U1P2*T1*Q23-32*U1*T1P5+104*U1*T1P4*Q2-120*U1*T1P3*
     &  Q22+56*U1*T1P2*Q23-8*U1*T1*Q24-8*T1P6+40*T1P5*Q2-72*T1P4
     &  *Q22+56*T1P3*Q23-16*T1P2*Q24)
     &  +LHM5*DLOGQ13T*(-16*U1P2*T1P4+48*U1P2*T1P3*Q2-48*U1P2*
     &  T1P2*Q22+16*U1P2*T1*Q23-64*U1*T1P5+208*U1*T1P4*Q2-240*U1*
     &  T1P3*Q22+112*U1*T1P2*Q23-16*U1*T1*Q24-16*T1P6+80*T1P5*Q2
     &  -144*T1P4*Q22+112*T1P3*Q23-32*T1P2*Q24)
      VPS(58) =
     &  +LHPM1*DLOGQ6U*(16*U1P3*T1M1-8*U1P2*T1M1*Q2+48*U1P2+32*
     &  U1*T1-32*U1*Q2-8*T1*Q2+8*Q22)
     &  +LHPM1*DLOGQ7U*(16*U1P3*T1M1-8*U1P2*T1M1*Q2+48*U1P2+32*
     &  U1*T1-32*U1*Q2-8*T1*Q2+8*Q22)
     &  +LHPM1*DLOGQ8U*(-16*U1P3*T1M1+8*U1P2*T1M1*Q2-48*U1P2-
     &  32*U1*T1+32*U1*Q2+8*T1*Q2-8*Q22)
     &  +LHPM1*DLOGQ9U*(-16*U1P3*T1M1+8*U1P2*T1M1*Q2-48*U1P2-
     &  32*U1*T1+32*U1*Q2+8*T1*Q2-8*Q22)
     &  +LHPM1*DLOGQ10U*(-16*U1P3*T1M1+8*U1P2*T1M1*Q2-48*U1P2
     &  -32*U1*T1+32*U1*Q2+8*T1*Q2-8*Q22)
     &  +LHPM1*DLOGQ11U*(-16*U1P3*T1M1+8*U1P2*T1M1*Q2-48*U1P2
     &  -32*U1*T1+32*U1*Q2+8*T1*Q2-8*Q22)
     &  +LHPM1*DLOGQ12U*(16*U1P3*T1M1-8*U1P2*T1M1*Q2+48*U1P2+32
     &  *U1*T1-32*U1*Q2-8*T1*Q2+8*Q22)
     &  +LHPM1*DLOGQ13U*(32*U1P3*T1M1-16*U1P2*T1M1*Q2+96*U1P2+
     &  64*U1*T1-64*U1*Q2-16*T1*Q2+16*Q22)
      VPS(59) =
     &  +LHPM2*(4*U1P5*T1M1*UM1-4*U1P4*T1M1*UM1*Q2-8*U1P4*
     &  T1M1+20*U1P4*UM1-12*U1P3*T1M1*UM1*Q22+20*U1P3*T1M1*Q2+
     &  24*U1P3*UM1*Q2-44*U1P3-32*U1P2*T1-4*U1P2*T1M1*UM1*Q23-8*
     &  U1P2*T1M1*Q22+4*U1P2*UM1*Q22+40*U1P2*Q2-12*U1*T1P2+68*U1*
     &  T1*Q2+12*U1*T1M1*Q23-60*U1*Q22-4*U1M1*T1P2*Q22+4*U1M1*
     &  T1*Q23+16*T1P2*Q2-40*T1*Q22+16*Q23)
     &  +LHPM3*DLOGQ6U*(-16*U1P5*T1M1+40*U1P4*T1M1*Q2-32*U1P4
     &  +8*U1P3*T1-32*U1P3*T1M1*Q22+72*U1P3*Q2+8*U1P2*T1P2+8*U1P2
     &  *T1*Q2+8*U1P2*T1M1*Q23-56*U1P2*Q22-8*U1*T1P2*Q2-16*U1*T1*
     &  Q22+16*U1*Q23)
     &  +LHPM3*DLOGQ7U*(-16*U1P5*T1M1+40*U1P4*T1M1*Q2-32*U1P4
     &  +8*U1P3*T1-32*U1P3*T1M1*Q22+72*U1P3*Q2+8*U1P2*T1P2+8*U1P2
     &  *T1*Q2+8*U1P2*T1M1*Q23-56*U1P2*Q22-8*U1*T1P2*Q2-16*U1*T1*
     &  Q22+16*U1*Q23)
     &  +LHPM3*DLOGQ8U*(16*U1P5*T1M1-40*U1P4*T1M1*Q2+32*U1P4-8*
     &  U1P3*T1+32*U1P3*T1M1*Q22-72*U1P3*Q2-8*U1P2*T1P2-8*U1P2*T1*
     &  Q2-8*U1P2*T1M1*Q23+56*U1P2*Q22+8*U1*T1P2*Q2+16*U1*T1*Q22
     &  -16*U1*Q23)
      VPS(60) =
     &  +LHPM3*DLOGQ9U*(16*U1P5*T1M1-40*U1P4*T1M1*Q2+32*U1P4-8*
     &  U1P3*T1+32*U1P3*T1M1*Q22-72*U1P3*Q2-8*U1P2*T1P2-8*U1P2*T1*
     &  Q2-8*U1P2*T1M1*Q23+56*U1P2*Q22+8*U1*T1P2*Q2+16*U1*T1*Q22
     &  -16*U1*Q23)
     &  +LHPM3*DLOGQ10U*(16*U1P5*T1M1-40*U1P4*T1M1*Q2+32*U1P4-8
     &  *U1P3*T1+32*U1P3*T1M1*Q22-72*U1P3*Q2-8*U1P2*T1P2-8*U1P2*T1*
     &  Q2-8*U1P2*T1M1*Q23+56*U1P2*Q22+8*U1*T1P2*Q2+16*U1*T1*Q22
     &  -16*U1*Q23)
     &  +LHPM3*DLOGQ11U*(16*U1P5*T1M1-40*U1P4*T1M1*Q2+32*U1P4-8
     &  *U1P3*T1+32*U1P3*T1M1*Q22-72*U1P3*Q2-8*U1P2*T1P2-8*U1P2*T1*
     &  Q2-8*U1P2*T1M1*Q23+56*U1P2*Q22+8*U1*T1P2*Q2+16*U1*T1*Q22
     &  -16*U1*Q23)
     &  +LHPM3*DLOGQ12U*(-16*U1P5*T1M1+40*U1P4*T1M1*Q2-32*U1P4
     &  +8*U1P3*T1-32*U1P3*T1M1*Q22+72*U1P3*Q2+8*U1P2*T1P2+8*U1P2
     &  *T1*Q2+8*U1P2*T1M1*Q23-56*U1P2*Q22-8*U1*T1P2*Q2-16*U1*T1*
     &  Q22+16*U1*Q23)
      VPS(61) =
     &  +LHPM3*DLOGQ13U*(-32*U1P5*T1M1+80*U1P4*T1M1*Q2-64*U1P4
     &  +16*U1P3*T1-64*U1P3*T1M1*Q22+144*U1P3*Q2+16*U1P2*T1P2+16*
     &  U1P2*T1*Q2+16*U1P2*T1M1*Q23-112*U1P2*Q22-16*U1*T1P2*Q2-32*
     &  U1*T1*Q22+32*U1*Q23)
     &  +LHPM5*DLOGQ6U*(-8*U1P6-32*U1P5*T1+40*U1P5*Q2-8*U1P4*
     &  T1P2+104*U1P4*T1*Q2-72*U1P4*Q22+24*U1P3*T1P2*Q2-120*U1P3*T1*
     &  Q22+56*U1P3*Q23-24*U1P2*T1P2*Q22+56*U1P2*T1*Q23-16*U1P2*
     &  Q24+8*U1*T1P2*Q23-8*U1*T1*Q24)
     &  +LHPM5*DLOGQ7U*(-8*U1P6-32*U1P5*T1+40*U1P5*Q2-8*U1P4*
     &  T1P2+104*U1P4*T1*Q2-72*U1P4*Q22+24*U1P3*T1P2*Q2-120*U1P3*T1*
     &  Q22+56*U1P3*Q23-24*U1P2*T1P2*Q22+56*U1P2*T1*Q23-16*U1P2*
     &  Q24+8*U1*T1P2*Q23-8*U1*T1*Q24)
     &  +LHPM5*DLOGQ8U*(8*U1P6+32*U1P5*T1-40*U1P5*Q2+8*U1P4*T1P2
     &  -104*U1P4*T1*Q2+72*U1P4*Q22-24*U1P3*T1P2*Q2+120*U1P3*T1*Q22
     &  -56*U1P3*Q23+24*U1P2*T1P2*Q22-56*U1P2*T1*Q23+16*U1P2*Q24
     &  -8*U1*T1P2*Q23+8*U1*T1*Q24)
      VPS(62) =
     &  +LHPM5*DLOGQ9U*(8*U1P6+32*U1P5*T1-40*U1P5*Q2+8*U1P4*T1P2
     &  -104*U1P4*T1*Q2+72*U1P4*Q22-24*U1P3*T1P2*Q2+120*U1P3*T1*Q22
     &  -56*U1P3*Q23+24*U1P2*T1P2*Q22-56*U1P2*T1*Q23+16*U1P2*Q24
     &  -8*U1*T1P2*Q23+8*U1*T1*Q24)
     &  +LHPM5*DLOGQ10U*(8*U1P6+32*U1P5*T1-40*U1P5*Q2+8*U1P4*T1P2
     &  -104*U1P4*T1*Q2+72*U1P4*Q22-24*U1P3*T1P2*Q2+120*U1P3*T1*Q22
     &  -56*U1P3*Q23+24*U1P2*T1P2*Q22-56*U1P2*T1*Q23+16*U1P2*Q24
     &  -8*U1*T1P2*Q23+8*U1*T1*Q24)
     &  +LHPM5*DLOGQ11U*(8*U1P6+32*U1P5*T1-40*U1P5*Q2+8*U1P4*T1P2
     &  -104*U1P4*T1*Q2+72*U1P4*Q22-24*U1P3*T1P2*Q2+120*U1P3*T1*Q22
     &  -56*U1P3*Q23+24*U1P2*T1P2*Q22-56*U1P2*T1*Q23+16*U1P2*Q24
     &  -8*U1*T1P2*Q23+8*U1*T1*Q24)
     &  +LHPM5*DLOGQ12U*(-8*U1P6-32*U1P5*T1+40*U1P5*Q2-8*U1P4*
     &  T1P2+104*U1P4*T1*Q2-72*U1P4*Q22+24*U1P3*T1P2*Q2-120*U1P3*T1*
     &  Q22+56*U1P3*Q23-24*U1P2*T1P2*Q22+56*U1P2*T1*Q23-16*U1P2*
     &  Q24+8*U1*T1P2*Q23-8*U1*T1*Q24)
      VPS(63) =
     &  +LHPM5*DLOGQ13U*(-16*U1P6-64*U1P5*T1+80*U1P5*Q2-16*U1P4
     &  *T1P2+208*U1P4*T1*Q2-144*U1P4*Q22+48*U1P3*T1P2*Q2-240*U1P3*
     &  T1*Q22+112*U1P3*Q23-48*U1P2*T1P2*Q22+112*U1P2*T1*Q23-32*
     &  U1P2*Q24+16*U1*T1P2*Q23-16*U1*T1*Q24)
     &  +LOG7X2*(8*U1P3*SPM2+24*U1P2*T1*SPM2-8*U1P2*Q2*SPM2+
     &  16*U1P2*SPM1+24*U1*T1P2*SPM2-16*U1*T1*Q2*SPM2+32*U1*T1*SPM1
     &  -16*U1*Q2*SPM1+8*T1P3*SPM2-8*T1P2*Q2*SPM2+16*T1P2*SPM1-
     &  16*T1*Q2*SPM1)
     &  +(-12*U1P3*T1M1*UM1+4*U1P2*T1M1*UM1*Q2+8*U1P2*T1M1*
     &  Q2*S1M1+20*U1P2*T1M1+4*U1P2*UM1-16*U1P2*S1M1+32*U1P2*
     &  SPM1+16*U1*T1*UM1+16*U1*T1*TM1-32*U1*T1*S1M1+64*U1*T1*
     &  SPM1-8*U1*T1M1*Q22*S1M1-24*U1*T1M1*Q2-16*U1*UM1*Q2+40*
     &  U1*Q2*S1M1+76*U1-12*U1M1*T1P3*TM1+4*U1M1*T1P2*TM1*Q2+8*
     &  U1M1*T1P2*Q2*S1M1+20*U1M1*T1P2-8*U1M1*T1*Q22*S1M1-24*
     &  U1M1*T1*Q2+4*T1P2*TM1-16*T1P2*S1M1+32*T1P2*SPM1-16*T1*
     &  TM1*Q2+40*T1*Q2*S1M1+76*T1-16*Q22*S1M1-16*Q2-64*BQED*
     &  LOGDEL-32*BQED-64*MQED)
C SUM CONTRIBUTIONS AND MULTIPLY BY COMMON FACTOR:
      SPLUSV = 0.D0
      DO 10 I = 1,63
C        PRINT '(''0     VPS  = '',D20.7)',VPS(I)
   10 SPLUSV = SPLUSV + VPS(I)
C        DO 20 II= 1,62
C 20        WRITE(6,1000) II,VPS(II)
CBH     SVCFCF_L = SPLUSV
C DIVIDE BY -16 TO GET NORMALIZATION RIGHT:
CBH        VQEDL2 = SVCFCF_L/-16.0D0
C
 1000 FORMAT('VPS(',I2,') =',D20.10)
CBH SUBTRACT OFF OLD FINITE SOFT PIECES
      SPLUSV = SPLUSV - ( SQM * ( 128*M2*LOGDEL*LOG1
     &  + 64*M2*ZETA2 - 128*M2*LOG1*LOG5 - 128*M2*LOG1*LOG6
     &  + 64*M2*LOG1 + 64*M2*LOG1X2 - 128*M2*DLOG2 - 128*M2*DLOG1 )
     &  + XSQM1 * (  - 64*LOGDEL*LOG1 - 32*ZETA2 + 64*LOG1*LOG5
     &  + 64*LOG1*LOG6 - 32*LOG1 - 32*LOG1X2 + 64*DLOG2 + 64*DLOG1 )
     &  + 32 - 64*LOGDEL )*BQED
CBH ADD ON NEW FINITE SOFT PIECES
      SPLUSV = SPLUSV + ( SQM * ( 128*M2*LI2B
     &  + 256*M2*LNB*LOG1 - 64*M2*LOG1*LOG2 + 128*M2*LOG1*LOGSP
     &  + 32*M2*LOG1X2 ) + XSQM1 * (  - 64*LI2B - 128*LNB*LOG1
     &  + 32*LOG1*LOG2 - 64*LOG1*LOGSP - 32*LOG1 - 16*LOG1X2 )
     &  - 128*LNB + 32*LOG2 - 64*LOGSP )*BQED
CBH SWITCH Q2 BACK TO POSITIVE
      Q2 = QTMP
CBH GET THE NORMALIZATION CORRECT
      VQEDL2 = -4.D0*Q2*SPLUSV/(SP*SP)
      RETURN
      END
