/****************************************************************
* TrackingAction.hh
* Header file for class: TrackingAction
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

#ifndef __TRACKINGACTION_HH__
#define __TRACKINGACTION_HH__ 1

#include "globals.hh"
#include "G4Track.hh"
#include "G4UserTrackingAction.hh"

class G4Track;

class TrackingAction : public G4UserTrackingAction
{
public:
    TrackingAction();
    ~TrackingAction();

public:
    void PreUserTrackingAction(const G4Track* pTrack);
    void PostUserTrackingAction(const G4Track* pTrack);
};

#endif
