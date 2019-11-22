/****************************************************************
* TrackerHit.cc
* Implementation file for class: TrackerHit
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

#include "TrackerHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator<TrackerHit> TrackerHitAllocator;

TrackerHit::TrackerHit()
{
}

TrackerHit::~TrackerHit()
{
}

TrackerHit::TrackerHit(const TrackerHit& right)
	: G4VHit()
{
    stepLength = right.stepLength;
    trackID    = right.trackID;
    edep       = right.edep;
    pos        = right.pos;
}

const TrackerHit& TrackerHit::operator=(const TrackerHit& right)
{
    stepLength = right.stepLength;
    trackID    = right.trackID;
    edep       = right.edep;
    pos        = right.pos;

    return *this;
}

int TrackerHit::operator==(const TrackerHit& ) const
{
    return 0;
}
void TrackerHit::Draw()
{
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

    if (pVVisManager)
    {
        G4Circle circle(pos);
        circle.SetScreenSize(0.04);
        circle.SetFillStyle(G4Circle::filled);

        G4Colour bleu(0.,0.,1.);

        G4VisAttributes attribs(bleu);
        circle.SetVisAttributes(attribs);
        pVVisManager->Draw(circle);
    }
}

void TrackerHit::Print()
{
    G4cout << "  trackID: " << trackID
           << "  energy deposit: " << G4BestUnit(edep,"Energy")
           << "  position: " << G4BestUnit(pos,"Length") << G4endl;
}
