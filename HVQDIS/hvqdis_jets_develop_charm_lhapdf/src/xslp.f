      FUNCTION XSLP(W)
C----------------------------------------------------------------
C     MOMENTUM DISTRIBUTION OF S.L. DECAY MUONS IN DECAYING
C     HADRON REST FRAME CONSTRUCTED FROM RAPGAP
C     This is the routine from Vincenzo
C----------------------------------------------------------------
      IMPLICIT DOUBLE PRECISION(A-H,O-Z)
      DIMENSION X(100), Y(100)

      DATA (X(I),I=1,100)
     +/0.154216E-03,  0.118966E-02,  0.326056E-02, 0.724813E-02,
     +0.130863E-01,  0.208191E-01,  0.308211E-01,  0.432465E-01,
     +0.574343E-01,  0.718645E-01,  0.877487E-01,  0.103831E+00,
     +0.120641E+00,  0.139807E+00,  0.158159E+00,  0.176379E+00,
     +0.195061E+00,  0.213831E+00,  0.232161E+00,  0.249829E+00,
     +0.267013E+00,  0.284484E+00,  0.301469E+00,  0.317199E+00,
     +0.334053E+00,  0.349342E+00,  0.363310E+00,  0.376947E+00,
     +0.390518E+00,  0.404463E+00,  0.417902E+00,  0.430614E+00,
     +0.442753E+00,  0.454363E+00,  0.466326E+00,  0.477914E+00,
     +0.489260E+00,  0.500738E+00,  0.512282E+00,  0.523099E+00,
     +0.534621E+00,  0.546144E+00,  0.557423E+00,  0.568857E+00,
     +0.580864E+00,  0.592562E+00,  0.604239E+00,  0.614946E+00,
     +0.627569E+00,  0.639752E+00,  0.650966E+00,  0.662246E+00,
     +0.674054E+00,  0.686303E+00,  0.697605E+00,  0.708885E+00,
     +0.720958E+00,  0.732546E+00,  0.744156E+00,  0.755172E+00,
     +0.766738E+00,  0.778370E+00,  0.789099E+00,  0.800401E+00,
     +0.812011E+00,  0.823269E+00,  0.834328E+00,  0.845873E+00,
     +0.856712E+00,  0.867110E+00,  0.877839E+00,  0.888304E+00,
     +0.898063E+00,  0.908242E+00,  0.917517E+00,  0.926682E+00,
     +0.935538E+00,  0.943777E+00,  0.952259E+00,  0.958362E+00,
     +0.964795E+00,  0.971140E+00,  0.976361E+00,  0.981142E+00,
     +0.984799E+00,  0.988346E+00,  0.991276E+00,  0.993633E+00,
     +0.995616E+00,  0.996762E+00,  0.997334E+00,  0.997863E+00,
     +0.998238E+00,  0.998590E+00,  0.998810E+00,  0.999075E+00,
     +0.999251E+00,  0.999427E+00,  0.999780E+00,  0.100000E+01/

      DATA(Y(I),I=1,100)
     +/0.125000E-01,  0.375000E-01,  0.625000E-01,  0.875000E-01,
     + 0.112500E+00,  0.137500E+00,  0.162500E+00,  0.187500E+00,
     + 0.212500E+00,  0.237500E+00,  0.262500E+00,  0.287500E+00,
     + 0.312500E+00,  0.337500E+00,  0.362500E+00,  0.387500E+00,
     + 0.412500E+00,  0.437500E+00,  0.462500E+00,  0.487500E+00,
     + 0.512500E+00,  0.537500E+00,  0.562500E+00,  0.587500E+00,
     + 0.612500E+00,  0.637500E+00,  0.662500E+00,  0.687500E+00,
     + 0.712500E+00,  0.737500E+00,  0.762500E+00,  0.787500E+00,
     + 0.812500E+00,  0.837500E+00,  0.862500E+00,  0.887500E+00,
     + 0.912500E+00,  0.937500E+00,  0.962500E+00,  0.987500E+00,
     + 0.101250E+01,  0.103750E+01,  0.106250E+01,  0.108750E+01,
     + 0.111250E+01,  0.113750E+01,  0.116250E+01,  0.118750E+01,
     + 0.121250E+01,  0.123750E+01,  0.126250E+01,  0.128750E+01,
     + 0.131250E+01,  0.133750E+01,  0.136250E+01,  0.138750E+01,
     + 0.141250E+01,  0.143750E+01,  0.146250E+01,  0.148750E+01,
     + 0.151250E+01,  0.153750E+01,  0.156250E+01,  0.158750E+01,
     + 0.161250E+01,  0.163750E+01,  0.166250E+01,  0.168750E+01,
     + 0.171250E+01,  0.173750E+01,  0.176250E+01,  0.178750E+01,
     + 0.181250E+01,  0.183750E+01,  0.186250E+01,  0.188750E+01,
     + 0.191250E+01,  0.193750E+01,  0.196250E+01,  0.198750E+01,
     + 0.201250E+01,  0.203750E+01,  0.206250E+01,  0.208750E+01,
     + 0.211250E+01,  0.213750E+01,  0.216250E+01,  0.218750E+01,
     + 0.221250E+01,  0.223750E+01,  0.226250E+01,  0.228750E+01,
     + 0.231250E+01,  0.233750E+01,  0.236250E+01,  0.238750E+01,
     + 0.241250E+01,  0.243750E+01,  0.246250E+01,  0.248750E+01/

      DO 10 I=1,100
         IF(W.GT.X(I))GOTO 10
         IF(I.EQ.1)THEN
            XM=Y(I)/X(I)
            XB=Y(I)-XM*X(I)
         ELSE
            XM=( Y(I)-Y(I-1) )/( X(I) - X(I-1) )
            XB=Y(I)-XM*X(I)
         ENDIF
         TMP=XM*W+XB
         GOTO 100
 10   CONTINUE
 100  XSLP=TMP

      RETURN
      END

