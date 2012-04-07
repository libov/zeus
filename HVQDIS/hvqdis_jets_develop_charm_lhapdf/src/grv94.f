* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                 *
*    G R V  -  P R O T O N  - P A R A M E T R I Z A T I O N S     *
*                                                                 *
*                         1994 UPDATE                             *
*                                                                 *
*                 FOR A DETAILED EXPLANATION SEE                  *
*                   M. GLUECK, E.REYA, A.VOGT :                   *
*                   DO-TH 94/24  =  DESY 94-206                   *
*                    (TO APPEAR IN Z. PHYS. C)                    *
*                                                                 *
*   THE PARAMETRIZATIONS ARE FITTED TO THE EVOLVED PARTONS FOR    *
*        Q**2 / GEV**2  BETWEEN   0.4   AND  1.E6                 *
*             X         BETWEEN  1.E-5  AND   1.                  *
*   LARGE-X REGIONS, WHERE THE DISTRIBUTION UNDER CONSIDERATION   *
*   IS NEGLIGIBLY SMALL, WERE EXCLUDED FROM THE FIT.              *
*                                                                 *
*   HEAVY QUARK THRESHOLDS  Q(H) = M(H)  IN THE BETA FUNCTION :   *
*                   M(C)  =  1.5,  M(B)  =  4.5                   *
*   CORRESPONDING LAMBDA(F) VALUES IN GEV FOR  Q**2 > M(H)**2 :   *
*      LO :   LAMBDA(3)  =  0.232,   LAMBDA(4)  =  0.200,         *
*             LAMBDA(5)  =  0.153,                                *
*      NLO :  LAMBDA(3)  =  0.248,   LAMBDA(4)  =  0.200,         *
*             LAMBDA(5)  =  0.131.                                *
*   THE NUMBER OF ACTIVE QUARK FLAVOURS IS  NF = 3  EVERYWHERE    *
*   EXCEPT IN THE BETA FUNCTION, I.E. THE HEAVY QUARKS C,B,...    *
*   ARE NOT PRESENT AS PARTONS IN THE Q2-EVOLUTION.               *
*                                                                 * 
*   NLO DISTRIBUTIONS ARE GIVEN IN MS-BAR FACTORIZATION SCHEME    *
*   (SUBROUTINE GRV94HO) AS WELL AS IN THE DIS SCHEME (GRV94DI),  *
*   THE LEADING ORDER PARAMETRIZATION IS PROVIDED BY "GRV94LO".   *
*                                                                 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*...INPUT PARAMETERS : 
*
*    X   = MOMENTUM FRACTION 
*    Q2  = SCALE Q**2 IN GEV**2
*
*...OUTPUT (ALWAYS X TIMES THE DISTRIBUTION) :
*
*    UV  = U(VAL) = U - U(BAR)
*    DV  = D(VAL) = D - D(BAR)
*    DEL = D(BAR) - U(BAR)
*    UDB = U(BAR) + D(BAR) 
*    SB  = S = S(BAR)
*    GL  = GLUON
*
*...LO PARAMETRIZATION :
*
       SUBROUTINE GRV94LO (X, Q2, UV, DV, DEL, UDB, SB, GL)
       IMPLICIT DOUBLE PRECISION (A - Z)
       MU2  = 0.23
       LAM2 = 0.2322 * 0.2322
       S  = DLOG (DLOG(Q2/LAM2) / DLOG(MU2/LAM2))
       DS = DSQRT (S)
       S2 = S * S
       S3 = S2 * S
*...UV :
       NU  =  2.284 + 0.802 * S + 0.055 * S2
       AKU =  0.590 - 0.024 * S
       BKU =  0.131 + 0.063 * S
       AU  = -0.449 - 0.138 * S - 0.076 * S2
       BU  =  0.213 + 2.669 * S - 0.728 * S2 
       CU  =  8.854 - 9.135 * S + 1.979 * S2
       DU  =  2.997 + 0.753 * S - 0.076 * S2 
       UV  = FV (X, NU, AKU, BKU, AU, BU, CU, DU)
