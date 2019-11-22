/****************************************************************
* SteppingVerbose.hh
* Header file for class: SteppingVerbose
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

#ifndef __STEPPINGVERBOSE_H__
#define __STEPPINGVERBOSE_H__ 1

// This class manages the verbose outputs in G4SteppingManager.
// It inherits from G4SteppingVerbose.
// It shows how to extract informations during the tracking of a particle.

#include "G4SteppingVerbose.hh"

class SteppingVerbose : public G4SteppingVerbose
{
public:

    SteppingVerbose();
   ~SteppingVerbose();

    void StepInfo();
    void TrackingStarted();
};

#endif
