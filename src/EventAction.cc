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


    G4int DSSD142TrackID=-1;
    G4int DSSD142xid=-1;
    G4int DSSD142yid=-1;
    G4double DSSD142Edep=0;
    G4double DSSD142Posx=0;
    G4double DSSD142Posy=0;
    G4double DSSD142Posz=0;
    G4int DSSD40TrackID=-1;
    G4int DSSD40xid=-1;
    G4int DSSD40yid=-1;
    G4double DSSD40Edep=0;
    G4double DSSD40Posx=0;
    G4double DSSD40Posy=0;
    G4double DSSD40Posz=0;
    G4int DSSD304TrackID=-1;
    G4int DSSD304xid=-1;
    G4int DSSD304yid=-1;
    G4double DSSD304Edep=0;
    G4double DSSD304Posx=0;
    G4double DSSD304Posy=0;
    G4double DSSD304Posz=0;

    // get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();

    //G4cout<<DSSD142HitsCollection->entries()<<G4endl;
    for (int i = 0; i < DSSD142HitsCollection->entries(); ++i) {
        SDHit *a142Hit=(*DSSD142HitsCollection)[i];
        SDHit *a40Hit=(*DSSD40HitsCollection)[i];
        SDHit *a304Hit=(*DSSD304HitsCollection)[i];
        DSSD142TrackID=a142Hit->GetTrackID();
        DSSD142xid=a142Hit->GetXid();
        DSSD142yid=a142Hit->GetYid();
        DSSD142Edep=a142Hit->GetEdep();
        DSSD142Posx=a142Hit->GetPos().x();
        DSSD142Posy=a142Hit->GetPos().y();
        DSSD142Posz=a142Hit->GetPos().z();



        DSSD40TrackID=a40Hit->GetTrackID();
        DSSD40xid=a40Hit->GetXid();
        DSSD40yid=a40Hit->GetYid();
        DSSD40Edep=a40Hit->GetEdep();
        DSSD40Posx=a40Hit->GetPos().x();
        DSSD40Posy=a40Hit->GetPos().y();
        DSSD40Posz=a40Hit->GetPos().z();



        DSSD304TrackID=a304Hit->GetTrackID();
        DSSD304xid=a304Hit->GetXid();
        DSSD304yid=a304Hit->GetYid();
        DSSD304Edep=a304Hit->GetEdep();
        DSSD304Posx=a304Hit->GetPos().x();
        DSSD304Posy=a304Hit->GetPos().y();
        DSSD304Posz=a304Hit->GetPos().z();

        if(DSSD142TrackID>0||DSSD40TrackID>0||DSSD304TrackID>0){

         analysisManager->FillNtupleIColumn(0,DSSD142TrackID);
         analysisManager->FillNtupleDColumn(1,DSSD142Edep);
         analysisManager->FillNtupleDColumn(2,DSSD142Posx);
         analysisManager->FillNtupleDColumn(3,DSSD142Posy);
         analysisManager->FillNtupleDColumn(4,DSSD142Posz);
         analysisManager->FillNtupleIColumn(5,DSSD142xid);
         analysisManager->FillNtupleIColumn(6,DSSD142yid);

         analysisManager->FillNtupleIColumn(7,DSSD40TrackID);
         analysisManager->FillNtupleDColumn(8,DSSD40Edep);
         analysisManager->FillNtupleDColumn(9,DSSD40Posx);
         analysisManager->FillNtupleDColumn(10,DSSD40Posy);
         analysisManager->FillNtupleDColumn(11,DSSD40Posz);
         analysisManager->FillNtupleIColumn(12,DSSD40xid);
         analysisManager->FillNtupleIColumn(13,DSSD40yid);

         analysisManager->FillNtupleIColumn(14,DSSD304TrackID);
         analysisManager->FillNtupleDColumn(15,DSSD304Edep);
         analysisManager->FillNtupleDColumn(16,DSSD304Posx);
         analysisManager->FillNtupleDColumn(17,DSSD304Posy);
         analysisManager->FillNtupleDColumn(18,DSSD304Posz);
         analysisManager->FillNtupleIColumn(19,DSSD304xid);
         analysisManager->FillNtupleIColumn(20,DSSD304yid);

         analysisManager->AddNtupleRow();
     }
    }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


