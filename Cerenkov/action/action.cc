#include "action.hh"

MyActionInitialization::MyActionInitialization() {}

MyActionInitialization::~MyActionInitialization() {}

void MyActionInitialization::Build() const {
    MyPrimaryGenerator *primaryGenerator = new MyPrimaryGenerator();
    SetUserAction(primaryGenerator);
    // SetUserAction(new MyRunAction());
    // SetUserAction(new MyEventAction());
    // SetUserAction(new MySteppingAction());
};