/// ENLCEDRICSimRunAction.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef ENLCEDRICSimRunAction_h
#define ENLCEDRICSimRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "TROOT.h"
#include "TTree.h"
#include "ENLCEDRICSimEventAction.hh"
#include <TFile.h>
#include <vector>

class Geometry;
class G4Run;

class ENLCEDRICSimRunAction : public G4UserRunAction
{

public:
  ENLCEDRICSimRunAction(char*);
  ~ENLCEDRICSimRunAction();

public:
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);
  void EcrireDistribElectrons(G4int num_IP, G4double Energie);
  void EcrireDistribGammas(G4int num_IP, G4double Energie);
  void SetHistoName(G4String name) {fname = name;}
  void SetStepParams(G4int m_ID,G4double m_Temps,G4String m_PartName);
  void InitialiseHistos();

  void AddElectronEnergy(G4int num_IP, G4double Edep) {E_dep_electrons[num_IP]+=Edep;}
  void AddGammaEnergy(G4int num_IP, G4double Edep) {E_dep_gammas[num_IP]+=Edep;}
  void AddEnergyTot(G4int num_IP, G4double Edep) {E_dep_tot[num_IP]+=Edep;}
  void AddElectronEnergyEff(G4int num_IP, G4double Edep) {E_dep_electrons_eff[num_IP]+=Edep;}
  void AddGammaEnergyEff(G4int num_IP, G4double Edep) {E_dep_gammas_eff[num_IP]+=Edep;}
  void AddEnergyTotEff(G4int num_IP, G4double Edep) {E_dep_tot_eff[num_IP]+=Edep;}

  G4double GetPosZSensitiveIP1(){return PosZ_Sensitive_IP1;}
  G4double GetPosZSensitiveIP2(){return PosZ_Sensitive_IP2;}
  G4double GetPosZSensitiveIP3(){return PosZ_Sensitive_IP3;}
  G4double GetPosZSensitiveIP4(){return PosZ_Sensitive_IP4;}
  G4double GetPosZSensitiveIP5(){return PosZ_Sensitive_IP5;}
  G4double GetPosZSensitiveIP6(){return PosZ_Sensitive_IP6;}
  G4double GetPosZSensitiveIP7(){return PosZ_Sensitive_IP7;}
  G4double GetEpaisseurTantale12(){return Epaisseur_tantale1_2;}
  G4double GetEpaisseurTantale23(){return Epaisseur_tantale2_3;}
  G4double GetEpaisseurTantale34(){return Epaisseur_tantale3_4;}
  G4double GetEpaisseurTantale45(){return Epaisseur_tantale4_5;}
  G4double GetEpaisseurTantale56(){return Epaisseur_tantale5_6;}
  G4double GetEpaisseurTantale67(){return Epaisseur_tantale6_7;}
  G4double GetLabs(){return Labs;}
  G4double GetCoefPSL(){return Coef_PSL;}

  //adds the photon fates from an event to the run tree
  void UpdateStatistics(RunTally);

private:
  Geometry *Geom;




private:
  static const G4int Nombre_IP = 7;
  static const G4String path_bin;
  G4String suffixe;
  RunTally Stats;
  TFile *f;
  TTree *IP;
  TBranch *RunBranch;
  time_t start;
  G4String fname, nom_fichier;
  TH1D *HistoDistribElectrons[Nombre_IP];
  TH1D *HistoDistribGammas[Nombre_IP];
  G4double E_dep_electrons[Nombre_IP],  E_dep_gammas[Nombre_IP], E_dep_tot[Nombre_IP];
  G4double E_dep_electrons_eff[Nombre_IP],  E_dep_gammas_eff[Nombre_IP], E_dep_tot_eff[Nombre_IP];
  G4double Rayon_cylindre_interieur;
  G4double Rayon_cylindre_exterieur;
  G4double Stack_IP_pos_ini;
  G4double Disque_alu_epaisseur;
  G4double Bloc_mylar_hauteur;
  G4double Cylindre_tantale_hauteur;
  G4double IPa1_z;
  G4double IPa2_z;
  G4double IPa3_z;
  G4double IPa4_z;
  G4double PosZ_Sensitive_IP1;
  G4double PosZ_Sensitive_IP2;
  G4double PosZ_Sensitive_IP3;
  G4double PosZ_Sensitive_IP4;
  G4double PosZ_Sensitive_IP5;
  G4double PosZ_Sensitive_IP6;
  G4double PosZ_Sensitive_IP7;
  G4double Epaisseur_tantale1_2;
  G4double Epaisseur_tantale2_3;
  G4double Epaisseur_tantale3_4;
  G4double Epaisseur_tantale4_5;
  G4double Epaisseur_tantale5_6;
  G4double Epaisseur_tantale6_7;
  G4double Labs;
  G4double Coef_PSL;

};

#endif
