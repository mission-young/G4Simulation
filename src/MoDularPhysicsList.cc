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

MoDularPhysicsList::MoDularPhysicsList():G4VModularPhysicsList ()
{
    G4DataQuestionaire it(photon,neutron,no,no,no,neutronxs);
    G4cout << "<<< Geant4 Physics List: MyPhysicsList " <<G4endl;
    G4cout <<G4endl;
    defaultCutValue = 0.7*mm;
    G4int ver = 1;
    SetVerboseLevel(ver);
    // EM Physics
    RegisterPhysics( new G4EmStandardPhysics(ver) );
    // Synchroton Radiation & GN Physics
    RegisterPhysics( new G4EmExtraPhysics(ver) );
    // Decays
    RegisterPhysics( new G4DecayPhysics(ver) );
    // Hadron physics
    RegisterPhysics( new G4HadronElasticPhysicsXS(ver) );
    RegisterPhysics( new G4StoppingPhysics(ver) );
    RegisterPhysics( new G4IonBinaryCascadePhysics(ver) );
    RegisterPhysics( new G4HadronInelasticQBBC(ver));
    // Neutron tracking cut
    RegisterPhysics( new G4NeutronTrackingCut(ver) );
}
