      REAL FUNCTION myana(RW)
*************************************************************************
*
*     O. Behnke 08/08                            
*     Create linear track fit y = p(1) + p(2)*x + gaussian error
*
*************************************************************************

      include 'csmunt.inc'


      REAL RW 

      real arr(1)
      integer iarr(1)
      equivalence (arr(1),iarr(1))


      LOGICAL FIRST
      DATA FIRST /.TRUE./
      integer osl

      vector x
      vector y
      vector ey
      vector nd
      vector p
*
*---  Enter user code here
*     
*      IF (FIRST ) THEN
         call ranlux(arr, 1)
*      ENDIF
C

      DO I=1,nd(1)
        call rannor(t,u)
        y(I) = p(1) + p(2)*x(I) + t*ey(I)
      ENDDO

C
C---  hahaha: generate some outliers
C
      y(1)  = y(1) +3.*ey(1)
      y(11) = y(11)-6.*ey(11)
      y(50) = y(50)+3.*ey(50)
      y(56) = y(56)+7.*ey(56)

 
      RETURN 
      END