C. MOMENTUM DISTRIBUTION OF S.L. DECAY ELECTRON IN DECAYING HADRON 
C. REST FRAME.  CONSTRUCTED FROM RAPGAP.
C This is the routine from Felix for charm
C. Charm:
      FUNCTION XSLPc(W)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION X(100),Y(100)
      DATA (Y(I),I=1,100)
     ./0.005D0,0.015D0,0.025D0,0.035D0,0.045D0,0.055D0,0.065D0,0.075D0,
     . 0.085D0,0.095D0,0.105D0,0.115D0,0.125D0,0.135D0,0.145D0,0.155D0,
     . 0.165D0,0.175D0,0.185D0,0.195D0,0.205D0,0.215D0,0.225D0,0.235D0,
     . 0.245D0,0.255D0,0.265D0,0.275D0,0.285D0,0.295D0,0.305D0,0.315D0,
     . 0.325D0,0.335D0,0.345D0,0.355D0,0.365D0,0.375D0,0.385D0,0.395D0,
     . 0.405D0,0.415D0,0.425D0,0.435D0,0.445D0,0.455D0,0.465D0,0.475D0,
     . 0.485D0,0.495D0,0.505D0,0.515D0,0.525D0,0.535D0,0.545D0,0.555D0,
     . 0.565D0,0.575D0,0.585D0,0.595D0,0.605D0,0.615D0,0.625D0,0.635D0,
     . 0.645D0,0.655D0,0.665D0,0.675D0,0.685D0,0.695D0,0.705D0,0.715D0,
     . 0.725D0,0.735D0,0.745D0,0.755D0,0.765D0,0.775D0,0.785D0,0.795D0,
     . 0.805D0,0.815D0,0.825D0,0.835D0,0.845D0,0.855D0,0.865D0,0.875D0,
     . 0.885D0,0.895D0,0.905D0,0.915D0,0.925D0,0.935D0,0.945D0,0.955D0,
     . 0.965D0,0.975D0,0.985D0,0.995/
      DATA (X(I),I=1,100)
     ./2.27095419D-6,6.40907359D-5,0.000283992431D0,0.000747542142D0,
     . 0.00153114012D0,0.00270397181D0,0.00432889369D0,0.00670635012D0,
     . 0.00915751168D0,0.0124587851D0,0.0168395622D0,0.0210398662D0,
     . 0.0263862532D0,0.0324726582D0,0.0400473697D0,0.0469448526D0,
     . 0.0553585288D0,0.0655330823D0,0.0745764878D0,0.0853817205D0,
     . 0.0981808314D0,0.109355546D0,0.122500483D0,0.137825328D0,
     . 0.151019202D0,0.166347618D0,0.182353112D0,0.199005223D0,
     . 0.218029686D0,0.234113968D0,0.252496847D0,0.271379278D0,
     . 0.290719306D0,0.310473354D0,0.332627308D0,0.353103092D0,
     . 0.371764512D0,0.392714704D0,0.413844929D0,0.435106779D0,
     . 0.456451837D0,0.47996997D0,0.499199122D0,0.520506361D0,
     . 0.541707224D0,0.562756334D0,0.583609485D0,0.606270509D0,
     . 0.624557968D0,0.644572227D0,0.664228665D0,0.683491264D0,
     . 0.702326029D0,0.72070109D0,0.738586793D0,0.755955775D0,
     . 0.774435074D0,0.790640441D0,0.804724478D0,0.81980088D0,
     . 0.834260044D0,0.848089339D0,0.861278649D0,0.873820354D0,
     . 0.885709312D0,0.896942826D0,0.907520601D0,0.917444702D0,
     . 0.926719489D0,0.936179743D0,0.944115048D0,0.950724761D0,
     . 0.957489635D0,0.963659147D0,0.969249984D0,0.974280607D0,
     . 0.978771173D0,0.98274346D0,0.986220794D0,0.989227988D0,
     . 0.991791295D0,0.994131301D0,0.995854174D0,0.997223568D0,
     . 0.998180435D0,0.998968635D0,0.999502371D0,0.999820871D0,
     . 0.999968345D0,1D0,1D0,1D0,1D0,1D0,1D0,1D0,1D0,1D0,1D0,1D0/
      DO 10 I=1,100
         IF(W.GT.X(I))GOTO 10
         IF(I.EQ.1)THEN
            XM=Y(I)/X(I)
            XB=Y(I)-XM*X(I)
         ELSE
            XM=( Y(I)-Y(I-1) )/( X(I) - X(I-1) )
            XB=Y(I)-XM*X(I)
         ENDIF
         TMP=XM*W+XB
         GOTO 100
 10   CONTINUE
 100  XSLPc=TMP
      RETURN
      END

