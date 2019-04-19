#include "EventAction.hh"
#include "G4EventManager.hh"
#include "RunAction.hh"
#include "g4root.hh"
#include "G4SystemOfUnits.hh"
#include "G4Trajectory.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Event.hh"
#include "G4VHitsCollection.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
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
//    G4int hcid = G4SDManager::GetSDMpointer()->GetCollectionID("HitsCollection");
//    auto hitsCollection= static_cast<HitsCollection*>(event->GetHCofThisEvent()->GetHC(hcid));

//    auto Hit=(*hitsCollection)[hitsCollection->entries()-1];


    G4TrajectoryContainer* trajectoryContainer=event->GetTrajectoryContainer();
    G4int n_trajectories=0;
    if(trajectoryContainer) n_trajectories=trajectoryContainer->entries();
    G4int eventID=event->GetEventID();
    if(eventID<100||eventID%100==0){
        G4cout<<">>> Event: "<<eventID<<G4endl;
        if(trajectoryContainer){
            G4cout<<"    "<<n_trajectories
                 <<" trajectories stored in this event."<<G4endl;
        }
        //G4cout<<"    "<<event->GetHCofThisEvent()->GetHC(0)->GetSize()<<" hits stored in this event"<<G4endl;
    }


    fRunAction->Accumulate(accumulateValueList);
    auto analysisManager=G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(0,accumulateValueList[0]);
    analysisManager->AddNtupleRow();
    analysisManager->FillH1(1,accumulateValueList[0]);
  //  analysisManager->FillH1(1,Hit->GetEdep());
}

void EventAction::Accumulate(G4double *list)
{
    for (int i = 0; i < accumulateValueCount; ++i) {
        accumulateValueList[i]+=list[i];
    }
}


