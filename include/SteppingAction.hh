// ****** unload ******
#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include "EventAction.hh"

class EventAction;
class G4LogicalVolume;

class SteppingAction : public G4UserSteppingAction
{
public:
    SteppingAction(EventAction *eventAction);
    virtual ~SteppingAction();

    virtual void UserSteppingAction(const G4Step* step);
private:
    EventAction* fEventAction;
    G4LogicalVolume* fScoringVolume;

};

#endif // STEPPINGACTION_HH
