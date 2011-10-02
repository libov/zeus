#ifndef breitboost_h
#define breitboost_h

#include "Dijets.h"


// *************************************************************
// *************************************************************
// Never ever touch code beyond this line!!!!!!!!!!!!!!!!!!!!
// *************************************************************
// *************************************************************

void Dijets::BreitBoost(TObjArray &InputCandList, TObjArray &OutputCandList, Double_t PzInLepton, Double_t PzInHadron,TLorentzVector POutLepton,Int_t Scheme)
{
// Boost input particle into Breit-frame
// PInLepton is momentum of incoming lepton in +z direction 
// POutLepton is momentum of outgoning lepton  
// PInHadron is momentum of incoming hadron in +z direction 
// Scheme = 1 => boost to Breit-frame  
//        = 2 => boost from Breit-frame
// Loop. vars
Int_t k4Vec; 
 
// Number of entries
Int_t NumInputEntries;

// Breit-vars
Double_t ArbFactor, PRelLepton,CenterOfMass[4];
Double_t ZHadrons[4], XZ[4];

// boost to and from Breit-frame implemented
if (Scheme != 1 && Scheme != 2)
     return;

     // Get number of particles stored in the list
     if (InputCandList.GetEntries()>0)
     NumInputEntries = InputCandList.GetEntries();  
     else {
printf("Inputlist is empty: No boost possible\n");
return;
}
/*   if(m_Debug > 1)  */
/*     cout << "In Breitboost: NumInputEntries = "  */
/* 	 << NumInputEntries << endl; */
 
// Init
TLorentzVector *Boosted4Vector = new TLorentzVector(0,0,0);
for (k4Vec = 0;k4Vec < 4;k4Vec++)
{
  CenterOfMass[k4Vec] = 0;
  ZHadrons[k4Vec] = 0;
  XZ[k4Vec] = 0;
}         
      
// Find 4-momentum of Breit frame (times an arbitrary factor)
// Breit-frame 4-vector given by "CenterOfMass"

/*  if(m_Debug > 1)  */
/*     cout << PzInHadron << ' ' << PzInLepton << ' ' */
/* 	 << POutLepton.X() << ' ' */
/* 	 << POutLepton.Y() << ' ' */
/* 	 << POutLepton.Z() << ' ' */
/* 	 << POutLepton.E() << endl; */

// Calculate arbitrary factor 
 ArbFactor = fabs(PzInHadron)*(fabs(PzInLepton)-POutLepton.E())-PzInHadron*(PzInLepton-POutLepton.Z());
 /*  if(m_Debug > 1)  */
 /*     cout << "In Breitboost: ArbFactor = "  */
 /* 	 << ArbFactor << endl; */

 // Relative momentum squared
 PRelLepton = pow((fabs(PzInLepton)-POutLepton.E()),2)-pow((PzInLepton-POutLepton.Z()),2)-pow(POutLepton.Y(),2)-pow(POutLepton.X(),2);
 /*  if(m_Debug > 1)  */
 /*     cout << "In Breitboost: PRelLepton = "  */
 /* 	 << PRelLepton << endl; */

 // CM-calculation
 CenterOfMass[0] = ArbFactor * ( -POutLepton.X()); 
 CenterOfMass[1] = ArbFactor * ( -POutLepton.Y());
 CenterOfMass[2] = ArbFactor * (PzInLepton - POutLepton.Z())-PRelLepton*PzInHadron;
 CenterOfMass[3] = ArbFactor * (fabs(PzInLepton)-POutLepton.E())-PRelLepton*fabs(PzInHadron);
 /*  if(m_Debug > 1)  */
 /*     cout << "In Breitboost: CenterOfMass = "  */
 /* 	 << CenterOfMass[0] << ' '  */
 /* 	 << CenterOfMass[1] << ' '  */
 /* 	 << CenterOfMass[2] << ' '  */
 /* 	 << CenterOfMass[3] << ' '  */
 /* 	 << endl; */

 // Find rotation to put incoming hadron back on z-axis      
 ZHadrons[0] = 0.;
 ZHadrons[1] = 0.;
 ZHadrons[2] = PzInHadron;
 ZHadrons[3] = fabs(PzInHadron);
 /*   if(m_Debug > 1)  */
 /*     cout << "In Breitboost: ZHadrons = "  */
 /* 	 << ZHadrons[0] << ' '  */
 /* 	 << ZHadrons[1] << ' '  */
 /* 	 << ZHadrons[2] << ' '  */
 /* 	 << ZHadrons[3] << ' '  */
 /* 	 << endl; */

 // Init XZ
 XZ[0] = 0;
 XZ[1] = 0;
 XZ[2] = 0;
 XZ[3] = 0;

 // introduce a 4-array to get the POutLept into the Boost method
 Double_t helpPOut[4];
 // fix here - this is 2 or 3 in ktbrei - do the rotation to xz
 helpPOut[0] = POutLepton.Px();
 helpPOut[1] = POutLepton.Py();
 helpPOut[2] = POutLepton.Pz();
 helpPOut[3] = POutLepton.E();
 // fix here - this is the 0 or 1 option in ktbrei - no rotation in xz
 helpPOut[0] = 0.;
 helpPOut[1] = 0.;
 helpPOut[2] = 0.;
 helpPOut[3] = 0.;

 // Do the boost
 if(Scheme == 1)
   Dijets::Boost(CenterOfMass,PzInHadron,ZHadrons,
		 helpPOut,NumInputEntries,InputCandList,OutputCandList,Scheme);
 else if(Scheme == 2)
   Dijets::Boost(CenterOfMass,PzInHadron,ZHadrons,
		 helpPOut,NumInputEntries,InputCandList,OutputCandList,Scheme);

 // Delete old objects
 delete Boosted4Vector;


}
void Dijets::Boost(Double_t CM[4],Double_t Sign,Double_t ZHad[4],
		   Double_t XZMomentum[4],Int_t NumPart,TObjArray &InputCandList, 
		   TObjArray &OutputCandList,Int_t Scheme)
{
  // Boost method
  // Corresponds to old DKTFRAM subroutine 

  // Rotation matrix
  Double_t RMatrix[4][4],HelpMatrix[4][4];
  Double_t OldVector[4], NewVector[4];

  // Declare 4-vector for input and output of boost
  Double_t Cand4Vec[4], FinalCand4Vec[4];
 
  // Loop. vars
  Int_t iCol, jLin, iParticle;

  // Init matrix RMatrix with id.
  for (iCol = 0;iCol<4;iCol++)
    for (jLin = 0;jLin < 4;jLin++)
      {
	if (iCol != jLin)
          RMatrix[iCol][jLin] = 0;
        else RMatrix[iCol][jLin] = 1;
      }

  // Do a Lorentz boost to/from cm frame of XXXX
  Dijets::LorentzBoost(RMatrix,CM,0);

  //for (iCol = 0;iCol<4;iCol++)
  //for (jLin = 0;jLin < 4;jLin++)
  // {
  //cout << "rmatrix2 = " << iCol << ' ' << jLin << ' ' << RMatrix[iCol][jLin] << endl;
  // }

  // Find rotation to put boosted Z on the (sign) z axis
  if (Sign!=0.)
    {
      for (jLin = 0;jLin<4;jLin++)
	{
	  OldVector[jLin] = 0.;
	  for (iCol = 0;iCol < 4;iCol++)
	    OldVector[jLin] += RMatrix[jLin][iCol]*ZHad[iCol]; 
	}

      //cout << "old1 = " 
      //  << OldVector[0] << ' ' 
      //  << OldVector[1] << ' ' 
      //  << OldVector[2] << ' ' 
      //  << OldVector[3] << ' ' 
      //  << endl;

      // Check if not 0 and fill in new vector
      if (OldVector[0]!=0. || OldVector[1]!=0. || OldVector[2]!=0.)
	{
	  NewVector[0] = 0.;
	  NewVector[1] = 0.;
	  NewVector[2] = Sign;
	  NewVector[3] = fabs(Sign);
	  //cout << "new1 = " 
	  //   << NewVector[0] << ' ' 
	  //   << NewVector[1] << ' ' 
	  //   << NewVector[2] << ' ' 
	  //   << NewVector[3] << endl;
	  Dijets::RRot(RMatrix,OldVector,NewVector);

	  // Find rotation to put boosted Z and rotated XZMomentum into XZ-plane
	  // fix here
	  for (jLin = 0;jLin<4;jLin++)
	    {
	      OldVector[jLin] = 0.;
	      for (iCol = 0;iCol < 4;iCol++)
		OldVector[jLin] += RMatrix[jLin][iCol]*XZMomentum[iCol]; 
	    }
       
	  /*
	    for (jLin = 0;jLin<4;jLin++)
	    {
	    cout << " rmat = " 
	    << RMatrix[jLin][0] << ' '
	    << RMatrix[jLin][1] << ' '
	    << RMatrix[jLin][2] << ' '
	    << RMatrix[jLin][3] << endl;
	    }
	    cout << "xzmomentum = " 
	    <<  XZMomentum[0] << ' '
	    <<  XZMomentum[1] << ' '
	    <<  XZMomentum[2] << ' '
	    <<  XZMomentum[3] << endl;
	    cout << "old2 = " 
	    << OldVector[0] << ' ' 
	    << OldVector[1] << ' ' 
	    << OldVector[2] << ' ' 
	    << OldVector[3] << ' ' 
	    << endl;
	  */

	  // check if not negative
	  if (OldVector[0]!=0. || OldVector[1]!=0.)
	    {
	      NewVector[0] = 1.;
	      NewVector[1] = 0.;
	      NewVector[2] = 0.;
	      NewVector[3] = 1.;
	      OldVector[2] = 0.;
	      /*cout << "new2 = " 
		<< NewVector[0] << ' ' 
		<< NewVector[1] << ' ' 
		<< NewVector[2] << ' ' 
		<< NewVector[3] << ' ' 
		<< OldVector[0] << ' ' 
		<< OldVector[1] << ' ' 
		<< OldVector[2] << ' ' 
		<< OldVector[3] << ' ' 
		<< endl; */
	  
	      //---NOTE THAT A POTENTIALLY AWKWARD SPECIAL CASE IS AVERTED, BECAUSE IF
	      //   OLD AND NEW ARE EXACTLY BACK-TO-BACK, THE ROTATION AXIS IS UNDEFINED
	      //   BUT IN THAT CASE DKTRROT WILL USE THE Z AXIS, AS REQUIRED
	      Dijets::RRot(RMatrix, OldVector, NewVector);
      
	    }
	} 
    }

  // Invert the transformation if necessary
  if (Scheme==2)
    {
      Dijets::MatrixInv(RMatrix,HelpMatrix);
      for (iCol = 0;iCol<4;iCol++)
	for (jLin = 0;jLin < 4;jLin++)
	  RMatrix[iCol][jLin] = HelpMatrix[iCol][jLin];
    }
  
  // Clear output list
  OutputCandList.Clear();

  // Apply the result for all vectors
  for (iParticle=0;iParticle<NumPart;iParticle++)
    {
      // get actual 4-vector candidate
      // For Energy --> mass assumption = 0 => massless
      TLorentzVector Candidate;
      if(InputCandList.At(iParticle)->InheritsFrom(TLorentzVector::Class()))
	{
	  Candidate = *((TLorentzVector*)InputCandList.At(iParticle));
	}
      else
	{
	  cout << "ERROR in Boost: InputCand of unknown type !" << endl; 
	}

      Cand4Vec[0] = Candidate.X();
      Cand4Vec[1] = Candidate.Y();
      Cand4Vec[2] = Candidate.Z();
      Cand4Vec[3] = Candidate.T();
      /*   if(m_Debug > 1) */
      /* 	cout << "Cand = "  */
      /* 	     << Cand4Vec[0] << ' ' << Cand4Vec[1] << ' ' */
      /* 	     << Cand4Vec[2] << ' ' << Cand4Vec[3] << endl; */

      // Boost Cand4Vec --> FinalCand4Vec
      for (jLin = 0;jLin < 4;jLin++)
	{
	  FinalCand4Vec[jLin] = 0.;
	  for (iCol = 0;iCol<4;iCol++)
            FinalCand4Vec[jLin] += RMatrix[jLin][iCol]*Cand4Vec[iCol]; 
	}

      //cout << "Final= " 
      //   << FinalCand4Vec[0] << ' '
      //   << FinalCand4Vec[1] << ' '
      //   << FinalCand4Vec[2] << ' '
      //   << FinalCand4Vec[3] 
      //   << endl;

      // Create particle with boosted 4-vector 
      TLorentzVector *Cand5 = new TLorentzVector(FinalCand4Vec[0],
						 FinalCand4Vec[1],
						 FinalCand4Vec[2],
						 FinalCand4Vec[3]);
      OutputCandList.Add(Cand5);

      // Fill in outputlist
      /* if(m_Debug > 1)  */
      /* 	{ */
      /* 	  cout << "-------- Output particle list (Boost) --------" << endl; */
      /* 	  cout << ((TLorentzVector*)Cand5)->Px() << ' ' */
      /* 	       << ((TLorentzVector*)Cand5)->Py() << ' ' */
      /* 	       << ((TLorentzVector*)Cand5)->Pz() << ' ' */
      /* 	       << ((TLorentzVector*)Cand5)->E()  */
      /* 	       << endl; */
      /* 	} */
    }  
}
void Dijets::LorentzBoost(Double_t RotMatrix[4][4], Double_t Momentum[4], Int_t Option)
{
  // Lorentz boost
  // Option = 0 => Lorentz boost to cm frame of "Momemtum"
  // Option = 1 => Lorentz boost from cm frame of "Momemtum"

  // Temp vars
  Double_t TempMomentum[4], TempMass;

  // Boosted matriz
  Double_t BoostMatrix[4][4];

  // Loop. vars
  Int_t k4Vec,iCol,jLin;

  // Copy vector into temp.
  for (k4Vec=0;k4Vec<4;k4Vec++)
    TempMomentum[k4Vec] = Momentum[k4Vec];
       
  // Calculate (temp. mass)^2
  TempMass = pow(TempMomentum[3],2)-pow(TempMomentum[1],2)-pow(TempMomentum[2],2)-pow(TempMomentum[0],2);

  // Check if negative => else cal. real mass
  if (TempMass<0) 
    {
      printf("Mass negative\n");
      return;
    }
  else TempMass = sqrt(TempMass);

  // Add mass
  TempMomentum[3] = TempMomentum[3] + TempMass;

  // Calc Factor
  TempMass = 1 /(TempMass*TempMomentum[3]);

  // Check in which direction: "from" or "to"
  if (Option == 0)
    TempMomentum[3] = - TempMomentum[3];
  else if (Option != 1)
    {
      printf("Wrong Option: 1 => from , 0 => to\n");
      return;
    }

  //cout << "tempmom = " 
  //   << TempMomentum[0] << ' '
  //   << TempMomentum[1] << ' '
  //   << TempMomentum[2] << ' '
  //   << TempMomentum[3] << ' '
  //   << TempMass << endl;

  // Calc. boost matrix away (Pas sur que ca marche!!!!)
  for(iCol=0;iCol<4;iCol++)
    for(jLin=0;jLin<4;jLin++)
      {
	BoostMatrix[iCol][jLin] = TempMomentum[iCol]*TempMomentum[jLin]*TempMass;
        if (iCol == jLin) 
	  BoostMatrix[iCol][jLin] = BoostMatrix[iCol][jLin] + 1;
	//cout << "boostmat1 = " << iCol << ' ' << jLin << ' '
	//   << BoostMatrix[iCol][jLin] << ' '
	//   << RotMatrix[iCol][jLin] << ' ' 
	//   << endl;
      }
    
  // Treat last element
  BoostMatrix[3][3] = BoostMatrix[3][3] - 2;

  // Boost away (et tjrs pas sur)
  Dijets::MatrixMul(BoostMatrix,RotMatrix, RotMatrix);

  //for(iCol=0;iCol<4;iCol++)
  //for(jLin=0;jLin<4;jLin++)
  //cout << "boostmat1 = " << iCol << ' ' << jLin << ' '
  //     << BoostMatrix[iCol][jLin] << ' '
  //     << RotMatrix[iCol][jLin] << ' ' 
  //     << endl;
    
}

