#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4RandomDirection.hh"
#include "G4GeneralParticleSource.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction():G4VUserPrimaryGeneratorAction()
{
    fGeneralParticleGun=new G4GeneralParticleSource();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *event)
{
    DefineParticleGuns();
    fParticleGun->GeneratePrimaryVertex(event);
    fGeneralParticleGun->GeneratePrimaryVertex(event);

}

void PrimaryGeneratorAction::DefineParticleGun(G4int particleNumber, G4String particleName, G4ThreeVector particlePosition, G4ThreeVector particleDirection, G4double particleEnergy)
{

    fParticleGun=new G4ParticleGun(particleNumber);// 创建particleNumber个全同粒子。包括电荷、质量、方向等等。
    //fParticleGun->SetNumberOfParticles(particleNumber);
    fParticleGun->SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle(particleName));
    fParticleGun->SetParticlePosition(particlePosition);
    fParticleGun->SetParticleMomentumDirection(particleDirection.unit());// 方向向量需为单位向量
    //如果设置为点源，则可以将particleDirection传入为G4RandomDirection();
    fParticleGun->SetParticleEnergy(particleEnergy);
}

void PrimaryGeneratorAction::DefineParticleGuns()
{
    // TODO: load configuration

    DefineParticleGun(1,"proton",G4ThreeVector(0,0,0),G4RandomDirection(),2*MeV);
}

G4ParticleGun *PrimaryGeneratorAction::GetParticleGun()
{
    return fParticleGun;
}

