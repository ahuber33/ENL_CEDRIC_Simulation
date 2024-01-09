// ENLCEDRICSimGeometry_test.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2017 (C) Projet BADGE - CARMELEC -P2R

#include "ENLCEDRICSimGeometry.hh"
#include "ENLCEDRICSimRunAction.hh"
#include "ENLCEDRICSimMaterials.hh"
#include "ENLCEDRICSimSteppingAction.hh"
#include "Geometry.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4UnitsTable.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4Box.hh"
#include "G4Orb.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4SDManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RunManager.hh"
#include "G4Transform3D.hh"
#include "G4SurfaceProperty.hh"
#include "globals.hh"
#include <fstream>
#include <iostream>

using namespace CLHEP;

const G4String ENLCEDRICSimGeometry::path_bin = "../bin/";
const G4String ENLCEDRICSimGeometry::path = "../simulation_input_files/";

// Constructor
ENLCEDRICSimGeometry::ENLCEDRICSimGeometry(){
  for (int i=0;i<10;i++) {
    physiStackIP1[i]=0;
    physiStackIP2[i]=0;
    physiStackIP3[i]=0;
    physiStackIP4[i]=0;
  }
}

// Destructor
ENLCEDRICSimGeometry::~ENLCEDRICSimGeometry()
{
}

