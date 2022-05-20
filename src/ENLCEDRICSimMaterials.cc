/// ENLCEDRICSimMaterials.cc
/// Auteur: Arnaud HUBER <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLCEDRICSimMaterials.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4MaterialPropertyVector.hh"
#include "G4NistManager.hh"
#include <fstream>
#include <iostream>
#include "G4UnitsTable.hh"
#include "G4ThreeVector.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4Scintillation.hh"

using namespace CLHEP;

const G4String ENLCEDRICSimMaterials::path = "../simulation_input_files/";

// Used to set up all material properties.  Some materials
// are left over from previous simulations and may not be
// needed.  Code to read in material properties from file
// is poorly done.  Can improve using vectors.  Careful of
// memory leaks.  Careful of files and how they are read in.

ENLCEDRICSimMaterials::ENLCEDRICSimMaterials(G4String prop_buildfile)
{


	//G4cout << "Test" << G4endl;

	std::ifstream config_prop;
	config_prop.open(prop_buildfile);
	if (!config_prop.is_open())
	G4cout << "Error opening file " << prop_buildfile << G4endl;
	else{
		//G4cout << "Accessing the properties file. " << G4endl;

		while(!config_prop.eof()){
			G4String variable,unit;
			G4double value;

			config_prop >> variable;
			if(!config_prop.good()) break;
			if(variable == "scintIndexconst")
			{
				config_prop>>scintIndexconst;
			}
			if(variable == "scalingfactor_low")
			{
				config_prop>>scalingfactor_low;
			}
			if(variable == "scalingfactor_high")
			{
				config_prop>>scalingfactor_high;
			}
			if(variable == "pop_scalingfactor_low")
			{
				config_prop>>pop_scalingfactor_low;
			}
			if(variable == "pop_scalingfactor_high")
			{
				config_prop>>pop_scalingfactor_high;
			}
			if(variable == "lightyield")
			{
				config_prop>>lightyield;
			}
			if(variable == "paint_ref_coeff")
			{
				config_prop>>paint_ref_coeff;
			}
			if(variable == "mylar_ref_coeff")
			{
				config_prop>>mylar_ref_coeff;
			}
			else if(variable == "scintAbsorbconst")
			{
				config_prop >> value >> unit;
				scintAbsorbconst = value*G4UnitDefinition::GetValueOf(unit);
			}

		}
	}

	config_prop.close();
	Construct();


}

ENLCEDRICSimMaterials::~ENLCEDRICSimMaterials()
{}


	void ENLCEDRICSimMaterials::Construct()
	{
		G4double a, z,fractionmass;
  	G4double density,pressure,temperature;
		G4double R = 8.3144621; //(en J/K/mole => Constante gaz parfait)
		G4int nel;
		density = 1.e-25*g/cm3;
		pressure = 1.e-19*pascal;
		temperature = 0.1*kelvin;

		//***********************
		// Define the Elements  *
		//***********************
		C = new G4Material("C",z=6., a=12.01*g/mole,density=2.25*g/cm3);
		Al = new G4Material("Aluminium", z=13., a=27.*g/mole, density=2.7*g/cm3);
		Fe = new G4Material("Fer",z=26., a=55.827*g/mole, density=7.874*g/cm3);
		Cu = new G4Material("Cuivre",z=29., a=63.7056*g/mole, density=7.11*g/cm3);
		Ta = new G4Material("Tantale",z=73.,a=180.94788*g/mole,16.4*g/cm3);
		Pb = new G4Material("Plomb",z=82., a=207.25*g/mole, density=11.35*g/cm3);


		//Hydrogen
		G4Element* H = new G4Element("Hydrogen","H",z=1.,a= 1.0079*g/mole);
		//Carbone
		G4Element* C = new G4Element("Carbon","C",z=6., a=12.01*g/mole);
		//Oxygen
		G4Element* O = new G4Element("Oxygen","O",z=8., a=15.9994*g/mole);
		//Baryum
		G4Element* Ba = new G4Element("Barium","Ba",z=56., a=138.9055*g/mole);
		//Fluor
		G4Element* F = new G4Element("Fluorine","F",z=9., a=18.9984*g/mole);
		//Brome
		G4Element* Br = new G4Element("Boron","Br",z=35., a=79.904*g/mole);
		//Azote
		G4Element* N = new G4Element("Nitrogen","N",z=7., a=14.0067*g/mole);
		//Fe
		G4Element* Fe = new G4Element("Iron","Fe",z=26., a=55.847*g/mole);
		//Manganese
		G4Element* Mn = new G4Element("Manganese","Mn",z=25., a=54.9380*g/mole);
		//Zinc
		G4Element* Zn = new G4Element("Zinc","Zn",z=30., a=65.38*g/mole);



		//***********************
		// Build Materials      *
		//***********************
		//Vide
		vacuum = new G4Material ("vacuum",
		1.0,  //1.0
		1.01*g/mole,  //1.01*g/mole
		universe_mean_density,   //universe_mean_density
		kStateGas,   //kStateGas
		3.e-18*pascal, //3.e-18*pascal
		2.73*kelvin);  //2.73*kelvin


		//Air
		Air =new G4Material("Air",density=1.2*mg/cm3,nel=2);
		Air->AddElement(N,fractionmass=0.70);
		Air->AddElement(O,fractionmass=0.30);
		TypeIP = "MS";

		if(TypeIP=="SR") density =1.273*g/cm3;
		else density = 1.66*g/cm3 ;

		Polyester=new G4Material("Polyester",density=1.66*g/cm3,nel=3);
		Polyester->AddElement(C,fractionmass=0.625);
		Polyester->AddElement(H,fractionmass=0.042);
		Polyester->AddElement(O,fractionmass=0.333);

		Sensitive=new G4Material("Sensitive",density=3.31*g/cm3,nel=7);
		Sensitive->AddElement(C,fractionmass=0.127);
		Sensitive->AddElement(H,fractionmass=0.016);
		Sensitive->AddElement(O,fractionmass=0.042);
		Sensitive->AddElement(N,fractionmass=0.018);
		Sensitive->AddElement(Ba,fractionmass=0.463);
		Sensitive->AddElement(F,fractionmass=0.064);
		Sensitive->AddElement(Br,fractionmass=0.27);

		Base=new G4Material("Base",density=2.77*g/cm3,nel=7);
		Base->AddElement(C,fractionmass=0.121);
		Base->AddElement(H,fractionmass=0.015);
		Base->AddElement(O,fractionmass=0.354);
		Base->AddElement(N,fractionmass=0.018);
		Base->AddElement(Fe,fractionmass=0.308);
		Base->AddElement(Mn,fractionmass=0.119);
		Base->AddElement(Zn,fractionmass=0.065);

		Default_Material = vacuum;

	}

	G4Material* ENLCEDRICSimMaterials::GetMaterial(G4String material)
	{
		G4Material* pttoMaterial = G4Material::GetMaterial(material);
		return pttoMaterial;
	}
