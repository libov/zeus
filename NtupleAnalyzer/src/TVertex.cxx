#include <iostream>
#include <assert.h>
using namespace std;


#include<inc/TVertex.h>
#include<TMath.h>
#include <inc/constants.h>

#include<DAFVertexFinder.hh>
#include<VertexFitter.hh>
#include "LinearizedTrack.hh"

#include "CLHEP/Vector/LorentzVector.h"
using CLHEP::HepLorentzVector;

using namespace VxLite;

using namespace constants;

// declarations of Sasha's routine
void TrackAllEfficiency
   (int& ntrack, int& ntrMax, float* Phi, float* cotTheta, float* Zh, float* Mom
    , int& Charge, int& IDpart, float& TrEff, float& TrInt);

void TrackAllEfficiency
       (float& Phi, float& cotTheta, float& Mom,
       int& Charge, int& IDpart, float& TrEff, float& TrInt);

void TrackSumEfficiency
       (float& Phi, float& cotTheta, float& Mom,
       int& Charge, int& IDpart, float& TrEff, float& TrEffI, float& TrInt, float& TrIntN, float& TrPrm);

TVertex::TVertex():
fApplySmearing(false),
fDropTracks(false),
fDropProbability(0.02),
fTracks_dropped(0),
fChi2(0),
fHadronicInteractionCorrection(0.4),
fUseHadronicInteractionMap(true)
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

        // default values - are set outside the class
        Float_t SmearingGauss1Width = fSmearingGauss1Width;
        Float_t SmearingGauss1Prob = fSmearingGauss1Prob;
        Float_t SmearingGauss2Width = fSmearingGauss2Width;
        Float_t SmearingGauss2Prob = fSmearingGauss2Prob;
        Float_t exponent = fSmearingExpCoeff;

        // for highest eta bin using a bit different parameters
        if ( (1.6 < fAxisEta) && (fAxisEta < 2.2) ) {
            SmearingGauss1Prob = 0.09;
            SmearingGauss2Prob = 0.006;
        }

        // Smear core by Gaussian
        if( nr_rand < SmearingGauss1Prob ) {
            Double_t nr_rand_gauss = rnd.Gaus();
            Float_t smearvalue = SmearingGauss1Width * ProjectedDecayLengthError * nr_rand_gauss;
            ProjectedDecayLength += smearvalue;
        }

        // Smear intermediate tails by Gaussian
        if( nr_rand < SmearingGauss2Prob ) {
            Double_t nr_rand_gauss = rnd.Gaus();
            Float_t smearvalue = SmearingGauss2Width * ProjectedDecayLengthError * nr_rand_gauss;
            ProjectedDecayLength += smearvalue;
        }

        // Smear extreme tails by exponential function
        if( nr_rand < fSmearingExpProb * ProjectedDecayLengthError ) {
            Double_t nr_rand2 = rnd2.Rndm();
            Double_t randtemp = 2*nr_rand2-1;
            Float_t sign = randtemp/TMath::Abs(randtemp);
            ProjectedDecayLength += sign*TMath::Log(1-TMath::Abs(randtemp))/(-exponent);
        }
    }

    fProjectedDecayLengthError = ProjectedDecayLengthError;
    fSignificanceSmeared = ProjectedDecayLength / ProjectedDecayLengthError;
    fProjDecayLengthSmeared = ProjectedDecayLength;

    // what to return better?
    fSignificance = fSignificanceSmeared;
    fProjDecayLength = ProjectedDecayLength;

    return fSignificanceSmeared;
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

void TVertex::SetTrackTheta(Int_t ntracks, Float_t * theta) {
    // sanity check: number of tracks
    if (fNumberOfTracks != ntracks) {
        cout << "ERROR: number of tracks given != number of tracks assigned to the vertex" << endl;
        abort();
    }
    for (int i = 0; i < fNumberOfTracks; i++ ) {
        fTrackTheta[i] = theta[i];
    }
}

void TVertex::SetTrackPhi(Int_t ntracks, Float_t * phi) {
    // sanity check: number of tracks
    if (fNumberOfTracks != ntracks) {
        cout << "ERROR: number of tracks given != number of tracks assigned to the vertex" << endl;
        abort();
    }
    for (int i = 0; i < fNumberOfTracks; i++ ) {
        fTrackPhi[i] = phi[i];
    }
}

void TVertex::SetTrackCharge(Int_t ntracks, Float_t * charge) {
    // sanity check: number of tracks
    if (fNumberOfTracks != ntracks) {
        cout << "ERROR: number of tracks given != number of tracks assigned to the vertex" << endl;
        abort();
    }
    for (int i = 0; i < fNumberOfTracks; i++ ) {
        fTrackCharge[i] = charge[i];
    }
}

void TVertex::GetTrackPt(Float_t * trackpT) {
    for (int i = 0; i < fNumberOfTracks; i++ ) {
        trackpT[i]= fTrackPT[i]; 
    }
}

