#ifndef TVertex_H
#define TVertex_H

#include <TROOT.h>
#include <TRandom3.h>
#include <vector>
using namespace std;

/*! \brief Secondary Vertex Class
*  
*
* This class contains information about single secondary vertex.
* On one hand it can be used just for storage (as it was before 11/02/2011)
* On the other hand some operations can be performed (after 11/02/2011): 
*  <ul>
*       \li Significance calculation from vertex position, reference axis, and beam spot (was done in TMiniNtupleAnalyzer.cxx before)
*       \li Vertex refitting using information track information
*  </ul>
*/

class TVertex
{
        public:
                TVertex();
                ~TVertex();
                Float_t         CalculateVertexSignificance();
                Float_t         CalculateVertexProjectedDecayLength();
                bool            RefitVertex();
                void            SetVertexCoordinates(Float_t x, Float_t y, Float_t z);
                void            SetPrimaryVertexCoordinates(Float_t x, Float_t y, Float_t z);
                void            SetPrimaryVertexCoordinatesError(Float_t xerr, Float_t yerr, Float_t zerr);
                void            SetAxisVector(Float_t eta, Float_t phi);
                void            SetVertexCovariance(Float_t * cov);
		void		SetVertexTracks(Int_t ntracks, Int_t * trackIDs);
		void 		SetTrackParameters(Int_t ntracks, Float_t    helices[30][5], Float_t helixcov[30][15], Float_t * trackmom);
                void            SetTrackPt(Int_t ntracks, Float_t   * trackpT);
                void            SetTrackTheta(Int_t ntracks, Float_t   * theta);
                void            SetTrackPhi(Int_t ntracks, Float_t   * phi);
                void            SetTrackCharge(Int_t ntracks, Float_t   * charge);
		void		SetApplySmearing(bool applysmearing);
                void            SetSmearingGauss1Prob(Double_t value) {fSmearingGauss1Prob = value;}
                void            SetSmearingGauss1Width(Double_t value) {fSmearingGauss1Width = value;}
                void            SetSmearingGauss2Prob(Double_t value) {fSmearingGauss2Prob = value;}
                void            SetSmearingGauss2Width(Double_t value) {fSmearingGauss2Width = value;}
                void            SetSmearingExpProb(Double_t value) {fSmearingExpProb = value;}
                void            SetSmearingExpCoeff(Double_t value) {fSmearingExpCoeff = value;}

                void            SetDropTracks(bool drop_tracks) {fDropTracks = drop_tracks;}
                void            SetUseHadronicInteractionMap(bool use_map) {fUseHadronicInteractionMap = use_map;}
                void            SetDropTrackProbability(Float_t prob) {fDropProbability = prob;}
                void            SetHadronicInteractionCorrection(Float_t corr) {fHadronicInteractionCorrection = corr;};
                void            SetVertexMass(Float_t mass) {fMass = mass;}
                void            SetChi2(Float_t chi2) {fChi2 = chi2;}
                void            SetNTracks(Int_t ntracks) {fNumberOfTracks=ntracks;}

                void            SetZUFO_jet_ratio(Float_t  ZUFO_jet) {fZUFO_jet_ratio = ZUFO_jet;}
                void            SetCAL_total_ratio(Float_t  CAL_total) {fCAL_total_ratio = CAL_total;}
                void            SetZUFO_type(Int_t type) {fZUFO_type = type;}

                // various getters
                void            GetTrackParameters(Int_t & ntracks, Float_t    helices[30][5], Float_t helixcov[30][15], Float_t * trackmom);
                void            GetTrackPt(Float_t   * trackpT);
                void            GetVertexCoordinates (Float_t & x, Float_t & y, Float_t & z) {x = fVertexX; y = fVertexY; z = fVertexZ;}
                Float_t*        GetVertexCovariance () { return fVertexCovariance;}
                void            GetVertexTracks(Int_t & ntracks, Int_t * trackIDs);
                Float_t         GetVertexMass() { return fMass;}
                Float_t         GetVertexSignificance() {return fSignificance;}
                Float_t         GetVertexProjectedDecayLength(){ return fProjDecayLength;}
                Float_t         GetVertexProjectedDecayLengthError() {return fProjectedDecayLengthError;}
                Float_t         GetVertexDecayLength() {return fDecayLength;}
                Float_t         GetAxisPhi() {return fAxisPhi;}
                Float_t         GetAxisEta() {return fAxisEta;}
                Float_t         GetPrimaryVertexXError() {return fPrimaryVertexXError;}
                Float_t         GetPrimaryVertexYError() {return fPrimaryVertexYError;}
                Float_t         GetPrimaryVertexCoordinateX() {return fPrimaryVertexX;}
                Float_t         GetPrimaryVertexCoordinateY() {return fPrimaryVertexY;}
                Float_t         GetPrimaryVertexCoordinateZ() {return fPrimaryVertexZ;}
                Int_t           GetNTracks() {return fNumberOfTracks;}
                unsigned        GetNTracksDropped(){return fTracks_dropped;}
                Float_t         GetChi2() {return fChi2;}
                Float_t         GetTrackMomentum(unsigned index) {return fTrackMomentum[index];}
                Float_t         GetTrackPT(unsigned index) {return fTrackPT[index];}
                Float_t         GetTrackTheta(unsigned index) {return fTrackTheta[index];}
                Float_t         GetTrackPhi(unsigned index) {return fTrackPhi[index];}
                Float_t         GetTrackDropProbability(unsigned index) {return fTrackDropProbability[index];}