void Dijets::RRot(Double_t RotMatrix[4][4], Double_t Vector1[4], Double_t Vector2[4]){
  //   PREMULTIPLY R BY THE 4 BY 4 MATRIX TO
  //   ROTATE FROM VECTOR A TO VECTOR B BY THE SHORTEST ROUTE
  //   IF THEY ARE EXACTLY BACK-TO-BACK, THE ROTATION AXIS IS THE VECTOR
  //   WHICH IS PERPENDICULAR TO THEM AND THE X AXIS, UNLESS THEY ARE
  //   PERPENDICULAR TO THE Y AXIS, WHEN IT IS THE VECTOR WHICH IS
  //   PERPENDICULAR TO THEM AND THE Y AXIS.
  //   NOTE THAT THESE CONDITIONS GUARANTEE THAT IF BOTH ARE PERPENDICULAR
  //   TO THE Z AXIS, IT WILL BE USED AS THE ROTATION AXIS.

  // Define precision of measurement
  const Double_t AnglePres = 0.0000005;

  // counters
  Int_t ic,jc;

  // Rotation matrix M
  Double_t M[4][4];

  // Helper matrix
  Double_t HelpMatrix[4][4];

  // "P"^2 of Vector1 and Vector2 
  Double_t LenghtVec1, LenghtVec2, SumVec;
  
  // Temp vector
  Double_t TempVec1[4], TempVec2[4];
 
  // Temo lenght
  Double_t TempLenght, TempLenght1, TempLenght2;

  //for(ic=0;ic<4;ic++)
  //  cout << "r1 = " 
  //   << RotMatrix[ic][0] << ' '
  //   << RotMatrix[ic][1] << ' '
  //   << RotMatrix[ic][2] << ' '
  //   << RotMatrix[ic][3] << endl;

  LenghtVec1 = pow(Vector1[0],2)+pow(Vector1[1],2)+pow(Vector1[2],2);
  LenghtVec2 = pow(Vector2[0],2)+pow(Vector2[1],2)+pow(Vector2[2],2);

  if (LenghtVec1<0 || LenghtVec2<0)
    {
      printf("Input vectors are ambiguous\n");
      return;
    }
  else
    {
      LenghtVec1 = 1/sqrt(LenghtVec1);
      LenghtVec2 = 1/sqrt(LenghtVec2);
    }
  
  // Calc sum vector
  SumVec = (Vector1[0]*Vector2[0]+Vector1[1]*Vector2[1]+Vector1[2]*Vector2[2])*LenghtVec1*LenghtVec2;

  // If collinear => nothing to do
  if (SumVec > (1-AnglePres))
    return;
  else if (SumVec < (-1+AnglePres))
    {
      // If they are back to back => use axis perpendicular to them and X axis
      if (fabs(Vector2[1]) > AnglePres)
	{
	  TempVec1[0] = 0;
	  TempVec1[1] = -Vector2[2];
	  TempVec1[2] = Vector2[1];
	}
      else 
	{
	  TempVec1[0] = Vector2[2];
	  TempVec1[1] = 0;
	  TempVec1[2] = -Vector2[0];
	}
    }
  else
    {
      // Find rotation axis
      TempVec1[0] = Vector1[1]*Vector2[2] - Vector1[2]*Vector2[1];
      TempVec1[1] = Vector1[2]*Vector2[0] - Vector1[0]*Vector2[2];
      TempVec1[2] = Vector1[0]*Vector2[1] - Vector1[1]*Vector2[0];
    }

  // Calc. norm of vector Vec1
  TempLenght = (TempVec1[0]*TempVec1[0])+(TempVec1[1]*TempVec1[1])+(TempVec1[2]*TempVec1[2]);

  if (TempLenght < 0 )
    {
      printf("Lenght TempLenght1 negative\n");
      return;
    }
  else
    TempLenght = 1/sqrt(TempLenght);

  //cout << "c in rrot = " 
  //   << TempLenght << ' '
  //   << TempVec1[0] << ' '
  //   << TempVec1[1] << ' '
  //   << TempVec1[2] << endl;

  // Find rotation to intermediate axis from Vector1
  TempVec2[0] = Vector1[1]*TempVec1[2] - Vector1[2]*TempVec1[1];
  TempVec2[1] = Vector1[2]*TempVec1[0] - Vector1[0]*TempVec1[2];
  TempVec2[2] = Vector1[0]*TempVec1[1] - Vector1[1]*TempVec1[0];

  TempLenght1 = LenghtVec1*TempLenght;

  //cout << "d1 in rrot = " 
  //   << TempLenght1 << ' '
  //   << LenghtVec1 << ' '
  //   << TempLenght << ' '
  //   << TempVec2[0] << ' '
  //   << TempVec2[1] << ' '
  //   << TempVec2[2] << endl;

  // fill in rotation matrix M
  M[0][0] = Vector1[0]* LenghtVec1;
  M[0][1] = Vector1[1]* LenghtVec1;
  M[0][2] = Vector1[2]* LenghtVec1;
  M[0][3] = 0;
  M[1][0] = TempVec1[0]* TempLenght;
  M[1][1] = TempVec1[1]* TempLenght;
  M[1][2] = TempVec1[2]* TempLenght;
  M[1][3] = 0;
  M[2][0] = TempVec2[0]*TempLenght1;
  M[2][1] = TempVec2[1]*TempLenght1;
  M[2][2] = TempVec2[2]*TempLenght1;
  M[2][3] = 0;
  M[3][0] = 0;
  M[3][1] = 0;
  M[3][2] = 0;
  M[3][3] = 1;

  //for(ic=0;ic<4;ic++)
  //  cout << "m2 = " 
  //   << M[ic][0] << ' '
  //   << M[ic][1] << ' '
  //   << M[ic][2] << ' '
  //   << M[ic][3] << endl;

  //for(ic=0;ic<4;ic++)
  //   cout << "r2 = " 
  //   << RotMatrix[ic][0] << ' '
  //   << RotMatrix[ic][1] << ' '
  //   << RotMatrix[ic][2] << ' '
  //   << RotMatrix[ic][3] << endl;

  // Mul matrices - but reset HelpMatrix first
  for(ic=0;ic<4;ic++)
    for(jc=0;jc<4;jc++)
      HelpMatrix[ic][jc] = 0.;
  Dijets::MatrixMul(M,RotMatrix,HelpMatrix);

  // copy to RotMatrix array
  for(ic=0;ic<4;ic++)
    for(jc=0;jc<4;jc++)
      RotMatrix[ic][jc] = HelpMatrix[ic][jc];

  //for(ic=0;ic<4;ic++)
  //  cout << "r3 = " 
  //   << RotMatrix[ic][0] << ' '
  //   << RotMatrix[ic][1] << ' '
  //   << RotMatrix[ic][2] << ' '
  //   << RotMatrix[ic][3] << endl;

  // Find rotation from intermediate axes to Vector2
  TempVec2[0] = Vector2[1]*TempVec1[2] - Vector2[2]*TempVec1[1];
  TempVec2[1] = Vector2[2]*TempVec1[0] - Vector2[0]*TempVec1[2];
  TempVec2[2] = Vector2[0]*TempVec1[1] - Vector2[1]*TempVec1[0];

  TempLenght2 = LenghtVec2*TempLenght;

  //cout << "d2 in rrot = " 
  //   << TempLenght2 << ' '
  //   << TempVec2[0] << ' '
  //   << TempVec2[1] << ' '
  // << TempVec2[2] << endl;

  M[0][0] = Vector2[0]*LenghtVec2;
  M[1][0] = Vector2[1]*LenghtVec2;
  M[2][0] = Vector2[2]*LenghtVec2;
  M[0][1] = TempVec1[0]*TempLenght;
  M[1][1] = TempVec1[1]*TempLenght;
  M[2][1] = TempVec1[2]*TempLenght;
  M[0][2] = TempVec2[0]*TempLenght2;
  M[1][2] = TempVec2[1]*TempLenght2;
  M[2][2] = TempVec2[2]*TempLenght2;

  //for(ic=0;ic<4;ic++)
  //  cout << "m2 = " 
  //   << M[ic][0] << ' '
  //   << M[ic][1] << ' '
  //   << M[ic][2] << ' '
  //   << M[ic][3] << endl;

  // Mult. matrices - but reset HelpMatrix first
  for(ic=0;ic<4;ic++)
    for(jc=0;jc<4;jc++)
      HelpMatrix[ic][jc] = 0.;
  Dijets::MatrixMul(M,RotMatrix,HelpMatrix);

  // copy to RotMatrix array
  for(ic=0;ic<4;ic++)
    for(jc=0;jc<4;jc++)
      RotMatrix[ic][jc] = HelpMatrix[ic][jc];

  //for(ic=0;ic<4;ic++)
  //  cout << "r4 = " 
  //   << RotMatrix[ic][0] << ' '
  //   << RotMatrix[ic][1] << ' '
  //   << RotMatrix[ic][2] << ' '
  //   << RotMatrix[ic][3] << endl;
}
  
