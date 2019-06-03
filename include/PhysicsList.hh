#ifndef PHYSICSLIST_HH
#define PHYSICSLIST_HH

#include "G4VUserPhysicsList.hh"

class PhysicsList : public G4VUserPhysicsList
{
public:
    PhysicsList();
    virtual void ConstructParticle();
    virtual void ConstructProcess();
    virtual void SetCuts();
    virtual void ConstructGammaEm();
    virtual void ConstructDecay();

};

#endif // PHYSICSLIST_HH
