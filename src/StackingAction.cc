#include "StackingAction.hh"
#include "G4Track.hh"
StackingAction::StackingAction():G4UserStackingAction ()
{

}

StackingAction::~StackingAction()
{

}

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(const G4Track *track)
{
    if(track->GetParentID()==0)   return fUrgent;
}
