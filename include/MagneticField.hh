/****************************************************************
* MagneticField.hh
* Header file for class: MagneticField
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

#ifndef __MAGNETICFIELD_H__
#define __MAGNETICFIELD_H__ 1

// A class for control of the Magnetic Field of the detector.
// The field is assumed to be uniform.

#include "G4UniformMagField.hh"

class G4FieldManager;

class MagneticField : public G4UniformMagField
{
public:

    MagneticField(G4ThreeVector);  //  The value of the field
    MagneticField();               //  A zero field
    ~MagneticField();  

    //Set the field (fieldValue,0,0)
    void SetFieldValue(G4double fieldValue);
    void SetFieldValue(G4ThreeVector fieldVector);

    G4ThreeVector GetConstantFieldValue();

protected:

    // Find the global Field Manager
    G4FieldManager* GetGlobalFieldManager();
};

#endif
