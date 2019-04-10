#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

class G4ParticleGun;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();
    virtual void GeneratePrimaries(G4Event* event);
private:
    virtual void DefineParticleGun(G4int particleNumber,G4String particleName,G4ThreeVector particlePosition, G4ThreeVector particleDirection,G4double particleEnergy);
    virtual void DefineParticleGuns();
    virtual G4ParticleGun* GetParticleGun();
protected:
    G4ParticleGun *fParticleGun;
};

#endif // PRIMARYGENERATORACTION_HH
