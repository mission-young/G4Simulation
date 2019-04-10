#include "RunAction.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
RunAction::RunAction(G4int accumulateParsNum):G4UserRunAction ()
{
    accumulateListSize=accumulateParsNum;
    DefineAccumulableManager();
}

RunAction::~RunAction()
{

}

void RunAction::BeginOfRunAction(const G4Run *run)
{
    //inform the runManager to save random number seed
    G4RunManager::GetRunManager()->SetRandomNumberStore(false);
    accumulableManager->Reset();//accumulableManager can't be static.
}

void RunAction::EndOfRunAction(const G4Run *run)
{
    G4int nEvent=run->GetNumberOfEvent();
    if(nEvent == 0) return;
    accumulableManager->Merge();

    for (int i = 0; i < accumulateListSize; ++i) {
        accumulateValueList[i]=accumulateList[i].GetValue();
    }
}

void RunAction::DefineAccumulableManager()
{
    accumulableManager=G4AccumulableManager::Instance();
    if(accumulateListSize>0){
        accumulateValueList=new G4double[accumulateListSize];
    }
    for (int i = 0; i < accumulateListSize; ++i) {
        accumulateList[i]=0;
        accumulateValueList[i]=0;
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
