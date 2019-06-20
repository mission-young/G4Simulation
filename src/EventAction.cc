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

//    static int DSSD142HCID=-1;
//    static int DSSD40HCID=-1;
//    static int DSSD304HCID=-1;

//    if(DSSD142HCID<0) DSSD142HCID=G4SDManager::GetSDMpointer()->GetCollectionID("DSSD142HitsCollection");
//    if(DSSD40HCID<0) DSSD40HCID=G4SDManager::GetSDMpointer()->GetCollectionID("DSSD40HitsCollection");
//    if(DSSD304HCID<0) DSSD304HCID=G4SDManager::GetSDMpointer()->GetCollectionID("DSSD304HitsCollection");

static int DSSDHCID=-1;
if(DSSDHCID<0) DSSDHCID=G4SDManager::GetSDMpointer()->GetCollectionID("DSSDHitsCollection");
auto DSSDHitsCollection=static_cast<HitsCollection*>(event->GetHCofThisEvent()->GetHC(DSSDHCID));

//    auto DSSD142HitsCollection=static_cast<HitsCollection*>(event->GetHCofThisEvent()->GetHC(DSSD142HCID));
//    auto DSSD40HitsCollection=static_cast<HitsCollection*>(event->GetHCofThisEvent()->GetHC(DSSD40HCID));
//    auto DSSD304HitsCollection=static_cast<HitsCollection*>(event->GetHCofThisEvent()->GetHC(DSSD304HCID));

//    if(DSSD142HitsCollection->entries()>-1) G4cout<<DSSD142HitsCollection->entries()<<G4endl;
//    SDHit *Hit0=(*DSSD142HitsCollection)[0];
//    if(Hit0->GetEdep()<0.01){
//        G4cout<<Hit0->GetTrackID()<<'\t'<<Hit0->GetEventID()<<'\t'<<Hit0->GetXid()<<'\t'<<Hit0->GetYid()<<'\n';
//    }
    const RunAction *conrunAction=static_cast<const RunAction*>(G4RunManager::GetRunManager()->GetUserRunAction());
    RunAction *runAction=const_cast<RunAction*>(conrunAction);


    runAction->clear();


    SDHit *nullHit=new SDHit();
//    for (int i = 0; i < maxhit; ++i) {
//        SDHit *aHit[3]={nullptr,nullptr,nullptr};
//        for (int j = 0; j < DSSD142HitsCollection->entries(); ++j) {
//            if((*DSSD142HitsCollection)[j]->GetTrackID()==i+1){
//                aHit[0]=(*DSSD142HitsCollection)[j];
//            }
//        }
//        if(aHit[0]==nullptr) aHit[0]=nullHit;

//        for (int j = 0; j < DSSD40HitsCollection->entries(); ++j) {
//            if((*DSSD40HitsCollection)[j]->GetTrackID()==i+1){
//                aHit[1]=(*DSSD40HitsCollection)[j];
//            }
//        }

//        if(aHit[1]==nullptr) aHit[1]=nullHit;
//        for (int j = 0; j < DSSD304HitsCollection->entries(); ++j) {
//            if((*DSSD304HitsCollection)[j]->GetTrackID()==i+1){
//                aHit[2]=(*DSSD304HitsCollection)[j];
//            }
//        }
//        if(aHit[2]==nullptr) aHit[2]=nullHit;


//        for(int j=0;j<3;j++){
//            runAction->de[j][i]=aHit[j]->GetEdep();
//            runAction->dx[j][i]=aHit[j]->GetPos().x();
//            runAction->dy[j][i]=aHit[j]->GetPos().y();
//            runAction->dz[j][i]=aHit[j]->GetPos().z();
//        }

//    }
    for(int i=0;i<maxhit;i++){
        SDHit *aHit=nullptr;
        for(int j=0;j<DSSDHitsCollection->entries();++j){
            if((*DSSDHitsCollection)[j]->GetTrackID()==i+1){
                aHit=(*DSSDHitsCollection)[j];
            }
        }
        if(aHit==nullptr) aHit=nullHit;
        runAction->de[0][i]=aHit->GetEdep();
        runAction->dx[0][i]=aHit->GetPos().x();
        runAction->dy[0][i]=aHit->GetPos().y();
        runAction->dz[0][i]=aHit->GetPos().z();
    }
    RootIO *rootManager=RootIO::GetInstance();
    rootManager->GetOpt()->Fill();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


