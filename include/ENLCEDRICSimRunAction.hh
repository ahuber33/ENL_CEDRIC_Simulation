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

  //adds the photon fates from an event to the run tree
  void UpdateStatistics(RunTally);




private:
  static const G4int Nombre_IP = 7;
  G4String suffixe;
  RunTally Stats;
  TFile *f;
  TTree *theRunTree;
  TBranch *RunBranch;
  time_t start;
  G4String fname, nom_fichier;
  TH1D *HistoDistribElectrons[Nombre_IP];
  TH1D *HistoDistribGammas[Nombre_IP];
  G4double E_dep_electrons[Nombre_IP],  E_dep_gammas[Nombre_IP], E_dep_tot[Nombre_IP];

};

#endif
