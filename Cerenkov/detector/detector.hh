#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4String.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4StepPoint.hh"

class MySensitiveDetector : public G4VSensitiveDetector {

public:
  MySensitiveDetector(const G4String& name);
  ~MySensitiveDetector() ;

private:
  
virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);

};


#endif