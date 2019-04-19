#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "tls.hh"

#include "G4GlobalMagFieldMessenger.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4UserLimits;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    // Construct函数为在G4VUserDetectorConstruction中有实现。这里只需要重写，不需要在构造函数中调用。
    virtual G4VPhysicalVolume* Construct();
    virtual G4LogicalVolume* GetScoringVolume() const;
    void SetCheckOverlaps(G4bool checkOverLaps);
    virtual void ConstructSDandField();
private:
    void DefineMaterials();

    void DefineVolumes();

    void DefineWorldVolume(G4double x,G4double y,G4double z);
    void DefineTargetVolume();
    void DefineChamberVolume();
    void DefineOtherVolume();

    void DefineVisAttributes();

private:
    G4LogicalVolume* fScoringVolume;
    G4bool fCheckOverLaps;
    G4UserLimits* fStepLimit;
    G4LogicalVolume *logicWorld;
    G4VPhysicalVolume *physicsWorld;

    G4LogicalVolume*   fLogicTarget;
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger;
    //G4UserLimits* fStepLimit;
};

#endif // DETECTORCONSTRUCTION_HH
