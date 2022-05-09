/// ENLCEDRICSimSteppingAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef ENLCEDRICSimSteppingAction_h
#define ENLCEDRICSimSteppingAction_h

#include "G4UserSteppingAction.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalVolume.hh"
#include "TH2F.h"
#include "TFile.h"

class G4Step;
class G4SteppingManager;
class ENLCEDRICSimGeometry;
class ENLCEDRICSimRunAction;
class ENLCEDRICSimEventAction;

class ENLCEDRICSimSteppingAction : public G4UserSteppingAction
{
public:
  ENLCEDRICSimSteppingAction(ENLCEDRICSimGeometry*,ENLCEDRICSimRunAction*,ENLCEDRICSimEventAction*);
  ~ENLCEDRICSimSteppingAction();
public:
  void UserSteppingAction(const G4Step*);



private:
  ENLCEDRICSimGeometry * detector;
  ENLCEDRICSimRunAction* runaction;
  ENLCEDRICSimEventAction* eventaction;
  static const G4String path;
  int PreviousTrack;
  double Length_Track;
  double Total_Length_Track;


};
#endif
