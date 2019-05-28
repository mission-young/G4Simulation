// ********* unload ******
#include "SDHit.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4UnitsTable.hh"
#include <iomanip>
#include "G4EventManager.hh"
#include "G4RunManager.hh"
G4ThreadLocal G4Allocator<SDHit>* HitAllocator=nullptr;

SDHit::SDHit():G4VHit(),fCopyID(-1),fIsHit(false),fEventID(-1),fTrackID(-1),fEdep(0.),fPos(G4ThreeVector(-999,-999,-999)),fxid(-1),fyid(-1)
{

}

SDHit::SDHit(const SDHit &right):G4VHit()
{
    fEventID  = right.fEventID;
    fTrackID  = right.fTrackID;
    fEdep     = right.fEdep;
    fPos      = right.fPos;
    fxid      = right.fxid;
    fyid      = right.fyid;
    fCopyID   = right.fCopyID;
    fIsHit    = right.fIsHit;
}

SDHit::~SDHit()
{

}

const SDHit &SDHit::operator=(const SDHit &right)
{
    fEventID  = right.fEventID;
    fTrackID  = right.fTrackID;
    fEdep     = right.fEdep;
    fPos      = right.fPos;
    fxid      = right.fxid;
    fyid      = right.fyid;
    fCopyID   = right.fCopyID;
    fIsHit    = right.fIsHit;
    return *this;
}

G4int SDHit::operator==(const SDHit &right) const
{
    return (this==&right)?1:0;
}

void SDHit::Draw()
{
    G4VVisManager* visManager=G4VVisManager::GetConcreteInstance();
    if(visManager){
        G4Circle circle(fPos);
        circle.SetScreenSize(4.);
        circle.SetFillStyle(G4Circle::filled);
        G4Colour colour(1,0,0);
        G4VisAttributes attribs(colour);
        circle.SetVisAttributes(attribs);
        visManager->Draw(circle);
    }
}

void SDHit::Print()
{
    G4cout<<fTrackID<<'\t'<<fPos.x()<<'\t'<<fPos.y()<<'\t'<<fPos.z()<<'\t'<<fEdep<<'\t'<<fxid<<'\t'<<fyid<<G4endl;
}

void SDHit::SetEventID()
{
    fEventID=G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
}

void SDHit::SetCopyID(G4Step *step)
{
    fCopyID=step->GetPreStepPoint()->GetTouchable()->GetCopyNumber();
}

void SDHit::SetPos(G4Step *step)
{
    fPos=step->GetPostStepPoint()->GetPosition();
}

void SDHit::AddEdep(G4double edep)
{
    fEdep+=edep;
}

void SDHit::SetEdep(G4double edep)
{
    fEdep=edep;
}

void SDHit::SetTrackID(G4Step *step)
{
    fTrackID=step->GetTrack()->GetTrackID();
}
