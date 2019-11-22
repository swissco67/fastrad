/****************************************************************
* SensitiveVolume.hh
* Header file for class: SensitiveVolume
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

#ifndef __SENSITIVEVOLUME_H__
#define __SENSITIVEVOLUME_H__ 1

#include "G4String.hh"

#include "Histogram.hh"

class G4LogicalVolume;
class G4VSensitiveDetector;
class G4Event;

class SensitiveVolume
{
public:
	SensitiveVolume(G4LogicalVolume* pLogicalVolume);
	~SensitiveVolume();

	void InitialisationDebutDuRun();
	void InitialisationDebutDuTir();

	void TraitementFinDuTir(const G4Event* evt);

	//---------------------------------------------------------------------

	void WriteHistograms(bool bWriteHeader);
	void WriteSpectreLET(bool bWriteHeader);
	void WriteSpectreInter(bool bWriteHeader);

	//---------------------------------------------------------------------
	//---------------------------------------------------------------------
	//---------------------------------------------------------------------

	G4double totalEnergy_;

	//---------------------------------------------------------------------
	// Dose in TrackerSD

	G4double totalDepositedEnergyByParticles_;
	G4double totalDepositedEnergyByPrimaries_;
	G4double totalDepositedEnergyBySecondaryGamma_;
	G4double totalDepositedEnergyBySecondaryElectrons_;

	std::vector<G4double> energyPrimaries_;
	std::vector<G4double> energySecondaryGamma_;
	std::vector<G4double> energySecondaryElectrons_;

	G4double depositedEnergyByParticles_;
	G4double depositedEnergyByPrimaries_;
	G4double depositedEnergyBySecondaryGamma_;
	G4double depositedEnergyBySecondaryElectrons_;

	G4double depositedEnergyInterByPrimaries_;
	G4double depositedEnergyInterBySecondaries_;

	G4int numberHit_;

	G4int nbParticles_;
	G4int nbPrimaries_;
	G4int nbNeutrons_;
	G4int nbSecondaryGamma_;
	G4int nbSecondaryElectrons_;
	G4int totalNbSecondaryGamma_;
	G4int totalNbSecondaryElectrons_;

	G4int nbInterPrimaries_;
	G4int nbInterSecondaries_;
	G4int nbSecondaries_;

	G4int nbHitsTotal_;

	// Tracking
	G4bool primaryAlreadyCounted_;
	G4bool secondaryGammaAlreadyCounted_;
	G4bool secondaryElectronAlreadyCounted_;
	G4bool primaryLETAlreadyCounted_;
	G4bool primaryInterAlreadyCounted_;
	G4bool secondaryInterAlreadyCounted_;

	G4int previousID_;
	G4int evtID_;

	//---------------------------------------------------------------------
	// SEU in SpectreLET

	std::vector<G4double> energyLET_;

	G4double depositedEnergyLET_;
	G4int nbLETPrimaries_;
	G4double range_;

	std::vector<G4double> primaryIncidentEnergy_;
	std::vector<G4double> secondaryDepositedEnergyInter_;
	G4double secondaryIncidentEnergy_;

	std::vector<G4String> primaryName_;
	std::vector<G4String> secondaryName_;
	std::vector<G4String> originVolume_;

	//---------------------------------------------------------------------
	// Nuclear Interacions

	G4String originalVolume_;

	std::vector<G4double> primaryDepositedEnergyInter_;

	std::vector<G4int> primaryEventID_;

	std::vector<G4double> primaryMomemtumX_;
	std::vector<G4double> primaryMomemtumY_;
	std::vector<G4double> primaryMomemtumZ_;
	std::vector<G4double> secondaryMomemtumX_;
	std::vector<G4double> secondaryMomemtumY_;
	std::vector<G4double> secondaryMomemtumZ_;

	std::vector<G4int> secondaryEventID_;
	std::vector<G4double> energyInterSecondaries_;

	//---------------------------------------------------------------------
	// Desc

	G4double detectorMass_;
	G4VSensitiveDetector* pAssociatedDet_;
	G4LogicalVolume* pLogicialVolume_;
	Histogram histo_;
	G4String name_;

};
#endif
