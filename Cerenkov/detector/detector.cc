#include "../detector/detector.hh"


MySensitiveDetector::MySensitiveDetector(const G4String& name):
    G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}
G4bool MySensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* history)
{
  G4Track* track = step->GetTrack();

  track->SetTrackStatus(fStopAndKill); //no permite la propagación dentro del detector.

  G4StepPoint *preStepPoint = step->GetPreStepPoint();
  G4StepPoint *postStepPoint = step->GetPostStepPoint();

  G4ThreeVector posPhoton = preStepPoint->GetPosition();

  // G4cout << "Photon position: " << posPhoton << G4endl;

  const G4VTouchable* touchable = step->GetPreStepPoint()->GetTouchable();
  G4int copyNo = touchable->GetCopyNumber();
  // G4cout << "Detector copy number: " << copyNo << G4endl;

  G4VPhysicalVolume* volume = touchable->GetVolume();
  G4ThreeVector posVolume = volume->GetTranslation();
  G4cout << "Detector position: " << posVolume << G4endl;
}