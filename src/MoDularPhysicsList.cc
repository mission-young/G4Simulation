//****** unload *******
#include "MoDularPhysicsList.hh"
#include "G4DataQuestionaire.hh"
#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4HadronElasticPhysicsXS.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4SystemOfUnits.hh"
#include "G4RadioactiveDecayPhysics.hh"
MoDularPhysicsList::MoDularPhysicsList():G4VModularPhysicsList ()
{
    G4DataQuestionaire it(photon,neutron,no,no,no,neutronxs);
    G4cout << "<<< Geant4 Physics List: MyPhysicsList " <<G4endl;
    G4cout <<G4endl;
    defaultCutValue = 0.7*mm;
    SetVerboseLevel(1);
    // EM Physics
    RegisterPhysics( new G4EmStandardPhysics() );
    // Synchroton Radiation & GN Physics
    RegisterPhysics( new G4EmExtraPhysics() );
    // Decays
    RegisterPhysics( new G4DecayPhysics() );
    // Hadron physics
    RegisterPhysics( new G4HadronElasticPhysicsXS() );
    RegisterPhysics( new G4StoppingPhysics() );
    RegisterPhysics( new G4IonBinaryCascadePhysics() );
    RegisterPhysics( new G4HadronInelasticQBBC());
    // Neutron tracking cut
    RegisterPhysics( new G4NeutronTrackingCut() );
    RegisterPhysics(new G4RadioactiveDecayPhysics());
}
