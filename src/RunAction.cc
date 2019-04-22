#include "RunAction.hh"
#include "Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(G4int accumulateParsNum)
 : G4UserRunAction()
{
    accumulateListSize=accumulateParsNum;
    DefineAccumulableManager();

    // set printing event number per each event
    G4RunManager::GetRunManager()->SetPrintProgress(100);
    // Get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();
         G4cout << "Using " << analysisManager->GetType() << G4endl;

    analysisManager->SetVerboseLevel(1);
    analysisManager->SetFirstHistoId(0);

    //histo
    // Create directories
    //analysisManager->SetHistoDirectoryName("histograms");
    //analysisManager->SetNtupleDirectoryName("ntuple");
    analysisManager->SetNtupleMerging(true);
    analysisManager->SetNtupleRowWise(false);
      // Note: merging ntuples is available only with Root output

    // Book histograms, ntuple
    //

    // Creating histograms
//    analysisManager->CreateH1("Eabs","Edep in absorber", 100, 0., 800*MeV);
//    analysisManager->CreateH1("Egap","Edep in gap", 100, 0., 100*MeV);
//    analysisManager->CreateH1("Labs","trackL in absorber", 100, 0., 1*m);
//    analysisManager->CreateH1("Lgap","trackL in gap", 100, 0., 50*cm);


    // Creating ntuple
    //
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
  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

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
   G4AccumulableManager* accumulableManager=G4AccumulableManager::Instance();
   accumulableManager->Merge();
   for (int i = 0; i < accumulateListSize; ++i) {
       accumulateValueList[i]=accumulateList[i].GetValue();
   }
  // print histogram statistics
  //
  auto analysisManager = G4AnalysisManager::Instance();


  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();
}

void RunAction::Accumulate(G4double *list)
{
    for (int i = 0; i < accumulateListSize; ++i) {
        accumulateList[i]+=list[i];
    }
}

void RunAction::DefineAccumulableManager()
{
    G4AccumulableManager* accumulableManager=G4AccumulableManager::Instance();
    for (int i = 0; i < accumulateListSize; ++i) {
        accumulableManager->RegisterAccumulable(accumulateList[i]);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
