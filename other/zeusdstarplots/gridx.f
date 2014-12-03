C     ------------------------------------------------------------------
      SUBROUTINE GRIDX(XMIN,XMAX,NX)
C     ------------------------------------------------------------------
C     MAKES X-GRID
C     ------------------------------------------------------------------
      IMPLICIT REAL (A-H,O-Z)

      VECTOR XXVEC

C     X GRID
      NXX         = NX 
      XXVEC(1)    = XMIN 
      XXVEC(NXX)  = XMAX 
      XMI      = XXVEC(1)
      XMA      = XXVEC(NXX)
      XMIL     = LOG10(XMI)
      XMAL     = LOG10(XMA)
      BWX      = (XMAL-XMIL)/(NXX-1)

C     EQUAL BINS IN LOG10(X) UP TO XX(NXX0)
      DO J=1,NXX
         XL    = XMIL+(J-1)*BWX
         XXVEC(J) = 10**(XL)
      ENDDO

C      print*,'input ',xmin,xmax,nx
C      print*,'xxvec ', xxvec
      END
C     ------------------------------------------------------------------