void Dijets::MatrixMul(Double_t M1[4][4], Double_t M2[4][4], Double_t M3[4][4])
{
  // Mult. Matrix M1 and M2 --> result stored in M3

  // loop. vars
  Int_t iCol, jLin, kInd;

  // saefty array
  Double_t MSave[4][4];

  //for (iCol=0;iCol<4;iCol++)
  //cout << "kmul1 = " << iCol << ' ' 
  // << M1[iCol][0] << ' ' << M1[iCol][1] << ' ' 
  // << M1[iCol][2] << ' ' << M1[iCol][3] << ' ' 
  // << M2[iCol][0] << ' ' << M2[iCol][1] << ' ' 
  // << M2[iCol][2] << ' ' << M2[iCol][3] << ' ' 
  // << endl; 

  // Loop over all matrix elements and multipoy them one by one
  for (iCol=0;iCol<4;iCol++)
    {
      for (jLin=0;jLin<4;jLin++)
	{
	  //cout << "mist = " << M2[0][0] << endl;
	  MSave[iCol][jLin] = 0;
          for (kInd=0;kInd<4;kInd++)
	    {
	      MSave[iCol][jLin] += M1[iCol][kInd]*M2[kInd][jLin];
	      //tssMSave[iCol][jLin] += M1[kInd][jLin]*M2[iCol][kInd];
	      //cout << "element " << kInd << ' ' 
	      //   << iCol << ' ' << jLin << ' ' 
	      //   << M1[kInd][jLin] << ' '
	      //   << M2[iCol][kInd] << ' '
	      //   << MSave[iCol][jLin] 
	      //   << endl;
	    }
	}
    }

  //for (iCol=0;iCol<4;iCol++)
  //cout << "kmul1 = " << iCol << ' ' 
  // << MSave[iCol][0] << ' ' << MSave[iCol][1] << ' ' 
  // << MSave[iCol][2] << ' ' << MSave[iCol][3] << ' ' 
  // << endl; 

  for (iCol=0;iCol<4;iCol++)
    for (jLin=0;jLin<4;jLin++)
      M3[iCol][jLin] = MSave[iCol][jLin];
}

void Dijets::MatrixInv(Double_t M1[4][4], Double_t M2[4][4])
{
  // Invert Matrix

  // Some vars
  Double_t TempMatrix[4][4];
  Int_t iCol, jLin;

  // Loop over all elements => transpose
  for (iCol=0;iCol<4;iCol++)
    for(jLin=0;jLin<4;jLin++)
      TempMatrix[iCol][jLin] = M1[jLin][iCol];
  
  // Negative energy-momentum mixing
  for (iCol=0;iCol<3;iCol++)
    {
      TempMatrix[3][iCol] = -TempMatrix[3][iCol];
      TempMatrix[iCol][3] = - TempMatrix[iCol][3];
    }
 
  // Output
  for (iCol=0;iCol<4;iCol++)
    for(jLin=0;jLin<4;jLin++)
      M2[iCol][jLin] = TempMatrix[iCol][jLin];

}



#endif
