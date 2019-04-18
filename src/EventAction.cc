#include "EventAction.hh"
#include "RunAction.hh"
#include "g4root.hh"
#include "G4SystemOfUnits.hh"
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
    auto analysisManager=G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(0,accumulateValueList[0]);
    analysisManager->AddNtupleRow();
    analysisManager->FillH1(1,accumulateValueList[0]);
}

void EventAction::Accumulate(G4double *list)
{
    for (int i = 0; i < accumulateValueCount; ++i) {
        accumulateValueList[i]+=list[i];
    }
}


