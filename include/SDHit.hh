// ****** unload ******
#ifndef HIT_HH
#define HIT_HH

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "tls.hh"
#include "G4Threading.hh"
#include "G4Step.hh"

class SDHit : public G4VHit
{
public:
    SDHit();
    SDHit(const SDHit& right);
    virtual ~SDHit();

    const SDHit& operator=(const SDHit& right);
    G4int operator==(const SDHit& right) const;

    inline void* operator new(size_t);
    inline void  operator delete(void* hit);

    virtual void Draw();
    virtual void Print();

    void SetEvent(G4Step* step);
    void SetPos(G4Step* step);
    void SetEdep(G4Step* step);
    void SetTrackID(G4Step* step);
    void SetEventID();
    void SetXid(int xid) {fxid=xid;}
    void SetYid(int yid) {fyid=yid;}
    void SetXYid(int xid,int yid){fxid=xid;fyid=yid;}
    void SetCopyID(G4Step* step);
    void SetCopyID(int copyid) {fCopyID=copyid;}
    void SetIsHit(G4bool ishit){fIsHit=ishit;}

    G4int           GetEventID() const {return fEventID;}
    G4int           GetTrackID() const {return fTrackID;}
    G4double        GetEdep() const    {return fEdep;}
    G4ThreeVector   GetPos() const     {return fPos;}
    G4int           GetXid() const     {return fxid;}
    G4int           GetYid() const     {return fyid;}
    G4int           GetCopyID() const  {return fCopyID;}
    G4bool          GetIsHit()  const  {return fIsHit;}
private:
    G4int   fCopyID;
    G4bool  fIsHit;
    G4int   fEventID;
    G4int   fTrackID;
    G4double fEdep;
    G4ThreeVector   fPos;
    G4int fxid;
    G4int fyid;
};

typedef G4THitsCollection<SDHit> HitsCollection;
extern  G4ThreadLocal G4Allocator<SDHit>* HitAllocator;

inline void* SDHit::operator new(size_t)
{
    if(!HitAllocator) HitAllocator=new G4Allocator<SDHit>;
    return (void*)HitAllocator->MallocSingle();
}


inline void SDHit::operator delete(void *hit)
{
    HitAllocator->FreeSingle((SDHit*)hit);
}
#endif // HIT_HH
