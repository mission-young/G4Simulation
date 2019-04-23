#include "RunAction.hh"
#include "Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
 : G4UserRunAction()
{

    // set printing event number per each event
    G4RunManager::GetRunManager()->SetPrintProgress(1000);
    // Get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();

    analysisManager->SetVerboseLevel(1);
    //analysisManager->SetFirstHistoId(0);

    analysisManager->SetNtupleMerging(true);
    analysisManager->SetNtupleRowWise(false);


    analysisManager->CreateNtuple("tree", "G4 Simulation tree");


    analysisManager->CreateNtupleIColumn("DSSD142TrackID");
    analysisManager->CreateNtupleDColumn("DSSD142Edep");
    analysisManager->CreateNtupleDColumn("DSSD142Posx");
    analysisManager->CreateNtupleDColumn("DSSD142Posy");
    analysisManager->CreateNtupleDColumn("DSSD142Posz");
    analysisManager->CreateNtupleIColumn("DSSD142xid");
    analysisManager->CreateNtupleIColumn("DSSD142yid");

    analysisManager->CreateNtupleIColumn("DSSD40TrackID");
    analysisManager->CreateNtupleDColumn("DSSD40Edep");
    analysisManager->CreateNtupleDColumn("DSSD40Posx");
    analysisManager->CreateNtupleDColumn("DSSD40Posy");
    analysisManager->CreateNtupleDColumn("DSSD40Posz");
    analysisManager->CreateNtupleIColumn("DSSD40xid");
    analysisManager->CreateNtupleIColumn("DSSD40yid");

    analysisManager->CreateNtupleIColumn("DSSD304TrackID");
    analysisManager->CreateNtupleDColumn("DSSD304Edep");
    analysisManager->CreateNtupleDColumn("DSSD304Posx");
    analysisManager->CreateNtupleDColumn("DSSD304Posy");
    analysisManager->CreateNtupleDColumn("DSSD304Posz");
    analysisManager->CreateNtupleIColumn("DSSD304xid");
    analysisManager->CreateNtupleIColumn("DSSD304yid");

    analysisManager->FinishNtuple();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  G4String fileName = "out";
  analysisManager->OpenFile(fileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
   G4int nEvent=run->GetNumberOfEvent();
   if(nEvent==0) return;


  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager->Write();
  analysisManager->CloseFile();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
