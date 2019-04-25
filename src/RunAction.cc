#include "RunAction.hh"
#include "Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "EventAction.hh"
//#include "RootIO.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
 : G4UserRunAction()
{

    // set printing event number per each event
    G4RunManager::GetRunManager()->SetPrintProgress(1000);

    auto analysisManager=G4AnalysisManager::Instance();
    analysisManager->SetVerboseLevel(1);

    analysisManager->SetNtupleMerging(true);
    analysisManager->SetNtupleRowWise(false);

    analysisManager->CreateNtuple("tree","G4 simulation");
//    G4AutoLock l(&aMutex);
//    l.lock();
    init();
    for (int i = 0; i < maxhit; ++i) {
        for (int j = 0; j < 3; ++j) {
            char name[32];
            for (int k = 0; k < intInfo.size(); ++k) {
                sprintf(name,"%s_%03d_%s",intPars[j].first.data(),i,intInfo[k].first.data());
                analysisManager->CreateNtupleIColumn(name);
            }
            for (int k = 0; k < doubleInfo.size(); ++k) {
                sprintf(name,"%s_%03d_%s",doublePars[j].first.data(),i,doubleInfo[k].first.data());
                analysisManager->CreateNtupleDColumn(name);
            }
        }
    }
    analysisManager->FinishNtuple();
    clear();
 //   l.unlock();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
    delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
    auto analysisManager=G4AnalysisManager::Instance();
    G4String fileName="simu";
    analysisManager->OpenFile(fileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
    G4int nEvent=run->GetNumberOfEvent();
    if(nEvent==0) return;

    auto analysisManager=G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
