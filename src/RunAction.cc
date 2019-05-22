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

    tree->Branch("d0xid",&d[0].xid,"d[0].xid/I");
    tree->Branch("d0yid",&d[0].yid,"d[0].yid/I");
    tree->Branch("d0trackid",&d[0].trackID,"d[0].trackID/I");
    tree->Branch("d0eventid",&d[0].eventID,"d[0].eventID/I");
    tree->Branch("d0e",&d[0].eDep,"d[0].eDep/D");
    tree->Branch("d0x",&d[0].posX,"d[0].posX/D");
    tree->Branch("d0y",&d[0].posY,"d[0].posY/D");
    tree->Branch("d0y",&d[0].posY,"d[0].posY/D");
    tree->Branch("d0z",&d[0].posZ,"d[0].posZ/D");

    tree->Branch("d1xid",&d[1].xid,"d[1].xid/I");
    tree->Branch("d1yid",&d[1].yid,"d[1].yid/I");
    tree->Branch("d1trackid",&d[1].trackID,"d[1].trackID/I");
    tree->Branch("d1eventid",&d[1].eventID,"d[1].eventID/I");
    tree->Branch("d1e",&d[1].eDep,"d[1].eDep/D");
    tree->Branch("d1x",&d[1].posX,"d[1].posX/D");
    tree->Branch("d1y",&d[1].posY,"d[1].posY/D");
    tree->Branch("d1y",&d[1].posY,"d[1].posY/D");
    tree->Branch("d1z",&d[1].posZ,"d[1].posZ/D");

    tree->Branch("d2xid",&d[2].xid,"d[2].xid/I");
    tree->Branch("d2yid",&d[2].yid,"d[2].yid/I");
    tree->Branch("d2trackid",&d[2].trackID,"d[2].trackID/I");
    tree->Branch("d2eventid",&d[2].eventID,"d[2].eventID/I");
    tree->Branch("d2e",&d[2].eDep,"d[2].eDep/D");
    tree->Branch("d2x",&d[2].posX,"d[2].posX/D");
    tree->Branch("d2y",&d[2].posY,"d[2].posY/D");
    tree->Branch("d2y",&d[2].posY,"d[2].posY/D");
    tree->Branch("d2z",&d[2].posZ,"d[2].posZ/D");
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
        d[i].xid=-1;
        d[i].yid=-1;
        d[i].eventID=-1;
        d[i].trackID=-1;
        d[i].eDep=0;
        d[i].posX=0;
        d[i].posY=0;
        d[i].posZ=0;
    }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
