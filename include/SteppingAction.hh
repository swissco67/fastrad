/****************************************************************
* SteppingAction.hh
* Header file for class: SteppingAction
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

#ifndef __STEPPINGACTION_H__
#define __STEPPINGACTION_H__ 1

#include "G4UserSteppingAction.hh"
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
public:
    SteppingAction(EventAction* eventAction);
   ~SteppingAction(){};

    void UserSteppingAction(const G4Step*);
  private:
    EventAction*  fEventAction;
};

#endif
