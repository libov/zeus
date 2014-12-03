      SUBROUTINE FILLXS(XMIN,ITYPE,ICDU,IQX)

      INTEGER ITYPE,ICDU,IQX,NMAX
      REAL XMIN
      VECTOR XSME
      VECTOR XXME
      VECTOR NPTS 

      NMAX=NPTS(1)
      IF (IQX.EQ.1) THEN
         DO I=1,NMAX
            XSME(I) = REDX(XMIN,XXME(I),ITYPE,ICDU)
         ENDDO
      ELSEIF (IQX.EQ.2) THEN
         DO I=1,NMAX
         XSME(I) = REDX(XXME(I),XMIN,ITYPE,ICDU)
         ENDDO
      ELSE
         PRINT*,'WRONG IQX'
         STOP 
      ENDIF
C      print*,'iqx xmin ',iqx, xmin
C      print*,'xsme ', xsme
      END
