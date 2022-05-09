/// ENLCEDRICSimMaterials.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

// This class is used to create a plastic scintillator.

#ifndef ENLCEDRICSimMaterials_h
#define ENLCEDRICSimMaterials_h


#include "G4MaterialPropertiesTable.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4OpticalSurface.hh"
#include "CLHEP/Units/SystemOfUnits.h"

class G4Material;

class ENLCEDRICSimMaterials
{
public:

  ENLCEDRICSimMaterials(G4String prop_buildfile);
  ~ENLCEDRICSimMaterials();
  void Construct();

public:
  G4Material *GetMaterial(G4String);


private:

  static const G4String path;

  //materiaux
  G4Material* vacuum;
  G4Material* C;
  G4Material* Al;
  G4Material* Fe;
  G4Material* Pb;
  G4Material* Cu;
  G4Material* Ta;
  G4Material* Air;
  G4Material* Default_Material;
  G4Material* Polyester;
  G4Material* Sensitive;
  G4Material* Base;

  G4String TypeIP;
  G4int Nbre_IP;

  G4double scintAbsorbconst;
  G4double scintIndexconst;
  G4double scalingfactor_low;
  G4double scalingfactor_high;
  G4double pop_scalingfactor_low;
  G4double pop_scalingfactor_high;
  G4double lightyield;
  G4double paint_ref_coeff;
  G4double mylar_ref_coeff;
  G4double pWavelength;
  G4double ratio;


};
#endif
