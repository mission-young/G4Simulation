#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"


class G4ParticleGun;
class G4Event;
class G4GeneralParticleSource;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();
    // GeneratePrimaries父类中已有，此处重写
    virtual void GeneratePrimaries(G4Event* event);
private:
    virtual void DefineParticleGun(G4int particleNumber,G4String particleName,G4ThreeVector particlePosition, G4ThreeVector particleDirection,G4double particleEnergy);

    virtual void DefineParticleGuns();
    virtual G4ParticleGun* GetParticleGun();
protected:
    G4ParticleGun *fParticleGun;
    G4GeneralParticleSource *fGeneralParticleGun;
};

#endif // PRIMARYGENERATORACTION_HH
