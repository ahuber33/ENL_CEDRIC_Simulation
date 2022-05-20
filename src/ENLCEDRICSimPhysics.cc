/// ENLCEDRICSimPhysics.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLCEDRICSimPhysics.hh"
//#include "G4MuNuclearInteraction.hh"
#include "G4KokoulinMuonNuclearXS.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4ShortLivedConstructor.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4ios.hh"
#include "G4OpWLS.hh"
#include "G4GenericIon.hh"
#include "G4Decay.hh"
#include "G4IonConstructor.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4ParticleDefinition.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProcessManager.hh"
#include "G4LossTableManager.hh"
#include "G4EmSaturation.hh"

using namespace CLHEP;

// Taken from N06 and LXe examples in GEANT4

ENLCEDRICSimPhysics::ENLCEDRICSimPhysics():  G4VModularPhysicsList()
{
  // Here used the default cut value you have typed in

  //defaultCutValue = 0.001*mm; //0.001
  defaultCutValue = 100*nm; //0.001
  //was 0.5*mm

  SetVerboseLevel(1);

  //default physics
  particleList = new G4DecayPhysics();

  //default physics
  raddecayList = new G4RadioactiveDecayPhysics();

  // EM physics
  emPhysicsList = new G4EmStandardPhysics_option3();
}

ENLCEDRICSimPhysics::~ENLCEDRICSimPhysics(){
  delete raddecayList;
  delete emPhysicsList;
}

void ENLCEDRICSimPhysics::ConstructParticle()
{
  // Here are constructed all particles you have chosen
  particleList->ConstructParticle();
  //ConstructBosons();
  //ConstructLeptons();
  //ConstructMesons();
  //ConstructBaryons();
  //ConstructAllShortLiveds();
  //G4GenericIon::GenericIonDefinition();
  //G4IonConstructor iConstructor;
  //iConstructor.ConstructParticle();
}



void ENLCEDRICSimPhysics::ConstructProcess()
{
  // Transportation, electromagnetic and general processes

  AddTransportation();
  //ConstructEM();
  //ConstructGeneral();
  // Electromagnetic physics list
  emPhysicsList->ConstructProcess();
  particleList->ConstructProcess();
  raddecayList->ConstructProcess();
}

void ENLCEDRICSimPhysics::SetCuts()
{
  // defaultCutValue you have typed in is used

  if (verboseLevel >1){
    G4cout << "opticalPhysics::SetCuts:";
  }
  SetCutsWithDefault();
  //  SetCutValue(5*mm,"opticalphoton");
}
