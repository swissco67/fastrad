/****************************************************************
* RunManager.cc
* Implementation file for class: RunManager
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

#include "RunManager.hh"

RunManager::RunManager ()
    : timeused(0.)
{
    timer = new G4Timer();
    timer->Start();
}

RunManager::~RunManager()
{
    delete timer;
    G4cout << "Run Manager deleting... " << G4endl;
}

G4double RunManager::GetTimeUsed ()
{
    timer->Stop();
    timeused += (timer->GetUserElapsed() + timer->GetSystemElapsed() );
    timer->Start();
    return timeused;
}
