/// ENLCEDRICSimEventAction.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef ENLCEDRICSimEventAction_h
#define ENLCEDRICSimEventAction_h 1
#include "G4ParticleGun.hh"
#include "G4UserEventAction.hh"
#include "TH1F.h"
#include "TROOT.h"
#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"
#include "TCanvas.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include <vector>
#include "TVector.h"

class G4Event;

//This struct carries statistics for the whole Run
struct RunTally {
  float  IncidentE;
  float  IncidentE_Elec_Stack1;
  float  DepositE_Elec_Stack1;
  std::vector<float> IncidentE_Gamma_Stack1;
  float DepositE_Gamma_Stack1;
  float  IncidentE_Elec_Stack2;
  float  DepositE_Elec_Stack2;
  std::vector<float> IncidentE_Gamma_Stack2;
  float DepositE_Gamma_Stack2;
  float  IncidentE_Elec_Stack3;
  float  DepositE_Elec_Stack3;
  std::vector<float> IncidentE_Gamma_Stack3;
  float DepositE_Gamma_Stack3;
  float  IncidentE_Elec_Stack4;
  float  DepositE_Elec_Stack4;
  std::vector<float> IncidentE_Gamma_Stack4;
  float DepositE_Gamma_Stack4;
  float  IncidentE_Elec_Stack5;
  float  DepositE_Elec_Stack5;
  std::vector<float> IncidentE_Gamma_Stack5;
  float DepositE_Gamma_Stack5;
  float  IncidentE_Elec_Stack6;
  float  DepositE_Elec_Stack6;
  std::vector<float> IncidentE_Gamma_Stack6;
  float DepositE_Gamma_Stack6;
  float  IncidentE_Elec_Stack7;
  float  DepositE_Elec_Stack7;
  std::vector<float> IncidentE_Gamma_Stack7;
  float DepositE_Gamma_Stack7;


  inline int operator ==(const RunTally& right) const
  {return (this==&right);}
};



class ENLCEDRICSimEventAction : public G4UserEventAction
{
public:
  ENLCEDRICSimEventAction(char*);
  ~ENLCEDRICSimEventAction();

public:
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
  void SetStepParams(G4int num_IP,G4int m_ID,G4double m_Temps,G4String m_PartName);
  G4int GetIDParent(G4int num_IP) {return ID[num_IP];}
  G4double GetTempsParent(G4int num_IP) {return Temps[num_IP];}
  G4String GetIDPartName(G4int num_IP) {return PartName[num_IP];}
  void ActiveElectronFlag(G4int num_IP) {electron_flag_incident[num_IP]=true;}
  G4bool GetElectronFlag(G4int num_IP) {return electron_flag_incident[num_IP];}

  void SetIncidentE(G4double a){Statistics.IncidentE=a;}
  void SetIncidentELecStack(G4int num_IP, G4double a){IncidentE_Elec_Stack[num_IP]=a;}
  void AddEdepELecStack(G4int num_IP, G4double a){DepositE_Elec_Stack[num_IP]+=a;}
  void SetEdepELecStack1(G4double a){Statistics.DepositE_Elec_Stack1=a;}
  void SetEdepELecStack2(G4double a){Statistics.DepositE_Elec_Stack2=a;}
  void SetEdepELecStack3(G4double a){Statistics.DepositE_Elec_Stack3=a;}
  void SetEdepELecStack4(G4double a){Statistics.DepositE_Elec_Stack4=a;}
  void SetEdepELecStack5(G4double a){Statistics.DepositE_Elec_Stack5=a;}
  void SetEdepELecStack6(G4double a){Statistics.DepositE_Elec_Stack6=a;}
  void SetEdepELecStack7(G4double a){Statistics.DepositE_Elec_Stack7=a;}
  void FillIncidentGammaStack1(G4double a){Statistics.IncidentE_Gamma_Stack1.push_back(a);}
  void FillIncidentGammaStack2(G4double a){Statistics.IncidentE_Gamma_Stack2.push_back(a);}
  void FillIncidentGammaStack3(G4double a){Statistics.IncidentE_Gamma_Stack3.push_back(a);}
  void FillIncidentGammaStack4(G4double a){Statistics.IncidentE_Gamma_Stack4.push_back(a);}
  void FillIncidentGammaStack5(G4double a){Statistics.IncidentE_Gamma_Stack5.push_back(a);}
  void FillIncidentGammaStack6(G4double a){Statistics.IncidentE_Gamma_Stack6.push_back(a);}
  void FillIncidentGammaStack7(G4double a){Statistics.IncidentE_Gamma_Stack7.push_back(a);}
  void AddEdepGammaStack1(G4double a){Statistics.DepositE_Gamma_Stack1+=a;}
  void AddEdepGammaStack2(G4double a){Statistics.DepositE_Gamma_Stack2+=a;}
  void AddEdepGammaStack3(G4double a){Statistics.DepositE_Gamma_Stack3+=a;}
  void AddEdepGammaStack4(G4double a){Statistics.DepositE_Gamma_Stack4+=a;}
  void AddEdepGammaStack5(G4double a){Statistics.DepositE_Gamma_Stack5+=a;}
  void AddEdepGammaStack6(G4double a){Statistics.DepositE_Gamma_Stack6+=a;}
  void AddEdepGammaStack7(G4double a){Statistics.DepositE_Gamma_Stack7+=a;}

  //void AddEdep(G4float edep){Statistics.Deposit+=edep;}
  //void SetIncidentE(G4float e){Statistics.IncidentE =e;}
  //G4float GetIncidentE(){return Statistics.IncidentE;}
  // void FillEBremCreation(G4float e){Statistics.EBremCreation.push_back(e);}
  // void FillEBremPlaque(G4float e){Statistics.EBremPlaque.push_back(e);}
  // void FillENeutronCreation(G4float e){Statistics.ENeutronCreation.push_back(e);}
  // void FillENeutronPlaque(G4float e){Statistics.ENeutronPlaque.push_back(e);}

private:
  TTree *EventTree;
  TBranch *EventBranch;
  RunTally Statistics;
  G4String suffixe;
  G4int ID[10];
  G4double Temps[10];
  G4String PartName[10];
  G4bool electron_flag_incident[10];
  G4double IncidentE_Elec_Stack[10];
  G4double DepositE_Elec_Stack[10];
  G4double DepositE_Gamma_Stack[10];





};


#endif
