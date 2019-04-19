// ****** unload ******
#ifndef HIT_HH
#define HIT_HH

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "tls.hh"
#include "G4Threading.hh"

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

    void SetTrackID (G4int trackid)     {fTrackID=trackid;}
    void SetEdep    (G4double edep)     {fEdep=edep;}
    void SetPos     (G4ThreeVector Pos) {fPos=Pos;}

    G4int           GetTrackID() const {return fTrackID;}
    G4double        GetEdep() const    {return fEdep;}
    G4ThreeVector   GetPos() const     {return fPos;}
private:
    G4int   fTrackID;
    G4double    fEdep;
    G4ThreeVector   fPos;
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
