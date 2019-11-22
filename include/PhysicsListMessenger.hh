/****************************************************************
* PhysicsListMessenger.hh
* Header file for class: PhysicsListMessenger
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

#ifndef __PHYSICSLISTMESSENGER_H__
#define __PHYSICSLISTMESSENGER_H__ 1

#include "globals.hh"
#include "G4UImessenger.hh"

#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

class PhysicsListMessenger : public G4UImessenger
{
public:

    PhysicsListMessenger ();
    ~PhysicsListMessenger ();

    void SetNewValue (G4UIcommand*, G4String);

private:

    G4UIdirectory* physDir;

    G4UIcmdWithAString* physListCmd;

    G4UIdirectory* CutsDir;
    G4UIdirectory* CutsGlobalDir;

    G4UIcmdWithADoubleAndUnit* gDefaultCmd;
    G4UIcmdWithADoubleAndUnit* gGammaCmd;
    G4UIcmdWithADoubleAndUnit* gElectronCmd;
    G4UIcmdWithADoubleAndUnit* gPositronCmd;

    G4UIcmdWithAnInteger* verboseCmd;
};

#endif
