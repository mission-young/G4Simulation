#ifndef RUNACTION_HH
#define RUNACTION_HH


#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4Accumulable.hh"
#include "G4AccumulableManager.hh"

class G4Run;
struct data
{
    double d0[16][16];
    double d1[16][16];
    double d2[16][16];
};
class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    virtual ~RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

public:
    data target;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif // RUNACTION_HH
