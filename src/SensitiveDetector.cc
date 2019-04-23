#include "SensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ios.hh"
SensitiveDetector::SensitiveDetector(const G4String &name, const G4String &hitsCollectionName,int nofCells):G4VSensitiveDetector (name),fHitsCollection(nullptr),fHitsCollectionID(-1),fNofCells(nofCells)
{
    collectionName.insert(hitsCollectionName);
}

SensitiveDetector::~SensitiveDetector()
{

}

void SensitiveDetector::Initialize(G4HCofThisEvent *hitCollection)
{

    fHitsCollection=new HitsCollection(SensitiveDetectorName,collectionName[0]);
    fHitsCollectionID=G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hitCollection->AddHitsCollection(fHitsCollectionID,fHitsCollection);

    for (int i = 0; i < fNofCells; ++i) {
        fHitsCollection->insert(new SDHit());
    }
}

G4bool SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *history)
{
    G4double edep=step->GetTotalEnergyDeposit();

    if(edep==0.) return false;
    auto touchable=step->GetPreStepPoint()->GetTouchableHandle();
    int copyid=touchable->GetCopyNumber();
    int xid=copyid/16;
    int yid=copyid%16;
    SDHit *aHit=(*fHitsCollection)[copyid];
    aHit->SetEdep(step);
    aHit->SetPos(step);
    aHit->SetTrackID(step);
    aHit->SetEventID();
    aHit->SetXid(xid);
    aHit->SetYid(yid);
    aHit->SetCopyID(copyid);
    aHit->SetIsHit(true);
    return true;

}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent *hitCollection)
{

  if(verboseLevel>1){
        G4int nofHits=fHitsCollection->entries();
        G4cout<<G4endl
             <<"------->Hits Collection: in this event they are "<<nofHits
            <<" hits in the tracker chambers: "<<G4endl;
        for (G4int i=0;i<nofHits;i++) {if((*fHitsCollection)[i]->GetIsHit()) G4cout<<(*fHitsCollection)[i]->GetXid()<<'\t'<<(*fHitsCollection)[i]->GetYid()<<G4endl;}
 }
}

