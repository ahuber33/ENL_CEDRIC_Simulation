// Geometry.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLCEDRICSimMaterials.hh"
#include "Geometry.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Transform3D.hh"
#include "G4UnionSolid.hh"
#include <fstream>
#include <iostream>
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Polyhedra.hh"
#include <G4Polycone.hh>
#include "G4Sphere.hh"
#include "G4Trap.hh"
#include "G4Trd.hh"
#include "G4SubtractionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4UnitsTable.hh"
#include <math.h>

//#ifndef disable_gdml
#include "G4GDMLParser.hh"
//#endif


using namespace CLHEP;

// ***********************
// Constructor
// ***********************
const G4String Geometry::path_bin = "../bin/";


Geometry::Geometry(G4String buildfile){

  // Read keys and values from file buildfile defined in x_blockGeometry.cc
  // Some of these variables may not be needed.
  std::ifstream config;
  config.open(buildfile);
  if ( !config.is_open() )
    G4cout << "Error opening file " << buildfile << G4endl;
  else{
    while( config.is_open() ){
      G4String variable;
      G4String unit;
      G4double value;

      config >> variable;
      if(!config.good()) break;
      //####################### COMMON variables ###########################
      if(variable == "Rayon_cylindre_interieur"){
  	config >> value >> unit;
  	Rayon_cylindre_interieur = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "Rayon_cylindre_exterieur"){
  	config >> value >> unit;
  	Rayon_cylindre_exterieur = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "Stack_IP_pos_ini"){
  	config >> value >> unit;
  	Stack_IP_pos_ini = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "Bloc_mylar_hauteur"){
  	config >> value >> unit;
  	Bloc_mylar_hauteur = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "Cylindre_tantale_hauteur"){
  	config >> value >> unit;
  	Cylindre_tantale_hauteur = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "Disque_alu_epaisseur"){
  	config >> value >> unit;
  	Disque_alu_epaisseur = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "Nombre_IP"){
  	config >> value;
  	Nombre_IP = value;
      }
      else if(variable == "IPa1_z"){
  	config >> value >> unit;
  	IPa1_z = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "IPa2_z"){
  	config >> value >> unit;
  	IPa2_z = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "IPa3_z"){
  	config >> value >> unit;
  	IPa3_z = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "IPa4_z"){
  	config >> value >> unit;
  	IPa4_z = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "Epaisseur_tantale1_2"){
  	config >> value >> unit;
  	Epaisseur_tantale1_2 = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "Epaisseur_tantale2_3"){
  	config >> value >> unit;
  	Epaisseur_tantale2_3 = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "Epaisseur_tantale3_4"){
  	config >> value >> unit;
  	Epaisseur_tantale3_4 = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "Epaisseur_tantale4_5"){
  	config >> value >> unit;
  	Epaisseur_tantale4_5 = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "Epaisseur_tantale5_6"){
  	config >> value >> unit;
  	Epaisseur_tantale5_6 = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "Epaisseur_tantale6_7"){
  	config >> value >> unit;
  	Epaisseur_tantale6_7 = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "Labs"){
  	config >> value >> unit;
  	Labs = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "Coef_PSL"){
  	config >> value >> unit;
  	Coef_PSL = value;
      }
    }
  }
  config.close();



    G4cout << "\n The Variables that we read in are: "
    << "\n Rayon_cylindre_interieur = " << Rayon_cylindre_interieur
    << "\n Rayon_cylindre_exterieur = " << Rayon_cylindre_exterieur
    << "\n Disque_alu_epaisseur = " << Disque_alu_epaisseur
    << "\n Bloc_mylar_hauteur = " << Bloc_mylar_hauteur
    << "\n Cylindre_tantale_hauteur = " << Cylindre_tantale_hauteur
    << "\n Nombre IP = " << Nombre_IP
    << "\n IPa1_z = " << IPa1_z
    << "\n IPa2_z = " << IPa2_z
    << "\n IPa3_z = " << IPa3_z
    << "\n IPa4_z = " << IPa4_z
    << "\n Epaisseur tantale 1->2 = " << Epaisseur_tantale1_2
    << "\n Epaisseur tantale 2->3 = " << Epaisseur_tantale2_3
    << "\n Epaisseur tantale 3->4 = " << Epaisseur_tantale3_4
    << "\n Epaisseur tantale 4->5 = " << Epaisseur_tantale4_5
    << "\n Epaisseur tantale 5->6 = " << Epaisseur_tantale5_6
    << "\n Epaisseur tantale 6->7 = " << Epaisseur_tantale6_7
    << "\n Labs = " << Labs
    << "\n Coef PSL = " << Coef_PSL

    << "\n " << G4endl;

}
// ***********************
// Destructor
// ***********************
Geometry::~Geometry(){
  if(scintProp) { delete scintProp; scintProp = 0; }
  if(clear) { delete clear; clear = 0; }
}


G4LogicalVolume *Geometry::GetTantale1_2(){

  Material = scintProp->GetMaterial("Tantale");
  //Material = scintProp->GetMaterial("Aluminium");

  G4VSolid* solid = new G4Tubs("solid",0.,Rayon_cylindre_interieur, (Epaisseur_tantale1_2/2)*mm,0.,360.*deg);
  LogicalVolume = new G4LogicalVolume(solid, Material,"Ta_1_2");

  return LogicalVolume;
}


