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
  float  EffectiveDepositE_Elec_Stack1;
  float  X_Position_Elec_Stack1;
  float  Y_Position_Elec_Stack1;
  std::vector<float> IncidentE_Gamma_Stack1;
  float DepositE_Gamma_Stack1;
  float  EffectiveDepositE_Gamma_Stack1;
  float  X_Position_Gamma_Stack1;
  float  Y_Position_Gamma_Stack1;
  float  IncidentE_Elec_Stack2;
  float  DepositE_Elec_Stack2;
  float  EffectiveDepositE_Elec_Stack2;
  float  X_Position_Elec_Stack2;
  float  Y_Position_Elec_Stack2;
  std::vector<float> IncidentE_Gamma_Stack2;
  float DepositE_Gamma_Stack2;
  float  EffectiveDepositE_Gamma_Stack2;
  float  X_Position_Gamma_Stack2;
  float  Y_Position_Gamma_Stack2;
  float  IncidentE_Elec_Stack3;
  float  DepositE_Elec_Stack3;
  float  EffectiveDepositE_Elec_Stack3;
  float  X_Position_Elec_Stack3;
  float  Y_Position_Elec_Stack3;
  std::vector<float> IncidentE_Gamma_Stack3;
  float DepositE_Gamma_Stack3;
  float  EffectiveDepositE_Gamma_Stack3;
  float  X_Position_Gamma_Stack3;
  float  Y_Position_Gamma_Stack3;
  float  IncidentE_Elec_Stack4;
  float  DepositE_Elec_Stack4;
  float  EffectiveDepositE_Elec_Stack4;
  float  X_Position_Elec_Stack4;
  float  Y_Position_Elec_Stack4;
  std::vector<float> IncidentE_Gamma_Stack4;
  float DepositE_Gamma_Stack4;
  float  EffectiveDepositE_Gamma_Stack4;
  float  X_Position_Gamma_Stack4;
  float  Y_Position_Gamma_Stack4;
  float  IncidentE_Elec_Stack5;
  float  DepositE_Elec_Stack5;
  float  EffectiveDepositE_Elec_Stack5;
  float  X_Position_Elec_Stack5;
  float  Y_Position_Elec_Stack5;
  std::vector<float> IncidentE_Gamma_Stack5;
  float DepositE_Gamma_Stack5;
  float  EffectiveDepositE_Gamma_Stack5;
  float  X_Position_Gamma_Stack5;
  float  Y_Position_Gamma_Stack5;
  float  IncidentE_Elec_Stack6;
  float  DepositE_Elec_Stack6;
  float  EffectiveDepositE_Elec_Stack6;
  float  X_Position_Elec_Stack6;
  float  Y_Position_Elec_Stack6;
  std::vector<float> IncidentE_Gamma_Stack6;
  float DepositE_Gamma_Stack6;
  float  EffectiveDepositE_Gamma_Stack6;
  float  X_Position_Gamma_Stack6;
  float  Y_Position_Gamma_Stack6;
  float  IncidentE_Elec_Stack7;
  float  DepositE_Elec_Stack7;
  float  EffectiveDepositE_Elec_Stack7;
  float  X_Position_Elec_Stack7;
  float  Y_Position_Elec_Stack7;
  std::vector<float> IncidentE_Gamma_Stack7;
  float DepositE_Gamma_Stack7;
  float  EffectiveDepositE_Gamma_Stack7;
  float  X_Position_Gamma_Stack7;
  float  Y_Position_Gamma_Stack7;
  int compteur;
  std::vector<float> EBremCreation;
  std::vector<float> EBremExit;


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
  void SetTrackingID(G4int Track_ID, G4String PartName);
  G4int GetIDParentSize() {return TrackID.size();}
  G4int GetIDParent(G4int i) {return TrackID.at(i);}
  G4String GetIDPartName() {return ParticuleName;}
  void SetIDPartName(G4String PartName) {ParticuleName=PartName;}
  void ActiveElectronFlag(G4int num_IP) {electron_flag_incident[num_IP]=true;}
  G4bool GetElectronFlag(G4int num_IP) {return electron_flag_incident[num_IP];}

  void SetIncidentE(G4double a){Statistics.IncidentE=a;}
  void SetIncidentELecStack(G4int num_IP, G4double a){IncidentE_Elec_Stack[num_IP]=a;}
  void SetIncidentElecStack1(G4double a){Statistics.IncidentE_Elec_Stack1=a;}
  void SetIncidentElecStack2(G4double a){Statistics.IncidentE_Elec_Stack2=a;}
  void SetIncidentElecStack3(G4double a){Statistics.IncidentE_Elec_Stack3=a;}
  void SetIncidentElecStack4(G4double a){Statistics.IncidentE_Elec_Stack4=a;}
  void SetIncidentElecStack5(G4double a){Statistics.IncidentE_Elec_Stack5=a;}
  void SetIncidentElecStack6(G4double a){Statistics.IncidentE_Elec_Stack6=a;}
  void SetIncidentElecStack7(G4double a){Statistics.IncidentE_Elec_Stack7=a;}
  void AddEdepElecStack1(G4double a){Statistics.DepositE_Elec_Stack1+=a;}
  void AddEdepElecStack2(G4double a){Statistics.DepositE_Elec_Stack2+=a;}
  void AddEdepElecStack3(G4double a){Statistics.DepositE_Elec_Stack3+=a;}
  void AddEdepElecStack4(G4double a){Statistics.DepositE_Elec_Stack4+=a;}
  void AddEdepElecStack5(G4double a){Statistics.DepositE_Elec_Stack5+=a;}
  void AddEdepElecStack6(G4double a){Statistics.DepositE_Elec_Stack6+=a;}
  void AddEdepElecStack7(G4double a){Statistics.DepositE_Elec_Stack7+=a;}
  void AddEffEdepElecStack1(G4double a){Statistics.EffectiveDepositE_Elec_Stack1+=a;}
  void AddEffEdepElecStack2(G4double a){Statistics.EffectiveDepositE_Elec_Stack2+=a;}
  void AddEffEdepElecStack3(G4double a){Statistics.EffectiveDepositE_Elec_Stack3+=a;}
  void AddEffEdepElecStack4(G4double a){Statistics.EffectiveDepositE_Elec_Stack4+=a;}
  void AddEffEdepElecStack5(G4double a){Statistics.EffectiveDepositE_Elec_Stack5+=a;}
  void AddEffEdepElecStack6(G4double a){Statistics.EffectiveDepositE_Elec_Stack6+=a;}
  void AddEffEdepElecStack7(G4double a){Statistics.EffectiveDepositE_Elec_Stack7+=a;}
  void SetXPositionElecStack1(G4double a){Statistics.X_Position_Elec_Stack1=a;}
  void SetXPositionElecStack2(G4double a){Statistics.X_Position_Elec_Stack2=a;}
  void SetXPositionElecStack3(G4double a){Statistics.X_Position_Elec_Stack3=a;}
  void SetXPositionElecStack4(G4double a){Statistics.X_Position_Elec_Stack4=a;}
  void SetXPositionElecStack5(G4double a){Statistics.X_Position_Elec_Stack5=a;}
  void SetXPositionElecStack6(G4double a){Statistics.X_Position_Elec_Stack6=a;}
  void SetXPositionElecStack7(G4double a){Statistics.X_Position_Elec_Stack7=a;}
  void SetYPositionElecStack1(G4double a){Statistics.Y_Position_Elec_Stack1=a;}
  void SetYPositionElecStack2(G4double a){Statistics.Y_Position_Elec_Stack2=a;}
  void SetYPositionElecStack3(G4double a){Statistics.Y_Position_Elec_Stack3=a;}
  void SetYPositionElecStack4(G4double a){Statistics.Y_Position_Elec_Stack4=a;}
  void SetYPositionElecStack5(G4double a){Statistics.Y_Position_Elec_Stack5=a;}
  void SetYPositionElecStack6(G4double a){Statistics.Y_Position_Elec_Stack6=a;}
  void SetYPositionElecStack7(G4double a){Statistics.Y_Position_Elec_Stack7=a;}
  void ActivePositionElectronFlag(G4int num_IP) {electron_flag_position[num_IP]=true;}
  G4bool GetPositionElectronFlag(G4int num_IP) {return electron_flag_position[num_IP];}
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
  void AddEffEdepGammaStack1(G4double a){Statistics.EffectiveDepositE_Gamma_Stack1+=a;}
  void AddEffEdepGammaStack2(G4double a){Statistics.EffectiveDepositE_Gamma_Stack2+=a;}
  void AddEffEdepGammaStack3(G4double a){Statistics.EffectiveDepositE_Gamma_Stack3+=a;}
  void AddEffEdepGammaStack4(G4double a){Statistics.EffectiveDepositE_Gamma_Stack4+=a;}
  void AddEffEdepGammaStack5(G4double a){Statistics.EffectiveDepositE_Gamma_Stack5+=a;}
  void AddEffEdepGammaStack6(G4double a){Statistics.EffectiveDepositE_Gamma_Stack6+=a;}
  void AddEffEdepGammaStack7(G4double a){Statistics.EffectiveDepositE_Gamma_Stack7+=a;}
  void SetXPositionGammaStack1(G4double a){Statistics.X_Position_Gamma_Stack1=a;}
  void SetXPositionGammaStack2(G4double a){Statistics.X_Position_Gamma_Stack2=a;}
  void SetXPositionGammaStack3(G4double a){Statistics.X_Position_Gamma_Stack3=a;}
  void SetXPositionGammaStack4(G4double a){Statistics.X_Position_Gamma_Stack4=a;}
  void SetXPositionGammaStack5(G4double a){Statistics.X_Position_Gamma_Stack5=a;}
  void SetXPositionGammaStack6(G4double a){Statistics.X_Position_Gamma_Stack6=a;}
  void SetXPositionGammaStack7(G4double a){Statistics.X_Position_Gamma_Stack7=a;}
  void SetYPositionGammaStack1(G4double a){Statistics.Y_Position_Gamma_Stack1=a;}
  void SetYPositionGammaStack2(G4double a){Statistics.Y_Position_Gamma_Stack2=a;}
  void SetYPositionGammaStack3(G4double a){Statistics.Y_Position_Gamma_Stack3=a;}
  void SetYPositionGammaStack4(G4double a){Statistics.Y_Position_Gamma_Stack4=a;}
  void SetYPositionGammaStack5(G4double a){Statistics.Y_Position_Gamma_Stack5=a;}
  void SetYPositionGammaStack6(G4double a){Statistics.Y_Position_Gamma_Stack6=a;}
  void SetYPositionGammaStack7(G4double a){Statistics.Y_Position_Gamma_Stack7=a;}
  void ActiveFlagGoodEvent(){flag_good_event=true;}
  void ActivePositionGammaFlag(G4int num_IP) {gamma_flag_position[num_IP]=true;}
  G4bool GetPositionGammaFlag(G4int num_IP) {return gamma_flag_position[num_IP];}
  void ActiveCompteur(){Statistics.compteur++;}
  G4int GetCompteur(){return Statistics.compteur;}
  void FillEBremCreation(G4double a){Statistics.EBremCreation.push_back(a);}
  void FillEBremExit(G4double a){Statistics.EBremExit.push_back(a);}

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
  std::vector<int> TrackID;
  G4String ParticuleName;
  G4bool electron_flag_incident[10];
  G4bool electron_flag_position[10];
  G4bool gamma_flag_position[10];
  G4bool flag_good_event;
  G4double IncidentE_Elec_Stack[10];
  G4double DepositE_Elec_Stack[10];
  G4double DepositE_Gamma_Stack[10];





};


#endif
