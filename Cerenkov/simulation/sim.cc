#include <iostream>

#include "G4RunManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

#include "../construction/construction.hh"
#include "../physics/physics.hh"
#include "../action/action.hh"


int main(int argc, char** argv){

    G4RunManager *runManager = new G4RunManager();

    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());
    runManager->Initialize();

    G4UIExecutive *ui = new G4UIExecutive(argc, argv);

    G4VisManager *visManager = new G4VisExecutive(); 
    visManager->Initialize();

    G4UImanager *UIManager = G4UImanager::GetUIpointer();
    UIManager->ApplyCommand("/vis/open OGL");
    UIManager->ApplyCommand("/vis/drawVolume");
    UIManager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
    UIManager->ApplyCommand("/vis/viewer/zoom 1.4");
    UIManager->ApplyCommand("/vis/viewer/update");
    UIManager->ApplyCommand("/vis/scene/add/trajectories smooth");
    UIManager->ApplyCommand("/vis/scene/endOfEventAction accumulate");

    // EJECUTA EVENTOS
    UIManager->ApplyCommand("/run/beamOn 1");

    // FUERZA EL REFRESCO
    UIManager->ApplyCommand("/vis/viewer/flush");
    UIManager->ApplyCommand("/vis/viewer/refresh");

    ui->SessionStart();

    return 0;
}
