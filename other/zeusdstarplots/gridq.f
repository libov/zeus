C     ------------------------------------------------------------------
      SUBROUTINE GRIDQ(QMIN,QMAX,NQ)
C     ------------------------------------------------------------------
C     MAKES Q2-GRID
C     ------------------------------------------------------------------
      IMPLICIT REAL (A-H,O-Z)

      VECTOR QQVEC



C      print*,'eeee ', qmin,qmax
C     Q2 GRID
      NQQ         = NQ 
      QQVEC(1)    = QMIN 
      QQVEC(NQQ)  = QMAX 
      QMI      = QQVEC(1)
      QMA      = QQVEC(NQQ)
      QMIL     = LOG10(QMI)
      QMAL     = LOG10(QMA)
      BWQ      = (QMAL-QMIL)/(NQQ-1)

C     EQUAL BINS IN LOG10(Q2)
      DO J=1,NQQ
         QL    = QMIL+(J-1)*BWQ
         QQVEC(J) = 10**(QL)
      ENDDO


C      print*,'Q2 grid info'
C      print*, qmin,qmax,nq 
C      print*, qqvec
      END
C     ------------------------------------------------------------------

