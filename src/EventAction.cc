#include "EventAction.hh"
#include "RunAction.hh"

EventAction::EventAction(RunAction *runAction):G4UserEventAction (),fRunAction(runAction)
{
    accumulateValueList=fRunAction->GetAccumulateValue();
    accumulateValueCount=fRunAction->GetAccumulateValueCount();
}

EventAction::~EventAction()
{

}

void EventAction::BeginOfEventAction(const G4Event *event)
{
    for (int i = 0; i < accumulateValueCount; ++i) {
        accumulateValueList[i]=0;
    }
}

void EventAction::EndOfEventAction(const G4Event *event)
{
    fRunAction->Accumulate(accumulateValueList);
}

void EventAction::Accumulate(G4double *list)
{
    for (int i = 0; i < accumulateValueCount; ++i) {
        accumulateValueList[i]+=list[i];
    }
}


