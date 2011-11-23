#include <iostream>
#include <assert.h>
using namespace std;


#include<inc/TVertex.h>
#include<TMath.h>

#include<DAFVertexFinder.hh>
#include<VertexFitter.hh>
#include "LinearizedTrack.hh"

#include "CLHEP/Vector/LorentzVector.h"
using CLHEP::HepLorentzVector;

using namespace VxLite;

TVertex::TVertex():
fApplySmearing(false),
fDropTracks(false),
fDropProbability(0.02),
fTracks_dropped(0),
fChi2(0)
{
}

TVertex::~TVertex() {
}

// calculates projected decay length
Float_t TVertex::CalculateVertexProjectedDecayLength() {

    // v02: the finder returns 666 if the vertex was not found for this jet;
    // most likely disappears in the following CN versions but still keeping
    // so that can potentially be used for v02
    if ((fVertexX==666)||(fVertexY==666)||(fVertexZ==666)) return (-999);

    // get a primary-secondary vertex distance in the transverse plane
    Float_t deltaX = fVertexX - fPrimaryVertexX;
    Float_t deltaY = fVertexY - fPrimaryVertexY;

    // get the decay length
    Float_t DecayLength=TMath::Sqrt(deltaX*deltaX+deltaY*deltaY);
    fDecayLength = DecayLength;
    if ( DecayLength > 1. )     return (-998);
    if ( TMath::Abs(fVertexZ) >30. )    return (-998);

    // get projected decay length
    Float_t ProjectedDecayLength=0;

    Float_t AxisSinPhi=TMath::Sin(fAxisPhi);
    Float_t AxisCosPhi=TMath::Cos(fAxisPhi);
    ProjectedDecayLength = deltaX*AxisCosPhi+deltaY*AxisSinPhi;

    // eta-dependend shift of the whole projected decay length distribution
    // (for the highest eta bins)
    // note that this should be done only for MC, hence we use fApplySmearing flag,
    // which is set to true for MC in case smearing is switched on in analysis.cxx.
    // Hence this shift won't work if smearing is switched off.
    if (fApplySmearing) {
        if ( (1.6 < fAxisEta) && (fAxisEta < 2.2) ) ProjectedDecayLength -= 0.0021913;
        if ( (1.3 < fAxisEta) && (fAxisEta < 1.6) ) ProjectedDecayLength -= 0.0015827;
        if ( (1.0 < fAxisEta) && (fAxisEta < 1.3) ) ProjectedDecayLength -= 0.000766;
    }

    fProjDecayLength = ProjectedDecayLength;
    return      ProjectedDecayLength;
}

Float_t TVertex::CalculateVertexSignificance() {

    Float_t ProjectedDecayLength=CalculateVertexProjectedDecayLength();
    if (ProjectedDecayLength == -998) return -998;
    if (ProjectedDecayLength == -999) return -999;

    Float_t d1=TMath::Cos(fAxisPhi);
    Float_t d2=TMath::Sin(fAxisPhi);

    Float_t ProjectedDecayLengthError=0;

    Float_t sigma_x=TMath::Sqrt(fVertexCovariance[0]);
    Float_t sigma_y=TMath::Sqrt(fVertexCovariance[2]);

    // ProjectedDecayLengthError squared consists from three terms
    Double_t a = d1*d1*(sigma_x*sigma_x+fPrimaryVertexXError*fPrimaryVertexXError);
    Double_t b = d2*d2*(sigma_y*sigma_y+fPrimaryVertexYError*fPrimaryVertexYError);
    Double_t c = 2*d1*d2*fVertexCovariance[1];
    ProjectedDecayLengthError=TMath::Sqrt(a + b + c);

    // unsmeared significance
    fSignificance = ProjectedDecayLength / ProjectedDecayLengthError;

    // now apply smearing, code taken from Verena and further tuned to give the best
    // description in our case
    if (fApplySmearing) {

        Double_t nr_rand = rnd.Rndm();
        Float_t exponent = 5.;

        // Smear core by Gaussian
        if( nr_rand < 0.05 )
        {
            Double_t nr_rand_gauss = rnd.Gaus();
            Float_t smearvalue = 1.8*ProjectedDecayLengthError*nr_rand_gauss;
            ProjectedDecayLength += smearvalue;
            //cout<<"case 1 "<<smearvalue<<endl;
        }

        // Smear intermediate tails by Gaussian
        if( nr_rand < 0.01 )
        {
            Double_t nr_rand_gauss = rnd.Gaus();
            Float_t smearvalue = 2.3*ProjectedDecayLengthError*nr_rand_gauss;
            ProjectedDecayLength += smearvalue;
            //cout<<"case 2 "<<smearvalue<<endl;
        }

        // Smear extreme tails by exponential function
        if( nr_rand < 0.1*ProjectedDecayLengthError )
        {
            //TRandom3 *rnd2 = new TRandom3();
            Double_t nr_rand2 = rnd2.Rndm();
            Double_t randtemp = 2*nr_rand2-1;
            Float_t sign = randtemp/TMath::Abs(randtemp);
            ProjectedDecayLength += sign*TMath::Log(1-TMath::Abs(randtemp))/(-exponent);
            //delete rnd2;
            //cout<<"case 3 "<<sign*TMath::Log(1-TMath::Abs(randtemp))/(-exponent)<<endl;
            //cout<<ProjectedDecayLengthError<<" "<<randtemp<<" "<<nr_rand2<<endl;
        }
        //delete rnd;
    }

    fProjectedDecayLengthError = ProjectedDecayLengthError;
    fSignificanceSmeared = ProjectedDecayLength / ProjectedDecayLengthError;
    fProjDecayLengthSmeared = ProjectedDecayLength;

    // what to return better?
    fSignificance = fSignificanceSmeared;
    fProjDecayLength = ProjectedDecayLength;

    return          fSignificanceSmeared;
}

