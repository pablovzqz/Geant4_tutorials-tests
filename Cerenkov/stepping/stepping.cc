#include "../stepping/stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
  
{
    fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
  G4LogicalVolume *VolumeStep = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  const MyDetectorConstruction *sensDet = static_cast<const MyDetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());

  G4LogicalVolume* fScoringVolume = sensDet->GetScoringVolume();

  if (VolumeStep != fScoringVolume) return;

  G4double edep = step->GetTotalEnergyDeposit();
  fEventAction->AddEdep(edep);
}
