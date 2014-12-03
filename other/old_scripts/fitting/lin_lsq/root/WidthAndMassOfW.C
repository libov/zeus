
/**********************************************************************************
 * Statistics WS at DESY                                                          *
 * mean of W mass and width including correaltion                                 *
 * correlation between Tevatron measurements are taken into account               *
 * data from 2005, see also hep-ex/0509008 page 197                               *
 * Author: Martin Goebel                                                          *
 **********************************************************************************/
#include "TMinuit.h"
#include "TMath.h"
#include "TMatrixD.h"
#include <stdlib>

using namespace std;

// measurements and corresponding errors 
//                          Tevatron-I  |   LEP-II
Double_t values[]     = { 80.452, 2.102, 80.412, 2.150 };
Double_t errors[]     = {  0.059, 0.106,  0.042, 0.091 };

// dimension of matrix, here equal to number of measurements
const Int_t dim = 4;

// inverse error matrix (4x4)
TMatrixD* invErorMatrix = new TMatrixD( dim, dim );

// minimal chi2
Double_t chi2Min = 1000;

void WidthAndMassOfW()
{
   // correlation matrix (4x4)
   TMatrixD* corr = new TMatrixD( dim, dim);

   // fill correlation matrix
   for ( Int_t i=0; i<dim; i++){
      for ( Int_t j=0; j<dim; j++){
         (*corr)(i,j) = 0;
         if(i == j) (*corr)(i,j) = 1; // diagonal elements = 1
      }
   }
   // correlation between Tevatron measurements (GammaW and MW) 
   (*corr)(0,1) = -0.174; 
   (*corr)(1,0) = -0.174;
   // correlation between LEP-II results are still under evaluation (set to 0) 
   (*corr)(2,3) = 0; 
   (*corr)(3,2) = 0;

   // compute covariance matrix
   TMatrixD *covMatrix = GetCovarianceMatrix( corr );
   // invert covariance matrix
   covMatrix->Invert();
   invErorMatrix = new TMatrixD( *covMatrix );

   // number of parameters
   const int npar = 2;
   
   // create minuit pointer
   TMinuit *minuit = new TMinuit( npar );
   
   // set FCN function
   minuit->SetFCN( &fcn );
 
   // -1=quiet, 0=normal, 1=verbose
   minuit->SetPrintLevel( 0 );

   // start values
   Double_t startVal[] = { 80, 2 };
   Double_t fitStep[]  = { 0.1, 0.1 };
   Double_t limitMin[] = { 70, 1.5 };
   Double_t limitMax[] = { 90, 2.5 };
   minuit->DefineParameter( 0, "MW", startVal[0], fitStep[0], limitMin[0], limitMax[0]);
   minuit->DefineParameter( 1, "GammaW", startVal[1], fitStep[1], limitMin[1], limitMax[1]);

   // minimize with MIGRAD
   Int_t ierr = 0;
   Double_t args[2];
   args[0] = 0; // maximum function calls (0=default)
   args[1] = 0; // tolerance at minimum (0=default)
   minuit->mnexcm( "MIGrad", args, 2, ierr );
   if ( ierr != 0 )
      cout << "Warning: Maybe fit didn't converge!" << endl;

   // fit results
   Double_t fitval[2], fiterr[2]; 
   minuit->GetParameter( 0, fitval[0], fiterr[0] );
   minuit->GetParameter( 1, fitval[1], fiterr[1] );

   cout << "\n\n*************************************************" << endl;
   cout << "  chi2Min = " << chi2Min  << endl;
   cout << "  n_dof   = " << dim-2  << endl;
   cout << "  p-value = " << TMath::Prob(chi2Min, dim-2)  << endl;
   cout << "  MW      = " << fitval[0] << " +- " << fiterr[0] << endl;
   cout << "  GammaW  = " << fitval[1] << " +- " << fiterr[1] << endl;
   cout << "*************************************************" << endl;

}

// Computation of chi2
void fcn(Int_t& npars, Double_t* grad, Double_t& f, Double_t fitPars[], Int_t iflag)
{
   // Evaluate the minimisation function ----------------------------------------------------
   //
   //  Input parameters:
   //    npars:   number of currently variable parameters
   //             CAUTION: this is not (necessarily) the dimension of the fitPars vector !
   //    fitPars: array of (constant and variable) parameters
   //    iflag:   indicates what is to be calculated
   //    grad:    array of gradients
   //
   //  Output parameters:
   //    f:       the calculated function value.
   //    grad:    the (optional) vector of first derivatives).
   // ---------------------------------------------------------------------------------------
   
   // first compute deviation
   Double_t delta[dim];
   for( Int_t ipar=0; ipar<dim; ipar++ ){
      Int_t iFitValue = 0;
      if ( ipar%2 == 0 ) iFitValue = 0; // MW is fit value
      else               iFitValue = 1; // GammaW is fit value
      // compute delta
      delta[ipar] = values[ipar] - fitPars[iFitValue];
   }
   
   // compute chi2
   Double_t chi2 = 0;
   for( Int_t ipar=0; ipar<dim; ipar++ ){
      for( Int_t jpar=0; jpar<dim; jpar++ ){
         chi2 + = delta[ipar] * (*invErorMatrix)(ipar,jpar) * delta[jpar];
      }
   }
  
   // save minimum chi2
   if (chi2 < chi2Min) chi2Min = chi2;

   f = chi2;
}          
  
// compute covariance matrix
TMatrixD *GetCovarianceMatrix( TMatrixD *corr )
{
   TMatrixD *cov = new TMatrixD( dim, dim );
   
   for( Int_t ipar=0; ipar<dim; ipar++ ){
      for( Int_t jpar=0; jpar<dim; jpar++ ){
         (*cov)(ipar,jpar) = (*corr)(ipar,jpar)*errors[ipar]*errors[jpar];
      }
   }

   return cov;
}
