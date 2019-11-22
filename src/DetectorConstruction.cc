/****************************************************************
* DetectorConstruction.cc
* Implementation file for class: DetectorConstruction
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

#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4EllipticalTube.hh"
#include "G4Torus.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4TessellatedSolid.hh"
#include "G4TriangularFacet.hh"
#include "G4QuadrangularFacet.hh"

#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4ExtrudedSolid.hh"
#include "G4ScaledSolid.hh"

#include <vector>
#include "G4ThreeVector.hh"

#include "G4GDMLParser.hh"
G4bool writeDose_ = false;
G4bool writeLET_  = false;
G4bool writeInter_= false;

extern std::vector<SensitiveVolume*>   listeVS_;

DetectorConstruction::DetectorConstruction()
    : solidWorld_(0),  logicWorld_(0),  physiWorld_(0),
      magneticField_(0)
{
    detectorMessenger_ = new DetectorMessenger(this);

    magneticField_ = new MagneticField();
}

DetectorConstruction::DetectorConstruction(G4String& GDMLfile)
    : solidWorld_(0),  logicWorld_(0),  physiWorld_(0),
      magneticField_(0)
{
    detectorMessenger_ = new DetectorMessenger(this);

    gdmlFileName_ = GDMLfile;

    magneticField_ = new MagneticField();
}

DetectorConstruction::~DetectorConstruction()
{
    if (detectorMessenger_)
    {
        delete detectorMessenger_;
    }

    if (magneticField_)
    {
        delete magneticField_;
    }
}
void DetectorConstruction::CreateSensitiveVolume(	
    G4LogicalVolume* pLogicalVolume)	
{	
	// SV Data
	SensitiveVolume* pVSData = new SensitiveVolume(pLogicalVolume);
	pVSData->InitialisationDebutDuRun();
	
	// G4 SV
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
	
	G4String lgName = pLogicalVolume->GetName();
	int is = lgName.rfind("Logic");
	G4String SDname = lgName.substr(0, is) + "Detector";
	TrackerSD* pTrackerSD = new TrackerSD(SDname, pVSData);
	
	//Add
	SDman->AddNewDetector(pTrackerSD);
	pLogicalVolume->SetSensitiveDetector(pTrackerSD);
	
	// Info
	pVSData->detectorMass_ = (pLogicalVolume->GetMass() / CLHEP::kg);
	pVSData->pAssociatedDet_ = pTrackerSD;	
	listeVS_.push_back(pVSData);
}	

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    mat_.DefineMaterials();
    return GeometricalConstruction();
}

void DetectorConstruction::SetDetection(G4String det)
{
//-----------------------------------------------
// Sensitive detector

//	G4cout << "Sensitive Detector ..." << G4endl;

    G4SDManager* SDman = G4SDManager::GetSDMpointer();

    if (!SDman) return;

//--------------------------------------------------------------------------

    G4String SDname;

//--------------------------------------------------------------------------

    writeDose_  = false;
    writeLET_   = false;
    writeInter_ = false;

//--------------------------------------------------------------------------

    if (   det == "dose"
        || det == "Dose"
        || det == "DOSE")
    {
        // Ajout
        for (int i = 0; i<listeVS_.size(); i++)
        {
                TrackerSD* pTrackerSD = new TrackerSD(listeVS_[i]->name_, listeVS_[i]);
                SDman->AddNewDetector(pTrackerSD);
                listeVS_[i]->pLogicialVolume_->SetSensitiveDetector(pTrackerSD);
        }

        writeDose_ = true;
    }

//--------------------------------------------------------------------------

    if (   det == "let"
        || det == "Let"
        || det == "LET")
    {
        // Ajout
        for (int i = 0; i<listeVS_.size(); i++)
        {
                LETSpectrum* pLETSpectrum = new LETSpectrum(listeVS_[i]->name_, listeVS_[i]);
                SDman->AddNewDetector(pLETSpectrum);
                listeVS_[i]->pLogicialVolume_->SetSensitiveDetector(pLETSpectrum);
        }

        writeLET_ = true;
    }

//--------------------------------------------------------------------------

    if (   det == "interactions"
        || det == "Interactions"
        || det == "INTERACTIONS")
    {
        // Ajout
        for (int i = 0; i<listeVS_.size(); i++)
        {
                Interactions* pInteractions = new Interactions(listeVS_[i]->name_, listeVS_[i]);
                SDman->AddNewDetector(pInteractions);
                listeVS_[i]->pLogicialVolume_->SetSensitiveDetector(pInteractions);
        }

        writeInter_ = true;
    }
}

void DetectorConstruction::SetMagneticField(G4double fieldValue)
{
    magneticField_->SetFieldValue(fieldValue);
}

void DetectorConstruction::UpdateGeometry()
{
    G4RunManager::GetRunManager()->DefineWorldVolume(GeometricalConstruction());
}

G4VPhysicalVolume* DetectorConstruction::GeometricalConstruction()
{
   G4GDMLParser parser;
   parser.Read(gdmlFileName_);
    physiWorld_ = (G4VPhysicalVolume *)parser.GetWorldVolume();
    if (!physiWorld_)
    {
        G4Exception(
            "World volume not set properly check your setup selection criteria or GDML input!",
            "Exc", FatalException, "Exc");
    }

    physiWorld_->GetLogicalVolume()->SetVisAttributes(G4VisAttributes::Invisible);

    //---------------------------------------------------------------------------
    // Sensitive(s) Detector(s)
    // Browse auxiliary map
    const G4GDMLAuxMapType* lAuxMap = parser.GetAuxMap();
    for (G4GDMLAuxMapType::const_iterator lIt = lAuxMap->begin(); lIt != lAuxMap->end(); ++lIt)
    {
         G4LogicalVolume* lLogicalVolume = lIt->first;
         const G4GDMLAuxListType& lLogicalVolumeAuxList = lIt->second;
         for (size_t lIdx = 0; lIdx < lLogicalVolumeAuxList.size(); ++lIdx)
         {
               if (lLogicalVolumeAuxList[lIdx].type == "SensitiveVolume" && lLogicalVolumeAuxList[lIdx].value == "true")
               {
    //-----------------------------------------------
    // Sensitive detector(s)

                     CreateSensitiveVolume(lLogicalVolume);
               }
         }
    }
//---------------------------------------------------------------------------

    return physiWorld_;
}
