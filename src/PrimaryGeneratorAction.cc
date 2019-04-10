#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction():G4VUserPrimaryGeneratorAction()
{

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *event)
{
    DefineParticleGuns();
    fParticleGun->GeneratePrimaryVertex(event);
}

void PrimaryGeneratorAction::DefineParticleGun(G4int particleNumber, G4String particleName, G4ThreeVector particlePosition, G4ThreeVector particleDirection, G4double particleEnergy)
{
    fParticleGun=new G4ParticleGun(particleNumber);
    fParticleGun->SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle(particleName));
    fParticleGun->SetParticlePosition(particlePosition);
    fParticleGun->SetParticleMomentumDirection(particleDirection);
    fParticleGun->SetParticleEnergy(particleEnergy);
}

void PrimaryGeneratorAction::DefineParticleGuns()
{
    // TODO: load configuration

    DefineParticleGun(1,"proton",G4ThreeVector(1*cm,-1*cm,1*cm),G4ThreeVector(-1,0,1),3*MeV);
}

G4ParticleGun *PrimaryGeneratorAction::GetParticleGun()
{
    return fParticleGun;
}

