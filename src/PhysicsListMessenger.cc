/****************************************************************
* PhysicsListMessenger.cc
* Implementation file for class: PhysicsListMessenger
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

#include "PhysicsListMessenger.hh"

#include "G4VModularPhysicsList.hh"
#include "G4PhysListFactory.hh"
#include "G4ios.hh"
#include "G4Tokenizer.hh"

#include "G4Electron.hh"
#include "G4Gamma.hh"
#include "G4Positron.hh"

#include <iomanip>
#include <sstream>
#include "G4MTRunManager.hh"

extern G4VModularPhysicsList* pCurrentPhys_;
extern G4MTRunManager* runManager;

//---------------------------------------------------------------------

PhysicsListMessenger::PhysicsListMessenger()
{
    physDir = new G4UIdirectory("/phys/");
    physDir->SetGuidance(" Controls of the physics processes");

    physListCmd = new G4UIcmdWithAString("/phys/list",this);
    physListCmd->SetGuidance(" Select the physic list");
    physListCmd->SetGuidance(" FTFP_BERT|FTFP_BERT_TRV|FTFP_BERT_HP			|FTFP_INCLXX|FTFP_INCLXX_HP|FTF_BIC|LBE|QBBC|QGSP_BERT|QGSP_BERT_HP			|QGSP_BIC|QGSP_BIC_HP|QGSP_FTFP_BERT|QGSP_INCLXX|QGSP_INCLXX_HP			|QGS_BIC|Shielding|ShieldingLEND[_EMV|_EMX|_EMY|_EMZ|_LIV|_PEN]");
    physListCmd->SetGuidance("Look at : http://geant4.cern.ch/support/proc_mod_catalog/physics_lists/referencePL.shtml ");

    physListCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

//--------------------------------------------------------------------------

    CutsDir = new G4UIdirectory("/phys/cuts/");
    CutsDir->SetGuidance("Controls to set the cuts.");

    CutsGlobalDir = new G4UIdirectory("/phys/cuts/global/");
    CutsGlobalDir->SetGuidance("Set the global cuts");

//--------------------------------------------------------------------------

    gDefaultCmd = new G4UIcmdWithADoubleAndUnit("/phys/cuts/global/default", this);
    gDefaultCmd->SetGuidance("Set default cut in range.");
    gDefaultCmd->SetGuidance("defaultCut unit");
    gDefaultCmd->SetParameterName("defaultCut",false);
    gDefaultCmd->SetRange("defaultCut > 0.0");
    gDefaultCmd->SetUnitCandidates("um mm cm m");
    gDefaultCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

//--------------------------------------------------------------------------

    gGammaCmd = new G4UIcmdWithADoubleAndUnit("/phys/cuts/global/gamma", this);
    gGammaCmd->SetGuidance("Set cut for gamma in range.");
    gGammaCmd->SetGuidance("gammaCut unit");
    gGammaCmd->SetParameterName("gammaCut",false);
    gGammaCmd->SetRange("gammaCut > 0.0");
    gGammaCmd->SetUnitCandidates("um mm cm m");
    gGammaCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    gElectronCmd = new G4UIcmdWithADoubleAndUnit("/phys/cuts/global/electron", this);
    gElectronCmd->SetGuidance("Set cut for electron in range.");
    gElectronCmd->SetGuidance("electronCut unit");
    gElectronCmd->SetParameterName("electronCut",false);
    gElectronCmd->SetRange("electronCut > 0.0");
    gElectronCmd->SetUnitCandidates("um mm cm m");
    gElectronCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    gPositronCmd = new G4UIcmdWithADoubleAndUnit("/phys/cuts/global/positron", this);
    gPositronCmd->SetGuidance("Set cut for positron in range.");
    gPositronCmd->SetGuidance("positronCut unit");
    gPositronCmd->SetParameterName("positronCut",false);
    gPositronCmd->SetRange("positronCut > 0.0");
    gPositronCmd->SetUnitCandidates("um mm cm m");
    gPositronCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

//--------------------------------------------------------------------------
}

PhysicsListMessenger::~PhysicsListMessenger()
{
    delete physDir;

    delete physListCmd;

    delete verboseCmd;

    delete CutsDir;
    delete CutsGlobalDir;

    delete gDefaultCmd;
    delete gGammaCmd;
    delete gElectronCmd;
    delete gPositronCmd;
}

void PhysicsListMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
    if (command == physListCmd)
    {
        G4PhysListFactory factory;
        pCurrentPhys_ = factory.GetReferencePhysList(newValue);
        if (pCurrentPhys_ == nullptr)
         G4Exception(__FILE__, "BadPhysListName", FatalErrorInArgument,
                     "Unknown physic");
    runManager->SetUserInitialization(pCurrentPhys_);
    }
    else if (command == verboseCmd)
    {
//        pPhysicsList->SetVerboseLevel(verboseCmd->GetNewIntValue(newValue));
    }
    else if (command == gDefaultCmd)
    {
        pCurrentPhys_->SetDefaultCutValue(gDefaultCmd->GetNewDoubleValue(newValue));
    }
    else if (command == gGammaCmd)
    {
        pCurrentPhys_->SetParticleCuts(gGammaCmd->GetNewDoubleValue(newValue), G4Gamma::Gamma());
    }
    else if (command == gElectronCmd)
    {
        pCurrentPhys_->SetParticleCuts(gElectronCmd->GetNewDoubleValue(newValue), G4Electron::Electron());
    }
    else if (command == gPositronCmd)
    {
        pCurrentPhys_->SetParticleCuts(gPositronCmd->GetNewDoubleValue(newValue), G4Positron::Positron());
    }
}
