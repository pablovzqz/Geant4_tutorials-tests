#include "action.hh"
#include "../stepping/stepping.hh"
#include "../event/event.hh"

MyActionInitialization::MyActionInitialization() {}

MyActionInitialization::~MyActionInitialization() {}

void MyActionInitialization::Build() const {
    MyPrimaryGenerator *primaryGenerator = new MyPrimaryGenerator();
    SetUserAction(primaryGenerator);

    MyRunAction *runAction = new MyRunAction();
    SetUserAction(runAction);

    MyEventAction *eventAction = new MyEventAction(runAction);
    SetUserAction(eventAction);

    MySteppingAction *steppingAction = new MySteppingAction(eventAction);
    SetUserAction(steppingAction);
    // SetUserAction(new MyRunAction());
    // SetUserAction(new MyEventAction());
    // SetUserAction(new MySteppingAction());
};