#ifndef STEPPING_HH
#define STEPPING_HH 

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

#include "../event/event.hh"
#include "../construction/construction.hh"

class MySteppingAction : public G4UserSteppingAction
{
  public:
    MySteppingAction(MyEventAction *eventAction);
    ~MySteppingAction();

    virtual void UserSteppingAction(const G4Step *step);

  private:
    MyEventAction *fEventAction;
};


#endif