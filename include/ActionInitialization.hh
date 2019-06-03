#ifndef ACTIONINITIALIZATION_HH
#define ACTIONINITIALIZATION_HH
#include "G4VUserActionInitialization.hh"

/// Action initialization class.
///

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization();
    virtual ~ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif // ACTIONINITIALIZATION_HH
