/****************************************************************
* EventAction.hh
* Header file for class: EventAction
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

#ifndef __EVENTACTION_H__
#define __EVENTACTION_H__ 1

#include "G4UserEventAction.hh"

class RunAction;
class G4Event;

class EventAction : public G4UserEventAction
{
public:
    EventAction(RunAction* runAction);
   ~EventAction();

public:
    void BeginOfEventAction(const G4Event* event);
    void EndOfEventAction  (const G4Event* event);
};

#endif
