/// Geometry.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

// This class is used to create a plastic scintillator.

#ifndef Geometry_h
#define Geometry_h

#include "G4LogicalVolume.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "CLHEP/Units/SystemOfUnits.h"

class ENLOpticalSimMaterials;
class Geometry

{
public:

  //constructor, builds from keys specified in buildfile
  Geometry(G4String buildfile);
  ~Geometry();
  //  void Construct();

public:

  G4LogicalVolume *GetTantale2mm();
  G4LogicalVolume *GetTantale4mm();
  G4LogicalVolume *GetTantale28mm();
  G4LogicalVolume *GetStackIP1();
  G4LogicalVolume *GetStackIP2();
  G4LogicalVolume *GetStackIP3();
  G4LogicalVolume *GetStackIP4();
  G4LogicalVolume *GetBlocMylar();
  G4LogicalVolume *GetCylindreTantale();
  G4LogicalVolume *GetDisqueAlu();

  G4double GetRayonCylindreInterieur(){return Rayon_cylindre_interieur;}
  G4double GetRayonCylindreExterieur(){return Rayon_cylindre_exterieur;}
  G4double GetStackIPPosIni(){return Stack_IP_pos_ini;}
  G4double GetDisqueAluEpaisseur(){return Disque_alu_epaisseur;}
  G4double GetBlocMylarHauteur(){return Bloc_mylar_hauteur;}
  G4double GetCylindreTantaleHauteur(){return Cylindre_tantale_hauteur;}
  G4double GetNombreIP(){return Nombre_IP;}
  G4double GetIPa1z(){return IPa1_z;}
  G4double GetIPa2z(){return IPa2_z;}
  G4double GetIPa3z(){return IPa3_z;}
  G4double GetIPa4z(){return IPa4_z;}


private:


  Geometry *Geom;
  ENLCEDRICSimMaterials* scintProp;

  static const G4String path_bin;


  // Materials
  G4Material *Material;

  // Logical Volumes
  G4LogicalVolume *LogicalVolume;

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

  // Other
  G4VisAttributes *clear;

};
#endif
