#include "EventAction.hh"
#include "Analysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction *runAction)
 : G4UserEventAction(),
   fRunAction(runAction)
{
    //optional
    accumulateValueList=fRunAction->GetAccumulateValue();
    accumulateValueCount=fRunAction->GetAccumulateValueCount();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4THitsMap<G4double>*
EventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
  auto hitsCollection
    = static_cast<G4THitsMap<G4double>*>(
        event->GetHCofThisEvent()->GetHC(hcID));

  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("EventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }

  return hitsCollection;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double EventAction::GetSum(G4THitsMap<G4double>* hitsMap) const
{
  G4double sumValue = 0.;
  for ( auto it : *hitsMap->GetMap() ) {
    // hitsMap->GetMap() returns the map of std::map<G4int, G4double*>
    sumValue += *(it.second);
  }
  return sumValue;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::PrintEventStatistics(
                            G4double absoEdep, G4double absoTrackLength,
                            G4double gapEdep, G4double gapTrackLength) const
{
  // Print event statistics
  //
  G4cout
     << "   Absorber: total energy: "
     << std::setw(7) << G4BestUnit(absoEdep, "Energy")
     << "       total track length: "
     << std::setw(7) << G4BestUnit(absoTrackLength, "Length")
     << G4endl
     << "        Gap: total energy: "
     << std::setw(7) << G4BestUnit(gapEdep, "Energy")
     << "       total track length: "
     << std::setw(7) << G4BestUnit(gapTrackLength, "Length")
     << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{
    for (int i = 0; i < accumulateValueCount; ++i) {
            accumulateValueList[i]=0;
        }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
   // Get hist collections IDs
//    if ( fAbsoEdepHCID == -1 ) {
//      fAbsoEdepHCID
//        = G4SDManager::GetSDMpointer()->GetCollectionID("Absorber/Edep");
//      fGapEdepHCID
//        = G4SDManager::GetSDMpointer()->GetCollectionID("Gap/Edep");
//      fAbsoTrackLengthHCID
//        = G4SDManager::GetSDMpointer()->GetCollectionID("Absorber/TrackLength");
//      fGapTrackLengthHCID
//        = G4SDManager::GetSDMpointer()->GetCollectionID("Gap/TrackLength");
//    }

  // Get sum values from hits collections
  //
//  auto absoEdep = GetSum(GetHitsCollection(fAbsoEdepHCID, event));
//  auto gapEdep = GetSum(GetHitsCollection(fGapEdepHCID, event));
  G4int DSSD142HCID=G4SDManager::GetSDMpointer()->GetCollectionID("DSSD142um/Edep");
  auto DSSD142E=GetSum(GetHitsCollection(DSSD142HCID,event));
  G4int DSSD40HCID=G4SDManager::GetSDMpointer()->GetCollectionID("DSSD40um/Edep");
  auto DSSD40E=GetSum(GetHitsCollection(DSSD40HCID,event));
  G4int DSSD304HCID=G4SDManager::GetSDMpointer()->GetCollectionID("DSSD304um/Edep");
  auto DSSD304E=GetSum(GetHitsCollection(DSSD304HCID,event));

//  auto absoTrackLength
//    = GetSum(GetHitsCollection(fAbsoTrackLengthHCID, event));
//  auto gapTrackLength
//    = GetSum(GetHitsCollection(fGapTrackLengthHCID, event));

  fRunAction->Accumulate(accumulateValueList);

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();


  // fill histograms
  //
//  analysisManager->FillH1(0, absoEdep);
//  analysisManager->FillH1(1, gapEdep);
//  analysisManager->FillH1(2, absoTrackLength);
//  analysisManager->FillH1(3, gapTrackLength);

  // fill ntuple
  //
//  analysisManager->FillNtupleDColumn(0, absoEdep);
//  analysisManager->FillNtupleDColumn(1, gapEdep);
//  analysisManager->FillNtupleDColumn(2, absoTrackLength);
//  analysisManager->FillNtupleDColumn(3, gapTrackLength);
  analysisManager->FillNtupleDColumn(0,accumulateValueList[0]);
  analysisManager->FillNtupleDColumn(1,DSSD142E);
  analysisManager->FillNtupleDColumn(2,DSSD40E);
  analysisManager->FillNtupleDColumn(3,DSSD304E);
  analysisManager->AddNtupleRow();

  //print per event (modulo n)
  //
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
//  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
//    G4cout << "---> End of event: " << eventID << G4endl;
//    PrintEventStatistics(absoEdep, absoTrackLength, gapEdep, gapTrackLength);
//  }
}

void EventAction::Accumulate(G4double *list)
{
    for (int i = 0; i < accumulateValueCount; ++i) {
        accumulateValueList[i]+=list[i];
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