void TVertex::SetVertexCoordinates(Float_t x, Float_t y, Float_t z) {
        fVertexX = x;
        fVertexY = y;
        fVertexZ = z;
}
void TVertex::SetPrimaryVertexCoordinates(Float_t x, Float_t y, Float_t z) {
        fPrimaryVertexX = x;
        fPrimaryVertexY = y;
        fPrimaryVertexZ = z;
}

void TVertex::SetPrimaryVertexCoordinatesError(Float_t xerr, Float_t yerr, Float_t zerr) {
        fPrimaryVertexXError = xerr;
        fPrimaryVertexYError = yerr;
        fPrimaryVertexZError = zerr;
}

void TVertex::SetAxisVector(Float_t eta, Float_t phi) {
        fAxisEta = eta;
        fAxisPhi = phi;
}

void TVertex::SetVertexCovariance(Float_t * cov) {
        for (int k = 0; k<6; k++) fVertexCovariance[k] = cov[k];
}

void TVertex::SetVertexTracks(Int_t ntracks, Int_t * trackIDs){
	fNumberOfTracks = ntracks;
	for (int i = 0; i<fNumberOfTracks; i++) {
		fTrackIDs[i] = trackIDs[i];
	}
}

void TVertex::GetVertexTracks(Int_t & ntracks, Int_t * trackIDs) {
    ntracks = fNumberOfTracks;
    for (int i = 0; i<fNumberOfTracks; i++) {
        trackIDs[i] = fTrackIDs[i];
    }
}

void TVertex::SetTrackParameters(Int_t ntracks, Float_t	helices[30][5], Float_t	helixcov[30][15], Float_t * trackmom) {
    fNumberOfTracks = ntracks;
    for (int i = 0; i < fNumberOfTracks; i++ ) {
        for (int j = 0; j < 5; j++) {
            fTrackHelices[i][j] = helices[i][j];
        }
        for (int j = 0; j < 15; j++) {
            fTrackHelixCovariance[i][j] = helixcov[i][j];
        }
        fTrackMomentum[i] = trackmom[i]; 
    }
}

void TVertex::GetTrackParameters(Int_t & ntracks, Float_t helices[30][5], Float_t helixcov[30][15], Float_t * trackmom) {
    ntracks = fNumberOfTracks;
    for (int i = 0; i < fNumberOfTracks; i++ ) {
        for (int j = 0; j < 5; j++) {
            helices[i][j] = fTrackHelices[i][j];
        }
        for (int j = 0; j < 15; j++) {
            helixcov[i][j] = fTrackHelixCovariance[i][j];
        }
        trackmom[i] = fTrackMomentum[i]; 
    }
}

void TVertex::SetTrackPt(Int_t ntracks, Float_t * trackpT) {
    if (fNumberOfTracks != ntracks) {
        cout << "wtf" << endl;
        abort();
    }
    for (int i = 0; i < fNumberOfTracks; i++ ) {
        fTrackPT[i] = trackpT[i]; 
    }
}

void TVertex::GetTrackPt(Float_t * trackpT) {
    for (int i = 0; i < fNumberOfTracks; i++ ) {
        trackpT[i]= fTrackPT[i]; 
    }
}


