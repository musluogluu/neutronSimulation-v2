#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

class SteppingAction : public G4UserSteppingAction
{
public:
    SteppingAction(class RunAction* runAction);
    ~SteppingAction() override;

    void UserSteppingAction(const G4Step*) override;

private:
    RunAction* fRunAction;
};

#endif