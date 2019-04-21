#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;


class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();
//optional
public:
    virtual G4LogicalVolume* GetScoringVolume() const{return fScoringVolume;}
    void SetCheckOverlaps(G4bool checkOverLaps){fCheckOverLaps=checkOverLaps;}

  private:

    void DefineMaterials();
    void DefineVolumes();
    void DefineWorldVolume(G4double x,G4double y,G4double z);
    void DefineTargetVolume();
    void DefineChamberVolume();
    void DefineOtherVolume();
    void DefineVisAttributes();
    void DefineSensitiveDetector();
    void DefineMagField();
    // xn,yn x,y的条数；xl,yl x,y的Si块宽度；xd,yd x,y的Si块间隔
    G4LogicalVolume* DefineDSSD(G4String name,G4int xn,G4int yn,G4double xl,G4double yl,G4double zl,G4double xd,G4double yd);
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger;
    G4bool  fCheckOverlaps;
private:
    G4VPhysicalVolume *physicsWorld;
    G4LogicalVolume *logicWorld;
    //G4LogicalVolume *calorLV;
    G4LogicalVolume *fScoringVolume;
    G4bool fCheckOverLaps;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif // DETECTORCONSTRUCTION_HH
