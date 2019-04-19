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
                      const G4String& hitsCollectionName);
    virtual ~SensitiveDetector();

    virtual void Initalize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step,G4TouchableHistory* history);
    virtual void EndOfEvent(G4HCofThisEvent* hitCollection);

private:
    HitsCollection* fHitsCollection;

};

#endif // SENSITIVEDETECTOR_HH
