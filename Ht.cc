/****************************************************************
* Main.cc
* Main program file for project: Ht
* (Geant4 compatible)
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

#include "RunManager.hh"

#include "PhysicsListMessenger.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "TrackingAction.hh"
#include "SteppingAction.hh"
#include "SteppingVerbose.hh"

#include "G4PhysListFactory.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"

#include "G4Timer.hh"

#include "G4UnitsTable.hh"

#include "VisManager.hh"

//----------------------------------------------------------------------------------------

G4String particleType_;
G4double incidentEnergy_;
G4int numberOfBeams_;

std::vector<SensitiveVolume*>   listeVS_;

//----------------------------------------------------------------------------------------

#include "Histogram.hh"
#include "LETSpectrum.hh"
#include "Interactions.hh"

extern G4bool writeDose_;
extern G4bool writeLET_;
extern G4bool writeInter_;

//----------------------------------------------------------------------------------------
// Running Times
G4Timer duration_;
G4Timer totalDuration_;

// Verbose
G4int verboseType_;

// RunManager
RunManager* pRunManager_;
G4VModularPhysicsList* pCurrentPhys_;

//----------------------------------------------------------------------------------------

int main(int argc,char** argv) 
{
    totalDuration_.Start();

    particleType_ = "proton";
    incidentEnergy_ = 10.00*CLHEP::MeV;

	verboseType_ = 1;

//-----------------------------------------------------------------------
// Verbose output class

    G4VSteppingVerbose::SetInstance(new SteppingVerbose);

//-----------------------------------------------------------------------
// Run manager

    pRunManager_ = NULL;
    pRunManager_ = new RunManager;

    if (!pRunManager_)
    {
        G4cout << "RunManager construction error" << G4endl;
        return 0;
    }

//-----------------------------------------------------------------------
// Geometry

    G4String GDMLfile = "Ht.gdml";

    DetectorConstruction* pDetecteur = NULL;

    pDetecteur = new DetectorConstruction(GDMLfile);

    if (!pDetecteur)
    {
        G4cout << "DetectorConstruction construction error" << G4endl;
        return 0;
    }

    pRunManager_->SetUserInitialization(pDetecteur);

//-----------------------------------------------------------------------
// Physics

    PhysicsListMessenger physicMessenger;    G4PhysListFactory factory;
    pCurrentPhys_ = factory.GetReferencePhysList("FTFP_BERT_HP");

    pRunManager_->SetUserInitialization(pCurrentPhys_);

//-----------------------------------------------------------------------
// Visualization

    VisManager* pVisManager = NULL;
    pVisManager = new VisManager;

    if (!pVisManager)
    {
        G4cout << "VisManager construction error" << G4endl;
        return 0;
    }

    pVisManager->Initialize();

//-----------------------------------------------------------------------
// User Actions

    pRunManager_->SetUserAction(new PrimaryGeneratorAction);
    pRunManager_->SetUserAction(new RunAction);
    pRunManager_->SetUserAction(new EventAction);
    pRunManager_->SetUserAction(new TrackingAction);
    pRunManager_->SetUserAction(new SteppingAction);
        
//-----------------------------------------------------------------------
// Get the pointer to the User Interface manager 

    G4UImanager* pUI = NULL;
    pUI = G4UImanager::GetUIpointer();  

    if (!pUI)
    {
        G4cout << "G4UImanager::GetUIpointer() error" << G4endl;
        return 0;
    }

//-----------------------------------------------------------------------

    {
        duration_.Start();

        numberOfBeams_ = 50;

//-----------------------------------------------------------------------

        G4String commande;
        char buf[1024];

//-----------------------------------------------------------------------

        pUI->ApplyCommand("/run/verbose 0");
        pUI->ApplyCommand("/event/verbose 0");

//-----------------------------------------------------------------------

        sprintf(buf,"/geom/update");
        commande = buf;
        pUI->ApplyCommand(commande);

//-----------------------------------------------------------------------

        sprintf(buf,"/phys/cuts/global/gamma %s", "1.E-6 m");
        commande = buf;
        pUI->ApplyCommand(commande);
        sprintf(buf,"/phys/cuts/global/electron %s", "2.E-6 m");
        commande = buf;
        pUI->ApplyCommand(commande);
        sprintf(buf,"/phys/cuts/global/positron %s", "10.E-6 m");
        commande = buf;
        pUI->ApplyCommand(commande);

//-----------------------------------------------------------------------
/*
        sprintf(buf,"/gun/particle %s", particleType_.data());
        commande = buf;
        pUI->ApplyCommand(commande);

        sprintf(buf,"/gun/energy %f MeV", incidentEnergy_);
        commande = buf;
        pUI->ApplyCommand(commande);
*/
        sprintf(buf,"/tracking/verbose %d", verboseType_);
        commande = buf;
        pUI->ApplyCommand(commande);

