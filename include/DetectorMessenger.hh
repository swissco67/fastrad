/****************************************************************
* DetectorMessenger.hh
* Header file for class: DetectorMessenger
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

#ifndef __DETECTORMESSENGER_H__
#define __DETECTORMESSENGER_H__ 1

#include "globals.hh"
#include "G4UImessenger.hh"

#include "DetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

class DetectorConstruction;

class DetectorMessenger : public G4UImessenger
{
public:
    DetectorMessenger(DetectorConstruction*);
   ~DetectorMessenger();

    void SetNewValue(G4UIcommand*, G4String);

private:
    DetectorConstruction* pDetectorConstruction_;

    G4UIdirectory* geomDir_;
    G4UIdirectory* magnDir_;

    G4UIcmdWithADoubleAndUnit* magnCmd_;

    G4UIcmdWithoutParameter*   updateCmd_;

    G4UIcmdWithAString*        detCmd_;
};

#endif
