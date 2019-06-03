#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4GeneralParticleSource.hh"
#include "RootIO.hh"
class G4ParticleGun;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction();
  virtual ~PrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event* event);

  // set methods
  void SetRandomFlag(G4bool value);
private:
  virtual void DefineParticleGun(G4int particleNumber,G4String particleName,G4ThreeVector particlePosition, G4ThreeVector particleDirection,G4double particleEnergy);

  virtual void DefineParticleGuns();
  virtual G4ParticleGun* GetParticleGun(){return fParticleGun;}
private:
  G4ParticleGun*  fParticleGun; // G4 particle gun
  G4GeneralParticleSource *fGeneralParticleGun;

  TH3F *pos3D;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif // PRIMARYGENERATORACTION_HH
