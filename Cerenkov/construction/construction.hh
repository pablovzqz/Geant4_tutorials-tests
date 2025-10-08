#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#include "G4GenericMessenger.hh"
#include "G4PVReplica.hh"


#include "../detector/detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction {

    public:
        MyDetectorConstruction();
        ~MyDetectorConstruction();

        virtual G4VPhysicalVolume *Construct();
    private:
        G4LogicalVolume* logicDetector;
        virtual void ConstructSDandField();

        G4Box *solidWorld, *solidDetector, *solidRadiator;
        G4LogicalVolume *LogicWorld, *LogicRadiator;
        G4VPhysicalVolume *PhysWorld, *PhysRadiator, *PhysDetector;

        G4int Ncols, Nrows;

        G4GenericMessenger *fMessenger;
    
        G4Material *SiO2, *H2O, *Aerogel, *worldMat;
        G4Element *C;

        void defineMaterial();

};


#endif