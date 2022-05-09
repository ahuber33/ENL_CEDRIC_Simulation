/// ENLCEDRICSimVisManager.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef ENLCEDRICSimVisManager_h
#define ENLCEDRICSimVisManager_h 1

#include "G4VisManager.hh"


class ENLCEDRICSimVisManager: public G4VisManager {

public:

  ENLCEDRICSimVisManager ();

private:

  void RegisterGraphicsSystems ();

};

#endif
