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
  LogicalTantale2mm = Geom->GetTantale2mm();
  LogicalTantale4mm = Geom->GetTantale4mm();
  LogicalTantale28mm = Geom->GetTantale28mm();
  LogicalStackIP1 = Geom->GetStackIP1();
  LogicalStackIP2 = Geom->GetStackIP2();
  LogicalStackIP3 = Geom->GetStackIP3();
  LogicalStackIP4 = Geom->GetStackIP4();
  LogicalDisqueAlu = Geom->GetDisqueAlu();
  LogicalBlocMylar = Geom->GetBlocMylar();
  LogicalCylindreTantale = Geom->GetCylindreTantale();



  // Set colors of various block materials
  LogicalTantale2mm->SetVisAttributes(blue);
  LogicalTantale4mm->SetVisAttributes(blue);
  LogicalTantale28mm->SetVisAttributes(blue);
  LogicalStackIP1->SetVisAttributes(gray_bis);
  LogicalStackIP2->SetVisAttributes(red_hot);
  LogicalStackIP3->SetVisAttributes(green);
  LogicalStackIP4->SetVisAttributes(black);
  LogicalDisqueAlu->SetVisAttributes(gray);
  LogicalBlocMylar->SetVisAttributes(yellow);
  LogicalCylindreTantale->SetVisAttributes(orange);




  //############################
  // DEFINE GEOMETRY PLACEMENTS#
  //############################

  #ifndef disable_gdml

  G4RotationMatrix* stack_rot = new G4RotationMatrix;
  //G4double theta = -12*deg;
  G4double theta = 0*deg;
  stack_rot->rotateZ(0*deg);
  stack_rot->rotateX(0*deg);

  //***********************
  // Various Positioning values
  //***********************

  distance_au_centre+= Stack_IP_pos_ini + Disque_alu_epaisseur/2;

  Cylindre_Disque_Alu_entree = new G4PVPlacement(stack_rot,               // no rotation
    G4ThreeVector(0, 0, distance_au_centre), //position
    LogicalDisqueAlu,    // its logical volume
    "Disque_Alu_entree",
    LogicalWorld,               // its mother  volume
    false,           // no boolean operations
    0,
    false);


    distance_au_centre= Stack_IP_pos_ini + Disque_alu_epaisseur + Cylindre_tantale_hauteur/2.;

    Cylindre_Tantale_phys = new G4PVPlacement(stack_rot,               // no rotation
      G4ThreeVector(0, 0, distance_au_centre), //position
      LogicalCylindreTantale,    // its logical volume
      "Cylindre_Tantale",
      LogicalWorld,               // its mother  volume
      false,           // no boolean operations
      0,
      false);

      //les IP et les epaisseurs de Ta sont appliqués contre la couche d'alu du fond
      distance_au_centre = Stack_IP_pos_ini + Disque_alu_epaisseur + Cylindre_tantale_hauteur;
      distance_au_centre -= Nombre_IP * epaisseur_IP + 28.*mm + 3.*4.*mm  + 2.*2.*mm + Bloc_mylar_hauteur/2.;

      Bloc_Mylar_phys = new G4PVPlacement(stack_rot,               // no rotation
        G4ThreeVector(0, 0, distance_au_centre), //position
        LogicalBlocMylar,    // its logical volume
        "Bloc_mylar",
        LogicalWorld,               // its mother  volume
        false,           // no boolean operations
        0,
        false);

        distance_au_centre += Bloc_mylar_hauteur/2.;


        for (int i=0;i<Nombre_IP;i++) {
          G4String numero, nom;
          if (i==0) numero="1";
          else if (i==1) numero="2";
          else if (i==2) numero="3";
          else if (i==3) numero="4";
          else if (i==4) numero="5";
          else if (i==5) numero="6";
          else if (i==6) numero="7";
          else if (i==7) numero="8";
          else if (i==8) numero="9";
          else if (i==9) numero="10";

          distance_au_centre += IPa1_z/2.;

          nom="Stack_IP1_"+numero;
          physiStackIP1[i] = new G4PVPlacement(stack_rot,               // no rotation
            G4ThreeVector(0, 0, distance_au_centre), //position
            LogicalStackIP1,     // its logical volume
            nom,        // its name
            LogicalWorld ,      // its mother  volume
            false,           // no boolean operations
            0,
            false);

            G4cout << "Distance au centre = " << distance_au_centre << G4endl;

            distance_au_centre += IPa1_z/2. + IPa2_z/2.;

            nom="Stack_IP2_"+numero;
            physiStackIP2[i] = new G4PVPlacement(stack_rot,               // no rotation
              G4ThreeVector(0, 0, distance_au_centre), //position
              LogicalStackIP2,     // its logical volume
              nom,        // its name
              LogicalWorld,      // its mother  volume
              false,           // no boolean operations
              0,
              false);

              distance_au_centre += IPa2_z/2. + IPa3_z/2.;
              nom="Stack_IP3_"+numero;
              physiStackIP3[i] = new G4PVPlacement(stack_rot,               // no rotation
                G4ThreeVector(0, 0, distance_au_centre), //position
                LogicalStackIP3,     // its logical volume
                nom,        // its name
                LogicalWorld,      // its mother  volume
                false,           // no boolean operations
                0,
                false);

                distance_au_centre += IPa3_z/2. + IPa4_z/2.;
                nom="Stack_IP4_"+numero;
                physiStackIP4[i] = new G4PVPlacement(stack_rot,               // no rotation
                  G4ThreeVector(0, 0, distance_au_centre), //position
                  LogicalStackIP4,     // its logical volume
                  nom,        // its name
                  LogicalWorld,      // its mother  volume
                  false,           // no boolean operations
                  0,
                  false);


                  distance_au_centre += IPa4_z/2.;

                  nom="disque_ta_"+numero;
                  G4double epaisseur_tantale = 0.;

                  if(i<2) {
                    epaisseur_tantale = 2.*mm;
                    distance_au_centre += epaisseur_tantale/2.;
                    physiDisqueTa[i] = new G4PVPlacement(stack_rot,               // no rotation
                      G4ThreeVector(0, 0, distance_au_centre), //position
                      LogicalTantale2mm,     // its logical volume
                      nom,        // its name
                      LogicalWorld,      // its mother  volume
                      false,           // no boolean operations
                      0,
                      false);
                      distance_au_centre += epaisseur_tantale/2.;
                    }//fin if(i<2)

                    if(i>=2 && i<5) {
                      epaisseur_tantale = 4.*mm;
                      distance_au_centre += epaisseur_tantale/2.;
                      physiDisqueTa[i] = new G4PVPlacement(stack_rot,               // no rotation
                        G4ThreeVector(0, 0, distance_au_centre), //position
                        LogicalTantale4mm,     // its logical volume
                        nom,        // its name
                        LogicalWorld,      // its mother  volume
                        false,           // no boolean operations
                        0,
                        false);
                        distance_au_centre += epaisseur_tantale/2.;
                      }//fin (i>=2 && i<5)

                      if(i==5) {
                        epaisseur_tantale = 28.*mm;
                        distance_au_centre += epaisseur_tantale/2.;
                        physiDisqueTa[i] = new G4PVPlacement(stack_rot,               // no rotation
                          G4ThreeVector(0, 0, distance_au_centre), //position
                          LogicalTantale28mm,     // its logical volume
                          nom,        // its name
                          LogicalWorld,      // its mother  volume
                          false,           // no boolean operations
                          0,
                          false);
                          distance_au_centre += epaisseur_tantale/2.;
                        }//fin (i==5)
                      }


                      distance_au_centre += Disque_alu_epaisseur/2.;

                      Cylindre_Disque_Alu_sortie = new G4PVPlacement(stack_rot,               // no rotation
                        G4ThreeVector(0, 0, distance_au_centre), //position
                        LogicalDisqueAlu,    // its logical volume
                        "Disque_Alu_sortie",
                        LogicalWorld,               // its mother  volume
                        false,           // no boolean operations
                        0,
                        false);

                        #else

                        #endif





                        // Returns world with everything in it and all properties set
                        return PhysicalWorld;
                      }
