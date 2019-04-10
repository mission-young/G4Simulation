#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "G4RunManager.hh"


SteppingAction::SteppingAction(EventAction *eventAction):G4UserSteppingAction(),fEventAction(eventAction)
{

}

SteppingAction::~SteppingAction()
{

}

void SteppingAction::UserSteppingAction(const G4Step *step)
{
    const DetectorConstruction* det=static_cast<const DetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume=det->GetScoringVolume();
    G4LogicalVolume* volume=step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    if(volume!=fScoringVolume) return;
    G4double energy=step->GetTotalEnergyDeposit();
    fEventAction->Accumulate(&energy);
}
