// ******** unload *******
#include "PhysicsList.hh"
#include "G4Proton.hh"
#include "G4Electron.hh"
#include "G4Gamma.hh"
#include "G4Positron.hh"
#include "G4Transportation.hh"
#include "G4PhysicsListHelper.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4RayleighScattering.hh"
#include "G4ProcessManager.hh"
#include "G4RadioactiveDecay.hh"

PhysicsList::PhysicsList()
{

}

void PhysicsList::ConstructParticle()
{
    G4Proton::ProtonDefinition();
    G4Electron::ElectronDefinition();
    G4Gamma::GammaDefinition();
    G4Positron::PositronDefinition();
}

void PhysicsList::ConstructProcess()
{

    AddTransportation();
    ConstructGammaEm();
}

void PhysicsList::SetCuts()
{
    SetDefaultCutValue(defaultCutValue);
}

void PhysicsList::ConstructGammaEm()
{
    G4PhysicsListHelper* ph=G4PhysicsListHelper::GetPhysicsListHelper();
    G4ParticleDefinition* gamma=G4Gamma::GammaDefinition();

    ph->RegisterProcess(new G4PhotoElectricEffect(),gamma);
    ph->RegisterProcess(new G4ComptonScattering(),gamma);
    ph->RegisterProcess(new G4GammaConversion(),gamma);
    ph->RegisterProcess(new G4RayleighScattering(),gamma);
}

void PhysicsList::ConstructDecay()
{
    G4ParticleDefinition* p=G4Proton::ProtonDefinition();
    G4ProcessManager *pm=p->GetProcessManager();
    pm->AddProcess(new G4RadioactiveDecay());

}

