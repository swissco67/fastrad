/****************************************************************
* TrackerHit.hh
* Header file for class: TrackerHit
* (Geant4 compatible class)
*
* Project: Ht
*
*
* Neither the authors of this software system, nor their employing 
* institutes,nor the agencies providing financial support for this 
* work  make  any representation or  warranty, express or implied, 
* regarding  this  software system or assume any liability for its 
* use.                                                             
*
*
* Creation: 2019/11/22 by Fastrad ((C) 2019)
* Last Modified: 
*****************************************************************/

#ifndef __TRACKERHIT_H__
#define __TRACKERHIT_H__ 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class TrackerHit : public G4VHit
{
public:

    TrackerHit();
    ~TrackerHit();

    TrackerHit(const TrackerHit&);

    const TrackerHit& operator=(const TrackerHit&);
    int operator==(const TrackerHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    void Draw();
    void Print();

public:

    void SetStepLength(G4double length)    { stepLength = length; };
    void SetTrackID   (G4int track)        { trackID = track; };
    void SetEdep      (G4double de)        { edep = de; };
    void SetPos       (G4ThreeVector xyz)  { pos = xyz; };

    G4double GetStepLength(){ return stepLength; };
    G4int GetTrackID()      { return trackID; };
    G4double GetEdep()      { return edep; };
    G4ThreeVector GetPos()  { return pos; };

private:

    G4double      stepLength;
    G4int         trackID;
    G4double      edep;
    G4ThreeVector pos;
};

typedef G4THitsCollection<TrackerHit> TrackerHitsCollection;

extern G4Allocator<TrackerHit> TrackerHitAllocator;

inline void* TrackerHit::operator new(size_t)
{
    void *aHit;
    aHit = (void *) TrackerHitAllocator.MallocSingle();
    return aHit;
}

inline void TrackerHit::operator delete(void *aHit)
{
    TrackerHitAllocator.FreeSingle((TrackerHit*) aHit);
}

#endif
