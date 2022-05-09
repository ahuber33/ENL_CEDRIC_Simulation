/// ENLCEDRICSimPhysics.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef  ENLCEDRICSimPhysics_h
#define   ENLCEDRICSimPhysics_h  1

//#include "G4VUserPhysicsList.hh"
#include "G4VModularPhysicsList.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
class  ENLCEDRICSimPhysics:  public G4VModularPhysicsList
{      public:
  ENLCEDRICSimPhysics();
  virtual ~ENLCEDRICSimPhysics();

protected:
  virtual void ConstructParticle();
  virtual void ConstructProcess();
  virtual void SetCuts();


private:
  G4VPhysicsConstructor*  emPhysicsList;
  G4VPhysicsConstructor*  particleList;
  G4VPhysicsConstructor*  raddecayList;
};
#endif
