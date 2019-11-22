/****************************************************************
* TrackerSD.cc
* Implementation file for class: TrackerSD
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

#include "TrackerSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "Histogram.hh"

//-------------------------------------------------

TrackerSD::TrackerSD(G4String name, SensitiveVolume* pVs)
	: G4VSensitiveDetector(name), pVSData_(pVs)
{
    G4String HCname;
    collectionName.insert(HCname=name);
}

TrackerSD::~TrackerSD(){ }

void TrackerSD::Initialize(G4HCofThisEvent* HCE)
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

G4bool TrackerSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{
    G4double edep = aStep->GetTotalEnergyDeposit();
    G4int trackID = aStep->GetTrack()->GetTrackID();

    G4String originVolume = aStep->GetTrack()->GetLogicalVolumeAtVertex()->GetName();

    if (edep == 0.) 
    {
//        return false;
    }

//-----------------------------------------------------------------------------

    TrackerHit* newHit = new TrackerHit();
    newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());

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

	G4int i;

    // Primaries
    if (trackID == 1)
    {
     if (!pVSData_->primaryAlreadyCounted_)
		{
			pVSData_->depositedEnergyByPrimaries_ = 0.;
			pVSData_->primaryAlreadyCounted_ = true;
		}

		//-----------------------------------------------------------------------------
		// Deposited energy in the detector

		pVSData_->depositedEnergyByPrimaries_ += edep;
	}

    // Secondary gamma
    if (particleName == "gamma" && (trackID > 1))
    {
     if (trackID != pVSData_->previousID_)
		{
			if (pVSData_->nbSecondaryGamma_)
			{
				pVSData_->energySecondaryGamma_.push_back(pVSData_->depositedEnergyBySecondaryGamma_);

				//-----------------------------------------------------------------------------
				// Deposited energy histogram

				G4bool samplingParticle = false;

				for (i=0;i<pVSData_->histo_.nbEnergyGroups_ && !samplingParticle;i++)
				{
					if ( pVSData_->histo_.energyMinTab_[i] <= pVSData_->energySecondaryGamma_[pVSData_->nbSecondaryGamma_-1]
					&& pVSData_->energySecondaryGamma_[pVSData_->nbSecondaryGamma_-1] < pVSData_->histo_.energyMaxTab_[i])
					{
						pVSData_->histo_.nbSecondaryGammaByEnergyGroup_[i]++;
						samplingParticle = true;
					}
				}

				// Values greater than maximum are pushed in an extra energy group
				if (pVSData_->energySecondaryGamma_[pVSData_->nbSecondaryGamma_-1] >=
						pVSData_->histo_.energyMaxTab_[pVSData_->histo_.nbEnergyGroups_-1])
				{
					pVSData_->histo_.nbSecondaryGammaByEnergyGroup_[pVSData_->histo_.nbEnergyGroups_]++;
				}
			}
			pVSData_->depositedEnergyBySecondaryGamma_ = 0.;
			pVSData_->previousID_ = trackID;
			pVSData_->nbSecondaryGamma_++;
			pVSData_->secondaryGammaAlreadyCounted_ = true;
		}

		//-------------------------------------------------------------------------------
		// Deposited energy in the detector by secondaries

		pVSData_->totalDepositedEnergyBySecondaryGamma_ += edep;
		pVSData_->depositedEnergyBySecondaryGamma_ += edep;

	}

    // Secondary electron
    if (particleName == "e-" && (trackID > 1))
    {
     if (trackID != pVSData_->previousID_)
		{
			if (pVSData_->nbSecondaryElectrons_)
			{
				pVSData_->energySecondaryElectrons_.push_back(pVSData_->depositedEnergyBySecondaryElectrons_);

				//-----------------------------------------------------------------------------
				// Deposited energy histogram

				G4bool samplingParticle = false;

				for (i=0;i<pVSData_->histo_.nbEnergyGroups_ && !samplingParticle;i++)
				{
					if ( pVSData_->histo_.energyMinTab_[i] <= pVSData_->energySecondaryElectrons_[pVSData_->nbSecondaryElectrons_-1]
					&& pVSData_->energySecondaryElectrons_[pVSData_->nbSecondaryElectrons_-1] < pVSData_->histo_.energyMaxTab_[i])
					{
						pVSData_->histo_.nbSecondaryElectronsByEnergyGroup_[i]++;
						samplingParticle = true;
					}
				}

				// Values greater than maximum are pushed in an extra energy group
				if (pVSData_->energySecondaryElectrons_[pVSData_->nbSecondaryElectrons_-1] >=
						pVSData_->histo_.energyMaxTab_[pVSData_->histo_.nbEnergyGroups_-1])
				{
					pVSData_->histo_.nbSecondaryElectronsByEnergyGroup_[pVSData_->histo_.nbEnergyGroups_]++;
				}
			}
			pVSData_->depositedEnergyBySecondaryElectrons_ = 0.;
			pVSData_->previousID_ = trackID;
			pVSData_->nbSecondaryElectrons_++;
			pVSData_->secondaryElectronAlreadyCounted_ = true;
		}

		//-------------------------------------------------------------------------------
		// Deposited energy in the detector by secondaries

		pVSData_->totalDepositedEnergyBySecondaryElectrons_ += edep;
		pVSData_->depositedEnergyBySecondaryElectrons_ += edep;

	}

	// Neutrons
	if (particleName == "neutron")
	{
		if (trackID != pVSData_->previousID_)
		{
			pVSData_->nbNeutrons_++;
			pVSData_->previousID_ = trackID;
		}
	}

//    newHit->Print();
//    newHit->Draw();

    return true;
}

void TrackerSD::EndOfEvent(G4HCofThisEvent* )
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

void TrackerSD::Clear()
{
}

void TrackerSD::PrintAll()
{
}
