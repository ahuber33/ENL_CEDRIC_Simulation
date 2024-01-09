/// ENLCEDRICSimEventAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2017 (C) Projet BADGE - CARMELEC -P2R

#include "G4SteppingManager.hh"
#include "ENLCEDRICSimSteppingAction.hh"
#include "G4Run.hh"
#include "ENLCEDRICSimEventAction.hh"
#include "G4RunManager.hh"
#include "ENLCEDRICSimRunAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include <fstream>
#include <iostream>
#include "G4PrimaryVertex.hh"
#include <math.h>
#include "TRandom3.h"
#include "TGraph.h"

using namespace CLHEP;


ENLCEDRICSimEventAction::ENLCEDRICSimEventAction(char* suff):suffixe(suff){}

ENLCEDRICSimEventAction::~ENLCEDRICSimEventAction(){}


// Initialize all counters and set up the event branches for
// filling histograms with ROOT
void ENLCEDRICSimEventAction::BeginOfEventAction(const G4Event* evt){

  G4int event_id = evt->GetEventID();

  //G4cout << "EVENT : " << event_id << G4endl;

  Statistics.IncidentE =0;
  Statistics.IncidentE_Elec_Stack1 = 0;
  Statistics.DepositE_Elec_Stack1 = 0;
  Statistics.EffectiveDepositE_Elec_Stack1 = 0;
  Statistics.X_Position_Elec_Stack1 = 0;
  Statistics.Y_Position_Elec_Stack1 = 0;
  Statistics.IncidentE_Gamma_Stack1.clear();
  Statistics.DepositE_Gamma_Stack1 =0;
  Statistics.EffectiveDepositE_Gamma_Stack1 = 0;
  Statistics.X_Position_Gamma_Stack1 = 0;
  Statistics.Y_Position_Gamma_Stack1 = 0;
  Statistics.IncidentE_Elec_Stack2 = 0;
  Statistics.DepositE_Elec_Stack2 = 0;
  Statistics.EffectiveDepositE_Elec_Stack2 = 0;
  Statistics.X_Position_Elec_Stack2 = 0;
  Statistics.Y_Position_Elec_Stack2 = 0;
  Statistics.IncidentE_Gamma_Stack2.clear();
  Statistics.DepositE_Gamma_Stack2 =0;
  Statistics.EffectiveDepositE_Gamma_Stack2 = 0;
  Statistics.X_Position_Gamma_Stack2 = 0;
  Statistics.Y_Position_Gamma_Stack2 = 0;
  Statistics.IncidentE_Elec_Stack3 = 0;
  Statistics.DepositE_Elec_Stack3 = 0;
  Statistics.EffectiveDepositE_Elec_Stack3 = 0;
  Statistics.X_Position_Elec_Stack3 = 0;
  Statistics.Y_Position_Elec_Stack3 = 0;
  Statistics.IncidentE_Gamma_Stack3.clear();
  Statistics.DepositE_Gamma_Stack3 =0;
  Statistics.EffectiveDepositE_Gamma_Stack3 = 0;
  Statistics.X_Position_Gamma_Stack3 = 0;
  Statistics.Y_Position_Gamma_Stack3 = 0;
  Statistics.IncidentE_Elec_Stack4 = 0;
  Statistics.DepositE_Elec_Stack4 = 0;
  Statistics.EffectiveDepositE_Elec_Stack4 = 0;
  Statistics.X_Position_Elec_Stack4 = 0;
  Statistics.Y_Position_Elec_Stack4 = 0;
  Statistics.IncidentE_Gamma_Stack4.clear();
  Statistics.DepositE_Gamma_Stack4 =0;
  Statistics.EffectiveDepositE_Gamma_Stack4 = 0;
  Statistics.X_Position_Gamma_Stack4 = 0;
  Statistics.Y_Position_Gamma_Stack4 = 0;
  Statistics.IncidentE_Elec_Stack5 = 0;
  Statistics.DepositE_Elec_Stack5 = 0;
  Statistics.EffectiveDepositE_Elec_Stack5 = 0;
  Statistics.X_Position_Elec_Stack5 = 0;
  Statistics.Y_Position_Elec_Stack5 = 0;
  Statistics.IncidentE_Gamma_Stack5.clear();
  Statistics.DepositE_Gamma_Stack5 =0;
  Statistics.EffectiveDepositE_Gamma_Stack5 = 0;
  Statistics.X_Position_Gamma_Stack5 = 0;
  Statistics.Y_Position_Gamma_Stack5 = 0;
  Statistics.IncidentE_Elec_Stack6 = 0;
  Statistics.DepositE_Elec_Stack6 = 0;
  Statistics.EffectiveDepositE_Elec_Stack6 = 0;
  Statistics.X_Position_Elec_Stack6 = 0;
  Statistics.Y_Position_Elec_Stack6 = 0;
  Statistics.IncidentE_Gamma_Stack6.clear();
  Statistics.DepositE_Gamma_Stack6 =0;
  Statistics.EffectiveDepositE_Gamma_Stack6 = 0;
  Statistics.X_Position_Gamma_Stack6 = 0;
  Statistics.Y_Position_Gamma_Stack6 = 0;
  Statistics.IncidentE_Elec_Stack7 = 0;
  Statistics.DepositE_Elec_Stack7 = 0;
  Statistics.EffectiveDepositE_Elec_Stack7 = 0;
  Statistics.X_Position_Elec_Stack7 = 0;
  Statistics.Y_Position_Elec_Stack7 = 0;
  Statistics.IncidentE_Gamma_Stack7.clear();
  Statistics.DepositE_Gamma_Stack7 =0;
  Statistics.EffectiveDepositE_Gamma_Stack7 = 0;
  Statistics.X_Position_Gamma_Stack7 = 0;
  Statistics.Y_Position_Gamma_Stack7 = 0;
  Statistics.compteur=0;
  Statistics.EBremCreation.clear();
  Statistics.EBremExit.clear();

  flag_good_event=false;

  for(G4int i = 0; i<10;i++){
    electron_flag_incident[i]=false;
    electron_flag_position[i] = false;
    gamma_flag_position[i] = false;
    IncidentE_Elec_Stack[i] =0;
    DepositE_Elec_Stack[i] =0;
    DepositE_Gamma_Stack[i] =0;
  }

TrackID.clear();

}

void ENLCEDRICSimEventAction::SetTrackingID(G4int Track_ID, G4String PartName){
  TrackID.push_back(Track_ID);
  ParticuleName = PartName;
}

// Get the number of stored trajectories and calculate the statistics
void ENLCEDRICSimEventAction::EndOfEventAction(const G4Event* evt){
  G4int event_id = evt->GetEventID();

  ENLCEDRICSimRunAction *runac = (ENLCEDRICSimRunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());

  float Energie=0;
  for(G4int i = 0; i<10;i++){
    Energie+=DepositE_Elec_Stack[i];
    Energie+=DepositE_Gamma_Stack[i];
  }

    //if(flag_good_event==true)
    runac->UpdateStatistics(Statistics);
}
