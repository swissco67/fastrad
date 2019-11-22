/****************************************************************
* Histogram.hh
* Header file for class: Histogram
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

#ifndef __HISTOGRAM_H__
#define __HISTOGRAM_H__ 1

#include "globals.hh"
#include "G4Timer.hh"
#include "G4ThreeVector.hh"
#include <iostream>
#include <vector>

using namespace std;


class Histogram
{
public:
	Histogram();
	virtual ~Histogram();

public:

// Fonctions diverses

	void InitialisationHistograms();

	void InitialisationEnergies();
	void InitialiseHistogramEnergy();
	void InitialiseHistogramLET();
	void InitialiseHistogramInter();

// Contenu

// Energy histogram

	G4double energyMin_;
	G4double energyMax_;
	std::vector<G4double> energyMinTab_;
	std::vector<G4double> energyMaxTab_;

	G4int nbEnergyGroups_;
	std::vector<G4int> nbPrimariesByEnergyGroup_;
	std::vector<G4int> nbSecondaryGammaByEnergyGroup_;
	std::vector<G4int> nbSecondaryElectronsByEnergyGroup_;

// LET histogram

	G4double energyLETMin_;
	G4double energyLETMax_;
	std::vector<G4double> energyLETMinTab_;
	std::vector<G4double> energyLETMaxTab_;

	G4int nbEnergyLETGroups_;
	std::vector<G4int> nbPrimariesLETByEnergyGroup_;

// Interactions histogram

	G4double energyInterMin_;
	G4double energyInterMax_;
	std::vector<G4double> energyInterMinTab_;
	std::vector<G4double> energyInterMaxTab_;

	G4int nbEnergyInterGroups_;
	std::vector<G4int> nbPrimariesInterByEnergyGroup_;
	std::vector<G4int> nbSecondariesInterByEnergyGroup_;

};

#endif
