/****************************************************************
* RunAction.hh
* Header file for class: RunAction
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

#ifndef __RUNACTION_H__
#define __RUNACTION_H__ 1

#include "globals.hh"
#include "G4UserRunAction.hh"

class G4Run;

class RunAction : public G4UserRunAction
{
public:
    RunAction();
   ~RunAction();

public:
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
};

#endif
