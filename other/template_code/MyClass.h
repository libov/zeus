//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jul 18 14:47:25 2011 by ROOT version 5.26/00c
// from TChain orange/
//////////////////////////////////////////////////////////

#ifndef MyClass_h
#define MyClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TMath.h>

class MyClass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           Runnr;
   Int_t           Eventnr;
   Int_t           Evtake;
   Int_t           Evtake_iwant;
   Int_t           Mvdtake;
   Int_t           Stttake;
   Int_t           Tpoltake;
   Int_t           Lpoltake;
   Int_t           Fmutake;
   Int_t           Mbtake;
   Int_t           Tag6take;
   Int_t           Fltw[2];
   Int_t           Fltpsw[2];
   Int_t           Fltfl;
   Int_t           Gslt_global;
   Int_t           Sltw[6];
   Int_t           Sltupw[6];
   Int_t           Tltw[15];
   Int_t           Dstw[4];
   Int_t           Fltpsfcw[2];
   Float_t         Bac_etot;
   Float_t         Bac_etot_o2r;
   Int_t           Bac_npad;
   Int_t           Bac_npad_o2r;
   Float_t         Bac_et;
   Float_t         Bac_px;
   Float_t         Bac_py;
   Int_t           Nbacmu;
   Float_t         Mubac_xyz[50][3];   //[NBACMU]
   Float_t         Mubac_dxyz[50][3];   //[NBACMU]
   Float_t         Mubac_cos[50][3];   //[NBACMU]
   Float_t         Mubac_dcos[50][3];   //[NBACMU]
   Float_t         Mubac_eloss[50];   //[NBACMU]
   Float_t         Mubac_deloss[50];   //[NBACMU]
   Int_t           Mubac_unit[50];   //[NBACMU]
   Int_t           Mubac_dim[50];   //[NBACMU]
   Int_t           Mubac_quality[50];   //[NBACMU]
   Int_t           Ahit[50];   //[NBACMU]
   Int_t           Pad[50];   //[NBACMU]
   Int_t           Bitword[2];
   Int_t           Calib_idcalscheme;
   Float_t         Cal_px;
   Float_t         Cal_py;
   Float_t         Cal_pz;
   Float_t         Cal_e;
   Float_t         Cal_et;
   Float_t         Cal_empz;
   Float_t         Cal_pt;
   Float_t         Cal_phi;
   Float_t         Remc[6];
   Float_t         Bemc[6];
   Float_t         Femc[6];
   Float_t         Rhac[6];
   Float_t         Bhac[6];
   Float_t         Fhac[6];
   Float_t         Bhac2[6];
   Float_t         Fhac2[6];
   Int_t           Nfemc;
   Int_t           Nfhac1;
   Int_t           Nfhac2;
   Int_t           Nbemc;
   Int_t           Nbhac1;
   Int_t           Nbhac2;
   Int_t           Nremc;
   Int_t           Nrhac;
   Float_t         Cal_tf;
   Float_t         Cal_tb;
   Float_t         Cal_tr;
   Float_t         Cal_tg;
   Float_t         Cal_tu;
   Float_t         Cal_td;
   Float_t         Cal_tu_e;
   Float_t         Cal_td_e;
   Int_t           Cal_tu_n;
   Int_t           Cal_td_n;
   Float_t         Etamax_ce;
   Float_t         Etamax_ce4;
   Float_t         Cal_et10;
   Float_t         Mtrknoe_pi;
   Float_t         Mtrknoe_k;
   Float_t         E_hk;
   Float_t         Unmen_pi;
   Float_t         Unmen_k;
   Int_t           Sparkf;
   Float_t         Pex1ir[4];
   Float_t         Et1ir;
   Float_t         Etex1ir;
   Float_t         Pex2ir[4];
   Float_t         Et2ir;
   Float_t         Etex2ir;
   Float_t         Percir[4];
   Float_t         Etrcir;
   Float_t         Cc_had_0[4];
   Float_t         Cc_gamma_0;
   Float_t         Cc_cehmom[4];
   Float_t         Cc_zuhmom[4];
   Float_t         Cc_cchmom[4];
   Float_t         Cc_pt;
   Float_t         Cc_et;
   Float_t         Cc_empz;
   Float_t         Cc_gamma;
   Float_t         Cc_yjb;
   Float_t         Cc_q2jb;
   Float_t         Cc_xjb;
   Float_t         Cc_etamax;
   Float_t         Cc_eemc;
   Float_t         Cc_ehac1;
   Float_t         Cc_ehac2;
   Float_t         Cc_emaxco;
   Int_t           Cc_nemc;
   Int_t           Cc_nhac1;
   Int_t           Cc_nhac2;
   Int_t           Cc_fclus_dt;
   Int_t           Cc_fclus_dm;
   Float_t         Cc_fclus_et;
   Float_t         Cc_fclus_e;
   Float_t         Cc_rclus_asoe;
   Float_t         Cc_vapvpcell;
   Float_t         Cc_vapvpzu;
   Float_t         Cc_vapvpcac;
   Int_t           Nlepton;
   Int_t           Nradpho;
   Int_t           Nboson;
   Int_t           Nquark;
   Int_t           Ngluon;
   Int_t           Idscatlep;
   Int_t           Idradpho;
   Int_t           Idboson;
   Int_t           Idquark;
   Int_t           Idgluon;
   Int_t           Dolepton;
   Int_t           Doradpho;
   Int_t           Doboson;
   Int_t           Doquark;
   Int_t           Dogluon;
   Float_t         Plepton[5];
   Float_t         Pradpho[5];
   Float_t         Pboson[5];
   Float_t         Pquark[5];
   Float_t         Pgluon[5];
   Int_t           Nqg;
   Int_t           Quarkprt;
   Int_t           Idqg[1275];   //[nqg]
   Int_t           Doqg[1275];   //[nqg]
   Int_t           Prtqg[1275];   //[nqg]
   Float_t         Pqg[1275][5];   //[nqg]
   Int_t           Emncand;
   Int_t           Emerror;
   Float_t         Emprob[4];   //[EmNcand]
   Float_t         Empos[4][3];   //[EmNcand]
   Float_t         Emcalpos[4][3];   //[EmNcand]
   Float_t         Emcalene[4];   //[EmNcand]
   Float_t         Emein[4];   //[EmNcand]
   Float_t         Emenin[4];   //[EmNcand]
   Float_t         Emecorr[4][3];   //[EmNcand]
   Float_t         Emth[4];   //[EmNcand]
   Float_t         Emph[4];   //[EmNcand]
   Float_t         Empt[4];   //[EmNcand]
   Int_t           Emxdet[4][3];   //[EmNcand]
   Int_t           Emydet[4][3];   //[EmNcand]
   Int_t           Emtrknr[4];   //[EmNcand]
   Int_t           Emnrsl[4];   //[EmNcand]
   Float_t         Emdca[4];   //[EmNcand]
   Float_t         Emdcabeam[4];   //[EmNcand]
   Float_t         Emtrkp[4];   //[EmNcand]
   Float_t         Emtrkth[4];   //[EmNcand]
   Float_t         Emtrkph[4];   //[EmNcand]
   Float_t         Emtrkq[4];   //[EmNcand]
   Float_t         Emtrkdme[4];   //[EmNcand]
   Float_t         Emtrkdce[4];   //[EmNcand]
   Float_t         Emtrkpos[4][3];   //[EmNcand]
   Int_t           Emsrtf[4];   //[EmNcand]
   Int_t           Emsrtquad[4];   //[EmNcand]
   Int_t           Emhesf[4];   //[EmNcand]
   Int_t           Emcorrcode[4];   //[EmNcand]
   Float_t         Emsrtpos[4][2];   //[EmNcand]
   Float_t         Emsrtene[4];   //[EmNcand]
   Float_t         Emhespos[4][2];   //[EmNcand]
   Float_t         Emhesene[4];   //[EmNcand]
   Float_t         Emhesr[4];   //[EmNcand]
   Float_t         Emprsene[4][3];   //[EmNcand]
   Float_t         Emccet[4];   //[EmNcand]
   Float_t         Emccempz[4];   //[EmNcand]
   Float_t         Emetamax[4];   //[EmNcand]
   Float_t         Emcehmom[4][4];   //[EmNcand]
   Float_t         Emzuhmom[4][4];   //[EmNcand]
   Float_t         Emcchmom[4][4];   //[EmNcand]
   Float_t         Emxel[4];   //[EmNcand]
   Float_t         Emyel[4];   //[EmNcand]
   Float_t         Emq2el[4];   //[EmNcand]
   Float_t         Emxda[4];   //[EmNcand]
   Float_t         Emyda[4];   //[EmNcand]
   Float_t         Emq2da[4];   //[EmNcand]
   Float_t         Emxda_cell[4];   //[EmNcand]
   Float_t         Emyda_cell[4];   //[EmNcand]
   Float_t         Emq2da_cell[4];   //[EmNcand]
   Float_t         Emxjb[4];   //[EmNcand]
   Float_t         Emyjb[4];   //[EmNcand]
   Float_t         Emq2jb[4];   //[EmNcand]
   Float_t         Emxjb_cell[4];   //[EmNcand]
   Float_t         Emyjb_cell[4];   //[EmNcand]
   Float_t         Emq2jb_cell[4];   //[EmNcand]
   Float_t         Emfemc[4];   //[EmNcand]
   Float_t         Emcalprob[4];   //[EmNcand]
   Int_t           Eminctd[4];   //[EmNcand]
   Int_t           Emnneartrk[4][2];   //[EmNcand]
   Float_t         Emetneartrk[4][2];   //[EmNcand]
   Float_t         Emtrkmatchi2[4];   //[EmNcand]
   Float_t         Emfmaxbemc[4];   //[EmNcand]
   Float_t         Emfmaxremc[4];   //[EmNcand]
   Float_t         Emfmaxfemc[4];   //[EmNcand]
   Float_t         Emdeltaz[4];   //[EmNcand]
   Float_t         Emdeltax[4];   //[EmNcand]
   Float_t         Emdeltay[4];   //[EmNcand]
   Int_t           E5ncand;
   Int_t           E5error;
   Float_t         E5prob[4];   //[E5Ncand]
   Float_t         E5pos[4][3];   //[E5Ncand]
   Float_t         E5calpos[4][3];   //[E5Ncand]
   Float_t         E5calene[4];   //[E5Ncand]
   Float_t         E5ein[4];   //[E5Ncand]
   Float_t         E5enin[4];   //[E5Ncand]
   Float_t         E5ecorr[4][3];   //[E5Ncand]
   Float_t         E5th[4];   //[E5Ncand]
   Float_t         E5ph[4];   //[E5Ncand]
   Float_t         E5pt[4];   //[E5Ncand]
   Int_t           E5xdet[4][3];   //[E5Ncand]
   Int_t           E5ydet[4][3];   //[E5Ncand]
   Int_t           E5trknr[4];   //[E5Ncand]
   Int_t           E5nrsl[4];   //[E5Ncand]
   Float_t         E5dca[4];   //[E5Ncand]
   Float_t         E5dcabeam[4];   //[E5Ncand]
   Float_t         E5trkp[4];   //[E5Ncand]
   Float_t         E5trkth[4];   //[E5Ncand]
   Float_t         E5trkph[4];   //[E5Ncand]
   Float_t         E5trkq[4];   //[E5Ncand]
   Float_t         E5trkdme[4];   //[E5Ncand]
   Float_t         E5trkdce[4];   //[E5Ncand]
   Float_t         E5trkpos[4][3];   //[E5Ncand]
   Int_t           E5srtf[4];   //[E5Ncand]
   Int_t           E5srtquad[4];   //[E5Ncand]
   Int_t           E5hesf[4];   //[E5Ncand]
   Int_t           E5corrcode[4];   //[E5Ncand]
   Float_t         E5srtpos[4][2];   //[E5Ncand]
   Float_t         E5srtene[4];   //[E5Ncand]
   Float_t         E5hespos[4][2];   //[E5Ncand]
   Float_t         E5hesene[4];   //[E5Ncand]
   Float_t         E5hesr[4];   //[E5Ncand]
   Float_t         E5prsene[4][3];   //[E5Ncand]
   Float_t         E5ccet[4];   //[E5Ncand]
   Float_t         E5ccempz[4];   //[E5Ncand]
   Float_t         E5etamax[4];   //[E5Ncand]
   Float_t         E5cehmom[4][4];   //[E5Ncand]
   Float_t         E5zuhmom[4][4];   //[E5Ncand]
   Float_t         E5cchmom[4][4];   //[E5Ncand]
   Float_t         E5xel[4];   //[E5Ncand]
   Float_t         E5yel[4];   //[E5Ncand]
   Float_t         E5q2el[4];   //[E5Ncand]
   Float_t         E5xda[4];   //[E5Ncand]
   Float_t         E5yda[4];   //[E5Ncand]
   Float_t         E5q2da[4];   //[E5Ncand]
   Float_t         E5xda_cell[4];   //[E5Ncand]
   Float_t         E5yda_cell[4];   //[E5Ncand]
   Float_t         E5q2da_cell[4];   //[E5Ncand]
   Float_t         E5xjb[4];   //[E5Ncand]
   Float_t         E5yjb[4];   //[E5Ncand]
   Float_t         E5q2jb[4];   //[E5Ncand]
   Float_t         E5xjb_cell[4];   //[E5Ncand]
   Float_t         E5yjb_cell[4];   //[E5Ncand]
   Float_t         E5q2jb_cell[4];   //[E5Ncand]
   Float_t         E5femc[4];   //[E5Ncand]
   Float_t         E5calprob[4];   //[E5Ncand]
   Int_t           E5inctd[4];   //[E5Ncand]
   Int_t           E5nneartrk[4][2];   //[E5Ncand]
   Float_t         E5etneartrk[4][2];   //[E5Ncand]
   Float_t         E5trkmatchi2[4];   //[E5Ncand]
   Float_t         E5fmaxbemc[4];   //[E5Ncand]
   Float_t         E5fmaxremc[4];   //[E5Ncand]
   Float_t         E5fmaxfemc[4];   //[E5Ncand]
   Float_t         E5deltaz[4];   //[E5Ncand]
   Float_t         E5deltax[4];   //[E5Ncand]
   Float_t         E5deltay[4];   //[E5Ncand]
   Int_t           Npart;
   Int_t           Idlepton;
   Int_t           Idphoton;
   Int_t           Part_id[2044];   //[nPart]
   Int_t           Part_prt[2044];   //[nPart]
   Float_t         Part_p[2044][4];   //[nPart]
   Int_t           Nmu;
   Int_t           Muqual[20];   //[Nmu]
   Int_t           Mucharge[20];   //[Nmu]
   Float_t         Mupt[20];   //[Nmu]
   Float_t         Muth[20];   //[Nmu]
   Float_t         Muph[20];   //[Nmu]
   Float_t         Mup[20][3];   //[Nmu]
   Float_t         Muperr[20];   //[Nmu]
   Int_t           Mutrfl[20];   //[Nmu]
   Int_t           Mutrid[20];   //[Nmu]
   Int_t           Muvcid[20];   //[Nmu]
   Int_t           Muztid[20];   //[Nmu]
   Int_t           Mustid[20];   //[Nmu]
   Int_t           Muvtxfl[20];   //[Nmu]
   Int_t           Muvtxid[20];   //[Nmu]
   Int_t           Muglomu[20];   //[Nmu]
   Int_t           Mubremat[20];   //[Nmu]
   Int_t           Mubacmat[20];   //[Nmu]
   Int_t           Mumubac[20];   //[Nmu]
   Int_t           Mumamma[20];   //[Nmu]
   Int_t           Mumpmat[20];   //[Nmu]
   Int_t           Mumufo[20];   //[Nmu]
   Int_t           Mumip[20];   //[Nmu]
   Int_t           Mumv[20];   //[Nmu]
   Int_t           Mucalfl[20];   //[Nmu]
   Float_t         Mucalene[20];   //[Nmu]
   Float_t         Muhac2[20];   //[Nmu]
   Int_t           Muzufid[20];   //[Nmu]
   Float_t         Mupmip[20];   //[Nmu]
   Float_t         Muhene[20];   //[Nmu]
   Float_t         Mutime[20];   //[Nmu]
   Int_t           Muchfl[20];   //[Nmu]
   Int_t           Muchid[20];   //[Nmu]
   Float_t         Mupmat[20];   //[Nmu]
   Int_t           Mundof[20];   //[Nmu]
   Int_t           Munphi[20];   //[Nmu]
   Float_t         Muz[20];   //[Nmu]
   Float_t         Muprec[20];   //[Nmu]
   Float_t         Mubmchi2[20];   //[Nmu]
   Int_t           Mubmbac[20];   //[Nmu]
   Float_t         Mubacdca[20];   //[Nmu]
   Int_t           Mubacdimq[20];   //[Nmu]
   Float_t         Mudxy[20];   //[Nmu]
   Float_t         Mudz[20];   //[Nmu]
   Float_t         Muisol[20][10];   //[Nmu]
   Int_t           Munis[20][10];   //[Nmu]
   Float_t         Muisdrmip[20][2];   //[Nmu]
   Float_t         Muisetmip[20][2];   //[Nmu]
   Int_t           Muistumip[20][2];   //[Nmu]
   Int_t           Mujetfl_a[20];   //[Nmu]
   Int_t           Mujetid_a[20];   //[Nmu]
   Float_t         Mujetdr_a[20];   //[Nmu]
   Float_t         Mujetpt_a[20];   //[Nmu]
   Float_t         Mujetdr2_a[20];   //[Nmu]
   Float_t         Mujetpt2_a[20];   //[Nmu]
   Int_t           Muhjet_id[20];   //[Nmu]
   Int_t           Mujetfl_b[20];   //[Nmu]
   Int_t           Mujetid_b[20];   //[Nmu]
   Float_t         Mujetdr_b[20];   //[Nmu]
   Float_t         Mujetpt_b[20];   //[Nmu]
   Float_t         Mujetdr2_b[20];   //[Nmu]
   Float_t         Mujetpt2_b[20];   //[Nmu]
   Int_t           Mujetfl_c[20];   //[Nmu]
   Int_t           Mujetid_c[20];   //[Nmu]
   Float_t         Mujetdr_c[20];   //[Nmu]
   Float_t         Mujetpt_c[20];   //[Nmu]
   Float_t         Mujetdr2_c[20];   //[Nmu]
   Float_t         Mujetpt2_c[20];   //[Nmu]
   Int_t           Mujetfl_d[20];   //[Nmu]
   Int_t           Mujetid_d[20];   //[Nmu]
   Float_t         Mujetdr_d[20];   //[Nmu]
   Float_t         Mujetpt_d[20];   //[Nmu]
   Float_t         Mujetdr2_d[20];   //[Nmu]
   Float_t         Mujetpt2_d[20];   //[Nmu]
   Int_t           Muick[20];   //[Nmu]
   Int_t           Mupartyp[20];   //[Nmu]
   Float_t         Mumc_p[20][4];   //[Nmu]
   Int_t           Mudirtyp[20];   //[Nmu]
   Float_t         Mumc_d[20][4];   //[Nmu]
   Int_t           Muqtyp[20];   //[Nmu]
   Float_t         Mumc_q[20][4];   //[Nmu]
   Int_t           Mutruefl[20];   //[Nmu]
   Float_t         Mudecdist[20];   //[Nmu]
   Int_t           Kt_njet_a;
   Float_t         Kt_etjet_a[30];   //[KT_NJET_A]
   Float_t         Kt_etajet_a[30];   //[KT_NJET_A]
   Float_t         Kt_phijet_a[30];   //[KT_NJET_A]
   Float_t         Kt_masjet_a[30];   //[KT_NJET_A]
   Int_t           Kt_njet_b;
   Float_t         Kt_etjet_b[30];   //[KT_NJET_B]
   Float_t         Kt_etajet_b[30];   //[KT_NJET_B]
   Float_t         Kt_phijet_b[30];   //[KT_NJET_B]
   Float_t         Kt_masjet_b[30];   //[KT_NJET_B]
   Float_t         Kt_bst_b[4];
   Int_t           Kt_njet_c;
   Float_t         Kt_etjet_c[30];   //[KT_NJET_C]
   Float_t         Kt_etajet_c[30];   //[KT_NJET_C]
   Float_t         Kt_phijet_c[30];   //[KT_NJET_C]
   Float_t         Kt_masjet_c[30];   //[KT_NJET_C]
   Float_t         Kt_bst_c[4];
   Int_t           Kt_njet_d;
   Float_t         Kt_etjet_d[30];   //[KT_NJET_D]
   Float_t         Kt_etajet_d[30];   //[KT_NJET_D]
   Float_t         Kt_phijet_d[30];   //[KT_NJET_D]
   Float_t         Kt_masjet_d[30];   //[KT_NJET_D]
   Float_t         Kt_bst_d[4];
   Int_t           Kt_njet_e;
   Float_t         Kt_etjet_e[30];   //[KT_NJET_E]
   Float_t         Kt_etajet_e[30];   //[KT_NJET_E]
   Float_t         Kt_phijet_e[30];   //[KT_NJET_E]
   Float_t         Kt_bst_e[4];
   Int_t           Kt_njet_f;
   Float_t         Kt_etjet_f[30];   //[KT_NJET_F]
   Float_t         Kt_etajet_f[30];   //[KT_NJET_F]
   Float_t         Kt_phijet_f[30];   //[KT_NJET_F]
   Float_t         Kt_bst_f[4];
   Int_t           Kt_njet_g;
   Float_t         Kt_etjet_g[30];   //[KT_NJET_G]
   Float_t         Kt_etajet_g[30];   //[KT_NJET_G]
   Float_t         Kt_phijet_g[30];   //[KT_NJET_G]
   Float_t         Kt_bst_g[4];
   Int_t           Kt_njet_h;
   Float_t         Kt_etjet_h[30];   //[KT_NJET_H]
   Float_t         Kt_etajet_h[30];   //[KT_NJET_H]
   Float_t         Kt_phijet_h[30];   //[KT_NJET_H]
   Float_t         Kt_bst_h[4];
   Int_t           Kt_njet_i;
   Float_t         Kt_etjet_i[30];   //[KT_NJET_I]
   Float_t         Kt_etajet_i[30];   //[KT_NJET_I]
   Float_t         Kt_phijet_i[30];   //[KT_NJET_I]
   Int_t           Kt_njet_j;
   Float_t         Kt_etjet_j[30];   //[KT_NJET_J]
   Float_t         Kt_etajet_j[30];   //[KT_NJET_J]
   Float_t         Kt_phijet_j[30];   //[KT_NJET_J]
   Int_t           Kt_njet_k;
   Float_t         Kt_etjet_k[30];   //[KT_NJET_K]
   Float_t         Kt_etajet_k[30];   //[KT_NJET_K]
   Float_t         Kt_phijet_k[30];   //[KT_NJET_K]
   Float_t         Kt_bst_k[4];
   Int_t           Kt_njet_l;
   Float_t         Kt_etjet_l[30];   //[KT_NJET_L]
   Float_t         Kt_etajet_l[30];   //[KT_NJET_L]
   Float_t         Kt_phijet_l[30];   //[KT_NJET_L]
   Float_t         Kt_bst_l[4];
   Int_t           Cone_njet;
   Float_t         Cone_etjet[20];   //[CONE_NJET]
   Float_t         Cone_etajet[20];   //[CONE_NJET]
   Float_t         Cone_phijet[20];   //[CONE_NJET]
   Float_t         Elumie;
   Float_t         Xlumie;
   Float_t         Ylumie;
   Float_t         Elumig;
   Float_t         Xlumig;
   Float_t         Ylumig;
   Int_t           Nmcdstar;
   Int_t           Imcdstar[10];   //[nmcdstar]
   Float_t         Ptmcdstar[10];   //[nmcdstar]
   Float_t         Etamcdstar[10];   //[nmcdstar]
   Float_t         Phimcdstar[10];   //[nmcdstar]
   Int_t           Ndsd02;
   Float_t         Pdsd02[20][2];   //[ndsd02]
   Float_t         Tdsd02[20][2];   //[ndsd02]
   Float_t         Fdsd02[20][2];   //[ndsd02]
   Int_t           Kdsd02[20][2];   //[ndsd02]
   Float_t         Pdsps2[20];   //[ndsd02]
   Float_t         Tdsps2[20];   //[ndsd02]
   Float_t         Fdsps2[20];   //[ndsd02]
   Float_t         Pmds2[20][4];   //[ndsd02]
   Int_t           Kmds2[20];   //[ndsd02]
   Int_t           Nmds2[20];   //[ndsd02]
   Int_t           Ndsd04;
   Float_t         Pdsd04[20][4];   //[ndsd04]
   Float_t         Tdsd04[20][4];   //[ndsd04]
   Float_t         Fdsd04[20][4];   //[ndsd04]
   Int_t           Kdsd04[20][4];   //[ndsd04]
   Int_t           Mdsd04[20][4];   //[ndsd04]
   Float_t         Pdsps4[20];   //[ndsd04]
   Float_t         Tdsps4[20];   //[ndsd04]
   Float_t         Fdsps4[20];   //[ndsd04]
   Float_t         Pmds4[20][4];   //[ndsd04]
   Int_t           Kmds4[20];   //[ndsd04]
   Int_t           Nmds4[20];   //[ndsd04]
   Int_t           Ndzd02;
   Float_t         Pdzd02[20][2];   //[ndzd02]
   Float_t         Tdzd02[20][2];   //[ndzd02]
   Float_t         Fdzd02[20][2];   //[ndzd02]
   Int_t           Kdzd02[20][2];   //[ndzd02]
   Float_t         Pdzga2[20];   //[ndzd02]
   Float_t         Tdzga2[20];   //[ndzd02]
   Float_t         Fdzga2[20];   //[ndzd02]
   Float_t         Pmdz2[20][4];   //[ndzd02]
   Int_t           Kmdz2[20];   //[ndzd02]
   Int_t           Nmdz2[20];   //[ndzd02]
   Int_t           Ndzd04;
   Float_t         Pdzd04[20][4];   //[ndzd04]
   Float_t         Tdzd04[20][4];   //[ndzd04]
   Float_t         Fdzd04[20][4];   //[ndzd04]
   Int_t           Kdzd04[20][4];   //[ndzd04]
   Int_t           Mdzd04[20][4];   //[ndzd04]
   Float_t         Pdzga4[20];   //[ndzd04]
   Float_t         Tdzga4[20];   //[ndzd04]
   Float_t         Fdzga4[20];   //[ndzd04]
   Float_t         Pmdz4[20][4];   //[ndzd04]
   Int_t           Kmdz4[20];   //[ndzd04]
   Int_t           Nmdz4[20];   //[ndzd04]
   Int_t           Nd02;
   Float_t         Pd02[20][2];   //[nd02]
   Float_t         Td02[20][2];   //[nd02]
   Float_t         Fd02[20][2];   //[nd02]
   Int_t           Kd02[20][2];   //[nd02]
   Float_t         Pmd02[20][4];   //[nd02]
   Int_t           Kmd02[20];   //[nd02]
   Int_t           Nmd02[20];   //[nd02]
   Int_t           Nd04;
   Float_t         Pd04[20][4];   //[nd04]
   Float_t         Td04[20][4];   //[nd04]
   Float_t         Fd04[20][4];   //[nd04]
   Int_t           Kd04[20][4];   //[nd04]
   Int_t           Md04[20][4];   //[nd04]
   Float_t         Pmd04[20][4];   //[nd04]
   Int_t           Kmd04[20];   //[nd04]
   Int_t           Nmd04[20];   //[nd04]
   Int_t           Ndsdch;
   Float_t         Pdsdch[20][3];   //[ndsdch]
   Float_t         Tdsdch[20][3];   //[ndsdch]
   Float_t         Fdsdch[20][3];   //[ndsdch]
   Int_t           Kdsdch[20][3];   //[ndsdch]
   Int_t           Mdsdch[20][3];   //[ndsdch]
   Float_t         Pdsgah[20];   //[ndsdch]
   Float_t         Tdsgah[20];   //[ndsdch]
   Float_t         Fdsgah[20];   //[ndsdch]
   Float_t         Pmdsh[20][4];   //[ndsdch]
   Int_t           Kmdsh[20];   //[ndsdch]
   Int_t           Nmdsh[20];   //[ndsdch]
   Int_t           Ndch;
   Float_t         Pdch[60][3];   //[ndch]
   Float_t         Tdch[60][3];   //[ndch]
   Float_t         Fdch[60][3];   //[ndch]
   Int_t           Kdch[60][3];   //[ndch]
   Int_t           Mdch[60][3];   //[ndch]
   Float_t         Pmdch[20][4];
   Int_t           Kmdch[20];
   Int_t           Nmdch[20];
   Int_t           Ndtdss;
   Float_t         Pdtdss[20][3];   //[ndtdss]
   Float_t         Tdtdss[20][3];   //[ndtdss]
   Float_t         Fdtdss[20][3];   //[ndtdss]
   Int_t           Kdtdss[20][3];   //[ndtdss]
   Int_t           Mdtdss[20][3];   //[ndtdss]
   Float_t         Pdtgas[20];   //[ndtdss]
   Float_t         Tdtgas[20];   //[ndtdss]
   Float_t         Fdtgas[20];   //[ndtdss]
   Float_t         Pmdts[20][4];   //[ndtdss]
   Int_t           Kmdts[20];   //[ndtdss]
   Int_t           Nmdts[20];   //[ndtdss]
   Int_t           Ndss;
   Float_t         Pdss[20][3];   //[ndss]
   Float_t         Tdss[20][3];   //[ndss]
   Float_t         Fdss[20][3];   //[ndss]
   Int_t           Kdss[20][3];   //[ndss]
   Int_t           Mdss[20][3];   //[ndss]
   Float_t         Pmdss[20][4];   //[ndss]
   Int_t           Kmdss[20];   //[ndss]
   Int_t           Nmdss[20];   //[ndss]
   Int_t           Ndla;
   Float_t         Pdla[20][3];   //[ndla]
   Float_t         Tdla[20][3];   //[ndla]
   Float_t         Fdla[20][3];   //[ndla]
   Int_t           Kdla[20][3];   //[ndla]
   Int_t           Mdla[20][3];   //[ndla]
   Float_t         Pmdla[20][4];   //[ndla]
   Int_t           Kmdla[20];   //[ndla]
   Int_t           Nmdla[20];   //[ndla]
   Float_t         Mc_ez;
   Float_t         Mc_esum;
   Float_t         Mc_etcone;
   Float_t         Mc_ercal;
   Float_t         Mc_el;
   Float_t         Mc_ep;
   Float_t         Mc_x;
   Float_t         Mc_y;
   Float_t         Mc_q2;
   Float_t         Mc_mu;
   Float_t         Mc_pt;
   Float_t         Mc_xpro;
   Float_t         Mc_xgam;
   Float_t         Mc_xpom;
   Float_t         Mc_beta;
   Float_t         Mc_t;
   Int_t           Mc_idl;
   Int_t           Mc_pidl;
   Int_t           Mc_pidp;
   Int_t           Mc_idfsl;
   Float_t         Mc_pfsl[4];
   Float_t         Mc_pfsph[4];
   Float_t         Mc_vtx[3];
   Int_t           Mc_ichnn;
   Float_t         Mc_q2_cr;
   Float_t         Mc_x_cr;
   Float_t         Mcvtx[3];
   Int_t           Simrun;
   Int_t           Sincand;
   Int_t           Sierror;
   Float_t         Siprob[4];   //[SiNcand]
   Float_t         Sipos[4][3];   //[SiNcand]
   Float_t         Sicalpos[4][3];   //[SiNcand]
   Float_t         Sicalene[4];   //[SiNcand]
   Float_t         Siein[4];   //[SiNcand]
   Float_t         Sienin[4];   //[SiNcand]
   Float_t         Siecorr[4][3];   //[SiNcand]
   Float_t         Sith[4];   //[SiNcand]
   Float_t         Siph[4];   //[SiNcand]
   Float_t         Sipt[4];   //[SiNcand]
   Int_t           Sixdet[4][3];   //[SiNcand]
   Int_t           Siydet[4][3];   //[SiNcand]
   Int_t           Sitrknr[4];   //[SiNcand]
   Int_t           Sinrsl[4];   //[SiNcand]
   Float_t         Sidca[4];   //[SiNcand]
   Float_t         Sitrkp[4];   //[SiNcand]
   Float_t         Sitrkth[4];   //[SiNcand]
   Float_t         Sitrkph[4];   //[SiNcand]
   Float_t         Sitrkq[4];   //[SiNcand]
   Float_t         Sitrkdme[4];   //[SiNcand]
   Float_t         Sitrkpos[4][3];   //[SiNcand]
   Int_t           Sisrtf[4];   //[SiNcand]
   Int_t           Sisrtquad[4];   //[SiNcand]
   Int_t           Sihesf[4];   //[SiNcand]
   Int_t           Sicorrcode[4];   //[SiNcand]
   Float_t         Sisrtpos[4][2];   //[SiNcand]
   Float_t         Sisrtene[4];   //[SiNcand]
   Float_t         Sihespos[4][2];   //[SiNcand]
   Float_t         Sihesene[4];   //[SiNcand]
   Float_t         Sihesr[4];   //[SiNcand]
   Float_t         Siprsene[4][3];   //[SiNcand]
   Float_t         Siccet[4];   //[SiNcand]
   Float_t         Siccempz[4];   //[SiNcand]
   Float_t         Sietamax[4];   //[SiNcand]
   Float_t         Sicehmom[4][4];   //[SiNcand]
   Float_t         Sizuhmom[4][4];   //[SiNcand]
   Float_t         Sicchmom[4][4];   //[SiNcand]
   Float_t         Sixel[4];   //[SiNcand]
   Float_t         Siyel[4];   //[SiNcand]
   Float_t         Siq2el[4];   //[SiNcand]
   Float_t         Sixda[4];   //[SiNcand]
   Float_t         Siyda[4];   //[SiNcand]
   Float_t         Siq2da[4];   //[SiNcand]
   Float_t         Sixda_cell[4];   //[SiNcand]
   Float_t         Siyda_cell[4];   //[SiNcand]
   Float_t         Siq2da_cell[4];   //[SiNcand]
   Float_t         Sixjb[4];   //[SiNcand]
   Float_t         Siyjb[4];   //[SiNcand]
   Float_t         Siq2jb[4];   //[SiNcand]
   Float_t         Sixjb_cell[4];   //[SiNcand]
   Float_t         Siyjb_cell[4];   //[SiNcand]
   Float_t         Siq2jb_cell[4];   //[SiNcand]
   Int_t           Nbpchn;
   Float_t         Bpmip[432];   //[nBPchn]
   Float_t         Bpxyz[432][3];   //[nBPchn]
   Float_t         Bptim[432];   //[nBPchn]
   Int_t           Tsu_halo;
   Int_t           Nv0lite;
   Float_t         Tsecvtx[80][3];   //[nv0lite]
   Float_t         Tsecvtx_chi[80];   //[nv0lite]
   Float_t         Tsecvtx_dca[80];   //[nv0lite]
   Float_t         Tsecvtx_collin2[80];   //[nv0lite]
   Float_t         Tsecvtx_collin3[80];   //[nv0lite]
   Float_t         Tsecvtx_dlen2[80];   //[nv0lite]
   Float_t         Tsecvtx_dlen3[80];   //[nv0lite]
   Int_t           Tq1[80];   //[nv0lite]
   Int_t           Tq2[80];   //[nv0lite]
   Int_t           Ent1[80];   //[nv0lite]
   Int_t           Ent2[80];   //[nv0lite]
   Int_t           Tt1_layinn[80];   //[nv0lite]
   Int_t           Tt1_layout[80];   //[nv0lite]
   Int_t           Tt2_layinn[80];   //[nv0lite]
   Int_t           Tt2_layout[80];   //[nv0lite]
   Int_t           Tt1_id[80];   //[nv0lite]
   Int_t           Tt2_id[80];   //[nv0lite]
   Int_t           Stt1[80];   //[nv0lite]
   Int_t           Stt2[80];   //[nv0lite]
   Int_t           Tt1_ndof[80];   //[nv0lite]
   Int_t           Tt2_ndof[80];   //[nv0lite]
   Float_t         Tp1[80][3];   //[nv0lite]
   Float_t         Tp2[80][3];   //[nv0lite]
   Float_t         Tpk[80][3];   //[nv0lite]
   Float_t         Tinvmass_lambda[80];   //[nv0lite]
   Float_t         Tinvmass_alambda[80];   //[nv0lite]
   Float_t         Tinvmass_k0[80];   //[nv0lite]
   Float_t         Tinvmass_ee[80];   //[nv0lite]
   Int_t           Ntrkvtx;
   Float_t         Xvtx;
   Float_t         Yvtx;
   Float_t         Zvtx;
   Float_t         Chivtx;
   Int_t           Nsecvtx;
   Float_t         Xsecvtx[40];   //[Nsecvtx]
   Float_t         Ysecvtx[40];   //[Nsecvtx]
   Float_t         Zsecvtx[40];   //[Nsecvtx]
   Float_t         Chisecvtx[40];   //[Nsecvtx]
   Float_t         Fetatr;
   Float_t         Betatr;
   Float_t         Pt_tr;
   Float_t         Empz_tr_pi;
   Float_t         Et_tr;
   Float_t         E_tr_pi;
   Float_t         Phi_tr;
   Float_t         Zvtx_fcal;
   Int_t           Fcal_nrgoodcells;
   Float_t         Fcal_vzerr;
   Float_t         V_h_px_zu;
   Float_t         V_h_py_zu;
   Float_t         V_h_pz_zu;
   Float_t         V_h_e_zu;
   Float_t         Etamax_zu;
   Float_t         Etamax_zu4;
   Float_t         Fgap;
   Float_t         Bgap;
   Int_t           Nzufos;
   Int_t           Tufo[250][4];   //[Nzufos]
   Int_t           Zufo_bsp[250];   //[Nzufos]
   Float_t         Zufo[250][4];   //[Nzufos]
   Float_t         Cufo[250];   //[Nzufos]
   Float_t         Zufoecal[250];   //[Nzufos]
   Float_t         Zufoeemc[250];   //[Nzufos]
   Int_t           Nt;
   Int_t           Vcthid[200];   //[nT]
   Int_t           Qtr[200];   //[nT]
   Int_t           Swmtr[200];   //[nT]
   Int_t           Qlttr[200];   //[nT]
   Int_t           Mtri[200];   //[nT]
   Int_t           Wtri[200][10];   //[nT]
   Float_t         Ptr[200];   //[nT]
   Float_t         Dptr[200];   //[nT]
   Float_t         Thtr[200];   //[nT]
   Float_t         Phtr[200];   //[nT]
   Float_t         Dist_istr[200];   //[nT]
   Int_t           Trk_ntracks;
   Int_t           Trk_type[400];   //[trk_ntracks]
   Int_t           Ntrack_type[4];
   Int_t           Def_trk_type;
   Int_t           Trk_id[400];   //[trk_ntracks]
   Int_t           Trk_id2[400];   //[trk_ntracks]
   Float_t         Trk_px[400];   //[trk_ntracks]
   Float_t         Trk_py[400];   //[trk_ntracks]
   Float_t         Trk_pz[400];   //[trk_ntracks]
   Float_t         Trk_charge[400];   //[trk_ntracks]
   Int_t           Trk_vtx[400];   //[trk_ntracks]
   Int_t           Trk_prim_vtx[400];   //[trk_ntracks]
   Int_t           Trk_sec_vtx[400];   //[trk_ntracks]
   Int_t           Trk_vxid[400];   //[trk_ntracks]
   Int_t           Trk_nzbyt[400];   //[trk_ntracks]
   Int_t           Trk_naxial[400];   //[trk_ntracks]
   Int_t           Trk_nstereo[400];   //[trk_ntracks]
   Int_t           Trk_ndof[400];   //[trk_ntracks]
   Int_t           Trk_layinner[400];   //[trk_ntracks]
   Int_t           Trk_layouter[400];   //[trk_ntracks]
   Float_t         Trk_dedxctd[400];   //[trk_ntracks]
   Float_t         Trk_dedxctdcr[400];   //[trk_ntracks]
   Int_t           Trk_dedxctderr[400];   //[trk_ntracks]
   Int_t           Trk_dedxctdnh[400];   //[trk_ntracks]
   Int_t           Trk_dedxctdsaturated[400];   //[trk_ntracks]
   Float_t         Trk_chi2[400];   //[trk_ntracks]
   Float_t         Trk_vchi2[400];   //[trk_ntracks]
   Int_t           Trk_nbr[400];   //[trk_ntracks]
   Int_t           Trk_nbz[400];   //[trk_ntracks]
   Int_t           Trk_nwu[400];   //[trk_ntracks]
   Int_t           Trk_nwv[400];   //[trk_ntracks]
   Int_t           Trk_nstt[400];   //[trk_ntracks]
   Float_t         Trk_dedxmvd[400];   //[trk_ntracks]
   Float_t         Trk_imppar[400];   //[trk_ntracks]
   Float_t         Trk_imperr[400];   //[trk_ntracks]
   Float_t         Trk_pca[400][3];   //[trk_ntracks]
   Int_t           Mcmatfmckin_id[400];   //[trk_ntracks]
   Float_t         Mcmatpx[400];   //[trk_ntracks]
   Float_t         Mcmatpy[400];   //[trk_ntracks]
   Float_t         Mcmatpz[400];   //[trk_ntracks]
   Float_t         Mcmate[400];   //[trk_ntracks]
   Float_t         Mcmatm[400];   //[trk_ntracks]
   Float_t         Mcmatcharge[400];   //[trk_ntracks]
   Int_t           Mcmatquality[400];   //[trk_ntracks]
   Int_t           Mcmattype[400];   //[trk_ntracks]
   Float_t         Mcmatsvert_x[400];   //[trk_ntracks]
   Float_t         Mcmatsvert_y[400];   //[trk_ntracks]
   Float_t         Mcmatsvert_z[400];   //[trk_ntracks]
   Int_t           Mcmatmother[400];   //[trk_ntracks]
   Float_t         Mcmatmother_px[400];   //[trk_ntracks]
   Float_t         Mcmatmother_py[400];   //[trk_ntracks]
   Float_t         Mcmatmother_pz[400];   //[trk_ntracks]
   Float_t         Mcmatmother_e[400];   //[trk_ntracks]
   Float_t         Mcmatmother_m[400];   //[trk_ntracks]
   Float_t         Mcmatmother_prt[400];   //[trk_ntracks]
   Int_t           Nchvtx;
   Float_t         Chvtxpar[1000][3];   //[nchvtx]
   Float_t         Chvtxcov[1000][6];   //[nchvtx]
   Float_t         Chchi2[1000];   //[nchvtx]
   Int_t           Nchds1;
   Float_t         Ds1ms[50];   //[nchds1]
   Float_t         Ds1pm[50];   //[nchds1]
   Float_t         Ds1th[50];   //[nchds1]
   Float_t         Ds1ph[50];   //[nchds1]
   Float_t         D1d0ms[50];   //[nchds1]
   Float_t         D1d0pm[50];   //[nchds1]
   Float_t         D1d0th[50];   //[nchds1]
   Float_t         D1d0ph[50];   //[nchds1]
   Float_t         D1kapm[50];   //[nchds1]
   Float_t         D1kath[50];   //[nchds1]
   Float_t         D1kaph[50];   //[nchds1]
   Float_t         D1pipm[50];   //[nchds1]
   Float_t         D1pith[50];   //[nchds1]
   Float_t         D1piph[50];   //[nchds1]
   Float_t         D1pspm[50];   //[nchds1]
   Float_t         D1psth[50];   //[nchds1]
   Float_t         D1psph[50];   //[nchds1]
   Int_t           Ds1trk[50];   //[nchds1]
   Int_t           Tds1ka[50];   //[nchds1]
   Int_t           Tds1pi[50];   //[nchds1]
   Int_t           Tds1ps[50];   //[nchds1]
   Int_t           Id1d0vtx[50];   //[nchds1]
   Int_t           Ids1rprm[50];   //[nchds1]
   Int_t           Nchds2;
   Float_t         Ds2ms[150];   //[nchds2]
   Float_t         Ds2pm[150];   //[nchds2]
   Float_t         Ds2th[150];   //[nchds2]
   Float_t         Ds2ph[150];   //[nchds2]
   Float_t         D2d0ms[150];   //[nchds2]
   Float_t         D2d0pm[150];   //[nchds2]
   Float_t         D2d0th[150];   //[nchds2]
   Float_t         D2d0ph[150];   //[nchds2]
   Float_t         D2kapm[150];   //[nchds2]
   Float_t         D2kath[150];   //[nchds2]
   Float_t         D2kaph[150];   //[nchds2]
   Float_t         D2p1pm[150];   //[nchds2]
   Float_t         D2p1th[150];   //[nchds2]
   Float_t         D2p1ph[150];   //[nchds2]
   Float_t         D2p2pm[150];   //[nchds2]
   Float_t         D2p2th[150];   //[nchds2]
   Float_t         D2p2ph[150];   //[nchds2]
   Float_t         D2p3pm[150];   //[nchds2]
   Float_t         D2p3th[150];   //[nchds2]
   Float_t         D2p3ph[150];   //[nchds2]
   Float_t         D2pspm[150];   //[nchds2]
   Float_t         D2psth[150];   //[nchds2]
   Float_t         D2psph[150];   //[nchds2]
   Int_t           Ds2trk[150];   //[nchds2]
   Int_t           Tds2ka[150];   //[nchds2]
   Int_t           Tds2p1[150];   //[nchds2]
   Int_t           Tds2p2[150];   //[nchds2]
   Int_t           Tds2p3[150];   //[nchds2]
   Int_t           Tds2ps[150];   //[nchds2]
   Int_t           Id2d0vtx[150];   //[nchds2]
   Int_t           Ids2rprm[150];   //[nchds2]
   Int_t           Ds2rin[150];   //[nchds2]
   Float_t         D2maxdca[150];   //[nchds2]
   Int_t           Nchd0;
   Float_t         D0ms[50];   //[nchd0]
   Float_t         D0pm[50];   //[nchd0]
   Float_t         D0th[50];   //[nchd0]
   Float_t         D0ph[50];   //[nchd0]
   Float_t         D0kapm[50];   //[nchd0]
   Float_t         D0kath[50];   //[nchd0]
   Float_t         D0kaph[50];   //[nchd0]
   Float_t         D0pipm[50];   //[nchd0]
   Float_t         D0pith[50];   //[nchd0]
   Float_t         D0piph[50];   //[nchd0]
   Int_t           D0trk[50];   //[nchd0]
   Int_t           Td0ka[50];   //[nchd0]
   Int_t           Td0pi[50];   //[nchd0]
   Int_t           Id0vtx[50];   //[nchd0]
   Int_t           Id0rprm[50];   //[nchd0]
   Int_t           Nchdch;
   Float_t         Dchms[100];   //[nchdch]
   Float_t         Dchpm[100];   //[nchdch]
   Float_t         Dchth[100];   //[nchdch]
   Float_t         Dchph[100];   //[nchdch]
   Float_t         Dckapm[100];   //[nchdch]
   Float_t         Dckath[100];   //[nchdch]
   Float_t         Dckaph[100];   //[nchdch]
   Float_t         Dcp1pm[100];   //[nchdch]
   Float_t         Dcp1th[100];   //[nchdch]
   Float_t         Dcp1ph[100];   //[nchdch]
   Float_t         Dcp2pm[100];   //[nchdch]
   Float_t         Dcp2th[100];   //[nchdch]
   Float_t         Dcp2ph[100];   //[nchdch]
   Int_t           Dchtrk[100];   //[nchdch]
   Int_t           Tdchka[100];   //[nchdch]
   Int_t           Tdchp1[100];   //[nchdch]
   Int_t           Tdchp2[100];   //[nchdch]
   Int_t           Idchvtx[100];   //[nchdch]
   Int_t           Idchrprm[100];   //[nchdch]
   Int_t           Nchdla;
   Float_t         Dlams[100];   //[nchdla]
   Float_t         Dlapm[100];   //[nchdla]
   Float_t         Dlath[100];   //[nchdla]
   Float_t         Dlaph[100];   //[nchdla]
   Float_t         Dlkapm[100];   //[nchdla]
   Float_t         Dlkath[100];   //[nchdla]
   Float_t         Dlkaph[100];   //[nchdla]
   Float_t         Dlprpm[100];   //[nchdla]
   Float_t         Dlprth[100];   //[nchdla]
   Float_t         Dlprph[100];   //[nchdla]
   Float_t         Dlpipm[100];   //[nchdla]
   Float_t         Dlpith[100];   //[nchdla]
   Float_t         Dlpiph[100];   //[nchdla]
   Int_t           Dlatrk[100];   //[nchdla]
   Int_t           Tdlaka[100];   //[nchdla]
   Int_t           Tdlapr[100];   //[nchdla]
   Int_t           Tdlapi[100];   //[nchdla]
   Int_t           Idlavtx[100];   //[nchdla]
   Int_t           Idlarprm[100];   //[nchdla]
   Int_t           Nchdss;
   Float_t         Dssms[50];   //[nchdss]
   Float_t         Dsspm[50];   //[nchdss]
   Float_t         Dssth[50];   //[nchdss]
   Float_t         Dssph[50];   //[nchdss]
   Float_t         Dsphms[50];   //[nchdss]
   Float_t         Dsphpm[50];   //[nchdss]
   Float_t         Dsphth[50];   //[nchdss]
   Float_t         Dsphph[50];   //[nchdss]
   Float_t         Dsk1pm[50];   //[nchdss]
   Float_t         Dsk1th[50];   //[nchdss]
   Float_t         Dsk1ph[50];   //[nchdss]
   Float_t         Dsk2pm[50];   //[nchdss]
   Float_t         Dsk2th[50];   //[nchdss]
   Float_t         Dsk2ph[50];   //[nchdss]
   Float_t         Dspipm[50];   //[nchdss]
   Float_t         Dspith[50];   //[nchdss]
   Float_t         Dspiph[50];   //[nchdss]
   Int_t           Dsstrk[50];   //[nchdss]
   Int_t           Tdssk1[50];   //[nchdss]
   Int_t           Tdssk2[50];   //[nchdss]
   Int_t           Tdsspi[50];   //[nchdss]
   Int_t           Idssvtx[50];   //[nchdss]
   Int_t           Idssrprm[50];   //[nchdss]
   Int_t           Bspt_prog;
   Float_t         Bspt_x;
   Float_t         Bspt_y;
   Float_t         Bspt_z;
   Float_t         Bspt_xer;
   Float_t         Bspt_yer;
   Float_t         Bspt_zer;
   Float_t         Bspt_dxdz;
   Float_t         Bspt_dydz;
   Float_t         Bspt_dxdzer;
   Float_t         Bspt_dydzer;
   Float_t         Bspt_xoff;
   Float_t         Bspt_yoff;
   Float_t         Bspt_xoffer;
   Float_t         Bspt_yoffer;
   Int_t           Ncb;
   Int_t           Cb_id[160];   //[ncb]
   Int_t           Cb_mother[160];   //[ncb]
   Int_t           Cb_daughter[160];   //[ncb]
   Int_t           Cb_daughter2[160];   //[ncb]
   Int_t           Cb_prt[160];   //[ncb]
   Int_t           Nlight_daughters[160];   //[ncb]
   Int_t           Plight_daughters[160];   //[ncb]
   Float_t         Cb_p[160][5];   //[ncb]
   Int_t           Tot_daughters;
   Int_t           Light_dau_id[1024];   //[tot_daughters]
   Int_t           Light_dau_index[1024];   //[tot_daughters]
   Float_t         Vtxredprm_x;
   Float_t         Vtxredprm_y;
   Float_t         Vtxredprm_z;
   Float_t         Vtxredprm_chi2;
   Float_t         Vtxredprm_cov[6];
   Float_t         Vtxredprm_ndf;
   Int_t           Nr_secvtx;
   Float_t         Vtxsec_x[60];   //[nr_secvtx]
   Float_t         Vtxsec_y[60];   //[nr_secvtx]
   Float_t         Vtxsec_z[60];   //[nr_secvtx]
   Float_t         Vtxsec_mass[60];   //[nr_secvtx]
   Float_t         Vtxsec_chi2[60];   //[nr_secvtx]
   Float_t         Vtxsec_ndf[60];   //[nr_secvtx]
   Int_t           Vtxsec_multi[60];   //[nr_secvtx]
   Float_t         Vtxsec_cov[60][6];   //[nr_secvtx]
   Int_t           Vtxsec_zttid[60][15];   //[nr_secvtx]
   Float_t         Vtxsec2d_x[60];   //[nr_secvtx]
   Float_t         Vtxsec2d_y[60];   //[nr_secvtx]
   Float_t         Vtxsec2d_z[60];   //[nr_secvtx]
   Float_t         Vtxsec2d_mass[60];   //[nr_secvtx]
   Float_t         Vtxsec2d_chi2[60];   //[nr_secvtx]
   Float_t         Vtxsec2d_ndf[60];   //[nr_secvtx]
   Float_t         Vtxsec2d_cov[60][6];   //[nr_secvtx]
   Int_t           Fmck_nkin;
   Float_t         Fmck_q2;
   Float_t         Fmck_w;
   Float_t         Fmck_xg;
   Int_t           Fmck_nstor;
   Int_t           Fmck_id[400];   //[fmck_nstor]
   Float_t         Fmck_px[400];   //[fmck_nstor]
   Float_t         Fmck_py[400];   //[fmck_nstor]
   Float_t         Fmck_pz[400];   //[fmck_nstor]
   Float_t         Fmck_e[400];   //[fmck_nstor]
   Float_t         Fmck_m[400];   //[fmck_nstor]
   Int_t           Fmck_isthep[400];   //[fmck_nstor]
   Int_t           Fmck_daug[400];   //[fmck_nstor]
   Int_t           Fmck_daug2[400];   //[fmck_nstor]
   Int_t           Fmck_prt[400];   //[fmck_nstor]
   Int_t           Fmck_prat[400];   //[fmck_nstor]
   Float_t         Fmck_impar[400];   //[fmck_nstor]
   Float_t         Fmck_impar2[400];   //[fmck_nstor]
   Int_t           Fmck_hadjet[400];   //[fmck_nstor]
   Int_t           Fmck_mhadjet[400];   //[fmck_nstor]
   Int_t           Fmck_bhadjet[400];   //[fmck_nstor]
   Int_t           Fmck_mbhadjet[400];   //[fmck_nstor]
   Int_t           Fmck_partjet[400];   //[fmck_nstor]
   Int_t           Fmck_mpartjet[400];   //[fmck_nstor]
   Int_t           Fmck_brhadjet[400];   //[fmck_nstor]
   Int_t           Fmck_brmhadjet[400];   //[fmck_nstor]
   Int_t           Fmck_brbhadjet[400];   //[fmck_nstor]
   Int_t           Fmck_brmbhadjet[400];   //[fmck_nstor]
   Int_t           Fmck_brpartjet[400];   //[fmck_nstor]
   Int_t           Fmck_brmpartjet[400];   //[fmck_nstor]
   Int_t           Fmvtx_nstor;
   Int_t           Fmvtx_id[50];   //[fmvtx_nstor]
   Float_t         Fmvtx_r[50][3];   //[fmvtx_nstor]
   Float_t         Fmvtx_time[50];   //[fmvtx_nstor]
   Int_t           Fmvtx_prby[50];   //[fmvtx_nstor]
   Int_t           Nhjets;
   Float_t         Pxhjet[10];   //[nhjets]
   Float_t         Pyhjet[10];   //[nhjets]
   Float_t         Pzhjet[10];   //[nhjets]
   Float_t         Ehjet[10];   //[nhjets]
   Int_t           Nhmjets;
   Float_t         Pxhmjet[10];   //[nhmjets]
   Float_t         Pyhmjet[10];   //[nhmjets]
   Float_t         Pzhmjet[10];   //[nhmjets]
   Float_t         Ehmjet[10];   //[nhmjets]
   Int_t           Nhbjets;
   Float_t         Pxhbjet[5120];   //[nhbjets]
   Float_t         Pyhbjet[5120];   //[nhbjets]
   Float_t         Pzhbjet[5120];   //[nhbjets]
   Float_t         Ehbjet[5120];   //[nhbjets]
   Int_t           Flhbjet[5120];   //[nhbjets]
   Int_t           Nphbjet[5120];   //[nhbjets]
   Int_t           Phbjet[5120][512];   //[nhbjets]
   Int_t           Nhbmjets;
   Float_t         Pxhbmjet[5120];   //[nhbmjets]
   Float_t         Pyhbmjet[5120];   //[nhbmjets]
   Float_t         Pzhbmjet[5120];   //[nhbmjets]
   Float_t         Ehbmjet[5120];   //[nhbmjets]
   Int_t           Flhbmjet[5120];   //[nhbmjets]
   Int_t           Nphbmjet[5120];   //[nhbmjets]
   Int_t           Phbmjet[5120][512];   //[nhbmjets]
   Int_t           Npjets;
   Float_t         Pxpjet[10];   //[npjets]
   Float_t         Pypjet[10];   //[npjets]
   Float_t         Pzpjet[10];   //[npjets]
   Float_t         Epjet[10];   //[npjets]
   Int_t           Npmjets;
   Float_t         Pxpmjet[10];   //[npmjets]
   Float_t         Pypmjet[10];   //[npmjets]
   Float_t         Pzpmjet[10];   //[npmjets]
   Float_t         Epmjet[10];   //[npmjets]
   Int_t           Nbrhjets;
   Float_t         Pxbrhjet[10];   //[nbrhjets]
   Float_t         Pybrhjet[10];   //[nbrhjets]
   Float_t         Pzbrhjet[10];   //[nbrhjets]
   Float_t         Ebrhjet[10];   //[nbrhjets]
   Int_t           Nbrhmjets;
   Float_t         Pxbrhmjet[10];   //[nbrhmjets]
   Float_t         Pybrhmjet[10];   //[nbrhmjets]
   Float_t         Pzbrhmjet[10];   //[nbrhmjets]
   Float_t         Ebrhmjet[10];   //[nbrhmjets]
   Int_t           Nbrhbjets;
   Float_t         Pxbrhbjet[10];   //[nbrhbjets]
   Float_t         Pybrhbjet[10];   //[nbrhbjets]
   Float_t         Pzbrhbjet[10];   //[nbrhbjets]
   Float_t         Ebrhbjet[10];   //[nbrhbjets]
   Int_t           Nbrhbmjets;
   Float_t         Pxbrhbmjet[10];   //[nbrhbmjets]
   Float_t         Pybrhbmjet[10];   //[nbrhbmjets]
   Float_t         Pzbrhbmjet[10];   //[nbrhbmjets]
   Float_t         Ebrhbmjet[10];   //[nbrhbmjets]
   Int_t           Nbrpjets;
   Float_t         Pxbrpjet[10];   //[nbrpjets]
   Float_t         Pybrpjet[10];   //[nbrpjets]
   Float_t         Pzbrpjet[10];   //[nbrpjets]
   Float_t         Ebrpjet[10];   //[nbrpjets]
   Int_t           Nbrpmjets;
   Float_t         Pxbrpmjet[10];   //[nbrpmjets]
   Float_t         Pybrpmjet[10];   //[nbrpmjets]
   Float_t         Pzbrpmjet[10];   //[nbrpmjets]
   Float_t         Ebrpmjet[10];   //[nbrpmjets]
   Int_t           Bm_n;
   Int_t           Bm_idvc[100];   //[Bm_n]
   Int_t           Bm_idmubac[100];   //[Bm_n]
   Int_t           Bm_istop[100];   //[Bm_n]
   Int_t           Bm_error[100];   //[Bm_n]
   Int_t           Bm_readout[100];   //[Bm_n]
   Float_t         Bm_x[100][2][3];   //[Bm_n]
   Float_t         Bm_p[100][2][3];   //[Bm_n]
   Float_t         Bm_chi2[100][2];   //[Bm_n]
   Float_t         Bm_dca[100][2];   //[Bm_n]
   Float_t         Bm_gcov[100][2][15];   //[Bm_n]
   Float_t         Bm_fcov[100][2][10];   //[Bm_n]
   Float_t         Bm_resloc[100][2][4];   //[Bm_n]
   Float_t         Bm_prob[100][2];   //[Bm_n]
   Float_t         Bm_zpen[100][2];   //[Bm_n]
   Float_t         Bm_dlh[100];   //[Bm_n]
   Int_t           Bm_mubac_n;
   Int_t           Bm_mubac_hit[750];   //[Bm_mubac_n]
   Int_t           Bm_mubac_pad[750];   //[Bm_mubac_n]
   Int_t           Bm_mubac_unit[750];   //[Bm_mubac_n]
   Int_t           Bm_mubac_hp1[750];   //[Bm_mubac_n]
   Int_t           Bm_mubac_hp2[750];   //[Bm_mubac_n]
   Float_t         Bm_mubac_xyz[750][3];   //[Bm_mubac_n]
   Float_t         Bm_mubac_dxyz[750][3];   //[Bm_mubac_n]
   Float_t         Bm_mubac_cos[750][3];   //[Bm_mubac_n]
   Float_t         Bm_mubac_plf[750][5][3];   //[Bm_mubac_n]

   // List of branches
   TBranch        *b_RUNNR;   //!
   TBranch        *b_EVENTNR;   //!
   TBranch        *b_EVTAKE;   //!
   TBranch        *b_EVTAKE_iwant;   //!
   TBranch        *b_MVDTAKE;   //!
   TBranch        *b_STTTAKE;   //!
   TBranch        *b_TPOLTAKE;   //!
   TBranch        *b_LPOLTAKE;   //!
   TBranch        *b_FMUTAKE;   //!
   TBranch        *b_MBTAKE;   //!
   TBranch        *b_TAG6TAKE;   //!
   TBranch        *b_FLTW;   //!
   TBranch        *b_FLTPSW;   //!
   TBranch        *b_FLTfl;   //!
   TBranch        *b_GSLT_global;   //!
   TBranch        *b_SLTW;   //!
   TBranch        *b_SLTUPW;   //!
   TBranch        *b_TLTW;   //!
   TBranch        *b_DSTW;   //!
   TBranch        *b_FLTPSFCW;   //!
   TBranch        *b_BAC_etot;   //!
   TBranch        *b_BAC_etot_o2r;   //!
   TBranch        *b_BAC_npad;   //!
   TBranch        *b_BAC_npad_o2r;   //!
   TBranch        *b_BAC_et;   //!
   TBranch        *b_BAC_px;   //!
   TBranch        *b_BAC_py;   //!
   TBranch        *b_NBACMU;   //!
   TBranch        *b_Mubac_xyz;   //!
   TBranch        *b_Mubac_dxyz;   //!
   TBranch        *b_Mubac_cos;   //!
   TBranch        *b_Mubac_dcos;   //!
   TBranch        *b_Mubac_eloss;   //!
   TBranch        *b_Mubac_deloss;   //!
   TBranch        *b_Mubac_unit;   //!
   TBranch        *b_Mubac_dim;   //!
   TBranch        *b_Mubac_quality;   //!
   TBranch        *b_Ahit;   //!
   TBranch        *b_Pad;   //!
   TBranch        *b_BITWORD;   //!
   TBranch        *b_calib_idcalscheme;   //!
   TBranch        *b_CAL_px;   //!
   TBranch        *b_CAL_py;   //!
   TBranch        *b_CAL_pz;   //!
   TBranch        *b_CAL_E;   //!
   TBranch        *b_CAL_Et;   //!
   TBranch        *b_CAL_Empz;   //!
   TBranch        *b_CAL_Pt;   //!
   TBranch        *b_CAL_phi;   //!
   TBranch        *b_REmc;   //!
   TBranch        *b_BEmc;   //!
   TBranch        *b_FEmc;   //!
   TBranch        *b_RHac;   //!
   TBranch        *b_BHac;   //!
   TBranch        *b_FHac;   //!
   TBranch        *b_BHac2;   //!
   TBranch        *b_FHac2;   //!
   TBranch        *b_NFEMC;   //!
   TBranch        *b_NFHAC1;   //!
   TBranch        *b_NFHAC2;   //!
   TBranch        *b_NBEMC;   //!
   TBranch        *b_NBHAC1;   //!
   TBranch        *b_NBHAC2;   //!
   TBranch        *b_NREMC;   //!
   TBranch        *b_NRHAC;   //!
   TBranch        *b_CAL_Tf;   //!
   TBranch        *b_CAL_Tb;   //!
   TBranch        *b_CAL_Tr;   //!
   TBranch        *b_CAL_Tg;   //!
   TBranch        *b_CAL_Tu;   //!
   TBranch        *b_CAL_Td;   //!
   TBranch        *b_CAL_Tu_E;   //!
   TBranch        *b_CAL_Td_E;   //!
   TBranch        *b_CAL_Tu_n;   //!
   TBranch        *b_CAL_Td_n;   //!
   TBranch        *b_Etamax_ce;   //!
   TBranch        *b_Etamax_ce4;   //!
   TBranch        *b_CAL_Et10;   //!
   TBranch        *b_Mtrknoe_pi;   //!
   TBranch        *b_Mtrknoe_K;   //!
   TBranch        *b_E_HK;   //!
   TBranch        *b_UnmEn_pi;   //!
   TBranch        *b_UnmEn_k;   //!
   TBranch        *b_SparkF;   //!
   TBranch        *b_PEX1IR;   //!
   TBranch        *b_ET1IR;   //!
   TBranch        *b_ETEX1IR;   //!
   TBranch        *b_PEX2IR;   //!
   TBranch        *b_ET2IR;   //!
   TBranch        *b_ETEX2IR;   //!
   TBranch        *b_PERCIR;   //!
   TBranch        *b_ETRCIR;   //!
   TBranch        *b_cc_Had_0;   //!
   TBranch        *b_cc_Gamma_0;   //!
   TBranch        *b_cc_CeHMom;   //!
   TBranch        *b_cc_ZuHMom;   //!
   TBranch        *b_cc_CCHMom;   //!
   TBranch        *b_CC_Pt;   //!
   TBranch        *b_CC_Et;   //!
   TBranch        *b_CC_EmPz;   //!
   TBranch        *b_CC_gamma;   //!
   TBranch        *b_CC_yjb;   //!
   TBranch        *b_CC_Q2jb;   //!
   TBranch        *b_CC_xjb;   //!
   TBranch        *b_cc_ETAMAX;   //!
   TBranch        *b_cc_EEMC;   //!
   TBranch        *b_cc_EHAC1;   //!
   TBranch        *b_cc_EHAC2;   //!
   TBranch        *b_cc_EMAXCO;   //!
   TBranch        *b_cc_NEMC;   //!
   TBranch        *b_cc_NHAC1;   //!
   TBranch        *b_cc_NHAC2;   //!
   TBranch        *b_cc_FClus_dt;   //!
   TBranch        *b_cc_FClus_dm;   //!
   TBranch        *b_cc_FClus_Et;   //!
   TBranch        *b_cc_FClus_E;   //!
   TBranch        *b_cc_RClus_asoE;   //!
   TBranch        *b_cc_VapVpCELL;   //!
   TBranch        *b_cc_VapVpZU;   //!
   TBranch        *b_cc_VapVpCAC;   //!
   TBranch        *b_nlepton;   //!
   TBranch        *b_nradpho;   //!
   TBranch        *b_nboson;   //!
   TBranch        *b_nquark;   //!
   TBranch        *b_ngluon;   //!
   TBranch        *b_idscatlep;   //!
   TBranch        *b_idradpho;   //!
   TBranch        *b_idboson;   //!
   TBranch        *b_idquark;   //!
   TBranch        *b_idgluon;   //!
   TBranch        *b_dolepton;   //!
   TBranch        *b_doradpho;   //!
   TBranch        *b_doboson;   //!
   TBranch        *b_doquark;   //!
   TBranch        *b_dogluon;   //!
   TBranch        *b_plepton;   //!
   TBranch        *b_pradpho;   //!
   TBranch        *b_pboson;   //!
   TBranch        *b_pquark;   //!
   TBranch        *b_pgluon;   //!
   TBranch        *b_nqg;   //!
   TBranch        *b_quarkprt;   //!
   TBranch        *b_Idqg;   //!
   TBranch        *b_Doqg;   //!
   TBranch        *b_Prtqg;   //!
   TBranch        *b_Pqg;   //!
   TBranch        *b_EmNcand;   //!
   TBranch        *b_EmError;   //!
   TBranch        *b_Emprob;   //!
   TBranch        *b_Empos;   //!
   TBranch        *b_Emcalpos;   //!
   TBranch        *b_Emcalene;   //!
   TBranch        *b_Emein;   //!
   TBranch        *b_Emenin;   //!
   TBranch        *b_Emecorr;   //!
   TBranch        *b_Emth;   //!
   TBranch        *b_Emph;   //!
   TBranch        *b_Empt;   //!
   TBranch        *b_Emxdet;   //!
   TBranch        *b_Emydet;   //!
   TBranch        *b_Emtrknr;   //!
   TBranch        *b_Emnrsl;   //!
   TBranch        *b_Emdca;   //!
   TBranch        *b_Emdcabeam;   //!
   TBranch        *b_Emtrkp;   //!
   TBranch        *b_Emtrkth;   //!
   TBranch        *b_Emtrkph;   //!
   TBranch        *b_Emtrkq;   //!
   TBranch        *b_Emtrkdme;   //!
   TBranch        *b_Emtrkdce;   //!
   TBranch        *b_Emtrkpos;   //!
   TBranch        *b_Emsrtf;   //!
   TBranch        *b_Emsrtquad;   //!
   TBranch        *b_Emhesf;   //!
   TBranch        *b_Emcorrcode;   //!
   TBranch        *b_Emsrtpos;   //!
   TBranch        *b_Emsrtene;   //!
   TBranch        *b_Emhespos;   //!
   TBranch        *b_Emhesene;   //!
   TBranch        *b_Emhesr;   //!
   TBranch        *b_Emprsene;   //!
   TBranch        *b_Emccet;   //!
   TBranch        *b_Emccempz;   //!
   TBranch        *b_Emetamax;   //!
   TBranch        *b_Emcehmom;   //!
   TBranch        *b_Emzuhmom;   //!
   TBranch        *b_Emcchmom;   //!
   TBranch        *b_Emxel;   //!
   TBranch        *b_Emyel;   //!
   TBranch        *b_Emq2el;   //!
   TBranch        *b_Emxda;   //!
   TBranch        *b_Emyda;   //!
   TBranch        *b_Emq2da;   //!
   TBranch        *b_Emxda_cell;   //!
   TBranch        *b_Emyda_cell;   //!
   TBranch        *b_Emq2da_cell;   //!
   TBranch        *b_Emxjb;   //!
   TBranch        *b_Emyjb;   //!
   TBranch        *b_Emq2jb;   //!
   TBranch        *b_Emxjb_cell;   //!
   TBranch        *b_Emyjb_cell;   //!
   TBranch        *b_Emq2jb_cell;   //!
   TBranch        *b_Emfemc;   //!
   TBranch        *b_Emcalprob;   //!
   TBranch        *b_Eminctd;   //!
   TBranch        *b_Emnneartrk;   //!
   TBranch        *b_Emetneartrk;   //!
   TBranch        *b_Emtrkmatchi2;   //!
   TBranch        *b_Emfmaxbemc;   //!
   TBranch        *b_Emfmaxremc;   //!
   TBranch        *b_Emfmaxfemc;   //!
   TBranch        *b_Emdeltaz;   //!
   TBranch        *b_Emdeltax;   //!
   TBranch        *b_Emdeltay;   //!
   TBranch        *b_E5Ncand;   //!
   TBranch        *b_E5Error;   //!
   TBranch        *b_E5prob;   //!
   TBranch        *b_E5pos;   //!
   TBranch        *b_E5calpos;   //!
   TBranch        *b_E5calene;   //!
   TBranch        *b_E5ein;   //!
   TBranch        *b_E5enin;   //!
   TBranch        *b_E5ecorr;   //!
   TBranch        *b_E5th;   //!
   TBranch        *b_E5ph;   //!
   TBranch        *b_E5pt;   //!
   TBranch        *b_E5xdet;   //!
   TBranch        *b_E5ydet;   //!
   TBranch        *b_E5trknr;   //!
   TBranch        *b_E5nrsl;   //!
   TBranch        *b_E5dca;   //!
   TBranch        *b_E5dcabeam;   //!
   TBranch        *b_E5trkp;   //!
   TBranch        *b_E5trkth;   //!
   TBranch        *b_E5trkph;   //!
   TBranch        *b_E5trkq;   //!
   TBranch        *b_E5trkdme;   //!
   TBranch        *b_E5trkdce;   //!
   TBranch        *b_E5trkpos;   //!
   TBranch        *b_E5srtf;   //!
   TBranch        *b_E5srtquad;   //!
   TBranch        *b_E5hesf;   //!
   TBranch        *b_E5corrcode;   //!
   TBranch        *b_E5srtpos;   //!
   TBranch        *b_E5srtene;   //!
   TBranch        *b_E5hespos;   //!
   TBranch        *b_E5hesene;   //!
   TBranch        *b_E5hesr;   //!
   TBranch        *b_E5prsene;   //!
   TBranch        *b_E5ccet;   //!
   TBranch        *b_E5ccempz;   //!
   TBranch        *b_E5etamax;   //!
   TBranch        *b_E5cehmom;   //!
   TBranch        *b_E5zuhmom;   //!
   TBranch        *b_E5cchmom;   //!
   TBranch        *b_E5xel;   //!
   TBranch        *b_E5yel;   //!
   TBranch        *b_E5q2el;   //!
   TBranch        *b_E5xda;   //!
   TBranch        *b_E5yda;   //!
   TBranch        *b_E5q2da;   //!
   TBranch        *b_E5xda_cell;   //!
   TBranch        *b_E5yda_cell;   //!
   TBranch        *b_E5q2da_cell;   //!
   TBranch        *b_E5xjb;   //!
   TBranch        *b_E5yjb;   //!
   TBranch        *b_E5q2jb;   //!
   TBranch        *b_E5xjb_cell;   //!
   TBranch        *b_E5yjb_cell;   //!
   TBranch        *b_E5q2jb_cell;   //!
   TBranch        *b_E5femc;   //!
   TBranch        *b_E5calprob;   //!
   TBranch        *b_E5inctd;   //!
   TBranch        *b_E5nneartrk;   //!
   TBranch        *b_E5etneartrk;   //!
   TBranch        *b_E5trkmatchi2;   //!
   TBranch        *b_E5fmaxbemc;   //!
   TBranch        *b_E5fmaxremc;   //!
   TBranch        *b_E5fmaxfemc;   //!
   TBranch        *b_E5deltaz;   //!
   TBranch        *b_E5deltax;   //!
   TBranch        *b_E5deltay;   //!
   TBranch        *b_nPart;   //!
   TBranch        *b_idLepton;   //!
   TBranch        *b_idPhoton;   //!
   TBranch        *b_Part_id;   //!
   TBranch        *b_Part_prt;   //!
   TBranch        *b_Part_p;   //!
   TBranch        *b_Nmu;   //!
   TBranch        *b_Muqual;   //!
   TBranch        *b_Mucharge;   //!
   TBranch        *b_Mupt;   //!
   TBranch        *b_Muth;   //!
   TBranch        *b_Muph;   //!
   TBranch        *b_Mup;   //!
   TBranch        *b_Muperr;   //!
   TBranch        *b_Mutrfl;   //!
   TBranch        *b_Mutrid;   //!
   TBranch        *b_Muvcid;   //!
   TBranch        *b_Muztid;   //!
   TBranch        *b_Mustid;   //!
   TBranch        *b_Muvtxfl;   //!
   TBranch        *b_Muvtxid;   //!
   TBranch        *b_Muglomu;   //!
   TBranch        *b_Mubremat;   //!
   TBranch        *b_Mubacmat;   //!
   TBranch        *b_Mumubac;   //!
   TBranch        *b_Mumamma;   //!
   TBranch        *b_Mumpmat;   //!
   TBranch        *b_Mumufo;   //!
   TBranch        *b_Mumip;   //!
   TBranch        *b_Mumv;   //!
   TBranch        *b_Mucalfl;   //!
   TBranch        *b_Mucalene;   //!
   TBranch        *b_Muhac2;   //!
   TBranch        *b_Muzufid;   //!
   TBranch        *b_Mupmip;   //!
   TBranch        *b_Muhene;   //!
   TBranch        *b_Mutime;   //!
   TBranch        *b_Muchfl;   //!
   TBranch        *b_Muchid;   //!
   TBranch        *b_Mupmat;   //!
   TBranch        *b_Mundof;   //!
   TBranch        *b_Munphi;   //!
   TBranch        *b_Muz;   //!
   TBranch        *b_Muprec;   //!
   TBranch        *b_Mubmchi2;   //!
   TBranch        *b_Mubmbac;   //!
   TBranch        *b_Mubacdca;   //!
   TBranch        *b_Mubacdimq;   //!
   TBranch        *b_Mudxy;   //!
   TBranch        *b_Mudz;   //!
   TBranch        *b_Muisol;   //!
   TBranch        *b_Munis;   //!
   TBranch        *b_Muisdrmip;   //!
   TBranch        *b_Muisetmip;   //!
   TBranch        *b_Muistumip;   //!
   TBranch        *b_Mujetfl_a;   //!
   TBranch        *b_Mujetid_a;   //!
   TBranch        *b_Mujetdr_a;   //!
   TBranch        *b_Mujetpt_a;   //!
   TBranch        *b_Mujetdr2_a;   //!
   TBranch        *b_Mujetpt2_a;   //!
   TBranch        *b_Muhjet_id;   //!
   TBranch        *b_Mujetfl_b;   //!
   TBranch        *b_Mujetid_b;   //!
   TBranch        *b_Mujetdr_b;   //!
   TBranch        *b_Mujetpt_b;   //!
   TBranch        *b_Mujetdr2_b;   //!
   TBranch        *b_Mujetpt2_b;   //!
   TBranch        *b_Mujetfl_c;   //!
   TBranch        *b_Mujetid_c;   //!
   TBranch        *b_Mujetdr_c;   //!
   TBranch        *b_Mujetpt_c;   //!
   TBranch        *b_Mujetdr2_c;   //!
   TBranch        *b_Mujetpt2_c;   //!
   TBranch        *b_Mujetfl_d;   //!
   TBranch        *b_Mujetid_d;   //!
   TBranch        *b_Mujetdr_d;   //!
   TBranch        *b_Mujetpt_d;   //!
   TBranch        *b_Mujetdr2_d;   //!
   TBranch        *b_Mujetpt2_d;   //!
   TBranch        *b_Muick;   //!
   TBranch        *b_Mupartyp;   //!
   TBranch        *b_Mumc_p;   //!
   TBranch        *b_Mudirtyp;   //!
   TBranch        *b_Mumc_d;   //!
   TBranch        *b_Muqtyp;   //!
   TBranch        *b_Mumc_q;   //!
   TBranch        *b_Mutruefl;   //!
   TBranch        *b_Mudecdist;   //!
   TBranch        *b_KT_NJET_A;   //!
   TBranch        *b_Kt_etjet_a;   //!
   TBranch        *b_Kt_etajet_a;   //!
   TBranch        *b_Kt_phijet_a;   //!
   TBranch        *b_Kt_masjet_a;   //!
   TBranch        *b_KT_NJET_B;   //!
   TBranch        *b_Kt_etjet_b;   //!
   TBranch        *b_Kt_etajet_b;   //!
   TBranch        *b_Kt_phijet_b;   //!
   TBranch        *b_Kt_masjet_b;   //!
   TBranch        *b_KT_BST_B;   //!
   TBranch        *b_KT_NJET_C;   //!
   TBranch        *b_Kt_etjet_c;   //!
   TBranch        *b_Kt_etajet_c;   //!
   TBranch        *b_Kt_phijet_c;   //!
   TBranch        *b_Kt_masjet_c;   //!
   TBranch        *b_KT_BST_C;   //!
   TBranch        *b_KT_NJET_D;   //!
   TBranch        *b_Kt_etjet_d;   //!
   TBranch        *b_Kt_etajet_d;   //!
   TBranch        *b_Kt_phijet_d;   //!
   TBranch        *b_Kt_masjet_d;   //!
   TBranch        *b_KT_BST_D;   //!
   TBranch        *b_KT_NJET_E;   //!
   TBranch        *b_Kt_etjet_e;   //!
   TBranch        *b_Kt_etajet_e;   //!
   TBranch        *b_Kt_phijet_e;   //!
   TBranch        *b_KT_BST_E;   //!
   TBranch        *b_KT_NJET_F;   //!
   TBranch        *b_Kt_etjet_f;   //!
   TBranch        *b_Kt_etajet_f;   //!
   TBranch        *b_Kt_phijet_f;   //!
   TBranch        *b_KT_BST_F;   //!
   TBranch        *b_KT_NJET_G;   //!
   TBranch        *b_Kt_etjet_g;   //!
   TBranch        *b_Kt_etajet_g;   //!
   TBranch        *b_Kt_phijet_g;   //!
   TBranch        *b_KT_BST_G;   //!
   TBranch        *b_KT_NJET_H;   //!
   TBranch        *b_Kt_etjet_h;   //!
   TBranch        *b_Kt_etajet_h;   //!
   TBranch        *b_Kt_phijet_h;   //!
   TBranch        *b_KT_BST_H;   //!
   TBranch        *b_KT_NJET_I;   //!
   TBranch        *b_Kt_etjet_i;   //!
   TBranch        *b_Kt_etajet_i;   //!
   TBranch        *b_Kt_phijet_i;   //!
   TBranch        *b_KT_NJET_J;   //!
   TBranch        *b_Kt_etjet_j;   //!
   TBranch        *b_Kt_etajet_j;   //!
   TBranch        *b_Kt_phijet_j;   //!
   TBranch        *b_KT_NJET_K;   //!
   TBranch        *b_Kt_etjet_k;   //!
   TBranch        *b_Kt_etajet_k;   //!
   TBranch        *b_Kt_phijet_k;   //!
   TBranch        *b_KT_BST_K;   //!
   TBranch        *b_KT_NJET_L;   //!
   TBranch        *b_Kt_etjet_l;   //!
   TBranch        *b_Kt_etajet_l;   //!
   TBranch        *b_Kt_phijet_l;   //!
   TBranch        *b_KT_BST_L;   //!
   TBranch        *b_CONE_NJET;   //!
   TBranch        *b_Cone_etjet;   //!
   TBranch        *b_Cone_etajet;   //!
   TBranch        *b_Cone_phijet;   //!
   TBranch        *b_ELumie;   //!
   TBranch        *b_XLumie;   //!
   TBranch        *b_YLumie;   //!
   TBranch        *b_ELumig;   //!
   TBranch        *b_XLumig;   //!
   TBranch        *b_YLumig;   //!
   TBranch        *b_nmcdstar;   //!
   TBranch        *b_Imcdstar;   //!
   TBranch        *b_Ptmcdstar;   //!
   TBranch        *b_Etamcdstar;   //!
   TBranch        *b_Phimcdstar;   //!
   TBranch        *b_ndsd02;   //!
   TBranch        *b_Pdsd02;   //!
   TBranch        *b_Tdsd02;   //!
   TBranch        *b_Fdsd02;   //!
   TBranch        *b_Kdsd02;   //!
   TBranch        *b_Pdsps2;   //!
   TBranch        *b_Tdsps2;   //!
   TBranch        *b_Fdsps2;   //!
   TBranch        *b_Pmds2;   //!
   TBranch        *b_Kmds2;   //!
   TBranch        *b_Nmds2;   //!
   TBranch        *b_ndsd04;   //!
   TBranch        *b_Pdsd04;   //!
   TBranch        *b_Tdsd04;   //!
   TBranch        *b_Fdsd04;   //!
   TBranch        *b_Kdsd04;   //!
   TBranch        *b_Mdsd04;   //!
   TBranch        *b_Pdsps4;   //!
   TBranch        *b_Tdsps4;   //!
   TBranch        *b_Fdsps4;   //!
   TBranch        *b_Pmds4;   //!
   TBranch        *b_Kmds4;   //!
   TBranch        *b_Nmds4;   //!
   TBranch        *b_ndzd02;   //!
   TBranch        *b_Pdzd02;   //!
   TBranch        *b_Tdzd02;   //!
   TBranch        *b_Fdzd02;   //!
   TBranch        *b_Kdzd02;   //!
   TBranch        *b_Pdzga2;   //!
   TBranch        *b_Tdzga2;   //!
   TBranch        *b_Fdzga2;   //!
   TBranch        *b_Pmdz2;   //!
   TBranch        *b_Kmdz2;   //!
   TBranch        *b_Nmdz2;   //!
   TBranch        *b_ndzd04;   //!
   TBranch        *b_Pdzd04;   //!
   TBranch        *b_Tdzd04;   //!
   TBranch        *b_Fdzd04;   //!
   TBranch        *b_Kdzd04;   //!
   TBranch        *b_Mdzd04;   //!
   TBranch        *b_Pdzga4;   //!
   TBranch        *b_Tdzga4;   //!
   TBranch        *b_Fdzga4;   //!
   TBranch        *b_Pmdz4;   //!
   TBranch        *b_Kmdz4;   //!
   TBranch        *b_Nmdz4;   //!
   TBranch        *b_nd02;   //!
   TBranch        *b_Pd02;   //!
   TBranch        *b_Td02;   //!
   TBranch        *b_Fd02;   //!
   TBranch        *b_Kd02;   //!
   TBranch        *b_Pmd02;   //!
   TBranch        *b_Kmd02;   //!
   TBranch        *b_Nmd02;   //!
   TBranch        *b_nd04;   //!
   TBranch        *b_Pd04;   //!
   TBranch        *b_Td04;   //!
   TBranch        *b_Fd04;   //!
   TBranch        *b_Kd04;   //!
   TBranch        *b_Md04;   //!
   TBranch        *b_Pmd04;   //!
   TBranch        *b_Kmd04;   //!
   TBranch        *b_Nmd04;   //!
   TBranch        *b_ndsdch;   //!
   TBranch        *b_Pdsdch;   //!
   TBranch        *b_Tdsdch;   //!
   TBranch        *b_Fdsdch;   //!
   TBranch        *b_Kdsdch;   //!
   TBranch        *b_Mdsdch;   //!
   TBranch        *b_Pdsgah;   //!
   TBranch        *b_Tdsgah;   //!
   TBranch        *b_Fdsgah;   //!
   TBranch        *b_Pmdsh;   //!
   TBranch        *b_Kmdsh;   //!
   TBranch        *b_Nmdsh;   //!
   TBranch        *b_ndch;   //!
   TBranch        *b_Pdch;   //!
   TBranch        *b_Tdch;   //!
   TBranch        *b_Fdch;   //!
   TBranch        *b_Kdch;   //!
   TBranch        *b_Mdch;   //!
   TBranch        *b_pmdch;   //!
   TBranch        *b_kmdch;   //!
   TBranch        *b_nmdch;   //!
   TBranch        *b_ndtdss;   //!
   TBranch        *b_Pdtdss;   //!
   TBranch        *b_Tdtdss;   //!
   TBranch        *b_Fdtdss;   //!
   TBranch        *b_Kdtdss;   //!
   TBranch        *b_Mdtdss;   //!
   TBranch        *b_Pdtgas;   //!
   TBranch        *b_Tdtgas;   //!
   TBranch        *b_Fdtgas;   //!
   TBranch        *b_Pmdts;   //!
   TBranch        *b_Kmdts;   //!
   TBranch        *b_Nmdts;   //!
   TBranch        *b_ndss;   //!
   TBranch        *b_Pdss;   //!
   TBranch        *b_Tdss;   //!
   TBranch        *b_Fdss;   //!
   TBranch        *b_Kdss;   //!
   TBranch        *b_Mdss;   //!
   TBranch        *b_Pmdss;   //!
   TBranch        *b_Kmdss;   //!
   TBranch        *b_Nmdss;   //!
   TBranch        *b_ndla;   //!
   TBranch        *b_Pdla;   //!
   TBranch        *b_Tdla;   //!
   TBranch        *b_Fdla;   //!
   TBranch        *b_Kdla;   //!
   TBranch        *b_Mdla;   //!
   TBranch        *b_Pmdla;   //!
   TBranch        *b_Kmdla;   //!
   TBranch        *b_Nmdla;   //!
   TBranch        *b_MC_EZ;   //!
   TBranch        *b_MC_ESUM;   //!
   TBranch        *b_MC_ETCONE;   //!
   TBranch        *b_MC_ERCAL;   //!
   TBranch        *b_MC_EL;   //!
   TBranch        *b_MC_EP;   //!
   TBranch        *b_MC_X;   //!
   TBranch        *b_MC_Y;   //!
   TBranch        *b_MC_Q2;   //!
   TBranch        *b_MC_MU;   //!
   TBranch        *b_MC_PT;   //!
   TBranch        *b_MC_XPRO;   //!
   TBranch        *b_MC_XGAM;   //!
   TBranch        *b_MC_XPOM;   //!
   TBranch        *b_MC_BETA;   //!
   TBranch        *b_MC_T;   //!
   TBranch        *b_MC_IDL;   //!
   TBranch        *b_MC_PIDL;   //!
   TBranch        *b_MC_PIDP;   //!
   TBranch        *b_MC_IDFSL;   //!
   TBranch        *b_MC_PFSL;   //!
   TBranch        *b_MC_PFSPH;   //!
   TBranch        *b_MC_VTX;   //!
   TBranch        *b_MC_ICHNN;   //!
   TBranch        *b_MC_Q2_CR;   //!
   TBranch        *b_MC_X_CR;   //!
   TBranch        *b_MCVtx;   //!
   TBranch        *b_simrun;   //!
   TBranch        *b_SiNcand;   //!
   TBranch        *b_SiError;   //!
   TBranch        *b_Siprob;   //!
   TBranch        *b_Sipos;   //!
   TBranch        *b_Sicalpos;   //!
   TBranch        *b_Sicalene;   //!
   TBranch        *b_Siein;   //!
   TBranch        *b_Sienin;   //!
   TBranch        *b_Siecorr;   //!
   TBranch        *b_Sith;   //!
   TBranch        *b_Siph;   //!
   TBranch        *b_Sipt;   //!
   TBranch        *b_Sixdet;   //!
   TBranch        *b_Siydet;   //!
   TBranch        *b_Sitrknr;   //!
   TBranch        *b_Sinrsl;   //!
   TBranch        *b_Sidca;   //!
   TBranch        *b_Sitrkp;   //!
   TBranch        *b_Sitrkth;   //!
   TBranch        *b_Sitrkph;   //!
   TBranch        *b_Sitrkq;   //!
   TBranch        *b_Sitrkdme;   //!
   TBranch        *b_Sitrkpos;   //!
   TBranch        *b_Sisrtf;   //!
   TBranch        *b_Sisrtquad;   //!
   TBranch        *b_Sihesf;   //!
   TBranch        *b_Sicorrcode;   //!
   TBranch        *b_Sisrtpos;   //!
   TBranch        *b_Sisrtene;   //!
   TBranch        *b_Sihespos;   //!
   TBranch        *b_Sihesene;   //!
   TBranch        *b_Sihesr;   //!
   TBranch        *b_Siprsene;   //!
   TBranch        *b_Siccet;   //!
   TBranch        *b_Siccempz;   //!
   TBranch        *b_Sietamax;   //!
   TBranch        *b_Sicehmom;   //!
   TBranch        *b_Sizuhmom;   //!
   TBranch        *b_Sicchmom;   //!
   TBranch        *b_Sixel;   //!
   TBranch        *b_Siyel;   //!
   TBranch        *b_Siq2el;   //!
   TBranch        *b_Sixda;   //!
   TBranch        *b_Siyda;   //!
   TBranch        *b_Siq2da;   //!
   TBranch        *b_Sixda_cell;   //!
   TBranch        *b_Siyda_cell;   //!
   TBranch        *b_Siq2da_cell;   //!
   TBranch        *b_Sixjb;   //!
   TBranch        *b_Siyjb;   //!
   TBranch        *b_Siq2jb;   //!
   TBranch        *b_Sixjb_cell;   //!
   TBranch        *b_Siyjb_cell;   //!
   TBranch        *b_Siq2jb_cell;   //!
   TBranch        *b_nBPchn;   //!
   TBranch        *b_Bpmip;   //!
   TBranch        *b_Bpxyz;   //!
   TBranch        *b_Bptim;   //!
   TBranch        *b_tsu_halo;   //!
   TBranch        *b_nv0lite;   //!
   TBranch        *b_Tsecvtx;   //!
   TBranch        *b_Tsecvtx_chi;   //!
   TBranch        *b_Tsecvtx_dca;   //!
   TBranch        *b_Tsecvtx_collin2;   //!
   TBranch        *b_Tsecvtx_collin3;   //!
   TBranch        *b_Tsecvtx_dlen2;   //!
   TBranch        *b_Tsecvtx_dlen3;   //!
   TBranch        *b_Tq1;   //!
   TBranch        *b_Tq2;   //!
   TBranch        *b_Ent1;   //!
   TBranch        *b_Ent2;   //!
   TBranch        *b_Tt1_layinn;   //!
   TBranch        *b_Tt1_layout;   //!
   TBranch        *b_Tt2_layinn;   //!
   TBranch        *b_Tt2_layout;   //!
   TBranch        *b_Tt1_id;   //!
   TBranch        *b_Tt2_id;   //!
   TBranch        *b_Stt1;   //!
   TBranch        *b_Stt2;   //!
   TBranch        *b_Tt1_ndof;   //!
   TBranch        *b_Tt2_ndof;   //!
   TBranch        *b_Tp1;   //!
   TBranch        *b_Tp2;   //!
   TBranch        *b_Tpk;   //!
   TBranch        *b_Tinvmass_lambda;   //!
   TBranch        *b_Tinvmass_alambda;   //!
   TBranch        *b_Tinvmass_k0;   //!
   TBranch        *b_Tinvmass_ee;   //!
   TBranch        *b_Ntrkvtx;   //!
   TBranch        *b_Xvtx;   //!
   TBranch        *b_Yvtx;   //!
   TBranch        *b_Zvtx;   //!
   TBranch        *b_Chivtx;   //!
   TBranch        *b_Nsecvtx;   //!
   TBranch        *b_Xsecvtx;   //!
   TBranch        *b_Ysecvtx;   //!
   TBranch        *b_Zsecvtx;   //!
   TBranch        *b_Chisecvtx;   //!
   TBranch        *b_Fetatr;   //!
   TBranch        *b_Betatr;   //!
   TBranch        *b_Pt_tr;   //!
   TBranch        *b_Empz_tr_pi;   //!
   TBranch        *b_Et_tr;   //!
   TBranch        *b_E_tr_pi;   //!
   TBranch        *b_phi_tr;   //!
   TBranch        *b_zvtx_fcal;   //!
   TBranch        *b_fcal_NrGoodCells;   //!
   TBranch        *b_fcal_VzErr;   //!
   TBranch        *b_V_H_px_zu;   //!
   TBranch        *b_V_H_py_zu;   //!
   TBranch        *b_V_H_pz_zu;   //!
   TBranch        *b_V_H_E_zu;   //!
   TBranch        *b_Etamax_zu;   //!
   TBranch        *b_Etamax_zu4;   //!
   TBranch        *b_Fgap;   //!
   TBranch        *b_Bgap;   //!
   TBranch        *b_Nzufos;   //!
   TBranch        *b_Tufo;   //!
   TBranch        *b_Zufo_bsp;   //!
   TBranch        *b_Zufo;   //!
   TBranch        *b_Cufo;   //!
   TBranch        *b_Zufoecal;   //!
   TBranch        *b_Zufoeemc;   //!
   TBranch        *b_nT;   //!
   TBranch        *b_Vcthid;   //!
   TBranch        *b_Qtr;   //!
   TBranch        *b_Swmtr;   //!
   TBranch        *b_Qlttr;   //!
   TBranch        *b_Mtri;   //!
   TBranch        *b_Wtri;   //!
   TBranch        *b_Ptr;   //!
   TBranch        *b_Dptr;   //!
   TBranch        *b_Thtr;   //!
   TBranch        *b_Phtr;   //!
   TBranch        *b_Dist_istr;   //!
   TBranch        *b_trk_ntracks;   //!
   TBranch        *b_Trk_type;   //!
   TBranch        *b_ntrack_type;   //!
   TBranch        *b_def_trk_type;   //!
   TBranch        *b_Trk_id;   //!
   TBranch        *b_Trk_id2;   //!
   TBranch        *b_Trk_px;   //!
   TBranch        *b_Trk_py;   //!
   TBranch        *b_Trk_pz;   //!
   TBranch        *b_Trk_charge;   //!
   TBranch        *b_Trk_vtx;   //!
   TBranch        *b_Trk_prim_vtx;   //!
   TBranch        *b_Trk_sec_vtx;   //!
   TBranch        *b_Trk_vxid;   //!
   TBranch        *b_Trk_nzbyt;   //!
   TBranch        *b_Trk_naxial;   //!
   TBranch        *b_Trk_nstereo;   //!
   TBranch        *b_Trk_ndof;   //!
   TBranch        *b_Trk_layinner;   //!
   TBranch        *b_Trk_layouter;   //!
   TBranch        *b_Trk_dedxctd;   //!
   TBranch        *b_Trk_dedxctdcr;   //!
   TBranch        *b_Trk_dedxctderr;   //!
   TBranch        *b_Trk_dedxctdnh;   //!
   TBranch        *b_Trk_dedxctdsaturated;   //!
   TBranch        *b_Trk_chi2;   //!
   TBranch        *b_Trk_vchi2;   //!
   TBranch        *b_Trk_nbr;   //!
   TBranch        *b_Trk_nbz;   //!
   TBranch        *b_Trk_nwu;   //!
   TBranch        *b_Trk_nwv;   //!
   TBranch        *b_Trk_nstt;   //!
   TBranch        *b_Trk_dedxmvd;   //!
   TBranch        *b_Trk_imppar;   //!
   TBranch        *b_Trk_imperr;   //!
   TBranch        *b_Trk_pca;   //!
   TBranch        *b_Mcmatfmckin_id;   //!
   TBranch        *b_Mcmatpx;   //!
   TBranch        *b_Mcmatpy;   //!
   TBranch        *b_Mcmatpz;   //!
   TBranch        *b_Mcmate;   //!
   TBranch        *b_Mcmatm;   //!
   TBranch        *b_Mcmatcharge;   //!
   TBranch        *b_Mcmatquality;   //!
   TBranch        *b_Mcmattype;   //!
   TBranch        *b_Mcmatsvert_x;   //!
   TBranch        *b_Mcmatsvert_y;   //!
   TBranch        *b_Mcmatsvert_z;   //!
   TBranch        *b_Mcmatmother;   //!
   TBranch        *b_Mcmatmother_px;   //!
   TBranch        *b_Mcmatmother_py;   //!
   TBranch        *b_Mcmatmother_pz;   //!
   TBranch        *b_Mcmatmother_e;   //!
   TBranch        *b_Mcmatmother_m;   //!
   TBranch        *b_Mcmatmother_prt;   //!
   TBranch        *b_nchvtx;   //!
   TBranch        *b_Chvtxpar;   //!
   TBranch        *b_Chvtxcov;   //!
   TBranch        *b_Chchi2;   //!
   TBranch        *b_nchds1;   //!
   TBranch        *b_Ds1ms;   //!
   TBranch        *b_Ds1pm;   //!
   TBranch        *b_Ds1th;   //!
   TBranch        *b_Ds1ph;   //!
   TBranch        *b_D1d0ms;   //!
   TBranch        *b_D1d0pm;   //!
   TBranch        *b_D1d0th;   //!
   TBranch        *b_D1d0ph;   //!
   TBranch        *b_D1kapm;   //!
   TBranch        *b_D1kath;   //!
   TBranch        *b_D1kaph;   //!
   TBranch        *b_D1pipm;   //!
   TBranch        *b_D1pith;   //!
   TBranch        *b_D1piph;   //!
   TBranch        *b_D1pspm;   //!
   TBranch        *b_D1psth;   //!
   TBranch        *b_D1psph;   //!
   TBranch        *b_Ds1trk;   //!
   TBranch        *b_Tds1ka;   //!
   TBranch        *b_Tds1pi;   //!
   TBranch        *b_Tds1ps;   //!
   TBranch        *b_Id1d0vtx;   //!
   TBranch        *b_Ids1rprm;   //!
   TBranch        *b_nchds2;   //!
   TBranch        *b_Ds2ms;   //!
   TBranch        *b_Ds2pm;   //!
   TBranch        *b_Ds2th;   //!
   TBranch        *b_Ds2ph;   //!
   TBranch        *b_D2d0ms;   //!
   TBranch        *b_D2d0pm;   //!
   TBranch        *b_D2d0th;   //!
   TBranch        *b_D2d0ph;   //!
   TBranch        *b_D2kapm;   //!
   TBranch        *b_D2kath;   //!
   TBranch        *b_D2kaph;   //!
   TBranch        *b_D2p1pm;   //!
   TBranch        *b_D2p1th;   //!
   TBranch        *b_D2p1ph;   //!
   TBranch        *b_D2p2pm;   //!
   TBranch        *b_D2p2th;   //!
   TBranch        *b_D2p2ph;   //!
   TBranch        *b_D2p3pm;   //!
   TBranch        *b_D2p3th;   //!
   TBranch        *b_D2p3ph;   //!
   TBranch        *b_D2pspm;   //!
   TBranch        *b_D2psth;   //!
   TBranch        *b_D2psph;   //!
   TBranch        *b_Ds2trk;   //!
   TBranch        *b_Tds2ka;   //!
   TBranch        *b_Tds2p1;   //!
   TBranch        *b_Tds2p2;   //!
   TBranch        *b_Tds2p3;   //!
   TBranch        *b_Tds2ps;   //!
   TBranch        *b_Id2d0vtx;   //!
   TBranch        *b_Ids2rprm;   //!
   TBranch        *b_Ds2rin;   //!
   TBranch        *b_D2maxdca;   //!
   TBranch        *b_nchd0;   //!
   TBranch        *b_D0ms;   //!
   TBranch        *b_D0pm;   //!
   TBranch        *b_D0th;   //!
   TBranch        *b_D0ph;   //!
   TBranch        *b_D0kapm;   //!
   TBranch        *b_D0kath;   //!
   TBranch        *b_D0kaph;   //!
   TBranch        *b_D0pipm;   //!
   TBranch        *b_D0pith;   //!
   TBranch        *b_D0piph;   //!
   TBranch        *b_D0trk;   //!
   TBranch        *b_Td0ka;   //!
   TBranch        *b_Td0pi;   //!
   TBranch        *b_Id0vtx;   //!
   TBranch        *b_Id0rprm;   //!
   TBranch        *b_nchdch;   //!
   TBranch        *b_Dchms;   //!
   TBranch        *b_Dchpm;   //!
   TBranch        *b_Dchth;   //!
   TBranch        *b_Dchph;   //!
   TBranch        *b_Dckapm;   //!
   TBranch        *b_Dckath;   //!
   TBranch        *b_Dckaph;   //!
   TBranch        *b_Dcp1pm;   //!
   TBranch        *b_Dcp1th;   //!
   TBranch        *b_Dcp1ph;   //!
   TBranch        *b_Dcp2pm;   //!
   TBranch        *b_Dcp2th;   //!
   TBranch        *b_Dcp2ph;   //!
   TBranch        *b_Dchtrk;   //!
   TBranch        *b_Tdchka;   //!
   TBranch        *b_Tdchp1;   //!
   TBranch        *b_Tdchp2;   //!
   TBranch        *b_Idchvtx;   //!
   TBranch        *b_Idchrprm;   //!
   TBranch        *b_nchdla;   //!
   TBranch        *b_Dlams;   //!
   TBranch        *b_Dlapm;   //!
   TBranch        *b_Dlath;   //!
   TBranch        *b_Dlaph;   //!
   TBranch        *b_Dlkapm;   //!
   TBranch        *b_Dlkath;   //!
   TBranch        *b_Dlkaph;   //!
   TBranch        *b_Dlprpm;   //!
   TBranch        *b_Dlprth;   //!
   TBranch        *b_Dlprph;   //!
   TBranch        *b_Dlpipm;   //!
   TBranch        *b_Dlpith;   //!
   TBranch        *b_Dlpiph;   //!
   TBranch        *b_Dlatrk;   //!
   TBranch        *b_Tdlaka;   //!
   TBranch        *b_Tdlapr;   //!
   TBranch        *b_Tdlapi;   //!
   TBranch        *b_Idlavtx;   //!
   TBranch        *b_Idlarprm;   //!
   TBranch        *b_nchdss;   //!
   TBranch        *b_Dssms;   //!
   TBranch        *b_Dsspm;   //!
   TBranch        *b_Dssth;   //!
   TBranch        *b_Dssph;   //!
   TBranch        *b_Dsphms;   //!
   TBranch        *b_Dsphpm;   //!
   TBranch        *b_Dsphth;   //!
   TBranch        *b_Dsphph;   //!
   TBranch        *b_Dsk1pm;   //!
   TBranch        *b_Dsk1th;   //!
   TBranch        *b_Dsk1ph;   //!
   TBranch        *b_Dsk2pm;   //!
   TBranch        *b_Dsk2th;   //!
   TBranch        *b_Dsk2ph;   //!
   TBranch        *b_Dspipm;   //!
   TBranch        *b_Dspith;   //!
   TBranch        *b_Dspiph;   //!
   TBranch        *b_Dsstrk;   //!
   TBranch        *b_Tdssk1;   //!
   TBranch        *b_Tdssk2;   //!
   TBranch        *b_Tdsspi;   //!
   TBranch        *b_Idssvtx;   //!
   TBranch        *b_Idssrprm;   //!
   TBranch        *b_bspt_prog;   //!
   TBranch        *b_bspt_x;   //!
   TBranch        *b_bspt_y;   //!
   TBranch        *b_bspt_z;   //!
   TBranch        *b_bspt_xer;   //!
   TBranch        *b_bspt_yer;   //!
   TBranch        *b_bspt_zer;   //!
   TBranch        *b_bspt_dxdz;   //!
   TBranch        *b_bspt_dydz;   //!
   TBranch        *b_bspt_dxdzer;   //!
   TBranch        *b_bspt_dydzer;   //!
   TBranch        *b_bspt_xoff;   //!
   TBranch        *b_bspt_yoff;   //!
   TBranch        *b_bspt_xoffer;   //!
   TBranch        *b_bspt_yoffer;   //!
   TBranch        *b_ncb;   //!
   TBranch        *b_Cb_id;   //!
   TBranch        *b_Cb_mother;   //!
   TBranch        *b_Cb_daughter;   //!
   TBranch        *b_Cb_daughter2;   //!
   TBranch        *b_Cb_prt;   //!
   TBranch        *b_Nlight_daughters;   //!
   TBranch        *b_Plight_daughters;   //!
   TBranch        *b_Cb_p;   //!
   TBranch        *b_tot_daughters;   //!
   TBranch        *b_Light_dau_id;   //!
   TBranch        *b_Light_dau_index;   //!
   TBranch        *b_vtxredprm_x;   //!
   TBranch        *b_vtxredprm_y;   //!
   TBranch        *b_vtxredprm_z;   //!
   TBranch        *b_vtxredprm_chi2;   //!
   TBranch        *b_vtxredprm_cov;   //!
   TBranch        *b_vtxredprm_ndf;   //!
   TBranch        *b_nr_secvtx;   //!
   TBranch        *b_Vtxsec_x;   //!
   TBranch        *b_Vtxsec_y;   //!
   TBranch        *b_Vtxsec_z;   //!
   TBranch        *b_Vtxsec_mass;   //!
   TBranch        *b_Vtxsec_chi2;   //!
   TBranch        *b_Vtxsec_ndf;   //!
   TBranch        *b_Vtxsec_multi;   //!
   TBranch        *b_Vtxsec_cov;   //!
   TBranch        *b_Vtxsec_zttid;   //!
   TBranch        *b_Vtxsec2d_x;   //!
   TBranch        *b_Vtxsec2d_y;   //!
   TBranch        *b_Vtxsec2d_z;   //!
   TBranch        *b_Vtxsec2d_mass;   //!
   TBranch        *b_Vtxsec2d_chi2;   //!
   TBranch        *b_Vtxsec2d_ndf;   //!
   TBranch        *b_Vtxsec2d_cov;   //!
   TBranch        *b_fmck_nkin;   //!
   TBranch        *b_fmck_q2;   //!
   TBranch        *b_fmck_w;   //!
   TBranch        *b_fmck_xg;   //!
   TBranch        *b_fmck_nstor;   //!
   TBranch        *b_Fmck_id;   //!
   TBranch        *b_Fmck_px;   //!
   TBranch        *b_Fmck_py;   //!
   TBranch        *b_Fmck_pz;   //!
   TBranch        *b_Fmck_e;   //!
   TBranch        *b_Fmck_m;   //!
   TBranch        *b_Fmck_isthep;   //!
   TBranch        *b_Fmck_daug;   //!
   TBranch        *b_Fmck_daug2;   //!
   TBranch        *b_Fmck_prt;   //!
   TBranch        *b_Fmck_prat;   //!
   TBranch        *b_Fmck_impar;   //!
   TBranch        *b_Fmck_impar2;   //!
   TBranch        *b_Fmck_hadjet;   //!
   TBranch        *b_Fmck_mhadjet;   //!
   TBranch        *b_Fmck_bhadjet;   //!
   TBranch        *b_Fmck_mbhadjet;   //!
   TBranch        *b_Fmck_partjet;   //!
   TBranch        *b_Fmck_mpartjet;   //!
   TBranch        *b_Fmck_brhadjet;   //!
   TBranch        *b_Fmck_brmhadjet;   //!
   TBranch        *b_Fmck_brbhadjet;   //!
   TBranch        *b_Fmck_brmbhadjet;   //!
   TBranch        *b_Fmck_brpartjet;   //!
   TBranch        *b_Fmck_brmpartjet;   //!
   TBranch        *b_fmvtx_nstor;   //!
   TBranch        *b_Fmvtx_id;   //!
   TBranch        *b_Fmvtx_r;   //!
   TBranch        *b_Fmvtx_time;   //!
   TBranch        *b_Fmvtx_prby;   //!
   TBranch        *b_nhjets;   //!
   TBranch        *b_Pxhjet;   //!
   TBranch        *b_Pyhjet;   //!
   TBranch        *b_Pzhjet;   //!
   TBranch        *b_Ehjet;   //!
   TBranch        *b_nhmjets;   //!
   TBranch        *b_Pxhmjet;   //!
   TBranch        *b_Pyhmjet;   //!
   TBranch        *b_Pzhmjet;   //!
   TBranch        *b_Ehmjet;   //!
   TBranch        *b_nhbjets;   //!
   TBranch        *b_Pxhbjet;   //!
   TBranch        *b_Pyhbjet;   //!
   TBranch        *b_Pzhbjet;   //!
   TBranch        *b_Ehbjet;   //!
   TBranch        *b_Flhbjet;   //!
   TBranch        *b_Nphbjet;   //!
   TBranch        *b_Phbjet;   //!
   TBranch        *b_nhbmjets;   //!
   TBranch        *b_Pxhbmjet;   //!
   TBranch        *b_Pyhbmjet;   //!
   TBranch        *b_Pzhbmjet;   //!
   TBranch        *b_Ehbmjet;   //!
   TBranch        *b_Flhbmjet;   //!
   TBranch        *b_Nphbmjet;   //!
   TBranch        *b_Phbmjet;   //!
   TBranch        *b_npjets;   //!
   TBranch        *b_Pxpjet;   //!
   TBranch        *b_Pypjet;   //!
   TBranch        *b_Pzpjet;   //!
   TBranch        *b_Epjet;   //!
   TBranch        *b_npmjets;   //!
   TBranch        *b_Pxpmjet;   //!
   TBranch        *b_Pypmjet;   //!
   TBranch        *b_Pzpmjet;   //!
   TBranch        *b_Epmjet;   //!
   TBranch        *b_nbrhjets;   //!
   TBranch        *b_Pxbrhjet;   //!
   TBranch        *b_Pybrhjet;   //!
   TBranch        *b_Pzbrhjet;   //!
   TBranch        *b_Ebrhjet;   //!
   TBranch        *b_nbrhmjets;   //!
   TBranch        *b_Pxbrhmjet;   //!
   TBranch        *b_Pybrhmjet;   //!
   TBranch        *b_Pzbrhmjet;   //!
   TBranch        *b_Ebrhmjet;   //!
   TBranch        *b_nbrhbjets;   //!
   TBranch        *b_Pxbrhbjet;   //!
   TBranch        *b_Pybrhbjet;   //!
   TBranch        *b_Pzbrhbjet;   //!
   TBranch        *b_Ebrhbjet;   //!
   TBranch        *b_nbrhbmjets;   //!
   TBranch        *b_Pxbrhbmjet;   //!
   TBranch        *b_Pybrhbmjet;   //!
   TBranch        *b_Pzbrhbmjet;   //!
   TBranch        *b_Ebrhbmjet;   //!
   TBranch        *b_nbrpjets;   //!
   TBranch        *b_Pxbrpjet;   //!
   TBranch        *b_Pybrpjet;   //!
   TBranch        *b_Pzbrpjet;   //!
   TBranch        *b_Ebrpjet;   //!
   TBranch        *b_nbrpmjets;   //!
   TBranch        *b_Pxbrpmjet;   //!
   TBranch        *b_Pybrpmjet;   //!
   TBranch        *b_Pzbrpmjet;   //!
   TBranch        *b_Ebrpmjet;   //!
   TBranch        *b_Bm_n;   //!
   TBranch        *b_Bm_idvc;   //!
   TBranch        *b_Bm_idmubac;   //!
   TBranch        *b_Bm_istop;   //!
   TBranch        *b_Bm_error;   //!
   TBranch        *b_Bm_readout;   //!
   TBranch        *b_Bm_x;   //!
   TBranch        *b_Bm_p;   //!
   TBranch        *b_Bm_chi2;   //!
   TBranch        *b_Bm_dca;   //!
   TBranch        *b_Bm_gcov;   //!
   TBranch        *b_Bm_fcov;   //!
   TBranch        *b_Bm_resloc;   //!
   TBranch        *b_Bm_prob;   //!
   TBranch        *b_Bm_zpen;   //!
   TBranch        *b_Bm_dlh;   //!
   TBranch        *b_Bm_mubac_n;   //!
   TBranch        *b_Bm_mubac_hit;   //!
   TBranch        *b_Bm_mubac_pad;   //!
   TBranch        *b_Bm_mubac_unit;   //!
   TBranch        *b_Bm_mubac_hp1;   //!
   TBranch        *b_Bm_mubac_hp2;   //!
   TBranch        *b_Bm_mubac_xyz;   //!
   TBranch        *b_Bm_mubac_dxyz;   //!
   TBranch        *b_Bm_mubac_cos;   //!
   TBranch        *b_Bm_mubac_plf;   //!

   MyClass(TTree *tree=0);
   virtual ~MyClass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
    Float_t CalculateProjDecayLength(Int_t	vertex);
    Float_t CalculateSignificance(Int_t	vertex);
};

