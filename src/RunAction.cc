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

    rootManager->SetIpf("pos.root");
    //    TFile *opf=rootManager->GetOpf();
  //  opf=new TFile("simu.root","recreate");
    rootManager->SetOpf("simu.root");
//    TTree *tree=rootManager->GetOpt();
 //   tree=new TTree("tree","simu tree");
    rootManager->SetOpt("tree","simulation");

//    rootManager->SetOpf();
//    rootManager->SetOpt();
        TTree *tree=rootManager->GetOpt();
        tree->Branch("de",de,TString::Format("de[3][%d]/D",maxhit).Data());
        tree->Branch("dx",dx,TString::Format("dx[3][%d]/D",maxhit).Data());
        tree->Branch("dy",dy,TString::Format("dy[3][%d]/D",maxhit).Data());
        tree->Branch("dz",dz,TString::Format("dz[3][%d]/D",maxhit).Data());
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
            de[i][j]=0;
            dx[i][j]=0;
            dy[i][j]=0;
            dz[i][j]=0;
        }
    }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
