/****************************************************************
* Histogram.cc
* Implementation file for class: Histogram
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

#include "Histogram.hh"
#include "CLHEP/Units/SystemOfUnits.h"

Histogram::Histogram()
{
}

Histogram::~Histogram()
{
}

//--------------------------------------------------------
//--------------------------------------------------------

void Histogram::InitialisationHistograms()
{
	InitialiseHistogramEnergy();
	InitialiseHistogramLET();
	InitialiseHistogramInter();
}

//--------------------------------------------------------
//--------------------------------------------------------

void Histogram::InitialisationEnergies()
{
	energyMin_ = 0.001000*CLHEP::MeV;
	energyMax_ = 2000.000000*CLHEP::MeV;
}

//--------------------------------------------------------
//--------------------------------------------------------

void Histogram::InitialiseHistogramEnergy()
{
	G4double eMin;
	G4double eMax;

	InitialisationEnergies();

	G4double stepE = 0.001000; // MeV

	energyMinTab_.clear();
	energyMaxTab_.clear();

	nbPrimariesByEnergyGroup_.clear();
	nbSecondaryGammaByEnergyGroup_.clear();
	nbSecondaryElectronsByEnergyGroup_.clear();

	nbEnergyGroups_ = 0;

	eMin = energyMin_;
	// Logarithmic stepping
	eMax = energyMin_*pow(10.,stepE);

	energyMinTab_.push_back(eMin);
	energyMaxTab_.push_back(eMax);

	nbPrimariesByEnergyGroup_.push_back(0);
	nbSecondaryGammaByEnergyGroup_.push_back(0);
	nbSecondaryElectronsByEnergyGroup_.push_back(0);
	nbEnergyGroups_++;

	while (eMax < energyMax_)
	{
		// Logarithmic stepping
		eMin = eMin*pow(10.,stepE);
		eMax = eMax*pow(10.,stepE);
		energyMinTab_.push_back(eMin);
		energyMaxTab_.push_back(eMax);

		nbPrimariesByEnergyGroup_.push_back(0);
		nbSecondaryGammaByEnergyGroup_.push_back(0);
		nbSecondaryElectronsByEnergyGroup_.push_back(0);
		nbEnergyGroups_++;
	}
	nbPrimariesByEnergyGroup_.push_back(0);
	nbSecondaryGammaByEnergyGroup_.push_back(0);
	nbSecondaryElectronsByEnergyGroup_.push_back(0);
}

//--------------------------------------------------------
//--------------------------------------------------------

void Histogram::InitialiseHistogramLET()
{
	G4double eLETMin;
	G4double eLETMax;

	energyLETMin_ = 0.000000;
	energyLETMax_ = 2000.000000;

	G4double stepLET = 0.100000; // MeV.cm2.g-1

	energyLETMinTab_.clear();
	energyLETMaxTab_.clear();

	nbPrimariesLETByEnergyGroup_.clear();

	nbEnergyLETGroups_ = 0;

	eLETMin = energyLETMin_;
	// Linear stepping
	eLETMax = energyLETMin_ + stepLET;

	energyLETMinTab_.push_back(eLETMin);
	energyLETMaxTab_.push_back(eLETMax);

	nbPrimariesLETByEnergyGroup_.push_back(0);

	nbEnergyLETGroups_++;

	while (eLETMax < energyLETMax_)
	{
		// Linear stepping
		eLETMin = eLETMin + stepLET;
		eLETMax = eLETMax + stepLET;
		energyLETMinTab_.push_back(eLETMin);
		energyLETMaxTab_.push_back(eLETMax);

		nbPrimariesLETByEnergyGroup_.push_back(0);
		nbEnergyLETGroups_++;
	}
	nbPrimariesLETByEnergyGroup_.push_back(0);
}
//--------------------------------------------------------
//--------------------------------------------------------

void Histogram::InitialiseHistogramInter()
{
	G4double eMin;
	G4double eMax;

	energyInterMin_ = 0.000000;
	energyInterMax_ = 2000.000000;

	G4double step = 0.100000; // MeV

	energyInterMinTab_.clear();
	energyInterMaxTab_.clear();
	nbPrimariesInterByEnergyGroup_.clear();
	nbSecondariesInterByEnergyGroup_.clear();

	nbEnergyInterGroups_ = 0;

	eMin = energyInterMin_;
	// Linear stepping
	eMax = energyInterMin_ + step;

	energyInterMinTab_.push_back(eMin);
	energyInterMaxTab_.push_back(eMax);

	nbPrimariesInterByEnergyGroup_.push_back(0);
	nbSecondariesInterByEnergyGroup_.push_back(0);

	nbEnergyInterGroups_++;

	while (eMax < energyInterMax_)
	{
		// Linear stepping
		eMin = eMin + step;
		eMax = eMax + step;
		energyInterMinTab_.push_back(eMin);
		energyInterMaxTab_.push_back(eMax);

		nbPrimariesInterByEnergyGroup_.push_back(0);
		nbSecondariesInterByEnergyGroup_.push_back(0);
		nbEnergyInterGroups_++;
	}
	nbPrimariesInterByEnergyGroup_.push_back(0);
	nbSecondariesInterByEnergyGroup_.push_back(0);
}

//--------------------------------------------------------
