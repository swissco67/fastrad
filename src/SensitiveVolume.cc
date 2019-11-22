/****************************************************************
* SensitiveVolume.cc
* Implementation file for class: SensitiveVolume
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

#include "SensitiveVolume.hh"
#include "G4Event.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4LogicalVolume.hh"

extern G4Timer duration_;
extern G4Timer totalDuration_;

SensitiveVolume::SensitiveVolume(G4LogicalVolume* pLogicalVolume)
{
	pLogicialVolume_ = pLogicalVolume;
	name_ = pLogicialVolume_->GetName();
}

void SensitiveVolume::InitialisationDebutDuRun()
{
	nbHitsTotal_ = 0;
	nbParticles_ = 0;
	nbPrimaries_ = 0;
	nbNeutrons_ = 0;
	nbSecondaryGamma_ = 0;
	nbSecondaryElectrons_ = 0;
	totalNbSecondaryGamma_ = 0;
	totalNbSecondaryElectrons_ = 0;
	nbLETPrimaries_ = 0;
	nbInterPrimaries_ = 0;
	nbInterSecondaries_ = 0;
	nbSecondaries_ = 0;

	depositedEnergyByParticles_ = 0.*CLHEP::MeV;
	depositedEnergyByPrimaries_ = 0.*CLHEP::MeV;
	depositedEnergyBySecondaryGamma_ = 0.*CLHEP::MeV;
	depositedEnergyBySecondaryElectrons_ = 0.*CLHEP::MeV;
	depositedEnergyInterByPrimaries_ = 0.*CLHEP::MeV;
	depositedEnergyInterBySecondaries_ = 0.*CLHEP::MeV;

	totalDepositedEnergyByParticles_ = 0.*CLHEP::MeV;
	totalDepositedEnergyByPrimaries_ = 0.*CLHEP::MeV;
	totalDepositedEnergyBySecondaryGamma_ = 0.*CLHEP::MeV;
	totalDepositedEnergyBySecondaryElectrons_ = 0.*CLHEP::MeV;

	depositedEnergyLET_ = 0.*CLHEP::MeV;

	histo_.InitialisationHistograms();
}

void SensitiveVolume::InitialisationDebutDuTir()
{
	nbParticles_++;

	primaryAlreadyCounted_ = false;
	secondaryGammaAlreadyCounted_ = false;
	secondaryElectronAlreadyCounted_ = false;

	primaryLETAlreadyCounted_ = false;
	primaryInterAlreadyCounted_ = false;
	secondaryInterAlreadyCounted_ = false;

	previousID_ = 1;

	nbSecondaryGamma_ = 0;
	nbSecondaryElectrons_ = 0;
	nbInterSecondaries_ = 0;

	energySecondaryGamma_.clear();
	energySecondaryElectrons_.clear();
}

void SensitiveVolume::TraitementFinDuTir(const G4Event* evt)
{
	// Storage of particle's energy for each event
	G4int i;

	if (primaryAlreadyCounted_)
	{
		energyPrimaries_.push_back(depositedEnergyByPrimaries_);
		totalDepositedEnergyByPrimaries_ += depositedEnergyByPrimaries_;

		//--------------------------------------------------------------------
		// Deposited energy histogram

		G4bool samplingParticle = false;

		for (i = 0; i < histo_.nbEnergyGroups_ && !samplingParticle; i++)
		{
			if (histo_.energyMinTab_[i] <= energyPrimaries_[nbPrimaries_]
			    && energyPrimaries_[nbPrimaries_] < histo_.energyMaxTab_[i])
			{
				histo_.nbPrimariesByEnergyGroup_[i]++;
				samplingParticle = true;
			}
		}

		// Values greater than maximum are pushed in an extra energy group
		if (energyPrimaries_[nbPrimaries_] >=
		    histo_.energyMaxTab_[histo_.nbEnergyGroups_ - 1])
		{
			histo_.nbPrimariesByEnergyGroup_[histo_.nbEnergyGroups_]++;
		}

		nbPrimaries_++;
	}

	if (secondaryGammaAlreadyCounted_)
	{
		energySecondaryGamma_.push_back(depositedEnergyBySecondaryGamma_);

		//--------------------------------------------------------------------
		// Deposited energy histogram

		G4bool samplingParticle = false;

		for (i = 0; i < histo_.nbEnergyGroups_ && !samplingParticle; i++)
		{
			if (histo_.energyMinTab_[i] <= energySecondaryGamma_[nbSecondaryGamma_ - 1]
			    && energySecondaryGamma_[nbSecondaryGamma_ - 1] < histo_.energyMaxTab_[i])
			{
				histo_.nbSecondaryGammaByEnergyGroup_[i]++;
				samplingParticle = true;
			}
		}

		// Values greater than maximum are pushed in an extra energy group
		if (energySecondaryGamma_[nbSecondaryGamma_ - 1] >=
		    histo_.energyMaxTab_[histo_.nbEnergyGroups_ - 1])
		{
			histo_.nbSecondaryGammaByEnergyGroup_[histo_.nbEnergyGroups_]++;
		}

		totalNbSecondaryGamma_ += nbSecondaryGamma_;;
	}

	if (secondaryElectronAlreadyCounted_)
	{
		energySecondaryElectrons_.push_back(depositedEnergyBySecondaryElectrons_);

		//--------------------------------------------------------------------
		// Deposited energy histogram

		G4bool samplingParticle = false;

		for (i = 0; i < histo_.nbEnergyGroups_ && !samplingParticle; i++)
		{
			if (histo_.energyMinTab_[i] <= energySecondaryElectrons_[nbSecondaryElectrons_
			                                                         - 1]
			    && energySecondaryElectrons_[nbSecondaryElectrons_ - 1] <
			    histo_.energyMaxTab_[i])
			{
				histo_.nbSecondaryElectronsByEnergyGroup_[i]++;
				samplingParticle = true;
			}
		}

		// Values greater than maximum are pushed in an extra energy group
		if (energySecondaryElectrons_[nbSecondaryElectrons_ - 1] >=
		    histo_.energyMaxTab_[histo_.nbEnergyGroups_ - 1])
		{
			histo_.nbSecondaryElectronsByEnergyGroup_[histo_.nbEnergyGroups_]++;
		}

		totalNbSecondaryElectrons_ += nbSecondaryElectrons_;;
	}

	if (primaryLETAlreadyCounted_)
	{
		G4double DEDX = (depositedEnergyLET_ / CLHEP::MeV) / (range_ / CLHEP::cm);

		G4double densityAl = 2.700;
		DEDX = (DEDX / densityAl);

		// Storage of the spectre LET
		energyLET_.push_back(DEDX);

		//--------------------------------------------------------------------
		// LET histogram

		G4bool samplingParticle = false;

		for (i = 0; i < histo_.nbEnergyLETGroups_ && !samplingParticle; i++)
		{
			if (histo_.energyLETMinTab_[i] <= energyLET_[nbLETPrimaries_ - 1]
			    && energyLET_[nbLETPrimaries_ - 1] < histo_.energyLETMaxTab_[i])
			{
				histo_.nbPrimariesLETByEnergyGroup_[i]++;
				samplingParticle = true;
			}
		}

		// Values greater than maximum are pushed in an extra energy group
		if (energyLET_[nbLETPrimaries_ - 1] >=
		    histo_.energyLETMaxTab_[histo_.nbEnergyLETGroups_ - 1])
		{
			histo_.nbPrimariesLETByEnergyGroup_[histo_.nbEnergyLETGroups_]++;
		}
	}


	G4int event_id = evt->GetEventID();
	evtID_ = event_id;

	if (primaryInterAlreadyCounted_)
	{
		primaryDepositedEnergyInter_.push_back(depositedEnergyInterByPrimaries_);
		primaryEventID_.push_back(evtID_);
	}

	if (secondaryInterAlreadyCounted_)
	{
		if (originalVolume_ != name_)
		{
			energyInterSecondaries_.push_back(secondaryIncidentEnergy_ / CLHEP::MeV);

			//-----------------------------------------------------------------------------
			// Incident energy histogram

			G4bool samplingParticle = false;

			for (i = 0; i < histo_.nbEnergyInterGroups_ && !samplingParticle; i++)
			{
				if (histo_.energyInterMinTab_[i] <= energyInterSecondaries_[nbSecondaries_]
				    && energyInterSecondaries_[nbSecondaries_] < histo_.energyInterMaxTab_[i])
				{
					histo_.nbSecondariesInterByEnergyGroup_[i]++;
					samplingParticle = true;
				}
			}

			// Values greater than maximum are pushed in an extra energy group
			if (energyInterSecondaries_[nbSecondaries_] >=
			    histo_.energyInterMaxTab_[histo_.nbEnergyInterGroups_ - 1])
			{
				histo_.nbSecondariesInterByEnergyGroup_[histo_.nbEnergyInterGroups_]++;
			}

			nbSecondaries_++;
		}
		secondaryDepositedEnergyInter_.push_back(depositedEnergyInterBySecondaries_);
		secondaryEventID_.push_back(evtID_);
	}

}

//--------------------------------------------------------
//--------------------------------------------------------

void SensitiveVolume::WriteHistograms(bool bWriteHeader)
{
	G4int i;

	G4String nameResu;

	nameResu = "./Ht_resu.dat";

	FILE* resu;

	if (bWriteHeader)
	{
		resu = fopen(nameResu.data(), "w");

		struct tm* date;
		time_t now = time(NULL);
		date = localtime(&now);

		//--------------------------------------------------------

		fprintf(resu,
		        "#===========================================================================================\n");
		fprintf(resu, "#   GEANT4 - RESULT FILE			%i/%i/%i   %i:%i\n",
		        (date->tm_year) + 1900,
		        (date->tm_mon) + 1,
		        date->tm_mday,
		        date->tm_hour,
		        date->tm_min);
		fprintf(resu, "#\n");
		fprintf(resu, "# Project: Ht\n");
		fprintf(resu, "#\n");
		fprintf(resu, "# File: %s\n", nameResu.data());
		fprintf(resu, "#\n");
		fprintf(resu, "# Creation by Fastrad ((C) 2016)\n");
		fprintf(resu, "#\n");
		fprintf(resu,
		        "#===========================================================================================\n");
		fprintf(resu, "#\n");
	}
	else
	{
		resu = fopen(nameResu.data(), "a");
	}

	fprintf(resu, "# Sensitive volume name : %s \n", name_.c_str());

	fprintf(resu, "# Particle type : proton \n");
	fprintf(resu, "# Number of hit particles : %d \n", nbParticles_);
	fprintf(resu, "# Number of energy groups : %d \n", histo_.nbEnergyGroups_);

	//--------------------------------------------------------

	fprintf(resu, "#\n");
	fprintf(resu, "# Detector mass = %f kg\n", detectorMass_);  // kg
	fprintf(resu, "#\n");
	fprintf(resu, "# %d hit primaries\n", nbPrimaries_);
	fprintf(resu, "# %d hit neutrons\n", nbNeutrons_);
	fprintf(resu, "# %d hit secondary gamma\n", totalNbSecondaryGamma_);
	fprintf(resu, "# %d hit secondary electrons\n", totalNbSecondaryElectrons_);
	fprintf(resu, "# Total number of particles' steps in the detector : %d\n",
	        nbHitsTotal_);

	fprintf(resu, " \n");
	fprintf(resu, " \n");

	fprintf(resu, "# Deposited energy by primaries = %10.4f MeV (%10.4e J) \n",
	        totalDepositedEnergyByPrimaries_,
	        totalDepositedEnergyByPrimaries_ / CLHEP::joule);

	G4double dose = (totalDepositedEnergyByPrimaries_ / CLHEP::joule) /
	                detectorMass_;

	fprintf(resu, "# Total dose due to primaries = %10.4e Gy (%10.4e rad)\n",
	        dose, dose * 100);
	fprintf(resu, " \n");

	//--------------------------------------------------------

	fprintf(resu,
	        "# Deposited energy by secondary gamma = %10.4f MeV (%10.4e J) \n",
	        totalDepositedEnergyBySecondaryGamma_,
	        totalDepositedEnergyBySecondaryGamma_ / CLHEP::joule);

	dose = (totalDepositedEnergyBySecondaryGamma_ / CLHEP::joule) / detectorMass_;

	fprintf(resu, "# Total dose due to secondary gamma = %10.4e Gy (%10.4e rad)\n",
	        dose, dose * 100);
	fprintf(resu, " \n");

	//--------------------------------------------------------

	fprintf(resu,
	        "# Deposited energy by secondary electrons = %10.4f MeV (%10.4e J) \n",
	        totalDepositedEnergyBySecondaryElectrons_,
	        totalDepositedEnergyBySecondaryElectrons_ / CLHEP::joule);

	dose = (totalDepositedEnergyBySecondaryElectrons_ / CLHEP::joule) /
	       detectorMass_;

	fprintf(resu,
	        "# Total dose due to secondary electrons = %10.4e Gy (%10.4e rad)\n",
	        dose, dose * 100);
	fprintf(resu, " \n");

	//--------------------------------------------------------

	fprintf(resu, " \n");

	if (duration_.IsValid())
	{
		fprintf(resu, "# Run duration : %f s  \n", duration_.GetRealElapsed());
		fprintf(resu, "#                %f mn \n", duration_.GetRealElapsed() / 60.);
		fprintf(resu, "#                %f h  \n", duration_.GetRealElapsed() / 3600.);
	}

	fprintf(resu, " \n");

	//--------------------------------------------------------
	// Primary's histogram for energy

	fprintf(resu, "#   Gr       Energy       Energy    #Primaries\n");
	fprintf(resu, "#    -        (MeV)        (MeV)\n");

	G4int nbPrimaries_ = 0;
	for (i = 0; i < histo_.nbEnergyGroups_; i++)
	{
		fprintf(resu, " %5d %12f %12f %8d\n",
		        i + 1,
		        histo_.energyMinTab_[i],
		        histo_.energyMaxTab_[i],
		        histo_.nbPrimariesByEnergyGroup_[i]);

		nbPrimaries_ += histo_.nbPrimariesByEnergyGroup_[i];
	}
	fprintf(resu, " %5d     Energy_> %12f %8d\n",
	        histo_.nbEnergyGroups_ + 1,
	        histo_.energyMaxTab_[histo_.nbEnergyGroups_ - 1],
	        histo_.nbPrimariesByEnergyGroup_[histo_.nbEnergyGroups_]);
	nbPrimaries_ += histo_.nbPrimariesByEnergyGroup_[histo_.nbEnergyGroups_];

	fprintf(resu, "#    -        -            Total %8d primaries\n", nbPrimaries_);

	fprintf(resu, " \n");
	fprintf(resu, " \n");

	//--------------------------------------------------------
	// Secondary gamma's histogram for energy

	fprintf(resu,
	        "# This histogram represents secondary gamma particles created out of the detector\n");
	fprintf(resu, " \n");
	fprintf(resu, "#   Gr       Energy       Energy    #Secondary Gamma\n");
	fprintf(resu, "#    -        (MeV)        (MeV)\n");

	G4int nbSecondaryGamma_ = 0;
	for (i = 0; i < histo_.nbEnergyGroups_; i++)
	{
		fprintf(resu, " %5d %12f %12f     %8d\n",
		        i + 1,
		        histo_.energyMinTab_[i],
		        histo_.energyMaxTab_[i],
		        histo_.nbSecondaryGammaByEnergyGroup_[i]);

		nbSecondaryGamma_ += histo_.nbSecondaryGammaByEnergyGroup_[i];
	}
	fprintf(resu, " %5d     Energy_> %12f     %8d\n",
	        histo_.nbEnergyGroups_ + 1,
	        histo_.energyMaxTab_[histo_.nbEnergyGroups_ - 1],
	        histo_.nbSecondaryGammaByEnergyGroup_[histo_.nbEnergyGroups_]);
	nbSecondaryGamma_ +=
	    histo_.nbSecondaryGammaByEnergyGroup_[histo_.nbEnergyGroups_];

	fprintf(resu, "#    -        -            Total     %8d secondary gamma\n",
	        nbSecondaryGamma_);

	fprintf(resu, " \n");
	fprintf(resu, " \n");

	//--------------------------------------------------------
	// Secondary electron's histogram for energy

	fprintf(resu,
	        "# This histogram represents secondary electrons created out of the detector\n");
	fprintf(resu, " \n");
	fprintf(resu, "#   Gr       Energy       Energy    #Secondary Electron\n");
	fprintf(resu, "#    -        (MeV)        (MeV)\n");

	G4int nbSecondaryElectrons_ = 0;
	for (i = 0; i < histo_.nbEnergyGroups_; i++)
	{
		fprintf(resu, " %5d %12f %12f     %8d\n",
		        i + 1,
		        histo_.energyMinTab_[i],
		        histo_.energyMaxTab_[i],
		        histo_.nbSecondaryElectronsByEnergyGroup_[i]);

		nbSecondaryElectrons_ += histo_.nbSecondaryElectronsByEnergyGroup_[i];
	}
	fprintf(resu, " %5d     Energy_> %12f     %8d\n",
	        histo_.nbEnergyGroups_ + 1,
	        histo_.energyMaxTab_[histo_.nbEnergyGroups_ - 1],
	        histo_.nbSecondaryElectronsByEnergyGroup_[histo_.nbEnergyGroups_]);
	nbSecondaryElectrons_ +=
	    histo_.nbSecondaryElectronsByEnergyGroup_[histo_.nbEnergyGroups_];

	fprintf(resu, "#    -        -            Total     %8d secondary electrons\n",
	        nbSecondaryElectrons_);

	fprintf(resu, " \n");
	fprintf(resu, " \n");

	//--------------------------------------------------------

	fclose(resu);
}

//--------------------------------------------------------
//--------------------------------------------------------

void SensitiveVolume::WriteSpectreLET(bool bWriteHeader)
{
	G4int i;

	G4String nameLET;

	nameLET = "./LET_Spectrum.dat";

	FILE* spec;
	if (bWriteHeader)
	{
		spec = fopen(nameLET.data(), "w");

		struct tm* date;
		time_t now = time(NULL);
		date = localtime(&now);

		//--------------------------------------------------------

		fprintf(spec,
		        "#===========================================================================================\n");
		fprintf(spec, "#   GEANT4 - RESULT FILE			%i/%i/%i   %i:%i\n",
		        (date->tm_year) + 1900,
		        (date->tm_mon) + 1,
		        date->tm_mday,
		        date->tm_hour,
		        date->tm_min);
		fprintf(spec, "#\n");
		fprintf(spec, "# Project: Debug_carto_mca\n");
		fprintf(spec, "#\n");
		fprintf(spec, "# File: %s\n", nameLET.data());
		fprintf(spec, "#\n");
		fprintf(spec, "# Creation by Fastrad ((C) 2016)\n");
		fprintf(spec, "#\n");
		fprintf(spec,
		        "#===========================================================================================\n");
		fprintf(spec, "#\n");
	}
	else
	{
		spec = fopen(nameLET.data(), "a");
	}

	fprintf(spec, "#\n");

	fprintf(spec, "# Sensitive volume name : %s \n", name_.c_str());

	fprintf(spec, "# Particles' type : proton \n");
	fprintf(spec, "# Number of hit particles : %d \n", nbParticles_);
	fprintf(spec, "# Number of energy's groups  : %d \n", histo_.nbEnergyLETGroups_);
	fprintf(spec, "#\n");
	fprintf(spec, "# %d hit proton\n", nbLETPrimaries_);
	fprintf(spec, " \n");

	//--------------------------------------------------------
	// LET spectrum

	fprintf(spec, "#   Gr       Energy LET       Energy LET      # particles\n");
	fprintf(spec, "#    -        (MeV/g/cm2)      (MeV/g/cm2)\n");

	G4int nbLETPrimaries_ = 0;
	for (i = 0; i < histo_.nbEnergyLETGroups_; i++)
	{
		fprintf(spec, " %5d   %12f     %12f   %8d\n",
		        i + 1,
		        histo_.energyLETMinTab_[i],
		        histo_.energyLETMaxTab_[i],
		        histo_.nbPrimariesLETByEnergyGroup_[i]);

		nbLETPrimaries_ += histo_.nbPrimariesLETByEnergyGroup_[i];
	}
	fprintf(spec, " %5d     Energy_LET_>   %12f   %8d\n",
	        histo_.nbEnergyLETGroups_ + 1,
	        histo_.energyLETMaxTab_[histo_.nbEnergyLETGroups_ - 1],
	        histo_.nbPrimariesLETByEnergyGroup_[histo_.nbEnergyLETGroups_]);
	nbLETPrimaries_ += histo_.nbPrimariesLETByEnergyGroup_[histo_.nbEnergyLETGroups_];

	fprintf(spec, "#    -          -              Total %8d particles\n",
	        nbLETPrimaries_);

	fprintf(spec, " \n");
	fprintf(spec, " \n");

	//--------------------------------------------------------

	fclose(spec);
}

//--------------------------------------------------------
//--------------------------------------------------------

void SensitiveVolume::WriteSpectreInter(bool bWriteHeader)
{
	G4int i;

	G4String name;

	name = "./NuclearInteractions.dat";

	FILE* inter;
	if (bWriteHeader)
	{
		inter = fopen(name.data(), "w");

		struct tm* date;
		time_t now = time(NULL);
		date = localtime(&now);

		//--------------------------------------------------------

		fprintf(inter,
		        "#===========================================================================================\n");
		fprintf(inter, "#   GEANT4 - RESULT FILE			%i/%i/%i   %i:%i\n",
		        (date->tm_year) + 1900,
		        (date->tm_mon) + 1,
		        date->tm_mday,
		        date->tm_hour,
		        date->tm_min);
		fprintf(inter, "#\n");
		fprintf(inter, "# Project: Debug_carto_mca\n");
		fprintf(inter, "#\n");
		fprintf(inter, "# File: %s\n", name.data());
		fprintf(inter, "#\n");
		fprintf(inter, "# Creation by Fastrad ((C) 2016)\n");
		fprintf(inter, "#\n");
		fprintf(inter,
		        "#===========================================================================================\n");
		fprintf(inter, "#\n");
	}
	else
	{
		inter = fopen(name.data(), "a");
	}

	fprintf(inter, "#\n");

	fprintf(inter, "# Sensitive volume name : %s \n", name_.c_str());

	fprintf(inter, "# Particles' type : proton \n");
	fprintf(inter, "# Number of hit particles : %d \n", nbParticles_);
	fprintf(inter, "# Number of energy's groups  : %d \n", histo_.nbEnergyInterGroups_);
	fprintf(inter, "#\n");
	fprintf(inter, "# %d hit primaries\n", nbInterPrimaries_);
	fprintf(inter, "# %d hit secondaries\n", nbSecondaries_);
	fprintf(inter, " \n");

	//--------------------------------------------------------
	// Energy spectrum for primary particles

	fprintf(inter, "# This histogram represents primaries hiting the detector\n");
	fprintf(inter, " \n");
	fprintf(inter, "#   Gr       Energy       Energy    #Primaries\n");
	fprintf(inter, "#    -        (MeV)        (MeV)\n");

	G4int nbInterPrimaries_ = 0;
	for (i = 0; i < histo_.nbEnergyInterGroups_; i++)
	{
		fprintf(inter, " %5d %12f %12f %8d\n",
		        i + 1,
		        histo_.energyInterMinTab_[i],
		        histo_.energyInterMaxTab_[i],
		        histo_.nbPrimariesInterByEnergyGroup_[i]);

		nbInterPrimaries_ += histo_.nbPrimariesInterByEnergyGroup_[i];
	}
	fprintf(inter, " %5d     Energy_> %12f %8d\n",
	        histo_.nbEnergyInterGroups_ + 1,
	        histo_.energyInterMaxTab_[histo_.nbEnergyInterGroups_ - 1],
	        histo_.nbPrimariesInterByEnergyGroup_[histo_.nbEnergyInterGroups_]);

	nbInterPrimaries_ +=
	    histo_.nbPrimariesInterByEnergyGroup_[histo_.nbEnergyInterGroups_];

	fprintf(inter, "#    -        -            Total %8d primaries\n",
	        nbInterPrimaries_);

	fprintf(inter, "\n");
	fprintf(inter, "\n");

	//--------------------------------------------------------
	// Energy spectrum for secondary particles

	fprintf(inter,
	        "# This histogram represents secondaries created out of the detector\n");
	fprintf(inter, " \n");
	fprintf(inter, "#   Gr       Energy       Energy    #Secondaries\n");
	fprintf(inter, "#    -        (MeV)        (MeV)\n");

	G4int nbSecondaries_ = 0;
	for (i = 0; i < histo_.nbEnergyInterGroups_; i++)
	{
		fprintf(inter, " %5d %12f %12f %8d\n",
		        i + 1,
		        histo_.energyInterMinTab_[i],
		        histo_.energyInterMaxTab_[i],
		        histo_.nbSecondariesInterByEnergyGroup_[i]);

		nbSecondaries_ += histo_.nbSecondariesInterByEnergyGroup_[i];
	}
	fprintf(inter, " %5d     Energy_> %12f %8d\n",
	        histo_.nbEnergyInterGroups_ + 1,
	        histo_.energyInterMaxTab_[histo_.nbEnergyInterGroups_ - 1],
	        histo_.nbSecondariesInterByEnergyGroup_[histo_.nbEnergyInterGroups_]);

	nbSecondaries_ += histo_.nbSecondariesInterByEnergyGroup_[histo_.nbEnergyInterGroups_];

	fprintf(inter, "#    -        -            Total %8d secondaries\n",
	        nbSecondaries_);

	fprintf(inter, "\n");
	fprintf(inter, "\n");

	//--------------------------------------------------------
	// Details on primaries hiting the detector

	fprintf(inter, "# Details on primaries hiting the detector\n");

	for (i = 0; i < (int)primaryEventID_.size(); i++)
	{
		fprintf(inter,
		        "#####################################################################################################\n");
		fprintf(inter,
		        "# Primary : Event # Particle # Incident Energy # Deposited Energy # Momemtum \n");
		fprintf(inter, "#	  %7i", primaryEventID_[i]);
		fprintf(inter, "  %9s", primaryName_[i].data());
		fprintf(inter, "    %6.3f MeV", primaryIncidentEnergy_[i] / CLHEP::MeV);
		fprintf(inter, "        %4f MeV", primaryDepositedEnergyInter_[i] / CLHEP::MeV);
		fprintf(inter, "    (%f,", primaryMomemtumX_[i]);
		fprintf(inter, " %f,", primaryMomemtumY_[i]);
		fprintf(inter, " %f)\n", primaryMomemtumZ_[i]);
		fprintf(inter, "\n");

	}

	fprintf(inter, "\n");
	fprintf(inter, "\n");

	//--------------------------------------------------------
	// Details on secondaries hiting the detector

	fprintf(inter, "# Details on secondaries hiting the detector\n");

	for (i = 0; i < (int)secondaryEventID_.size(); i++)
	{
		fprintf(inter,
		        "#####################################################################################################\n");
		fprintf(inter,
		        "# Secondary : Event # Particle # Incident Energy # Deposited Energy # Origin Volume # Momemtum \n");
		fprintf(inter, "#	    %7i", secondaryEventID_[i]);
		fprintf(inter, "  %9s", secondaryName_[i].data());
		fprintf(inter, "    %6.3f MeV", energyInterSecondaries_[i] / CLHEP::MeV);
		fprintf(inter, "        %4f MeV",
		        secondaryDepositedEnergyInter_[i] / CLHEP::MeV);
		fprintf(inter, "     %13s", originVolume_[i].data());
		fprintf(inter, "    (%f,", secondaryMomemtumX_[i]);
		fprintf(inter, " %f,", secondaryMomemtumY_[i]);
		fprintf(inter, " %f)\n", secondaryMomemtumZ_[i]);
		fprintf(inter, "\n");

	}

	fprintf(inter, "\n");
	fprintf(inter, "\n");

	//--------------------------------------------------------

	fclose(inter);
}

