/// ENLCEDRICSimGeometry.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef ENLCEDRICSimGeometry_h
#define ENLCEDRICSimGeometry_h  1

#include "G4MaterialPropertiesTable.hh"

class Geometry;
class ENLCEDRICSimMaterials;
class G4VPhysicalVolume;

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "CLHEP/Units/SystemOfUnits.h"

class  ENLCEDRICSimGeometry:  public G4VUserDetectorConstruction
{
public:
  ENLCEDRICSimGeometry();
  ~ENLCEDRICSimGeometry();

public:
  G4VPhysicalVolume* Construct();
  G4LogicalVolume* GetLWorld() {return LogicalWorld;}

private:
  static const G4String path_bin;
  static const G4String path;
  // Classes for building various components
  //     LogicalHolder *holder;
  ENLCEDRICSimMaterials *scintProp;
  Geometry *Geom;
  G4Material *Vacuum;
  G4Material *VacuumWorld;
  G4Material *Air;
  G4Material *Alu;

  // Colors for visualizations
  G4VisAttributes *invis;
  G4VisAttributes *white;
  G4VisAttributes *gray;
  G4VisAttributes *gray_bis;
  G4VisAttributes *black;
  G4VisAttributes *black_bis;
  G4VisAttributes *red;
  G4VisAttributes *red_hot;
  G4VisAttributes *orange;
  G4VisAttributes *yellow;
  G4VisAttributes *green;
  G4VisAttributes *green_hot;
  G4VisAttributes *cyan;
  G4VisAttributes *blue;
  G4VisAttributes *magenta;

  // Logical Volumes
  G4LogicalVolume *LogicalWorld;
  G4LogicalVolume *LogicalTantale2mm;
  G4LogicalVolume *LogicalTantale4mm;
  G4LogicalVolume *LogicalTantale28mm;
  G4LogicalVolume *LogicalStackIP1;
  G4LogicalVolume *LogicalStackIP2;
  G4LogicalVolume *LogicalStackIP3;
  G4LogicalVolume *LogicalStackIP4;
  G4LogicalVolume *LogicalDisqueAlu;
  G4LogicalVolume *LogicalCylindreTantale;
  G4LogicalVolume *LogicalBlocMylar;



  // Physical volumes
  G4VPhysicalVolume *PhysicalWorld;
  G4VPhysicalVolume *PhysicalTantale2mm;
  G4VPhysicalVolume* physiStackIP1[10];
  G4VPhysicalVolume* physiStackIP2[10];
  G4VPhysicalVolume* physiStackIP3[10];
  G4VPhysicalVolume* physiStackIP4[10];
  G4VPhysicalVolume* physiDisqueTa[10];
  G4VPhysicalVolume* Bloc_Mylar_phys;
  G4VPhysicalVolume* Cylindre_Tantale_phys;
  G4VPhysicalVolume* Cylindre_Disque_Alu_entree;
  G4VPhysicalVolume* Cylindre_Disque_Alu_sortie;

  G4double Rayon_cylindre_interieur;
  G4double Rayon_cylindre_exterieur;
  G4double Stack_IP_pos_ini;
  G4double Disque_alu_epaisseur;
  G4double Bloc_mylar_hauteur;
  G4double Cylindre_tantale_hauteur;
  G4int Nombre_IP;
  G4double IPa1_z;
  G4double IPa2_z;
  G4double IPa3_z;
  G4double IPa4_z;


};
#endif
