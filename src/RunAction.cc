#include "RunAction.hh"
#include "Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "EventAction.hh"
#include "RootIO.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
 : G4UserRunAction()
{

    // set printing event number per each event
    G4RunManager::GetRunManager()->SetPrintProgress(1000);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
    delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{

    RootIO* rootManager=RootIO::GetInstance();
//    TFile *opf=rootManager->GetOpf();
  //  opf=new TFile("simu.root","recreate");
    rootManager->SetOpf("simu.root");
//    TTree *tree=rootManager->GetOpt();
 //   tree=new TTree("tree","simu tree");
    rootManager->SetOpt("tree","simulation");

//    rootManager->SetOpf();
//    rootManager->SetOpt();
    TTree *tree=rootManager->GetOpt();
//    tree->Branch("d0xid",&d[0].xid,TString::Format("d[0].xid[%d]/I",maxhit).Data());
//    tree->Branch("d0yid",&d[0].yid,TString::Format("d[0].yid[%d]/I",maxhit).Data());
//    tree->Branch("d0trackid",&d[0].trackID,TString::Format("d[0].trackID[%d]/I",maxhit).Data());
//    tree->Branch("d0eventid",&d[0].eventID,TString::Format("d[0].eventID[%d]/I",maxhit).Data());
//    tree->Branch("d0e",&d[0].eDep,TString::Format("d[0].eDep[%d]/D",maxhit).Data());
//    tree->Branch("d0x",&d[0].posX,TString::Format("d[0].posX[%d]/D",maxhit).Data());
//    tree->Branch("d0y",&d[0].posY,TString::Format("d[0].posY[%d]/D",maxhit).Data());
//    tree->Branch("d0z",&d[0].posZ,TString::Format("d[0].posZ[%d]/D",maxhit).Data());

//    tree->Branch("d1xid",d[1].xid,TString::Format("d[1].xid[%d]/I",maxhit).Data());
//    tree->Branch("d1yid",d[1].yid,TString::Format("d[1].yid[%d]/I",maxhit).Data());
//    tree->Branch("d1trackid",d[1].trackID,TString::Format("d[1].trackID[%d]/I",maxhit).Data());
//    tree->Branch("d1eventid",d[1].eventID,TString::Format("d[1].eventID[%d]/I",maxhit).Data());
//    tree->Branch("d1e",d[1].eDep,TString::Format("d[1].eDep[%d]/D",maxhit).Data());
//    tree->Branch("d1x",d[1].posX,TString::Format("d[1].posX[%d]/D",maxhit).Data());
//    tree->Branch("d1y",d[1].posY,TString::Format("d[1].posY[%d]/D",maxhit).Data());
//    tree->Branch("d1z",d[1].posZ,TString::Format("d[1].posZ[%d]/D",maxhit).Data());

//    tree->Branch("d2xid",d[2].xid,TString::Format("d[2].xid[%d]/I",maxhit).Data());
//    tree->Branch("d2yid",d[2].yid,TString::Format("d[2].yid[%d]/I",maxhit).Data());
//    tree->Branch("d2trackid",d[2].trackID,TString::Format("d[2].trackID[%d]/I",maxhit).Data());
//    tree->Branch("d2eventid",d[2].eventID,TString::Format("d[2].eventID[%d]/I",maxhit).Data());
//    tree->Branch("d2e",d[2].eDep,TString::Format("d[2].eDep[%d]/D",maxhit).Data());
//    tree->Branch("d2x",d[2].posX,TString::Format("d[2].posX[%d]/D",maxhit).Data());
//    tree->Branch("d2y",d[2].posY,TString::Format("d[2].posY[%d]/D",maxhit).Data());
//    tree->Branch("d2z",d[2].posZ,TString::Format("d[2].posZ[%d]/D",maxhit).Data());

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
    G4int nEvent=run->GetNumberOfEvent();
    if(nEvent==0) return;

    RootIO* rootManager=RootIO::GetInstance();
    rootManager->GetOpf()->Write();
    rootManager->GetOpf()->Close();

}

void RunAction::clear()
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < maxhit; ++j) {
            d[i].xid[j]=-1;
            d[i].yid[j]=-1;
            d[i].eventID[j]=-1;
            d[i].trackID[j]=-1;
            d[i].eDep[j]=0;
            d[i].posX[j]=0;
            d[i].posY[j]=0;
            d[i].posZ[j]=0;
        }

    }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
