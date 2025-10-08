#include "../event/event.hh"

MyEventAction::MyEventAction(MyRunAction *run)
{
    fEdep = 0.;
}

MyEventAction::~MyEventAction()
{
}

void MyEventAction::BeginOfEventAction(const G4Event *event)
{
    fEdep = 0.;
}

void MyEventAction::EndOfEventAction(const G4Event *event)
{
    G4cout << "Total energy deposited in this event: " << fEdep << G4endl;
    G4AnalysisManager* analysis = G4AnalysisManager::Instance();
    
    analysis->FillNtupleDColumn(2, 0, fEdep);
    analysis->AddNtupleRow(2);
}