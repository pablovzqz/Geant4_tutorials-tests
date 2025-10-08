#include "../construction/construction.hh"



MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

    G4Box *solidWorld = new G4Box("solidWorld", 0.5 * m, 0.5 * m, 0.5 * m);

    G4LogicalVolume *LogicWorld = new G4LogicalVolume(solidWorld, worldMat, "LogicWorld");
    G4VPhysicalVolume *PhysWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), LogicWorld, "PhysWorld", 0, false, 0, true); 
    //El primer 0 denota que no hay rotación, el segundo que no está dentro de otro volumen, habría que poner el nombre del 
    // volumen madre si lo hubiese. El último true comprueba si hay overlaps.


    return PhysWorld;

}  