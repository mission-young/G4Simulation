#include "EventAction.hh"
#include "Analysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>
#include "SensitiveDetector.hh"
#include "RootIO.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
    : G4UserEventAction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{

    static int DSSD142HCID=-1;
    static int DSSD40HCID=-1;
    static int DSSD304HCID=-1;

    if(DSSD142HCID<0) DSSD142HCID=G4SDManager::GetSDMpointer()->GetCollectionID("DSSD142HitsCollection");
    if(DSSD40HCID<0) DSSD40HCID=G4SDManager::GetSDMpointer()->GetCollectionID("DSSD40HitsCollection");
    if(DSSD304HCID<0) DSSD304HCID=G4SDManager::GetSDMpointer()->GetCollectionID("DSSD304HitsCollection");


    auto DSSD142HitsCollection=static_cast<HitsCollection*>(event->GetHCofThisEvent()->GetHC(DSSD142HCID));
    auto DSSD40HitsCollection=static_cast<HitsCollection*>(event->GetHCofThisEvent()->GetHC(DSSD40HCID));
    auto DSSD304HitsCollection=static_cast<HitsCollection*>(event->GetHCofThisEvent()->GetHC(DSSD304HCID));



    const RunAction *conrunAction=static_cast<const RunAction*>(G4RunManager::GetRunManager()->GetUserRunAction());
    RunAction *runAction=const_cast<RunAction*>(conrunAction);

    runAction->clear();
    SDHit *nullHit=new SDHit();

    SDHit *aHit[3]={nullptr,nullptr,nullptr};
    if(DSSD142HitsCollection->entries()>0){
        aHit[0]=(*DSSD142HitsCollection)[0];
    }else {
        aHit[0]=nullHit;
    }
    if(DSSD40HitsCollection->entries()>0){
        aHit[1]=(*DSSD40HitsCollection)[0];
    }else {
        aHit[1]=nullHit;
    }
    if(DSSD304HitsCollection->entries()>0){
        aHit[2]=(*DSSD304HitsCollection)[0];
    }else {
        aHit[2]=nullHit;
    }
    for (int i = 0; i < 3; ++i) {
        runAction->d[i].xid=aHit[i]->GetXid();
        runAction->d[i].yid=aHit[i]->GetYid();
        runAction->d[i].eventID=aHit[i]->GetEventID();
        runAction->d[i].trackID=aHit[i]->GetTrackID();
        runAction->d[i].eDep=aHit[i]->GetEdep();
        runAction->d[i].posX=aHit[i]->GetPos().x();
        runAction->d[i].posY=aHit[i]->GetPos().y();
        runAction->d[i].posZ=aHit[i]->GetPos().z();
    }
    RootIO *rootManager=RootIO::GetInstance();
    rootManager->GetOpt()->Fill();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


