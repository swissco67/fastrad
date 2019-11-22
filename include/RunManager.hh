/****************************************************************
* RunManager.hh
* Header file for class: RunManager
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

#ifndef __RUNMANAGER_H__
#define __RUNMANAGER_H__ 1

#include "globals.hh"
#include "G4RunManager.hh"

#include "G4Timer.hh"

class RunManager : public G4RunManager
{

public:
    RunManager();
    virtual ~RunManager();

public:

   G4double GetTimeUsed();

public:

    inline void PhysicsListHasNotBeenChanged (G4bool bval)
    { 
        physicsInitialized = bval;
    };

private:

    G4Timer* timer;
    G4double timeused;
};

#endif