// Main Function: Builds Full block, coupling, and PMT geometries
G4VPhysicalVolume* ENLCEDRICSimGeometry::Construct( ){
  // Initialize scint classes
  scintProp = new ENLCEDRICSimMaterials(path_bin+"Materials.cfg");
  Vacuum = scintProp->GetMaterial("vacuum");
  Air = scintProp->GetMaterial("Air");
  Geom = new Geometry(path_bin+"ENLCEDRICSim.cfg");


  // ***********************
  // Visualization Colors
  // ***********************
  // Create some colors for visualizations
  invis = new G4VisAttributes( G4Colour(255/255. ,255/255. ,255/255. ));
  invis->SetVisibility(false);

  white = new G4VisAttributes(G4Colour(1,1,1,0.1)); // Sets the color (can be looked up online)
  //white->SetForceWireframe(true); // Sets to wire frame mode for coloring the volume
  white->SetForceSolid(true); // Sets to solid mode for coloring the volume
  white->SetVisibility(true); // Makes color visible in visualization

  gray = new G4VisAttributes(G4Colour(0.5,0.5,0.5,0.5));
  //  gray->SetForceWireframe(true);
  gray->SetForceSolid(true);
  gray->SetVisibility(true);

  gray_bis = new G4VisAttributes(G4Colour(0.5,0.5,0.5,0.25));
  //  gray->SetForceWireframe(true);
  gray_bis->SetForceSolid(true);
  gray_bis->SetVisibility(true);

  black = new G4VisAttributes(G4Colour(0,0,0,0.7));
  //  black->SetForceWireframe(true);
  black->SetForceSolid(true);
  black->SetVisibility(true);


  black_bis = new G4VisAttributes(G4Colour(0,0,0,0.4));
  //  black->SetForceWireframe(true);
  black_bis->SetForceSolid(true);
  black_bis->SetVisibility(true);

  red = new G4VisAttributes(G4Colour(1,0,0,0.5));
  //  red->SetForceWireframe(true);
  red->SetForceSolid(true);
  red->SetVisibility(true);


  red_hot = new G4VisAttributes(G4Colour(1,0,0,1));
  //  red->SetForceWireframe(true);
  red_hot->SetForceSolid(true);
  red_hot->SetVisibility(true);

  orange = new G4VisAttributes(G4Colour(1,0.5,0,0.2));
  //  orange->SetForceWireframe(true);
  orange->SetForceSolid(true);
  orange->SetVisibility(true);

  yellow = new G4VisAttributes(G4Colour(1,1,0,0.39));
  //  yellow->SetForceWireframe(true);
  yellow->SetForceSolid(true);
  yellow->SetVisibility(true);

  green = new G4VisAttributes(G4Colour(0,1,0,0.35));
  //  green->SetForceWireframe(true);
  green->SetForceSolid(true);
  green->SetVisibility(true);

  green_hot = new G4VisAttributes(G4Colour(0,1,0,1));
  //  green_hot->SetForceWireframe(true);
  green_hot->SetForceSolid(true);
  green_hot->SetVisibility(true);

  cyan = new G4VisAttributes(G4Colour(0,1,1,0.55));
  //  cyan->SetForceWireframe(true);
  cyan->SetForceSolid(true);
  cyan->SetVisibility(true);

  blue = new G4VisAttributes(G4Colour(0,0,1,0.3));
  //  blue->SetForceWireframe(true);
  blue->SetForceSolid(true);
  blue->SetVisibility(true);

  magenta = new G4VisAttributes(G4Colour(1,0,1,0.85));
  //  magenta->SetForceWireframe(true);
  //magenta->SetForceSolid(true);
  magenta->SetVisibility(true);

  // Define common rotations
  G4RotationMatrix DontRotate;
  DontRotate.rotateX(0.0*deg);
  G4RotationMatrix Flip;
  Flip.rotateZ(0*deg);
  Flip.rotateX(180*deg);
  Flip.rotateY(0*deg);


  // ***********************
  // Various dimensions
  // ***********************
  Stack_IP_pos_ini = Geom->GetStackIPPosIni();
  Rayon_cylindre_exterieur = Geom->GetRayonCylindreExterieur();
  Rayon_cylindre_interieur = Geom->GetRayonCylindreInterieur();
  Disque_alu_epaisseur = Geom->GetDisqueAluEpaisseur();
  Bloc_mylar_hauteur = Geom->GetBlocMylarHauteur();
  Cylindre_tantale_hauteur = Geom->GetCylindreTantaleHauteur();
  IPa1_z = Geom->GetIPa1z();
  IPa2_z = Geom->GetIPa2z();
  IPa3_z = Geom->GetIPa3z();
  IPa4_z = Geom->GetIPa4z();
  Epaisseur_tantale1_2 = Geom->GetEpaisseurTantale12();
  Epaisseur_tantale2_3 = Geom->GetEpaisseurTantale23();
  Epaisseur_tantale3_4 = Geom->GetEpaisseurTantale34();
  Epaisseur_tantale4_5 = Geom->GetEpaisseurTantale45();
  Epaisseur_tantale5_6 = Geom->GetEpaisseurTantale56();
  Epaisseur_tantale6_7 = Geom->GetEpaisseurTantale67();
  G4double epaisseur_IP = IPa1_z + IPa2_z + IPa3_z + IPa4_z;
  G4double  distance_au_centre = 0;
  Nombre_IP = Geom->GetNombreIP();


  //#########################
  // DEFINE GEOMETRY VOLUMES#
  //#########################

  // Create World Volume
  // This is just a big box to place all other logical volumes inside
  G4Box *SolidWorld = new G4Box("SolidWorld", 110*cm, 110*cm, 110*cm );
  LogicalWorld = new G4LogicalVolume(SolidWorld, Vacuum,"LogicalWorld",0,0,0);
  LogicalWorld->SetVisAttributes(invis);

  // Place the world volume: center of world at origin (0,0,0)
  PhysicalWorld = new G4PVPlacement(G4Transform3D(DontRotate,G4ThreeVector(0,0,0)),"PhysicalWorld",LogicalWorld,NULL,false,0);


  //*********************************
  // Build scint et wrapping volumes*
  //*********************** *********
  //Simply calls functions from Scintillator() class
  LogicalTantale1_2 = Geom->GetTantale1_2();
  LogicalTantale2_3 = Geom->GetTantale2_3();
  LogicalTantale3_4 = Geom->GetTantale3_4();
  LogicalTantale4_5 = Geom->GetTantale4_5();
  LogicalTantale5_6 = Geom->GetTantale5_6();
  LogicalTantale6_7 = Geom->GetTantale6_7();
  LogicalStackIP1 = Geom->GetStackIP1();
  LogicalStackIP2 = Geom->GetStackIP2();
  LogicalStackIP3 = Geom->GetStackIP3();
  LogicalStackIP4 = Geom->GetStackIP4();
  LogicalDisqueAlu = Geom->GetDisqueAlu();
  LogicalBlocMylar = Geom->GetBlocMylar();
  LogicalCylindreTantale = Geom->GetCylindreTantale();
  LogicalCylindrePlomb = Geom->GetCylindrePlomb();
  LogicalPlaqueTantale = Geom->GetPlaqueTantale();



  // Set colors of various block materials
  LogicalTantale1_2->SetVisAttributes(blue);
  LogicalTantale2_3->SetVisAttributes(blue);
  LogicalTantale3_4->SetVisAttributes(blue);
  LogicalTantale4_5->SetVisAttributes(blue);
  LogicalTantale5_6->SetVisAttributes(blue);
  LogicalTantale6_7->SetVisAttributes(blue);
  LogicalStackIP1->SetVisAttributes(gray_bis);
  LogicalStackIP2->SetVisAttributes(red_hot);
  LogicalStackIP3->SetVisAttributes(green);
  LogicalStackIP4->SetVisAttributes(black);
  LogicalDisqueAlu->SetVisAttributes(gray);
  LogicalBlocMylar->SetVisAttributes(yellow);
  LogicalCylindreTantale->SetVisAttributes(orange);
  LogicalCylindrePlomb->SetVisAttributes(black);
  LogicalPlaqueTantale->SetVisAttributes(orange);




  //############################
  // DEFINE GEOMETRY PLACEMENTS#
  //############################

  #ifndef disable_gdml

  G4RotationMatrix* stack_rot = new G4RotationMatrix;
  //G4double theta = -12*deg;
  stack_rot->rotateZ(0*deg);
  stack_rot->rotateX(0*deg);

  //***********************
  // Various Positioning values
  //***********************

  PhysicalPlaqueTantale = new G4PVPlacement(stack_rot,               // no rotation
    G4ThreeVector(0, 0, 0), //position
    LogicalPlaqueTantale,    // its logical volume
    "Plaque_Tantale",
    LogicalWorld,               // its mother  volume
    false,           // no boolean operations
    0,
    false);


  // distance_au_centre+= Stack_IP_pos_ini + Disque_alu_epaisseur/2;
  //
  // Cylindre_Disque_Alu_entree = new G4PVPlacement(stack_rot,               // no rotation
  //   G4ThreeVector(0, 0, distance_au_centre), //position
  //   LogicalDisqueAlu,    // its logical volume
  //   "Disque_Alu_entree",
  //   LogicalWorld,               // its mother  volume
  //   false,           // no boolean operations
  //   0,
  //   false);
  //
  //
  //   distance_au_centre= Stack_IP_pos_ini + Disque_alu_epaisseur + Cylindre_tantale_hauteur/2.;
  //
  //   Cylindre_Tantale_phys = new G4PVPlacement(stack_rot,               // no rotation
  //     G4ThreeVector(0, 0, distance_au_centre), //position
  //     LogicalCylindreTantale,    // its logical volume
  //     "Cylindre_Tantale",
  //     LogicalWorld,               // its mother  volume
  //     false,           // no boolean operations
  //     0,
  //     false);
  //
  //     //les IP et les epaisseurs de Ta sont appliqués contre la couche d'alu du fond
  //     distance_au_centre = Stack_IP_pos_ini + Disque_alu_epaisseur + Cylindre_tantale_hauteur;
  //     distance_au_centre -= Nombre_IP * epaisseur_IP + Epaisseur_tantale1_2 + Epaisseur_tantale2_3 + Epaisseur_tantale3_4 + Epaisseur_tantale4_5 + Epaisseur_tantale5_6 + Epaisseur_tantale6_7 + Bloc_mylar_hauteur/2.;
  //     distance_au_centre -= 12.7;
  //
  //     Bloc_Mylar_phys = new G4PVPlacement(stack_rot,               // no rotation
  //       G4ThreeVector(0, 0, distance_au_centre), //position
  //       LogicalBlocMylar,    // its logical volume
  //       "Bloc_mylar",
  //       LogicalWorld,               // its mother  volume
  //       false,           // no boolean operations
  //       0,
  //       false);
  //
  //       distance_au_centre += Bloc_mylar_hauteur/2.;
  //
  //
  //       for (int i=0;i<Nombre_IP;i++) {
  //       //for (int i=0;i<1;i++) {
  //         G4String numero, nom;
  //         if (i==0) numero="1";
  //         else if (i==1) numero="2";
  //         else if (i==2) numero="3";
  //         else if (i==3) numero="4";
  //         else if (i==4) numero="5";
  //         else if (i==5) numero="6";
  //         else if (i==6) numero="7";
  //         else if (i==7) numero="8";
  //         else if (i==8) numero="9";
  //         else if (i==9) numero="10";
  //
  //         distance_au_centre += IPa1_z/2.;
  //
  //         nom="Stack_IP1_"+numero;
  //         physiStackIP1[i] = new G4PVPlacement(stack_rot,               // no rotation
  //           G4ThreeVector(0, 0, distance_au_centre), //position
  //           LogicalStackIP1,     // its logical volume
  //           nom,        // its name
  //           LogicalWorld ,      // its mother  volume
  //           false,           // no boolean operations
  //           0,
  //           false);
  //
  //           G4cout << "Distance au centre = " << distance_au_centre << G4endl;
  //
  //           distance_au_centre += IPa1_z/2. + IPa2_z/2.;
  //
  //           nom="Stack_IP2_"+numero;
  //           physiStackIP2[i] = new G4PVPlacement(stack_rot,               // no rotation
  //             G4ThreeVector(0, 0, distance_au_centre), //position
  //             LogicalStackIP2,     // its logical volume
  //             nom,        // its name
  //             LogicalWorld,      // its mother  volume
  //             false,           // no boolean operations
  //             0,
  //             false);
  //
  //             distance_au_centre += IPa2_z/2. + IPa3_z/2.;
  //             nom="Stack_IP3_"+numero;
  //             physiStackIP3[i] = new G4PVPlacement(stack_rot,               // no rotation
  //               G4ThreeVector(0, 0, distance_au_centre), //position
  //               LogicalStackIP3,     // its logical volume
  //               nom,        // its name
  //               LogicalWorld,      // its mother  volume
  //               false,           // no boolean operations
  //               0,
  //               false);
  //
  //               distance_au_centre += IPa3_z/2. + IPa4_z/2.;
  //               nom="Stack_IP4_"+numero;
  //               physiStackIP4[i] = new G4PVPlacement(stack_rot,               // no rotation
  //                 G4ThreeVector(0, 0, distance_au_centre), //position
  //                 LogicalStackIP4,     // its logical volume
  //                 nom,        // its name
  //                 LogicalWorld,      // its mother  volume
  //                 false,           // no boolean operations
  //                 0,
  //                 false);
  //
  //
  //                 distance_au_centre += IPa4_z/2.;
  //
  //                 nom="disque_ta_"+numero;
  //                 G4double epaisseur_tantale = 0.;
  //
  //                 if(i==0) {
  //                   epaisseur_tantale = Epaisseur_tantale1_2;
  //                   distance_au_centre += epaisseur_tantale/2.;
  //                   physiDisqueTa[i] = new G4PVPlacement(stack_rot,               // no rotation
  //                     G4ThreeVector(0, 0, distance_au_centre), //position
  //                     LogicalTantale1_2,     // its logical volume
  //                     nom,        // its name
  //                     LogicalWorld,      // its mother  volume
  //                     false,           // no boolean operations
  //                     0,
  //                     false);
  //                     distance_au_centre += epaisseur_tantale/2.;
  //                   }
  //
  //                   if(i==1) {
  //                     epaisseur_tantale = Epaisseur_tantale2_3;
  //                     distance_au_centre += epaisseur_tantale/2.;
  //                     physiDisqueTa[i] = new G4PVPlacement(stack_rot,               // no rotation
  //                       G4ThreeVector(0, 0, distance_au_centre), //position
  //                       LogicalTantale2_3,     // its logical volume
  //                       nom,        // its name
  //                       LogicalWorld,      // its mother  volume
  //                       false,           // no boolean operations
  //                       0,
  //                       false);
  //                       distance_au_centre += epaisseur_tantale/2.;
  //                     }
  //
  //                     if(i==2) {
  //                       epaisseur_tantale = Epaisseur_tantale3_4;
  //                       distance_au_centre += epaisseur_tantale/2.;
  //                       physiDisqueTa[i] = new G4PVPlacement(stack_rot,               // no rotation
  //                         G4ThreeVector(0, 0, distance_au_centre), //position
  //                         LogicalTantale3_4,     // its logical volume
  //                         nom,        // its name
  //                         LogicalWorld,      // its mother  volume
  //                         false,           // no boolean operations
  //                         0,
  //                         false);
  //                         distance_au_centre += epaisseur_tantale/2.;
  //                       }
  //
  //                       if(i==3) {
  //                         epaisseur_tantale = Epaisseur_tantale4_5;
  //                         distance_au_centre += epaisseur_tantale/2.;
  //                         physiDisqueTa[i] = new G4PVPlacement(stack_rot,               // no rotation
  //                           G4ThreeVector(0, 0, distance_au_centre), //position
  //                           LogicalTantale4_5,     // its logical volume
  //                           nom,        // its name
  //                           LogicalWorld,      // its mother  volume
  //                           false,           // no boolean operations
  //                           0,
  //                           false);
  //                           distance_au_centre += epaisseur_tantale/2.;
  //                         }
  //
  //                         if(i==4) {
  //                           epaisseur_tantale = Epaisseur_tantale5_6;
  //                           distance_au_centre += epaisseur_tantale/2.;
  //                           physiDisqueTa[i] = new G4PVPlacement(stack_rot,               // no rotation
  //                             G4ThreeVector(0, 0, distance_au_centre), //position
  //                             LogicalTantale5_6,     // its logical volume
  //                             nom,        // its name
  //                             LogicalWorld,      // its mother  volume
  //                             false,           // no boolean operations
  //                             0,
  //                             false);
  //                             distance_au_centre += epaisseur_tantale/2.;
  //                           }
  //
  //                           if(i==5) {
  //                             epaisseur_tantale = Epaisseur_tantale6_7;
  //                             distance_au_centre += epaisseur_tantale/2.;
  //                             physiDisqueTa[i] = new G4PVPlacement(stack_rot,               // no rotation
  //                               G4ThreeVector(0, 0, distance_au_centre), //position
  //                               LogicalTantale6_7,     // its logical volume
  //                               nom,        // its name
  //                               LogicalWorld,      // its mother  volume
  //                               false,           // no boolean operations
  //                               0,
  //                               false);
  //                               distance_au_centre += epaisseur_tantale/2.;
  //                             }
  //                           }
  //
  //                           distance_au_centre += 12.7/2;
  //
  //                           Cylindre_Plomb_phys = new G4PVPlacement(stack_rot,               // no rotation
  //                             G4ThreeVector(0, 0, distance_au_centre), //position
  //                             LogicalCylindrePlomb,    // its logical volume
  //                             "Cylindre_Plomb",
  //                             LogicalWorld,               // its mother  volume
  //                             false,           // no boolean operations
  //                             0,
  //                             false);
  //
  //                           distance_au_centre += Disque_alu_epaisseur/2.+12.7/2;
  //
  //                           Cylindre_Disque_Alu_sortie = new G4PVPlacement(stack_rot,               // no rotation
  //                             G4ThreeVector(0, 0, distance_au_centre), //position
  //                             LogicalDisqueAlu,    // its logical volume
  //                             "Disque_Alu_sortie",
  //                             LogicalWorld,               // its mother  volume
  //                             false,           // no boolean operations
  //                             0,
  //                             false);

                              #else

                              #endif





                              // Returns world with everything in it and all properties set
                              return PhysicalWorld;
                            }
