#include "../run/run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    G4VAnalysisManager *man = G4ToolsAnalysisManager::Instance();
    man->OpenFile("Cerenkov.root");
    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleIColumn("eventID");
    man->CreateNtupleDColumn("X");
    man->CreateNtupleDColumn("Y");
    man->CreateNtupleDColumn("Z");
    man->FinishNtuple(0);

}

void MyRunAction::EndOfRunAction(const G4Run* run)
{
    G4VAnalysisManager *man = G4ToolsAnalysisManager::Instance();
    man->Write();
    man->CloseFile();
}