G4LogicalVolume *Geometry::GetTantale2_3(){

  Material = scintProp->GetMaterial("Tantale");
  //Material = scintProp->GetMaterial("Aluminium");

  G4VSolid* solid = new G4Tubs("solid",0.,Rayon_cylindre_interieur, (Epaisseur_tantale2_3/2)*mm,0.,360.*deg);
  LogicalVolume = new G4LogicalVolume(solid, Material,"Ta_2_3");

  return LogicalVolume;
}

G4LogicalVolume *Geometry::GetTantale3_4(){

  Material = scintProp->GetMaterial("Tantale");
  //Material = scintProp->GetMaterial("Aluminium");

  G4VSolid* solid = new G4Tubs("solid",0.,Rayon_cylindre_interieur, (Epaisseur_tantale3_4/2)*mm,0.,360.*deg);
  LogicalVolume = new G4LogicalVolume(solid, Material,"Ta_3_4");

  return LogicalVolume;
}


G4LogicalVolume *Geometry::GetTantale4_5(){

  Material = scintProp->GetMaterial("Tantale");
  //Material = scintProp->GetMaterial("Aluminium");

  G4VSolid* solid = new G4Tubs("solid",0.,Rayon_cylindre_interieur, (Epaisseur_tantale4_5/2)*mm,0.,360.*deg);
  LogicalVolume = new G4LogicalVolume(solid, Material,"Ta_4_5");

  return LogicalVolume;
}


G4LogicalVolume *Geometry::GetTantale5_6(){

  Material = scintProp->GetMaterial("Tantale");
  //Material = scintProp->GetMaterial("Aluminium");

  G4VSolid* solid = new G4Tubs("solid",0.,Rayon_cylindre_interieur, (Epaisseur_tantale5_6/2)*mm,0.,360.*deg);
  LogicalVolume = new G4LogicalVolume(solid, Material,"Ta_5_6");

  return LogicalVolume;
}


G4LogicalVolume *Geometry::GetTantale6_7(){

  Material = scintProp->GetMaterial("Tantale");
  //Material = scintProp->GetMaterial("Aluminium");

  G4VSolid* solid = new G4Tubs("solid",0.,Rayon_cylindre_interieur, (Epaisseur_tantale6_7/2)*mm,0.,360.*deg);
  LogicalVolume = new G4LogicalVolume(solid, Material,"Ta_6_7");

  return LogicalVolume;
}


G4LogicalVolume *Geometry::GetStackIP1(){

  Material = scintProp->GetMaterial("Polyester");

  G4VSolid* solid = new G4Tubs("Stack_IP1",0.,Rayon_cylindre_interieur,IPa1_z/2.,0.,360.*deg);
  LogicalVolume = new G4LogicalVolume(solid, Material,"Stack_IP1");

  return LogicalVolume;
}


G4LogicalVolume *Geometry::GetStackIP2(){

  Material = scintProp->GetMaterial("Sensitive");

  G4VSolid* solid = new G4Tubs("Stack_IP2",0.,Rayon_cylindre_interieur,IPa2_z/2.,0.,360.*deg);
  LogicalVolume = new G4LogicalVolume(solid, Material,"Stack_IP2");

  return LogicalVolume;
}


G4LogicalVolume *Geometry::GetStackIP3(){

  Material = scintProp->GetMaterial("Polyester");

  G4VSolid* solid = new G4Tubs("Stack_IP3",0.,Rayon_cylindre_interieur,IPa3_z/2.,0.,360.*deg);
  LogicalVolume = new G4LogicalVolume(solid, Material,"Stack_IP3");

  return LogicalVolume;
}


G4LogicalVolume *Geometry::GetStackIP4(){

  Material = scintProp->GetMaterial("Base");

  G4VSolid* solid = new G4Tubs("Stack_IP4",0.,Rayon_cylindre_interieur,IPa4_z/2.,0.,360.*deg);
  LogicalVolume = new G4LogicalVolume(solid, Material,"Stack_IP4");

  return LogicalVolume;
}


G4LogicalVolume *Geometry::GetBlocMylar(){

  Material = scintProp->GetMaterial("Polyester");

  G4VSolid* solid = new G4Tubs("Bloc_mylar",0., Rayon_cylindre_interieur, Bloc_mylar_hauteur/2.,0.,360.*deg);
  LogicalVolume = new G4LogicalVolume(solid, Material,"Bloc_mylar");

  return LogicalVolume;
}


G4LogicalVolume *Geometry::GetCylindreTantale(){

  Material = scintProp->GetMaterial("Tantale");

  G4VSolid* solid = new G4Tubs("Cylindre_Tantale", Rayon_cylindre_interieur, Rayon_cylindre_exterieur, Cylindre_tantale_hauteur/2.,0.,360.*deg);
  LogicalVolume = new G4LogicalVolume(solid, Material,"Cylindre_Tantale");

  return LogicalVolume;
}


G4LogicalVolume *Geometry::GetDisqueAlu(){

  Material = scintProp->GetMaterial("Aluminium");

  G4VSolid* solid = new G4Tubs("Disque_Alu",0., Rayon_cylindre_exterieur, Disque_alu_epaisseur/2.,0.,360.*deg);
  LogicalVolume = new G4LogicalVolume(solid, Material,"Cylindre_Tantale");

  return LogicalVolume;
}