*...DV :
       ND  =  0.371 + 0.083 * S + 0.039 * S2 
       AKD =  0.376 
       BKD =  0.486 + 0.062 * S
       AD  = -0.509 + 3.310 * S - 1.248 * S2
       BD  =  12.41 - 10.52 * S + 2.267 * S2 
       CD  =  6.373 - 6.208 * S + 1.418 * S2
       DD  =  3.691 + 0.799 * S - 0.071 * S2 
       DV  = FV (X, ND, AKD, BKD, AD, BD, CD, DD)
*...DEL :
       NE  =  0.082 + 0.014 * S + 0.008 * S2 
       AKE =  0.409 - 0.005 * S
       BKE =  0.799 + 0.071 * S
       AE  = -38.07 + 36.13 * S - 0.656 * S2
       BE  =  90.31 - 74.15 * S + 7.645 * S2 
       CE  =  0.0
       DE  =  7.486 + 1.217 * S - 0.159 * S2 
       DEL = FV (X, NE, AKE, BKE, AE, BE, CE, DE)
*...UDB :
       ALX =  1.451
       BEX =  0.271 
       AKX =  0.410 - 0.232 * S 
       BKX =  0.534 - 0.457 * S
       AGX =  0.890 - 0.140 * S
       BGX = -0.981
       CX  =  0.320 + 0.683 * S
       DX  =  4.752 + 1.164 * S + 0.286 * S2
       EX  =  4.119 + 1.713 * S
       ESX =  0.682 + 2.978 * S
       UDB = FW (X, S, ALX, BEX, AKX, BKX, AGX, BGX, CX, DX, EX, ESX)
*...SB :
       ALS =  0.914
       BES =  0.577
       AKS =  1.798 - 0.596 * S
       AS  = -5.548 + 3.669 * DS - 0.616 * S
       BS  =  18.92 - 16.73 * DS + 5.168 * S
       DST =  6.379 - 0.350 * S  + 0.142 * S2
       EST =  3.981 + 1.638 * S
       ESS =  6.402 
       SB  = FWS (X, S, ALS, BES, AKS, AS, BS, DST, EST, ESS)
*...GL :
       ALG =  0.524
       BEG =  1.088
       AKG =  1.742 - 0.930 * S
       BKG =        - 0.399 * S2
       AG  =  7.486 - 2.185 * S
       BG  =  16.69 - 22.74 * S  + 5.779 * S2
       CG  = -25.59 + 29.71 * S  - 7.296 * S2
       DG  =  2.792 + 2.215 * S  + 0.422 * S2 - 0.104 * S3
       EG  =  0.807 + 2.005 * S  
       ESG =  3.841 + 0.316 * S 
       GL  = FW (X, S, ALG, BEG, AKG, BKG, AG, BG, CG, DG, EG, ESG)
       RETURN
       END
*
*...NLO PARAMETRIZATION (MS(BAR)) :
*
       SUBROUTINE GRV94HO (X, Q2, UV, DV, DEL, UDB, SB, GL)
       IMPLICIT DOUBLE PRECISION (A - Z)
       MU2  = 0.34
       LAM2 = 0.248 * 0.248
       S  = DLOG (DLOG(Q2/LAM2) / DLOG(MU2/LAM2))
       DS = DSQRT (S)
       S2 = S * S
       S3 = S2 * S
*...UV :
       NU  =  1.304 + 0.863 * S 
       AKU =  0.558 - 0.020 * S
       BKU =          0.183 * S
       AU  = -0.113 + 0.283 * S - 0.321 * S2
       BU  =  6.843 - 5.089 * S + 2.647 * S2 - 0.527 * S3
       CU  =  7.771 - 10.09 * S + 2.630 * S2
       DU  =  3.315 + 1.145 * S - 0.583 * S2 + 0.154 * S3
       UV  = FV (X, NU, AKU, BKU, AU, BU, CU, DU)
