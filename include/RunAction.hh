#ifndef RUNACTION_HH
#define RUNACTION_HH


#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4Accumulable.hh"
#include "G4AccumulableManager.hh"
#include "dataStructure.hh"
class G4Run;
struct detInfo{
int eventID[maxhit];
int trackID[maxhit];
int xid[maxhit];
int yid[maxhit];
double eDep[maxhit];
double posX[maxhit];
double posY[maxhit];
double posZ[maxhit];
};
class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    virtual ~RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

public:
    detInfo d[3];
    void clear();

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif // RUNACTION_HH
