#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "G4AccumulableManager.hh"

class G4Run;

class RunAction:public G4UserRunAction
{
public:
    RunAction(G4int accumulateParsNum=0);
    virtual ~RunAction();
    virtual void BeginOfRunAction(const G4Run* run);
    virtual void EndOfRunAction(const G4Run* run);
    G4double* GetAccumulateValue();
    int GetAccumulateValueCount();
    void Accumulate(G4double *list);
private:
    virtual void DefineAccumulableManager();
private:
    G4Accumulable<G4double> accumulateList[10]={0,0,0,0,0,0,0,0,0,0}; //mark your accumulatelist
    // id:0 每一个event沉积的总能量
    G4int accumulateListSize;
    G4double accumulateValueList[10]={0,0,0,0,0,0,0,0,0,0};


};

#endif // RUNACTION_HH
