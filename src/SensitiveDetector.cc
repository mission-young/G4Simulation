#include "SensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ios.hh"
SensitiveDetector::SensitiveDetector(const G4String &name, const G4String &hitsCollectionName):G4VSensitiveDetector (name),fHitsCollection(nullptr)
{
    collectionName.insert(hitsCollectionName);
}

SensitiveDetector::~SensitiveDetector()
{

}

void SensitiveDetector::Initalize(G4HCofThisEvent *hitCollection)
{
    fHitsCollection=new HitsCollection(SensitiveDetectorName,collectionName[0]);
    G4int hcID=G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hitCollection->AddHitsCollection(hcID,fHitsCollection);
}

G4bool SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *history)
{
    G4double edep=step->GetTotalEnergyDeposit();
    if(edep==0.) return false;
    SDHit *newHit=new SDHit();
    newHit->SetTrackID(step->GetTrack()->GetTrackID());
    newHit->SetEdep(edep);
    newHit->SetPos(step->GetPostStepPoint()->GetPosition());
    fHitsCollection->insert(newHit);
    return true;

}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent *hitCollection)
{
    if(verboseLevel>1){
        G4int nofHits=fHitsCollection->entries();
        G4cout<<G4endl
             <<"------->Hits Collection: in this event they are "<<nofHits
            <<" hits in the tracker chambers: "<<G4endl;
        for (G4int i=0;i<nofHits;i++) (*fHitsCollection)[i]->Print();
    }
}