*...DV :
       ND  =  0.102 - 0.017 * S + 0.005 * S2 
       AKD =  0.270 - 0.019 * S
       BKD =  0.260
       AD  =  2.393 + 6.228 * S - 0.881 * S2
       BD  =  46.06 + 4.673 * S - 14.98 * S2 + 1.331 * S3
       CD  =  17.83 - 53.47 * S + 21.24 * S2
       DD  =  4.081 + 0.976 * S - 0.485 * S2 + 0.152 * S3
       DV  = FV (X, ND, AKD, BKD, AD, BD, CD, DD)
*...DEL :
       NE  =  0.070 + 0.042 * S - 0.011 * S2 + 0.004 * S3 
       AKE =  0.409 - 0.007 * S
       BKE =  0.782 + 0.082 * S
       AE  = -29.65 + 26.49 * S + 5.429 * S2
       BE  =  90.20 - 74.97 * S + 4.526 * S2 
       CE  =  0.0
       DE  =  8.122 + 2.120 * S - 1.088 * S2 + 0.231 * S3
       DEL = FV (X, NE, AKE, BKE, AE, BE, CE, DE)
*...UDB :
       ALX =  0.877
       BEX =  0.561
       AKX =  0.275 
       BKX =  0.0
       AGX =  0.997
       BGX =  3.210 - 1.866 * S
       CX  =  7.300
       DX  =  9.010 + 0.896 * DS + 0.222 * S2
       EX  =  3.077 + 1.446 * S
       ESX =  3.173 - 2.445 * DS + 2.207 * S
       UDB = FW (X, S, ALX, BEX, AKX, BKX, AGX, BGX, CX, DX, EX, ESX)
*...SB :
       ALS =  0.756
       BES =  0.216
       AKS =  1.690 + 0.650 * DS - 0.922 * S
       AS  = -4.329 + 1.131 * S
       BS  =  9.568 - 1.744 * S
       DST =  9.377 + 1.088 * DS - 1.320 * S + 0.130 * S2
       EST =  3.031 + 1.639 * S
       ESS =  5.837 + 0.815 * S
       SB  = FWS (X, S, ALS, BES, AKS, AS, BS, DST, EST, ESS)
*...GL :
       ALG =  1.014
       BEG =  1.738
       AKG =  1.724 + 0.157 * S
       BKG =  0.800 + 1.016 * S
       AG  =  7.517 - 2.547 * S
       BG  =  34.09 - 52.21 * DS + 17.47 * S
       CG  =  4.039 + 1.491 * S
       DG  =  3.404 + 0.830 * S
       EG  = -1.112 + 3.438 * S  - 0.302 * S2
       ESG =  3.256 - 0.436 * S 
       GL  = FW (X, S, ALG, BEG, AKG, BKG, AG, BG, CG, DG, EG, ESG)
       RETURN
       END
*
*...NLO PARAMETRIZATION (DIS) :
*
       SUBROUTINE GRV94DI (X, Q2, UV, DV, DEL, UDB, SB, GL)
       IMPLICIT DOUBLE PRECISION (A - Z)
       MU2  = 0.34
       LAM2 = 0.248 * 0.248
       S  = DLOG (DLOG(Q2/LAM2) / DLOG(MU2/LAM2))
       DS = DSQRT (S)
       S2 = S * S
       S3 = S2 * S
*...UV :
       NU  =  2.484 + 0.116 * S + 0.093 * S2 
       AKU =  0.563 - 0.025 * S
       BKU =  0.054 + 0.154 * S
       AU  = -0.326 - 0.058 * S - 0.135 * S2
       BU  = -3.322 + 8.259 * S - 3.119 * S2 + 0.291 * S3
       CU  =  11.52 - 12.99 * S + 3.161 * S2
       DU  =  2.808 + 1.400 * S - 0.557 * S2 + 0.119 * S3
       UV  = FV (X, NU, AKU, BKU, AU, BU, CU, DU)
