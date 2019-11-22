/****************************************************************
* SteppingAction.cc
* Implementation file for class: SteppingAction
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

#include "SteppingAction.hh"
#include "G4SteppingManager.hh"

#include "G4RunManager.hh"

SteppingAction::SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step* pStep)
{

    G4String particleName;

    if (pStep->GetTrack()->GetCurrentStepNumber() == 1)
    {
        particleName = pStep->GetTrack()
                            ->GetDynamicParticle()
                            ->GetDefinition()
                            ->GetParticleName();

//        G4cout << particleName << G4endl;
    }

}