bool    TVertex::RefitVertex() {

        // set the chi2_cut (taken from where??) and create an instance of DAFVertexF
	float	chi2_cut = 20;
	DAFVertexFinder finder(chi2_cut);

        // for debugging purposes: calculate total number of two-track vertices
        if (fDropTracks && (fNumberOfTracks == 2) ) two_track_vertices_total++;

        // loop over all tracks assigned to this vertex
        // initialize counter of how many tracks were dropped from the vertex
        fTracks_dropped = 0;
        for(int i = 0 ; i < fNumberOfTracks; ++i) {
                // check whether dropping tracks for systematic studies was selected
                if (fDropTracks) {
                    // if yes, generate a random number
                    // it turned out that the way I used TRandom3 (declaring as a private member of TVertex) is completely wrong,
                    // because an instance of it was created for every TVertex object, hence the seed was
                    // always the same (the default one), thus the random sequence was the same as well;
                    // now declared TRandom3 object as static;
                    // the problem with this approach is that it can't be private anymore and
                    // has to be set up outside the scope of the class; this is done in analysis.cxx in the global scope.
                    // TODO: check that random numbers are actually uniformly distributed
                    // NOTE: one could also do: Double_t  rand_number = gRandom -> Rndm(); that is using global
                    // TRandom object from ROOT. However I don't know whether it's safe to use one object for 
                    // for different purposes (different types of smearing, track dropping, etc.)
                    Double_t  rand_number = fRndDropTracks.Rndm();
                    //cout << "random number: " << rand_number << "; prob: " << fDropProbability << endl;

                    // if the random number is smaller or equal to chosen probability to loose tracks - drop the track
                    // otherwise - proceed normally and add the track to the vertex
                    if (rand_number <= fDropProbability) {
                        fTracks_dropped++;
                        continue;
                    }
                }
                // add track to the vertex
                //cout << "adding track" << endl;
		finder.addTrack(new LinearizedTrack(i+1, fTrackHelices[i], fTrackHelixCovariance[i]));
	}
        // if this number of tracks after dropping is less than 2 - don't do a fit and return a flag saying that the fit wasn't done  
        // NOTE: condition (fTracks_dropped > 0) could be removed, but  here we are exploiting the fact that all vertices from Orange
        // must have at least two tracks, hence having less than two tracks can only happen if some tracks were dropped here
        // thus fTracks_dropped > 0
        if ( (fTracks_dropped > 0) && ( (fNumberOfTracks - fTracks_dropped) < 2)  ) {
          if (fNumberOfTracks==2) two_track_vertices_dropped++;
          return false;
        }
        double  sumofweights = 0;
        // after all tracks were added to a vertex, fit it
	sumofweights = finder.findVertex();
        if (sumofweights==0) {
            cout << "****** WARNING: Sum of weights are zero!! Skipping this vertex!" << endl;
            fChi2=999999;
            chi2ndf=99999;
            return false;
        }

        // now get the vertex object and results of the fit
	const VertexFitter* fitter = finder.fitter();
	
        // set refitted vertex coordinates
        fVertexX = fitter->vertex()[0];
        fVertexY = fitter->vertex()[1];
        fVertexZ = fitter->vertex()[2];
  
        // set covariance matrix of the refitted vertex
        // NOTE: the index convention of elements can be found here:
        // https://www-zeus-data.desy.de/tracking/ZEUS_ONLY/tools/tLite/vxlite.html
        CLHEP::HepSymMatrix cov_mat = fitter->covariance();
        fVertexCovariance[0] = cov_mat[0][0];
        fVertexCovariance[1] = cov_mat[0][1];
        fVertexCovariance[2] = cov_mat[1][1];
        fVertexCovariance[3] = cov_mat[0][2];
        fVertexCovariance[4] = cov_mat[1][2];
        fVertexCovariance[5] = cov_mat[2][2];

        // recalculate significance
        Float_t     Significance = CalculateVertexSignificance();
        // I'm not sure whether this can be removed for v04, so keep for the timebeing (the 2nd one has some effect!)
        if (Significance==(-999)) return false;
        if (Significance==(-998)) return false;

        // update also chi2/ndf
        fChi2 = fitter->chi2();
        chi2ndf = fitter->chi2() / fitter->ndof();

        // mass calculation after refittng,
        // it has be different from just fitter->mass() because in orange vxlitedaffitp is called in fact,
        // and in this function the mass calculation is somewhat different,
        // in particular there's momentum constraint
        // below is a copy of relevant part from this function (see VxLite::DAFVertexFinder class)
        HepLorentzVector p(0,0,0,0);
        for(int i = 0 ; i < (fNumberOfTracks - fTracks_dropped); ++i) {
          const LinearizedTrack* t = finder.track(i);
          if(! t->expanded()) {
              assert(t->weight() == 0);
              continue;
          }
          HepLorentzVector tp = t->momentum( fTrackMomentum[i] );    // Q: what is this??
          p +=  t->weight() * tp;
        }
        fMass = p.m();

        finder.reset(); // to have the same what is used in orange; should no make any difference though!

        return true;
}

void TVertex::SetApplySmearing(bool applysmearing) {
    fApplySmearing = applysmearing;
}

void TVertex::Print() {
    cout << "fNumberOfTracks= " << fNumberOfTracks << endl;
    cout << "fSignificance= " << fSignificance << endl;
    cout << "fPrimaryVertexX= " << fPrimaryVertexX << endl;
    cout << "fPrimaryVertexY= " << fPrimaryVertexY << endl;
    cout << "fPrimaryVertexZ= " << fPrimaryVertexZ << endl;
    cout << "fVertexZ= " << fVertexZ << endl;
    cout << "fVertexX= " << fVertexX << endl;
    cout << "fVertexY= " << fVertexY << endl;
    cout << "fMass= " << fMass << endl;
    cout << "fChi2= " << fChi2 << endl;
    cout << "fDecayLength= " << fDecayLength << endl;
    cout << "fAxisEta= " << fAxisEta << endl;
    cout << "fAxisPhi= " << fAxisPhi << endl;
}