C. MOMENTUM DISTRIBUTION OF S.L. DECAY ELECTRON IN DECAYING HADRON 
C. REST FRAME.  CONSTRUCTED FROM RAPGAP.
C This is the routine from felix direct only
C. beauty
      FUNCTION XSLPb(W)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION X(100),Y(100)
      DATA (Y(I),I=1,100)
     ,/0.0150, 0.0450, 0.0750, 0.1050, 0.1350, 0.1650, 0.1950, 0.2250, 
     , 0.2550, 0.2850, 0.3150, 0.3450, 0.3750, 0.4050, 0.4350, 0.4650, 
     , 0.4950, 0.5250, 0.5550, 0.5850, 0.6150, 0.6450, 0.6750, 0.7050, 
     , 0.7350, 0.7650, 0.7950, 0.8250, 0.8550, 0.8850, 0.9150, 0.9450, 
     , 0.9750, 1.0050, 1.0350, 1.0650, 1.0950, 1.1250, 1.1550, 1.1850, 
     , 1.2150, 1.2450, 1.2750, 1.3050, 1.3350, 1.3650, 1.3950, 1.4250, 
     , 1.4550, 1.4850, 1.5150, 1.5450, 1.5750, 1.6050, 1.6350, 1.6650, 
     , 1.6950, 1.7250, 1.7550, 1.7850, 1.8150, 1.8450, 1.8750, 1.9050, 
     , 1.9350, 1.9650, 1.9950, 2.0250, 2.0550, 2.0850, 2.1150, 2.1450, 
     , 2.1750, 2.2050, 2.2350, 2.2650, 2.2950, 2.3250, 2.3550, 2.3850, 
     , 2.4150, 2.4450, 2.4750, 2.5050, 2.5350, 2.5650, 2.5950, 2.6250, 
     , 2.6550, 2.6850, 2.7150, 2.7450, 2.7750, 2.8050, 2.8350, 2.8650, 
     , 2.8950, 2.9250, 2.9550, 2.9850/
      DATA (X(I),I=1,100)
     ,/  0.00003580,   0.00007160,   0.00021481,   0.00075183, 
     ,   0.00121724,   0.00225548,   0.00336531,   0.00451095, 
     ,   0.00576399,   0.00773306,   0.01038235,   0.01303164, 
     ,   0.01639695,   0.02004867,   0.02466702,   0.02942858, 
     ,   0.03347412,   0.03959613,   0.04496631,   0.05173273, 
     ,   0.05882137,   0.06666183,   0.07478870,   0.08463404, 
     ,   0.09415715,   0.10479011,   0.11606748,   0.12677205, 
     ,   0.14009009,   0.15373035,   0.16822983,   0.18373175, 
     ,   0.19916207,   0.21577382,   0.23091772,   0.24842452, 
     ,   0.26571649,   0.28540716,   0.30506203,   0.32611313, 
     ,   0.34655562,   0.36710551,   0.38969606,   0.41339645, 
     ,   0.43784866,   0.46051082,   0.48260015,   0.50708818, 
     ,   0.53125399,   0.55663705,   0.58108926,   0.60618591, 
     ,   0.63221341,   0.65938652,   0.68426836,   0.70907861, 
     ,   0.73406786,   0.75741023,   0.78082418,   0.80359375, 
     ,   0.82679296,   0.85020691,   0.87050617,   0.88998204, 
     ,   0.90777522,   0.92331296,   0.93727541,   0.94969845, 
     ,   0.96176344,   0.97168040,   0.98034430,   0.98768353, 
     ,   0.99251670,   0.99552399,   0.99760044,   0.99910408, 
     ,   0.99964112,   0.99992752,   0.99999911,   1.00000000, 
     ,   1.00000000,   1.00000000,   1.00000000,   1.00000000, 
     ,   1.00000000,   1.00000000,   1.00000000,   1.00000000, 
     ,   1.00000000,   1.00000000,   1.00000000,   1.00000000, 
     ,   1.00000000,   1.00000000,   1.00000000,   1.00000000, 
     ,   1.00000000,   1.00000000,   1.00000000,   1.00000000/
      DO 10 I=1,100
         IF(W.GT.X(I))GOTO 10
         IF(I.EQ.1)THEN
            XM=Y(I)/X(I)
            XB=Y(I)-XM*X(I)
         ELSE
            XM=( Y(I)-Y(I-1) )/( X(I) - X(I-1) )
            XB=Y(I)-XM*X(I)
         ENDIF
         TMP=XM*W+XB
         GOTO 100
 10   CONTINUE
 100  XSLPb=TMP
      RETURN
      END
