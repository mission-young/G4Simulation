#include "PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4RandomDirection.hh"
#include "G4IonTable.hh"
#include "G4UniformRandPool.hh"
#include "dataStructure.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(nullptr)
{
    fGeneralParticleGun=new G4GeneralParticleSource();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    DefineParticleGuns();
    fParticleGun->GeneratePrimaryVertex(event);
    fGeneralParticleGun->GeneratePrimaryVertex(event);
  // This function is called at the begining of event
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

    DefineParticleGun(maxhit,"proton",G4ThreeVector(0,0,-5*mm),G4RandomDirection(0.98), G4UniformRand()*10*MeV);

  //fParticleGun->SetParticleDefinition(G4ParticleTable::GetParticleTable()->GetIonTable()->GetIon(13,22));
    //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.4,0.2,1.1).unit());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

