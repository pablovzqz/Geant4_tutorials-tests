#include "../run/run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    G4VAnalysisManager *man = G4ToolsAnalysisManager::Instance();

    G4int runID = run->GetRunID();
    std::stringstream strRunID;
    strRunID<<runID;

    man->OpenFile("Cerenkov" + strRunID.str() + ".root");


    man->CreateNtuple("Photons", "Photons");
    man->CreateNtupleIColumn("eventID");
    man->CreateNtupleDColumn("X");
    man->CreateNtupleDColumn("Y");
    man->CreateNtupleDColumn("Z");
    man->CreateNtupleDColumn("Wavelength")
    man->FinishNtuple(0);

    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleIColumn("eventID");
    man->CreateNtupleDColumn("X");
    man->CreateNtupleDColumn("Y");
    man->CreateNtupleDColumn("Z");
    man->FinishNtuple(1);

}

void MyRunAction::EndOfRunAction(const G4Run* run)
{
    G4VAnalysisManager *man = G4ToolsAnalysisManager::Instance();
    man->Write();
    man->CloseFile();
}