C. MOMENTUM DISTRIBUTION OF S.L. DECAY ELECTRON IN DECAYING HADRON 
C. REST FRAME.  CONSTRUCTED FROM RAPGAP.
C This is the routine from felix direct+indirect
C. beauty
      FUNCTION XSLPbc(W)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION X(100),Y(100)
      DATA (Y(I),I=1,100)
     ,/0.0150, 0.0450, 0.0750, 0.1050, 0.1350, 0.1650, 0.1950, 0.2250, 
     , 0.2550, 0.2850, 0.3150, 0.3450, 0.3750, 0.4050, 0.4350, 0.4650, 
     , 0.4950, 0.5250, 0.5550, 0.5850, 0.6150, 0.6450, 0.6750, 0.7050, 
     , 0.7350, 0.7650, 0.7950, 0.8250, 0.8550, 0.8850, 0.9150, 0.9450, 
     , 0.9750, 1.0050, 1.0350, 1.0650, 1.0950, 1.1250, 1.1550, 1.1850, 
     , 1.2150, 1.2450, 1.2750, 1.3050, 1.3350, 1.3650, 1.3950, 1.4250, 
     , 1.4550, 1.4850, 1.5150, 1.5450, 1.5750, 1.6050, 1.6350, 1.6650, 
     , 1.6950, 1.7250, 1.7550, 1.7850, 1.8150, 1.8450, 1.8750, 1.9050, 
     , 1.9350, 1.9650, 1.9950, 2.0250, 2.0550, 2.0850, 2.1150, 2.1450, 
     , 2.1750, 2.2050, 2.2350, 2.2650, 2.2950, 2.3250, 2.3550, 2.3850, 
     , 2.4150, 2.4450, 2.4750, 2.5050, 2.5350, 2.5650, 2.5950, 2.6250, 
     , 2.6550, 2.6850, 2.7150, 2.7450, 2.7750, 2.8050, 2.8350, 2.8650, 
     , 2.8950, 2.9250, 2.9550, 2.9850/
      DATA (X(I),I=1,100)
     ,/  0.00020277,   0.00168976,   0.00537344,   0.01165934, 
     ,   0.02145995,   0.03455559,   0.05087867,   0.07000676, 
     ,   0.09085840,   0.11360257,   0.13695505,   0.16162555, 
     ,   0.18609327,   0.21203108,   0.23788440,   0.26171002, 
     ,   0.28421763,   0.30768839,   0.32943559,   0.35094625, 
     ,   0.37171340,   0.39173704,   0.41103411,   0.42967215, 
     ,   0.44656974,   0.46296042,   0.47899625,   0.49330851, 
     ,   0.50853324,   0.52260894,   0.53612703,   0.54971272, 
     ,   0.56321388,   0.57698542,   0.58984447,   0.60253459, 
     ,   0.61449808,   0.62793165,   0.64057106,   0.65388638, 
     ,   0.66603577,   0.67853999,   0.69143283,   0.70444399, 
     ,   0.71782690,   0.73016214,   0.74231154,   0.75539029, 
     ,   0.76792830,   0.78110844,   0.79383230,   0.80658996, 
     ,   0.81968558,   0.83325434,   0.84560651,   0.85797554, 
     ,   0.87036151,   0.88191944,   0.89334220,   0.90441012, 
     ,   0.91569769,   0.92701906,   0.93678588,   0.94631612, 
     ,   0.95484942,   0.96236885,   0.96906030,   0.97497445, 
     ,   0.98073655,   0.98555237,   0.98972607,   0.99325764, 
     ,   0.99565709,   0.99714410,   0.99815798,   0.99898595, 
     ,   0.99929011,   0.99944216,   0.99957734,   0.99959421, 
     ,   0.99959421,   0.99967867,   0.99972934,   0.99979693, 
     ,   0.99986452,   0.99988139,   0.99988139,   0.99988139, 
     ,   0.99991518,   0.99991518,   0.99991518,   0.99991518, 
     ,   0.99991518,   0.99991518,   0.99996585,   0.99998271, 
     ,   0.99998271,   1.00000000,   1.00000000,   1.00000000/       
      DO 10 I=1,100
         IF(W.GT.X(I))GOTO 10
         IF(I.EQ.1)THEN
            XM=Y(I)/X(I)
            XB=Y(I)-XM*X(I)
         ELSE
            XM=( Y(I)-Y(I-1) )/( X(I) - X(I-1) )
            XB=Y(I)-XM*X(I)
         ENDIF
         TMP=XM*W+XB
         GOTO 100
 10   CONTINUE
 100  XSLPbc=TMP
      RETURN
      END