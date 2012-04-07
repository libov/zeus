*CMZ :  0.00/03 16/10/98  12.31.43  by  Tancredi Carli
*CMZ :  0.00/02 09/12/97  18.43.12  by  Tancredi Carli
*-- Author :
      SUBROUTINE HZLIHEP(IPRINT)
*#**********************************************************************
*#
*#    SUBROUTINE HZLIHEP(IPRINT)
*#
*# PURPOSE:  Print COMMON/HEPEVTP/ with IPRINT=1 for the whole common
*#           and otherwise exluding the arrays referring to the vertices
*#           of decays.
*#
*# INPUT:  COMMON /HEPEVTP/
*#
*# Author: Reimer Selle (rselle@rec06.desy.de)
*#
*# CHANGED BY:                              AT:
*# REASON:
*#
*#**********************************************************************
**
      IMPLICIT NONE
*
*KEEP,HEPEVTP.
*
* HEP event prime common
* (for explanation see manual)
      Integer NMXHEP
      PARAMETER (NMXHEP=2000)
      Integer NEVHEP,NHEP,ISTHEP,IDHEP
      Integer JMOHEP,JDAHEP
      Double Precision PHEP,VHEP
      COMMON/HEPEVTP/NEVHEP,NHEP,ISTHEP(NMXHEP),IDHEP(NMXHEP),
     & JMOHEP(2,NMXHEP),JDAHEP(2,NMXHEP),PHEP(5,NMXHEP),VHEP(4,NMXHEP)
*
*KEND.
*
      Integer i,j,ihep,iprint
      Real PHEPR(5,nmxhep),VHEPR(4,nmxhep)
      Double precision pges(4)
*                                    conversion to real for printing
*
      do i=1,4
       pges(i)=0.
      enddo
*
      do ihep=1,nhep
       do j=1,5
        PHEPR(j,ihep)=real(PHEP(j,ihep))
       enddo
       do i=1,4
        VHEPR(i,ihep)=real(VHEP(i,ihep))
       enddo
      enddo
*
      write(6,*) '** HZLIHEP nhep= ',nhep
      IF(IPRINT .EQ. 1) THEN
         WRITE(6,608)
         DO 100 I=1,NHEP
         WRITE(6,610) I,ISTHEP(I),IDHEP(I),
     &                (JMOHEP(J,I),J=1,2),(JDAHEP(J,I),J=1,2),
     &                (PHEPR(J,I),J=1,5),(VHEPR(J,I),J=1,4)
*
         if(ISTHEP(I).eq.1) then
         do J=1,4
          pges(J) = pges(J)+PHEP(j,i)
         end do
C         write(6,'(i3,a,4f9.3)') i,' Pges= ',(pges(j),j=1,4)
        endif
*
*
  100    CONTINUE
      ELSE
         WRITE(6,618)
         DO 200 I=1,NHEP
         WRITE(6,620) I,ISTHEP(I),IDHEP(I),
     &                (JMOHEP(J,I),J=1,2),(JDAHEP(J,I),J=1,2),
     &                (PHEPR(J,I),J=1,5)
*
        if(ISTHEP(I).eq.1) then
         do J=1,4
          pges(J) = pges(J)+PHEP(j,i)
         end do
C         write(6,'(i3,a,35x,4f9.3)') i,' Pges= ',(pges(j),j=1,4)
        endif
*
  200    CONTINUE
      ENDIF
*
      write(6,'(a,25x,4f8.3)') ' Pges= ',(pges(i),i=1,4)
*
  608 FORMAT(/'                    Event Listing (Common HEPEVTP)',
     &      //'   I IST    ID JMO1 JMO2 JDAf JDAl',
     &        '   p_x     p_y     p_z      E       m   '/34X,
     &        '  x [mm]  y [mm]  z [mm] t [mm/c] '/)
  610 FORMAT(2I4,I6,4I5,5F8.3,/34X,4F8.3)
  618 FORMAT(/'                    Event Listing (Common HEPEVTP)',
     &      //'   I IST    ID JMO1 JMO2 JDAf JDAl',
     &        '   p_x     p_y     p_z      E       m   '/)
  620 FORMAT(2I4,I6,4I5,5F8.3)
 
      RETURN
      END
