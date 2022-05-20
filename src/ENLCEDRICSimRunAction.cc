/// ENLCEDRICSimRunAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLCEDRICSimRunAction.hh"
#include "Randomize.hh"
#include <time.h>
#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include "TFile.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH2I.h"
#include "TH1D.h"
#include "TAxis.h"
#include <fstream>
#include <iostream>
#include "Geometry.hh"

using namespace CLHEP;

const G4String ENLCEDRICSimRunAction::path_bin = "../bin/";

ENLCEDRICSimRunAction::ENLCEDRICSimRunAction(char* suff):suffixe(suff){}
ENLCEDRICSimRunAction::~ENLCEDRICSimRunAction(){}


//-----------------------------------------------------
//  BeginOfRunAction:  used to calculate the start time and
//  to set up information in the run tree.
//-----------------------------------------------------
void ENLCEDRICSimRunAction::BeginOfRunAction(const G4Run* aRun){

  Geom = new Geometry(path_bin+"ENLCEDRICSim.cfg");

  //gROOT->ProcessLine("#include <vector>");

  G4String fileName = suffixe+".root";
  f = new TFile(fileName,"RECREATE");
  //f = new TFile("test.root","UPDATE");

  start = time(NULL);     //start the timer clock to calculate run times

  IP = new TTree("IP","Tree_Information");

  // create the branch for each event.
  // Be careful of the data structure here!  /F is a float  /I is an integer
  RunBranch = IP->Branch("IncidentE", &Stats.IncidentE, "IncidentE/F");
  RunBranch = IP->Branch("IncidentE_Elec_Stack1", &Stats.IncidentE_Elec_Stack1, "IncidentE_Elec_Stack1/F");
  RunBranch = IP->Branch("DepositE_Elec_Stack1", &Stats.DepositE_Elec_Stack1, "DepositE_Elec_Stack1/F");
  RunBranch = IP->Branch("EffectiveDepositE_Elec_Stack1", &Stats.EffectiveDepositE_Elec_Stack1, "EffectiveDepositE_Elec_Stack1/F");
  RunBranch = IP->Branch("X_Position_Elec_Stack1", &Stats.X_Position_Elec_Stack1, "X_Position_Elec_Stack1/F");
  RunBranch = IP->Branch("Y_Position_Elec_Stack1", &Stats.Y_Position_Elec_Stack1, "Y_Position_Elec_Stack1/F");
  RunBranch = IP->Branch("IncidentE_Gamma_Stack1", "vector<float>", &Stats.IncidentE_Gamma_Stack1);
  RunBranch = IP->Branch("DepositE_Gamma_Stack1", &Stats.DepositE_Gamma_Stack1, "DepositE_Gamma_Stack1/F");
  RunBranch = IP->Branch("EffectiveDepositE_Gamma_Stack1", &Stats.EffectiveDepositE_Gamma_Stack1, "EffectiveDepositE_Gamma_Stack1/F");
  RunBranch = IP->Branch("X_Position_Gamma_Stack1", &Stats.X_Position_Gamma_Stack1, "X_Position_Gamma_Stack1/F");
  RunBranch = IP->Branch("Y_Position_Gamma_Stack1", &Stats.Y_Position_Gamma_Stack1, "Y_Position_Gamma_Stack1/F");
  RunBranch = IP->Branch("IncidentE_Elec_Stack2", &Stats.IncidentE_Elec_Stack2, "IncidentE_Elec_Stack2/F");
  RunBranch = IP->Branch("DepositE_Elec_Stack2", &Stats.DepositE_Elec_Stack2, "DepositE_Elec_Stack2/F");
  RunBranch = IP->Branch("EffectiveDepositE_Elec_Stack2", &Stats.EffectiveDepositE_Elec_Stack2, "EffectiveDepositE_Elec_Stack2/F");
  RunBranch = IP->Branch("X_Position_Elec_Stack2", &Stats.X_Position_Elec_Stack2, "X_Position_Elec_Stack2/F");
  RunBranch = IP->Branch("Y_Position_Elec_Stack2", &Stats.Y_Position_Elec_Stack2, "Y_Position_Elec_Stack2/F");
  RunBranch = IP->Branch("IncidentE_Gamma_Stack2", "vector<float>", &Stats.IncidentE_Gamma_Stack2);
  RunBranch = IP->Branch("DepositE_Gamma_Stack2", &Stats.DepositE_Gamma_Stack2, "DepositE_Gamma_Stack2/F");
  RunBranch = IP->Branch("EffectiveDepositE_Gamma_Stack2", &Stats.EffectiveDepositE_Gamma_Stack2, "EffectiveDepositE_Gamma_Stack2/F");
  RunBranch = IP->Branch("X_Position_Gamma_Stack2", &Stats.X_Position_Gamma_Stack2, "X_Position_Gamma_Stack2/F");
  RunBranch = IP->Branch("Y_Position_Gamma_Stack2", &Stats.Y_Position_Gamma_Stack2, "Y_Position_Gamma_Stack2/F");
  RunBranch = IP->Branch("IncidentE_Elec_Stack3", &Stats.IncidentE_Elec_Stack3, "IncidentE_Elec_Stack3/F");
  RunBranch = IP->Branch("DepositE_Elec_Stack3", &Stats.DepositE_Elec_Stack3, "DepositE_Elec_Stack3/F");
  RunBranch = IP->Branch("EffectiveDepositE_Elec_Stack3", &Stats.EffectiveDepositE_Elec_Stack3, "EffectiveDepositE_Elec_Stack3/F");
  RunBranch = IP->Branch("X_Position_Elec_Stack3", &Stats.X_Position_Elec_Stack3, "X_Position_Elec_Stack3/F");
  RunBranch = IP->Branch("Y_Position_Elec_Stack3", &Stats.Y_Position_Elec_Stack3, "Y_Position_Elec_Stack3/F");
  RunBranch = IP->Branch("IncidentE_Gamma_Stack3", "vector<float>", &Stats.IncidentE_Gamma_Stack3);
  RunBranch = IP->Branch("DepositE_Gamma_Stack3", &Stats.DepositE_Gamma_Stack3, "DepositE_Gamma_Stack3/F");
  RunBranch = IP->Branch("EffectiveDepositE_Gamma_Stack3", &Stats.EffectiveDepositE_Gamma_Stack3, "EffectiveDepositE_Gamma_Stack3/F");
  RunBranch = IP->Branch("X_Position_Gamma_Stack3", &Stats.X_Position_Gamma_Stack3, "X_Position_Gamma_Stack3/F");
  RunBranch = IP->Branch("Y_Position_Gamma_Stack3", &Stats.Y_Position_Gamma_Stack3, "Y_Position_Gamma_Stack3/F");
  RunBranch = IP->Branch("IncidentE_Elec_Stack4", &Stats.IncidentE_Elec_Stack4, "IncidentE_Elec_Stack4/F");
  RunBranch = IP->Branch("DepositE_Elec_Stack4", &Stats.DepositE_Elec_Stack4, "DepositE_Elec_Stack4/F");
  RunBranch = IP->Branch("EffectiveDepositE_Elec_Stack4", &Stats.EffectiveDepositE_Elec_Stack4, "EffectiveDepositE_Elec_Stack4/F");
  RunBranch = IP->Branch("X_Position_Elec_Stack4", &Stats.X_Position_Elec_Stack4, "X_Position_Elec_Stack4/F");
  RunBranch = IP->Branch("Y_Position_Elec_Stack4", &Stats.Y_Position_Elec_Stack4, "Y_Position_Elec_Stack4/F");
  RunBranch = IP->Branch("IncidentE_Gamma_Stack4", "vector<float>", &Stats.IncidentE_Gamma_Stack4);
  RunBranch = IP->Branch("DepositE_Gamma_Stack4", &Stats.DepositE_Gamma_Stack4, "DepositE_Gamma_Stack4/F");
  RunBranch = IP->Branch("EffectiveDepositE_Gamma_Stack4", &Stats.EffectiveDepositE_Gamma_Stack4, "EffectiveDepositE_Gamma_Stack4/F");
  RunBranch = IP->Branch("X_Position_Gamma_Stack4", &Stats.X_Position_Gamma_Stack4, "X_Position_Gamma_Stack4/F");
  RunBranch = IP->Branch("Y_Position_Gamma_Stack4", &Stats.Y_Position_Gamma_Stack4, "Y_Position_Gamma_Stack4/F");
  RunBranch = IP->Branch("IncidentE_Elec_Stack5", &Stats.IncidentE_Elec_Stack5, "IncidentE_Elec_Stack5/F");
  RunBranch = IP->Branch("DepositE_Elec_Stack5", &Stats.DepositE_Elec_Stack5, "DepositE_Elec_Stack5/F");
  RunBranch = IP->Branch("EffectiveDepositE_Elec_Stack5", &Stats.EffectiveDepositE_Elec_Stack5, "EffectiveDepositE_Elec_Stack5/F");
  RunBranch = IP->Branch("X_Position_Elec_Stack5", &Stats.X_Position_Elec_Stack5, "X_Position_Elec_Stack5/F");
  RunBranch = IP->Branch("Y_Position_Elec_Stack5", &Stats.Y_Position_Elec_Stack5, "Y_Position_Elec_Stack5/F");
  RunBranch = IP->Branch("IncidentE_Gamma_Stack5", "vector<float>", &Stats.IncidentE_Gamma_Stack5);
  RunBranch = IP->Branch("DepositE_Gamma_Stack5", &Stats.DepositE_Gamma_Stack5, "DepositE_Gamma_Stack5/F");
  RunBranch = IP->Branch("EffectiveDepositE_Gamma_Stack5", &Stats.EffectiveDepositE_Gamma_Stack5, "EffectiveDepositE_Gamma_Stack5/F");
  RunBranch = IP->Branch("X_Position_Gamma_Stack5", &Stats.X_Position_Gamma_Stack5, "X_Position_Gamma_Stack5/F");
  RunBranch = IP->Branch("Y_Position_Gamma_Stack5", &Stats.Y_Position_Gamma_Stack5, "Y_Position_Gamma_Stack5/F");
  RunBranch = IP->Branch("IncidentE_Elec_Stack6", &Stats.IncidentE_Elec_Stack6, "IncidentE_Elec_Stack6/F");
  RunBranch = IP->Branch("DepositE_Elec_Stack6", &Stats.DepositE_Elec_Stack6, "DepositE_Elec_Stack6/F");
  RunBranch = IP->Branch("EffectiveDepositE_Elec_Stack6", &Stats.EffectiveDepositE_Elec_Stack6, "EffectiveDepositE_Elec_Stack6/F");
  RunBranch = IP->Branch("X_Position_Elec_Stack6", &Stats.X_Position_Elec_Stack6, "X_Position_Elec_Stack6/F");
  RunBranch = IP->Branch("Y_Position_Elec_Stack6", &Stats.Y_Position_Elec_Stack6, "Y_Position_Elec_Stack6/F");
  RunBranch = IP->Branch("IncidentE_Gamma_Stack6", "vector<float>", &Stats.IncidentE_Gamma_Stack6);
  RunBranch = IP->Branch("DepositE_Gamma_Stack6", &Stats.DepositE_Gamma_Stack6, "DepositE_Gamma_Stack6/F");
  RunBranch = IP->Branch("EffectiveDepositE_Gamma_Stack6", &Stats.EffectiveDepositE_Gamma_Stack6, "EffectiveDepositE_Gamma_Stack6/F");
  RunBranch = IP->Branch("X_Position_Gamma_Stack6", &Stats.X_Position_Gamma_Stack6, "X_Position_Gamma_Stack6/F");
  RunBranch = IP->Branch("Y_Position_Gamma_Stack6", &Stats.Y_Position_Gamma_Stack6, "Y_Position_Gamma_Stack6/F");
  RunBranch = IP->Branch("IncidentE_Elec_Stack7", &Stats.IncidentE_Elec_Stack7, "IncidentE_Elec_Stack7/F");
  RunBranch = IP->Branch("DepositE_Elec_Stack7", &Stats.DepositE_Elec_Stack7, "DepositE_Elec_Stack7/F");
  RunBranch = IP->Branch("EffectiveDepositE_Elec_Stack7", &Stats.EffectiveDepositE_Elec_Stack7, "EffectiveDepositE_Elec_Stack7/F");
  RunBranch = IP->Branch("X_Position_Elec_Stack7", &Stats.X_Position_Elec_Stack7, "X_Position_Elec_Stack7/F");
  RunBranch = IP->Branch("Y_Position_Elec_Stack7", &Stats.Y_Position_Elec_Stack7, "Y_Position_Elec_Stack7/F");
  RunBranch = IP->Branch("IncidentE_Gamma_Stack7", "vector<float>", &Stats.IncidentE_Gamma_Stack7);
  RunBranch = IP->Branch("DepositE_Gamma_Stack7", &Stats.DepositE_Gamma_Stack7, "DepositE_Gamma_Stack7/F");
  RunBranch = IP->Branch("EffectiveDepositE_Gamma_Stack7", &Stats.EffectiveDepositE_Gamma_Stack7, "EffectiveDepositE_Gamma_Stack7/F");
  RunBranch = IP->Branch("X_Position_Gamma_Stack7", &Stats.X_Position_Gamma_Stack7, "X_Position_Gamma_Stack7/F");
  RunBranch = IP->Branch("Y_Position_Gamma_Stack7", &Stats.Y_Position_Gamma_Stack7, "Y_Position_Gamma_Stack7/F");


  //set the random seed to the CPU clock
  //G4Random::setTheEngine(new CLHEP::HepJamesRandom);
  G4long seed = time(NULL);
  G4Random::setTheSeed(seed);
  //G4Random::setTheSeed(1653032367);
  G4cout << "seed = " << seed << G4endl;

  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

  if (G4VVisManager::GetConcreteInstance()){
    G4UImanager* UI = G4UImanager::GetUIpointer();
    UI->ApplyCommand("/vis/scene/notifyHandlers");
  }

  //InitialiseHistos();
  for(G4int i = 0; i<Nombre_IP;i++){
    E_dep_electrons[i] = 0.;
    E_dep_gammas[i] = 0.;
    E_dep_tot[i] = 0.;
    E_dep_electrons_eff[i] = 0.;
    E_dep_gammas_eff[i] = 0.;
    E_dep_tot_eff[i] = 0.;
  }


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
  Labs = Geom->GetLabs();
  Coef_PSL = Geom->GetCoefPSL();
  G4double epaisseur_IP = IPa1_z + IPa2_z + IPa3_z + IPa4_z;
  G4double vide = Cylindre_tantale_hauteur
  -(Bloc_mylar_hauteur + (Nombre_IP * epaisseur_IP) + Epaisseur_tantale1_2 + Epaisseur_tantale2_3 + Epaisseur_tantale3_4 + Epaisseur_tantale4_5 + Epaisseur_tantale5_6 + Epaisseur_tantale6_7);

  PosZ_Sensitive_IP1 = Stack_IP_pos_ini + Disque_alu_epaisseur + vide + Bloc_mylar_hauteur + IPa1_z;
  PosZ_Sensitive_IP2 = PosZ_Sensitive_IP1 + epaisseur_IP + Epaisseur_tantale1_2;
  PosZ_Sensitive_IP3 = PosZ_Sensitive_IP2 + epaisseur_IP + Epaisseur_tantale2_3;
  PosZ_Sensitive_IP4 = PosZ_Sensitive_IP3 + epaisseur_IP + Epaisseur_tantale3_4;
  PosZ_Sensitive_IP5 = PosZ_Sensitive_IP4 + epaisseur_IP + Epaisseur_tantale4_5;
  PosZ_Sensitive_IP6 = PosZ_Sensitive_IP5 + epaisseur_IP + Epaisseur_tantale5_6;
  PosZ_Sensitive_IP7 = PosZ_Sensitive_IP6 + epaisseur_IP + Epaisseur_tantale6_7;


  G4cout << "Z_IP1 = " << PosZ_Sensitive_IP1 << G4endl;
  G4cout << "Z_IP2 = " << PosZ_Sensitive_IP2 << G4endl;
  G4cout << "Z_IP3 = " << PosZ_Sensitive_IP3 << G4endl;
  G4cout << "Z_IP4 = " << PosZ_Sensitive_IP4 << G4endl;
  G4cout << "Z_IP5 = " << PosZ_Sensitive_IP5 << G4endl;
  G4cout << "Z_IP6 = " << PosZ_Sensitive_IP6 << G4endl;
  G4cout << "Z_IP7 = " << PosZ_Sensitive_IP7 << G4endl;


}  //end BeginOfRunAction



