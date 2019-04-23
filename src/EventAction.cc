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


    std::vector<int> DSSD142TrackID;
    std::vector<int> DSSD142xid;
    std::vector<int> DSSD142yid;
    std::vector<double> DSSD142Edep;
    std::vector<double> DSSD142Posx;
    std::vector<double> DSSD142Posy;
    std::vector<double> DSSD142Posz;
    std::vector<int> DSSD40TrackID;
    std::vector<int> DSSD40xid;
    std::vector<int> DSSD40yid;
    std::vector<double> DSSD40Edep;
    std::vector<double> DSSD40Posx;
    std::vector<double> DSSD40Posy;
    std::vector<double> DSSD40Posz;
    std::vector<int> DSSD304TrackID;
    std::vector<int> DSSD304xid;
    std::vector<int> DSSD304yid;
    std::vector<double> DSSD304Edep;
    std::vector<double> DSSD304Posx;
    std::vector<double> DSSD304Posy;
    std::vector<double> DSSD304Posz;
    std::vector<int> DSSD142EventID;
    std::vector<int> DSSD40EventID;
    std::vector<int> DSSD304EventID;
    // get analysis manager
    //auto analysisManager = G4AnalysisManager::Instance();

    //G4cout<<DSSD142HitsCollection->entries()<<G4endl;

    const RunAction *conrunAction=static_cast<const RunAction*>(G4RunManager::GetRunManager()->GetUserRunAction());
    RunAction *runAction=const_cast<RunAction*>(conrunAction);

    for (int i = 0; i < DSSD142HitsCollection->entries(); ++i) {
       SDHit *a142Hit=(*DSSD142HitsCollection)[i];
       runAction->target.d0[a142Hit->GetXid()][a142Hit->GetYid()]=a142Hit->GetEdep();

//       if(a142Hit->GetIsHit()){
//           DSSD142TrackID.push_back(a142Hit->GetTrackID());
//           DSSD142xid.push_back(a142Hit->GetXid());
//           DSSD142yid.push_back(a142Hit->GetYid());
//           DSSD142Edep.push_back(a142Hit->GetEdep());
//           DSSD142Posx.push_back(a142Hit->GetPos().x());
//           DSSD142Posy.push_back(a142Hit->GetPos().y());
//           DSSD142Posz.push_back(a142Hit->GetPos().z());
//           DSSD142EventID.push_back(a142Hit->GetEventID());
//       }
    }

    for (int i = 0; i < DSSD40HitsCollection->entries(); ++i) {
       SDHit *a40Hit=(*DSSD40HitsCollection)[i];
       runAction->target.d1[a40Hit->GetXid()][a40Hit->GetYid()]=a40Hit->GetEdep();
//       if(a40Hit->GetIsHit()){
//           DSSD40TrackID.push_back(a40Hit->GetTrackID());
//           DSSD40xid.push_back(a40Hit->GetXid());
//           DSSD40yid.push_back(a40Hit->GetYid());
//           DSSD40Edep.push_back(a40Hit->GetEdep());
//           DSSD40Posx.push_back(a40Hit->GetPos().x());
//           DSSD40Posy.push_back(a40Hit->GetPos().y());
//           DSSD40Posz.push_back(a40Hit->GetPos().z());
//           DSSD40EventID.push_back(a40Hit->GetEventID());
//       }
    }

    for (int i = 0; i < DSSD304HitsCollection->entries(); ++i) {
       SDHit *a304Hit=(*DSSD304HitsCollection)[i];
       runAction->target.d2[a304Hit->GetXid()][a304Hit->GetYid()]=a304Hit->GetEdep();
//       if(a304Hit->GetIsHit()){
//           DSSD304TrackID.push_back(a304Hit->GetTrackID());
//           DSSD304xid.push_back(a304Hit->GetXid());
//           DSSD304yid.push_back(a304Hit->GetYid());
//           DSSD304Edep.push_back(a304Hit->GetEdep());
//           DSSD304Posx.push_back(a304Hit->GetPos().x());
//           DSSD304Posy.push_back(a304Hit->GetPos().y());
//           DSSD304Posz.push_back(a304Hit->GetPos().z());
//           DSSD304EventID.push_back(a304Hit->GetEventID());
//       }
    }
//    for (int i = 0; i < 16; ++i) {
//        for (int j = 0; j < 16; ++j) {
//            if(runAction->d0[i][j]>0||runAction->d1[i][j]>0||runAction->d2[i][j]>0)
//                G4cout<<"hello"<<G4endl;
//        }
//    }
    RootIO *rootManager=RootIO::GetInstance();
    rootManager->GetOpt()->Fill();

     //   if(DSSD142TrackID>0||DSSD40TrackID>0||DSSD304TrackID>0){
           //analysisManager->FillNtupleIColumn(0,vectortest);
//         analysisManager->FillNtupleIColumn(0,DSSD142TrackID);
//         analysisManager->FillNtupleDColumn(1,DSSD142Edep);
//         analysisManager->FillNtupleDColumn(2,DSSD142Posx);
//         analysisManager->FillNtupleDColumn(3,DSSD142Posy);
//         analysisManager->FillNtupleDColumn(4,DSSD142Posz);
//         analysisManager->FillNtupleIColumn(5,DSSD142xid);
//         analysisManager->FillNtupleIColumn(6,DSSD142yid);

//         analysisManager->FillNtupleIColumn(7,DSSD40TrackID);
//         analysisManager->FillNtupleDColumn(8,DSSD40Edep);
//         analysisManager->FillNtupleDColumn(9,DSSD40Posx);
//         analysisManager->FillNtupleDColumn(10,DSSD40Posy);
//         analysisManager->FillNtupleDColumn(11,DSSD40Posz);
//         analysisManager->FillNtupleIColumn(12,DSSD40xid);
//         analysisManager->FillNtupleIColumn(13,DSSD40yid);

//         analysisManager->FillNtupleIColumn(14,DSSD304TrackID);
//         analysisManager->FillNtupleDColumn(15,DSSD304Edep);
//         analysisManager->FillNtupleDColumn(16,DSSD304Posx);
//         analysisManager->FillNtupleDColumn(17,DSSD304Posy);
//         analysisManager->FillNtupleDColumn(18,DSSD304Posz);
//         analysisManager->FillNtupleIColumn(19,DSSD304xid);
//         analysisManager->FillNtupleIColumn(20,DSSD304yid);

//         analysisManager->FillNtupleIColumn(21,DSSD142EventID);
//         analysisManager->FillNtupleIColumn(22,DSSD40EventID);
//         analysisManager->FillNtupleIColumn(23,DSSD304EventID);
         //analysisManager->AddNtupleRow();
  //   }

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