#endif

#ifdef MyClass_cxx
MyClass::MyClass(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f) {
         f = new TFile("Memory Directory");
         f->cd("Rint:/");
      }
      tree = (TTree*)gDirectory->Get("orange");

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("orange","");
      chain->Add("zeus://acs/z/ntup/04/v02e/mc/root/zeusmc.acpx424.f13695.rgap3.nc.ccdir.p.q2g4.205.root/orange");
      chain->Add("zeus://acs/z/ntup/04/v02e/mc/root/zeusmc.fcpx424.f13695.rgap3.nc.ccdir.p.q2g4.208.root/orange");

      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

MyClass::~MyClass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MyClass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MyClass::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void MyClass::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Runnr", &Runnr, &b_RUNNR);
   fChain->SetBranchAddress("Eventnr", &Eventnr, &b_EVENTNR);
   fChain->SetBranchAddress("Evtake", &Evtake, &b_EVTAKE);
   fChain->SetBranchAddress("Evtake_iwant", &Evtake_iwant, &b_EVTAKE_iwant);
   fChain->SetBranchAddress("Mvdtake", &Mvdtake, &b_MVDTAKE);
   fChain->SetBranchAddress("Stttake", &Stttake, &b_STTTAKE);
   fChain->SetBranchAddress("Tpoltake", &Tpoltake, &b_TPOLTAKE);
   fChain->SetBranchAddress("Lpoltake", &Lpoltake, &b_LPOLTAKE);
   fChain->SetBranchAddress("Fmutake", &Fmutake, &b_FMUTAKE);
   fChain->SetBranchAddress("Mbtake", &Mbtake, &b_MBTAKE);
   fChain->SetBranchAddress("Tag6take", &Tag6take, &b_TAG6TAKE);
   fChain->SetBranchAddress("Fltw", Fltw, &b_FLTW);
   fChain->SetBranchAddress("Fltpsw", Fltpsw, &b_FLTPSW);
   fChain->SetBranchAddress("Fltfl", &Fltfl, &b_FLTfl);
   fChain->SetBranchAddress("Gslt_global", &Gslt_global, &b_GSLT_global);
   fChain->SetBranchAddress("Sltw", Sltw, &b_SLTW);
   fChain->SetBranchAddress("Sltupw", Sltupw, &b_SLTUPW);
   fChain->SetBranchAddress("Tltw", Tltw, &b_TLTW);
   fChain->SetBranchAddress("Dstw", Dstw, &b_DSTW);
   fChain->SetBranchAddress("Fltpsfcw", Fltpsfcw, &b_FLTPSFCW);
   fChain->SetBranchAddress("Bac_etot", &Bac_etot, &b_BAC_etot);
   fChain->SetBranchAddress("Bac_etot_o2r", &Bac_etot_o2r, &b_BAC_etot_o2r);
   fChain->SetBranchAddress("Bac_npad", &Bac_npad, &b_BAC_npad);
   fChain->SetBranchAddress("Bac_npad_o2r", &Bac_npad_o2r, &b_BAC_npad_o2r);
   fChain->SetBranchAddress("Bac_et", &Bac_et, &b_BAC_et);
   fChain->SetBranchAddress("Bac_px", &Bac_px, &b_BAC_px);
   fChain->SetBranchAddress("Bac_py", &Bac_py, &b_BAC_py);
   fChain->SetBranchAddress("Nbacmu", &Nbacmu, &b_NBACMU);
   fChain->SetBranchAddress("Mubac_xyz", Mubac_xyz, &b_Mubac_xyz);
   fChain->SetBranchAddress("Mubac_dxyz", Mubac_dxyz, &b_Mubac_dxyz);
   fChain->SetBranchAddress("Mubac_cos", Mubac_cos, &b_Mubac_cos);
   fChain->SetBranchAddress("Mubac_dcos", Mubac_dcos, &b_Mubac_dcos);
   fChain->SetBranchAddress("Mubac_eloss", Mubac_eloss, &b_Mubac_eloss);
   fChain->SetBranchAddress("Mubac_deloss", Mubac_deloss, &b_Mubac_deloss);
   fChain->SetBranchAddress("Mubac_unit", Mubac_unit, &b_Mubac_unit);
   fChain->SetBranchAddress("Mubac_dim", Mubac_dim, &b_Mubac_dim);
   fChain->SetBranchAddress("Mubac_quality", Mubac_quality, &b_Mubac_quality);
   fChain->SetBranchAddress("Ahit", Ahit, &b_Ahit);
   fChain->SetBranchAddress("Pad", Pad, &b_Pad);
   fChain->SetBranchAddress("Bitword", Bitword, &b_BITWORD);
   fChain->SetBranchAddress("Calib_idcalscheme", &Calib_idcalscheme, &b_calib_idcalscheme);
   fChain->SetBranchAddress("Cal_px", &Cal_px, &b_CAL_px);
   fChain->SetBranchAddress("Cal_py", &Cal_py, &b_CAL_py);
   fChain->SetBranchAddress("Cal_pz", &Cal_pz, &b_CAL_pz);
   fChain->SetBranchAddress("Cal_e", &Cal_e, &b_CAL_E);
   fChain->SetBranchAddress("Cal_et", &Cal_et, &b_CAL_Et);
   fChain->SetBranchAddress("Cal_empz", &Cal_empz, &b_CAL_Empz);
   fChain->SetBranchAddress("Cal_pt", &Cal_pt, &b_CAL_Pt);
   fChain->SetBranchAddress("Cal_phi", &Cal_phi, &b_CAL_phi);
   fChain->SetBranchAddress("Remc", Remc, &b_REmc);
   fChain->SetBranchAddress("Bemc", Bemc, &b_BEmc);
   fChain->SetBranchAddress("Femc", Femc, &b_FEmc);
   fChain->SetBranchAddress("Rhac", Rhac, &b_RHac);
   fChain->SetBranchAddress("Bhac", Bhac, &b_BHac);
   fChain->SetBranchAddress("Fhac", Fhac, &b_FHac);
   fChain->SetBranchAddress("Bhac2", Bhac2, &b_BHac2);
   fChain->SetBranchAddress("Fhac2", Fhac2, &b_FHac2);
   fChain->SetBranchAddress("Nfemc", &Nfemc, &b_NFEMC);
   fChain->SetBranchAddress("Nfhac1", &Nfhac1, &b_NFHAC1);
   fChain->SetBranchAddress("Nfhac2", &Nfhac2, &b_NFHAC2);
   fChain->SetBranchAddress("Nbemc", &Nbemc, &b_NBEMC);
   fChain->SetBranchAddress("Nbhac1", &Nbhac1, &b_NBHAC1);
   fChain->SetBranchAddress("Nbhac2", &Nbhac2, &b_NBHAC2);
   fChain->SetBranchAddress("Nremc", &Nremc, &b_NREMC);
   fChain->SetBranchAddress("Nrhac", &Nrhac, &b_NRHAC);
   fChain->SetBranchAddress("Cal_tf", &Cal_tf, &b_CAL_Tf);
   fChain->SetBranchAddress("Cal_tb", &Cal_tb, &b_CAL_Tb);
   fChain->SetBranchAddress("Cal_tr", &Cal_tr, &b_CAL_Tr);
   fChain->SetBranchAddress("Cal_tg", &Cal_tg, &b_CAL_Tg);
   fChain->SetBranchAddress("Cal_tu", &Cal_tu, &b_CAL_Tu);
   fChain->SetBranchAddress("Cal_td", &Cal_td, &b_CAL_Td);
   fChain->SetBranchAddress("Cal_tu_e", &Cal_tu_e, &b_CAL_Tu_E);
   fChain->SetBranchAddress("Cal_td_e", &Cal_td_e, &b_CAL_Td_E);
   fChain->SetBranchAddress("Cal_tu_n", &Cal_tu_n, &b_CAL_Tu_n);
   fChain->SetBranchAddress("Cal_td_n", &Cal_td_n, &b_CAL_Td_n);
   fChain->SetBranchAddress("Etamax_ce", &Etamax_ce, &b_Etamax_ce);
   fChain->SetBranchAddress("Etamax_ce4", &Etamax_ce4, &b_Etamax_ce4);
   fChain->SetBranchAddress("Cal_et10", &Cal_et10, &b_CAL_Et10);
   fChain->SetBranchAddress("Mtrknoe_pi", &Mtrknoe_pi, &b_Mtrknoe_pi);
   fChain->SetBranchAddress("Mtrknoe_k", &Mtrknoe_k, &b_Mtrknoe_K);
   fChain->SetBranchAddress("E_hk", &E_hk, &b_E_HK);
   fChain->SetBranchAddress("Unmen_pi", &Unmen_pi, &b_UnmEn_pi);
   fChain->SetBranchAddress("Unmen_k", &Unmen_k, &b_UnmEn_k);
   fChain->SetBranchAddress("Sparkf", &Sparkf, &b_SparkF);
   fChain->SetBranchAddress("Pex1ir", Pex1ir, &b_PEX1IR);
   fChain->SetBranchAddress("Et1ir", &Et1ir, &b_ET1IR);
   fChain->SetBranchAddress("Etex1ir", &Etex1ir, &b_ETEX1IR);
   fChain->SetBranchAddress("Pex2ir", Pex2ir, &b_PEX2IR);
   fChain->SetBranchAddress("Et2ir", &Et2ir, &b_ET2IR);
   fChain->SetBranchAddress("Etex2ir", &Etex2ir, &b_ETEX2IR);
   fChain->SetBranchAddress("Percir", Percir, &b_PERCIR);
   fChain->SetBranchAddress("Etrcir", &Etrcir, &b_ETRCIR);
   fChain->SetBranchAddress("Cc_had_0", Cc_had_0, &b_cc_Had_0);
   fChain->SetBranchAddress("Cc_gamma_0", &Cc_gamma_0, &b_cc_Gamma_0);
   fChain->SetBranchAddress("Cc_cehmom", Cc_cehmom, &b_cc_CeHMom);
   fChain->SetBranchAddress("Cc_zuhmom", Cc_zuhmom, &b_cc_ZuHMom);
   fChain->SetBranchAddress("Cc_cchmom", Cc_cchmom, &b_cc_CCHMom);
   fChain->SetBranchAddress("Cc_pt", &Cc_pt, &b_CC_Pt);
   fChain->SetBranchAddress("Cc_et", &Cc_et, &b_CC_Et);
   fChain->SetBranchAddress("Cc_empz", &Cc_empz, &b_CC_EmPz);
   fChain->SetBranchAddress("Cc_gamma", &Cc_gamma, &b_CC_gamma);
   fChain->SetBranchAddress("Cc_yjb", &Cc_yjb, &b_CC_yjb);
   fChain->SetBranchAddress("Cc_q2jb", &Cc_q2jb, &b_CC_Q2jb);
   fChain->SetBranchAddress("Cc_xjb", &Cc_xjb, &b_CC_xjb);
   fChain->SetBranchAddress("Cc_etamax", &Cc_etamax, &b_cc_ETAMAX);
   fChain->SetBranchAddress("Cc_eemc", &Cc_eemc, &b_cc_EEMC);
   fChain->SetBranchAddress("Cc_ehac1", &Cc_ehac1, &b_cc_EHAC1);
   fChain->SetBranchAddress("Cc_ehac2", &Cc_ehac2, &b_cc_EHAC2);
   fChain->SetBranchAddress("Cc_emaxco", &Cc_emaxco, &b_cc_EMAXCO);
   fChain->SetBranchAddress("Cc_nemc", &Cc_nemc, &b_cc_NEMC);
   fChain->SetBranchAddress("Cc_nhac1", &Cc_nhac1, &b_cc_NHAC1);
   fChain->SetBranchAddress("Cc_nhac2", &Cc_nhac2, &b_cc_NHAC2);
   fChain->SetBranchAddress("Cc_fclus_dt", &Cc_fclus_dt, &b_cc_FClus_dt);
   fChain->SetBranchAddress("Cc_fclus_dm", &Cc_fclus_dm, &b_cc_FClus_dm);
   fChain->SetBranchAddress("Cc_fclus_et", &Cc_fclus_et, &b_cc_FClus_Et);
   fChain->SetBranchAddress("Cc_fclus_e", &Cc_fclus_e, &b_cc_FClus_E);
   fChain->SetBranchAddress("Cc_rclus_asoe", &Cc_rclus_asoe, &b_cc_RClus_asoE);
   fChain->SetBranchAddress("Cc_vapvpcell", &Cc_vapvpcell, &b_cc_VapVpCELL);
   fChain->SetBranchAddress("Cc_vapvpzu", &Cc_vapvpzu, &b_cc_VapVpZU);
   fChain->SetBranchAddress("Cc_vapvpcac", &Cc_vapvpcac, &b_cc_VapVpCAC);
   fChain->SetBranchAddress("Nlepton", &Nlepton, &b_nlepton);
   fChain->SetBranchAddress("Nradpho", &Nradpho, &b_nradpho);
   fChain->SetBranchAddress("Nboson", &Nboson, &b_nboson);
   fChain->SetBranchAddress("Nquark", &Nquark, &b_nquark);
   fChain->SetBranchAddress("Ngluon", &Ngluon, &b_ngluon);
   fChain->SetBranchAddress("Idscatlep", &Idscatlep, &b_idscatlep);
   fChain->SetBranchAddress("Idradpho", &Idradpho, &b_idradpho);
   fChain->SetBranchAddress("Idboson", &Idboson, &b_idboson);
   fChain->SetBranchAddress("Idquark", &Idquark, &b_idquark);
   fChain->SetBranchAddress("Idgluon", &Idgluon, &b_idgluon);
   fChain->SetBranchAddress("Dolepton", &Dolepton, &b_dolepton);
   fChain->SetBranchAddress("Doradpho", &Doradpho, &b_doradpho);
   fChain->SetBranchAddress("Doboson", &Doboson, &b_doboson);
   fChain->SetBranchAddress("Doquark", &Doquark, &b_doquark);
   fChain->SetBranchAddress("Dogluon", &Dogluon, &b_dogluon);
   fChain->SetBranchAddress("Plepton", Plepton, &b_plepton);
   fChain->SetBranchAddress("Pradpho", Pradpho, &b_pradpho);
   fChain->SetBranchAddress("Pboson", Pboson, &b_pboson);
   fChain->SetBranchAddress("Pquark", Pquark, &b_pquark);
   fChain->SetBranchAddress("Pgluon", Pgluon, &b_pgluon);
   fChain->SetBranchAddress("Nqg", &Nqg, &b_nqg);
   fChain->SetBranchAddress("Quarkprt", &Quarkprt, &b_quarkprt);
   fChain->SetBranchAddress("Idqg", Idqg, &b_Idqg);
   fChain->SetBranchAddress("Doqg", Doqg, &b_Doqg);
   fChain->SetBranchAddress("Prtqg", Prtqg, &b_Prtqg);
   fChain->SetBranchAddress("Pqg", Pqg, &b_Pqg);
   fChain->SetBranchAddress("Emncand", &Emncand, &b_EmNcand);
   fChain->SetBranchAddress("Emerror", &Emerror, &b_EmError);
   fChain->SetBranchAddress("Emprob", Emprob, &b_Emprob);
   fChain->SetBranchAddress("Empos", Empos, &b_Empos);
   fChain->SetBranchAddress("Emcalpos", Emcalpos, &b_Emcalpos);
   fChain->SetBranchAddress("Emcalene", Emcalene, &b_Emcalene);
   fChain->SetBranchAddress("Emein", Emein, &b_Emein);
   fChain->SetBranchAddress("Emenin", Emenin, &b_Emenin);
   fChain->SetBranchAddress("Emecorr", Emecorr, &b_Emecorr);
   fChain->SetBranchAddress("Emth", Emth, &b_Emth);
   fChain->SetBranchAddress("Emph", Emph, &b_Emph);
   fChain->SetBranchAddress("Empt", Empt, &b_Empt);
   fChain->SetBranchAddress("Emxdet", Emxdet, &b_Emxdet);
   fChain->SetBranchAddress("Emydet", Emydet, &b_Emydet);
   fChain->SetBranchAddress("Emtrknr", Emtrknr, &b_Emtrknr);
   fChain->SetBranchAddress("Emnrsl", Emnrsl, &b_Emnrsl);
   fChain->SetBranchAddress("Emdca", Emdca, &b_Emdca);
   fChain->SetBranchAddress("Emdcabeam", Emdcabeam, &b_Emdcabeam);
   fChain->SetBranchAddress("Emtrkp", Emtrkp, &b_Emtrkp);
   fChain->SetBranchAddress("Emtrkth", Emtrkth, &b_Emtrkth);
   fChain->SetBranchAddress("Emtrkph", Emtrkph, &b_Emtrkph);
   fChain->SetBranchAddress("Emtrkq", Emtrkq, &b_Emtrkq);
   fChain->SetBranchAddress("Emtrkdme", Emtrkdme, &b_Emtrkdme);
   fChain->SetBranchAddress("Emtrkdce", Emtrkdce, &b_Emtrkdce);
   fChain->SetBranchAddress("Emtrkpos", Emtrkpos, &b_Emtrkpos);
   fChain->SetBranchAddress("Emsrtf", Emsrtf, &b_Emsrtf);
   fChain->SetBranchAddress("Emsrtquad", Emsrtquad, &b_Emsrtquad);
   fChain->SetBranchAddress("Emhesf", Emhesf, &b_Emhesf);
   fChain->SetBranchAddress("Emcorrcode", Emcorrcode, &b_Emcorrcode);
   fChain->SetBranchAddress("Emsrtpos", Emsrtpos, &b_Emsrtpos);
   fChain->SetBranchAddress("Emsrtene", Emsrtene, &b_Emsrtene);
   fChain->SetBranchAddress("Emhespos", Emhespos, &b_Emhespos);
   fChain->SetBranchAddress("Emhesene", Emhesene, &b_Emhesene);
   fChain->SetBranchAddress("Emhesr", Emhesr, &b_Emhesr);
   fChain->SetBranchAddress("Emprsene", Emprsene, &b_Emprsene);
   fChain->SetBranchAddress("Emccet", Emccet, &b_Emccet);
   fChain->SetBranchAddress("Emccempz", Emccempz, &b_Emccempz);
   fChain->SetBranchAddress("Emetamax", Emetamax, &b_Emetamax);
   fChain->SetBranchAddress("Emcehmom", Emcehmom, &b_Emcehmom);
   fChain->SetBranchAddress("Emzuhmom", Emzuhmom, &b_Emzuhmom);
   fChain->SetBranchAddress("Emcchmom", Emcchmom, &b_Emcchmom);
   fChain->SetBranchAddress("Emxel", Emxel, &b_Emxel);
   fChain->SetBranchAddress("Emyel", Emyel, &b_Emyel);
   fChain->SetBranchAddress("Emq2el", Emq2el, &b_Emq2el);
   fChain->SetBranchAddress("Emxda", Emxda, &b_Emxda);
   fChain->SetBranchAddress("Emyda", Emyda, &b_Emyda);
   fChain->SetBranchAddress("Emq2da", Emq2da, &b_Emq2da);
   fChain->SetBranchAddress("Emxda_cell", Emxda_cell, &b_Emxda_cell);
   fChain->SetBranchAddress("Emyda_cell", Emyda_cell, &b_Emyda_cell);
   fChain->SetBranchAddress("Emq2da_cell", Emq2da_cell, &b_Emq2da_cell);
   fChain->SetBranchAddress("Emxjb", Emxjb, &b_Emxjb);
   fChain->SetBranchAddress("Emyjb", Emyjb, &b_Emyjb);
   fChain->SetBranchAddress("Emq2jb", Emq2jb, &b_Emq2jb);
   fChain->SetBranchAddress("Emxjb_cell", Emxjb_cell, &b_Emxjb_cell);
   fChain->SetBranchAddress("Emyjb_cell", Emyjb_cell, &b_Emyjb_cell);
   fChain->SetBranchAddress("Emq2jb_cell", Emq2jb_cell, &b_Emq2jb_cell);
   fChain->SetBranchAddress("Emfemc", Emfemc, &b_Emfemc);
   fChain->SetBranchAddress("Emcalprob", Emcalprob, &b_Emcalprob);
   fChain->SetBranchAddress("Eminctd", Eminctd, &b_Eminctd);
   fChain->SetBranchAddress("Emnneartrk", Emnneartrk, &b_Emnneartrk);
   fChain->SetBranchAddress("Emetneartrk", Emetneartrk, &b_Emetneartrk);
   fChain->SetBranchAddress("Emtrkmatchi2", Emtrkmatchi2, &b_Emtrkmatchi2);
   fChain->SetBranchAddress("Emfmaxbemc", Emfmaxbemc, &b_Emfmaxbemc);
   fChain->SetBranchAddress("Emfmaxremc", Emfmaxremc, &b_Emfmaxremc);
   fChain->SetBranchAddress("Emfmaxfemc", Emfmaxfemc, &b_Emfmaxfemc);
   fChain->SetBranchAddress("Emdeltaz", Emdeltaz, &b_Emdeltaz);
   fChain->SetBranchAddress("Emdeltax", Emdeltax, &b_Emdeltax);
   fChain->SetBranchAddress("Emdeltay", Emdeltay, &b_Emdeltay);
   fChain->SetBranchAddress("E5ncand", &E5ncand, &b_E5Ncand);
   fChain->SetBranchAddress("E5error", &E5error, &b_E5Error);
   fChain->SetBranchAddress("E5prob", E5prob, &b_E5prob);
   fChain->SetBranchAddress("E5pos", E5pos, &b_E5pos);
   fChain->SetBranchAddress("E5calpos", E5calpos, &b_E5calpos);
   fChain->SetBranchAddress("E5calene", E5calene, &b_E5calene);
   fChain->SetBranchAddress("E5ein", E5ein, &b_E5ein);
   fChain->SetBranchAddress("E5enin", E5enin, &b_E5enin);
   fChain->SetBranchAddress("E5ecorr", E5ecorr, &b_E5ecorr);
   fChain->SetBranchAddress("E5th", E5th, &b_E5th);
   fChain->SetBranchAddress("E5ph", E5ph, &b_E5ph);
   fChain->SetBranchAddress("E5pt", E5pt, &b_E5pt);
   fChain->SetBranchAddress("E5xdet", E5xdet, &b_E5xdet);
   fChain->SetBranchAddress("E5ydet", E5ydet, &b_E5ydet);
   fChain->SetBranchAddress("E5trknr", E5trknr, &b_E5trknr);
   fChain->SetBranchAddress("E5nrsl", E5nrsl, &b_E5nrsl);
   fChain->SetBranchAddress("E5dca", E5dca, &b_E5dca);
   fChain->SetBranchAddress("E5dcabeam", E5dcabeam, &b_E5dcabeam);
   fChain->SetBranchAddress("E5trkp", E5trkp, &b_E5trkp);
   fChain->SetBranchAddress("E5trkth", E5trkth, &b_E5trkth);
   fChain->SetBranchAddress("E5trkph", E5trkph, &b_E5trkph);
   fChain->SetBranchAddress("E5trkq", E5trkq, &b_E5trkq);
   fChain->SetBranchAddress("E5trkdme", E5trkdme, &b_E5trkdme);
   fChain->SetBranchAddress("E5trkdce", E5trkdce, &b_E5trkdce);
   fChain->SetBranchAddress("E5trkpos", E5trkpos, &b_E5trkpos);
   fChain->SetBranchAddress("E5srtf", E5srtf, &b_E5srtf);
   fChain->SetBranchAddress("E5srtquad", E5srtquad, &b_E5srtquad);
   fChain->SetBranchAddress("E5hesf", E5hesf, &b_E5hesf);
   fChain->SetBranchAddress("E5corrcode", E5corrcode, &b_E5corrcode);
   fChain->SetBranchAddress("E5srtpos", E5srtpos, &b_E5srtpos);
   fChain->SetBranchAddress("E5srtene", E5srtene, &b_E5srtene);
   fChain->SetBranchAddress("E5hespos", E5hespos, &b_E5hespos);
   fChain->SetBranchAddress("E5hesene", E5hesene, &b_E5hesene);
   fChain->SetBranchAddress("E5hesr", E5hesr, &b_E5hesr);
   fChain->SetBranchAddress("E5prsene", E5prsene, &b_E5prsene);
   fChain->SetBranchAddress("E5ccet", E5ccet, &b_E5ccet);
   fChain->SetBranchAddress("E5ccempz", E5ccempz, &b_E5ccempz);
   fChain->SetBranchAddress("E5etamax", E5etamax, &b_E5etamax);
   fChain->SetBranchAddress("E5cehmom", E5cehmom, &b_E5cehmom);
   fChain->SetBranchAddress("E5zuhmom", E5zuhmom, &b_E5zuhmom);
   fChain->SetBranchAddress("E5cchmom", E5cchmom, &b_E5cchmom);
   fChain->SetBranchAddress("E5xel", E5xel, &b_E5xel);
   fChain->SetBranchAddress("E5yel", E5yel, &b_E5yel);
   fChain->SetBranchAddress("E5q2el", E5q2el, &b_E5q2el);
   fChain->SetBranchAddress("E5xda", E5xda, &b_E5xda);
   fChain->SetBranchAddress("E5yda", E5yda, &b_E5yda);
   fChain->SetBranchAddress("E5q2da", E5q2da, &b_E5q2da);
   fChain->SetBranchAddress("E5xda_cell", E5xda_cell, &b_E5xda_cell);
   fChain->SetBranchAddress("E5yda_cell", E5yda_cell, &b_E5yda_cell);
   fChain->SetBranchAddress("E5q2da_cell", E5q2da_cell, &b_E5q2da_cell);
   fChain->SetBranchAddress("E5xjb", E5xjb, &b_E5xjb);
   fChain->SetBranchAddress("E5yjb", E5yjb, &b_E5yjb);
   fChain->SetBranchAddress("E5q2jb", E5q2jb, &b_E5q2jb);
   fChain->SetBranchAddress("E5xjb_cell", E5xjb_cell, &b_E5xjb_cell);
   fChain->SetBranchAddress("E5yjb_cell", E5yjb_cell, &b_E5yjb_cell);
   fChain->SetBranchAddress("E5q2jb_cell", E5q2jb_cell, &b_E5q2jb_cell);
   fChain->SetBranchAddress("E5femc", E5femc, &b_E5femc);
   fChain->SetBranchAddress("E5calprob", E5calprob, &b_E5calprob);
   fChain->SetBranchAddress("E5inctd", E5inctd, &b_E5inctd);
   fChain->SetBranchAddress("E5nneartrk", E5nneartrk, &b_E5nneartrk);
   fChain->SetBranchAddress("E5etneartrk", E5etneartrk, &b_E5etneartrk);
   fChain->SetBranchAddress("E5trkmatchi2", E5trkmatchi2, &b_E5trkmatchi2);
   fChain->SetBranchAddress("E5fmaxbemc", E5fmaxbemc, &b_E5fmaxbemc);
   fChain->SetBranchAddress("E5fmaxremc", E5fmaxremc, &b_E5fmaxremc);
   fChain->SetBranchAddress("E5fmaxfemc", E5fmaxfemc, &b_E5fmaxfemc);
   fChain->SetBranchAddress("E5deltaz", E5deltaz, &b_E5deltaz);
   fChain->SetBranchAddress("E5deltax", E5deltax, &b_E5deltax);
   fChain->SetBranchAddress("E5deltay", E5deltay, &b_E5deltay);
   fChain->SetBranchAddress("Npart", &Npart, &b_nPart);
   fChain->SetBranchAddress("Idlepton", &Idlepton, &b_idLepton);
   fChain->SetBranchAddress("Idphoton", &Idphoton, &b_idPhoton);
   fChain->SetBranchAddress("Part_id", Part_id, &b_Part_id);
   fChain->SetBranchAddress("Part_prt", Part_prt, &b_Part_prt);
   fChain->SetBranchAddress("Part_p", Part_p, &b_Part_p);
   fChain->SetBranchAddress("Nmu", &Nmu, &b_Nmu);
   fChain->SetBranchAddress("Muqual", Muqual, &b_Muqual);
   fChain->SetBranchAddress("Mucharge", Mucharge, &b_Mucharge);
   fChain->SetBranchAddress("Mupt", Mupt, &b_Mupt);
   fChain->SetBranchAddress("Muth", Muth, &b_Muth);
   fChain->SetBranchAddress("Muph", Muph, &b_Muph);
   fChain->SetBranchAddress("Mup", Mup, &b_Mup);
   fChain->SetBranchAddress("Muperr", Muperr, &b_Muperr);
   fChain->SetBranchAddress("Mutrfl", Mutrfl, &b_Mutrfl);
   fChain->SetBranchAddress("Mutrid", Mutrid, &b_Mutrid);
   fChain->SetBranchAddress("Muvcid", Muvcid, &b_Muvcid);
   fChain->SetBranchAddress("Muztid", Muztid, &b_Muztid);
   fChain->SetBranchAddress("Mustid", Mustid, &b_Mustid);
   fChain->SetBranchAddress("Muvtxfl", Muvtxfl, &b_Muvtxfl);
   fChain->SetBranchAddress("Muvtxid", Muvtxid, &b_Muvtxid);
   fChain->SetBranchAddress("Muglomu", Muglomu, &b_Muglomu);
   fChain->SetBranchAddress("Mubremat", Mubremat, &b_Mubremat);
   fChain->SetBranchAddress("Mubacmat", Mubacmat, &b_Mubacmat);
   fChain->SetBranchAddress("Mumubac", Mumubac, &b_Mumubac);
   fChain->SetBranchAddress("Mumamma", Mumamma, &b_Mumamma);
   fChain->SetBranchAddress("Mumpmat", Mumpmat, &b_Mumpmat);
   fChain->SetBranchAddress("Mumufo", Mumufo, &b_Mumufo);
   fChain->SetBranchAddress("Mumip", Mumip, &b_Mumip);
   fChain->SetBranchAddress("Mumv", Mumv, &b_Mumv);
   fChain->SetBranchAddress("Mucalfl", Mucalfl, &b_Mucalfl);
   fChain->SetBranchAddress("Mucalene", Mucalene, &b_Mucalene);
   fChain->SetBranchAddress("Muhac2", Muhac2, &b_Muhac2);
   fChain->SetBranchAddress("Muzufid", Muzufid, &b_Muzufid);
   fChain->SetBranchAddress("Mupmip", Mupmip, &b_Mupmip);
   fChain->SetBranchAddress("Muhene", Muhene, &b_Muhene);
   fChain->SetBranchAddress("Mutime", Mutime, &b_Mutime);
   fChain->SetBranchAddress("Muchfl", Muchfl, &b_Muchfl);
   fChain->SetBranchAddress("Muchid", Muchid, &b_Muchid);
   fChain->SetBranchAddress("Mupmat", Mupmat, &b_Mupmat);
   fChain->SetBranchAddress("Mundof", Mundof, &b_Mundof);
   fChain->SetBranchAddress("Munphi", Munphi, &b_Munphi);
   fChain->SetBranchAddress("Muz", Muz, &b_Muz);
   fChain->SetBranchAddress("Muprec", Muprec, &b_Muprec);
   fChain->SetBranchAddress("Mubmchi2", Mubmchi2, &b_Mubmchi2);
   fChain->SetBranchAddress("Mubmbac", Mubmbac, &b_Mubmbac);
   fChain->SetBranchAddress("Mubacdca", Mubacdca, &b_Mubacdca);
   fChain->SetBranchAddress("Mubacdimq", Mubacdimq, &b_Mubacdimq);
   fChain->SetBranchAddress("Mudxy", Mudxy, &b_Mudxy);
   fChain->SetBranchAddress("Mudz", Mudz, &b_Mudz);
   fChain->SetBranchAddress("Muisol", Muisol, &b_Muisol);
   fChain->SetBranchAddress("Munis", Munis, &b_Munis);
   fChain->SetBranchAddress("Muisdrmip", Muisdrmip, &b_Muisdrmip);
   fChain->SetBranchAddress("Muisetmip", Muisetmip, &b_Muisetmip);
   fChain->SetBranchAddress("Muistumip", Muistumip, &b_Muistumip);
   fChain->SetBranchAddress("Mujetfl_a", Mujetfl_a, &b_Mujetfl_a);
   fChain->SetBranchAddress("Mujetid_a", Mujetid_a, &b_Mujetid_a);
   fChain->SetBranchAddress("Mujetdr_a", Mujetdr_a, &b_Mujetdr_a);
   fChain->SetBranchAddress("Mujetpt_a", Mujetpt_a, &b_Mujetpt_a);
   fChain->SetBranchAddress("Mujetdr2_a", Mujetdr2_a, &b_Mujetdr2_a);
   fChain->SetBranchAddress("Mujetpt2_a", Mujetpt2_a, &b_Mujetpt2_a);
   fChain->SetBranchAddress("Muhjet_id", Muhjet_id, &b_Muhjet_id);
   fChain->SetBranchAddress("Mujetfl_b", Mujetfl_b, &b_Mujetfl_b);
   fChain->SetBranchAddress("Mujetid_b", Mujetid_b, &b_Mujetid_b);
   fChain->SetBranchAddress("Mujetdr_b", Mujetdr_b, &b_Mujetdr_b);
   fChain->SetBranchAddress("Mujetpt_b", Mujetpt_b, &b_Mujetpt_b);
   fChain->SetBranchAddress("Mujetdr2_b", Mujetdr2_b, &b_Mujetdr2_b);
   fChain->SetBranchAddress("Mujetpt2_b", Mujetpt2_b, &b_Mujetpt2_b);
   fChain->SetBranchAddress("Mujetfl_c", Mujetfl_c, &b_Mujetfl_c);
   fChain->SetBranchAddress("Mujetid_c", Mujetid_c, &b_Mujetid_c);
   fChain->SetBranchAddress("Mujetdr_c", Mujetdr_c, &b_Mujetdr_c);
   fChain->SetBranchAddress("Mujetpt_c", Mujetpt_c, &b_Mujetpt_c);
   fChain->SetBranchAddress("Mujetdr2_c", Mujetdr2_c, &b_Mujetdr2_c);
   fChain->SetBranchAddress("Mujetpt2_c", Mujetpt2_c, &b_Mujetpt2_c);
   fChain->SetBranchAddress("Mujetfl_d", Mujetfl_d, &b_Mujetfl_d);
   fChain->SetBranchAddress("Mujetid_d", Mujetid_d, &b_Mujetid_d);
   fChain->SetBranchAddress("Mujetdr_d", Mujetdr_d, &b_Mujetdr_d);
   fChain->SetBranchAddress("Mujetpt_d", Mujetpt_d, &b_Mujetpt_d);
   fChain->SetBranchAddress("Mujetdr2_d", Mujetdr2_d, &b_Mujetdr2_d);
   fChain->SetBranchAddress("Mujetpt2_d", Mujetpt2_d, &b_Mujetpt2_d);
   fChain->SetBranchAddress("Muick", Muick, &b_Muick);
   fChain->SetBranchAddress("Mupartyp", Mupartyp, &b_Mupartyp);
   fChain->SetBranchAddress("Mumc_p", Mumc_p, &b_Mumc_p);
   fChain->SetBranchAddress("Mudirtyp", Mudirtyp, &b_Mudirtyp);
   fChain->SetBranchAddress("Mumc_d", Mumc_d, &b_Mumc_d);
   fChain->SetBranchAddress("Muqtyp", Muqtyp, &b_Muqtyp);
   fChain->SetBranchAddress("Mumc_q", Mumc_q, &b_Mumc_q);
   fChain->SetBranchAddress("Mutruefl", Mutruefl, &b_Mutruefl);
   fChain->SetBranchAddress("Mudecdist", Mudecdist, &b_Mudecdist);
   fChain->SetBranchAddress("Kt_njet_a", &Kt_njet_a, &b_KT_NJET_A);
   fChain->SetBranchAddress("Kt_etjet_a", Kt_etjet_a, &b_Kt_etjet_a);
   fChain->SetBranchAddress("Kt_etajet_a", Kt_etajet_a, &b_Kt_etajet_a);
   fChain->SetBranchAddress("Kt_phijet_a", Kt_phijet_a, &b_Kt_phijet_a);
   fChain->SetBranchAddress("Kt_masjet_a", Kt_masjet_a, &b_Kt_masjet_a);
   fChain->SetBranchAddress("Kt_njet_b", &Kt_njet_b, &b_KT_NJET_B);
   fChain->SetBranchAddress("Kt_etjet_b", Kt_etjet_b, &b_Kt_etjet_b);
   fChain->SetBranchAddress("Kt_etajet_b", Kt_etajet_b, &b_Kt_etajet_b);
   fChain->SetBranchAddress("Kt_phijet_b", Kt_phijet_b, &b_Kt_phijet_b);
   fChain->SetBranchAddress("Kt_masjet_b", Kt_masjet_b, &b_Kt_masjet_b);
   fChain->SetBranchAddress("Kt_bst_b", Kt_bst_b, &b_KT_BST_B);
   fChain->SetBranchAddress("Kt_njet_c", &Kt_njet_c, &b_KT_NJET_C);
   fChain->SetBranchAddress("Kt_etjet_c", Kt_etjet_c, &b_Kt_etjet_c);
   fChain->SetBranchAddress("Kt_etajet_c", Kt_etajet_c, &b_Kt_etajet_c);
   fChain->SetBranchAddress("Kt_phijet_c", Kt_phijet_c, &b_Kt_phijet_c);
   fChain->SetBranchAddress("Kt_masjet_c", Kt_masjet_c, &b_Kt_masjet_c);
   fChain->SetBranchAddress("Kt_bst_c", Kt_bst_c, &b_KT_BST_C);
   fChain->SetBranchAddress("Kt_njet_d", &Kt_njet_d, &b_KT_NJET_D);
   fChain->SetBranchAddress("Kt_etjet_d", Kt_etjet_d, &b_Kt_etjet_d);
   fChain->SetBranchAddress("Kt_etajet_d", Kt_etajet_d, &b_Kt_etajet_d);
   fChain->SetBranchAddress("Kt_phijet_d", Kt_phijet_d, &b_Kt_phijet_d);
   fChain->SetBranchAddress("Kt_masjet_d", Kt_masjet_d, &b_Kt_masjet_d);
   fChain->SetBranchAddress("Kt_bst_d", Kt_bst_d, &b_KT_BST_D);
   fChain->SetBranchAddress("Kt_njet_e", &Kt_njet_e, &b_KT_NJET_E);
   fChain->SetBranchAddress("Kt_etjet_e", Kt_etjet_e, &b_Kt_etjet_e);
   fChain->SetBranchAddress("Kt_etajet_e", Kt_etajet_e, &b_Kt_etajet_e);
   fChain->SetBranchAddress("Kt_phijet_e", Kt_phijet_e, &b_Kt_phijet_e);
   fChain->SetBranchAddress("Kt_bst_e", Kt_bst_e, &b_KT_BST_E);
   fChain->SetBranchAddress("Kt_njet_f", &Kt_njet_f, &b_KT_NJET_F);
   fChain->SetBranchAddress("Kt_etjet_f", Kt_etjet_f, &b_Kt_etjet_f);
   fChain->SetBranchAddress("Kt_etajet_f", Kt_etajet_f, &b_Kt_etajet_f);
   fChain->SetBranchAddress("Kt_phijet_f", Kt_phijet_f, &b_Kt_phijet_f);
   fChain->SetBranchAddress("Kt_bst_f", Kt_bst_f, &b_KT_BST_F);
   fChain->SetBranchAddress("Kt_njet_g", &Kt_njet_g, &b_KT_NJET_G);
   fChain->SetBranchAddress("Kt_etjet_g", Kt_etjet_g, &b_Kt_etjet_g);
   fChain->SetBranchAddress("Kt_etajet_g", Kt_etajet_g, &b_Kt_etajet_g);
   fChain->SetBranchAddress("Kt_phijet_g", Kt_phijet_g, &b_Kt_phijet_g);
   fChain->SetBranchAddress("Kt_bst_g", Kt_bst_g, &b_KT_BST_G);
   fChain->SetBranchAddress("Kt_njet_h", &Kt_njet_h, &b_KT_NJET_H);
   fChain->SetBranchAddress("Kt_etjet_h", Kt_etjet_h, &b_Kt_etjet_h);
   fChain->SetBranchAddress("Kt_etajet_h", Kt_etajet_h, &b_Kt_etajet_h);
   fChain->SetBranchAddress("Kt_phijet_h", Kt_phijet_h, &b_Kt_phijet_h);
   fChain->SetBranchAddress("Kt_bst_h", Kt_bst_h, &b_KT_BST_H);
   fChain->SetBranchAddress("Kt_njet_i", &Kt_njet_i, &b_KT_NJET_I);
   fChain->SetBranchAddress("Kt_etjet_i", Kt_etjet_i, &b_Kt_etjet_i);
   fChain->SetBranchAddress("Kt_etajet_i", Kt_etajet_i, &b_Kt_etajet_i);
   fChain->SetBranchAddress("Kt_phijet_i", Kt_phijet_i, &b_Kt_phijet_i);
   fChain->SetBranchAddress("Kt_njet_j", &Kt_njet_j, &b_KT_NJET_J);
   fChain->SetBranchAddress("Kt_etjet_j", Kt_etjet_j, &b_Kt_etjet_j);
   fChain->SetBranchAddress("Kt_etajet_j", Kt_etajet_j, &b_Kt_etajet_j);
   fChain->SetBranchAddress("Kt_phijet_j", Kt_phijet_j, &b_Kt_phijet_j);
   fChain->SetBranchAddress("Kt_njet_k", &Kt_njet_k, &b_KT_NJET_K);
   fChain->SetBranchAddress("Kt_etjet_k", Kt_etjet_k, &b_Kt_etjet_k);
   fChain->SetBranchAddress("Kt_etajet_k", Kt_etajet_k, &b_Kt_etajet_k);
   fChain->SetBranchAddress("Kt_phijet_k", Kt_phijet_k, &b_Kt_phijet_k);
   fChain->SetBranchAddress("Kt_bst_k", Kt_bst_k, &b_KT_BST_K);
   fChain->SetBranchAddress("Kt_njet_l", &Kt_njet_l, &b_KT_NJET_L);
   fChain->SetBranchAddress("Kt_etjet_l", Kt_etjet_l, &b_Kt_etjet_l);
   fChain->SetBranchAddress("Kt_etajet_l", Kt_etajet_l, &b_Kt_etajet_l);
   fChain->SetBranchAddress("Kt_phijet_l", Kt_phijet_l, &b_Kt_phijet_l);
   fChain->SetBranchAddress("Kt_bst_l", Kt_bst_l, &b_KT_BST_L);
   fChain->SetBranchAddress("Cone_njet", &Cone_njet, &b_CONE_NJET);
   fChain->SetBranchAddress("Cone_etjet", Cone_etjet, &b_Cone_etjet);
   fChain->SetBranchAddress("Cone_etajet", Cone_etajet, &b_Cone_etajet);
   fChain->SetBranchAddress("Cone_phijet", Cone_phijet, &b_Cone_phijet);
   fChain->SetBranchAddress("Elumie", &Elumie, &b_ELumie);
   fChain->SetBranchAddress("Xlumie", &Xlumie, &b_XLumie);
   fChain->SetBranchAddress("Ylumie", &Ylumie, &b_YLumie);
   fChain->SetBranchAddress("Elumig", &Elumig, &b_ELumig);
   fChain->SetBranchAddress("Xlumig", &Xlumig, &b_XLumig);
   fChain->SetBranchAddress("Ylumig", &Ylumig, &b_YLumig);
   fChain->SetBranchAddress("Nmcdstar", &Nmcdstar, &b_nmcdstar);
   fChain->SetBranchAddress("Imcdstar", Imcdstar, &b_Imcdstar);
   fChain->SetBranchAddress("Ptmcdstar", Ptmcdstar, &b_Ptmcdstar);
   fChain->SetBranchAddress("Etamcdstar", Etamcdstar, &b_Etamcdstar);
   fChain->SetBranchAddress("Phimcdstar", Phimcdstar, &b_Phimcdstar);
   fChain->SetBranchAddress("Ndsd02", &Ndsd02, &b_ndsd02);
   fChain->SetBranchAddress("Pdsd02", Pdsd02, &b_Pdsd02);
   fChain->SetBranchAddress("Tdsd02", Tdsd02, &b_Tdsd02);
   fChain->SetBranchAddress("Fdsd02", Fdsd02, &b_Fdsd02);
   fChain->SetBranchAddress("Kdsd02", Kdsd02, &b_Kdsd02);
   fChain->SetBranchAddress("Pdsps2", Pdsps2, &b_Pdsps2);
   fChain->SetBranchAddress("Tdsps2", Tdsps2, &b_Tdsps2);
   fChain->SetBranchAddress("Fdsps2", Fdsps2, &b_Fdsps2);
   fChain->SetBranchAddress("Pmds2", Pmds2, &b_Pmds2);
   fChain->SetBranchAddress("Kmds2", Kmds2, &b_Kmds2);
   fChain->SetBranchAddress("Nmds2", Nmds2, &b_Nmds2);
   fChain->SetBranchAddress("Ndsd04", &Ndsd04, &b_ndsd04);
   fChain->SetBranchAddress("Pdsd04", Pdsd04, &b_Pdsd04);
   fChain->SetBranchAddress("Tdsd04", Tdsd04, &b_Tdsd04);
   fChain->SetBranchAddress("Fdsd04", Fdsd04, &b_Fdsd04);
   fChain->SetBranchAddress("Kdsd04", Kdsd04, &b_Kdsd04);
   fChain->SetBranchAddress("Mdsd04", Mdsd04, &b_Mdsd04);
   fChain->SetBranchAddress("Pdsps4", Pdsps4, &b_Pdsps4);
   fChain->SetBranchAddress("Tdsps4", Tdsps4, &b_Tdsps4);
   fChain->SetBranchAddress("Fdsps4", Fdsps4, &b_Fdsps4);
   fChain->SetBranchAddress("Pmds4", Pmds4, &b_Pmds4);
   fChain->SetBranchAddress("Kmds4", Kmds4, &b_Kmds4);
   fChain->SetBranchAddress("Nmds4", Nmds4, &b_Nmds4);
   fChain->SetBranchAddress("Ndzd02", &Ndzd02, &b_ndzd02);
   fChain->SetBranchAddress("Pdzd02", Pdzd02, &b_Pdzd02);
   fChain->SetBranchAddress("Tdzd02", Tdzd02, &b_Tdzd02);
   fChain->SetBranchAddress("Fdzd02", Fdzd02, &b_Fdzd02);
   fChain->SetBranchAddress("Kdzd02", Kdzd02, &b_Kdzd02);
   fChain->SetBranchAddress("Pdzga2", Pdzga2, &b_Pdzga2);
   fChain->SetBranchAddress("Tdzga2", Tdzga2, &b_Tdzga2);
   fChain->SetBranchAddress("Fdzga2", Fdzga2, &b_Fdzga2);
   fChain->SetBranchAddress("Pmdz2", Pmdz2, &b_Pmdz2);
   fChain->SetBranchAddress("Kmdz2", Kmdz2, &b_Kmdz2);
   fChain->SetBranchAddress("Nmdz2", Nmdz2, &b_Nmdz2);
   fChain->SetBranchAddress("Ndzd04", &Ndzd04, &b_ndzd04);
   fChain->SetBranchAddress("Pdzd04", Pdzd04, &b_Pdzd04);
   fChain->SetBranchAddress("Tdzd04", Tdzd04, &b_Tdzd04);
   fChain->SetBranchAddress("Fdzd04", Fdzd04, &b_Fdzd04);
   fChain->SetBranchAddress("Kdzd04", Kdzd04, &b_Kdzd04);
   fChain->SetBranchAddress("Mdzd04", Mdzd04, &b_Mdzd04);
   fChain->SetBranchAddress("Pdzga4", Pdzga4, &b_Pdzga4);
   fChain->SetBranchAddress("Tdzga4", Tdzga4, &b_Tdzga4);
   fChain->SetBranchAddress("Fdzga4", Fdzga4, &b_Fdzga4);
   fChain->SetBranchAddress("Pmdz4", Pmdz4, &b_Pmdz4);
   fChain->SetBranchAddress("Kmdz4", Kmdz4, &b_Kmdz4);
   fChain->SetBranchAddress("Nmdz4", Nmdz4, &b_Nmdz4);
   fChain->SetBranchAddress("Nd02", &Nd02, &b_nd02);
   fChain->SetBranchAddress("Pd02", Pd02, &b_Pd02);
   fChain->SetBranchAddress("Td02", Td02, &b_Td02);
   fChain->SetBranchAddress("Fd02", Fd02, &b_Fd02);
   fChain->SetBranchAddress("Kd02", Kd02, &b_Kd02);
   fChain->SetBranchAddress("Pmd02", Pmd02, &b_Pmd02);
   fChain->SetBranchAddress("Kmd02", Kmd02, &b_Kmd02);
   fChain->SetBranchAddress("Nmd02", Nmd02, &b_Nmd02);
   fChain->SetBranchAddress("Nd04", &Nd04, &b_nd04);
   fChain->SetBranchAddress("Pd04", Pd04, &b_Pd04);
   fChain->SetBranchAddress("Td04", Td04, &b_Td04);
   fChain->SetBranchAddress("Fd04", Fd04, &b_Fd04);
   fChain->SetBranchAddress("Kd04", Kd04, &b_Kd04);
   fChain->SetBranchAddress("Md04", Md04, &b_Md04);
   fChain->SetBranchAddress("Pmd04", Pmd04, &b_Pmd04);
   fChain->SetBranchAddress("Kmd04", Kmd04, &b_Kmd04);
   fChain->SetBranchAddress("Nmd04", Nmd04, &b_Nmd04);
   fChain->SetBranchAddress("Ndsdch", &Ndsdch, &b_ndsdch);
   fChain->SetBranchAddress("Pdsdch", Pdsdch, &b_Pdsdch);
   fChain->SetBranchAddress("Tdsdch", Tdsdch, &b_Tdsdch);
   fChain->SetBranchAddress("Fdsdch", Fdsdch, &b_Fdsdch);
   fChain->SetBranchAddress("Kdsdch", Kdsdch, &b_Kdsdch);
   fChain->SetBranchAddress("Mdsdch", Mdsdch, &b_Mdsdch);
   fChain->SetBranchAddress("Pdsgah", Pdsgah, &b_Pdsgah);
   fChain->SetBranchAddress("Tdsgah", Tdsgah, &b_Tdsgah);
   fChain->SetBranchAddress("Fdsgah", Fdsgah, &b_Fdsgah);
   fChain->SetBranchAddress("Pmdsh", Pmdsh, &b_Pmdsh);
   fChain->SetBranchAddress("Kmdsh", Kmdsh, &b_Kmdsh);
   fChain->SetBranchAddress("Nmdsh", Nmdsh, &b_Nmdsh);
   fChain->SetBranchAddress("Ndch", &Ndch, &b_ndch);
   fChain->SetBranchAddress("Pdch", Pdch, &b_Pdch);
   fChain->SetBranchAddress("Tdch", Tdch, &b_Tdch);
   fChain->SetBranchAddress("Fdch", Fdch, &b_Fdch);
   fChain->SetBranchAddress("Kdch", Kdch, &b_Kdch);
   fChain->SetBranchAddress("Mdch", Mdch, &b_Mdch);
   fChain->SetBranchAddress("Pmdch", Pmdch, &b_pmdch);
   fChain->SetBranchAddress("Kmdch", Kmdch, &b_kmdch);
   fChain->SetBranchAddress("Nmdch", Nmdch, &b_nmdch);
   fChain->SetBranchAddress("Ndtdss", &Ndtdss, &b_ndtdss);
   fChain->SetBranchAddress("Pdtdss", Pdtdss, &b_Pdtdss);
   fChain->SetBranchAddress("Tdtdss", Tdtdss, &b_Tdtdss);
   fChain->SetBranchAddress("Fdtdss", Fdtdss, &b_Fdtdss);
   fChain->SetBranchAddress("Kdtdss", Kdtdss, &b_Kdtdss);
   fChain->SetBranchAddress("Mdtdss", Mdtdss, &b_Mdtdss);
   fChain->SetBranchAddress("Pdtgas", Pdtgas, &b_Pdtgas);
   fChain->SetBranchAddress("Tdtgas", Tdtgas, &b_Tdtgas);
   fChain->SetBranchAddress("Fdtgas", Fdtgas, &b_Fdtgas);
   fChain->SetBranchAddress("Pmdts", Pmdts, &b_Pmdts);
   fChain->SetBranchAddress("Kmdts", Kmdts, &b_Kmdts);
   fChain->SetBranchAddress("Nmdts", Nmdts, &b_Nmdts);
   fChain->SetBranchAddress("Ndss", &Ndss, &b_ndss);
   fChain->SetBranchAddress("Pdss", Pdss, &b_Pdss);
   fChain->SetBranchAddress("Tdss", Tdss, &b_Tdss);
   fChain->SetBranchAddress("Fdss", Fdss, &b_Fdss);
   fChain->SetBranchAddress("Kdss", Kdss, &b_Kdss);
   fChain->SetBranchAddress("Mdss", Mdss, &b_Mdss);
   fChain->SetBranchAddress("Pmdss", Pmdss, &b_Pmdss);
   fChain->SetBranchAddress("Kmdss", Kmdss, &b_Kmdss);
   fChain->SetBranchAddress("Nmdss", Nmdss, &b_Nmdss);
   fChain->SetBranchAddress("Ndla", &Ndla, &b_ndla);
   fChain->SetBranchAddress("Pdla", Pdla, &b_Pdla);
   fChain->SetBranchAddress("Tdla", Tdla, &b_Tdla);
   fChain->SetBranchAddress("Fdla", Fdla, &b_Fdla);
   fChain->SetBranchAddress("Kdla", Kdla, &b_Kdla);
   fChain->SetBranchAddress("Mdla", Mdla, &b_Mdla);
   fChain->SetBranchAddress("Pmdla", Pmdla, &b_Pmdla);
   fChain->SetBranchAddress("Kmdla", Kmdla, &b_Kmdla);
   fChain->SetBranchAddress("Nmdla", Nmdla, &b_Nmdla);
   fChain->SetBranchAddress("Mc_ez", &Mc_ez, &b_MC_EZ);
   fChain->SetBranchAddress("Mc_esum", &Mc_esum, &b_MC_ESUM);
   fChain->SetBranchAddress("Mc_etcone", &Mc_etcone, &b_MC_ETCONE);
   fChain->SetBranchAddress("Mc_ercal", &Mc_ercal, &b_MC_ERCAL);
   fChain->SetBranchAddress("Mc_el", &Mc_el, &b_MC_EL);
   fChain->SetBranchAddress("Mc_ep", &Mc_ep, &b_MC_EP);
   fChain->SetBranchAddress("Mc_x", &Mc_x, &b_MC_X);
   fChain->SetBranchAddress("Mc_y", &Mc_y, &b_MC_Y);
   fChain->SetBranchAddress("Mc_q2", &Mc_q2, &b_MC_Q2);
   fChain->SetBranchAddress("Mc_mu", &Mc_mu, &b_MC_MU);
   fChain->SetBranchAddress("Mc_pt", &Mc_pt, &b_MC_PT);
   fChain->SetBranchAddress("Mc_xpro", &Mc_xpro, &b_MC_XPRO);
   fChain->SetBranchAddress("Mc_xgam", &Mc_xgam, &b_MC_XGAM);
   fChain->SetBranchAddress("Mc_xpom", &Mc_xpom, &b_MC_XPOM);
   fChain->SetBranchAddress("Mc_beta", &Mc_beta, &b_MC_BETA);
   fChain->SetBranchAddress("Mc_t", &Mc_t, &b_MC_T);
   fChain->SetBranchAddress("Mc_idl", &Mc_idl, &b_MC_IDL);
   fChain->SetBranchAddress("Mc_pidl", &Mc_pidl, &b_MC_PIDL);
   fChain->SetBranchAddress("Mc_pidp", &Mc_pidp, &b_MC_PIDP);
   fChain->SetBranchAddress("Mc_idfsl", &Mc_idfsl, &b_MC_IDFSL);
   fChain->SetBranchAddress("Mc_pfsl", Mc_pfsl, &b_MC_PFSL);
   fChain->SetBranchAddress("Mc_pfsph", Mc_pfsph, &b_MC_PFSPH);
   fChain->SetBranchAddress("Mc_vtx", Mc_vtx, &b_MC_VTX);
   fChain->SetBranchAddress("Mc_ichnn", &Mc_ichnn, &b_MC_ICHNN);
   fChain->SetBranchAddress("Mc_q2_cr", &Mc_q2_cr, &b_MC_Q2_CR);
   fChain->SetBranchAddress("Mc_x_cr", &Mc_x_cr, &b_MC_X_CR);
   fChain->SetBranchAddress("Mcvtx", Mcvtx, &b_MCVtx);
   fChain->SetBranchAddress("Simrun", &Simrun, &b_simrun);
   fChain->SetBranchAddress("Sincand", &Sincand, &b_SiNcand);
   fChain->SetBranchAddress("Sierror", &Sierror, &b_SiError);
   fChain->SetBranchAddress("Siprob", Siprob, &b_Siprob);
   fChain->SetBranchAddress("Sipos", Sipos, &b_Sipos);
   fChain->SetBranchAddress("Sicalpos", Sicalpos, &b_Sicalpos);
   fChain->SetBranchAddress("Sicalene", Sicalene, &b_Sicalene);
   fChain->SetBranchAddress("Siein", Siein, &b_Siein);
   fChain->SetBranchAddress("Sienin", Sienin, &b_Sienin);
   fChain->SetBranchAddress("Siecorr", Siecorr, &b_Siecorr);
   fChain->SetBranchAddress("Sith", Sith, &b_Sith);
   fChain->SetBranchAddress("Siph", Siph, &b_Siph);
   fChain->SetBranchAddress("Sipt", Sipt, &b_Sipt);
   fChain->SetBranchAddress("Sixdet", Sixdet, &b_Sixdet);
   fChain->SetBranchAddress("Siydet", Siydet, &b_Siydet);
   fChain->SetBranchAddress("Sitrknr", Sitrknr, &b_Sitrknr);
   fChain->SetBranchAddress("Sinrsl", Sinrsl, &b_Sinrsl);
   fChain->SetBranchAddress("Sidca", Sidca, &b_Sidca);
   fChain->SetBranchAddress("Sitrkp", Sitrkp, &b_Sitrkp);
   fChain->SetBranchAddress("Sitrkth", Sitrkth, &b_Sitrkth);
   fChain->SetBranchAddress("Sitrkph", Sitrkph, &b_Sitrkph);
   fChain->SetBranchAddress("Sitrkq", Sitrkq, &b_Sitrkq);
   fChain->SetBranchAddress("Sitrkdme", Sitrkdme, &b_Sitrkdme);
   fChain->SetBranchAddress("Sitrkpos", Sitrkpos, &b_Sitrkpos);
   fChain->SetBranchAddress("Sisrtf", Sisrtf, &b_Sisrtf);
   fChain->SetBranchAddress("Sisrtquad", Sisrtquad, &b_Sisrtquad);
   fChain->SetBranchAddress("Sihesf", Sihesf, &b_Sihesf);
   fChain->SetBranchAddress("Sicorrcode", Sicorrcode, &b_Sicorrcode);
   fChain->SetBranchAddress("Sisrtpos", Sisrtpos, &b_Sisrtpos);
   fChain->SetBranchAddress("Sisrtene", Sisrtene, &b_Sisrtene);
   fChain->SetBranchAddress("Sihespos", Sihespos, &b_Sihespos);
   fChain->SetBranchAddress("Sihesene", Sihesene, &b_Sihesene);
   fChain->SetBranchAddress("Sihesr", Sihesr, &b_Sihesr);
   fChain->SetBranchAddress("Siprsene", Siprsene, &b_Siprsene);
   fChain->SetBranchAddress("Siccet", Siccet, &b_Siccet);
   fChain->SetBranchAddress("Siccempz", Siccempz, &b_Siccempz);
   fChain->SetBranchAddress("Sietamax", Sietamax, &b_Sietamax);
   fChain->SetBranchAddress("Sicehmom", Sicehmom, &b_Sicehmom);
   fChain->SetBranchAddress("Sizuhmom", Sizuhmom, &b_Sizuhmom);
   fChain->SetBranchAddress("Sicchmom", Sicchmom, &b_Sicchmom);
   fChain->SetBranchAddress("Sixel", Sixel, &b_Sixel);
   fChain->SetBranchAddress("Siyel", Siyel, &b_Siyel);
   fChain->SetBranchAddress("Siq2el", Siq2el, &b_Siq2el);
   fChain->SetBranchAddress("Sixda", Sixda, &b_Sixda);
   fChain->SetBranchAddress("Siyda", Siyda, &b_Siyda);
   fChain->SetBranchAddress("Siq2da", Siq2da, &b_Siq2da);
   fChain->SetBranchAddress("Sixda_cell", Sixda_cell, &b_Sixda_cell);
   fChain->SetBranchAddress("Siyda_cell", Siyda_cell, &b_Siyda_cell);
   fChain->SetBranchAddress("Siq2da_cell", Siq2da_cell, &b_Siq2da_cell);
   fChain->SetBranchAddress("Sixjb", Sixjb, &b_Sixjb);
   fChain->SetBranchAddress("Siyjb", Siyjb, &b_Siyjb);
   fChain->SetBranchAddress("Siq2jb", Siq2jb, &b_Siq2jb);
   fChain->SetBranchAddress("Sixjb_cell", Sixjb_cell, &b_Sixjb_cell);
   fChain->SetBranchAddress("Siyjb_cell", Siyjb_cell, &b_Siyjb_cell);
   fChain->SetBranchAddress("Siq2jb_cell", Siq2jb_cell, &b_Siq2jb_cell);
   fChain->SetBranchAddress("Nbpchn", &Nbpchn, &b_nBPchn);
   fChain->SetBranchAddress("Bpmip", Bpmip, &b_Bpmip);
   fChain->SetBranchAddress("Bpxyz", Bpxyz, &b_Bpxyz);
   fChain->SetBranchAddress("Bptim", Bptim, &b_Bptim);
   fChain->SetBranchAddress("Tsu_halo", &Tsu_halo, &b_tsu_halo);
   fChain->SetBranchAddress("Nv0lite", &Nv0lite, &b_nv0lite);
   fChain->SetBranchAddress("Tsecvtx", Tsecvtx, &b_Tsecvtx);
   fChain->SetBranchAddress("Tsecvtx_chi", Tsecvtx_chi, &b_Tsecvtx_chi);
   fChain->SetBranchAddress("Tsecvtx_dca", Tsecvtx_dca, &b_Tsecvtx_dca);
   fChain->SetBranchAddress("Tsecvtx_collin2", Tsecvtx_collin2, &b_Tsecvtx_collin2);
   fChain->SetBranchAddress("Tsecvtx_collin3", Tsecvtx_collin3, &b_Tsecvtx_collin3);
   fChain->SetBranchAddress("Tsecvtx_dlen2", Tsecvtx_dlen2, &b_Tsecvtx_dlen2);
   fChain->SetBranchAddress("Tsecvtx_dlen3", Tsecvtx_dlen3, &b_Tsecvtx_dlen3);
   fChain->SetBranchAddress("Tq1", Tq1, &b_Tq1);
   fChain->SetBranchAddress("Tq2", Tq2, &b_Tq2);
   fChain->SetBranchAddress("Ent1", Ent1, &b_Ent1);
   fChain->SetBranchAddress("Ent2", Ent2, &b_Ent2);
   fChain->SetBranchAddress("Tt1_layinn", Tt1_layinn, &b_Tt1_layinn);
   fChain->SetBranchAddress("Tt1_layout", Tt1_layout, &b_Tt1_layout);
   fChain->SetBranchAddress("Tt2_layinn", Tt2_layinn, &b_Tt2_layinn);
   fChain->SetBranchAddress("Tt2_layout", Tt2_layout, &b_Tt2_layout);
   fChain->SetBranchAddress("Tt1_id", Tt1_id, &b_Tt1_id);
   fChain->SetBranchAddress("Tt2_id", Tt2_id, &b_Tt2_id);
   fChain->SetBranchAddress("Stt1", Stt1, &b_Stt1);
   fChain->SetBranchAddress("Stt2", Stt2, &b_Stt2);
   fChain->SetBranchAddress("Tt1_ndof", Tt1_ndof, &b_Tt1_ndof);
   fChain->SetBranchAddress("Tt2_ndof", Tt2_ndof, &b_Tt2_ndof);
   fChain->SetBranchAddress("Tp1", Tp1, &b_Tp1);
   fChain->SetBranchAddress("Tp2", Tp2, &b_Tp2);
   fChain->SetBranchAddress("Tpk", Tpk, &b_Tpk);
   fChain->SetBranchAddress("Tinvmass_lambda", Tinvmass_lambda, &b_Tinvmass_lambda);
   fChain->SetBranchAddress("Tinvmass_alambda", Tinvmass_alambda, &b_Tinvmass_alambda);
   fChain->SetBranchAddress("Tinvmass_k0", Tinvmass_k0, &b_Tinvmass_k0);
   fChain->SetBranchAddress("Tinvmass_ee", Tinvmass_ee, &b_Tinvmass_ee);
   fChain->SetBranchAddress("Ntrkvtx", &Ntrkvtx, &b_Ntrkvtx);
   fChain->SetBranchAddress("Xvtx", &Xvtx, &b_Xvtx);
   fChain->SetBranchAddress("Yvtx", &Yvtx, &b_Yvtx);
   fChain->SetBranchAddress("Zvtx", &Zvtx, &b_Zvtx);
   fChain->SetBranchAddress("Chivtx", &Chivtx, &b_Chivtx);
   fChain->SetBranchAddress("Nsecvtx", &Nsecvtx, &b_Nsecvtx);
   fChain->SetBranchAddress("Xsecvtx", Xsecvtx, &b_Xsecvtx);
   fChain->SetBranchAddress("Ysecvtx", Ysecvtx, &b_Ysecvtx);
   fChain->SetBranchAddress("Zsecvtx", Zsecvtx, &b_Zsecvtx);
   fChain->SetBranchAddress("Chisecvtx", Chisecvtx, &b_Chisecvtx);
   fChain->SetBranchAddress("Fetatr", &Fetatr, &b_Fetatr);
   fChain->SetBranchAddress("Betatr", &Betatr, &b_Betatr);
   fChain->SetBranchAddress("Pt_tr", &Pt_tr, &b_Pt_tr);
   fChain->SetBranchAddress("Empz_tr_pi", &Empz_tr_pi, &b_Empz_tr_pi);
   fChain->SetBranchAddress("Et_tr", &Et_tr, &b_Et_tr);
   fChain->SetBranchAddress("E_tr_pi", &E_tr_pi, &b_E_tr_pi);
   fChain->SetBranchAddress("Phi_tr", &Phi_tr, &b_phi_tr);
   fChain->SetBranchAddress("Zvtx_fcal", &Zvtx_fcal, &b_zvtx_fcal);
   fChain->SetBranchAddress("Fcal_nrgoodcells", &Fcal_nrgoodcells, &b_fcal_NrGoodCells);
   fChain->SetBranchAddress("Fcal_vzerr", &Fcal_vzerr, &b_fcal_VzErr);
   fChain->SetBranchAddress("V_h_px_zu", &V_h_px_zu, &b_V_H_px_zu);
   fChain->SetBranchAddress("V_h_py_zu", &V_h_py_zu, &b_V_H_py_zu);
   fChain->SetBranchAddress("V_h_pz_zu", &V_h_pz_zu, &b_V_H_pz_zu);
   fChain->SetBranchAddress("V_h_e_zu", &V_h_e_zu, &b_V_H_E_zu);
   fChain->SetBranchAddress("Etamax_zu", &Etamax_zu, &b_Etamax_zu);
   fChain->SetBranchAddress("Etamax_zu4", &Etamax_zu4, &b_Etamax_zu4);
   fChain->SetBranchAddress("Fgap", &Fgap, &b_Fgap);
   fChain->SetBranchAddress("Bgap", &Bgap, &b_Bgap);
   fChain->SetBranchAddress("Nzufos", &Nzufos, &b_Nzufos);
   fChain->SetBranchAddress("Tufo", Tufo, &b_Tufo);
   fChain->SetBranchAddress("Zufo_bsp", Zufo_bsp, &b_Zufo_bsp);
   fChain->SetBranchAddress("Zufo", Zufo, &b_Zufo);
   fChain->SetBranchAddress("Cufo", Cufo, &b_Cufo);
   fChain->SetBranchAddress("Zufoecal", Zufoecal, &b_Zufoecal);
   fChain->SetBranchAddress("Zufoeemc", Zufoeemc, &b_Zufoeemc);
   fChain->SetBranchAddress("Nt", &Nt, &b_nT);
   fChain->SetBranchAddress("Vcthid", Vcthid, &b_Vcthid);
   fChain->SetBranchAddress("Qtr", Qtr, &b_Qtr);
   fChain->SetBranchAddress("Swmtr", Swmtr, &b_Swmtr);
   fChain->SetBranchAddress("Qlttr", Qlttr, &b_Qlttr);
   fChain->SetBranchAddress("Mtri", Mtri, &b_Mtri);
   fChain->SetBranchAddress("Wtri", Wtri, &b_Wtri);
   fChain->SetBranchAddress("Ptr", Ptr, &b_Ptr);
   fChain->SetBranchAddress("Dptr", Dptr, &b_Dptr);
   fChain->SetBranchAddress("Thtr", Thtr, &b_Thtr);
   fChain->SetBranchAddress("Phtr", Phtr, &b_Phtr);
   fChain->SetBranchAddress("Dist_istr", Dist_istr, &b_Dist_istr);
   fChain->SetBranchAddress("Trk_ntracks", &Trk_ntracks, &b_trk_ntracks);
   fChain->SetBranchAddress("Trk_type", Trk_type, &b_Trk_type);
   fChain->SetBranchAddress("Ntrack_type", Ntrack_type, &b_ntrack_type);
   fChain->SetBranchAddress("Def_trk_type", &Def_trk_type, &b_def_trk_type);
   fChain->SetBranchAddress("Trk_id", Trk_id, &b_Trk_id);
   fChain->SetBranchAddress("Trk_id2", Trk_id2, &b_Trk_id2);
   fChain->SetBranchAddress("Trk_px", Trk_px, &b_Trk_px);
   fChain->SetBranchAddress("Trk_py", Trk_py, &b_Trk_py);
   fChain->SetBranchAddress("Trk_pz", Trk_pz, &b_Trk_pz);
   fChain->SetBranchAddress("Trk_charge", Trk_charge, &b_Trk_charge);
   fChain->SetBranchAddress("Trk_vtx", Trk_vtx, &b_Trk_vtx);
   fChain->SetBranchAddress("Trk_prim_vtx", Trk_prim_vtx, &b_Trk_prim_vtx);
   fChain->SetBranchAddress("Trk_sec_vtx", Trk_sec_vtx, &b_Trk_sec_vtx);
   fChain->SetBranchAddress("Trk_vxid", Trk_vxid, &b_Trk_vxid);
   fChain->SetBranchAddress("Trk_nzbyt", Trk_nzbyt, &b_Trk_nzbyt);
   fChain->SetBranchAddress("Trk_naxial", Trk_naxial, &b_Trk_naxial);
   fChain->SetBranchAddress("Trk_nstereo", Trk_nstereo, &b_Trk_nstereo);
   fChain->SetBranchAddress("Trk_ndof", Trk_ndof, &b_Trk_ndof);
   fChain->SetBranchAddress("Trk_layinner", Trk_layinner, &b_Trk_layinner);
   fChain->SetBranchAddress("Trk_layouter", Trk_layouter, &b_Trk_layouter);
   fChain->SetBranchAddress("Trk_dedxctd", Trk_dedxctd, &b_Trk_dedxctd);
   fChain->SetBranchAddress("Trk_dedxctdcr", Trk_dedxctdcr, &b_Trk_dedxctdcr);
   fChain->SetBranchAddress("Trk_dedxctderr", Trk_dedxctderr, &b_Trk_dedxctderr);
   fChain->SetBranchAddress("Trk_dedxctdnh", Trk_dedxctdnh, &b_Trk_dedxctdnh);
   fChain->SetBranchAddress("Trk_dedxctdsaturated", Trk_dedxctdsaturated, &b_Trk_dedxctdsaturated);
   fChain->SetBranchAddress("Trk_chi2", Trk_chi2, &b_Trk_chi2);
   fChain->SetBranchAddress("Trk_vchi2", Trk_vchi2, &b_Trk_vchi2);
   fChain->SetBranchAddress("Trk_nbr", Trk_nbr, &b_Trk_nbr);
   fChain->SetBranchAddress("Trk_nbz", Trk_nbz, &b_Trk_nbz);
   fChain->SetBranchAddress("Trk_nwu", Trk_nwu, &b_Trk_nwu);
   fChain->SetBranchAddress("Trk_nwv", Trk_nwv, &b_Trk_nwv);
   fChain->SetBranchAddress("Trk_nstt", Trk_nstt, &b_Trk_nstt);
   fChain->SetBranchAddress("Trk_dedxmvd", Trk_dedxmvd, &b_Trk_dedxmvd);
   fChain->SetBranchAddress("Trk_imppar", Trk_imppar, &b_Trk_imppar);
   fChain->SetBranchAddress("Trk_imperr", Trk_imperr, &b_Trk_imperr);
   fChain->SetBranchAddress("Trk_pca", Trk_pca, &b_Trk_pca);
   fChain->SetBranchAddress("Mcmatfmckin_id", Mcmatfmckin_id, &b_Mcmatfmckin_id);
   fChain->SetBranchAddress("Mcmatpx", Mcmatpx, &b_Mcmatpx);
   fChain->SetBranchAddress("Mcmatpy", Mcmatpy, &b_Mcmatpy);
   fChain->SetBranchAddress("Mcmatpz", Mcmatpz, &b_Mcmatpz);
   fChain->SetBranchAddress("Mcmate", Mcmate, &b_Mcmate);
   fChain->SetBranchAddress("Mcmatm", Mcmatm, &b_Mcmatm);
   fChain->SetBranchAddress("Mcmatcharge", Mcmatcharge, &b_Mcmatcharge);
   fChain->SetBranchAddress("Mcmatquality", Mcmatquality, &b_Mcmatquality);
   fChain->SetBranchAddress("Mcmattype", Mcmattype, &b_Mcmattype);
   fChain->SetBranchAddress("Mcmatsvert_x", Mcmatsvert_x, &b_Mcmatsvert_x);
   fChain->SetBranchAddress("Mcmatsvert_y", Mcmatsvert_y, &b_Mcmatsvert_y);
   fChain->SetBranchAddress("Mcmatsvert_z", Mcmatsvert_z, &b_Mcmatsvert_z);
   fChain->SetBranchAddress("Mcmatmother", Mcmatmother, &b_Mcmatmother);
   fChain->SetBranchAddress("Mcmatmother_px", Mcmatmother_px, &b_Mcmatmother_px);
   fChain->SetBranchAddress("Mcmatmother_py", Mcmatmother_py, &b_Mcmatmother_py);
   fChain->SetBranchAddress("Mcmatmother_pz", Mcmatmother_pz, &b_Mcmatmother_pz);
   fChain->SetBranchAddress("Mcmatmother_e", Mcmatmother_e, &b_Mcmatmother_e);
   fChain->SetBranchAddress("Mcmatmother_m", Mcmatmother_m, &b_Mcmatmother_m);
   fChain->SetBranchAddress("Mcmatmother_prt", Mcmatmother_prt, &b_Mcmatmother_prt);
   fChain->SetBranchAddress("Nchvtx", &Nchvtx, &b_nchvtx);
   fChain->SetBranchAddress("Chvtxpar", Chvtxpar, &b_Chvtxpar);
   fChain->SetBranchAddress("Chvtxcov", Chvtxcov, &b_Chvtxcov);
   fChain->SetBranchAddress("Chchi2", Chchi2, &b_Chchi2);
   fChain->SetBranchAddress("Nchds1", &Nchds1, &b_nchds1);
   fChain->SetBranchAddress("Ds1ms", Ds1ms, &b_Ds1ms);
   fChain->SetBranchAddress("Ds1pm", Ds1pm, &b_Ds1pm);
   fChain->SetBranchAddress("Ds1th", Ds1th, &b_Ds1th);
   fChain->SetBranchAddress("Ds1ph", Ds1ph, &b_Ds1ph);
   fChain->SetBranchAddress("D1d0ms", D1d0ms, &b_D1d0ms);
   fChain->SetBranchAddress("D1d0pm", D1d0pm, &b_D1d0pm);
   fChain->SetBranchAddress("D1d0th", D1d0th, &b_D1d0th);
   fChain->SetBranchAddress("D1d0ph", D1d0ph, &b_D1d0ph);
   fChain->SetBranchAddress("D1kapm", D1kapm, &b_D1kapm);
   fChain->SetBranchAddress("D1kath", D1kath, &b_D1kath);
   fChain->SetBranchAddress("D1kaph", D1kaph, &b_D1kaph);
   fChain->SetBranchAddress("D1pipm", D1pipm, &b_D1pipm);
   fChain->SetBranchAddress("D1pith", D1pith, &b_D1pith);
   fChain->SetBranchAddress("D1piph", D1piph, &b_D1piph);
   fChain->SetBranchAddress("D1pspm", D1pspm, &b_D1pspm);
   fChain->SetBranchAddress("D1psth", D1psth, &b_D1psth);
   fChain->SetBranchAddress("D1psph", D1psph, &b_D1psph);
   fChain->SetBranchAddress("Ds1trk", Ds1trk, &b_Ds1trk);
   fChain->SetBranchAddress("Tds1ka", Tds1ka, &b_Tds1ka);
   fChain->SetBranchAddress("Tds1pi", Tds1pi, &b_Tds1pi);
   fChain->SetBranchAddress("Tds1ps", Tds1ps, &b_Tds1ps);
   fChain->SetBranchAddress("Id1d0vtx", Id1d0vtx, &b_Id1d0vtx);
   fChain->SetBranchAddress("Ids1rprm", Ids1rprm, &b_Ids1rprm);
   fChain->SetBranchAddress("Nchds2", &Nchds2, &b_nchds2);
   fChain->SetBranchAddress("Ds2ms", Ds2ms, &b_Ds2ms);
   fChain->SetBranchAddress("Ds2pm", Ds2pm, &b_Ds2pm);
   fChain->SetBranchAddress("Ds2th", Ds2th, &b_Ds2th);
   fChain->SetBranchAddress("Ds2ph", Ds2ph, &b_Ds2ph);
   fChain->SetBranchAddress("D2d0ms", D2d0ms, &b_D2d0ms);
   fChain->SetBranchAddress("D2d0pm", D2d0pm, &b_D2d0pm);
   fChain->SetBranchAddress("D2d0th", D2d0th, &b_D2d0th);
   fChain->SetBranchAddress("D2d0ph", D2d0ph, &b_D2d0ph);
   fChain->SetBranchAddress("D2kapm", D2kapm, &b_D2kapm);
   fChain->SetBranchAddress("D2kath", D2kath, &b_D2kath);
   fChain->SetBranchAddress("D2kaph", D2kaph, &b_D2kaph);
   fChain->SetBranchAddress("D2p1pm", D2p1pm, &b_D2p1pm);
   fChain->SetBranchAddress("D2p1th", D2p1th, &b_D2p1th);
   fChain->SetBranchAddress("D2p1ph", D2p1ph, &b_D2p1ph);
   fChain->SetBranchAddress("D2p2pm", D2p2pm, &b_D2p2pm);
   fChain->SetBranchAddress("D2p2th", D2p2th, &b_D2p2th);
   fChain->SetBranchAddress("D2p2ph", D2p2ph, &b_D2p2ph);
   fChain->SetBranchAddress("D2p3pm", D2p3pm, &b_D2p3pm);
   fChain->SetBranchAddress("D2p3th", D2p3th, &b_D2p3th);
   fChain->SetBranchAddress("D2p3ph", D2p3ph, &b_D2p3ph);
   fChain->SetBranchAddress("D2pspm", D2pspm, &b_D2pspm);
   fChain->SetBranchAddress("D2psth", D2psth, &b_D2psth);
   fChain->SetBranchAddress("D2psph", D2psph, &b_D2psph);
   fChain->SetBranchAddress("Ds2trk", Ds2trk, &b_Ds2trk);
   fChain->SetBranchAddress("Tds2ka", Tds2ka, &b_Tds2ka);
   fChain->SetBranchAddress("Tds2p1", Tds2p1, &b_Tds2p1);
   fChain->SetBranchAddress("Tds2p2", Tds2p2, &b_Tds2p2);
   fChain->SetBranchAddress("Tds2p3", Tds2p3, &b_Tds2p3);
   fChain->SetBranchAddress("Tds2ps", Tds2ps, &b_Tds2ps);
   fChain->SetBranchAddress("Id2d0vtx", Id2d0vtx, &b_Id2d0vtx);
   fChain->SetBranchAddress("Ids2rprm", Ids2rprm, &b_Ids2rprm);
   fChain->SetBranchAddress("Ds2rin", Ds2rin, &b_Ds2rin);
   fChain->SetBranchAddress("D2maxdca", D2maxdca, &b_D2maxdca);
   fChain->SetBranchAddress("Nchd0", &Nchd0, &b_nchd0);
   fChain->SetBranchAddress("D0ms", D0ms, &b_D0ms);
   fChain->SetBranchAddress("D0pm", D0pm, &b_D0pm);
   fChain->SetBranchAddress("D0th", D0th, &b_D0th);
   fChain->SetBranchAddress("D0ph", D0ph, &b_D0ph);
   fChain->SetBranchAddress("D0kapm", D0kapm, &b_D0kapm);
   fChain->SetBranchAddress("D0kath", D0kath, &b_D0kath);
   fChain->SetBranchAddress("D0kaph", D0kaph, &b_D0kaph);
   fChain->SetBranchAddress("D0pipm", D0pipm, &b_D0pipm);
   fChain->SetBranchAddress("D0pith", D0pith, &b_D0pith);
   fChain->SetBranchAddress("D0piph", D0piph, &b_D0piph);
   fChain->SetBranchAddress("D0trk", D0trk, &b_D0trk);
   fChain->SetBranchAddress("Td0ka", Td0ka, &b_Td0ka);
   fChain->SetBranchAddress("Td0pi", Td0pi, &b_Td0pi);
   fChain->SetBranchAddress("Id0vtx", Id0vtx, &b_Id0vtx);
   fChain->SetBranchAddress("Id0rprm", Id0rprm, &b_Id0rprm);
   fChain->SetBranchAddress("Nchdch", &Nchdch, &b_nchdch);
   fChain->SetBranchAddress("Dchms", Dchms, &b_Dchms);
   fChain->SetBranchAddress("Dchpm", Dchpm, &b_Dchpm);
   fChain->SetBranchAddress("Dchth", Dchth, &b_Dchth);
   fChain->SetBranchAddress("Dchph", Dchph, &b_Dchph);
   fChain->SetBranchAddress("Dckapm", Dckapm, &b_Dckapm);
   fChain->SetBranchAddress("Dckath", Dckath, &b_Dckath);
   fChain->SetBranchAddress("Dckaph", Dckaph, &b_Dckaph);
   fChain->SetBranchAddress("Dcp1pm", Dcp1pm, &b_Dcp1pm);
   fChain->SetBranchAddress("Dcp1th", Dcp1th, &b_Dcp1th);
   fChain->SetBranchAddress("Dcp1ph", Dcp1ph, &b_Dcp1ph);
   fChain->SetBranchAddress("Dcp2pm", Dcp2pm, &b_Dcp2pm);
   fChain->SetBranchAddress("Dcp2th", Dcp2th, &b_Dcp2th);
   fChain->SetBranchAddress("Dcp2ph", Dcp2ph, &b_Dcp2ph);
   fChain->SetBranchAddress("Dchtrk", Dchtrk, &b_Dchtrk);
   fChain->SetBranchAddress("Tdchka", Tdchka, &b_Tdchka);
   fChain->SetBranchAddress("Tdchp1", Tdchp1, &b_Tdchp1);
   fChain->SetBranchAddress("Tdchp2", Tdchp2, &b_Tdchp2);
   fChain->SetBranchAddress("Idchvtx", Idchvtx, &b_Idchvtx);
   fChain->SetBranchAddress("Idchrprm", Idchrprm, &b_Idchrprm);
   fChain->SetBranchAddress("Nchdla", &Nchdla, &b_nchdla);
   fChain->SetBranchAddress("Dlams", Dlams, &b_Dlams);
   fChain->SetBranchAddress("Dlapm", Dlapm, &b_Dlapm);
   fChain->SetBranchAddress("Dlath", Dlath, &b_Dlath);
   fChain->SetBranchAddress("Dlaph", Dlaph, &b_Dlaph);
   fChain->SetBranchAddress("Dlkapm", Dlkapm, &b_Dlkapm);
   fChain->SetBranchAddress("Dlkath", Dlkath, &b_Dlkath);
   fChain->SetBranchAddress("Dlkaph", Dlkaph, &b_Dlkaph);
   fChain->SetBranchAddress("Dlprpm", Dlprpm, &b_Dlprpm);
   fChain->SetBranchAddress("Dlprth", Dlprth, &b_Dlprth);
   fChain->SetBranchAddress("Dlprph", Dlprph, &b_Dlprph);
   fChain->SetBranchAddress("Dlpipm", Dlpipm, &b_Dlpipm);
   fChain->SetBranchAddress("Dlpith", Dlpith, &b_Dlpith);
   fChain->SetBranchAddress("Dlpiph", Dlpiph, &b_Dlpiph);
   fChain->SetBranchAddress("Dlatrk", Dlatrk, &b_Dlatrk);
   fChain->SetBranchAddress("Tdlaka", Tdlaka, &b_Tdlaka);
   fChain->SetBranchAddress("Tdlapr", Tdlapr, &b_Tdlapr);
   fChain->SetBranchAddress("Tdlapi", Tdlapi, &b_Tdlapi);
   fChain->SetBranchAddress("Idlavtx", Idlavtx, &b_Idlavtx);
   fChain->SetBranchAddress("Idlarprm", Idlarprm, &b_Idlarprm);
   fChain->SetBranchAddress("Nchdss", &Nchdss, &b_nchdss);
   fChain->SetBranchAddress("Dssms", Dssms, &b_Dssms);
   fChain->SetBranchAddress("Dsspm", Dsspm, &b_Dsspm);
   fChain->SetBranchAddress("Dssth", Dssth, &b_Dssth);
   fChain->SetBranchAddress("Dssph", Dssph, &b_Dssph);
   fChain->SetBranchAddress("Dsphms", Dsphms, &b_Dsphms);
   fChain->SetBranchAddress("Dsphpm", Dsphpm, &b_Dsphpm);
   fChain->SetBranchAddress("Dsphth", Dsphth, &b_Dsphth);
   fChain->SetBranchAddress("Dsphph", Dsphph, &b_Dsphph);
   fChain->SetBranchAddress("Dsk1pm", Dsk1pm, &b_Dsk1pm);
   fChain->SetBranchAddress("Dsk1th", Dsk1th, &b_Dsk1th);
   fChain->SetBranchAddress("Dsk1ph", Dsk1ph, &b_Dsk1ph);
   fChain->SetBranchAddress("Dsk2pm", Dsk2pm, &b_Dsk2pm);
   fChain->SetBranchAddress("Dsk2th", Dsk2th, &b_Dsk2th);
   fChain->SetBranchAddress("Dsk2ph", Dsk2ph, &b_Dsk2ph);
   fChain->SetBranchAddress("Dspipm", Dspipm, &b_Dspipm);
   fChain->SetBranchAddress("Dspith", Dspith, &b_Dspith);
   fChain->SetBranchAddress("Dspiph", Dspiph, &b_Dspiph);
   fChain->SetBranchAddress("Dsstrk", Dsstrk, &b_Dsstrk);
   fChain->SetBranchAddress("Tdssk1", Tdssk1, &b_Tdssk1);
   fChain->SetBranchAddress("Tdssk2", Tdssk2, &b_Tdssk2);
   fChain->SetBranchAddress("Tdsspi", Tdsspi, &b_Tdsspi);
   fChain->SetBranchAddress("Idssvtx", Idssvtx, &b_Idssvtx);
   fChain->SetBranchAddress("Idssrprm", Idssrprm, &b_Idssrprm);
   fChain->SetBranchAddress("Bspt_prog", &Bspt_prog, &b_bspt_prog);
   fChain->SetBranchAddress("Bspt_x", &Bspt_x, &b_bspt_x);
   fChain->SetBranchAddress("Bspt_y", &Bspt_y, &b_bspt_y);
   fChain->SetBranchAddress("Bspt_z", &Bspt_z, &b_bspt_z);
   fChain->SetBranchAddress("Bspt_xer", &Bspt_xer, &b_bspt_xer);
   fChain->SetBranchAddress("Bspt_yer", &Bspt_yer, &b_bspt_yer);
   fChain->SetBranchAddress("Bspt_zer", &Bspt_zer, &b_bspt_zer);
   fChain->SetBranchAddress("Bspt_dxdz", &Bspt_dxdz, &b_bspt_dxdz);
   fChain->SetBranchAddress("Bspt_dydz", &Bspt_dydz, &b_bspt_dydz);
   fChain->SetBranchAddress("Bspt_dxdzer", &Bspt_dxdzer, &b_bspt_dxdzer);
   fChain->SetBranchAddress("Bspt_dydzer", &Bspt_dydzer, &b_bspt_dydzer);
   fChain->SetBranchAddress("Bspt_xoff", &Bspt_xoff, &b_bspt_xoff);
   fChain->SetBranchAddress("Bspt_yoff", &Bspt_yoff, &b_bspt_yoff);
   fChain->SetBranchAddress("Bspt_xoffer", &Bspt_xoffer, &b_bspt_xoffer);
   fChain->SetBranchAddress("Bspt_yoffer", &Bspt_yoffer, &b_bspt_yoffer);
   fChain->SetBranchAddress("Ncb", &Ncb, &b_ncb);
   fChain->SetBranchAddress("Cb_id", Cb_id, &b_Cb_id);
   fChain->SetBranchAddress("Cb_mother", Cb_mother, &b_Cb_mother);
   fChain->SetBranchAddress("Cb_daughter", Cb_daughter, &b_Cb_daughter);
   fChain->SetBranchAddress("Cb_daughter2", Cb_daughter2, &b_Cb_daughter2);
   fChain->SetBranchAddress("Cb_prt", Cb_prt, &b_Cb_prt);
   fChain->SetBranchAddress("Nlight_daughters", Nlight_daughters, &b_Nlight_daughters);
   fChain->SetBranchAddress("Plight_daughters", Plight_daughters, &b_Plight_daughters);
   fChain->SetBranchAddress("Cb_p", Cb_p, &b_Cb_p);
   fChain->SetBranchAddress("Tot_daughters", &Tot_daughters, &b_tot_daughters);
   fChain->SetBranchAddress("Light_dau_id", Light_dau_id, &b_Light_dau_id);
   fChain->SetBranchAddress("Light_dau_index", Light_dau_index, &b_Light_dau_index);
   fChain->SetBranchAddress("Vtxredprm_x", &Vtxredprm_x, &b_vtxredprm_x);
   fChain->SetBranchAddress("Vtxredprm_y", &Vtxredprm_y, &b_vtxredprm_y);
   fChain->SetBranchAddress("Vtxredprm_z", &Vtxredprm_z, &b_vtxredprm_z);
   fChain->SetBranchAddress("Vtxredprm_chi2", &Vtxredprm_chi2, &b_vtxredprm_chi2);
   fChain->SetBranchAddress("Vtxredprm_cov", Vtxredprm_cov, &b_vtxredprm_cov);
   fChain->SetBranchAddress("Vtxredprm_ndf", &Vtxredprm_ndf, &b_vtxredprm_ndf);
   fChain->SetBranchAddress("Nr_secvtx", &Nr_secvtx, &b_nr_secvtx);
   fChain->SetBranchAddress("Vtxsec_x", Vtxsec_x, &b_Vtxsec_x);
   fChain->SetBranchAddress("Vtxsec_y", Vtxsec_y, &b_Vtxsec_y);
   fChain->SetBranchAddress("Vtxsec_z", Vtxsec_z, &b_Vtxsec_z);
   fChain->SetBranchAddress("Vtxsec_mass", Vtxsec_mass, &b_Vtxsec_mass);
   fChain->SetBranchAddress("Vtxsec_chi2", Vtxsec_chi2, &b_Vtxsec_chi2);
   fChain->SetBranchAddress("Vtxsec_ndf", Vtxsec_ndf, &b_Vtxsec_ndf);
   fChain->SetBranchAddress("Vtxsec_multi", Vtxsec_multi, &b_Vtxsec_multi);
   fChain->SetBranchAddress("Vtxsec_cov", Vtxsec_cov, &b_Vtxsec_cov);
   fChain->SetBranchAddress("Vtxsec_zttid", Vtxsec_zttid, &b_Vtxsec_zttid);
   fChain->SetBranchAddress("Vtxsec2d_x", Vtxsec2d_x, &b_Vtxsec2d_x);
   fChain->SetBranchAddress("Vtxsec2d_y", Vtxsec2d_y, &b_Vtxsec2d_y);
   fChain->SetBranchAddress("Vtxsec2d_z", Vtxsec2d_z, &b_Vtxsec2d_z);
   fChain->SetBranchAddress("Vtxsec2d_mass", Vtxsec2d_mass, &b_Vtxsec2d_mass);
   fChain->SetBranchAddress("Vtxsec2d_chi2", Vtxsec2d_chi2, &b_Vtxsec2d_chi2);
   fChain->SetBranchAddress("Vtxsec2d_ndf", Vtxsec2d_ndf, &b_Vtxsec2d_ndf);
   fChain->SetBranchAddress("Vtxsec2d_cov", Vtxsec2d_cov, &b_Vtxsec2d_cov);
   fChain->SetBranchAddress("Fmck_nkin", &Fmck_nkin, &b_fmck_nkin);
   fChain->SetBranchAddress("Fmck_q2", &Fmck_q2, &b_fmck_q2);
   fChain->SetBranchAddress("Fmck_w", &Fmck_w, &b_fmck_w);
   fChain->SetBranchAddress("Fmck_xg", &Fmck_xg, &b_fmck_xg);
   fChain->SetBranchAddress("Fmck_nstor", &Fmck_nstor, &b_fmck_nstor);
   fChain->SetBranchAddress("Fmck_id", Fmck_id, &b_Fmck_id);
   fChain->SetBranchAddress("Fmck_px", Fmck_px, &b_Fmck_px);
   fChain->SetBranchAddress("Fmck_py", Fmck_py, &b_Fmck_py);
   fChain->SetBranchAddress("Fmck_pz", Fmck_pz, &b_Fmck_pz);
   fChain->SetBranchAddress("Fmck_e", Fmck_e, &b_Fmck_e);
   fChain->SetBranchAddress("Fmck_m", Fmck_m, &b_Fmck_m);
   fChain->SetBranchAddress("Fmck_isthep", Fmck_isthep, &b_Fmck_isthep);
   fChain->SetBranchAddress("Fmck_daug", Fmck_daug, &b_Fmck_daug);
   fChain->SetBranchAddress("Fmck_daug2", Fmck_daug2, &b_Fmck_daug2);
   fChain->SetBranchAddress("Fmck_prt", Fmck_prt, &b_Fmck_prt);
   fChain->SetBranchAddress("Fmck_prat", Fmck_prat, &b_Fmck_prat);
   fChain->SetBranchAddress("Fmck_impar", Fmck_impar, &b_Fmck_impar);
   fChain->SetBranchAddress("Fmck_impar2", Fmck_impar2, &b_Fmck_impar2);
   fChain->SetBranchAddress("Fmck_hadjet", Fmck_hadjet, &b_Fmck_hadjet);
   fChain->SetBranchAddress("Fmck_mhadjet", Fmck_mhadjet, &b_Fmck_mhadjet);
   fChain->SetBranchAddress("Fmck_bhadjet", Fmck_bhadjet, &b_Fmck_bhadjet);
   fChain->SetBranchAddress("Fmck_mbhadjet", Fmck_mbhadjet, &b_Fmck_mbhadjet);
   fChain->SetBranchAddress("Fmck_partjet", Fmck_partjet, &b_Fmck_partjet);
   fChain->SetBranchAddress("Fmck_mpartjet", Fmck_mpartjet, &b_Fmck_mpartjet);
   fChain->SetBranchAddress("Fmck_brhadjet", Fmck_brhadjet, &b_Fmck_brhadjet);
   fChain->SetBranchAddress("Fmck_brmhadjet", Fmck_brmhadjet, &b_Fmck_brmhadjet);
   fChain->SetBranchAddress("Fmck_brbhadjet", Fmck_brbhadjet, &b_Fmck_brbhadjet);
   fChain->SetBranchAddress("Fmck_brmbhadjet", Fmck_brmbhadjet, &b_Fmck_brmbhadjet);
   fChain->SetBranchAddress("Fmck_brpartjet", Fmck_brpartjet, &b_Fmck_brpartjet);
   fChain->SetBranchAddress("Fmck_brmpartjet", Fmck_brmpartjet, &b_Fmck_brmpartjet);
   fChain->SetBranchAddress("Fmvtx_nstor", &Fmvtx_nstor, &b_fmvtx_nstor);
   fChain->SetBranchAddress("Fmvtx_id", Fmvtx_id, &b_Fmvtx_id);
   fChain->SetBranchAddress("Fmvtx_r", Fmvtx_r, &b_Fmvtx_r);
   fChain->SetBranchAddress("Fmvtx_time", Fmvtx_time, &b_Fmvtx_time);
   fChain->SetBranchAddress("Fmvtx_prby", Fmvtx_prby, &b_Fmvtx_prby);
   fChain->SetBranchAddress("Nhjets", &Nhjets, &b_nhjets);
   fChain->SetBranchAddress("Pxhjet", Pxhjet, &b_Pxhjet);
   fChain->SetBranchAddress("Pyhjet", Pyhjet, &b_Pyhjet);
   fChain->SetBranchAddress("Pzhjet", Pzhjet, &b_Pzhjet);
   fChain->SetBranchAddress("Ehjet", Ehjet, &b_Ehjet);
   fChain->SetBranchAddress("Nhmjets", &Nhmjets, &b_nhmjets);
   fChain->SetBranchAddress("Pxhmjet", Pxhmjet, &b_Pxhmjet);
   fChain->SetBranchAddress("Pyhmjet", Pyhmjet, &b_Pyhmjet);
   fChain->SetBranchAddress("Pzhmjet", Pzhmjet, &b_Pzhmjet);
   fChain->SetBranchAddress("Ehmjet", Ehmjet, &b_Ehmjet);
   fChain->SetBranchAddress("Nhbjets", &Nhbjets, &b_nhbjets);
   fChain->SetBranchAddress("Pxhbjet", Pxhbjet, &b_Pxhbjet);
   fChain->SetBranchAddress("Pyhbjet", Pyhbjet, &b_Pyhbjet);
   fChain->SetBranchAddress("Pzhbjet", Pzhbjet, &b_Pzhbjet);
   fChain->SetBranchAddress("Ehbjet", Ehbjet, &b_Ehbjet);
   fChain->SetBranchAddress("Flhbjet", Flhbjet, &b_Flhbjet);
   fChain->SetBranchAddress("Nphbjet", Nphbjet, &b_Nphbjet);
   fChain->SetBranchAddress("Phbjet", Phbjet, &b_Phbjet);
   fChain->SetBranchAddress("Nhbmjets", &Nhbmjets, &b_nhbmjets);
   fChain->SetBranchAddress("Pxhbmjet", Pxhbmjet, &b_Pxhbmjet);
   fChain->SetBranchAddress("Pyhbmjet", Pyhbmjet, &b_Pyhbmjet);
   fChain->SetBranchAddress("Pzhbmjet", Pzhbmjet, &b_Pzhbmjet);
   fChain->SetBranchAddress("Ehbmjet", Ehbmjet, &b_Ehbmjet);
   fChain->SetBranchAddress("Flhbmjet", Flhbmjet, &b_Flhbmjet);
   fChain->SetBranchAddress("Nphbmjet", Nphbmjet, &b_Nphbmjet);
   fChain->SetBranchAddress("Phbmjet", Phbmjet, &b_Phbmjet);
   fChain->SetBranchAddress("Npjets", &Npjets, &b_npjets);
   fChain->SetBranchAddress("Pxpjet", Pxpjet, &b_Pxpjet);
   fChain->SetBranchAddress("Pypjet", Pypjet, &b_Pypjet);
   fChain->SetBranchAddress("Pzpjet", Pzpjet, &b_Pzpjet);
   fChain->SetBranchAddress("Epjet", Epjet, &b_Epjet);
   fChain->SetBranchAddress("Npmjets", &Npmjets, &b_npmjets);
   fChain->SetBranchAddress("Pxpmjet", Pxpmjet, &b_Pxpmjet);
   fChain->SetBranchAddress("Pypmjet", Pypmjet, &b_Pypmjet);
   fChain->SetBranchAddress("Pzpmjet", Pzpmjet, &b_Pzpmjet);
   fChain->SetBranchAddress("Epmjet", Epmjet, &b_Epmjet);
   fChain->SetBranchAddress("Nbrhjets", &Nbrhjets, &b_nbrhjets);
   fChain->SetBranchAddress("Pxbrhjet", Pxbrhjet, &b_Pxbrhjet);
   fChain->SetBranchAddress("Pybrhjet", Pybrhjet, &b_Pybrhjet);
   fChain->SetBranchAddress("Pzbrhjet", Pzbrhjet, &b_Pzbrhjet);
   fChain->SetBranchAddress("Ebrhjet", Ebrhjet, &b_Ebrhjet);
   fChain->SetBranchAddress("Nbrhmjets", &Nbrhmjets, &b_nbrhmjets);
   fChain->SetBranchAddress("Pxbrhmjet", Pxbrhmjet, &b_Pxbrhmjet);
   fChain->SetBranchAddress("Pybrhmjet", Pybrhmjet, &b_Pybrhmjet);
   fChain->SetBranchAddress("Pzbrhmjet", Pzbrhmjet, &b_Pzbrhmjet);
   fChain->SetBranchAddress("Ebrhmjet", Ebrhmjet, &b_Ebrhmjet);
   fChain->SetBranchAddress("Nbrhbjets", &Nbrhbjets, &b_nbrhbjets);
   fChain->SetBranchAddress("Pxbrhbjet", Pxbrhbjet, &b_Pxbrhbjet);
   fChain->SetBranchAddress("Pybrhbjet", Pybrhbjet, &b_Pybrhbjet);
   fChain->SetBranchAddress("Pzbrhbjet", Pzbrhbjet, &b_Pzbrhbjet);
   fChain->SetBranchAddress("Ebrhbjet", Ebrhbjet, &b_Ebrhbjet);
   fChain->SetBranchAddress("Nbrhbmjets", &Nbrhbmjets, &b_nbrhbmjets);
   fChain->SetBranchAddress("Pxbrhbmjet", Pxbrhbmjet, &b_Pxbrhbmjet);
   fChain->SetBranchAddress("Pybrhbmjet", Pybrhbmjet, &b_Pybrhbmjet);
   fChain->SetBranchAddress("Pzbrhbmjet", Pzbrhbmjet, &b_Pzbrhbmjet);
   fChain->SetBranchAddress("Ebrhbmjet", Ebrhbmjet, &b_Ebrhbmjet);
   fChain->SetBranchAddress("Nbrpjets", &Nbrpjets, &b_nbrpjets);
   fChain->SetBranchAddress("Pxbrpjet", Pxbrpjet, &b_Pxbrpjet);
   fChain->SetBranchAddress("Pybrpjet", Pybrpjet, &b_Pybrpjet);
   fChain->SetBranchAddress("Pzbrpjet", Pzbrpjet, &b_Pzbrpjet);
   fChain->SetBranchAddress("Ebrpjet", Ebrpjet, &b_Ebrpjet);
   fChain->SetBranchAddress("Nbrpmjets", &Nbrpmjets, &b_nbrpmjets);
   fChain->SetBranchAddress("Pxbrpmjet", Pxbrpmjet, &b_Pxbrpmjet);
   fChain->SetBranchAddress("Pybrpmjet", Pybrpmjet, &b_Pybrpmjet);
   fChain->SetBranchAddress("Pzbrpmjet", Pzbrpmjet, &b_Pzbrpmjet);
   fChain->SetBranchAddress("Ebrpmjet", Ebrpmjet, &b_Ebrpmjet);
   fChain->SetBranchAddress("Bm_n", &Bm_n, &b_Bm_n);
   fChain->SetBranchAddress("Bm_idvc", Bm_idvc, &b_Bm_idvc);
   fChain->SetBranchAddress("Bm_idmubac", Bm_idmubac, &b_Bm_idmubac);
   fChain->SetBranchAddress("Bm_istop", Bm_istop, &b_Bm_istop);
   fChain->SetBranchAddress("Bm_error", Bm_error, &b_Bm_error);
   fChain->SetBranchAddress("Bm_readout", Bm_readout, &b_Bm_readout);
   fChain->SetBranchAddress("Bm_x", Bm_x, &b_Bm_x);
   fChain->SetBranchAddress("Bm_p", Bm_p, &b_Bm_p);
   fChain->SetBranchAddress("Bm_chi2", Bm_chi2, &b_Bm_chi2);
   fChain->SetBranchAddress("Bm_dca", Bm_dca, &b_Bm_dca);
   fChain->SetBranchAddress("Bm_gcov", Bm_gcov, &b_Bm_gcov);
   fChain->SetBranchAddress("Bm_fcov", Bm_fcov, &b_Bm_fcov);
   fChain->SetBranchAddress("Bm_resloc", Bm_resloc, &b_Bm_resloc);
   fChain->SetBranchAddress("Bm_prob", Bm_prob, &b_Bm_prob);
   fChain->SetBranchAddress("Bm_zpen", Bm_zpen, &b_Bm_zpen);
   fChain->SetBranchAddress("Bm_dlh", Bm_dlh, &b_Bm_dlh);
   fChain->SetBranchAddress("Bm_mubac_n", &Bm_mubac_n, &b_Bm_mubac_n);
   fChain->SetBranchAddress("Bm_mubac_hit", Bm_mubac_hit, &b_Bm_mubac_hit);
   fChain->SetBranchAddress("Bm_mubac_pad", Bm_mubac_pad, &b_Bm_mubac_pad);
   fChain->SetBranchAddress("Bm_mubac_unit", Bm_mubac_unit, &b_Bm_mubac_unit);
   fChain->SetBranchAddress("Bm_mubac_hp1", Bm_mubac_hp1, &b_Bm_mubac_hp1);
   fChain->SetBranchAddress("Bm_mubac_hp2", Bm_mubac_hp2, &b_Bm_mubac_hp2);
   fChain->SetBranchAddress("Bm_mubac_xyz", Bm_mubac_xyz, &b_Bm_mubac_xyz);
   fChain->SetBranchAddress("Bm_mubac_dxyz", Bm_mubac_dxyz, &b_Bm_mubac_dxyz);
   fChain->SetBranchAddress("Bm_mubac_cos", Bm_mubac_cos, &b_Bm_mubac_cos);
   fChain->SetBranchAddress("Bm_mubac_plf", Bm_mubac_plf, &b_Bm_mubac_plf);
   Notify();
}

