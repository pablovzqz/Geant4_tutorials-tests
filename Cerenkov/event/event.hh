#ifndef EVENT_HH
#define EVENT_HH 

#include "../run/run.hh"
#include "G4Event.hh"
#include "G4UserEventAction.hh"


class MyEventAction : public G4UserEventAction
{
  public:
    MyEventAction(MyRunAction *runAction);
    ~MyEventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

    void AddEdep(G4double edep) {fEdep += edep; }

  private:
    G4double fEdep;
};

#endif