//-----------------------------------------------------------------------

        if (argc == 1)
        // Batch mode
        { 
//-----------------------------------------------------------------------

            pRunManager_->Initialize();

//-----------------------------------------------------------------------

            sprintf(buf,"/control/execute %s", "HtTrack.mac");
            commande = buf;
            pUI->ApplyCommand(commande);
        }
        else
        // Define (G)UI terminal for interactive mode  
        {
            // G4UIterminal is a (dumb) terminal.
            G4UIsession* pSession = 0;

#ifdef G4UI_USE_TCSH
            pSession = new G4UIterminal(new G4UItcsh);      
#else
            pSession = new G4UIterminal();
#endif

//-----------------------------------------------------------------------

            pRunManager_->Initialize();

//-----------------------------------------------------------------------

            sprintf(buf,"/control/execute %s", argv[1]);
            commande = buf;
            pUI->ApplyCommand(commande);

            pSession->SessionStart();

            delete pSession;
        }

//---------------------------------------------------------------------------

		for (unsigned int i = 0; i < listeVS_.size(); ++i)
		{
			if (writeDose_)
			{
				listeVS_[i]->WriteHistograms(i == 0);
			}
			else if (writeLET_)
			{
				listeVS_[i]->WriteSpectreLET(i == 0);
			}
			else if (writeInter_)
			{
				listeVS_[i]->WriteSpectreInter(i == 0);
			}
		}

//---------------------------------------------------------------------------
// Energy deposited on detector
/*
        G4cout << G4endl;
        G4cout << "Total energy deposited by protons on detector: " << G4BestUnit(depositedEnergyByProtons_, "Energy") << G4endl;
        G4cout << G4endl;

        G4cout << G4endl;
        G4cout << "Total energy deposited by protons on detector: " << G4BestUnit(depositedEnergyByGamma_, "Energy") << G4endl;
        G4cout << G4endl;

        G4cout << G4endl;
        G4cout << "Total energy deposited by protons on detector: " << G4BestUnit(depositedEnergyByElectrons_, "Energy") << G4endl;
        G4cout << G4endl;

//---------------------------------------------------------------------------
// Dose received by detector

        G4cout << G4endl;
        G4cout << "Detector's mass: " << detectorMass_ << " kg" << G4endl;
        G4cout << "Total proton's dose received by detector: " << (depositedEnergyByProtons_ / joule) / detectorMass_ << " Gray" << G4endl;
        G4cout << "Total proton's dose received by detector: " << 100*(depositedEnergyByProtons_ / joule) / detectorMass_ << " rad" << G4endl;
        G4cout << G4endl;

        G4cout << G4endl;
        G4cout << "Total gamma's dose received by detector: " << (depositedEnergyByGamma_ / joule) / detectorMass_ << " Gray" << G4endl;
        G4cout << "Total gamma's dose received by detector: " << 100*(depositedEnergyByGamma_ / joule) / detectorMass_ << " rad" << G4endl;
        G4cout << G4endl;

        G4cout << G4endl;
        G4cout << "Total electron's dose received by detector: " << (depositedEnergyByElectrons_ / joule) / detectorMass_ << " Gray" << G4endl;
        G4cout << "Total electron's dose received by detector: " << 100*(depositedEnergyByElectrons_ / joule) / detectorMass_ << " rad" << G4endl;
        G4cout << G4endl;
*/
//---------------------------------------------------------------------------

        duration_.Stop();

        G4cout << G4endl;
        G4cout << "Run Duration: " << duration_.GetRealElapsed()       << " s"  << G4endl;
        G4cout << "              " << duration_.GetRealElapsed()/60.   << " mn" << G4endl;
        G4cout << "              " << duration_.GetRealElapsed()/3600. << " h"  << G4endl;
        G4cout << G4endl;
    }

//---------------------------------------------------------------------------

    totalDuration_.Stop();

    G4cout << G4endl;
    G4cout << "Run Total Duration : " << totalDuration_.GetRealElapsed()       << " s"  << G4endl;
    G4cout << "                     " << totalDuration_.GetRealElapsed()/60.   << " mn" << G4endl;
    G4cout << "                     " << totalDuration_.GetRealElapsed()/3600. << " h"  << G4endl;
    G4cout << G4endl;

//---------------------------------------------------------------------------
// Job termination

    if (pVisManager)
    {
        delete pVisManager;
    }

    if (pRunManager_)
    {
        delete pRunManager_;
    }

//---------------------------------------------------------------------------

    return 0;
}
