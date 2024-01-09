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
#include "CLHEP/Random/RandFlat.h"
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
    //G4EventManager *evtman = G4EventManager::GetEventManager();
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
    //G4double Temps = track->GetGlobalTime();
    G4ThreeVector prePoint = aStep->GetPreStepPoint()->GetPosition();
    G4ThreeVector postPoint = aStep->GetPostStepPoint()->GetPosition();
    G4ThreeVector point = prePoint + G4UniformRand()*(postPoint-prePoint);

    G4double x = aStep->GetTrack()->GetPosition().x();
    G4double y = aStep->GetTrack()->GetPosition().y();
    G4double z = aStep->GetTrack()->GetPosition().z();
    // G4double r = sqrt(x*x + y*y);
    //G4double my_dist_after = track->GetTrackLength()/mm;
    G4double Edep = aStep->GetTotalEnergyDeposit()/keV;
    G4double EdepEff = 0;
    G4double Energy = track->GetKineticEnergy()/MeV ;

    PosZ_Sensitive_IP1 = runaction->GetPosZSensitiveIP1()-12.7;
    PosZ_Sensitive_IP2 = runaction->GetPosZSensitiveIP2()-12.7;
    PosZ_Sensitive_IP3 = runaction->GetPosZSensitiveIP3()-12.7;
    PosZ_Sensitive_IP4 = runaction->GetPosZSensitiveIP4()-12.7;
    PosZ_Sensitive_IP5 = runaction->GetPosZSensitiveIP5()-12.7;
    PosZ_Sensitive_IP6 = runaction->GetPosZSensitiveIP6()-12.7;
    PosZ_Sensitive_IP7 = runaction->GetPosZSensitiveIP7()-12.7;

    Labs = runaction->GetLabs();

    if(PartName == "geantino" && PreVolumName == "Disque_Alu_entree")
    {
      eventaction->ActiveCompteur();
      //G4cout << "Compteur = " << eventaction->GetCompteur() << G4endl;
    }

    //#######################################################################
    //#######################################################################
    //###########################START EM INFOS PART#########################
    //#######################################################################
    //#######################################################################

    if (Parent_ID ==0 && StepNo==1)
    {
      eventaction->SetIncidentE(aStep->GetPreStepPoint()->GetKineticEnergy()/MeV);
    }


    if(StepNo ==1)
    {
      //G4cout << "ID = " << ID << G4endl;
      eventaction->SetIDPartName(PartName);
      if(Parent_ID==0 && PartName == "gamma") eventaction->SetTrackingID(ID, PartName);

      if(Parent_ID>0)
      {
        //G4cout << "Creator Process = " << track->GetCreatorProcess()->GetProcessName() << G4endl;
        if(track->GetCreatorProcess()->GetProcessName()=="compt" || track->GetCreatorProcess()->GetProcessName() == "phot" || track->GetCreatorProcess()->GetProcessName() == "conv" || track->GetCreatorProcess()->GetProcessName() == "eBrem")
        {
          eventaction->SetTrackingID(ID, "gamma");
        }
        else
        {
          for (int i=0; i<eventaction->GetIDParentSize(); i++)
          {
            if(Parent_ID ==eventaction->GetIDParent(i))
            {
              //G4cout << "ID[" << i << "] = " << eventaction->GetIDParent(i) << G4endl;
              eventaction->SetTrackingID(ID, "gamma");
              break;
            }
          }
        }
      }
    }



    for (G4int num_IP=0;num_IP<7;num_IP++) {
      char chaine[30];
      sprintf(chaine,"Stack_IP1_%d",num_IP+1);
      if(PreVolumName==chaine) {// && prePoint->GetPhysicalVolume () != track->GetVolume()) {
        //cout<<chaine<<"\t"<<PartName<<"\t"<<ID<<endl;
        //cout<<PreVolumName<<endl;
        if(PartName=="e-" && eventaction->GetElectronFlag(num_IP) == false)
        {
          //runaction->EcrireDistribElectrons(num_IP, Energy);
          //G4cout << "Energy e- = " << Energy << G4endl;
          eventaction->SetIncidentELecStack(num_IP, Energy);
          if(num_IP==0) eventaction->SetIncidentElecStack1(Energy);
          if(num_IP==1) eventaction->SetIncidentElecStack2(Energy);
          if(num_IP==2) eventaction->SetIncidentElecStack3(Energy);
          if(num_IP==3) eventaction->SetIncidentElecStack4(Energy);
          if(num_IP==4) eventaction->SetIncidentElecStack5(Energy);
          if(num_IP==5) eventaction->SetIncidentElecStack6(Energy);
          if(num_IP==6) eventaction->SetIncidentElecStack7(Energy);
          //G4cout << "E incident elec [" << num_IP << "]= " << Energy << G4endl;
          eventaction->ActiveElectronFlag(num_IP);
        }

        else if(PartName=="gamma")
        {
          //runaction->EcrireDistribGammas(num_IP, Energy);
          //G4cout << "Energy gamma = " << Energy << G4endl;
          if(num_IP==0) eventaction->FillIncidentGammaStack1(Energy);
          if(num_IP==1) eventaction->FillIncidentGammaStack2(Energy);
          if(num_IP==2) eventaction->FillIncidentGammaStack3(Energy);
          if(num_IP==3) eventaction->FillIncidentGammaStack4(Energy);
          if(num_IP==4) eventaction->FillIncidentGammaStack5(Energy);
          if(num_IP==5) eventaction->FillIncidentGammaStack6(Energy);
          if(num_IP==6) eventaction->FillIncidentGammaStack7(Energy);
          //G4cout << "E incident gamma [" << num_IP << "]= " << Energy << G4endl;
        }
      }


      sprintf(chaine,"Stack_IP2_%d",num_IP+1);

      if(PreVolumName==chaine){

        runaction->AddEnergyTot(num_IP,Edep);
        // G4cout << "Z = " << z << G4endl;
        // G4cout << "Z (pre) = " << prePoint.z() << G4endl;
        // G4cout << "Z (post) = " << postPoint.z() << G4endl;
        // G4cout << "Z (rand) = " << point.z() << G4endl;
        // G4cout << "IDPartName = " << eventaction->GetIDPartName() << G4endl;
        // G4cout << "Edep [" << num_IP << "]= " << Edep << G4endl;

        if(eventaction->GetIDPartName()=="e-")
        {
          //G4cout<<"energie ajoutée coeff e-"<<"\t"<<Edep<<"\t"<<num_IP<<"\t"<<PartName<<"\t"<<ProcessName<<G4endl;
          //G4cout << "E dep elec [" << num_IP << "]= " << Edep << G4endl;
          runaction->AddElectronEnergy(num_IP,Edep);
          eventaction->ActiveFlagGoodEvent();
          if(num_IP==0)
          {
            eventaction->AddEdepElecStack1(Edep);
            EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP1)/Labs);
            runaction->AddEnergyTotEff(num_IP,EdepEff);
            runaction->AddElectronEnergyEff(num_IP,EdepEff);
            eventaction->AddEffEdepElecStack1(EdepEff);
            // G4cout << "Z (IP) = " << point.z()-PosZ_Sensitive_IP1 << G4endl;
            // G4cout << "Edep Eff [" << num_IP << "]= " << EdepEff << G4endl;

            if(eventaction->GetPositionElectronFlag(num_IP) ==false)
            {
              eventaction->SetXPositionElecStack1(x);
              eventaction->SetYPositionElecStack1(y);
              eventaction->ActivePositionElectronFlag(num_IP);
            }
          }

          if(num_IP==1)
          {
            eventaction->AddEdepElecStack2(Edep);
            EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP2)/Labs);
            runaction->AddEnergyTotEff(num_IP,EdepEff);
            runaction->AddElectronEnergyEff(num_IP,EdepEff);
            eventaction->AddEffEdepElecStack2(EdepEff);

            if(eventaction->GetPositionElectronFlag(num_IP) ==false)
            {
              eventaction->SetXPositionElecStack2(x);
              eventaction->SetYPositionElecStack2(y);
              eventaction->ActivePositionElectronFlag(num_IP);
            }
          }

          if(num_IP==2)
          {
            eventaction->AddEdepElecStack3(Edep);
            EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP3)/Labs);
            runaction->AddEnergyTotEff(num_IP,EdepEff);
            runaction->AddElectronEnergyEff(num_IP,EdepEff);
            eventaction->AddEffEdepElecStack3(EdepEff);

            if(eventaction->GetPositionElectronFlag(num_IP) ==false)
            {
              eventaction->SetXPositionElecStack3(x);
              eventaction->SetYPositionElecStack3(y);
              eventaction->ActivePositionElectronFlag(num_IP);
            }
          }

          if(num_IP==3)
          {
            eventaction->AddEdepElecStack4(Edep);
            EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP4)/Labs);
            runaction->AddEnergyTotEff(num_IP,EdepEff);
            runaction->AddElectronEnergyEff(num_IP,EdepEff);
            eventaction->AddEffEdepElecStack4(EdepEff);

            if(eventaction->GetPositionElectronFlag(num_IP) ==false)
            {
              eventaction->SetXPositionElecStack4(x);
              eventaction->SetYPositionElecStack4(y);
              eventaction->ActivePositionElectronFlag(num_IP);
            }
          }

          if(num_IP==4)
          {
            eventaction->AddEdepElecStack5(Edep);
            EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP5)/Labs);
            runaction->AddEnergyTotEff(num_IP,EdepEff);
            runaction->AddElectronEnergyEff(num_IP,EdepEff);
            eventaction->AddEffEdepElecStack5(EdepEff);

            if(eventaction->GetPositionElectronFlag(num_IP) ==false)
            {
              eventaction->SetXPositionElecStack5(x);
              eventaction->SetYPositionElecStack5(y);
              eventaction->ActivePositionElectronFlag(num_IP);
            }
          }

          if(num_IP==5)
          {
            eventaction->AddEdepElecStack6(Edep);
            EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP6)/Labs);
            runaction->AddEnergyTotEff(num_IP,EdepEff);
            runaction->AddElectronEnergyEff(num_IP,EdepEff);
            eventaction->AddEffEdepElecStack6(EdepEff);

            if(eventaction->GetPositionElectronFlag(num_IP) ==false)
            {
              eventaction->SetXPositionElecStack6(x);
              eventaction->SetYPositionElecStack6(y);
              eventaction->ActivePositionElectronFlag(num_IP);
            }
          }

          if(num_IP==6)
          {
            eventaction->AddEdepElecStack7(Edep);
            EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP7)/Labs);
            runaction->AddEnergyTotEff(num_IP,EdepEff);
            runaction->AddElectronEnergyEff(num_IP,EdepEff);
            eventaction->AddEffEdepElecStack7(EdepEff);

            if(eventaction->GetPositionElectronFlag(num_IP) ==false)
            {
              eventaction->SetXPositionElecStack7(x);
              eventaction->SetYPositionElecStack7(y);
              eventaction->ActivePositionElectronFlag(num_IP);
            }
          }

        }

        if(eventaction->GetIDPartName()=="gamma")
        {
          runaction->AddGammaEnergy(num_IP,Edep);
          eventaction->ActiveFlagGoodEvent();
          if(num_IP==0)
          {
            //G4cout << "Edep = " << Edep << G4endl;
            eventaction->AddEdepGammaStack1(Edep);
            EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP1)/Labs);
            //G4cout << "Edep Eff = " << EdepEff << G4endl;
            runaction->AddEnergyTotEff(num_IP,EdepEff);
            runaction->AddGammaEnergyEff(num_IP,EdepEff);
            eventaction->AddEffEdepGammaStack1(EdepEff);

            if(eventaction->GetPositionGammaFlag(num_IP) ==false)
            {
              eventaction->SetXPositionGammaStack1(x);
              eventaction->SetYPositionGammaStack1(y);
              eventaction->ActivePositionGammaFlag(num_IP);
            }
          }
          if(num_IP==1)
          {
            eventaction->AddEdepGammaStack2(Edep);
            EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP2)/Labs);
            runaction->AddEnergyTotEff(num_IP,EdepEff);
            runaction->AddGammaEnergyEff(num_IP,EdepEff);
            eventaction->AddEffEdepGammaStack2(EdepEff);
            if(eventaction->GetPositionGammaFlag(num_IP) ==false)
            {
              eventaction->SetXPositionGammaStack2(x);
              eventaction->SetYPositionGammaStack2(y);
              eventaction->ActivePositionGammaFlag(num_IP);
            }
          }
          if(num_IP==2)
          {
            eventaction->AddEdepGammaStack3(Edep);
            EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP3)/Labs);
            runaction->AddEnergyTotEff(num_IP,EdepEff);
            runaction->AddGammaEnergyEff(num_IP,EdepEff);
            eventaction->AddEffEdepGammaStack3(EdepEff);

            if(eventaction->GetPositionGammaFlag(num_IP) ==false)
            {
              eventaction->SetXPositionGammaStack3(x);
              eventaction->SetYPositionGammaStack3(y);
              eventaction->ActivePositionGammaFlag(num_IP);
            }
          }

          if(num_IP==3)
          {
            eventaction->AddEdepGammaStack4(Edep);
            EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP4)/Labs);
            runaction->AddEnergyTotEff(num_IP,EdepEff);
            runaction->AddGammaEnergyEff(num_IP,EdepEff);
            eventaction->AddEffEdepGammaStack4(EdepEff);

            if(eventaction->GetPositionGammaFlag(num_IP) ==false)
            {
              eventaction->SetXPositionGammaStack4(x);
              eventaction->SetYPositionGammaStack4(y);
              eventaction->ActivePositionGammaFlag(num_IP);
            }
          }

          if(num_IP==4)
          {
            eventaction->AddEdepGammaStack5(Edep);
            EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP5)/Labs);
            runaction->AddEnergyTotEff(num_IP,EdepEff);
            runaction->AddGammaEnergyEff(num_IP,EdepEff);
            eventaction->AddEffEdepGammaStack5(EdepEff);

            if(eventaction->GetPositionGammaFlag(num_IP) ==false)
            {
              eventaction->SetXPositionGammaStack5(x);
              eventaction->SetYPositionGammaStack5(y);
              eventaction->ActivePositionGammaFlag(num_IP);
            }
          }

          if(num_IP==5)
          {
            eventaction->AddEdepGammaStack6(Edep);
            EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP6)/Labs);
            runaction->AddEnergyTotEff(num_IP,EdepEff);
            runaction->AddGammaEnergyEff(num_IP,EdepEff);
            eventaction->AddEffEdepGammaStack6(EdepEff);

            if(eventaction->GetPositionGammaFlag(num_IP) ==false)
            {
              eventaction->SetXPositionGammaStack6(x);
              eventaction->SetYPositionGammaStack6(y);
              eventaction->ActivePositionGammaFlag(num_IP);
            }
          }

          if(num_IP==6)
          {
            eventaction->AddEdepGammaStack7(Edep);
            EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP7)/Labs);
            runaction->AddEnergyTotEff(num_IP,EdepEff);
            runaction->AddGammaEnergyEff(num_IP,EdepEff);
            eventaction->AddEffEdepGammaStack7(EdepEff);

            if(eventaction->GetPositionGammaFlag(num_IP) ==false)
            {
              eventaction->SetXPositionGammaStack7(x);
              eventaction->SetYPositionGammaStack7(y);
              eventaction->ActivePositionGammaFlag(num_IP);
            }
          }

          if(eventaction->GetIDPartName()!="gamma" && eventaction->GetIDPartName()!="e-")
          {
            eventaction->ActiveFlagGoodEvent();
            if(num_IP==0)
            {
              EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP1)/Labs);
              runaction->AddEnergyTotEff(num_IP,EdepEff);
            }

            if(num_IP==1)
            {
              EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP2)/Labs);
              runaction->AddEnergyTotEff(num_IP,EdepEff);
            }

            if(num_IP==2)
            {
              EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP3)/Labs);
              runaction->AddEnergyTotEff(num_IP,EdepEff);
            }

            if(num_IP==3)
            {
              EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP4)/Labs);
              runaction->AddEnergyTotEff(num_IP,EdepEff);
            }

            if(num_IP==4)
            {
              EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP5)/Labs);
              runaction->AddEnergyTotEff(num_IP,EdepEff);
            }

            if(num_IP==5)
            {
              EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP6)/Labs);
              runaction->AddEnergyTotEff(num_IP,EdepEff);
            }

            if(num_IP==6)
            {
              EdepEff = Edep*exp(-(point.z()-PosZ_Sensitive_IP7)/Labs);
              runaction->AddEnergyTotEff(num_IP,EdepEff);
            }
          }
        }// fin if
      }
    }//fin for





    if(Parent_ID>0)
    {
      if(track->GetCreatorProcess()->GetProcessName() == "eBrem")
      {
        if(StepNo==1)
        {
          //G4cout << "Brem with E = " << Energy << G4endl;
          eventaction->FillEBremCreation(Energy);
        }
        if(VolumName=="PhysicalWorld")
        {
          eventaction->FillEBremExit(Energy);
        }
      }
    }

  }