*...DV :
       ND  =  0.156 - 0.017 * S 
       AKD =  0.299 - 0.022 * S
       BKD =  0.259 - 0.015 * S
       AD  =  3.445 + 1.278 * S + 0.326 * S2
       BD  = -6.934 + 37.45 * S - 18.95 * S2 + 1.463 * S3
       CD  =  55.45 - 69.92 * S + 20.78 * S2
       DD  =  3.577 + 1.441 * S - 0.683 * S2 + 0.179 * S3
       DV  = FV (X, ND, AKD, BKD, AD, BD, CD, DD)
*...DEL :
       NE  =  0.099 + 0.019 * S + 0.002 * S2  
       AKE =  0.419 - 0.013 * S
       BKE =  1.064 - 0.038 * S
       AE  = -44.00 + 98.70 * S - 14.79 * S2 
       BE  =  28.59 - 40.94 * S - 13.66 * S2 + 2.523 * S3
       CE  =  84.57 - 108.8 * S + 31.52 * S2 
       DE  =  7.469 + 2.480 * S - 0.866 * S2 
       DEL = FV (X, NE, AKE, BKE, AE, BE, CE, DE)
*...UDB :
       ALX =  1.215
       BEX =  0.466
       AKX =  0.326 + 0.150 * S 
       BKX =  0.956 + 0.405 * S
       AGX =  0.272
       BGX =  3.794 - 2.359 * DS
       CX  =  2.014
       DX  =  7.941 + 0.534 * DS - 0.940 * S + 0.410 * S2
       EX  =  3.049 + 1.597 * S
       ESX =  4.396 - 4.594 * DS + 3.268 * S
       UDB = FW (X, S, ALX, BEX, AKX, BKX, AGX, BGX, CX, DX, EX, ESX)
*...SB :
       ALS =  0.175
       BES =  0.344
       AKS =  1.415 - 0.641 * DS 
       AS  =  0.580 - 9.763 * DS + 6.795 * S  - 0.558 * S2
       BS  =  5.617 + 5.709 * DS - 3.972 * S
       DST =  13.78 - 9.581 * S  + 5.370 * S2 - 0.996 * S3
       EST =  4.546 + 0.372 * S2
       ESS =  5.053 - 1.070 * S  + 0.805 * S2
       SB  = FWS (X, S, ALS, BES, AKS, AS, BS, DST, EST, ESS)
*...GL :
       ALG =  1.258
       BEG =  1.846
       AKG =  2.423 
       BKG =  2.427 + 1.311 * S  - 0.153 * S2
       AG  =  25.09 - 7.935 * S
       BG  = -14.84 - 124.3 * DS + 72.18 * S
       CG  =  590.3 - 173.8 * S
       DG  =  5.196 + 1.857 * S
       EG  = -1.648 + 3.988 * S  - 0.432 * S2
       ESG =  3.232 - 0.542 * S 
       GL  = FW (X, S, ALG, BEG, AKG, BKG, AG, BG, CG, DG, EG, ESG)
       RETURN
       END
*
*...FUNCTIONAL FORMS OF THE PARAMETRIZATIONS :
*
       FUNCTION FV (X, N, AK, BK, A, B, C, D)
       IMPLICIT DOUBLE PRECISION (A - Z)
       DX = DSQRT (X)
       FV = N * X**AK * (1.+ A*X**BK + X * (B + C*DX)) * (1.- X)**D
       RETURN
       END
*
       FUNCTION FW (X, S, AL, BE, AK, BK, A, B, C, D, E, ES)
       IMPLICIT DOUBLE PRECISION (A - Z)
       LX = DLOG (1./X)
       FW = (X**AK * (A + X * (B + X*C)) * LX**BK + S**AL
     1      * DEXP (-E + DSQRT (ES * S**BE * LX))) * (1.- X)**D
       RETURN
       END
*
       FUNCTION FWS (X, S, AL, BE, AK, AG, B, D, E, ES)
       IMPLICIT DOUBLE PRECISION (A - Z)
       DX = DSQRT (X)
       LX = DLOG (1./X)
       FWS = S**AL / LX**AK * (1.+ AG*DX + B*X) * (1.- X)**D
     1       * DEXP (-E + DSQRT (ES * S**BE * LX))
       RETURN
       END