// void  ENLCEDRICSimRunAction::EcrireDistribElectrons(G4int num_IP, G4double Energie)
// {
//   HistoDistribElectrons[num_IP]->Fill(Energie);
// }
//
// void  ENLCEDRICSimRunAction::EcrireDistribGammas(G4int num_IP, G4double Energie)
// {
//   HistoDistribGammas[num_IP]->Fill(Energie);
// }

// void  ENLCEDRICSimRunAction::InitialiseHistos() {
//
//   for (int i =0 ; i<Nombre_IP;i++) {
//     char nom_histo[50];
//     char titre[50];
//
//     ////histo electrons
//     sprintf(nom_histo,"distribution_electrons_%d",i+1);
//     sprintf(titre,"Distribution Electrons IP %d",i+1);
//     HistoDistribElectrons[i] = new TH1D(nom_histo,titre,1000,0,50);
//     HistoDistribElectrons[i]->GetXaxis()->SetTitle("Energie(MeV)");
//     HistoDistribElectrons[i]->GetYaxis()->SetTitle("dN/dE");
//
//     ////histo gammas
//     sprintf(nom_histo,"distribution_gammas_%d",i+1);
//     sprintf(titre,"Distribution Gammas IP %d",i+1);
//     HistoDistribGammas[i] = new TH1D(nom_histo,titre,1000,0,50);
//     HistoDistribGammas[i]->GetXaxis()->SetTitle("Energie(MeV)");
//     HistoDistribGammas[i]->GetYaxis()->SetTitle("dN/dE");
//   }
// }//fin InitialiseHistos

