#include "../construction/construction.hh"
#include "G4Element.hh"
#include "G4MaterialPropertiesTable.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

    G4Material *SiO2 = new G4Material("SiO2", 2.201 * g / cm3, 2);
    SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
    SiO2->AddElement(nist->FindOrBuildElement("O"), 2);

    G4Material *H2O = new G4Material("H2O", 1.000 * g / cm3, 2);
    H2O->AddElement(nist->FindOrBuildElement("H"), 2);
    H2O->AddElement(nist->FindOrBuildElement("O"), 1);

    G4Element *C = nist->FindOrBuildElement("C");


    G4Material *Aerogel = new G4Material("Aerogel", 0.200 * g / cm3, 3);
    Aerogel->AddMaterial(SiO2, 62.5 * perCent);
    Aerogel->AddMaterial(H2O, 37.4 * perCent);
    Aerogel->AddElement(C, 0.1 * perCent);

    G4double energy[2] = {1.239841939 * eV / 0.9, 1.239841939 * eV / 0.2};
    G4double rindexAerogel[2] = {1.1, 1.1};
    G4double rindexWorld[2] = {1, 1};

    G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
    mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);
    Aerogel->SetMaterialPropertiesTable(mptAerogel);

    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
    worldMat->SetMaterialPropertiesTable(mptWorld);

    G4Box *solidWorld = new G4Box("solidWorld", 0.5 * m, 0.5 * m, 0.5 * m);
    G4Box *solidRadiator = new G4Box("solidRadiator", 40 * cm, 40 * cm, 1 * cm);

    G4LogicalVolume *LogicWorld = new G4LogicalVolume(solidWorld, worldMat, "LogicWorld");
    G4LogicalVolume *LogicRadiator = new G4LogicalVolume(solidRadiator, Aerogel, "LogicRadiator");

    G4VPhysicalVolume *PhysWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), LogicWorld, "PhysWorld", 0, false, 0, true); 
    G4VPhysicalVolume *PhysRadiator = new G4PVPlacement(0, G4ThreeVector(0, 0, 0.25 * m), LogicRadiator, "PhysRadiator", LogicWorld, false, 0, true); 
    //El primer 0 denota que no hay rotación, el segundo que no está dentro de otro volumen, habría que poner el nombre del 
    // volumen madre si lo hubiese. El último true comprueba si hay overlaps.


    return PhysWorld;

}  
