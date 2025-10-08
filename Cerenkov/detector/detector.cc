#include "../detector/detector.hh"
#include "../run/run.hh"


MySensitiveDetector::MySensitiveDetector(const G4String& name):
    G4VSensitiveDetector(name)
{
  quEff = new G4PhysicsOrderedFreeVector();

  std::ifstream file;
  file.open("eff.dat");
  while(1)
  {
    G4double wlen, queff;
    file >> wlen >> queff;
    if(file.eof())
    break;
     quEff->InsertValues(wlen, queff/100);
    }

    file.close();
    quEff->SetSpline(false);
}

MySensitiveDetector::~MySensitiveDetector()
{}
G4bool MySensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* history)
{
  G4Track* track = step->GetTrack();

  track->SetTrackStatus(fStopAndKill); //no permite la propagación dentro del detector.

  G4StepPoint *preStepPoint = step->GetPreStepPoint();
  G4StepPoint *postStepPoint = step->GetPostStepPoint();

  G4ThreeVector posPhoton = preStepPoint->GetPosition();
  G4ThreeVector momPhoton = preStepPoint->GetMomentum();

  G4double wlen = (1.239841030*eV/momPhoton.mag())*1E+03; //nm

  // G4cout << "Photon position: " << posPhoton << G4endl;

  const G4VTouchable* touchable = step->GetPreStepPoint()->GetTouchable();
  G4int copyNo = touchable->GetCopyNumber();
  // G4cout << "Detector copy number: " << copyNo << G4endl;

  G4VPhysicalVolume* volume = touchable->GetVolume();
  G4ThreeVector posVolume = volume->GetTranslation();
  G4cout << "Detector position: " << posVolume << G4endl;

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->FillNtupleIColumn(0, 0, evt);
    man->FillNtupleDColumn(0, 1, posVolume[0]);
    man->FillNtupleDColumn(0, 2, posVolume[1]);
    man->FillNtupleDColumn(0, 3, posVolume[2]);
    man->AddNtupleRow(1);

    if(G4UniformRand() <= quEff->Value(wlen))
    {
      man->FillNtupleIColumn(0, 0, evt);
      man->FillNtupleDColumn(0, 1, posPhoton[0]);
      man->FillNtupleDColumn(0, 2, posPhoton[1]);
      man->FillNtupleDColumn(0, 3, posPhoton[2]);
      man->FillNtupleDColumn(0, 4, wlen);
      man->AddNtupleRow(0);
    }
    

}