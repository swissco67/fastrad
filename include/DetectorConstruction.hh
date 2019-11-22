/****************************************************************
* DetectorConstruction.hh
* Header file for class: DetectorConstruction
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

#ifndef __DETECTORCONSTRUCTION_H__
#define __DETECTORCONSTRUCTION_H__ 1

#include "globals.hh"

#include "DetectorMessenger.hh"
#include "MaterialDefinition.hh"
#include "MagneticField.hh"
#include "TrackerSD.hh"
#include "LETSpectrum.hh"
#include "Interactions.hh"

#include "G4VUserDetectorConstruction.hh"

#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"
#include "G4RunManager.hh"

#include "G4GeometryManager.hh"
#include "G4SDManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RegionStore.hh"

//-----------------------------------------------------------------------

class DetectorMessenger;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:

    DetectorConstruction();
    DetectorConstruction(G4String& GDMLfile);
    ~DetectorConstruction();

    G4VPhysicalVolume* Construct();
    G4VPhysicalVolume* GeometricalConstruction();

    void SetDetection(G4String);

    void SetMagneticField(G4double);

    void UpdateGeometry();

    void CreateSensitiveVolume(G4LogicalVolume* pLogicalVolume);

public:
    
    DetectorMessenger* detectorMessenger_;

    MaterialDefinition mat_;

    G4String       gdmlFileName_;
    G4Sphere*          solidWorld_;
    G4LogicalVolume*   logicWorld_;
    G4VPhysicalVolume* physiWorld_;

    MagneticField* magneticField_;
};

#endif
