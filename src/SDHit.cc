// ********* unload ******
#include "SDHit.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4UnitsTable.hh"
#include <iomanip>
G4ThreadLocal G4Allocator<SDHit>* HitAllocator=nullptr;

SDHit::SDHit():G4VHit(),fTrackID(-1),fEdep(0.),fPos(G4ThreeVector())
{

}

SDHit::SDHit(const SDHit &right):G4VHit()
{
    fTrackID  = right.fTrackID;
    fEdep     = right.fEdep;
    fPos      = right.fPos;
}

SDHit::~SDHit()
{

}

const SDHit &SDHit::operator=(const SDHit &right)
{
    fTrackID  = right.fTrackID;
    fEdep     = right.fEdep;
    fPos      = right.fPos;
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
    G4cout <<" trackID: "<<fTrackID<<" Edep: "<<std::setw(7)<< G4BestUnit(fEdep,"Energy")
          <<std::setw(7)<<G4BestUnit(fPos,"Length")<<G4endl;
}
