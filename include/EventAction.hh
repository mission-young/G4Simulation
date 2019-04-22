#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4UserEventAction.hh"

#include "G4THitsMap.hh"
#include "globals.hh"
#include "RunAction.hh"
/// Event action class
///
/// In EndOfEventAction(), it prints the accumulated quantities of the energy
/// deposit and track lengths of charged particles in Absober and Gap layers
/// stored in the hits collections.

class EventAction : public G4UserEventAction
{
public:
  EventAction(RunAction* runAction);
  virtual ~EventAction();

  virtual void  BeginOfEventAction(const G4Event* event);
  virtual void    EndOfEventAction(const G4Event* event);

  virtual void Accumulate(G4double *list);
private:
  // methods



  // data members
//  G4int  fAbsoEdepHCID;
//  G4int  fGapEdepHCID;
//  G4int  fAbsoTrackLengthHCID;
//  G4int  fGapTrackLengthHCID;
  RunAction *fRunAction;

  G4double *accumulateValueList;
  G4int accumulateValueCount;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif // EVENTACTION_HH
