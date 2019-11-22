/****************************************************************
* MagneticField.cc
* Implementation file for class: MagneticField
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

#include "MagneticField.hh"

#include "G4FieldManager.hh"

MagneticField::MagneticField()
    : G4UniformMagField(G4ThreeVector())
{
    GetGlobalFieldManager()->SetDetectorField(this);
    GetGlobalFieldManager()->CreateChordFinder(this);
}

MagneticField::MagneticField(G4ThreeVector fieldVector)
  : G4UniformMagField(fieldVector)
{
    GetGlobalFieldManager()->SetDetectorField(this);    
    GetGlobalFieldManager()->CreateChordFinder(this);
}

// Set the value of the Global Field to fieldValue along X

void MagneticField::SetFieldValue(G4double fieldValue)
{
    G4UniformMagField::SetFieldValue(G4ThreeVector(fieldValue,0,0));
}

// Set the value of the Global Field

void MagneticField::SetFieldValue(G4ThreeVector fieldVector)
{
    // Find the Field Manager for the global field
    G4FieldManager* fieldMgr= GetGlobalFieldManager();
    
    if(fieldVector!=G4ThreeVector(0.,0.,0.))
	{ 
        G4UniformMagField::SetFieldValue(fieldVector);
        fieldMgr->SetDetectorField(this);
	} 
    else 
	{
        // If the new field's value is Zero, then it is best to
        // insure that it is not used for propagation.
        G4MagneticField* magField = NULL;
        fieldMgr->SetDetectorField(magField);
    }
}

MagneticField::~MagneticField()
{
//      GetGlobalFieldManager()->SetDetectorField(0);
}

#include "G4TransportationManager.hh"

G4FieldManager*  MagneticField::GetGlobalFieldManager()
{
    return G4TransportationManager::GetTransportationManager()->GetFieldManager();
}