//-----------------------------------------------------
//  EndOfRunAction:  used to calculate the end time and
//  to write information to the run tree.
//-----------------------------------------------------
void ENLCEDRICSimRunAction::EndOfRunAction(const G4Run*aRun){

  TH1D* histo_edep_electrons = new TH1D("edep_electrons","energie deposee par des electrons",7,0.5,7.5);
  histo_edep_electrons ->GetXaxis()->SetTitle("numero de l'IP");
  histo_edep_electrons ->GetYaxis()->SetTitle("Energie deposee (keV)");
  TH1D* histo_edep_electrons_eff = new TH1D("edep_electrons_eff","energie deposee effective par des electrons",7,0.5,7.5);
  histo_edep_electrons_eff ->GetXaxis()->SetTitle("numero de l'IP");
  histo_edep_electrons_eff ->GetYaxis()->SetTitle("Energie deposee effective (keV)");
  TH1D* histo_edep_gammas = new TH1D("edep_gammas","energie deposee par des photons",7,0.5,7.5);
  histo_edep_gammas ->GetXaxis()->SetTitle("numero de l'IP");
  histo_edep_gammas ->GetYaxis()->SetTitle("Energie deposee (keV)");
  TH1D* histo_edep_gammas_eff = new TH1D("edep_gammas_eff","energie deposee effective par des photons",7,0.5,7.5);
  histo_edep_gammas_eff ->GetXaxis()->SetTitle("numero de l'IP");
  histo_edep_gammas_eff ->GetYaxis()->SetTitle("Energie deposee effective (keV)");
  TH1D* histo_edep_tot = new TH1D("edep_totale","energie totale deposee",7,0.5,7.5);
  histo_edep_tot ->GetXaxis()->SetTitle("numero de l'IP");
  histo_edep_tot ->GetYaxis()->SetTitle("Energie deposee (keV)");
  TH1D* histo_edep_tot_eff = new TH1D("edep_totale_eff","energie totale deposee effective",7,0.5,7.5);
  histo_edep_tot_eff ->GetXaxis()->SetTitle("numero de l'IP");
  histo_edep_tot_eff ->GetYaxis()->SetTitle("Energie deposee effective (keV)");
  TH1D* histo_PSL = new TH1D("PSL vs IP","PSL vs IP",7,0.5,7.5);
  histo_PSL ->GetXaxis()->SetTitle("numero de l'IP");
  histo_PSL ->GetYaxis()->SetTitle("PSL" );

  for (G4int i =0 ; i<Nombre_IP;i++) {
    //    G4cout<<"depot alpha_electron "<<i<<" "<<E_dep_electrons[i]<<"\t depot alpha_gamma "<<i<<" "<<E_dep_gammas[i]<<G4endl;
    histo_edep_electrons->SetBinContent(i+1,E_dep_electrons[i]);
    histo_edep_gammas->SetBinContent(i+1,E_dep_gammas[i]);
    histo_edep_tot->SetBinContent(i+1,E_dep_tot[i]);
    histo_edep_electrons_eff->SetBinContent(i+1,E_dep_electrons_eff[i]);
    histo_edep_gammas_eff->SetBinContent(i+1,E_dep_gammas_eff[i]);
    histo_edep_tot_eff->SetBinContent(i+1,E_dep_tot_eff[i]);
    histo_PSL->SetBinContent(i+1,E_dep_tot_eff[i]*Coef_PSL);
    //G4cout << "Edeptot[" << i << "] = " << E_dep_tot[i] << G4endl;
  }

  //update the temp root file
  G4String fileName = suffixe+".root";
  //f = new TFile(fileName,"update");
  f->Write();
  //IP->Write();

  f->Close();

  if (G4VVisManager::GetConcreteInstance()){
    G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");
  }

  //display run time and write to file Rntime.out
  time_t end = time(NULL);
  G4int elapsed = end-start;
  G4cout << "Run Completed in " << elapsed/3600
  << ":" << (elapsed%3600)/60 << ":"
  << ((elapsed%3600)%60) << G4endl;

  // Output the time in the file Runtime.out
  std::ofstream timeout;
  timeout.open("Runtime.out",std::ios::app);
  timeout << "Run " << aRun->GetRunID()
  << ": " <<elapsed/3600
  << ":" <<(elapsed%3600)/60
  << ":" <<((elapsed%3600)%60) << G4endl;
  timeout.close();

  G4cout<<"Leaving Run Action"<<G4endl;
}

//---------------------------------------------------------
//  For each event update the statistics in the Run tree
//---------------------------------------------------------

void ENLCEDRICSimRunAction::UpdateStatistics(RunTally aRunTally){
  Stats = aRunTally;
  IP->Fill();
}
