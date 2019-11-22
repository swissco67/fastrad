/****************************************************************
* Interactions.cc
* Implementation file for class: Interactions
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

#include "Interactions.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"


#include "Histogram.hh"
//-------------------------------------------------

Interactions::Interactions(G4String name, SensitiveVolume* pVs)
    : G4VSensitiveDetector(name), pVSData_(pVs)
{
    G4String HCname;
    collectionName.insert(HCname=name);
}

Interactions::~Interactions(){ }

void Interactions::Initialize(G4HCofThisEvent* HCE)
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

G4bool Interactions::ProcessHits(G4Step* aStep, G4TouchableHistory* )
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
                                                                                               

	G4int i;

	if (trackID==1)
	{
		if (!pVSData_->primaryInterAlreadyCounted_)
		{
			pVSData_->depositedEnergyInterByPrimaries_ = 0.*CLHEP::MeV;

			pVSData_->primaryInterAlreadyCounted_ = true;
			pVSData_->primaryName_.push_back(particleName);

			//------------------------------------------------------------------
			// Incident energy hiting the detector 

			pVSData_->primaryIncidentEnergy_.push_back(aStep->GetPreStepPoint()->GetKineticEnergy());

			//------------------------------------------------------------------
			// Incident energy histogram

			G4bool samplingParticle = false;

			for (i=0;i<pVSData_->histo_.nbEnergyInterGroups_ && !samplingParticle;i++)
			{
				if ( pVSData_->histo_.energyInterMinTab_[i] <= pVSData_->primaryIncidentEnergy_[pVSData_->nbInterPrimaries_]
					&& pVSData_->primaryIncidentEnergy_[pVSData_->nbInterPrimaries_] < pVSData_->histo_.energyInterMaxTab_[i])
				{
					pVSData_->histo_.nbPrimariesInterByEnergyGroup_[i]++;
					samplingParticle = true;
				}
			}

			// Values greater than maximum are pushed in an extra energy
			if (pVSData_->primaryIncidentEnergy_[pVSData_->nbInterPrimaries_] >=
					pVSData_->histo_.energyInterMaxTab_[pVSData_->histo_.nbEnergyInterGroups_-1])
			{
				pVSData_->histo_.nbPrimariesInterByEnergyGroup_[pVSData_->histo_.nbEnergyInterGroups_]++;
			}

		    pVSData_->primaryMomemtumX_.push_back(aStep->GetPreStepPoint()->GetMomentumDirection().x());
		    pVSData_->primaryMomemtumY_.push_back(aStep->GetPreStepPoint()->GetMomentumDirection().y());
		    pVSData_->primaryMomemtumZ_.push_back(aStep->GetPreStepPoint()->GetMomentumDirection().z());

			pVSData_->nbInterPrimaries_++;
		}
		//-----------------------------------------------------------------------------
		// Deposited energy in the detector

		pVSData_->depositedEnergyInterByPrimaries_ += edep;
	}

	else
	{
		if (trackID != pVSData_->previousID_)
		{
			if (pVSData_->nbInterSecondaries_)
			{
				if (pVSData_->originalVolume_ != pVSData_->name_)
				{
					pVSData_->energyInterSecondaries_.push_back(pVSData_->secondaryIncidentEnergy_/CLHEP::MeV);

					//-----------------------------------------------------------------------------
					// Incident energy histogram

					G4bool samplingParticle = false;

					for (i=0;i<pVSData_->histo_.nbEnergyInterGroups_ && !samplingParticle;i++)
					{
						if ( pVSData_->histo_.energyInterMinTab_[i] <=
								pVSData_->energyInterSecondaries_[pVSData_->nbSecondaries_]
						&& pVSData_->energyInterSecondaries_[pVSData_->nbSecondaries_] < pVSData_->histo_.energyInterMaxTab_[i])
						{
							pVSData_->histo_.nbSecondariesInterByEnergyGroup_[i]++;
							samplingParticle = true;
						}
					}

					// Values greater than maximum are pushed in an extra energy
					if (pVSData_->energyInterSecondaries_[pVSData_->nbSecondaries_] >=
							pVSData_->histo_.energyInterMaxTab_[pVSData_->histo_.nbEnergyInterGroups_-1])
					{
						pVSData_->histo_.nbSecondariesInterByEnergyGroup_[pVSData_->histo_.nbEnergyInterGroups_]++;
					}

					pVSData_->nbSecondaries_++;
				}
				pVSData_->secondaryDepositedEnergyInter_.push_back(pVSData_->depositedEnergyInterBySecondaries_);
				pVSData_->secondaryEventID_.push_back(pVSData_->evtID_+1);
			}
			pVSData_->depositedEnergyInterBySecondaries_ = 0.*CLHEP::MeV;
			pVSData_->previousID_ = trackID;
			pVSData_->nbInterSecondaries_++;
			pVSData_->secondaryInterAlreadyCounted_ = true;
			pVSData_->secondaryName_.push_back(particleName);

			//------------------------------------------------------------------
			// Incident energy hiting the detector 

			pVSData_->secondaryIncidentEnergy_ = aStep->GetPreStepPoint()->GetKineticEnergy();

			pVSData_->secondaryMomemtumX_.push_back(aStep->GetPreStepPoint()->GetMomentumDirection().x());
			pVSData_->secondaryMomemtumY_.push_back(aStep->GetPreStepPoint()->GetMomentumDirection().y());
			pVSData_->secondaryMomemtumZ_.push_back(aStep->GetPreStepPoint()->GetMomentumDirection().z());

			pVSData_->originalVolume_ = aStep->GetTrack()->GetLogicalVolumeAtVertex()->GetName();
			pVSData_->originVolume_.push_back(pVSData_->originalVolume_);
		}

		//--------------------------------------------------------------------
		// Deposited energy in the detector

		pVSData_->depositedEnergyInterBySecondaries_ += edep;
	}


//    newHit->Print();
//    newHit->Draw();

    return true;
}

void Interactions::EndOfEvent(G4HCofThisEvent* )
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

void Interactions::Clear()
{
}

void Interactions::PrintAll()
{
}
