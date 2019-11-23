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

#include "PhysicsListMessenger.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "TrackingAction.hh"
#include "SteppingAction.hh"
#include "SteppingVerbose.hh"

#include "G4PhysListFactory.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"

#include "G4Timer.hh"

#include "G4UnitsTable.hh"

#include "VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4MTRunManager.hh"
#include "B1ActionInitialization.hh"

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
G4Timer totalDuration_;
G4Timer duration_;

// Verbose
G4int verboseType_;

G4VModularPhysicsList* pCurrentPhys_;

//----------------------------------------------------------------------------------------

int main(int argc,char** argv) 
{
    G4cout << "Start!!!" << G4endl;
    totalDuration_.Start();

    particleType_ = "proton";
    incidentEnergy_ = 10.00*CLHEP::MeV;

	verboseType_ = 1;

//-----------------------------------------------------------------------
// Verbose output class

    G4VSteppingVerbose::SetInstance(new SteppingVerbose);
    G4cout << "SteppingVerbose!!!" << G4endl;

//-----------------------------------------------------------------------
// Run manager
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    G4cout << "G4UIExecutive1!!!" << G4endl;
    ui = new G4UIExecutive(argc, argv);
    G4cout << "G4UIExecutive2!!!" << G4endl;
  }

  // Construct the default run manager
  //
  G4MTRunManager* runManager = new G4MTRunManager;

//-----------------------------------------------------------------------
// Geometry

    G4String GDMLfile = "Ht.gdml";
    G4cout << "GDMLfile!!!" << G4endl;

    DetectorConstruction* pDetecteur = NULL;

    pDetecteur = new DetectorConstruction(GDMLfile);

    if (!pDetecteur)
    {
        G4cout << "DetectorConstruction construction error" << G4endl;
        return 0;
    }

    runManager->SetUserInitialization(pDetecteur);
    G4cout << "DetectorConstruction!!!" << G4endl;

//-----------------------------------------------------------------------
// Physics

    PhysicsListMessenger physicMessenger;    G4PhysListFactory factory;
    pCurrentPhys_ = factory.GetReferencePhysList("FTFP_BERT_HP");

    runManager->SetUserInitialization(pCurrentPhys_);
    G4cout << "pCurrentPhys_!!!" << G4endl;

//-----------------------------------------------------------------------

// User action initialization
    runManager->SetUserInitialization(new B1ActionInitialization());
    G4cout << "B1ActionInitialization" << G4endl;
    
// Visualization

    VisManager* pVisManager = NULL;
    pVisManager = new VisManager;

    if (!pVisManager)
    {
        G4cout << "VisManager construction error" << G4endl;
        return 0;
    }

    pVisManager->Initialize();
    G4cout << "VisManager" << G4endl;
    
  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute HtTrack.mac");
    ui->SessionStart();
    delete ui;
  }

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


    totalDuration_.Stop();

    G4cout << G4endl;
    G4cout << "Run Total Duration : " << totalDuration_.GetRealElapsed()       << " s"  << G4endl;
    G4cout << "                     " << totalDuration_.GetRealElapsed()/60.   << " mn" << G4endl;
    G4cout << "                     " << totalDuration_.GetRealElapsed()/3600. << " h"  << G4endl;
    G4cout << G4endl;

    if (pVisManager)
    {
        delete pVisManager;
    }

    if (runManager)
    {
        delete runManager;
    }

    return 0;
}