                Float_t         GetZUFO_jet_ratio() {return fZUFO_jet_ratio;}
                Float_t         GetCAL_total_ratio() {return fCAL_total_ratio;}
                Int_t           GetZUFO_type() {return fZUFO_type;}

                void            Print();

		Int_t		id;
		Int_t		fJetB;
		Float_t		ProjDecayLength;
		Float_t		ProjDecayLengthError;
		Float_t		Significance;
		Float_t		chi2ndf;
                // added 11/02/2011; some variables overlap with above, but this
                // is done for backward compatibility

                Int_t           fTrackList[30];

                // some static members related to random numbers

                // TRandom objects
                static TRandom3 rnd;
                static TRandom3 rnd2;

                // TRandom object for dropping the tracks; created a different one - not using those for smearing
                // not sure this is needed, but to be on the safe side and avoid possible interferences (if any)
                static TRandom3	fRndDropTracks;
                static unsigned two_track_vertices_total;
                static unsigned two_track_vertices_dropped;

                // select how to determine the hadronic interaction probability
                static bool fUseTrackSumEfficiency;

                // scaling factor for phadr calculated from TrackSumEfficiency
                static Float_t  fPHADRScaling;

                // default (average) value of phadr; employed if the map gives zero values
                static Float_t  fPHADRaverage;

        private:
                Float_t         fSignificance;          //!< significance of the vertex
                Float_t         fProjDecayLength;       //!< projected decay length of the vertex

                Float_t         fSignificanceSmeared;          //!< significance of the vertex after the smearing
                Float_t         fProjDecayLengthSmeared;       //!< projected decay length of the vertex after smearing

                Float_t         fVertexX;               //!< X coordinate of the vertex
                Float_t         fVertexY;               //!< Y coordinate of the vertex
                Float_t         fVertexZ;               //!< Z coordinate of the vertex
                Float_t         fVertexCovariance[6];     //!< Array containing to covariance matrix of the vertex

                Float_t         fPrimaryVertexX;        //!< X coordinate of the primary vertex (= beam spot X)
                Float_t         fPrimaryVertexY;        //!< Y coordinate of the primary vertex (= beam spot Y)
                Float_t         fPrimaryVertexZ;        //!< Z coordinate of the primary vertex (= reduced primary Z)
                Float_t         fPrimaryVertexXError;   //!< error on X coordinate of the primary vertex (= beam spot size X)
                Float_t         fPrimaryVertexYError;   //!< error on Y coordinate of the primary vertex (= beam spot size Y)
                Float_t         fPrimaryVertexZError;   //!< error on Z coordinate of the primary vertex (= error on reduced primary Z)

                Float_t         fAxisEta;               //!< eta (pseudorapidity) of the reference axis
                Float_t         fAxisPhi;               //!< phi angle of the reference axis
                //Float_t         fJetEt;                 //!< jet transverse energy - if jets serves as a reference axis

                Float_t         fMass;                  //!< vertex mass
                Float_t         fChi2;

                Int_t           fNumberOfTracks;
                Int_t           fTrackIDs[30];

                Float_t         fTrackHelices[30][5];
                Float_t         fTrackHelixCovariance[30][15];
                Float_t         fTrackMomentum[30];
                Float_t         fTrackPT[30];
                Float_t         fTrackTheta[30];
                Float_t         fTrackPhi[30];
                Float_t         fTrackCharge[30];
                Float_t         fTrackDropProbability[30];

                bool            fApplySmearing;
                Double_t        fSmearingGauss1Prob;
                Double_t        fSmearingGauss1Width;
                Double_t        fSmearingGauss2Prob;
                Double_t        fSmearingGauss2Width;
                Double_t        fSmearingExpProb;
                Double_t        fSmearingExpCoeff;

                // flag that says whether drop tracks from the vertex or keep them all 
                // (for evaluation of systematics uncertainty due to tracking inefficiency)
                bool            fDropTracks;
                // if above is true, this varible specifies probability to drop the track
                Float_t         fDropProbability;
                unsigned        fTracks_dropped;        //!< number of tracks dropped from the fit
                Float_t         fHadronicInteractionCorrection;
                bool            fUseHadronicInteractionMap;

                Float_t         fProjectedDecayLengthError;
                Float_t         fDecayLength;

                // some "temporary" variables
                Float_t         fZUFO_jet_ratio;
                Float_t         fCAL_total_ratio;
                Int_t           fZUFO_type;
};
#endif