bool    TVertex::RefitVertex() {

    // set the chi2_cut (taken from where??) and create an instance of DAFVertexF
    float chi2_cut = 20;
    DAFVertexFinder finder(chi2_cut);

    // for debugging purposes: calculate total number of two-track vertices
    if (fDropTracks && (fNumberOfTracks == 2) ) two_track_vertices_total++;

    // loop over all tracks assigned to this vertex
    // initialize counter of how many tracks were dropped from the vertex
    fTracks_dropped = 0;
    for(int i = 0 ; i < fNumberOfTracks; ++i) {
        // check whether dropping tracks for systematic studies was selected
        Float_t probability = -1;
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

            // get the probability of loosing a track
            // Sasha Spiridonov's map
            if (fUseHadronicInteractionMap) {
                Float_t TrEff = -1;
                Float_t TrInt = -1;
                Float_t TrEffI = -1;
                Float_t TrIntN = -1;
                Float_t TrPrm = -1;
                Int_t   charge = fTrackCharge[i];
                Float_t theta = fTrackTheta[i];
                // in case of Sum map - take into account 'cutoffs' below 11.5 and 160 degrees
                if (fUseTrackSumEfficiency && CUTOFF) {
                    Float_t lower_cutoff = 11.5 / RADtoDEG;
                    Float_t upper_cutoff = 160. / RADtoDEG;
                    if ( theta  < lower_cutoff ) {
                        theta = lower_cutoff;
                    } else if ( theta > upper_cutoff ) {
                        theta = upper_cutoff;
                    }
                }
                Float_t cot = 1./(TMath::Tan(theta));
                // 2=kaon, 3=proton, else=pion
                Int_t   id = 1;
                Float_t phadr = -1;
                if (fUseTrackSumEfficiency) {
                    TrackSumEfficiency (fTrackPhi[i], cot, fTrackMomentum[i], charge, id, TrEff, TrEffI, TrInt, TrIntN, TrPrm);
                    if ( (TrEff<0) || (TrEffI<0) || (TrInt<0) || (TrIntN<0) || (TrPrm<0) ) {
                        cout << "ERROR in TVertex: TrackSumEfficiency map failure - negative output values!" << endl;
                        cout << fTrackPhi[i] << " " << theta * RADtoDEG << " " << fTrackMomentum[i] << " " << charge << " " << id << endl;
                        cout << TrEff << " " << TrEffI << " " << TrInt << " " << TrIntN << " " << TrPrm << endl;
                        abort();
                    }
                    if ( (TrEff==0) || (TrEffI==0) || (TrInt==0) || (TrIntN==0) || (TrPrm==0) ) {
                        cout << "WARNING in TVertex: TrackSumEfficiency map failure - zero output values! Setting phadr to average = 4 per cent" << endl;
                        cout << fTrackPhi[i] << " " << theta * RADtoDEG << " " << fTrackMomentum[i] << " " << charge << " " << id << endl;
                        cout << TrEff << " " << TrEffI << " " << TrInt << " " << TrIntN << " " << TrPrm << endl;
                        phadr = fPHADRaverage;
                    } else {
                        Float_t TrEff_plus_TrEffI = TrEff + TrEffI;
                        Float_t VMCU_match_eff = TrEff_plus_TrEffI / TrPrm;
                        Float_t detector_eff = TrEff / ( (TrEff + TrIntN) * VMCU_match_eff) ;
                        phadr = TrEffI + TrInt - TrEffI/ ( VMCU_match_eff * detector_eff) ;
                        phadr = phadr/fPHADRScaling;
                    }

                } else {
                    TrackAllEfficiency (fTrackPhi[i], cot, fTrackMomentum[i], charge, id, TrEff, TrInt);
                    // sanity check
                    if ( (TrEff<0) || (TrInt<0) ) {
                        cout << "ERROR in TVertex: TrackAllEfficiency map failure - negative output values!" << endl;
                        abort();
                    }
                    if ( (TrEff==0) || (TrInt==0) ) {
                        cout << "WARNING in TVertex: TrackAllEfficiency map failure - zero output values! Setting phadr to average = 4 per cent" << endl;
                        phadr = fPHADRaverage;
                    } else phadr = TrInt;
                }
                // correct only low-pt tracks
                if (fTrackPT[i]<1.5) {
                    probability = fHadronicInteractionCorrection * phadr / (1. - phadr);
                } else {
                    probability = 0;
                }
            // constant probability
            } else {
                probability = fDropProbability;
            }

            // store to an array
            fTrackDropProbability[i] = probability / fHadronicInteractionCorrection;

            // if the random number is smaller or equal to chosen probability to loose tracks - drop the track
            // otherwise - proceed normally and add the track to the vertex
            if (rand_number <= probability) {
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
    cout << "fPrimaryVertexX= " << fPrimaryVertexX << " +- " << fPrimaryVertexXError << endl;
    cout << "fPrimaryVertexY= " << fPrimaryVertexY << " +- " << fPrimaryVertexYError << endl;
    cout << "fPrimaryVertexZ= " << fPrimaryVertexZ << " +- " << fPrimaryVertexZError << endl;
    cout << "fVertexZ= " << fVertexZ << endl;
    cout << "fVertexX= " << fVertexX << endl;
    cout << "fVertexY= " << fVertexY << endl;
    cout << "fVertexCovariance[0]= " << fVertexCovariance[0] << endl;
    cout << "fVertexCovariance[1]= " << fVertexCovariance[1] << endl;
    cout << "fVertexCovariance[2]= " << fVertexCovariance[2] << endl;
    cout << "fMass= " << fMass << endl;
    cout << "fChi2= " << fChi2 << endl;
    cout << "fDecayLength= " << fDecayLength << endl;
    cout << "fProjDecayLength= " << fProjDecayLength << endl;
    cout << "fAxisEta= " << fAxisEta << endl;
    cout << "fAxisPhi= " << fAxisPhi << endl;
}
