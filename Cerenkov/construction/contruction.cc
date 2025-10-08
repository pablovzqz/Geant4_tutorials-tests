#include "../construction/construction.hh"
#include "G4Element.hh"
#include "G4MaterialPropertiesTable.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
    fMessenger = new G4GenericMessenger(this, "/detector/", "Detector constuction");

    fMessenger->DeclareProperty("nCols", Ncols, "Number of columns of the detector array");
    fMessenger->DeclareProperty("nRows", Nrows, "Number of rows of the detector array");

    Ncols = 100;
    Nrows = 100;

    defineMaterial();
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::defineMaterial()
{
    G4NistManager *nist = G4NistManager::Instance();
    worldMat = nist->FindOrBuildMaterial("G4_AIR");

    SiO2 = new G4Material("SiO2", 2.201 * g / cm3, 2);
    SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
    SiO2->AddElement(nist->FindOrBuildElement("O"), 2);

    H2O = new G4Material("H2O", 1.000 * g / cm3, 2);
    H2O->AddElement(nist->FindOrBuildElement("H"), 2);
    H2O->AddElement(nist->FindOrBuildElement("O"), 1);

    C = nist->FindOrBuildElement("C");
    Aerogel = new G4Material("Aerogel", 0.200 * g / cm3, 3);
    Aerogel->AddMaterial(SiO2, 62.5 * perCent);
    Aerogel->AddMaterial(H2O, 37.4 * perCent);
    Aerogel->AddElement(C, 0.1 * perCent);  

    G4double energy[2] = {1.239841939 * eV / 0.9, 1.239841939 * eV / 0.2};
    G4double rindexAerogel[2] = {1.1, 1.1};
    G4double rindexWorld[2] = {1, 1};

    G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
    mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);

    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);

    Aerogel->SetMaterialPropertiesTable(mptAerogel);
    worldMat->SetMaterialPropertiesTable(mptWorld);

}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4double xWorld = 0.5 * m;
    G4double yWorld = 0.5 * m;
    G4double zWorld = 0.5 * m;
    
    solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
    solidRadiator = new G4Box("solidRadiator", 40 * cm, 40 * cm, 1 * cm);
    
    LogicWorld = new G4LogicalVolume(solidWorld, worldMat, "LogicWorld");
    LogicRadiator = new G4LogicalVolume(solidRadiator, Aerogel, "LogicRadiator");
    
    PhysWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), LogicWorld, "PhysWorld", 0, false, 0, true);
    PhysRadiator = new G4PVPlacement(0, G4ThreeVector(0, 0, 0.25 * m), LogicRadiator, "PhysRadiator", LogicWorld, false, 0, true);
    
    // Crear contenedor para el array de detectores
    G4Box *solidDetectorArray = new G4Box("solidDetectorArray", xWorld, yWorld, 0.01*m);
    G4LogicalVolume *logicDetectorArray = new G4LogicalVolume(solidDetectorArray, worldMat, "logicDetectorArray");
    new G4PVPlacement(0, G4ThreeVector(0, 0, 0.48*m), logicDetectorArray, "physDetectorArray", LogicWorld, false, 0, true);
    
    // División en filas (Y)
    G4double cellSizeY = (2.0 * yWorld) / Nrows;
    G4Box *solidRow = new G4Box("solidRow", xWorld, cellSizeY*0.5, 0.01*m);
    G4LogicalVolume *logicRow = new G4LogicalVolume(solidRow, worldMat, "logicRow");
    new G4PVReplica("physRow", logicRow, logicDetectorArray, kYAxis, Nrows, cellSizeY);
    
    // División en columnas (X) - detectores finales
    G4double cellSizeX = (2.0 * xWorld) / Ncols;
    solidDetector = new G4Box("solidDetector", cellSizeX*0.5, cellSizeY*0.5, 0.01*m);
    logicDetector = new G4LogicalVolume(solidDetector, worldMat, "LogicDetector");
    new G4PVReplica("PhysDetector", logicDetector, logicRow, kXAxis, Ncols, cellSizeX);
    
    return PhysWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
    logicDetector->SetSensitiveDetector(sensDet);
}
