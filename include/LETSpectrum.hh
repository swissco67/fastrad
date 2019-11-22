/****************************************************************
* LETSpectrum.hh
* Header file for class: LETSpectrum
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

#ifndef __LETSPECTRUM_H__
#define __LETSPECTRUM_H__ 1

#include "TrackerHit.hh"
#include "G4VSensitiveDetector.hh"

#include "G4VSensitiveDetector.hh"
#include <vector>
#include "G4Vector3D.hh"
#include "G4LogicalVolume.hh"
#include "TrackerSD.hh"

class G4Step;
class G4HCofThisEvent;

class LETSpectrum : public G4VSensitiveDetector
{
public:
    LETSpectrum(G4String, SensitiveVolume*);
    ~LETSpectrum();

    void Initialize(G4HCofThisEvent*);
    G4bool ProcessHits(G4Step*, G4TouchableHistory*);
    void EndOfEvent(G4HCofThisEvent*);
    void Clear();
    void PrintAll();

private:
    TrackerHitsCollection* pTrackerCollection_;
    SensitiveVolume* pVSData_;
};

#endif
