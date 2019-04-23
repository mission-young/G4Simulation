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

    tree->Branch("d0",target.d0,"d0[16][16]/D");
    tree->Branch("d1",target.d1,"d1[16][16]/D");
    tree->Branch("d2",target.d2,"d2[16][16]/D");


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


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
