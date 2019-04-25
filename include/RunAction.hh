#ifndef RUNACTION_HH
#define RUNACTION_HH


#include "G4UserRunAction.hh"
#include "globals.hh"
#include "Analysis.hh"
#include "dataStructure.hh"
class G4Run;


class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    virtual ~RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

public:

};



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif // RUNACTION_HH
