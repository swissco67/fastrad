/****************************************************************
* DetectorMessenger.cc
* Implementation file for class: DetectorMessenger
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

#include "DetectorMessenger.hh"

#include "G4ios.hh"
#include "G4Tokenizer.hh"

#include <iomanip>
#include <sstream>

//---------------------------------------------------------------------

DetectorMessenger::DetectorMessenger(DetectorConstruction* pGeom)
    : pDetectorConstruction_(pGeom)
{ 
    geomDir_ = new G4UIdirectory("/geom/");
    geomDir_->SetGuidance("Shielding Thickness Control");

    magnDir_ = new G4UIdirectory("/magn/");
    magnDir_->SetGuidance("Magnetic Filed Intensity Control.");

    detCmd_ = new G4UIcmdWithAString("/geom/detector",this);
    detCmd_->SetGuidance("Select a type of detection");
    detCmd_->SetGuidance("Dose");
    detCmd_->SetGuidance("LET");
    detCmd_->SetGuidance("Nuclear interactions");
    detCmd_->SetCandidates(" dose let interactions Dose Let Interactions DOSE LET INTERACTIONS ");
    detCmd_->AvailableForStates(G4State_PreInit,G4State_Idle);

    magnCmd_ = new G4UIcmdWithADoubleAndUnit("/magn/setField",this);
    magnCmd_->SetGuidance("Define Magnetic Field Intensity.");
    magnCmd_->SetGuidance("Magnetic field will be in X direction.");
    magnCmd_->SetParameterName("Bx",false);
    magnCmd_->SetDefaultUnit("tesla");
    magnCmd_->SetUnitCategory("Magnetic flux density");
    magnCmd_->AvailableForStates(G4State_PreInit,G4State_Idle);

    updateCmd_ = new G4UIcmdWithoutParameter("/geom/update",this);
    updateCmd_->SetGuidance("Update Geometry.");
    updateCmd_->SetGuidance("This command MUST be applied before \"beamOn\" ");
    updateCmd_->SetGuidance("if you changed geometrical value(s).");
    updateCmd_->AvailableForStates(G4State_Idle);
}

DetectorMessenger::~DetectorMessenger()
{
    delete magnCmd_;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if ( command == magnCmd_ )
    { 
        pDetectorConstruction_
          ->SetMagneticField(magnCmd_->GetNewDoubleValue(newValue));
    }

    if ( command == updateCmd_ )
    {
        pDetectorConstruction_->UpdateGeometry(); 
    }

    if ( command == detCmd_ )
	{
		pDetectorConstruction_->SetDetection(newValue);
	}
}
