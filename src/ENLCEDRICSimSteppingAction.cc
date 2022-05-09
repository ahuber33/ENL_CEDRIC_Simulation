/// ENLCEDRICSimSteppingAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLCEDRICSimSteppingAction.hh"
#include "G4DynamicParticle.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4ProcessManager.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4OpticalPhoton.hh"
#include "ENLCEDRICSimRunAction.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "ENLCEDRICSimEventAction.hh"
#include <iostream>
#include <fstream>
#include "G4Material.hh"
#include "G4Trajectory.hh"
#include "ENLCEDRICSimGeometry.hh"
#include "G4StepPoint.hh"
#include "TRandom3.h"
#include "TF1.h"


using namespace CLHEP;

const G4String ENLCEDRICSimSteppingAction::path = "../simulation_input_files/";

ENLCEDRICSimSteppingAction::ENLCEDRICSimSteppingAction(ENLCEDRICSimGeometry* OptGeom, ENLCEDRICSimRunAction* runaction, ENLCEDRICSimEventAction* eventaction)
  :detector(OptGeom),runaction(runaction),eventaction(eventaction)
{}

  ENLCEDRICSimSteppingAction::~ENLCEDRICSimSteppingAction(){}
  void ENLCEDRICSimSteppingAction::UserSteppingAction(const G4Step *aStep){


    //###################################
    // Déclaration of functions/variables
    //###################################
    ENLCEDRICSimRunAction *runac = (ENLCEDRICSimRunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());
    G4EventManager *evtman = G4EventManager::GetEventManager();
    ENLCEDRICSimEventAction *evtac = (ENLCEDRICSimEventAction*)evtman->GetUserEventAction();
    G4int Parent_ID = aStep->GetTrack()->GetParentID();
    G4int StepNo = aStep->GetTrack()->GetCurrentStepNumber();
    G4Track* track = aStep->GetTrack();
    G4StepPoint* thePrePoint  = aStep->GetPreStepPoint();
    G4StepPoint * thePostPoint = aStep->GetPostStepPoint();
    G4String ProcessName = thePostPoint->GetProcessDefinedStep()->GetProcessName();
    G4String VolumName = track->GetVolume()->GetName();
    G4String PreVolumName =  thePrePoint->GetPhysicalVolume()->GetName();
    G4String PartName = track->GetDefinition()->GetParticleName();
    G4int ID = track->GetTrackID();
    G4double Temps = track->GetGlobalTime();

    G4double x = aStep->GetTrack()->GetPosition().x();
    G4double y = aStep->GetTrack()->GetPosition().y();
    G4double z = aStep->GetTrack()->GetPosition().z();
    G4double r = sqrt(x*x + y*y);
    G4double my_dist_after = track->GetTrackLength()/mm;
    G4double Edep = aStep->GetTotalEnergyDeposit()/keV;
    G4double Energy = track->GetKineticEnergy()/MeV ;




    //#######################################################################
    //#######################################################################
    //###########################START EM INFOS PART#########################
    //#######################################################################
    //#######################################################################

    if (Parent_ID ==0 && StepNo==1)
    {
      eventaction->SetIncidentE(aStep->GetPreStepPoint()->GetKineticEnergy()/MeV);
    }

    for (G4int num_IP=0;num_IP<7;num_IP++) {
      char chaine[30];
      sprintf(chaine,"Stack_IP1_%d",num_IP+1);
      if(VolumName==chaine) {// && prePoint->GetPhysicalVolume () != track->GetVolume()) {
        //cout<<chaine<<"\t"<<PartName<<"\t"<<ID<<endl;
        //cout<<PreVolumName<<endl;
        if(PartName=="e-" && eventaction->GetElectronFlag(num_IP) == false)
        {
          runaction->EcrireDistribElectrons(num_IP, Energy);
          G4cout << "Energy e- = " << Energy << G4endl;
          eventaction->SetIncidentELecStack(num_IP, Energy);
          eventaction->ActiveElectronFlag(num_IP);
        }

        else if(PartName=="gamma")
        {
          runaction->EcrireDistribGammas(num_IP, Energy);
          G4cout << "Energy gamma = " << Energy << G4endl;
        }
        eventaction->SetStepParams(num_IP,ID,Temps,PartName);
      }

      sprintf(chaine,"Stack_IP2_%d",num_IP+1);

      if(VolumName==chaine){
        runaction->AddEnergyTot(num_IP,Edep);
        if (ID>=eventaction->GetIDParent(num_IP) && Temps>eventaction->GetTempsParent(num_IP)) {
          if(eventaction->GetIDPartName(num_IP)=="e-"){
            eventaction->AddEdepELecStack(num_IP, Edep);
            G4cout<<"energie ajoutée coeff e-"<<"\t"<<Edep<<"\t"<<num_IP<<"\t"<<PartName<<"\t"<<ProcessName<<G4endl;
            runaction->AddElectronEnergy(num_IP,Edep);
          }// fin if
          else if(eventaction->GetIDPartName(num_IP)=="gamma") {
            G4cout<<"energie ajoutée coeff gamma"<<"\t"<<Edep<<"\t"<<num_IP<<"\t"<<PartName<<"\t"<<ProcessName<<G4endl;
            runaction->AddGammaEnergy(num_IP,Edep);
          }// fin if
        }
      }
    }//fin for


  }
