// ****** unload ******
#ifndef SENSITIVEDETECTOR_HH
#define SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "SDHit.hh"
#include <vector>
class G4Step;
class G4HCofThisEvent;

class SensitiveDetector : public G4VSensitiveDetector
{
public:
    SensitiveDetector(const G4String& name,
                      const G4String& hitsCollectionName,
                      const int nofCells);
    virtual ~SensitiveDetector();

    virtual void Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step,G4TouchableHistory* history);
    virtual void EndOfEvent(G4HCofThisEvent* hitCollection);


private:
    HitsCollection* fHitsCollection;
    std::vector<SDHit*> singleSi;
    G4int fHitsCollectionID;
    G4int fNofCells;
};

#endif // SENSITIVEDETECTOR_HH
