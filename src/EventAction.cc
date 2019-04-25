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
// 有时候会出现trackid 1~10 12 13 15之类的情况，跳过了11，14TrackID。这些应该是逃逸未被探测到的粒子。
    //需要处理三块Si hit事件数不一致引起的事件错乱。
    //表现为DSSD142/40/304 HitsCollection的长度不一致。
    // 已修正。以自定义数据结构为框架，填充数据，若响应数据为空，则填入默认空数据。
/*               自定义
                结构序号 TrackID  Edep
    G4WT0 > DSSD40: 0*****1     0.578864
    G4WT0 > DSSD304: 0****1     4.02085
    G4WT0 > DSSD40: 1*****2     0.65679
    G4WT0 > DSSD304: 1****2     4.00354
    G4WT0 > DSSD40: 2*****3     0.645412
    G4WT0 > DSSD304: 2****3     4.04642
    G4WT0 > DSSD40: 3*****4     0.569747
    G4WT0 > DSSD304: 3****4     4.05631
    G4WT0 > DSSD40: 4****-1     0
    G4WT0 > DSSD304: 4****5     4.55477
    G4WT0 > DSSD40: 7***8	0.406095
    G4WT0 > DSSD304: 7***-1	0
    G4WT0 > DSSD40: 8***9	0.435864
    G4WT0 > DSSD304: 8***9	4.2344
    G4WT0 > DSSD40: 9***10	0.441579
    G4WT0 > DSSD304: 9***-1	0
*/
    //以上，对于TrackID为5的事件，DSSD304探测到，而DSSD40未探测到，因而填充空数据占位
    //而对于TrackID为8和10的事件，DSSD40探测到，而DSSD304未探测到，同样填充空数据占位。
    clear();
    init();
    SDHit *nullHit=new SDHit();
    for (int i = 0; i < maxhit; ++i) {
        SDHit *a142Hit=nullptr;
        for (int j = 0; j < DSSD142HitsCollection->entries(); ++j) {
            if((*DSSD142HitsCollection)[j]->GetTrackID()==i+1){
                a142Hit=(*DSSD142HitsCollection)[j];
            }
        }
        if(a142Hit==nullptr){
            a142Hit=nullHit;
        }
        ihit[i][0].second[0].second=a142Hit->GetEventID();
        ihit[i][0].second[1].second=a142Hit->GetTrackID();
        ihit[i][0].second[2].second=a142Hit->GetXid();
        ihit[i][0].second[3].second=a142Hit->GetYid();

        dhit[i][0].second[0].second=a142Hit->GetEdep();
        dhit[i][0].second[1].second=a142Hit->GetPos().x();
        dhit[i][0].second[2].second=a142Hit->GetPos().y();
        dhit[i][0].second[3].second=a142Hit->GetPos().z();
    }

    for (int i = 0; i < maxhit; ++i) {
        SDHit *a40Hit=nullptr;
        for (int j = 0; j < DSSD40HitsCollection->entries(); ++j) {
            if((*DSSD40HitsCollection)[j]->GetTrackID()==i+1){
                a40Hit=(*DSSD40HitsCollection)[j];
            }
        }
        if(a40Hit==nullptr){
            a40Hit=nullHit;
        }
        ihit[i][1].second[0].second=a40Hit->GetEventID();
        ihit[i][1].second[1].second=a40Hit->GetTrackID();
        ihit[i][1].second[2].second=a40Hit->GetXid();
        ihit[i][1].second[3].second=a40Hit->GetYid();

        dhit[i][1].second[0].second=a40Hit->GetEdep();
        dhit[i][1].second[1].second=a40Hit->GetPos().x();
        dhit[i][1].second[2].second=a40Hit->GetPos().y();
        dhit[i][1].second[3].second=a40Hit->GetPos().z();
    }

    for (int i = 0; i < maxhit; ++i) {
        SDHit *a304Hit=nullptr;
        for (int j = 0; j < DSSD304HitsCollection->entries(); ++j) {
            if((*DSSD304HitsCollection)[j]->GetTrackID()==i+1){
                a304Hit=(*DSSD304HitsCollection)[j];
            }
        }
        if(a304Hit==nullptr){
            a304Hit=nullHit;
        }
        ihit[i][2].second[0].second=a304Hit->GetEventID();
        ihit[i][2].second[1].second=a304Hit->GetTrackID();
        ihit[i][2].second[2].second=a304Hit->GetXid();
        ihit[i][2].second[3].second=a304Hit->GetYid();

        dhit[i][2].second[0].second=a304Hit->GetEdep();
        dhit[i][2].second[1].second=a304Hit->GetPos().x();
        dhit[i][2].second[2].second=a304Hit->GetPos().y();
        dhit[i][2].second[3].second=a304Hit->GetPos().z();
    }

    // 找到不同探测器hit响应数不一致的事件，并输出对应的TrackID和能量以确保同一TrackID的事件是否被保存到同一root事件中。

//    if(DSSD40HitsCollection->entries()!=DSSD304HitsCollection->entries()){
//        for (int i = 0; i<maxhit; ++i) {
//           G4cout<< "DSSD40: "<< i <<"***" <<ihit[i][1].second[1].second << '\t' <<dhit[i][1].second[0].second << G4endl;
//           G4cout<< "DSSD304: "<< i << "***" <<ihit[i][2].second[1].second << '\t' <<dhit[i][2].second[0].second << G4endl;
//        }
//    }
    // get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();


    int index=0;
    for (int i = 0; i < maxhit; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < intInfo.size(); ++k) {
                analysisManager->FillNtupleIColumn(index,ihit[i][j].second[k].second);
                index++;
            }
            for (int k = 0; k < doubleInfo.size(); ++k) {
                analysisManager->FillNtupleDColumn(index,dhit[i][j].second[k].second);
                index++;
            }
        }
    }
    analysisManager->AddNtupleRow();

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


