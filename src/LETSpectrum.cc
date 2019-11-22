/****************************************************************
* LETSpectrum.cc
* Implementation file for class: LETSpectrum
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

#include "LETSpectrum.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "Histogram.hh"

//-------------------------------------------------

LETSpectrum::LETSpectrum(G4String name, SensitiveVolume* pVs)
	: G4VSensitiveDetector(name), pVSData_(pVs)
{
    G4String HCname;
    collectionName.insert(HCname=name);
}

LETSpectrum::~LETSpectrum(){ }

void LETSpectrum::Initialize(G4HCofThisEvent* HCE)
{
    pTrackerCollection_ = new TrackerHitsCollection
                                  (SensitiveDetectorName, collectionName[0]); 

    static G4int HCID = -1;
    
    if (HCID<0)
    { 
        HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); 
    }

    HCE->AddHitsCollection( HCID, pTrackerCollection_ ); 
}

G4bool LETSpectrum::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{
    G4double edep = aStep->GetTotalEnergyDeposit();
    G4double stepLength = aStep->GetStepLength();
    G4int trackID = aStep->GetTrack()->GetTrackID();

    G4String originVolume = aStep->GetTrack()->GetLogicalVolumeAtVertex()->GetName();

    if (edep == 0.) 
    {
//        return false;
    }

//-----------------------------------------------------------------------------

    TrackerHit* newHit = new TrackerHit();
    newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());

    newHit->SetStepLength(stepLength);
    newHit->SetEdep(edep);
    newHit->SetPos (aStep->GetPostStepPoint()->GetPosition());
    pTrackerCollection_->insert( newHit );

    const G4DynamicParticle* particleDyn = aStep->GetTrack()
                        ->GetDynamicParticle();

    G4ParticleDefinition* particleDef = particleDyn
                        ->GetDefinition();

    G4String particleName = particleDef
                        ->GetParticleName();
                                                                                               
//-----------------------------------------------------------------------------
// Histogram for energy

    // Primary
    if (trackID == 1)
    {
     if (!pVSData_->primaryLETAlreadyCounted_)
		{
			pVSData_->range_ = 0.*CLHEP::mm;
			pVSData_->primaryLETAlreadyCounted_ = true;

			pVSData_->nbLETPrimaries_++;

			pVSData_->depositedEnergyLET_ = 0.*CLHEP::MeV;
		}

		//-----------------------------------------------------------------------------
		// Deposited energy in the detector

		pVSData_->depositedEnergyLET_ += edep;

		//-----------------------------------------------------------------------------
		// Track length in the detector

		pVSData_->range_ += (stepLength / CLHEP::mm);
	}

//    newHit->Print();
//    newHit->Draw();

    return true;
}

void LETSpectrum::EndOfEvent(G4HCofThisEvent* )
{
        G4int nbHits = pTrackerCollection_->entries();

        pVSData_->nbHitsTotal_ += nbHits;

/*     
        G4cout << "\n-------->Hits Collection: in this event they are " << nbHits 
               << " hits in the Silicon Detector " << G4endl;
*/
/*            
        for (G4int i=0;i<nbHits;i++) 
        {
            (*trackerCollection)[i]->Print();
        }
*/
}

void LETSpectrum::Clear()
{
}

void LETSpectrum::PrintAll()
{
}