Bool_t MyClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MyClass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MyClass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

Float_t	MyClass::CalculateProjDecayLength(Int_t	vertex) {

	Float_t		Xsv=Vtxsec_x[vertex];
	Float_t		Ysv=Vtxsec_y[vertex];
	Float_t		Zsv=Vtxsec_z[vertex];


	if ((Xsv==666)||(Ysv==666)||(Zsv==666)) return (-999);

	Float_t		deltaX=Xsv-Bspt_x;
	Float_t		deltaY=Ysv-Bspt_y;

	Float_t		DecayLength=TMath::Sqrt(deltaX*deltaX+deltaY*deltaY);
	if ( DecayLength > 1. ) return (-998);
	if ( TMath::Abs(Zsv) >30. )	return (-998);

	Float_t		ProjectedDecayLength=0;

	Int_t	         jet=vertex;

	Float_t		PhiJet=Kt_phijet_a[jet];
	Float_t		SinPhiJet=TMath::Sin(PhiJet);
	Float_t		CosPhiJet=TMath::Cos(PhiJet);
	ProjectedDecayLength=deltaX*CosPhiJet+deltaY*SinPhiJet;

	return 		ProjectedDecayLength;
}

Float_t	MyClass::CalculateSignificance(Int_t vertex) {

    Float_t    ProjectedDecayLength=CalculateProjDecayLength(vertex);
    if (ProjectedDecayLength == -998) return -998;
    if (ProjectedDecayLength == -999) return -999;

    Int_t   jet=vertex;

	Float_t		PhiJet=Kt_phijet_a[jet];
/*	Float_t		EtaJet=Kt_etajet_a[jet];
	Float_t		ThetaJet=2*TMath::ATan(TMath::Exp(-EtaJet));
	Float_t		SinThetaJet=TMath::Sin(ThetaJet);*/
	Float_t		SinPhiJet=TMath::Sin(PhiJet);
	Float_t		CosPhiJet=TMath::Cos(PhiJet);

	Float_t	ProjectedDecayLengthError=0;

	Float_t	d1=CosPhiJet;
	Float_t	d2=SinPhiJet;
	Float_t	sigma_x=TMath::Sqrt(Vtxsec_cov[vertex][0]);
	Float_t	sigma_y=TMath::Sqrt(Vtxsec_cov[vertex][2]);

	//if ( (period == TSubSet::k0304P) || (period == TSubSet::k0607P) || (period == TSubSet::k06P) || (period == TSubSet::k07P) ){
			Bspt_xer=0.0088;
			Bspt_yer=0.0024;
// 	} else if ((period==TSubSet::k05E) || (period==TSubSet::k06E))	{
// 			Bspt_xer=0.0080;
// 			Bspt_yer=0.0022;
// 	}

ProjectedDecayLengthError=TMath::Sqrt(d1*d1*(sigma_x*sigma_x+Bspt_xer*Bspt_xer)+d2*d2*(sigma_y*sigma_y+Bspt_yer*Bspt_yer)+2*d1*d2*Vtxsec_cov[vertex][1]);

	Float_t		Significance=0;
	Significance = ProjectedDecayLength / ProjectedDecayLengthError;
	return 		Significance;
}


#endif // #ifdef MyClass_cxx
