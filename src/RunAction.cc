#include "RunAction.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
//#include "G4RootAnalysisManager.hh"
//以下三个头文件，载入那个就会生成对应格式的文件。而不需要更改下面G4AnalysisManager的具体实现类型。
#include "g4root.hh"
//#include "g4xml.hh"
//#include "g4csv.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction(G4int accumulateParsNum):G4UserRunAction()
{
    accumulateListSize=accumulateParsNum;
    DefineAccumulableManager();
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetFirstHistoId(1);
    analysisManager->CreateNtuple("tree","G4-tree");
    analysisManager->CreateNtupleDColumn("E");
    analysisManager->FinishNtuple();
    analysisManager->CreateH1("h1","h1",1000,0,2*MeV);
}

RunAction::~RunAction()
{
    delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction(const G4Run *run)
{
    //inform the runManager to save random number seed
    G4RunManager::GetRunManager()->SetRandomNumberStore(false);
    G4AccumulableManager* accumulableManager=G4AccumulableManager::Instance();
    accumulableManager->Reset();//accumulableManager can't be static.

    auto analysisManager=G4AnalysisManager::Instance();
    analysisManager->OpenFile("testOutput");

}

void RunAction::EndOfRunAction(const G4Run *run)
{
    G4int nEvent=run->GetNumberOfEvent();
    if(nEvent == 0) return;
    G4AccumulableManager* accumulableManager=G4AccumulableManager::Instance();
    accumulableManager->Merge();

    for (int i = 0; i < accumulateListSize; ++i) {
        accumulateValueList[i]=accumulateList[i].GetValue();
    }
    auto analysisManager=G4AnalysisManager::Instance();

    analysisManager->Write();
    analysisManager->CloseFile();
}

void RunAction::DefineAccumulableManager()
{
    G4AccumulableManager* accumulableManager=G4AccumulableManager::Instance();
    for (int i = 0; i < accumulateListSize; ++i) {
        accumulableManager->RegisterAccumulable(accumulateList[i]);
    }
}

G4double *RunAction::GetAccumulateValue()
{
    return accumulateValueList;
}

int RunAction::GetAccumulateValueCount()
{
    return accumulateListSize;
}

void RunAction::Accumulate(G4double *list)
{
    for (int i = 0; i < accumulateListSize; ++i) {
        accumulateList[i]+=list[i];
    }
}
